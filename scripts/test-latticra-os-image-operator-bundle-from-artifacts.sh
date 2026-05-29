#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image operator bundle: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_not_line() {
  pattern="$1"
  file="$2"
  if grep -Eq "$pattern" "$file"; then
    fail "forbidden executable-looking line in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-operator-bundle-from-artifacts.sh'
artifact_generator='scripts/latticra-os-image-artifact-manifest-from-files.sh'
artifact_validator='scripts/latticra-os-image-artifact-manifest-validate.sh'
usb_generator='scripts/latticra-os-image-usb-write-command.sh'
vm_generator='scripts/latticra-os-image-vm-test-command.sh'

for file in "$doc" "$manifest" "$script" "$artifact_generator" "$artifact_validator" "$usb_generator" "$vm_generator"; do
  require_file "$file"
done

require_contains 'os_image_operator_bundle_generator_present=1' "$doc"
require_contains 'scripts/latticra-os-image-operator-bundle-from-artifacts.sh' "$doc"
require_contains 'operator_bundle_readme_path=<bundle-path>' "$doc"
require_contains 'operator_bundle_ready_for_local_review=1' "$doc"
require_contains 'os_image_operator_bundle_generator_present = true' "$manifest"
require_contains 'LATTICRA OS IMAGE OPERATOR BUNDLE' "$script"
require_contains 'os_image_operator_bundle_generator_present = true' "$script"
require_contains 'artifact_manifest_ready_for_operator_review=1' "$script"
require_contains 'usb_write_execution_allowed=0' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'hardware_install_ready=0' "$script"
require_contains 'full_os_install_ready=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"

sh -n "$script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-operator-bundle.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

iso="$tmp/latticra-x86_64.iso"
vm="$tmp/latticra-x86_64.qcow2"
firmware="$tmp/OVMF_CODE.fd"
artifact_manifest="$tmp/manifest.txt"
bundle="$tmp/operator-bundle"

printf 'fake iso fixture\n' > "$iso"
printf 'fake vm fixture\n' > "$vm"
printf 'fake uefi firmware fixture\n' > "$firmware"
printf 'fake signature\n' > "$tmp/latticra-x86_64.iso.sig"
printf 'fake signature\n' > "$tmp/latticra-x86_64.qcow2.sig"
printf '{"sbom":"fake-iso"}\n' > "$tmp/iso-sbom.spdx.json"
printf '{"sbom":"fake-vm"}\n' > "$tmp/vm-sbom.spdx.json"
printf 'reimage from known-good release media\n' > "$tmp/recovery.txt"

sh "$artifact_generator" \
  --artifact-version test-fixture \
  --source-commit test-fixture \
  --source-tag none \
  --build-environment test-fixture \
  --iso "$iso" \
  --iso-signature "$tmp/latticra-x86_64.iso.sig" \
  --iso-sbom "$tmp/iso-sbom.spdx.json" \
  --vm-image "$vm" \
  --vm-format qcow2 \
  --vm-signature "$tmp/latticra-x86_64.qcow2.sig" \
  --vm-sbom "$tmp/vm-sbom.spdx.json" \
  --operator-recovery-path "$tmp/recovery.txt" > "$artifact_manifest"

output=$(sh "$script" \
  --artifact-manifest "$artifact_manifest" \
  --output-dir "$bundle" \
  --vm-firmware uefi \
  --uefi-firmware "$firmware" \
  --serial-log "$tmp/serial.log")

require_output_contains "$output" 'LATTICRA OS IMAGE OPERATOR BUNDLE'
require_output_contains "$output" 'bundle_status=ok'
require_output_contains "$output" 'artifact_manifest_ready_for_operator_review=1'
require_output_contains "$output" 'operator_bundle_readme_path='
require_output_contains "$output" 'operator_bundle_ready_for_local_review=1'
require_output_contains "$output" 'usb_write_execution_allowed=0'
require_output_contains "$output" 'qemu_execution_allowed_by_guard=0'
require_output_contains "$output" 'hardware_install_ready=0'
require_output_contains "$output" 'full_os_install_ready=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

require_file "$bundle/latticra-x86_64.iso"
require_file "$bundle/latticra-x86_64.iso.sha256"
require_file "$bundle/latticra-x86_64.qcow2"
require_file "$bundle/latticra-x86_64.qcow2.sha256"
require_file "$bundle/manifest.txt"
require_file "$bundle/artifact-manifest-validation.txt"
require_file "$bundle/iso-sbom.spdx.json"
require_file "$bundle/vm-sbom.spdx.json"
require_file "$bundle/operator-recovery-reference.txt"
require_file "$bundle/README.txt"
require_file "$bundle/operator-bundle-report.txt"
require_file "$bundle/usb-write-linux.txt"
require_file "$bundle/usb-write-macos.txt"
require_file "$bundle/vm-test-command.txt"

require_contains 'artifact_manifest_ready_for_operator_review=1' "$bundle/artifact-manifest-validation.txt"
require_contains 'platform=linux' "$bundle/usb-write-linux.txt"
require_contains 'usb_write_command_ready=1' "$bundle/usb-write-linux.txt"
require_contains 'usb_write_execution_allowed=0' "$bundle/usb-write-linux.txt"
require_contains 'platform=macos' "$bundle/usb-write-macos.txt"
require_contains 'usb_write_command_ready=1' "$bundle/usb-write-macos.txt"
require_contains 'firmware=uefi' "$bundle/vm-test-command.txt"
require_contains "uefi_firmware_path=$firmware" "$bundle/vm-test-command.txt"
require_contains 'uefi_firmware_exists=1' "$bundle/vm-test-command.txt"
require_contains 'vm_test_command_ready=1' "$bundle/vm-test-command.txt"
require_contains 'qemu_execution_allowed_by_guard=0' "$bundle/vm-test-command.txt"
require_contains 'This directory is a local review bundle' "$bundle/README.txt"
require_contains 'This bundle generator did not write USB media.' "$bundle/README.txt"
require_contains 'operator_bundle_readme_path=' "$bundle/operator-bundle-report.txt"
require_contains 'operator_bundle_ready_for_local_review=1' "$bundle/operator-bundle-report.txt"

printf 'latticra_os_image_operator_bundle_from_artifacts: ok\n'
