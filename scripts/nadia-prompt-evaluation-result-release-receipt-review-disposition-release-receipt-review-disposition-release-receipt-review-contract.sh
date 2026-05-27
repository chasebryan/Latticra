#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract.sh [options]

Options:
  --prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt <file>  Stage-43 Nadia prompt-evaluation result release receipt review disposition release receipt review disposition release receipt contract
  --request-class <label>                                                               Operator request classification label
  --review-family <label>                                                               Planned prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review family label
  --review-format <label>                                                               Planned prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review format label
  --output <dir>                                                                        Output directory for prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review contracts

Creates Nadia Stage-44 prompt-evaluation result release receipt review
disposition release receipt review disposition release receipt review contract
metadata only. It verifies the Stage-43 release receipt contract and records
planned release receipt review requirements before any receipt-review record,
review decision, review findings, disposition record, receipt signing,
publication, runtime invocation, prompt evaluation, dialogue generation,
token generation, or inference boundary. It does not review receipts, decide
reviews, sign receipts, publish receipts, package receipts, read or record
model output, invoke a runtime, evaluate prompts, generate dialogue, generate
tokens, run inference, execute tools, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation result release receipt review disposition release receipt review disposition release receipt review contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT=""
REQUEST_CLASS="awareness-education"
REVIEW_FAMILY="operator-reviewed-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"
REVIEW_FORMAT="contract-only-offline-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt" 64
      PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT="$2"
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

if [ -z "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT" ] && [ -f "reports/nadia/prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt/latest-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract.txt" ]; then
  PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT="reports/nadia/prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt/latest-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT" ] || fail "prompt evaluation result release receipt review disposition release receipt review disposition release receipt contract is required" 64
[ -f "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT" ] || fail "prompt evaluation result release receipt review disposition release receipt review disposition release receipt contract not found: $PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "review family" "$REVIEW_FAMILY"
reject_boundary_label "review format" "$REVIEW_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract-$TS.txt"

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT")")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")

require_field stage 43-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract "release receipt prerequisite stage must be Stage-43"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_status contract_only "release receipt prerequisite must remain contract-only"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_stage contract-only "release receipt prerequisite stage must remain contract-only"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_authority 0 "release receipt authority must remain denied"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_allowed 0 "release receipt must remain disallowed"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_recorded 0 "release receipt must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_created 0 "release receipt must not be created"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_performed 0 "release receipt must not be performed"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_metadata_present 1 "release receipt metadata must be present"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_decision blocked_contract_only "release receipt decision must remain blocked"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_evidence_present 1 "release receipt evidence must be present"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_plan_recorded 1 "release receipt plan must be recorded"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_result_recorded 0 "release receipt result must remain absent"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_runtime_invoked 0 "release receipt runtime must not be invoked"
require_field requires_prompt_evaluation_result_release_receipt_review_disposition_release_contract 1 "release-disposition contract must be required"
require_field requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract 1 "future release receipt review contract must be required"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created 0 "release receipt record must not be created"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_decision_recorded 0 "release receipt decision must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_findings_recorded 0 "release receipt findings must not be recorded"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_emitted 0 "release receipt must not be emitted"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed 0 "release receipt must not be signed"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_published 0 "release receipt must not be published"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_packaged 0 "release receipt must not be packaged"
require_field prompt_evaluation_result_release_receipt_review_disposition_release_record_created 0 "release-disposition record must not be created"
require_field prompt_evaluation_result_release_receipt_review_disposition_record_created 0 "review-disposition record must not be created"
require_field prompt_evaluation_result_release_receipt_review_record_created 0 "release receipt review record must not be created"
require_field prompt_evaluation_result_release_receipt_record_created 0 "release receipt record must not be created"
require_field prompt_evaluation_result_model_output_recorded 0 "model output must not be recorded"
require_field prompt_evaluation_result_output_text_recorded 0 "output text must not be recorded"
require_field runtime_invoked 0 "runtime must not be invoked"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_performed 0 "inference must not be performed"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field answer_text_generated 0 "answer text must not be generated"
require_field sexual_user_request_authority 0 "sexual user request authority must remain denied"
require_field sexual_content_generation 0 "sexual content generation must remain forbidden"
require_field sexualized_dialogue_generation 0 "sexualized dialogue generation must remain forbidden"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"
require_field network_authority 0 "network authority must remain denied"
require_field tool_execution_authority 0 "tool execution authority must remain denied"
require_field source_mutation_authority 0 "source mutation authority must remain denied"
require_field training_performed 0 "training must not be performed"
require_field distillation_performed 0 "distillation must not be performed"

PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_status "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_STAGE=$(field_or_unknown prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_stage "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_FAMILY=$(field_or_unknown prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_family "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")
PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_FORMAT=$(field_or_unknown prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_format "$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW DISPOSITION RELEASE RECEIPT REVIEW DISPOSITION RELEASE RECEIPT REVIEW CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=44-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_status=contract_only
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_stage=contract-only
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_authority=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_allowed=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_created=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_performed=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_metadata_present=1
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_family=$REVIEW_FAMILY
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_format=$REVIEW_FORMAT
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_decision=blocked_contract_only
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_evidence_present=1
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_source_policy=operator-reviewed-offline
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_plan_recorded=1
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_method_planned=offline-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-policy-review
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_result_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_runtime_invoked=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_approval_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_rejection_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_findings_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_applied=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_published=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_packaged=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_findings_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_emitted=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_published=0
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_packaged=0
prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_release_published=0
prompt_evaluation_result_release_receipt_review_disposition_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0
prompt_evaluation_result_release_receipt_review_record_created=0
prompt_evaluation_result_release_receipt_review_decision_recorded=0
prompt_evaluation_result_release_receipt_review_findings_recorded=0
prompt_evaluation_result_release_receipt_record_created=0
prompt_evaluation_result_release_receipt_signed=0
prompt_evaluation_result_release_receipt_published=0
prompt_evaluation_result_release_record_created=0
prompt_evaluation_result_release_decision_recorded=0
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
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_ABS
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_measurement=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_MEASUREMENT
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_stage_required=43-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_status=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_CONTRACT_STATUS
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_stage=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_STAGE
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_family=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_FAMILY
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_format=$PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_FORMAT

[prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract]
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract.sh
installed_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1
requires_prompt_evaluation_result_release_receipt_review_disposition_contract=1
requires_prompt_evaluation_result_release_receipt_review_contract=1
requires_prompt_evaluation_result_release_receipt_contract=1
requires_prompt_evaluation_result_release_contract=1
requires_prompt_evaluation_result_disposition_contract=1
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract=1
prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_promotion_allowed=0

[prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_requirements]
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_reference=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_reference=1
requires_prompt_evaluation_result_release_receipt_review_disposition_reference=1
requires_prompt_evaluation_result_release_receipt_review_reference=1
requires_prompt_evaluation_result_release_receipt_reference=1
requires_prompt_evaluation_result_release_reference=1
requires_prompt_evaluation_result_disposition_reference=1
requires_prompt_evaluation_result_review_reference=1
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_schema_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_denial_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_policy=1
requires_generated_text_denial_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition_release=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition=1
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

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_RECORDED=0\n'
printf 'NADIA_RUNTIME_INVOKED=0\n'
