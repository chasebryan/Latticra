#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub boot preview qemu argv template: %s\n' "$1" >&2
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

doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md'
evidence_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md'
capture_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md'
manifest='installer/manifests/seabios-grub-boot-preview.toml'
script='scripts/seabios-grub-boot-preview-qemu-argv-template.sh'
test_script='scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'

for file in \
  "$doc" \
  "$evidence_doc" \
  "$capture_doc" \
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

require_contains 'Status: no-effect boot-preview QEMU argv template' "$doc"
require_contains 'seabios_grub_boot_preview_qemu_argv_template_present=1' "$doc"
require_contains 'qemu_argv_template_mode=no-effect-template' "$doc"
require_contains 'qemu_argv_template_decision=blocked-template-only-no-qemu-execution' "$doc"
require_contains 'qemu_argv_record_ready=0' "$doc"
require_contains 'qemu_boot_execution_attempted=0' "$doc"
require_contains 'sh scripts/seabios-grub-boot-preview-qemu-argv-template.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh' "$doc"

require_contains 'QEMU argv template' "$evidence_doc"
require_contains 'seabios_grub_boot_preview_qemu_argv_template_present=1' "$evidence_doc"
require_contains 'scripts/seabios-grub-boot-preview-qemu-argv-template.sh' "$evidence_doc"
require_contains 'scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh' "$evidence_doc"
require_contains 'QEMU argv template' "$capture_doc"
require_contains 'scripts/seabios-grub-boot-preview-qemu-argv-template.sh' "$capture_doc"

require_contains 'SEABIOS GRUB BOOT PREVIEW QEMU ARGV TEMPLATE' "$script"
require_contains 'qemu_argv_template_decision=blocked-template-only-no-qemu-execution' "$script"
require_contains 'qemu_argv_record_ready=0' "$script"
require_contains 'future_arg_00=qemu-system-x86_64' "$script"
require_contains 'future_arg_01=-machine' "$script"
require_contains 'future_arg_06=file:<serial-console-boot-log-path>' "$script"
require_contains 'ovmf_vars_ephemeral_copy_path=<required-before-qemu-argv-record>' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'qemu_run_performed=0' "$script"
require_contains 'qemu_boot_execution_attempted=0' "$script"
require_contains 'grub_install_invoked=0' "$script"
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

require_contains 'docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md' "$readme"
require_contains 'scripts/seabios-grub-boot-preview-qemu-argv-template.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-qemu-argv-template.sh' "$readme"
require_contains 'SeaBIOS and GRUB boot-preview QEMU argv template' "$installer_readme"
require_contains 'seabios-grub-boot-preview-qemu-argv-template.sh' "$installer_readme"
require_contains 'QEMU argv template' "$roadmap"
require_contains 'test-seabios-grub-boot-preview-qemu-argv-template.sh' Makefile
require_contains 'boot-qemu-argv-template:' Makefile

sh -n "$script"
sh -n "$test_script"

output=$(sh "$script")
require_output_contains "$output" 'SEABIOS GRUB BOOT PREVIEW QEMU ARGV TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'seabios_grub_boot_preview_qemu_argv_template_present=1'
require_output_contains "$output" 'qemu_argv_template_mode=no-effect-template'
require_output_contains "$output" 'qemu_argv_template_decision=blocked-template-only-no-qemu-execution'
require_output_contains "$output" 'qemu_argv_record_ready=0'
require_output_contains "$output" '[profile:x86_64-seabios-grub-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-bios-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-uefi-preview]'
require_output_contains "$output" 'future_arg_00=qemu-system-x86_64'
require_output_contains "$output" 'qemu_execution_allowed_by_guard=0'
require_output_contains "$output" 'qemu_run_performed=0'
require_output_contains "$output" 'qemu_boot_execution_attempted=0'
require_output_contains "$output" 'grub_install_invoked=0'
require_output_contains "$output" 'disk_image_created=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'seabios_grub_boot_preview_qemu_argv_template: ok\n'
