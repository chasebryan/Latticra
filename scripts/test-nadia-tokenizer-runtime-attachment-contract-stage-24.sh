#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer runtime attachment contract stage 24: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer runtime attachment contract stage 24: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer runtime attachment contract stage 24: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage24_doc='docs/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24.md'
stage24_status='docs/status/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24_STATUS.md'
stage23_status='docs/status/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
attachment_script='scripts/nadia-tokenizer-runtime-attachment-contract.sh'
stage24_guard='scripts/test-nadia-tokenizer-runtime-attachment-contract-stage-24.sh'
stage23_guard='scripts/test-nadia-tokenizer-artifact-binding-contract-stage-23.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage24_doc"
require_file "$stage24_status"
require_file "$stage23_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$attachment_script"
require_file "$stage24_guard"
require_file "$stage23_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-24 implementation contract' "$stage24_doc"
require_contains 'tokenizer_runtime_attachment_contract_command=scripts/nadia-tokenizer-runtime-attachment-contract.sh' "$stage24_doc"
require_contains 'installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment' "$stage24_doc"
require_contains 'tokenizer_runtime_attachment_contract_status=contract_only' "$stage24_doc"
require_contains 'tokenizer_runtime_attachment_authority=0' "$stage24_doc"
require_contains 'requires_future_prompt_tokenization_contract=1' "$stage24_doc"
require_contains 'tokenizer_runtime_attachment_attached=0' "$stage24_doc"
require_contains 'tokenizer_attached_to_runtime=0' "$stage24_doc"
require_contains 'runtime_invoked=0' "$stage24_doc"
require_contains 'prompt_tokenized=0' "$stage24_doc"
require_contains 'sh scripts/test-nadia-tokenizer-runtime-attachment-contract-stage-24.sh' "$stage24_doc"

require_contains 'Status: implementation status record' "$stage24_status"
require_contains 'nadia_stage_24_tokenizer_runtime_attachment_contract_present=1' "$stage24_status"
require_contains 'nadia_tokenizer_runtime_attachment_contract_generator_present=1' "$stage24_status"
require_contains 'tokenizer_runtime_attachment_contract_status=contract_only' "$stage24_status"
require_contains 'tokenizer_runtime_attachment_promotion_allowed=0' "$stage24_status"

require_contains 'Stage-24: Tokenizer Runtime Attachment Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-runtime-attachment-contract.sh' "$foundation"
require_contains 'Stage-25: Prompt Tokenization Contract' "$foundation"
require_contains 'test-nadia-tokenizer-runtime-attachment-contract-stage-24.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer runtime attachment contract Stage-24 + guardrails' "$foundation_index"
require_contains 'nadia_stage_24_tokenizer_runtime_attachment_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer runtime attachment contract Stage-24 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer runtime attachment contract Stage-24 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer runtime attachment contract Stage-24' "$current_status"
require_contains 'Stage-24 now defines a tokenizer runtime attachment contract' "$stage23_status"

require_contains 'NADIA TOKENIZER RUNTIME ATTACHMENT CONTRACT' "$attachment_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$attachment_script"
require_contains 'tokenizer_runtime_attachment_contract_status=contract_only' "$attachment_script"
require_contains 'requires_future_prompt_tokenization_contract=1' "$attachment_script"
require_contains 'tokenizer_runtime_attachment_plan_recorded=1' "$attachment_script"
require_contains 'tokenizer_runtime_attachment_performed=0' "$attachment_script"
require_contains 'tokenizer_runtime_attachment_attached=0' "$attachment_script"
require_contains 'tokenizer_runtime_attachment_runtime_invoked=0' "$attachment_script"
require_contains 'tokenizer_attached_to_runtime=0' "$attachment_script"
require_contains 'runtime_session_created=0' "$attachment_script"
require_contains 'runtime_invoked=0' "$attachment_script"
require_contains 'tokenizer_artifact_binding_performed=0' "$attachment_script"
require_contains 'tokenizer_artifact_file_opened=0' "$attachment_script"
require_contains 'tokenizer_artifact_file_read=0' "$attachment_script"
require_contains 'tokenizer_manifest_loaded=0' "$attachment_script"
require_contains 'tokenizer_manifest_parsed=0' "$attachment_script"
require_contains 'tokenizer_file_opened=0' "$attachment_script"
require_contains 'prompt_tokenized=0' "$attachment_script"
require_contains 'prompt_evaluated=0' "$attachment_script"
require_contains 'token_generation_performed=0' "$attachment_script"
require_contains 'inference_performed=0' "$attachment_script"
require_contains 'tool_execution_performed=0' "$attachment_script"
require_contains 'outside Nadia tokenizer-runtime-attachment boundary' "$attachment_script"
require_not_contains 'curl ' "$attachment_script"
require_not_contains 'wget ' "$attachment_script"
require_not_contains 'ssh ' "$attachment_script"

