#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenizer specification contract stage 18: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer specification contract stage 18: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenizer specification contract stage 18: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage18_doc='docs/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md'
stage18_status='docs/status/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
tokenizer_script='scripts/nadia-tokenizer-specification-contract.sh'
stage18_guard='scripts/test-nadia-tokenizer-specification-contract-stage-18.sh'
stage17_guard='scripts/test-nadia-tokenization-boundary-contract-stage-17.sh'
stage17_status='docs/status/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17_STATUS.md'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage18_doc"
require_file "$stage18_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$tokenizer_script"
require_file "$stage18_guard"
require_file "$stage17_guard"
require_file "$stage17_status"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-18 implementation contract' "$stage18_doc"
require_contains 'tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh' "$stage18_doc"
require_contains 'installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification' "$stage18_doc"
require_contains 'tokenizer_specification_contract_status=contract_only' "$stage18_doc"
require_contains 'tokenizer_specification_authority=0' "$stage18_doc"
require_contains 'requires_future_tokenizer_manifest_contract=1' "$stage18_doc"
require_contains 'tokenizer_file_opened=0' "$stage18_doc"
require_contains 'prompt_tokenized=0' "$stage18_doc"
require_contains 'sh scripts/test-nadia-tokenizer-specification-contract-stage-18.sh' "$stage18_doc"

require_contains 'Status: implementation status record' "$stage18_status"
require_contains 'nadia_stage_18_tokenizer_specification_contract_present=1' "$stage18_status"
require_contains 'nadia_tokenizer_specification_contract_generator_present=1' "$stage18_status"
require_contains 'tokenizer_specification_contract_status=contract_only' "$stage18_status"
require_contains 'tokenizer_specification_promotion_allowed=0' "$stage18_status"

require_contains 'Stage-18: Tokenizer Specification Contract' "$foundation"
require_contains 'scripts/nadia-tokenizer-specification-contract.sh' "$foundation"
require_contains 'Stage-19: Tokenizer Manifest Contract' "$foundation"
require_contains 'test-nadia-tokenizer-specification-contract-stage-18.sh' "$foundation"
require_contains 'NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md' "$foundation_index"
require_contains 'NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18_STATUS.md' "$status_index"
require_contains 'Nadia tokenizer specification contract Stage-18 + guardrails' "$foundation_index"
require_contains 'nadia_stage_18_tokenizer_specification_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenizer specification contract Stage-18 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenizer specification contract Stage-18 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenizer specification contract Stage-18' "$current_status"
require_contains 'Stage-18 now defines a tokenizer specification contract' "$stage17_status"

require_contains 'NADIA TOKENIZER SPECIFICATION CONTRACT' "$tokenizer_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenizer_script"
require_contains 'tokenizer_specification_contract_status=contract_only' "$tokenizer_script"
require_contains 'requires_future_tokenizer_manifest_contract=1' "$tokenizer_script"
require_contains 'tokenizer_file_opened=0' "$tokenizer_script"
require_contains 'prompt_tokenized=0' "$tokenizer_script"
require_contains 'prompt_evaluated=0' "$tokenizer_script"
require_contains 'token_generation_performed=0' "$tokenizer_script"
require_contains 'inference_performed=0' "$tokenizer_script"
require_contains 'tool_execution_performed=0' "$tokenizer_script"
require_contains 'outside Nadia tokenizer-specification boundary' "$tokenizer_script"
require_not_contains 'curl ' "$tokenizer_script"
require_not_contains 'wget ' "$tokenizer_script"
require_not_contains 'ssh ' "$tokenizer_script"

require_contains 'tokenizer-specification' "$apply_script"
require_contains 'scripts/nadia-tokenizer-specification-contract.sh' "$apply_script"
require_contains 'tokenizer_specification_contract_stage=18-tokenizer-specification-contract' "$panel_config"
require_contains 'nadia tokenizer-specification' "$panel_ui"
require_contains 'latticra-nadia tokenizer-specification' "$installer_readme"
require_contains 'nadia tokenizer-specification' "$ui_model"
require_contains 'tokenizer-specification' "$components_manifest"
require_contains 'nadia-tokenizer-specification' "$makefile"

