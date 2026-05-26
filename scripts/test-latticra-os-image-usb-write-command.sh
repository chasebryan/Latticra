#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image usb write command: %s\n' "$1" >&2
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
script='scripts/latticra-os-image-usb-write-command.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'USB Write Command Boundary' "$doc"
require_contains 'usb_write_command=sudo dd if=' "$doc"
require_contains 'post_write_command=sync' "$doc"
require_contains 'usb_write_execution_allowed=0' "$doc"
require_contains 'usb_write_executed=0' "$doc"

require_contains 'LATTICRA OS IMAGE USB WRITE COMMAND TEMPLATE' "$script"
require_contains 'template_decision=operator-review-required-no-usb-write-execution' "$script"
require_contains 'usb_write_command_ready=' "$script"
require_contains 'usb_write_execution_allowed=0' "$script"
require_contains 'usb_write_executed=0' "$script"
require_contains 'block_device_write_performed=0' "$script"
require_contains 'hardware_install_ready=0' "$script"
require_contains 'full_os_install_ready=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*diskutil[[:space:]]' "$script"

sh -n "$script"

tmp_root=${TMPDIR:-/tmp}
tmp_root="${tmp_root%/}"
tmp=$(mktemp -d "$tmp_root/latticra-os-image-usb-test.XXXXXX")
trap 'rm -rf "$tmp"' EXIT INT HUP TERM
iso="$tmp/latticra-x86_64.iso"
printf 'fake iso fixture\n' > "$iso"

output=$(sh "$script" --iso "$iso" --device /dev/sdX --platform linux)
require_output_contains "$output" 'LATTICRA OS IMAGE USB WRITE COMMAND TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'platform=linux'
require_output_contains "$output" 'iso_exists=1'
require_output_contains "$output" 'device_path=/dev/sdX'
require_output_contains "$output" 'device_path_valid=1'
require_output_contains "$output" 'device_path_blocked=0'
require_output_contains "$output" 'usb_write_command_ready=1'
require_output_contains "$output" 'usb_write_command=sudo dd if='
require_output_contains "$output" 'bs=4M conv=fsync status=progress'
require_output_contains "$output" 'post_write_command=sync'
require_output_contains "$output" 'usb_write_execution_allowed=0'
require_output_contains "$output" 'usb_write_executed=0'
require_output_contains "$output" 'block_device_write_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

blocked_output=$(sh "$script" --iso "$iso" --device /dev/sda --platform linux)
require_output_contains "$blocked_output" 'device_path_blocked=1'
require_output_contains "$blocked_output" 'usb_write_command_ready=0'

printf 'latticra_os_image_usb_write_command: ok\n'
