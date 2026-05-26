#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-usb-write-command.sh --iso <path> --device <path> [--platform linux|macos] [--manifest <path>]

Prints a no-effect USB write command for a future Latticra ISO. It validates
the release fixture and the command shape, but it does not run dd, unmount
devices, write block devices, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image usb write command: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
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

shell_quote() {
  awk -v value="$1" 'BEGIN {
    gsub(/\047/, "\047\\\047\047", value)
    printf "\047%s\047", value
  }'
}

device_path_valid() {
  case "$1" in
    /dev/*) printf '1\n' ;;
    *) printf '0\n' ;;
  esac
}

device_path_blocked() {
  case "$1" in
    /dev/disk0|/dev/rdisk0|/dev/sda|/dev/vda|/dev/nvme0n1) printf '1\n' ;;
    *) printf '0\n' ;;
  esac
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
ISO=""
DEVICE=""
PLATFORM="auto"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --iso)
      [ "$#" -ge 2 ] || fail "missing value for --iso" 64
      ISO="$2"
      shift 2
      ;;
    --device)
      [ "$#" -ge 2 ] || fail "missing value for --device" 64
      DEVICE="$2"
      shift 2
      ;;
    --platform)
      [ "$#" -ge 2 ] || fail "missing value for --platform" 64
      PLATFORM="$2"
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

[ -n "$ISO" ] || fail "missing --iso" 64
[ -n "$DEVICE" ] || fail "missing --device" 64
[ -f "$MANIFEST" ] || fail "manifest not found: $MANIFEST" 66

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'iso_artifact_present = false'
require_manifest_field 'usb_write_command_template_present = true'
require_manifest_field 'usb_write_execution_allowed = false'
require_manifest_field 'usb_block_device_write_allowed = false'
require_manifest_field 'hardware_install_ready = false'
require_manifest_field 'full_os_install_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'
require_manifest_field 'profile = "x86_64-usb-iso"'

if [ "$PLATFORM" = "auto" ]; then
  case "$(uname -s 2>/dev/null || printf unknown)" in
    Darwin) PLATFORM="macos" ;;
    *) PLATFORM="linux" ;;
  esac
fi

case "$PLATFORM" in
  linux|macos) ;;
  *) fail "unsupported platform: $PLATFORM" 64 ;;
esac

ISO_EXISTS=0
ISO_SIZE_BYTES=missing
ISO_MEASUREMENT=missing
if [ -f "$ISO" ]; then
  ISO_EXISTS=1
  ISO_SIZE_BYTES=$(wc -c < "$ISO" | awk '{ print $1 }')
  ISO_MEASUREMENT=$(measure_file "$ISO")
fi

DEVICE_PATH_VALID=$(device_path_valid "$DEVICE")
DEVICE_PATH_BLOCKED=$(device_path_blocked "$DEVICE")
USB_WRITE_COMMAND_READY=0
if [ "$ISO_EXISTS" = "1" ] && [ "$DEVICE_PATH_VALID" = "1" ] && [ "$DEVICE_PATH_BLOCKED" = "0" ]; then
  USB_WRITE_COMMAND_READY=1
fi

ISO_Q=$(shell_quote "$ISO")
DEVICE_Q=$(shell_quote "$DEVICE")

PRE_WRITE_UNMOUNT_COMMAND=not-required-for-linux-template
case "$PLATFORM" in
  linux)
    USB_WRITE_COMMAND="sudo dd if=$ISO_Q of=$DEVICE_Q bs=4M conv=fsync status=progress"
    ;;
  macos)
    DISKUTIL_TARGET="$DEVICE"
    case "$DEVICE" in
      /dev/rdisk*) DISKUTIL_TARGET="/dev/disk${DEVICE#/dev/rdisk}" ;;
    esac
    DISKUTIL_TARGET_Q=$(shell_quote "$DISKUTIL_TARGET")
    PRE_WRITE_UNMOUNT_COMMAND="diskutil unmountDisk $DISKUTIL_TARGET_Q"
    USB_WRITE_COMMAND="sudo dd if=$ISO_Q of=$DEVICE_Q bs=4m"
    ;;
esac

cat <<REPORT
LATTICRA OS IMAGE USB WRITE COMMAND TEMPLATE

template_status=ok
latticra_os_image_usb_write_command_template_present=1
template_mode=no-effect-command-generator
template_decision=operator-review-required-no-usb-write-execution
manifest_path=$MANIFEST
platform=$PLATFORM
iso_path=$ISO
iso_exists=$ISO_EXISTS
iso_size_bytes=$ISO_SIZE_BYTES
iso_measurement=$ISO_MEASUREMENT
device_path=$DEVICE
device_path_valid=$DEVICE_PATH_VALID
device_path_blocked=$DEVICE_PATH_BLOCKED
usb_write_command_ready=$USB_WRITE_COMMAND_READY
pre_write_unmount_command=$PRE_WRITE_UNMOUNT_COMMAND
usb_write_command=$USB_WRITE_COMMAND
post_write_command=sync
checksum_verification_required=1
target_device_verified_removable_required=1
target_device_contains_no_required_data_required=1
operator_consent_required=1
operator_recovery_path_required=1
usb_write_execution_allowed=0
usb_write_executed=0
block_device_write_performed=0
partition_mutation_performed=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
