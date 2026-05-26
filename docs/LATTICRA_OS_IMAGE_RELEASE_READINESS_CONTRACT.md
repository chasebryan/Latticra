# Latticra OS Image Release Readiness Contract

Status: contract record
Evidence level: 10 target, ISO USB and VM image readiness contract only
Scope: prepare the release lane for a future Latticra ISO, USB write command, and virtual machine image without claiming that a bootable operating system artifact exists yet.

## Purpose

This contract defines what must be present before Latticra can offer users a hardware install path from a USB ISO and a virtual machine image for testing.

It is a release-preparation lane. It does not create an ISO, create a VM image, write a USB device, run QEMU, install a bootloader, install a kernel, mutate firmware, or claim that Latticra is ready as a full operating system.

```text
latticra_os_image_release_readiness_contract_present=1
iso_artifact_present=0
usb_write_command_template_present=1
usb_write_execution_allowed=0
vm_image_artifact_present=0
vm_test_command_template_present=1
qemu_execution_allowed_by_guard=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
```

## Current Manifest

The current fixture manifest is:

```text
installer/manifests/latticra-os-image-release.toml
```

The manifest records the future artifact names, target profiles, and blocked authority flags for:

```text
x86_64-usb-iso
x86_64-qemu-qcow2
x86_64-qemu-iso
```

## Required Release Artifact Set

A future reviewed release candidate should use a deterministic artifact directory such as:

```text
artifacts/os-images/<version>/
```

Minimum hardware-install artifacts:

```text
latticra-x86_64.iso
latticra-x86_64.iso.sha256
latticra-x86_64.iso.sig
manifest.txt
sbom.spdx.json
```

Minimum VM-test artifacts:

```text
latticra-x86_64.qcow2
latticra-x86_64.qcow2.sha256
latticra-x86_64.qcow2.sig
manifest.txt
sbom.spdx.json
```

The ISO and VM image may not be described as ready until checksums, signatures or explicit unsigned-local status, SBOM metadata, boot evidence, recovery steps, and install evidence are reviewed.

## Commands

Preflight the fixture:

```sh
sh scripts/latticra-os-image-release-preflight.sh
```

Generate a Linux USB write command for operator review:

```sh
sh scripts/latticra-os-image-usb-write-command.sh --iso artifacts/os-images/<version>/latticra-x86_64.iso --device /dev/sdX --platform linux
```

Generate a macOS USB write command for operator review:

```sh
sh scripts/latticra-os-image-usb-write-command.sh --iso artifacts/os-images/<version>/latticra-x86_64.iso --device /dev/rdiskN --platform macos
```

Generate a QEMU VM test command for operator review:

```sh
sh scripts/latticra-os-image-vm-test-command.sh --image artifacts/os-images/<version>/latticra-x86_64.qcow2 --format qcow2 --firmware seabios
```

These scripts print commands and evidence fields. They do not run the USB write command or QEMU command.

## USB Write Command Boundary

The command generator may print a command shaped like:

```text
usb_write_command=sudo dd if='<iso-path>' of='<target-device>' bs=4M conv=fsync status=progress
post_write_command=sync
```

Before an operator runs a printed write command, the release evidence must include:

```text
iso_artifact_present=1
iso_artifact_sha256_recorded=1
iso_checksum_verified_by_operator=1
target_device_verified_removable=1
target_device_contains_no_required_data=1
operator_recovery_path_recorded=1
operator_consent_recorded=1
```

The generator must preserve:

```text
usb_write_execution_allowed=0
usb_write_executed=0
partition_mutation_performed=0
host_mutation_performed=0
```

## VM Image Test Boundary

The VM command generator may print a command shaped like:

```text
qemu_test_command=qemu-system-x86_64 ...
```

Before a VM image can become accepted test evidence, the release evidence must include:

```text
vm_image_artifact_present=1
vm_image_sha256_recorded=1
vm_image_checksum_verified_by_operator=1
qemu_argv_recorded=1
serial_console_boot_log_recorded=1
read_only_vm_evidence_recorded=1
operator_recovery_path_recorded=1
```

The generator must preserve:

```text
qemu_execution_allowed_by_guard=0
qemu_run_performed=0
qemu_boot_execution_recorded=0
host_mutation_performed=0
```

## Required Promotion Evidence

Before any future claim changes from `0` to `1`, the project needs reviewed evidence for:

```text
source_tag_recorded=1
build_environment_recorded=1
iso_build_command_recorded=1
vm_image_build_command_recorded=1
artifact_reproducibility_reviewed=1
artifact_sha256_recorded=1
artifact_signature_recorded_or_unsigned_local_status_declared=1
sbom_recorded=1
license_metadata_recorded=1
bootloader_configuration_recorded=1
kernel_image_recorded=1
initramfs_recorded=1
hardware_usb_write_transcript_recorded=1
hardware_install_transcript_recorded=1
vm_boot_transcript_recorded=1
serial_console_boot_log_recorded=1
rollback_or_recovery_path_recorded=1
post_install_verification_recorded=1
uninstall_or_reimage_recovery_recorded=1
multi_machine_validation_recorded=1
```

## Guard Validation

This lane is guarded by:

```sh
sh scripts/test-latticra-os-image-release-readiness-contract.sh
sh scripts/test-latticra-os-image-usb-write-command.sh
sh scripts/test-latticra-os-image-vm-test-command.sh
```

Expected outputs:

```text
latticra_os_image_release_readiness_contract: ok
latticra_os_image_usb_write_command: ok
latticra_os_image_vm_test_command: ok
```

## Current Classification

```text
os_image_release_readiness_contract_present=1
os_image_release_manifest_fixture_present=1
iso_artifact_present=0
vm_image_artifact_present=0
usb_write_command_template_present=1
vm_test_command_template_present=1
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
```

## Non-claims

This contract is not a bootable ISO, not a VM image, not a USB writer, not a hardware installer, not a production installer, not operating-system completeness, not a daily-driver readiness claim, not security hardening, not sandboxing, not malware prevention, not ransomware prevention, and not a production OS claim.
