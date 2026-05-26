#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage28.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation input contract stage 28: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation input contract stage 28: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation input contract stage 28: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage28_doc='docs/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28.md'
stage28_status='docs/status/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28_STATUS.md'
stage27_status='docs/status/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
input_script='scripts/nadia-prompt-evaluation-input-contract.sh'
stage28_guard='scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh'
stage27_guard='scripts/test-nadia-context-window-assembly-contract-stage-27.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'
workflow='.github/workflows/nadia-prompt-evaluation-input-contract-stage-28.yml'

require_file "$stage28_doc"
require_file "$stage28_status"
require_file "$stage27_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$input_script"
require_file "$stage28_guard"
require_file "$stage27_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"
require_file "$workflow"

require_contains 'Status: Stage-28 implementation contract' "$stage28_doc"
require_contains 'prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh' "$stage28_doc"
require_contains 'installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input' "$stage28_doc"
require_contains 'prompt_evaluation_input_contract_status=contract_only' "$stage28_doc"
require_contains 'prompt_evaluation_input_authority=0' "$stage28_doc"
require_contains 'requires_context_window_assembly_contract=1' "$stage28_doc"
require_contains 'requires_future_prompt_evaluation_runtime_handoff_contract=1' "$stage28_doc"
require_contains 'prompt_evaluation_input_created=0' "$stage28_doc"
require_contains 'runtime_invoked=0' "$stage28_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh' "$stage28_doc"

require_contains 'Status: implementation status record' "$stage28_status"
require_contains 'nadia_stage_28_prompt_evaluation_input_contract_present=1' "$stage28_status"
require_contains 'nadia_prompt_evaluation_input_contract_generator_present=1' "$stage28_status"
require_contains 'prompt_evaluation_input_contract_status=contract_only' "$stage28_status"
require_contains 'prompt_evaluation_input_promotion_allowed=0' "$stage28_status"
require_contains 'prompt-evaluation runtime handoff contract' "$stage28_status"

require_contains 'Stage-28: Prompt Evaluation Input Contract' "$foundation"
require_contains 'Stage-29: Prompt Evaluation Runtime Handoff Contract' "$foundation"
require_contains 'Stage-30: Prompt Evaluation Invocation Contract' "$foundation"
require_contains 'scripts/nadia-prompt-evaluation-input-contract.sh' "$foundation"
require_contains 'test-nadia-prompt-evaluation-input-contract-stage-28.sh' "$foundation"
require_contains 'Before Stage-37 starts' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28_STATUS.md' "$status_index"
require_contains 'Nadia prompt evaluation input contract Stage-28 + guardrails' "$foundation_index"
require_contains 'nadia_stage_28_prompt_evaluation_input_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt evaluation input contract Stage-28 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation input contract Stage-28 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt evaluation input contract Stage-28' "$current_status"
require_contains 'Stage-28 now defines a prompt-evaluation-input contract' "$stage27_status"

require_contains 'NADIA PROMPT EVALUATION INPUT CONTRACT' "$input_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$input_script"
require_contains 'prompt_evaluation_input_contract_status=contract_only' "$input_script"
require_contains 'requires_context_window_assembly_contract=1' "$input_script"
require_contains 'requires_future_prompt_evaluation_runtime_handoff_contract=1' "$input_script"
require_contains 'prompt_evaluation_input_plan_recorded=1' "$input_script"
require_contains 'prompt_evaluation_input_created=0' "$input_script"
require_contains 'prompt_evaluation_input_materialized=0' "$input_script"
require_contains 'prompt_evaluation_input_validated=0' "$input_script"
require_contains 'prompt_evaluation_input_serialized=0' "$input_script"
require_contains 'prompt_evaluation_input_written=0' "$input_script"
require_contains 'context_window_assembled=0' "$input_script"
require_contains 'prompt_text_read=0' "$input_script"
require_contains 'prompt_tokens_created=0' "$input_script"
require_contains 'runtime_invoked=0' "$input_script"
require_contains 'runtime_session_created=0' "$input_script"
require_contains 'qa_dialogue_generated=0' "$input_script"
require_contains 'sexual_request_refusal=always' "$input_script"
require_contains 'manipulation_resistance=required' "$input_script"
require_contains 'outside Nadia prompt-evaluation-input boundary' "$input_script"
require_not_contains 'curl ' "$input_script"
require_not_contains 'wget ' "$input_script"
require_not_contains 'ssh ' "$input_script"

