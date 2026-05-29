#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image artifact manifest from files: %s\n' "$1" >&2
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

require_not_line() {
  pattern="$1"
  file="$2"
  if grep -Eq "$pattern" "$file"; then
    fail "forbidden executable-looking line in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-artifact-manifest-from-files.sh'
validator='scripts/latticra-os-image-artifact-manifest-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"
require_file "$validator"

require_contains 'os_image_artifact_manifest_generator_present=1' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-from-files.sh' "$doc"
require_contains 'os_image_artifact_manifest_generator_present = true' "$manifest"
require_contains 'LATTICRA OS IMAGE ARTIFACT MANIFEST' "$script"
require_contains 'os_image_artifact_manifest_generator_present = true' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"

sh -n "$script"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-artifact-manifest-from-files.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

iso="$tmp/latticra-x86_64.iso"
vm="$tmp/latticra-x86_64.qcow2"
printf 'fake iso fixture\n' > "$iso"
printf 'fake vm fixture\n' > "$vm"
printf 'fake signature\n' > "$tmp/latticra-x86_64.iso.sig"
printf 'fake signature\n' > "$tmp/latticra-x86_64.qcow2.sig"
printf '{"sbom":"fake"}\n' > "$tmp/iso-sbom.spdx.json"
printf '{"sbom":"fake"}\n' > "$tmp/vm-sbom.spdx.json"
printf 'reimage from known-good release media\n' > "$tmp/recovery.txt"

iso_expected="$(cd "$(dirname "$iso")" && pwd -P)/$(basename "$iso")"
vm_expected="$(cd "$(dirname "$vm")" && pwd -P)/$(basename "$vm")"
candidate="$tmp/manifest.txt"

output=$(sh "$script" \
  --artifact-version test-fixture \
  --source-commit test-fixture \
  --source-tag none \
  --build-environment test-fixture \
  --iso "$iso" \
  --iso-signature "$tmp/latticra-x86_64.iso.sig" \
  --iso-sbom "$tmp/iso-sbom.spdx.json" \
  --vm-image "$vm" \
  --vm-format qcow2 \
  --vm-signature "$tmp/latticra-x86_64.qcow2.sig" \
  --vm-sbom "$tmp/vm-sbom.spdx.json" \
  --operator-recovery-path "$tmp/recovery.txt")

require_output_contains "$output" 'LATTICRA OS IMAGE ARTIFACT MANIFEST'
require_output_contains "$output" 'manifest_version=1'
require_output_contains "$output" 'artifact_set=os-image-release'
require_output_contains "$output" 'artifact_version=test-fixture'
require_output_contains "$output" "iso_artifact_path=$iso_expected"
require_output_contains "$output" 'iso_artifact_sha256=sha256:'
require_output_contains "$output" "vm_image_path=$vm_expected"
require_output_contains "$output" 'vm_image_format=qcow2'
require_output_contains "$output" 'vm_image_sha256=sha256:'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf '%s\n' "$output" > "$candidate"
candidate_output=$(sh "$validator" --artifact-manifest "$candidate")
require_output_contains "$candidate_output" 'artifact_manifest_candidate_supplied=1'
require_output_contains "$candidate_output" 'artifact_manifest_metadata_consistent=1'
require_output_contains "$candidate_output" 'artifact_manifest_ready_for_operator_review=1'
require_output_contains "$candidate_output" 'iso_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'vm_image_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_artifact_manifest_from_files: ok\n'
