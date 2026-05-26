#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'seabios grub boot preview evidence validate: %s\n' "$1" >&2
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

doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_VALIDATION.md'
evidence_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md'
capture_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md'
qemu_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md'
preflight_doc='docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md'
manifest='installer/manifests/seabios-grub-boot-preview.toml'
script='scripts/seabios-grub-boot-preview-evidence-validate.sh'
test_script='scripts/test-seabios-grub-boot-preview-evidence-validate.sh'
readme='README.md'
installer_readme='installer/README.md'
roadmap='installer/INSTALLER_ROADMAP.md'

for file in \
  "$doc" \
  "$evidence_doc" \
  "$capture_doc" \
  "$qemu_doc" \
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

require_contains 'Status: no-effect boot-preview evidence validation' "$doc"
require_contains 'seabios_grub_boot_preview_evidence_validation_present=1' "$doc"
require_contains 'boot_evidence_validation_mode=no-effect-readiness-check' "$doc"
require_contains 'boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence' "$doc"
require_contains 'boot_evidence_candidate_ready=0' "$doc"
require_contains 'qemu_i440fx_seabios_boot_validation_completed=0' "$doc"
require_contains 'serial_console_boot_log_recorded=0' "$doc"
require_contains 'operator_recovery_runbook_present=0' "$doc"
require_contains 'sh scripts/seabios-grub-boot-preview-evidence-validate.sh' "$doc"
require_contains 'sh scripts/test-seabios-grub-boot-preview-evidence-validate.sh' "$doc"

require_contains 'Boot-preview evidence validation' "$evidence_doc"
require_contains 'seabios_grub_boot_preview_evidence_validation_present=1' "$evidence_doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-validate.sh' "$evidence_doc"
require_contains 'scripts/test-seabios-grub-boot-preview-evidence-validate.sh' "$evidence_doc"
require_contains 'Boot-preview evidence validation' "$capture_doc"
require_contains 'boot_evidence_validation_report_path' "$capture_doc"
require_contains 'scripts/seabios-grub-boot-preview-evidence-validate.sh' "$capture_doc"
require_contains 'boot_evidence_validation_report_path' "$qemu_doc"
require_contains 'boot-preview evidence validation' "$preflight_doc"

require_contains 'SEABIOS GRUB BOOT PREVIEW EVIDENCE VALIDATION' "$script"
require_contains 'boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence' "$script"
require_contains 'boot_evidence_candidate_ready=0' "$script"
require_contains 'forbid_manifest_field' "$script"
require_contains 'qemu_i440fx_seabios_boot_validation_completed = true' "$script"
require_contains 'serial_console_boot_log_recorded = true' "$script"
require_contains 'operator_recovery_runbook_present = true' "$script"
require_contains 'qemu_run_performed=0' "$script"
require_contains 'qemu_boot_execution_attempted=0' "$script"
require_contains 'grub_install_invoked=0' "$script"
require_contains 'disk_image_created=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_contains 'grub-install ' "$script"
require_not_contains 'grub-mkconfig ' "$script"
require_not_contains 'grub-mkrescue ' "$script"
require_not_contains 'qemu-system-x86_64 -' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

require_contains 'docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_VALIDATION.md' "$readme"
require_contains 'scripts/seabios-grub-boot-preview-evidence-validate.sh' "$readme"
require_contains 'test-seabios-grub-boot-preview-evidence-validate.sh' "$readme"
require_contains 'SeaBIOS and GRUB boot-preview evidence validation' "$installer_readme"
require_contains 'seabios-grub-boot-preview-evidence-validate.sh' "$installer_readme"
require_contains 'boot-preview evidence validation' "$roadmap"
require_contains 'test-seabios-grub-boot-preview-evidence-validate.sh' Makefile
require_contains 'boot-evidence-validate:' Makefile
require_contains 'sh ./scripts/seabios-grub-boot-preview-evidence-validate.sh' Makefile

sh -n "$script"
sh -n "$test_script"

output=$(sh "$script")
require_output_contains "$output" 'SEABIOS GRUB BOOT PREVIEW EVIDENCE VALIDATION'
require_output_contains "$output" 'validation_status=ok'
require_output_contains "$output" 'seabios_grub_boot_preview_evidence_validation_present=1'
require_output_contains "$output" 'boot_evidence_validation_mode=no-effect-readiness-check'
require_output_contains "$output" 'boot_evidence_validation_decision=blocked-fixture-only-no-boot-evidence'
require_output_contains "$output" 'boot_evidence_candidate_ready=0'
require_output_contains "$output" 'qemu_i440fx_seabios_boot_validation_completed=0'
require_output_contains "$output" 'qemu_grub2_bios_boot_validation_completed=0'
require_output_contains "$output" 'qemu_ovmf_grub2_uefi_boot_validation_completed=0'
require_output_contains "$output" 'serial_console_boot_log_recorded=0'
require_output_contains "$output" 'operator_console_boot_path_recorded=0'
require_output_contains "$output" 'read_only_vm_evidence_recorded=0'
require_output_contains "$output" 'operator_recovery_runbook_present=0'
require_output_contains "$output" '[profile:x86_64-seabios-grub-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-bios-preview]'
require_output_contains "$output" '[profile:x86_64-grub2-uefi-preview]'
require_output_contains "$output" 'qemu_run_performed=0'
require_output_contains "$output" 'qemu_boot_execution_attempted=0'
require_output_contains "$output" 'grub_install_invoked=0'
require_output_contains "$output" 'disk_image_created=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-boot-evidence-validate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

forged="$tmpdir/forged-qemu.toml"
sed 's/qemu_grub2_bios_boot_validation_completed = false/qemu_grub2_bios_boot_validation_completed = true/' "$manifest" > "$forged"
if sh "$script" --manifest "$forged" > "$tmpdir/forged.out" 2> "$tmpdir/forged.err"; then
  fail "validator accepted forged GRUB BIOS QEMU evidence claim"
fi
require_contains 'forbidden premature evidence claim: qemu_grub2_bios_boot_validation_completed = true' "$tmpdir/forged.err"

serial="$tmpdir/forged-serial.toml"
sed 's/serial_console_boot_log_recorded = false/serial_console_boot_log_recorded = true/' "$manifest" > "$serial"
if sh "$script" --manifest "$serial" > "$tmpdir/serial.out" 2> "$tmpdir/serial.err"; then
  fail "validator accepted forged serial-console evidence claim"
fi
require_contains 'forbidden premature evidence claim: serial_console_boot_log_recorded = true' "$tmpdir/serial.err"

missing="$tmpdir/missing-profile.toml"
grep -Fv 'profile = "x86_64-grub2-uefi-preview"' "$manifest" > "$missing"
if sh "$script" --manifest "$missing" > "$tmpdir/missing.out" 2> "$tmpdir/missing.err"; then
  fail "validator accepted manifest missing UEFI profile"
fi
require_contains 'manifest missing required field: profile = "x86_64-grub2-uefi-preview"' "$tmpdir/missing.err"

printf 'seabios_grub_boot_preview_evidence_validate: ok\n'
