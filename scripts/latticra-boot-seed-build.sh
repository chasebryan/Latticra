#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-boot-seed-build.sh [--manifest <path>] [--source-dir <path>] [--output-dir <path>]

Builds the minimal Latticra GRUB Multiboot2 boot seed ELF and ISO. It writes
only into the requested output directory. It does not write USB media, mutate
firmware, install bootloaders, create a production rootfs, or claim full OS
readiness.
USAGE
}

fail() {
  printf 'latticra boot seed build: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_manifest_field() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$MANIFEST"; then
    fail "manifest missing required field: $pattern" 65
  fi
}

tool_path() {
  if command -v "$1" >/dev/null 2>&1; then
    command -v "$1"
  else
    printf 'missing\n'
  fi
}

grub_mkrescue_binary() {
  for candidate in "${GRUB_MKRESCUE:-}" grub-mkrescue x86_64-elf-grub-mkrescue; do
    [ -n "$candidate" ] || continue
    if command -v "$candidate" >/dev/null 2>&1; then
      command -v "$candidate"
      return
    fi
  done
  printf 'missing\n'
}

MANIFEST="installer/manifests/latticra-os-image-release.toml"
SOURCE_DIR="boot/latticra-boot-seed"
OUTPUT_DIR="build/boot-seed"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --source-dir)
      [ "$#" -ge 2 ] || fail "missing value for --source-dir" 64
      SOURCE_DIR="$2"
      shift 2
      ;;
    --output-dir)
      [ "$#" -ge 2 ] || fail "missing value for --output-dir" 64
      OUTPUT_DIR="$2"
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
[ -f "$SOURCE_DIR/boot.S" ] || fail "missing boot seed assembly source" 66
[ -f "$SOURCE_DIR/kernel.c" ] || fail "missing boot seed kernel source" 66
[ -f "$SOURCE_DIR/linker.ld" ] || fail "missing boot seed linker script" 66
[ -f "$SOURCE_DIR/grub.cfg" ] || fail "missing boot seed GRUB config" 66

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_seed_contract_present = true'
require_manifest_field 'boot_seed_source_present = true'
require_manifest_field 'boot_seed_build_script_present = true'
require_manifest_field 'boot_seed_qemu_smoke_script_present = true'
require_manifest_field 'boot_seed_full_os_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

ZIG=$(tool_path zig)
GRUB_FILE=$(tool_path x86_64-elf-grub-file)
GRUB_MKRESCUE=$(grub_mkrescue_binary)

[ "$ZIG" != "missing" ] || fail "missing required tool: zig" 69
[ "$GRUB_FILE" != "missing" ] || fail "missing required tool: x86_64-elf-grub-file" 69
[ "$GRUB_MKRESCUE" != "missing" ] || fail "missing required tool: grub-mkrescue compatible binary" 69

mkdir -p "$OUTPUT_DIR"
ISO_ROOT=$(mktemp -d "$OUTPUT_DIR/iso-root.XXXXXX")
trap 'rm -rf "$ISO_ROOT"' EXIT INT HUP TERM
mkdir -p "$ISO_ROOT/boot/grub"

KERNEL_ELF="$OUTPUT_DIR/latticra-boot-seed.elf"
ISO_PATH="$OUTPUT_DIR/latticra-boot-seed.iso"
ZIG_GLOBAL_CACHE_DIR_VALUE="$OUTPUT_DIR/zig-global-cache"
ZIG_LOCAL_CACHE_DIR_VALUE="$OUTPUT_DIR/zig-local-cache"
mkdir -p "$ZIG_GLOBAL_CACHE_DIR_VALUE" "$ZIG_LOCAL_CACHE_DIR_VALUE"

ZIG_GLOBAL_CACHE_DIR="$ZIG_GLOBAL_CACHE_DIR_VALUE" \
ZIG_LOCAL_CACHE_DIR="$ZIG_LOCAL_CACHE_DIR_VALUE" \
"$ZIG" cc \
  -target x86-freestanding-none \
  -ffreestanding \
  -fno-stack-protector \
  -fno-sanitize=undefined \
  -O2 \
  -nostdlib \
  -Wl,-T,"$SOURCE_DIR/linker.ld" \
  -Wl,--build-id=none \
  -o "$KERNEL_ELF" \
  "$SOURCE_DIR/boot.S" \
  "$SOURCE_DIR/kernel.c"

"$GRUB_FILE" --is-x86-multiboot2 "$KERNEL_ELF"
cp "$KERNEL_ELF" "$ISO_ROOT/boot/latticra-boot-seed.elf"
cp "$SOURCE_DIR/grub.cfg" "$ISO_ROOT/boot/grub/grub.cfg"
"$GRUB_MKRESCUE" -o "$ISO_PATH" "$ISO_ROOT" >/dev/null 2>&1

cat <<REPORT
LATTICRA BOOT SEED BUILD

build_status=ok
latticra_boot_seed_build_script_present=1
boot_seed_source_present=1
boot_seed_toolchain=zig-grub-mkrescue
zig_path=$ZIG
grub_file_path=$GRUB_FILE
grub_mkrescue_path=$GRUB_MKRESCUE
output_dir=$OUTPUT_DIR
boot_seed_kernel_path=$KERNEL_ELF
boot_seed_kernel_artifact_created_by_build=1
boot_seed_kernel_multiboot2_verified=1
boot_seed_iso_path=$ISO_PATH
boot_seed_iso_artifact_created_by_build=1
boot_seed_serial_sentinel=LATTICRA_BOOT_SEED_OK
usb_write_executed=0
host_mutation_performed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
