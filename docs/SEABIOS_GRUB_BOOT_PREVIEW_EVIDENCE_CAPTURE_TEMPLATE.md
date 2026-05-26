# SeaBIOS and GRUB Boot Preview Evidence Capture Template

Status: no-effect boot-preview evidence capture template
Evidence level: 8 target, template only
Scope: future QEMU evidence bundle shape for SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot-preview profiles.

## Purpose

This template defines what a future boot evidence bundle must record before Latticra can make any boot-preview claim.

It is a capture template only. It does not execute QEMU, invoke GRUB, create an ISO, create a disk image, write bootloader state, record a serial log, or promote Latticra to a bootable operating system.

```text
seabios_grub_boot_preview_evidence_capture_template_present=1
capture_template_mode=no-effect-template
capture_template_decision=blocked-template-only-no-boot-execution
capture_template_complete=0
boot_evidence_record_ready=0
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-evidence-template.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-evidence-template.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

The command emits a deterministic evidence-record template to stdout.

The QEMU argv template companion is:

```sh
sh scripts/seabios-grub-boot-preview-qemu-argv-template.sh
```

It prints future profile-specific QEMU argv record placeholders without running QEMU.

The Boot artifact manifest template companion is:

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh
```

It prints future boot artifact metadata placeholders without creating disk images, installing GRUB, or writing boot files.

## Required Future Evidence Fields

A future completed evidence bundle must record:

```text
operator_review_id
preflight_report_path
preflight_report_sha256
boot_preview_manifest_path
boot_preview_manifest_sha256
boot_artifact_manifest_path
boot_artifact_manifest_sha256
boot_artifact_manifest_template_path
disk_image_path
disk_image_sha256
artifact_format
target_firmware
target_bootloader
qemu_machine
qemu_binary
qemu_argv_record_path
qemu_argv_template_path
serial_console_boot_log_path
serial_console_boot_log_sha256
boot_result
operator_console_boot_path
operator_recovery_path
rollback_or_recovery_path
host_mutation_performed
firmware_mutation_performed
bootloader_write_performed
```

## Required Profiles

The template keeps separate placeholders for:

```text
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
```

Each remains blocked until artifact, QEMU argv, serial-log, and recovery evidence exist.

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-evidence-template.sh
```

Expected output:

```text
seabios_grub_boot_preview_evidence_template: ok
```

## Non-claims

This template does not create a boot artifact manifest, boot a VM, run QEMU, invoke GRUB, create a disk image, create an ISO, install a kernel, install an initramfs, mutate firmware, write bootloader state, change host boot state, prove SeaBIOS compatibility, prove GRUB compatibility, or make Latticra installer-ready as a production OS.
