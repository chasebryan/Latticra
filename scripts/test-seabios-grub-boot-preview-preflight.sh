#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub boot preview preflight: %s\n' "$1" >&2
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

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "forbidden pattern in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md'
evidence_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md'
manifest='installer/manifests/seabios-grub-boot-preview.toml'
script='scripts/seabios-grub-boot-preview-preflight.sh'
test_script='scripts/test-seabios-grub-boot-preview-preflight.sh'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'

for file in \
  "$doc" \
  "$evidence_doc" \
  "$manifest" \
  "$script" \
  "$test_script" \
  "$readme" \
  "$installer_readme" \
  "$roadmap" \
  Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect boot-preview preflight' "$doc"
require_contains 'seabios_grub_boot_preview_preflight_present=1' "$doc"
require_contains 'preflight_mode=no-effect-report' "$doc"
require_contains 'preflight_decision=blocked-fixture-only-no-boot-execution' "$doc"
require_contains 'qemu_boot_execution_attempted=0' "$doc"
require_contains 'grub_install_invoked=0' "$doc"
require_contains 'disk_image_created=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'sh scripts/seabios-grub-boot-preview-preflight.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-preflight.sh' "$doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-template.sh' "$doc"

require_contains 'Boot-preview preflight' "$evidence_doc"
require_contains 'seabios_grub_boot_preview_preflight_present=1' "$evidence_doc"
require_contains 'scripts/seabios-grub-boot-preview-preflight.sh' "$evidence_doc"
require_contains 'scripts/test-seabios-grub-boot-preview-preflight.sh' "$evidence_doc"

require_contains 'SEABIOS GRUB BOOT PREVIEW PREFLIGHT' "$script"
require_contains 'preflight_decision=blocked-fixture-only-no-boot-execution' "$script"
require_contains 'manifest_fixture_valid=1' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'qemu_boot_execution_attempted=0' "$script"
require_contains 'qemu_boot_execution_recorded=0' "$script"
require_contains 'grub_install_invoked=0' "$script"
require_contains 'grub_mkrescue_invoked=0' "$script"
require_contains 'disk_image_created=0' "$script"
require_contains 'disk_image_written=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_contains 'grub-install ' "$script"
require_not_contains 'grub-mkrescue ' "$script"
require_not_contains 'qemu-system-x86_64 -' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

require_contains 'docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md' "$readme"
require_contains 'scripts/seabios-grub-boot-preview-preflight.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-preflight.sh' "$readme"
require_contains 'SeaBIOS and GRUB boot-preview preflight' "$installer_readme"
require_contains 'seabios-grub-boot-preview-preflight.sh' "$installer_readme"
require_contains 'boot-preview preflight report' "$roadmap"
require_contains 'test-seabios-grub-boot-preview-preflight.sh' Makefile
require_contains 'boot-preview-preflight:' Makefile
require_contains 'sh ./scripts/seabios-grub-boot-preview-preflight.sh' Makefile

output=$(sh "$script")
require_output_contains "$output" 'SEABIOS GRUB BOOT PREVIEW PREFLIGHT'
require_output_contains "$output" 'preflight_status=ok'
require_output_contains "$output" 'seabios_grub_boot_preview_preflight_present=1'
require_output_contains "$output" 'preflight_mode=no-effect-report'
require_output_contains "$output" 'preflight_decision=blocked-fixture-only-no-boot-execution'
require_output_contains "$output" 'manifest_fixture_valid=1'
require_output_contains "$output" 'boot_artifact_manifest_present=0'
require_output_contains "$output" 'qemu_execution_allowed_by_guard=0'
require_output_contains "$output" 'qemu_boot_execution_attempted=0'
require_output_contains "$output" 'grub_install_invoked=0'
require_output_contains "$output" 'disk_image_created=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'seabios_grub_boot_preview_preflight: ok\n'
