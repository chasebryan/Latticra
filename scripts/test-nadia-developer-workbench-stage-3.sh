#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage3.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia developer workbench stage 3: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia developer workbench stage 3: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia developer workbench stage 3: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage3_doc='docs/NADIA_DEVELOPER_WORKBENCH_STAGE_3.md'
stage3_status='docs/status/NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
plan_script='scripts/nadia-prompt-plan.sh'
stage3_guard='scripts/test-nadia-developer-workbench-stage-3.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
makefile='Makefile'

require_file "$stage3_doc"
require_file "$stage3_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$plan_script"
require_file "$stage3_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$makefile"

require_contains 'Status: Stage-3 implementation contract' "$stage3_doc"
require_contains 'nadia_stage_3_developer_workbench_present=1' "$stage3_doc"
require_contains 'prompt_plan_command=scripts/nadia-prompt-plan.sh' "$stage3_doc"
require_contains 'installed_prompt_plan_command=latticra-nadia prompt-plan' "$stage3_doc"
require_contains 'requires_context_pack=1' "$stage3_doc"
require_contains 'requires_runtime_profile=1' "$stage3_doc"
require_contains 'prompt_evaluated=0' "$stage3_doc"
require_contains 'sh scripts/test-nadia-developer-workbench-stage-3.sh' "$stage3_doc"

require_contains 'Status: implementation status record' "$stage3_status"
require_contains 'nadia_prompt_plan_generator_present=1' "$stage3_status"
require_contains 'context_pack_measured=1' "$stage3_status"
require_contains 'runtime_profile_measured=1' "$stage3_status"

require_contains 'Stage-3: Developer Workbench' "$foundation"
require_contains 'scripts/nadia-prompt-plan.sh' "$foundation"
require_contains 'NADIA_DEVELOPER_WORKBENCH_STAGE_3.md' "$foundation_index"
require_contains 'NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md' "$status_index"
require_contains 'nadia_stage_3_developer_workbench_present=1' "$readme"
require_contains 'Latest Nadia developer workbench Stage-3 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia developer workbench Stage-3 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia developer workbench Stage-3' "$current_status"

require_contains 'NADIA PROMPT PLAN' "$plan_script"
require_contains 'prompt_evaluated=0' "$plan_script"
require_contains 'inference_performed=0' "$plan_script"
require_contains 'source_mutation_authority=0' "$plan_script"
require_contains 'requires_operator_review=1' "$plan_script"
require_not_contains 'curl ' "$plan_script"
require_not_contains 'wget ' "$plan_script"
require_not_contains 'ssh ' "$plan_script"

require_contains 'prompt-plan' "$apply_script"
require_contains 'scripts/nadia-prompt-plan.sh' "$apply_script"
require_contains 'developer_workbench_stage=3-developer-workbench-planning' "$panel_config"
require_contains 'nadia plan' "$panel_ui"
require_contains 'latticra-nadia prompt-plan' "$installer_readme"
require_contains 'nadia-plan' "$makefile"

out="$tmpdir/latticra-nadia-stage3-plan-test"
context_out="$tmpdir/latticra-nadia-stage3-context-test"
runtime_out="$tmpdir/latticra-nadia-stage3-runtime-test"
context_stdout="$tmpdir/latticra-nadia-stage3-context-test.out"
runtime_stdout="$tmpdir/latticra-nadia-stage3-runtime-test.out"
plan_stdout="$tmpdir/latticra-nadia-stage3-plan-test.out"
rm -rf "$out" "$context_out" "$runtime_out"
mkdir -p "$out" "$context_out" "$runtime_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage3-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" > "$context_stdout"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage3-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" > "$runtime_stdout"
NADIA_PROMPT_PLAN_TIMESTAMP=stage3-test sh "$plan_script" \
  --context-pack "$context_out/nadia-context-pack-stage3-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage3-test.txt" \
  --task "runtime boundary planning" \
  --output "$out" > "$plan_stdout"
plan="$out/nadia-prompt-plan-stage3-test.txt"

require_file "$plan"
require_file "$out/latest-prompt-plan.txt"
require_contains 'stage=3-developer-workbench-planning' "$plan"
require_contains 'task=runtime boundary planning' "$plan"
require_contains 'context_pack_stage=1-local-context-engine' "$plan"
require_contains 'runtime_profile_stage=2-runtime-profile-boundary' "$plan"
require_contains 'prompt_plan_ready=1' "$plan"
require_contains 'prompt_evaluated=0' "$plan"
require_contains 'inference_performed=0' "$plan"
require_contains 'source_mutation_authority=0' "$plan"
require_contains 'requires_future_prompt_contract=1' "$plan"
require_contains 'community_awareness_posture=1' "$plan"

printf 'nadia_developer_workbench_stage_3: ok\n'
