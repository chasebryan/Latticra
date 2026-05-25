#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt tokenization contract stage 25: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt tokenization contract stage 25: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt tokenization contract stage 25: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage25_doc='docs/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25.md'
stage25_status='docs/status/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25_STATUS.md'
stage24_status='docs/status/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
tokenization_script='scripts/nadia-prompt-tokenization-contract.sh'
stage25_guard='scripts/test-nadia-prompt-tokenization-contract-stage-25.sh'
stage24_guard='scripts/test-nadia-tokenizer-runtime-attachment-contract-stage-24.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage25_doc"
require_file "$stage25_status"
require_file "$stage24_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$tokenization_script"
require_file "$stage25_guard"
require_file "$stage24_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-25 implementation contract' "$stage25_doc"
require_contains 'prompt_tokenization_contract_command=scripts/nadia-prompt-tokenization-contract.sh' "$stage25_doc"
require_contains 'installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization' "$stage25_doc"
require_contains 'prompt_tokenization_contract_status=contract_only' "$stage25_doc"
require_contains 'prompt_tokenization_authority=0' "$stage25_doc"
require_contains 'requires_tokenizer_runtime_attachment_contract=1' "$stage25_doc"
require_contains 'requires_future_prompt_token_sequence_contract=1' "$stage25_doc"
require_contains 'prompt_tokens_created=0' "$stage25_doc"
require_contains 'prompt_token_count_recorded=0' "$stage25_doc"
require_contains 'prompt_token_sequence_recorded=0' "$stage25_doc"
require_contains 'runtime_invoked=0' "$stage25_doc"
require_contains 'sh scripts/test-nadia-prompt-tokenization-contract-stage-25.sh' "$stage25_doc"

require_contains 'Status: implementation status record' "$stage25_status"
require_contains 'nadia_stage_25_prompt_tokenization_contract_present=1' "$stage25_status"
require_contains 'nadia_prompt_tokenization_contract_generator_present=1' "$stage25_status"
require_contains 'prompt_tokenization_contract_status=contract_only' "$stage25_status"
require_contains 'prompt_tokenization_promotion_allowed=0' "$stage25_status"

require_contains 'Stage-25: Prompt Tokenization Contract' "$foundation"
require_contains 'scripts/nadia-prompt-tokenization-contract.sh' "$foundation"
require_contains 'Stage-26: Prompt Token Sequence Contract' "$foundation"
require_contains 'test-nadia-prompt-tokenization-contract-stage-25.sh' "$foundation"
require_contains 'NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25.md' "$foundation_index"
require_contains 'NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25_STATUS.md' "$status_index"
require_contains 'Nadia prompt tokenization contract Stage-25 + guardrails' "$foundation_index"
require_contains 'nadia_stage_25_prompt_tokenization_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt tokenization contract Stage-25 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt tokenization contract Stage-25 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt tokenization contract Stage-25' "$current_status"
require_contains 'Stage-25 now defines a prompt-tokenization contract' "$stage24_status"

