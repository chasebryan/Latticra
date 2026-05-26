#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub compatibility contract: %s\n' "$1" >&2
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

doc='docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'
host_targets='docs/HOST_ARCHITECTURE_TARGETS.md'
ui='installer/latticra-installer/src/ui.rs'
apply='installer/scripts/latticra-installer-apply.sh'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'

for file in \
  "$doc" \
  "$readme" \
  "$installer_readme" \
  "$roadmap" \
  "$host_targets" \
  "$ui" \
  "$apply" \
  "$prod" \
  Makefile
do
  require_file "$file"
done

require_contains 'Status: compatibility-readiness contract' "$doc"
require_contains 'seabios_grub_compatibility_contract_present=1' "$doc"
require_contains 'installer_ready_for_user_local_panel=1' "$doc"
require_contains 'installer_boot_safe_by_absence=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'bootable_os_ready=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'user_local_prefix_only=1' "$doc"
require_contains 'firmware_mutation_allowed=0' "$doc"
require_contains 'bootloader_write_allowed=0' "$doc"
require_contains 'partition_mutation_allowed=0' "$doc"
require_contains 'mbr_write_allowed=0' "$doc"
require_contains 'gpt_write_allowed=0' "$doc"
require_contains 'efi_variable_write_allowed=0' "$doc"
require_contains 'esp_write_allowed=0' "$doc"
require_contains 'grub_cfg_write_allowed=0' "$doc"
require_contains 'grub_install_allowed=0' "$doc"
require_contains 'grub_mkconfig_allowed=0' "$doc"
require_contains 'efibootmgr_allowed=0' "$doc"
require_contains 'kernel_install_allowed=0' "$doc"
require_contains 'initramfs_write_allowed=0' "$doc"
require_contains 'x86_64-seabios-grub-preview' "$doc"
require_contains 'x86_64-grub2-bios-preview' "$doc"
require_contains 'x86_64-grub2-uefi-preview' "$doc"
require_contains 'qemu_i440fx_seabios_boot_validation_completed=0' "$doc"
require_contains 'qemu_grub2_bios_boot_validation_completed=0' "$doc"
require_contains 'qemu_ovmf_grub2_uefi_boot_validation_completed=0' "$doc"
require_contains 'boot_artifact_manifest_present=0' "$doc"
require_contains 'seabios_grub_boot_claim_allowed=0' "$doc"
require_contains 'grub_bootloader_write_allowed=0' "$doc"
require_contains 'production_os_claim=0' "$doc"
require_contains 'sh scripts/test-seabios-grub-compatibility-contract.sh' "$doc"

require_contains 'SeaBIOS and GRUB compatibility' "$readme"
require_contains 'docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md' "$readme"
require_contains 'bootloader_write_allowed=0' "$installer_readme"
require_contains 'SeaBIOS and GRUB compatibility contract' "$installer_readme"
require_contains 'firmware/SeaBIOS/GRUB mutation authority' "$roadmap"
require_contains 'x86_64-seabios-grub-preview' "$host_targets"
require_contains 'bootloader_write_allowed=0 partition_mutation_allowed=0 driver_load_allowed=0 service_install_allowed=0' "$ui"
require_contains 'bootloader_write_allowed = false' "$apply"
require_contains 'production_installer_ready=0' "$prod"
require_contains 'test-seabios-grub-compatibility-contract.sh' Makefile

printf 'seabios_grub_compatibility_contract: ok\n'
