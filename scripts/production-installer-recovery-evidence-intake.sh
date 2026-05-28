#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-recovery-evidence-intake.sh \
    --runbook <path> \
    --failure-register <path> \
    --recovery-drill <path> \
    --rollback-drill <path> \
    --operator-receipt <path> \
    --runbook-review <path> \
    --failure-register-review <path> \
    --recovery-drill-review <path> \
    --rollback-drill-review <path> \
    --operator-receipt-review <path> \
    --evidence <path>

Validates a future production-installer recovery evidence bundle.
It checks local file presence, recovery evidence markers, review hashes,
required evidence fields, and placeholder absence. It does not recover,
rollback, invoke a package manager, accept evidence, pass promotion, or mutate
the host.
USAGE
}

fail() {
  printf 'production installer recovery evidence intake: %s\n' "$1" >&2
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
    fail "placeholder value is not acceptable in recovery evidence"
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

RUNBOOK=''
FAILURE_REGISTER=''
RECOVERY_DRILL=''
ROLLBACK_DRILL=''
OPERATOR_RECEIPT=''
RUNBOOK_REVIEW=''
FAILURE_REGISTER_REVIEW=''
RECOVERY_DRILL_REVIEW=''
ROLLBACK_DRILL_REVIEW=''
OPERATOR_RECEIPT_REVIEW=''
EVIDENCE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --runbook)
      [ "$#" -ge 2 ] || fail 'missing value for --runbook' 64
      RUNBOOK="$2"
      shift 2
      ;;
    --failure-register)
      [ "$#" -ge 2 ] || fail 'missing value for --failure-register' 64
      FAILURE_REGISTER="$2"
      shift 2
      ;;
    --recovery-drill)
      [ "$#" -ge 2 ] || fail 'missing value for --recovery-drill' 64
      RECOVERY_DRILL="$2"
      shift 2
      ;;
    --rollback-drill)
      [ "$#" -ge 2 ] || fail 'missing value for --rollback-drill' 64
      ROLLBACK_DRILL="$2"
      shift 2
      ;;
    --operator-receipt)
      [ "$#" -ge 2 ] || fail 'missing value for --operator-receipt' 64
      OPERATOR_RECEIPT="$2"
      shift 2
      ;;
    --runbook-review)
      [ "$#" -ge 2 ] || fail 'missing value for --runbook-review' 64
      RUNBOOK_REVIEW="$2"
      shift 2
      ;;
    --failure-register-review)
      [ "$#" -ge 2 ] || fail 'missing value for --failure-register-review' 64
      FAILURE_REGISTER_REVIEW="$2"
      shift 2
      ;;
    --recovery-drill-review)
      [ "$#" -ge 2 ] || fail 'missing value for --recovery-drill-review' 64
      RECOVERY_DRILL_REVIEW="$2"
      shift 2
      ;;
    --rollback-drill-review)
      [ "$#" -ge 2 ] || fail 'missing value for --rollback-drill-review' 64
      ROLLBACK_DRILL_REVIEW="$2"
      shift 2
      ;;
    --operator-receipt-review)
      [ "$#" -ge 2 ] || fail 'missing value for --operator-receipt-review' 64
      OPERATOR_RECEIPT_REVIEW="$2"
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

[ -n "$RUNBOOK" ] || fail 'missing --runbook path' 64
[ -n "$FAILURE_REGISTER" ] || fail 'missing --failure-register path' 64
[ -n "$RECOVERY_DRILL" ] || fail 'missing --recovery-drill path' 64
[ -n "$ROLLBACK_DRILL" ] || fail 'missing --rollback-drill path' 64
[ -n "$OPERATOR_RECEIPT" ] || fail 'missing --operator-receipt path' 64
[ -n "$RUNBOOK_REVIEW" ] || fail 'missing --runbook-review path' 64
[ -n "$FAILURE_REGISTER_REVIEW" ] || fail 'missing --failure-register-review path' 64
[ -n "$RECOVERY_DRILL_REVIEW" ] || fail 'missing --recovery-drill-review path' 64
[ -n "$ROLLBACK_DRILL_REVIEW" ] || fail 'missing --rollback-drill-review path' 64
[ -n "$OPERATOR_RECEIPT_REVIEW" ] || fail 'missing --operator-receipt-review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$RUNBOOK" "$FAILURE_REGISTER" "$RECOVERY_DRILL" "$ROLLBACK_DRILL" "$OPERATOR_RECEIPT" "$RUNBOOK_REVIEW" "$FAILURE_REGISTER_REVIEW" "$RECOVERY_DRILL_REVIEW" "$ROLLBACK_DRILL_REVIEW" "$OPERATOR_RECEIPT_REVIEW" "$EVIDENCE"
do
  require_nonempty_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-recovery-failure-mode-status.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'production_installer_recovery_failure_mode_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_recovery_failure_mode_status_no_effect=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'recovery_runbook_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'failure_mode_register_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'recovery_drill_transcript_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'rollback_drill_transcript_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'operator_recovery_receipt_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'recovery_runbook_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'failure_mode_register_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'recovery_drill_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'rollback_drill_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'operator_recovery_receipt_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_failure_mode_documented=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_recovery_runbook_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_recovery_runbook_reviewed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_recovery_drill_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_rollback_drill_validated=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_failure_mode_evidence_recorded=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect installer recovery failure-mode status contract' docs/PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md
