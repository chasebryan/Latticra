#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage29.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation runtime handoff contract stage 29: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation runtime handoff contract stage 29: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage29_doc='docs/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29.md'
stage29_status='docs/status/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29_STATUS.md'
stage28_status='docs/status/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
foundation_index='docs/FOUNDATION_INDEX.md'
status_index='docs/status/README.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
handoff_script='scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh'
stage29_guard='scripts/test-nadia-prompt-evaluation-runtime-handoff-contract-stage-29.sh'
workflow='.github/workflows/nadia-prompt-evaluation-runtime-handoff-contract-stage-29.yml'
makefile='Makefile'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'

require_file "$stage29_doc"
require_file "$stage29_status"
require_file "$stage28_status"
require_file "$foundation"
require_file "$foundation_index"
require_file "$status_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$handoff_script"
require_file "$stage29_guard"
require_file "$workflow"
require_file "$makefile"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"

require_contains 'Status: Stage-29 implementation contract' "$stage29_doc"
require_contains 'prompt_evaluation_runtime_handoff_contract_command=scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh' "$stage29_doc"
require_contains 'installed_prompt_evaluation_runtime_handoff_contract_command=latticra-nadia prompt-evaluation-runtime-handoff' "$stage29_doc"
require_contains 'prompt_evaluation_runtime_handoff_contract_status=contract_only' "$stage29_doc"
require_contains 'prompt_evaluation_runtime_handoff_authority=0' "$stage29_doc"
require_contains 'requires_prompt_evaluation_input_contract=1' "$stage29_doc"
require_contains 'requires_future_prompt_evaluation_invocation_contract=1' "$stage29_doc"
require_contains 'runtime_invoked=0' "$stage29_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-runtime-handoff-contract-stage-29.sh' "$stage29_doc"

require_contains 'Status: implementation status record' "$stage29_status"
require_contains 'nadia_stage_29_prompt_evaluation_runtime_handoff_contract_present=1' "$stage29_status"
require_contains 'nadia_prompt_evaluation_runtime_handoff_contract_generator_present=1' "$stage29_status"
require_contains 'prompt_evaluation_runtime_handoff_contract_status=contract_only' "$stage29_status"
require_contains 'prompt_evaluation_runtime_handoff_promotion_allowed=0' "$stage29_status"
require_contains 'prompt-evaluation invocation contract' "$stage29_status"

require_contains 'Stage-29: Prompt Evaluation Runtime Handoff Contract' "$foundation"
require_contains 'Stage-30: Prompt Evaluation Invocation Contract' "$foundation"
require_contains 'Stage-31: Prompt Evaluation Result Contract' "$foundation"
require_contains 'Before Stage-37 starts' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29_STATUS.md' "$status_index"
require_contains 'Nadia prompt evaluation runtime handoff contract Stage-29 + guardrails' "$foundation_index"
require_contains 'nadia_stage_29_prompt_evaluation_runtime_handoff_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt evaluation runtime handoff contract Stage-29 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation runtime handoff contract Stage-29 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt evaluation runtime handoff contract Stage-29' "$current_status"
require_contains 'Stage-29 now defines a prompt-evaluation runtime handoff contract' "$stage28_status"
require_contains 'nadia-prompt-evaluation-runtime-handoff' "$makefile"
require_contains 'sh ./scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-runtime-handoff-contract-stage-29.sh' "$workflow"

require_contains 'NADIA PROMPT EVALUATION RUNTIME HANDOFF CONTRACT' "$handoff_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$handoff_script"
require_contains 'prompt_evaluation_runtime_handoff_contract_status=contract_only' "$handoff_script"
require_contains 'requires_prompt_evaluation_input_contract=1' "$handoff_script"
require_contains 'requires_future_prompt_evaluation_invocation_contract=1' "$handoff_script"
require_contains 'prompt_evaluation_runtime_handoff_performed=0' "$handoff_script"
require_contains 'runtime_invoked=0' "$handoff_script"
require_contains 'prompt_evaluated=0' "$handoff_script"
require_contains 'token_generation_performed=0' "$handoff_script"
require_contains 'inference_performed=0' "$handoff_script"
require_contains 'outside Nadia prompt-evaluation-runtime-handoff boundary' "$handoff_script"

