#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image input bundle from files: %s\n' "$1" >&2
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
script='scripts/latticra-os-image-input-bundle-from-files.sh'
validator='scripts/latticra-os-image-input-bundle-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"
require_file "$validator"

require_contains 'os_image_input_bundle_manifest_generator_present=1' "$doc"
require_contains 'scripts/latticra-os-image-input-bundle-from-files.sh' "$doc"
require_contains 'os_image_input_bundle_manifest_generator_present = true' "$manifest"

require_contains 'LATTICRA OS IMAGE INPUT BUNDLE MANIFEST' "$script"
require_contains 'os_image_input_bundle_manifest_generator_present = true' "$script"
require_contains 'os_image_build_execution_allowed = false' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*grub-mkrescue[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"

sh -n "$script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-input-bundle-from-files-test.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

kernel="$tmp/kernel"
initramfs="$tmp/initramfs.img"
rootfs="$tmp/rootfs.tar"
candidate="$tmp/input-bundle.txt"
printf 'fake kernel\n' > "$kernel"
printf 'fake initramfs\n' > "$initramfs"
printf 'fake rootfs\n' > "$rootfs"
printf 'reimage from known-good release media\n' > "$tmp/recovery.txt"
kernel_expected="$(cd "$(dirname "$kernel")" && pwd -P)/$(basename "$kernel")"
initramfs_expected="$(cd "$(dirname "$initramfs")" && pwd -P)/$(basename "$initramfs")"
rootfs_expected="$(cd "$(dirname "$rootfs")" && pwd -P)/$(basename "$rootfs")"

output=$(sh "$script" \
  --kernel "$kernel" \
  --initramfs "$initramfs" \
  --rootfs "$rootfs" \
  --rootfs-format tar \
  --source-commit test-fixture \
  --build-environment test-fixture \
  --operator-recovery-path "$tmp/recovery.txt")

require_output_contains "$output" 'LATTICRA OS IMAGE INPUT BUNDLE MANIFEST'
require_output_contains "$output" 'manifest_version=1'
require_output_contains "$output" 'bundle_kind=os-image-build-inputs'
require_output_contains "$output" 'source_commit=test-fixture'
require_output_contains "$output" 'build_environment=test-fixture'
require_output_contains "$output" "kernel_image_input_path=$kernel_expected"
require_output_contains "$output" 'kernel_image_input_sha256=sha256:'
require_output_contains "$output" "initramfs_input_path=$initramfs_expected"
require_output_contains "$output" 'initramfs_input_sha256=sha256:'
require_output_contains "$output" "rootfs_input_path=$rootfs_expected"
require_output_contains "$output" 'rootfs_input_format=tar'
require_output_contains "$output" 'rootfs_input_sha256=sha256:'
require_output_contains "$output" "operator_recovery_path=$tmp/recovery.txt"
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf '%s\n' "$output" > "$candidate"
candidate_output=$(sh "$validator" --input-manifest "$candidate")
require_output_contains "$candidate_output" 'input_bundle_manifest_candidate_supplied=1'
require_output_contains "$candidate_output" 'input_bundle_metadata_consistent=1'
require_output_contains "$candidate_output" 'input_bundle_ready_for_build_preflight=1'
require_output_contains "$candidate_output" 'kernel_image_input_present=1'
require_output_contains "$candidate_output" 'initramfs_input_present=1'
require_output_contains "$candidate_output" 'rootfs_input_present=1'
require_output_contains "$candidate_output" 'os_image_build_execution_allowed=0'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_input_bundle_from_files: ok\n'
