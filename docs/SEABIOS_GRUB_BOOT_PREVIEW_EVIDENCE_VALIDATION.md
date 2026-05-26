# SeaBIOS and GRUB Boot Preview Evidence Validation

Status: no-effect boot-preview evidence validation
Evidence level: 8 target, validation gate only
Scope: current fixture validation for future SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot evidence bundles.

## Purpose

This validation gate makes the boot evidence lane checkable before any VM boot evidence exists.

It validates that the current fixture remains unbooted, incomplete, and unable to promote a boot-preview claim. It does not accept a serial log, run QEMU, invoke GRUB, create a disk image, create an ISO, write firmware state, write bootloader state, mutate partitions, or claim Latticra is bootable.

```text
seabios_grub_boot_preview_evidence_validation_present=1
boot_evidence_validation_mode=no-effect-readiness-check
boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence
boot_evidence_candidate_ready=0
qemu_i440fx_seabios_boot_validation_completed=0
qemu_grub2_bios_boot_validation_completed=0
qemu_ovmf_grub2_uefi_boot_validation_completed=0
serial_console_boot_log_recorded=0
operator_console_boot_path_recorded=0
read_only_vm_evidence_recorded=0
operator_recovery_runbook_present=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-evidence-validate.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-evidence-validate.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

## Required Fixture Fields

The validator requires the current preview fixture to preserve:

```text
boot_artifact_manifest_present = false
boot_artifact_checksum_recorded = false
qemu_i440fx_seabios_boot_validation_completed = false
qemu_grub2_bios_boot_validation_completed = false
qemu_ovmf_grub2_uefi_boot_validation_completed = false
serial_console_boot_log_recorded = false
operator_console_boot_path_recorded = false
read_only_vm_evidence_recorded = false
operator_recovery_runbook_present = false
seabios_grub_boot_claim_allowed = false
grub_bootloader_write_allowed = false
bootable_os_ready = false
production_os_claim = false
```

The protected non-mutation fields must remain:

```text
host_mutation_authority = false
firmware_mutation_allowed = false
bootloader_write_allowed = false
partition_mutation_allowed = false
qemu_execution_allowed_by_guard = false
no_host_bootloader_mutation = true
no_firmware_mutation = true
```

## Required Rejections

The validator must reject premature claims for:

```text
qemu_i440fx_seabios_boot_validation_completed = true
qemu_grub2_bios_boot_validation_completed = true
qemu_ovmf_grub2_uefi_boot_validation_completed = true
serial_console_boot_log_recorded = true
operator_console_boot_path_recorded = true
read_only_vm_evidence_recorded = true
operator_recovery_runbook_present = true
seabios_grub_boot_claim_allowed = true
bootable_os_ready = true
production_os_claim = true
```

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-evidence-validate.sh
```

Expected output:

```text
seabios_grub_boot_preview_evidence_validate: ok
```

## Non-claims

This validator does not run QEMU, create or verify a boot log, prove SeaBIOS boot, prove GRUB BIOS boot, prove GRUB UEFI boot, create a bootable Latticra OS image, authorize bootloader writes, or make Latticra production installer ready.
