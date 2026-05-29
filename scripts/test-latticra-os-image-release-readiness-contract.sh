#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image release readiness contract: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
preflight='scripts/latticra-os-image-release-preflight.sh'
bundle='scripts/latticra-os-image-operator-bundle-from-artifacts.sh'
usb='scripts/latticra-os-image-usb-write-command.sh'
vm='scripts/latticra-os-image-vm-test-command.sh'

for file in "$doc" "$manifest" "$preflight" "$bundle" "$usb" "$vm"; do
  require_file "$file"
done

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 10 target, ISO USB and VM image readiness contract only' "$doc"
require_contains 'latticra_os_image_release_readiness_contract_present=1' "$doc"
require_contains 'iso_artifact_present=0' "$doc"
require_contains 'os_image_artifact_manifest_template_present=1' "$doc"
require_contains 'os_image_artifact_manifest_generator_present=1' "$doc"
require_contains 'os_image_artifact_manifest_validation_present=1' "$doc"
require_contains 'os_image_artifact_manifest_candidate_present=0' "$doc"
require_contains 'os_image_operator_bundle_generator_present=1' "$doc"
require_contains 'os_image_build_preflight_present=1' "$doc"
require_contains 'os_image_build_execution_allowed=0' "$doc"
require_contains 'os_image_input_bundle_manifest_generator_present=1' "$doc"
require_contains 'boot_seed_contract_present=1' "$doc"
require_contains 'boot_seed_vm_image_build_script_present=1' "$doc"
require_contains 'boot_seed_vm_qcow2_artifact_present=0' "$doc"
require_contains 'boot_seed_sbom_generator_present=1' "$doc"
require_contains 'boot_seed_full_os_ready=0' "$doc"
require_contains 'usb_write_command_template_present=1' "$doc"
require_contains 'usb_write_execution_allowed=0' "$doc"
require_contains 'vm_image_artifact_present=0' "$doc"
require_contains 'vm_test_command_template_present=1' "$doc"
require_contains 'qemu_execution_allowed_by_guard=0' "$doc"
require_contains 'hardware_install_ready=0' "$doc"
require_contains 'full_os_install_ready=0' "$doc"
require_contains 'bootable_os_ready=0' "$doc"
require_contains 'production_os_claim=0' "$doc"
require_contains 'installer/manifests/latticra-os-image-release.toml' "$doc"
require_contains 'artifacts/os-images/<version>/' "$doc"
require_contains 'latticra-x86_64.iso' "$doc"
require_contains 'latticra-x86_64.qcow2' "$doc"
require_contains 'scripts/latticra-os-image-release-preflight.sh' "$doc"
require_contains 'scripts/latticra-os-image-build-preflight.sh' "$doc"
require_contains 'scripts/latticra-boot-seed-build.sh' "$doc"
require_contains 'scripts/latticra-boot-seed-qemu-smoke.sh' "$doc"
require_contains 'scripts/latticra-boot-seed-vm-image-build.sh' "$doc"
require_contains 'scripts/latticra-boot-seed-sbom-generate.sh' "$doc"
require_contains 'scripts/latticra-os-image-input-bundle-from-files.sh' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-template.sh' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-from-files.sh' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-validate.sh' "$doc"
require_contains 'scripts/latticra-os-image-operator-bundle-from-artifacts.sh' "$doc"
require_contains 'scripts/latticra-os-image-usb-write-command.sh' "$doc"
require_contains 'scripts/latticra-os-image-vm-test-command.sh' "$doc"
require_contains 'operator_bundle_ready_for_local_review=1' "$doc"
require_contains 'hardware_usb_write_transcript_recorded=1' "$doc"
require_contains 'vm_boot_transcript_recorded=1' "$doc"
require_contains 'not a bootable ISO' "$doc"
require_contains 'not a production OS claim' "$doc"

