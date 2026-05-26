#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia tokenization boundary contract stage 17: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenization boundary contract stage 17: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia tokenization boundary contract stage 17: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage17_doc='docs/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md'
stage17_status='docs/status/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
tokenization_script='scripts/nadia-tokenization-boundary-contract.sh'
stage17_guard='scripts/test-nadia-tokenization-boundary-contract-stage-17.sh'
stage16_guard='scripts/test-nadia-prompt-evaluation-handoff-contract-stage-16.sh'
stage16_status='docs/status/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16_STATUS.md'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage17_doc"
require_file "$stage17_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$tokenization_script"
require_file "$stage17_guard"
require_file "$stage16_guard"
require_file "$stage16_status"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-17 implementation contract' "$stage17_doc"
require_contains 'tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh' "$stage17_doc"
require_contains 'installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary' "$stage17_doc"
require_contains 'tokenization_boundary_contract_status=contract_only' "$stage17_doc"
require_contains 'tokenization_boundary_authority=0' "$stage17_doc"
require_contains 'requires_future_tokenizer_specification_contract=1' "$stage17_doc"
require_contains 'prompt_tokenized=0' "$stage17_doc"
require_contains 'prompt_evaluated=0' "$stage17_doc"
require_contains 'sh scripts/test-nadia-tokenization-boundary-contract-stage-17.sh' "$stage17_doc"

require_contains 'Status: implementation status record' "$stage17_status"
require_contains 'nadia_stage_17_tokenization_boundary_contract_present=1' "$stage17_status"
require_contains 'nadia_tokenization_boundary_contract_generator_present=1' "$stage17_status"
require_contains 'tokenization_boundary_contract_status=contract_only' "$stage17_status"
require_contains 'tokenization_boundary_promotion_allowed=0' "$stage17_status"

require_contains 'Stage-17: Tokenization Boundary Contract' "$foundation"
require_contains 'scripts/nadia-tokenization-boundary-contract.sh' "$foundation"
require_contains 'Stage-18: Tokenizer Specification Contract' "$foundation"
require_contains 'test-nadia-tokenization-boundary-contract-stage-17.sh' "$foundation"
require_contains 'NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md' "$foundation_index"
require_contains 'NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17_STATUS.md' "$status_index"
require_contains 'Nadia tokenization boundary contract Stage-17 + guardrails' "$foundation_index"
require_contains 'nadia_stage_17_tokenization_boundary_contract_present=1' "$readme"
require_contains 'Latest Nadia tokenization boundary contract Stage-17 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia tokenization boundary contract Stage-17 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia tokenization boundary contract Stage-17' "$current_status"
require_contains 'Stage-17 now defines a tokenization boundary contract' "$stage16_status"

require_contains 'NADIA TOKENIZATION BOUNDARY CONTRACT' "$tokenization_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenization_script"
require_contains 'tokenization_boundary_contract_status=contract_only' "$tokenization_script"
require_contains 'requires_future_tokenizer_specification_contract=1' "$tokenization_script"
require_contains 'prompt_tokenized=0' "$tokenization_script"
require_contains 'prompt_evaluated=0' "$tokenization_script"
require_contains 'token_generation_performed=0' "$tokenization_script"
require_contains 'inference_performed=0' "$tokenization_script"
require_contains 'tool_execution_performed=0' "$tokenization_script"
require_contains 'outside Nadia tokenization-boundary boundary' "$tokenization_script"
require_not_contains 'curl ' "$tokenization_script"
require_not_contains 'wget ' "$tokenization_script"
require_not_contains 'ssh ' "$tokenization_script"

require_contains 'tokenization-boundary' "$apply_script"
require_contains 'scripts/nadia-tokenization-boundary-contract.sh' "$apply_script"
require_contains 'tokenization_boundary_contract_stage=17-tokenization-boundary-contract' "$panel_config"
require_contains 'nadia tokenization-boundary' "$panel_ui"
require_contains 'latticra-nadia tokenization-boundary' "$installer_readme"
require_contains 'nadia tokenization-boundary' "$ui_model"
require_contains 'tokenization-boundary' "$components_manifest"
require_contains 'nadia-tokenization-boundary' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage17-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

log_out="$tmp_root/stage17/logs"
mkdir -p "$log_out"
NADIA_TEST_TMP_ROOT="$tmp_root" sh "$stage16_guard" >"$log_out/prereq-stage16.out"

