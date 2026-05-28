#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer artifact integrity status contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md'
status_script='scripts/production-installer-artifact-integrity-status.sh'
test_script='scripts/test-production-installer-artifact-integrity-status-contract.sh'
fixture='fixtures/artifact/local-artifact-manifest.txt'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'

for file in "$doc" "$status_script" "$test_script" "$fixture" "$prod" "$ledger" "$index" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect artifact-integrity status contract' "$doc"
require_contains 'Evidence level: 10 target, status evidence only' "$doc"
require_contains 'sh scripts/production-installer-artifact-integrity-status.sh' "$doc"
require_contains 'local_artifact_manifest_fixture_required=1' "$doc"
require_contains 'production_installer_preflight_guard_present=1' "$doc"
require_contains 'installer_install_plan_preview_present=1' "$doc"
require_contains 'artifact_integrity_status_present=1' "$doc"
require_contains 'installer_artifact_checksum_status_present=1' "$doc"
require_contains 'installer_artifact_signature_status_present=1' "$doc"
require_contains 'fixture_manifest_sha256_recorded=1' "$doc"
require_contains 'fixture_manifest_artifact_sha256_field=fixture-placeholder-not-release-checksum' "$doc"
require_contains 'fixture_manifest_artifact_signature_field=none' "$doc"
require_contains 'release_artifact_present=0' "$doc"
require_contains 'release_artifact_sha256_recorded=0' "$doc"
require_contains 'release_artifact_signature_present=0' "$doc"
require_contains 'release_artifact_signature_verified=0' "$doc"
require_contains 'installer_artifact_reproducible=0' "$doc"
require_contains 'installer_artifact_checksum_recorded=0' "$doc"
require_contains 'installer_artifact_signature_recorded=0' "$doc"
require_contains 'installer_public_key_documented=0' "$doc"
require_contains 'signature_verification_documented=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'It does not close the production-installer checksum or signature gates.' "$doc"
require_contains 'release_artifact_present=1' "$doc"
require_contains 'release_artifact_built_from_tag=1' "$doc"
require_contains 'release_artifact_reproducible=1' "$doc"
require_contains 'release_artifact_signature_verified=1' "$doc"
require_contains 'Run the release-artifact promotion gate against a tagged release artifact candidate and collect checksum, signature, public-key, verification, reproducibility, and review evidence.' "$doc"
require_contains 'This status record is not a production installer.' "$doc"

require_contains 'artifact_sha256=fixture-placeholder-not-release-checksum' "$fixture"
require_contains 'artifact_signature=none' "$fixture"
require_contains 'artifact_checksum_recorded=0' "$fixture"
require_contains 'artifact_signature_recorded=0' "$fixture"

require_contains 'artifact_integrity_status_present=1' "$prod"
require_contains 'installer_artifact_checksum_status_present=1' "$prod"
require_contains 'installer_artifact_signature_status_present=1' "$prod"
require_contains 'installer_artifact_checksum_recorded=0' "$prod"
require_contains 'installer_artifact_signature_recorded=0' "$prod"
require_contains 'artifact_integrity_status_present=1' "$ledger"
require_contains 'installer_artifact_checksum_status_present=1' "$ledger"
require_contains 'installer_artifact_signature_status_present=1' "$ledger"
require_contains 'PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md' "$index"
require_contains 'test-production-installer-artifact-integrity-status-contract.sh' Makefile

output="$(sh "$status_script")"
require_output_contains 'LATTICRA PRODUCTION INSTALLER ARTIFACT INTEGRITY STATUS' "$output"
require_output_contains 'status_mode=no-effect-artifact-integrity-review' "$output"
require_output_contains 'artifact_integrity_status_present=1' "$output"
require_output_contains 'installer_artifact_checksum_status_present=1' "$output"
require_output_contains 'installer_artifact_signature_status_present=1' "$output"
require_output_contains 'fixture_manifest_sha256_recorded=1' "$output"
require_output_contains 'fixture_manifest_sha256=' "$output"
require_output_contains 'fixture_manifest_artifact_sha256_field=fixture-placeholder-not-release-checksum' "$output"
require_output_contains 'fixture_manifest_artifact_signature_field=none' "$output"
require_output_contains 'release_artifact_present=0' "$output"
require_output_contains 'release_artifact_sha256_recorded=0' "$output"
require_output_contains 'release_artifact_signature_present=0' "$output"
require_output_contains 'release_artifact_signature_verified=0' "$output"
require_output_contains 'installer_artifact_reproducible=0' "$output"
require_output_contains 'installer_artifact_checksum_recorded=0' "$output"
require_output_contains 'installer_artifact_signature_recorded=0' "$output"
require_output_contains 'signature_verification_documented=0' "$output"
require_output_contains 'install_performed=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"

printf 'production_installer_artifact_integrity_status_contract: ok\n'
