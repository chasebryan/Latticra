#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer manifest contract stage 19: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer manifest contract stage 19: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer manifest contract stage 19: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage19_doc='docs/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md'
stage19_status='docs/status/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19_STATUS.md'
stage18_status='docs/status/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
manifest_script='scripts/nadia-tokenizer-manifest-contract.sh'
stage19_guard='scripts/test-nadia-tokenizer-manifest-contract-stage-19.sh'
stage18_guard='scripts/test-nadia-tokenizer-specification-contract-stage-18.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage19_doc"
require_file "$stage19_status"
require_file "$stage18_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$manifest_script"
require_file "$stage19_guard"
require_file "$stage18_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-19 implementation contract' "$stage19_doc"
require_contains 'tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh' "$stage19_doc"
require_contains 'installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest' "$stage19_doc"
require_contains 'tokenizer_manifest_contract_status=contract_only' "$stage19_doc"
require_contains 'tokenizer_manifest_authority=0' "$stage19_doc"
require_contains 'requires_future_tokenizer_artifact_inventory_contract=1' "$stage19_doc"
require_contains 'tokenizer_manifest_loaded=0' "$stage19_doc"
require_contains 'tokenizer_file_opened=0' "$stage19_doc"
require_contains 'prompt_tokenized=0' "$stage19_doc"
require_contains 'sh scripts/test-nadia-tokenizer-manifest-contract-stage-19.sh' "$stage19_doc"

require_contains 'Status: implementation status record' "$stage19_status"
require_contains 'nadia_stage_19_tokenizer_manifest_contract_present=1' "$stage19_status"
require_contains 'nadia_tokenizer_manifest_contract_generator_present=1' "$stage19_status"
require_contains 'tokenizer_manifest_contract_status=contract_only' "$stage19_status"
require_contains 'tokenizer_manifest_promotion_allowed=0' "$stage19_status"

require_contains 'Stage-19: Tokenizer Manifest Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-manifest-contract.sh' "$foundation"
require_contains 'Stage-20: Tokenizer Artifact Inventory Contract' "$foundation"
require_contains 'test-nadia-tokenizer-manifest-contract-stage-19.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer manifest contract Stage-19 + guardrails' "$foundation_index"
require_contains 'nadia_stage_19_tokenizer_manifest_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer manifest contract Stage-19 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer manifest contract Stage-19 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer manifest contract Stage-19' "$current_status"
require_contains 'Stage-19 now defines a tokenizer manifest contract' "$stage18_status"

require_contains 'NADIA TOKENIZER MANIFEST CONTRACT' "$manifest_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$manifest_script"
require_contains 'tokenizer_manifest_contract_status=contract_only' "$manifest_script"
require_contains 'requires_future_tokenizer_artifact_inventory_contract=1' "$manifest_script"
require_contains 'tokenizer_manifest_loaded=0' "$manifest_script"
require_contains 'tokenizer_manifest_opened=0' "$manifest_script"
require_contains 'tokenizer_manifest_parsed=0' "$manifest_script"
require_contains 'tokenizer_file_opened=0' "$manifest_script"
require_contains 'prompt_tokenized=0' "$manifest_script"
require_contains 'prompt_evaluated=0' "$manifest_script"
require_contains 'token_generation_performed=0' "$manifest_script"
require_contains 'inference_performed=0' "$manifest_script"
require_contains 'tool_execution_performed=0' "$manifest_script"
require_contains 'outside Nadia tokenizer-manifest boundary' "$manifest_script"
require_not_contains 'curl ' "$manifest_script"
require_not_contains 'wget ' "$manifest_script"
require_not_contains 'ssh ' "$manifest_script"

require_contains 'tokenizer-manifest' "$apply_script"
require_contains 'scripts/nadia-tokenizer-manifest-contract.sh' "$apply_script"
require_contains 'tokenizer_manifest_contract_stage=19-tokenizer-manifest-contract' "$panel_config"
require_contains 'nadia tokenizer-manifest' "$panel_ui"
require_contains 'latticra-nadia tokenizer-manifest' "$installer_readme"
require_contains 'nadia tokenizer-manifest' "$ui_model"
require_contains 'tokenizer-manifest' "$components_manifest"
require_contains 'nadia-tokenizer-manifest' "$makefile"

