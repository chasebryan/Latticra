#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia prompt evaluation result release contract stage 34: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  output="$1"
  pattern="$2"
  printf '%s\n' "$output" | grep -Fq -- "$pattern" ||
    fail "missing required output pattern: $pattern"
}

doc='docs/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_CONTRACT_STAGE_34.md'
status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_CONTRACT_STAGE_34_STATUS.md'
status_index='docs/status/README.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
release_script='scripts/nadia-prompt-evaluation-result-release-contract.sh'
guard='scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-release-contract-stage-34.yml'

require_file "$doc"
require_file "$status"
require_file "$status_index"
require_file "$foundation"
require_file "$release_script"
require_file "$guard"
require_file "$workflow"

require_contains 'Status: Stage-34 implementation contract' "$doc"
require_contains 'nadia_stage_34_prompt_evaluation_result_release_contract_present=1' "$doc"
require_contains 'prompt_evaluation_result_release_contract_command=scripts/nadia-prompt-evaluation-result-release-contract.sh' "$doc"
require_contains 'prompt_evaluation_result_release_contract_status=contract_only' "$doc"
require_contains 'prompt_evaluation_result_release_authority=0' "$doc"
require_contains 'prompt_evaluation_result_release_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_decision_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_published=0' "$doc"
require_contains 'prompt_evaluation_result_release_packaged=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_created=0' "$doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$doc"
require_contains 'runtime_invoked=0' "$doc"
require_contains 'prompt_evaluated=0' "$doc"
require_contains 'token_generation_performed=0' "$doc"
require_contains 'inference_performed=0' "$doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh' "$doc"

require_contains 'Status: implementation status record' "$status"
require_contains 'nadia_stage_34_prompt_evaluation_result_release_contract_present=1' "$status"
require_contains 'prompt_evaluation_result_release_contract_status=contract_only' "$status"
require_contains 'prompt_evaluation_result_release_allowed=0' "$status"
require_contains 'prompt_evaluation_result_release_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_record_created=0' "$status"
require_contains 'prompt_evaluation_result_release_decision_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_published=0' "$status"
require_contains 'prompt_evaluation_result_release_packaged=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_created=0' "$status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$status"
require_contains 'runtime_invoked=0' "$status"
require_contains 'prompt_evaluated=0' "$status"
require_contains 'token_generation_performed=0' "$status"
require_contains 'inference_performed=0' "$status"
require_contains 'sexual_request_refusal=always' "$status"
require_contains 'manipulation_resistance=required' "$status"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_CONTRACT_STAGE_34_STATUS.md' "$status_index"
require_contains 'Stage-34: Prompt Evaluation Result Release Contract' "$foundation"

require_contains 'NADIA PROMPT EVALUATION RESULT RELEASE CONTRACT' "$release_script"
require_contains 'prompt_evaluation_result_release_contract_status=contract_only' "$release_script"
require_contains 'requires_prompt_evaluation_result_disposition_contract=1' "$release_script"
require_contains 'requires_future_prompt_evaluation_result_release_receipt_contract=1' "$release_script"
require_contains 'prompt_evaluation_result_release_record_created=0' "$release_script"
require_contains 'prompt_evaluation_result_release_decision_recorded=0' "$release_script"
require_contains 'prompt_evaluation_result_release_published=0' "$release_script"
require_contains 'prompt_evaluation_result_release_packaged=0' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_created=0' "$release_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$release_script"
require_contains 'runtime_invoked=0' "$release_script"
require_contains 'prompt_evaluated=0' "$release_script"
require_contains 'token_generation_performed=0' "$release_script"
require_contains 'inference_performed=0' "$release_script"
require_contains 'network_authority=0' "$release_script"
require_contains 'tool_execution_authority=0' "$release_script"
require_contains 'source_mutation_authority=0' "$release_script"
require_contains 'outside Nadia prompt-evaluation-result-release boundary' "$release_script"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh' "$workflow"

tmp_root="${TMPDIR:-/tmp}"
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage34-result-release-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

