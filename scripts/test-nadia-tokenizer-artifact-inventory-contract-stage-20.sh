#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer artifact inventory contract stage 20: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact inventory contract stage 20: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact inventory contract stage 20: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage20_doc='docs/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20.md'
stage20_status='docs/status/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20_STATUS.md'
stage19_status='docs/status/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
inventory_script='scripts/nadia-tokenizer-artifact-inventory-contract.sh'
stage20_guard='scripts/test-nadia-tokenizer-artifact-inventory-contract-stage-20.sh'
stage19_guard='scripts/test-nadia-tokenizer-manifest-contract-stage-19.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage20_doc"
require_file "$stage20_status"
require_file "$stage19_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$inventory_script"
require_file "$stage20_guard"
require_file "$stage19_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-20 implementation contract' "$stage20_doc"
require_contains 'tokenizer_artifact_inventory_contract_command=scripts/nadia-tokenizer-artifact-inventory-contract.sh' "$stage20_doc"
require_contains 'installed_tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory' "$stage20_doc"
require_contains 'tokenizer_artifact_inventory_contract_status=contract_only' "$stage20_doc"
require_contains 'tokenizer_artifact_inventory_authority=0' "$stage20_doc"
require_contains 'requires_future_tokenizer_artifact_measurement_contract=1' "$stage20_doc"
require_contains 'tokenizer_artifact_file_opened=0' "$stage20_doc"
require_contains 'tokenizer_artifact_hash_computed=0' "$stage20_doc"
require_contains 'prompt_tokenized=0' "$stage20_doc"
require_contains 'sh scripts/test-nadia-tokenizer-artifact-inventory-contract-stage-20.sh' "$stage20_doc"

require_contains 'Status: implementation status record' "$stage20_status"
require_contains 'nadia_stage_20_tokenizer_artifact_inventory_contract_present=1' "$stage20_status"
require_contains 'nadia_tokenizer_artifact_inventory_contract_generator_present=1' "$stage20_status"
require_contains 'tokenizer_artifact_inventory_contract_status=contract_only' "$stage20_status"
require_contains 'tokenizer_artifact_inventory_promotion_allowed=0' "$stage20_status"

require_contains 'Stage-20: Tokenizer Artifact Inventory Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-artifact-inventory-contract.sh' "$foundation"
require_contains 'Stage-21: Tokenizer Artifact Measurement Contract' "$foundation"
require_contains 'test-nadia-tokenizer-artifact-inventory-contract-stage-20.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer artifact inventory contract Stage-20 + guardrails' "$foundation_index"
require_contains 'nadia_stage_20_tokenizer_artifact_inventory_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer artifact inventory contract Stage-20 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer artifact inventory contract Stage-20 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer artifact inventory contract Stage-20' "$current_status"
require_contains 'Stage-20 now defines a tokenizer artifact inventory contract' "$stage19_status"

require_contains 'NADIA TOKENIZER ARTIFACT INVENTORY CONTRACT' "$inventory_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$inventory_script"
require_contains 'tokenizer_artifact_inventory_contract_status=contract_only' "$inventory_script"
require_contains 'requires_future_tokenizer_artifact_measurement_contract=1' "$inventory_script"
require_contains 'tokenizer_artifact_path_resolved=0' "$inventory_script"
require_contains 'tokenizer_artifact_file_opened=0' "$inventory_script"
require_contains 'tokenizer_artifact_hash_computed=0' "$inventory_script"
require_contains 'tokenizer_artifact_measurement_performed=0' "$inventory_script"
require_contains 'tokenizer_manifest_loaded=0' "$inventory_script"
require_contains 'tokenizer_manifest_parsed=0' "$inventory_script"
require_contains 'tokenizer_file_opened=0' "$inventory_script"
require_contains 'prompt_tokenized=0' "$inventory_script"
require_contains 'prompt_evaluated=0' "$inventory_script"
require_contains 'token_generation_performed=0' "$inventory_script"
require_contains 'inference_performed=0' "$inventory_script"
require_contains 'tool_execution_performed=0' "$inventory_script"
require_contains 'outside Nadia tokenizer-artifact-inventory boundary' "$inventory_script"
require_not_contains 'curl ' "$inventory_script"
require_not_contains 'wget ' "$inventory_script"
require_not_contains 'ssh ' "$inventory_script"

require_contains 'tokenizer-artifact-inventory' "$apply_script"
require_contains 'scripts/nadia-tokenizer-artifact-inventory-contract.sh' "$apply_script"
require_contains 'tokenizer_artifact_inventory_contract_stage=20-tokenizer-artifact-inventory-contract' "$panel_config"
require_contains 'nadia tokenizer-artifact-inventory' "$panel_ui"
require_contains 'latticra-nadia tokenizer-artifact-inventory' "$installer_readme"
require_contains 'nadia tokenizer-artifact-inventory' "$ui_model"
require_contains 'tokenizer-artifact-inventory' "$components_manifest"
require_contains 'nadia-tokenizer-artifact-inventory' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage20-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

