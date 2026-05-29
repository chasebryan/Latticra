#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-operator-bundle-from-artifacts.sh --artifact-manifest <path> [options]

Options:
  --manifest <path>             Readiness manifest to guard against promotion.
  --output-dir <path>           Directory to stage the local operator bundle.
  --vm-firmware <seabios|uefi>  Firmware mode for the VM command template.
  --uefi-firmware <path|auto>   UEFI firmware path recorded in the VM template.
  --linux-device <path>         Linux USB device placeholder.
  --macos-device <path>         macOS USB device placeholder.
  --serial-log <path>           Serial log path recorded in the VM template.

Stages a local review bundle from an already validated OS-image artifact
manifest. It copies artifacts and writes command-template files, but it does
not write USB media, run QEMU, install bootloaders, or mutate the host outside
the requested bundle directory.
USAGE
}

fail() {
  printf 'latticra os image operator bundle: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

artifact_value() {
  key="$1"
  grep -E "^$key=" "$ARTIFACT_MANIFEST" | head -n 1 | sed "s/^$key=//"
}

resolve_artifact_path() {
  candidate="$1"
  case "$candidate" in
    none) printf 'none\n' ;;
    /*) printf '%s\n' "$candidate" ;;
    *) printf '%s/%s\n' "$ARTIFACT_MANIFEST_DIR" "$candidate" ;;
  esac
}

copy_file_to() {
  source="$1"
  destination="$2"
  if [ "$source" != "$destination" ]; then
    cp "$source" "$destination"
  fi
}

sha256_hex_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print $1 }'
  else
    fail "missing sha256sum or shasum for bundle checksum files" 69
  fi
}

write_sha256_file() {
  file="$1"
  checksum_file="$2"
  checksum=$(sha256_hex_file "$file")
  printf '%s  %s\n' "$checksum" "$(basename "$file")" > "$checksum_file"
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ARTIFACT_MANIFEST=""
OUTPUT_DIR=""
VM_FIRMWARE="uefi"
UEFI_FIRMWARE="auto"
LINUX_DEVICE="/dev/sdX"
MACOS_DEVICE="/dev/rdiskN"
SERIAL_LOG="reports/latticra-os-image-vm-serial.log"

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
    --output-dir)
      [ "$#" -ge 2 ] || fail "missing value for --output-dir" 64
      OUTPUT_DIR="$2"
      shift 2
      ;;
    --vm-firmware)
      [ "$#" -ge 2 ] || fail "missing value for --vm-firmware" 64
      VM_FIRMWARE="$2"
      shift 2
      ;;
    --uefi-firmware)
      [ "$#" -ge 2 ] || fail "missing value for --uefi-firmware" 64
      UEFI_FIRMWARE="$2"
      shift 2
      ;;
    --linux-device)
      [ "$#" -ge 2 ] || fail "missing value for --linux-device" 64
      LINUX_DEVICE="$2"
      shift 2
      ;;
    --macos-device)
      [ "$#" -ge 2 ] || fail "missing value for --macos-device" 64
      MACOS_DEVICE="$2"
      shift 2
      ;;
    --serial-log)
      [ "$#" -ge 2 ] || fail "missing value for --serial-log" 64
      SERIAL_LOG="$2"
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

[ -n "$ARTIFACT_MANIFEST" ] || fail "missing --artifact-manifest" 64
[ -f "$MANIFEST" ] || fail "manifest not found: $MANIFEST" 66
[ -f "$ARTIFACT_MANIFEST" ] || fail "artifact manifest not found: $ARTIFACT_MANIFEST" 66

case "$VM_FIRMWARE" in
  seabios|uefi) ;;
  *) fail "unsupported VM firmware: $VM_FIRMWARE" 64 ;;
esac

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_artifact_manifest_validation_present = true'
require_manifest_field 'os_image_operator_bundle_generator_present = true'
require_manifest_field 'usb_write_command_template_present = true'
require_manifest_field 'vm_test_command_template_present = true'
require_manifest_field 'usb_write_execution_allowed = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

for helper in \
  scripts/latticra-os-image-artifact-manifest-validate.sh \
  scripts/latticra-os-image-usb-write-command.sh \
  scripts/latticra-os-image-vm-test-command.sh
do
  [ -f "$helper" ] || fail "missing helper: $helper" 66
done

VALIDATION_OUTPUT=$(sh scripts/latticra-os-image-artifact-manifest-validate.sh \
  --manifest "$MANIFEST" \
  --artifact-manifest "$ARTIFACT_MANIFEST")
if ! printf '%s\n' "$VALIDATION_OUTPUT" | grep -Fq 'artifact_manifest_ready_for_operator_review=1'; then
  fail "artifact manifest is not ready for local operator review" 65
fi

ARTIFACT_MANIFEST_DIR=$(cd "$(dirname "$ARTIFACT_MANIFEST")" && pwd -P)
ARTIFACT_VERSION=$(artifact_value artifact_version)
ISO_PATH=$(resolve_artifact_path "$(artifact_value iso_artifact_path)")
VM_IMAGE_PATH=$(resolve_artifact_path "$(artifact_value vm_image_path)")
VM_FORMAT=$(artifact_value vm_image_format)
ISO_SBOM_PATH=$(resolve_artifact_path "$(artifact_value iso_sbom_path)")
VM_SBOM_PATH=$(resolve_artifact_path "$(artifact_value vm_sbom_path)")
OPERATOR_RECOVERY_PATH=$(artifact_value operator_recovery_path)

[ "$ISO_PATH" != "none" ] || fail "artifact manifest has no ISO path" 65
[ "$VM_IMAGE_PATH" != "none" ] || fail "artifact manifest has no VM image path" 65
[ "$ISO_SBOM_PATH" != "none" ] || fail "artifact manifest has no ISO SBOM path" 65
[ "$VM_SBOM_PATH" != "none" ] || fail "artifact manifest has no VM SBOM path" 65
[ -f "$ISO_PATH" ] || fail "ISO artifact not found: $ISO_PATH" 66
[ -f "$VM_IMAGE_PATH" ] || fail "VM image artifact not found: $VM_IMAGE_PATH" 66
[ -f "$ISO_SBOM_PATH" ] || fail "ISO SBOM not found: $ISO_SBOM_PATH" 66
[ -f "$VM_SBOM_PATH" ] || fail "VM SBOM not found: $VM_SBOM_PATH" 66

case "$VM_FORMAT" in
  qcow2|raw) ;;
  *) fail "operator bundle requires qcow2 or raw VM format" 65 ;;
esac

if [ -z "$OUTPUT_DIR" ]; then
  OUTPUT_DIR="artifacts/os-images/$ARTIFACT_VERSION/operator-bundle"
fi
if [ -e "$OUTPUT_DIR" ] && [ ! -d "$OUTPUT_DIR" ]; then
  fail "output path exists and is not a directory: $OUTPUT_DIR" 66
fi
mkdir -p "$OUTPUT_DIR"
OUTPUT_DIR_ABS=$(cd "$OUTPUT_DIR" && pwd -P)

ISO_DEST="$OUTPUT_DIR_ABS/$(basename "$ISO_PATH")"
VM_DEST="$OUTPUT_DIR_ABS/$(basename "$VM_IMAGE_PATH")"
MANIFEST_DEST="$OUTPUT_DIR_ABS/manifest.txt"
VALIDATION_DEST="$OUTPUT_DIR_ABS/artifact-manifest-validation.txt"
USB_LINUX_DEST="$OUTPUT_DIR_ABS/usb-write-linux.txt"
USB_MACOS_DEST="$OUTPUT_DIR_ABS/usb-write-macos.txt"
VM_COMMAND_DEST="$OUTPUT_DIR_ABS/vm-test-command.txt"
RECOVERY_DEST="$OUTPUT_DIR_ABS/operator-recovery-reference.txt"
README_DEST="$OUTPUT_DIR_ABS/README.txt"
REPORT_DEST="$OUTPUT_DIR_ABS/operator-bundle-report.txt"

copy_file_to "$ISO_PATH" "$ISO_DEST"
copy_file_to "$VM_IMAGE_PATH" "$VM_DEST"
copy_file_to "$ARTIFACT_MANIFEST" "$MANIFEST_DEST"
printf '%s\n' "$VALIDATION_OUTPUT" > "$VALIDATION_DEST"
write_sha256_file "$ISO_DEST" "$ISO_DEST.sha256"
write_sha256_file "$VM_DEST" "$VM_DEST.sha256"

if [ "$ISO_SBOM_PATH" = "$VM_SBOM_PATH" ]; then
  SBOM_DEST="$OUTPUT_DIR_ABS/sbom.spdx.json"
  copy_file_to "$ISO_SBOM_PATH" "$SBOM_DEST"
  ISO_SBOM_DEST="$SBOM_DEST"
  VM_SBOM_DEST="$SBOM_DEST"
else
  ISO_SBOM_DEST="$OUTPUT_DIR_ABS/iso-sbom.spdx.json"
  VM_SBOM_DEST="$OUTPUT_DIR_ABS/vm-sbom.spdx.json"
  copy_file_to "$ISO_SBOM_PATH" "$ISO_SBOM_DEST"
  copy_file_to "$VM_SBOM_PATH" "$VM_SBOM_DEST"
fi

if [ -f "$OPERATOR_RECOVERY_PATH" ]; then
  copy_file_to "$OPERATOR_RECOVERY_PATH" "$RECOVERY_DEST"
else
  printf 'operator_recovery_path=%s\n' "$OPERATOR_RECOVERY_PATH" > "$RECOVERY_DEST"
fi

sh scripts/latticra-os-image-usb-write-command.sh \
  --manifest "$MANIFEST" \
  --iso "$ISO_DEST" \
  --device "$LINUX_DEVICE" \
  --platform linux > "$USB_LINUX_DEST"

sh scripts/latticra-os-image-usb-write-command.sh \
  --manifest "$MANIFEST" \
  --iso "$ISO_DEST" \
  --device "$MACOS_DEVICE" \
  --platform macos > "$USB_MACOS_DEST"

sh scripts/latticra-os-image-vm-test-command.sh \
  --manifest "$MANIFEST" \
  --image "$VM_DEST" \
  --format "$VM_FORMAT" \
  --firmware "$VM_FIRMWARE" \
  --uefi-firmware "$UEFI_FIRMWARE" \
  --serial-log "$SERIAL_LOG" > "$VM_COMMAND_DEST"

cat > "$README_DEST" <<README
Latticra OS image operator bundle

This directory is a local review bundle for an already-built Latticra OS image
candidate. It stages the ISO, VM image, checksums, SBOM, artifact manifest, and
review-only command templates in one place.

Files:
- $(basename "$ISO_DEST")
- $(basename "$ISO_DEST").sha256
- $(basename "$VM_DEST")
- $(basename "$VM_DEST").sha256
- $(basename "$ISO_SBOM_DEST")
- manifest.txt
- artifact-manifest-validation.txt
- operator-recovery-reference.txt
- usb-write-linux.txt
- usb-write-macos.txt
- vm-test-command.txt
- operator-bundle-report.txt

Review boundaries:
- The USB files contain command templates only.
- The VM file contains a command template only.
- This bundle generator did not write USB media.
- This bundle generator did not run QEMU.
- This bundle generator did not promote hardware, full OS, bootable OS, or
  production OS readiness.
README

cat > "$REPORT_DEST" <<REPORT
LATTICRA OS IMAGE OPERATOR BUNDLE

bundle_status=ok
latticra_os_image_operator_bundle_generator_present=1
bundle_mode=local-artifact-handoff-no-install
artifact_manifest_path=$ARTIFACT_MANIFEST
artifact_manifest_ready_for_operator_review=1
bundle_dir=$OUTPUT_DIR_ABS
artifact_version=$ARTIFACT_VERSION
iso_artifact_path=$ISO_DEST
iso_sha256_path=$ISO_DEST.sha256
iso_sbom_path=$ISO_SBOM_DEST
vm_image_path=$VM_DEST
vm_image_format=$VM_FORMAT
vm_sha256_path=$VM_DEST.sha256
vm_sbom_path=$VM_SBOM_DEST
artifact_manifest_copy_path=$MANIFEST_DEST
artifact_manifest_validation_path=$VALIDATION_DEST
usb_write_linux_template_path=$USB_LINUX_DEST
usb_write_macos_template_path=$USB_MACOS_DEST
vm_test_command_template_path=$VM_COMMAND_DEST
operator_recovery_reference_path=$RECOVERY_DEST
operator_bundle_readme_path=$README_DEST
operator_bundle_ready_for_local_review=1
usb_write_execution_allowed=0
usb_write_executed=0
qemu_execution_allowed_by_guard=0
qemu_run_performed=0
qemu_boot_execution_recorded=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
host_mutation_performed=0
REPORT

cat "$REPORT_DEST"
