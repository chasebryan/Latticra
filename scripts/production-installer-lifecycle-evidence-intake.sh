#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-lifecycle-evidence-intake.sh \
    --upgrade <path> \
    --rollback <path> \
    --reinstall <path> \
    --upgrade-review <path> \
    --rollback-review <path> \
    --reinstall-review <path> \
    --evidence <path>

Validates a future production-installer lifecycle evidence bundle.
It checks local file presence, lifecycle transcript markers, review evidence
hashes, required evidence fields, and placeholder absence. It does not upgrade,
rollback, reinstall, invoke a package manager, accept evidence, pass promotion,
or mutate the host.
USAGE
}

fail() {
  printf 'production installer lifecycle evidence intake: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_nonempty_file() {
  file="$1"
  require_file "$file"
  [ -s "$file" ] || fail "empty file: $file"
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
    fail "placeholder value is not acceptable in lifecycle evidence"
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

require_digest() {
  digest="$1"
  label="$2"
  printf '%s\n' "$digest" | grep -Eq '^[0-9a-f]{64}$' ||
    fail "invalid sha256 digest for $label"
}

UPGRADE=''
ROLLBACK=''
REINSTALL=''
UPGRADE_REVIEW=''
ROLLBACK_REVIEW=''
REINSTALL_REVIEW=''
EVIDENCE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --upgrade)
      [ "$#" -ge 2 ] || fail 'missing value for --upgrade' 64
      UPGRADE="$2"
      shift 2
      ;;
    --rollback)
      [ "$#" -ge 2 ] || fail 'missing value for --rollback' 64
      ROLLBACK="$2"
      shift 2
      ;;
    --reinstall)
      [ "$#" -ge 2 ] || fail 'missing value for --reinstall' 64
      REINSTALL="$2"
      shift 2
      ;;
    --upgrade-review)
      [ "$#" -ge 2 ] || fail 'missing value for --upgrade-review' 64
      UPGRADE_REVIEW="$2"
      shift 2
      ;;
    --rollback-review)
      [ "$#" -ge 2 ] || fail 'missing value for --rollback-review' 64
      ROLLBACK_REVIEW="$2"
      shift 2
      ;;
    --reinstall-review)
      [ "$#" -ge 2 ] || fail 'missing value for --reinstall-review' 64
      REINSTALL_REVIEW="$2"
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

[ -n "$UPGRADE" ] || fail 'missing --upgrade path' 64
[ -n "$ROLLBACK" ] || fail 'missing --rollback path' 64
[ -n "$REINSTALL" ] || fail 'missing --reinstall path' 64
[ -n "$UPGRADE_REVIEW" ] || fail 'missing --upgrade-review path' 64
[ -n "$ROLLBACK_REVIEW" ] || fail 'missing --rollback-review path' 64
[ -n "$REINSTALL_REVIEW" ] || fail 'missing --reinstall-review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$UPGRADE" "$ROLLBACK" "$REINSTALL" "$UPGRADE_REVIEW" "$ROLLBACK_REVIEW" "$REINSTALL_REVIEW" "$EVIDENCE"
do
  require_nonempty_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_LIFECYCLE_VALIDATION_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-lifecycle-validation-status.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'production_installer_lifecycle_validation_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_lifecycle_validation_status_no_effect=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_upgrade_path_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_rollback_path_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_downgrade_or_rollback_path_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_reinstall_idempotence_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect installer lifecycle validation status contract' docs/PRODUCTION_INSTALLER_LIFECYCLE_VALIDATION_STATUS_CONTRACT.md
require_contains 'transcript_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

require_contains 'LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN UPGRADE TRANSCRIPT' "$UPGRADE"
require_contains 'production_installer_lifecycle_validation_performed=1' "$UPGRADE"
require_contains 'upgrade_transcript_present=1' "$UPGRADE"
require_contains 'upgrade_performed=0' "$UPGRADE"
require_contains 'package_manager_invoked=0' "$UPGRADE"
require_contains 'host_mutation_performed=0' "$UPGRADE"
require_contains 'network_allowed=0' "$UPGRADE"

require_contains 'LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN ROLLBACK TRANSCRIPT' "$ROLLBACK"
require_contains 'production_installer_lifecycle_validation_performed=1' "$ROLLBACK"
require_contains 'rollback_transcript_present=1' "$ROLLBACK"
require_contains 'rollback_performed=0' "$ROLLBACK"
require_contains 'package_manager_invoked=0' "$ROLLBACK"
require_contains 'host_mutation_performed=0' "$ROLLBACK"
require_contains 'network_allowed=0' "$ROLLBACK"

