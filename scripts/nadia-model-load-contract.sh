#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-model-load-contract.sh [options]

Options:
  --runtime-invocation <file>  Stage-11 Nadia runtime-invocation contract
  --request-class <label>      Operator request classification label
  --output <dir>               Output directory for model-load contracts

Creates Nadia Stage-12 model-load contract metadata only. It does not
materialize prompts, evaluate prompts, open model files, map model weights,
verify model weights, load model weights, spawn a runtime, create a model
session, generate tokens, run inference, execute tools, mutate source, train,
distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia model load contract: %s\n' "$1" >&2
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
      fail "$name is outside Nadia model-load boundary" 65
      ;;
  esac
}

RUNTIME_INVOCATION=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --runtime-invocation)
      [ "$#" -ge 2 ] || fail "missing value for --runtime-invocation" 64
      RUNTIME_INVOCATION="$2"
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

if [ -z "$RUNTIME_INVOCATION" ] && [ -f "reports/nadia/runtime-invocation/latest-runtime-invocation-contract.txt" ]; then
  RUNTIME_INVOCATION="reports/nadia/runtime-invocation/latest-runtime-invocation-contract.txt"
fi

[ -n "$RUNTIME_INVOCATION" ] || fail "runtime invocation contract is required" 64
[ -f "$RUNTIME_INVOCATION" ] || fail "runtime invocation contract not found: $RUNTIME_INVOCATION" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/model-load"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_MODEL_LOAD_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-model-load-contract-$TS.txt"