disposition="$tmpdir/prompt-evaluation-result-disposition-stage33-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$disposition" <<'EOF_DISPOSITION'
NADIA PROMPT EVALUATION RESULT DISPOSITION CONTRACT
stage=33-prompt-evaluation-result-disposition-contract
prompt_evaluation_result_disposition_contract_status=contract_only
prompt_evaluation_result_disposition_stage=contract-only
prompt_evaluation_result_disposition_authority=0
prompt_evaluation_result_disposition_allowed=0
prompt_evaluation_result_disposition_recorded=0
prompt_evaluation_result_disposition_created=0
prompt_evaluation_result_disposition_performed=0
prompt_evaluation_result_disposition_metadata_present=1
prompt_evaluation_result_disposition_family=operator-reviewed-prompt-evaluation-result-disposition
prompt_evaluation_result_disposition_format=contract-only-offline-evaluation-result-disposition
prompt_evaluation_result_disposition_decision=blocked_contract_only
prompt_evaluation_result_disposition_evidence_present=1
prompt_evaluation_result_disposition_source_policy=operator-reviewed-offline
prompt_evaluation_result_disposition_plan_recorded=1
prompt_evaluation_result_disposition_method_planned=offline-prompt-evaluation-result-disposition-policy-review
prompt_evaluation_result_disposition_result_recorded=0
prompt_evaluation_result_disposition_runtime_invoked=0
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_contract=1
prompt_evaluation_result_disposition_promotion_allowed=0
requires_prompt_evaluation_result_review_reference=1
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_invocation_reference=1
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_result_disposition_schema_policy=1
requires_prompt_evaluation_result_disposition_denial_policy=1
requires_prompt_evaluation_result_release_policy=1
requires_generated_text_denial_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_result_disposition=1
requires_no_prompt_evaluation_result_release=1
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
prompt_evaluation_result_disposition_record_created=0
prompt_evaluation_result_disposition_decision_recorded=0
prompt_evaluation_result_disposition_applied=0
prompt_evaluation_result_release_record_created=0
prompt_evaluation_result_release_decision_recorded=0
prompt_evaluation_result_review_record_created=0
prompt_evaluation_result_review_decision_recorded=0
prompt_evaluation_result_review_findings_recorded=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_record_created=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
prompt_evaluation_result_score_recorded=0
prompt_evaluation_result_token_logprobs_recorded=0
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
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
live_web_lookup_authority=0
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
network_authority=0
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
self_modification_authority=0
training_performed=0
distillation_performed=0
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_stage=contract-only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
EOF_DISPOSITION

output=$(
  NADIA_PROMPT_EVALUATION_RESULT_RELEASE_TIMESTAMP=20260525T000000Z \
    sh "$release_script" \
      --prompt-evaluation-result-disposition "$disposition" \
      --output "$out"
)

require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_CONTRACT='
require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECORDED=0'
require_output_contains "$output" 'NADIA_RUNTIME_INVOKED=0'

report="$out/nadia-prompt-evaluation-result-release-contract-20260525T000000Z.txt"
latest="$out/latest-prompt-evaluation-result-release-contract.txt"
require_file "$report"
require_file "$latest"
require_contains 'stage=34-prompt-evaluation-result-release-contract' "$report"
require_contains 'prompt_evaluation_result_release_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_release_record_created=0' "$report"
require_contains 'prompt_evaluation_result_release_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_published=0' "$report"
require_contains 'prompt_evaluation_result_release_packaged=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_created=0' "$report"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'network_authority=0' "$report"
require_contains 'tool_execution_authority=0' "$report"
require_contains 'source_mutation_authority=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

if sh "$release_script" \
  --prompt-evaluation-result-disposition "$disposition" \
  --request-class sexual \
  --output "$out/bad" >/dev/null 2>&1; then
  fail "sexual request class must be rejected"
fi

printf 'nadia_prompt_evaluation_result_release_contract_stage_34: ok\n'
