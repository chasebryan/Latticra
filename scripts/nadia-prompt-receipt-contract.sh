#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-receipt-contract.sh [options]

Options:
  --model-load <file>      Stage-12 Nadia model-load contract
  --request-class <label>  Operator request classification label
  --output <dir>           Output directory for prompt-receipt contracts

Creates Nadia Stage-13 prompt-receipt contract metadata only. It does not
receive prompt text, read prompt sources, materialize prompts, evaluate prompts,
load model weights, spawn a runtime, create a model session, generate tokens,
run inference, execute tools, mutate source, train, distill, download, or use
network.
USAGE
}

fail() {
  printf 'nadia prompt receipt contract: %s\n' "$1" >&2
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
      fail "$name is outside Nadia prompt-receipt boundary" 65
      ;;
  esac
}

MODEL_LOAD=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --model-load)
      [ "$#" -ge 2 ] || fail "missing value for --model-load" 64
      MODEL_LOAD="$2"
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

if [ -z "$MODEL_LOAD" ] && [ -f "reports/nadia/model-load/latest-model-load-contract.txt" ]; then
  MODEL_LOAD="reports/nadia/model-load/latest-model-load-contract.txt"
fi

[ -n "$MODEL_LOAD" ] || fail "model load contract is required" 64
[ -f "$MODEL_LOAD" ] || fail "model load contract not found: $MODEL_LOAD" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-receipt"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_RECEIPT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-receipt-contract-$TS.txt"