RUNTIME_INVOCATION_ABS=$(cd "$(dirname -- "$RUNTIME_INVOCATION")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$RUNTIME_INVOCATION")")
RUNTIME_INVOCATION_MEASUREMENT=$(measure_file "$RUNTIME_INVOCATION_ABS")
INVOCATION_STAGE=$(field_or_unknown stage "$RUNTIME_INVOCATION_ABS")
RUNTIME_INVOCATION_CONTRACT_STATUS=$(field_or_unknown runtime_invocation_contract_status "$RUNTIME_INVOCATION_ABS")
RUNTIME_INVOCATION_STAGE=$(field_or_unknown runtime_invocation_stage "$RUNTIME_INVOCATION_ABS")
RUNTIME_INVOCATION_AUTHORITY=$(field_or_unknown runtime_invocation_authority "$RUNTIME_INVOCATION_ABS")
RUNTIME_INVOCATION_ALLOWED=$(field_or_unknown runtime_invocation_allowed "$RUNTIME_INVOCATION_ABS")
RUNTIME_INVOKED=$(field_or_unknown runtime_invoked "$RUNTIME_INVOCATION_ABS")
INVOCATION_DECISION=$(field_or_unknown invocation_decision "$RUNTIME_INVOCATION_ABS")
INVOCATION_EVIDENCE_PRESENT=$(field_or_unknown invocation_evidence_present "$RUNTIME_INVOCATION_ABS")
REQUIRES_INFERENCE_READINESS_CONTRACT=$(field_or_unknown requires_inference_readiness_contract "$RUNTIME_INVOCATION_ABS")
REQUIRES_MODEL_REGISTRY_CONTRACT=$(field_or_unknown requires_model_registry_contract "$RUNTIME_INVOCATION_ABS")
REQUIRES_PROMPT_CONTRACT=$(field_or_unknown requires_prompt_contract "$RUNTIME_INVOCATION_ABS")
REQUIRES_RUNTIME_PROFILE=$(field_or_unknown requires_runtime_profile "$RUNTIME_INVOCATION_ABS")
REQUIRES_PROTECTIVE_SAFETY_BOUNDARY=$(field_or_unknown requires_protective_safety_boundary "$RUNTIME_INVOCATION_ABS")
REQUIRES_TOOL_PREFLIGHT=$(field_or_unknown requires_tool_preflight "$RUNTIME_INVOCATION_ABS")
REQUIRES_OPERATOR_REVIEW=$(field_or_unknown requires_operator_review "$RUNTIME_INVOCATION_ABS")
REQUIRES_FUTURE_MODEL_LOAD_CONTRACT=$(field_or_unknown requires_future_model_load_contract "$RUNTIME_INVOCATION_ABS")
INVOCATION_PROMOTION_ALLOWED=$(field_or_unknown invocation_promotion_allowed "$RUNTIME_INVOCATION_ABS")
RUNTIME_PROCESS_SPAWN_AUTHORITY=$(field_or_unknown runtime_process_spawn_authority "$RUNTIME_INVOCATION_ABS")
RUNTIME_BINARY_EXECUTION_AUTHORITY=$(field_or_unknown runtime_binary_execution_authority "$RUNTIME_INVOCATION_ABS")
RUNTIME_SESSION_AUTHORITY=$(field_or_unknown runtime_session_authority "$RUNTIME_INVOCATION_ABS")
MODEL_SESSION_AUTHORITY=$(field_or_unknown model_session_authority "$RUNTIME_INVOCATION_ABS")
TOKEN_GENERATION_AUTHORITY=$(field_or_unknown token_generation_authority "$RUNTIME_INVOCATION_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$RUNTIME_INVOCATION_ABS")
MODEL_ID=$(field_or_unknown model_id "$RUNTIME_INVOCATION_ABS")
MODEL_FAMILY=$(field_or_unknown model_family "$RUNTIME_INVOCATION_ABS")
MODEL_FORMAT=$(field_or_unknown model_format "$RUNTIME_INVOCATION_ABS")
QUANTIZATION=$(field_or_unknown quantization "$RUNTIME_INVOCATION_ABS")
CONTEXT_TOKENS=$(field_or_unknown context_window_tokens "$RUNTIME_INVOCATION_ABS")
MEMORY_MIB=$(field_or_unknown memory_budget_mib "$RUNTIME_INVOCATION_ABS")
INFERENCE_READY=$(field_or_unknown inference_ready "$RUNTIME_INVOCATION_ABS")
READINESS_DECISION=$(field_or_unknown readiness_decision "$RUNTIME_INVOCATION_ABS")
CANDIDATE_USABLE_FOR_INFERENCE=$(field_or_unknown candidate_usable_for_inference "$RUNTIME_INVOCATION_ABS")
CANDIDATE_SELECTED_FOR_RUNTIME=$(field_or_unknown candidate_selected_for_runtime "$RUNTIME_INVOCATION_ABS")
MODEL_SELECTION_AUTHORITY=$(field_or_unknown model_selection_authority "$RUNTIME_INVOCATION_ABS")
MODEL_LOAD_AUTHORITY=$(field_or_unknown model_load_authority "$RUNTIME_INVOCATION_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$RUNTIME_INVOCATION_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$RUNTIME_INVOCATION_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$RUNTIME_INVOCATION_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$RUNTIME_INVOCATION_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$RUNTIME_INVOCATION_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$RUNTIME_INVOCATION_ABS")
MODEL_RUNTIME_PRESENT=$(field_or_unknown model_runtime_present "$RUNTIME_INVOCATION_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$RUNTIME_INVOCATION_ABS")
RUNTIME_PROCESS_SPAWNED=$(field_or_unknown runtime_process_spawned "$RUNTIME_INVOCATION_ABS")
RUNTIME_BINARY_EXECUTED=$(field_or_unknown runtime_binary_executed "$RUNTIME_INVOCATION_ABS")
RUNTIME_SESSION_CREATED=$(field_or_unknown runtime_session_created "$RUNTIME_INVOCATION_ABS")
MODEL_WEIGHTS_INSTALLED=$(field_or_unknown model_weights_installed "$RUNTIME_INVOCATION_ABS")
MODEL_WEIGHTS_LOADED=$(field_or_unknown model_weights_loaded "$RUNTIME_INVOCATION_ABS")
MODEL_WEIGHTS_COPIED=$(field_or_unknown model_weights_copied "$RUNTIME_INVOCATION_ABS")
MODEL_WEIGHTS_DOWNLOADED=$(field_or_unknown model_weights_downloaded "$RUNTIME_INVOCATION_ABS")
MODEL_WEIGHTS_INSPECTED=$(field_or_unknown model_weights_inspected "$RUNTIME_INVOCATION_ABS")
TOKEN_GENERATION_PERFORMED=$(field_or_unknown token_generation_performed "$RUNTIME_INVOCATION_ABS")
INFERENCE_AUTHORITY=$(field_or_unknown inference_authority "$RUNTIME_INVOCATION_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$RUNTIME_INVOCATION_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$RUNTIME_INVOCATION_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$RUNTIME_INVOCATION_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$RUNTIME_INVOCATION_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$RUNTIME_INVOCATION_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$RUNTIME_INVOCATION_ABS")

