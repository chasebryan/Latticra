#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-result-review-contract.sh [options]

Options:
  --prompt-evaluation-result <file>  Stage-31 Nadia prompt-evaluation result contract
  --request-class <label>            Operator request classification label
  --review-family <label>            Planned prompt-evaluation result review family label
  --review-format <label>            Planned prompt-evaluation result review format label
  --output <dir>                     Output directory for prompt-evaluation result review contracts

Creates Nadia Stage-32 prompt-evaluation result review contract metadata only.
It verifies the prompt-evaluation result contract and records planned review
requirements before any review record, result record, model-output recording,
runtime invocation, prompt evaluation, dialogue generation, token generation,
or inference boundary. It does not create result-review records, create result
records, record model output, record generated text, invoke a runtime, evaluate
prompts, generate dialogue, generate tokens, run inference, execute tools,
mutate source, train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation result review contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_RESULT_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-result-review boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_RESULT=""
REQUEST_CLASS="awareness-education"
REVIEW_FAMILY="operator-reviewed-prompt-evaluation-result-review"
REVIEW_FORMAT="contract-only-offline-evaluation-result-review"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-result)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-result" 64
      PROMPT_EVALUATION_RESULT="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --review-family)
      [ "$#" -ge 2 ] || fail "missing value for --review-family" 64
      REVIEW_FAMILY="$2"
      shift 2
      ;;
    --review-format)
      [ "$#" -ge 2 ] || fail "missing value for --review-format" 64
      REVIEW_FORMAT="$2"
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

if [ -z "$PROMPT_EVALUATION_RESULT" ] && [ -f "reports/nadia/prompt-evaluation-result/latest-prompt-evaluation-result-contract.txt" ]; then
  PROMPT_EVALUATION_RESULT="reports/nadia/prompt-evaluation-result/latest-prompt-evaluation-result-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_RESULT" ] || fail "prompt evaluation result contract is required" 64
[ -f "$PROMPT_EVALUATION_RESULT" ] || fail "prompt evaluation result contract not found: $PROMPT_EVALUATION_RESULT" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "review family" "$REVIEW_FAMILY"
reject_boundary_label "review format" "$REVIEW_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-result-review"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_RESULT_REVIEW_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-result-review-contract-$TS.txt"

PROMPT_EVALUATION_RESULT_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_RESULT")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_RESULT")")
PROMPT_EVALUATION_RESULT_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_RESULT_ABS")