require_contains 'name = "latticra-os-image-release"' "$manifest"
require_contains 'status = "fixture-only"' "$manifest"
require_contains 'os_image_release_readiness_contract_present = true' "$manifest"
require_contains 'iso_artifact_present = false' "$manifest"
require_contains 'os_image_artifact_manifest_template_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_generator_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_validation_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_candidate_present = false' "$manifest"
require_contains 'os_image_operator_bundle_generator_present = true' "$manifest"
require_contains 'os_image_build_preflight_present = true' "$manifest"
require_contains 'os_image_build_execution_allowed = false' "$manifest"
require_contains 'os_image_input_bundle_manifest_generator_present = true' "$manifest"
require_contains 'boot_seed_contract_present = true' "$manifest"
require_contains 'boot_seed_source_present = true' "$manifest"
require_contains 'boot_seed_build_script_present = true' "$manifest"
require_contains 'boot_seed_qemu_smoke_script_present = true' "$manifest"
require_contains 'boot_seed_vm_image_build_script_present = true' "$manifest"
require_contains 'boot_seed_vm_qcow2_artifact_present = false' "$manifest"
require_contains 'boot_seed_sbom_generator_present = true' "$manifest"
require_contains 'boot_seed_full_os_ready = false' "$manifest"
require_contains 'os_image_toolchain_contract_present = true' "$manifest"
require_contains 'os_image_toolchain_preflight_present = true' "$manifest"
require_contains 'os_image_toolchain_ready = false' "$manifest"
require_contains 'usb_write_command_template_present = true' "$manifest"
require_contains 'usb_write_execution_allowed = false' "$manifest"
require_contains 'vm_image_artifact_present = false' "$manifest"
require_contains 'vm_test_command_template_present = true' "$manifest"
require_contains 'qemu_execution_allowed_by_guard = false' "$manifest"
require_contains 'hardware_install_ready = false' "$manifest"
require_contains 'full_os_install_ready = false' "$manifest"
require_contains 'bootable_os_ready = false' "$manifest"
require_contains 'production_os_claim = false' "$manifest"
require_contains 'profile = "x86_64-usb-iso"' "$manifest"
require_contains 'profile = "x86_64-qemu-qcow2"' "$manifest"
require_contains 'profile = "x86_64-qemu-iso"' "$manifest"

require_contains 'LATTICRA OS IMAGE RELEASE PREFLIGHT' "$preflight"
require_contains 'preflight_decision=blocked-fixture-only-no-os-image-artifact' "$preflight"
require_contains 'os_image_artifact_manifest_template_present=1' "$preflight"
require_contains 'os_image_artifact_manifest_generator_present=1' "$preflight"
require_contains 'os_image_artifact_manifest_validation_present=1' "$preflight"
require_contains 'os_image_artifact_manifest_candidate_present=0' "$preflight"
require_contains 'os_image_operator_bundle_generator_present=1' "$preflight"
require_contains 'os_image_build_preflight_present=1' "$preflight"
require_contains 'os_image_build_execution_allowed=0' "$preflight"
require_contains 'os_image_input_bundle_manifest_generator_present=1' "$preflight"
require_contains 'boot_seed_contract_present=1' "$preflight"
require_contains 'boot_seed_vm_image_build_script_present=1' "$preflight"
require_contains 'boot_seed_vm_qcow2_artifact_present=0' "$preflight"
require_contains 'boot_seed_sbom_generator_present=1' "$preflight"
require_contains 'boot_seed_full_os_ready=0' "$preflight"
require_contains 'os_image_toolchain_preflight_present=1' "$preflight"
require_contains 'os_image_toolchain_ready=0' "$preflight"
require_contains 'usb_write_execution_allowed=0' "$preflight"
require_contains 'qemu_execution_allowed_by_guard=0' "$preflight"
require_contains 'bootable_os_ready=0' "$preflight"
require_contains 'production_os_claim=0' "$preflight"

sh -n "$preflight"
output=$(sh "$preflight")
require_output_contains "$output" 'LATTICRA OS IMAGE RELEASE PREFLIGHT'
require_output_contains "$output" 'preflight_status=ok'
require_output_contains "$output" 'iso_artifact_present=0'
require_output_contains "$output" 'os_image_artifact_manifest_template_present=1'
require_output_contains "$output" 'os_image_artifact_manifest_generator_present=1'
require_output_contains "$output" 'os_image_artifact_manifest_validation_present=1'
require_output_contains "$output" 'os_image_artifact_manifest_candidate_present=0'
require_output_contains "$output" 'os_image_operator_bundle_generator_present=1'
require_output_contains "$output" 'os_image_build_preflight_present=1'
require_output_contains "$output" 'os_image_build_execution_allowed=0'
require_output_contains "$output" 'os_image_input_bundle_manifest_generator_present=1'
require_output_contains "$output" 'boot_seed_contract_present=1'
require_output_contains "$output" 'boot_seed_vm_image_build_script_present=1'
require_output_contains "$output" 'boot_seed_vm_qcow2_artifact_present=0'
require_output_contains "$output" 'boot_seed_sbom_generator_present=1'
require_output_contains "$output" 'boot_seed_full_os_ready=0'
require_output_contains "$output" 'os_image_toolchain_preflight_present=1'
require_output_contains "$output" 'os_image_toolchain_ready=0'
require_output_contains "$output" 'usb_write_command_template_present=1'
require_output_contains "$output" 'vm_image_artifact_present=0'
require_output_contains "$output" 'vm_test_command_template_present=1'
require_output_contains "$output" 'hardware_install_ready=0'
require_output_contains "$output" 'full_os_install_ready=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'latticra_os_image_release_readiness_contract: ok\n'