[ "$INVOCATION_STAGE" = "11-runtime-invocation-contract" ] || fail "runtime invocation stage must be 11-runtime-invocation-contract" 65
[ "$RUNTIME_INVOCATION_CONTRACT_STATUS" = "contract_only" ] || fail "runtime invocation contract must remain contract-only" 65
[ "$RUNTIME_INVOCATION_STAGE" = "contract-only" ] || fail "runtime invocation stage must be contract-only" 65
[ "$RUNTIME_INVOCATION_AUTHORITY" = "0" ] || fail "runtime invocation must not grant authority" 65
[ "$RUNTIME_INVOCATION_ALLOWED" = "0" ] || fail "runtime invocation must remain disallowed" 65
[ "$RUNTIME_INVOKED" = "0" ] || fail "runtime must not be invoked" 65
[ "$INVOCATION_DECISION" = "blocked_contract_only" ] || fail "invocation decision must be blocked_contract_only" 65
[ "$INVOCATION_EVIDENCE_PRESENT" = "1" ] || fail "invocation evidence must be present" 65
[ "$REQUIRES_INFERENCE_READINESS_CONTRACT" = "1" ] || fail "invocation must require inference readiness" 65
[ "$REQUIRES_MODEL_REGISTRY_CONTRACT" = "1" ] || fail "invocation must require model registry" 65
[ "$REQUIRES_PROMPT_CONTRACT" = "1" ] || fail "invocation must require prompt contract" 65
[ "$REQUIRES_RUNTIME_PROFILE" = "1" ] || fail "invocation must require runtime profile" 65
[ "$REQUIRES_PROTECTIVE_SAFETY_BOUNDARY" = "1" ] || fail "invocation must require protective safety" 65
[ "$REQUIRES_TOOL_PREFLIGHT" = "1" ] || fail "invocation must require tool preflight" 65
[ "$REQUIRES_OPERATOR_REVIEW" = "1" ] || fail "invocation must require operator review" 65
[ "$REQUIRES_FUTURE_MODEL_LOAD_CONTRACT" = "1" ] || fail "invocation must require a future model load contract" 65
[ "$INVOCATION_PROMOTION_ALLOWED" = "0" ] || fail "invocation must not allow promotion" 65
[ "$RUNTIME_PROCESS_SPAWN_AUTHORITY" = "0" ] || fail "invocation must not grant process spawn authority" 65
[ "$RUNTIME_BINARY_EXECUTION_AUTHORITY" = "0" ] || fail "invocation must not grant runtime binary execution authority" 65
[ "$RUNTIME_SESSION_AUTHORITY" = "0" ] || fail "invocation must not grant runtime session authority" 65
[ "$MODEL_SESSION_AUTHORITY" = "0" ] || fail "invocation must not grant model session authority" 65
[ "$TOKEN_GENERATION_AUTHORITY" = "0" ] || fail "invocation must not grant token generation authority" 65
[ "$INFERENCE_READY" = "0" ] || fail "inference readiness must remain blocked" 65
[ "$READINESS_DECISION" = "blocked_contract_only" ] || fail "readiness decision must remain blocked_contract_only" 65
[ "$CANDIDATE_USABLE_FOR_INFERENCE" = "0" ] || fail "model candidate must not be usable for inference" 65
[ "$CANDIDATE_SELECTED_FOR_RUNTIME" = "0" ] || fail "model candidate must not be selected for runtime" 65
[ "$MODEL_SELECTION_AUTHORITY" = "0" ] || fail "model selection authority must remain denied" 65
[ "$MODEL_LOAD_AUTHORITY" = "0" ] || fail "model load authority must remain denied" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "sexual content generation must remain forbidden" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "sexual requests must always be refused" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "manipulation resistance must remain required" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "prompts must not be materialized" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "prompt evaluation authority must remain denied" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "prompts must not be evaluated" 65
[ "$MODEL_RUNTIME_PRESENT" = "0" ] || fail "runtime presence must not be claimed" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "model runtime must not be invoked" 65
[ "$RUNTIME_PROCESS_SPAWNED" = "0" ] || fail "runtime process must not be spawned" 65
[ "$RUNTIME_BINARY_EXECUTED" = "0" ] || fail "runtime binary must not be executed" 65
[ "$RUNTIME_SESSION_CREATED" = "0" ] || fail "runtime session must not be created" 65
[ "$MODEL_WEIGHTS_INSTALLED" = "0" ] || fail "model weights must not be installed" 65
[ "$MODEL_WEIGHTS_LOADED" = "0" ] || fail "model weights must not be loaded" 65
[ "$MODEL_WEIGHTS_COPIED" = "0" ] || fail "model weights must not be copied" 65
[ "$MODEL_WEIGHTS_DOWNLOADED" = "0" ] || fail "model weights must not be downloaded" 65
[ "$MODEL_WEIGHTS_INSPECTED" = "0" ] || fail "model weights must not be inspected" 65
[ "$TOKEN_GENERATION_PERFORMED" = "0" ] || fail "token generation must not be performed" 65
[ "$INFERENCE_AUTHORITY" = "0" ] || fail "inference authority must remain denied" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "inference must not be performed" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "tool execution authority must remain denied" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "network authority must remain denied" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "source mutation authority must remain denied" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "training must not be performed" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "distillation must not be performed" 65

