#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer artifact measurement contract stage 21: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact measurement contract stage 21: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact measurement contract stage 21: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage21_doc='docs/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21.md'
stage21_status='docs/status/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21_STATUS.md'
stage20_status='docs/status/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
measurement_script='scripts/nadia-tokenizer-artifact-measurement-contract.sh'
stage21_guard='scripts/test-nadia-tokenizer-artifact-measurement-contract-stage-21.sh'
stage20_guard='scripts/test-nadia-tokenizer-artifact-inventory-contract-stage-20.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage21_doc"
require_file "$stage21_status"
require_file "$stage20_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$measurement_script"
require_file "$stage21_guard"
require_file "$stage20_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-21 implementation contract' "$stage21_doc"
require_contains 'tokenizer_artifact_measurement_contract_command=scripts/nadia-tokenizer-artifact-measurement-contract.sh' "$stage21_doc"
require_contains 'installed_tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement' "$stage21_doc"
require_contains 'tokenizer_artifact_measurement_contract_status=contract_only' "$stage21_doc"
require_contains 'tokenizer_artifact_measurement_authority=0' "$stage21_doc"
require_contains 'requires_future_tokenizer_artifact_verification_contract=1' "$stage21_doc"
require_contains 'tokenizer_artifact_measurement_hash_computed=0' "$stage21_doc"
require_contains 'tokenizer_artifact_file_opened=0' "$stage21_doc"
require_contains 'prompt_tokenized=0' "$stage21_doc"
require_contains 'sh scripts/test-nadia-tokenizer-artifact-measurement-contract-stage-21.sh' "$stage21_doc"

require_contains 'Status: implementation status record' "$stage21_status"
require_contains 'nadia_stage_21_tokenizer_artifact_measurement_contract_present=1' "$stage21_status"
require_contains 'nadia_tokenizer_artifact_measurement_contract_generator_present=1' "$stage21_status"
require_contains 'tokenizer_artifact_measurement_contract_status=contract_only' "$stage21_status"
require_contains 'tokenizer_artifact_measurement_promotion_allowed=0' "$stage21_status"

require_contains 'Stage-21: Tokenizer Artifact Measurement Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-artifact-measurement-contract.sh' "$foundation"
require_contains 'Stage-22: Tokenizer Artifact Verification Contract' "$foundation"
require_contains 'test-nadia-tokenizer-artifact-measurement-contract-stage-21.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer artifact measurement contract Stage-21 + guardrails' "$foundation_index"
require_contains 'nadia_stage_21_tokenizer_artifact_measurement_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer artifact measurement contract Stage-21 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer artifact measurement contract Stage-21 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer artifact measurement contract Stage-21' "$current_status"
require_contains 'Stage-21 now defines a tokenizer artifact measurement contract' "$stage20_status"

require_contains 'NADIA TOKENIZER ARTIFACT MEASUREMENT CONTRACT' "$measurement_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$measurement_script"
require_contains 'tokenizer_artifact_measurement_contract_status=contract_only' "$measurement_script"
require_contains 'requires_future_tokenizer_artifact_verification_contract=1' "$measurement_script"
require_contains 'tokenizer_artifact_measurement_plan_recorded=1' "$measurement_script"
require_contains 'tokenizer_artifact_measurement_hash_computed=0' "$measurement_script"
require_contains 'tokenizer_artifact_measurement_performed=0' "$measurement_script"
require_contains 'tokenizer_artifact_digest_recorded=0' "$measurement_script"
require_contains 'tokenizer_artifact_size_recorded=0' "$measurement_script"
require_contains 'tokenizer_artifact_file_opened=0' "$measurement_script"
require_contains 'tokenizer_artifact_file_read=0' "$measurement_script"
require_contains 'tokenizer_manifest_loaded=0' "$measurement_script"
require_contains 'tokenizer_manifest_parsed=0' "$measurement_script"
require_contains 'tokenizer_file_opened=0' "$measurement_script"
require_contains 'prompt_tokenized=0' "$measurement_script"
require_contains 'prompt_evaluated=0' "$measurement_script"
require_contains 'token_generation_performed=0' "$measurement_script"
require_contains 'inference_performed=0' "$measurement_script"
require_contains 'tool_execution_performed=0' "$measurement_script"
require_contains 'outside Nadia tokenizer-artifact-measurement boundary' "$measurement_script"
require_not_contains 'curl ' "$measurement_script"
require_not_contains 'wget ' "$measurement_script"
require_not_contains 'ssh ' "$measurement_script"