require_contains 'NADIA PROMPT TOKENIZATION CONTRACT' "$tokenization_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenization_script"
require_contains 'prompt_tokenization_contract_status=contract_only' "$tokenization_script"
require_contains 'requires_tokenizer_runtime_attachment_contract=1' "$tokenization_script"
require_contains 'requires_future_prompt_token_sequence_contract=1' "$tokenization_script"
require_contains 'prompt_tokenization_plan_recorded=1' "$tokenization_script"
require_contains 'prompt_tokenization_performed=0' "$tokenization_script"
require_contains 'prompt_tokenization_token_count_recorded=0' "$tokenization_script"
require_contains 'prompt_tokenization_token_sequence_recorded=0' "$tokenization_script"
require_contains 'prompt_tokenization_runtime_invoked=0' "$tokenization_script"
require_contains 'prompt_tokens_created=0' "$tokenization_script"
require_contains 'prompt_token_count_recorded=0' "$tokenization_script"
require_contains 'prompt_token_sequence_recorded=0' "$tokenization_script"
require_contains 'prompt_token_buffer_created=0' "$tokenization_script"
require_contains 'prompt_tokenized=0' "$tokenization_script"
require_contains 'prompt_text_read=0' "$tokenization_script"
require_contains 'prompt_text_received=0' "$tokenization_script"
require_contains 'prompt_text_materialized=0' "$tokenization_script"
require_contains 'tokenizer_runtime_attachment_performed=0' "$tokenization_script"
require_contains 'tokenizer_attached_to_runtime=0' "$tokenization_script"
require_contains 'runtime_invoked=0' "$tokenization_script"
require_contains 'runtime_session_created=0' "$tokenization_script"
require_contains 'tokenizer_artifact_binding_performed=0' "$tokenization_script"
require_contains 'tokenizer_artifact_file_opened=0' "$tokenization_script"
require_contains 'tokenizer_artifact_file_read=0' "$tokenization_script"
require_contains 'tokenizer_manifest_loaded=0' "$tokenization_script"
require_contains 'tokenizer_manifest_parsed=0' "$tokenization_script"
require_contains 'tokenizer_file_opened=0' "$tokenization_script"
require_contains 'tokenizer_vocab_loaded=0' "$tokenization_script"
require_contains 'qa_dialogue_generated=0' "$tokenization_script"
require_contains 'sexual_request_refusal=always' "$tokenization_script"
require_contains 'manipulation_resistance=required' "$tokenization_script"
require_contains 'inference_performed=0' "$tokenization_script"
require_contains 'outside Nadia prompt-tokenization boundary' "$tokenization_script"
require_not_contains 'curl ' "$tokenization_script"
require_not_contains 'wget ' "$tokenization_script"
require_not_contains 'ssh ' "$tokenization_script"

require_contains 'prompt-tokenization' "$apply_script"
require_contains 'scripts/nadia-prompt-tokenization-contract.sh' "$apply_script"
require_contains 'prompt_tokenization_contract_stage=25-prompt-tokenization-contract' "$panel_config"
require_contains 'nadia prompt-tokenization' "$panel_ui"
require_contains 'latticra-nadia prompt-tokenization' "$installer_readme"
require_contains 'nadia prompt-tokenization' "$ui_model"
require_contains 'prompt-tokenization' "$components_manifest"
require_contains 'nadia-prompt-tokenization' "$makefile"

sh "$stage24_guard" >/tmp/latticra-nadia-stage25-prereq-stage24-test.out

out='/private/tmp/latticra-nadia-stage25-prompt-tokenization-test'
attachment='/private/tmp/latticra-nadia-stage24-tokenizer-runtime-attachment-test/nadia-tokenizer-runtime-attachment-contract-stage24-test.txt'
rm -rf "$out"
mkdir -p "$out"

require_file "$attachment"

NADIA_PROMPT_TOKENIZATION_TIMESTAMP=stage25-test sh "$tokenization_script" \
  --tokenizer-runtime-attachment "$attachment" \
  --request-class awareness-education \
  --tokenization-family operator-reviewed-prompt-tokenization \
  --tokenization-format contract-only-offline-tokenization \
  --output "$out" >/tmp/latticra-nadia-stage25-prompt-tokenization-test.out
tokenization="$out/nadia-prompt-tokenization-contract-stage25-test.txt"

