#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra boot seed sbom: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_BOOT_SEED_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-boot-seed-sbom-generate.sh'
artifact_generator='scripts/latticra-os-image-artifact-manifest-from-files.sh'
artifact_validator='scripts/latticra-os-image-artifact-manifest-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"
require_file "$artifact_generator"
require_file "$artifact_validator"

require_contains 'boot_seed_sbom_generator_present=1' "$doc"
require_contains 'scripts/latticra-boot-seed-sbom-generate.sh' "$doc"
require_contains 'boot_seed_sbom_generator_present = true' "$manifest"
require_contains 'SPDX-2.3' "$script"
require_contains 'bootable_os_ready = false' "$script"
require_contains 'production_os_claim = false' "$script"

sh -n "$script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-boot-seed-sbom.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

iso="$tmp/latticra-boot-seed.iso"
vm="$tmp/latticra-boot-seed.qcow2"
kernel="$tmp/latticra-boot-seed.elf"
efi="$tmp/BOOTX64.EFI"
esp="$tmp/latticra-boot-seed-esp.raw"
sbom="$tmp/sbom.spdx.json"
manifest_candidate="$tmp/manifest.txt"
printf 'fake iso\n' > "$iso"
printf 'fake qcow2\n' > "$vm"
printf 'fake kernel\n' > "$kernel"
printf 'fake efi\n' > "$efi"
printf 'fake esp\n' > "$esp"

sh "$script" \
  --artifact-version test-fixture \
  --source-commit test-fixture \
  --iso "$iso" \
  --vm-image "$vm" \
  --kernel "$kernel" \
  --efi-bootloader "$efi" \
  --esp-raw "$esp" > "$sbom"

python3 -m json.tool "$sbom" >/dev/null
require_contains 'SPDX-2.3' "$sbom"
require_contains 'SPDXRef-File-BootSeedISO' "$sbom"
require_contains 'SPDXRef-File-BootSeedQCOW2' "$sbom"
require_contains 'SPDXRef-File-BootSeedKernel' "$sbom"

artifact_output=$(sh "$artifact_generator" \
  --artifact-version test-fixture \
  --source-commit test-fixture \
  --source-tag none \
  --build-environment test-fixture \
  --iso "$iso" \
  --iso-sbom "$sbom" \
  --vm-image "$vm" \
  --vm-format qcow2 \
  --vm-sbom "$sbom" \
  --operator-recovery-path "$doc")
printf '%s\n' "$artifact_output" > "$manifest_candidate"

validation_output=$(sh "$artifact_validator" --artifact-manifest "$manifest_candidate")
require_output_contains "$validation_output" 'artifact_manifest_ready_for_operator_review=1'
require_output_contains "$validation_output" 'iso_checksum_verified_by_validator=1'
require_output_contains "$validation_output" 'vm_image_checksum_verified_by_validator=1'
require_output_contains "$validation_output" 'bootable_os_ready=0'
require_output_contains "$validation_output" 'production_os_claim=0'

printf 'latticra_boot_seed_sbom: ok\n'