MODEL_LOAD_ABS=$(cd "$(dirname -- "$MODEL_LOAD")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MODEL_LOAD")")
MODEL_LOAD_MEASUREMENT=$(measure_file "$MODEL_LOAD_ABS")
MODEL_LOAD_STAGE_VALUE=$(field_or_unknown stage "$MODEL_LOAD_ABS")
MODEL_LOAD_CONTRACT_STATUS=$(field_or_unknown model_load_contract_status "$MODEL_LOAD_ABS")
MODEL_LOAD_STAGE=$(field_or_unknown model_load_stage "$MODEL_LOAD_ABS")
MODEL_LOAD_AUTHORITY=$(field_or_unknown model_load_authority "$MODEL_LOAD_ABS")
MODEL_LOAD_ALLOWED=$(field_or_unknown model_load_allowed "$MODEL_LOAD_ABS")
MODEL_LOADED=$(field_or_unknown model_loaded "$MODEL_LOAD_ABS")
LOAD_DECISION=$(field_or_unknown load_decision "$MODEL_LOAD_ABS")
LOAD_EVIDENCE_PRESENT=$(field_or_unknown load_evidence_present "$MODEL_LOAD_ABS")
REQUIRES_RUNTIME_INVOCATION_CONTRACT=$(field_or_unknown requires_runtime_invocation_contract "$MODEL_LOAD_ABS")
REQUIRES_INFERENCE_READINESS_CONTRACT=$(field_or_unknown requires_inference_readiness_contract "$MODEL_LOAD_ABS")
REQUIRES_MODEL_REGISTRY_CONTRACT=$(field_or_unknown requires_model_registry_contract "$MODEL_LOAD_ABS")
REQUIRES_PROMPT_CONTRACT=$(field_or_unknown requires_prompt_contract "$MODEL_LOAD_ABS")
REQUIRES_RUNTIME_PROFILE=$(field_or_unknown requires_runtime_profile "$MODEL_LOAD_ABS")
REQUIRES_PROTECTIVE_SAFETY_BOUNDARY=$(field_or_unknown requires_protective_safety_boundary "$MODEL_LOAD_ABS")
REQUIRES_TOOL_PREFLIGHT=$(field_or_unknown requires_tool_preflight "$MODEL_LOAD_ABS")
REQUIRES_OPERATOR_REVIEW=$(field_or_unknown requires_operator_review "$MODEL_LOAD_ABS")
REQUIRES_FUTURE_PROMPT_RECEIPT_CONTRACT=$(field_or_unknown requires_future_prompt_receipt_contract "$MODEL_LOAD_ABS")
LOAD_PROMOTION_ALLOWED=$(field_or_unknown load_promotion_allowed "$MODEL_LOAD_ABS")
MODEL_FILE_OPEN_AUTHORITY=$(field_or_unknown model_file_open_authority "$MODEL_LOAD_ABS")
MODEL_WEIGHT_READ_AUTHORITY=$(field_or_unknown model_weight_read_authority "$MODEL_LOAD_ABS")
MODEL_WEIGHT_MAPPING_AUTHORITY=$(field_or_unknown model_weight_mapping_authority "$MODEL_LOAD_ABS")
MODEL_WEIGHT_VERIFICATION_AUTHORITY=$(field_or_unknown model_weight_verification_authority "$MODEL_LOAD_ABS")
RUNTIME_MODEL_ATTACH_AUTHORITY=$(field_or_unknown runtime_model_attach_authority "$MODEL_LOAD_ABS")
MODEL_SESSION_AUTHORITY=$(field_or_unknown model_session_authority "$MODEL_LOAD_ABS")
TOKEN_GENERATION_AUTHORITY=$(field_or_unknown token_generation_authority "$MODEL_LOAD_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$MODEL_LOAD_ABS")
MODEL_ID=$(field_or_unknown model_id "$MODEL_LOAD_ABS")
MODEL_FAMILY=$(field_or_unknown model_family "$MODEL_LOAD_ABS")
MODEL_FORMAT=$(field_or_unknown model_format "$MODEL_LOAD_ABS")
QUANTIZATION=$(field_or_unknown quantization "$MODEL_LOAD_ABS")
CONTEXT_TOKENS=$(field_or_unknown context_window_tokens "$MODEL_LOAD_ABS")
MEMORY_MIB=$(field_or_unknown memory_budget_mib "$MODEL_LOAD_ABS")
RUNTIME_INVOCATION_AUTHORITY=$(field_or_unknown runtime_invocation_authority "$MODEL_LOAD_ABS")
RUNTIME_INVOCATION_ALLOWED=$(field_or_unknown runtime_invocation_allowed "$MODEL_LOAD_ABS")
RUNTIME_INVOKED=$(field_or_unknown runtime_invoked "$MODEL_LOAD_ABS")
INVOCATION_DECISION=$(field_or_unknown invocation_decision "$MODEL_LOAD_ABS")
CANDIDATE_USABLE_FOR_INFERENCE=$(field_or_unknown candidate_usable_for_inference "$MODEL_LOAD_ABS")
CANDIDATE_SELECTED_FOR_RUNTIME=$(field_or_unknown candidate_selected_for_runtime "$MODEL_LOAD_ABS")
MODEL_SELECTION_AUTHORITY=$(field_or_unknown model_selection_authority "$MODEL_LOAD_ABS")
MODEL_FILE_OPENED=$(field_or_unknown model_file_opened "$MODEL_LOAD_ABS")
MODEL_FILE_DESCRIPTOR_OPENED=$(field_or_unknown model_file_descriptor_opened "$MODEL_LOAD_ABS")
MODEL_MEMORY_MAP_CREATED=$(field_or_unknown model_memory_map_created "$MODEL_LOAD_ABS")
MODEL_WEIGHTS_MAPPED=$(field_or_unknown model_weights_mapped "$MODEL_LOAD_ABS")
MODEL_WEIGHTS_LOADED=$(field_or_unknown model_weights_loaded "$MODEL_LOAD_ABS")
MODEL_WEIGHTS_ATTACHED=$(field_or_unknown model_weights_attached "$MODEL_LOAD_ABS")
MODEL_LOAD_PERFORMED=$(field_or_unknown model_load_performed "$MODEL_LOAD_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$MODEL_LOAD_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$MODEL_LOAD_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$MODEL_LOAD_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$MODEL_LOAD_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$MODEL_LOAD_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$MODEL_LOAD_ABS")
MODEL_RUNTIME_PRESENT=$(field_or_unknown model_runtime_present "$MODEL_LOAD_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$MODEL_LOAD_ABS")
RUNTIME_PROCESS_SPAWNED=$(field_or_unknown runtime_process_spawned "$MODEL_LOAD_ABS")
RUNTIME_SESSION_CREATED=$(field_or_unknown runtime_session_created "$MODEL_LOAD_ABS")
TOKEN_GENERATION_PERFORMED=$(field_or_unknown token_generation_performed "$MODEL_LOAD_ABS")
INFERENCE_AUTHORITY=$(field_or_unknown inference_authority "$MODEL_LOAD_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$MODEL_LOAD_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$MODEL_LOAD_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$MODEL_LOAD_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$MODEL_LOAD_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$MODEL_LOAD_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$MODEL_LOAD_ABS")

