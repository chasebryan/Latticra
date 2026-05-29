#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  seabios-grub-boot-preview-preflight.sh [--manifest <path>]

Emits a no-effect SeaBIOS/GRUB boot-preview preflight report. It validates the
fixture manifest and reports local tool visibility, but it does not run QEMU,
invoke GRUB tools, create disk images, write boot state, or mutate the host.
USAGE
}

fail() {
  printf 'seabios grub boot preview preflight: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

tool_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

ovmf_detected() {
  for candidate in \
    /usr/share/OVMF/OVMF_CODE.fd \
    /usr/share/edk2/ovmf/OVMF_CODE.fd \
    /usr/share/qemu/OVMF.fd \
    /opt/homebrew/share/qemu/edk2-x86_64-code.fd
  do
    if [ -f "$candidate" ]; then
      printf '1\n'
      return
    fi
  done
  printf '0\n'
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
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'profile = "x86_64-seabios-grub-preview"'
require_manifest_field 'profile = "x86_64-grub2-bios-preview"'
require_manifest_field 'profile = "x86_64-grub2-uefi-preview"'
require_manifest_field 'qemu_i440fx_seabios_boot_validation_completed = false'
require_manifest_field 'qemu_grub2_bios_boot_validation_completed = false'
require_manifest_field 'qemu_ovmf_grub2_uefi_boot_validation_completed = false'
require_manifest_field 'seabios_grub_boot_claim_allowed = false'

QEMU_SYSTEM_X86_64_AVAILABLE=$(tool_available qemu-system-x86_64)
GRUB_MKRESCUE_AVAILABLE=$(tool_available grub-mkrescue)
GRUB_INSTALL_AVAILABLE=$(tool_available grub-install)
XORRISO_AVAILABLE=$(tool_available xorriso)
OVMF_FIRMWARE_DETECTED=$(ovmf_detected)

cat <<REPORT
SEABIOS GRUB BOOT PREVIEW PREFLIGHT

preflight_status=ok
seabios_grub_boot_preview_preflight_present=1
preflight_mode=no-effect-report
preflight_decision=blocked-fixture-only-no-boot-execution
manifest_path=$MANIFEST
manifest_fixture_valid=1
boot_preview_manifest_fixture_present=1
boot_preview_manifest_validated=1
boot_artifact_manifest_present=0
boot_artifact_checksum_recorded=0
boot_artifact_signature_recorded=0
qemu_system_x86_64_available=$QEMU_SYSTEM_X86_64_AVAILABLE
grub_mkrescue_available=$GRUB_MKRESCUE_AVAILABLE
grub_install_available=$GRUB_INSTALL_AVAILABLE
xorriso_available=$XORRISO_AVAILABLE
ovmf_firmware_detected=$OVMF_FIRMWARE_DETECTED
x86_64_seabios_grub_preview_preflight_decision=blocked-missing-boot-artifact-manifest
x86_64_grub2_bios_preview_preflight_decision=blocked-missing-boot-artifact-manifest
x86_64_grub2_uefi_preview_preflight_decision=blocked-missing-boot-artifact-manifest
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
qemu_i440fx_seabios_boot_validation_completed=0
qemu_grub2_bios_boot_validation_completed=0
qemu_ovmf_grub2_uefi_boot_validation_completed=0
grub_install_invoked=0
grub_mkconfig_invoked=0
grub_mkrescue_invoked=0
disk_image_created=0
disk_image_written=0
iso_created=0
serial_console_boot_log_recorded=0
operator_console_boot_path_recorded=0
read_only_vm_evidence_recorded=0
firmware_mutation_performed=0
bootloader_write_performed=0
partition_mutation_performed=0
mbr_write_performed=0
gpt_write_performed=0
efi_variable_write_performed=0
esp_write_performed=0
kernel_install_performed=0
initramfs_write_performed=0
driver_load_performed=0
service_install_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
bootable_os_ready=0
production_os_claim=0
next_required_evidence=qemu-artifact-manifest-with-checksum-serial-log-and-recovery-path
REPORT