require_file "$tokenization"
require_file "$out/latest-prompt-tokenization-contract.txt"
require_contains 'NADIA PROMPT TOKENIZATION CONTRACT' "$tokenization"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenization"
require_contains 'public_name=Nadia' "$tokenization"
require_contains 'stage=25-prompt-tokenization-contract' "$tokenization"
require_contains 'request_class=awareness-education' "$tokenization"
require_contains 'prompt_tokenization_contract_status=contract_only' "$tokenization"
require_contains 'prompt_tokenization_stage=contract-only' "$tokenization"
require_contains 'prompt_tokenization_authority=0' "$tokenization"
require_contains 'prompt_tokenization_allowed=0' "$tokenization"
require_contains 'prompt_tokenization_performed=0' "$tokenization"
require_contains 'prompt_tokenization_metadata_present=1' "$tokenization"
require_contains 'prompt_tokenization_family=operator-reviewed-prompt-tokenization' "$tokenization"
require_contains 'prompt_tokenization_format=contract-only-offline-tokenization' "$tokenization"
require_contains 'prompt_tokenization_loaded=0' "$tokenization"
require_contains 'prompt_tokenization_opened=0' "$tokenization"
require_contains 'prompt_tokenization_read=0' "$tokenization"
require_contains 'prompt_tokenization_validated=0' "$tokenization"
require_contains 'prompt_text_read=0' "$tokenization"
require_contains 'prompt_text_received=0' "$tokenization"
require_contains 'prompt_text_materialized=0' "$tokenization"
require_contains 'prompt_buffer_allocated=0' "$tokenization"
require_contains 'prompt_buffer_written=0' "$tokenization"
require_contains 'prompt_tokenized=0' "$tokenization"
require_contains 'prompt_tokens_created=0' "$tokenization"
require_contains 'prompt_token_count_recorded=0' "$tokenization"
require_contains 'prompt_token_sequence_recorded=0' "$tokenization"
require_contains 'prompt_token_buffer_created=0' "$tokenization"
require_contains 'prompt_token_buffer_written=0' "$tokenization"
require_contains 'tokenizer_runtime_attachment_stage_required=24-tokenizer-runtime-attachment-contract' "$tokenization"
require_contains 'prompt_tokenization_contract_command=scripts/nadia-prompt-tokenization-contract.sh' "$tokenization"
require_contains 'installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization' "$tokenization"
require_contains 'prompt_tokenization_decision=blocked_contract_only' "$tokenization"
require_contains 'prompt_tokenization_evidence_present=1' "$tokenization"
require_contains 'prompt_tokenization_source_policy=operator-reviewed-offline' "$tokenization"
require_contains 'prompt_tokenization_plan_recorded=1' "$tokenization"
require_contains 'prompt_tokenization_method_planned=offline-tokenization-policy-review' "$tokenization"
require_contains 'prompt_tokenization_result_recorded=0' "$tokenization"
require_contains 'prompt_tokenization_token_count_recorded=0' "$tokenization"
require_contains 'prompt_tokenization_token_sequence_recorded=0' "$tokenization"
require_contains 'prompt_tokenization_runtime_invoked=0' "$tokenization"
require_contains 'requires_tokenizer_runtime_attachment_contract=1' "$tokenization"
require_contains 'requires_tokenizer_artifact_binding_contract=1' "$tokenization"
require_contains 'requires_tokenizer_artifact_verification_contract=1' "$tokenization"
require_contains 'requires_tokenizer_artifact_measurement_contract=1' "$tokenization"
require_contains 'requires_tokenizer_artifact_inventory_contract=1' "$tokenization"
require_contains 'requires_tokenizer_manifest_contract=1' "$tokenization"
require_contains 'requires_tokenizer_specification_contract=1' "$tokenization"
require_contains 'requires_tokenization_boundary_contract=1' "$tokenization"
require_contains 'requires_prompt_materialization_contract=1' "$tokenization"
require_contains 'requires_prompt_receipt_contract=1' "$tokenization"
require_contains 'requires_future_prompt_token_sequence_contract=1' "$tokenization"
require_contains 'prompt_tokenization_promotion_allowed=0' "$tokenization"
require_contains 'requires_tokenizer_runtime_attachment_reference=1' "$tokenization"
require_contains 'requires_prompt_materialization_reference=1' "$tokenization"
require_contains 'requires_prompt_receipt_reference=1' "$tokenization"
require_contains 'requires_tokenization_policy=1' "$tokenization"
require_contains 'requires_token_count_policy=1' "$tokenization"
require_contains 'requires_token_sequence_policy=1' "$tokenization"
require_contains 'requires_no_prompt_text_read=1' "$tokenization"
require_contains 'requires_no_prompt_token_creation=1' "$tokenization"
require_contains 'requires_no_prompt_token_sequence_recording=1' "$tokenization"
require_contains 'prompt_tokenization_open_authority=0' "$tokenization"
require_contains 'prompt_tokenization_read_authority=0' "$tokenization"
require_contains 'prompt_tokenization_write_authority=0' "$tokenization"
require_contains 'prompt_tokenization_execute_authority=0' "$tokenization"
require_contains 'prompt_tokenization_runtime_authority=0' "$tokenization"
require_contains 'prompt_tokenization_token_create_authority=0' "$tokenization"
require_contains 'prompt_tokenization_sequence_record_authority=0' "$tokenization"
require_contains 'prompt_tokenization_bytes_read=0' "$tokenization"
require_contains 'prompt_tokenization_hash_computed=0' "$tokenization"
require_contains 'prompt_tokenization_entries_loaded=0' "$tokenization"
require_contains 'prompt_tokenization_file_written=0' "$tokenization"
require_contains 'tokenizer_runtime_attachment_performed=0' "$tokenization"
require_contains 'tokenizer_runtime_attachment_attached=0' "$tokenization"
require_contains 'tokenizer_attached_to_runtime=0' "$tokenization"
require_contains 'runtime_tokenizer_attachment_performed=0' "$tokenization"
require_contains 'runtime_session_created=0' "$tokenization"
require_contains 'runtime_invoked=0' "$tokenization"
require_contains 'runtime_process_spawned=0' "$tokenization"
require_contains 'runtime_binary_executed=0' "$tokenization"
require_contains 'tokenizer_artifact_binding_performed=0' "$tokenization"
require_contains 'tokenizer_artifact_binding_hash_computed=0' "$tokenization"
require_contains 'tokenizer_artifact_file_opened=0' "$tokenization"
require_contains 'tokenizer_artifact_file_read=0' "$tokenization"
require_contains 'tokenizer_artifact_hash_computed=0' "$tokenization"
require_contains 'tokenizer_manifest_loaded=0' "$tokenization"
require_contains 'tokenizer_manifest_parsed=0' "$tokenization"
require_contains 'tokenizer_file_opened=0' "$tokenization"
require_contains 'tokenizer_file_read=0' "$tokenization"
require_contains 'tokenizer_vocab_loaded=0' "$tokenization"
require_contains 'future_qa_dialogue_capability_planned=1' "$tokenization"
require_contains 'qa_dialogue_generated=0' "$tokenization"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$tokenization"
require_contains 'q_and_a_format_required=1' "$tokenization"
require_contains 'survivor_centered_dialogue_required=1' "$tokenization"
require_contains 'official_source_grounding_required=1' "$tokenization"
require_contains 'live_web_lookup_authority=0' "$tokenization"
require_contains 'topic_yazidi_genocide_awareness=1' "$tokenization"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$tokenization"
require_contains 'topic_womens_empowerment=1' "$tokenization"
require_contains 'sexualized_dialogue_generation=0' "$tokenization"
require_contains 'graphic_sexual_detail_allowed=0' "$tokenization"
require_contains 'victim_blaming_allowed=0' "$tokenization"
require_contains 'genocide_denial_allowed=0' "$tokenization"
require_contains 'sexual_request_refusal=always' "$tokenization"
require_contains 'manipulation_resistance=required' "$tokenization"
require_contains 'prompt_evaluated=0' "$tokenization"
require_contains 'token_generation_performed=0' "$tokenization"
require_contains 'inference_performed=0' "$tokenization"
require_contains 'tool_execution_performed=0' "$tokenization"
require_contains 'network_authority=0' "$tokenization"

if NADIA_PROMPT_TOKENIZATION_TIMESTAMP=stage25-reject sh "$tokenization_script" \
  --tokenizer-runtime-attachment "$attachment" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage25-reject-test.out 2>/tmp/latticra-nadia-stage25-reject-test.err; then
  printf 'nadia prompt tokenization contract stage 25: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-tokenization boundary' /tmp/latticra-nadia-stage25-reject-test.err

printf 'nadia_prompt_tokenization_contract_stage_25: ok\n'
