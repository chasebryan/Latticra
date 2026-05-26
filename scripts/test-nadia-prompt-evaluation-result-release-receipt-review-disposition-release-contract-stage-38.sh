#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia prompt evaluation result release receipt review disposition release contract stage 38: %s\n' "$1" >&2
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

doc='docs/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_CONTRACT_STAGE_38.md'
status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_CONTRACT_STAGE_38_STATUS.md'
status_index='docs/status/README.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
foundation_index='docs/FOUNDATION_INDEX.md'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
release_script='scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract.sh'
guard='scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.yml'

for file in "$doc" "$status" "$status_index" "$foundation" "$foundation_index" "$installer_readme" "$ui_model" "$components_manifest" "$apply_script" "$panel_config" "$panel_ui" "$release_script" "$guard" "$workflow" Makefile
do
  require_file "$file"
done

require_contains 'Status: Stage-38 implementation contract' "$doc"
require_contains 'nadia_stage_38_prompt_evaluation_result_release_receipt_review_disposition_release_contract_present=1' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract.sh' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_status=contract_only' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_decision_recorded=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_published=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_receipt_created=0' "$doc"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$doc"
require_contains 'runtime_invoked=0' "$doc"
require_contains 'prompt_evaluated=0' "$doc"
require_contains 'token_generation_performed=0' "$doc"
require_contains 'inference_performed=0' "$doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh' "$doc"

require_contains 'Status: implementation status record' "$status"
require_contains 'nadia_stage_38_prompt_evaluation_result_release_receipt_review_disposition_release_contract_present=1' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_status=contract_only' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_allowed=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_created=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_decision_recorded=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_published=0' "$status"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_receipt_created=0' "$status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$status"
require_contains 'runtime_invoked=0' "$status"
require_contains 'prompt_evaluated=0' "$status"
require_contains 'token_generation_performed=0' "$status"
require_contains 'inference_performed=0' "$status"
require_contains 'sexual_request_refusal=always' "$status"
require_contains 'manipulation_resistance=required' "$status"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_CONTRACT_STAGE_38_STATUS.md' "$status_index"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_CONTRACT_STAGE_38.md' "$foundation_index"
require_contains 'Nadia prompt evaluation result release receipt review disposition release contract Stage-38 + guardrails' "$foundation_index"
require_contains 'Stage-38: Prompt Evaluation Result Release Receipt Review Disposition Release Contract' "$foundation"
require_contains 'latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release' "$installer_readme"
require_contains 'prompt-evaluation result release receipt review disposition release recording' "$installer_readme"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, Stage-38, Stage-39, and Stage-40 console surfaces are metadata-only' "$ui_model"
require_contains 'Stage-38 prompt-evaluation result release receipt review disposition release contract' "$components_manifest"
require_contains 'prompt-evaluation result release receipt review disposition release recording' "$components_manifest"
require_contains 'prompt-evaluation-result-release-receipt-review-disposition-release metadata records future prompt evaluation result release receipt review disposition release receipt requirements' "$components_manifest"
require_contains 'command=prompt-evaluation-result-release-receipt-review-disposition-release stage=38' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$apply_script"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_disposition_release_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_published=0' "$apply_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$panel_config"
require_contains 'installed_prompt_evaluation_result_release_receipt_review_disposition_release_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release' "$panel_config"
require_contains 'nadia prompt-evaluation-result-release-receipt-review-disposition-release' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result_release_receipt_review_disposition_release=stage-38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$panel_ui"
require_contains 'sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh' Makefile
require_contains 'sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract.sh' Makefile

require_contains 'NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW DISPOSITION RELEASE CONTRACT' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_status=contract_only' "$release_script"
require_contains 'requires_prompt_evaluation_result_release_receipt_review_disposition_contract=1' "$release_script"
require_contains 'requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract=1' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_decision_recorded=0' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_published=0' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_receipt_created=0' "$release_script"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_record_created=0' "$release_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$release_script"
require_contains 'runtime_invoked=0' "$release_script"
require_contains 'prompt_evaluated=0' "$release_script"
require_contains 'token_generation_performed=0' "$release_script"
require_contains 'inference_performed=0' "$release_script"
require_contains 'network_authority=0' "$release_script"
require_contains 'tool_execution_authority=0' "$release_script"
require_contains 'source_mutation_authority=0' "$release_script"
require_contains 'outside Nadia prompt-evaluation-result-release-receipt-review-disposition-release boundary' "$release_script"

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh' "$workflow"

