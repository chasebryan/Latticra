#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer artifact verification contract stage 22: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact verification contract stage 22: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer artifact verification contract stage 22: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage22_doc='docs/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22.md'
stage22_status='docs/status/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22_STATUS.md'
stage21_status='docs/status/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
verification_script='scripts/nadia-tokenizer-artifact-verification-contract.sh'
stage22_guard='scripts/test-nadia-tokenizer-artifact-verification-contract-stage-22.sh'
stage21_guard='scripts/test-nadia-tokenizer-artifact-measurement-contract-stage-21.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage22_doc"
require_file "$stage22_status"
require_file "$stage21_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$verification_script"
require_file "$stage22_guard"
require_file "$stage21_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-22 implementation contract' "$stage22_doc"
require_contains 'tokenizer_artifact_verification_contract_command=scripts/nadia-tokenizer-artifact-verification-contract.sh' "$stage22_doc"
require_contains 'installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification' "$stage22_doc"
require_contains 'tokenizer_artifact_verification_contract_status=contract_only' "$stage22_doc"
require_contains 'tokenizer_artifact_verification_authority=0' "$stage22_doc"
require_contains 'requires_future_tokenizer_artifact_binding_contract=1' "$stage22_doc"
require_contains 'tokenizer_artifact_verification_hash_computed=0' "$stage22_doc"
require_contains 'tokenizer_artifact_verification_comparison_performed=0' "$stage22_doc"
require_contains 'tokenizer_artifact_file_opened=0' "$stage22_doc"
require_contains 'prompt_tokenized=0' "$stage22_doc"
require_contains 'sh scripts/test-nadia-tokenizer-artifact-verification-contract-stage-22.sh' "$stage22_doc"

require_contains 'Status: implementation status record' "$stage22_status"
require_contains 'nadia_stage_22_tokenizer_artifact_verification_contract_present=1' "$stage22_status"
require_contains 'nadia_tokenizer_artifact_verification_contract_generator_present=1' "$stage22_status"
require_contains 'tokenizer_artifact_verification_contract_status=contract_only' "$stage22_status"
require_contains 'tokenizer_artifact_verification_promotion_allowed=0' "$stage22_status"

require_contains 'Stage-22: Tokenizer Artifact Verification Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-artifact-verification-contract.sh' "$foundation"
require_contains 'Stage-23: Tokenizer Artifact Binding Contract' "$foundation"
require_contains 'test-nadia-tokenizer-artifact-verification-contract-stage-22.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer artifact verification contract Stage-22 + guardrails' "$foundation_index"
require_contains 'nadia_stage_22_tokenizer_artifact_verification_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer artifact verification contract Stage-22 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer artifact verification contract Stage-22 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer artifact verification contract Stage-22' "$current_status"
require_contains 'Stage-22 now defines a tokenizer artifact verification contract' "$stage21_status"

require_contains 'NADIA TOKENIZER ARTIFACT VERIFICATION CONTRACT' "$verification_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$verification_script"
require_contains 'tokenizer_artifact_verification_contract_status=contract_only' "$verification_script"
require_contains 'requires_future_tokenizer_artifact_binding_contract=1' "$verification_script"
require_contains 'tokenizer_artifact_verification_plan_recorded=1' "$verification_script"
require_contains 'tokenizer_artifact_verification_hash_computed=0' "$verification_script"
require_contains 'tokenizer_artifact_verification_performed=0' "$verification_script"
require_contains 'tokenizer_artifact_verification_comparison_performed=0' "$verification_script"
require_contains 'tokenizer_artifact_verification_digest_match_recorded=0' "$verification_script"
require_contains 'tokenizer_artifact_digest_recorded=0' "$verification_script"
require_contains 'tokenizer_artifact_size_recorded=0' "$verification_script"
require_contains 'tokenizer_artifact_file_opened=0' "$verification_script"
require_contains 'tokenizer_artifact_file_read=0' "$verification_script"
require_contains 'tokenizer_manifest_loaded=0' "$verification_script"
require_contains 'tokenizer_manifest_parsed=0' "$verification_script"
require_contains 'tokenizer_file_opened=0' "$verification_script"
require_contains 'prompt_tokenized=0' "$verification_script"
require_contains 'prompt_evaluated=0' "$verification_script"
require_contains 'token_generation_performed=0' "$verification_script"
require_contains 'inference_performed=0' "$verification_script"
require_contains 'tool_execution_performed=0' "$verification_script"
require_contains 'outside Nadia tokenizer-artifact-verification boundary' "$verification_script"
require_not_contains 'curl ' "$verification_script"
require_not_contains 'wget ' "$verification_script"
require_not_contains 'ssh ' "$verification_script"

