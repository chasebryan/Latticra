# SeaBIOS and GRUB Compatibility Contract

Status: compatibility-readiness contract
Evidence level: 8 target, contract and guard only
Scope: installer and future OS-base compatibility boundaries for SeaBIOS, legacy BIOS, GRUB, and GRUB 2.

## Purpose

Latticra is moving toward an advanced operating-system direction for operators, but the current repository must keep boot claims evidence-bound.

This contract defines what may be said today:

```text
seabios_grub_compatibility_contract_present=1
installer_ready_for_user_local_panel=1
installer_boot_safe_by_absence=1
production_installer_ready=0
bootable_os_ready=0
daily_driver_install_ready=0
```

The current Latticra Panel installer is compatible with SeaBIOS and GRUB in the narrow sense that it is a guarded user-local installer and does not write firmware, partitions, boot sectors, EFI variables, GRUB configuration, or bootloader entries.

It is not yet a SeaBIOS-bootable Latticra image, a GRUB-bootable Latticra image, a production OS installer, or a daily-driver operating system.

## Current installer boundary

The current installer and Panel lane must preserve:

```text
user_local_prefix_only=1
root_authority=0
network_authority=0
host_mutation_authority=0
runtime_enforcement_authority=0
firmware_mutation_allowed=0
bootloader_write_allowed=0
partition_mutation_allowed=0
mbr_write_allowed=0
gpt_write_allowed=0
efi_variable_write_allowed=0
esp_write_allowed=0
grub_cfg_write_allowed=0
grub_install_allowed=0
grub_mkconfig_allowed=0
efibootmgr_allowed=0
kernel_install_allowed=0
initramfs_write_allowed=0
driver_load_allowed=0
service_install_allowed=0
```

That boundary lets the installer be used on hosts that boot through SeaBIOS and GRUB without becoming a bootloader participant.

## Future compatibility targets

Future OS-base work may target these profiles only after explicit evidence records exist:

```text
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
x86_64-qemu-operator-console-preview
```

Required future validation before any bootable claim:

```text
qemu_i440fx_seabios_boot_validation_completed=0
qemu_grub2_bios_boot_validation_completed=0
qemu_ovmf_grub2_uefi_boot_validation_completed=0
serial_console_boot_log_recorded=0
operator_console_boot_path_recorded=0
read_only_vm_evidence_recorded=0
install_plan_preview_for_boot_artifact_recorded=0
rollback_or_recovery_path_recorded=0
```

## Required future boot artifact metadata

Any future boot artifact must declare:

```text
artifact_format=<recorded>
target_firmware=<seabios-or-uefi-or-both>
target_bootloader=<grub2-or-none>
partition_scheme=<mbr-or-gpt-or-hybrid>
bios_boot_partition_declared=<0-or-1>
efi_system_partition_declared=<0-or-1>
grub_config_path=<recorded-or-none>
kernel_image_path=<recorded-or-none>
initramfs_path=<recorded-or-none>
serial_console_enabled=<0-or-1>
operator_recovery_path=<recorded>
checksum_recorded=1
signature_recorded=<0-or-1>
sbom_recorded=<0-or-1>
```

Before those fields are real evidence, Latticra must preserve:

```text
boot_artifact_manifest_present=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
bootable_os_ready=0
production_os_claim=0
```

## Promotion gates

A future SeaBIOS/GRUB compatibility promotion requires:

```text
compatibility_contract_present=1
boot_artifact_manifest_present=1
qemu_seabios_fixture_present=1
qemu_grub2_bios_fixture_present=1
qemu_grub2_uefi_fixture_present=1
operator_console_fixture_present=1
boot_log_reviewed=1
no_host_bootloader_mutation=1
no_firmware_mutation=1
operator_recovery_runbook_present=1
security_non_claims_preserved=1
```

Until every gate is met, status remains:

```text
seabios_grub_boot_claim_allowed=0
grub_bootloader_write_allowed=0
production_os_claim=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-seabios-grub-compatibility-contract.sh
sh scripts/test-seabios-grub-boot-preview-evidence-contract.sh
```

Expected output:

```text
seabios_grub_compatibility_contract: ok
```

## Non-claims

This contract does not create a bootable image, GRUB configuration, disk image, ISO, kernel, initramfs, bootloader entry, firmware entry, VM launcher, hypervisor integration, production installer, or operating-system release.

It does not modify SeaBIOS, GRUB, EFI variables, MBR, GPT, ESP, kernel command lines, initramfs content, services, drivers, partitions, or host boot state.