[ "$MODEL_LOAD_STAGE_VALUE" = "12-model-load-contract" ] || fail "model load stage must be 12-model-load-contract" 65
[ "$MODEL_LOAD_CONTRACT_STATUS" = "contract_only" ] || fail "model load contract must remain contract-only" 65
[ "$MODEL_LOAD_STAGE" = "contract-only" ] || fail "model load stage must be contract-only" 65
[ "$MODEL_LOAD_AUTHORITY" = "0" ] || fail "model load authority must remain denied" 65
[ "$MODEL_LOAD_ALLOWED" = "0" ] || fail "model load must remain disallowed" 65
[ "$MODEL_LOADED" = "0" ] || fail "model must not be loaded" 65
[ "$LOAD_DECISION" = "blocked_contract_only" ] || fail "load decision must be blocked_contract_only" 65
[ "$LOAD_EVIDENCE_PRESENT" = "1" ] || fail "load evidence must be present" 65
[ "$REQUIRES_RUNTIME_INVOCATION_CONTRACT" = "1" ] || fail "load must require runtime invocation" 65
[ "$REQUIRES_INFERENCE_READINESS_CONTRACT" = "1" ] || fail "load must require inference readiness" 65
[ "$REQUIRES_MODEL_REGISTRY_CONTRACT" = "1" ] || fail "load must require model registry" 65
[ "$REQUIRES_PROMPT_CONTRACT" = "1" ] || fail "load must require prompt contract" 65
[ "$REQUIRES_RUNTIME_PROFILE" = "1" ] || fail "load must require runtime profile" 65
[ "$REQUIRES_PROTECTIVE_SAFETY_BOUNDARY" = "1" ] || fail "load must require protective safety" 65
[ "$REQUIRES_TOOL_PREFLIGHT" = "1" ] || fail "load must require tool preflight" 65
[ "$REQUIRES_OPERATOR_REVIEW" = "1" ] || fail "load must require operator review" 65
[ "$REQUIRES_FUTURE_PROMPT_RECEIPT_CONTRACT" = "1" ] || fail "load must require future prompt receipt contract" 65
[ "$LOAD_PROMOTION_ALLOWED" = "0" ] || fail "load must not allow promotion" 65
[ "$MODEL_FILE_OPEN_AUTHORITY" = "0" ] || fail "model file open authority must remain denied" 65
[ "$MODEL_WEIGHT_READ_AUTHORITY" = "0" ] || fail "model weight read authority must remain denied" 65
[ "$MODEL_WEIGHT_MAPPING_AUTHORITY" = "0" ] || fail "model weight mapping authority must remain denied" 65
[ "$MODEL_WEIGHT_VERIFICATION_AUTHORITY" = "0" ] || fail "model weight verification authority must remain denied" 65
[ "$RUNTIME_MODEL_ATTACH_AUTHORITY" = "0" ] || fail "runtime model attach authority must remain denied" 65
[ "$MODEL_SESSION_AUTHORITY" = "0" ] || fail "model session authority must remain denied" 65
[ "$TOKEN_GENERATION_AUTHORITY" = "0" ] || fail "token generation authority must remain denied" 65
[ "$RUNTIME_INVOCATION_AUTHORITY" = "0" ] || fail "runtime invocation authority must remain denied" 65
[ "$RUNTIME_INVOCATION_ALLOWED" = "0" ] || fail "runtime invocation must remain disallowed" 65
[ "$RUNTIME_INVOKED" = "0" ] || fail "runtime must not be invoked" 65
[ "$INVOCATION_DECISION" = "blocked_contract_only" ] || fail "invocation decision must remain blocked" 65
[ "$CANDIDATE_USABLE_FOR_INFERENCE" = "0" ] || fail "candidate must not be usable for inference" 65
[ "$CANDIDATE_SELECTED_FOR_RUNTIME" = "0" ] || fail "candidate must not be selected for runtime" 65
[ "$MODEL_SELECTION_AUTHORITY" = "0" ] || fail "model selection authority must remain denied" 65
[ "$MODEL_FILE_OPENED" = "0" ] || fail "model file must not be opened" 65
[ "$MODEL_FILE_DESCRIPTOR_OPENED" = "0" ] || fail "model file descriptor must not be opened" 65
[ "$MODEL_MEMORY_MAP_CREATED" = "0" ] || fail "model memory map must not be created" 65
[ "$MODEL_WEIGHTS_MAPPED" = "0" ] || fail "model weights must not be mapped" 65
[ "$MODEL_WEIGHTS_LOADED" = "0" ] || fail "model weights must not be loaded" 65
[ "$MODEL_WEIGHTS_ATTACHED" = "0" ] || fail "model weights must not be attached" 65
[ "$MODEL_LOAD_PERFORMED" = "0" ] || fail "model load must not be performed" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "sexual content generation must remain forbidden" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "sexual requests must always be refused" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "manipulation resistance must remain required" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "prompts must not be materialized" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "prompt evaluation authority must remain denied" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "prompts must not be evaluated" 65
[ "$MODEL_RUNTIME_PRESENT" = "0" ] || fail "runtime presence must not be claimed" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "model runtime must not be invoked" 65
[ "$RUNTIME_PROCESS_SPAWNED" = "0" ] || fail "runtime process must not be spawned" 65
[ "$RUNTIME_SESSION_CREATED" = "0" ] || fail "runtime session must not be created" 65
[ "$TOKEN_GENERATION_PERFORMED" = "0" ] || fail "token generation must not be performed" 65
[ "$INFERENCE_AUTHORITY" = "0" ] || fail "inference authority must remain denied" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "inference must not be performed" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "tool execution authority must remain denied" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "network authority must remain denied" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "source mutation authority must remain denied" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "training must not be performed" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "distillation must not be performed" 65