require_contains 'tokenizer-artifact-verification' "$apply_script"
require_contains 'scripts/nadia-tokenizer-artifact-verification-contract.sh' "$apply_script"
require_contains 'tokenizer_artifact_verification_contract_stage=22-tokenizer-artifact-verification-contract' "$panel_config"
require_contains 'nadia tokenizer-artifact-verification' "$panel_ui"
require_contains 'latticra-nadia tokenizer-artifact-verification' "$installer_readme"
require_contains 'nadia tokenizer-artifact-verification' "$ui_model"
require_contains 'tokenizer-artifact-verification' "$components_manifest"
require_contains 'nadia-tokenizer-artifact-verification' "$makefile"

sh "$stage21_guard" >/tmp/latticra-nadia-stage22-prereq-stage21-test.out

out="${TMPDIR:-/tmp}/latticra-nadia-stage22-tokenizer-artifact-verification-test"
measurement="${TMPDIR:-/tmp}/latticra-nadia-stage21-tokenizer-artifact-measurement-test/nadia-tokenizer-artifact-measurement-contract-stage21-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$measurement"

NADIA_TOKENIZER_ARTIFACT_VERIFICATION_TIMESTAMP=stage22-test sh "$verification_script" \
  --tokenizer-artifact-measurement "$measurement" \
  --request-class awareness-education \
  --verification-family operator-reviewed-tokenizer-artifact-verification \
  --verification-format contract-only-offline-verification \
  --output "$out" >/tmp/latticra-nadia-stage22-tokenizer-artifact-verification-test.out
verification="$out/nadia-tokenizer-artifact-verification-contract-stage22-test.txt"

