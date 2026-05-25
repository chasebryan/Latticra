#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer artifact binding contract stage 23: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact binding contract stage 23: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact binding contract stage 23: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage23_doc='docs/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23.md'
stage23_status='docs/status/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23_STATUS.md'
stage22_status='docs/status/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
binding_script='scripts/nadia-tokenizer-artifact-binding-contract.sh'
stage23_guard='scripts/test-nadia-tokenizer-artifact-binding-contract-stage-23.sh'
stage22_guard='scripts/test-nadia-tokenizer-artifact-verification-contract-stage-22.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage23_doc"
require_file "$stage23_status"
require_file "$stage22_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$binding_script"
require_file "$stage23_guard"
require_file "$stage22_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-23 implementation contract' "$stage23_doc"
require_contains 'tokenizer_artifact_binding_contract_command=scripts/nadia-tokenizer-artifact-binding-contract.sh' "$stage23_doc"
require_contains 'installed_tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding' "$stage23_doc"
require_contains 'tokenizer_artifact_binding_contract_status=contract_only' "$stage23_doc"
require_contains 'tokenizer_artifact_binding_authority=0' "$stage23_doc"
require_contains 'requires_future_tokenizer_runtime_attachment_contract=1' "$stage23_doc"
require_contains 'tokenizer_artifact_binding_hash_computed=0' "$stage23_doc"
require_contains 'tokenizer_artifact_binding_bound=0' "$stage23_doc"
require_contains 'tokenizer_attached_to_runtime=0' "$stage23_doc"
require_contains 'prompt_tokenized=0' "$stage23_doc"
require_contains 'sh scripts/test-nadia-tokenizer-artifact-binding-contract-stage-23.sh' "$stage23_doc"

require_contains 'Status: implementation status record' "$stage23_status"
require_contains 'nadia_stage_23_tokenizer_artifact_binding_contract_present=1' "$stage23_status"
require_contains 'nadia_tokenizer_artifact_binding_contract_generator_present=1' "$stage23_status"
require_contains 'tokenizer_artifact_binding_contract_status=contract_only' "$stage23_status"
require_contains 'tokenizer_artifact_binding_promotion_allowed=0' "$stage23_status"

require_contains 'Stage-23: Tokenizer Artifact Binding Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-artifact-binding-contract.sh' "$foundation"
require_contains 'Stage-24: Tokenizer Runtime Attachment Contract' "$foundation"
require_contains 'test-nadia-tokenizer-artifact-binding-contract-stage-23.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer artifact binding contract Stage-23 + guardrails' "$foundation_index"
require_contains 'nadia_stage_23_tokenizer_artifact_binding_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer artifact binding contract Stage-23 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer artifact binding contract Stage-23 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer artifact binding contract Stage-23' "$current_status"
require_contains 'Stage-23 now defines a tokenizer artifact binding contract' "$stage22_status"

require_contains 'NADIA TOKENIZER ARTIFACT BINDING CONTRACT' "$binding_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$binding_script"
require_contains 'tokenizer_artifact_binding_contract_status=contract_only' "$binding_script"
require_contains 'requires_future_tokenizer_runtime_attachment_contract=1' "$binding_script"
require_contains 'tokenizer_artifact_binding_plan_recorded=1' "$binding_script"
require_contains 'tokenizer_artifact_binding_hash_computed=0' "$binding_script"
require_contains 'tokenizer_artifact_binding_performed=0' "$binding_script"
require_contains 'tokenizer_artifact_binding_bound=0' "$binding_script"
require_contains 'tokenizer_artifact_binding_runtime_attachment_performed=0' "$binding_script"
require_contains 'tokenizer_artifact_verification_performed=0' "$binding_script"
require_contains 'tokenizer_artifact_file_opened=0' "$binding_script"
require_contains 'tokenizer_artifact_file_read=0' "$binding_script"
require_contains 'tokenizer_attached_to_runtime=0' "$binding_script"
require_contains 'tokenizer_manifest_loaded=0' "$binding_script"
require_contains 'tokenizer_manifest_parsed=0' "$binding_script"
require_contains 'tokenizer_file_opened=0' "$binding_script"
require_contains 'prompt_tokenized=0' "$binding_script"
require_contains 'prompt_evaluated=0' "$binding_script"
require_contains 'token_generation_performed=0' "$binding_script"
require_contains 'inference_performed=0' "$binding_script"
require_contains 'tool_execution_performed=0' "$binding_script"
require_contains 'outside Nadia tokenizer-artifact-binding boundary' "$binding_script"
require_not_contains 'curl ' "$binding_script"
require_not_contains 'wget ' "$binding_script"
require_not_contains 'ssh ' "$binding_script"

