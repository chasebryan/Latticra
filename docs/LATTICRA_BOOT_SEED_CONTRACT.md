# Latticra Boot Seed Contract

Status: boot-smoke seed
Evidence level: local build and QEMU smoke only
Scope: provide a minimal GRUB Multiboot2 kernel seed that proves the local ISO toolchain can load Latticra-controlled boot code.

## Purpose

The boot seed is the first executable boot artifact for the OS-image lane. It writes `LATTICRA_BOOT_SEED_OK` to COM1 and a short VGA message after GRUB transfers control to the kernel.

It is not the Latticra OS, not an installer, not a root filesystem, not a shell, not a driver stack, not a persistence layer, and not a production operating-system claim.

```text
latticra_boot_seed_contract_present=1
boot_seed_source_present=1
boot_seed_build_script_present=1
boot_seed_qemu_smoke_script_present=1
boot_seed_vm_image_build_script_present=1
boot_seed_vm_qcow2_artifact_present=0
boot_seed_sbom_generator_present=1
boot_seed_kernel_artifact_created_by_build=<0-or-1>
boot_seed_iso_artifact_created_by_build=<0-or-1>
boot_seed_vm_qcow2_artifact_created_by_build=<0-or-1>
boot_seed_qemu_smoke_ready=<0-or-1>
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
```

## Sources

```text
boot/latticra-boot-seed/boot.S
boot/latticra-boot-seed/kernel.c
boot/latticra-boot-seed/linker.ld
boot/latticra-boot-seed/grub.cfg
```

## Commands

Build the seed ELF and ISO:

```sh
sh scripts/latticra-boot-seed-build.sh --output-dir build/boot-seed
```

Smoke boot the ISO under QEMU/UEFI:

```sh
sh scripts/latticra-boot-seed-qemu-smoke.sh --iso build/boot-seed/latticra-boot-seed.iso --output-dir build/boot-seed/qemu-smoke
```

Build a qcow2 VM image that boots the same seed from a FAT EFI system image:

```sh
sh scripts/latticra-boot-seed-vm-image-build.sh --kernel build/boot-seed/latticra-boot-seed.elf --output-dir build/boot-seed
```

Smoke boot the qcow2 VM image under QEMU/UEFI:

```sh
sh scripts/latticra-boot-seed-qemu-smoke.sh --disk-image build/boot-seed/latticra-boot-seed.qcow2 --format qcow2 --output-dir build/boot-seed/vm-qemu-smoke
```

Generate the local boot-seed SBOM:

```sh
sh scripts/latticra-boot-seed-sbom-generate.sh --iso build/boot-seed/latticra-boot-seed.iso --vm-image build/boot-seed/latticra-boot-seed.qcow2 --kernel build/boot-seed/latticra-boot-seed.elf --efi-bootloader build/boot-seed/BOOTX64.EFI --esp-raw build/boot-seed/latticra-boot-seed-esp.raw > build/boot-seed/sbom.spdx.json
```

The QEMU smoke script records a serial log and passes only when the log contains:

```text
LATTICRA_BOOT_SEED_OK
```

## Local Firmware Note

The Homebrew GRUB toolchain currently available on this host provides `x86_64-efi` modules, not `i386-pc` BIOS modules. This seed therefore records a local UEFI smoke path here. SeaBIOS remains a separate compatibility target that needs an i386-pc GRUB toolchain or equivalent BIOS boot builder.

## Non-claims

This contract does not mark Latticra ready for hardware installation, full operating-system installation, production deployment, or daily-driver use.
