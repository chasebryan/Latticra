#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-boot-seed-sbom-generate.sh --iso <path> --vm-image <path> --kernel <path> --efi-bootloader <path> --esp-raw <path> [options]

Options:
  --manifest <path>           Readiness manifest to guard against promotion.
  --artifact-version <value>  Artifact version label.
  --source-commit <value>     Source revision recorded in the SBOM.
  --created <timestamp>       SPDX creation timestamp. Defaults to a stable local timestamp.

Prints a minimal SPDX 2.3 JSON SBOM for the Latticra boot-seed artifact set.
It does not build artifacts, sign artifacts, write USB media, run QEMU, or
claim full OS readiness.
USAGE
}

fail() {
  printf 'latticra boot seed sbom generate: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

sha256_hex() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print $1 }'
  else
    cksum "$file" | awk '{ print "cksum-" $1 "-" $2 }'
  fi
}

absolute_file_path() {
  file="$1"
  dir=$(cd "$(dirname "$file")" && pwd -P)
  base=$(basename "$file")
  printf '%s/%s\n' "$dir" "$base"
}

json_escape() {
  printf '%s' "$1" | sed 's/\\/\\\\/g; s/"/\\"/g'
}

default_source_commit() {
  if command -v git >/dev/null 2>&1; then
    git rev-parse --short HEAD 2>/dev/null || printf 'unknown\n'
  else
    printf 'unknown\n'
  fi
}

file_entry() {
  spdx_id="$1"
  file_name="$2"
  checksum="$3"
  comma="$4"
  escaped_name=$(json_escape "$file_name")
  cat <<ENTRY
    {
      "SPDXID": "$spdx_id",
      "fileName": "$escaped_name",
      "checksums": [
        {
          "algorithm": "SHA256",
          "checksumValue": "$checksum"
        }
      ],
      "licenseConcluded": "NOASSERTION",
      "licenseInfoInFiles": [
        "NOASSERTION"
      ],
      "copyrightText": "NOASSERTION"
    }$comma
ENTRY
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ARTIFACT_VERSION="boot-seed-local"
SOURCE_COMMIT=""
CREATED="1970-01-01T00:00:00Z"
ISO=""
VM_IMAGE=""
KERNEL=""
EFI_BOOTLOADER=""
ESP_RAW=""

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
    --created)
      [ "$#" -ge 2 ] || fail "missing value for --created" 64
      CREATED="$2"
      shift 2
      ;;
    --iso)
      [ "$#" -ge 2 ] || fail "missing value for --iso" 64
      ISO="$2"
      shift 2
      ;;
    --vm-image)
      [ "$#" -ge 2 ] || fail "missing value for --vm-image" 64
      VM_IMAGE="$2"
      shift 2
      ;;
    --kernel)
      [ "$#" -ge 2 ] || fail "missing value for --kernel" 64
      KERNEL="$2"
      shift 2
      ;;
    --efi-bootloader)
      [ "$#" -ge 2 ] || fail "missing value for --efi-bootloader" 64
      EFI_BOOTLOADER="$2"
      shift 2
      ;;
    --esp-raw)
      [ "$#" -ge 2 ] || fail "missing value for --esp-raw" 64
      ESP_RAW="$2"
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
[ -n "$ISO" ] || fail "missing --iso" 64
[ -n "$VM_IMAGE" ] || fail "missing --vm-image" 64
[ -n "$KERNEL" ] || fail "missing --kernel" 64
[ -n "$EFI_BOOTLOADER" ] || fail "missing --efi-bootloader" 64
[ -n "$ESP_RAW" ] || fail "missing --esp-raw" 64
[ -f "$ISO" ] || fail "ISO not found: $ISO" 66
[ -f "$VM_IMAGE" ] || fail "VM image not found: $VM_IMAGE" 66
[ -f "$KERNEL" ] || fail "kernel not found: $KERNEL" 66
[ -f "$EFI_BOOTLOADER" ] || fail "EFI bootloader not found: $EFI_BOOTLOADER" 66
[ -f "$ESP_RAW" ] || fail "ESP raw image not found: $ESP_RAW" 66

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_seed_contract_present = true'
require_manifest_field 'boot_seed_sbom_generator_present = true'
require_manifest_field 'boot_seed_full_os_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