require_contains 'tokenizer-artifact-measurement' "$apply_script"
require_contains 'scripts/nadia-tokenizer-artifact-measurement-contract.sh' "$apply_script"
require_contains 'tokenizer_artifact_measurement_contract_stage=21-tokenizer-artifact-measurement-contract' "$panel_config"
require_contains 'nadia tokenizer-artifact-measurement' "$panel_ui"
require_contains 'latticra-nadia tokenizer-artifact-measurement' "$installer_readme"
require_contains 'nadia tokenizer-artifact-measurement' "$ui_model"
require_contains 'tokenizer-artifact-measurement' "$components_manifest"
require_contains 'nadia-tokenizer-artifact-measurement' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage21-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

log_out="$tmp_root/stage21/logs"
mkdir -p "$log_out"
NADIA_TEST_TMP_ROOT="$tmp_root" sh "$stage20_guard" >"$log_out/prereq-stage20.out"

out="$tmp_root/stage21/tokenizer-artifact-measurement"
inventory="$tmp_root/stage20/tokenizer-artifact-inventory/nadia-tokenizer-artifact-inventory-contract-stage20-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$inventory"

NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_TIMESTAMP=stage21-test sh "$measurement_script" \
  --tokenizer-artifact-inventory "$inventory" \
  --request-class awareness-education \
  --measurement-family operator-reviewed-tokenizer-artifact-measurement \
  --measurement-format contract-only-offline-measurement \
  --output "$out" >"$log_out/measurement.out"
measurement="$out/nadia-tokenizer-artifact-measurement-contract-stage21-test.txt"

