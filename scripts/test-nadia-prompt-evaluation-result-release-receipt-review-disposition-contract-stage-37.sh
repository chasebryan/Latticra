#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia prompt evaluation result release receipt review disposition contract stage 37: %s\n' "$1" >&2
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

doc='docs/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT_STAGE_37.md'
status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT_STAGE_37_STATUS.md'
status_index='docs/status/README.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
foundation_index='docs/FOUNDATION_INDEX.md'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
disposition_script='scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh'
guard='scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.yml'

for file in "$doc" "$status" "$status_index" "$foundation" "$foundation_index" "$installer_readme" "$ui_model" "$components_manifest" "$apply_script" "$panel_config" "$panel_ui" "$disposition_script" "$guard" "$workflow" Makefile
do
  require_file "$file"
done

require_contains 'Status: Stage-37 implementation contract' "$doc"
require_contains 'nadia_stage_37_prompt_evaluation_result_release_receipt_review_disposition_contract_present=1' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_signed=0' "$doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$doc"
require_contains 'runtime_invoked=0' "$doc"
require_contains 'prompt_evaluated=0' "$doc"
require_contains 'token_generation_performed=0' "$doc"
require_contains 'inference_performed=0' "$doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh' "$doc"

require_contains 'Status: implementation status record' "$status"
require_contains 'nadia_stage_37_prompt_evaluation_result_release_receipt_review_disposition_contract_present=1' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_allowed=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_created=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0' "$status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$status"
require_contains 'runtime_invoked=0' "$status"
require_contains 'prompt_evaluated=0' "$status"
require_contains 'token_generation_performed=0' "$status"
require_contains 'inference_performed=0' "$status"
require_contains 'sexual_request_refusal=always' "$status"
require_contains 'manipulation_resistance=required' "$status"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT_STAGE_37_STATUS.md' "$status_index"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT_STAGE_37.md' "$foundation_index"
require_contains 'Nadia prompt evaluation result release receipt review disposition contract Stage-37 + guardrails' "$foundation_index"
require_contains 'Stage-37: Prompt Evaluation Result Release Receipt Review Disposition Contract' "$foundation"
require_contains 'latticra-nadia prompt-evaluation-result-release-receipt-review-disposition' "$installer_readme"
require_contains 'prompt-evaluation result release receipt review disposition recording' "$installer_readme"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, and Stage-38 console surfaces are metadata-only' "$ui_model"
require_contains 'Stage-37 prompt-evaluation result release receipt review disposition contract' "$components_manifest"
require_contains 'prompt-evaluation result release receipt review disposition recording' "$components_manifest"
require_contains 'prompt-evaluation-result-release-receipt-review-disposition metadata records future prompt evaluation result release receipt review disposition release requirements' "$components_manifest"
require_contains 'command=prompt-evaluation-result-release-receipt-review-disposition stage=37' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$apply_script"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_disposition_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$panel_config"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_disposition_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition' "$panel_config"
require_contains 'nadia prompt-evaluation-result-release-receipt-review-disposition' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result_release_receipt_review_disposition=stage-37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$panel_ui"
require_contains 'sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh' Makefile
require_contains 'sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh' Makefile

require_contains 'NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW DISPOSITION CONTRACT' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only' "$disposition_script"
require_contains 'requires_prompt_evaluation_result_release_receipt_review_contract=1' "$disposition_script"
require_contains 'requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$disposition_script"
require_contains 'prompt_evaluation_result_release_receipt_signed=0' "$disposition_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$disposition_script"
require_contains 'runtime_invoked=0' "$disposition_script"
require_contains 'prompt_evaluated=0' "$disposition_script"
require_contains 'token_generation_performed=0' "$disposition_script"
require_contains 'inference_performed=0' "$disposition_script"
require_contains 'network_authority=0' "$disposition_script"
require_contains 'tool_execution_authority=0' "$disposition_script"
require_contains 'source_mutation_authority=0' "$disposition_script"
require_contains 'outside Nadia prompt-evaluation-result-release-receipt-review-disposition boundary' "$disposition_script"

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh' "$workflow"

tmp_root=${TMPDIR:-/tmp}
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage37-release-receipt-review-disposition-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

review="$tmpdir/prompt-evaluation-result-release-receipt-review-stage36-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$review" <<'EOF_REVIEW'
NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW CONTRACT
stage=36-prompt-evaluation-result-release-receipt-review-contract
prompt_evaluation_result_release_receipt_review_contract_status=contract_only
prompt_evaluation_result_release_receipt_review_stage=contract-only
prompt_evaluation_result_release_receipt_review_authority=0
prompt_evaluation_result_release_receipt_review_allowed=0
prompt_evaluation_result_release_receipt_review_recorded=0
prompt_evaluation_result_release_receipt_review_created=0
prompt_evaluation_result_release_receipt_review_performed=0
prompt_evaluation_result_release_receipt_review_metadata_present=1
prompt_evaluation_result_release_receipt_review_family=operator-reviewed-prompt-evaluation-result-release-receipt-review
prompt_evaluation_result_release_receipt_review_format=contract-only-offline-evaluation-result-release-receipt-review
prompt_evaluation_result_release_receipt_review_decision=blocked_contract_only
prompt_evaluation_result_release_receipt_review_evidence_present=1
prompt_evaluation_result_release_receipt_review_source_policy=operator-reviewed-offline
prompt_evaluation_result_release_receipt_review_plan_recorded=1
prompt_evaluation_result_release_receipt_review_result_recorded=0
prompt_evaluation_result_release_receipt_review_runtime_invoked=0
requires_prompt_evaluation_result_release_receipt_contract=1
requires_prompt_evaluation_result_release_contract=1
requires_prompt_evaluation_result_disposition_contract=1
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_receipt_review_disposition_contract=1
prompt_evaluation_result_release_receipt_review_promotion_allowed=0
requires_prompt_evaluation_result_release_receipt_reference=1
requires_prompt_evaluation_result_release_reference=1
requires_prompt_evaluation_result_disposition_reference=1
requires_prompt_evaluation_result_review_reference=1
requires_prompt_evaluation_result_reference=1
requires_prompt_evaluation_invocation_reference=1
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_result_release_receipt_review_schema_policy=1
requires_prompt_evaluation_result_release_receipt_review_denial_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_policy=1
requires_no_prompt_evaluation_result_release_receipt_review=1
requires_no_prompt_evaluation_result_release_receipt_review_disposition=1
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
prompt_evaluation_result_release_receipt_stage=contract-only
prompt_evaluation_result_release_stage=contract-only
prompt_evaluation_result_disposition_stage=contract-only
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_stage=contract-only
EOF_REVIEW

output=$(
  NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_TIMESTAMP=20260526T030000Z \
    sh "$disposition_script" \
      --prompt-evaluation-result-release-receipt-review "$review" \
      --output "$out"
)

require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_CONTRACT='
require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RECORDED=0'
require_output_contains "$output" 'NADIA_RUNTIME_INVOKED=0'

report="$out/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-20260526T030000Z.txt"
latest="$out/latest-prompt-evaluation-result-release-receipt-review-disposition-contract.txt"
require_file "$report"
require_file "$latest"
require_contains 'stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_record_created=0' "$report"
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

printf 'nadia_prompt_evaluation_result_release_receipt_review_disposition_contract_stage_37: ok\n'
