#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia awareness dialogue contract stage 15: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia awareness dialogue contract stage 15: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia awareness dialogue contract stage 15: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage15_doc='docs/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md'
stage15_status='docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
awareness_script='scripts/nadia-awareness-dialogue-contract.sh'
stage15_guard='scripts/test-nadia-awareness-dialogue-contract-stage-15.sh'
stage14_guard='scripts/test-nadia-prompt-materialization-contract-stage-14.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage15_doc"
require_file "$stage15_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$awareness_script"
require_file "$stage15_guard"
require_file "$stage14_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-15 implementation contract' "$stage15_doc"
require_contains 'awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh' "$stage15_doc"
require_contains 'installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue' "$stage15_doc"
require_contains 'future_qa_dialogue_capability_planned=1' "$stage15_doc"
require_contains 'q_and_a_format_required=1' "$stage15_doc"
require_contains 'survivor_centered_dialogue_required=1' "$stage15_doc"
require_contains 'topic_yazidi_genocide_awareness=1' "$stage15_doc"
require_contains 'topic_womens_empowerment=1' "$stage15_doc"
require_contains 'graphic_sexual_detail_allowed=0' "$stage15_doc"
require_contains 'qa_dialogue_generated=0' "$stage15_doc"
require_contains 'sh scripts/test-nadia-awareness-dialogue-contract-stage-15.sh' "$stage15_doc"

require_contains 'Status: implementation status record' "$stage15_status"
require_contains 'nadia_awareness_dialogue_contract_generator_present=1' "$stage15_status"
require_contains 'awareness_dialogue_contract_status=contract_only' "$stage15_status"
require_contains 'awareness_dialogue_promotion_allowed=0' "$stage15_status"

require_contains 'Stage-15: Awareness Dialogue Contract' "$foundation"
require_contains 'scripts/nadia-awareness-dialogue-contract.sh' "$foundation"
require_contains 'NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md' "$foundation_index"
require_contains 'NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md' "$status_index"
require_contains 'nadia_stage_15_awareness_dialogue_contract_present=1' "$readme"
require_contains 'implementation_name=Nadia Witness Foundation' "$readme"
require_contains 'Latest Nadia awareness dialogue contract Stage-15 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia awareness dialogue contract Stage-15 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia awareness dialogue contract Stage-15' "$current_status"

require_contains 'NADIA AWARENESS DIALOGUE CONTRACT' "$awareness_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$awareness_script"
require_contains 'public_name=Nadia' "$awareness_script"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$awareness_script"
require_contains 'source_nadia_initiative_home=https://www.nadiasinitiative.org/home' "$awareness_script"
require_contains 'topic_yazidi_genocide_awareness=1' "$awareness_script"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$awareness_script"
require_contains 'topic_sinjar_reconstruction=1' "$awareness_script"
require_contains 'topic_wash_clean_water_sanitation_hygiene=1' "$awareness_script"
require_contains 'sexualized_dialogue_generation=0' "$awareness_script"
require_contains 'graphic_sexual_detail_allowed=0' "$awareness_script"
require_contains 'qa_dialogue_generated=0' "$awareness_script"
require_contains 'inference_performed=0' "$awareness_script"
require_not_contains 'curl ' "$awareness_script"
require_not_contains 'wget ' "$awareness_script"
require_not_contains 'ssh ' "$awareness_script"

require_contains 'awareness-dialogue' "$apply_script"
require_contains 'scripts/nadia-awareness-dialogue-contract.sh' "$apply_script"
require_contains 'awareness_dialogue_contract_stage=15-awareness-dialogue-contract' "$panel_config"
require_contains 'nadia awareness-dialogue' "$panel_ui"
require_contains 'latticra-nadia awareness-dialogue' "$installer_readme"
require_contains 'nadia awareness-dialogue' "$ui_model"
require_contains 'awareness-dialogue' "$components_manifest"
require_contains 'nadia-awareness-dialogue' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage15-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

log_out="$tmp_root/stage15/logs"
mkdir -p "$log_out"
NADIA_TEST_TMP_ROOT="$tmp_root" sh "$stage14_guard" >"$log_out/prereq-stage14.out"

