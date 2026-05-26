#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation result review contract stage 32: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation result review contract stage 32: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage32_doc='docs/NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT_STAGE_32.md'
stage32_status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT_STAGE_32_STATUS.md'
stage31_status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_CONTRACT_STAGE_31_STATUS.md'
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
review_script='scripts/nadia-prompt-evaluation-result-review-contract.sh'
stage32_guard='scripts/test-nadia-prompt-evaluation-result-review-contract-stage-32.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-review-contract-stage-32.yml'
makefile='Makefile'

require_file "$stage32_doc"
require_file "$stage32_status"
require_file "$stage31_status"
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
require_file "$review_script"
require_file "$stage32_guard"
require_file "$workflow"
require_file "$makefile"

require_contains 'Status: Stage-32 implementation contract' "$stage32_doc"
require_contains 'nadia_stage_32_prompt_evaluation_result_review_contract_present=1' "$stage32_doc"
require_contains 'prompt_evaluation_result_review_contract_command=scripts/nadia-prompt-evaluation-result-review-contract.sh' "$stage32_doc"
require_contains 'installed_prompt_evaluation_result_review_contract_command=latticra-nadia prompt-evaluation-result-review' "$stage32_doc"
require_contains 'prompt_evaluation_result_review_contract_status=contract_only' "$stage32_doc"
require_contains 'prompt_evaluation_result_review_authority=0' "$stage32_doc"
require_contains 'requires_prompt_evaluation_result_contract=1' "$stage32_doc"
require_contains 'requires_future_prompt_evaluation_result_disposition_contract=1' "$stage32_doc"
require_contains 'prompt_evaluation_result_review_record_created=0' "$stage32_doc"
require_contains 'prompt_evaluation_result_review_decision_recorded=0' "$stage32_doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage32_doc"
require_contains 'answer_text_generated=0' "$stage32_doc"
require_contains 'runtime_invoked=0' "$stage32_doc"
require_contains 'prompt_evaluated=0' "$stage32_doc"
require_contains 'token_generation_performed=0' "$stage32_doc"
require_contains 'inference_performed=0' "$stage32_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-review-contract-stage-32.sh' "$stage32_doc"

require_contains 'Status: implementation status record' "$stage32_status"
require_contains 'nadia_stage_32_prompt_evaluation_result_review_contract_present=1' "$stage32_status"
require_contains 'nadia_prompt_evaluation_result_review_contract_generator_present=1' "$stage32_status"
require_contains 'prompt_evaluation_result_review_contract_status=contract_only' "$stage32_status"
require_contains 'prompt_evaluation_result_review_promotion_allowed=0' "$stage32_status"
require_contains 'prompt_evaluation_result_review_record_created=0' "$stage32_status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage32_status"
require_contains 'runtime_invoked=0' "$stage32_status"
require_contains 'prompt_evaluated=0' "$stage32_status"
require_contains 'token_generation_performed=0' "$stage32_status"
require_contains 'inference_performed=0' "$stage32_status"
require_contains 'prompt-evaluation result disposition contract' "$stage32_status"

require_contains 'Stage-32: Prompt Evaluation Result Review Contract' "$foundation"
require_contains 'Stage-33: Prompt Evaluation Result Disposition Contract' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT_STAGE_32.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_REVIEW_CONTRACT_STAGE_32_STATUS.md' "$status_index"
require_contains 'prompt-evaluation result review contract' "$stage31_status"
require_contains 'Nadia prompt evaluation result review contract Stage-32 + guardrails' "$foundation_index"
require_contains 'nadia_stage_32_prompt_evaluation_result_review_contract_present=1' "$readme"
require_contains 'latticra-nadia prompt-evaluation-result-review' "$readme"
require_contains '| Nadia offline AI foundation | 74% |' "$readme"
require_contains 'Latest Nadia prompt evaluation result review contract Stage-32 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation result review contract Stage-32 note: 2026-05-25 CDT' "$current_status"
require_contains '| Nadia offline AI foundation | 74% |' "$root_status"
require_contains '| Nadia offline AI foundation | 74% |' "$current_status"
require_contains 'Nadia prompt evaluation result review contract Stage-32' "$current_status"
require_contains 'latticra-nadia prompt-evaluation-result-review' "$installer_readme"
require_contains 'prompt-evaluation result review recording' "$installer_readme"
require_contains 'review decision recording' "$installer_readme"
require_contains 'nadia prompt-evaluation-result-review' "$ui_model"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, Stage-38, Stage-39, and Stage-40 console surfaces are metadata-only' "$ui_model"
require_contains 'share/latticra/nadia/prompt-evaluation-result-review' "$components_manifest"
require_contains 'prompt-evaluation result review recording' "$components_manifest"
require_contains 'prompt-evaluation-result-review metadata records future prompt evaluation result disposition requirements' "$components_manifest"
require_contains 'scripts/nadia-prompt-evaluation-result-review-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_result_review_contract_stage=32-prompt-evaluation-result-review-contract' "$apply_script"
require_contains 'prompt_evaluation_result_review_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_review_decision_recorded=0' "$apply_script"
require_contains 'stage=40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract' "$apply_script"
require_contains 'stage=40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract' "$panel_config"
require_contains 'prompt_evaluation_result_review_contract_stage=32-prompt-evaluation-result-review-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-result-review' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result_review=stage-32-prompt-evaluation-result-review-contract' "$panel_ui"
require_contains 'nadia-prompt-evaluation-result-review' "$makefile"
require_contains 'sh ./scripts/nadia-prompt-evaluation-result-review-contract.sh' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-review-contract-stage-32.sh' "$workflow"

