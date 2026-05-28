#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release artifact evidence intake validator contract: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    set -- $(sha256sum "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  elif command -v shasum >/dev/null 2>&1; then
    set -- $(shasum -a 256 "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  else
    fail 'missing sha256 tool'
  fi
}

doc='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-release-artifact-evidence-intake.sh'
test_script='scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
artifact_status='docs/PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-release-artifact-evidence-intake-validator.yml'

for file in "$doc" "$status" "$script" "$test_script" "$readiness" "$artifact_status" "$promotion_gate" "$ledger" "$index" "$workflow" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release-artifact evidence intake validator contract' "$doc"
require_contains 'release_artifact_evidence_intake_validator_present=1' "$doc"
require_contains 'release_artifact_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'release_artifact_candidate_valid=0' "$doc"
require_contains 'release_artifact_sha256_matches=0' "$doc"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'release_artifact_evidence_written_by_intake_validator=0' "$doc"
require_contains 'release_artifact_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-release-artifact-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'release_artifact_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'release_artifact_candidate_valid=1' "$script"
require_contains 'release_artifact_sha256_matches=1' "$script"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'release_artifact_evidence_written_by_intake_validator=0' "$script"
require_contains 'release_artifact_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'artifact checksum mismatch' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'release_artifact_evidence_intake_validator_present=1' \
  'release_artifact_evidence_intake_validation_mode=no-effect-validation' \
  'release_artifact_candidate_valid=0' \
  'release_artifact_checksum_file_present=0' \
  'release_artifact_sha256_matches=0' \
  'release_artifact_signature_file_present=0' \
  'release_public_key_file_present=0' \
  'signature_verification_transcript_present=0' \
  'reproducibility_transcript_present=0' \
  'artifact_integrity_review_present=0' \
  'release_artifact_evidence_accepted_by_intake_validator=0' \
  'release_artifact_evidence_written_by_intake_validator=0' \
  'release_artifact_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
done

for future_field in \
  'release_artifact_evidence_status=complete' \
  'release_artifact_present=1' \
  'release_artifact_built_from_tag=1' \
  'release_artifact_reproducible=1' \
  'release_artifact_sha256_recorded=1' \
  'release_artifact_signature_present=1' \
  'release_artifact_signature_verified=1' \
  'release_public_key_documented=1' \
  'signature_verification_documented=1' \
  'artifact_integrity_reviewed=1' \
  'installer_artifact_reproducible=1' \
  'installer_artifact_checksum_recorded=1' \
  'installer_artifact_signature_recorded=1' \
  'installer_public_key_documented=1' \
  'signature_verification_transcript_present=1' \
  'reproducibility_transcript_present=1' \
  'artifact_integrity_review_present=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$status"
  require_contains "$future_field" "$script"
done

require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'release_artifact_evidence_intake_validator_present=1' "$readiness"
require_contains 'release_artifact_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'release_artifact_candidate_valid=0' "$readiness"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'release_artifact_evidence_intake_validator_present=1' "$ledger"
require_contains 'release_artifact_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md

require_contains 'production-installer-release-artifact-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer Release Artifact Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-release-artifact-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-release-artifact-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

artifact="$tmp/latticra-production-installer.rpm"
checksum="$tmp/latticra-production-installer.rpm.sha256"
signature="$tmp/latticra-production-installer.rpm.sig"
public_key="$tmp/latticra-release-public-key.asc"
verification="$tmp/signature-verification.txt"
reproducibility="$tmp/reproducibility.txt"
review="$tmp/artifact-integrity-review.txt"
valid_evidence="$tmp/release-artifact-evidence.txt"
placeholder_evidence="$tmp/release-artifact-placeholder-evidence.txt"
bad_checksum="$tmp/bad.sha256"

printf 'local release artifact candidate fixture\n' >"$artifact"
printf 'detached signature fixture\n' >"$signature"
printf 'public key fixture\n' >"$public_key"
printf 'signature verification transcript fixture\n' >"$verification"
printf 'reproducibility transcript fixture\n' >"$reproducibility"
printf 'artifact integrity review fixture\n' >"$review"

artifact_sha="$(sha256_file "$artifact")"
signature_sha="$(sha256_file "$signature")"
public_key_sha="$(sha256_file "$public_key")"
verification_sha="$(sha256_file "$verification")"
reproducibility_sha="$(sha256_file "$reproducibility")"
review_sha="$(sha256_file "$review")"

printf '%s  %s\n' "$artifact_sha" "$artifact" >"$checksum"
printf '%s  %s\n' '0000000000000000000000000000000000000000000000000000000000000000' "$artifact" >"$bad_checksum"

cat >"$valid_evidence" <<VALID_EVIDENCE
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE
release_artifact_evidence_status=complete
release_artifact_present=1
release_artifact_built_from_tag=1
release_artifact_reproducible=1
release_artifact_sha256_recorded=1
release_artifact_signature_present=1
release_artifact_signature_verified=1
release_public_key_documented=1
signature_verification_documented=1
artifact_integrity_reviewed=1
installer_artifact_reproducible=1
installer_artifact_checksum_recorded=1
installer_artifact_signature_recorded=1
installer_public_key_documented=1
signature_verification_transcript_present=1
reproducibility_transcript_present=1
artifact_integrity_review_present=1
artifact_sha256=$artifact_sha
artifact_signature_sha256=$signature_sha
release_public_key_sha256=$public_key_sha
signature_verification_transcript_sha256=$verification_sha
reproducibility_transcript_sha256=$reproducibility_sha
artifact_integrity_review_sha256=$review_sha
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
VALID_EVIDENCE

cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --artifact "$artifact" \
  --sha256 "$checksum" \
  --signature "$signature" \
  --public-key "$public_key" \
  --verification "$verification" \
  --reproducibility "$reproducibility" \
  --review "$review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'release_artifact_evidence_intake_validator_present=1'
require_output_contains "$output" 'release_artifact_candidate_valid=1'
require_output_contains "$output" 'release_artifact_sha256_matches=1'
require_output_contains "$output" "candidate_release_artifact_sha256=$artifact_sha"
require_output_contains "$output" "candidate_artifact_signature_sha256=$signature_sha"
require_output_contains "$output" "candidate_release_public_key_sha256=$public_key_sha"
require_output_contains "$output" "candidate_signature_verification_transcript_sha256=$verification_sha"
require_output_contains "$output" "candidate_reproducibility_transcript_sha256=$reproducibility_sha"
require_output_contains "$output" "candidate_artifact_integrity_review_sha256=$review_sha"
require_output_contains "$output" 'release_artifact_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'release_artifact_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'release_artifact_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --artifact "$artifact" \
  --sha256 "$bad_checksum" \
  --signature "$signature" \
  --public-key "$public_key" \
  --verification "$verification" \
  --reproducibility "$reproducibility" \
  --review "$review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'bad checksum release-artifact evidence unexpectedly passed validation'
fi

if sh "$script" \
  --artifact "$artifact" \
  --sha256 "$checksum" \
  --signature "$signature" \
  --public-key "$public_key" \
  --verification "$verification" \
  --reproducibility "$reproducibility" \
  --review "$review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder release-artifact evidence unexpectedly passed validation'
fi

printf 'production_installer_release_artifact_evidence_intake_validator_contract: ok\n'
