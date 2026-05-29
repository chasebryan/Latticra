# Latticra Platform Boot and Firmware Integrity Baseline

Status: platform boot and firmware integrity baseline
Source refresh date: 2026-05-28
Scope: platform inventory, boot mode, UEFI Secure Boot state, Secure Boot key databases, boot binary inventory, TPM and PCR measurement planning, firmware version inventory, firmware update provenance, firmware recovery, boot integrity logging, platform administrator access, rollback planning, incident handoff, and platform-integrity non-claims before bootable OS readiness, Secure Boot enforcement, measured boot, TPM attestation, firmware update, firmware recovery, hardware root-of-trust, platform integrity, or production boot claims.

This baseline records platform boot and firmware integrity requirements only. It does not implement Secure Boot, measured boot, TPM attestation, firmware updates, firmware recovery, bootloader signing, boot policy enforcement, bootable OS readiness, hardware root-of-trust behavior, platform integrity enforcement, host mutation, or runtime authority.

## Authoritative Platform Integrity Sources

Date checked: 2026-05-28

| Source | Latticra use |
| --- | --- |
| NSA Guidance for Managing UEFI Secure Boot | Secure Boot configuration review, DB/DBX/PK/KEK inventory, enforcement verification, misconfiguration recovery, and bootkit-risk vocabulary |
| NSA Boot Security Modes and Recommendations | UEFI, Secure Boot standard/custom mode, TPM auditing, PCR tracking, full/thorough boot, and legacy/CSM avoidance vocabulary |
| NSA UEFI Secure Boot Customization | owner-managed Secure Boot policy, signature/hash tracking, MOK/DB/DBX planning, and high-integrity boot customization vocabulary |
| CISA Call to Action: Bolster UEFI Cybersecurity Now | UEFI ecosystem risk, update distribution, rollback prevention, and firmware security communication vocabulary |
| CISA/FBI Product Security Bad Practices | secure-by-design product posture, dangerous default patterns, and high-risk product security non-claims |
| NIST SP 800-193 Platform Firmware Resiliency Guidelines | protect, detect, and recover model for platform firmware resiliency and destructive firmware attack recovery vocabulary |
| NIST SP 800-147 BIOS Protection Guidelines | unauthorized BIOS/UEFI modification prevention, authenticated update, firmware integrity, and platform administrator vocabulary |
| NIST SP 800-155 BIOS Integrity Measurement Guidelines draft | BIOS/UEFI measurement, roots of trust, PCR, measurement reporting, and golden measurement vocabulary |
| NIST SP 800-53 Rev. 5 System and Information Integrity, Configuration Management, Access Control, and System and Services Acquisition controls | control vocabulary for future platform-integrity profiles without making a compliance claim |

Authoritative URLs:

```text
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4356302/nsa-releases-unified-extensible-firmware-interface-secure-boot-guidance/
https://www.nsa.gov/portals/75/documents/resources/cybersecurity-professionals/csi-boot-security-modes-and-recommendations.pdf
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/2347822/nsa-releases-cybersecurity-technical-report-on-uefi-secure-boot-customization/
https://www.cisa.gov/news-events/news/call-action-bolster-uefi-cybersecurity-now
https://www.cisa.gov/news-events/alerts/2025/01/17/cisa-and-fbi-release-updated-guidance-product-security-bad-practices
https://csrc.nist.gov/pubs/sp/800/193/final
https://csrc.nist.gov/pubs/sp/800/147/final
https://csrc.nist.gov/pubs/sp/800/155/ipd
https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final
```

## Current Fields

