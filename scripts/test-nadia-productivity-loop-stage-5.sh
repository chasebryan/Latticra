#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia productivity loop stage 5: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia productivity loop stage 5: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia productivity loop stage 5: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage5_doc='docs/NADIA_PRODUCTIVITY_LOOP_STAGE_5.md'
stage5_status='docs/status/NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
ledger_script='scripts/nadia-productivity-ledger.sh'
stage5_guard='scripts/test-nadia-productivity-loop-stage-5.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage5_doc"
require_file "$stage5_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$ledger_script"
require_file "$stage5_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-5 implementation contract' "$stage5_doc"
require_contains 'nadia_stage_5_productivity_loop_present=1' "$stage5_doc"
require_contains 'productivity_ledger_command=scripts/nadia-productivity-ledger.sh' "$stage5_doc"
require_contains 'installed_productivity_ledger_command=latticra-nadia productivity-ledger' "$stage5_doc"
require_contains 'learning_scope=operator-reviewed-local-productivity' "$stage5_doc"
require_contains 'training_performed=0' "$stage5_doc"
require_contains 'distillation_performed=0' "$stage5_doc"
require_contains 'sh scripts/test-nadia-productivity-loop-stage-5.sh' "$stage5_doc"

require_contains 'Status: implementation status record' "$stage5_status"
require_contains 'nadia_productivity_ledger_generator_present=1' "$stage5_status"
require_contains 'ledger_append_only=1' "$stage5_status"
require_contains 'project_memory_scope=local-metadata-only' "$stage5_status"

require_contains 'Stage-5: Productivity Loop' "$foundation"
require_contains 'scripts/nadia-productivity-ledger.sh' "$foundation"
require_contains 'NADIA_PRODUCTIVITY_LOOP_STAGE_5.md' "$foundation_index"
require_contains 'NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md' "$status_index"
require_contains 'nadia_stage_5_productivity_loop_present=1' "$readme"
require_contains 'Latest Nadia productivity loop Stage-5 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia productivity loop Stage-5 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia productivity loop Stage-5' "$current_status"

require_contains 'NADIA PRODUCTIVITY LEDGER ENTRY' "$ledger_script"
require_contains 'learning_scope=operator-reviewed-local-productivity' "$ledger_script"
require_contains 'ledger_append_only=1' "$ledger_script"
require_contains 'training_performed=0' "$ledger_script"
require_contains 'distillation_performed=0' "$ledger_script"
require_contains 'source_mutation_authority=0' "$ledger_script"
require_not_contains 'curl ' "$ledger_script"
require_not_contains 'wget ' "$ledger_script"
require_not_contains 'ssh ' "$ledger_script"

require_contains 'productivity-ledger' "$apply_script"
require_contains 'scripts/nadia-productivity-ledger.sh' "$apply_script"
require_contains 'productivity_loop_stage=5-productivity-ledger-loop' "$panel_config"
require_contains 'nadia ledger' "$panel_ui"
require_contains 'latticra-nadia productivity-ledger' "$installer_readme"
require_contains 'nadia ledger' "$ui_model"
require_contains 'productivity-ledger' "$components_manifest"
require_contains 'nadia-ledger' "$makefile"

out="${TMPDIR:-/tmp}/latticra-nadia-stage5-ledger-test"
context_out="${TMPDIR:-/tmp}/latticra-nadia-stage5-context-test"
runtime_out="${TMPDIR:-/tmp}/latticra-nadia-stage5-runtime-test"
plan_out="${TMPDIR:-/tmp}/latticra-nadia-stage5-plan-test"
mode_out="${TMPDIR:-/tmp}/latticra-nadia-stage5-mode-test"
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage5-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage5-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage5-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" >/tmp/latticra-nadia-stage5-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage5-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage5-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage5-test.txt" \
  --task "productivity loop planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage5-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage5-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage5-test.txt" \
  --mode ai-development \
  --output "$mode_out" >/tmp/latticra-nadia-stage5-mode-test.out
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage5-test sh "$ledger_script" \
  --mode-validation "$mode_out/nadia-mode-validation-stage5-test.txt" \
  --outcome "accepted planning surface" \
  --recommendation "run stage guards" \
  --output "$out" >/tmp/latticra-nadia-stage5-ledger-test.out
entry="$out/nadia-productivity-entry-stage5-test.txt"

require_file "$entry"
require_file "$out/latest-productivity-entry.txt"
require_file "$out/productivity-ledger-index.tsv"
require_contains 'NADIA PRODUCTIVITY LEDGER ENTRY' "$entry"
require_contains 'stage=5-productivity-ledger-loop' "$entry"
require_contains 'learning_scope=operator-reviewed-local-productivity' "$entry"
require_contains 'mode_validation_stage=4-systems-engineering-mode-validation' "$entry"
require_contains 'mode=ai-development' "$entry"
require_contains 'operator_reviewed_outcome=accepted planning surface' "$entry"
require_contains 'operator_reviewed_recommendation=run stage guards' "$entry"
require_contains 'ledger_append_only=1' "$entry"
require_contains 'training_performed=0' "$entry"
require_contains 'distillation_performed=0' "$entry"
require_contains 'source_mutation_authority=0' "$entry"
require_contains 'community_awareness_posture=1' "$entry"
require_contains 'stage5-test' "$out/productivity-ledger-index.tsv"

printf 'nadia_productivity_loop_stage_5: ok\n'