require_contains 'lifecycle_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'transcript_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

require_contains 'LATTICRA PRODUCTION INSTALLER RECOVERY RUNBOOK' "$RUNBOOK"
require_contains 'recovery_runbook_present=1' "$RUNBOOK"
require_contains 'installer_recovery_runbook_present=1' "$RUNBOOK"
require_contains 'package_manager_invoked=0' "$RUNBOOK"
require_contains 'host_mutation_performed=0' "$RUNBOOK"
require_contains 'network_allowed=0' "$RUNBOOK"

require_contains 'LATTICRA PRODUCTION INSTALLER FAILURE-MODE REGISTER' "$FAILURE_REGISTER"
require_contains 'failure_mode_register_present=1' "$FAILURE_REGISTER"
require_contains 'installer_failure_mode_documented=1' "$FAILURE_REGISTER"
require_contains 'package_manager_invoked=0' "$FAILURE_REGISTER"
require_contains 'host_mutation_performed=0' "$FAILURE_REGISTER"
require_contains 'network_allowed=0' "$FAILURE_REGISTER"

require_contains 'LATTICRA PRODUCTION INSTALLER RECOVERY DRILL TRANSCRIPT' "$RECOVERY_DRILL"
require_contains 'recovery_drill_transcript_present=1' "$RECOVERY_DRILL"
require_contains 'installer_recovery_drill_validated=1' "$RECOVERY_DRILL"
require_contains 'recovery_performed=0' "$RECOVERY_DRILL"
require_contains 'package_manager_invoked=0' "$RECOVERY_DRILL"
require_contains 'host_mutation_performed=0' "$RECOVERY_DRILL"
require_contains 'network_allowed=0' "$RECOVERY_DRILL"

require_contains 'LATTICRA PRODUCTION INSTALLER ROLLBACK DRILL TRANSCRIPT' "$ROLLBACK_DRILL"
require_contains 'rollback_drill_transcript_present=1' "$ROLLBACK_DRILL"
require_contains 'installer_rollback_drill_validated=1' "$ROLLBACK_DRILL"
require_contains 'rollback_drill_performed=0' "$ROLLBACK_DRILL"
require_contains 'package_manager_invoked=0' "$ROLLBACK_DRILL"
require_contains 'host_mutation_performed=0' "$ROLLBACK_DRILL"
require_contains 'network_allowed=0' "$ROLLBACK_DRILL"

require_contains 'LATTICRA PRODUCTION INSTALLER OPERATOR RECOVERY RECEIPT' "$OPERATOR_RECEIPT"
require_contains 'operator_recovery_receipt_present=1' "$OPERATOR_RECEIPT"
require_contains 'installer_failure_mode_evidence_recorded=1' "$OPERATOR_RECEIPT"
require_contains 'package_manager_invoked=0' "$OPERATOR_RECEIPT"
require_contains 'host_mutation_performed=0' "$OPERATOR_RECEIPT"
require_contains 'network_allowed=0' "$OPERATOR_RECEIPT"

runbook_sha256="$(sha256_file "$RUNBOOK")"
failure_register_sha256="$(sha256_file "$FAILURE_REGISTER")"
recovery_drill_sha256="$(sha256_file "$RECOVERY_DRILL")"
rollback_drill_sha256="$(sha256_file "$ROLLBACK_DRILL")"
operator_receipt_sha256="$(sha256_file "$OPERATOR_RECEIPT")"
runbook_review_sha256="$(sha256_file "$RUNBOOK_REVIEW")"
failure_register_review_sha256="$(sha256_file "$FAILURE_REGISTER_REVIEW")"
recovery_drill_review_sha256="$(sha256_file "$RECOVERY_DRILL_REVIEW")"
rollback_drill_review_sha256="$(sha256_file "$ROLLBACK_DRILL_REVIEW")"
operator_receipt_review_sha256="$(sha256_file "$OPERATOR_RECEIPT_REVIEW")"

require_digest "$runbook_sha256" 'recovery runbook'
require_digest "$failure_register_sha256" 'failure-mode register'
require_digest "$recovery_drill_sha256" 'recovery drill transcript'
require_digest "$rollback_drill_sha256" 'rollback drill transcript'
require_digest "$operator_receipt_sha256" 'operator recovery receipt'
require_digest "$runbook_review_sha256" 'recovery runbook review'
require_digest "$failure_register_review_sha256" 'failure-mode register review'
require_digest "$recovery_drill_review_sha256" 'recovery drill review'
require_digest "$rollback_drill_review_sha256" 'rollback drill review'
require_digest "$operator_receipt_review_sha256" 'operator recovery receipt review'

