#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  seabios-grub-boot-preview-boot-artifact-manifest-template.sh [--manifest <path>]

Emits a no-effect SeaBIOS/GRUB boot-preview boot artifact manifest template. It
validates the fixture manifest and prints future artifact metadata requirements.
It does not create disk images, invoke GRUB tools, install kernels, write
initramfs files, run QEMU, write boot state, or mutate the host.
USAGE
}

fail() {
  printf 'seabios grub boot preview boot artifact manifest template: %s\n' "$1" >&2
  exit "${2:-1}"
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

MANIFEST="installer/manifests/seabios-grub-boot-preview.toml"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

[ -f "$MANIFEST" ] || fail "manifest not found: $MANIFEST" 66

require_manifest_field 'name = "seabios-grub-boot-preview"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_preview_manifest_fixture_present = true'
require_manifest_field 'boot_preview_manifest_validated = true'
require_manifest_field 'boot_artifact_manifest_present = false'
require_manifest_field 'boot_artifact_checksum_recorded = false'
require_manifest_field 'boot_artifact_signature_recorded = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'profile = "x86_64-seabios-grub-preview"'
require_manifest_field 'profile = "x86_64-grub2-bios-preview"'
require_manifest_field 'profile = "x86_64-grub2-uefi-preview"'
require_manifest_field 'seabios_grub_boot_claim_allowed = false'

MANIFEST_ABS=$(cd "$(dirname -- "$MANIFEST")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MANIFEST")")
MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST_ABS")

cat <<REPORT
SEABIOS GRUB BOOT PREVIEW BOOT ARTIFACT MANIFEST TEMPLATE

template_status=ok
seabios_grub_boot_preview_boot_artifact_manifest_template_present=1
boot_artifact_manifest_template_mode=no-effect-template
boot_artifact_manifest_template_decision=blocked-template-only-no-artifact
boot_artifact_manifest_template_complete=0
boot_artifact_manifest_ready=0
boot_artifact_manifest_present=0
manifest_path=$MANIFEST
manifest_measurement=$MANIFEST_MEASUREMENT

[required_future_manifest_fields]
artifact_id=<required-before-boot-artifact-manifest>
artifact_format=<required-before-boot-artifact-manifest>
artifact_path=<required-before-boot-artifact-manifest>
artifact_sha256=<required-before-boot-artifact-manifest>
target_firmware=<required-before-boot-artifact-manifest>
target_bootloader=<required-before-boot-artifact-manifest>
partition_scheme=<required-before-boot-artifact-manifest>
bios_boot_partition_declared=<required-before-boot-artifact-manifest>
efi_system_partition_declared=<required-before-boot-artifact-manifest>
grub_config_path=<required-before-boot-artifact-manifest>
grub_config_sha256=<required-before-boot-artifact-manifest>
kernel_image_path=<required-before-boot-artifact-manifest>
kernel_image_sha256=<required-before-boot-artifact-manifest>
initramfs_path=<required-before-boot-artifact-manifest>
initramfs_sha256=<required-before-boot-artifact-manifest>
serial_console_enabled=<required-before-boot-artifact-manifest>
operator_recovery_path=<required-before-boot-artifact-manifest>
rollback_or_recovery_path=<required-before-boot-artifact-manifest>
sbom_path=<required-before-boot-artifact-manifest>
sbom_sha256=<required-before-boot-artifact-manifest>
signature_path=<required-before-boot-artifact-manifest>
signature_sha256=<required-before-boot-artifact-manifest>

[profile:x86_64-seabios-grub-preview]
profile_template_present=1
target_firmware=seabios
target_bootloader=grub2
artifact_format=<qcow2-or-raw-or-iso-required-before-boot-evidence>
partition_scheme=<mbr-or-gpt-required-before-boot-evidence>
bios_boot_partition_declared=<required-before-boot-evidence>
efi_system_partition_declared=0
serial_console_enabled=1
profile_boot_artifact_manifest_ready=0

[profile:x86_64-grub2-bios-preview]
profile_template_present=1
target_firmware=seabios
target_bootloader=grub2-bios
artifact_format=<qcow2-or-raw-or-iso-required-before-boot-evidence>
partition_scheme=<mbr-or-gpt-required-before-boot-evidence>
bios_boot_partition_declared=<required-before-boot-evidence>
efi_system_partition_declared=0
serial_console_enabled=1
profile_boot_artifact_manifest_ready=0

[profile:x86_64-grub2-uefi-preview]
profile_template_present=1
target_firmware=uefi
target_bootloader=grub2-uefi
artifact_format=<qcow2-or-raw-or-iso-required-before-boot-evidence>
partition_scheme=gpt
bios_boot_partition_declared=0
efi_system_partition_declared=<required-before-boot-evidence>
serial_console_enabled=1
profile_boot_artifact_manifest_ready=0

[non_effects]
boot_artifact_manifest_written=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
disk_image_created=0
disk_image_written=0
iso_created=0
grub_install_invoked=0
grub_mkconfig_invoked=0
grub_mkrescue_invoked=0
kernel_install_performed=0
initramfs_write_performed=0
firmware_mutation_performed=0
bootloader_write_performed=0
partition_mutation_performed=0
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
host_mutation_performed=0
network_performed=0
root_authority=0
bootable_os_ready=0
production_os_claim=0
REPORT
