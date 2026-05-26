#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia prompt evaluation result release receipt review contract stage 36: %s\n' "$1" >&2
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

doc='docs/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT_STAGE_36.md'
status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT_STAGE_36_STATUS.md'
status_index='docs/status/README.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
review_script='scripts/nadia-prompt-evaluation-result-release-receipt-review-contract.sh'
receipt_script='scripts/nadia-prompt-evaluation-result-release-receipt-contract.sh'
guard='scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.yml'

require_file "$doc"
require_file "$status"
require_file "$status_index"
require_file "$foundation"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$review_script"
require_file "$receipt_script"
require_file "$guard"
require_file "$workflow"

require_contains 'Status: Stage-36 implementation contract' "$doc"
require_contains 'nadia_stage_36_prompt_evaluation_result_release_receipt_review_contract_present=1' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-contract.sh' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_status=contract_only' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_authority=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_decision_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_findings_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_signed=0' "$doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$doc"
require_contains 'runtime_invoked=0' "$doc"
require_contains 'prompt_evaluated=0' "$doc"
require_contains 'token_generation_performed=0' "$doc"
require_contains 'inference_performed=0' "$doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh' "$doc"

require_contains 'Status: implementation status record' "$status"
require_contains 'nadia_stage_36_prompt_evaluation_result_release_receipt_review_contract_present=1' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_status=contract_only' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_allowed=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_created=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_decision_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_findings_recorded=0' "$status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$status"
require_contains 'runtime_invoked=0' "$status"
require_contains 'prompt_evaluated=0' "$status"
require_contains 'token_generation_performed=0' "$status"
require_contains 'inference_performed=0' "$status"
require_contains 'sexual_request_refusal=always' "$status"
require_contains 'manipulation_resistance=required' "$status"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT_STAGE_36_STATUS.md' "$status_index"
require_contains 'Stage-36: Prompt Evaluation Result Release Receipt Review Contract' "$foundation"
require_contains 'latticra-nadia prompt-evaluation-result-release-receipt-review' "$installer_readme"
require_contains 'prompt-evaluation result release receipt review recording' "$installer_readme"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, Stage-38, Stage-39, and Stage-40 console surfaces are metadata-only' "$ui_model"
require_contains 'Stage-36 prompt-evaluation result release receipt review contract' "$components_manifest"
require_contains 'prompt-evaluation result release receipt review recording' "$components_manifest"
require_contains 'prompt-evaluation-result-release-receipt-review metadata records future prompt evaluation result release receipt review disposition requirements' "$components_manifest"
require_contains 'command=prompt-evaluation-result-release-receipt-review stage=36' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_stage=36-prompt-evaluation-result-release-receipt-review-contract' "$apply_script"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_findings_recorded=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_stage=36-prompt-evaluation-result-release-receipt-review-contract' "$panel_config"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review' "$panel_config"
require_contains 'nadia prompt-evaluation-result-release-receipt-review' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result_release_receipt_review=stage-36-prompt-evaluation-result-release-receipt-review-contract' "$panel_ui"

require_contains 'NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW CONTRACT' "$review_script"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_status=contract_only' "$review_script"
require_contains 'requires_prompt_evaluation_result_release_receipt_contract=1' "$review_script"
require_contains 'requires_future_prompt_evaluation_result_release_receipt_review_disposition_contract=1' "$review_script"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$review_script"
require_contains 'prompt_evaluation_result_release_receipt_review_decision_recorded=0' "$review_script"
require_contains 'prompt_evaluation_result_release_receipt_review_findings_recorded=0' "$review_script"
require_contains 'prompt_evaluation_result_release_receipt_signed=0' "$review_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$review_script"
require_contains 'runtime_invoked=0' "$review_script"
require_contains 'prompt_evaluated=0' "$review_script"
require_contains 'token_generation_performed=0' "$review_script"
require_contains 'inference_performed=0' "$review_script"
require_contains 'network_authority=0' "$review_script"
require_contains 'tool_execution_authority=0' "$review_script"
require_contains 'source_mutation_authority=0' "$review_script"
require_contains 'outside Nadia prompt-evaluation-result-release-receipt-review boundary' "$review_script"

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh' "$workflow"

