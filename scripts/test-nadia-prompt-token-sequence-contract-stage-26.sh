#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt token sequence contract stage 26: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt token sequence contract stage 26: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt token sequence contract stage 26: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage26_doc='docs/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26.md'
stage26_status='docs/status/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26_STATUS.md'
stage25_status='docs/status/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
sequence_script='scripts/nadia-prompt-token-sequence-contract.sh'
stage26_guard='scripts/test-nadia-prompt-token-sequence-contract-stage-26.sh'
stage25_guard='scripts/test-nadia-prompt-tokenization-contract-stage-25.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage26_doc"
require_file "$stage26_status"
require_file "$stage25_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$sequence_script"
require_file "$stage26_guard"
require_file "$stage25_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-26 implementation contract' "$stage26_doc"
require_contains 'prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh' "$stage26_doc"
require_contains 'installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence' "$stage26_doc"
require_contains 'prompt_token_sequence_contract_status=contract_only' "$stage26_doc"
require_contains 'prompt_token_sequence_authority=0' "$stage26_doc"
require_contains 'requires_prompt_tokenization_contract=1' "$stage26_doc"
require_contains 'requires_future_context_window_assembly_contract=1' "$stage26_doc"
require_contains 'prompt_token_ids_recorded=0' "$stage26_doc"
require_contains 'prompt_attention_mask_created=0' "$stage26_doc"
require_contains 'context_window_assembled=0' "$stage26_doc"
require_contains 'prompt_evaluation_input_created=0' "$stage26_doc"
require_contains 'runtime_invoked=0' "$stage26_doc"
require_contains 'sh scripts/test-nadia-prompt-token-sequence-contract-stage-26.sh' "$stage26_doc"

require_contains 'Status: implementation status record' "$stage26_status"
require_contains 'nadia_stage_26_prompt_token_sequence_contract_present=1' "$stage26_status"
require_contains 'nadia_prompt_token_sequence_contract_generator_present=1' "$stage26_status"
require_contains 'prompt_token_sequence_contract_status=contract_only' "$stage26_status"
require_contains 'prompt_token_sequence_promotion_allowed=0' "$stage26_status"
require_contains 'context window assembly contract' "$stage26_status"

require_contains 'Stage-26: Prompt Token Sequence Contract' "$foundation"
require_contains 'Stage-27: Context Window Assembly Contract' "$foundation"
require_contains 'scripts/nadia-prompt-token-sequence-contract.sh' "$foundation"
require_contains 'test-nadia-prompt-token-sequence-contract-stage-26.sh' "$foundation"
require_contains 'Before Stage-27 starts' "$foundation"
require_contains 'Before context window assembly starts' "$foundation"
require_contains 'NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26.md' "$foundation_index"
require_contains 'NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26_STATUS.md' "$status_index"
require_contains 'Nadia prompt token sequence contract Stage-26 + guardrails' "$foundation_index"
require_contains 'nadia_stage_26_prompt_token_sequence_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt token sequence contract Stage-26 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt token sequence contract Stage-26 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt token sequence contract Stage-26' "$current_status"
require_contains 'Stage-26 now defines a prompt-token-sequence contract' "$stage25_status"

require_contains 'NADIA PROMPT TOKEN SEQUENCE CONTRACT' "$sequence_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$sequence_script"
require_contains 'prompt_token_sequence_contract_status=contract_only' "$sequence_script"
require_contains 'requires_prompt_tokenization_contract=1' "$sequence_script"
require_contains 'requires_future_context_window_assembly_contract=1' "$sequence_script"
require_contains 'prompt_token_sequence_plan_recorded=1' "$sequence_script"
require_contains 'prompt_token_sequence_recorded=0' "$sequence_script"
require_contains 'prompt_token_sequence_count_recorded=0' "$sequence_script"
require_contains 'prompt_token_sequence_order_recorded=0' "$sequence_script"
require_contains 'prompt_token_ids_recorded=0' "$sequence_script"
require_contains 'prompt_token_order_recorded=0' "$sequence_script"
require_contains 'prompt_token_offsets_recorded=0' "$sequence_script"
require_contains 'prompt_attention_mask_created=0' "$sequence_script"
require_contains 'prompt_position_ids_created=0' "$sequence_script"
require_contains 'context_window_assembled=0' "$sequence_script"
require_contains 'prompt_evaluation_input_created=0' "$sequence_script"
require_contains 'prompt_text_read=0' "$sequence_script"
require_contains 'prompt_tokens_created=0' "$sequence_script"
require_contains 'prompt_token_count_recorded=0' "$sequence_script"
require_contains 'prompt_token_sequence_recorded=0' "$sequence_script"
require_contains 'prompt_tokenized=0' "$sequence_script"
require_contains 'runtime_invoked=0' "$sequence_script"
require_contains 'runtime_session_created=0' "$sequence_script"
require_contains 'qa_dialogue_generated=0' "$sequence_script"
require_contains 'sexual_request_refusal=always' "$sequence_script"
require_contains 'manipulation_resistance=required' "$sequence_script"
require_contains 'outside Nadia prompt-token-sequence boundary' "$sequence_script"
require_not_contains 'curl ' "$sequence_script"
require_not_contains 'wget ' "$sequence_script"
require_not_contains 'ssh ' "$sequence_script"

