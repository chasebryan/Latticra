#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-artifact-evidence-intake.sh \
    --artifact <path> \
    --sha256 <path> \
    --signature <path> \
    --public-key <path> \
    --verification <path> \
    --reproducibility <path> \
    --review <path> \
    --evidence <path>

Validates a future production-installer release-artifact evidence bundle.
It checks local file presence, checksum consistency, required evidence markers,
and placeholder absence. It does not build, sign, publish, install, accept
evidence, pass promotion, or mutate the host.
USAGE
}

fail() {
  printf 'production installer release artifact evidence intake: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in release artifact evidence"
  fi
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

first_checksum_field() {
  file="$1"
  line="$(sed -n '/^[[:space:]]*#/d; /^[[:space:]]*$/d; p; q' "$file")"
  [ -n "$line" ] || fail "empty checksum file: $file"
  set -- $line
  printf '%s\n' "$1" | tr 'A-F' 'a-f'
}

require_digest() {
  digest="$1"
  label="$2"
  printf '%s\n' "$digest" | grep -Eq '^[0-9a-f]{64}$' ||
    fail "invalid sha256 digest for $label"
}

ARTIFACT=''
CHECKSUM=''
SIGNATURE=''
PUBLIC_KEY=''
VERIFICATION=''
REPRODUCIBILITY=''
REVIEW=''
EVIDENCE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --artifact)
      [ "$#" -ge 2 ] || fail 'missing value for --artifact' 64
      ARTIFACT="$2"
      shift 2
      ;;
    --sha256)
      [ "$#" -ge 2 ] || fail 'missing value for --sha256' 64
      CHECKSUM="$2"
      shift 2
      ;;
    --signature)
      [ "$#" -ge 2 ] || fail 'missing value for --signature' 64
      SIGNATURE="$2"
      shift 2
      ;;
    --public-key)
      [ "$#" -ge 2 ] || fail 'missing value for --public-key' 64
      PUBLIC_KEY="$2"
      shift 2
      ;;
    --verification)
      [ "$#" -ge 2 ] || fail 'missing value for --verification' 64
      VERIFICATION="$2"
      shift 2
      ;;
    --reproducibility)
      [ "$#" -ge 2 ] || fail 'missing value for --reproducibility' 64
      REPRODUCIBILITY="$2"
      shift 2
      ;;
    --review)
      [ "$#" -ge 2 ] || fail 'missing value for --review' 64
      REVIEW="$2"
      shift 2
      ;;
    --evidence)
      [ "$#" -ge 2 ] || fail 'missing value for --evidence' 64
      EVIDENCE="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

[ -n "$ARTIFACT" ] || fail 'missing --artifact path' 64
[ -n "$CHECKSUM" ] || fail 'missing --sha256 path' 64
[ -n "$SIGNATURE" ] || fail 'missing --signature path' 64
[ -n "$PUBLIC_KEY" ] || fail 'missing --public-key path' 64
[ -n "$VERIFICATION" ] || fail 'missing --verification path' 64
[ -n "$REPRODUCIBILITY" ] || fail 'missing --reproducibility path' 64
[ -n "$REVIEW" ] || fail 'missing --review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$ARTIFACT" "$CHECKSUM" "$SIGNATURE" "$PUBLIC_KEY" "$VERIFICATION" "$REPRODUCIBILITY" "$REVIEW" "$EVIDENCE"
do
  require_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-artifact-integrity-status.sh
require_file scripts/production-installer-release-artifact-promotion-gate.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'artifact_integrity_status_present=1' docs/PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

expected_artifact_sha256="$(first_checksum_field "$CHECKSUM")"
actual_artifact_sha256="$(sha256_file "$ARTIFACT")"
signature_sha256="$(sha256_file "$SIGNATURE")"
public_key_sha256="$(sha256_file "$PUBLIC_KEY")"
verification_sha256="$(sha256_file "$VERIFICATION")"
reproducibility_sha256="$(sha256_file "$REPRODUCIBILITY")"
review_sha256="$(sha256_file "$REVIEW")"

require_digest "$expected_artifact_sha256" 'checksum file'
require_digest "$actual_artifact_sha256" 'artifact'
require_digest "$signature_sha256" 'signature'
require_digest "$public_key_sha256" 'public key'
require_digest "$verification_sha256" 'signature verification transcript'
require_digest "$reproducibility_sha256" 'reproducibility transcript'
require_digest "$review_sha256" 'artifact integrity review'

[ "$actual_artifact_sha256" = "$expected_artifact_sha256" ] ||
  fail 'artifact checksum mismatch'

for marker in \
  'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE' \
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
  "artifact_sha256=$actual_artifact_sha256" \
  "artifact_signature_sha256=$signature_sha256" \
  "release_public_key_sha256=$public_key_sha256" \
  "signature_verification_transcript_sha256=$verification_sha256" \
  "reproducibility_transcript_sha256=$reproducibility_sha256" \
  "artifact_integrity_review_sha256=$review_sha256" \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$marker" "$EVIDENCE"
done

reject_placeholders "$EVIDENCE"

for forbidden_claim in \
  'release_artifact_evidence_accepted_by_intake_validator=1' \
  'release_artifact_evidence_written_by_intake_validator=1' \
  'release_artifact_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'host_mutation_performed=1'
do
  require_absent "$forbidden_claim" "$EVIDENCE"
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_intake_validation_mode=no-effect-validation
release_artifact_candidate_valid=1
release_artifact_checksum_file_present=1
release_artifact_sha256_matches=1
release_artifact_signature_file_present=1
release_public_key_file_present=1
signature_verification_transcript_present=1
reproducibility_transcript_present=1
artifact_integrity_review_present=1
candidate_release_artifact_path=$ARTIFACT
candidate_release_artifact_sha256=$actual_artifact_sha256
candidate_artifact_signature_sha256=$signature_sha256
candidate_release_public_key_sha256=$public_key_sha256
candidate_signature_verification_transcript_sha256=$verification_sha256
candidate_reproducibility_transcript_sha256=$reproducibility_sha256
candidate_artifact_integrity_review_sha256=$review_sha256
candidate_release_artifact_present=1
candidate_release_artifact_built_from_tag=1
candidate_release_artifact_reproducible=1
candidate_release_artifact_signature_present=1
candidate_release_artifact_signature_verified=1
candidate_release_public_key_documented=1
candidate_signature_verification_documented=1
candidate_artifact_integrity_reviewed=1
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
REPORT
