# Latticra Platform Boot and Firmware Integrity Baseline Status

Status: status record for platform boot and firmware integrity baseline
Date: 2026-05-28

## Scope

This record tracks the platform boot and firmware integrity baseline for platform inventory, boot mode, UEFI Secure Boot state, Secure Boot key databases, boot binary inventory, TPM and PCR measurement planning, firmware version inventory, firmware update provenance, firmware recovery, boot integrity logging, platform administrator access, rollback planning, incident handoff, and platform-integrity non-claims.

It does not implement Secure Boot, measured boot, TPM attestation, firmware updates, firmware recovery, bootloader signing, boot policy enforcement, bootable OS readiness, hardware root-of-trust behavior, platform integrity enforcement, host mutation, or runtime authority.

## Current fields

```text
platform_boot_firmware_integrity_baseline_present=1
platform_boot_firmware_integrity_status_present=1
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

## Validation

```sh
sh scripts/test-platform-boot-firmware-integrity-baseline.sh
```

Expected output:

```text
platform_boot_firmware_integrity_baseline: ok
```