require_contains 'prompt-evaluation-input' "$apply_script"
require_contains 'scripts/nadia-prompt-evaluation-input-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_input_contract_stage=28-prompt-evaluation-input-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-input' "$panel_ui"
require_contains 'latticra-nadia prompt-evaluation-input' "$installer_readme"
require_contains 'nadia prompt-evaluation-input' "$ui_model"
require_contains 'prompt-evaluation-input' "$components_manifest"
require_contains 'nadia-prompt-evaluation-input' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh' "$workflow"

stage27_guard_stdout="$tmpdir/latticra-nadia-stage28-stage27-guard.out"
sh "$stage27_guard" >"$stage27_guard_stdout"
require_contains 'nadia_context_window_assembly_contract_stage_27: ok' "$stage27_guard_stdout"

out="$tmpdir/latticra-nadia-stage28-prompt-evaluation-input-test"
context="$out/nadia-context-window-assembly-contract-stage27-fixture.txt"
input_stdout="$tmpdir/latticra-nadia-stage28-prompt-evaluation-input-test.out"
boundary_stdout="$tmpdir/latticra-nadia-stage28-boundary.out"
mkdir -p "$out"

cat > "$context" <<'EOF_CONTEXT'
NADIA CONTEXT WINDOW ASSEMBLY CONTRACT
stage=27-context-window-assembly-contract
context_window_assembly_contract_status=contract_only
context_window_assembly_stage=contract-only
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_performed=0
context_window_assembly_metadata_present=1
context_window_family=operator-reviewed-context-window-assembly
context_window_format=contract-only-offline-context-window
context_window_assembly_decision=blocked_contract_only
context_window_assembly_evidence_present=1
context_window_assembly_source_policy=operator-reviewed-offline
context_window_assembly_plan_recorded=1
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
tokenizer_runtime_attachment_stage=contract-only
tokenization_boundary_stage=contract-only
requires_prompt_token_sequence_contract=1
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
requires_future_prompt_evaluation_input_contract=1
context_window_assembly_promotion_allowed=0
requires_context_window_layout_policy=1
requires_context_window_token_budget_policy=1
requires_context_window_truncation_policy=1
requires_context_window_ordering_policy=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_prompt_evaluation_input_policy=1
requires_no_context_window_assembly=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
context_window_assembly_open_authority=0
context_window_assembly_read_authority=0
context_window_assembly_write_authority=0
context_window_assembly_execute_authority=0
context_window_assembly_runtime_authority=0
context_window_assembly_prompt_evaluation_input_authority=0
context_window_loaded=0
context_window_opened=0
context_window_read=0
context_window_validated=0
context_window_assembled=0
context_window_token_budget_recorded=0
context_window_entry_count_recorded=0
context_window_truncation_applied=0
context_window_serialized=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_written=0
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
prompt_attention_mask_created=0
prompt_position_ids_created=0
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
EOF_CONTEXT

require_file "$context"

NADIA_PROMPT_EVALUATION_INPUT_TIMESTAMP=stage28-test sh "$input_script" \
  --context-window-assembly "$context" \
  --request-class awareness-education \
  --input-family operator-reviewed-prompt-evaluation-input \
  --input-format contract-only-offline-evaluation-input \
  --output "$out" >"$input_stdout"
input="$out/nadia-prompt-evaluation-input-contract-stage28-test.txt"

