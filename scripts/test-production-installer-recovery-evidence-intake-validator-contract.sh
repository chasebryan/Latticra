#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer recovery evidence intake validator contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-recovery-evidence-intake.sh'
test_script='scripts/test-production-installer-recovery-evidence-intake-validator-contract.sh'
recovery_status='docs/PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md'
lifecycle_intake='docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
transcript_intake='docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-recovery-evidence-intake-validator.yml'
installer_page='docs/installer.html'

for file in "$doc" "$status" "$script" "$test_script" "$recovery_status" "$lifecycle_intake" "$transcript_intake" "$readiness" "$promotion_gate" "$ledger" "$index" "$workflow" "$installer_page" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect recovery evidence intake validator contract' "$doc"
require_contains 'recovery_evidence_intake_validator_present=1' "$doc"
require_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'recovery_evidence_candidate_valid=0' "$doc"
require_contains 'recovery_runbook_file_present=0' "$doc"
require_contains 'failure_mode_register_file_present=0' "$doc"
require_contains 'recovery_drill_transcript_file_present=0' "$doc"
require_contains 'rollback_drill_transcript_file_present=0' "$doc"
require_contains 'operator_recovery_receipt_file_present=0' "$doc"
require_contains 'recovery_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'recovery_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_recovery_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'installer_failure_mode_documented=0' "$doc"
require_contains 'installer_recovery_runbook_present=0' "$doc"
require_contains 'installer_recovery_runbook_reviewed=0' "$doc"
require_contains 'installer_recovery_drill_validated=0' "$doc"
require_contains 'installer_rollback_drill_validated=0' "$doc"
require_contains 'installer_failure_mode_evidence_recorded=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-recovery-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-recovery-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'recovery_evidence_candidate_valid=1' "$script"
require_contains 'candidate_installer_failure_mode_documented=1' "$script"
require_contains 'candidate_installer_recovery_runbook_present=1' "$script"
require_contains 'candidate_installer_recovery_drill_validated=1' "$script"
require_contains 'candidate_installer_rollback_drill_validated=1' "$script"
require_contains 'candidate_installer_failure_mode_evidence_recorded=1' "$script"
require_contains 'recovery_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'recovery_evidence_written_by_intake_validator=0' "$script"
require_contains 'installer_recovery_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'placeholder value is not acceptable in recovery evidence' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'recovery_evidence_intake_validator_present=1' \
  'recovery_evidence_intake_validation_mode=no-effect-validation' \
  'recovery_evidence_candidate_valid=0' \
  'recovery_runbook_file_present=0' \
  'failure_mode_register_file_present=0' \
  'recovery_drill_transcript_file_present=0' \
  'rollback_drill_transcript_file_present=0' \
  'operator_recovery_receipt_file_present=0' \
  'recovery_runbook_sha256_recorded=0' \
  'failure_mode_register_sha256_recorded=0' \
  'recovery_drill_transcript_sha256_recorded=0' \
  'rollback_drill_transcript_sha256_recorded=0' \
  'operator_recovery_receipt_sha256_recorded=0' \
  'recovery_runbook_review_present=0' \
  'failure_mode_register_review_present=0' \
  'recovery_drill_review_present=0' \
  'rollback_drill_review_present=0' \
  'operator_recovery_receipt_review_present=0' \
  'recovery_evidence_accepted_by_intake_validator=0' \
  'recovery_evidence_written_by_intake_validator=0' \
  'installer_recovery_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'installer_failure_mode_documented=0' \
  'installer_recovery_runbook_present=0' \
  'installer_recovery_runbook_reviewed=0' \
  'installer_recovery_drill_validated=0' \
  'installer_rollback_drill_validated=0' \
  'installer_failure_mode_evidence_recorded=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$recovery_status"
done

for future_field in \
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
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$status"
  require_contains "$future_field" "$script"
done

require_contains 'PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'recovery_evidence_intake_validator_present=1' "$readiness"
require_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'recovery_evidence_candidate_valid=0' "$readiness"
require_contains 'recovery_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'recovery_evidence_intake_validator_present=1' "$ledger"
require_contains 'recovery_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md
require_contains 'recovery_evidence_intake_validator' "$installer_page"

require_contains 'production-installer-recovery-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-recovery-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer Recovery Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-recovery-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-recovery-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-recovery-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

