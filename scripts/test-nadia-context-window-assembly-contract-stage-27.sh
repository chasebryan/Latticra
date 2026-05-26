#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia context window assembly contract stage 27: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia context window assembly contract stage 27: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia context window assembly contract stage 27: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage27_doc='docs/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27.md'
stage27_status='docs/status/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27_STATUS.md'
stage26_status='docs/status/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
context_script='scripts/nadia-context-window-assembly-contract.sh'
stage27_guard='scripts/test-nadia-context-window-assembly-contract-stage-27.sh'
stage26_guard='scripts/test-nadia-prompt-token-sequence-contract-stage-26.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'
workflow='.github/workflows/nadia-context-window-assembly-contract-stage-27.yml'

require_file "$stage27_doc"
require_file "$stage27_status"
require_file "$stage26_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$context_script"
require_file "$stage27_guard"
require_file "$stage26_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"
require_file "$workflow"

require_contains 'Status: Stage-27 implementation contract' "$stage27_doc"
require_contains 'context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh' "$stage27_doc"
require_contains 'installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly' "$stage27_doc"
require_contains 'context_window_assembly_contract_status=contract_only' "$stage27_doc"
require_contains 'context_window_assembly_authority=0' "$stage27_doc"
require_contains 'requires_prompt_token_sequence_contract=1' "$stage27_doc"
require_contains 'requires_future_prompt_evaluation_input_contract=1' "$stage27_doc"
require_contains 'context_window_assembled=0' "$stage27_doc"
require_contains 'prompt_evaluation_input_created=0' "$stage27_doc"
require_contains 'runtime_invoked=0' "$stage27_doc"
require_contains 'sh scripts/test-nadia-context-window-assembly-contract-stage-27.sh' "$stage27_doc"

require_contains 'Status: implementation status record' "$stage27_status"
require_contains 'nadia_stage_27_context_window_assembly_contract_present=1' "$stage27_status"
require_contains 'nadia_context_window_assembly_contract_generator_present=1' "$stage27_status"
require_contains 'context_window_assembly_contract_status=contract_only' "$stage27_status"
require_contains 'context_window_assembly_promotion_allowed=0' "$stage27_status"
require_contains 'prompt evaluation input contract' "$stage27_status"

require_contains 'Stage-27: Context Window Assembly Contract' "$foundation"
require_contains 'Stage-28: Prompt Evaluation Input Contract' "$foundation"
require_contains 'Stage-29: Prompt Evaluation Runtime Handoff Contract' "$foundation"
require_contains 'scripts/nadia-context-window-assembly-contract.sh' "$foundation"
require_contains 'test-nadia-context-window-assembly-contract-stage-27.sh' "$foundation"
require_contains 'Before Stage-28 starts' "$foundation"
require_contains 'Before Stage-32 starts' "$foundation"
require_contains 'NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27.md' "$foundation_index"
require_contains 'NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27_STATUS.md' "$status_index"
require_contains 'Nadia context window assembly contract Stage-27 + guardrails' "$foundation_index"
require_contains 'nadia_stage_27_context_window_assembly_contract_present=1' "$readme"
require_contains 'Latest Nadia context window assembly contract Stage-27 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia context window assembly contract Stage-27 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia context window assembly contract Stage-27' "$current_status"
require_contains 'Stage-27 now defines a context-window assembly contract' "$stage26_status"

require_contains 'NADIA CONTEXT WINDOW ASSEMBLY CONTRACT' "$context_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$context_script"
require_contains 'context_window_assembly_contract_status=contract_only' "$context_script"
require_contains 'requires_prompt_token_sequence_contract=1' "$context_script"
require_contains 'requires_future_prompt_evaluation_input_contract=1' "$context_script"
require_contains 'context_window_assembly_plan_recorded=1' "$context_script"
require_contains 'context_window_assembly_performed=0' "$context_script"
require_contains 'context_window_assembled=0' "$context_script"
require_contains 'context_window_token_budget_recorded=0' "$context_script"
require_contains 'context_window_truncation_applied=0' "$context_script"
require_contains 'context_window_serialized=0' "$context_script"
require_contains 'prompt_evaluation_input_created=0' "$context_script"
require_contains 'prompt_evaluation_input_materialized=0' "$context_script"
require_contains 'prompt_text_read=0' "$context_script"
require_contains 'prompt_tokens_created=0' "$context_script"
require_contains 'prompt_token_sequence_recorded=0' "$context_script"
require_contains 'runtime_invoked=0' "$context_script"
require_contains 'runtime_session_created=0' "$context_script"
require_contains 'qa_dialogue_generated=0' "$context_script"
require_contains 'sexual_request_refusal=always' "$context_script"
require_contains 'manipulation_resistance=required' "$context_script"
require_contains 'outside Nadia context-window-assembly boundary' "$context_script"
require_not_contains 'curl ' "$context_script"
require_not_contains 'wget ' "$context_script"
require_not_contains 'ssh ' "$context_script"