sh "$stage18_guard" >/tmp/latticra-nadia-stage19-prereq-stage18-test.out

out='/private/tmp/latticra-nadia-stage19-tokenizer-manifest-test'
tokenizer_spec='/private/tmp/latticra-nadia-stage18-tokenizer-test/nadia-tokenizer-specification-contract-stage18-test.txt'
rm -rf "$out"
mkdir -p "$out"

require_file "$tokenizer_spec"

NADIA_TOKENIZER_MANIFEST_TIMESTAMP=stage19-test sh "$manifest_script" \
  --tokenizer-specification "$tokenizer_spec" \
  --request-class awareness-education \
  --manifest-family operator-reviewed-tokenizer-manifest \
  --manifest-format contract-only-offline-manifest \
  --output "$out" >/tmp/latticra-nadia-stage19-tokenizer-manifest-test.out
manifest="$out/nadia-tokenizer-manifest-contract-stage19-test.txt"

require_file "$manifest"
require_file "$out/latest-tokenizer-manifest-contract.txt"
require_contains 'NADIA TOKENIZER MANIFEST CONTRACT' "$manifest"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$manifest"
require_contains 'public_name=Nadia' "$manifest"
require_contains 'stage=19-tokenizer-manifest-contract' "$manifest"
require_contains 'request_class=awareness-education' "$manifest"
require_contains 'tokenizer_manifest_contract_status=contract_only' "$manifest"
require_contains 'tokenizer_manifest_stage=contract-only' "$manifest"
require_contains 'tokenizer_manifest_authority=0' "$manifest"
require_contains 'tokenizer_manifest_allowed=0' "$manifest"
require_contains 'tokenizer_manifest_performed=0' "$manifest"
require_contains 'tokenizer_manifest_metadata_present=1' "$manifest"
require_contains 'tokenizer_manifest_family=operator-reviewed-tokenizer-manifest' "$manifest"
require_contains 'tokenizer_manifest_format=contract-only-offline-manifest' "$manifest"
require_contains 'tokenizer_manifest_decision=blocked_contract_only' "$manifest"
require_contains 'tokenizer_manifest_evidence_present=1' "$manifest"
require_contains 'tokenizer_manifest_source_policy=operator-reviewed-offline' "$manifest"
require_contains 'tokenizer_manifest_path_recorded=0' "$manifest"
require_contains 'tokenizer_manifest_schema_planned=1' "$manifest"
require_contains 'requires_tokenizer_specification_contract=1' "$manifest"
require_contains 'requires_tokenization_boundary_contract=1' "$manifest"
require_contains 'requires_prompt_evaluation_handoff_contract=1' "$manifest"
require_contains 'requires_awareness_dialogue_contract=1' "$manifest"
require_contains 'requires_prompt_materialization_contract=1' "$manifest"
require_contains 'requires_prompt_receipt_contract=1' "$manifest"
require_contains 'requires_prompt_buffer_boundary=1' "$manifest"
require_contains 'requires_protective_safety_boundary=1' "$manifest"
require_contains 'requires_operator_review=1' "$manifest"
require_contains 'requires_official_source_snapshot=1' "$manifest"
require_contains 'requires_future_tokenizer_artifact_inventory_contract=1' "$manifest"
require_contains 'tokenizer_manifest_promotion_allowed=0' "$manifest"
require_contains 'requires_manifest_identity=1' "$manifest"
require_contains 'requires_manifest_schema_review=1' "$manifest"
require_contains 'requires_model_tokenizer_compatibility_reference=1' "$manifest"
require_contains 'requires_tokenizer_file_inventory=1' "$manifest"
require_contains 'requires_vocabulary_file_entry=1' "$manifest"
require_contains 'requires_special_tokens_entry=1' "$manifest"
require_contains 'requires_chat_template_entry=1' "$manifest"
require_contains 'requires_unicode_policy_entry=1' "$manifest"
require_contains 'requires_normalization_policy_entry=1' "$manifest"
require_contains 'requires_context_window_entry=1' "$manifest"
require_contains 'requires_stop_sequence_entry=1' "$manifest"
require_contains 'requires_license_and_source_entry=1' "$manifest"
require_contains 'tokenizer_manifest_open_authority=0' "$manifest"
require_contains 'tokenizer_manifest_read_authority=0' "$manifest"
require_contains 'tokenizer_manifest_parse_authority=0' "$manifest"
require_contains 'tokenizer_manifest_validation_authority=0' "$manifest"
require_contains 'tokenizer_manifest_load_authority=0' "$manifest"
require_contains 'tokenizer_manifest_opened=0' "$manifest"
require_contains 'tokenizer_manifest_read=0' "$manifest"
require_contains 'tokenizer_manifest_parsed=0' "$manifest"
require_contains 'tokenizer_manifest_validated=0' "$manifest"
require_contains 'tokenizer_manifest_loaded=0' "$manifest"
require_contains 'tokenizer_manifest_bytes_read=0' "$manifest"
require_contains 'tokenizer_manifest_hash_computed=0' "$manifest"
require_contains 'tokenizer_manifest_entries_loaded=0' "$manifest"
require_contains 'tokenizer_file_path_resolved=0' "$manifest"
require_contains 'tokenizer_file_open_authority=0' "$manifest"
require_contains 'tokenizer_file_read_authority=0' "$manifest"
require_contains 'tokenizer_vocab_load_authority=0' "$manifest"
require_contains 'tokenizer_file_opened=0' "$manifest"
require_contains 'tokenizer_file_read=0' "$manifest"
require_contains 'tokenizer_vocab_loaded=0' "$manifest"
require_contains 'tokenizer_bytes_read=0' "$manifest"
require_contains 'tokenizer_hash_computed=0' "$manifest"
require_contains 'future_qa_dialogue_capability_planned=1' "$manifest"
require_contains 'qa_dialogue_generated=0' "$manifest"
require_contains 'question_generated=0' "$manifest"
require_contains 'answer_generated=0' "$manifest"
require_contains 'answer_text_generated=0' "$manifest"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$manifest"
require_contains 'q_and_a_format_required=1' "$manifest"
require_contains 'survivor_centered_dialogue_required=1' "$manifest"
require_contains 'official_source_grounding_required=1' "$manifest"
require_contains 'live_web_lookup_authority=0' "$manifest"
require_contains 'topic_yazidi_genocide_awareness=1' "$manifest"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$manifest"
require_contains 'topic_womens_empowerment=1' "$manifest"
require_contains 'sexualized_dialogue_generation=0' "$manifest"
require_contains 'graphic_sexual_detail_allowed=0' "$manifest"
require_contains 'victim_blaming_allowed=0' "$manifest"
require_contains 'genocide_denial_allowed=0' "$manifest"
require_contains 'medical_advice_authority=0' "$manifest"
require_contains 'legal_advice_authority=0' "$manifest"
require_contains 'trauma_counseling_authority=0' "$manifest"
require_contains 'sexual_request_refusal=always' "$manifest"
require_contains 'manipulation_resistance=required' "$manifest"
require_contains 'prompt_materialized=0' "$manifest"
require_contains 'prompt_text_materialized=0' "$manifest"
require_contains 'prompt_buffer_allocated=0' "$manifest"
require_contains 'prompt_buffer_written=0' "$manifest"
require_contains 'prompt_tokenization_authority=0' "$manifest"
require_contains 'prompt_tokenization_allowed=0' "$manifest"
require_contains 'prompt_tokenized=0' "$manifest"
require_contains 'prompt_tokens_created=0' "$manifest"
require_contains 'prompt_evaluation_authority=0' "$manifest"
require_contains 'prompt_evaluated=0' "$manifest"
require_contains 'token_generation_performed=0' "$manifest"
require_contains 'inference_performed=0' "$manifest"
require_contains 'tool_execution_performed=0' "$manifest"
require_contains 'network_authority=0' "$manifest"

if NADIA_TOKENIZER_MANIFEST_TIMESTAMP=stage19-reject sh "$manifest_script" \
  --tokenizer-specification "$tokenizer_spec" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage19-reject-test.out 2>/tmp/latticra-nadia-stage19-reject-test.err; then
  printf 'nadia tokenizer manifest contract stage 19: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-manifest boundary' /tmp/latticra-nadia-stage19-reject-test.err

printf 'nadia_tokenizer_manifest_contract_stage_19: ok\n'