```text
platform_boot_firmware_integrity_baseline_present=1
platform_boot_firmware_integrity_guard_present=1
nsa_uefi_secure_boot_guidance_tracked=1
nsa_boot_security_modes_guidance_tracked=1
nsa_uefi_secure_boot_customization_tracked=1
cisa_uefi_security_guidance_tracked=1
cisa_fbi_product_security_bad_practices_tracked=1
nist_sp_800_193_platform_firmware_resiliency_tracked=1
nist_sp_800_147_bios_protection_tracked=1
nist_sp_800_155_bios_integrity_measurement_tracked=1
nist_sp_800_53_platform_integrity_controls_tracked=1
platform_inventory_required=1
boot_mode_inventory_required=1
legacy_csm_review_required=1
secure_boot_configuration_review_required=1
uefi_secure_boot_enforcement_review_required=1
secure_boot_key_database_inventory_required=1
boot_binary_inventory_required=1
bootloader_kernel_driver_signing_review_required=1
tpm_measurement_policy_required=1
pcr_baseline_required=1
firmware_version_inventory_required=1
firmware_update_integrity_required=1
firmware_recovery_plan_required=1
boot_artifact_provenance_required=1
os_image_boot_chain_review_required=1
platform_admin_privilege_control_required=1
firmware_vulnerability_review_required=1
boot_integrity_logging_required=1
platform_exception_owner_required=1
platform_exception_expiration_required=1
implementation_behavior_changed=0
secure_boot_enforcement_added=0
measured_boot_added=0
tpm_attestation_added=0
firmware_update_added=0
firmware_recovery_added=0
bootloader_signing_added=0
boot_policy_enforcement_added=0
host_firmware_mutation_added=0
bootable_os_ready_claim_allowed=0
secure_boot_claim_allowed=0
measured_boot_claim_allowed=0
platform_integrity_claim_allowed=0
hardware_root_trust_claim_allowed=0
external_endorsement_claimed=0
```

## Required Platform Integrity Promotion Gate

No bootable OS readiness, Secure Boot enforcement, measured boot, TPM attestation, firmware update, firmware recovery, hardware root-of-trust, platform integrity, boot-chain security, or production boot claim may be promoted until this gate is complete:

```text
platform_inventory_present=1
platform_owner_recorded=1
boot_mode_recorded=1
legacy_csm_disabled_or_exception_recorded=1
secure_boot_state_recorded=1
secure_boot_policy_owner_recorded=1
pk_kek_db_dbx_inventory_recorded=1
dbx_update_review_recorded=1
boot_binary_inventory_recorded=1
bootloader_kernel_driver_signature_review_recorded=1
tpm_presence_and_version_recorded=1
pcr_measurement_policy_recorded=1
golden_measurement_baseline_recorded=1
firmware_version_inventory_recorded=1
firmware_update_source_recorded=1
firmware_update_signature_validation_recorded=1
firmware_recovery_path_recorded=1
os_image_boot_chain_recorded=1
boot_artifact_manifest_recorded=1
boot_integrity_log_review_recorded=1
platform_admin_access_recorded=1
firmware_vulnerability_review_recorded=1
rollback_plan_recorded=1
incident_response_handoff_recorded=1
exception_owner_recorded=1
exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
secure_boot_enforcement_allowed=0
measured_boot_allowed=0
tpm_attestation_allowed=0
firmware_update_allowed=0
firmware_recovery_allowed=0
bootloader_signing_allowed=0
boot_policy_enforcement_allowed=0
host_firmware_mutation_allowed=0
bootable_os_ready_claim_allowed=0
secure_boot_claim_allowed=0
platform_integrity_claim_allowed=0
hardware_root_trust_claim_allowed=0
```

## Latticra Boundary

Current Latticra boot-related records remain no-effect, metadata-only, and local evidence work.

```text
latticra_boot_platform_metadata_only=1
latticra_boot_seed_contract_no_firmware_mutation=1
latticra_os_image_preflight_no_secure_boot_authority=1
latticra_seabios_grub_preview_no_platform_integrity_claim=1
latticra_installer_no_firmware_mutation=1
latticra_secure_boot_configuration_changed=0
latticra_measured_boot_added=0
latticra_tpm_attestation_added=0
latticra_firmware_update_added=0
latticra_firmware_recovery_added=0
latticra_platform_integrity_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
docs/LATTICRA_BOOT_SEED_CONTRACT.md
docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md
docs/LATTICRA_OS_IMAGE_TOOLCHAIN_CONTRACT.md
docs/LATTICRA_OS_IMAGE_BUILD_RECIPE_CONTRACT.md
docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md
SECURITY.md
scripts/test-platform-boot-firmware-integrity-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-platform-boot-firmware-integrity-baseline.sh
```
