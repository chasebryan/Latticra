# SeaBIOS and GRUB Boot Preview QEMU Argv Template

Status: no-effect boot-preview QEMU argv template
Evidence level: 8 target, argv template only
Scope: future QEMU invocation records for SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot-preview profiles.

## Purpose

This template defines how future QEMU argv records must be captured before any boot-preview evidence can be promoted.

It is not a VM launcher. It does not execute QEMU, create a disk image, invoke GRUB, write firmware state, write bootloader state, or claim that Latticra is bootable.

```text
seabios_grub_boot_preview_qemu_argv_template_present=1
qemu_argv_template_mode=no-effect-template
qemu_argv_template_decision=blocked-template-only-no-qemu-execution
qemu_argv_record_ready=0
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-qemu-argv-template.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-qemu-argv-template.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

## Required Future Inputs

A future argv record must not be accepted unless these inputs exist:

```text
operator_review_id
boot_artifact_manifest_template_path
boot_artifact_manifest_validation_report_path
boot_artifact_manifest_path
disk_image_path
disk_image_sha256
serial_console_boot_log_path
qemu_argv_record_path
operator_recovery_path
rollback_or_recovery_path
```

The UEFI profile also requires:

```text
ovmf_code_path
ovmf_vars_template_path
ovmf_vars_ephemeral_copy_path
```

## Required Non-Effects

The template must always preserve:

```text
qemu_run_performed=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
grub_install_invoked=0
grub_mkrescue_invoked=0
disk_image_created=0
disk_image_written=0
firmware_mutation_performed=0
bootloader_write_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
```

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh
```

Expected output:

```text
seabios_grub_boot_preview_qemu_argv_template: ok
```

## Non-claims

This template does not prove SeaBIOS boot, GRUB BIOS boot, GRUB UEFI boot, QEMU compatibility, kernel readiness, initramfs readiness, artifact integrity, recovery safety, or production OS readiness.