[ -n "$SOURCE_COMMIT" ] || SOURCE_COMMIT=$(default_source_commit)
DOCUMENT_NAMESPACE_COMMIT=$(json_escape "$SOURCE_COMMIT")
DOCUMENT_NAME=$(json_escape "Latticra boot seed artifact SBOM $ARTIFACT_VERSION")

ISO_PATH=$(absolute_file_path "$ISO")
VM_PATH=$(absolute_file_path "$VM_IMAGE")
KERNEL_PATH=$(absolute_file_path "$KERNEL")
EFI_PATH=$(absolute_file_path "$EFI_BOOTLOADER")
ESP_PATH=$(absolute_file_path "$ESP_RAW")
ISO_SHA=$(sha256_hex "$ISO")
VM_SHA=$(sha256_hex "$VM_IMAGE")
KERNEL_SHA=$(sha256_hex "$KERNEL")
EFI_SHA=$(sha256_hex "$EFI_BOOTLOADER")
ESP_SHA=$(sha256_hex "$ESP_RAW")

cat <<REPORT
{
  "spdxVersion": "SPDX-2.3",
  "dataLicense": "CC0-1.0",
  "SPDXID": "SPDXRef-DOCUMENT",
  "name": "$DOCUMENT_NAME",
  "documentNamespace": "https://latticra.local/spdx/boot-seed/$DOCUMENT_NAMESPACE_COMMIT",
  "creationInfo": {
    "created": "$CREATED",
    "creators": [
      "Tool: latticra-boot-seed-sbom-generate.sh"
    ]
  },
  "packages": [
    {
      "SPDXID": "SPDXRef-Package-LatticraBootSeed",
      "name": "latticra-boot-seed",
      "versionInfo": "$(json_escape "$ARTIFACT_VERSION")",
      "downloadLocation": "NOASSERTION",
      "filesAnalyzed": true,
      "licenseConcluded": "NOASSERTION",
      "licenseDeclared": "NOASSERTION",
      "copyrightText": "NOASSERTION"
    }
  ],
  "files": [
$(file_entry "SPDXRef-File-BootSeedISO" "$ISO_PATH" "$ISO_SHA" ",")
$(file_entry "SPDXRef-File-BootSeedQCOW2" "$VM_PATH" "$VM_SHA" ",")
$(file_entry "SPDXRef-File-BootSeedKernel" "$KERNEL_PATH" "$KERNEL_SHA" ",")
$(file_entry "SPDXRef-File-BootSeedEFI" "$EFI_PATH" "$EFI_SHA" ",")
$(file_entry "SPDXRef-File-BootSeedESPRaw" "$ESP_PATH" "$ESP_SHA" "")
  ],
  "relationships": [
    {
      "spdxElementId": "SPDXRef-DOCUMENT",
      "relationshipType": "DESCRIBES",
      "relatedSpdxElement": "SPDXRef-Package-LatticraBootSeed"
    },
    {
      "spdxElementId": "SPDXRef-Package-LatticraBootSeed",
      "relationshipType": "CONTAINS",
      "relatedSpdxElement": "SPDXRef-File-BootSeedISO"
    },
    {
      "spdxElementId": "SPDXRef-Package-LatticraBootSeed",
      "relationshipType": "CONTAINS",
      "relatedSpdxElement": "SPDXRef-File-BootSeedQCOW2"
    },
    {
      "spdxElementId": "SPDXRef-Package-LatticraBootSeed",
      "relationshipType": "CONTAINS",
      "relatedSpdxElement": "SPDXRef-File-BootSeedKernel"
    },
    {
      "spdxElementId": "SPDXRef-Package-LatticraBootSeed",
      "relationshipType": "CONTAINS",
      "relatedSpdxElement": "SPDXRef-File-BootSeedEFI"
    },
    {
      "spdxElementId": "SPDXRef-Package-LatticraBootSeed",
      "relationshipType": "CONTAINS",
      "relatedSpdxElement": "SPDXRef-File-BootSeedESPRaw"
    }
  ]
}
REPORT