require_file "$verification"
require_file "$out/latest-tokenizer-artifact-verification-contract.txt"
require_contains 'NADIA TOKENIZER ARTIFACT VERIFICATION CONTRACT' "$verification"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$verification"
require_contains 'public_name=Nadia' "$verification"
require_contains 'stage=22-tokenizer-artifact-verification-contract' "$verification"
require_contains 'request_class=awareness-education' "$verification"
require_contains 'tokenizer_artifact_verification_contract_status=contract_only' "$verification"
require_contains 'tokenizer_artifact_verification_stage=contract-only' "$verification"
require_contains 'tokenizer_artifact_verification_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_allowed=0' "$verification"
require_contains 'tokenizer_artifact_verification_performed=0' "$verification"
require_contains 'tokenizer_artifact_verification_metadata_present=1' "$verification"
require_contains 'tokenizer_artifact_verification_family=operator-reviewed-tokenizer-artifact-verification' "$verification"
require_contains 'tokenizer_artifact_verification_format=contract-only-offline-verification' "$verification"
require_contains 'tokenizer_artifact_verification_loaded=0' "$verification"
require_contains 'tokenizer_artifact_verification_opened=0' "$verification"
require_contains 'tokenizer_artifact_verification_read=0' "$verification"
require_contains 'tokenizer_artifact_verification_validated=0' "$verification"
require_contains 'tokenizer_artifact_verification_compared=0' "$verification"
require_contains 'tokenizer_artifact_verification_decision=blocked_contract_only' "$verification"
require_contains 'tokenizer_artifact_verification_evidence_present=1' "$verification"
require_contains 'tokenizer_artifact_verification_source_policy=operator-reviewed-offline' "$verification"
require_contains 'tokenizer_artifact_verification_plan_recorded=1' "$verification"
require_contains 'tokenizer_artifact_verification_method_planned=offline-digest-and-size-policy-review' "$verification"
require_contains 'tokenizer_artifact_verification_comparison_performed=0' "$verification"
require_contains 'tokenizer_artifact_verification_result_recorded=0' "$verification"
require_contains 'tokenizer_artifact_verification_digest_match_recorded=0' "$verification"
require_contains 'tokenizer_artifact_verification_size_match_recorded=0' "$verification"
require_contains 'tokenizer_artifact_source_signature_verified=0' "$verification"
require_contains 'requires_tokenizer_artifact_measurement_contract=1' "$verification"
require_contains 'requires_tokenizer_artifact_inventory_contract=1' "$verification"
require_contains 'requires_tokenizer_manifest_contract=1' "$verification"
require_contains 'requires_tokenizer_specification_contract=1' "$verification"
require_contains 'requires_tokenization_boundary_contract=1' "$verification"
require_contains 'requires_future_tokenizer_artifact_binding_contract=1' "$verification"
require_contains 'tokenizer_artifact_verification_promotion_allowed=0' "$verification"
require_contains 'requires_artifact_identity=1' "$verification"
require_contains 'requires_artifact_role_classification=1' "$verification"
require_contains 'requires_measurement_contract_reference=1' "$verification"
require_contains 'requires_inventory_entry_reference=1' "$verification"
require_contains 'requires_expected_digest_policy=1' "$verification"
require_contains 'requires_observed_digest_policy=1' "$verification"
require_contains 'requires_digest_comparison_policy=1' "$verification"
require_contains 'requires_size_comparison_policy=1' "$verification"
require_contains 'requires_source_snapshot_reference=1' "$verification"
require_contains 'requires_license_and_source_review=1' "$verification"
require_contains 'requires_operator_approval_record=1' "$verification"
require_contains 'requires_official_source_snapshot=1' "$verification"
require_contains 'requires_no_runtime_binding=1' "$verification"
require_contains 'requires_refusal_policy_link=1' "$verification"
require_contains 'requires_survivor_centered_language_review=1' "$verification"
require_contains 'tokenizer_artifact_verification_open_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_read_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_hash_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_validation_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_load_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_compare_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_bind_authority=0' "$verification"
require_contains 'tokenizer_artifact_verification_bytes_read=0' "$verification"
require_contains 'tokenizer_artifact_verification_hash_computed=0' "$verification"
require_contains 'tokenizer_artifact_verification_entries_loaded=0' "$verification"
require_contains 'tokenizer_artifact_verification_digest_comparison_performed=0' "$verification"
require_contains 'tokenizer_artifact_verification_size_comparison_performed=0' "$verification"
require_contains 'tokenizer_artifact_verification_expected_digest_loaded=0' "$verification"
require_contains 'tokenizer_artifact_verification_observed_digest_loaded=0' "$verification"
require_contains 'tokenizer_artifact_digest_recorded=0' "$verification"
require_contains 'tokenizer_artifact_size_recorded=0' "$verification"
require_contains 'tokenizer_artifact_path_resolved=0' "$verification"
require_contains 'tokenizer_artifact_scan_performed=0' "$verification"
require_contains 'tokenizer_artifact_stat_performed=0' "$verification"
require_contains 'tokenizer_artifact_file_opened=0' "$verification"
require_contains 'tokenizer_artifact_file_read=0' "$verification"
require_contains 'tokenizer_artifact_bytes_read=0' "$verification"
require_contains 'tokenizer_artifact_hash_computed=0' "$verification"
require_contains 'tokenizer_artifact_measurement_open_authority=0' "$verification"
require_contains 'tokenizer_artifact_measurement_read_authority=0' "$verification"
require_contains 'tokenizer_artifact_measurement_hash_authority=0' "$verification"
require_contains 'tokenizer_artifact_measurement_opened=0' "$verification"
require_contains 'tokenizer_artifact_measurement_read=0' "$verification"
require_contains 'tokenizer_artifact_measurement_performed=0' "$verification"
require_contains 'tokenizer_artifact_measurement_hash_computed=0' "$verification"
require_contains 'tokenizer_manifest_open_authority=0' "$verification"
require_contains 'tokenizer_manifest_read_authority=0' "$verification"
require_contains 'tokenizer_manifest_parse_authority=0' "$verification"
require_contains 'tokenizer_manifest_opened=0' "$verification"
require_contains 'tokenizer_manifest_read=0' "$verification"
require_contains 'tokenizer_manifest_parsed=0' "$verification"
require_contains 'tokenizer_manifest_loaded=0' "$verification"
require_contains 'tokenizer_file_open_authority=0' "$verification"
require_contains 'tokenizer_file_read_authority=0' "$verification"
require_contains 'tokenizer_vocab_load_authority=0' "$verification"
require_contains 'tokenizer_file_opened=0' "$verification"
require_contains 'tokenizer_file_read=0' "$verification"
require_contains 'tokenizer_vocab_loaded=0' "$verification"
require_contains 'future_qa_dialogue_capability_planned=1' "$verification"
require_contains 'qa_dialogue_generated=0' "$verification"
require_contains 'question_generated=0' "$verification"
require_contains 'answer_generated=0' "$verification"
require_contains 'answer_text_generated=0' "$verification"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$verification"
require_contains 'q_and_a_format_required=1' "$verification"
require_contains 'survivor_centered_dialogue_required=1' "$verification"
require_contains 'official_source_grounding_required=1' "$verification"
require_contains 'live_web_lookup_authority=0' "$verification"
require_contains 'topic_yazidi_genocide_awareness=1' "$verification"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$verification"
require_contains 'topic_womens_empowerment=1' "$verification"
require_contains 'sexualized_dialogue_generation=0' "$verification"
require_contains 'graphic_sexual_detail_allowed=0' "$verification"
require_contains 'victim_blaming_allowed=0' "$verification"
require_contains 'genocide_denial_allowed=0' "$verification"
require_contains 'sexual_request_refusal=always' "$verification"
require_contains 'manipulation_resistance=required' "$verification"
require_contains 'prompt_materialized=0' "$verification"
require_contains 'prompt_text_materialized=0' "$verification"
require_contains 'prompt_buffer_allocated=0' "$verification"
require_contains 'prompt_buffer_written=0' "$verification"
require_contains 'prompt_tokenization_authority=0' "$verification"
require_contains 'prompt_tokenization_allowed=0' "$verification"
require_contains 'prompt_tokenized=0' "$verification"
require_contains 'prompt_tokens_created=0' "$verification"
require_contains 'prompt_evaluation_authority=0' "$verification"
require_contains 'prompt_evaluated=0' "$verification"
require_contains 'token_generation_performed=0' "$verification"
require_contains 'inference_performed=0' "$verification"
require_contains 'tool_execution_performed=0' "$verification"
require_contains 'network_authority=0' "$verification"

if NADIA_TOKENIZER_ARTIFACT_VERIFICATION_TIMESTAMP=stage22-reject sh "$verification_script" \
  --tokenizer-artifact-measurement "$measurement" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage22-reject-test.out 2>/tmp/latticra-nadia-stage22-reject-test.err; then
  printf 'nadia tokenizer artifact verification contract stage 22: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-artifact-verification boundary' /tmp/latticra-nadia-stage22-reject-test.err

printf 'nadia_tokenizer_artifact_verification_contract_stage_22: ok\n'
