#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  seabios-grub-boot-preview-boot-artifact-manifest-validate.sh [--manifest <path>]

Validates the no-effect SeaBIOS/GRUB boot-preview boot artifact manifest
fixture. This is a readiness gate for future artifact metadata, not an artifact
builder. It does not create disk images, invoke GRUB tools, install kernels,
write initramfs files, run QEMU, write boot state, or mutate the host.
USAGE
}

fail() {
  printf 'seabios grub boot preview boot artifact manifest validate: %s\n' "$1" >&2
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

forbid_manifest_field() {
  pattern="$1"
  if grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest has forbidden premature claim: $pattern" 65
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
forbid_manifest_field 'boot_artifact_manifest_present = true'
forbid_manifest_field 'boot_artifact_checksum_recorded = true'
forbid_manifest_field 'boot_artifact_signature_recorded = true'
forbid_manifest_field 'bootable_os_ready = true'
forbid_manifest_field 'production_os_claim = true'
forbid_manifest_field 'qemu_execution_allowed_by_guard = true'
forbid_manifest_field 'seabios_grub_boot_claim_allowed = true'
forbid_manifest_field 'grub_bootloader_write_allowed = true'
require_manifest_field 'boot_artifact_manifest_present = false'
require_manifest_field 'boot_artifact_checksum_recorded = false'
require_manifest_field 'boot_artifact_signature_recorded = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'host_mutation_authority = false'
require_manifest_field 'root_authority = false'
require_manifest_field 'network_authority = false'
require_manifest_field 'firmware_mutation_allowed = false'
require_manifest_field 'bootloader_write_allowed = false'
require_manifest_field 'partition_mutation_allowed = false'
require_manifest_field 'grub_install_allowed = false'
require_manifest_field 'grub_mkconfig_allowed = false'
require_manifest_field 'kernel_install_allowed = false'
require_manifest_field 'initramfs_write_allowed = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'format = "none"'
require_manifest_field 'disk_image_path = "none"'
require_manifest_field 'disk_image_sha256 = "none"'
require_manifest_field 'signature_path = "none"'
require_manifest_field 'sbom_path = "none"'
require_manifest_field 'kernel_image_path = "none"'
require_manifest_field 'initramfs_path = "none"'
require_manifest_field 'grub_config_path = "none"'
require_manifest_field 'operator_recovery_path = "none"'
require_manifest_field 'profile = "x86_64-seabios-grub-preview"'
require_manifest_field 'profile = "x86_64-grub2-bios-preview"'
require_manifest_field 'profile = "x86_64-grub2-uefi-preview"'
require_manifest_field 'target_firmware = "seabios"'
require_manifest_field 'target_firmware = "uefi"'
require_manifest_field 'target_bootloader = "grub2"'
require_manifest_field 'target_bootloader = "grub2-bios"'
require_manifest_field 'target_bootloader = "grub2-uefi"'
require_manifest_field 'serial_console_enabled = true'
require_manifest_field 'qemu_boot_execution_recorded = false'
require_manifest_field 'serial_console_boot_log_recorded = false'
require_manifest_field 'operator_console_boot_path_recorded = false'
require_manifest_field 'read_only_vm_evidence_recorded = false'
require_manifest_field 'qemu_i440fx_seabios_boot_validation_completed = false'
require_manifest_field 'qemu_grub2_bios_boot_validation_completed = false'
require_manifest_field 'qemu_ovmf_grub2_uefi_boot_validation_completed = false'
require_manifest_field 'operator_recovery_runbook_present = false'
require_manifest_field 'no_host_bootloader_mutation = true'
require_manifest_field 'no_firmware_mutation = true'
require_manifest_field 'seabios_grub_boot_claim_allowed = false'
require_manifest_field 'grub_bootloader_write_allowed = false'

forbid_manifest_field 'boot_artifact_manifest_present = true'
forbid_manifest_field 'boot_artifact_checksum_recorded = true'
forbid_manifest_field 'boot_artifact_signature_recorded = true'
forbid_manifest_field 'bootable_os_ready = true'
forbid_manifest_field 'production_os_claim = true'
forbid_manifest_field 'qemu_execution_allowed_by_guard = true'
forbid_manifest_field 'seabios_grub_boot_claim_allowed = true'
forbid_manifest_field 'grub_bootloader_write_allowed = true'

MANIFEST_ABS=$(cd "$(dirname -- "$MANIFEST")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MANIFEST")")
MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST_ABS")

cat <<REPORT
SEABIOS GRUB BOOT PREVIEW BOOT ARTIFACT MANIFEST VALIDATION

validation_status=ok
seabios_grub_boot_preview_boot_artifact_manifest_validation_present=1
boot_artifact_manifest_validation_mode=no-effect-readiness-check
boot_artifact_manifest_validation_decision=blocked-fixture-only-incomplete
boot_artifact_manifest_candidate_ready=0
boot_preview_manifest_fixture_present=1
boot_preview_manifest_validated=1
boot_artifact_manifest_present=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
bootable_os_ready=0
production_os_claim=0
qemu_execution_allowed_by_guard=0
manifest_path=$MANIFEST
manifest_measurement=$MANIFEST_MEASUREMENT

[artifact_placeholders]
artifact_format=none
disk_image_path=none
disk_image_sha256=none
signature_path=none
sbom_path=none
kernel_image_path=none
initramfs_path=none
grub_config_path=none
operator_recovery_path=none

[missing_required_future_fields]
artifact_id=missing
artifact_path=missing
artifact_sha256=missing
grub_config_sha256=missing
kernel_image_sha256=missing
initramfs_sha256=missing
operator_recovery_runbook=missing
serial_console_boot_log=missing
qemu_argv_record=missing
read_only_vm_evidence=missing

[profile:x86_64-seabios-grub-preview]
profile_manifest_present=1
target_firmware=seabios
target_bootloader=grub2
serial_console_enabled=1
qemu_boot_execution_recorded=0
profile_boot_artifact_manifest_ready=0

[profile:x86_64-grub2-bios-preview]
profile_manifest_present=1
target_firmware=seabios
target_bootloader=grub2-bios
serial_console_enabled=1
qemu_boot_execution_recorded=0
profile_boot_artifact_manifest_ready=0

[profile:x86_64-grub2-uefi-preview]
profile_manifest_present=1
target_firmware=uefi
target_bootloader=grub2-uefi
serial_console_enabled=1
qemu_boot_execution_recorded=0
profile_boot_artifact_manifest_ready=0

[non_effects]
boot_artifact_manifest_written=0
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
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
host_mutation_performed=0
network_performed=0
root_authority=0
REPORT
