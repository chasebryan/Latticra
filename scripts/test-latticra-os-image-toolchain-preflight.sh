#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image toolchain preflight: %s\n' "$1" >&2
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

doc='docs/LATTICRA_OS_IMAGE_TOOLCHAIN_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-toolchain-preflight.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'Status: contract record' "$doc"
require_contains 'latticra_os_image_toolchain_contract_present=1' "$doc"
require_contains 'os_image_toolchain_preflight_present=1' "$doc"
require_contains 'os_image_toolchain_ready=0' "$doc"
require_contains 'qemu-img' "$doc"
require_contains 'qemu-system-x86_64' "$doc"
require_contains 'xorriso' "$doc"
require_contains 'grub-mkrescue compatible binary' "$doc"
require_contains 'x86_64-elf-grub-mkrescue' "$doc"
require_contains 'grub_mkrescue_path=<path-or-missing>' "$doc"
require_contains 'tool_install_performed=0' "$doc"
require_contains 'package_manager_invoked=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'bootable_os_ready=0' "$doc"
require_contains 'production_os_claim=0' "$doc"

require_contains 'os_image_toolchain_contract_present = true' "$manifest"
require_contains 'os_image_toolchain_preflight_present = true' "$manifest"
require_contains 'os_image_toolchain_ready = false' "$manifest"

require_contains 'LATTICRA OS IMAGE TOOLCHAIN PREFLIGHT' "$script"
require_contains 'preflight_decision=toolchain-readiness-report-no-install' "$script"
require_contains 'qemu_img_available=' "$script"
require_contains 'qemu_system_x86_64_available=' "$script"
require_contains 'xorriso_available=' "$script"
require_contains 'x86_64-elf-grub-mkrescue' "$script"
require_contains 'grub_mkrescue_available=' "$script"
require_contains 'grub_mkrescue_path=' "$script"
require_contains 'os_image_toolchain_ready=' "$script"
require_contains 'tool_install_performed=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*brew[[:space:]]' "$script"
require_not_line '^[[:space:]]*apt-get[[:space:]]' "$script"
require_not_line '^[[:space:]]*dnf[[:space:]]' "$script"
require_not_line '^[[:space:]]*grub-mkrescue[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"

sh -n "$script"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA OS IMAGE TOOLCHAIN PREFLIGHT'
require_output_contains "$output" 'preflight_status=ok'
require_output_contains "$output" 'qemu_img_available='
require_output_contains "$output" 'qemu_system_x86_64_available='
require_output_contains "$output" 'xorriso_available='
require_output_contains "$output" 'grub_mkrescue_available='
require_output_contains "$output" 'grub_mkrescue_path='
require_output_contains "$output" 'tar_available='
require_output_contains "$output" 'gzip_available='
require_output_contains "$output" 'cpio_available='
require_output_contains "$output" 'sha256_tool_available='
require_output_contains "$output" 'os_image_toolchain_ready='
require_output_contains "$output" 'tool_install_performed=0'
require_output_contains "$output" 'package_manager_invoked=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'latticra_os_image_toolchain_preflight: ok\n'
