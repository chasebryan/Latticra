#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra boot seed vm image: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_BOOT_SEED_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
source_dir='boot/latticra-boot-seed'
build_script='scripts/latticra-boot-seed-build.sh'
vm_script='scripts/latticra-boot-seed-vm-image-build.sh'
smoke_script='scripts/latticra-boot-seed-qemu-smoke.sh'

require_file "$doc"
require_file "$manifest"
require_file "$source_dir/grub.cfg"
require_file "$build_script"
require_file "$vm_script"
require_file "$smoke_script"

require_contains 'boot_seed_vm_image_build_script_present=1' "$doc"
require_contains 'boot_seed_vm_qcow2_artifact_present=0' "$doc"
require_contains 'scripts/latticra-boot-seed-vm-image-build.sh' "$doc"
require_contains 'search --file --set=root /boot/latticra-boot-seed.elf' "$source_dir/grub.cfg"
require_contains 'boot_seed_vm_image_build_script_present = true' "$manifest"
require_contains 'boot_seed_vm_qcow2_artifact_present = false' "$manifest"
require_contains 'LATTICRA BOOT SEED VM IMAGE BUILD' "$vm_script"
require_contains 'boot_seed_vm_qcow2_artifact_created_by_build=1' "$vm_script"
require_contains 'boot_seed_qemu_boot_source=' "$smoke_script"

sh -n "$vm_script"
sh -n "$smoke_script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-boot-seed-vm-image.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

build_output=$(sh "$build_script" --output-dir "$tmp/build")
require_output_contains "$build_output" 'boot_seed_kernel_artifact_created_by_build=1'

vm_output=$(sh "$vm_script" --kernel "$tmp/build/latticra-boot-seed.elf" --output-dir "$tmp/build")
require_output_contains "$vm_output" 'LATTICRA BOOT SEED VM IMAGE BUILD'
require_output_contains "$vm_output" 'build_status=ok'
require_output_contains "$vm_output" 'boot_seed_vm_qcow2_artifact_created_by_build=1'
require_output_contains "$vm_output" 'boot_seed_vm_qcow2_artifact_present=0'
require_output_contains "$vm_output" 'bootable_os_ready=0'
require_output_contains "$vm_output" 'production_os_claim=0'

smoke_output=$(sh "$smoke_script" --disk-image "$tmp/build/latticra-boot-seed.qcow2" --format qcow2 --output-dir "$tmp/smoke" --timeout 20)
require_output_contains "$smoke_output" 'LATTICRA BOOT SEED QEMU SMOKE'
require_output_contains "$smoke_output" 'smoke_status=ok'
require_output_contains "$smoke_output" 'boot_seed_iso_path=none'
require_output_contains "$smoke_output" 'boot_seed_vm_image_path='
require_output_contains "$smoke_output" 'boot_seed_qemu_boot_source=disk'
require_output_contains "$smoke_output" 'boot_seed_qemu_serial_sentinel_recorded=1'
require_output_contains "$smoke_output" 'boot_seed_qemu_smoke_ready=1'
require_output_contains "$smoke_output" 'bootable_os_ready=0'
require_output_contains "$smoke_output" 'production_os_claim=0'

printf 'latticra_boot_seed_vm_image: ok\n'
