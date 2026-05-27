#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-build-preflight.sh [--manifest <path>] [--input-manifest <path>] [--kernel <path>] [--initramfs <path>] [--rootfs <path>] [--output-dir <path>]

Reports whether the future Latticra OS image build inputs and local tools are
visible. It prints command shapes for operator review, but it does not create
images, invoke GRUB, run qemu-img, write USB media, run QEMU, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image build preflight: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

tool_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

sha_tool_available() {
  if command -v sha256sum >/dev/null 2>&1 || command -v shasum >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

shell_quote() {
  awk -v value="$1" 'BEGIN {
    gsub(/\047/, "\047\\\047\047", value)
    printf "\047%s\047", value
  }'
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
INPUT_MANIFEST="build/os-image/input-bundle.txt"
KERNEL="build/os-image/kernel"
INITRAMFS="build/os-image/initramfs.img"
ROOTFS="build/os-image/rootfs.tar"
OUTPUT_DIR="artifacts/os-images/local-candidate"

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
    --input-manifest)
      [ "$#" -ge 2 ] || fail "missing value for --input-manifest" 64
      INPUT_MANIFEST="$2"
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
    --output-dir)
      [ "$#" -ge 2 ] || fail "missing value for --output-dir" 64
      OUTPUT_DIR="$2"
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
require_manifest_field 'os_image_build_recipe_contract_present = true'
require_manifest_field 'os_image_toolchain_contract_present = true'
require_manifest_field 'os_image_toolchain_preflight_present = true'
require_manifest_field 'os_image_toolchain_ready = false'
require_manifest_field 'os_image_build_preflight_present = true'
require_manifest_field 'os_image_build_recipe_template_present = true'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'os_image_input_bundle_manifest_template_present = true'
require_manifest_field 'os_image_input_bundle_manifest_validation_present = true'
require_manifest_field 'os_image_input_bundle_manifest_candidate_present = false'
require_manifest_field 'os_image_input_bundle_ready_for_build_preflight = false'
require_manifest_field 'kernel_image_input_present = false'
require_manifest_field 'initramfs_input_present = false'
require_manifest_field 'rootfs_input_present = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

KERNEL_PRESENT=0
INITRAMFS_PRESENT=0
ROOTFS_PRESENT=0
OUTPUT_DIR_PRESENT=0
INPUT_MANIFEST_PRESENT=0

[ -f "$INPUT_MANIFEST" ] && INPUT_MANIFEST_PRESENT=1
[ -f "$KERNEL" ] && KERNEL_PRESENT=1
[ -f "$INITRAMFS" ] && INITRAMFS_PRESENT=1
[ -e "$ROOTFS" ] && ROOTFS_PRESENT=1
[ -d "$OUTPUT_DIR" ] && OUTPUT_DIR_PRESENT=1

QEMU_IMG_AVAILABLE=$(tool_available qemu-img)
XORRISO_AVAILABLE=$(tool_available xorriso)
GRUB_MKRESCUE_AVAILABLE=$(tool_available grub-mkrescue)
TAR_AVAILABLE=$(tool_available tar)
GZIP_AVAILABLE=$(tool_available gzip)
SHA256_TOOL_AVAILABLE=$(sha_tool_available)

BUILD_INPUTS_READY=0
if [ "$KERNEL_PRESENT" = "1" ] && [ "$INITRAMFS_PRESENT" = "1" ] && [ "$ROOTFS_PRESENT" = "1" ]; then
  BUILD_INPUTS_READY=1
fi

BUILD_TOOLCHAIN_READY=0
if [ "$QEMU_IMG_AVAILABLE" = "1" ] &&
   [ "$XORRISO_AVAILABLE" = "1" ] &&
   [ "$GRUB_MKRESCUE_AVAILABLE" = "1" ] &&
   [ "$TAR_AVAILABLE" = "1" ] &&
   [ "$GZIP_AVAILABLE" = "1" ] &&
   [ "$SHA256_TOOL_AVAILABLE" = "1" ]; then
  BUILD_TOOLCHAIN_READY=1
