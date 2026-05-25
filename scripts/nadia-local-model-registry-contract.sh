#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-local-model-registry-contract.sh [options]

Options:
  --prompt-contract <file>  Stage-8 Nadia prompt-evaluation contract
  --runtime-profile <file>  Stage-2 Nadia runtime profile
  --model-id <label>        Local model candidate label
  --model-family <label>    Runtime/model family label
  --model-format <label>    Model format label
  --quantization <label>    Quantization label
  --context-tokens <n>      Declared context window tokens
  --memory-mib <n>          Declared memory budget in MiB
  --source <label>          Local provenance/source label
  --license <label>         License/review label
  --output <dir>            Output directory for model-registry contracts

Creates Nadia Stage-9 local model-registry contract metadata only. It does not
download, install, copy, load, mmap, execute, evaluate, benchmark, train,
distill, or inspect model weights.
USAGE
}

fail() {
  printf 'nadia local model registry contract: %s\n' "$1" >&2
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

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia local model-registry boundary" 65
      ;;
  esac
}

PROMPT_CONTRACT=""
RUNTIME_PROFILE=""
MODEL_ID="operator-provided-local-model"
MODEL_FAMILY="llama.cpp-compatible"
MODEL_FORMAT=""
QUANTIZATION="operator-declared"
CONTEXT_TOKENS=""
MEMORY_MIB=""
MODEL_SOURCE="operator-provided-local"
MODEL_LICENSE="operator-review-required"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-contract)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-contract" 64
      PROMPT_CONTRACT="$2"
      shift 2
      ;;
    --runtime-profile)
      [ "$#" -ge 2 ] || fail "missing value for --runtime-profile" 64
      RUNTIME_PROFILE="$2"
      shift 2
      ;;
    --model-id)
      [ "$#" -ge 2 ] || fail "missing value for --model-id" 64
      MODEL_ID="$2"
      shift 2
      ;;
    --model-family)
      [ "$#" -ge 2 ] || fail "missing value for --model-family" 64
      MODEL_FAMILY="$2"
      shift 2
      ;;
    --model-format)
      [ "$#" -ge 2 ] || fail "missing value for --model-format" 64
      MODEL_FORMAT="$2"
      shift 2
      ;;
    --quantization)
      [ "$#" -ge 2 ] || fail "missing value for --quantization" 64
      QUANTIZATION="$2"
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
    --source)
      [ "$#" -ge 2 ] || fail "missing value for --source" 64
      MODEL_SOURCE="$2"
      shift 2
      ;;
    --license)
      [ "$#" -ge 2 ] || fail "missing value for --license" 64
      MODEL_LICENSE="$2"
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

if [ -z "$PROMPT_CONTRACT" ] && [ -f "reports/nadia/prompt-contracts/latest-prompt-contract.txt" ]; then
  PROMPT_CONTRACT="reports/nadia/prompt-contracts/latest-prompt-contract.txt"
fi

if [ -z "$RUNTIME_PROFILE" ] && [ -f "reports/nadia/runtime-profiles/latest-runtime-profile.txt" ]; then
  RUNTIME_PROFILE="reports/nadia/runtime-profiles/latest-runtime-profile.txt"
fi

[ -n "$PROMPT_CONTRACT" ] || fail "prompt contract is required" 64
[ -n "$RUNTIME_PROFILE" ] || fail "runtime profile is required" 64
[ -f "$PROMPT_CONTRACT" ] || fail "prompt contract not found: $PROMPT_CONTRACT" 66
[ -f "$RUNTIME_PROFILE" ] || fail "runtime profile not found: $RUNTIME_PROFILE" 66

reject_boundary_label "model id" "$MODEL_ID"
reject_boundary_label "model family" "$MODEL_FAMILY"
reject_boundary_label "quantization label" "$QUANTIZATION"
reject_boundary_label "source label" "$MODEL_SOURCE"
reject_boundary_label "license label" "$MODEL_LICENSE"

PROMPT_CONTRACT_ABS=$(cd "$(dirname -- "$PROMPT_CONTRACT")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_CONTRACT")")
RUNTIME_PROFILE_ABS=$(cd "$(dirname -- "$RUNTIME_PROFILE")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$RUNTIME_PROFILE")")

