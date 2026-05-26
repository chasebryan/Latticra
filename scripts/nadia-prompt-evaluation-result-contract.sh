#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-result-contract.sh [options]

Options:
  --prompt-evaluation-invocation <file>  Stage-30 Nadia prompt-evaluation invocation contract
  --request-class <label>                Operator request classification label
  --result-family <label>                Planned prompt-evaluation result family label
  --result-format <label>                Planned prompt-evaluation result format label
  --output <dir>                         Output directory for prompt-evaluation result contracts

Creates Nadia Stage-31 prompt-evaluation result contract metadata only.
It verifies the prompt-evaluation invocation contract and records planned
prompt-evaluation result requirements before any result recording, model
output recording, runtime invocation, prompt evaluation, dialogue generation,
token generation, or inference boundary. It does not create result records,
record model output, record generated text, invoke a runtime, evaluate prompts,
generate dialogue, generate tokens, run inference, execute tools, mutate source,
train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation result contract: %s\n' "$1" >&2
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

require_field() {
  key="$1"
  expected="$2"
  message="$3"
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_INVOCATION_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-result boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_INVOCATION=""
REQUEST_CLASS="awareness-education"
RESULT_FAMILY="operator-reviewed-prompt-evaluation-result"
RESULT_FORMAT="contract-only-offline-evaluation-result"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-invocation)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-invocation" 64
      PROMPT_EVALUATION_INVOCATION="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --result-family)
      [ "$#" -ge 2 ] || fail "missing value for --result-family" 64
      RESULT_FAMILY="$2"
      shift 2
      ;;
    --result-format)
      [ "$#" -ge 2 ] || fail "missing value for --result-format" 64
      RESULT_FORMAT="$2"
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

if [ -z "$PROMPT_EVALUATION_INVOCATION" ] && [ -f "reports/nadia/prompt-evaluation-invocation/latest-prompt-evaluation-invocation-contract.txt" ]; then
  PROMPT_EVALUATION_INVOCATION="reports/nadia/prompt-evaluation-invocation/latest-prompt-evaluation-invocation-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_INVOCATION" ] || fail "prompt evaluation invocation contract is required" 64
[ -f "$PROMPT_EVALUATION_INVOCATION" ] || fail "prompt evaluation invocation contract not found: $PROMPT_EVALUATION_INVOCATION" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "result family" "$RESULT_FAMILY"
reject_boundary_label "result format" "$RESULT_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-result"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_RESULT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-result-contract-$TS.txt"

PROMPT_EVALUATION_INVOCATION_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_INVOCATION")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_INVOCATION")")
PROMPT_EVALUATION_INVOCATION_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_INVOCATION_ABS")