tmp_root=${TMPDIR:-/tmp}
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage36-release-receipt-review-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

release="$tmpdir/prompt-evaluation-result-release-stage34-fixture.txt"
receipt_out="$tmpdir/receipt"
review_out="$tmpdir/review"
mkdir -p "$receipt_out" "$review_out"

cat > "$release" <<'EOF_RELEASE'
NADIA PROMPT EVALUATION RESULT RELEASE CONTRACT
stage=34-prompt-evaluation-result-release-contract
prompt_evaluation_result_release_contract_status=contract_only
prompt_evaluation_result_release_stage=contract-only
prompt_evaluation_result_release_authority=0
prompt_evaluation_result_release_allowed=0
prompt_evaluation_result_release_recorded=0
prompt_evaluation_result_release_created=0
prompt_evaluation_result_release_performed=0
prompt_evaluation_result_release_metadata_present=1
prompt_evaluation_result_release_family=operator-reviewed-prompt-evaluation-result-release
prompt_evaluation_result_release_format=contract-only-offline-evaluation-result-release
prompt_evaluation_result_release_decision=blocked_contract_only
prompt_evaluation_result_release_evidence_present=1
prompt_evaluation_result_release_source_policy=operator-reviewed-offline
prompt_evaluation_result_release_plan_recorded=1
prompt_evaluation_result_release_method_planned=offline-prompt-evaluation-result-release-policy-review
prompt_evaluation_result_release_result_recorded=0
prompt_evaluation_result_release_runtime_invoked=0
requires_prompt_evaluation_result_disposition_contract=1
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_receipt_contract=1
prompt_evaluation_result_release_promotion_allowed=0
requires_prompt_evaluation_result_disposition_reference=1
requires_prompt_evaluation_result_review_reference=1
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_invocation_reference=1
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_result_release_schema_policy=1
requires_prompt_evaluation_result_release_denial_policy=1
requires_prompt_evaluation_result_release_receipt_policy=1
requires_no_prompt_evaluation_result_release=1
requires_no_prompt_evaluation_result_release_receipt=1
requires_no_prompt_evaluation_result_disposition=1
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
prompt_evaluation_result_release_record_created=0
prompt_evaluation_result_release_decision_recorded=0
prompt_evaluation_result_release_published=0
prompt_evaluation_result_release_packaged=0
prompt_evaluation_result_release_receipt_created=0
prompt_evaluation_result_release_receipt_recorded=0
prompt_evaluation_result_disposition_record_created=0
prompt_evaluation_result_disposition_decision_recorded=0
prompt_evaluation_result_disposition_applied=0
prompt_evaluation_result_review_record_created=0
prompt_evaluation_result_review_decision_recorded=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_record_created=0
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
prompt_evaluation_result_disposition_stage=contract-only
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_stage=contract-only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
EOF_RELEASE

NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_TIMESTAMP=20260526T010000Z \
  sh "$receipt_script" \
    --prompt-evaluation-result-release "$release" \
    --output "$receipt_out" >/dev/null

receipt="$receipt_out/latest-prompt-evaluation-result-release-receipt-contract.txt"
require_file "$receipt"

output=$(
  NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_TIMESTAMP=20260526T020000Z \
    sh "$review_script" \
      --prompt-evaluation-result-release-receipt "$receipt" \
      --output "$review_out"
)

require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_CONTRACT='
require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_RECORDED=0'
require_output_contains "$output" 'NADIA_RUNTIME_INVOKED=0'

report="$review_out/nadia-prompt-evaluation-result-release-receipt-review-contract-20260526T020000Z.txt"
latest="$review_out/latest-prompt-evaluation-result-release-receipt-review-contract.txt"
require_file "$report"
require_file "$latest"
require_contains 'stage=36-prompt-evaluation-result-release-receipt-review-contract' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_findings_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_signed=0' "$report"
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

printf 'nadia_prompt_evaluation_result_release_receipt_review_contract_stage_36: ok\n'
