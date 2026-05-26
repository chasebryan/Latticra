#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  seabios-grub-boot-preview-qemu-argv-template.sh [--manifest <path>]

Emits a no-effect SeaBIOS/GRUB boot-preview QEMU argv template. It validates
the fixture manifest and prints future argv record requirements. It does not
run QEMU, invoke GRUB tools, create disk images, write boot state, or mutate the
host.
USAGE
}

fail() {
  printf 'seabios grub boot preview qemu argv template: %s\n' "$1" >&2
  exit "${2:-1}"
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

MANIFEST="installer/manifests/seabios-grub-boot-preview.toml"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
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

require_manifest_field 'name = "seabios-grub-boot-preview"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_preview_manifest_fixture_present = true'
require_manifest_field 'boot_preview_manifest_validated = true'
require_manifest_field 'boot_artifact_manifest_present = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'profile = "x86_64-seabios-grub-preview"'
require_manifest_field 'profile = "x86_64-grub2-bios-preview"'
require_manifest_field 'profile = "x86_64-grub2-uefi-preview"'
require_manifest_field 'seabios_grub_boot_claim_allowed = false'

MANIFEST_ABS=$(cd "$(dirname -- "$MANIFEST")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MANIFEST")")
MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST_ABS")

cat <<REPORT
SEABIOS GRUB BOOT PREVIEW QEMU ARGV TEMPLATE

template_status=ok
seabios_grub_boot_preview_qemu_argv_template_present=1
qemu_argv_template_mode=no-effect-template
qemu_argv_template_decision=blocked-template-only-no-qemu-execution
qemu_argv_template_complete=0
qemu_argv_record_ready=0
manifest_path=$MANIFEST
manifest_measurement=$MANIFEST_MEASUREMENT
boot_preview_manifest_fixture_present=1
boot_preview_manifest_validated=1
boot_artifact_manifest_present=0

[required_future_inputs]
operator_review_id=<required-before-qemu-argv-record>
boot_artifact_manifest_path=<required-before-qemu-argv-record>
disk_image_path=<required-before-qemu-argv-record>
disk_image_sha256=<required-before-qemu-argv-record>
serial_console_boot_log_path=<required-before-qemu-argv-record>
qemu_argv_record_path=<required-before-qemu-argv-record>
operator_recovery_path=<required-before-qemu-argv-record>
rollback_or_recovery_path=<required-before-qemu-argv-record>

[profile:x86_64-seabios-grub-preview]
profile_template_present=1
target_firmware=seabios
target_bootloader=grub2
qemu_binary=qemu-system-x86_64
qemu_machine=pc-i440fx
future_arg_00=qemu-system-x86_64
future_arg_01=-machine
future_arg_02=pc-i440fx
future_arg_03=-display
future_arg_04=none
future_arg_05=-serial
future_arg_06=file:<serial-console-boot-log-path>
future_arg_07=-drive
future_arg_08=file:<disk-image-path>,format=<artifact-format>,if=virtio,readonly=on
qemu_argv_recorded=0
profile_qemu_argv_ready=0

[profile:x86_64-grub2-bios-preview]
profile_template_present=1
target_firmware=seabios
target_bootloader=grub2-bios
qemu_binary=qemu-system-x86_64
qemu_machine=pc-i440fx
future_arg_00=qemu-system-x86_64
future_arg_01=-machine
future_arg_02=pc-i440fx
future_arg_03=-display
future_arg_04=none
future_arg_05=-serial
future_arg_06=file:<serial-console-boot-log-path>
future_arg_07=-drive
future_arg_08=file:<disk-image-path>,format=<artifact-format>,if=virtio,readonly=on
qemu_argv_recorded=0
profile_qemu_argv_ready=0

[profile:x86_64-grub2-uefi-preview]
profile_template_present=1
target_firmware=uefi
target_bootloader=grub2-uefi
qemu_binary=qemu-system-x86_64
qemu_machine=q35
ovmf_code_path=<required-before-qemu-argv-record>
ovmf_vars_template_path=<required-before-qemu-argv-record>
ovmf_vars_ephemeral_copy_path=<required-before-qemu-argv-record>
future_arg_00=qemu-system-x86_64
future_arg_01=-machine
future_arg_02=q35
future_arg_03=-display
future_arg_04=none
future_arg_05=-serial
future_arg_06=file:<serial-console-boot-log-path>
future_arg_07=-drive
future_arg_08=if=pflash,format=raw,readonly=on,file:<ovmf-code-path>
future_arg_09=-drive
future_arg_10=if=pflash,format=raw,file:<ovmf-vars-ephemeral-copy-path>
future_arg_11=-drive
future_arg_12=file:<disk-image-path>,format=<artifact-format>,if=virtio,readonly=on
qemu_argv_recorded=0
profile_qemu_argv_ready=0

[non_effects]
qemu_execution_allowed_by_guard=0
qemu_run_performed=0
qemu_boot_execution_attempted=0
qemu_boot_execution_recorded=0
grub_install_invoked=0
grub_mkrescue_invoked=0
disk_image_created=0
disk_image_written=0
iso_created=0
serial_console_boot_log_recorded=0
firmware_mutation_performed=0
bootloader_write_performed=0
partition_mutation_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
bootable_os_ready=0
production_os_claim=0
REPORT
