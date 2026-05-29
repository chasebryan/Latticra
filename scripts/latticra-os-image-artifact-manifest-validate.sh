#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-artifact-manifest-validate.sh [--manifest <path>] [--artifact-manifest <path>]

Validates the current no-effect OS image release fixture, or validates a future
line-oriented artifact manifest candidate for ISO/QCOW2 path and checksum
consistency. It does not create artifacts, write USB media, run QEMU, install
bootloaders, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image artifact manifest validate: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

require_artifact_line() {
  pattern="$1"
  if ! grep -Fxq -- "$pattern" "$ARTIFACT_MANIFEST"; then
    fail "artifact manifest missing required line: $pattern" 65
  fi
}

require_artifact_key() {
  key="$1"
  if ! grep -Eq "^$key=" "$ARTIFACT_MANIFEST"; then
    fail "artifact manifest missing required key: $key" 65
  fi
}

artifact_value() {
  key="$1"
  grep -E "^$key=" "$ARTIFACT_MANIFEST" | head -n 1 | sed "s/^$key=//"
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

resolve_artifact_path() {
  candidate="$1"
  case "$candidate" in
    none) printf 'none\n' ;;
    /*) printf '%s\n' "$candidate" ;;
    *) printf '%s/%s\n' "$ARTIFACT_MANIFEST_DIR" "$candidate" ;;
  esac
}

validate_artifact_file() {
  label="$1"
  path_value="$2"
  checksum_value="$3"

  if [ "$path_value" = "none" ]; then
    printf '%s_artifact_present=0\n' "$label"
    printf '%s_checksum_verified_by_validator=0\n' "$label"
    return
  fi

  resolved_path=$(resolve_artifact_path "$path_value")
  [ -f "$resolved_path" ] || fail "$label artifact not found: $resolved_path" 66
  [ "$checksum_value" != "none" ] || fail "$label checksum must not be none when artifact path is present" 65

  actual_checksum=$(measure_file "$resolved_path")
  if [ "$actual_checksum" != "$checksum_value" ]; then
    fail "$label checksum mismatch: expected $checksum_value got $actual_checksum" 65
  fi

  printf '%s_artifact_present=1\n' "$label"
  printf '%s_checksum_verified_by_validator=1\n' "$label"
  printf '%s_resolved_path=%s\n' "$label" "$resolved_path"
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ARTIFACT_MANIFEST=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --artifact-manifest)
      [ "$#" -ge 2 ] || fail "missing value for --artifact-manifest" 64
      ARTIFACT_MANIFEST="$2"
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

if [ -z "$ARTIFACT_MANIFEST" ]; then
  cat <<REPORT
LATTICRA OS IMAGE ARTIFACT MANIFEST VALIDATION

validation_status=ok
latticra_os_image_artifact_manifest_validation_present=1
validation_mode=no-effect-fixture-check
validation_decision=blocked-fixture-only-no-artifact-manifest-candidate
manifest_path=$MANIFEST
artifact_manifest_candidate_supplied=0
artifact_manifest_metadata_consistent=0
artifact_manifest_ready_for_operator_review=0
iso_artifact_present=0
iso_checksum_verified_by_validator=0
vm_image_artifact_present=0
vm_image_checksum_verified_by_validator=0
usb_write_execution_allowed=0
qemu_execution_allowed_by_guard=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
  exit 0
fi

[ -f "$ARTIFACT_MANIFEST" ] || fail "artifact manifest not found: $ARTIFACT_MANIFEST" 66
ARTIFACT_MANIFEST_DIR=$(cd "$(dirname -- "$ARTIFACT_MANIFEST")" && pwd -P)

require_artifact_line 'LATTICRA OS IMAGE ARTIFACT MANIFEST'
for key in \
  manifest_version \
  artifact_set \
  artifact_version \
  source_commit \
  source_tag \
  build_environment \
  iso_artifact_path \
  iso_artifact_sha256 \
  iso_signature_path \
  iso_sbom_path \
  vm_image_path \
  vm_image_format \
  vm_image_sha256 \
  vm_signature_path \
  vm_sbom_path \
  usb_write_command_template_present \
  vm_test_command_template_present \
  operator_recovery_path \
  bootable_os_ready \
  production_os_claim
do
  require_artifact_key "$key"
done

require_artifact_line 'manifest_version=1'
require_artifact_line 'artifact_set=os-image-release'
require_artifact_line 'usb_write_command_template_present=1'
require_artifact_line 'vm_test_command_template_present=1'
require_artifact_line 'bootable_os_ready=0'
require_artifact_line 'production_os_claim=0'

VM_FORMAT=$(artifact_value vm_image_format)
case "$VM_FORMAT" in
  qcow2|raw|none) ;;
  *) fail "unsupported vm_image_format: $VM_FORMAT" 65 ;;
esac

ISO_PATH=$(artifact_value iso_artifact_path)
ISO_SHA256=$(artifact_value iso_artifact_sha256)
VM_PATH=$(artifact_value vm_image_path)
VM_SHA256=$(artifact_value vm_image_sha256)
ISO_SBOM_PATH=$(artifact_value iso_sbom_path)
VM_SBOM_PATH=$(artifact_value vm_sbom_path)
OPERATOR_RECOVERY_PATH=$(artifact_value operator_recovery_path)

ISO_REPORT=$(validate_artifact_file iso "$ISO_PATH" "$ISO_SHA256")
VM_REPORT=$(validate_artifact_file vm_image "$VM_PATH" "$VM_SHA256")

READY_FOR_REVIEW=0
if printf '%s\n' "$ISO_REPORT" | grep -Fq 'iso_artifact_present=1' &&
   printf '%s\n' "$VM_REPORT" | grep -Fq 'vm_image_artifact_present=1' &&
   [ "$ISO_SBOM_PATH" != "none" ] &&
   [ "$VM_SBOM_PATH" != "none" ] &&
   [ "$OPERATOR_RECOVERY_PATH" != "none" ]; then
  READY_FOR_REVIEW=1
fi

cat <<REPORT
LATTICRA OS IMAGE ARTIFACT MANIFEST VALIDATION

validation_status=ok
latticra_os_image_artifact_manifest_validation_present=1
validation_mode=no-effect-artifact-manifest-candidate-check
validation_decision=metadata-consistency-only-no-readiness-promotion
manifest_path=$MANIFEST
artifact_manifest_path=$ARTIFACT_MANIFEST
artifact_manifest_candidate_supplied=1
artifact_manifest_metadata_consistent=1
artifact_manifest_ready_for_operator_review=$READY_FOR_REVIEW
$ISO_REPORT
$VM_REPORT
usb_write_execution_allowed=0
qemu_execution_allowed_by_guard=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT
