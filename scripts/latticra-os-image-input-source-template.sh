#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-input-source-template.sh [--manifest <path>]

Prints the future Latticra OS image input source manifest shape for the
kernel/initramfs/rootfs producers. It does not compile kernels, create
initramfs files, assemble root filesystems, build images, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image input source template: %s\n' "$1" >&2
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
require_manifest_field 'os_image_input_source_manifest_template_present = true'
require_manifest_field 'os_image_input_source_manifest_validation_present = true'
require_manifest_field 'os_image_input_source_manifest_candidate_present = false'
require_manifest_field 'os_image_input_source_ready_for_input_bundle = false'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

cat <<REPORT
LATTICRA OS IMAGE INPUT SOURCE TEMPLATE

template_status=ok
latticra_os_image_input_source_template_present=1
template_mode=no-effect-template
template_decision=blocked-template-only-no-source-build
manifest_path=$MANIFEST
input_source_manifest_written=0
input_source_manifest_candidate_present=0
input_source_ready_for_input_bundle=0

[required_future_manifest]
header=LATTICRA OS IMAGE INPUT SOURCE MANIFEST
manifest_version=1
source_kind=os-image-input-sources
source_commit=<required>
kernel_source_kind=<external-reviewed-kernel-or-latticra-boot-kernel>
kernel_source_path=<path>
kernel_boot_protocol=<recorded-or-none>
kernel_bootable_claim=0
initramfs_source_kind=<recorded>
initramfs_source_path=<path>
rootfs_source_kind=<recorded>
rootfs_source_path=<path>
input_bundle_output_path=<recorded>
operator_recovery_path=<recorded-or-none>
bootable_os_ready=0
production_os_claim=0

[non_effects]
kernel_compiled=0
initramfs_created=0
rootfs_created=0
input_source_manifest_written=0
os_image_build_execution_allowed=0
iso_created=0
vm_image_created=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
