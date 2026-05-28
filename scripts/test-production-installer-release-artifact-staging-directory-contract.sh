#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release artifact staging directory contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_dir() {
  dir="$1"
  [ -d "$dir" ] || fail "missing directory: $dir"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_STATUS.md'
staging_readme='artifacts/release/README.md'
test_script='scripts/test-production-installer-release-artifact-staging-directory-contract.sh'
preflight_script='scripts/production-installer-release-artifact-candidate-preflight.sh'
preflight_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'
workflow='.github/workflows/production-installer-release-artifact-staging-directory.yml'

for file in "$doc" "$status" "$staging_readme" "$test_script" "$preflight_script" \
  "$preflight_contract" "$readiness" "$ledger" "$index" "$installer_page" \
  "$workflow" Makefile README.md
do
  require_file "$file"
done

require_dir 'artifacts/release'

sh -n "$test_script"

unexpected="$(find artifacts/release -type f ! -name README.md -print)"
if [ -n "$unexpected" ]; then
  fail "unexpected staged release output: $unexpected"
fi

for file in "$doc" "$status" "$staging_readme" "$readiness" "$ledger" README.md
do
  require_contains 'release_artifact_staging_directory_present=1' "$file"
  require_contains 'release_artifact_staging_directory_path=artifacts/release' "$file"
  require_contains 'release_artifact_staging_directory_no_effect=1' "$file"
  require_contains 'release_artifact_candidate_parent_dir_exists=1' "$file"
  require_contains 'release_artifact_created=0' "$file"
  require_contains 'release_artifact_present=0' "$file"
  require_contains 'source_archive_created=0' "$file"
  require_contains 'rpm_build_invoked=0' "$file"
  require_contains 'signature_created=0' "$file"
  require_contains 'checksum_recorded=0' "$file"
  require_contains 'release_artifact_evidence_written=0' "$file"
  require_contains 'release_artifact_evidence_accepted=0' "$file"
  require_contains 'release_artifact_promotion_gate_passed=0' "$file"
  require_contains 'production_installer_ready=0' "$file"
  require_contains 'host_mutation_performed=0' "$file"
done

require_contains 'Status: no-effect release-artifact staging directory contract' "$doc"
require_contains 'Forbidden staged outputs' "$doc"
require_contains 'sh scripts/test-production-installer-release-artifact-staging-directory-contract.sh' "$doc"
require_contains 'Status: staging/status alignment' "$status"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_STATUS.md' "$index"
require_contains 'Release artifact staging directory' "$installer_page"
require_contains 'artifact staging directory' "$installer_page"
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_STATUS.md' README.md

require_contains 'production-installer-release-artifact-staging-directory-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-artifact-staging-directory-contract.sh' Makefile
require_contains 'name: Production Installer Release Artifact Staging Directory' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-artifact-staging-directory-contract.sh' "$workflow"

require_absent '.rpm' "$staging_readme"
require_absent '.src.rpm' "$staging_readme"

preflight_output="$(sh "$preflight_script" \
  --tag v0.2.0edge \
  --artifact-path artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint none)"
require_output_contains "$preflight_output" 'release_artifact_candidate_parent_dir=artifacts/release'
require_output_contains "$preflight_output" 'release_artifact_candidate_parent_dir_exists=1'
require_output_contains "$preflight_output" 'release_artifact_candidate_preflight_passed=0'
require_output_contains "$preflight_output" 'release_artifact_candidate_inputs_satisfied=0'

printf 'production_installer_release_artifact_staging_directory_contract: ok\n'
