#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-context-pack.sh [--repo <dir>] [--output <dir>]

Creates a no-network Nadia Stage-1 local context pack from Latticra project files.
The pack is file inventory and measurement evidence only. It does not run a model,
embed text, mutate source, train, or use the network.
USAGE
}

fail() {
  printf 'nadia context pack: %s\n' "$1" >&2
  exit "${2:-1}"
}

REPO="."
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --repo)
      [ "$#" -ge 2 ] || fail "missing value for --repo" 64
      REPO="$2"
      shift 2
      ;;
    --output)
      [ "$#" -ge 2 ] || fail "missing value for --output" 64
      OUTPUT="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

[ -d "$REPO" ] || fail "repo directory not found: $REPO" 66

REPO_ROOT=$(CDPATH= cd -- "$REPO" && pwd -P)
if [ -z "$OUTPUT" ]; then
  OUTPUT="$REPO_ROOT/reports/nadia/context-packs"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_CONTEXT_PACK_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
PACK="$OUT_DIR/nadia-context-pack-$TS.txt"
INDEX="$OUT_DIR/nadia-context-file-index-$TS.tsv"
SORTED="$INDEX.sorted"

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

file_kind() {
  rel="$1"
  case "$rel" in
    *.md) printf 'markdown\n' ;;
    *.h|*.hpp) printf 'c_header\n' ;;
    *.c) printf 'c_source\n' ;;
    *.cpp|*.cc|*.cxx) printf 'cpp_source\n' ;;
    *.rs) printf 'rust_source\n' ;;
    *.sh) printf 'shell_guard\n' ;;
    *.toml) printf 'toml_config\n' ;;
    *.py) printf 'python_tool\n' ;;
    Makefile|*/Makefile) printf 'build_rule\n' ;;
    *) printf 'project_file\n' ;;
  esac
}

append_file() {
  abs="$1"
  [ -f "$abs" ] || return 0
  rel=${abs#"$REPO_ROOT"/}

  case "$rel" in
    .git/*|build/*|reports/nadia/context-packs/*|installer/latticra-installer/target/*|installer/latticra-installer-receipts/*|*.png|*.jpg|*.jpeg|*.pdf|*.docx|*.lock)
      return 0
      ;;
  esac

  lines=$(wc -l < "$abs" | tr -d ' ')
  bytes=$(wc -c < "$abs" | tr -d ' ')
  kind=$(file_kind "$rel")
  measurement=$(measure_file "$abs")
  printf '%s\t%s\t%s\t%s\t%s\n' "$rel" "$kind" "$lines" "$bytes" "$measurement" >> "$INDEX"
}

: > "$INDEX"

ROOTS="README.md STATUS.md SECURITY.md CONTRIBUTING.md docs include src tests scripts installer seal"
for root in $ROOTS; do
  if [ -f "$REPO_ROOT/$root" ]; then
    append_file "$REPO_ROOT/$root"
  elif [ -d "$REPO_ROOT/$root" ]; then
    find "$REPO_ROOT/$root" -type f | while IFS= read -r file; do
      append_file "$file"
    done
  fi
done

sort -u "$INDEX" > "$SORTED"
mv "$SORTED" "$INDEX"

total_files=$(wc -l < "$INDEX" | tr -d ' ')
total_lines=$(awk -F '\t' '{ sum += $3 } END { print sum + 0 }' "$INDEX")
total_bytes=$(awk -F '\t' '{ sum += $4 } END { print sum + 0 }' "$INDEX")

cat > "$PACK" <<PACK
NADIA LOCAL CONTEXT PACK

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=1-local-context-engine
repo_root=$REPO_ROOT
output_dir=$OUT_DIR
file_index=$INDEX

[authority]
offline_by_default=1
network_authority=0
model_runtime_present=0
model_weights_installed=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1

[inventory]
roots=README.md STATUS.md SECURITY.md CONTRIBUTING.md docs include src tests scripts installer seal
total_files=$total_files
total_lines=$total_lines
total_bytes=$total_bytes
index_format=path<TAB>kind<TAB>lines<TAB>bytes<TAB>measurement

[file_index]
PACK

cat "$INDEX" >> "$PACK"
cp "$PACK" "$OUT_DIR/latest-context-pack.txt"
cp "$INDEX" "$OUT_DIR/latest-file-index.tsv"

printf 'NADIA_CONTEXT_PACK=%s\n' "$PACK"
printf 'NADIA_FILE_INDEX=%s\n' "$INDEX"
printf 'NADIA_CONTEXT_FILES=%s\n' "$total_files"
