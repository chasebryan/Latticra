#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-plan.sh [options]

Options:
  --context-pack <file>      Stage-1 Nadia context pack
  --runtime-profile <file>   Stage-2 Nadia runtime profile
  --task <label>             Operator task label
  --output <dir>             Output directory for prompt plans

Creates Nadia Stage-3 prompt-plan metadata only. It does not evaluate prompts,
run a model, mutate source, execute tools, train, download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt plan: %s\n' "$1" >&2
  exit "${2:-1}"
}

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

field_or_unknown() {
  key="$1"
  file="$2"
  awk -F '=' -v key="$key" '
    $1 == key {
      val = $2
      for (i = 3; i <= NF; i++) val = val "=" $i
      print val
      found = 1
      exit
    }
    END {
      if (!found) print "unknown"
    }
  ' "$file"
}

CONTEXT_PACK=""
RUNTIME_PROFILE=""
TASK="latticra-development-planning"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --context-pack)
      [ "$#" -ge 2 ] || fail "missing value for --context-pack" 64
      CONTEXT_PACK="$2"
      shift 2
      ;;
    --runtime-profile)
      [ "$#" -ge 2 ] || fail "missing value for --runtime-profile" 64
      RUNTIME_PROFILE="$2"
      shift 2
      ;;
    --task)
      [ "$#" -ge 2 ] || fail "missing value for --task" 64
      TASK="$2"
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

if [ -z "$CONTEXT_PACK" ] && [ -f "reports/nadia/context-packs/latest-context-pack.txt" ]; then
  CONTEXT_PACK="reports/nadia/context-packs/latest-context-pack.txt"
fi

if [ -z "$RUNTIME_PROFILE" ] && [ -f "reports/nadia/runtime-profiles/latest-runtime-profile.txt" ]; then
  RUNTIME_PROFILE="reports/nadia/runtime-profiles/latest-runtime-profile.txt"
fi

[ -n "$CONTEXT_PACK" ] || fail "context pack is required" 64
[ -n "$RUNTIME_PROFILE" ] || fail "runtime profile is required" 64
[ -f "$CONTEXT_PACK" ] || fail "context pack not found: $CONTEXT_PACK" 66
[ -f "$RUNTIME_PROFILE" ] || fail "runtime profile not found: $RUNTIME_PROFILE" 66

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-plans"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_PLAN_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
PLAN="$OUT_DIR/nadia-prompt-plan-$TS.txt"

CONTEXT_PACK_ABS=$(cd "$(dirname -- "$CONTEXT_PACK")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$CONTEXT_PACK")")
RUNTIME_PROFILE_ABS=$(cd "$(dirname -- "$RUNTIME_PROFILE")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$RUNTIME_PROFILE")")

CONTEXT_MEASUREMENT=$(measure_file "$CONTEXT_PACK_ABS")
RUNTIME_MEASUREMENT=$(measure_file "$RUNTIME_PROFILE_ABS")
CONTEXT_STAGE=$(field_or_unknown stage "$CONTEXT_PACK_ABS")
RUNTIME_STAGE=$(field_or_unknown stage "$RUNTIME_PROFILE_ABS")
CONTEXT_FILES=$(field_or_unknown total_files "$CONTEXT_PACK_ABS")
RUNTIME_FAMILY=$(field_or_unknown runtime_family "$RUNTIME_PROFILE_ABS")
MODEL_FORMAT=$(field_or_unknown model_format "$RUNTIME_PROFILE_ABS")
MODEL_FILE_PRESENT=$(field_or_unknown model_file_present "$RUNTIME_PROFILE_ABS")

cat > "$PLAN" <<PLAN
NADIA PROMPT PLAN

timestamp_utc=$TS
system_name=Latticra Nadia
stage=3-developer-workbench-planning
output_dir=$OUT_DIR
task=$TASK

[inputs]
context_pack=$CONTEXT_PACK_ABS
context_pack_stage=$CONTEXT_STAGE
context_pack_measurement=$CONTEXT_MEASUREMENT
context_pack_total_files=$CONTEXT_FILES
runtime_profile=$RUNTIME_PROFILE_ABS
runtime_profile_stage=$RUNTIME_STAGE
runtime_profile_measurement=$RUNTIME_MEASUREMENT
runtime_family=$RUNTIME_FAMILY
model_format=$MODEL_FORMAT
model_file_present=$MODEL_FILE_PRESENT

[plan]
planning_mode=developer-workbench
intended_domain=software-development-systems-engineering-ai-development
context_use=reference-local-context-pack
runtime_use=reference-runtime-profile-only
prompt_plan_ready=1
prompt_text_materialized=0
prompt_evaluated=0

[authority]
offline_by_default=1
network_authority=0
model_runtime_invoked=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
self_modification_authority=0

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1

[operator_review]
requires_operator_review=1
requires_context_pack_review=1
requires_runtime_profile_review=1
requires_future_prompt_contract=1
PLAN

cp "$PLAN" "$OUT_DIR/latest-prompt-plan.txt"

printf 'NADIA_PROMPT_PLAN=%s\n' "$PLAN"
printf 'NADIA_PROMPT_PLAN_TASK=%s\n' "$TASK"
printf 'NADIA_PROMPT_EVALUATED=0\n'
