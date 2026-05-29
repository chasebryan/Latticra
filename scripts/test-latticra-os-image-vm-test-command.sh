#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image vm test command: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_not_line() {
  pattern="$1"
  file="$2"
  if grep -Eq "$pattern" "$file"; then
    fail "forbidden executable-looking line in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-vm-test-command.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'VM Image Test Boundary' "$doc"
require_contains 'qemu_test_command=qemu-system-x86_64' "$doc"
require_contains 'qemu_execution_allowed_by_guard=0' "$doc"
require_contains 'qemu_run_performed=0' "$doc"
require_contains 'qemu_boot_execution_recorded=0' "$doc"

require_contains 'LATTICRA OS IMAGE VM TEST COMMAND TEMPLATE' "$script"
require_contains 'template_decision=operator-review-required-no-qemu-execution' "$script"
require_contains '--uefi-firmware <path|auto>' "$script"
require_contains 'vm_test_command_ready=' "$script"
require_contains 'qemu_test_command=' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'qemu_run_performed=0' "$script"
require_contains 'qemu_boot_execution_recorded=0' "$script"
require_contains 'hardware_install_ready=0' "$script"
require_contains 'full_os_install_ready=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"

sh -n "$script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-vm-test.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM
image="$tmp/latticra-x86_64.qcow2"
firmware="$tmp/OVMF_CODE.fd"
printf 'fake qcow2 fixture\n' > "$image"
printf 'fake uefi firmware fixture\n' > "$firmware"

output=$(sh "$script" --image "$image" --format qcow2 --firmware seabios --memory-mib 2048 --cpus 2 --serial-log "$tmp/serial.log")
require_output_contains "$output" 'LATTICRA OS IMAGE VM TEST COMMAND TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'image_format=qcow2'
require_output_contains "$output" 'image_exists=1'
require_output_contains "$output" 'firmware=seabios'
require_output_contains "$output" 'qemu_machine=pc-i440fx'
require_output_contains "$output" 'vm_test_command_ready=1'
require_output_contains "$output" 'qemu_test_command=qemu-system-x86_64'
require_output_contains "$output" '-drive file='
require_output_contains "$output" 'format=qcow2'
require_output_contains "$output" 'readonly=on'
require_output_contains "$output" 'checksum_verification_required=1'
require_output_contains "$output" 'serial_console_boot_log_required=1'
require_output_contains "$output" 'qemu_execution_allowed_by_guard=0'
require_output_contains "$output" 'qemu_run_performed=0'
require_output_contains "$output" 'qemu_boot_execution_recorded=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

uefi_output=$(sh "$script" --image "$image" --format qcow2 --firmware uefi --uefi-firmware "$firmware")
require_output_contains "$uefi_output" 'firmware=uefi'
require_output_contains "$uefi_output" 'qemu_machine=q35'
require_output_contains "$uefi_output" 'uefi_ovmf_required=1'
require_output_contains "$uefi_output" "uefi_firmware_path=$firmware"
require_output_contains "$uefi_output" 'uefi_firmware_exists=1'
require_output_contains "$uefi_output" 'vm_test_command_ready=1'
require_output_contains "$uefi_output" '-drive if=pflash,format=raw,readonly=on,file='

printf 'latticra_os_image_vm_test_command: ok\n'