require_field stage 31-prompt-evaluation-result-contract "prompt evaluation result stage must be 31-prompt-evaluation-result-contract"
require_field prompt_evaluation_result_contract_status contract_only "prompt evaluation result contract must remain contract-only"
require_field prompt_evaluation_result_stage contract-only "prompt evaluation result stage must be contract-only"
require_field prompt_evaluation_result_authority 0 "prompt evaluation result authority must remain denied"
require_field prompt_evaluation_result_allowed 0 "prompt evaluation result must remain disallowed"
require_field prompt_evaluation_result_recorded 0 "prompt evaluation result must not be recorded"
require_field prompt_evaluation_result_created 0 "prompt evaluation result must not be created"
require_field prompt_evaluation_result_performed 0 "prompt evaluation result must not be performed"
require_field prompt_evaluation_result_metadata_present 1 "prompt evaluation result metadata must be present"
require_field prompt_evaluation_result_decision blocked_contract_only "prompt evaluation result decision must be blocked_contract_only"
require_field prompt_evaluation_result_evidence_present 1 "prompt evaluation result evidence must be present"
require_field prompt_evaluation_result_source_policy operator-reviewed-offline "prompt evaluation result source policy must be operator-reviewed-offline"
require_field prompt_evaluation_result_plan_recorded 1 "prompt evaluation result plan must be recorded"
require_field prompt_evaluation_result_result_recorded 0 "prompt evaluation result record must remain absent"
require_field prompt_evaluation_result_runtime_invoked 0 "prompt evaluation result runtime must not be invoked"
require_field requires_prompt_evaluation_invocation_contract 1 "prompt evaluation invocation contract must be required"
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
require_field requires_future_prompt_evaluation_result_review_contract 1 "future prompt evaluation result review contract must be required"
require_field prompt_evaluation_result_promotion_allowed 0 "prompt evaluation result must not allow promotion"
require_field requires_prompt_evaluation_invocation_reference 1 "prompt evaluation invocation reference must be required"
require_field requires_prompt_evaluation_runtime_handoff_reference 1 "runtime handoff reference must be required"
require_field requires_prompt_evaluation_input_reference 1 "prompt evaluation input reference must be required"
require_field requires_context_window_assembly_reference 1 "context window assembly reference must be required"
require_field requires_prompt_token_sequence_reference 1 "prompt token sequence reference must be required"
require_field requires_prompt_tokenization_reference 1 "prompt tokenization reference must be required"
require_field requires_prompt_evaluation_result_schema_policy 1 "prompt evaluation result schema policy must be required"
require_field requires_prompt_evaluation_result_denial_policy 1 "prompt evaluation result denial policy must be required"
require_field requires_prompt_evaluation_result_review_policy 1 "prompt evaluation result review policy must be required"
require_field requires_generated_text_denial_policy 1 "generated text denial policy must be required"
require_field requires_token_generation_denial_policy 1 "token generation denial policy must be required"
require_field requires_operator_approval_record 1 "operator approval record must be required"
require_field requires_official_source_snapshot 1 "official source snapshot must be required"
require_field requires_no_prompt_evaluation_result 1 "prompt evaluation result denial must be required"
require_field requires_no_model_output_recording 1 "model output recording denial must be required"
require_field requires_no_generated_answer 1 "generated answer denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_token_generation 1 "token generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field prompt_evaluation_result_record_created 0 "prompt evaluation result record must not be created"
require_field prompt_evaluation_result_record_validated 0 "prompt evaluation result record must not be validated"
require_field prompt_evaluation_result_record_serialized 0 "prompt evaluation result record must not be serialized"
require_field prompt_evaluation_result_record_written 0 "prompt evaluation result record must not be written"
require_field prompt_evaluation_result_record_submitted 0 "prompt evaluation result record must not be submitted"
require_field prompt_evaluation_result_model_output_recorded 0 "model output must not be recorded"
require_field prompt_evaluation_result_output_text_recorded 0 "output text must not be recorded"
require_field prompt_evaluation_result_score_recorded 0 "result score must not be recorded"
require_field prompt_evaluation_result_token_logprobs_recorded 0 "token log probabilities must not be recorded"
require_field prompt_evaluation_result_completion_reason_recorded 0 "completion reason must not be recorded"
require_field prompt_evaluation_result_error_recorded 0 "prompt evaluation error must not be recorded"
require_field prompt_evaluation_request_created 0 "prompt evaluation request must not be created"
require_field prompt_evaluation_request_serialized 0 "prompt evaluation request must not be serialized"
require_field prompt_evaluation_request_submitted 0 "prompt evaluation request must not be submitted"
require_field runtime_invocation_requested 0 "runtime invocation must not be requested"
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

