# Latticra OS Image Toolchain Contract

Status: contract record
Evidence level: 10 target, local toolchain preflight only
Scope: report local tooling required for future ISO, QCOW2, USB, and VM test lanes without installing packages or creating artifacts.

## Purpose

This contract isolates the host toolchain question from the artifact and build-input questions.

It does not install tools, download packages, create images, run QEMU, write USB media, mutate firmware, or claim operating-system readiness.

```text
latticra_os_image_toolchain_contract_present=1
os_image_toolchain_preflight_present=1
os_image_toolchain_ready=0
tool_install_performed=0
network_performed=0
iso_created=0
vm_image_created=0
bootable_os_ready=0
production_os_claim=0
```

## Required Tools

The build and test lanes require visibility for:

```text
qemu-img
qemu-system-x86_64
xorriso
grub-mkrescue compatible binary
tar
gzip
cpio
awk
sed
find
sha256sum or shasum
```

The GRUB rescue tool may be provided as `grub-mkrescue` on Linux hosts or
`x86_64-elf-grub-mkrescue` on Homebrew-based macOS hosts. The preflight reports
the resolved path as `grub_mkrescue_path=<path-or-missing>`.

The current toolchain may be partially present. Missing required tools must keep:

```text
os_image_toolchain_ready=0
os_image_build_recipe_ready=0
```

## Command

Run:

```sh
sh scripts/latticra-os-image-toolchain-preflight.sh
```

The command reports tool visibility only. It must preserve:

```text
tool_install_performed=0
package_manager_invoked=0
network_performed=0
grub_mkrescue_invoked=0
qemu_img_invoked=0
qemu_run_performed=0
host_mutation_performed=0
```

## Guard Validation

This contract is guarded by:

```sh
sh scripts/test-latticra-os-image-toolchain-preflight.sh
```

Expected output:

```text
latticra_os_image_toolchain_preflight: ok
```

## Non-claims

This contract is not a dependency installer, not an ISO builder, not a VM image builder, not a QEMU execution lane, not a USB writer, not hardware install readiness, not full OS readiness, and not a production OS claim.