require_contains 'tokenizer-artifact-binding' "$apply_script"
require_contains 'scripts/nadia-tokenizer-artifact-binding-contract.sh' "$apply_script"
require_contains 'tokenizer_artifact_binding_contract_stage=23-tokenizer-artifact-binding-contract' "$panel_config"
require_contains 'nadia tokenizer-artifact-binding' "$panel_ui"
require_contains 'latticra-nadia tokenizer-artifact-binding' "$installer_readme"
require_contains 'nadia tokenizer-artifact-binding' "$ui_model"
require_contains 'tokenizer-artifact-binding' "$components_manifest"
require_contains 'nadia-tokenizer-artifact-binding' "$makefile"

sh "$stage22_guard" >/tmp/latticra-nadia-stage23-prereq-stage22-test.out

out='/private/tmp/latticra-nadia-stage23-tokenizer-artifact-binding-test'
verification='/private/tmp/latticra-nadia-stage22-tokenizer-artifact-verification-test/nadia-tokenizer-artifact-verification-contract-stage22-test.txt'
rm -rf "$out"
mkdir -p "$out"

require_file "$verification"

NADIA_TOKENIZER_ARTIFACT_BINDING_TIMESTAMP=stage23-test sh "$binding_script" \
  --tokenizer-artifact-verification "$verification" \
  --request-class awareness-education \
  --binding-family operator-reviewed-tokenizer-artifact-binding \
  --binding-format contract-only-offline-binding \
  --output "$out" >/tmp/latticra-nadia-stage23-tokenizer-artifact-binding-test.out
binding="$out/nadia-tokenizer-artifact-binding-contract-stage23-test.txt"