require_contains 'context-window-assembly' "$apply_script"
require_contains 'scripts/nadia-context-window-assembly-contract.sh' "$apply_script"
require_contains 'context_window_assembly_contract_stage=27-context-window-assembly-contract' "$panel_config"
require_contains 'nadia context-window-assembly' "$panel_ui"
require_contains 'latticra-nadia context-window-assembly' "$installer_readme"
require_contains 'nadia context-window-assembly' "$ui_model"
require_contains 'context-window-assembly' "$components_manifest"
require_contains 'nadia-context-window-assembly' "$makefile"
require_contains 'sh scripts/test-nadia-context-window-assembly-contract-stage-27.sh' "$workflow"

out="${TMPDIR:-/tmp}/latticra-nadia-stage27-context-window-assembly-test-$$"
sequence="$out/nadia-prompt-token-sequence-contract-stage26-fixture.txt"
mkdir -p "$out"

cat > "$sequence" <<'EOF_SEQUENCE'
NADIA PROMPT TOKEN SEQUENCE CONTRACT
stage=26-prompt-token-sequence-contract
prompt_token_sequence_contract_status=contract_only
prompt_token_sequence_stage=contract-only
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_sequence_metadata_present=1
prompt_token_sequence_family=operator-reviewed-prompt-token-sequence
prompt_token_sequence_format=contract-only-offline-sequence
prompt_token_sequence_decision=blocked_contract_only
prompt_token_sequence_evidence_present=1
prompt_token_sequence_source_policy=operator-reviewed-offline
prompt_token_sequence_plan_recorded=1
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_sequence_runtime_invoked=0
prompt_tokenization_stage=contract-only
tokenizer_runtime_attachment_stage=contract-only
tokenizer_artifact_binding_stage=contract-only
tokenizer_artifact_verification_stage=contract-only
tokenizer_artifact_measurement_stage=contract-only
tokenizer_artifact_inventory_stage=contract-only
tokenizer_manifest_stage=contract-only
tokenizer_specification_stage=contract-only
tokenization_boundary_stage=contract-only
requires_prompt_tokenization_contract=1
requires_tokenizer_runtime_attachment_contract=1
requires_tokenizer_artifact_binding_contract=1
requires_tokenizer_artifact_verification_contract=1
requires_tokenizer_artifact_measurement_contract=1
requires_tokenizer_artifact_inventory_contract=1
requires_tokenizer_manifest_contract=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_future_context_window_assembly_contract=1
prompt_token_sequence_promotion_allowed=0
requires_prompt_tokenization_reference=1
requires_prompt_tokenization_contract_reference=1
requires_tokenizer_runtime_attachment_reference=1
requires_prompt_materialization_reference=1
requires_prompt_receipt_reference=1
requires_prompt_token_count_policy=1
requires_prompt_token_order_policy=1
requires_prompt_token_id_visibility_policy=1
requires_prompt_token_offset_policy=1
requires_context_window_policy=1
requires_no_prompt_token_ids_recorded=1
requires_no_attention_mask_creation=1
requires_no_position_id_creation=1
requires_no_context_window_assembly=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
prompt_token_sequence_open_authority=0
prompt_token_sequence_read_authority=0
prompt_token_sequence_write_authority=0
prompt_token_sequence_execute_authority=0
prompt_token_sequence_runtime_authority=0
prompt_token_sequence_token_id_record_authority=0
prompt_token_sequence_order_record_authority=0
prompt_token_sequence_offset_record_authority=0
prompt_token_sequence_context_window_authority=0
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
prompt_token_byte_offsets_recorded=0
prompt_attention_mask_created=0
prompt_position_ids_created=0
context_window_assembled=0
prompt_evaluation_input_created=0
prompt_text_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_tokenized=0
tokenizer_runtime_attachment_performed=0
tokenizer_attached_to_runtime=0
runtime_session_created=0
runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0
tokenizer_artifact_binding_performed=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_manifest_loaded=0
tokenizer_manifest_parsed=0
tokenizer_file_opened=0
tokenizer_vocab_loaded=0
future_qa_dialogue_capability_planned=1
qa_dialogue_generated=0
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
live_web_lookup_authority=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_evaluated=0
token_generation_performed=0
inference_performed=0
tool_execution_performed=0
network_authority=0
EOF_SEQUENCE

require_file "$sequence"

NADIA_CONTEXT_WINDOW_ASSEMBLY_TIMESTAMP=stage27-test sh "$context_script" \
  --prompt-token-sequence "$sequence" \
  --request-class awareness-education \
  --context-family operator-reviewed-context-window-assembly \
  --context-format contract-only-offline-context-window \
  --output "$out" >/tmp/latticra-nadia-stage27-context-window-assembly-test.out
