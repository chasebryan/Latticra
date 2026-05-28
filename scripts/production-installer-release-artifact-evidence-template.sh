#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-artifact-evidence-template.sh \
    [--artifact <path>] \
    [--sha256 <path>] \
    [--signature <path>] \
    [--public-key <path>] \
    [--verification <path>] \
    [--reproducibility <path>] \
    [--review <path>] \
    [--evidence <path>]

Prints a no-effect template for a future production-installer release-artifact
evidence bundle. It does not create artifacts, calculate release hashes, sign,
verify, write evidence files, accept evidence, pass promotion, publish, install,
invoke package managers, use network access, or mutate the host.
USAGE
}

fail() {
  printf 'production installer release artifact evidence template: %s\n' "$1" >&2
  exit "${2:-1}"
}

presence() {
  if [ -f "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

ARTIFACT='artifacts/release/latticra-production-installer.rpm'
CHECKSUM='artifacts/release/latticra-production-installer.rpm.sha256'
SIGNATURE='artifacts/release/latticra-production-installer.rpm.sig'
PUBLIC_KEY='artifacts/release/latticra-release-public-key.asc'
VERIFICATION='artifacts/release/latticra-production-installer-signature-verification.txt'
REPRODUCIBILITY='artifacts/release/latticra-production-installer-reproducibility.txt'
REVIEW='artifacts/release/latticra-production-installer-artifact-integrity-review.txt'
EVIDENCE='artifacts/release/latticra-production-installer-release-artifact-evidence.txt'

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

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_evidence_status=complete' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'Production quality blocker ledger' README.md

cat <<TEMPLATE
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE TEMPLATE
template_status=ok
release_artifact_evidence_template_present=1
release_artifact_evidence_template_mode=no-effect-template
release_artifact_evidence_template_decision=blocked-template-only-no-evidence-write
release_artifact_evidence_template_complete=0
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_intake_validation_mode=no-effect-validation
release_artifact_evidence_path=$EVIDENCE
release_artifact_candidate_path=$ARTIFACT
release_artifact_checksum_path=$CHECKSUM
release_artifact_signature_path=$SIGNATURE
release_public_key_path=$PUBLIC_KEY
signature_verification_transcript_path=$VERIFICATION
reproducibility_transcript_path=$REPRODUCIBILITY
artifact_integrity_review_path=$REVIEW
release_artifact_candidate_file_present=$(presence "$ARTIFACT")
release_artifact_checksum_file_present=$(presence "$CHECKSUM")
release_artifact_signature_file_present=$(presence "$SIGNATURE")
release_public_key_file_present=$(presence "$PUBLIC_KEY")
signature_verification_transcript_file_present=$(presence "$VERIFICATION")
reproducibility_transcript_file_present=$(presence "$REPRODUCIBILITY")
artifact_integrity_review_file_present=$(presence "$REVIEW")

[required_evidence_fields]
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
artifact_sha256=<required-artifact-sha256>
artifact_signature_sha256=<required-signature-sha256>
release_public_key_sha256=<required-public-key-sha256>
signature_verification_transcript_sha256=<required-verification-transcript-sha256>
reproducibility_transcript_sha256=<required-reproducibility-transcript-sha256>
artifact_integrity_review_sha256=<required-review-sha256>
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0

[template_non_effects]
release_artifact_evidence_written_by_template=0
release_artifact_evidence_accepted_by_template=0
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
release_artifact_created=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
artifact_signed=0
signature_verified=0
artifact_published=0
install_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
TEMPLATE
