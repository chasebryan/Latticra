#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload next validation lane plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload next validation lane plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN_STATUS.md'
index='docs/status/README.md'
readme='README.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
announcement='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_ANNOUNCEMENT_STATUS.md'
workflow='.github/workflows/fedora-vm-cli-payload-next-validation-lane-plan.yml'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$readme"
require_file "$evidence"
require_file "$announcement"
require_file "$workflow"
require_file packaging/fedora/latticra.spec
require_file src/latticra_cli.c

require_contains 'Status: planning record' "$doc"
require_contains 'next manual disposable Fedora VM validation lane for the no-effect CLI payload' "$doc"
require_contains 'test repeatability, not broaden authority' "$doc"
require_contains 'disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$doc"
require_contains 'validated_payload=/usr/bin/latticra' "$doc"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'mode=no-effect' "$doc"
require_contains 'runtime_behavior=disabled' "$doc"
require_contains 'effect_authority=denied' "$doc"
require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0' "$doc"
require_contains 'source_tree_revision_recorded=1' "$doc"
require_contains 'fedora_os_release_recorded=1' "$doc"
require_contains 'spec_checksum_recorded=1' "$doc"
require_contains 'source_archive_checksum_recorded=1' "$doc"
require_contains 'rpm_nevra_recorded=1' "$doc"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$doc"
require_contains 'cli_invalid_command_exit_recorded=1' "$doc"
require_contains 'validated_cli_mode_still_no_effect=1' "$doc"
require_contains 'validated_runtime_behavior_still_disabled=1' "$doc"
require_contains 'second_disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'cli_payload_repeatability_evidence_present=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'This plan does not implement a runner.' "$doc"
require_contains 'It does not execute RPM commands.' "$doc"
require_contains 'It does not mutate a host.' "$doc"
require_contains 'Add Fedora VM CLI payload repeatability transcript contract' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-next-validation-lane-plan.sh' "$doc"

require_contains 'Status: plan/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'Fedora VM CLI payload next-validation lane plan' "$status"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$status"
require_contains 'post_removal_absence_verified=1' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-next-validation-lane-plan.sh' "$status"
require_contains 'Add Fedora VM CLI payload repeatability transcript contract' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload next-validation plan checkpoint' "$index"
require_contains 'cli_payload_repeatability_evidence_present=1' "$index"
require_contains 'Add Fedora VM CLI payload repeatability transcript contract' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md' "$readme"
require_contains 'disposable_vm_cli_validation_completed=1' "$evidence"
require_contains 'host_install_ready_for_cli_payload=1' "$announcement"

require_contains 'name: Fedora VM CLI Payload Next Validation Lane Plan' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-next-validation-lane-plan.sh' "$workflow"

printf 'fedora_vm_cli_payload_next_validation_lane_plan: ok\n'
