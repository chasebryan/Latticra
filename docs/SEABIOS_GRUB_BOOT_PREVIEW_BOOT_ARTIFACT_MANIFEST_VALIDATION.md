# SeaBIOS and GRUB Boot Preview Boot Artifact Manifest Validation

Status: no-effect boot-preview boot artifact manifest validation
Evidence level: 8 target, validation gate only
Scope: current fixture validation for future SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI boot artifact manifests.

## Purpose

This validation gate makes the boot artifact manifest lane checkable before any boot media exists.

It validates that the current fixture remains incomplete, non-authoritative, and unable to promote a boot claim. It does not accept a production artifact, create a disk image, create an ISO, invoke GRUB, install a kernel, write an initramfs, run QEMU, or mutate host boot state.

```text
seabios_grub_boot_preview_boot_artifact_manifest_validation_present=1
boot_artifact_manifest_validation_mode=no-effect-readiness-check
boot_artifact_manifest_validation_decision=blocked-fixture-only-incomplete
boot_artifact_manifest_candidate_ready=0
boot_artifact_manifest_present=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
qemu_execution_allowed_by_guard=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

## Required Fixture Fields

The validator requires the current preview fixture to keep these blocked fields:

```text
status = "fixture-only"
boot_artifact_manifest_present = false
boot_artifact_checksum_recorded = false
boot_artifact_signature_recorded = false
bootable_os_ready = false
production_os_claim = false
qemu_execution_allowed_by_guard = false
seabios_grub_boot_claim_allowed = false
grub_bootloader_write_allowed = false
```

The artifact section must remain a placeholder:

```text
format = "none"
disk_image_path = "none"
disk_image_sha256 = "none"
signature_path = "none"
sbom_path = "none"
kernel_image_path = "none"
initramfs_path = "none"
grub_config_path = "none"
operator_recovery_path = "none"
```

## Required Profiles

The validator requires all preview profiles to remain present:

```text
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
```

Each profile remains blocked until artifact metadata, checksums, QEMU argv records, serial-console logs, and recovery paths are recorded by a later evidence lane.

## Required Rejections

The validator must reject premature claims for:

```text
boot_artifact_manifest_present = true
boot_artifact_checksum_recorded = true
boot_artifact_signature_recorded = true
bootable_os_ready = true
production_os_claim = true
qemu_execution_allowed_by_guard = true
seabios_grub_boot_claim_allowed = true
grub_bootloader_write_allowed = true
```

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh
```

Expected output:

```text
seabios_grub_boot_preview_boot_artifact_manifest_validate: ok
```

## Non-claims

This validator does not prove artifact integrity, create boot media, create a bootable Latticra OS image, prove SeaBIOS compatibility, prove GRUB BIOS compatibility, prove GRUB UEFI compatibility, authorize QEMU execution, or make Latticra production installer ready.
