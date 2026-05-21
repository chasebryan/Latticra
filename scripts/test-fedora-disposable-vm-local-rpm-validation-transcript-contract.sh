#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm local rpm validation transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm local rpm validation transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md'

require_file "$doc"
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
require_file docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_STATUS.md
require_file scripts/run-fedora-disposable-vm-local-rpm-validation-lane.sh
require_file scripts/test-fedora-disposable-vm-local-rpm-validation-status-alignment.sh
require_file packaging/fedora/latticra.spec

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 9 target, contract only' "$doc"
require_contains 'evidence schema only' "$doc"
require_contains 'It does not execute the validation runner.' "$doc"
require_contains 'It does not install or remove an RPM.' "$doc"
require_contains 'LATTICRA FEDORA DISPOSABLE VM LOCAL RPM VALIDATION TRANSCRIPT' "$doc"
require_contains 'transcript_kind=disposable-vm-local-rpm-validation' "$doc"
require_contains 'transcript_version=1' "$doc"
require_contains 'operator_review_required=1' "$doc"
require_contains 'validation_transcript_recorded_after_real_run=1' "$doc"
require_contains 'target_is_disposable_fedora_vm=1' "$doc"
require_contains 'target_is_daily_driver=0' "$doc"
require_contains 'target_is_production_host=0' "$doc"
require_contains 'target_is_immutable_fedora=0' "$doc"
require_contains 'target_has_clean_snapshot=1' "$doc"
require_contains 'target_has_recovery_path=1' "$doc"
require_contains 'operator_consent_recorded=1' "$doc"
require_contains 'fedora_os_release_recorded=1' "$doc"
require_contains 'fedora_kernel_version_recorded=1' "$doc"
require_contains 'rpm_tooling_recorded=1' "$doc"
require_contains 'rpmbuild_tooling_recorded=1' "$doc"
require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0' "$doc"
require_contains 'LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1' "$doc"
require_contains 'LATTICRA_TARGET_HAS_RECOVERY_PATH=1' "$doc"
require_contains 'LATTICRA_OPERATOR_CONSENT_RECORDED=1' "$doc"
require_contains 'ID=fedora' "$doc"
require_contains 'rpm_present=1' "$doc"
require_contains 'rpmbuild_present=1' "$doc"
require_contains 'local_rpm_built_from_current_tree=1' "$doc"
require_contains 'rpm_build_command_recorded=1' "$doc"
require_contains 'rpm_name_is_latticra=1' "$doc"
require_contains 'rpm_version_recorded=1' "$doc"
require_contains 'rpm_path_recorded=1' "$doc"
require_contains 'rpm_metadata_recorded=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_is_documentation_only=1' "$doc"
require_contains 'unexpected_runtime_surface_absent=1' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains '/usr/bin/latticra' "$doc"
require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains 'install_command_recorded=1' "$doc"
require_contains 'install_result_recorded=1' "$doc"
require_contains 'rpm_query_after_install_recorded=1' "$doc"
require_contains 'installed_payload_listing_recorded=1' "$doc"
require_contains 'installed_readme_present=1' "$doc"
require_contains 'rpm_verify_completed=1' "$doc"
require_contains 'removal_command_recorded=1' "$doc"
require_contains 'removal_result_recorded=1' "$doc"
require_contains 'post_removal_query_recorded=1' "$doc"
require_contains 'post_removal_absence_verified=1' "$doc"
require_contains 'FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE' "$doc"
require_contains 'validation_status=ok' "$doc"
require_contains 'vm_rpmdb_mutated=1' "$doc"
require_contains 'vm_filesystem_mutated=1' "$doc"
require_contains 'live_host_validation_completed=1' "$doc"
require_contains 'host_install_ready=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'fedora-os-release.txt' "$doc"
require_contains 'fedora-kernel-version.txt' "$doc"
require_contains 'rpm-version.txt' "$doc"
require_contains 'rpmbuild-version.txt' "$doc"
require_contains 'rpm-package-metadata.txt' "$doc"
require_contains 'rpm-payload.list' "$doc"
require_contains 'rpm-installed-payload.list' "$doc"
require_contains 'vm-validation.report' "$doc"
require_contains 'post-removal-absence-proof.txt' "$doc"
require_contains 'TARGET REVIEW' "$doc"
require_contains 'RUNNER GATE REVIEW' "$doc"
require_contains 'PACKAGE REVIEW' "$doc"
require_contains 'INSTALL VALIDATION REVIEW' "$doc"
require_contains 'REMOVAL VALIDATION REVIEW' "$doc"
require_contains 'POST-REMOVAL ABSENCE REVIEW' "$doc"
require_contains 'BOUNDARY REVIEW' "$doc"
require_contains 'OPERATOR SIGNOFF' "$doc"
require_contains 'NEXT ACTION REVIEW' "$doc"
require_contains 'disposable_vm_validation_transcript_status=accepted-for-review' "$doc"
require_contains 'disposable_vm_validation_transcript_status=blocked' "$doc"
require_contains 'disposable_vm_validation_transcript_status=invalid' "$doc"
require_contains 'disposable_vm_validation_transcript_present=0' "$doc"
require_contains 'disposable_vm_validation_completed=0' "$doc"
require_contains 'Capture real disposable Fedora VM local RPM validation transcript evidence' "$doc"
require_contains 'root README should not claim install readiness' "$doc"
require_contains 'not a completed validation transcript' "$doc"

printf 'fedora_disposable_vm_local_rpm_validation_transcript_contract: ok\n'
