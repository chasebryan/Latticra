#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload repeatability transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md

require_contains 'Status: contract record' "$doc"
require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' "$doc"
require_contains 'prior_cli_payload_evidence_recorded=1' "$doc"
require_contains 'source_tree_revision_recorded=1' "$doc"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$doc"
require_contains 'validated_cli_mode_still_no_effect=1' "$doc"
require_contains 'second_disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'cli_payload_repeatability_evidence_present=1' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' "$doc"
require_contains 'Add Fedora VM CLI payload repeatability runner plan' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract: ok' "$doc"

require_contains 'Status: contract/status alignment' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' "$status"
require_contains 'Add Fedora VM CLI payload repeatability runner plan' "$status"

printf 'fedora_vm_cli_payload_repeatability_transcript_contract: ok\n'