for marker in \
  'LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE' \
  'recovery_evidence_status=complete' \
  'recovery_runbook_present=1' \
  'failure_mode_register_present=1' \
  'recovery_drill_transcript_present=1' \
  'rollback_drill_transcript_present=1' \
  'operator_recovery_receipt_present=1' \
  'recovery_runbook_reviewed=1' \
  'failure_mode_register_reviewed=1' \
  'recovery_drill_reviewed=1' \
  'rollback_drill_reviewed=1' \
  'operator_recovery_receipt_reviewed=1' \
  'installer_failure_mode_documented=1' \
  'installer_recovery_runbook_present=1' \
  'installer_recovery_runbook_reviewed=1' \
  'installer_recovery_drill_validated=1' \
  'installer_rollback_drill_validated=1' \
  'installer_failure_mode_evidence_recorded=1' \
  "recovery_runbook_sha256=$runbook_sha256" \
  "failure_mode_register_sha256=$failure_register_sha256" \
  "recovery_drill_transcript_sha256=$recovery_drill_sha256" \
  "rollback_drill_transcript_sha256=$rollback_drill_sha256" \
  "operator_recovery_receipt_sha256=$operator_receipt_sha256" \
  "recovery_runbook_review_sha256=$runbook_review_sha256" \
  "failure_mode_register_review_sha256=$failure_register_review_sha256" \
  "recovery_drill_review_sha256=$recovery_drill_review_sha256" \
  "rollback_drill_review_sha256=$rollback_drill_review_sha256" \
  "operator_recovery_receipt_review_sha256=$operator_receipt_review_sha256" \
  'package_manager_invoked=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$marker" "$EVIDENCE"
done

for file in "$RUNBOOK" "$FAILURE_REGISTER" "$RECOVERY_DRILL" "$ROLLBACK_DRILL" "$OPERATOR_RECEIPT" "$RUNBOOK_REVIEW" "$FAILURE_REGISTER_REVIEW" "$RECOVERY_DRILL_REVIEW" "$ROLLBACK_DRILL_REVIEW" "$OPERATOR_RECEIPT_REVIEW" "$EVIDENCE"
do
  reject_placeholders "$file"
done

for forbidden_claim in \
  'recovery_evidence_accepted_by_intake_validator=1' \
  'recovery_evidence_written_by_intake_validator=1' \
  'installer_recovery_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'recovery_performed=1' \
  'rollback_drill_performed=1' \
  'package_manager_invoked=1' \
  'host_mutation_performed=1' \
  'network_allowed=1'
do
  for file in "$RUNBOOK" "$FAILURE_REGISTER" "$RECOVERY_DRILL" "$ROLLBACK_DRILL" "$OPERATOR_RECEIPT" "$RUNBOOK_REVIEW" "$FAILURE_REGISTER_REVIEW" "$RECOVERY_DRILL_REVIEW" "$ROLLBACK_DRILL_REVIEW" "$OPERATOR_RECEIPT_REVIEW" "$EVIDENCE"
  do
    require_absent "$forbidden_claim" "$file"
  done
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
recovery_evidence_intake_validator_present=1
recovery_evidence_intake_validation_mode=no-effect-validation
recovery_evidence_candidate_valid=1
recovery_runbook_file_present=1
failure_mode_register_file_present=1
recovery_drill_transcript_file_present=1
rollback_drill_transcript_file_present=1
operator_recovery_receipt_file_present=1
recovery_runbook_sha256_recorded=1
failure_mode_register_sha256_recorded=1
recovery_drill_transcript_sha256_recorded=1
rollback_drill_transcript_sha256_recorded=1
operator_recovery_receipt_sha256_recorded=1
candidate_recovery_runbook_sha256=$runbook_sha256
candidate_failure_mode_register_sha256=$failure_register_sha256
candidate_recovery_drill_transcript_sha256=$recovery_drill_sha256
candidate_rollback_drill_transcript_sha256=$rollback_drill_sha256
candidate_operator_recovery_receipt_sha256=$operator_receipt_sha256
candidate_recovery_runbook_review_sha256=$runbook_review_sha256
candidate_failure_mode_register_review_sha256=$failure_register_review_sha256
candidate_recovery_drill_review_sha256=$recovery_drill_review_sha256
candidate_rollback_drill_review_sha256=$rollback_drill_review_sha256
candidate_operator_recovery_receipt_review_sha256=$operator_receipt_review_sha256
candidate_recovery_runbook_reviewed=1
candidate_failure_mode_register_reviewed=1
candidate_recovery_drill_reviewed=1
candidate_rollback_drill_reviewed=1
candidate_operator_recovery_receipt_reviewed=1
candidate_installer_failure_mode_documented=1
candidate_installer_recovery_runbook_present=1
candidate_installer_recovery_runbook_reviewed=1
candidate_installer_recovery_drill_validated=1
candidate_installer_rollback_drill_validated=1
candidate_installer_failure_mode_evidence_recorded=1
recovery_evidence_accepted_by_intake_validator=0
recovery_evidence_written_by_intake_validator=0
installer_recovery_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_failure_mode_documented=0
installer_recovery_runbook_present=0
installer_recovery_runbook_reviewed=0
installer_recovery_drill_validated=0
installer_rollback_drill_validated=0
installer_failure_mode_evidence_recorded=0
recovery_performed=0
rollback_drill_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