require_contains 'tokenizer-runtime-attachment' "$apply_script"
require_contains 'scripts/nadia-tokenizer-runtime-attachment-contract.sh' "$apply_script"
require_contains 'tokenizer_runtime_attachment_contract_stage=24-tokenizer-runtime-attachment-contract' "$panel_config"
require_contains 'nadia tokenizer-runtime-attachment' "$panel_ui"
require_contains 'latticra-nadia tokenizer-runtime-attachment' "$installer_readme"
require_contains 'nadia tokenizer-runtime-attachment' "$ui_model"
require_contains 'tokenizer-runtime-attachment' "$components_manifest"
require_contains 'nadia-tokenizer-runtime-attachment' "$makefile"

sh "$stage23_guard" >/tmp/latticra-nadia-stage24-prereq-stage23-test.out

out="${TMPDIR:-/tmp}/latticra-nadia-stage24-tokenizer-runtime-attachment-test"
binding="${TMPDIR:-/tmp}/latticra-nadia-stage23-tokenizer-artifact-binding-test/nadia-tokenizer-artifact-binding-contract-stage23-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$binding"

NADIA_TOKENIZER_RUNTIME_ATTACHMENT_TIMESTAMP=stage24-test sh "$attachment_script" \
  --tokenizer-artifact-binding "$binding" \
  --request-class awareness-education \
  --attachment-family operator-reviewed-tokenizer-runtime-attachment \
  --attachment-format contract-only-offline-attachment \
  --output "$out" >/tmp/latticra-nadia-stage24-tokenizer-runtime-attachment-test.out
attachment="$out/nadia-tokenizer-runtime-attachment-contract-stage24-test.txt"