log_out="$tmp_root/stage20/logs"
mkdir -p "$log_out"
NADIA_TEST_TMP_ROOT="$tmp_root" sh "$stage19_guard" >"$log_out/prereq-stage19.out"

out="$tmp_root/stage20/tokenizer-artifact-inventory"
manifest="$tmp_root/stage19/tokenizer-manifest/nadia-tokenizer-manifest-contract-stage19-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$manifest"

NADIA_TOKENIZER_ARTIFACT_INVENTORY_TIMESTAMP=stage20-test sh "$inventory_script" \
  --tokenizer-manifest "$manifest" \
  --request-class awareness-education \
  --inventory-family operator-reviewed-tokenizer-artifact-inventory \
  --inventory-format contract-only-offline-inventory \
  --output "$out" >"$log_out/inventory.out"
inventory="$out/nadia-tokenizer-artifact-inventory-contract-stage20-test.txt"

require_file "$inventory"
require_file "$out/latest-tokenizer-artifact-inventory-contract.txt"
require_contains 'NADIA TOKENIZER ARTIFACT INVENTORY CONTRACT' "$inventory"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$inventory"
require_contains 'public_name=Nadia' "$inventory"
require_contains 'stage=20-tokenizer-artifact-inventory-contract' "$inventory"
require_contains 'request_class=awareness-education' "$inventory"
require_contains 'tokenizer_artifact_inventory_contract_status=contract_only' "$inventory"
require_contains 'tokenizer_artifact_inventory_stage=contract-only' "$inventory"
require_contains 'tokenizer_artifact_inventory_authority=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_allowed=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_performed=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_metadata_present=1' "$inventory"
require_contains 'tokenizer_artifact_inventory_family=operator-reviewed-tokenizer-artifact-inventory' "$inventory"
require_contains 'tokenizer_artifact_inventory_format=contract-only-offline-inventory' "$inventory"
require_contains 'tokenizer_artifact_inventory_decision=blocked_contract_only' "$inventory"
require_contains 'tokenizer_artifact_inventory_evidence_present=1' "$inventory"
require_contains 'tokenizer_artifact_inventory_source_policy=operator-reviewed-offline' "$inventory"
require_contains 'tokenizer_artifact_inventory_path_recorded=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_schema_planned=1' "$inventory"
require_contains 'tokenizer_artifact_inventory_entry_count=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_file_count=0' "$inventory"
require_contains 'requires_tokenizer_manifest_contract=1' "$inventory"
require_contains 'requires_tokenizer_specification_contract=1' "$inventory"
require_contains 'requires_tokenization_boundary_contract=1' "$inventory"
require_contains 'requires_prompt_evaluation_handoff_contract=1' "$inventory"
require_contains 'requires_awareness_dialogue_contract=1' "$inventory"
require_contains 'requires_prompt_materialization_contract=1' "$inventory"
require_contains 'requires_prompt_receipt_contract=1' "$inventory"
require_contains 'requires_prompt_buffer_boundary=1' "$inventory"
require_contains 'requires_protective_safety_boundary=1' "$inventory"
require_contains 'requires_operator_review=1' "$inventory"
require_contains 'requires_official_source_snapshot=1' "$inventory"
require_contains 'requires_future_tokenizer_artifact_measurement_contract=1' "$inventory"
require_contains 'tokenizer_artifact_inventory_promotion_allowed=0' "$inventory"
require_contains 'requires_artifact_identity=1' "$inventory"
require_contains 'requires_artifact_role_classification=1' "$inventory"
require_contains 'requires_manifest_entry_reference=1' "$inventory"
require_contains 'requires_vocab_artifact_entry=1' "$inventory"
require_contains 'requires_merges_artifact_entry_review=1' "$inventory"
require_contains 'requires_tokenizer_model_artifact_entry=1' "$inventory"
require_contains 'requires_special_tokens_artifact_entry=1' "$inventory"
require_contains 'requires_chat_template_artifact_entry=1' "$inventory"
require_contains 'requires_relative_path_policy_review=1' "$inventory"
require_contains 'requires_no_absolute_host_path_claim=1' "$inventory"
require_contains 'requires_no_runtime_binding=1' "$inventory"
require_contains 'tokenizer_artifact_inventory_open_authority=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_read_authority=0' "$inventory"
require_contains 'tokenizer_artifact_path_resolution_authority=0' "$inventory"
require_contains 'tokenizer_artifact_scan_authority=0' "$inventory"
require_contains 'tokenizer_artifact_stat_authority=0' "$inventory"
require_contains 'tokenizer_artifact_hash_authority=0' "$inventory"
require_contains 'tokenizer_artifact_measurement_authority=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_opened=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_read=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_parsed=0' "$inventory"
require_contains 'tokenizer_artifact_inventory_loaded=0' "$inventory"
require_contains 'tokenizer_artifact_path_resolved=0' "$inventory"
require_contains 'tokenizer_artifact_scan_performed=0' "$inventory"
require_contains 'tokenizer_artifact_stat_performed=0' "$inventory"
require_contains 'tokenizer_artifact_file_opened=0' "$inventory"
require_contains 'tokenizer_artifact_file_read=0' "$inventory"
require_contains 'tokenizer_artifact_bytes_read=0' "$inventory"
require_contains 'tokenizer_artifact_hash_computed=0' "$inventory"
require_contains 'tokenizer_artifact_measurement_performed=0' "$inventory"
require_contains 'tokenizer_vocab_artifact_loaded=0' "$inventory"
require_contains 'tokenizer_merges_artifact_loaded=0' "$inventory"
require_contains 'tokenizer_model_artifact_loaded=0' "$inventory"
require_contains 'tokenizer_special_tokens_artifact_loaded=0' "$inventory"
require_contains 'tokenizer_manifest_open_authority=0' "$inventory"
require_contains 'tokenizer_manifest_read_authority=0' "$inventory"
require_contains 'tokenizer_manifest_parse_authority=0' "$inventory"
require_contains 'tokenizer_manifest_opened=0' "$inventory"
require_contains 'tokenizer_manifest_read=0' "$inventory"
require_contains 'tokenizer_manifest_parsed=0' "$inventory"
require_contains 'tokenizer_manifest_loaded=0' "$inventory"
require_contains 'tokenizer_file_open_authority=0' "$inventory"
require_contains 'tokenizer_file_read_authority=0' "$inventory"
require_contains 'tokenizer_vocab_load_authority=0' "$inventory"
require_contains 'tokenizer_file_opened=0' "$inventory"
require_contains 'tokenizer_file_read=0' "$inventory"
require_contains 'tokenizer_vocab_loaded=0' "$inventory"
require_contains 'tokenizer_bytes_read=0' "$inventory"
require_contains 'tokenizer_hash_computed=0' "$inventory"
require_contains 'future_qa_dialogue_capability_planned=1' "$inventory"
require_contains 'qa_dialogue_generated=0' "$inventory"
require_contains 'question_generated=0' "$inventory"
require_contains 'answer_generated=0' "$inventory"
require_contains 'answer_text_generated=0' "$inventory"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$inventory"
require_contains 'q_and_a_format_required=1' "$inventory"
require_contains 'survivor_centered_dialogue_required=1' "$inventory"
require_contains 'official_source_grounding_required=1' "$inventory"
require_contains 'live_web_lookup_authority=0' "$inventory"
require_contains 'topic_yazidi_genocide_awareness=1' "$inventory"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$inventory"
require_contains 'topic_womens_empowerment=1' "$inventory"
require_contains 'sexualized_dialogue_generation=0' "$inventory"
require_contains 'graphic_sexual_detail_allowed=0' "$inventory"
require_contains 'victim_blaming_allowed=0' "$inventory"
require_contains 'genocide_denial_allowed=0' "$inventory"
require_contains 'medical_advice_authority=0' "$inventory"
require_contains 'legal_advice_authority=0' "$inventory"
require_contains 'trauma_counseling_authority=0' "$inventory"
require_contains 'sexual_request_refusal=always' "$inventory"
require_contains 'manipulation_resistance=required' "$inventory"
require_contains 'prompt_materialized=0' "$inventory"
require_contains 'prompt_text_materialized=0' "$inventory"
require_contains 'prompt_buffer_allocated=0' "$inventory"
require_contains 'prompt_buffer_written=0' "$inventory"
require_contains 'prompt_tokenization_authority=0' "$inventory"
require_contains 'prompt_tokenization_allowed=0' "$inventory"
require_contains 'prompt_tokenized=0' "$inventory"
require_contains 'prompt_tokens_created=0' "$inventory"
require_contains 'prompt_evaluation_authority=0' "$inventory"
require_contains 'prompt_evaluated=0' "$inventory"
require_contains 'token_generation_performed=0' "$inventory"
require_contains 'inference_performed=0' "$inventory"
require_contains 'tool_execution_performed=0' "$inventory"
require_contains 'network_authority=0' "$inventory"

if NADIA_TOKENIZER_ARTIFACT_INVENTORY_TIMESTAMP=stage20-reject sh "$inventory_script" \
  --tokenizer-manifest "$manifest" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia tokenizer artifact inventory contract stage 20: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-artifact-inventory boundary' "$log_out/reject.err"

printf 'nadia_tokenizer_artifact_inventory_contract_stage_20: ok\n'
