#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"

if [ ! -f "$fixture" ]; then
  printf 'production installer artifact integrity status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

fixture_sha256='unavailable'
if command -v sha256sum >/dev/null 2>&1; then
  set -- $(sha256sum "$fixture")
  fixture_sha256="$1"
elif command -v shasum >/dev/null 2>&1; then
  set -- $(shasum -a 256 "$fixture")
  fixture_sha256="$1"
else
  printf 'production installer artifact integrity status: missing sha256 tool\n' >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer artifact integrity status: missing fixture line: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_line 'artifact_sha256=fixture-placeholder-not-release-checksum'
require_line 'artifact_signature=none'
require_line 'artifact_signing_key_id=none'
require_line 'artifact_checksum_recorded=0'
require_line 'artifact_signature_recorded=0'
require_line 'production_installer_ready=0'

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER ARTIFACT INTEGRITY STATUS' \
  'status_version=1' \
  'status_mode=no-effect-artifact-integrity-review' \
  'artifact_integrity_status_present=1' \
  'installer_artifact_checksum_status_present=1' \
  'installer_artifact_signature_status_present=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_preflight_guard_present=1' \
  'installer_install_plan_preview_present=1' \
  'fixture_manifest_sha256_recorded=1' \
  "fixture_manifest_sha256=$fixture_sha256" \
  'fixture_manifest_artifact_sha256_field=fixture-placeholder-not-release-checksum' \
  'fixture_manifest_artifact_signature_field=none' \
  'fixture_manifest_artifact_signing_key_id=none' \
  'release_artifact_present=0' \
  'release_artifact_built_from_tag=0' \
  'release_artifact_reproducible=0' \
  'release_artifact_sha256_recorded=0' \
  'release_artifact_signature_present=0' \
  'release_artifact_signature_verified=0' \
  'release_public_key_documented=0' \
  'signature_verification_documented=0' \
  'artifact_integrity_reviewed=0' \
  'installer_artifact_reproducible=0' \
  'installer_artifact_checksum_recorded=0' \
  'installer_artifact_signature_recorded=0' \
  'installer_public_key_documented=0' \
  'installer_sbom_recorded=0' \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
