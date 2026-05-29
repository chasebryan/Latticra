#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-input-bundle-template.sh [--manifest <path>]

Prints the future Latticra OS image input bundle manifest shape for kernel,
initramfs, and rootfs handoff review. It does not create input files, write
manifests, build images, invoke GRUB, run qemu-img, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image input bundle template: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
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

cat <<REPORT
LATTICRA OS IMAGE INPUT BUNDLE TEMPLATE

template_status=ok
latticra_os_image_input_bundle_template_present=1
template_mode=no-effect-template
template_decision=blocked-template-only-no-input-write
manifest_path=$MANIFEST
input_bundle_manifest_written=0
input_bundle_manifest_candidate_present=0
input_bundle_ready_for_build_preflight=0

[required_future_manifest]
header=LATTICRA OS IMAGE INPUT BUNDLE MANIFEST
manifest_version=1
bundle_kind=os-image-build-inputs
source_commit=<required>
build_environment=<required>
kernel_image_input_path=<path>
kernel_image_input_sha256=<sha256>
initramfs_input_path=<path>
initramfs_input_sha256=<sha256>
rootfs_input_path=<path>
rootfs_input_format=<tar-or-tar.gz>
rootfs_input_sha256=<sha256>
operator_recovery_path=<recorded-or-none>
bootable_os_ready=0
production_os_claim=0

[non_effects]
kernel_image_created=0
initramfs_created=0
rootfs_created=0
input_bundle_manifest_written=0
os_image_build_execution_allowed=0
grub_mkrescue_invoked=0
qemu_img_invoked=0
iso_created=0
vm_image_created=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