require_file "$measurement"
require_file "$out/latest-tokenizer-artifact-measurement-contract.txt"
require_contains 'NADIA TOKENIZER ARTIFACT MEASUREMENT CONTRACT' "$measurement"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$measurement"
require_contains 'public_name=Nadia' "$measurement"
require_contains 'stage=21-tokenizer-artifact-measurement-contract' "$measurement"
require_contains 'request_class=awareness-education' "$measurement"
require_contains 'tokenizer_artifact_measurement_contract_status=contract_only' "$measurement"
require_contains 'tokenizer_artifact_measurement_stage=contract-only' "$measurement"
require_contains 'tokenizer_artifact_measurement_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_allowed=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_performed=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_metadata_present=1' "$measurement"
require_contains 'tokenizer_artifact_measurement_family=operator-reviewed-tokenizer-artifact-measurement' "$measurement"
require_contains 'tokenizer_artifact_measurement_format=contract-only-offline-measurement' "$measurement"
require_contains 'tokenizer_artifact_measurement_loaded=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_opened=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_read=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_validated=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_decision=blocked_contract_only' "$measurement"
require_contains 'tokenizer_artifact_measurement_evidence_present=1' "$measurement"
require_contains 'tokenizer_artifact_measurement_source_policy=operator-reviewed-offline' "$measurement"
require_contains 'tokenizer_artifact_measurement_plan_recorded=1' "$measurement"
require_contains 'tokenizer_artifact_measurement_algorithm_planned=sha256-or-approved-digest' "$measurement"
require_contains 'tokenizer_artifact_measurement_result_recorded=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_digest_recorded=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_size_recorded=0' "$measurement"
require_contains 'requires_tokenizer_artifact_inventory_contract=1' "$measurement"
require_contains 'requires_tokenizer_manifest_contract=1' "$measurement"
require_contains 'requires_tokenizer_specification_contract=1' "$measurement"
require_contains 'requires_tokenization_boundary_contract=1' "$measurement"
require_contains 'requires_future_tokenizer_artifact_verification_contract=1' "$measurement"
require_contains 'tokenizer_artifact_measurement_promotion_allowed=0' "$measurement"
require_contains 'requires_artifact_identity=1' "$measurement"
require_contains 'requires_artifact_role_classification=1' "$measurement"
require_contains 'requires_inventory_entry_reference=1' "$measurement"
require_contains 'requires_measurement_algorithm_policy=1' "$measurement"
require_contains 'requires_digest_format_policy=1' "$measurement"
require_contains 'requires_size_record_policy=1' "$measurement"
require_contains 'requires_reproducible_measurement_policy=1' "$measurement"
require_contains 'requires_operator_approval_record=1' "$measurement"
require_contains 'requires_official_source_snapshot=1' "$measurement"
require_contains 'requires_no_runtime_binding=1' "$measurement"
require_contains 'requires_refusal_policy_link=1' "$measurement"
require_contains 'requires_survivor_centered_language_review=1' "$measurement"
require_contains 'tokenizer_artifact_measurement_open_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_read_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_hash_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_validation_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_load_authority=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_bytes_read=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_hash_computed=0' "$measurement"
require_contains 'tokenizer_artifact_measurement_entries_loaded=0' "$measurement"
require_contains 'tokenizer_artifact_digest_recorded=0' "$measurement"
require_contains 'tokenizer_artifact_size_recorded=0' "$measurement"
require_contains 'tokenizer_artifact_path_resolved=0' "$measurement"
require_contains 'tokenizer_artifact_scan_performed=0' "$measurement"
require_contains 'tokenizer_artifact_stat_performed=0' "$measurement"
require_contains 'tokenizer_artifact_file_opened=0' "$measurement"
require_contains 'tokenizer_artifact_file_read=0' "$measurement"
require_contains 'tokenizer_artifact_bytes_read=0' "$measurement"
require_contains 'tokenizer_artifact_hash_computed=0' "$measurement"
require_contains 'tokenizer_manifest_open_authority=0' "$measurement"
require_contains 'tokenizer_manifest_read_authority=0' "$measurement"
require_contains 'tokenizer_manifest_parse_authority=0' "$measurement"
require_contains 'tokenizer_manifest_opened=0' "$measurement"
require_contains 'tokenizer_manifest_read=0' "$measurement"
require_contains 'tokenizer_manifest_parsed=0' "$measurement"
require_contains 'tokenizer_manifest_loaded=0' "$measurement"
require_contains 'tokenizer_file_open_authority=0' "$measurement"
require_contains 'tokenizer_file_read_authority=0' "$measurement"
require_contains 'tokenizer_vocab_load_authority=0' "$measurement"
require_contains 'tokenizer_file_opened=0' "$measurement"
require_contains 'tokenizer_file_read=0' "$measurement"
require_contains 'tokenizer_vocab_loaded=0' "$measurement"
require_contains 'tokenizer_bytes_read=0' "$measurement"
require_contains 'tokenizer_hash_computed=0' "$measurement"
require_contains 'future_qa_dialogue_capability_planned=1' "$measurement"
require_contains 'qa_dialogue_generated=0' "$measurement"
require_contains 'question_generated=0' "$measurement"
require_contains 'answer_generated=0' "$measurement"
require_contains 'answer_text_generated=0' "$measurement"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$measurement"
require_contains 'q_and_a_format_required=1' "$measurement"
require_contains 'survivor_centered_dialogue_required=1' "$measurement"
require_contains 'official_source_grounding_required=1' "$measurement"
require_contains 'live_web_lookup_authority=0' "$measurement"
require_contains 'topic_yazidi_genocide_awareness=1' "$measurement"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$measurement"
require_contains 'topic_womens_empowerment=1' "$measurement"
require_contains 'sexualized_dialogue_generation=0' "$measurement"
require_contains 'graphic_sexual_detail_allowed=0' "$measurement"
require_contains 'victim_blaming_allowed=0' "$measurement"
require_contains 'genocide_denial_allowed=0' "$measurement"
require_contains 'medical_advice_authority=0' "$measurement"
require_contains 'legal_advice_authority=0' "$measurement"
require_contains 'trauma_counseling_authority=0' "$measurement"
require_contains 'sexual_request_refusal=always' "$measurement"
require_contains 'manipulation_resistance=required' "$measurement"
require_contains 'prompt_materialized=0' "$measurement"
require_contains 'prompt_text_materialized=0' "$measurement"
require_contains 'prompt_buffer_allocated=0' "$measurement"
require_contains 'prompt_buffer_written=0' "$measurement"
require_contains 'prompt_tokenization_authority=0' "$measurement"
require_contains 'prompt_tokenization_allowed=0' "$measurement"
require_contains 'prompt_tokenized=0' "$measurement"
require_contains 'prompt_tokens_created=0' "$measurement"
require_contains 'prompt_evaluation_authority=0' "$measurement"
require_contains 'prompt_evaluated=0' "$measurement"
require_contains 'token_generation_performed=0' "$measurement"
require_contains 'inference_performed=0' "$measurement"
require_contains 'tool_execution_performed=0' "$measurement"
require_contains 'network_authority=0' "$measurement"

if NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_TIMESTAMP=stage21-reject sh "$measurement_script" \
  --tokenizer-artifact-inventory "$inventory" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia tokenizer artifact measurement contract stage 21: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-artifact-measurement boundary' "$log_out/reject.err"

printf 'nadia_tokenizer_artifact_measurement_contract_stage_21: ok\n'
