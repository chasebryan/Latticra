# SeaBIOS and GRUB Boot Preview Preflight

Status: no-effect boot-preview preflight
Evidence level: 8 target, local report only
Scope: operator-readable readiness check before any future SeaBIOS, GRUB 2 BIOS, or GRUB 2 UEFI QEMU evidence run.

## Purpose

This preflight makes the boot-preview lane operationally checkable without executing it.

It validates the fixture manifest, reports whether common local tooling is visible, and preserves the current non-claim posture:

```text
seabios_grub_boot_preview_preflight_present=1
preflight_mode=no-effect-report
preflight_decision=blocked-fixture-only-no-boot-execution
manifest_fixture_valid=1
boot_artifact_manifest_present=0
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
bootable_os_ready=0
production_os_claim=0
```

## Command

```sh
sh scripts/seabios-grub-boot-preview-preflight.sh
```

Optional manifest override:

```sh
sh scripts/seabios-grub-boot-preview-preflight.sh --manifest installer/manifests/seabios-grub-boot-preview.toml
```

## Reported Tool Visibility

The preflight reports local visibility only:

```text
qemu_system_x86_64_available=<0-or-1>
grub_mkrescue_available=<0-or-1>
grub_install_available=<0-or-1>
xorriso_available=<0-or-1>
ovmf_firmware_detected=<0-or-1>
```

Tool visibility is not boot evidence. Missing tools do not fail the contract guard because the current lane is still fixture-only.

The evidence capture template for the next non-executing step is:

```sh
sh scripts/seabios-grub-boot-preview-evidence-template.sh
```

## Required Non-Effects

The preflight must always report:

```text
qemu_boot_execution_attempted=0
grub_install_invoked=0
grub_mkrescue_invoked=0
disk_image_created=0
disk_image_written=0
firmware_mutation_performed=0
bootloader_write_performed=0
partition_mutation_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
```

## Guard

```sh
sh scripts/test-seabios-grub-boot-preview-preflight.sh
```

Expected output:

```text
seabios_grub_boot_preview_preflight: ok
```

## Non-claims

This preflight does not create an ISO, create a disk image, write a bootloader, call `grub-install`, call `grub-mkrescue`, run QEMU, boot a VM, record a serial log, install a kernel, install an initramfs, mutate firmware, change host boot state, or promote Latticra to a bootable operating system.