require_file "$attachment"
require_file "$out/latest-tokenizer-runtime-attachment-contract.txt"
require_contains 'NADIA TOKENIZER RUNTIME ATTACHMENT CONTRACT' "$attachment"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$attachment"
require_contains 'public_name=Nadia' "$attachment"
require_contains 'stage=24-tokenizer-runtime-attachment-contract' "$attachment"
require_contains 'request_class=awareness-education' "$attachment"
require_contains 'tokenizer_runtime_attachment_contract_status=contract_only' "$attachment"
require_contains 'tokenizer_runtime_attachment_stage=contract-only' "$attachment"
require_contains 'tokenizer_runtime_attachment_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_allowed=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_performed=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_metadata_present=1' "$attachment"
require_contains 'tokenizer_runtime_attachment_family=operator-reviewed-tokenizer-runtime-attachment' "$attachment"
require_contains 'tokenizer_runtime_attachment_format=contract-only-offline-attachment' "$attachment"
require_contains 'tokenizer_runtime_attachment_loaded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_opened=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_read=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_validated=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_attached=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_runtime_invoked=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_decision=blocked_contract_only' "$attachment"
require_contains 'tokenizer_runtime_attachment_evidence_present=1' "$attachment"
require_contains 'tokenizer_runtime_attachment_source_policy=operator-reviewed-offline' "$attachment"
require_contains 'tokenizer_runtime_attachment_plan_recorded=1' "$attachment"
require_contains 'tokenizer_runtime_attachment_method_planned=offline-runtime-tokenizer-attachment-review' "$attachment"
require_contains 'tokenizer_runtime_attachment_result_recorded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_record_created=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_runtime_reference_recorded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_tokenizer_reference_recorded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_session_created=0' "$attachment"
require_contains 'requires_tokenizer_artifact_binding_contract=1' "$attachment"
require_contains 'requires_tokenizer_artifact_verification_contract=1' "$attachment"
require_contains 'requires_tokenizer_artifact_measurement_contract=1' "$attachment"
require_contains 'requires_tokenizer_artifact_inventory_contract=1' "$attachment"
require_contains 'requires_tokenizer_manifest_contract=1' "$attachment"
require_contains 'requires_tokenizer_specification_contract=1' "$attachment"
require_contains 'requires_tokenization_boundary_contract=1' "$attachment"
require_contains 'requires_runtime_profile_contract=1' "$attachment"
require_contains 'requires_runtime_invocation_contract=1' "$attachment"
require_contains 'requires_model_load_contract=1' "$attachment"
require_contains 'requires_future_prompt_tokenization_contract=1' "$attachment"
require_contains 'tokenizer_runtime_attachment_promotion_allowed=0' "$attachment"
require_contains 'requires_bound_tokenizer_artifact_reference=1' "$attachment"
require_contains 'requires_binding_contract_reference=1' "$attachment"
require_contains 'requires_runtime_profile_reference=1' "$attachment"
require_contains 'requires_runtime_invocation_reference=1' "$attachment"
require_contains 'requires_model_load_reference=1' "$attachment"
require_contains 'requires_no_runtime_invocation=1' "$attachment"
require_contains 'requires_no_runtime_session_creation=1' "$attachment"
require_contains 'requires_no_prompt_tokenization=1' "$attachment"
require_contains 'requires_no_inference=1' "$attachment"
require_contains 'requires_refusal_policy_link=1' "$attachment"
require_contains 'requires_survivor_centered_language_review=1' "$attachment"
require_contains 'tokenizer_runtime_attachment_open_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_read_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_write_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_validation_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_load_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_attach_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_runtime_invoke_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_session_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_tokenizer_bind_authority=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_bytes_read=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_hash_computed=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_entries_loaded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_runtime_reference_loaded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_tokenizer_reference_loaded=0' "$attachment"
require_contains 'tokenizer_runtime_attachment_file_written=0' "$attachment"
require_contains 'tokenizer_attached_to_runtime=0' "$attachment"
require_contains 'runtime_tokenizer_attachment_performed=0' "$attachment"
require_contains 'runtime_session_created=0' "$attachment"
require_contains 'runtime_invoked=0' "$attachment"
require_contains 'runtime_process_spawned=0' "$attachment"
require_contains 'runtime_binary_executed=0' "$attachment"
require_contains 'tokenizer_artifact_binding_hash_computed=0' "$attachment"
require_contains 'tokenizer_artifact_binding_performed=0' "$attachment"
require_contains 'tokenizer_artifact_bound_to_manifest=0' "$attachment"
require_contains 'tokenizer_artifact_bound_to_tokenizer=0' "$attachment"
require_contains 'tokenizer_artifact_file_opened=0' "$attachment"
require_contains 'tokenizer_artifact_file_read=0' "$attachment"
require_contains 'tokenizer_artifact_hash_computed=0' "$attachment"
require_contains 'tokenizer_manifest_loaded=0' "$attachment"
require_contains 'tokenizer_manifest_parsed=0' "$attachment"
require_contains 'tokenizer_file_opened=0' "$attachment"
require_contains 'tokenizer_file_read=0' "$attachment"
require_contains 'tokenizer_vocab_loaded=0' "$attachment"
require_contains 'future_qa_dialogue_capability_planned=1' "$attachment"
require_contains 'qa_dialogue_generated=0' "$attachment"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$attachment"
require_contains 'q_and_a_format_required=1' "$attachment"
require_contains 'survivor_centered_dialogue_required=1' "$attachment"
require_contains 'official_source_grounding_required=1' "$attachment"
require_contains 'live_web_lookup_authority=0' "$attachment"
require_contains 'topic_yazidi_genocide_awareness=1' "$attachment"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$attachment"
require_contains 'topic_womens_empowerment=1' "$attachment"
require_contains 'sexualized_dialogue_generation=0' "$attachment"
require_contains 'graphic_sexual_detail_allowed=0' "$attachment"
require_contains 'victim_blaming_allowed=0' "$attachment"
require_contains 'genocide_denial_allowed=0' "$attachment"
require_contains 'sexual_request_refusal=always' "$attachment"
require_contains 'manipulation_resistance=required' "$attachment"
require_contains 'prompt_materialized=0' "$attachment"
require_contains 'prompt_tokenization_authority=0' "$attachment"
require_contains 'prompt_tokenized=0' "$attachment"
require_contains 'prompt_tokens_created=0' "$attachment"
require_contains 'prompt_evaluation_authority=0' "$attachment"
require_contains 'prompt_evaluated=0' "$attachment"
require_contains 'token_generation_performed=0' "$attachment"
require_contains 'inference_performed=0' "$attachment"
require_contains 'tool_execution_performed=0' "$attachment"
require_contains 'network_authority=0' "$attachment"

if NADIA_TOKENIZER_RUNTIME_ATTACHMENT_TIMESTAMP=stage24-reject sh "$attachment_script" \
  --tokenizer-artifact-binding "$binding" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage24-reject-test.out 2>/tmp/latticra-nadia-stage24-reject-test.err; then
  printf 'nadia tokenizer runtime attachment contract stage 24: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-runtime-attachment boundary' /tmp/latticra-nadia-stage24-reject-test.err

printf 'nadia_tokenizer_runtime_attachment_contract_stage_24: ok\n'
