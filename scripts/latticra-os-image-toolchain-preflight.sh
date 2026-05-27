#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-os-image-toolchain-preflight.sh [--manifest <path>]

Reports local tool visibility for future Latticra ISO/QCOW2 build and VM test
lanes. It does not install packages, download tools, create images, run QEMU,
write USB media, or mutate the host.
USAGE
}

fail() {
  printf 'latticra os image toolchain preflight: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

tool_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

tool_path() {
  if command -v "$1" >/dev/null 2>&1; then
    command -v "$1"
  else
    printf 'missing\n'
  fi
}

sha_tool_available() {
  if command -v sha256sum >/dev/null 2>&1 || command -v shasum >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"

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

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'os_image_toolchain_contract_present = true'
require_manifest_field 'os_image_toolchain_preflight_present = true'
require_manifest_field 'os_image_toolchain_ready = false'
require_manifest_field 'os_image_build_execution_allowed = false'
require_manifest_field 'qemu_execution_allowed_by_guard = false'
require_manifest_field 'usb_write_execution_allowed = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

QEMU_IMG_AVAILABLE=$(tool_available qemu-img)
QEMU_SYSTEM_X86_64_AVAILABLE=$(tool_available qemu-system-x86_64)
XORRISO_AVAILABLE=$(tool_available xorriso)
GRUB_MKRESCUE_AVAILABLE=$(tool_available grub-mkrescue)
TAR_AVAILABLE=$(tool_available tar)
GZIP_AVAILABLE=$(tool_available gzip)
CPIO_AVAILABLE=$(tool_available cpio)
AWK_AVAILABLE=$(tool_available awk)
SED_AVAILABLE=$(tool_available sed)
FIND_AVAILABLE=$(tool_available find)
SHA256_TOOL_AVAILABLE=$(sha_tool_available)

OS_IMAGE_TOOLCHAIN_READY=0
if [ "$QEMU_IMG_AVAILABLE" = "1" ] &&
   [ "$QEMU_SYSTEM_X86_64_AVAILABLE" = "1" ] &&
   [ "$XORRISO_AVAILABLE" = "1" ] &&
   [ "$GRUB_MKRESCUE_AVAILABLE" = "1" ] &&
   [ "$TAR_AVAILABLE" = "1" ] &&
   [ "$GZIP_AVAILABLE" = "1" ] &&
   [ "$CPIO_AVAILABLE" = "1" ] &&
   [ "$AWK_AVAILABLE" = "1" ] &&
   [ "$SED_AVAILABLE" = "1" ] &&
   [ "$FIND_AVAILABLE" = "1" ] &&
   [ "$SHA256_TOOL_AVAILABLE" = "1" ]; then
  OS_IMAGE_TOOLCHAIN_READY=1
fi

cat <<REPORT
LATTICRA OS IMAGE TOOLCHAIN PREFLIGHT

preflight_status=ok
latticra_os_image_toolchain_preflight_present=1
preflight_mode=no-effect-tool-visibility-report
preflight_decision=toolchain-readiness-report-no-install
manifest_path=$MANIFEST
qemu_img_available=$QEMU_IMG_AVAILABLE
qemu_img_path=$(tool_path qemu-img)
qemu_system_x86_64_available=$QEMU_SYSTEM_X86_64_AVAILABLE
qemu_system_x86_64_path=$(tool_path qemu-system-x86_64)
xorriso_available=$XORRISO_AVAILABLE
xorriso_path=$(tool_path xorriso)
grub_mkrescue_available=$GRUB_MKRESCUE_AVAILABLE
grub_mkrescue_path=$(tool_path grub-mkrescue)
tar_available=$TAR_AVAILABLE
gzip_available=$GZIP_AVAILABLE
cpio_available=$CPIO_AVAILABLE
awk_available=$AWK_AVAILABLE
sed_available=$SED_AVAILABLE
find_available=$FIND_AVAILABLE
sha256_tool_available=$SHA256_TOOL_AVAILABLE
os_image_toolchain_ready=$OS_IMAGE_TOOLCHAIN_READY

[non_effects]
tool_install_performed=0
package_manager_invoked=0
network_performed=0
grub_mkrescue_invoked=0
qemu_img_invoked=0
qemu_run_performed=0
usb_write_executed=0
iso_created=0
vm_image_created=0
host_mutation_performed=0
root_authority=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
