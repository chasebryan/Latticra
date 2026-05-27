#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra os image artifact manifest template: %s\n' "$1" >&2
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
script='scripts/latticra-os-image-artifact-manifest-template.sh'

require_file "$doc"
require_file "$manifest"
require_file "$script"

require_contains 'Artifact Manifest Boundary' "$doc"
require_contains 'LATTICRA OS IMAGE ARTIFACT MANIFEST' "$doc"
require_contains 'os_image_artifact_manifest_template_present=1' "$doc"
require_contains 'scripts/latticra-os-image-artifact-manifest-template.sh' "$doc"
require_contains 'os_image_artifact_manifest_template_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_validation_present = true' "$manifest"
require_contains 'os_image_artifact_manifest_candidate_present = false' "$manifest"

require_contains 'LATTICRA OS IMAGE ARTIFACT MANIFEST TEMPLATE' "$script"
require_contains 'template_decision=blocked-template-only-no-artifact-write' "$script"
require_contains 'artifact_manifest_written=0' "$script"
require_contains 'iso_created=0' "$script"
require_contains 'vm_image_created=0' "$script"
require_contains 'usb_write_executed=0' "$script"
require_contains 'qemu_run_performed=0' "$script"
require_contains 'bootable_os_ready=0' "$script"
require_contains 'production_os_claim=0' "$script"
require_not_line '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_line '^[[:space:]]*dd[[:space:]]' "$script"
require_not_line '^[[:space:]]*qemu-system-x86_64[[:space:]]' "$script"

sh -n "$script"
output=$(sh "$script")
require_output_contains "$output" 'LATTICRA OS IMAGE ARTIFACT MANIFEST TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'latticra_os_image_artifact_manifest_template_present=1'
require_output_contains "$output" 'artifact_manifest_ready_for_operator_review=0'
require_output_contains "$output" 'header=LATTICRA OS IMAGE ARTIFACT MANIFEST'
require_output_contains "$output" 'iso_artifact_path=<path-or-none>'
require_output_contains "$output" 'vm_image_format=<qcow2-or-raw-or-none>'
require_output_contains "$output" 'artifact_manifest_written=0'
require_output_contains "$output" 'bootable_os_ready=0'
require_output_contains "$output" 'production_os_claim=0'

printf 'latticra_os_image_artifact_manifest_template: ok\n'
