#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-release-preflight.sh [--manifest <path>]

Emits a no-effect Latticra OS image release preflight report for the future
ISO, USB write command, and VM image lane. It does not create images, write USB
media, run QEMU, install bootloaders, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image release preflight: %s\n' "$1" >&2
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

grub_mkrescue_binary() {
  for candidate in "${GRUB_MKRESCUE:-}" grub-mkrescue x86_64-elf-grub-mkrescue; do
    [ -n "$candidate" ] || continue
    if command -v "$candidate" >/dev/null 2>&1; then
      command -v "$candidate"
      return
    fi
  done
  printf 'missing\n'
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"

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

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_release_readiness_contract_present = true'
require_manifest_field 'iso_artifact_present = false'
require_manifest_field 'iso_artifact_path = "none"'
require_manifest_field 'iso_artifact_sha256 = "none"'
require_manifest_field 'os_image_artifact_manifest_template_present = true'
require_manifest_field 'os_image_artifact_manifest_validation_present = true'
require_manifest_field 'os_image_artifact_manifest_candidate_present = false'
require_manifest_field 'os_image_build_preflight_present = true'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'os_image_input_bundle_manifest_generator_present = true'
require_manifest_field 'boot_seed_contract_present = true'
require_manifest_field 'boot_seed_source_present = true'
require_manifest_field 'boot_seed_build_script_present = true'
require_manifest_field 'boot_seed_qemu_smoke_script_present = true'
require_manifest_field 'boot_seed_vm_image_build_script_present = true'
require_manifest_field 'boot_seed_vm_qcow2_artifact_present = false'
require_manifest_field 'boot_seed_full_os_ready = false'
require_manifest_field 'os_image_toolchain_contract_present = true'
require_manifest_field 'os_image_toolchain_preflight_present = true'
require_manifest_field 'os_image_toolchain_ready = false'
require_manifest_field 'usb_write_command_template_present = true'
require_manifest_field 'usb_write_execution_allowed = false'
require_manifest_field 'vm_image_artifact_present = false'
require_manifest_field 'vm_image_path = "none"'
require_manifest_field 'vm_image_format = "none"'
require_manifest_field 'vm_test_command_template_present = true'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'host_mutation_authority = false'
require_manifest_field 'root_authority = false'
require_manifest_field 'usb_block_device_write_allowed = false'
require_manifest_field 'profile = "x86_64-usb-iso"'
require_manifest_field 'profile = "x86_64-qemu-qcow2"'
require_manifest_field 'profile = "x86_64-qemu-iso"'

QEMU_SYSTEM_X86_64_AVAILABLE=$(tool_available qemu-system-x86_64)
QEMU_IMG_AVAILABLE=$(tool_available qemu-img)
XORRISO_AVAILABLE=$(tool_available xorriso)
GRUB_MKRESCUE_BINARY=$(grub_mkrescue_binary)
GRUB_MKRESCUE_AVAILABLE=0
[ "$GRUB_MKRESCUE_BINARY" != "missing" ] && GRUB_MKRESCUE_AVAILABLE=1
DD_AVAILABLE=$(tool_available dd)

cat <<REPORT
LATTICRA OS IMAGE RELEASE PREFLIGHT

preflight_status=ok
latticra_os_image_release_preflight_present=1
preflight_mode=no-effect-report
preflight_decision=blocked-fixture-only-no-os-image-artifact
manifest_path=$MANIFEST
os_image_release_manifest_fixture_present=1
iso_artifact_present=0
iso_artifact_sha256_recorded=0
os_image_artifact_manifest_template_present=1
os_image_artifact_manifest_validation_present=1
os_image_artifact_manifest_candidate_present=0
os_image_build_preflight_present=1
os_image_build_execution_allowed=0
os_image_input_bundle_manifest_generator_present=1
boot_seed_contract_present=1
boot_seed_source_present=1
boot_seed_build_script_present=1
boot_seed_qemu_smoke_script_present=1
boot_seed_vm_image_build_script_present=1
boot_seed_vm_qcow2_artifact_present=0
boot_seed_full_os_ready=0
os_image_toolchain_preflight_present=1
os_image_toolchain_ready=0
usb_write_command_template_present=1
usb_write_execution_allowed=0
usb_write_executed=0
vm_image_artifact_present=0
vm_image_sha256_recorded=0
vm_test_command_template_present=1
qemu_execution_allowed_by_guard=0
qemu_run_performed=0
qemu_boot_execution_recorded=0
qemu_system_x86_64_available=$QEMU_SYSTEM_X86_64_AVAILABLE
qemu_img_available=$QEMU_IMG_AVAILABLE
xorriso_available=$XORRISO_AVAILABLE
grub_mkrescue_available=$GRUB_MKRESCUE_AVAILABLE
grub_mkrescue_path=$GRUB_MKRESCUE_BINARY
dd_available=$DD_AVAILABLE
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
root_authority=0
network_performed=0
next_required_evidence=reviewed-iso-and-vm-artifacts-with-checksums-signatures-sbom-boot-logs-and-recovery-paths
REPORT
