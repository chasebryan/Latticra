#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-input-bundle-validate.sh [--manifest <path>] [--input-manifest <path>]

Validates the current no-effect OS image input bundle fixture, or validates a
future line-oriented input bundle manifest for kernel/initramfs/rootfs path and
checksum consistency. It does not create inputs, build images, invoke GRUB, run
qemu-img, write USB media, run QEMU, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image input bundle validate: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

require_input_line() {
  pattern="$1"
  if ! grep -Fxq -- "$pattern" "$INPUT_MANIFEST"; then
    fail "input bundle manifest missing required line: $pattern" 65
  fi
}

require_input_key() {
  key="$1"
  if ! grep -Eq "^$key=" "$INPUT_MANIFEST"; then
    fail "input bundle manifest missing required key: $key" 65
  fi
}

input_value() {
  key="$1"
  grep -E "^$key=" "$INPUT_MANIFEST" | head -n 1 | sed "s/^$key=//"
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

resolve_input_path() {
  candidate="$1"
  case "$candidate" in
    /*) printf '%s\n' "$candidate" ;;
    *) printf '%s/%s\n' "$INPUT_MANIFEST_DIR" "$candidate" ;;
  esac
}

validate_input_file() {
  label="$1"
  path_value="$2"
  checksum_value="$3"

  [ "$path_value" != "none" ] || fail "$label path must not be none in an input bundle candidate" 65
  [ "$checksum_value" != "none" ] || fail "$label checksum must not be none in an input bundle candidate" 65

  resolved_path=$(resolve_input_path "$path_value")
  [ -f "$resolved_path" ] || fail "$label input not found: $resolved_path" 66

  actual_checksum=$(measure_file "$resolved_path")
  if [ "$actual_checksum" != "$checksum_value" ]; then
    fail "$label checksum mismatch: expected $checksum_value got $actual_checksum" 65
  fi

  printf '%s_input_present=1\n' "$label"
  printf '%s_checksum_verified_by_validator=1\n' "$label"
  printf '%s_resolved_path=%s\n' "$label" "$resolved_path"
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
INPUT_MANIFEST=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --input-manifest)
      [ "$#" -ge 2 ] || fail "missing value for --input-manifest" 64
      INPUT_MANIFEST="$2"
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
require_manifest_field 'os_image_input_bundle_manifest_template_present = true'
require_manifest_field 'os_image_input_bundle_manifest_validation_present = true'
require_manifest_field 'os_image_input_bundle_manifest_candidate_present = false'
require_manifest_field 'os_image_input_bundle_ready_for_build_preflight = false'
require_manifest_field 'kernel_image_input_present = false'
require_manifest_field 'initramfs_input_present = false'
require_manifest_field 'rootfs_input_present = false'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

if [ -z "$INPUT_MANIFEST" ]; then
  cat <<REPORT
LATTICRA OS IMAGE INPUT BUNDLE VALIDATION

validation_status=ok
latticra_os_image_input_bundle_validation_present=1
validation_mode=no-effect-fixture-check
validation_decision=blocked-fixture-only-no-input-bundle-candidate
manifest_path=$MANIFEST
input_bundle_manifest_candidate_supplied=0
input_bundle_metadata_consistent=0
input_bundle_ready_for_build_preflight=0
kernel_image_input_present=0
kernel_image_checksum_verified_by_validator=0
initramfs_input_present=0
initramfs_checksum_verified_by_validator=0
rootfs_input_present=0
rootfs_checksum_verified_by_validator=0
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
  exit 0
fi

[ -f "$INPUT_MANIFEST" ] || fail "input bundle manifest not found: $INPUT_MANIFEST" 66
INPUT_MANIFEST_DIR=$(cd "$(dirname -- "$INPUT_MANIFEST")" && pwd -P)

require_input_line 'LATTICRA OS IMAGE INPUT BUNDLE MANIFEST'
for key in \
  manifest_version \
  bundle_kind \
  source_commit \
  build_environment \
  kernel_image_input_path \
  kernel_image_input_sha256 \
  initramfs_input_path \
  initramfs_input_sha256 \
  rootfs_input_path \
  rootfs_input_format \
  rootfs_input_sha256 \
  operator_recovery_path \
  bootable_os_ready \
  production_os_claim
do
  require_input_key "$key"
done

require_input_line 'manifest_version=1'
require_input_line 'bundle_kind=os-image-build-inputs'
require_input_line 'bootable_os_ready=0'
require_input_line 'production_os_claim=0'

ROOTFS_FORMAT=$(input_value rootfs_input_format)
case "$ROOTFS_FORMAT" in
  tar|tar.gz) ;;
  *) fail "unsupported rootfs_input_format: $ROOTFS_FORMAT" 65 ;;
esac

KERNEL_PATH=$(input_value kernel_image_input_path)
KERNEL_SHA256=$(input_value kernel_image_input_sha256)
INITRAMFS_PATH=$(input_value initramfs_input_path)
INITRAMFS_SHA256=$(input_value initramfs_input_sha256)
ROOTFS_PATH=$(input_value rootfs_input_path)
ROOTFS_SHA256=$(input_value rootfs_input_sha256)
OPERATOR_RECOVERY_PATH=$(input_value operator_recovery_path)

KERNEL_REPORT=$(validate_input_file kernel_image "$KERNEL_PATH" "$KERNEL_SHA256")
INITRAMFS_REPORT=$(validate_input_file initramfs "$INITRAMFS_PATH" "$INITRAMFS_SHA256")
ROOTFS_REPORT=$(validate_input_file rootfs "$ROOTFS_PATH" "$ROOTFS_SHA256")

READY_FOR_PREFLIGHT=0
if printf '%s\n' "$KERNEL_REPORT" | grep -Fq 'kernel_image_input_present=1' &&
   printf '%s\n' "$INITRAMFS_REPORT" | grep -Fq 'initramfs_input_present=1' &&
   printf '%s\n' "$ROOTFS_REPORT" | grep -Fq 'rootfs_input_present=1' &&
   [ "$OPERATOR_RECOVERY_PATH" != "none" ]; then
  READY_FOR_PREFLIGHT=1
fi

cat <<REPORT
LATTICRA OS IMAGE INPUT BUNDLE VALIDATION

validation_status=ok
latticra_os_image_input_bundle_validation_present=1
validation_mode=no-effect-input-bundle-candidate-check
validation_decision=metadata-consistency-only-no-build-readiness-promotion
manifest_path=$MANIFEST
input_bundle_manifest_path=$INPUT_MANIFEST
input_bundle_manifest_candidate_supplied=1
input_bundle_metadata_consistent=1
input_bundle_ready_for_build_preflight=$READY_FOR_PREFLIGHT
$KERNEL_REPORT
$INITRAMFS_REPORT
$ROOTFS_REPORT
os_image_build_execution_allowed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
