#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'production installer readiness contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'production installer readiness contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
readme='README.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'

require_file "$doc"
require_file "$readme"
require_file "$evidence"

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 10 target, contract only' "$doc"
require_contains 'before Latticra can claim a production installer' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"

require_contains 'disposable_vm_local_rpm_validation_completed=1' "$doc"
require_contains 'disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains '/usr/bin/latticra' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"

require_contains 'installer_artifact_built_from_tag=1' "$doc"
require_contains 'installer_artifact_reproducible=1' "$doc"
require_contains 'installer_artifact_checksum_recorded=1' "$doc"
require_contains 'installer_artifact_signature_recorded=1' "$doc"
require_contains 'installer_public_key_documented=1' "$doc"
require_contains 'installer_sbom_recorded=1' "$doc"
require_contains 'installer_supported_targets_declared=1' "$doc"
require_contains 'installer_unsupported_targets_declared=1' "$doc"
require_contains 'installer_preflight_guard_present=1' "$doc"
require_contains 'installer_requires_operator_consent=1' "$doc"
require_contains 'installer_install_transcript_recorded=1' "$doc"
require_contains 'installer_uninstall_transcript_recorded=1' "$doc"
require_contains 'installer_post_removal_absence_verified=1' "$doc"
require_contains 'installer_upgrade_path_validated=1' "$doc"
require_contains 'installer_downgrade_or_rollback_path_validated=1' "$doc"
require_contains 'installer_reinstall_idempotence_validated=1' "$doc"
require_contains 'installer_multi_vm_validation_completed=1' "$doc"
require_contains 'installer_security_non_claims_preserved=1' "$doc"

require_contains 'fresh_disposable_fedora_vm_validation=1' "$doc"
require_contains 'repeat_disposable_fedora_vm_validation=1' "$doc"
require_contains 'existing_install_upgrade_validation=1' "$doc"
require_contains 'remove_and_reinstall_validation=1' "$doc"
require_contains 'unsupported_target_block_validation=1' "$doc"
require_contains 'package_signature_verification_validation=1' "$doc"
require_contains 'checksum_verification_validation=1' "$doc"

require_contains 'PRODUCTION INSTALLER READINESS REPORT' "$doc"
require_contains 'production_installer_ready=1' "$doc"
require_contains 'evidence_level=10' "$doc"
require_contains 'Fedora distribution readiness and Fedora approval remain separate claims' "$doc"

require_contains 'production_installer_contract_present=1' "$doc"
require_contains 'installer_artifact_reproducible=0' "$doc"
require_contains 'installer_artifact_signature_recorded=0' "$doc"
require_contains 'installer_sbom_recorded=0' "$doc"
require_contains 'installer_preflight_guard_present=0' "$doc"
require_contains 'installer_install_transcript_recorded=0' "$doc"
require_contains 'installer_uninstall_transcript_recorded=0' "$doc"
require_contains 'installer_upgrade_path_validated=0' "$doc"
require_contains 'installer_rollback_path_validated=0' "$doc"
require_contains 'installer_multi_vm_validation_completed=0' "$doc"

require_contains 'Add local installer artifact manifest contract.' "$doc"
require_contains 'Add installer preflight classifier for supported and blocked targets.' "$doc"
require_contains 'Add signed artifact/checksum status contract.' "$doc"
require_contains 'Add disposable Fedora VM production-installer dry-run lane.' "$doc"
require_contains 'Only then consider production_installer_ready=1.' "$doc"

require_contains 'This contract is not a production installer.' "$doc"
require_contains 'It does not build, sign, publish, install, uninstall, upgrade, rollback, or distribute an installer.' "$doc"
require_contains 'not production readiness' "$doc"
require_contains 'not Fedora approval' "$doc"
require_contains 'not Fedora distribution readiness' "$doc"
require_contains 'not daily-driver readiness' "$doc"
require_contains 'not immutable Fedora readiness' "$doc"

require_contains 'production_installer_ready=0' "$readme"
require_contains 'not a production installer' "$readme"
require_contains 'host_install_ready_for_cli_payload=1' "$evidence"
require_contains 'production_installer_ready=0' "$evidence"

printf 'production_installer_readiness_contract: ok\n'