require_contains 'prompt-token-sequence' "$apply_script"
require_contains 'scripts/nadia-prompt-token-sequence-contract.sh' "$apply_script"
require_contains 'prompt_token_sequence_contract_stage=26-prompt-token-sequence-contract' "$panel_config"
require_contains 'nadia prompt-token-sequence' "$panel_ui"
require_contains 'latticra-nadia prompt-token-sequence' "$installer_readme"
require_contains 'nadia prompt-token-sequence' "$ui_model"
require_contains 'prompt-token-sequence' "$components_manifest"
require_contains 'nadia-prompt-token-sequence' "$makefile"

sh "$stage25_guard" >/tmp/latticra-nadia-stage26-prereq-stage25-test.out

out='/private/tmp/latticra-nadia-stage26-prompt-token-sequence-test'
tokenization='/private/tmp/latticra-nadia-stage25-prompt-tokenization-test/nadia-prompt-tokenization-contract-stage25-test.txt'
rm -rf "$out"
mkdir -p "$out"

require_file "$tokenization"

NADIA_PROMPT_TOKEN_SEQUENCE_TIMESTAMP=stage26-test sh "$sequence_script" \
  --prompt-tokenization "$tokenization" \
  --request-class awareness-education \
  --sequence-family operator-reviewed-prompt-token-sequence \
  --sequence-format contract-only-offline-sequence \
  --output "$out" >/tmp/latticra-nadia-stage26-prompt-token-sequence-test.out
sequence="$out/nadia-prompt-token-sequence-contract-stage26-test.txt"

