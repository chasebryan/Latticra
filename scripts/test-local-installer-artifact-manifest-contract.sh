#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'local installer artifact manifest contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'local installer artifact manifest contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/LOCAL_INSTALLER_ARTIFACT_MANIFEST_CONTRACT.md'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'

require_file "$doc"
require_file "$prod"

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 10 target, manifest contract only' "$doc"
require_contains 'This is not an installer.' "$doc"
require_contains 'This does not build, sign, publish, distribute, install, uninstall, upgrade, or rollback an installer.' "$doc"
require_contains 'This does not claim production installer readiness.' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"

require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains 'validated_payload_cli=/usr/bin/latticra' "$doc"
require_contains 'validated_payload_readme=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'artifacts/<artifact-name>/manifest.txt' "$doc"
require_contains 'plain text, line-oriented, deterministic, and reviewable' "$doc"

require_contains 'LATTICRA INSTALLER ARTIFACT MANIFEST' "$doc"
require_contains 'manifest_version=1' "$doc"
require_contains 'artifact_name=<recorded>' "$doc"
require_contains 'artifact_version=<recorded>' "$doc"
require_contains 'artifact_arch=<recorded>' "$doc"
require_contains 'artifact_format=<recorded>' "$doc"
require_contains 'artifact_filename=<recorded>' "$doc"
require_contains 'artifact_size_bytes=<recorded>' "$doc"
require_contains 'artifact_sha256=<recorded>' "$doc"
require_contains 'artifact_signature=<recorded-or-none>' "$doc"
require_contains 'artifact_signing_key_id=<recorded-or-none>' "$doc"
require_contains 'artifact_sbom_path=<recorded-or-none>' "$doc"
require_contains 'artifact_license_metadata_path=<recorded>' "$doc"
require_contains 'source_repository=Bryforge/Latticra' "$doc"
require_contains 'source_commit=<recorded>' "$doc"
require_contains 'source_tag=<recorded-or-none>' "$doc"
require_contains 'build_environment=<recorded>' "$doc"
require_contains 'build_command_recorded=1' "$doc"
require_contains 'build_reproducible=<0-or-1>' "$doc"

require_contains 'supported_target_family=<recorded>' "$doc"
require_contains 'supported_target_versions=<recorded>' "$doc"
require_contains 'supported_target_arches=<recorded>' "$doc"
require_contains 'unsupported_targets_declared=1' "$doc"
require_contains 'requires_operator_consent=1' "$doc"
require_contains 'preflight_guard_required=1' "$doc"
require_contains 'install_plan_preview_required=1' "$doc"
require_contains 'uninstall_path_required=1' "$doc"
require_contains 'rollback_or_recovery_path_required=1' "$doc"

require_contains 'network_required=0' "$doc"
require_contains 'service_activation_default=0' "$doc"
require_contains 'boot_change_default=0' "$doc"
require_contains 'kernel_module_default=0' "$doc"
require_contains 'selinux_policy_default=0' "$doc"
require_contains 'payload_listing_recorded=1' "$doc"
require_contains 'payload_contains_cli_binary=<0-or-1>' "$doc"
require_contains 'payload_contains_readme=<0-or-1>' "$doc"
require_contains 'payload_contains_service=<0-or-1>' "$doc"
require_contains 'payload_contains_kernel_module=<0-or-1>' "$doc"
require_contains 'payload_contains_boot_change=<0-or-1>' "$doc"
require_contains 'payload_contains_selinux_policy=<0-or-1>' "$doc"

require_contains 'artifact_sha256_recorded=1' "$doc"
require_contains 'artifact_signature_recorded=1' "$doc"
require_contains 'artifact_signing_key_documented=1' "$doc"
require_contains 'signature_verification_documented=1' "$doc"
require_contains 'artifact_sbom_path=<recorded>' "$doc"
require_contains 'sbom_present=1' "$doc"
require_contains 'sbom_reviewed=1' "$doc"
require_contains 'installer_sbom_recorded=0' "$doc"

require_contains 'not_production_readiness=1' "$doc"
require_contains 'not_fedora_approval=1' "$doc"
require_contains 'not_fedora_distribution_readiness=1' "$doc"
require_contains 'not_daily_driver_readiness=1' "$doc"
require_contains 'not_immutable_fedora_readiness=1' "$doc"
require_contains 'not_security_hardening_claim=1' "$doc"
require_contains 'not_malware_prevention_claim=1' "$doc"
require_contains 'not_ransomware_prevention_claim=1' "$doc"
require_contains 'not_os_replacement_claim=1' "$doc"

require_contains 'installer_artifact_manifest_contract_present=1' "$doc"
require_contains 'installer_artifact_manifest_present=0' "$doc"
require_contains 'installer_artifact_manifest_validated=0' "$doc"
require_contains 'installer_artifact_checksum_recorded=0' "$doc"
require_contains 'installer_artifact_signature_recorded=0' "$doc"
require_contains 'installer_supported_targets_declared=0' "$doc"
require_contains 'installer_unsupported_targets_declared=0' "$doc"
require_contains 'Add installer artifact manifest fixture' "$doc"

require_contains 'installer_artifact_format_declared=1' "$prod"
require_contains 'installer_artifact_checksum_recorded=1' "$prod"
require_contains 'installer_artifact_signature_recorded=1' "$prod"
require_contains 'installer_sbom_recorded=1' "$prod"
require_contains 'production_installer_ready=0' "$prod"

printf 'local_installer_artifact_manifest_contract: ok\n'
