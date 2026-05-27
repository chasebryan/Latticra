#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-input-bundle-from-files.sh --kernel <path> --initramfs <path> --rootfs <path> [options]

Options:
  --manifest <path>                 Readiness manifest to guard against promotion.
  --rootfs-format <tar|tar.gz>      Root filesystem archive format. Auto-detected when omitted.
  --source-commit <value>           Source revision recorded in the generated bundle.
  --build-environment <value>       Build environment label recorded in the bundle.
  --operator-recovery-path <path>   Recovery path/runbook reference, or none.

Prints a line-oriented Latticra OS image input bundle manifest for supplied
kernel/initramfs/rootfs files. It does not create inputs, build images, invoke
GRUB, run qemu-img, write USB media, run QEMU, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image input bundle from files: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
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

absolute_file_path() {
  file="$1"
  dir=$(cd "$(dirname "$file")" && pwd -P)
  base=$(basename "$file")
  printf '%s/%s\n' "$dir" "$base"
}

default_source_commit() {
  if command -v git >/dev/null 2>&1; then
    git rev-parse --short HEAD 2>/dev/null || printf 'unknown\n'
  else
    printf 'unknown\n'
  fi
}

default_build_environment() {
  os=$(uname -s 2>/dev/null || printf 'unknown')
  arch=$(uname -m 2>/dev/null || printf 'unknown')
  printf 'local-%s-%s\n' "$os" "$arch"
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
KERNEL=""
INITRAMFS=""
ROOTFS=""
ROOTFS_FORMAT=""
SOURCE_COMMIT=""
BUILD_ENVIRONMENT=""
OPERATOR_RECOVERY_PATH="none"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --kernel)
      [ "$#" -ge 2 ] || fail "missing value for --kernel" 64
      KERNEL="$2"
      shift 2
      ;;
    --initramfs)
      [ "$#" -ge 2 ] || fail "missing value for --initramfs" 64
      INITRAMFS="$2"
      shift 2
      ;;
    --rootfs)
      [ "$#" -ge 2 ] || fail "missing value for --rootfs" 64
      ROOTFS="$2"
      shift 2
      ;;
    --rootfs-format)
      [ "$#" -ge 2 ] || fail "missing value for --rootfs-format" 64
      ROOTFS_FORMAT="$2"
      shift 2
      ;;
    --source-commit)
      [ "$#" -ge 2 ] || fail "missing value for --source-commit" 64
      SOURCE_COMMIT="$2"
      shift 2
      ;;
    --build-environment)
      [ "$#" -ge 2 ] || fail "missing value for --build-environment" 64
      BUILD_ENVIRONMENT="$2"
      shift 2
      ;;
    --operator-recovery-path)
      [ "$#" -ge 2 ] || fail "missing value for --operator-recovery-path" 64
      OPERATOR_RECOVERY_PATH="$2"
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
[ -n "$KERNEL" ] || fail "missing --kernel" 64
[ -n "$INITRAMFS" ] || fail "missing --initramfs" 64
[ -n "$ROOTFS" ] || fail "missing --rootfs" 64
[ -f "$KERNEL" ] || fail "kernel input not found: $KERNEL" 66
[ -f "$INITRAMFS" ] || fail "initramfs input not found: $INITRAMFS" 66
[ -f "$ROOTFS" ] || fail "rootfs input not found: $ROOTFS" 66

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_input_bundle_manifest_generator_present = true'
require_manifest_field 'os_image_input_bundle_manifest_validation_present = true'
require_manifest_field 'os_image_input_bundle_manifest_candidate_present = false'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

if [ -z "$ROOTFS_FORMAT" ]; then
  case "$ROOTFS" in
    *.tar.gz|*.tgz) ROOTFS_FORMAT="tar.gz" ;;
    *) ROOTFS_FORMAT="tar" ;;
  esac
fi

case "$ROOTFS_FORMAT" in
  tar|tar.gz) ;;
  *) fail "unsupported rootfs format: $ROOTFS_FORMAT" 65 ;;
esac

[ -n "$SOURCE_COMMIT" ] || SOURCE_COMMIT=$(default_source_commit)
[ -n "$BUILD_ENVIRONMENT" ] || BUILD_ENVIRONMENT=$(default_build_environment)

KERNEL_PATH=$(absolute_file_path "$KERNEL")
INITRAMFS_PATH=$(absolute_file_path "$INITRAMFS")
ROOTFS_PATH=$(absolute_file_path "$ROOTFS")
KERNEL_SHA256=$(measure_file "$KERNEL")
INITRAMFS_SHA256=$(measure_file "$INITRAMFS")
ROOTFS_SHA256=$(measure_file "$ROOTFS")

cat <<REPORT
LATTICRA OS IMAGE INPUT BUNDLE MANIFEST
manifest_version=1
bundle_kind=os-image-build-inputs
source_commit=$SOURCE_COMMIT
build_environment=$BUILD_ENVIRONMENT
kernel_image_input_path=$KERNEL_PATH
kernel_image_input_sha256=$KERNEL_SHA256
initramfs_input_path=$INITRAMFS_PATH
initramfs_input_sha256=$INITRAMFS_SHA256
rootfs_input_path=$ROOTFS_PATH
rootfs_input_format=$ROOTFS_FORMAT
rootfs_input_sha256=$ROOTFS_SHA256
operator_recovery_path=$OPERATOR_RECOVERY_PATH
bootable_os_ready=0
production_os_claim=0
REPORT
