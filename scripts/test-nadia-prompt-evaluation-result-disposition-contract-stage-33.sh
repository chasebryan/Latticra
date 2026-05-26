#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation result disposition contract stage 33: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation result disposition contract stage 33: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage33_doc='docs/NADIA_PROMPT_EVALUATION_RESULT_DISPOSITION_CONTRACT_STAGE_33.md'
stage33_status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_DISPOSITION_CONTRACT_STAGE_33_STATUS.md'
stage32_status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT_STAGE_32_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
foundation_index='docs/FOUNDATION_INDEX.md'
status_index='docs/status/README.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
disposition_script='scripts/nadia-prompt-evaluation-result-disposition-contract.sh'
stage33_guard='scripts/test-nadia-prompt-evaluation-result-disposition-contract-stage-33.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-disposition-contract-stage-33.yml'
makefile='Makefile'

require_file "$stage33_doc"
require_file "$stage33_status"
require_file "$stage32_status"
require_file "$foundation"
require_file "$foundation_index"
require_file "$status_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$disposition_script"
require_file "$stage33_guard"
require_file "$workflow"
require_file "$makefile"

require_contains 'Status: Stage-33 implementation contract' "$stage33_doc"
require_contains 'nadia_stage_33_prompt_evaluation_result_disposition_contract_present=1' "$stage33_doc"
require_contains 'prompt_evaluation_result_disposition_contract_command=scripts/nadia-prompt-evaluation-result-disposition-contract.sh' "$stage33_doc"
require_contains 'installed_prompt_evaluation_result_disposition_contract_command=latticra-nadia prompt-evaluation-result-disposition' "$stage33_doc"
require_contains 'prompt_evaluation_result_disposition_contract_status=contract_only' "$stage33_doc"
require_contains 'prompt_evaluation_result_disposition_authority=0' "$stage33_doc"
require_contains 'requires_prompt_evaluation_result_review_contract=1' "$stage33_doc"
require_contains 'requires_future_prompt_evaluation_result_release_contract=1' "$stage33_doc"
require_contains 'prompt_evaluation_result_disposition_record_created=0' "$stage33_doc"
require_contains 'prompt_evaluation_result_disposition_decision_recorded=0' "$stage33_doc"
require_contains 'prompt_evaluation_result_release_record_created=0' "$stage33_doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage33_doc"
require_contains 'answer_text_generated=0' "$stage33_doc"
require_contains 'runtime_invoked=0' "$stage33_doc"
require_contains 'prompt_evaluated=0' "$stage33_doc"
require_contains 'token_generation_performed=0' "$stage33_doc"
require_contains 'inference_performed=0' "$stage33_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-disposition-contract-stage-33.sh' "$stage33_doc"

require_contains 'Status: implementation status record' "$stage33_status"
require_contains 'nadia_stage_33_prompt_evaluation_result_disposition_contract_present=1' "$stage33_status"
require_contains 'nadia_prompt_evaluation_result_disposition_contract_generator_present=1' "$stage33_status"
require_contains 'prompt_evaluation_result_disposition_contract_status=contract_only' "$stage33_status"
require_contains 'prompt_evaluation_result_disposition_promotion_allowed=0' "$stage33_status"
require_contains 'prompt_evaluation_result_disposition_record_created=0' "$stage33_status"
require_contains 'prompt_evaluation_result_release_record_created=0' "$stage33_status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage33_status"
require_contains 'runtime_invoked=0' "$stage33_status"
require_contains 'prompt_evaluated=0' "$stage33_status"
require_contains 'token_generation_performed=0' "$stage33_status"
require_contains 'inference_performed=0' "$stage33_status"
require_contains 'prompt-evaluation result release contract' "$stage33_status"

require_contains 'Stage-33: Prompt Evaluation Result Disposition Contract' "$foundation"
require_contains 'Stage-34: Prompt Evaluation Result Release Contract' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_DISPOSITION_CONTRACT_STAGE_33.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_DISPOSITION_CONTRACT_STAGE_33_STATUS.md' "$status_index"
require_contains 'Stage-33 now defines a prompt-evaluation result disposition contract' "$stage32_status"
require_contains 'Nadia prompt evaluation result disposition contract Stage-33 + guardrails' "$foundation_index"
require_contains 'nadia_stage_33_prompt_evaluation_result_disposition_contract_present=1' "$readme"
require_contains 'latticra-nadia prompt-evaluation-result-disposition' "$readme"
require_contains '| Nadia offline AI foundation | 71% |' "$readme"
require_contains 'Latest Nadia prompt evaluation result disposition contract Stage-33 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation result disposition contract Stage-33 note: 2026-05-25 CDT' "$current_status"
require_contains '| Nadia offline AI foundation | 71% |' "$root_status"
require_contains '| Nadia offline AI foundation | 71% |' "$current_status"
require_contains 'Nadia prompt evaluation result disposition contract Stage-33' "$current_status"
require_contains 'latticra-nadia prompt-evaluation-result-disposition' "$installer_readme"
require_contains 'prompt-evaluation result disposition recording' "$installer_readme"
require_contains 'disposition decision recording' "$installer_readme"
require_contains 'nadia prompt-evaluation-result-disposition' "$ui_model"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, and Stage-37 console surfaces are metadata-only' "$ui_model"
require_contains 'share/latticra/nadia/prompt-evaluation-result-disposition' "$components_manifest"
require_contains 'prompt-evaluation result disposition recording' "$components_manifest"
require_contains 'prompt-evaluation-result-disposition metadata records future prompt evaluation result release requirements' "$components_manifest"
require_contains 'scripts/nadia-prompt-evaluation-result-disposition-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_result_disposition_contract_stage=33-prompt-evaluation-result-disposition-contract' "$apply_script"
require_contains 'prompt_evaluation_result_disposition_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_disposition_decision_recorded=0' "$apply_script"
require_contains 'stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$apply_script"
require_contains 'stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract' "$panel_config"
require_contains 'prompt_evaluation_result_disposition_contract_stage=33-prompt-evaluation-result-disposition-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-result-disposition' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result_disposition=stage-33-prompt-evaluation-result-disposition-contract' "$panel_ui"
require_contains 'nadia-prompt-evaluation-result-disposition' "$makefile"
require_contains 'sh ./scripts/nadia-prompt-evaluation-result-disposition-contract.sh' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-disposition-contract-stage-33.sh' "$workflow"

