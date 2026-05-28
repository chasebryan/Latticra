#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image artifact manifest validate: %s\n' "$1" >&2
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

doc='docs/LATTICRA_OS_IMAGE_RELEASE_READINESS_CONTRACT.md'
manifest='installer/manifests/latticra-os-image-release.toml'
script='scripts/latticra-os-image-artifact-manifest-validate.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'scripts/latticra-os-image-artifact-manifest-validate.sh' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-from-files.sh' "$doc"
require_contains 'artifact_manifest_ready_for_operator_review=<0-or-1>' "$doc"
require_contains 'os_image_artifact_manifest_generator_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_validation_present = true' "$manifest"

require_contains 'LATTICRA OS IMAGE ARTIFACT MANIFEST VALIDATION' "$script"
require_contains 'validation_decision=blocked-fixture-only-no-artifact-manifest-candidate' "$script"
require_contains 'validation_decision=metadata-consistency-only-no-readiness-promotion' "$script"
require_contains 'artifact_manifest_ready_for_operator_review=' "$script"
require_contains 'usb_write_execution_allowed=0' "$script"
require_contains 'qemu_execution_allowed_by_guard=0' "$script"
require_contains 'hardware_install_ready=0' "$script"
require_contains 'full_os_install_ready=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"

sh -n "$script"

default_output=$(sh "$script")
require_output_contains "$default_output" 'LATTICRA OS IMAGE ARTIFACT MANIFEST VALIDATION'
require_output_contains "$default_output" 'validation_status=ok'
require_output_contains "$default_output" 'artifact_manifest_candidate_supplied=0'
require_output_contains "$default_output" 'artifact_manifest_ready_for_operator_review=0'
require_output_contains "$default_output" 'iso_artifact_present=0'
require_output_contains "$default_output" 'vm_image_artifact_present=0'
require_output_contains "$default_output" 'bootable_os_ready=0'
require_output_contains "$default_output" 'production_os_claim=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-os-image-artifact-manifest-test.XXXXXX")"
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

iso_sha=$(measure_file "$iso")
vm_sha=$(measure_file "$vm")
candidate="$tmp/manifest.txt"
cat > "$candidate" <<EOF
LATTICRA OS IMAGE ARTIFACT MANIFEST
manifest_version=1
artifact_set=os-image-release
artifact_version=test-fixture
source_commit=test-fixture
source_tag=none
build_environment=test-fixture
iso_artifact_path=latticra-x86_64.iso
iso_artifact_sha256=$iso_sha
iso_signature_path=latticra-x86_64.iso.sig
iso_sbom_path=iso-sbom.spdx.json
vm_image_path=latticra-x86_64.qcow2
vm_image_format=qcow2
vm_image_sha256=$vm_sha
vm_signature_path=latticra-x86_64.qcow2.sig
vm_sbom_path=vm-sbom.spdx.json
usb_write_command_template_present=1
vm_test_command_template_present=1
operator_recovery_path=recovery.txt
bootable_os_ready=0
production_os_claim=0
EOF

candidate_output=$(sh "$script" --artifact-manifest "$candidate")
require_output_contains "$candidate_output" 'artifact_manifest_candidate_supplied=1'
require_output_contains "$candidate_output" 'artifact_manifest_metadata_consistent=1'
require_output_contains "$candidate_output" 'artifact_manifest_ready_for_operator_review=1'
require_output_contains "$candidate_output" 'iso_artifact_present=1'
require_output_contains "$candidate_output" 'iso_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'vm_image_artifact_present=1'
require_output_contains "$candidate_output" 'vm_image_checksum_verified_by_validator=1'
require_output_contains "$candidate_output" 'hardware_install_ready=0'
require_output_contains "$candidate_output" 'full_os_install_ready=0'
require_output_contains "$candidate_output" 'bootable_os_ready=0'
require_output_contains "$candidate_output" 'production_os_claim=0'

printf 'latticra_os_image_artifact_manifest_validate: ok\n'