fi

OS_IMAGE_BUILD_RECIPE_READY=0
if [ "$BUILD_INPUTS_READY" = "1" ] && [ "$BUILD_TOOLCHAIN_READY" = "1" ]; then
  OS_IMAGE_BUILD_RECIPE_READY=1
fi

OUTPUT_Q=$(shell_quote "$OUTPUT_DIR")
KERNEL_Q=$(shell_quote "$KERNEL")
INITRAMFS_Q=$(shell_quote "$INITRAMFS")
ROOTFS_Q=$(shell_quote "$ROOTFS")
INPUT_MANIFEST_Q=$(shell_quote "$INPUT_MANIFEST")
ISO_Q=$(shell_quote "$OUTPUT_DIR/latticra-x86_64.iso")
VM_Q=$(shell_quote "$OUTPUT_DIR/latticra-x86_64.qcow2")
MANIFEST_Q=$(shell_quote "$OUTPUT_DIR/manifest.txt")

cat <<REPORT
LATTICRA OS IMAGE BUILD PREFLIGHT

preflight_status=ok
latticra_os_image_build_preflight_present=1
preflight_mode=no-effect-build-readiness-report
preflight_decision=blocked-no-build-execution
manifest_path=$MANIFEST
os_image_toolchain_preflight_present=1
input_bundle_manifest_path=$INPUT_MANIFEST
input_bundle_manifest_present=$INPUT_MANIFEST_PRESENT
input_bundle_manifest_required=1
kernel_image_input_path=$KERNEL
kernel_image_input_present=$KERNEL_PRESENT
initramfs_input_path=$INITRAMFS
initramfs_input_present=$INITRAMFS_PRESENT
rootfs_input_path=$ROOTFS
rootfs_input_present=$ROOTFS_PRESENT
output_dir=$OUTPUT_DIR
output_dir_present=$OUTPUT_DIR_PRESENT
qemu_img_available=$QEMU_IMG_AVAILABLE
xorriso_available=$XORRISO_AVAILABLE
grub_mkrescue_available=$GRUB_MKRESCUE_AVAILABLE
tar_available=$TAR_AVAILABLE
gzip_available=$GZIP_AVAILABLE
sha256_tool_available=$SHA256_TOOL_AVAILABLE
build_inputs_ready=$BUILD_INPUTS_READY
build_toolchain_ready=$BUILD_TOOLCHAIN_READY
os_image_build_recipe_ready=$OS_IMAGE_BUILD_RECIPE_READY

[future_command_shapes]
future_input_bundle_validation_command=sh scripts/latticra-os-image-input-bundle-validate.sh --input-manifest $INPUT_MANIFEST_Q
future_stage_rootfs_command=tar -xf $ROOTFS_Q -C '<staging-rootfs>'
future_kernel_install_command=install -m 0644 $KERNEL_Q '<staging-boot>/vmlinuz-latticra'
future_initramfs_install_command=install -m 0644 $INITRAMFS_Q '<staging-boot>/initramfs-latticra.img'
future_iso_build_command=grub-mkrescue -o $ISO_Q '<staging-iso-root>'
future_vm_image_create_command=qemu-img create -f qcow2 $VM_Q 16G
future_artifact_manifest_path=$MANIFEST_Q
future_artifact_manifest_validation_command=sh scripts/latticra-os-image-artifact-manifest-validate.sh --artifact-manifest $MANIFEST_Q
future_output_dir=$OUTPUT_Q

[non_effects]
os_image_build_execution_allowed=0
grub_mkrescue_invoked=0
qemu_img_invoked=0
iso_created=0
vm_image_created=0
artifact_manifest_written=0
usb_write_executed=0
qemu_run_performed=0
host_mutation_performed=0
root_authority=0
network_performed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
