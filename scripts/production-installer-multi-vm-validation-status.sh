#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"
fresh_vm_validation_evidence_path="${2:-artifacts/release/latticra-production-installer-fresh-vm-validation.txt}"
repeat_vm_validation_evidence_path="${3:-artifacts/release/latticra-production-installer-repeat-vm-validation.txt}"
existing_install_validation_evidence_path="${4:-artifacts/release/latticra-production-installer-existing-install-validation.txt}"
remove_reinstall_validation_evidence_path="${5:-artifacts/release/latticra-production-installer-remove-reinstall-validation.txt}"
unsupported_target_validation_evidence_path="${6:-artifacts/release/latticra-production-installer-unsupported-target-validation.txt}"
non_root_cli_validation_evidence_path="${7:-artifacts/release/latticra-production-installer-non-root-cli-validation.txt}"
root_boundary_validation_evidence_path="${8:-artifacts/release/latticra-production-installer-root-boundary-validation.txt}"
checksum_verification_evidence_path="${9:-artifacts/release/latticra-production-installer-checksum-verification.txt}"
package_signature_verification_evidence_path="${10:-artifacts/release/latticra-production-installer-package-signature-verification.txt}"

if [ ! -f "$fixture" ]; then
  printf 'production installer multi-VM validation status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer multi-VM validation status: missing fixture line: %s\n' "$pattern" >&2
    exit 1
  fi
}

presence() {
  if [ -f "$1" ]; then
    printf '1'
  else
    printf '0'
  fi
}

require_line 'artifact_manifest_fixture_present=1'
require_line 'artifact_manifest_validated=1'
require_line 'production_installer_ready=0'

