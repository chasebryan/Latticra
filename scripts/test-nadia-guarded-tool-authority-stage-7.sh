#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage7.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia guarded tool authority stage 7: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia guarded tool authority stage 7: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia guarded tool authority stage 7: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage7_doc='docs/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md'
stage7_status='docs/status/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
tool_script='scripts/nadia-tool-authority-preflight.sh'
stage7_guard='scripts/test-nadia-guarded-tool-authority-stage-7.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage7_doc"
require_file "$stage7_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$tool_script"
require_file "$stage7_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-7 implementation contract' "$stage7_doc"
require_contains 'nadia_stage_7_guarded_tool_authority_present=1' "$stage7_doc"
require_contains 'tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh' "$stage7_doc"
require_contains 'installed_tool_authority_preflight_command=latticra-nadia tool-preflight' "$stage7_doc"
require_contains 'preflight_decision=report_only_no_execution' "$stage7_doc"
require_contains 'tool_execution_authority=0' "$stage7_doc"
require_contains 'authority_transition_allowed=0' "$stage7_doc"
require_contains 'sh scripts/test-nadia-guarded-tool-authority-stage-7.sh' "$stage7_doc"

require_contains 'Status: implementation status record' "$stage7_status"
require_contains 'nadia_tool_authority_preflight_present=1' "$stage7_status"
require_contains 'tool_authority_stage=preflight-only' "$stage7_status"
require_contains 'requires_protective_safety_boundary=1' "$stage7_status"

require_contains 'Stage-7: Guarded Tool Authority' "$foundation"
require_contains 'scripts/nadia-tool-authority-preflight.sh' "$foundation"
require_contains 'NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md' "$foundation_index"
require_contains 'NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md' "$status_index"
require_contains 'nadia_stage_7_guarded_tool_authority_present=1' "$readme"
require_contains 'Latest Nadia guarded tool authority Stage-7 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia guarded tool authority Stage-7 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia guarded tool authority Stage-7' "$current_status"

require_contains 'NADIA GUARDED TOOL AUTHORITY PREFLIGHT' "$tool_script"
require_contains 'tool_execution_authority=0' "$tool_script"
require_contains 'tool_execution_performed=0' "$tool_script"
require_contains 'shell_execution_authority=0' "$tool_script"
require_contains 'network_tool_authority=0' "$tool_script"
require_contains 'source_mutation_authority=0' "$tool_script"
require_contains 'authority_transition_allowed=0' "$tool_script"
require_not_contains 'curl ' "$tool_script"
require_not_contains 'wget ' "$tool_script"
require_not_contains 'ssh ' "$tool_script"

require_contains 'tool-preflight' "$apply_script"
require_contains 'scripts/nadia-tool-authority-preflight.sh' "$apply_script"
require_contains 'tool_authority_stage=7-guarded-tool-authority-preflight' "$panel_config"
require_contains 'nadia tool' "$panel_ui"
require_contains 'latticra-nadia tool-preflight' "$installer_readme"
require_contains 'nadia tool' "$ui_model"
require_contains 'tool-preflights' "$components_manifest"
require_contains 'nadia-tool' "$makefile"

out="$tmpdir/latticra-nadia-stage7-tool-test"
context_out="$tmpdir/latticra-nadia-stage7-context-test"
runtime_out="$tmpdir/latticra-nadia-stage7-runtime-test"
plan_out="$tmpdir/latticra-nadia-stage7-plan-test"
mode_out="$tmpdir/latticra-nadia-stage7-mode-test"
ledger_out="$tmpdir/latticra-nadia-stage7-ledger-test"
safety_out="$tmpdir/latticra-nadia-stage7-safety-test"
context_stdout="$tmpdir/latticra-nadia-stage7-context-test.out"
runtime_stdout="$tmpdir/latticra-nadia-stage7-runtime-test.out"
plan_stdout="$tmpdir/latticra-nadia-stage7-plan-test.out"
mode_stdout="$tmpdir/latticra-nadia-stage7-mode-test.out"
ledger_stdout="$tmpdir/latticra-nadia-stage7-ledger-test.out"
safety_stdout="$tmpdir/latticra-nadia-stage7-safety-test.out"
tool_stdout="$tmpdir/latticra-nadia-stage7-tool-test.out"
reject_stdout="$tmpdir/latticra-nadia-stage7-reject-test.out"
reject_stderr="$tmpdir/latticra-nadia-stage7-reject-test.err"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage7-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >"$context_stdout"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage7-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" >"$runtime_stdout"
NADIA_PROMPT_PLAN_TIMESTAMP=stage7-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage7-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage7-test.txt" \
  --task "guarded tool authority planning" \
  --output "$plan_out" >"$plan_stdout"
NADIA_MODE_VALIDATION_TIMESTAMP=stage7-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage7-test.txt" \
  --mode systems-engineering \
  --output "$mode_out" >"$mode_stdout"
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage7-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage7-test.txt" \
  --outcome "accepted tool preflight boundary" \
  --recommendation "keep report-only preflight" \
  --output "$ledger_out" >"$ledger_stdout"
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage7-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage7-test.txt" \
  --request-class software-development \
  --output "$safety_out" >"$safety_stdout"
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage7-test sh "$tool_script" \
  --protective-safety "$safety_out/nadia-protective-safety-stage7-test.txt" \
  --tool-class local-evidence-review \
  --action "review generated receipts" \
  --output "$out" >"$tool_stdout"
report="$out/nadia-tool-preflight-stage7-test.txt"

require_file "$report"
require_file "$out/latest-tool-preflight.txt"
require_contains 'NADIA GUARDED TOOL AUTHORITY PREFLIGHT' "$report"
require_contains 'stage=7-guarded-tool-authority-preflight' "$report"
require_contains 'tool_class=local-evidence-review' "$report"
require_contains 'action=review generated receipts' "$report"
require_contains 'preflight_allowed=1' "$report"
require_contains 'preflight_decision=report_only_no_execution' "$report"
require_contains 'protective_safety_stage=6-protective-safety-boundary' "$report"
require_contains 'tool_authority_stage=preflight-only' "$report"
require_contains 'tool_execution_authority=0' "$report"
require_contains 'tool_execution_performed=0' "$report"
require_contains 'shell_execution_authority=0' "$report"
require_contains 'network_tool_authority=0' "$report"
require_contains 'source_mutation_authority=0' "$report"
require_contains 'destructive_action_authority=0' "$report"
require_contains 'credential_access_authority=0' "$report"
require_contains 'requires_operator_approval=1' "$report"
require_contains 'requires_nucleus_gate=1' "$report"
require_contains 'requires_runtime_boundary_gate=1' "$report"
require_contains 'requires_seal_receipt=1' "$report"
require_contains 'requires_protective_safety_boundary=1' "$report"
require_contains 'authority_transition_allowed=0' "$report"
require_contains 'sexual_content_generation=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"

if NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage7-reject sh "$tool_script" \
  --protective-safety "$safety_out/nadia-protective-safety-stage7-test.txt" \
  --tool-class shell-exec \
  --action "run shell command" \
  --output "$out" >"$reject_stdout" 2>"$reject_stderr"; then
  printf 'nadia guarded tool authority stage 7: shell tool class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Stage-7 report-only preflight boundary' "$reject_stderr"

printf 'nadia_guarded_tool_authority_stage_7: ok\n'
