#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-runtime-profile.sh [options]

Options:
  --output <dir>           Output directory for runtime profiles
  --runtime <name>         Runtime family label (default: llama.cpp-compatible)
  --runtime-binary <path>  Optional local runtime binary path to record only
  --model <file>           Optional operator-provided local model file to measure
  --model-format <format>  Model format label (default: gguf)
  --context-tokens <n>     Context window tokens (default: 4096)
  --memory-mib <n>         Memory budget in MiB (default: 4096)
  --thread-policy <label>  Thread policy label (default: operator-selected)
  --gpu-policy <label>     GPU policy label (default: disabled-by-default)

Creates Nadia Stage-2 runtime-readiness metadata only. It does not run a model,
load weights, evaluate prompts, mutate source, train, download, or use network.
USAGE
}

fail() {
  printf 'nadia runtime profile: %s\n' "$1" >&2
  exit "${2:-1}"
}

is_uint() {
  case "$1" in
    ''|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
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

OUTPUT=""
RUNTIME_FAMILY="llama.cpp-compatible"
RUNTIME_BINARY="operator-provided-future"
MODEL_FILE=""
MODEL_FORMAT="gguf"
CONTEXT_TOKENS="4096"
MEMORY_MIB="4096"
THREAD_POLICY="operator-selected"
GPU_POLICY="disabled-by-default"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --output)
      [ "$#" -ge 2 ] || fail "missing value for --output" 64
      OUTPUT="$2"
      shift 2
      ;;
    --runtime)
      [ "$#" -ge 2 ] || fail "missing value for --runtime" 64
      RUNTIME_FAMILY="$2"
      shift 2
      ;;
    --runtime-binary)
      [ "$#" -ge 2 ] || fail "missing value for --runtime-binary" 64
      RUNTIME_BINARY="$2"
      shift 2
      ;;
    --model)
      [ "$#" -ge 2 ] || fail "missing value for --model" 64
      MODEL_FILE="$2"
      shift 2
      ;;
    --model-format)
      [ "$#" -ge 2 ] || fail "missing value for --model-format" 64
      MODEL_FORMAT="$2"
      shift 2
      ;;
    --context-tokens)
      [ "$#" -ge 2 ] || fail "missing value for --context-tokens" 64
      CONTEXT_TOKENS="$2"
      shift 2
      ;;
    --memory-mib)
      [ "$#" -ge 2 ] || fail "missing value for --memory-mib" 64
      MEMORY_MIB="$2"
      shift 2
      ;;
    --thread-policy)
      [ "$#" -ge 2 ] || fail "missing value for --thread-policy" 64
      THREAD_POLICY="$2"
      shift 2
      ;;
    --gpu-policy)
      [ "$#" -ge 2 ] || fail "missing value for --gpu-policy" 64
      GPU_POLICY="$2"
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

is_uint "$CONTEXT_TOKENS" || fail "context tokens must be an unsigned integer" 64
is_uint "$MEMORY_MIB" || fail "memory MiB must be an unsigned integer" 64
[ "$CONTEXT_TOKENS" -gt 0 ] || fail "context tokens must be greater than zero" 64
[ "$MEMORY_MIB" -gt 0 ] || fail "memory MiB must be greater than zero" 64

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/runtime-profiles"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_RUNTIME_PROFILE_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
PROFILE="$OUT_DIR/nadia-runtime-profile-$TS.txt"

MODEL_FILE_PRESENT=0
MODEL_FILE_BYTES=0
MODEL_FILE_MEASUREMENT="none"
MODEL_FILE_RECORDED="operator-provided-future"

if [ -n "$MODEL_FILE" ]; then
  [ -f "$MODEL_FILE" ] || fail "model file not found: $MODEL_FILE" 66
  MODEL_FILE_PRESENT=1
  MODEL_FILE_RECORDED=$(cd "$(dirname -- "$MODEL_FILE")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MODEL_FILE")")
  MODEL_FILE_BYTES=$(wc -c < "$MODEL_FILE_RECORDED" | tr -d ' ')
  MODEL_FILE_MEASUREMENT=$(measure_file "$MODEL_FILE_RECORDED")
fi

RUNTIME_BINARY_PRESENT=0
RUNTIME_BINARY_RECORDED="$RUNTIME_BINARY"
RUNTIME_BINARY_MEASUREMENT="none"
if [ "$RUNTIME_BINARY" != "operator-provided-future" ]; then
  [ -f "$RUNTIME_BINARY" ] || fail "runtime binary not found: $RUNTIME_BINARY" 66
  RUNTIME_BINARY_PRESENT=1
  RUNTIME_BINARY_RECORDED=$(cd "$(dirname -- "$RUNTIME_BINARY")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$RUNTIME_BINARY")")
  RUNTIME_BINARY_MEASUREMENT=$(measure_file "$RUNTIME_BINARY_RECORDED")
fi

cat > "$PROFILE" <<PROFILE
NADIA RUNTIME PROFILE

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=2-runtime-profile-boundary
output_dir=$OUT_DIR

[runtime]
runtime_family=$RUNTIME_FAMILY
runtime_binary=$RUNTIME_BINARY_RECORDED
runtime_binary_present=$RUNTIME_BINARY_PRESENT
runtime_binary_measurement=$RUNTIME_BINARY_MEASUREMENT
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile

[model]
model_format=$MODEL_FORMAT
model_file=$MODEL_FILE_RECORDED
model_file_present=$MODEL_FILE_PRESENT
model_file_bytes=$MODEL_FILE_BYTES
model_file_measurement=$MODEL_FILE_MEASUREMENT
model_file_copied=0
model_weights_installed=0

[budget]
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB
thread_policy=$THREAD_POLICY
gpu_policy=$GPU_POLICY

[authority]
offline_by_default=1
network_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
self_modification_authority=0

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1
PROFILE

cp "$PROFILE" "$OUT_DIR/latest-runtime-profile.txt"

printf 'NADIA_RUNTIME_PROFILE=%s\n' "$PROFILE"
printf 'NADIA_RUNTIME_FAMILY=%s\n' "$RUNTIME_FAMILY"
printf 'NADIA_MODEL_FILE_PRESENT=%s\n' "$MODEL_FILE_PRESENT"
