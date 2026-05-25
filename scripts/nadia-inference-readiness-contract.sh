#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-inference-readiness-contract.sh [options]

Options:
  --model-registry <file>  Stage-9 Nadia local model-registry contract
  --request-class <label>  Operator request classification label
  --output <dir>           Output directory for inference-readiness contracts

Creates Nadia Stage-10 inference-readiness contract metadata only. It does not
materialize prompts, evaluate prompts, load model weights, invoke a runtime,
run inference, execute tools, mutate source, train, distill, download, or use
network.
USAGE
}

fail() {
  printf 'nadia inference readiness contract: %s\n' "$1" >&2
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

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia inference-readiness boundary" 65
      ;;
  esac
}

MODEL_REGISTRY=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --model-registry)
      [ "$#" -ge 2 ] || fail "missing value for --model-registry" 64
      MODEL_REGISTRY="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
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

if [ -z "$MODEL_REGISTRY" ] && [ -f "reports/nadia/model-registry/latest-model-registry-contract.txt" ]; then
  MODEL_REGISTRY="reports/nadia/model-registry/latest-model-registry-contract.txt"
fi

[ -n "$MODEL_REGISTRY" ] || fail "model registry contract is required" 64
[ -f "$MODEL_REGISTRY" ] || fail "model registry contract not found: $MODEL_REGISTRY" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/inference-readiness"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_INFERENCE_READINESS_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-inference-readiness-contract-$TS.txt"

