#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm local rpm validation evidence status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm local rpm validation evidence status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md'
index='docs/status/README.md'

require_file "$status"
require_file "$index"
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md
require_file docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_STATUS.md
require_file scripts/run-fedora-disposable-vm-local-rpm-validation-lane.sh
require_file packaging/fedora/latticra.spec

require_contains 'Status: evidence status alignment' "$status"
require_contains 'disposable Fedora VM local RPM validation run completed successfully' "$status"
require_contains 'source=operator disposable Fedora VM transcript' "$status"
require_contains 'repo_branch=pr-226' "$status"
require_contains 'followup_fix_pr=PR #226' "$status"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$status"
require_contains 'Building target platforms: noarch' "$status"
require_contains 'state_lattice_invariants: ok' "$status"
require_contains 'system_bootstrap: ok' "$status"
require_contains 'kernel: ok' "$status"
require_contains 'kernel_lifecycle: ok' "$status"
require_contains 'FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE' "$status"
require_contains 'validation_status=ok' "$status"
require_contains 'package_name=latticra' "$status"
require_contains 'package_version=0.0.0' "$status"
require_contains 'disposable_vm_target_verified=1' "$status"
require_contains 'snapshot_evidence_present=1' "$status"
require_contains 'recovery_evidence_present=1' "$status"
require_contains 'operator_consent_recorded=1' "$status"
require_contains 'rpm_payload_listing_recorded=1' "$status"
require_contains 'rpm_payload_is_documentation_only=1' "$status"
require_contains 'unexpected_runtime_surface_absent=1' "$status"
require_contains 'vm_rpmdb_mutated=1' "$status"
require_contains 'vm_filesystem_mutated=1' "$status"
require_contains 'install_validation_performed=1' "$status"
require_contains 'removal_validation_performed=1' "$status"
require_contains 'post_removal_absence_verified=1' "$status"
require_contains 'live_host_validation_completed=1' "$status"
require_contains 'host_install_ready=1' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'evidence_level=9' "$status"
require_contains 'fedora_disposable_vm_local_rpm_validation_lane: ok' "$status"
require_contains 'disposable_vm_validation_transcript_present=1' "$status"
require_contains 'disposable_vm_validation_completed=1' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"
require_contains '/usr/share/doc/latticra/README.md' "$status"
require_contains '/usr/bin/latticra' "$status"
require_contains '/etc/latticra' "$status"
require_contains '/usr/lib/systemd/system/latticra.service' "$status"
require_contains '/usr/lib/modules' "$status"
require_contains '/boot/latticra' "$status"
require_contains 'Add README install-readiness wording limited to disposable Fedora VM local RPM validation' "$status"
require_contains 'not production readiness' "$status"

require_contains 'FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md' "$index"
require_contains 'Current Fedora disposable VM local RPM validation evidence checkpoint' "$index"
require_contains 'source=operator disposable Fedora VM transcript' "$index"
require_contains 'validation_status=ok' "$index"
require_contains 'disposable_vm_validation_completed=1' "$index"
require_contains 'host_install_ready=1' "$index"
require_contains 'production_installer_ready=0' "$index"
require_contains 'fedora_distribution_ready=0' "$index"
require_contains 'fedora_approval_claimed=0' "$index"
require_contains 'Add README install-readiness wording limited to disposable Fedora VM local RPM validation' "$index"

printf 'fedora_disposable_vm_local_rpm_validation_evidence_status: ok\n'