require_contains 'NADIA PROMPT EVALUATION RESULT DISPOSITION CONTRACT' "$disposition_script"
require_contains 'prompt_evaluation_result_disposition_contract_status=contract_only' "$disposition_script"
require_contains 'requires_prompt_evaluation_result_review_contract=1' "$disposition_script"
require_contains 'requires_future_prompt_evaluation_result_release_contract=1' "$disposition_script"
require_contains 'prompt_evaluation_result_disposition_record_created=0' "$disposition_script"
require_contains 'prompt_evaluation_result_disposition_decision_recorded=0' "$disposition_script"
require_contains 'prompt_evaluation_result_release_record_created=0' "$disposition_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$disposition_script"
require_contains 'answer_text_generated=0' "$disposition_script"
require_contains 'runtime_invoked=0' "$disposition_script"
require_contains 'prompt_evaluated=0' "$disposition_script"
require_contains 'token_generation_performed=0' "$disposition_script"
require_contains 'inference_performed=0' "$disposition_script"
require_contains 'outside Nadia prompt-evaluation-result-disposition boundary' "$disposition_script"

tmp_root="${TMPDIR:-/tmp}"
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage33-result-disposition-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

review="$tmpdir/prompt-evaluation-result-review-stage32-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$review" <<'EOF_REVIEW'
NADIA PROMPT EVALUATION RESULT REVIEW CONTRACT
stage=32-prompt-evaluation-result-review-contract
prompt_evaluation_result_review_contract_status=contract_only
prompt_evaluation_result_review_stage=contract-only
prompt_evaluation_result_review_authority=0
prompt_evaluation_result_review_allowed=0
prompt_evaluation_result_review_recorded=0
prompt_evaluation_result_review_created=0
prompt_evaluation_result_review_performed=0
prompt_evaluation_result_review_metadata_present=1
prompt_evaluation_result_review_family=operator-reviewed-prompt-evaluation-result-review
prompt_evaluation_result_review_format=contract-only-offline-evaluation-result-review
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
prompt_evaluation_result_review_record_created=0
prompt_evaluation_result_review_record_validated=0
prompt_evaluation_result_review_record_serialized=0
prompt_evaluation_result_review_record_written=0
prompt_evaluation_result_review_record_submitted=0
prompt_evaluation_result_review_decision_recorded=0
prompt_evaluation_result_review_approval_recorded=0
prompt_evaluation_result_review_rejection_recorded=0
prompt_evaluation_result_review_findings_recorded=0
prompt_evaluation_result_recorded=0
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
future_qa_dialogue_capability_planned=1
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
prompt_evaluation_result_stage=contract-only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
EOF_REVIEW

NADIA_PROMPT_EVALUATION_RESULT_DISPOSITION_TIMESTAMP=stage33-test \
  sh "$disposition_script" \
  --prompt-evaluation-result-review "$review" \
  --request-class awareness-education \
  --disposition-family operator-reviewed-prompt-evaluation-result-disposition \
  --disposition-format contract-only-offline-evaluation-result-disposition \
  --output "$out" >/dev/null

report="$out/nadia-prompt-evaluation-result-disposition-contract-stage33-test.txt"
require_file "$report"
require_file "$out/latest-prompt-evaluation-result-disposition-contract.txt"

require_contains 'stage=33-prompt-evaluation-result-disposition-contract' "$report"
require_contains 'prompt_evaluation_result_disposition_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_disposition_authority=0' "$report"
require_contains 'prompt_evaluation_result_disposition_recorded=0' "$report"
require_contains 'prompt_evaluation_result_disposition_record_created=0' "$report"
require_contains 'prompt_evaluation_result_disposition_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_disposition_applied=0' "$report"
require_contains 'prompt_evaluation_result_release_record_created=0' "$report"
require_contains 'prompt_evaluation_result_review_record_created=0' "$report"
require_contains 'prompt_evaluation_result_review_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$report"
require_contains 'prompt_evaluation_result_output_text_recorded=0' "$report"
require_contains 'requires_prompt_evaluation_result_review_contract=1' "$report"
require_contains 'requires_future_prompt_evaluation_result_release_contract=1' "$report"
require_contains 'prompt_evaluation_result_disposition_promotion_allowed=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'qa_dialogue_generated=0' "$report"
require_contains 'answer_text_generated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

if sh "$disposition_script" \
  --prompt-evaluation-result-review "$review" \
  --disposition-family sexualized-disposition \
  --output "$out/boundary" >"$tmpdir/boundary.out" 2>&1; then
  printf 'nadia prompt evaluation result disposition contract stage 33: sexualized disposition family was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-result-disposition boundary' "$tmpdir/boundary.out"

printf 'nadia_prompt_evaluation_result_disposition_contract_stage_33: ok\n'
