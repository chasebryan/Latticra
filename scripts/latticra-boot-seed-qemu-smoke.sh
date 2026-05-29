#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-boot-seed-qemu-smoke.sh (--iso <path> | --disk-image <path>) [--format <qcow2|raw>] [--manifest <path>] [--output-dir <path>] [--firmware <auto-or-path>] [--timeout <seconds>]

Boots the Latticra boot-seed ISO under QEMU/UEFI and validates the serial
sentinel. It does not write USB media, mutate firmware, install bootloaders, or
claim full OS readiness.
USAGE
}

fail() {
  printf 'latticra boot seed qemu smoke: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

tool_path() {
  if command -v "$1" >/dev/null 2>&1; then
    command -v "$1"
  else
    printf 'missing\n'
  fi
}

resolve_firmware() {
  candidate="$1"
  if [ "$candidate" != "auto" ]; then
    printf '%s\n' "$candidate"
    return
  fi

  for path in \
    /opt/homebrew/share/qemu/edk2-x86_64-code.fd \
    /usr/share/OVMF/OVMF_CODE.fd \
    /usr/share/edk2/ovmf/OVMF_CODE.fd
  do
    if [ -f "$path" ]; then
      printf '%s\n' "$path"
      return
    fi
  done

  printf 'missing\n'
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ISO=""
DISK_IMAGE=""
DISK_FORMAT="qcow2"
OUTPUT_DIR="build/boot-seed/qemu-smoke"
FIRMWARE="auto"
TIMEOUT_SECONDS="20"
SENTINEL="LATTICRA_BOOT_SEED_OK"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --iso)
      [ "$#" -ge 2 ] || fail "missing value for --iso" 64
      ISO="$2"
      shift 2
      ;;
    --disk-image)
      [ "$#" -ge 2 ] || fail "missing value for --disk-image" 64
      DISK_IMAGE="$2"
      shift 2
      ;;
    --format)
      [ "$#" -ge 2 ] || fail "missing value for --format" 64
      DISK_FORMAT="$2"
      shift 2
      ;;
    --output-dir)
      [ "$#" -ge 2 ] || fail "missing value for --output-dir" 64
      OUTPUT_DIR="$2"
      shift 2
      ;;
    --firmware)
      [ "$#" -ge 2 ] || fail "missing value for --firmware" 64
      FIRMWARE="$2"
      shift 2
      ;;
    --timeout)
      [ "$#" -ge 2 ] || fail "missing value for --timeout" 64
      TIMEOUT_SECONDS="$2"
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
if [ -n "$ISO" ] && [ -n "$DISK_IMAGE" ]; then
  fail "choose either --iso or --disk-image, not both" 64
fi
[ -n "$ISO$DISK_IMAGE" ] || fail "missing --iso or --disk-image" 64
[ -z "$ISO" ] || [ -f "$ISO" ] || fail "boot seed ISO not found: $ISO" 66
[ -z "$DISK_IMAGE" ] || [ -f "$DISK_IMAGE" ] || fail "boot seed disk image not found: $DISK_IMAGE" 66
case "$DISK_FORMAT" in
  qcow2|raw) ;;
  *) fail "unsupported disk image format: $DISK_FORMAT" 64 ;;
esac

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_seed_contract_present = true'
require_manifest_field 'boot_seed_qemu_smoke_script_present = true'
require_manifest_field 'boot_seed_full_os_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

QEMU=$(tool_path qemu-system-x86_64)
TIMEOUT=$(tool_path timeout)
[ "$TIMEOUT" != "missing" ] || TIMEOUT=$(tool_path gtimeout)
FIRMWARE_PATH=$(resolve_firmware "$FIRMWARE")

[ "$QEMU" != "missing" ] || fail "missing required tool: qemu-system-x86_64" 69
[ "$TIMEOUT" != "missing" ] || fail "missing required tool: timeout or gtimeout" 69
[ "$FIRMWARE_PATH" != "missing" ] || fail "missing UEFI firmware path" 69
[ -f "$FIRMWARE_PATH" ] || fail "UEFI firmware not found: $FIRMWARE_PATH" 66

mkdir -p "$OUTPUT_DIR"
SERIAL_LOG="$OUTPUT_DIR/serial.log"
QEMU_LOG="$OUTPUT_DIR/qemu.log"
BOOT_SOURCE="iso"
[ -z "$DISK_IMAGE" ] || BOOT_SOURCE="disk"

QEMU_RC=0
if [ "$BOOT_SOURCE" = "iso" ]; then
  "$TIMEOUT" "$TIMEOUT_SECONDS" \
    "$QEMU" \
    -display none \
    -no-reboot \
    -serial "file:$SERIAL_LOG" \
    -device isa-debug-exit,iobase=0xf4,iosize=0x01 \
    -drive "if=pflash,format=raw,readonly=on,file=$FIRMWARE_PATH" \
    -cdrom "$ISO" \
    -boot d >"$QEMU_LOG" 2>&1 || QEMU_RC="$?"
else
  "$TIMEOUT" "$TIMEOUT_SECONDS" \
    "$QEMU" \
    -display none \
    -no-reboot \
    -serial "file:$SERIAL_LOG" \
    -device isa-debug-exit,iobase=0xf4,iosize=0x01 \
    -drive "if=pflash,format=raw,readonly=on,file=$FIRMWARE_PATH" \
    -drive "format=$DISK_FORMAT,file=$DISK_IMAGE" >"$QEMU_LOG" 2>&1 || QEMU_RC="$?"
fi

if ! grep -Fq "$SENTINEL" "$SERIAL_LOG"; then
  fail "serial sentinel not found in $SERIAL_LOG; qemu exit code $QEMU_RC" 70
fi

cat <<REPORT
LATTICRA BOOT SEED QEMU SMOKE

smoke_status=ok
latticra_boot_seed_qemu_smoke_script_present=1
boot_seed_iso_path=${ISO:-none}
boot_seed_vm_image_path=${DISK_IMAGE:-none}
boot_seed_qemu_boot_source=$BOOT_SOURCE
qemu_system_x86_64_path=$QEMU
uefi_firmware_path=$FIRMWARE_PATH
qemu_exit_code=$QEMU_RC
serial_log_path=$SERIAL_LOG
qemu_log_path=$QEMU_LOG
boot_seed_serial_sentinel=$SENTINEL
boot_seed_qemu_serial_sentinel_recorded=1
boot_seed_qemu_smoke_ready=1
qemu_run_performed=1
usb_write_executed=0
host_mutation_performed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