context="$out/nadia-context-window-assembly-contract-stage27-test.txt"

require_file "$context"
require_file "$out/latest-context-window-assembly-contract.txt"
require_contains 'NADIA CONTEXT WINDOW ASSEMBLY CONTRACT' "$context"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$context"
require_contains 'public_name=Nadia' "$context"
require_contains 'stage=27-context-window-assembly-contract' "$context"
require_contains 'request_class=awareness-education' "$context"
require_contains 'context_window_assembly_contract_status=contract_only' "$context"
require_contains 'context_window_assembly_stage=contract-only' "$context"
require_contains 'context_window_assembly_authority=0' "$context"
require_contains 'context_window_assembly_allowed=0' "$context"
require_contains 'context_window_assembly_performed=0' "$context"
require_contains 'context_window_assembly_metadata_present=1' "$context"
require_contains 'context_window_family=operator-reviewed-context-window-assembly' "$context"
require_contains 'context_window_format=contract-only-offline-context-window' "$context"
require_contains 'prompt_token_sequence_stage_required=26-prompt-token-sequence-contract' "$context"
require_contains 'context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh' "$context"
require_contains 'installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly' "$context"
require_contains 'context_window_assembly_decision=blocked_contract_only' "$context"
require_contains 'context_window_assembly_evidence_present=1' "$context"
require_contains 'context_window_assembly_source_policy=operator-reviewed-offline' "$context"
require_contains 'context_window_assembly_plan_recorded=1' "$context"
require_contains 'context_window_assembly_method_planned=offline-context-window-policy-review' "$context"
require_contains 'context_window_assembly_result_recorded=0' "$context"
require_contains 'context_window_assembly_runtime_invoked=0' "$context"
require_contains 'requires_prompt_token_sequence_contract=1' "$context"
require_contains 'requires_future_prompt_evaluation_input_contract=1' "$context"
require_contains 'context_window_assembly_promotion_allowed=0' "$context"
require_contains 'requires_context_window_layout_policy=1' "$context"
require_contains 'requires_context_window_token_budget_policy=1' "$context"
require_contains 'requires_context_window_truncation_policy=1' "$context"
require_contains 'requires_context_window_ordering_policy=1' "$context"
require_contains 'requires_attention_mask_policy=1' "$context"
require_contains 'requires_position_id_policy=1' "$context"
require_contains 'requires_prompt_evaluation_input_policy=1' "$context"
require_contains 'requires_no_context_window_assembly=1' "$context"
require_contains 'requires_no_prompt_evaluation_input_creation=1' "$context"
require_contains 'context_window_assembly_prompt_evaluation_input_authority=0' "$context"
require_contains 'context_window_assembled=0' "$context"
require_contains 'context_window_token_budget_recorded=0' "$context"
require_contains 'context_window_entry_count_recorded=0' "$context"
require_contains 'context_window_truncation_applied=0' "$context"
require_contains 'context_window_serialized=0' "$context"
require_contains 'prompt_evaluation_input_created=0' "$context"
require_contains 'prompt_evaluation_input_materialized=0' "$context"
require_contains 'prompt_evaluation_input_validated=0' "$context"
require_contains 'prompt_text_read=0' "$context"
require_contains 'prompt_text_received=0' "$context"
require_contains 'prompt_text_materialized=0' "$context"
require_contains 'prompt_tokens_created=0' "$context"
require_contains 'prompt_token_sequence_recorded=0' "$context"
require_contains 'prompt_token_ids_recorded=0' "$context"
require_contains 'prompt_attention_mask_created=0' "$context"
require_contains 'prompt_position_ids_created=0' "$context"
require_contains 'tokenizer_runtime_attachment_performed=0' "$context"
require_contains 'tokenizer_attached_to_runtime=0' "$context"
require_contains 'runtime_session_created=0' "$context"
require_contains 'runtime_invoked=0' "$context"
require_contains 'future_qa_dialogue_capability_planned=1' "$context"
require_contains 'qa_dialogue_generated=0' "$context"
require_contains 'sexual_request_refusal=always' "$context"
require_contains 'manipulation_resistance=required' "$context"
require_contains 'prompt_evaluated=0' "$context"
require_contains 'token_generation_performed=0' "$context"
require_contains 'inference_performed=0' "$context"
require_contains 'tool_execution_performed=0' "$context"
require_contains 'network_authority=0' "$context"

if sh "$context_script" \
  --prompt-token-sequence "$sequence" \
  --request-class sexual-content \
  --output "$out" >/tmp/latticra-nadia-stage27-boundary.out 2>&1; then
  printf 'nadia context window assembly contract stage 27: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia context-window-assembly boundary' /tmp/latticra-nadia-stage27-boundary.out

printf 'nadia_context_window_assembly_contract_stage_27: ok\n'
