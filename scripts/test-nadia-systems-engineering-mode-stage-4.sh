#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia systems engineering mode stage 4: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia systems engineering mode stage 4: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia systems engineering mode stage 4: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage4_doc='docs/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md'
stage4_status='docs/status/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
mode_script='scripts/nadia-mode-validate.sh'
stage4_guard='scripts/test-nadia-systems-engineering-mode-stage-4.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage4_doc"
require_file "$stage4_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$mode_script"
require_file "$stage4_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-4 implementation contract' "$stage4_doc"
require_contains 'nadia_stage_4_systems_engineering_mode_present=1' "$stage4_doc"
require_contains 'mode_validation_command=scripts/nadia-mode-validate.sh' "$stage4_doc"
require_contains 'installed_mode_validation_command=latticra-nadia mode-validate' "$stage4_doc"
require_contains 'prompt_evaluated=0' "$stage4_doc"
require_contains 'inference_performed=0' "$stage4_doc"
require_contains 'sh scripts/test-nadia-systems-engineering-mode-stage-4.sh' "$stage4_doc"

require_contains 'Status: implementation status record' "$stage4_status"
require_contains 'nadia_mode_validation_generator_present=1' "$stage4_status"
require_contains 'mode_taxonomy_present=1' "$stage4_status"
require_contains 'mode_allowed=1' "$stage4_status"

require_contains 'Stage-4: Systems Engineering Mode' "$foundation"
require_contains 'scripts/nadia-mode-validate.sh' "$foundation"
require_contains 'NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md' "$foundation_index"
require_contains 'NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md' "$status_index"
require_contains 'nadia_stage_4_systems_engineering_mode_present=1' "$readme"
require_contains 'Latest Nadia systems engineering mode Stage-4 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia systems engineering mode Stage-4 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia systems engineering mode Stage-4' "$current_status"

require_contains 'NADIA MODE VALIDATION' "$mode_script"
require_contains 'mode_allowed=1' "$mode_script"
require_contains 'prompt_evaluated=0' "$mode_script"
require_contains 'inference_performed=0' "$mode_script"
require_contains 'source_mutation_authority=0' "$mode_script"
require_not_contains 'curl ' "$mode_script"
require_not_contains 'wget ' "$mode_script"
require_not_contains 'ssh ' "$mode_script"

require_contains 'mode-validate' "$apply_script"
require_contains 'scripts/nadia-mode-validate.sh' "$apply_script"
require_contains 'systems_engineering_mode_stage=4-systems-engineering-mode-validation' "$panel_config"
require_contains 'nadia mode' "$panel_ui"
require_contains 'latticra-nadia mode-validate' "$installer_readme"
require_contains 'nadia mode' "$ui_model"
require_contains 'mode-validations' "$components_manifest"
require_contains 'nadia-mode' "$makefile"

out='/private/tmp/latticra-nadia-stage4-mode-test'
context_out='/private/tmp/latticra-nadia-stage4-context-test'
runtime_out='/private/tmp/latticra-nadia-stage4-runtime-test'
plan_out='/private/tmp/latticra-nadia-stage4-plan-test'
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage4-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage4-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage4-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" >/tmp/latticra-nadia-stage4-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage4-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage4-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage4-test.txt" \
  --task "systems mode planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage4-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage4-test sh "$mode_script" \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage4-test.txt" \
  --mode runtime-boundary \
  --output "$out" >/tmp/latticra-nadia-stage4-mode-test.out
report="$out/nadia-mode-validation-stage4-test.txt"

require_file "$report"
require_file "$out/latest-mode-validation.txt"
require_contains 'NADIA MODE VALIDATION' "$report"
require_contains 'stage=4-systems-engineering-mode-validation' "$report"
require_contains 'mode=runtime-boundary' "$report"
require_contains 'mode_allowed=1' "$report"
require_contains 'prompt_plan_stage=3-developer-workbench-planning' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'source_mutation_authority=0' "$report"
require_contains 'community_awareness_posture=1' "$report"

printf 'nadia_systems_engineering_mode_stage_4: ok\n'
