#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release signing identity reference contract: %s\n' "$1" >&2
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

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_not_matching() {
  pattern="$1"
  file="$2"
  if grep -Eq -- "$pattern" "$file"; then
    fail "unexpected executable pattern in $file: $pattern"
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

doc='docs/PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_STATUS.md'
script='scripts/production-installer-release-signing-identity-reference.sh'
test_script='scripts/test-production-installer-release-signing-identity-reference-contract.sh'
preflight_script='scripts/production-installer-release-artifact-candidate-preflight.sh'
preflight_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'
workflow='.github/workflows/production-installer-release-signing-identity-reference.yml'

for file in "$doc" "$status" "$script" "$test_script" "$preflight_script" \
  "$preflight_contract" "$readiness" "$ledger" "$index" "$installer_page" \
  "$workflow" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release signing identity reference contract' "$doc"
require_contains 'release_signing_identity_reference_validator_present=1' "$doc"
require_contains 'release_signing_identity_reference_mode=no-secret-inspection-reference-validation' "$doc"
require_contains 'release_signing_identity_reference_no_effect=1' "$doc"
require_contains 'release_signing_identity_reference_valid=0' "$doc"
require_contains 'release_signing_identity_reference_fingerprint_format_valid=0' "$doc"
require_contains 'release_artifact_signing_identity_reference_present=0' "$doc"
require_contains 'secret_key_inspection_performed=0' "$doc"
require_contains 'secret_key_material_read=0' "$doc"
require_contains 'secret_key_material_written=0' "$doc"
require_contains 'signing_performed=0' "$doc"
require_contains 'signature_created=0' "$doc"
require_contains 'signature_verified=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-release-signing-identity-reference.sh' "$doc"
require_contains 'sh scripts/test-production-installer-release-signing-identity-reference-contract.sh' "$doc"

require_contains 'Status: signing-identity/status alignment' "$status"
require_contains 'release_signing_identity_reference_validator_present=1' "$status"
require_contains 'release_signing_identity_reference_valid=0' "$status"
require_contains 'release_signing_identity_reference_fingerprint_format_valid=0' "$status"
require_contains 'release_artifact_signing_identity_reference_present=0' "$status"
require_contains 'secret_key_inspection_performed=0' "$status"
require_contains 'signing_performed=0' "$status"
require_contains 'production_installer_ready=0' "$status"

require_contains 'release_signing_identity_reference_validator_present=1' "$readiness"
require_contains 'release_signing_identity_reference_valid=0' "$readiness"
require_contains 'release_signing_identity_reference_fingerprint_format_valid=0' "$readiness"
require_contains 'release_artifact_signing_identity_reference_present=0' "$readiness"
require_contains 'secret_key_inspection_performed=0' "$readiness"
require_contains 'signing_performed=0' "$readiness"
require_contains 'signature_created=0' "$readiness"
require_contains 'release_signing_identity_reference_validator_present=1' "$ledger"
require_contains 'release_signing_identity_reference_valid=0' "$ledger"
require_contains 'release_signing_identity_reference_fingerprint_format_valid=0' "$ledger"
require_contains 'release_artifact_signing_identity_reference_present=0' "$ledger"
require_contains 'secret_key_inspection_performed=0' "$ledger"
require_contains 'signing_performed=0' "$ledger"
require_contains 'PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_STATUS.md' "$index"
require_contains 'release_signing_identity_reference_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_STATUS.md' README.md
require_contains 'release signing identity reference' "$installer_page"

require_contains 'release_signing_identity_reference_validator_present=1' "$preflight_contract"
require_contains 'release_artifact_signing_identity_reference_format_valid=0' "$preflight_contract"
require_contains 'signing_identity_reference_format_valid=' "$preflight_script"
require_contains 'fingerprint_format_valid' "$preflight_script"

require_absent 'list-secret-keys' "$script"
require_absent 'export-secret' "$script"
require_absent 'gpg --sign' "$script"
require_absent 'gpg -s' "$script"
require_absent 'rpm --addsign' "$script"
require_absent 'rpmsign' "$script"
require_not_matching '^[[:space:]]*gpg[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpmsign[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpm[[:space:]]' "$script"

require_contains 'production-installer-release-signing-identity-reference-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-signing-identity-reference-contract.sh' Makefile
require_contains 'name: Production Installer Release Signing Identity Reference' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-signing-identity-reference-contract.sh' "$workflow"

default_output="$(sh "$script")"
require_output_contains "$default_output" 'LATTICRA PRODUCTION INSTALLER RELEASE SIGNING IDENTITY REFERENCE'
require_output_contains "$default_output" 'signing_identity_reference_status=ok'
require_output_contains "$default_output" 'release_signing_identity_reference_validator_present=1'
require_output_contains "$default_output" 'release_signing_identity_reference_valid=0'
require_output_contains "$default_output" 'release_signing_identity_reference_fingerprint_format_valid=0'
require_output_contains "$default_output" 'release_artifact_signing_identity_reference_present=0'
require_output_contains "$default_output" 'secret_key_inspection_performed=0'
require_output_contains "$default_output" 'signing_performed=0'
require_output_contains "$default_output" 'production_installer_ready=0'

valid_fingerprint='0123456789ABCDEF0123456789ABCDEF01234567'
valid_output="$(sh "$script" \
  --fingerprint "$valid_fingerprint" \
  --identity-label release-test-reference \
  --public-key-path docs/keys/latticra-release-public-key.asc)"
require_output_contains "$valid_output" "release_signing_identity_reference_fingerprint=$valid_fingerprint"
require_output_contains "$valid_output" 'release_signing_identity_reference_valid=1'
require_output_contains "$valid_output" 'release_signing_identity_reference_fingerprint_format_valid=1'
require_output_contains "$valid_output" 'release_signing_identity_reference_label_present=1'
require_output_contains "$valid_output" 'release_signing_identity_reference_public_key_path_recorded=1'
require_output_contains "$valid_output" 'release_artifact_signing_identity_reference_present=1'
require_output_contains "$valid_output" 'secret_key_material_read=0'
require_output_contains "$valid_output" 'signature_created=0'
require_output_contains "$valid_output" 'release_artifact_promotion_gate_passed=0'

invalid_preflight="$(sh "$preflight_script" \
  --tag v0.2.0edge \
  --artifact-path artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint not-a-fingerprint)"
require_output_contains "$invalid_preflight" 'signing_identity_reference_format_valid=0'
require_output_contains "$invalid_preflight" 'signing_identity_reference_present=0'
require_output_contains "$invalid_preflight" 'release_artifact_candidate_preflight_passed=0'

valid_preflight="$(sh "$preflight_script" \
  --tag v0.2.0edge \
  --artifact-path artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint "$valid_fingerprint")"
require_output_contains "$valid_preflight" 'signing_identity_reference_format_valid=1'
require_output_contains "$valid_preflight" 'signing_identity_reference_present=1'
require_output_contains "$valid_preflight" 'release_artifact_candidate_preflight_passed=0'

if sh "$script" --unknown >/dev/null 2>&1; then
  fail 'unknown argument unexpectedly succeeded'
fi

printf 'production_installer_release_signing_identity_reference_contract: ok\n'