tmp_root=${TMPDIR:-/tmp}
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage38-review-disposition-release-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

disposition="$tmpdir/prompt-evaluation-result-release-receipt-review-disposition-stage37-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$disposition" <<'EOF_DISPOSITION'
NADIA PROMPT EVALUATION RESULT RELEASE RECEIPT REVIEW DISPOSITION CONTRACT
stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract
prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only
prompt_evaluation_result_release_receipt_review_disposition_stage=contract-only
prompt_evaluation_result_release_receipt_review_disposition_authority=0
prompt_evaluation_result_release_receipt_review_disposition_allowed=0
prompt_evaluation_result_release_receipt_review_disposition_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_created=0
prompt_evaluation_result_release_receipt_review_disposition_performed=0
prompt_evaluation_result_release_receipt_review_disposition_metadata_present=1
prompt_evaluation_result_release_receipt_review_disposition_family=operator-reviewed-prompt-evaluation-result-release-receipt-review-disposition
prompt_evaluation_result_release_receipt_review_disposition_format=contract-only-offline-evaluation-result-release-receipt-review-disposition
prompt_evaluation_result_release_receipt_review_disposition_decision=blocked_contract_only
prompt_evaluation_result_release_receipt_review_disposition_evidence_present=1
prompt_evaluation_result_release_receipt_review_disposition_source_policy=operator-reviewed-offline
prompt_evaluation_result_release_receipt_review_disposition_plan_recorded=1
prompt_evaluation_result_release_receipt_review_disposition_result_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_runtime_invoked=0
requires_prompt_evaluation_result_release_receipt_review_contract=1
requires_prompt_evaluation_result_release_receipt_contract=1
requires_prompt_evaluation_result_release_contract=1
requires_prompt_evaluation_result_disposition_contract=1
requires_prompt_evaluation_result_review_contract=1
requires_prompt_evaluation_result_contract=1
requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1
prompt_evaluation_result_release_receipt_review_disposition_promotion_allowed=0
requires_prompt_evaluation_result_release_receipt_review_disposition_schema_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_denial_policy=1
requires_prompt_evaluation_result_release_receipt_review_disposition_release_policy=1
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
prompt_evaluation_result_release_receipt_review_disposition_record_created=0
prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_approval_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_rejection_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0
prompt_evaluation_result_release_receipt_review_disposition_applied=0
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
runtime_invoked=0
prompt_evaluated=0
token_generation_performed=0
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
prompt_evaluation_result_release_receipt_review_stage=contract-only
prompt_evaluation_result_release_receipt_stage=contract-only
prompt_evaluation_result_release_stage=contract-only
prompt_evaluation_result_disposition_stage=contract-only
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_stage=contract-only
EOF_DISPOSITION

output=$(
  NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_TIMESTAMP=20260526T040000Z \
    sh "$release_script" \
      --prompt-evaluation-result-release-receipt-review-disposition "$disposition" \
      --output "$out"
)

require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_CONTRACT='
require_output_contains "$output" 'NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECORDED=0'
require_output_contains "$output" 'NADIA_RUNTIME_INVOKED=0'

report="$out/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-20260526T040000Z.txt"
latest="$out/latest-prompt-evaluation-result-release-receipt-review-disposition-release-contract.txt"
require_file "$report"
require_file "$latest"
require_contains 'stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_published=0' "$report"
require_contains 'prompt_evaluation_result_release_receipt_review_disposition_release_receipt_created=0' "$report"
require_contains 'requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract=1' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

printf 'nadia_prompt_evaluation_result_release_receipt_review_disposition_release_contract_stage_38: ok\n'
