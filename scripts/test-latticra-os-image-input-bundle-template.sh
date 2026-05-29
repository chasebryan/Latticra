#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image input bundle template: %s\n' "$1" >&2
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

doc='docs/LATTICRA_OS_IMAGE_BUILD_RECIPE_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-input-bundle-template.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'Input Bundle Manifest Boundary' "$doc"
require_contains 'LATTICRA OS IMAGE INPUT BUNDLE MANIFEST' "$doc"
require_contains 'os_image_input_bundle_manifest_template_present=1' "$doc"
require_contains 'os_image_input_bundle_manifest_generator_present=1' "$doc"
require_contains 'scripts/latticra-os-image-input-bundle-template.sh' "$doc"
require_contains 'os_image_input_bundle_manifest_template_present = true' "$manifest"
require_contains 'os_image_input_bundle_manifest_generator_present = true' "$manifest"
require_contains 'os_image_input_bundle_manifest_validation_present = true' "$manifest"
require_contains 'os_image_input_bundle_ready_for_build_preflight = false' "$manifest"

require_contains 'LATTICRA OS IMAGE INPUT BUNDLE TEMPLATE' "$script"
require_contains 'template_decision=blocked-template-only-no-input-write' "$script"
require_contains 'input_bundle_manifest_written=0' "$script"
require_contains 'kernel_image_created=0' "$script"
require_contains 'initramfs_created=0' "$script"
require_contains 'rootfs_created=0' "$script"
require_contains 'os_image_build_execution_allowed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*grub-mkrescue[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"

sh -n "$script"
output=$(sh "$script")
require_output_contains "$output" 'LATTICRA OS IMAGE INPUT BUNDLE TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'latticra_os_image_input_bundle_template_present=1'
require_output_contains "$output" 'header=LATTICRA OS IMAGE INPUT BUNDLE MANIFEST'
require_output_contains "$output" 'kernel_image_input_path=<path>'
require_output_contains "$output" 'initramfs_input_sha256=<sha256>'
require_output_contains "$output" 'rootfs_input_format=<tar-or-tar.gz>'
require_output_contains "$output" 'input_bundle_manifest_written=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'latticra_os_image_input_bundle_template: ok\n'
