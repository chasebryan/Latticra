# SeaBIOS and GRUB Boot Preview Evidence Contract

Status: boot-preview-evidence contract
Evidence level: 8 target, manifest fixture only
Scope: future QEMU evidence for SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot-preview profiles.

## Purpose

Latticra needs a disciplined path from installer-safe compatibility to real boot evidence.

This contract defines the next preview lane without claiming that a bootable Latticra operating-system image exists today.

```text
seabios_grub_boot_preview_evidence_contract_present=1
boot_preview_manifest_fixture_present=1
boot_preview_manifest_validated=1
boot_artifact_manifest_present=0
qemu_boot_execution_recorded=0
serial_console_boot_log_recorded=0
operator_console_boot_path_recorded=0
bootable_os_ready=0
production_os_claim=0
```

## Manifest fixture

The fixture manifest is:

```text
installer/manifests/seabios-grub-boot-preview.toml
```

It records the fields that future boot evidence must replace with real artifact paths, digests, and logs.

The fixture must preserve:

```text
status="fixture-only"
boot_artifact_manifest_present=false
bootable_os_ready=false
production_os_claim=false
host_mutation_authority=false
firmware_mutation_allowed=false
bootloader_write_allowed=false
partition_mutation_allowed=false
mbr_write_allowed=false
gpt_write_allowed=false
efi_variable_write_allowed=false
esp_write_allowed=false
qemu_execution_allowed_by_guard=false
```

## Required preview profiles

Future evidence must keep separate records for:

```text
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
```

Each profile must record:

```text
target_firmware
target_bootloader
qemu_machine
qemu_binary
disk_image_path
disk_image_sha256
boot_log_path
serial_console_enabled
host_bootloader_mutation
firmware_mutation
operator_recovery_path
```

## Promotion requirements

No boot-preview status may be promoted until these fields are true:

```text
boot_artifact_manifest_present=1
boot_artifact_checksum_recorded=1
qemu_i440fx_seabios_boot_validation_completed=1
qemu_grub2_bios_boot_validation_completed=1
qemu_ovmf_grub2_uefi_boot_validation_completed=1
serial_console_boot_log_recorded=1
operator_console_boot_path_recorded=1
read_only_vm_evidence_recorded=1
operator_recovery_runbook_present=1
no_host_bootloader_mutation=1
no_firmware_mutation=1
```

Until then:

```text
seabios_grub_boot_claim_allowed=0
grub_bootloader_write_allowed=0
qemu_boot_execution_allowed_by_guard=0
production_os_claim=0
```

## Guard validation

This preview lane is guarded by:

```sh
sh scripts/test-seabios-grub-boot-preview-evidence-contract.sh
```

Expected output:

```text
seabios_grub_boot_preview_evidence_contract: ok
```

## Non-claims

This contract does not create an ISO, disk image, bootloader configuration, kernel, initramfs, QEMU launcher, VM run, serial log, or operating-system release.

It does not authorize firmware writes, GRUB writes, partition mutation, MBR writes, GPT writes, EFI variable writes, ESP writes, kernel installation, initramfs writes, service installation, driver loading, root escalation, network access, or host boot changes.