cat > "$REPORT" <<REPORT
NADIA PROMPT RECEIPT CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=13-prompt-receipt-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_receipt_contract_status=contract_only
prompt_receipt_stage=contract-only
prompt_receipt_authority=0
prompt_receipt_allowed=0
prompt_received=0

[inputs]
model_load=$MODEL_LOAD_ABS
model_load_measurement=$MODEL_LOAD_MEASUREMENT
model_load_stage_required=12-model-load-contract
model_load_stage=$MODEL_LOAD_STAGE_VALUE
model_load_contract_status=$MODEL_LOAD_CONTRACT_STATUS
model_registry_stage=$MODEL_REGISTRY_STAGE
model_id=$MODEL_ID
model_family=$MODEL_FAMILY
model_format=$MODEL_FORMAT
quantization=$QUANTIZATION
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB

[prompt_receipt_contract]
prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh
installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt
receipt_decision=blocked_contract_only
receipt_evidence_present=1
requires_model_load_contract=1
requires_runtime_invocation_contract=1
requires_inference_readiness_contract=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_refusal_policy_review=1
requires_prompt_source_boundary=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
requires_future_prompt_materialization_contract=1
prompt_receipt_promotion_allowed=0
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_text_materialization_authority=0
prompt_content_storage_authority=0
prompt_hash_authority=0
prompt_classification_authority=0
model_session_authority=0
token_generation_authority=0

[inherited_model_load_boundary]
model_load_authority=0
model_load_allowed=0
model_loaded=0
load_decision=blocked_contract_only
load_evidence_present=1
load_promotion_allowed=0
model_file_open_authority=0
model_weight_read_authority=0
model_weight_mapping_authority=0
model_weight_verification_authority=0
runtime_model_attach_authority=0
model_file_opened=0
model_file_descriptor_opened=0
model_memory_map_created=0
model_weights_mapped=0
model_weights_loaded=0
model_weights_attached=0
model_load_performed=0

[prompt_boundary]
prompt_source_opened=0
prompt_source_read=0
prompt_bytes_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_content_stored=0
prompt_hash_computed=0
prompt_classified=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0

[runtime_boundary]
runtime_invocation_authority=0
runtime_invocation_allowed=0
runtime_invoked=0
model_runtime_present=0
model_runtime_invoked=0
runtime_process_spawned=0
runtime_session_created=0
token_generation_performed=0
inference_authority=0
inference_performed=0

[model_boundary]
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_load_authority=0
model_weights_loaded=0

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
requires_model_load_review=1
requires_prompt_receipt_review=1
requires_refusal_policy_review=1
requires_future_prompt_materialization_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-receipt-contract.txt"

printf 'NADIA_PROMPT_RECEIPT_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_RECEIVED=0\n'
printf 'NADIA_PROMPT_RECEIPT_AUTHORITY=0\n'