out="$tmp_root/stage15/awareness"
materialization="$tmp_root/stage14/materialization/nadia-prompt-materialization-contract-stage14-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$materialization"

NADIA_AWARENESS_DIALOGUE_TIMESTAMP=stage15-test sh "$awareness_script" \
  --prompt-materialization "$materialization" \
  --request-class awareness-education \
  --output "$out" >"$log_out/awareness.out"
awareness="$out/nadia-awareness-dialogue-contract-stage15-test.txt"

require_file "$awareness"
require_file "$out/latest-awareness-dialogue-contract.txt"
require_contains 'NADIA AWARENESS DIALOGUE CONTRACT' "$awareness"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$awareness"
require_contains 'public_name=Nadia' "$awareness"
require_contains 'stage=15-awareness-dialogue-contract' "$awareness"
require_contains 'request_class=awareness-education' "$awareness"
require_contains 'awareness_dialogue_contract_status=contract_only' "$awareness"
require_contains 'future_qa_dialogue_capability_planned=1' "$awareness"
require_contains 'awareness_dialogue_authority=0' "$awareness"
require_contains 'dialogue_generation_authority=0' "$awareness"
require_contains 'qa_dialogue_generated=0' "$awareness"
require_contains 'answer_text_generated=0' "$awareness"
require_contains 'prompt_materialization_stage=14-prompt-materialization-contract' "$awareness"
require_contains 'prompt_receipt_stage=13-prompt-receipt-contract' "$awareness"
require_contains 'dialogue_scope=official-nadia-initiative-awareness-work' "$awareness"
require_contains 'dialogue_format=question-and-answer' "$awareness"
require_contains 'q_and_a_format_required=1' "$awareness"
require_contains 'survivor_centered_dialogue_required=1' "$awareness"
require_contains 'official_source_grounding_required=1' "$awareness"
require_contains 'source_snapshot_policy=operator-reviewed-offline' "$awareness"
require_contains 'live_web_lookup_authority=0' "$awareness"
require_contains 'topic_yazidi_genocide_awareness=1' "$awareness"
require_contains 'topic_survivor_voice_and_dignity=1' "$awareness"
require_contains 'topic_conflict_related_sexual_violence_awareness_non_graphic=1' "$awareness"
require_contains 'topic_genocide_prevention=1' "$awareness"
require_contains 'topic_justice_and_accountability=1' "$awareness"
require_contains 'topic_sinjar_reconstruction=1' "$awareness"
require_contains 'topic_education_restoration=1' "$awareness"
require_contains 'topic_healthcare_and_mental_health=1' "$awareness"
require_contains 'topic_livelihoods_and_food_security=1' "$awareness"
require_contains 'topic_wash_clean_water_sanitation_hygiene=1' "$awareness"
require_contains 'topic_womens_empowerment=1' "$awareness"
require_contains 'topic_cultural_preservation_and_memorialization=1' "$awareness"
require_contains 'sexualized_dialogue_generation=0' "$awareness"
require_contains 'graphic_sexual_detail_allowed=0' "$awareness"
require_contains 'victim_blaming_allowed=0' "$awareness"
require_contains 'genocide_denial_allowed=0' "$awareness"
require_contains 'medical_advice_authority=0' "$awareness"
require_contains 'legal_advice_authority=0' "$awareness"
require_contains 'trauma_counseling_authority=0' "$awareness"
require_contains 'sexual_request_refusal=always' "$awareness"
require_contains 'prompt_materialized=0' "$awareness"
require_contains 'prompt_tokenized=0' "$awareness"
require_contains 'prompt_evaluated=0' "$awareness"
require_contains 'token_generation_performed=0' "$awareness"
require_contains 'inference_performed=0' "$awareness"
require_contains 'tool_execution_performed=0' "$awareness"
require_contains 'network_authority=0' "$awareness"

if NADIA_AWARENESS_DIALOGUE_TIMESTAMP=stage15-reject sh "$awareness_script" \
  --prompt-materialization "$materialization" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia awareness dialogue contract stage 15: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia awareness-dialogue boundary' "$log_out/reject.err"

printf 'nadia_awareness_dialogue_contract_stage_15: ok\n'