require_file "$binding"
require_file "$out/latest-tokenizer-artifact-binding-contract.txt"
require_contains 'NADIA TOKENIZER ARTIFACT BINDING CONTRACT' "$binding"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$binding"
require_contains 'public_name=Nadia' "$binding"
require_contains 'stage=23-tokenizer-artifact-binding-contract' "$binding"
require_contains 'request_class=awareness-education' "$binding"
require_contains 'tokenizer_artifact_binding_contract_status=contract_only' "$binding"
require_contains 'tokenizer_artifact_binding_stage=contract-only' "$binding"
require_contains 'tokenizer_artifact_binding_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_allowed=0' "$binding"
require_contains 'tokenizer_artifact_binding_performed=0' "$binding"
require_contains 'tokenizer_artifact_binding_metadata_present=1' "$binding"
require_contains 'tokenizer_artifact_binding_family=operator-reviewed-tokenizer-artifact-binding' "$binding"
require_contains 'tokenizer_artifact_binding_format=contract-only-offline-binding' "$binding"
require_contains 'tokenizer_artifact_binding_loaded=0' "$binding"
require_contains 'tokenizer_artifact_binding_opened=0' "$binding"
require_contains 'tokenizer_artifact_binding_read=0' "$binding"
require_contains 'tokenizer_artifact_binding_validated=0' "$binding"
require_contains 'tokenizer_artifact_binding_bound=0' "$binding"
require_contains 'tokenizer_artifact_binding_runtime_attached=0' "$binding"
require_contains 'tokenizer_artifact_binding_decision=blocked_contract_only' "$binding"
require_contains 'tokenizer_artifact_binding_evidence_present=1' "$binding"
require_contains 'tokenizer_artifact_binding_source_policy=operator-reviewed-offline' "$binding"
require_contains 'tokenizer_artifact_binding_plan_recorded=1' "$binding"
require_contains 'tokenizer_artifact_binding_method_planned=offline-manifest-artifact-role-binding-review' "$binding"
require_contains 'tokenizer_artifact_binding_result_recorded=0' "$binding"
require_contains 'tokenizer_artifact_binding_record_created=0' "$binding"
require_contains 'tokenizer_artifact_binding_manifest_reference_recorded=0' "$binding"
require_contains 'tokenizer_artifact_binding_artifact_reference_recorded=0' "$binding"
require_contains 'tokenizer_artifact_binding_runtime_attach_recorded=0' "$binding"
require_contains 'requires_tokenizer_artifact_verification_contract=1' "$binding"
require_contains 'requires_tokenizer_artifact_measurement_contract=1' "$binding"
require_contains 'requires_tokenizer_artifact_inventory_contract=1' "$binding"
require_contains 'requires_tokenizer_manifest_contract=1' "$binding"
require_contains 'requires_tokenizer_specification_contract=1' "$binding"
require_contains 'requires_tokenization_boundary_contract=1' "$binding"
require_contains 'requires_future_tokenizer_runtime_attachment_contract=1' "$binding"
require_contains 'tokenizer_artifact_binding_promotion_allowed=0' "$binding"
require_contains 'requires_verified_artifact_reference=1' "$binding"
require_contains 'requires_artifact_identity=1' "$binding"
require_contains 'requires_verification_contract_reference=1' "$binding"
require_contains 'requires_measurement_contract_reference=1' "$binding"
require_contains 'requires_inventory_entry_reference=1' "$binding"
require_contains 'requires_manifest_entry_reference=1' "$binding"
require_contains 'requires_tokenizer_specification_reference=1' "$binding"
require_contains 'requires_digest_match_record=1' "$binding"
require_contains 'requires_size_match_record=1' "$binding"
require_contains 'requires_no_runtime_attachment=1' "$binding"
require_contains 'requires_refusal_policy_link=1' "$binding"
require_contains 'requires_survivor_centered_language_review=1' "$binding"
require_contains 'tokenizer_artifact_binding_open_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_read_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_write_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_hash_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_validation_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_load_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_attach_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_runtime_attach_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_manifest_bind_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_tokenizer_bind_authority=0' "$binding"
require_contains 'tokenizer_artifact_binding_bytes_read=0' "$binding"
require_contains 'tokenizer_artifact_binding_hash_computed=0' "$binding"
require_contains 'tokenizer_artifact_binding_entries_loaded=0' "$binding"
require_contains 'tokenizer_artifact_binding_manifest_reference_loaded=0' "$binding"
require_contains 'tokenizer_artifact_binding_artifact_reference_loaded=0' "$binding"
require_contains 'tokenizer_artifact_binding_runtime_attachment_performed=0' "$binding"
require_contains 'tokenizer_artifact_binding_file_written=0' "$binding"
require_contains 'tokenizer_artifact_bound_to_manifest=0' "$binding"
require_contains 'tokenizer_artifact_bound_to_tokenizer=0' "$binding"
require_contains 'tokenizer_attached_to_runtime=0' "$binding"
require_contains 'tokenizer_runtime_attachment_performed=0' "$binding"
require_contains 'tokenizer_artifact_verification_hash_computed=0' "$binding"
require_contains 'tokenizer_artifact_verification_performed=0' "$binding"
require_contains 'tokenizer_artifact_digest_recorded=0' "$binding"
require_contains 'tokenizer_artifact_size_recorded=0' "$binding"
require_contains 'tokenizer_artifact_file_opened=0' "$binding"
require_contains 'tokenizer_artifact_file_read=0' "$binding"
require_contains 'tokenizer_artifact_hash_computed=0' "$binding"
require_contains 'tokenizer_manifest_loaded=0' "$binding"
require_contains 'tokenizer_manifest_parsed=0' "$binding"
require_contains 'tokenizer_file_opened=0' "$binding"
require_contains 'tokenizer_file_read=0' "$binding"
require_contains 'tokenizer_vocab_loaded=0' "$binding"
require_contains 'future_qa_dialogue_capability_planned=1' "$binding"
require_contains 'qa_dialogue_generated=0' "$binding"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$binding"
require_contains 'q_and_a_format_required=1' "$binding"
require_contains 'survivor_centered_dialogue_required=1' "$binding"
require_contains 'official_source_grounding_required=1' "$binding"
require_contains 'live_web_lookup_authority=0' "$binding"
require_contains 'topic_yazidi_genocide_awareness=1' "$binding"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$binding"
require_contains 'topic_womens_empowerment=1' "$binding"
require_contains 'sexualized_dialogue_generation=0' "$binding"
require_contains 'graphic_sexual_detail_allowed=0' "$binding"
require_contains 'victim_blaming_allowed=0' "$binding"
require_contains 'genocide_denial_allowed=0' "$binding"
require_contains 'sexual_request_refusal=always' "$binding"
require_contains 'manipulation_resistance=required' "$binding"
require_contains 'prompt_materialized=0' "$binding"
require_contains 'prompt_tokenization_authority=0' "$binding"
require_contains 'prompt_tokenized=0' "$binding"
require_contains 'prompt_tokens_created=0' "$binding"
require_contains 'prompt_evaluation_authority=0' "$binding"
require_contains 'prompt_evaluated=0' "$binding"
require_contains 'token_generation_performed=0' "$binding"
require_contains 'inference_performed=0' "$binding"
require_contains 'tool_execution_performed=0' "$binding"
require_contains 'network_authority=0' "$binding"

if NADIA_TOKENIZER_ARTIFACT_BINDING_TIMESTAMP=stage23-reject sh "$binding_script" \
  --tokenizer-artifact-verification "$verification" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage23-reject-test.out 2>/tmp/latticra-nadia-stage23-reject-test.err; then
  printf 'nadia tokenizer artifact binding contract stage 23: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-artifact-binding boundary' /tmp/latticra-nadia-stage23-reject-test.err

printf 'nadia_tokenizer_artifact_binding_contract_stage_23: ok\n'
