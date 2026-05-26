#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  seabios-grub-boot-preview-evidence-validate.sh [--manifest <path>]

Validates the no-effect SeaBIOS/GRUB boot-preview evidence fixture. This is a
readiness gate for future QEMU and serial-console evidence, not a VM launcher.
It does not run QEMU, invoke GRUB tools, create disk images, write boot state,
or mutate the host.
USAGE
}

fail() {
  printf 'seabios grub boot preview evidence validate: %s\n' "$1" >&2
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
    fail "manifest has forbidden premature evidence claim: $pattern" 65
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
forbid_manifest_field 'qemu_i440fx_seabios_boot_validation_completed = true'
forbid_manifest_field 'qemu_grub2_bios_boot_validation_completed = true'
forbid_manifest_field 'qemu_ovmf_grub2_uefi_boot_validation_completed = true'
forbid_manifest_field 'qemu_boot_execution_recorded = true'
forbid_manifest_field 'serial_console_boot_log_recorded = true'
forbid_manifest_field 'operator_console_boot_path_recorded = true'
forbid_manifest_field 'read_only_vm_evidence_recorded = true'
forbid_manifest_field 'operator_recovery_runbook_present = true'
forbid_manifest_field 'qemu_execution_allowed_by_guard = true'
forbid_manifest_field 'seabios_grub_boot_claim_allowed = true'
forbid_manifest_field 'grub_bootloader_write_allowed = true'
forbid_manifest_field 'bootable_os_ready = true'
forbid_manifest_field 'production_os_claim = true'

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
require_manifest_field 'profile = "x86_64-seabios-grub-preview"'
require_manifest_field 'profile = "x86_64-grub2-bios-preview"'
require_manifest_field 'profile = "x86_64-grub2-uefi-preview"'
require_manifest_field 'target_firmware = "seabios"'
require_manifest_field 'target_firmware = "uefi"'
require_manifest_field 'target_bootloader = "grub2"'
require_manifest_field 'target_bootloader = "grub2-bios"'
require_manifest_field 'target_bootloader = "grub2-uefi"'
require_manifest_field 'qemu_machine = "pc-i440fx"'
require_manifest_field 'qemu_machine = "q35"'
require_manifest_field 'qemu_binary = "qemu-system-x86_64"'
require_manifest_field 'qemu_boot_execution_recorded = false'
require_manifest_field 'serial_console_enabled = true'
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

MANIFEST_ABS=$(cd "$(dirname -- "$MANIFEST")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MANIFEST")")
MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST_ABS")

cat <<REPORT
SEABIOS GRUB BOOT PREVIEW EVIDENCE VALIDATION

validation_status=ok
seabios_grub_boot_preview_evidence_validation_present=1
boot_evidence_validation_mode=no-effect-readiness-check
boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence
boot_evidence_candidate_ready=0
boot_preview_manifest_fixture_present=1
boot_preview_manifest_validated=1
boot_artifact_manifest_present=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
qemu_i440fx_seabios_boot_validation_completed=0
qemu_grub2_bios_boot_validation_completed=0
qemu_ovmf_grub2_uefi_boot_validation_completed=0
serial_console_boot_log_recorded=0
operator_console_boot_path_recorded=0
read_only_vm_evidence_recorded=0
operator_recovery_runbook_present=0
qemu_execution_allowed_by_guard=0
seabios_grub_boot_claim_allowed=0
bootable_os_ready=0
production_os_claim=0
manifest_path=$MANIFEST
manifest_measurement=$MANIFEST_MEASUREMENT

[profile:x86_64-seabios-grub-preview]
profile_manifest_present=1
target_firmware=seabios
target_bootloader=grub2
qemu_machine=pc-i440fx
serial_console_enabled=1
qemu_boot_execution_recorded=0
serial_console_boot_log_recorded=0
profile_boot_evidence_ready=0

[profile:x86_64-grub2-bios-preview]
profile_manifest_present=1
target_firmware=seabios
target_bootloader=grub2-bios
qemu_machine=pc-i440fx
serial_console_enabled=1
qemu_boot_execution_recorded=0
serial_console_boot_log_recorded=0
profile_boot_evidence_ready=0

[profile:x86_64-grub2-uefi-preview]
profile_manifest_present=1
target_firmware=uefi
target_bootloader=grub2-uefi
qemu_machine=q35
serial_console_enabled=1
qemu_boot_execution_recorded=0
serial_console_boot_log_recorded=0
profile_boot_evidence_ready=0

[missing_required_future_evidence]
qemu_i440fx_seabios_boot_validation=missing
qemu_grub2_bios_boot_validation=missing
qemu_ovmf_grub2_uefi_boot_validation=missing
serial_console_boot_log=missing
operator_console_boot_path=missing
read_only_vm_evidence=missing
operator_recovery_runbook=missing
artifact_checksum=missing

[non_effects]
qemu_run_performed=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
grub_install_invoked=0
grub_mkconfig_invoked=0
grub_mkrescue_invoked=0
disk_image_created=0
disk_image_written=0
iso_created=0
firmware_mutation_performed=0
bootloader_write_performed=0
partition_mutation_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
REPORT
