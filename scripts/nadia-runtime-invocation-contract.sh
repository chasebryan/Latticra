#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-runtime-invocation-contract.sh [options]

Options:
  --inference-readiness <file>  Stage-10 Nadia inference-readiness contract
  --request-class <label>       Operator request classification label
  --output <dir>                Output directory for runtime-invocation contracts

Creates Nadia Stage-11 runtime-invocation contract metadata only. It does not
materialize prompts, evaluate prompts, load model weights, spawn a runtime,
create a model session, generate tokens, run inference, execute tools, mutate
source, train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia runtime invocation contract: %s\n' "$1" >&2
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
      fail "$name is outside Nadia runtime-invocation boundary" 65
      ;;
  esac
}

INFERENCE_READINESS=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --inference-readiness)
      [ "$#" -ge 2 ] || fail "missing value for --inference-readiness" 64
      INFERENCE_READINESS="$2"
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

if [ -z "$INFERENCE_READINESS" ] && [ -f "reports/nadia/inference-readiness/latest-inference-readiness-contract.txt" ]; then
  INFERENCE_READINESS="reports/nadia/inference-readiness/latest-inference-readiness-contract.txt"
fi

[ -n "$INFERENCE_READINESS" ] || fail "inference readiness contract is required" 64
[ -f "$INFERENCE_READINESS" ] || fail "inference readiness contract not found: $INFERENCE_READINESS" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/runtime-invocation"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_RUNTIME_INVOCATION_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-runtime-invocation-contract-$TS.txt"

INFERENCE_READINESS_ABS=$(cd "$(dirname -- "$INFERENCE_READINESS")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$INFERENCE_READINESS")")
INFERENCE_READINESS_MEASUREMENT=$(measure_file "$INFERENCE_READINESS_ABS")
READINESS_STAGE=$(field_or_unknown stage "$INFERENCE_READINESS_ABS")
READINESS_CONTRACT_STATUS=$(field_or_unknown inference_readiness_contract_status "$INFERENCE_READINESS_ABS")
INFERENCE_READINESS_STAGE=$(field_or_unknown inference_readiness_stage "$INFERENCE_READINESS_ABS")
INFERENCE_READINESS_AUTHORITY=$(field_or_unknown inference_readiness_authority "$INFERENCE_READINESS_ABS")
INFERENCE_READY=$(field_or_unknown inference_ready "$INFERENCE_READINESS_ABS")
READINESS_DECISION=$(field_or_unknown readiness_decision "$INFERENCE_READINESS_ABS")
READINESS_EVIDENCE_PRESENT=$(field_or_unknown readiness_evidence_present "$INFERENCE_READINESS_ABS")
REQUIRES_MODEL_REGISTRY_CONTRACT=$(field_or_unknown requires_model_registry_contract "$INFERENCE_READINESS_ABS")
REQUIRES_PROMPT_CONTRACT=$(field_or_unknown requires_prompt_contract "$INFERENCE_READINESS_ABS")
REQUIRES_RUNTIME_PROFILE=$(field_or_unknown requires_runtime_profile "$INFERENCE_READINESS_ABS")
REQUIRES_PROTECTIVE_SAFETY_BOUNDARY=$(field_or_unknown requires_protective_safety_boundary "$INFERENCE_READINESS_ABS")
REQUIRES_TOOL_PREFLIGHT=$(field_or_unknown requires_tool_preflight "$INFERENCE_READINESS_ABS")
REQUIRES_OPERATOR_REVIEW=$(field_or_unknown requires_operator_review "$INFERENCE_READINESS_ABS")
REQUIRES_FUTURE_RUNTIME_INVOCATION_CONTRACT=$(field_or_unknown requires_future_runtime_invocation_contract "$INFERENCE_READINESS_ABS")
READINESS_PROMOTION_ALLOWED=$(field_or_unknown readiness_promotion_allowed "$INFERENCE_READINESS_ABS")
RUNTIME_INVOCATION_AUTHORITY=$(field_or_unknown runtime_invocation_authority "$INFERENCE_READINESS_ABS")
TOKEN_GENERATION_AUTHORITY=$(field_or_unknown token_generation_authority "$INFERENCE_READINESS_ABS")
MODEL_SESSION_AUTHORITY=$(field_or_unknown model_session_authority "$INFERENCE_READINESS_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$INFERENCE_READINESS_ABS")
MODEL_ID=$(field_or_unknown model_id "$INFERENCE_READINESS_ABS")
MODEL_FAMILY=$(field_or_unknown model_family "$INFERENCE_READINESS_ABS")
MODEL_FORMAT=$(field_or_unknown model_format "$INFERENCE_READINESS_ABS")
QUANTIZATION=$(field_or_unknown quantization "$INFERENCE_READINESS_ABS")
CONTEXT_TOKENS=$(field_or_unknown context_window_tokens "$INFERENCE_READINESS_ABS")
MEMORY_MIB=$(field_or_unknown memory_budget_mib "$INFERENCE_READINESS_ABS")
CANDIDATE_USABLE_FOR_INFERENCE=$(field_or_unknown candidate_usable_for_inference "$INFERENCE_READINESS_ABS")
CANDIDATE_SELECTED_FOR_RUNTIME=$(field_or_unknown candidate_selected_for_runtime "$INFERENCE_READINESS_ABS")
MODEL_SELECTION_AUTHORITY=$(field_or_unknown model_selection_authority "$INFERENCE_READINESS_ABS")
MODEL_LOAD_AUTHORITY=$(field_or_unknown model_load_authority "$INFERENCE_READINESS_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$INFERENCE_READINESS_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$INFERENCE_READINESS_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$INFERENCE_READINESS_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$INFERENCE_READINESS_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$INFERENCE_READINESS_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$INFERENCE_READINESS_ABS")
MODEL_RUNTIME_PRESENT=$(field_or_unknown model_runtime_present "$INFERENCE_READINESS_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$INFERENCE_READINESS_ABS")
RUNTIME_INVOKED=$(field_or_unknown runtime_invoked "$INFERENCE_READINESS_ABS")
INFERENCE_AUTHORITY=$(field_or_unknown inference_authority "$INFERENCE_READINESS_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$INFERENCE_READINESS_ABS")
MODEL_WEIGHTS_INSTALLED=$(field_or_unknown model_weights_installed "$INFERENCE_READINESS_ABS")
MODEL_WEIGHTS_LOADED=$(field_or_unknown model_weights_loaded "$INFERENCE_READINESS_ABS")
MODEL_WEIGHTS_COPIED=$(field_or_unknown model_weights_copied "$INFERENCE_READINESS_ABS")
MODEL_WEIGHTS_DOWNLOADED=$(field_or_unknown model_weights_downloaded "$INFERENCE_READINESS_ABS")
MODEL_WEIGHTS_INSPECTED=$(field_or_unknown model_weights_inspected "$INFERENCE_READINESS_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$INFERENCE_READINESS_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$INFERENCE_READINESS_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$INFERENCE_READINESS_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$INFERENCE_READINESS_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$INFERENCE_READINESS_ABS")