fresh_vm_validation_evidence_present="$(presence "$fresh_vm_validation_evidence_path")"
repeat_vm_validation_evidence_present="$(presence "$repeat_vm_validation_evidence_path")"
existing_install_validation_evidence_present="$(presence "$existing_install_validation_evidence_path")"
remove_reinstall_validation_evidence_present="$(presence "$remove_reinstall_validation_evidence_path")"
unsupported_target_validation_evidence_present="$(presence "$unsupported_target_validation_evidence_path")"
non_root_cli_validation_evidence_present="$(presence "$non_root_cli_validation_evidence_path")"
root_boundary_validation_evidence_present="$(presence "$root_boundary_validation_evidence_path")"
checksum_verification_evidence_present="$(presence "$checksum_verification_evidence_path")"
package_signature_verification_evidence_present="$(presence "$package_signature_verification_evidence_path")"

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER MULTI-VM VALIDATION STATUS' \
  'status_version=1' \
  'status_mode=no-effect-installer-multi-vm-validation-status' \
  'production_installer_multi_vm_validation_status_present=1' \
  'installer_multi_vm_status_present=1' \
  'installer_fresh_vm_status_present=1' \
  'installer_repeat_vm_status_present=1' \
  'installer_existing_install_status_present=1' \
  'installer_non_root_cli_status_present=1' \
  'installer_root_boundary_status_present=1' \
  'installer_multi_vm_validation_status_no_effect=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_transcript_status_present=1' \
  'production_installer_lifecycle_validation_status_present=1' \
  'production_installer_recovery_failure_mode_status_present=1' \
  "fresh_vm_validation_evidence_path=$fresh_vm_validation_evidence_path" \
  "repeat_vm_validation_evidence_path=$repeat_vm_validation_evidence_path" \
  "existing_install_validation_evidence_path=$existing_install_validation_evidence_path" \
  "remove_reinstall_validation_evidence_path=$remove_reinstall_validation_evidence_path" \
  "unsupported_target_validation_evidence_path=$unsupported_target_validation_evidence_path" \
  "non_root_cli_validation_evidence_path=$non_root_cli_validation_evidence_path" \
  "root_boundary_validation_evidence_path=$root_boundary_validation_evidence_path" \
  "checksum_verification_evidence_path=$checksum_verification_evidence_path" \
  "package_signature_verification_evidence_path=$package_signature_verification_evidence_path" \
  "fresh_vm_validation_evidence_present=$fresh_vm_validation_evidence_present" \
  "repeat_vm_validation_evidence_present=$repeat_vm_validation_evidence_present" \
  "existing_install_validation_evidence_present=$existing_install_validation_evidence_present" \
  "remove_reinstall_validation_evidence_present=$remove_reinstall_validation_evidence_present" \
  "unsupported_target_validation_evidence_present=$unsupported_target_validation_evidence_present" \
  "non_root_cli_validation_evidence_present=$non_root_cli_validation_evidence_present" \
  "root_boundary_validation_evidence_present=$root_boundary_validation_evidence_present" \
  "checksum_verification_evidence_present=$checksum_verification_evidence_present" \
  "package_signature_verification_evidence_present=$package_signature_verification_evidence_present" \
  'fresh_vm_validation_reviewed=0' \
  'repeat_vm_validation_reviewed=0' \
  'existing_install_validation_reviewed=0' \
  'remove_reinstall_validation_reviewed=0' \
  'unsupported_target_validation_reviewed=0' \
  'non_root_cli_validation_reviewed=0' \
  'root_boundary_validation_reviewed=0' \
  'checksum_verification_reviewed=0' \
  'package_signature_verification_reviewed=0' \
  'multi_vm_evidence_intake_validator_present=1' \
  'multi_vm_evidence_intake_validation_mode=no-effect-validation' \
  'multi_vm_evidence_candidate_valid=0' \
  'fresh_vm_validation_file_present=0' \
  'repeat_vm_validation_file_present=0' \
  'existing_install_validation_file_present=0' \
  'remove_reinstall_validation_file_present=0' \
  'unsupported_target_validation_file_present=0' \
  'non_root_cli_validation_file_present=0' \
  'root_boundary_validation_file_present=0' \
  'checksum_verification_file_present=0' \
  'package_signature_verification_file_present=0' \
  'fresh_vm_validation_sha256_recorded=0' \
  'repeat_vm_validation_sha256_recorded=0' \
  'existing_install_validation_sha256_recorded=0' \
  'remove_reinstall_validation_sha256_recorded=0' \
  'unsupported_target_validation_sha256_recorded=0' \
  'non_root_cli_validation_sha256_recorded=0' \
  'root_boundary_validation_sha256_recorded=0' \
  'checksum_verification_sha256_recorded=0' \
  'package_signature_verification_sha256_recorded=0' \
  'fresh_vm_validation_review_present=0' \
  'repeat_vm_validation_review_present=0' \
  'existing_install_validation_review_present=0' \
  'remove_reinstall_validation_review_present=0' \
  'unsupported_target_validation_review_present=0' \
  'non_root_cli_validation_review_present=0' \
  'root_boundary_validation_review_present=0' \
  'checksum_verification_review_present=0' \
  'package_signature_verification_review_present=0' \
  'multi_vm_evidence_accepted_by_intake_validator=0' \
  'multi_vm_evidence_written_by_intake_validator=0' \
  'installer_multi_vm_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'fresh_disposable_fedora_vm_validation=0' \
  'repeat_disposable_fedora_vm_validation=0' \
  'existing_install_upgrade_validation=0' \
  'remove_and_reinstall_validation=0' \
  'unsupported_target_block_validation=0' \
  'non_root_cli_use_validation=0' \
  'root_boundary_validation=0' \
  'checksum_verification_validation=0' \
  'package_signature_verification_validation=0' \
  'installer_multi_vm_validation_completed=0' \
  'installer_fresh_vm_validation_completed=0' \
  'installer_repeat_vm_validation_completed=0' \
  'installer_existing_install_validation_completed=0' \
  'installer_non_root_cli_validation_completed=0' \
  'installer_root_boundary_validation_completed=0' \
  'vm_invocation_performed=0' \
  'install_performed=0' \
  'uninstall_performed=0' \
  'upgrade_performed=0' \
  'rollback_performed=0' \
  'package_manager_invoked=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
