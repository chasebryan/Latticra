#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image input source validate: %s\n' "$1" >&2
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
script='scripts/latticra-os-image-input-source-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'scripts/latticra-os-image-input-source-validate.sh' "$doc"
require_contains 'os_image_input_source_ready_for_input_bundle=<0-or-1>' "$doc"
require_contains 'os_image_input_source_manifest_validation_present = true' "$manifest"

require_contains 'LATTICRA OS IMAGE INPUT SOURCE VALIDATION' "$script"
require_contains 'validation_decision=blocked-fixture-only-no-input-source-candidate' "$script"
require_contains 'validation_decision=metadata-consistency-only-no-build-readiness-promotion' "$script"
require_contains 'input_source_ready_for_input_bundle=' "$script"
require_contains 'kernel_bootable_claim=0' "$script"
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
require_output_contains "$default_output" 'LATTICRA OS IMAGE INPUT SOURCE VALIDATION'
require_output_contains "$default_output" 'validation_status=ok'
require_output_contains "$default_output" 'input_source_manifest_candidate_supplied=0'
require_output_contains "$default_output" 'input_source_ready_for_input_bundle=0'
require_output_contains "$default_output" 'kernel_source_present=0'
require_output_contains "$default_output" 'kernel_bootable_claim=0'
require_output_contains "$default_output" 'bootable_os_ready=0'
require_output_contains "$default_output" 'production_os_claim=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-input-source-test.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM
mkdir "$tmp/kernel-src" "$tmp/initramfs-src" "$tmp/rootfs-src"
printf 'kernel source fixture\n' > "$tmp/kernel-src/README.txt"
printf 'initramfs source fixture\n' > "$tmp/initramfs-src/README.txt"
printf 'rootfs source fixture\n' > "$tmp/rootfs-src/README.txt"
printf 'reimage from known-good release media\n' > "$tmp/recovery.txt"

candidate="$tmp/input-source-map.txt"
cat > "$candidate" <<EOF
LATTICRA OS IMAGE INPUT SOURCE MANIFEST
manifest_version=1
source_kind=os-image-input-sources
source_commit=test-fixture
kernel_source_kind=external-reviewed-kernel
kernel_source_path=kernel-src
kernel_boot_protocol=multiboot2
kernel_bootable_claim=0
initramfs_source_kind=cpio-manifest
initramfs_source_path=initramfs-src
rootfs_source_kind=tar-rootfs
rootfs_source_path=rootfs-src
input_bundle_output_path=input-bundle.txt
operator_recovery_path=recovery.txt
bootable_os_ready=0
production_os_claim=0
EOF

candidate_output=$(sh "$script" --source-manifest "$candidate")
require_output_contains "$candidate_output" 'input_source_manifest_candidate_supplied=1'
require_output_contains "$candidate_output" 'input_source_metadata_consistent=1'
require_output_contains "$candidate_output" 'input_source_ready_for_input_bundle=1'
require_output_contains "$candidate_output" 'kernel_source_kind=external-reviewed-kernel'
require_output_contains "$candidate_output" 'kernel_source_present=1'
require_output_contains "$candidate_output" 'kernel_bootable_claim=0'
require_output_contains "$candidate_output" 'initramfs_source_present=1'
require_output_contains "$candidate_output" 'rootfs_source_present=1'
require_output_contains "$candidate_output" 'os_image_build_execution_allowed=0'
require_output_contains "$candidate_output" 'hardware_install_ready=0'
require_output_contains "$candidate_output" 'full_os_install_ready=0'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_input_source_validate: ok\n'