require_field stage 30-prompt-evaluation-invocation-contract "prompt evaluation invocation stage must be 30-prompt-evaluation-invocation-contract"
require_field prompt_evaluation_invocation_contract_status contract_only "prompt evaluation invocation contract must remain contract-only"
require_field prompt_evaluation_invocation_stage contract-only "prompt evaluation invocation stage must be contract-only"
require_field prompt_evaluation_invocation_authority 0 "prompt evaluation invocation authority must remain denied"
require_field prompt_evaluation_invocation_allowed 0 "prompt evaluation invocation must remain disallowed"
require_field prompt_evaluation_invocation_performed 0 "prompt evaluation invocation must not be performed"
require_field prompt_evaluation_invocation_metadata_present 1 "prompt evaluation invocation metadata must be present"
require_field prompt_evaluation_invocation_decision blocked_contract_only "prompt evaluation invocation decision must be blocked_contract_only"
require_field prompt_evaluation_invocation_evidence_present 1 "prompt evaluation invocation evidence must be present"
require_field prompt_evaluation_invocation_source_policy operator-reviewed-offline "prompt evaluation invocation source policy must be operator-reviewed-offline"
require_field prompt_evaluation_invocation_plan_recorded 1 "prompt evaluation invocation plan must be recorded"
require_field prompt_evaluation_invocation_result_recorded 0 "prompt evaluation invocation result must not be recorded"
require_field prompt_evaluation_invocation_runtime_invoked 0 "prompt evaluation invocation runtime must not be invoked"
require_field requires_prompt_evaluation_runtime_handoff_contract 1 "prompt evaluation runtime handoff contract must be required"
require_field requires_prompt_evaluation_input_contract 1 "prompt evaluation input contract must be required"
require_field requires_context_window_assembly_contract 1 "context window assembly contract must be required"
require_field requires_prompt_token_sequence_contract 1 "prompt token sequence contract must be required"
require_field requires_prompt_tokenization_contract 1 "prompt tokenization contract must be required"
require_field requires_tokenizer_runtime_attachment_contract 1 "tokenizer runtime attachment contract must be required"
require_field requires_runtime_invocation_contract 1 "runtime invocation contract must be required"
require_field requires_model_load_contract 1 "model load contract must be required"
require_field requires_inference_readiness_contract 1 "inference readiness contract must be required"
require_field requires_local_model_registry_contract 1 "local model registry contract must be required"
require_field requires_prompt_materialization_contract 1 "prompt materialization contract must be required"
require_field requires_prompt_receipt_contract 1 "prompt receipt contract must be required"
require_field requires_future_prompt_evaluation_result_contract 1 "future prompt evaluation result contract must be required"
require_field prompt_evaluation_invocation_promotion_allowed 0 "prompt evaluation invocation must not allow promotion"
require_field requires_prompt_evaluation_runtime_handoff_reference 1 "runtime handoff reference must be required"
require_field requires_prompt_evaluation_input_reference 1 "prompt evaluation input reference must be required"
require_field requires_context_window_assembly_reference 1 "context window assembly reference must be required"
require_field requires_prompt_token_sequence_reference 1 "prompt token sequence reference must be required"
require_field requires_prompt_tokenization_reference 1 "prompt tokenization reference must be required"
require_field requires_prompt_evaluation_invocation_schema_policy 1 "prompt evaluation invocation schema policy must be required"
require_field requires_prompt_evaluation_invocation_denial_policy 1 "prompt evaluation invocation denial policy must be required"
require_field requires_prompt_evaluation_result_schema_policy 1 "prompt evaluation result schema policy must be required"
require_field requires_token_generation_denial_policy 1 "token generation denial policy must be required"
require_field requires_operator_approval_record 1 "operator approval record must be required"
require_field requires_official_source_snapshot 1 "official source snapshot must be required"
require_field requires_no_prompt_evaluation_invocation 1 "prompt evaluation invocation denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_token_generation 1 "token generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field prompt_evaluation_invocation_request_created 0 "prompt evaluation invocation request must not be created"
require_field prompt_evaluation_invocation_request_validated 0 "prompt evaluation invocation request must not be validated"
require_field prompt_evaluation_invocation_request_serialized 0 "prompt evaluation invocation request must not be serialized"
require_field prompt_evaluation_invocation_request_written 0 "prompt evaluation invocation request must not be written"
require_field prompt_evaluation_invocation_request_submitted 0 "prompt evaluation invocation request must not be submitted"
require_field prompt_evaluation_invocation_request_scheduled 0 "prompt evaluation invocation request must not be scheduled"
require_field prompt_evaluation_invocation_request_queued 0 "prompt evaluation invocation request must not be queued"
require_field prompt_evaluation_invocation_runtime_selected 0 "runtime must not be selected"
require_field prompt_evaluation_invocation_model_selected 0 "model must not be selected"
require_field prompt_evaluation_invocation_session_created 0 "prompt evaluation invocation session must not be created"
require_field runtime_handoff_created 0 "runtime handoff must not be created"
require_field runtime_handoff_submitted 0 "runtime handoff must not be submitted"
require_field prompt_evaluation_request_created 0 "prompt evaluation request must not be created"
require_field prompt_evaluation_request_serialized 0 "prompt evaluation request must not be serialized"
require_field prompt_evaluation_request_submitted 0 "prompt evaluation request must not be submitted"
require_field runtime_invocation_requested 0 "runtime invocation must not be requested"
require_field runtime_invocation_authority 0 "runtime invocation authority must remain denied"
require_field runtime_session_authority 0 "runtime session authority must remain denied"
require_field runtime_invoked 0 "runtime must not be invoked"
require_field runtime_session_created 0 "runtime session must not be created"
require_field runtime_process_spawned 0 "runtime process must not be spawned"
require_field runtime_binary_executed 0 "runtime binary must not be executed"
require_field prompt_evaluation_authority 0 "prompt evaluation authority must remain denied"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_authority 0 "token generation authority must remain denied"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_authority 0 "inference authority must remain denied"
require_field inference_performed 0 "inference must not be performed"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field question_generated 0 "question must not be generated"
require_field answer_generated 0 "answer must not be generated"
require_field answer_text_generated 0 "answer text must not be generated"
require_field q_and_a_format_required 1 "Q&A format requirement must be present"
require_field survivor_centered_dialogue_required 1 "survivor-centered dialogue requirement must be required"
require_field official_source_grounding_required 1 "official source grounding must be required"
require_field live_web_lookup_authority 0 "live web lookup authority must remain denied"
require_field sexual_user_request_authority 0 "sexual user request authority must remain denied"
require_field sexual_content_generation 0 "sexual content generation must remain forbidden"
require_field sexualized_dialogue_generation 0 "sexualized dialogue generation must remain forbidden"
require_field graphic_sexual_detail_allowed 0 "graphic sexual detail must remain forbidden"
require_field erotic_content_allowed 0 "erotic content must remain forbidden"
require_field roleplay_allowed 0 "roleplay must remain forbidden"
require_field survivor_impersonation_allowed 0 "survivor impersonation must remain forbidden"
require_field victim_blaming_allowed 0 "victim blaming must remain forbidden"
require_field genocide_denial_allowed 0 "genocide denial must remain forbidden"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"
require_field network_authority 0 "network authority must remain denied"
require_field tool_execution_authority 0 "tool execution authority must remain denied"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field source_mutation_authority 0 "source mutation authority must remain denied"
require_field self_modification_authority 0 "self-modification authority must remain denied"
require_field training_performed 0 "training must not be performed"
require_field distillation_performed 0 "distillation must not be performed"

