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

require_file "$doc"
require_file "$status"
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md

require_contains 'Status: planning record' "$doc"
require_contains 'test repeatability, not broaden authority' "$doc"
require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$doc"
require_contains 'source_tree_revision_recorded=1' "$doc"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$doc"
require_contains 'cli_payload_repeatability_evidence_present=1' "$doc"
require_contains 'This plan does not implement a runner.' "$doc"
require_contains 'Add Fedora VM CLI payload repeatability transcript contract' "$doc"
require_contains 'fedora_vm_cli_payload_next_validation_lane_plan: ok' "$doc"

require_contains 'Status: plan/status alignment' "$status"
require_contains 'fedora_vm_cli_payload_next_validation_lane_plan_present=1' "$status"
require_contains 'Add Fedora VM CLI payload repeatability transcript contract' "$status"

printf 'fedora_vm_cli_payload_next_validation_lane_plan: ok\n'