MODEL_REGISTRY_ABS=$(cd "$(dirname -- "$MODEL_REGISTRY")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MODEL_REGISTRY")")
MODEL_REGISTRY_MEASUREMENT=$(measure_file "$MODEL_REGISTRY_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown stage "$MODEL_REGISTRY_ABS")
REGISTRY_CONTRACT_STATUS=$(field_or_unknown registry_contract_status "$MODEL_REGISTRY_ABS")
LOCAL_MODEL_REGISTRY_STAGE=$(field_or_unknown local_model_registry_stage "$MODEL_REGISTRY_ABS")
MODEL_REGISTRY_AUTHORITY=$(field_or_unknown model_registry_authority "$MODEL_REGISTRY_ABS")
MODEL_ID=$(field_or_unknown model_id "$MODEL_REGISTRY_ABS")
MODEL_FAMILY=$(field_or_unknown model_family "$MODEL_REGISTRY_ABS")
MODEL_FORMAT=$(field_or_unknown model_format "$MODEL_REGISTRY_ABS")
QUANTIZATION=$(field_or_unknown quantization "$MODEL_REGISTRY_ABS")
CONTEXT_TOKENS=$(field_or_unknown context_window_tokens "$MODEL_REGISTRY_ABS")
MEMORY_MIB=$(field_or_unknown memory_budget_mib "$MODEL_REGISTRY_ABS")
CANDIDATE_REVIEW_STATUS=$(field_or_unknown candidate_review_status "$MODEL_REGISTRY_ABS")
CANDIDATE_USABLE_FOR_INFERENCE=$(field_or_unknown candidate_usable_for_inference "$MODEL_REGISTRY_ABS")
CANDIDATE_SELECTED_FOR_RUNTIME=$(field_or_unknown candidate_selected_for_runtime "$MODEL_REGISTRY_ABS")
REGISTRY_PROMOTION_ALLOWED=$(field_or_unknown registry_promotion_allowed "$MODEL_REGISTRY_ABS")
MODEL_SELECTION_AUTHORITY=$(field_or_unknown model_selection_authority "$MODEL_REGISTRY_ABS")
MODEL_INSTALL_AUTHORITY=$(field_or_unknown model_install_authority "$MODEL_REGISTRY_ABS")
MODEL_DOWNLOAD_AUTHORITY=$(field_or_unknown model_download_authority "$MODEL_REGISTRY_ABS")
MODEL_COPY_AUTHORITY=$(field_or_unknown model_copy_authority "$MODEL_REGISTRY_ABS")
MODEL_LOAD_AUTHORITY=$(field_or_unknown model_load_authority "$MODEL_REGISTRY_ABS")
MODEL_BENCHMARK_AUTHORITY=$(field_or_unknown model_benchmark_authority "$MODEL_REGISTRY_ABS")
MODEL_WEIGHT_INSPECTION_AUTHORITY=$(field_or_unknown model_weight_inspection_authority "$MODEL_REGISTRY_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$MODEL_REGISTRY_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$MODEL_REGISTRY_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$MODEL_REGISTRY_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$MODEL_REGISTRY_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$MODEL_REGISTRY_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$MODEL_REGISTRY_ABS")
MODEL_RUNTIME_PRESENT=$(field_or_unknown model_runtime_present "$MODEL_REGISTRY_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$MODEL_REGISTRY_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$MODEL_REGISTRY_ABS")
MODEL_WEIGHTS_INSTALLED=$(field_or_unknown model_weights_installed "$MODEL_REGISTRY_ABS")
MODEL_WEIGHTS_LOADED=$(field_or_unknown model_weights_loaded "$MODEL_REGISTRY_ABS")
MODEL_WEIGHTS_COPIED=$(field_or_unknown model_weights_copied "$MODEL_REGISTRY_ABS")
MODEL_WEIGHTS_DOWNLOADED=$(field_or_unknown model_weights_downloaded "$MODEL_REGISTRY_ABS")
MODEL_WEIGHTS_INSPECTED=$(field_or_unknown model_weights_inspected "$MODEL_REGISTRY_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$MODEL_REGISTRY_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$MODEL_REGISTRY_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$MODEL_REGISTRY_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$MODEL_REGISTRY_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$MODEL_REGISTRY_ABS")

[ "$MODEL_REGISTRY_STAGE" = "9-local-model-registry-contract" ] || fail "model registry stage must be 9-local-model-registry-contract" 65
[ "$REGISTRY_CONTRACT_STATUS" = "metadata_only" ] || fail "model registry contract must remain metadata-only" 65
[ "$LOCAL_MODEL_REGISTRY_STAGE" = "contract-only" ] || fail "model registry stage must be contract-only" 65
[ "$MODEL_REGISTRY_AUTHORITY" = "0" ] || fail "model registry must not grant registry authority" 65
[ "$CANDIDATE_REVIEW_STATUS" = "operator_review_required" ] || fail "model candidate must require operator review" 65
[ "$CANDIDATE_USABLE_FOR_INFERENCE" = "0" ] || fail "model candidate must not be usable for inference" 65
[ "$CANDIDATE_SELECTED_FOR_RUNTIME" = "0" ] || fail "model candidate must not be selected for runtime" 65
[ "$REGISTRY_PROMOTION_ALLOWED" = "0" ] || fail "model registry must not allow promotion" 65
[ "$MODEL_SELECTION_AUTHORITY" = "0" ] || fail "model registry must not grant model selection authority" 65
[ "$MODEL_INSTALL_AUTHORITY" = "0" ] || fail "model registry must not grant model install authority" 65
[ "$MODEL_DOWNLOAD_AUTHORITY" = "0" ] || fail "model registry must not grant model download authority" 65
[ "$MODEL_COPY_AUTHORITY" = "0" ] || fail "model registry must not grant model copy authority" 65
[ "$MODEL_LOAD_AUTHORITY" = "0" ] || fail "model registry must not grant model load authority" 65
[ "$MODEL_BENCHMARK_AUTHORITY" = "0" ] || fail "model registry must not grant model benchmark authority" 65
[ "$MODEL_WEIGHT_INSPECTION_AUTHORITY" = "0" ] || fail "model registry must not grant weight inspection authority" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "model registry must forbid sexual content generation" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "model registry must always refuse sexual requests" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "model registry must require manipulation resistance" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "model registry must not materialize prompts" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "model registry must not grant prompt evaluation authority" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "model registry must not evaluate prompts" 65
[ "$MODEL_RUNTIME_PRESENT" = "0" ] || fail "model registry must not claim runtime presence" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "model registry must not invoke a model runtime" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "model registry must not include inference" 65
[ "$MODEL_WEIGHTS_INSTALLED" = "0" ] || fail "model registry must not install model weights" 65
[ "$MODEL_WEIGHTS_LOADED" = "0" ] || fail "model registry must not load model weights" 65
[ "$MODEL_WEIGHTS_COPIED" = "0" ] || fail "model registry must not copy model weights" 65
[ "$MODEL_WEIGHTS_DOWNLOADED" = "0" ] || fail "model registry must not download model weights" 65
[ "$MODEL_WEIGHTS_INSPECTED" = "0" ] || fail "model registry must not inspect model weights" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "model registry must not grant tool execution authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "model registry must not include network authority" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "model registry must not grant source mutation authority" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "model registry must not include training" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "model registry must not include distillation" 65

cat > "$REPORT" <<REPORT
NADIA INFERENCE READINESS CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia
stage=10-inference-readiness-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
inference_readiness_contract_status=contract_only
inference_readiness_stage=contract-only
inference_readiness_authority=0
inference_ready=0

[inputs]
model_registry=$MODEL_REGISTRY_ABS
model_registry_stage=$MODEL_REGISTRY_STAGE
model_registry_measurement=$MODEL_REGISTRY_MEASUREMENT
model_id=$MODEL_ID
model_family=$MODEL_FAMILY
model_format=$MODEL_FORMAT
quantization=$QUANTIZATION
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB

[readiness_contract]
inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh
installed_inference_readiness_contract_command=latticra-nadia inference-readiness
readiness_decision=blocked_contract_only
readiness_evidence_present=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_refusal_policy_review=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
requires_future_runtime_invocation_contract=1
readiness_promotion_allowed=0
runtime_invocation_authority=0
token_generation_authority=0
model_session_authority=0

[inherited_model_boundary]
registry_contract_status=metadata_only
model_registry_authority=0
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_install_authority=0
model_download_authority=0
model_copy_authority=0
model_load_authority=0
model_benchmark_authority=0
model_weight_inspection_authority=0
registry_promotion_allowed=0

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
runtime_invoked=0
inference_authority=0
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
requires_inference_readiness_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_model_safety_review=1
requires_future_runtime_invocation_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-inference-readiness-contract.txt"

printf 'NADIA_INFERENCE_READINESS_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_INFERENCE_READY=0\n'
printf 'NADIA_INFERENCE_AUTHORITY=0\n'