require_contains 'prompt-evaluation-runtime-handoff' "$apply_script"
require_contains 'scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_runtime_handoff_contract_stage=29-prompt-evaluation-runtime-handoff-contract' "$apply_script"
require_contains 'runtime_handoff_created=0' "$apply_script"
require_contains 'prompt_evaluation_runtime_handoff_contract_stage=29-prompt-evaluation-runtime-handoff-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-runtime-handoff' "$panel_ui"
require_contains 'nadia_prompt_evaluation_runtime_handoff=stage-29-prompt-evaluation-runtime-handoff-contract' "$panel_ui"
require_contains 'latticra-nadia prompt-evaluation-runtime-handoff' "$installer_readme"
require_contains 'nadia prompt-evaluation-runtime-handoff' "$ui_model"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, and Stage-36 console surfaces are metadata-only' "$ui_model"
require_contains 'prompt-evaluation-runtime-handoff' "$components_manifest"
require_contains 'prompt-evaluation runtime handoff metadata records future prompt evaluation invocation requirements' "$components_manifest"
require_contains 'Stage-30 now defines a prompt-evaluation invocation contract' "$stage29_status"

out="$tmpdir/latticra-nadia-stage29-runtime-handoff-test"
input="$out/prompt-evaluation-input-stage28-fixture.txt"
handoff_stdout="$tmpdir/latticra-nadia-stage29-runtime-handoff-test.out"
boundary_stdout="$tmpdir/latticra-nadia-stage29-boundary.out"
mkdir -p "$out"

cat > "$input" <<'EOF_INPUT'
NADIA PROMPT EVALUATION INPUT CONTRACT
stage=28-prompt-evaluation-input-contract
prompt_evaluation_input_contract_status=contract_only
prompt_evaluation_input_stage=contract-only
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_metadata_present=1
prompt_evaluation_input_family=operator-reviewed-prompt-evaluation-input
prompt_evaluation_input_format=contract-only-offline-evaluation-input
prompt_evaluation_input_decision=blocked_contract_only
prompt_evaluation_input_evidence_present=1
prompt_evaluation_input_source_policy=operator-reviewed-offline
prompt_evaluation_input_plan_recorded=1
prompt_evaluation_input_result_recorded=0
prompt_evaluation_input_runtime_invoked=0
requires_context_window_assembly_contract=1
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
requires_future_prompt_evaluation_runtime_handoff_contract=1
prompt_evaluation_input_promotion_allowed=0
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_evaluation_input_schema_policy=1
requires_evaluation_input_context_reference_policy=1
requires_evaluation_input_token_sequence_reference_policy=1
requires_evaluation_input_safety_envelope_policy=1
requires_evaluation_input_runtime_denial_policy=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
prompt_evaluation_input_open_authority=0
prompt_evaluation_input_read_authority=0
prompt_evaluation_input_write_authority=0
prompt_evaluation_input_execute_authority=0
prompt_evaluation_input_runtime_authority=0
prompt_evaluation_input_runtime_handoff_authority=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
prompt_evaluation_input_schema_validated=0
prompt_evaluation_input_context_reference_recorded=0
prompt_evaluation_input_token_reference_recorded=0
prompt_evaluation_input_safety_envelope_recorded=0
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
tokenizer_runtime_attachment_stage=contract-only
context_window_assembled=0
context_window_serialized=0
prompt_token_sequence_recorded=0
prompt_token_ids_recorded=0
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
EOF_INPUT

NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_TIMESTAMP=stage29-test sh "$handoff_script" \
  --prompt-evaluation-input "$input" \
  --request-class awareness-education \
  --handoff-family operator-reviewed-prompt-evaluation-runtime-handoff \
  --handoff-format contract-only-offline-runtime-handoff \
  --output "$out" >"$handoff_stdout"

report="$out/nadia-prompt-evaluation-runtime-handoff-contract-stage29-test.txt"
require_file "$report"
require_file "$out/latest-prompt-evaluation-runtime-handoff-contract.txt"
require_contains 'NADIA PROMPT EVALUATION RUNTIME HANDOFF CONTRACT' "$report"
require_contains 'stage=29-prompt-evaluation-runtime-handoff-contract' "$report"
require_contains 'prompt_evaluation_runtime_handoff_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_runtime_handoff_authority=0' "$report"
require_contains 'prompt_evaluation_runtime_handoff_performed=0' "$report"
require_contains 'requires_prompt_evaluation_input_contract=1' "$report"
require_contains 'requires_future_prompt_evaluation_invocation_contract=1' "$report"
require_contains 'prompt_evaluation_runtime_handoff_promotion_allowed=0' "$report"
require_contains 'prompt_evaluation_runtime_handoff_request_created=0' "$report"
require_contains 'prompt_evaluation_runtime_handoff_request_submitted=0' "$report"
require_contains 'runtime_handoff_created=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'runtime_session_created=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'qa_dialogue_generated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

if sh "$handoff_script" \
  --prompt-evaluation-input "$input" \
  --request-class sexual-content \
  --output "$out" >"$boundary_stdout" 2>&1; then
  printf 'nadia prompt evaluation runtime handoff contract stage 29: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-runtime-handoff boundary' "$boundary_stdout"

printf 'nadia_prompt_evaluation_runtime_handoff_contract_stage_29: ok\n'