out="$tmp_root/stage17/tokenization"
handoff="$tmp_root/stage16/handoff/nadia-prompt-evaluation-handoff-contract-stage16-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$handoff"

NADIA_TOKENIZATION_BOUNDARY_TIMESTAMP=stage17-test sh "$tokenization_script" \
  --prompt-evaluation-handoff "$handoff" \
  --request-class awareness-education \
  --output "$out" >"$log_out/tokenization.out"
tokenization="$out/nadia-tokenization-boundary-contract-stage17-test.txt"

require_file "$tokenization"
require_file "$out/latest-tokenization-boundary-contract.txt"
require_contains 'NADIA TOKENIZATION BOUNDARY CONTRACT' "$tokenization"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$tokenization"
require_contains 'public_name=Nadia' "$tokenization"
require_contains 'stage=17-tokenization-boundary-contract' "$tokenization"
require_contains 'request_class=awareness-education' "$tokenization"
require_contains 'tokenization_boundary_contract_status=contract_only' "$tokenization"
require_contains 'tokenization_boundary_stage=contract-only' "$tokenization"
require_contains 'tokenization_boundary_authority=0' "$tokenization"
require_contains 'tokenization_boundary_allowed=0' "$tokenization"
require_contains 'tokenization_boundary_performed=0' "$tokenization"
require_contains 'prompt_tokenization_authority=0' "$tokenization"
require_contains 'prompt_tokenization_allowed=0' "$tokenization"
require_contains 'prompt_tokenized=0' "$tokenization"
require_contains 'prompt_tokens_created=0' "$tokenization"
require_contains 'tokenizer_file_opened=0' "$tokenization"
require_contains 'tokenizer_vocab_loaded=0' "$tokenization"
require_contains 'prompt_evaluation_authority=0' "$tokenization"
require_contains 'prompt_evaluated=0' "$tokenization"
require_contains 'tokenization_decision=blocked_contract_only' "$tokenization"
require_contains 'tokenization_evidence_present=1' "$tokenization"
require_contains 'requires_prompt_evaluation_handoff_contract=1' "$tokenization"
require_contains 'requires_awareness_dialogue_contract=1' "$tokenization"
require_contains 'requires_prompt_materialization_contract=1' "$tokenization"
require_contains 'requires_prompt_receipt_contract=1' "$tokenization"
require_contains 'requires_prompt_buffer_boundary=1' "$tokenization"
require_contains 'requires_protective_safety_boundary=1' "$tokenization"
require_contains 'requires_operator_review=1' "$tokenization"
require_contains 'requires_official_source_snapshot=1' "$tokenization"
require_contains 'requires_future_tokenizer_specification_contract=1' "$tokenization"
require_contains 'tokenization_boundary_promotion_allowed=0' "$tokenization"
require_contains 'future_qa_dialogue_capability_planned=1' "$tokenization"
require_contains 'qa_dialogue_generated=0' "$tokenization"
require_contains 'question_generated=0' "$tokenization"
require_contains 'answer_generated=0' "$tokenization"
require_contains 'answer_text_generated=0' "$tokenization"
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
require_contains 'medical_advice_authority=0' "$tokenization"
require_contains 'legal_advice_authority=0' "$tokenization"
require_contains 'trauma_counseling_authority=0' "$tokenization"
require_contains 'sexual_request_refusal=always' "$tokenization"
require_contains 'manipulation_resistance=required' "$tokenization"
require_contains 'prompt_materialized=0' "$tokenization"
require_contains 'prompt_text_materialized=0' "$tokenization"
require_contains 'prompt_buffer_allocated=0' "$tokenization"
require_contains 'prompt_buffer_written=0' "$tokenization"
require_contains 'token_generation_performed=0' "$tokenization"
require_contains 'inference_performed=0' "$tokenization"
require_contains 'tool_execution_performed=0' "$tokenization"
require_contains 'network_authority=0' "$tokenization"

if NADIA_TOKENIZATION_BOUNDARY_TIMESTAMP=stage17-reject sh "$tokenization_script" \
  --prompt-evaluation-handoff "$handoff" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia tokenization boundary contract stage 17: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia tokenization-boundary boundary' "$log_out/reject.err"

printf 'nadia_tokenization_boundary_contract_stage_17: ok\n'
