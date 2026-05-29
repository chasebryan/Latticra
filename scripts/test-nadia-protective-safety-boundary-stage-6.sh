#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage6.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia protective safety boundary stage 6: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia protective safety boundary stage 6: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia protective safety boundary stage 6: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage6_doc='docs/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md'
stage6_status='docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
safety_script='scripts/nadia-protective-safety-boundary.sh'
stage6_guard='scripts/test-nadia-protective-safety-boundary-stage-6.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage6_doc"
require_file "$stage6_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$safety_script"
require_file "$stage6_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-6 implementation contract' "$stage6_doc"
require_contains 'nadia_stage_6_protective_safety_boundary_present=1' "$stage6_doc"
require_contains 'protective_safety_command=scripts/nadia-protective-safety-boundary.sh' "$stage6_doc"
require_contains 'installed_protective_safety_command=latticra-nadia protective-safety' "$stage6_doc"
require_contains 'sexual_content_generation=0' "$stage6_doc"
require_contains 'sexual_request_refusal=always' "$stage6_doc"
require_contains 'manipulation_resistance=required' "$stage6_doc"
require_contains 'namesake_cause_awareness=1' "$stage6_doc"
require_contains 'sh scripts/test-nadia-protective-safety-boundary-stage-6.sh' "$stage6_doc"

require_contains 'Status: implementation status record' "$stage6_status"
require_contains 'nadia_protective_safety_generator_present=1' "$stage6_status"
require_contains 'absolute_protective_boundary=1' "$stage6_status"
require_contains 'policy_bypass_authority=0' "$stage6_status"

require_contains 'Stage-6: Protective Safety Boundary' "$foundation"
require_contains 'scripts/nadia-protective-safety-boundary.sh' "$foundation"
require_contains 'NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md' "$foundation_index"
require_contains 'NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md' "$status_index"
require_contains 'nadia_stage_6_protective_safety_boundary_present=1' "$readme"
require_contains 'Latest Nadia protective safety boundary Stage-6 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia protective safety boundary Stage-6 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia protective safety boundary Stage-6' "$current_status"

require_contains 'NADIA PROTECTIVE SAFETY BOUNDARY' "$safety_script"
require_contains 'absolute_protective_boundary=1' "$safety_script"
require_contains 'sexual_content_generation=0' "$safety_script"
require_contains 'sexual_request_refusal=always' "$safety_script"
require_contains 'sexualized_namesake_or_survivor_content=0' "$safety_script"
require_contains 'manipulation_resistance=required' "$safety_script"
require_contains 'prompt_injection_override_authority=0' "$safety_script"
require_contains 'policy_bypass_authority=0' "$safety_script"
require_not_contains 'curl ' "$safety_script"
require_not_contains 'wget ' "$safety_script"
require_not_contains 'ssh ' "$safety_script"

require_contains 'protective-safety' "$apply_script"
require_contains 'scripts/nadia-protective-safety-boundary.sh' "$apply_script"
require_contains 'protective_safety_stage=6-protective-safety-boundary' "$panel_config"
require_contains 'nadia safety' "$panel_ui"
require_contains 'latticra-nadia protective-safety' "$installer_readme"
require_contains 'nadia safety' "$ui_model"
require_contains 'protective-safety' "$components_manifest"
require_contains 'nadia-safety' "$makefile"

out="$tmpdir/latticra-nadia-stage6-safety-test"
context_out="$tmpdir/latticra-nadia-stage6-context-test"
runtime_out="$tmpdir/latticra-nadia-stage6-runtime-test"
plan_out="$tmpdir/latticra-nadia-stage6-plan-test"
mode_out="$tmpdir/latticra-nadia-stage6-mode-test"
ledger_out="$tmpdir/latticra-nadia-stage6-ledger-test"
context_stdout="$tmpdir/latticra-nadia-stage6-context-test.out"
runtime_stdout="$tmpdir/latticra-nadia-stage6-runtime-test.out"
plan_stdout="$tmpdir/latticra-nadia-stage6-plan-test.out"
mode_stdout="$tmpdir/latticra-nadia-stage6-mode-test.out"
ledger_stdout="$tmpdir/latticra-nadia-stage6-ledger-test.out"
safety_stdout="$tmpdir/latticra-nadia-stage6-safety-test.out"
reject_stdout="$tmpdir/latticra-nadia-stage6-reject-test.out"
reject_stderr="$tmpdir/latticra-nadia-stage6-reject-test.err"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage6-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >"$context_stdout"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage6-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" >"$runtime_stdout"
NADIA_PROMPT_PLAN_TIMESTAMP=stage6-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage6-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage6-test.txt" \
  --task "protective safety planning" \
  --output "$plan_out" >"$plan_stdout"
NADIA_MODE_VALIDATION_TIMESTAMP=stage6-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage6-test.txt" \
  --mode awareness-safety \
  --output "$mode_out" >"$mode_stdout"
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage6-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage6-test.txt" \
  --outcome "accepted safety boundary" \
  --recommendation "enforce protective boundary" \
  --output "$ledger_out" >"$ledger_stdout"
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage6-test sh "$safety_script" \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage6-test.txt" \
  --request-class software-development \
  --output "$out" >"$safety_stdout"
report="$out/nadia-protective-safety-stage6-test.txt"

require_file "$report"
require_file "$out/latest-protective-safety.txt"
require_contains 'NADIA PROTECTIVE SAFETY BOUNDARY' "$report"
require_contains 'stage=6-protective-safety-boundary' "$report"
require_contains 'absolute_protective_boundary=1' "$report"
require_contains 'request_class=software-development' "$report"
require_contains 'productivity_entry_stage=5-productivity-ledger-loop' "$report"
require_contains 'mode=awareness-safety' "$report"
require_contains 'sexual_user_request_authority=0' "$report"
require_contains 'sexual_content_generation=0' "$report"
require_contains 'sexual_roleplay_authority=0' "$report"
require_contains 'sexualized_namesake_or_survivor_content=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'user_override_authority=0' "$report"
require_contains 'prompt_injection_override_authority=0' "$report"
require_contains 'manipulation_resistance=required' "$report"
require_contains 'policy_bypass_authority=0' "$report"
require_contains 'namesake_cause_awareness=1' "$report"
require_contains 'awareness_context=non_sensational_human_rights' "$report"
require_contains 'source_mutation_authority=0' "$report"
require_contains 'training_performed=0' "$report"
require_contains 'distillation_performed=0' "$report"

if NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage6-reject sh "$safety_script" \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage6-test.txt" \
  --request-class sexual \
  --output "$out" >"$reject_stdout" 2>"$reject_stderr"; then
  printf 'nadia protective safety boundary stage 6: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia protective boundary' "$reject_stderr"

printf 'nadia_protective_safety_boundary_stage_6: ok\n'