cat > "$REPORT" <<REPORT
NADIA MODEL LOAD CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=12-model-load-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
model_load_contract_status=contract_only
model_load_stage=contract-only
model_load_authority=0
model_load_allowed=0
model_loaded=0

[inputs]
runtime_invocation=$RUNTIME_INVOCATION_ABS
runtime_invocation_measurement=$RUNTIME_INVOCATION_MEASUREMENT
runtime_invocation_stage_required=11-runtime-invocation-contract
runtime_invocation_stage=$INVOCATION_STAGE
runtime_invocation_contract_status=$RUNTIME_INVOCATION_CONTRACT_STATUS
model_registry_stage=$MODEL_REGISTRY_STAGE
model_id=$MODEL_ID
model_family=$MODEL_FAMILY
model_format=$MODEL_FORMAT
quantization=$QUANTIZATION
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB

[model_load_contract]
model_load_contract_command=scripts/nadia-model-load-contract.sh
installed_model_load_contract_command=latticra-nadia model-load
load_decision=blocked_contract_only
load_evidence_present=1
requires_runtime_invocation_contract=1
requires_inference_readiness_contract=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_model_safety_review=1
requires_model_weight_measurement_contract=1
requires_refusal_policy_review=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
requires_future_prompt_receipt_contract=1
load_promotion_allowed=0
model_file_open_authority=0
model_weight_read_authority=0
model_weight_mapping_authority=0
model_weight_verification_authority=0
model_weight_inspection_authority=0
runtime_model_attach_authority=0
model_session_authority=0
token_generation_authority=0

[inherited_invocation_boundary]
runtime_invocation_authority=0
runtime_invocation_allowed=0
runtime_invoked=0
invocation_decision=blocked_contract_only
invocation_evidence_present=1
invocation_promotion_allowed=0
runtime_process_spawn_authority=0
runtime_binary_execution_authority=0
runtime_session_authority=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0

[model_boundary]
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_load_authority=0
model_weights_installed=0
model_file_opened=0
model_file_descriptor_opened=0
model_memory_map_created=0
model_weights_mapped=0
model_weights_loaded=0
model_weights_attached=0
model_weights_copied=0
model_weights_downloaded=0
model_weights_inspected=0
model_weight_measurement_performed=0
model_weight_verification_performed=0
model_load_performed=0

[runtime_boundary]
model_runtime_present=0
model_runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0
runtime_invoked=0
token_generation_performed=0
inference_authority=0
inference_performed=0

[prompt_boundary]
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0

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
training_performed=0
distillation_performed=0

[operator_review]
requires_operator_review=1
requires_runtime_invocation_review=1
requires_model_load_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_model_safety_review=1
requires_future_prompt_receipt_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-model-load-contract.txt"

printf 'NADIA_MODEL_LOAD_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_MODEL_LOADED=0\n'
printf 'NADIA_MODEL_LOAD_AUTHORITY=0\n'
