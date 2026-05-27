#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-artifact-manifest-template.sh [--manifest <path>]

Prints the future Latticra OS image artifact manifest shape for ISO, USB, and
VM image release review. It does not create artifacts, write manifest files,
write USB media, run QEMU, install bootloaders, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image artifact manifest template: %s\n' "$1" >&2
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
require_manifest_field 'os_image_artifact_manifest_template_present = true'
require_manifest_field 'os_image_artifact_manifest_validation_present = true'
require_manifest_field 'os_image_artifact_manifest_candidate_present = false'
require_manifest_field 'iso_artifact_present = false'
require_manifest_field 'vm_image_artifact_present = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

cat <<REPORT
LATTICRA OS IMAGE ARTIFACT MANIFEST TEMPLATE

template_status=ok
latticra_os_image_artifact_manifest_template_present=1
template_mode=no-effect-template
template_decision=blocked-template-only-no-artifact-write
manifest_path=$MANIFEST
artifact_manifest_written=0
artifact_manifest_candidate_present=0
artifact_manifest_ready_for_operator_review=0

[required_future_manifest]
header=LATTICRA OS IMAGE ARTIFACT MANIFEST
manifest_version=1
artifact_set=os-image-release
artifact_version=<required>
source_commit=<required>
source_tag=<recorded-or-none>
build_environment=<required>
iso_artifact_path=<path-or-none>
iso_artifact_sha256=<sha256-or-none>
iso_signature_path=<path-or-none>
iso_sbom_path=<path-or-none>
vm_image_path=<path-or-none>
vm_image_format=<qcow2-or-raw-or-none>
vm_image_sha256=<sha256-or-none>
vm_signature_path=<path-or-none>
vm_sbom_path=<path-or-none>
usb_write_command_template_present=1
vm_test_command_template_present=1
operator_recovery_path=<recorded-or-none>
bootable_os_ready=0
production_os_claim=0

[non_effects]
iso_created=0
vm_image_created=0
artifact_manifest_written=0
usb_write_executed=0
qemu_run_performed=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
