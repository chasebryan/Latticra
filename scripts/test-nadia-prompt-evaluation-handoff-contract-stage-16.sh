#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation handoff contract stage 16: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation handoff contract stage 16: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation handoff contract stage 16: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage16_doc='docs/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md'
stage16_status='docs/status/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
handoff_script='scripts/nadia-prompt-evaluation-handoff-contract.sh'
stage16_guard='scripts/test-nadia-prompt-evaluation-handoff-contract-stage-16.sh'
stage15_guard='scripts/test-nadia-awareness-dialogue-contract-stage-15.sh'
stage15_status='docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage16_doc"
require_file "$stage16_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$handoff_script"
require_file "$stage16_guard"
require_file "$stage15_guard"
require_file "$stage15_status"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-16 implementation contract' "$stage16_doc"
require_contains 'prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh' "$stage16_doc"
require_contains 'installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff' "$stage16_doc"
require_contains 'prompt_evaluation_handoff_contract_status=contract_only' "$stage16_doc"
require_contains 'prompt_evaluation_handoff_authority=0' "$stage16_doc"
require_contains 'requires_future_tokenization_contract=1' "$stage16_doc"
require_contains 'prompt_evaluated=0' "$stage16_doc"
require_contains 'qa_dialogue_generated=0' "$stage16_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-handoff-contract-stage-16.sh' "$stage16_doc"

require_contains 'Status: implementation status record' "$stage16_status"
require_contains 'nadia_stage_16_prompt_evaluation_handoff_contract_present=1' "$stage16_status"
require_contains 'nadia_prompt_evaluation_handoff_contract_generator_present=1' "$stage16_status"
require_contains 'prompt_evaluation_handoff_contract_status=contract_only' "$stage16_status"
require_contains 'prompt_evaluation_handoff_promotion_allowed=0' "$stage16_status"

require_contains 'Stage-16: Prompt Evaluation Handoff Contract' "$foundation"
require_contains 'scripts/nadia-prompt-evaluation-handoff-contract.sh' "$foundation"
require_contains 'Stage-17: Tokenization Boundary Contract' "$foundation"
require_contains 'test-nadia-prompt-evaluation-handoff-contract-stage-16.sh' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16_STATUS.md' "$status_index"
require_contains 'Nadia prompt evaluation handoff contract Stage-16 + guardrails' "$foundation_index"
require_contains 'nadia_stage_16_prompt_evaluation_handoff_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt evaluation handoff contract Stage-16 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation handoff contract Stage-16 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt evaluation handoff contract Stage-16' "$current_status"
require_contains 'Stage-16 now defines a prompt-evaluation handoff contract' "$stage15_status"

require_contains 'NADIA PROMPT EVALUATION HANDOFF CONTRACT' "$handoff_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$handoff_script"
require_contains 'prompt_evaluation_handoff_contract_status=contract_only' "$handoff_script"
require_contains 'requires_future_tokenization_contract=1' "$handoff_script"
require_contains 'qa_dialogue_generated=0' "$handoff_script"
require_contains 'prompt_evaluated=0' "$handoff_script"
require_contains 'token_generation_performed=0' "$handoff_script"
require_contains 'inference_performed=0' "$handoff_script"
require_contains 'tool_execution_performed=0' "$handoff_script"
require_contains 'outside Nadia prompt-evaluation-handoff boundary' "$handoff_script"
require_not_contains 'curl ' "$handoff_script"
require_not_contains 'wget ' "$handoff_script"
require_not_contains 'ssh ' "$handoff_script"

require_contains 'prompt-evaluation-handoff' "$apply_script"
require_contains 'scripts/nadia-prompt-evaluation-handoff-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_handoff_contract_stage=16-prompt-evaluation-handoff-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-handoff' "$panel_ui"
require_contains 'latticra-nadia prompt-evaluation-handoff' "$installer_readme"
require_contains 'nadia prompt-evaluation-handoff' "$ui_model"
require_contains 'prompt-evaluation-handoff' "$components_manifest"
require_contains 'nadia-prompt-evaluation-handoff' "$makefile"

sh "$stage15_guard" >/tmp/latticra-nadia-stage16-prereq-stage15-test.out

out="${TMPDIR:-/tmp}/latticra-nadia-stage16-handoff-test"
awareness="${TMPDIR:-/tmp}/latticra-nadia-stage15-awareness-test/nadia-awareness-dialogue-contract-stage15-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$awareness"