require_file "$input"
require_file "$out/latest-prompt-evaluation-input-contract.txt"
require_contains 'NADIA PROMPT EVALUATION INPUT CONTRACT' "$input"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$input"
require_contains 'public_name=Nadia' "$input"
require_contains 'stage=28-prompt-evaluation-input-contract' "$input"
require_contains 'request_class=awareness-education' "$input"
require_contains 'prompt_evaluation_input_contract_status=contract_only' "$input"
require_contains 'prompt_evaluation_input_stage=contract-only' "$input"
require_contains 'prompt_evaluation_input_authority=0' "$input"
require_contains 'prompt_evaluation_input_allowed=0' "$input"
require_contains 'prompt_evaluation_input_created=0' "$input"
require_contains 'prompt_evaluation_input_metadata_present=1' "$input"
require_contains 'prompt_evaluation_input_family=operator-reviewed-prompt-evaluation-input' "$input"
require_contains 'prompt_evaluation_input_format=contract-only-offline-evaluation-input' "$input"
require_contains 'context_window_assembly_stage_required=27-context-window-assembly-contract' "$input"
require_contains 'prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh' "$input"
require_contains 'installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input' "$input"
require_contains 'prompt_evaluation_input_decision=blocked_contract_only' "$input"
require_contains 'prompt_evaluation_input_evidence_present=1' "$input"
require_contains 'prompt_evaluation_input_source_policy=operator-reviewed-offline' "$input"
require_contains 'prompt_evaluation_input_plan_recorded=1' "$input"
require_contains 'prompt_evaluation_input_method_planned=offline-prompt-evaluation-input-policy-review' "$input"
require_contains 'prompt_evaluation_input_result_recorded=0' "$input"
require_contains 'prompt_evaluation_input_runtime_invoked=0' "$input"
require_contains 'requires_context_window_assembly_contract=1' "$input"
require_contains 'requires_future_prompt_evaluation_runtime_handoff_contract=1' "$input"
require_contains 'prompt_evaluation_input_promotion_allowed=0' "$input"
require_contains 'requires_evaluation_input_schema_policy=1' "$input"
require_contains 'requires_evaluation_input_context_reference_policy=1' "$input"
require_contains 'requires_evaluation_input_token_sequence_reference_policy=1' "$input"
require_contains 'requires_evaluation_input_safety_envelope_policy=1' "$input"
require_contains 'requires_evaluation_input_runtime_denial_policy=1' "$input"
require_contains 'requires_no_prompt_evaluation_input_creation=1' "$input"
require_contains 'prompt_evaluation_input_runtime_handoff_authority=0' "$input"
require_contains 'prompt_evaluation_input_materialized=0' "$input"
require_contains 'prompt_evaluation_input_loaded=0' "$input"
require_contains 'prompt_evaluation_input_opened=0' "$input"
require_contains 'prompt_evaluation_input_read=0' "$input"
require_contains 'prompt_evaluation_input_validated=0' "$input"
require_contains 'prompt_evaluation_input_serialized=0' "$input"
require_contains 'prompt_evaluation_input_written=0' "$input"
require_contains 'prompt_evaluation_input_context_reference_recorded=0' "$input"
require_contains 'prompt_evaluation_input_token_reference_recorded=0' "$input"
require_contains 'prompt_evaluation_input_safety_envelope_recorded=0' "$input"
require_contains 'context_window_assembled=0' "$input"
require_contains 'context_window_serialized=0' "$input"
require_contains 'prompt_text_read=0' "$input"
require_contains 'prompt_text_received=0' "$input"
require_contains 'prompt_text_materialized=0' "$input"
require_contains 'prompt_tokens_created=0' "$input"
require_contains 'prompt_token_sequence_recorded=0' "$input"
require_contains 'prompt_token_ids_recorded=0' "$input"
require_contains 'prompt_attention_mask_created=0' "$input"
require_contains 'prompt_position_ids_created=0' "$input"
require_contains 'tokenizer_runtime_attachment_performed=0' "$input"
require_contains 'tokenizer_attached_to_runtime=0' "$input"
require_contains 'runtime_session_created=0' "$input"
require_contains 'runtime_invoked=0' "$input"
require_contains 'future_qa_dialogue_capability_planned=1' "$input"
require_contains 'qa_dialogue_generated=0' "$input"
require_contains 'sexual_request_refusal=always' "$input"
require_contains 'manipulation_resistance=required' "$input"
require_contains 'prompt_evaluated=0' "$input"
require_contains 'token_generation_performed=0' "$input"
require_contains 'inference_performed=0' "$input"
require_contains 'tool_execution_performed=0' "$input"
require_contains 'network_authority=0' "$input"

if sh "$input_script" \
  --context-window-assembly "$context" \
  --request-class sexual-content \
  --output "$out" >"$boundary_stdout" 2>&1; then
  printf 'nadia prompt evaluation input contract stage 28: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-input boundary' "$boundary_stdout"

printf 'nadia_prompt_evaluation_input_contract_stage_28: ok\n'