PROMPT_EVALUATION_INVOCATION_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_invocation_contract_status "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_EVALUATION_INVOCATION_STAGE=$(field_or_unknown prompt_evaluation_invocation_stage "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_EVALUATION_INVOCATION_FAMILY=$(field_or_unknown prompt_evaluation_invocation_family "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_EVALUATION_INVOCATION_FORMAT=$(field_or_unknown prompt_evaluation_invocation_format "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE=$(field_or_unknown prompt_evaluation_runtime_handoff_stage "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_EVALUATION_INPUT_STAGE=$(field_or_unknown prompt_evaluation_input_stage "$PROMPT_EVALUATION_INVOCATION_ABS")
CONTEXT_WINDOW_ASSEMBLY_STAGE=$(field_or_unknown context_window_assembly_stage "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_TOKEN_SEQUENCE_STAGE=$(field_or_unknown prompt_token_sequence_stage "$PROMPT_EVALUATION_INVOCATION_ABS")
PROMPT_TOKENIZATION_STAGE=$(field_or_unknown prompt_tokenization_stage "$PROMPT_EVALUATION_INVOCATION_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION RESULT CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=31-prompt-evaluation-result-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_result_contract_status=contract_only
prompt_evaluation_result_stage=contract-only
prompt_evaluation_result_authority=0
prompt_evaluation_result_allowed=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_performed=0
prompt_evaluation_result_metadata_present=1
prompt_evaluation_result_family=$RESULT_FAMILY
prompt_evaluation_result_format=$RESULT_FORMAT
prompt_evaluation_result_schema_planned=1
prompt_evaluation_result_schema_validated=0
prompt_evaluation_result_record_created=0
prompt_evaluation_result_record_validated=0
prompt_evaluation_result_record_serialized=0
prompt_evaluation_result_record_written=0
prompt_evaluation_result_record_submitted=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
prompt_evaluation_result_score_recorded=0
prompt_evaluation_result_token_logprobs_recorded=0
prompt_evaluation_result_completion_reason_recorded=0
prompt_evaluation_result_error_recorded=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_submitted=0
runtime_handoff_created=0
runtime_handoff_submitted=0
runtime_invocation_requested=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
prompt_evaluation_invocation=$PROMPT_EVALUATION_INVOCATION_ABS
prompt_evaluation_invocation_measurement=$PROMPT_EVALUATION_INVOCATION_MEASUREMENT
prompt_evaluation_invocation_stage_required=30-prompt-evaluation-invocation-contract
prompt_evaluation_invocation_contract_status=$PROMPT_EVALUATION_INVOCATION_CONTRACT_STATUS
prompt_evaluation_invocation_stage=$PROMPT_EVALUATION_INVOCATION_STAGE
prompt_evaluation_invocation_family=$PROMPT_EVALUATION_INVOCATION_FAMILY
prompt_evaluation_invocation_format=$PROMPT_EVALUATION_INVOCATION_FORMAT
prompt_evaluation_runtime_handoff_stage=$PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE
prompt_evaluation_input_stage=$PROMPT_EVALUATION_INPUT_STAGE
context_window_assembly_stage=$CONTEXT_WINDOW_ASSEMBLY_STAGE
prompt_token_sequence_stage=$PROMPT_TOKEN_SEQUENCE_STAGE
prompt_tokenization_stage=$PROMPT_TOKENIZATION_STAGE

[prompt_evaluation_result_contract]
prompt_evaluation_result_contract_command=scripts/nadia-prompt-evaluation-result-contract.sh
installed_prompt_evaluation_result_contract_command=latticra-nadia prompt-evaluation-result
prompt_evaluation_result_decision=blocked_contract_only
prompt_evaluation_result_evidence_present=1
prompt_evaluation_result_source_policy=operator-reviewed-offline
prompt_evaluation_result_plan_recorded=1
prompt_evaluation_result_method_planned=offline-prompt-evaluation-result-policy-review
prompt_evaluation_result_result_recorded=0
prompt_evaluation_result_runtime_invoked=0
requires_prompt_evaluation_invocation_contract=1
requires_prompt_evaluation_runtime_handoff_contract=1
requires_prompt_evaluation_input_contract=1
requires_context_window_assembly_contract=1
requires_prompt_token_sequence_contract=1
requires_prompt_tokenization_contract=1
requires_tokenizer_runtime_attachment_contract=1
requires_runtime_invocation_contract=1
requires_model_load_contract=1
requires_inference_readiness_contract=1
requires_local_model_registry_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_future_prompt_evaluation_result_review_contract=1
prompt_evaluation_result_promotion_allowed=0

[prompt_evaluation_result_requirements]
requires_prompt_evaluation_invocation_reference=1
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_result_schema_policy=1
requires_prompt_evaluation_result_denial_policy=1
requires_prompt_evaluation_result_review_policy=1
requires_generated_text_denial_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_result=1
requires_no_model_output_recording=1
requires_no_generated_answer=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_token_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[prompt_evaluation_result_denial_boundary]
prompt_evaluation_result_authority=0
prompt_evaluation_result_allowed=0
prompt_evaluation_result_open_authority=0
prompt_evaluation_result_read_authority=0
prompt_evaluation_result_write_authority=0
prompt_evaluation_result_execute_authority=0
prompt_evaluation_result_runtime_authority=0
prompt_evaluation_result_prompt_evaluation_authority=0
prompt_evaluation_result_token_generation_authority=0
prompt_evaluation_result_inference_authority=0
prompt_evaluation_result_generation_authority=0
prompt_evaluation_result_recording_authority=0
prompt_evaluation_result_performed=0
prompt_evaluation_result_created=0
prompt_evaluation_result_materialized=0
prompt_evaluation_result_loaded=0
prompt_evaluation_result_opened=0
prompt_evaluation_result_read=0
prompt_evaluation_result_validated=0
prompt_evaluation_result_serialized=0
prompt_evaluation_result_written=0
prompt_evaluation_result_record_created=0
prompt_evaluation_result_record_validated=0
prompt_evaluation_result_record_serialized=0
prompt_evaluation_result_record_written=0
prompt_evaluation_result_record_submitted=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
prompt_evaluation_result_score_recorded=0
prompt_evaluation_result_token_logprobs_recorded=0
prompt_evaluation_result_completion_reason_recorded=0
prompt_evaluation_result_error_recorded=0
prompt_evaluation_result_runtime_invoked=0
prompt_evaluation_request_created=0
prompt_evaluation_request_serialized=0
prompt_evaluation_request_submitted=0
runtime_invocation_requested=0
runtime_invoked=0
runtime_session_created=0
runtime_process_spawned=0
runtime_binary_executed=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0

[prompt_evaluation_invocation_denial_boundary]
prompt_evaluation_invocation_authority=0
prompt_evaluation_invocation_allowed=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_validated=0
prompt_evaluation_invocation_request_serialized=0
prompt_evaluation_invocation_request_written=0
prompt_evaluation_invocation_request_submitted=0
prompt_evaluation_invocation_request_scheduled=0
prompt_evaluation_invocation_request_queued=0
prompt_evaluation_invocation_runtime_selected=0
prompt_evaluation_invocation_model_selected=0
prompt_evaluation_invocation_session_created=0
prompt_evaluation_invocation_runtime_invoked=0

[prompt_evaluation_runtime_handoff_denial_boundary]
prompt_evaluation_runtime_handoff_authority=0
prompt_evaluation_runtime_handoff_allowed=0
prompt_evaluation_runtime_handoff_performed=0
runtime_handoff_created=0
runtime_handoff_submitted=0

[prompt_evaluation_input_denial_boundary]
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0

[dialogue_scope]
future_qa_dialogue_capability_planned=1
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
respectful_tone_required=1
plain_language_required=1
source_attribution_required=1
official_source_grounding_required=1
source_snapshot_policy=operator-reviewed-offline
live_web_lookup_authority=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[dialogue_safety_boundary]
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
survivor_identifying_speculation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
hate_or_collective_blame_allowed=0
medical_advice_authority=0
legal_advice_authority=0
trauma_counseling_authority=0
crisis_intervention_authority=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1

[runtime_boundary]
runtime_invocation_authority=0
runtime_session_authority=0
runtime_invoked=0
runtime_session_created=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0

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
requires_awareness_topic_review=1
requires_official_source_review=1
requires_prompt_evaluation_invocation_review=1
requires_prompt_evaluation_result_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_result_review_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-result-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_RESULT_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_RESULT_RECORDED=0\n'
printf 'NADIA_RUNTIME_INVOKED=0\n'
