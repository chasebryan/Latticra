#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload validation evidence status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation evidence status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
index='docs/status/README.md'
runner_status='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md'

require_file "$status"
require_file "$index"
require_file "$runner_status"
require_file docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md

require_contains 'Status: evidence status alignment' "$status"
require_contains 'Date: 2026-05-21' "$status"
require_contains 'disposable Fedora VM CLI payload validation transcript reached the expected validation report' "$status"
require_contains 'disposable Fedora VM CLI payload validation run completed successfully' "$status"
require_contains 'not production readiness' "$status"
require_contains 'not Fedora approval' "$status"
require_contains 'not Fedora distribution readiness' "$status"
require_contains 'not daily-driver safety' "$status"
require_contains 'not immutable Fedora readiness' "$status"
require_contains 'not a production installer claim' "$status"

require_contains 'source=operator disposable Fedora VM transcript' "$status"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$status"
require_contains 'validated_package_name=latticra' "$status"
require_contains 'validated_package_version=0.0.0' "$status"
require_contains 'validated_package_arch=x86_64' "$status"
require_contains 'fedora_kernel_version=6.19.10-300.fc44.x86_64' "$status"

require_contains 'fedora_vm_cli_payload_validation_status_alignment: ok' "$status"
require_contains 'fedora_vm_cli_payload_transcript_capture_docs: ok' "$status"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$status"
require_contains 'state_lattice_invariants: ok' "$status"
require_contains 'system_bootstrap: ok' "$status"
require_contains 'kernel: ok' "$status"
require_contains 'kernel_lifecycle: ok' "$status"
require_contains 'fedora_vm_cli_payload_validation_lane: ok' "$status"

require_contains 'FEDORA VM CLI PAYLOAD VALIDATION LANE' "$status"
require_contains 'validation_status=ok' "$status"
require_contains 'package_name=latticra' "$status"
require_contains 'package_arch=x86_64' "$status"
require_contains 'rpm_payload_contains_cli_binary=1' "$status"
require_contains 'rpm_payload_contains_readme=1' "$status"
require_contains 'rpm_payload_contains_only_expected_surfaces=1' "$status"
require_contains 'unexpected_runtime_surface_absent=1' "$status"
require_contains 'installed_cli_binary_present=1' "$status"
require_contains 'installed_readme_present=1' "$status"
require_contains 'rpm_verify_completed=1' "$status"
require_contains 'cli_status_validation_performed=1' "$status"
require_contains 'cli_version_validation_performed=1' "$status"
require_contains 'cli_report_validation_performed=1' "$status"
require_contains 'removal_validation_performed=1' "$status"
require_contains 'post_removal_cli_absence_verified=1' "$status"
require_contains 'post_removal_readme_absence_verified=1' "$status"
require_contains 'disposable_vm_cli_validation_completed=1' "$status"
require_contains 'host_install_ready_for_cli_payload=1' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"
require_contains 'evidence_level=9' "$status"

require_contains 'disposable_vm_cli_validation_transcript_present=1' "$status"
require_contains 'host_install_ready_for_cli_payload=1' "$status"
require_contains '/usr/bin/latticra' "$status"
require_contains '/usr/share/doc/latticra/README.md' "$status"
require_contains 'This evidence is limited to a disposable Fedora VM CLI payload validation path.' "$status"
require_contains 'does not validate daily-driver installation' "$status"
require_contains 'Fedora QA approval' "$status"
require_contains 'Align README wording with disposable Fedora VM CLI payload validation evidence' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload validation evidence checkpoint' "$index"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$index"
require_contains 'disposable_vm_cli_validation_completed=1' "$index"
require_contains 'host_install_ready_for_cli_payload=1' "$index"
require_contains 'Align README wording with disposable Fedora VM CLI payload validation evidence' "$index"

require_contains 'fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run' "$runner_status"

printf 'fedora_vm_cli_payload_validation_evidence_status: ok\n'
