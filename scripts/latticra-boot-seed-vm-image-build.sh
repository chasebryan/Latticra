#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-boot-seed-vm-image-build.sh --kernel <path> [--manifest <path>] [--grub-cfg <path>] [--output-dir <path>] [--image-size-mib <n>]

Builds a local qcow2 VM image for the Latticra boot seed using a FAT EFI
system image, GRUB standalone, and the supplied Multiboot2 kernel ELF. It does
not write USB media, mutate firmware, install bootloaders on the host, create a
production rootfs, or claim full OS readiness.
USAGE
}

fail() {
  printf 'latticra boot seed vm image build: %s\n' "$1" >&2
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

MANIFEST="installer/manifests/latticra-os-image-release.toml"
KERNEL=""
GRUB_CFG="boot/latticra-boot-seed/grub.cfg"
OUTPUT_DIR="build/boot-seed"
IMAGE_SIZE_MIB="64"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --manifest)
      [ "$#" -ge 2 ] || fail "missing value for --manifest" 64
      MANIFEST="$2"
      shift 2
      ;;
    --kernel)
      [ "$#" -ge 2 ] || fail "missing value for --kernel" 64
      KERNEL="$2"
      shift 2
      ;;
    --grub-cfg)
      [ "$#" -ge 2 ] || fail "missing value for --grub-cfg" 64
      GRUB_CFG="$2"
      shift 2
      ;;
    --output-dir)
      [ "$#" -ge 2 ] || fail "missing value for --output-dir" 64
      OUTPUT_DIR="$2"
      shift 2
      ;;
    --image-size-mib)
      [ "$#" -ge 2 ] || fail "missing value for --image-size-mib" 64
      IMAGE_SIZE_MIB="$2"
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
[ -n "$KERNEL" ] || fail "missing --kernel" 64
[ -f "$KERNEL" ] || fail "boot seed kernel not found: $KERNEL" 66
[ -f "$GRUB_CFG" ] || fail "GRUB config not found: $GRUB_CFG" 66

case "$IMAGE_SIZE_MIB" in
  ''|*[!0-9]*) fail "image size must be a positive integer MiB value" 64 ;;
  *) ;;
esac
[ "$IMAGE_SIZE_MIB" -gt 0 ] || fail "image size must be greater than zero" 64

require_manifest_field 'name = "latticra-os-image-release"'
require_manifest_field 'status = "fixture-only"'
require_manifest_field 'boot_seed_contract_present = true'
require_manifest_field 'boot_seed_vm_image_build_script_present = true'
require_manifest_field 'boot_seed_vm_qcow2_artifact_present = false'
require_manifest_field 'boot_seed_full_os_ready = false'
require_manifest_field 'bootable_os_ready = false'
require_manifest_field 'production_os_claim = false'

GRUB_FILE=$(tool_path x86_64-elf-grub-file)
GRUB_MKSTANDALONE=$(tool_path x86_64-elf-grub-mkstandalone)
QEMU_IMG=$(tool_path qemu-img)
MFORMAT=$(tool_path mformat)
MMD=$(tool_path mmd)
MCOPY=$(tool_path mcopy)

[ "$GRUB_FILE" != "missing" ] || fail "missing required tool: x86_64-elf-grub-file" 69
[ "$GRUB_MKSTANDALONE" != "missing" ] || fail "missing required tool: x86_64-elf-grub-mkstandalone" 69
[ "$QEMU_IMG" != "missing" ] || fail "missing required tool: qemu-img" 69
[ "$MFORMAT" != "missing" ] || fail "missing required tool: mformat" 69
[ "$MMD" != "missing" ] || fail "missing required tool: mmd" 69
[ "$MCOPY" != "missing" ] || fail "missing required tool: mcopy" 69

"$GRUB_FILE" --is-x86-multiboot2 "$KERNEL"

mkdir -p "$OUTPUT_DIR"
EFI_BOOT="$OUTPUT_DIR/BOOTX64.EFI"
ESP_RAW="$OUTPUT_DIR/latticra-boot-seed-esp.raw"
VM_QCOW2="$OUTPUT_DIR/latticra-boot-seed.qcow2"

"$GRUB_MKSTANDALONE" -O x86_64-efi -o "$EFI_BOOT" "boot/grub/grub.cfg=$GRUB_CFG"
"$QEMU_IMG" create -f raw "$ESP_RAW" "${IMAGE_SIZE_MIB}M" >/dev/null
"$MFORMAT" -i "$ESP_RAW" -F ::
"$MMD" -i "$ESP_RAW" ::/EFI ::/EFI/BOOT ::/boot
"$MCOPY" -i "$ESP_RAW" "$EFI_BOOT" ::/EFI/BOOT/BOOTX64.EFI
"$MCOPY" -i "$ESP_RAW" "$KERNEL" ::/boot/latticra-boot-seed.elf
"$QEMU_IMG" convert -f raw -O qcow2 "$ESP_RAW" "$VM_QCOW2"

cat <<REPORT
LATTICRA BOOT SEED VM IMAGE BUILD

build_status=ok
latticra_boot_seed_vm_image_build_script_present=1
boot_seed_kernel_path=$KERNEL
boot_seed_kernel_multiboot2_verified=1
grub_mkstandalone_path=$GRUB_MKSTANDALONE
qemu_img_path=$QEMU_IMG
mformat_path=$MFORMAT
mcopy_path=$MCOPY
output_dir=$OUTPUT_DIR
boot_seed_efi_bootloader_path=$EFI_BOOT
boot_seed_esp_raw_path=$ESP_RAW
boot_seed_vm_qcow2_path=$VM_QCOW2
boot_seed_vm_qcow2_artifact_created_by_build=1
boot_seed_vm_qcow2_artifact_present=0
usb_write_executed=0
host_mutation_performed=0
hardware_install_ready=0
full_os_install_ready=0
bootable_os_ready=0
production_os_claim=0
REPORT