NADIA_PROMPT_EVALUATION_HANDOFF_TIMESTAMP=stage16-test sh "$handoff_script" \
  --awareness-dialogue "$awareness" \
  --request-class awareness-education \
  --output "$out" >/tmp/latticra-nadia-stage16-handoff-test.out
handoff="$out/nadia-prompt-evaluation-handoff-contract-stage16-test.txt"

require_file "$handoff"
require_file "$out/latest-prompt-evaluation-handoff-contract.txt"
require_contains 'NADIA PROMPT EVALUATION HANDOFF CONTRACT' "$handoff"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$handoff"
require_contains 'public_name=Nadia' "$handoff"
require_contains 'stage=16-prompt-evaluation-handoff-contract' "$handoff"
require_contains 'request_class=awareness-education' "$handoff"
require_contains 'prompt_evaluation_handoff_contract_status=contract_only' "$handoff"
require_contains 'prompt_evaluation_handoff_stage=contract-only' "$handoff"
require_contains 'prompt_evaluation_handoff_authority=0' "$handoff"
require_contains 'prompt_evaluation_handoff_allowed=0' "$handoff"
require_contains 'prompt_evaluation_handoff_performed=0' "$handoff"
require_contains 'prompt_evaluation_authority=0' "$handoff"
require_contains 'prompt_evaluated=0' "$handoff"
require_contains 'evaluation_handoff_decision=blocked_contract_only' "$handoff"
require_contains 'evaluation_handoff_evidence_present=1' "$handoff"
require_contains 'requires_awareness_dialogue_contract=1' "$handoff"
require_contains 'requires_prompt_materialization_contract=1' "$handoff"
require_contains 'requires_prompt_receipt_contract=1' "$handoff"
require_contains 'requires_protective_safety_boundary=1' "$handoff"
require_contains 'requires_operator_review=1' "$handoff"
require_contains 'requires_official_source_snapshot=1' "$handoff"
require_contains 'requires_future_tokenization_contract=1' "$handoff"
require_contains 'prompt_evaluation_handoff_promotion_allowed=0' "$handoff"
require_contains 'future_qa_dialogue_capability_planned=1' "$handoff"
require_contains 'qa_dialogue_generated=0' "$handoff"
require_contains 'question_generated=0' "$handoff"
require_contains 'answer_generated=0' "$handoff"
require_contains 'answer_text_generated=0' "$handoff"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$handoff"
require_contains 'q_and_a_format_required=1' "$handoff"
require_contains 'survivor_centered_dialogue_required=1' "$handoff"
require_contains 'official_source_grounding_required=1' "$handoff"
require_contains 'live_web_lookup_authority=0' "$handoff"
require_contains 'topic_yazidi_genocide_awareness=1' "$handoff"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$handoff"
require_contains 'topic_womens_empowerment=1' "$handoff"
require_contains 'sexualized_dialogue_generation=0' "$handoff"
require_contains 'graphic_sexual_detail_allowed=0' "$handoff"
require_contains 'victim_blaming_allowed=0' "$handoff"
require_contains 'genocide_denial_allowed=0' "$handoff"
require_contains 'medical_advice_authority=0' "$handoff"
require_contains 'legal_advice_authority=0' "$handoff"
require_contains 'trauma_counseling_authority=0' "$handoff"
require_contains 'sexual_request_refusal=always' "$handoff"
require_contains 'manipulation_resistance=required' "$handoff"
require_contains 'prompt_materialized=0' "$handoff"
require_contains 'prompt_tokenized=0' "$handoff"
require_contains 'token_generation_performed=0' "$handoff"
require_contains 'inference_performed=0' "$handoff"
require_contains 'tool_execution_performed=0' "$handoff"
require_contains 'network_authority=0' "$handoff"

if NADIA_PROMPT_EVALUATION_HANDOFF_TIMESTAMP=stage16-reject sh "$handoff_script" \
  --awareness-dialogue "$awareness" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage16-reject-test.out 2>/tmp/latticra-nadia-stage16-reject-test.err; then
  printf 'nadia prompt evaluation handoff contract stage 16: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-handoff boundary' /tmp/latticra-nadia-stage16-reject-test.err

printf 'nadia_prompt_evaluation_handoff_contract_stage_16: ok\n'