PROMPT_EVALUATION_RESULT_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_result_contract_status "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_RESULT_STAGE=$(field_or_unknown prompt_evaluation_result_stage "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_RESULT_FAMILY=$(field_or_unknown prompt_evaluation_result_family "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_RESULT_FORMAT=$(field_or_unknown prompt_evaluation_result_format "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_INVOCATION_STAGE=$(field_or_unknown prompt_evaluation_invocation_stage "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE=$(field_or_unknown prompt_evaluation_runtime_handoff_stage "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_EVALUATION_INPUT_STAGE=$(field_or_unknown prompt_evaluation_input_stage "$PROMPT_EVALUATION_RESULT_ABS")
CONTEXT_WINDOW_ASSEMBLY_STAGE=$(field_or_unknown context_window_assembly_stage "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_TOKEN_SEQUENCE_STAGE=$(field_or_unknown prompt_token_sequence_stage "$PROMPT_EVALUATION_RESULT_ABS")
PROMPT_TOKENIZATION_STAGE=$(field_or_unknown prompt_tokenization_stage "$PROMPT_EVALUATION_RESULT_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION RESULT REVIEW CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=32-prompt-evaluation-result-review-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_result_review_contract_status=contract_only
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_review_authority=0
prompt_evaluation_result_review_allowed=0
prompt_evaluation_result_review_recorded=0
prompt_evaluation_result_review_created=0
prompt_evaluation_result_review_performed=0
prompt_evaluation_result_review_metadata_present=1
prompt_evaluation_result_review_family=$REVIEW_FAMILY
prompt_evaluation_result_review_format=$REVIEW_FORMAT
prompt_evaluation_result_review_schema_planned=1
prompt_evaluation_result_review_schema_validated=0
prompt_evaluation_result_review_record_created=0
prompt_evaluation_result_review_record_validated=0
prompt_evaluation_result_review_record_serialized=0
prompt_evaluation_result_review_record_written=0
prompt_evaluation_result_review_record_submitted=0
prompt_evaluation_result_review_decision_recorded=0
prompt_evaluation_result_review_approval_recorded=0
prompt_evaluation_result_review_rejection_recorded=0
prompt_evaluation_result_review_findings_recorded=0
prompt_evaluation_result_record_created=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
prompt_evaluation_result_score_recorded=0
prompt_evaluation_result_token_logprobs_recorded=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_performed=0
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
prompt_evaluation_result=$PROMPT_EVALUATION_RESULT_ABS
prompt_evaluation_result_measurement=$PROMPT_EVALUATION_RESULT_MEASUREMENT
prompt_evaluation_result_stage_required=31-prompt-evaluation-result-contract
prompt_evaluation_result_contract_status=$PROMPT_EVALUATION_RESULT_CONTRACT_STATUS
prompt_evaluation_result_stage=$PROMPT_EVALUATION_RESULT_STAGE
prompt_evaluation_result_family=$PROMPT_EVALUATION_RESULT_FAMILY
prompt_evaluation_result_format=$PROMPT_EVALUATION_RESULT_FORMAT
prompt_evaluation_invocation_stage=$PROMPT_EVALUATION_INVOCATION_STAGE
prompt_evaluation_runtime_handoff_stage=$PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE
prompt_evaluation_input_stage=$PROMPT_EVALUATION_INPUT_STAGE
context_window_assembly_stage=$CONTEXT_WINDOW_ASSEMBLY_STAGE
prompt_token_sequence_stage=$PROMPT_TOKEN_SEQUENCE_STAGE
prompt_tokenization_stage=$PROMPT_TOKENIZATION_STAGE

[prompt_evaluation_result_review_contract]
prompt_evaluation_result_review_contract_command=scripts/nadia-prompt-evaluation-result-review-contract.sh
installed_prompt_evaluation_result_review_contract_command=latticra-nadia prompt-evaluation-result-review
prompt_evaluation_result_review_decision=blocked_contract_only
prompt_evaluation_result_review_evidence_present=1
prompt_evaluation_result_review_source_policy=operator-reviewed-offline
prompt_evaluation_result_review_plan_recorded=1
prompt_evaluation_result_review_method_planned=offline-prompt-evaluation-result-review-policy-review
prompt_evaluation_result_review_result_recorded=0
prompt_evaluation_result_review_runtime_invoked=0
requires_prompt_evaluation_result_contract=1
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
requires_future_prompt_evaluation_result_disposition_contract=1
prompt_evaluation_result_review_promotion_allowed=0

[prompt_evaluation_result_review_requirements]
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_invocation_reference=1
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_result_review_schema_policy=1
requires_prompt_evaluation_result_review_denial_policy=1
requires_prompt_evaluation_result_disposition_policy=1
requires_generated_text_denial_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_result_review=1
requires_no_prompt_evaluation_result=1
requires_no_model_output_read=1
requires_no_model_output_recording=1
requires_no_generated_answer=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_token_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[prompt_evaluation_result_review_denial_boundary]
prompt_evaluation_result_review_authority=0
prompt_evaluation_result_review_allowed=0
prompt_evaluation_result_review_open_authority=0
prompt_evaluation_result_review_read_authority=0
prompt_evaluation_result_review_write_authority=0
prompt_evaluation_result_review_execute_authority=0
prompt_evaluation_result_review_runtime_authority=0
prompt_evaluation_result_review_prompt_evaluation_authority=0
prompt_evaluation_result_review_token_generation_authority=0
prompt_evaluation_result_review_inference_authority=0
prompt_evaluation_result_review_generation_authority=0
prompt_evaluation_result_review_recording_authority=0
prompt_evaluation_result_review_performed=0
prompt_evaluation_result_review_created=0
prompt_evaluation_result_review_materialized=0
prompt_evaluation_result_review_loaded=0
prompt_evaluation_result_review_opened=0
prompt_evaluation_result_review_read=0
prompt_evaluation_result_review_validated=0
prompt_evaluation_result_review_serialized=0
prompt_evaluation_result_review_written=0
prompt_evaluation_result_review_record_created=0
prompt_evaluation_result_review_record_validated=0
prompt_evaluation_result_review_record_serialized=0
prompt_evaluation_result_review_record_written=0
prompt_evaluation_result_review_record_submitted=0
prompt_evaluation_result_review_decision_recorded=0
prompt_evaluation_result_review_approval_recorded=0
prompt_evaluation_result_review_rejection_recorded=0
prompt_evaluation_result_review_findings_recorded=0
prompt_evaluation_result_review_runtime_invoked=0

[prompt_evaluation_result_denial_boundary]
prompt_evaluation_result_authority=0
prompt_evaluation_result_allowed=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_performed=0
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

[runtime_boundary]
runtime_invocation_requested=0
runtime_invocation_authority=0
runtime_session_authority=0
runtime_invoked=0
runtime_session_created=0
runtime_process_spawned=0
runtime_binary_executed=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0

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
requires_prompt_evaluation_result_review=1
requires_prompt_evaluation_result_disposition_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_result_disposition_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-result-review-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_RESULT_REVIEW_RECORDED=0\n'
printf 'NADIA_RUNTIME_INVOKED=0\n'
