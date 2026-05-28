#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-artifact-manifest-from-files.sh [options]

Options:
  --manifest <path>                 Readiness manifest to guard against promotion.
  --artifact-version <value>        Artifact version label.
  --source-commit <value>           Source revision recorded in the manifest.
  --source-tag <value>              Source tag, or none.
  --build-environment <value>       Build environment label.
  --iso <path|none>                 ISO artifact path.
  --iso-signature <path|none>       ISO signature path.
  --iso-sbom <path|none>            ISO SBOM path.
  --vm-image <path|none>            VM image path.
  --vm-format <qcow2|raw|none>      VM image format.
  --vm-signature <path|none>        VM signature path.
  --vm-sbom <path|none>             VM SBOM path.
  --operator-recovery-path <path>   Recovery path/runbook reference, or none.

Prints a line-oriented Latticra OS image artifact manifest for supplied ISO and
VM image files. It does not create artifacts, write manifests by itself, write
USB media, run QEMU, install bootloaders, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image artifact manifest from files: %s\n' "$1" >&2
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
  candidate="$1"
  if [ "$candidate" = "none" ]; then
    printf 'none\n'
    return
  fi

  dir=$(cd "$(dirname "$candidate")" && pwd -P)
  base=$(basename "$candidate")
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

path_or_none_must_exist() {
  label="$1"
  candidate="$2"
  if [ "$candidate" != "none" ] && [ ! -f "$candidate" ]; then
    fail "$label not found: $candidate" 66
  fi
}

checksum_or_none() {
  candidate="$1"
  if [ "$candidate" = "none" ]; then
    printf 'none\n'
  else
    measure_file "$candidate"
  fi
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ARTIFACT_VERSION="local-candidate"
SOURCE_COMMIT=""
SOURCE_TAG="none"
BUILD_ENVIRONMENT=""
ISO="none"
ISO_SIGNATURE="none"
ISO_SBOM="none"
VM_IMAGE="none"
VM_FORMAT="none"
VM_SIGNATURE="none"
VM_SBOM="none"
OPERATOR_RECOVERY_PATH="none"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --artifact-version)
      [ "$#" -ge 2 ] || fail "missing value for --artifact-version" 64
      ARTIFACT_VERSION="$2"
      shift 2
      ;;
    --source-commit)
      [ "$#" -ge 2 ] || fail "missing value for --source-commit" 64
      SOURCE_COMMIT="$2"
      shift 2
      ;;
    --source-tag)
      [ "$#" -ge 2 ] || fail "missing value for --source-tag" 64
      SOURCE_TAG="$2"
      shift 2
      ;;
    --build-environment)
      [ "$#" -ge 2 ] || fail "missing value for --build-environment" 64
      BUILD_ENVIRONMENT="$2"
      shift 2
      ;;
    --iso)
      [ "$#" -ge 2 ] || fail "missing value for --iso" 64
      ISO="$2"
      shift 2
      ;;
    --iso-signature)
      [ "$#" -ge 2 ] || fail "missing value for --iso-signature" 64
      ISO_SIGNATURE="$2"
      shift 2
      ;;
    --iso-sbom)
      [ "$#" -ge 2 ] || fail "missing value for --iso-sbom" 64
      ISO_SBOM="$2"
      shift 2
      ;;
    --vm-image)
      [ "$#" -ge 2 ] || fail "missing value for --vm-image" 64
      VM_IMAGE="$2"
      shift 2
      ;;
    --vm-format)
      [ "$#" -ge 2 ] || fail "missing value for --vm-format" 64
      VM_FORMAT="$2"
      shift 2
      ;;
    --vm-signature)
      [ "$#" -ge 2 ] || fail "missing value for --vm-signature" 64
      VM_SIGNATURE="$2"
      shift 2
      ;;
    --vm-sbom)
      [ "$#" -ge 2 ] || fail "missing value for --vm-sbom" 64
      VM_SBOM="$2"
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

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_artifact_manifest_template_present = true'
require_manifest_field 'os_image_artifact_manifest_generator_present = true'
require_manifest_field 'os_image_artifact_manifest_validation_present = true'
require_manifest_field 'os_image_artifact_manifest_candidate_present = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

case "$VM_FORMAT" in
  qcow2|raw|none) ;;
  *) fail "unsupported VM format: $VM_FORMAT" 64 ;;
esac

if [ "$VM_IMAGE" != "none" ] && [ "$VM_FORMAT" = "none" ]; then
  fail "vm format must not be none when vm image is present" 64
fi

path_or_none_must_exist iso "$ISO"
path_or_none_must_exist iso_signature "$ISO_SIGNATURE"
path_or_none_must_exist iso_sbom "$ISO_SBOM"
path_or_none_must_exist vm_image "$VM_IMAGE"
path_or_none_must_exist vm_signature "$VM_SIGNATURE"
path_or_none_must_exist vm_sbom "$VM_SBOM"

[ -n "$SOURCE_COMMIT" ] || SOURCE_COMMIT=$(default_source_commit)
[ -n "$BUILD_ENVIRONMENT" ] || BUILD_ENVIRONMENT=$(default_build_environment)

ISO_PATH=$(absolute_file_path "$ISO")
ISO_SIGNATURE_PATH=$(absolute_file_path "$ISO_SIGNATURE")
ISO_SBOM_PATH=$(absolute_file_path "$ISO_SBOM")
VM_PATH=$(absolute_file_path "$VM_IMAGE")
VM_SIGNATURE_PATH=$(absolute_file_path "$VM_SIGNATURE")
VM_SBOM_PATH=$(absolute_file_path "$VM_SBOM")
ISO_SHA256=$(checksum_or_none "$ISO")
VM_SHA256=$(checksum_or_none "$VM_IMAGE")

cat <<REPORT
LATTICRA OS IMAGE ARTIFACT MANIFEST
manifest_version=1
artifact_set=os-image-release
artifact_version=$ARTIFACT_VERSION
source_commit=$SOURCE_COMMIT
source_tag=$SOURCE_TAG
build_environment=$BUILD_ENVIRONMENT
iso_artifact_path=$ISO_PATH
iso_artifact_sha256=$ISO_SHA256
iso_signature_path=$ISO_SIGNATURE_PATH
iso_sbom_path=$ISO_SBOM_PATH
vm_image_path=$VM_PATH
vm_image_format=$VM_FORMAT
vm_image_sha256=$VM_SHA256
vm_signature_path=$VM_SIGNATURE_PATH
vm_sbom_path=$VM_SBOM_PATH
usb_write_command_template_present=1
vm_test_command_template_present=1
operator_recovery_path=$OPERATOR_RECOVERY_PATH
bootable_os_ready=0
production_os_claim=0
REPORT