[ "$READINESS_STAGE" = "10-inference-readiness-contract" ] || fail "inference readiness stage must be 10-inference-readiness-contract" 65
[ "$READINESS_CONTRACT_STATUS" = "contract_only" ] || fail "inference readiness contract must remain contract-only" 65
[ "$INFERENCE_READINESS_STAGE" = "contract-only" ] || fail "inference readiness stage must be contract-only" 65
[ "$INFERENCE_READINESS_AUTHORITY" = "0" ] || fail "inference readiness must not grant authority" 65
[ "$INFERENCE_READY" = "0" ] || fail "inference readiness must remain blocked" 65
[ "$READINESS_DECISION" = "blocked_contract_only" ] || fail "readiness decision must be blocked_contract_only" 65
[ "$READINESS_EVIDENCE_PRESENT" = "1" ] || fail "readiness evidence must be present" 65
[ "$REQUIRES_MODEL_REGISTRY_CONTRACT" = "1" ] || fail "readiness must require a model registry contract" 65
[ "$REQUIRES_PROMPT_CONTRACT" = "1" ] || fail "readiness must require a prompt contract" 65
[ "$REQUIRES_RUNTIME_PROFILE" = "1" ] || fail "readiness must require a runtime profile" 65
[ "$REQUIRES_PROTECTIVE_SAFETY_BOUNDARY" = "1" ] || fail "readiness must require protective safety" 65
[ "$REQUIRES_TOOL_PREFLIGHT" = "1" ] || fail "readiness must require tool preflight" 65
[ "$REQUIRES_OPERATOR_REVIEW" = "1" ] || fail "readiness must require operator review" 65
[ "$REQUIRES_FUTURE_RUNTIME_INVOCATION_CONTRACT" = "1" ] || fail "readiness must require a future runtime invocation contract" 65
[ "$READINESS_PROMOTION_ALLOWED" = "0" ] || fail "readiness must not allow promotion" 65
[ "$RUNTIME_INVOCATION_AUTHORITY" = "0" ] || fail "readiness must not grant runtime invocation authority" 65
[ "$TOKEN_GENERATION_AUTHORITY" = "0" ] || fail "readiness must not grant token generation authority" 65
[ "$MODEL_SESSION_AUTHORITY" = "0" ] || fail "readiness must not grant model session authority" 65
[ "$CANDIDATE_USABLE_FOR_INFERENCE" = "0" ] || fail "model candidate must not be usable for inference" 65
[ "$CANDIDATE_SELECTED_FOR_RUNTIME" = "0" ] || fail "model candidate must not be selected for runtime" 65
[ "$MODEL_SELECTION_AUTHORITY" = "0" ] || fail "readiness must not grant model selection authority" 65
[ "$MODEL_LOAD_AUTHORITY" = "0" ] || fail "readiness must not grant model load authority" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "readiness must forbid sexual content generation" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "readiness must always refuse sexual requests" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "readiness must require manipulation resistance" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "readiness must not materialize prompts" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "readiness must not grant prompt evaluation authority" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "readiness must not evaluate prompts" 65
[ "$MODEL_RUNTIME_PRESENT" = "0" ] || fail "readiness must not claim runtime presence" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "readiness must not invoke a model runtime" 65
[ "$RUNTIME_INVOKED" = "0" ] || fail "readiness must not invoke runtime" 65
[ "$INFERENCE_AUTHORITY" = "0" ] || fail "readiness must not grant inference authority" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "readiness must not include inference" 65
[ "$MODEL_WEIGHTS_INSTALLED" = "0" ] || fail "readiness must not install model weights" 65
[ "$MODEL_WEIGHTS_LOADED" = "0" ] || fail "readiness must not load model weights" 65
[ "$MODEL_WEIGHTS_COPIED" = "0" ] || fail "readiness must not copy model weights" 65
[ "$MODEL_WEIGHTS_DOWNLOADED" = "0" ] || fail "readiness must not download model weights" 65
[ "$MODEL_WEIGHTS_INSPECTED" = "0" ] || fail "readiness must not inspect model weights" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "readiness must not grant tool execution authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "readiness must not include network authority" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "readiness must not grant source mutation authority" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "readiness must not include training" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "readiness must not include distillation" 65

cat > "$REPORT" <<REPORT
NADIA RUNTIME INVOCATION CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=11-runtime-invocation-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
runtime_invocation_contract_status=contract_only
runtime_invocation_stage=contract-only
runtime_invocation_authority=0
runtime_invocation_allowed=0
runtime_invoked=0

[inputs]
inference_readiness=$INFERENCE_READINESS_ABS
inference_readiness_measurement=$INFERENCE_READINESS_MEASUREMENT
inference_readiness_stage_required=10-inference-readiness-contract
inference_readiness_stage=$READINESS_STAGE
inference_readiness_contract_status=$READINESS_CONTRACT_STATUS
model_registry_stage=$MODEL_REGISTRY_STAGE
model_id=$MODEL_ID
model_family=$MODEL_FAMILY
model_format=$MODEL_FORMAT
quantization=$QUANTIZATION
context_window_tokens=$CONTEXT_TOKENS
memory_budget_mib=$MEMORY_MIB

[invocation_contract]
runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh
installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation
invocation_decision=blocked_contract_only
invocation_evidence_present=1
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
requires_refusal_policy_review=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
requires_future_model_load_contract=1
invocation_promotion_allowed=0
runtime_process_spawn_authority=0
runtime_binary_execution_authority=0
runtime_session_authority=0
model_session_authority=0
token_generation_authority=0

[inherited_readiness_boundary]
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
readiness_evidence_present=1
readiness_promotion_allowed=0
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_load_authority=0

[runtime_boundary]
model_runtime_present=0
model_runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0
runtime_invoked=0
model_weights_installed=0
model_weights_loaded=0
model_weights_copied=0
model_weights_downloaded=0
model_weights_inspected=0
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
requires_inference_readiness_review=1
requires_runtime_invocation_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_model_safety_review=1
requires_future_model_load_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-runtime-invocation-contract.txt"

printf 'NADIA_RUNTIME_INVOCATION_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_RUNTIME_INVOKED=0\n'
printf 'NADIA_RUNTIME_INVOCATION_AUTHORITY=0\n'
