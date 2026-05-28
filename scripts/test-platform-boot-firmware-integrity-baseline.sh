#!/usr/bin/env sh
set -eu

doc="docs/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md"
status_doc="docs/status/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'platform boot firmware integrity baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'platform boot firmware integrity baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_file docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_file docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
require_file docs/LATTICRA_BOOT_SEED_CONTRACT.md
require_file docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md
require_file docs/LATTICRA_OS_IMAGE_TOOLCHAIN_CONTRACT.md
require_file docs/LATTICRA_OS_IMAGE_BUILD_RECIPE_CONTRACT.md
require_file docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: platform boot and firmware integrity baseline' "$doc"
require_contains 'Source refresh date: 2026-05-28' "$doc"
require_contains 'Authoritative Platform Integrity Sources' "$doc"
require_contains 'NSA Guidance for Managing UEFI Secure Boot' "$doc"
require_contains 'NSA Boot Security Modes and Recommendations' "$doc"
require_contains 'NSA UEFI Secure Boot Customization' "$doc"
require_contains 'CISA Call to Action: Bolster UEFI Cybersecurity Now' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'NIST SP 800-193 Platform Firmware Resiliency Guidelines' "$doc"
require_contains 'NIST SP 800-147 BIOS Protection Guidelines' "$doc"
require_contains 'NIST SP 800-155 BIOS Integrity Measurement Guidelines draft' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 System and Information Integrity, Configuration Management, Access Control, and System and Services Acquisition controls' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4356302/nsa-releases-unified-extensible-firmware-interface-secure-boot-guidance/' "$doc"
require_contains 'https://www.nsa.gov/portals/75/documents/resources/cybersecurity-professionals/csi-boot-security-modes-and-recommendations.pdf' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/2347822/nsa-releases-cybersecurity-technical-report-on-uefi-secure-boot-customization/' "$doc"
require_contains 'https://www.cisa.gov/news-events/news/call-action-bolster-uefi-cybersecurity-now' "$doc"
require_contains 'https://www.cisa.gov/news-events/alerts/2025/01/17/cisa-and-fbi-release-updated-guidance-product-security-bad-practices' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/193/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/147/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/155/ipd' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"

for field in \
  'platform_boot_firmware_integrity_baseline_present=1' \
  'platform_boot_firmware_integrity_guard_present=1' \
  'nsa_uefi_secure_boot_guidance_tracked=1' \
  'nsa_boot_security_modes_guidance_tracked=1' \
  'nsa_uefi_secure_boot_customization_tracked=1' \
  'cisa_uefi_security_guidance_tracked=1' \
  'cisa_fbi_product_security_bad_practices_tracked=1' \
  'nist_sp_800_193_platform_firmware_resiliency_tracked=1' \
  'nist_sp_800_147_bios_protection_tracked=1' \
  'nist_sp_800_155_bios_integrity_measurement_tracked=1' \
  'nist_sp_800_53_platform_integrity_controls_tracked=1' \
  'platform_inventory_required=1' \
  'boot_mode_inventory_required=1' \
  'legacy_csm_review_required=1' \
  'secure_boot_configuration_review_required=1' \
  'uefi_secure_boot_enforcement_review_required=1' \
  'secure_boot_key_database_inventory_required=1' \
  'boot_binary_inventory_required=1' \
  'bootloader_kernel_driver_signing_review_required=1' \
  'tpm_measurement_policy_required=1' \
  'pcr_baseline_required=1' \
  'firmware_version_inventory_required=1' \
  'firmware_update_integrity_required=1' \
  'firmware_recovery_plan_required=1' \
  'boot_artifact_provenance_required=1' \
  'os_image_boot_chain_review_required=1' \
  'platform_admin_privilege_control_required=1' \
  'firmware_vulnerability_review_required=1' \
  'boot_integrity_logging_required=1' \
  'platform_exception_owner_required=1' \
  'platform_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'secure_boot_enforcement_added=0' \
  'measured_boot_added=0' \
  'tpm_attestation_added=0' \
  'firmware_update_added=0' \
  'firmware_recovery_added=0' \
  'bootloader_signing_added=0' \
  'boot_policy_enforcement_added=0' \
  'host_firmware_mutation_added=0' \
  'bootable_os_ready_claim_allowed=0' \
  'secure_boot_claim_allowed=0' \
  'measured_boot_claim_allowed=0' \
  'platform_integrity_claim_allowed=0' \
  'hardware_root_trust_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'platform_boot_firmware_integrity_status_present=1' "$status_doc"