sh "$stage17_guard" >/tmp/latticra-nadia-stage18-prereq-stage17-test.out

out="${TMPDIR:-/tmp}/latticra-nadia-stage18-tokenizer-test"
tokenization="${TMPDIR:-/tmp}/latticra-nadia-stage17-tokenization-test/nadia-tokenization-boundary-contract-stage17-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$tokenization"

NADIA_TOKENIZER_SPECIFICATION_TIMESTAMP=stage18-test sh "$tokenizer_script" \
  --tokenization-boundary "$tokenization" \
  --request-class awareness-education \
  --tokenizer-family model-compatible-tokenizer \
  --tokenizer-format operator-reviewed-offline-specification \
  --output "$out" >/tmp/latticra-nadia-stage18-tokenizer-test.out
tokenizer="$out/nadia-tokenizer-specification-contract-stage18-test.txt"

require_file "$tokenizer"
require_file "$out/latest-tokenizer-specification-contract.txt"
require_contains 'NADIA TOKENIZER SPECIFICATION CONTRACT' "$tokenizer"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenizer"
require_contains 'public_name=Nadia' "$tokenizer"
require_contains 'stage=18-tokenizer-specification-contract' "$tokenizer"
require_contains 'request_class=awareness-education' "$tokenizer"
require_contains 'tokenizer_specification_contract_status=contract_only' "$tokenizer"
require_contains 'tokenizer_specification_stage=contract-only' "$tokenizer"
require_contains 'tokenizer_specification_authority=0' "$tokenizer"
require_contains 'tokenizer_specification_allowed=0' "$tokenizer"
require_contains 'tokenizer_specification_performed=0' "$tokenizer"
require_contains 'tokenizer_specification_metadata_present=1' "$tokenizer"
require_contains 'tokenizer_family=model-compatible-tokenizer' "$tokenizer"
require_contains 'tokenizer_format=operator-reviewed-offline-specification' "$tokenizer"
require_contains 'tokenizer_specification_decision=blocked_contract_only' "$tokenizer"
require_contains 'tokenizer_specification_evidence_present=1' "$tokenizer"
require_contains 'tokenizer_source_policy=operator-reviewed-offline' "$tokenizer"
require_contains 'tokenizer_path_recorded=0' "$tokenizer"
require_contains 'tokenizer_manifest_loaded=0' "$tokenizer"
require_contains 'tokenizer_file_measurement_performed=0' "$tokenizer"
require_contains 'requires_tokenization_boundary_contract=1' "$tokenizer"
require_contains 'requires_prompt_evaluation_handoff_contract=1' "$tokenizer"
require_contains 'requires_awareness_dialogue_contract=1' "$tokenizer"
require_contains 'requires_prompt_materialization_contract=1' "$tokenizer"
require_contains 'requires_prompt_receipt_contract=1' "$tokenizer"
require_contains 'requires_prompt_buffer_boundary=1' "$tokenizer"
require_contains 'requires_protective_safety_boundary=1' "$tokenizer"
require_contains 'requires_operator_review=1' "$tokenizer"
require_contains 'requires_official_source_snapshot=1' "$tokenizer"
require_contains 'requires_future_tokenizer_manifest_contract=1' "$tokenizer"
require_contains 'tokenizer_specification_promotion_allowed=0' "$tokenizer"
require_contains 'requires_model_tokenizer_compatibility_review=1' "$tokenizer"
require_contains 'requires_unicode_policy_review=1' "$tokenizer"
require_contains 'requires_normalization_policy_review=1' "$tokenizer"
require_contains 'requires_special_token_policy_review=1' "$tokenizer"
require_contains 'requires_bos_eos_policy_review=1' "$tokenizer"
require_contains 'requires_chat_template_policy_review=1' "$tokenizer"
require_contains 'requires_prompt_template_boundary=1' "$tokenizer"
require_contains 'requires_context_window_policy_review=1' "$tokenizer"
require_contains 'requires_stop_sequence_policy_review=1' "$tokenizer"
require_contains 'future_qa_dialogue_capability_planned=1' "$tokenizer"
require_contains 'qa_dialogue_generated=0' "$tokenizer"
require_contains 'question_generated=0' "$tokenizer"
require_contains 'answer_generated=0' "$tokenizer"
require_contains 'answer_text_generated=0' "$tokenizer"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$tokenizer"
require_contains 'q_and_a_format_required=1' "$tokenizer"
require_contains 'survivor_centered_dialogue_required=1' "$tokenizer"
require_contains 'official_source_grounding_required=1' "$tokenizer"
require_contains 'live_web_lookup_authority=0' "$tokenizer"
require_contains 'topic_yazidi_genocide_awareness=1' "$tokenizer"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$tokenizer"
require_contains 'topic_womens_empowerment=1' "$tokenizer"
require_contains 'sexualized_dialogue_generation=0' "$tokenizer"
require_contains 'graphic_sexual_detail_allowed=0' "$tokenizer"
require_contains 'victim_blaming_allowed=0' "$tokenizer"
require_contains 'genocide_denial_allowed=0' "$tokenizer"
require_contains 'medical_advice_authority=0' "$tokenizer"
require_contains 'legal_advice_authority=0' "$tokenizer"
require_contains 'trauma_counseling_authority=0' "$tokenizer"
require_contains 'sexual_request_refusal=always' "$tokenizer"
require_contains 'manipulation_resistance=required' "$tokenizer"
require_contains 'tokenizer_file_open_authority=0' "$tokenizer"
require_contains 'tokenizer_file_read_authority=0' "$tokenizer"
require_contains 'tokenizer_vocab_load_authority=0' "$tokenizer"
require_contains 'tokenizer_file_opened=0' "$tokenizer"
require_contains 'tokenizer_file_read=0' "$tokenizer"
require_contains 'tokenizer_vocab_loaded=0' "$tokenizer"
require_contains 'tokenizer_bytes_read=0' "$tokenizer"
require_contains 'tokenizer_hash_computed=0' "$tokenizer"
require_contains 'prompt_materialized=0' "$tokenizer"
require_contains 'prompt_text_materialized=0' "$tokenizer"
require_contains 'prompt_buffer_allocated=0' "$tokenizer"
require_contains 'prompt_buffer_written=0' "$tokenizer"
require_contains 'prompt_tokenization_authority=0' "$tokenizer"
require_contains 'prompt_tokenization_allowed=0' "$tokenizer"
require_contains 'prompt_tokenized=0' "$tokenizer"
require_contains 'prompt_tokens_created=0' "$tokenizer"
require_contains 'prompt_evaluation_authority=0' "$tokenizer"
require_contains 'prompt_evaluated=0' "$tokenizer"
require_contains 'token_generation_performed=0' "$tokenizer"
require_contains 'inference_performed=0' "$tokenizer"
require_contains 'tool_execution_performed=0' "$tokenizer"
require_contains 'network_authority=0' "$tokenizer"

if NADIA_TOKENIZER_SPECIFICATION_TIMESTAMP=stage18-reject sh "$tokenizer_script" \
  --tokenization-boundary "$tokenization" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage18-reject-test.out 2>/tmp/latticra-nadia-stage18-reject-test.err; then
  printf 'nadia tokenizer specification contract stage 18: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenizer-specification boundary' /tmp/latticra-nadia-stage18-reject-test.err

printf 'nadia_tokenizer_specification_contract_stage_18: ok\n'