require_file "$sequence"
require_file "$out/latest-prompt-token-sequence-contract.txt"
require_contains 'NADIA PROMPT TOKEN SEQUENCE CONTRACT' "$sequence"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$sequence"
require_contains 'public_name=Nadia' "$sequence"
require_contains 'stage=26-prompt-token-sequence-contract' "$sequence"
require_contains 'request_class=awareness-education' "$sequence"
require_contains 'prompt_token_sequence_contract_status=contract_only' "$sequence"
require_contains 'prompt_token_sequence_stage=contract-only' "$sequence"
require_contains 'prompt_token_sequence_authority=0' "$sequence"
require_contains 'prompt_token_sequence_allowed=0' "$sequence"
require_contains 'prompt_token_sequence_recorded=0' "$sequence"
require_contains 'prompt_token_sequence_metadata_present=1' "$sequence"
require_contains 'prompt_token_sequence_family=operator-reviewed-prompt-token-sequence' "$sequence"
require_contains 'prompt_token_sequence_format=contract-only-offline-sequence' "$sequence"
require_contains 'prompt_tokenization_stage_required=25-prompt-tokenization-contract' "$sequence"
require_contains 'prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh' "$sequence"
require_contains 'installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence' "$sequence"
require_contains 'prompt_token_sequence_decision=blocked_contract_only' "$sequence"
require_contains 'prompt_token_sequence_evidence_present=1' "$sequence"
require_contains 'prompt_token_sequence_source_policy=operator-reviewed-offline' "$sequence"
require_contains 'prompt_token_sequence_plan_recorded=1' "$sequence"
require_contains 'prompt_token_sequence_method_planned=offline-token-sequence-policy-review' "$sequence"
require_contains 'prompt_token_sequence_result_recorded=0' "$sequence"
require_contains 'prompt_token_sequence_count_recorded=0' "$sequence"
require_contains 'prompt_token_sequence_order_recorded=0' "$sequence"
require_contains 'prompt_token_sequence_runtime_invoked=0' "$sequence"
require_contains 'requires_prompt_tokenization_contract=1' "$sequence"
require_contains 'requires_future_context_window_assembly_contract=1' "$sequence"
require_contains 'prompt_token_sequence_promotion_allowed=0' "$sequence"
require_contains 'requires_prompt_tokenization_reference=1' "$sequence"
require_contains 'requires_prompt_tokenization_contract_reference=1' "$sequence"
require_contains 'requires_prompt_token_count_policy=1' "$sequence"
require_contains 'requires_prompt_token_order_policy=1' "$sequence"
require_contains 'requires_prompt_token_id_visibility_policy=1' "$sequence"
require_contains 'requires_prompt_token_offset_policy=1' "$sequence"
require_contains 'requires_context_window_policy=1' "$sequence"
require_contains 'requires_no_prompt_token_ids_recorded=1' "$sequence"
require_contains 'requires_no_attention_mask_creation=1' "$sequence"
require_contains 'requires_no_context_window_assembly=1' "$sequence"
require_contains 'prompt_token_sequence_token_id_record_authority=0' "$sequence"
require_contains 'prompt_token_sequence_context_window_authority=0' "$sequence"
require_contains 'prompt_token_ids_recorded=0' "$sequence"
require_contains 'prompt_token_order_recorded=0' "$sequence"
require_contains 'prompt_token_offsets_recorded=0' "$sequence"
require_contains 'prompt_token_byte_offsets_recorded=0' "$sequence"
require_contains 'prompt_attention_mask_created=0' "$sequence"
require_contains 'prompt_position_ids_created=0' "$sequence"
require_contains 'context_window_assembled=0' "$sequence"
require_contains 'prompt_evaluation_input_created=0' "$sequence"
require_contains 'prompt_text_read=0' "$sequence"
require_contains 'prompt_text_received=0' "$sequence"
require_contains 'prompt_text_materialized=0' "$sequence"
require_contains 'prompt_tokens_created=0' "$sequence"
require_contains 'prompt_token_count_recorded=0' "$sequence"
require_contains 'prompt_token_sequence_recorded=0' "$sequence"
require_contains 'prompt_token_buffer_created=0' "$sequence"
require_contains 'prompt_tokenized=0' "$sequence"
require_contains 'tokenizer_runtime_attachment_performed=0' "$sequence"
require_contains 'tokenizer_attached_to_runtime=0' "$sequence"
require_contains 'runtime_session_created=0' "$sequence"
require_contains 'runtime_invoked=0' "$sequence"
require_contains 'tokenizer_artifact_binding_performed=0' "$sequence"
require_contains 'tokenizer_artifact_file_opened=0' "$sequence"
require_contains 'tokenizer_artifact_file_read=0' "$sequence"
require_contains 'tokenizer_manifest_loaded=0' "$sequence"
require_contains 'tokenizer_manifest_parsed=0' "$sequence"
require_contains 'tokenizer_file_opened=0' "$sequence"
require_contains 'tokenizer_vocab_loaded=0' "$sequence"
require_contains 'future_qa_dialogue_capability_planned=1' "$sequence"
require_contains 'qa_dialogue_generated=0' "$sequence"
require_contains 'sexual_request_refusal=always' "$sequence"
require_contains 'manipulation_resistance=required' "$sequence"
require_contains 'prompt_evaluated=0' "$sequence"
require_contains 'token_generation_performed=0' "$sequence"
require_contains 'inference_performed=0' "$sequence"
require_contains 'tool_execution_performed=0' "$sequence"
require_contains 'network_authority=0' "$sequence"

if sh "$sequence_script" \
  --prompt-tokenization "$tokenization" \
  --request-class sexual-content \
  --output "$out" >/tmp/latticra-nadia-stage26-boundary.out 2>&1; then
  printf 'nadia prompt token sequence contract stage 26: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-token-sequence boundary' /tmp/latticra-nadia-stage26-boundary.out

printf 'nadia_prompt_token_sequence_contract_stage_26: ok\n'
