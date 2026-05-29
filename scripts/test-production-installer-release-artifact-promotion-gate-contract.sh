#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release artifact promotion gate contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
gate='scripts/production-installer-release-artifact-promotion-gate.sh'
test_script='scripts/test-production-installer-release-artifact-promotion-gate-contract.sh'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'

for file in "$doc" "$gate" "$test_script" "$prod" "$ledger" "$index" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect release-artifact promotion gate contract' "$doc"
require_contains 'Evidence level: 10 target, promotion gate only' "$doc"
require_contains 'sh scripts/production-installer-release-artifact-promotion-gate.sh' "$doc"
require_contains 'production_installer_artifact_integrity_status_required=1' "$doc"
require_contains 'artifact_integrity_status_present=1' "$doc"
require_contains 'installer_artifact_checksum_status_present=1' "$doc"
require_contains 'installer_artifact_signature_status_present=1' "$doc"
require_contains 'release_artifact_candidate_preflight_present=1' "$doc"
require_contains 'release_artifact_candidate_preflight_passed=0' "$doc"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$doc"
require_contains 'release_artifact_promotion_gate_present=1' "$doc"
require_contains 'release_artifact_promotion_gate_no_effect=1' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'release_artifact_promotion_gate_decision=blocked-missing-tagged-release-artifact' "$doc"
require_contains 'release_artifact_present=0' "$doc"
require_contains 'release_artifact_built_from_tag=0' "$doc"
require_contains 'release_artifact_reproducible=0' "$doc"
require_contains 'release_artifact_sha256_recorded=0' "$doc"
require_contains 'release_artifact_signature_present=0' "$doc"
require_contains 'release_artifact_signature_verified=0' "$doc"
require_contains 'release_public_key_documented=0' "$doc"
require_contains 'signature_verification_documented=0' "$doc"
require_contains 'installer_artifact_reproducible=0' "$doc"
require_contains 'installer_artifact_checksum_recorded=0' "$doc"
require_contains 'installer_artifact_signature_recorded=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'It does not create, build, sign, publish, or verify a release artifact.' "$doc"
require_contains 'release_artifact_present=1' "$doc"
require_contains 'release_artifact_built_from_tag=1' "$doc"
require_contains 'release_artifact_signature_verified=1' "$doc"
require_contains 'Satisfy the release-artifact candidate preflight before creating a tagged release artifact candidate and collecting checksum, signature, public-key, verification, reproducibility, and review evidence.' "$doc"
require_contains 'This gate is not a production installer.' "$doc"

require_contains 'release_artifact_promotion_gate_present=1' "$prod"
require_contains 'release_artifact_promotion_gate_passed=0' "$prod"
require_contains 'release_artifact_candidate_preflight_present=1' "$prod"
require_contains 'release_artifact_candidate_preflight_passed=0' "$prod"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$prod"
require_contains 'release_artifact_present=0' "$prod"
require_contains 'release_artifact_promotion_gate_present=1' "$ledger"
require_contains 'release_artifact_promotion_gate_passed=0' "$ledger"
require_contains 'release_artifact_present=0' "$ledger"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md' "$index"
require_contains 'test-production-installer-release-artifact-promotion-gate-contract.sh' Makefile

output="$(sh "$gate")"
require_output_contains 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT PROMOTION GATE' "$output"
require_output_contains 'gate_mode=no-effect-release-artifact-promotion' "$output"
require_output_contains 'release_artifact_promotion_gate_present=1' "$output"
require_output_contains 'release_artifact_promotion_gate_no_effect=1' "$output"
require_output_contains 'release_artifact_promotion_gate_passed=0' "$output"
require_output_contains 'release_artifact_promotion_gate_decision=blocked-missing-tagged-release-artifact' "$output"
require_output_contains 'release_artifact_candidate_preflight_present=1' "$output"
require_output_contains 'release_artifact_candidate_preflight_passed=0' "$output"
require_output_contains 'release_artifact_candidate_inputs_satisfied=0' "$output"
require_output_contains 'release_artifact_promotion_required_evidence_count=9' "$output"
require_output_contains 'release_artifact_promotion_satisfied_evidence_count=0' "$output"
require_output_contains 'release_artifact_present=0' "$output"
require_output_contains 'release_artifact_built_from_tag=0' "$output"
require_output_contains 'release_artifact_reproducible=0' "$output"
require_output_contains 'release_artifact_sha256_recorded=0' "$output"
require_output_contains 'release_artifact_signature_present=0' "$output"
require_output_contains 'release_artifact_signature_verified=0' "$output"
require_output_contains 'release_public_key_documented=0' "$output"
require_output_contains 'signature_verification_documented=0' "$output"
require_output_contains 'installer_artifact_reproducible=0' "$output"
require_output_contains 'installer_artifact_checksum_recorded=0' "$output"
require_output_contains 'installer_artifact_signature_recorded=0' "$output"
require_output_contains 'install_performed=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"

printf 'production_installer_release_artifact_promotion_gate_contract: ok\n'