require_contains 'NADIA PROMPT EVALUATION RESULT REVIEW CONTRACT' "$review_script"
require_contains 'prompt_evaluation_result_review_contract_status=contract_only' "$review_script"
require_contains 'requires_prompt_evaluation_result_contract=1' "$review_script"
require_contains 'requires_future_prompt_evaluation_result_disposition_contract=1' "$review_script"
require_contains 'prompt_evaluation_result_review_record_created=0' "$review_script"
require_contains 'prompt_evaluation_result_review_decision_recorded=0' "$review_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$review_script"
require_contains 'answer_text_generated=0' "$review_script"
require_contains 'runtime_invoked=0' "$review_script"
require_contains 'prompt_evaluated=0' "$review_script"
require_contains 'token_generation_performed=0' "$review_script"
require_contains 'inference_performed=0' "$review_script"
require_contains 'outside Nadia prompt-evaluation-result-review boundary' "$review_script"

tmp_root="${TMPDIR:-/tmp}"
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage32-result-review-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

result="$tmpdir/prompt-evaluation-result-stage31-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$result" <<'EOF_RESULT'
NADIA PROMPT EVALUATION RESULT CONTRACT
stage=31-prompt-evaluation-result-contract
prompt_evaluation_result_contract_status=contract_only
prompt_evaluation_result_stage=contract-only
prompt_evaluation_result_authority=0
prompt_evaluation_result_allowed=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_performed=0
prompt_evaluation_result_metadata_present=1
prompt_evaluation_result_family=operator-reviewed-prompt-evaluation-result
prompt_evaluation_result_format=contract-only-offline-evaluation-result
prompt_evaluation_result_decision=blocked_contract_only
prompt_evaluation_result_evidence_present=1
prompt_evaluation_result_source_policy=operator-reviewed-offline
prompt_evaluation_result_plan_recorded=1
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
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
EOF_RESULT

NADIA_PROMPT_EVALUATION_RESULT_REVIEW_TIMESTAMP=stage32-test \
  sh "$review_script" \
  --prompt-evaluation-result "$result" \
  --request-class awareness-education \
  --review-family operator-reviewed-prompt-evaluation-result-review \
  --review-format contract-only-offline-evaluation-result-review \
  --output "$out" >/dev/null

report="$out/nadia-prompt-evaluation-result-review-contract-stage32-test.txt"
require_file "$report"
require_file "$out/latest-prompt-evaluation-result-review-contract.txt"

require_contains 'stage=32-prompt-evaluation-result-review-contract' "$report"
require_contains 'prompt_evaluation_result_review_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_review_authority=0' "$report"
require_contains 'prompt_evaluation_result_review_recorded=0' "$report"
require_contains 'prompt_evaluation_result_review_record_created=0' "$report"
require_contains 'prompt_evaluation_result_review_decision_recorded=0' "$report"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$report"
require_contains 'prompt_evaluation_result_output_text_recorded=0' "$report"
require_contains 'requires_prompt_evaluation_result_contract=1' "$report"
require_contains 'requires_future_prompt_evaluation_result_disposition_contract=1' "$report"
require_contains 'prompt_evaluation_result_review_promotion_allowed=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'qa_dialogue_generated=0' "$report"
require_contains 'answer_text_generated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

if sh "$review_script" \
  --prompt-evaluation-result "$result" \
  --review-family sexualized-review \
  --output "$out/boundary" >"$tmpdir/boundary.out" 2>&1; then
  printf 'nadia prompt evaluation result review contract stage 32: sexualized review family was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-result-review boundary' "$tmpdir/boundary.out"

printf 'nadia_prompt_evaluation_result_review_contract_stage_32: ok\n'
