#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub boot preview evidence contract: %s\n' "$1" >&2
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

doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md'
compat_doc='docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md'
manifest='installer/manifests/seabios-grub-boot-preview.toml'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'
host_targets='docs/HOST_ARCHITECTURE_TARGETS.md'

for file in \
  "$doc" \
  "$compat_doc" \
  "$manifest" \
  "$readme" \
  "$installer_readme" \
  "$roadmap" \
  "$host_targets" \
  Makefile
do
  require_file "$file"
done

require_contains 'Status: boot-preview-evidence contract' "$doc"
require_contains 'seabios_grub_boot_preview_evidence_contract_present=1' "$doc"
require_contains 'boot_preview_manifest_fixture_present=1' "$doc"
require_contains 'boot_preview_manifest_validated=1' "$doc"
require_contains 'boot_artifact_manifest_present=0' "$doc"
require_contains 'qemu_boot_execution_recorded=0' "$doc"
require_contains 'serial_console_boot_log_recorded=0' "$doc"
require_contains 'operator_console_boot_path_recorded=0' "$doc"
require_contains 'bootable_os_ready=0' "$doc"
require_contains 'production_os_claim=0' "$doc"
require_contains 'installer/manifests/seabios-grub-boot-preview.toml' "$doc"
require_contains 'qemu_boot_execution_allowed_by_guard=0' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-evidence-contract.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-preflight.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-evidence-template.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-evidence-validate.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh' "$doc"
require_contains 'seabios_grub_boot_preview_evidence_capture_template_present=1' "$doc"
require_contains 'capture_template_decision=blocked-template-only-no-boot-execution' "$doc"
require_contains 'seabios_grub_boot_preview_evidence_validation_present=1' "$doc"
require_contains 'boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence' "$doc"
require_contains 'seabios_grub_boot_preview_qemu_argv_template_present=1' "$doc"
require_contains 'qemu_argv_template_decision=blocked-template-only-no-qemu-execution' "$doc"
require_contains 'seabios_grub_boot_preview_boot_artifact_manifest_template_present=1' "$doc"
require_contains 'boot_artifact_manifest_template_decision=blocked-template-only-no-artifact' "$doc"
require_contains 'seabios_grub_boot_preview_boot_artifact_manifest_validation_present=1' "$doc"
require_contains 'boot_artifact_manifest_validation_decision=blocked-fixture-only-incomplete' "$doc"

require_contains 'name = "seabios-grub-boot-preview"' "$manifest"
require_contains 'status = "fixture-only"' "$manifest"
require_contains 'boot_preview_manifest_fixture_present = true' "$manifest"
require_contains 'boot_preview_manifest_validated = true' "$manifest"
require_contains 'boot_artifact_manifest_present = false' "$manifest"
require_contains 'boot_artifact_checksum_recorded = false' "$manifest"
require_contains 'bootable_os_ready = false' "$manifest"
require_contains 'production_os_claim = false' "$manifest"
require_contains 'host_mutation_authority = false' "$manifest"
require_contains 'firmware_mutation_allowed = false' "$manifest"
require_contains 'bootloader_write_allowed = false' "$manifest"
require_contains 'partition_mutation_allowed = false' "$manifest"
require_contains 'mbr_write_allowed = false' "$manifest"
require_contains 'gpt_write_allowed = false' "$manifest"
require_contains 'efi_variable_write_allowed = false' "$manifest"
require_contains 'esp_write_allowed = false' "$manifest"
require_contains 'grub_cfg_write_allowed = false' "$manifest"
require_contains 'grub_install_allowed = false' "$manifest"
require_contains 'grub_mkconfig_allowed = false' "$manifest"
require_contains 'efibootmgr_allowed = false' "$manifest"
require_contains 'kernel_install_allowed = false' "$manifest"
require_contains 'initramfs_write_allowed = false' "$manifest"
require_contains 'driver_load_allowed = false' "$manifest"
require_contains 'service_install_allowed = false' "$manifest"
require_contains 'qemu_execution_allowed_by_guard = false' "$manifest"
require_contains 'profile = "x86_64-seabios-grub-preview"' "$manifest"
require_contains 'profile = "x86_64-grub2-bios-preview"' "$manifest"
require_contains 'profile = "x86_64-grub2-uefi-preview"' "$manifest"
require_contains 'qemu_i440fx_seabios_boot_validation_completed = false' "$manifest"
require_contains 'qemu_grub2_bios_boot_validation_completed = false' "$manifest"
require_contains 'qemu_ovmf_grub2_uefi_boot_validation_completed = false' "$manifest"
require_contains 'seabios_grub_boot_claim_allowed = false' "$manifest"
require_contains 'grub_bootloader_write_allowed = false' "$manifest"

require_contains 'docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md' "$readme"
require_contains 'installer/manifests/seabios-grub-boot-preview.toml' "$readme"
require_contains 'test-seabios-grub-boot-preview-evidence-contract.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-evidence-template.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-evidence-validate.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-qemu-argv-template.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh' "$readme"
require_contains 'SeaBIOS and GRUB boot-preview evidence contract' "$installer_readme"
require_contains 'SeaBIOS and GRUB boot-preview evidence capture template' "$installer_readme"
require_contains 'SeaBIOS and GRUB boot-preview evidence validation' "$installer_readme"
require_contains 'SeaBIOS and GRUB boot-preview QEMU argv template' "$installer_readme"
require_contains 'SeaBIOS and GRUB boot-preview boot artifact manifest template' "$installer_readme"
require_contains 'SeaBIOS and GRUB boot-preview boot artifact manifest validation' "$installer_readme"
require_contains 'seabios-grub-boot-preview.toml' "$installer_readme"
require_contains 'boot-preview evidence manifest' "$roadmap"
require_contains 'x86_64-seabios-grub-preview' "$host_targets"
require_contains 'test-seabios-grub-boot-preview-evidence-contract.sh' Makefile
require_contains 'boot-compatibility:' Makefile

printf 'seabios_grub_boot_preview_evidence_contract: ok\n'