require_contains 'LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN REINSTALL TRANSCRIPT' "$REINSTALL"
require_contains 'production_installer_lifecycle_validation_performed=1' "$REINSTALL"
require_contains 'reinstall_transcript_present=1' "$REINSTALL"
require_contains 'reinstall_performed=0' "$REINSTALL"
require_contains 'package_manager_invoked=0' "$REINSTALL"
require_contains 'host_mutation_performed=0' "$REINSTALL"
require_contains 'network_allowed=0' "$REINSTALL"

upgrade_sha256="$(sha256_file "$UPGRADE")"
rollback_sha256="$(sha256_file "$ROLLBACK")"
reinstall_sha256="$(sha256_file "$REINSTALL")"
upgrade_review_sha256="$(sha256_file "$UPGRADE_REVIEW")"
rollback_review_sha256="$(sha256_file "$ROLLBACK_REVIEW")"
reinstall_review_sha256="$(sha256_file "$REINSTALL_REVIEW")"

require_digest "$upgrade_sha256" 'upgrade transcript'
require_digest "$rollback_sha256" 'rollback transcript'
require_digest "$reinstall_sha256" 'reinstall transcript'
require_digest "$upgrade_review_sha256" 'upgrade transcript review'
require_digest "$rollback_review_sha256" 'rollback transcript review'
require_digest "$reinstall_review_sha256" 'reinstall transcript review'

for marker in \
  'LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE' \
  'lifecycle_evidence_status=complete' \
  'production_installer_lifecycle_validation_performed=1' \
  'installer_upgrade_candidate_present=1' \
  'installer_rollback_candidate_present=1' \
  'installer_reinstall_candidate_present=1' \
  'upgrade_transcript_present=1' \
  'rollback_transcript_present=1' \
  'reinstall_transcript_present=1' \
  'upgrade_transcript_reviewed=1' \
  'rollback_transcript_reviewed=1' \
  'reinstall_transcript_reviewed=1' \
  'installer_upgrade_path_validated=1' \
  'installer_rollback_path_validated=1' \
  'installer_downgrade_or_rollback_path_validated=1' \
  'installer_reinstall_idempotence_validated=1' \
  "upgrade_transcript_sha256=$upgrade_sha256" \
  "rollback_transcript_sha256=$rollback_sha256" \
  "reinstall_transcript_sha256=$reinstall_sha256" \
  "upgrade_transcript_review_sha256=$upgrade_review_sha256" \
  "rollback_transcript_review_sha256=$rollback_review_sha256" \
  "reinstall_transcript_review_sha256=$reinstall_review_sha256" \
  'upgrade_performed=0' \
  'rollback_performed=0' \
  'reinstall_performed=0' \
  'package_manager_invoked=0' \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0' \
  'network_allowed=0'
do
  require_contains "$marker" "$EVIDENCE"
done

reject_placeholders "$EVIDENCE"

for forbidden_claim in \
  'lifecycle_evidence_accepted_by_intake_validator=1' \
  'lifecycle_evidence_written_by_intake_validator=1' \
  'installer_lifecycle_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'upgrade_performed=1' \
  'rollback_performed=1' \
  'reinstall_performed=1' \
  'package_manager_invoked=1' \
  'host_mutation_performed=1' \
  'network_allowed=1'
do
  require_absent "$forbidden_claim" "$EVIDENCE"
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
lifecycle_evidence_intake_validator_present=1
lifecycle_evidence_intake_validation_mode=no-effect-validation
lifecycle_evidence_candidate_valid=1
upgrade_transcript_file_present=1
rollback_transcript_file_present=1
reinstall_transcript_file_present=1
upgrade_transcript_sha256_recorded=1
rollback_transcript_sha256_recorded=1
reinstall_transcript_sha256_recorded=1
candidate_upgrade_transcript_sha256=$upgrade_sha256
candidate_rollback_transcript_sha256=$rollback_sha256
candidate_reinstall_transcript_sha256=$reinstall_sha256
candidate_upgrade_transcript_review_sha256=$upgrade_review_sha256
candidate_rollback_transcript_review_sha256=$rollback_review_sha256
candidate_reinstall_transcript_review_sha256=$reinstall_review_sha256
candidate_production_installer_lifecycle_validation_performed=1
candidate_upgrade_transcript_reviewed=1
candidate_rollback_transcript_reviewed=1
candidate_reinstall_transcript_reviewed=1
candidate_installer_upgrade_path_validated=1
candidate_installer_rollback_path_validated=1
candidate_installer_downgrade_or_rollback_path_validated=1
candidate_installer_reinstall_idempotence_validated=1
lifecycle_evidence_accepted_by_intake_validator=0
lifecycle_evidence_written_by_intake_validator=0
installer_lifecycle_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_downgrade_or_rollback_path_validated=0
installer_reinstall_idempotence_validated=0
upgrade_performed=0
rollback_performed=0
reinstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