for gate in \
  'platform_inventory_present=1' \
  'platform_owner_recorded=1' \
  'boot_mode_recorded=1' \
  'legacy_csm_disabled_or_exception_recorded=1' \
  'secure_boot_state_recorded=1' \
  'secure_boot_policy_owner_recorded=1' \
  'pk_kek_db_dbx_inventory_recorded=1' \
  'dbx_update_review_recorded=1' \
  'boot_binary_inventory_recorded=1' \
  'bootloader_kernel_driver_signature_review_recorded=1' \
  'tpm_presence_and_version_recorded=1' \
  'pcr_measurement_policy_recorded=1' \
  'golden_measurement_baseline_recorded=1' \
  'firmware_version_inventory_recorded=1' \
  'firmware_update_source_recorded=1' \
  'firmware_update_signature_validation_recorded=1' \
  'firmware_recovery_path_recorded=1' \
  'os_image_boot_chain_recorded=1' \
  'boot_artifact_manifest_recorded=1' \
  'boot_integrity_log_review_recorded=1' \
  'platform_admin_access_recorded=1' \
  'firmware_vulnerability_review_recorded=1' \
  'rollback_plan_recorded=1' \
  'incident_response_handoff_recorded=1' \
  'exception_owner_recorded=1' \
  'exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'secure_boot_enforcement_allowed=0' \
  'measured_boot_allowed=0' \
  'tpm_attestation_allowed=0' \
  'firmware_update_allowed=0' \
  'firmware_recovery_allowed=0' \
  'bootloader_signing_allowed=0' \
  'boot_policy_enforcement_allowed=0' \
  'host_firmware_mutation_allowed=0' \
  'bootable_os_ready_claim_allowed=0' \
  'secure_boot_claim_allowed=0' \
  'platform_integrity_claim_allowed=0' \
  'hardware_root_trust_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_boot_platform_metadata_only=1' \
  'latticra_boot_seed_contract_no_firmware_mutation=1' \
  'latticra_os_image_preflight_no_secure_boot_authority=1' \
  'latticra_seabios_grub_preview_no_platform_integrity_claim=1' \
  'latticra_installer_no_firmware_mutation=1' \
  'latticra_secure_boot_configuration_changed=0' \
  'latticra_measured_boot_added=0' \
  'latticra_tpm_attestation_added=0' \
  'latticra_firmware_update_added=0' \
  'latticra_firmware_recovery_added=0' \
  'latticra_platform_integrity_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'zero_trust_runtime_authority_baseline_present=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'supply_chain_security_baseline_present=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'secure_configuration_change_management_baseline_present=1' docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_contains 'vulnerability_management_release_gate_baseline_present=1' docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_contains 'backup_recovery_resilience_baseline_present=1' docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
require_contains 'bootable_os_ready=0' docs/LATTICRA_OS_IMAGE_TOOLCHAIN_CONTRACT.md
require_contains 'bootable_os_ready=0' docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md
require_contains 'bootable_os_ready=0' docs/LATTICRA_OS_IMAGE_BUILD_RECIPE_CONTRACT.md
require_contains 'firmware_mutation_authority=0' docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md
require_contains 'platform_boot_firmware_integrity_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-platform-boot-firmware-integrity-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md' SECURITY.md
require_contains 'platform_boot_firmware_integrity_baseline_present=1' README.md
require_contains 'platform_boot_firmware_integrity_baseline_present=1' STATUS.md
require_contains 'PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'platform_boot_firmware_integrity_baseline_present=1' docs/status/README.md
require_contains 'Latest platform boot and firmware integrity baseline note: 2026-05-28 CDT' docs/status/CURRENT_STATUS.md
require_contains 'PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Platform boot and firmware integrity baseline' docs/security.html
require_contains 'PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-platform-boot-firmware-integrity-baseline.sh' Makefile
require_contains 'platform-boot-firmware-integrity-baseline:' Makefile
require_contains 'sh ./scripts/test-platform-boot-firmware-integrity-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-platform-boot-firmware-integrity-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'platform_boot_firmware_integrity_baseline: ok\n'
