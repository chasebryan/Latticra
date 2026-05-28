#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation result contract stage 31: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation result contract stage 31: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage31_doc='docs/NADIA_PROMPT_EVALUATION_RESULT_CONTRACT_STAGE_31.md'
stage31_status='docs/status/NADIA_PROMPT_EVALUATION_RESULT_CONTRACT_STAGE_31_STATUS.md'
stage30_status='docs/status/NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT_STAGE_30_STATUS.md'
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
result_script='scripts/nadia-prompt-evaluation-result-contract.sh'
stage31_guard='scripts/test-nadia-prompt-evaluation-result-contract-stage-31.sh'
workflow='.github/workflows/nadia-prompt-evaluation-result-contract-stage-31.yml'
makefile='Makefile'

require_file "$stage31_doc"
require_file "$stage31_status"
require_file "$stage30_status"
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
require_file "$result_script"
require_file "$stage31_guard"
require_file "$workflow"
require_file "$makefile"

require_contains 'Status: Stage-31 implementation contract' "$stage31_doc"
require_contains 'nadia_stage_31_prompt_evaluation_result_contract_present=1' "$stage31_doc"
require_contains 'prompt_evaluation_result_contract_command=scripts/nadia-prompt-evaluation-result-contract.sh' "$stage31_doc"
require_contains 'installed_prompt_evaluation_result_contract_command=latticra-nadia prompt-evaluation-result' "$stage31_doc"
require_contains 'prompt_evaluation_result_contract_status=contract_only' "$stage31_doc"
require_contains 'prompt_evaluation_result_authority=0' "$stage31_doc"
require_contains 'requires_prompt_evaluation_invocation_contract=1' "$stage31_doc"
require_contains 'requires_future_prompt_evaluation_result_review_contract=1' "$stage31_doc"
require_contains 'prompt_evaluation_result_record_created=0' "$stage31_doc"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage31_doc"
require_contains 'answer_text_generated=0' "$stage31_doc"
require_contains 'runtime_invoked=0' "$stage31_doc"
require_contains 'prompt_evaluated=0' "$stage31_doc"
require_contains 'token_generation_performed=0' "$stage31_doc"
require_contains 'inference_performed=0' "$stage31_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-contract-stage-31.sh' "$stage31_doc"

require_contains 'Status: implementation status record' "$stage31_status"
require_contains 'nadia_stage_31_prompt_evaluation_result_contract_present=1' "$stage31_status"
require_contains 'nadia_prompt_evaluation_result_contract_generator_present=1' "$stage31_status"
require_contains 'prompt_evaluation_result_contract_status=contract_only' "$stage31_status"
require_contains 'prompt_evaluation_result_promotion_allowed=0' "$stage31_status"
require_contains 'prompt_evaluation_result_record_created=0' "$stage31_status"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$stage31_status"
require_contains 'runtime_invoked=0' "$stage31_status"
require_contains 'prompt_evaluated=0' "$stage31_status"
require_contains 'token_generation_performed=0' "$stage31_status"
require_contains 'inference_performed=0' "$stage31_status"
require_contains 'prompt-evaluation result review contract' "$stage31_status"
require_contains 'Stage-32 now defines a prompt-evaluation result review contract' "$stage31_status"

require_contains 'Stage-31: Prompt Evaluation Result Contract' "$foundation"
require_contains 'Stage-32: Prompt Evaluation Result Review Contract' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_CONTRACT_STAGE_31.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_RESULT_CONTRACT_STAGE_31_STATUS.md' "$status_index"
require_contains 'prompt-evaluation result contract' "$stage30_status"
require_contains 'Nadia prompt evaluation result contract Stage-31 + guardrails' "$foundation_index"
require_contains 'nadia_stage_31_prompt_evaluation_result_contract_present=1' "$readme"
require_contains 'latticra-nadia prompt-evaluation-result' "$readme"
require_contains '| Nadia offline AI foundation | 77% |' "$readme"
require_contains 'Latest Nadia prompt evaluation result contract Stage-31 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation result contract Stage-31 note: 2026-05-25 CDT' "$current_status"
require_contains '| Nadia offline AI foundation | 77% |' "$root_status"
require_contains '| Nadia offline AI foundation | 77% |' "$current_status"
require_contains 'Nadia prompt evaluation result contract Stage-31' "$current_status"
require_contains 'latticra-nadia prompt-evaluation-result' "$installer_readme"
require_contains 'prompt-evaluation result recording' "$installer_readme"
require_contains 'model-output recording' "$installer_readme"
require_contains 'nadia prompt-evaluation-result' "$ui_model"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, Stage-38, Stage-39, and Stage-40 console surfaces are metadata-only' "$ui_model"
require_contains 'share/latticra/nadia/prompt-evaluation-result' "$components_manifest"
require_contains 'prompt-evaluation result recording' "$components_manifest"
require_contains 'prompt-evaluation-result metadata records future prompt evaluation result review requirements' "$components_manifest"
require_contains 'scripts/nadia-prompt-evaluation-result-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_result_contract_stage=31-prompt-evaluation-result-contract' "$apply_script"
require_contains 'prompt_evaluation_result_record_created=0' "$apply_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$apply_script"
require_contains 'stage=40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract' "$apply_script"
require_contains 'stage=40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract' "$panel_config"
require_contains 'prompt_evaluation_result_contract_stage=31-prompt-evaluation-result-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-result' "$panel_ui"
require_contains 'nadia_prompt_evaluation_result=stage-31-prompt-evaluation-result-contract' "$panel_ui"
require_contains 'nadia-prompt-evaluation-result' "$makefile"
require_contains 'sh ./scripts/nadia-prompt-evaluation-result-contract.sh' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-result-contract-stage-31.sh' "$workflow"

