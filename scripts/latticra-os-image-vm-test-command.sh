#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-vm-test-command.sh --image <path> --format raw|qcow2|iso [--firmware seabios|uefi] [--memory-mib <n>] [--cpus <n>] [--serial-log <path>] [--manifest <path>]

Prints a no-effect QEMU test command for a future Latticra VM image or ISO. It
validates the release fixture and the command shape, but it does not run QEMU,
create images, write firmware variables, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image vm test command: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
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

shell_quote() {
  awk -v value="$1" 'BEGIN {
    gsub(/\047/, "\047\\\047\047", value)
    printf "\047%s\047", value
  }'
}

positive_integer() {
  case "$1" in
    ''|*[!0-9]*) return 1 ;;
    0) return 1 ;;
    *) return 0 ;;
  esac
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
IMAGE=""
FORMAT=""
FIRMWARE="seabios"
MEMORY_MIB="2048"
CPUS="2"
SERIAL_LOG="reports/latticra-os-image-vm-serial.log"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --image)
      [ "$#" -ge 2 ] || fail "missing value for --image" 64
      IMAGE="$2"
      shift 2
      ;;
    --format)
      [ "$#" -ge 2 ] || fail "missing value for --format" 64
      FORMAT="$2"
      shift 2
      ;;
    --firmware)
      [ "$#" -ge 2 ] || fail "missing value for --firmware" 64
      FIRMWARE="$2"
      shift 2
      ;;
    --memory-mib)
      [ "$#" -ge 2 ] || fail "missing value for --memory-mib" 64
      MEMORY_MIB="$2"
      shift 2
      ;;
    --cpus)
      [ "$#" -ge 2 ] || fail "missing value for --cpus" 64
      CPUS="$2"
      shift 2
      ;;
    --serial-log)
      [ "$#" -ge 2 ] || fail "missing value for --serial-log" 64
      SERIAL_LOG="$2"
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

[ -n "$IMAGE" ] || fail "missing --image" 64
[ -n "$FORMAT" ] || fail "missing --format" 64
[ -f "$MANIFEST" ] || fail "manifest not found: $MANIFEST" 66

case "$FORMAT" in
  raw|qcow2|iso) ;;
  *) fail "unsupported format: $FORMAT" 64 ;;
esac

case "$FIRMWARE" in
  seabios|uefi) ;;
  *) fail "unsupported firmware: $FIRMWARE" 64 ;;
esac

positive_integer "$MEMORY_MIB" || fail "memory must be a positive integer" 64
positive_integer "$CPUS" || fail "cpus must be a positive integer" 64

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'vm_image_artifact_present = false'
require_manifest_field 'vm_test_command_template_present = true'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'qemu_execution_allowed = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'profile = "x86_64-qemu-qcow2"'
require_manifest_field 'profile = "x86_64-qemu-iso"'

IMAGE_EXISTS=0
IMAGE_SIZE_BYTES=missing
IMAGE_MEASUREMENT=missing
if [ -f "$IMAGE" ]; then
  IMAGE_EXISTS=1
  IMAGE_SIZE_BYTES=$(wc -c < "$IMAGE" | awk '{ print $1 }')
  IMAGE_MEASUREMENT=$(measure_file "$IMAGE")
fi

MACHINE="pc-i440fx"
UEFI_OVMF_REQUIRED=0
if [ "$FIRMWARE" = "uefi" ]; then
  MACHINE="q35"
  UEFI_OVMF_REQUIRED=1
fi

IMAGE_Q=$(shell_quote "$IMAGE")
SERIAL_LOG_Q=$(shell_quote "$SERIAL_LOG")

if [ "$FORMAT" = "iso" ]; then
  QEMU_TEST_COMMAND="qemu-system-x86_64 -m $MEMORY_MIB -smp $CPUS -machine $MACHINE -display none -serial file:$SERIAL_LOG_Q -drive file=$IMAGE_Q,media=cdrom,readonly=on"
else
  QEMU_TEST_COMMAND="qemu-system-x86_64 -m $MEMORY_MIB -smp $CPUS -machine $MACHINE -display none -serial file:$SERIAL_LOG_Q -drive file=$IMAGE_Q,format=$FORMAT,if=virtio,readonly=on"
fi

VM_TEST_COMMAND_READY=0
if [ "$IMAGE_EXISTS" = "1" ] && [ "$FIRMWARE" = "seabios" ]; then
  VM_TEST_COMMAND_READY=1
fi

cat <<REPORT
LATTICRA OS IMAGE VM TEST COMMAND TEMPLATE

template_status=ok
latticra_os_image_vm_test_command_template_present=1
template_mode=no-effect-command-generator
template_decision=operator-review-required-no-qemu-execution
manifest_path=$MANIFEST
image_path=$IMAGE
image_format=$FORMAT
image_exists=$IMAGE_EXISTS
image_size_bytes=$IMAGE_SIZE_BYTES
image_measurement=$IMAGE_MEASUREMENT
firmware=$FIRMWARE
qemu_machine=$MACHINE
memory_mib=$MEMORY_MIB
cpus=$CPUS
serial_log_path=$SERIAL_LOG
uefi_ovmf_required=$UEFI_OVMF_REQUIRED
vm_test_command_ready=$VM_TEST_COMMAND_READY
qemu_test_command=$QEMU_TEST_COMMAND
checksum_verification_required=1
serial_console_boot_log_required=1
read_only_vm_evidence_required=1
operator_recovery_path_required=1
qemu_execution_allowed_by_guard=0
qemu_run_performed=0
qemu_boot_execution_recorded=0
firmware_mutation_performed=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
