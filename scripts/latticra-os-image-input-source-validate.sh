#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-input-source-validate.sh [--manifest <path>] [--source-manifest <path>]

Validates the current no-effect OS image input source fixture, or validates a
future line-oriented source manifest for the kernel/initramfs/rootfs producers.
It does not compile kernels, create inputs, build images, invoke GRUB, run
qemu-img, write USB media, run QEMU, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image input source validate: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

require_source_line() {
  pattern="$1"
  if ! grep -Fxq -- "$pattern" "$SOURCE_MANIFEST"; then
    fail "input source manifest missing required line: $pattern" 65
  fi
}

require_source_key() {
  key="$1"
  if ! grep -Eq "^$key=" "$SOURCE_MANIFEST"; then
    fail "input source manifest missing required key: $key" 65
  fi
}

source_value() {
  key="$1"
  grep -E "^$key=" "$SOURCE_MANIFEST" | head -n 1 | sed "s/^$key=//"
}

resolve_source_path() {
  candidate="$1"
  case "$candidate" in
    none) printf 'none\n' ;;
    /*) printf '%s\n' "$candidate" ;;
    *) printf '%s/%s\n' "$SOURCE_MANIFEST_DIR" "$candidate" ;;
  esac
}

path_present() {
  candidate="$1"
  resolved=$(resolve_source_path "$candidate")
  if [ "$resolved" != "none" ] && [ -e "$resolved" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
SOURCE_MANIFEST=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --source-manifest)
      [ "$#" -ge 2 ] || fail "missing value for --source-manifest" 64
      SOURCE_MANIFEST="$2"
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

[ -f "$MANIFEST" ] || fail "manifest not found: $MANIFEST" 66

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_input_source_manifest_template_present = true'
require_manifest_field 'os_image_input_source_manifest_validation_present = true'
require_manifest_field 'os_image_input_source_manifest_candidate_present = false'
require_manifest_field 'os_image_input_source_ready_for_input_bundle = false'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

if [ -z "$SOURCE_MANIFEST" ]; then
  cat <<REPORT
LATTICRA OS IMAGE INPUT SOURCE VALIDATION

validation_status=ok
latticra_os_image_input_source_validation_present=1
validation_mode=no-effect-fixture-check
validation_decision=blocked-fixture-only-no-input-source-candidate
manifest_path=$MANIFEST
input_source_manifest_candidate_supplied=0
input_source_metadata_consistent=0
input_source_ready_for_input_bundle=0
kernel_source_present=0
kernel_bootable_claim=0
initramfs_source_present=0
rootfs_source_present=0
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
  exit 0
fi

[ -f "$SOURCE_MANIFEST" ] || fail "input source manifest not found: $SOURCE_MANIFEST" 66
SOURCE_MANIFEST_DIR=$(cd "$(dirname -- "$SOURCE_MANIFEST")" && pwd -P)

require_source_line 'LATTICRA OS IMAGE INPUT SOURCE MANIFEST'
for key in \
  manifest_version \
  source_kind \
  source_commit \
  kernel_source_kind \
  kernel_source_path \
  kernel_boot_protocol \
  kernel_bootable_claim \
  initramfs_source_kind \
  initramfs_source_path \
  rootfs_source_kind \
  rootfs_source_path \
  input_bundle_output_path \
  operator_recovery_path \
  bootable_os_ready \
  production_os_claim
do
  require_source_key "$key"
done

require_source_line 'manifest_version=1'
require_source_line 'source_kind=os-image-input-sources'
require_source_line 'kernel_bootable_claim=0'
require_source_line 'bootable_os_ready=0'
require_source_line 'production_os_claim=0'

KERNEL_SOURCE_KIND=$(source_value kernel_source_kind)
case "$KERNEL_SOURCE_KIND" in
  external-reviewed-kernel|latticra-boot-kernel) ;;
  *) fail "unsupported kernel_source_kind: $KERNEL_SOURCE_KIND" 65 ;;
esac

KERNEL_SOURCE_PATH=$(source_value kernel_source_path)
INITRAMFS_SOURCE_PATH=$(source_value initramfs_source_path)
ROOTFS_SOURCE_PATH=$(source_value rootfs_source_path)
OPERATOR_RECOVERY_PATH=$(source_value operator_recovery_path)

KERNEL_SOURCE_PRESENT=$(path_present "$KERNEL_SOURCE_PATH")
INITRAMFS_SOURCE_PRESENT=$(path_present "$INITRAMFS_SOURCE_PATH")
ROOTFS_SOURCE_PRESENT=$(path_present "$ROOTFS_SOURCE_PATH")

READY_FOR_INPUT_BUNDLE=0
if [ "$KERNEL_SOURCE_PRESENT" = "1" ] &&
   [ "$INITRAMFS_SOURCE_PRESENT" = "1" ] &&
   [ "$ROOTFS_SOURCE_PRESENT" = "1" ] &&
   [ "$OPERATOR_RECOVERY_PATH" != "none" ]; then
  READY_FOR_INPUT_BUNDLE=1
fi

cat <<REPORT
LATTICRA OS IMAGE INPUT SOURCE VALIDATION

validation_status=ok
latticra_os_image_input_source_validation_present=1
validation_mode=no-effect-input-source-candidate-check
validation_decision=metadata-consistency-only-no-build-readiness-promotion
manifest_path=$MANIFEST
input_source_manifest_path=$SOURCE_MANIFEST
input_source_manifest_candidate_supplied=1
input_source_metadata_consistent=1
input_source_ready_for_input_bundle=$READY_FOR_INPUT_BUNDLE
kernel_source_kind=$KERNEL_SOURCE_KIND
kernel_source_present=$KERNEL_SOURCE_PRESENT
kernel_bootable_claim=0
initramfs_source_present=$INITRAMFS_SOURCE_PRESENT
rootfs_source_present=$ROOTFS_SOURCE_PRESENT
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