runbook="$tmp/recovery-runbook.md"
failure_register="$tmp/failure-mode-register.txt"
recovery_drill="$tmp/recovery-drill-transcript.txt"
rollback_drill="$tmp/rollback-drill-transcript.txt"
operator_receipt="$tmp/operator-recovery-receipt.txt"
bad_runbook="$tmp/bad-recovery-runbook.md"
runbook_review="$tmp/recovery-runbook-review.txt"
failure_register_review="$tmp/failure-mode-register-review.txt"
recovery_drill_review="$tmp/recovery-drill-review.txt"
rollback_drill_review="$tmp/rollback-drill-review.txt"
operator_receipt_review="$tmp/operator-recovery-receipt-review.txt"
valid_evidence="$tmp/recovery-evidence.txt"
bad_hash_evidence="$tmp/recovery-bad-hash-evidence.txt"
placeholder_evidence="$tmp/recovery-placeholder-evidence.txt"

cat >"$runbook" <<'RECOVERY_RUNBOOK'
LATTICRA PRODUCTION INSTALLER RECOVERY RUNBOOK
recovery_runbook_present=1
installer_recovery_runbook_present=1
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
RECOVERY_RUNBOOK

cat >"$failure_register" <<'FAILURE_REGISTER'
LATTICRA PRODUCTION INSTALLER FAILURE-MODE REGISTER
failure_mode_register_present=1
installer_failure_mode_documented=1
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
FAILURE_REGISTER

cat >"$recovery_drill" <<'RECOVERY_DRILL'
LATTICRA PRODUCTION INSTALLER RECOVERY DRILL TRANSCRIPT
recovery_drill_transcript_present=1
installer_recovery_drill_validated=1
recovery_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
RECOVERY_DRILL

cat >"$rollback_drill" <<'ROLLBACK_DRILL'
LATTICRA PRODUCTION INSTALLER ROLLBACK DRILL TRANSCRIPT
rollback_drill_transcript_present=1
installer_rollback_drill_validated=1
rollback_drill_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
ROLLBACK_DRILL

cat >"$operator_receipt" <<'OPERATOR_RECEIPT'
LATTICRA PRODUCTION INSTALLER OPERATOR RECOVERY RECEIPT
operator_recovery_receipt_present=1
installer_failure_mode_evidence_recorded=1
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
OPERATOR_RECEIPT

printf 'missing required recovery runbook markers\n' >"$bad_runbook"
printf 'recovery runbook review fixture\n' >"$runbook_review"
printf 'failure-mode register review fixture\n' >"$failure_register_review"
printf 'recovery drill review fixture\n' >"$recovery_drill_review"
printf 'rollback drill review fixture\n' >"$rollback_drill_review"
printf 'operator recovery receipt review fixture\n' >"$operator_receipt_review"

runbook_sha="$(sha256_file "$runbook")"
failure_register_sha="$(sha256_file "$failure_register")"
recovery_drill_sha="$(sha256_file "$recovery_drill")"
rollback_drill_sha="$(sha256_file "$rollback_drill")"
operator_receipt_sha="$(sha256_file "$operator_receipt")"
runbook_review_sha="$(sha256_file "$runbook_review")"
failure_register_review_sha="$(sha256_file "$failure_register_review")"
recovery_drill_review_sha="$(sha256_file "$recovery_drill_review")"
rollback_drill_review_sha="$(sha256_file "$rollback_drill_review")"
operator_receipt_review_sha="$(sha256_file "$operator_receipt_review")"

cat >"$valid_evidence" <<VALID_EVIDENCE
LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE
recovery_evidence_status=complete
recovery_runbook_present=1
failure_mode_register_present=1
recovery_drill_transcript_present=1
rollback_drill_transcript_present=1
operator_recovery_receipt_present=1
recovery_runbook_reviewed=1
failure_mode_register_reviewed=1
recovery_drill_reviewed=1
rollback_drill_reviewed=1
operator_recovery_receipt_reviewed=1
installer_failure_mode_documented=1
installer_recovery_runbook_present=1
installer_recovery_runbook_reviewed=1
installer_recovery_drill_validated=1
installer_rollback_drill_validated=1
installer_failure_mode_evidence_recorded=1
recovery_runbook_sha256=$runbook_sha
failure_mode_register_sha256=$failure_register_sha
recovery_drill_transcript_sha256=$recovery_drill_sha
rollback_drill_transcript_sha256=$rollback_drill_sha
operator_recovery_receipt_sha256=$operator_receipt_sha
recovery_runbook_review_sha256=$runbook_review_sha
failure_mode_register_review_sha256=$failure_register_review_sha
recovery_drill_review_sha256=$recovery_drill_review_sha
rollback_drill_review_sha256=$rollback_drill_review_sha
operator_recovery_receipt_review_sha256=$operator_receipt_review_sha
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
VALID_EVIDENCE