require_contains 'NADIA PROMPT EVALUATION RESULT CONTRACT' "$result_script"
require_contains 'prompt_evaluation_result_contract_status=contract_only' "$result_script"
require_contains 'requires_prompt_evaluation_invocation_contract=1' "$result_script"
require_contains 'requires_future_prompt_evaluation_result_review_contract=1' "$result_script"
require_contains 'prompt_evaluation_result_record_created=0' "$result_script"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$result_script"
require_contains 'answer_text_generated=0' "$result_script"
require_contains 'runtime_invoked=0' "$result_script"
require_contains 'prompt_evaluated=0' "$result_script"
require_contains 'token_generation_performed=0' "$result_script"
require_contains 'inference_performed=0' "$result_script"
require_contains 'outside Nadia prompt-evaluation-result boundary' "$result_script"

tmp_root="${TMPDIR:-/tmp}"
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage31-result-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

invocation="$tmpdir/prompt-evaluation-invocation-stage30-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$invocation" <<'EOF_INVOCATION'
NADIA PROMPT EVALUATION INVOCATION CONTRACT
stage=30-prompt-evaluation-invocation-contract
prompt_evaluation_invocation_contract_status=contract_only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_invocation_authority=0
prompt_evaluation_invocation_allowed=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_metadata_present=1
prompt_evaluation_invocation_family=operator-reviewed-prompt-evaluation-invocation
prompt_evaluation_invocation_format=contract-only-offline-evaluation-invocation
prompt_evaluation_invocation_decision=blocked_contract_only
prompt_evaluation_invocation_evidence_present=1
prompt_evaluation_invocation_source_policy=operator-reviewed-offline
prompt_evaluation_invocation_plan_recorded=1
prompt_evaluation_invocation_result_recorded=0
prompt_evaluation_invocation_runtime_invoked=0
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
requires_future_prompt_evaluation_result_contract=1
prompt_evaluation_invocation_promotion_allowed=0
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_prompt_evaluation_invocation_schema_policy=1
requires_prompt_evaluation_invocation_denial_policy=1
requires_prompt_evaluation_result_schema_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_invocation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_token_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
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
runtime_handoff_created=0
runtime_handoff_submitted=0
prompt_evaluation_request_created=0
prompt_evaluation_request_serialized=0
prompt_evaluation_request_submitted=0
runtime_invocation_requested=0
runtime_invocation_authority=0
runtime_session_authority=0
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
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
EOF_INVOCATION

NADIA_PROMPT_EVALUATION_RESULT_TIMESTAMP=stage31-test sh "$result_script" \
  --prompt-evaluation-invocation "$invocation" \
  --request-class awareness-education \
  --result-family operator-reviewed-prompt-evaluation-result \
  --result-format contract-only-offline-evaluation-result \
  --output "$out" > "$tmpdir/stdout.txt"

report="$out/nadia-prompt-evaluation-result-contract-stage31-test.txt"
require_file "$report"
require_file "$out/latest-prompt-evaluation-result-contract.txt"
require_contains 'NADIA PROMPT EVALUATION RESULT CONTRACT' "$report"
require_contains 'stage=31-prompt-evaluation-result-contract' "$report"
require_contains 'prompt_evaluation_result_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_result_authority=0' "$report"
require_contains 'prompt_evaluation_result_recorded=0' "$report"
require_contains 'prompt_evaluation_result_record_created=0' "$report"
require_contains 'prompt_evaluation_result_model_output_recorded=0' "$report"
require_contains 'prompt_evaluation_result_output_text_recorded=0' "$report"
require_contains 'requires_prompt_evaluation_invocation_contract=1' "$report"
require_contains 'requires_future_prompt_evaluation_result_review_contract=1' "$report"
require_contains 'prompt_evaluation_result_promotion_allowed=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'runtime_session_created=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'qa_dialogue_generated=0' "$report"
require_contains 'answer_text_generated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"
require_contains 'network_authority=0' "$report"
require_contains 'tool_execution_performed=0' "$report"
require_contains 'source_mutation_authority=0' "$report"

if sh "$result_script" \
  --prompt-evaluation-invocation "$invocation" \
  --request-class sexual-content \
  --output "$out" > "$tmpdir/boundary.out" 2>&1; then
  printf 'nadia prompt evaluation result contract stage 31: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-result boundary' "$tmpdir/boundary.out"

printf 'nadia_prompt_evaluation_result_contract_stage_31: ok\n'
