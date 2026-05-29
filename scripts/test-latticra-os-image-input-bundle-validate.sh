#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image input bundle validate: %s\n' "$1" >&2
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

doc='docs/LATTICRA_OS_IMAGE_BUILD_RECIPE_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-input-bundle-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'scripts/latticra-os-image-input-bundle-validate.sh' "$doc"
require_contains 'os_image_input_bundle_ready_for_build_preflight=<0-or-1>' "$doc"
require_contains 'os_image_input_bundle_manifest_validation_present = true' "$manifest"

require_contains 'LATTICRA OS IMAGE INPUT BUNDLE VALIDATION' "$script"
require_contains 'validation_decision=blocked-fixture-only-no-input-bundle-candidate' "$script"
require_contains 'validation_decision=metadata-consistency-only-no-build-readiness-promotion' "$script"
require_contains 'input_bundle_ready_for_build_preflight=' "$script"
require_contains 'os_image_build_execution_allowed=0' "$script"
require_contains 'hardware_install_ready=0' "$script"
require_contains 'full_os_install_ready=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*grub-mkrescue[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-img[[:space:]]' "$script"

sh -n "$script"

default_output=$(sh "$script")
require_output_contains "$default_output" 'LATTICRA OS IMAGE INPUT BUNDLE VALIDATION'
require_output_contains "$default_output" 'validation_status=ok'
require_output_contains "$default_output" 'input_bundle_manifest_candidate_supplied=0'
require_output_contains "$default_output" 'input_bundle_ready_for_build_preflight=0'
require_output_contains "$default_output" 'kernel_image_input_present=0'
require_output_contains "$default_output" 'initramfs_input_present=0'
require_output_contains "$default_output" 'rootfs_input_present=0'
require_output_contains "$default_output" 'bootable_os_ready=0'
require_output_contains "$default_output" 'production_os_claim=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-input-bundle-test.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

kernel="$tmp/kernel"
initramfs="$tmp/initramfs.img"
rootfs="$tmp/rootfs.tar"
printf 'fake kernel\n' > "$kernel"
printf 'fake initramfs\n' > "$initramfs"
printf 'fake rootfs\n' > "$rootfs"
printf 'reimage from known-good release media\n' > "$tmp/recovery.txt"

kernel_sha=$(measure_file "$kernel")
initramfs_sha=$(measure_file "$initramfs")
rootfs_sha=$(measure_file "$rootfs")
candidate="$tmp/input-bundle.txt"
cat > "$candidate" <<EOF
LATTICRA OS IMAGE INPUT BUNDLE MANIFEST
manifest_version=1
bundle_kind=os-image-build-inputs
source_commit=test-fixture
build_environment=test-fixture
kernel_image_input_path=kernel
kernel_image_input_sha256=$kernel_sha
initramfs_input_path=initramfs.img
initramfs_input_sha256=$initramfs_sha
rootfs_input_path=rootfs.tar
rootfs_input_format=tar
rootfs_input_sha256=$rootfs_sha
operator_recovery_path=recovery.txt
bootable_os_ready=0
production_os_claim=0
EOF

candidate_output=$(sh "$script" --input-manifest "$candidate")
require_output_contains "$candidate_output" 'input_bundle_manifest_candidate_supplied=1'
require_output_contains "$candidate_output" 'input_bundle_metadata_consistent=1'
require_output_contains "$candidate_output" 'input_bundle_ready_for_build_preflight=1'
require_output_contains "$candidate_output" 'kernel_image_input_present=1'
require_output_contains "$candidate_output" 'kernel_image_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'initramfs_input_present=1'
require_output_contains "$candidate_output" 'initramfs_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'rootfs_input_present=1'
require_output_contains "$candidate_output" 'rootfs_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'os_image_build_execution_allowed=0'
require_output_contains "$candidate_output" 'hardware_install_ready=0'
require_output_contains "$candidate_output" 'full_os_install_ready=0'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_input_bundle_validate: ok\n'