sed "s/$runbook_sha/0000000000000000000000000000000000000000000000000000000000000000/" "$valid_evidence" >"$bad_hash_evidence"
cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'recovery_runbook_review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --runbook "$runbook" \
  --failure-register "$failure_register" \
  --recovery-drill "$recovery_drill" \
  --rollback-drill "$rollback_drill" \
  --operator-receipt "$operator_receipt" \
  --runbook-review "$runbook_review" \
  --failure-register-review "$failure_register_review" \
  --recovery-drill-review "$recovery_drill_review" \
  --rollback-drill-review "$rollback_drill_review" \
  --operator-receipt-review "$operator_receipt_review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'recovery_evidence_intake_validator_present=1'
require_output_contains "$output" 'recovery_evidence_candidate_valid=1'
require_output_contains "$output" "candidate_recovery_runbook_sha256=$runbook_sha"
require_output_contains "$output" "candidate_failure_mode_register_sha256=$failure_register_sha"
require_output_contains "$output" "candidate_recovery_drill_transcript_sha256=$recovery_drill_sha"
require_output_contains "$output" "candidate_rollback_drill_transcript_sha256=$rollback_drill_sha"
require_output_contains "$output" "candidate_operator_recovery_receipt_sha256=$operator_receipt_sha"
require_output_contains "$output" "candidate_recovery_runbook_review_sha256=$runbook_review_sha"
require_output_contains "$output" "candidate_failure_mode_register_review_sha256=$failure_register_review_sha"
require_output_contains "$output" "candidate_recovery_drill_review_sha256=$recovery_drill_review_sha"
require_output_contains "$output" "candidate_rollback_drill_review_sha256=$rollback_drill_review_sha"
require_output_contains "$output" "candidate_operator_recovery_receipt_review_sha256=$operator_receipt_review_sha"
require_output_contains "$output" 'recovery_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'recovery_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'installer_recovery_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'installer_failure_mode_documented=0'
require_output_contains "$output" 'installer_recovery_runbook_present=0'
require_output_contains "$output" 'installer_recovery_drill_validated=0'
require_output_contains "$output" 'installer_rollback_drill_validated=0'
require_output_contains "$output" 'installer_failure_mode_evidence_recorded=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --runbook "$bad_runbook" \
  --failure-register "$failure_register" \
  --recovery-drill "$recovery_drill" \
  --rollback-drill "$rollback_drill" \
  --operator-receipt "$operator_receipt" \
  --runbook-review "$runbook_review" \
  --failure-register-review "$failure_register_review" \
  --recovery-drill-review "$recovery_drill_review" \
  --rollback-drill-review "$rollback_drill_review" \
  --operator-receipt-review "$operator_receipt_review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'bad recovery runbook evidence unexpectedly passed validation'
fi

if sh "$script" \
  --runbook "$runbook" \
  --failure-register "$failure_register" \
  --recovery-drill "$recovery_drill" \
  --rollback-drill "$rollback_drill" \
  --operator-receipt "$operator_receipt" \
  --runbook-review "$runbook_review" \
  --failure-register-review "$failure_register_review" \
  --recovery-drill-review "$recovery_drill_review" \
  --rollback-drill-review "$rollback_drill_review" \
  --operator-receipt-review "$operator_receipt_review" \
  --evidence "$bad_hash_evidence" >/dev/null 2>&1; then
  fail 'bad-hash recovery evidence unexpectedly passed validation'
fi

if sh "$script" \
  --runbook "$runbook" \
  --failure-register "$failure_register" \
  --recovery-drill "$recovery_drill" \
  --rollback-drill "$rollback_drill" \
  --operator-receipt "$operator_receipt" \
  --runbook-review "$runbook_review" \
  --failure-register-review "$failure_register_review" \
  --recovery-drill-review "$recovery_drill_review" \
  --rollback-drill-review "$rollback_drill_review" \
  --operator-receipt-review "$operator_receipt_review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder recovery evidence unexpectedly passed validation'
fi

printf 'production_installer_recovery_evidence_intake_validator_contract: ok\n'