PROMPT_CONTRACT_STAGE=$(field_or_unknown stage "$PROMPT_CONTRACT_ABS")
PROMPT_CONTRACT_STATUS=$(field_or_unknown prompt_contract_status "$PROMPT_CONTRACT_ABS")
PROMPT_EVALUATION_STAGE=$(field_or_unknown prompt_evaluation_stage "$PROMPT_CONTRACT_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$PROMPT_CONTRACT_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$PROMPT_CONTRACT_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$PROMPT_CONTRACT_ABS")
PROMPT_CONTRACT_PROMOTION=$(field_or_unknown contract_promotion_allowed "$PROMPT_CONTRACT_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$PROMPT_CONTRACT_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$PROMPT_CONTRACT_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$PROMPT_CONTRACT_ABS")
PROMPT_TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$PROMPT_CONTRACT_ABS")
PROMPT_MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$PROMPT_CONTRACT_ABS")
PROMPT_INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$PROMPT_CONTRACT_ABS")
PROMPT_MODEL_WEIGHTS_INSTALLED=$(field_or_unknown model_weights_installed "$PROMPT_CONTRACT_ABS")
PROMPT_NETWORK_AUTHORITY=$(field_or_unknown network_authority "$PROMPT_CONTRACT_ABS")

[ "$PROMPT_CONTRACT_STAGE" = "8-prompt-evaluation-contract" ] || fail "prompt contract stage must be 8-prompt-evaluation-contract" 65
[ "$PROMPT_CONTRACT_STATUS" = "contract_only" ] || fail "prompt contract must remain contract-only" 65
[ "$PROMPT_EVALUATION_STAGE" = "contract-only" ] || fail "prompt evaluation stage must be contract-only" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "prompt contract must not materialize prompts" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "prompt contract must not grant prompt evaluation authority" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "prompt contract must not evaluate prompts" 65
[ "$PROMPT_CONTRACT_PROMOTION" = "0" ] || fail "prompt contract must not allow promotion" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "prompt contract must forbid sexual content generation" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "prompt contract must always refuse sexual requests" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "prompt contract must require manipulation resistance" 65
[ "$PROMPT_TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "prompt contract must not grant tool execution authority" 65
[ "$PROMPT_MODEL_RUNTIME_INVOKED" = "0" ] || fail "prompt contract must not invoke a model runtime" 65
[ "$PROMPT_INFERENCE_PERFORMED" = "0" ] || fail "prompt contract must not include inference" 65
[ "$PROMPT_MODEL_WEIGHTS_INSTALLED" = "0" ] || fail "prompt contract must not install model weights" 65
[ "$PROMPT_NETWORK_AUTHORITY" = "0" ] || fail "prompt contract must not include network authority" 65

RUNTIME_STAGE=$(field_or_unknown stage "$RUNTIME_PROFILE_ABS")
RUNTIME_FAMILY=$(field_or_unknown runtime_family "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FORMAT=$(field_or_unknown model_format "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FILE=$(field_or_unknown model_file "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FILE_PRESENT=$(field_or_unknown model_file_present "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FILE_BYTES=$(field_or_unknown model_file_bytes "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FILE_MEASUREMENT=$(field_or_unknown model_file_measurement "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_FILE_COPIED=$(field_or_unknown model_file_copied "$RUNTIME_PROFILE_ABS")
RUNTIME_CONTEXT_TOKENS=$(field_or_unknown context_window_tokens "$RUNTIME_PROFILE_ABS")
RUNTIME_MEMORY_MIB=$(field_or_unknown memory_budget_mib "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_WEIGHTS_INSTALLED=$(field_or_unknown model_weights_installed "$RUNTIME_PROFILE_ABS")
RUNTIME_NETWORK_AUTHORITY=$(field_or_unknown network_authority "$RUNTIME_PROFILE_ABS")
RUNTIME_MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$RUNTIME_PROFILE_ABS")
RUNTIME_INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$RUNTIME_PROFILE_ABS")
RUNTIME_PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$RUNTIME_PROFILE_ABS")
RUNTIME_TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$RUNTIME_PROFILE_ABS")
RUNTIME_SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$RUNTIME_PROFILE_ABS")
RUNTIME_TRAINING_PERFORMED=$(field_or_unknown training_performed "$RUNTIME_PROFILE_ABS")
RUNTIME_SELF_MODIFICATION_AUTHORITY=$(field_or_unknown self_modification_authority "$RUNTIME_PROFILE_ABS")

[ "$RUNTIME_STAGE" = "2-runtime-profile-boundary" ] || fail "runtime profile stage must be 2-runtime-profile-boundary" 65
[ "$RUNTIME_MODEL_FILE_COPIED" = "0" ] || fail "runtime profile must not copy model files" 65
[ "$RUNTIME_MODEL_WEIGHTS_INSTALLED" = "0" ] || fail "runtime profile must not install model weights" 65
[ "$RUNTIME_NETWORK_AUTHORITY" = "0" ] || fail "runtime profile must not include network authority" 65
[ "$RUNTIME_MODEL_RUNTIME_INVOKED" = "0" ] || fail "runtime profile must not invoke a model runtime" 65
[ "$RUNTIME_INFERENCE_PERFORMED" = "0" ] || fail "runtime profile must not include inference" 65
[ "$RUNTIME_PROMPT_EVALUATED" = "0" ] || fail "runtime profile must not evaluate prompts" 65
[ "$RUNTIME_TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "runtime profile must not grant tool execution authority" 65
[ "$RUNTIME_SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "runtime profile must not grant source mutation authority" 65
[ "$RUNTIME_TRAINING_PERFORMED" = "0" ] || fail "runtime profile must not include training" 65
[ "$RUNTIME_SELF_MODIFICATION_AUTHORITY" = "0" ] || fail "runtime profile must not grant self-modification authority" 65

if [ -z "$MODEL_FORMAT" ]; then
  MODEL_FORMAT="$RUNTIME_MODEL_FORMAT"
fi

if [ -z "$CONTEXT_TOKENS" ]; then
  CONTEXT_TOKENS="$RUNTIME_CONTEXT_TOKENS"
fi

if [ -z "$MEMORY_MIB" ]; then
  MEMORY_MIB="$RUNTIME_MEMORY_MIB"
fi

reject_boundary_label "model format" "$MODEL_FORMAT"
is_uint "$CONTEXT_TOKENS" || fail "context tokens must be an unsigned integer" 64
is_uint "$MEMORY_MIB" || fail "memory MiB must be an unsigned integer" 64
[ "$CONTEXT_TOKENS" -gt 0 ] || fail "context tokens must be greater than zero" 64
[ "$MEMORY_MIB" -gt 0 ] || fail "memory MiB must be greater than zero" 64

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/model-registry"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_MODEL_REGISTRY_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-model-registry-contract-$TS.txt"
PROMPT_CONTRACT_MEASUREMENT=$(measure_file "$PROMPT_CONTRACT_ABS")
RUNTIME_PROFILE_MEASUREMENT=$(measure_file "$RUNTIME_PROFILE_ABS")

cat > "$REPORT" <<REPORT
NADIA LOCAL MODEL REGISTRY CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=9-local-model-registry-contract
output_dir=$OUT_DIR
registry_contract_status=metadata_only
model_registry_authority=0

[inputs]
prompt_contract=$PROMPT_CONTRACT_ABS
prompt_contract_stage=$PROMPT_CONTRACT_STAGE
prompt_contract_measurement=$PROMPT_CONTRACT_MEASUREMENT
runtime_profile=$RUNTIME_PROFILE_ABS
runtime_profile_stage=$RUNTIME_STAGE
runtime_profile_measurement=$RUNTIME_PROFILE_MEASUREMENT

[candidate]
model_id=$MODEL_ID
model_family=$MODEL_FAMILY
model_format=$MODEL_FORMAT
quantization=$QUANTIZATION
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB
model_source=$MODEL_SOURCE
model_license=$MODEL_LICENSE
runtime_family=$RUNTIME_FAMILY
runtime_model_file=$RUNTIME_MODEL_FILE
runtime_model_file_present=$RUNTIME_MODEL_FILE_PRESENT
runtime_model_file_bytes=$RUNTIME_MODEL_FILE_BYTES
runtime_model_file_measurement=$RUNTIME_MODEL_FILE_MEASUREMENT
candidate_recorded=1
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
candidate_selected_for_runtime=0

[registry_contract]
local_model_registry_stage=contract-only
model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh
installed_model_registry_contract_command=latticra-nadia model-registry
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_license_review=1
requires_provenance_review=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
registry_promotion_allowed=0
model_selection_authority=0
model_install_authority=0
model_download_authority=0
model_copy_authority=0
model_load_authority=0
model_benchmark_authority=0
model_weight_inspection_authority=0

[protective_boundary]
sexual_user_request_authority=0
sexual_content_generation=0
sexual_request_refusal=always
sexual_roleplay_authority=0
sexualized_namesake_or_survivor_content=0
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1

[authority]
offline_by_default=1
network_authority=0
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
self_modification_authority=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_runtime_present=0
model_runtime_invoked=0
inference_performed=0
model_weights_installed=0
model_weights_loaded=0
model_weights_copied=0
model_weights_downloaded=0
model_weights_inspected=0
training_performed=0
distillation_performed=0

[operator_review]
requires_operator_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_model_safety_review=1
requires_future_inference_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-model-registry-contract.txt"

printf 'NADIA_MODEL_REGISTRY_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_MODEL_REGISTRY_AUTHORITY=0\n'
printf 'NADIA_MODEL_RUNTIME_INVOKED=0\n'
