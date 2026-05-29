# SeaBIOS and GRUB Boot Preview Boot Artifact Manifest Template

Status: no-effect boot-preview boot artifact manifest template
Evidence level: 8 target, manifest template only
Scope: future boot artifact metadata for SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot-preview profiles.

## Purpose

This template defines the boot artifact manifest shape required before any future disk image, ISO, kernel, initramfs, or GRUB configuration can become boot evidence.

It is not a boot artifact. It does not create a disk image, create an ISO, install GRUB, generate GRUB config, install a kernel, write an initramfs, run QEMU, or mutate host boot state.

```text
seabios_grub_boot_preview_boot_artifact_manifest_template_present=1
boot_artifact_manifest_template_mode=no-effect-template
boot_artifact_manifest_template_decision=blocked-template-only-no-artifact
boot_artifact_manifest_ready=0
boot_artifact_manifest_present=0
disk_image_created=0
disk_image_written=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

## Boot artifact manifest validation

The current fixture is checked by:

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh
```

The validation gate rejects premature bootable, GRUB, QEMU, or production OS claims while keeping the artifact manifest incomplete.

## Required Future Manifest Fields

A future completed boot artifact manifest must record:

```text
artifact_id
artifact_format
artifact_path
artifact_sha256
target_firmware
target_bootloader
partition_scheme
bios_boot_partition_declared
efi_system_partition_declared
grub_config_path
grub_config_sha256
kernel_image_path
kernel_image_sha256
initramfs_path
initramfs_sha256
serial_console_enabled
operator_recovery_path
rollback_or_recovery_path
sbom_path
sbom_sha256
signature_path
signature_sha256
```

## Required Profile Templates

The template keeps separate blocked manifests for:

```text
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
```

Each profile remains incomplete until artifact, checksum, partition, bootloader, kernel, initramfs, serial-console, and recovery metadata exists.

## Required Non-Effects

The template must always preserve:

```text
boot_artifact_manifest_written=0
disk_image_created=0
disk_image_written=0
iso_created=0
grub_install_invoked=0
grub_mkconfig_invoked=0
grub_mkrescue_invoked=0
kernel_install_performed=0
initramfs_write_performed=0
qemu_boot_execution_attempted=0
host_mutation_performed=0
```

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh
```

Expected output:

```text
seabios_grub_boot_preview_boot_artifact_manifest_template: ok
```

## Non-claims

This template does not prove artifact integrity, create boot media, create a bootable Latticra OS image, prove SeaBIOS compatibility, prove GRUB BIOS compatibility, prove GRUB UEFI compatibility, or make Latticra production installer ready.
