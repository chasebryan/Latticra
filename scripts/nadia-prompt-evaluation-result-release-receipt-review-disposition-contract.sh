#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh [options]

Options:
  --prompt-evaluation-result-release-receipt-review <file>  Stage-36 Nadia prompt-evaluation result release receipt review contract
  --request-class <label>                                   Operator request classification label
  --disposition-family <label>                              Planned prompt-evaluation result release receipt review disposition family label
  --disposition-format <label>                              Planned prompt-evaluation result release receipt review disposition format label
  --output <dir>                                            Output directory for prompt-evaluation result release receipt review disposition contracts

Creates Nadia Stage-37 prompt-evaluation result release receipt review
disposition contract metadata only. It verifies the prompt-evaluation result
release receipt review contract and records planned review-disposition
requirements before any review-disposition record, review decision, review
findings, receipt record, receipt signing, release record, model-output
access, runtime invocation, prompt evaluation, dialogue generation, token
generation, or inference boundary. It does not create dispositions, review
receipts, approve receipts, reject receipts, create receipts, sign receipts,
publish receipts, create release records, read or record model output, record
generated text, invoke a runtime, evaluate prompts, generate dialogue,
generate tokens, run inference, execute tools, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation result release receipt review disposition contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-result-release-receipt-review-disposition boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW=""
REQUEST_CLASS="awareness-education"
DISPOSITION_FAMILY="operator-reviewed-prompt-evaluation-result-release-receipt-review-disposition"
DISPOSITION_FORMAT="contract-only-offline-evaluation-result-release-receipt-review-disposition"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-result-release-receipt-review)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-result-release-receipt-review" 64
      PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --disposition-family)
      [ "$#" -ge 2 ] || fail "missing value for --disposition-family" 64
      DISPOSITION_FAMILY="$2"
      shift 2
      ;;
    --disposition-format)
      [ "$#" -ge 2 ] || fail "missing value for --disposition-format" 64
      DISPOSITION_FORMAT="$2"
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

if [ -z "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW" ] && [ -f "reports/nadia/prompt-evaluation-result-release-receipt-review/latest-prompt-evaluation-result-release-receipt-review-contract.txt" ]; then
  PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW="reports/nadia/prompt-evaluation-result-release-receipt-review/latest-prompt-evaluation-result-release-receipt-review-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW" ] || fail "prompt evaluation result release receipt review contract is required" 64
[ -f "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW" ] || fail "prompt evaluation result release receipt review contract not found: $PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "disposition family" "$DISPOSITION_FAMILY"
reject_boundary_label "disposition format" "$DISPOSITION_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-result-release-receipt-review-disposition"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-$TS.txt"

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW")")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")

