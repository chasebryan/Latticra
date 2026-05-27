# Latticra OS Image Build Recipe Contract

Status: contract record
Evidence level: 10 target, build recipe and preflight only
Scope: define the local build inputs and command recipe required before a future Latticra ISO or VM image can be produced.

## Purpose

This contract makes the future image build path inspectable before any artifact is built.

It does not create an ISO, create a QCOW2 image, stage a root filesystem, install GRUB, write USB media, run QEMU, or claim operating-system readiness.

```text
latticra_os_image_build_recipe_contract_present=1
os_image_build_preflight_present=1
os_image_build_recipe_template_present=1
os_image_build_execution_allowed=0
os_image_toolchain_preflight_present=1
os_image_toolchain_ready=0
os_image_input_source_manifest_template_present=1
os_image_input_source_manifest_validation_present=1
os_image_input_source_manifest_candidate_present=0
os_image_input_source_ready_for_input_bundle=0
os_image_input_bundle_manifest_template_present=1
os_image_input_bundle_manifest_validation_present=1
os_image_input_bundle_manifest_candidate_present=0
os_image_input_bundle_ready_for_build_preflight=0
kernel_image_input_present=0
initramfs_input_present=0
rootfs_input_present=0
build_inputs_ready=0
build_toolchain_ready=0
os_image_build_recipe_ready=0
iso_created=0
vm_image_created=0
bootable_os_ready=0
production_os_claim=0
```

## Required Inputs

A future build candidate must provide explicit inputs:

```text
input_bundle_manifest_path=<recorded>
kernel_image_input_path=<recorded>
initramfs_input_path=<recorded>
rootfs_input_path=<recorded>
output_dir=<recorded>
```

Before those inputs are accepted, a source manifest must identify the reviewed producers:

```text
input_source_manifest_path=<recorded>
kernel_source_kind=<external-reviewed-kernel-or-latticra-boot-kernel>
kernel_source_path=<recorded>
kernel_boot_protocol=<recorded-or-none>
kernel_bootable_claim=0
initramfs_source_kind=<recorded>
initramfs_source_path=<recorded>
rootfs_source_kind=<recorded>
rootfs_source_path=<recorded>
```

The current default local paths are placeholders:

```text
build/os-image/kernel
build/os-image/initramfs.img
build/os-image/rootfs.tar
artifacts/os-images/local-candidate/
```

## Input Bundle Manifest Boundary

The input source manifest prevents the build lane from treating ordinary Latticra C report modules or CLI binaries as a bootable kernel:

```text
LATTICRA OS IMAGE INPUT SOURCE MANIFEST
manifest_version=1
source_kind=os-image-input-sources
source_commit=<recorded>
kernel_source_kind=<external-reviewed-kernel-or-latticra-boot-kernel>
kernel_source_path=<path>
kernel_boot_protocol=<recorded-or-none>
kernel_bootable_claim=0
initramfs_source_kind=<recorded>
initramfs_source_path=<path>
rootfs_source_kind=<recorded>
rootfs_source_path=<path>
input_bundle_output_path=<recorded>
operator_recovery_path=<recorded-or-none>
bootable_os_ready=0
production_os_claim=0
```

The validator may mark the source map ready for input-bundle preflight, but it must preserve:

```text
os_image_input_source_ready_for_input_bundle=<0-or-1>
kernel_bootable_claim=0
os_image_build_execution_allowed=0
bootable_os_ready=0
production_os_claim=0
```

The input bundle manifest is the reviewable handoff into the image build lane:

```text
LATTICRA OS IMAGE INPUT BUNDLE MANIFEST
manifest_version=1
bundle_kind=os-image-build-inputs
source_commit=<recorded>
build_environment=<recorded>
kernel_image_input_path=<path>
kernel_image_input_sha256=<sha256>
initramfs_input_path=<path>
initramfs_input_sha256=<sha256>
rootfs_input_path=<path>
rootfs_input_format=<tar-or-tar.gz>
rootfs_input_sha256=<sha256>
operator_recovery_path=<recorded-or-none>
bootable_os_ready=0
production_os_claim=0
```

The validator may prove path and checksum consistency, but it must preserve:

```text
os_image_input_bundle_ready_for_build_preflight=<0-or-1>
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
```

## Required Tools

The preflight reports local visibility for:

```text
qemu-img
xorriso
grub-mkrescue
tar
gzip
sha256sum or shasum
```

Missing tools must block the build recipe from being marked ready.

## Commands

Run the build preflight:

```sh
sh scripts/latticra-os-image-toolchain-preflight.sh
sh scripts/latticra-os-image-build-preflight.sh
```

Generate the input bundle manifest template:

```sh
sh scripts/latticra-os-image-input-source-template.sh
sh scripts/latticra-os-image-input-bundle-template.sh
```

Validate the current source fixture or a future input source manifest:

```sh
sh scripts/latticra-os-image-input-source-validate.sh
sh scripts/latticra-os-image-input-source-validate.sh --source-manifest build/os-image/input-source-map.txt
```

Validate the current fixture or a future input bundle manifest:

```sh
sh scripts/latticra-os-image-input-bundle-validate.sh
sh scripts/latticra-os-image-input-bundle-validate.sh --input-manifest build/os-image/input-bundle.txt
```

Run it with explicit candidate inputs:

```sh
sh scripts/latticra-os-image-build-preflight.sh --kernel build/os-image/kernel --initramfs build/os-image/initramfs.img --rootfs build/os-image/rootfs.tar --output-dir artifacts/os-images/local-candidate
```

The preflight prints future command shapes, including:

```text
future_iso_build_command=grub-mkrescue ...
future_vm_image_create_command=qemu-img create ...
future_input_bundle_validation_command=sh scripts/latticra-os-image-input-bundle-validate.sh ...
future_input_source_validation_command=sh scripts/latticra-os-image-input-source-validate.sh ...
future_artifact_manifest_validation_command=sh scripts/latticra-os-image-artifact-manifest-validate.sh ...
```

It must preserve:

```text
grub_mkrescue_invoked=0
qemu_img_invoked=0
iso_created=0
vm_image_created=0
artifact_manifest_written=0
usb_write_executed=0
qemu_run_performed=0
host_mutation_performed=0
```

## Build Recipe Promotion Gates

Before a future implementation may run the recipe, reviewed evidence must show:

```text
kernel_image_input_present=1
initramfs_input_present=1
rootfs_input_present=1
os_image_input_source_ready_for_input_bundle=1
os_image_input_bundle_ready_for_build_preflight=1
qemu_img_available=1
xorriso_available=1
grub_mkrescue_available=1
source_tag_recorded=1
build_environment_recorded=1
recovery_path_recorded=1
operator_consent_recorded=1
```

Even when those are present, this contract alone must keep:

```text
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
```

## Guard Validation

This contract is guarded by:

```sh
sh scripts/test-latticra-os-image-build-preflight.sh
sh scripts/test-latticra-os-image-input-source-template.sh
sh scripts/test-latticra-os-image-input-source-validate.sh
sh scripts/test-latticra-os-image-input-bundle-template.sh
sh scripts/test-latticra-os-image-input-bundle-validate.sh
```

Expected output:

```text
latticra_os_image_build_preflight: ok
latticra_os_image_input_source_template: ok
latticra_os_image_input_source_validate: ok
latticra_os_image_input_bundle_template: ok
latticra_os_image_input_bundle_validate: ok
```

## Non-claims

This contract is not a kernel, not an initramfs, not a root filesystem, not an ISO builder, not a VM image builder, not a boot proof, not a USB installer, not hardware install readiness, not full OS readiness, and not a production OS claim.
