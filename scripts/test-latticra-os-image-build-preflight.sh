#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image build preflight: %s\n' "$1" >&2
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
release_doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-build-preflight.sh'

require_file "$doc"
require_file "$release_doc"
require_file "$manifest"
require_file "$script"

require_contains 'Status: contract record' "$doc"
require_contains 'latticra_os_image_build_recipe_contract_present=1' "$doc"
require_contains 'os_image_build_preflight_present=1' "$doc"
require_contains 'os_image_build_recipe_template_present=1' "$doc"
require_contains 'os_image_build_execution_allowed=0' "$doc"
require_contains 'os_image_input_bundle_manifest_template_present=1' "$doc"
require_contains 'os_image_input_bundle_manifest_validation_present=1' "$doc"
require_contains 'os_image_input_bundle_ready_for_build_preflight=0' "$doc"
require_contains 'kernel_image_input_present=0' "$doc"
require_contains 'initramfs_input_present=0' "$doc"
require_contains 'rootfs_input_present=0' "$doc"
require_contains 'future_iso_build_command=grub-mkrescue' "$doc"
require_contains 'future_vm_image_create_command=qemu-img create' "$doc"
require_contains 'future_input_bundle_validation_command=sh scripts/latticra-os-image-input-bundle-validate.sh' "$doc"
require_contains 'grub_mkrescue_invoked=0' "$doc"
require_contains 'qemu_img_invoked=0' "$doc"
require_contains 'bootable_os_ready=0' "$doc"
require_contains 'production_os_claim=0' "$doc"

require_contains 'os_image_build_recipe_contract_present = true' "$manifest"
require_contains 'os_image_build_preflight_present = true' "$manifest"
require_contains 'os_image_build_recipe_template_present = true' "$manifest"
require_contains 'os_image_build_execution_allowed = false' "$manifest"
require_contains 'os_image_input_bundle_manifest_template_present = true' "$manifest"
require_contains 'os_image_input_bundle_manifest_validation_present = true' "$manifest"
require_contains 'os_image_input_bundle_ready_for_build_preflight = false' "$manifest"
require_contains 'kernel_image_input_present = false' "$manifest"
require_contains 'initramfs_input_present = false' "$manifest"
require_contains 'rootfs_input_present = false' "$manifest"

require_contains 'LATTICRA OS IMAGE BUILD PREFLIGHT' "$script"
require_contains 'preflight_decision=blocked-no-build-execution' "$script"
require_contains 'build_inputs_ready=' "$script"
require_contains 'input_bundle_manifest_required=1' "$script"
require_contains 'future_input_bundle_validation_command=sh scripts/latticra-os-image-input-bundle-validate.sh' "$script"
require_contains 'build_toolchain_ready=' "$script"
require_contains 'os_image_build_recipe_ready=' "$script"
require_contains 'future_iso_build_command=grub-mkrescue' "$script"
require_contains 'future_vm_image_create_command=qemu-img create' "$script"
require_contains 'os_image_build_execution_allowed=0' "$script"
require_contains 'grub_mkrescue_invoked=0' "$script"
require_contains 'qemu_img_invoked=0' "$script"
require_contains 'iso_created=0' "$script"
require_contains 'vm_image_created=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*grub-mkrescue[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"

sh -n "$script"

default_output=$(sh "$script")
require_output_contains "$default_output" 'LATTICRA OS IMAGE BUILD PREFLIGHT'
require_output_contains "$default_output" 'preflight_status=ok'
require_output_contains "$default_output" 'input_bundle_manifest_present=0'
require_output_contains "$default_output" 'input_bundle_manifest_required=1'
require_output_contains "$default_output" 'kernel_image_input_present=0'
require_output_contains "$default_output" 'initramfs_input_present=0'
require_output_contains "$default_output" 'rootfs_input_present=0'
require_output_contains "$default_output" 'build_inputs_ready=0'
require_output_contains "$default_output" 'os_image_build_execution_allowed=0'
require_output_contains "$default_output" 'iso_created=0'
require_output_contains "$default_output" 'vm_image_created=0'
require_output_contains "$default_output" 'bootable_os_ready=0'
require_output_contains "$default_output" 'production_os_claim=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-build-preflight-test.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM
printf 'fake kernel\n' > "$tmp/kernel"
printf 'fake initramfs\n' > "$tmp/initramfs.img"
printf 'fake rootfs\n' > "$tmp/rootfs.tar"
mkdir "$tmp/out"

candidate_output=$(sh "$script" --kernel "$tmp/kernel" --initramfs "$tmp/initramfs.img" --rootfs "$tmp/rootfs.tar" --output-dir "$tmp/out")
require_output_contains "$candidate_output" 'input_bundle_manifest_present=0'
require_output_contains "$candidate_output" 'kernel_image_input_present=1'
require_output_contains "$candidate_output" 'initramfs_input_present=1'
require_output_contains "$candidate_output" 'rootfs_input_present=1'
require_output_contains "$candidate_output" 'output_dir_present=1'
require_output_contains "$candidate_output" 'build_inputs_ready=1'
require_output_contains "$candidate_output" 'future_input_bundle_validation_command=sh scripts/latticra-os-image-input-bundle-validate.sh'
require_output_contains "$candidate_output" 'future_artifact_manifest_validation_command=sh scripts/latticra-os-image-artifact-manifest-validate.sh'
require_output_contains "$candidate_output" 'os_image_build_execution_allowed=0'
require_output_contains "$candidate_output" 'grub_mkrescue_invoked=0'
require_output_contains "$candidate_output" 'qemu_img_invoked=0'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_build_preflight: ok\n'
