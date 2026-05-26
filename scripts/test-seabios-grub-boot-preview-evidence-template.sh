#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub boot preview evidence template: %s\n' "$1" >&2
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

doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md'
evidence_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md'
preflight_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md'
manifest='installer/manifests/seabios-grub-boot-preview.toml'
script='scripts/seabios-grub-boot-preview-evidence-template.sh'
test_script='scripts/test-seabios-grub-boot-preview-evidence-template.sh'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'

for file in \
  "$doc" \
  "$evidence_doc" \
  "$preflight_doc" \
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

require_contains 'Status: no-effect boot-preview evidence capture template' "$doc"
require_contains 'seabios_grub_boot_preview_evidence_capture_template_present=1' "$doc"
require_contains 'capture_template_mode=no-effect-template' "$doc"
require_contains 'capture_template_decision=blocked-template-only-no-boot-execution' "$doc"
require_contains 'boot_evidence_record_ready=0' "$doc"
require_contains 'qemu_boot_execution_attempted=0' "$doc"
require_contains 'sh scripts/seabios-grub-boot-preview-evidence-template.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-evidence-template.sh' "$doc"

require_contains 'Boot-preview evidence capture template' "$evidence_doc"
require_contains 'seabios_grub_boot_preview_evidence_capture_template_present=1' "$evidence_doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-template.sh' "$evidence_doc"
require_contains 'scripts/test-seabios-grub-boot-preview-evidence-template.sh' "$evidence_doc"
require_contains 'evidence capture template' "$preflight_doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-template.sh' "$preflight_doc"
require_contains 'QEMU argv template' "$doc"
require_contains 'scripts/seabios-grub-boot-preview-qemu-argv-template.sh' "$doc"
require_contains 'Boot artifact manifest template' "$doc"
require_contains 'scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh' "$doc"
require_contains 'Boot-preview evidence validation' "$doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-validate.sh' "$doc"
require_contains 'boot_evidence_validation_report_path' "$doc"
require_contains 'Boot artifact manifest validation' "$doc"
require_contains 'scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh' "$doc"
require_contains 'boot_artifact_manifest_validation_report_path' "$doc"

require_contains 'SEABIOS GRUB BOOT PREVIEW EVIDENCE CAPTURE TEMPLATE' "$script"
require_contains 'capture_template_decision=blocked-template-only-no-boot-execution' "$script"
require_contains 'boot_evidence_record_ready=0' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'qemu_boot_execution_attempted=0' "$script"
require_contains 'grub_install_invoked=0' "$script"
require_contains 'grub_mkrescue_invoked=0' "$script"
require_contains 'disk_image_created=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_contains 'grub-install ' "$script"
require_not_contains 'grub-mkrescue ' "$script"
require_not_contains 'qemu-system-x86_64 -' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

require_contains 'docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md' "$readme"
require_contains 'scripts/seabios-grub-boot-preview-evidence-template.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-evidence-template.sh' "$readme"
require_contains 'SeaBIOS and GRUB boot-preview evidence capture template' "$installer_readme"
require_contains 'seabios-grub-boot-preview-evidence-template.sh' "$installer_readme"
require_contains 'boot-preview evidence capture template' "$roadmap"
require_contains 'test-seabios-grub-boot-preview-evidence-template.sh' Makefile
require_contains 'boot-evidence-template:' Makefile
require_contains 'sh ./scripts/seabios-grub-boot-preview-evidence-template.sh' Makefile

sh -n "$script"
sh -n "$test_script"

output=$(sh "$script")
require_output_contains "$output" 'SEABIOS GRUB BOOT PREVIEW EVIDENCE CAPTURE TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'seabios_grub_boot_preview_evidence_capture_template_present=1'
require_output_contains "$output" 'capture_template_mode=no-effect-template'
require_output_contains "$output" 'capture_template_decision=blocked-template-only-no-boot-execution'
require_output_contains "$output" 'capture_template_complete=0'
require_output_contains "$output" 'boot_evidence_record_ready=0'
require_output_contains "$output" '[profile:x86_64-seabios-grub-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-bios-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-uefi-preview]'
require_output_contains "$output" 'qemu_execution_allowed_by_guard=0'
require_output_contains "$output" 'qemu_boot_execution_attempted=0'
require_output_contains "$output" 'grub_install_invoked=0'
require_output_contains "$output" 'disk_image_created=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'seabios_grub_boot_preview_evidence_template: ok\n'