require_field stage 36-prompt-evaluation-result-release-receipt-review-contract "prompt evaluation result release receipt review stage must be 36-prompt-evaluation-result-release-receipt-review-contract"
require_field prompt_evaluation_result_release_receipt_review_contract_status contract_only "prompt evaluation result release receipt review contract must remain contract-only"
require_field prompt_evaluation_result_release_receipt_review_stage contract-only "prompt evaluation result release receipt review stage must be contract-only"
require_field prompt_evaluation_result_release_receipt_review_authority 0 "prompt evaluation result release receipt review authority must remain denied"
require_field prompt_evaluation_result_release_receipt_review_allowed 0 "prompt evaluation result release receipt review must remain disallowed"
require_field prompt_evaluation_result_release_receipt_review_recorded 0 "prompt evaluation result release receipt review must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_created 0 "prompt evaluation result release receipt review must not be created"
require_field prompt_evaluation_result_release_receipt_review_performed 0 "prompt evaluation result release receipt review must not be performed"
require_field prompt_evaluation_result_release_receipt_review_metadata_present 1 "prompt evaluation result release receipt review metadata must be present"
require_field prompt_evaluation_result_release_receipt_review_decision blocked_contract_only "prompt evaluation result release receipt review decision must be blocked_contract_only"
require_field prompt_evaluation_result_release_receipt_review_evidence_present 1 "prompt evaluation result release receipt review evidence must be present"
require_field prompt_evaluation_result_release_receipt_review_source_policy operator-reviewed-offline "prompt evaluation result release receipt review source policy must be operator-reviewed-offline"
require_field prompt_evaluation_result_release_receipt_review_plan_recorded 1 "prompt evaluation result release receipt review plan must be recorded"
require_field prompt_evaluation_result_release_receipt_review_result_recorded 0 "prompt evaluation result release receipt review result must remain absent"
require_field prompt_evaluation_result_release_receipt_review_runtime_invoked 0 "prompt evaluation result release receipt review runtime must not be invoked"
require_field requires_prompt_evaluation_result_release_receipt_contract 1 "prompt evaluation result release receipt contract must be required"
require_field requires_prompt_evaluation_result_release_contract 1 "prompt evaluation result release contract must be required"
require_field requires_prompt_evaluation_result_disposition_contract 1 "prompt evaluation result disposition contract must be required"
require_field requires_prompt_evaluation_result_review_contract 1 "prompt evaluation result review contract must be required"
require_field requires_prompt_evaluation_result_contract 1 "prompt evaluation result contract must be required"
require_field requires_future_prompt_evaluation_result_release_receipt_review_disposition_contract 1 "future prompt evaluation result release receipt review disposition contract must be required"
require_field prompt_evaluation_result_release_receipt_review_promotion_allowed 0 "prompt evaluation result release receipt review must not allow promotion"
require_field requires_prompt_evaluation_result_release_receipt_reference 1 "prompt evaluation result release receipt reference must be required"
require_field requires_prompt_evaluation_result_release_reference 1 "prompt evaluation result release reference must be required"
require_field requires_prompt_evaluation_result_disposition_reference 1 "prompt evaluation result disposition reference must be required"
require_field requires_prompt_evaluation_result_review_reference 1 "prompt evaluation result review reference must be required"
require_field requires_prompt_evaluation_result_reference 1 "prompt evaluation result reference must be required"
require_field requires_prompt_evaluation_invocation_reference 1 "prompt evaluation invocation reference must be required"
require_field requires_prompt_evaluation_runtime_handoff_reference 1 "runtime handoff reference must be required"
require_field requires_prompt_evaluation_input_reference 1 "prompt evaluation input reference must be required"
require_field requires_context_window_assembly_reference 1 "context window assembly reference must be required"
require_field requires_prompt_token_sequence_reference 1 "prompt token sequence reference must be required"
require_field requires_prompt_tokenization_reference 1 "prompt tokenization reference must be required"
require_field requires_prompt_evaluation_result_release_receipt_review_schema_policy 1 "prompt evaluation result release receipt review schema policy must be required"
require_field requires_prompt_evaluation_result_release_receipt_review_denial_policy 1 "prompt evaluation result release receipt review denial policy must be required"
require_field requires_prompt_evaluation_result_release_receipt_review_disposition_policy 1 "prompt evaluation result release receipt review disposition policy must be required"
require_field requires_no_prompt_evaluation_result_release_receipt_review 1 "prompt evaluation result release receipt review denial must be required"
require_field requires_no_prompt_evaluation_result_release_receipt_review_disposition 1 "prompt evaluation result release receipt review disposition denial must be required"
require_field requires_no_prompt_evaluation_result_release_receipt 1 "prompt evaluation result release receipt denial must be required"
require_field requires_no_prompt_evaluation_result_release 1 "prompt evaluation result release denial must be required"
require_field requires_no_model_output_read 1 "model output read denial must be required"
require_field requires_no_model_output_recording 1 "model output recording denial must be required"
require_field requires_no_generated_answer 1 "generated answer denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_token_generation 1 "token generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field prompt_evaluation_result_release_receipt_review_record_created 0 "prompt evaluation result release receipt review record must not be created"
require_field prompt_evaluation_result_release_receipt_review_decision_recorded 0 "prompt evaluation result release receipt review decision must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_approval_recorded 0 "prompt evaluation result release receipt review approval must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_rejection_recorded 0 "prompt evaluation result release receipt review rejection must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_findings_recorded 0 "prompt evaluation result release receipt review findings must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_applied 0 "prompt evaluation result release receipt review must not be applied"
require_field prompt_evaluation_result_release_receipt_record_created 0 "prompt evaluation result release receipt record must not be created"
require_field prompt_evaluation_result_release_receipt_signed 0 "prompt evaluation result release receipt must not be signed"
require_field prompt_evaluation_result_release_receipt_published 0 "prompt evaluation result release receipt must not be published"
require_field prompt_evaluation_result_release_receipt_packaged 0 "prompt evaluation result release receipt must not be packaged"
require_field prompt_evaluation_result_release_record_created 0 "prompt evaluation result release record must not be created"
require_field prompt_evaluation_result_release_decision_recorded 0 "prompt evaluation result release decision must not be recorded"
require_field prompt_evaluation_result_release_published 0 "prompt evaluation result release must not be published"
require_field prompt_evaluation_result_release_packaged 0 "prompt evaluation result release must not be packaged"
require_field prompt_evaluation_result_model_output_recorded 0 "model output must not be recorded"
require_field prompt_evaluation_result_output_text_recorded 0 "output text must not be recorded"
require_field runtime_invocation_requested 0 "runtime invocation must not be requested"
require_field runtime_invoked 0 "runtime must not be invoked"
require_field runtime_session_created 0 "runtime session must not be created"
require_field prompt_evaluation_authority 0 "prompt evaluation authority must remain denied"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_authority 0 "token generation authority must remain denied"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_authority 0 "inference authority must remain denied"
require_field inference_performed 0 "inference must not be performed"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field answer_text_generated 0 "answer text must not be generated"
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

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_result_release_receipt_review_contract_status "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_STAGE=$(field_or_unknown prompt_evaluation_result_release_receipt_review_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_FAMILY=$(field_or_unknown prompt_evaluation_result_release_receipt_review_family "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_FORMAT=$(field_or_unknown prompt_evaluation_result_release_receipt_review_format "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_STAGE=$(field_or_unknown prompt_evaluation_result_release_receipt_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_STAGE=$(field_or_unknown prompt_evaluation_result_release_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_DISPOSITION_STAGE=$(field_or_unknown prompt_evaluation_result_disposition_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_REVIEW_STAGE=$(field_or_unknown prompt_evaluation_result_review_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")
PROMPT_EVALUATION_RESULT_STAGE=$(field_or_unknown prompt_evaluation_result_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW DISPOSITION CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only
prompt_evaluation_result_release_receipt_review_disposition_stage=contract-only
prompt_evaluation_result_release_receipt_review_disposition_authority=0
prompt_evaluation_result_release_receipt_review_disposition_allowed=0
prompt_evaluation_result_release_receipt_review_disposition_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_created=0
prompt_evaluation_result_release_receipt_review_disposition_performed=0
prompt_evaluation_result_release_receipt_review_disposition_metadata_present=1
prompt_evaluation_result_release_receipt_review_disposition_family=$DISPOSITION_FAMILY
prompt_evaluation_result_release_receipt_review_disposition_format=$DISPOSITION_FORMAT
prompt_evaluation_result_release_receipt_review_disposition_decision=blocked_contract_only
prompt_evaluation_result_release_receipt_review_disposition_evidence_present=1
prompt_evaluation_result_release_receipt_review_disposition_source_policy=operator-reviewed-offline
prompt_evaluation_result_release_receipt_review_disposition_plan_recorded=1
prompt_evaluation_result_release_receipt_review_disposition_method_planned=offline-prompt-evaluation-result-release-receipt-review-disposition-policy-review
prompt_evaluation_result_release_receipt_review_disposition_result_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_runtime_invoked=0
prompt_evaluation_result_release_receipt_review_disposition_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_approval_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_rejection_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_applied=0
prompt_evaluation_result_release_receipt_review_record_created=0
prompt_evaluation_result_release_receipt_review_decision_recorded=0
prompt_evaluation_result_release_receipt_review_findings_recorded=0
prompt_evaluation_result_release_receipt_review_applied=0
prompt_evaluation_result_release_receipt_record_created=0
prompt_evaluation_result_release_receipt_signed=0
prompt_evaluation_result_release_receipt_published=0
prompt_evaluation_result_release_receipt_packaged=0
prompt_evaluation_result_release_record_created=0
prompt_evaluation_result_release_decision_recorded=0
prompt_evaluation_result_release_published=0
prompt_evaluation_result_release_packaged=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
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
answer_text_generated=0

[inputs]
prompt_evaluation_result_release_receipt_review=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_ABS
prompt_evaluation_result_release_receipt_review_measurement=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_MEASUREMENT
prompt_evaluation_result_release_receipt_review_stage_required=36-prompt-evaluation-result-release-receipt-review-contract
prompt_evaluation_result_release_receipt_review_contract_status=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT_STATUS
prompt_evaluation_result_release_receipt_review_stage=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_STAGE
prompt_evaluation_result_release_receipt_review_family=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_FAMILY
prompt_evaluation_result_release_receipt_review_format=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_FORMAT
prompt_evaluation_result_release_receipt_stage=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_STAGE
prompt_evaluation_result_release_stage=$PROMPT_EVALUATION_RESULT_RELEASE_STAGE
prompt_evaluation_result_disposition_stage=$PROMPT_EVALUATION_RESULT_DISPOSITION_STAGE
prompt_evaluation_result_review_stage=$PROMPT_EVALUATION_RESULT_REVIEW_STAGE
prompt_evaluation_result_stage=$PROMPT_EVALUATION_RESULT_STAGE

[prompt_evaluation_result_release_receipt_review_disposition_contract]
prompt_evaluation_result_release_receipt_review_disposition_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh
installed_prompt_evaluation_result_release_receipt_review_disposition_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition
requires_prompt_evaluation_result_release_receipt_review_contract=1
requires_prompt_evaluation_result_release_receipt_contract=1
requires_prompt_evaluation_result_release_contract=1
requires_prompt_evaluation_result_disposition_contract=1
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1
prompt_evaluation_result_release_receipt_review_disposition_promotion_allowed=0

[prompt_evaluation_result_release_receipt_review_disposition_requirements]
requires_prompt_evaluation_result_release_receipt_review_reference=1
requires_prompt_evaluation_result_release_receipt_reference=1
requires_prompt_evaluation_result_release_reference=1
requires_prompt_evaluation_result_disposition_reference=1
requires_prompt_evaluation_result_review_reference=1
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_result_release_receipt_review_disposition_schema_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_denial_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_policy=1
requires_generated_text_denial_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition_release=1
requires_no_prompt_evaluation_result_release_receipt_review=1
requires_no_prompt_evaluation_result_release_receipt=1
requires_no_prompt_evaluation_result_release=1
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

[prompt_evaluation_result_release_receipt_review_disposition_denial_boundary]
prompt_evaluation_result_release_receipt_review_disposition_authority=0
prompt_evaluation_result_release_receipt_review_disposition_allowed=0
prompt_evaluation_result_release_receipt_review_disposition_open_authority=0
prompt_evaluation_result_release_receipt_review_disposition_read_authority=0
prompt_evaluation_result_release_receipt_review_disposition_write_authority=0
prompt_evaluation_result_release_receipt_review_disposition_execute_authority=0
prompt_evaluation_result_release_receipt_review_disposition_runtime_authority=0
prompt_evaluation_result_release_receipt_review_disposition_prompt_evaluation_authority=0
prompt_evaluation_result_release_receipt_review_disposition_token_generation_authority=0
prompt_evaluation_result_release_receipt_review_disposition_inference_authority=0
prompt_evaluation_result_release_receipt_review_disposition_generation_authority=0
prompt_evaluation_result_release_receipt_review_disposition_recording_authority=0
prompt_evaluation_result_release_receipt_review_disposition_performed=0
prompt_evaluation_result_release_receipt_review_disposition_created=0
prompt_evaluation_result_release_receipt_review_disposition_loaded=0
prompt_evaluation_result_release_receipt_review_disposition_opened=0
prompt_evaluation_result_release_receipt_review_disposition_read=0
prompt_evaluation_result_release_receipt_review_disposition_validated=0
prompt_evaluation_result_release_receipt_review_disposition_serialized=0
prompt_evaluation_result_release_receipt_review_disposition_written=0
prompt_evaluation_result_release_receipt_review_disposition_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_approval_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_rejection_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_applied=0
prompt_evaluation_result_release_receipt_review_record_created=0
prompt_evaluation_result_release_receipt_review_decision_recorded=0
prompt_evaluation_result_release_receipt_review_approval_recorded=0
prompt_evaluation_result_release_receipt_review_rejection_recorded=0
prompt_evaluation_result_release_receipt_review_findings_recorded=0
prompt_evaluation_result_release_receipt_review_applied=0
prompt_evaluation_result_release_receipt_record_created=0
prompt_evaluation_result_release_receipt_signed=0
prompt_evaluation_result_release_receipt_published=0
prompt_evaluation_result_release_receipt_packaged=0
prompt_evaluation_result_release_record_created=0
prompt_evaluation_result_release_decision_recorded=0
prompt_evaluation_result_release_published=0
prompt_evaluation_result_release_packaged=0

[runtime_denial_boundary]
runtime_invocation_requested=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
model_runtime_present=0
model_runtime_invoked=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
qa_dialogue_generated=0
answer_text_generated=0
network_authority=0
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
self_modification_authority=0
training_performed=0
distillation_performed=0

[protective_safety_boundary]
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
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-result-release-receipt-review-disposition-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RECORDED=0\n'
printf 'NADIA_RUNTIME_INVOKED=0\n'
