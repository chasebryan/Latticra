#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer recovery failure-mode status contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md'
status_script='scripts/production-installer-recovery-failure-mode-status.sh'
test_script='scripts/test-production-installer-recovery-failure-mode-status-contract.sh'
fixture='fixtures/artifact/local-artifact-manifest.txt'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'

for file in "$doc" "$status_script" "$test_script" "$fixture" "$prod" "$ledger" "$index" "$installer_page" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect installer recovery failure-mode status contract' "$doc"
require_contains 'Evidence level: 10 target, status evidence only' "$doc"
require_contains 'sh scripts/production-installer-recovery-failure-mode-status.sh' "$doc"
require_contains 'production_installer_recovery_failure_mode_status_present=1' "$doc"
require_contains 'installer_failure_mode_status_present=1' "$doc"
require_contains 'installer_recovery_runbook_status_present=1' "$doc"
require_contains 'installer_recovery_drill_status_present=1' "$doc"
require_contains 'installer_recovery_failure_mode_status_no_effect=1' "$doc"
require_contains 'recovery_runbook_present=0' "$doc"
require_contains 'failure_mode_register_present=0' "$doc"
require_contains 'recovery_drill_transcript_present=0' "$doc"
require_contains 'rollback_drill_transcript_present=0' "$doc"
require_contains 'operator_recovery_receipt_present=0' "$doc"
require_contains 'recovery_runbook_reviewed=0' "$doc"
require_contains 'failure_mode_register_reviewed=0' "$doc"
require_contains 'recovery_drill_reviewed=0' "$doc"
require_contains 'rollback_drill_reviewed=0' "$doc"
require_contains 'operator_recovery_receipt_reviewed=0' "$doc"
require_contains 'recovery_evidence_intake_validator_present=1' "$doc"
require_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'recovery_evidence_candidate_valid=0' "$doc"
require_contains 'recovery_runbook_file_present=0' "$doc"
require_contains 'failure_mode_register_file_present=0' "$doc"
require_contains 'recovery_drill_transcript_file_present=0' "$doc"
require_contains 'rollback_drill_transcript_file_present=0' "$doc"
require_contains 'operator_recovery_receipt_file_present=0' "$doc"
require_contains 'recovery_runbook_sha256_recorded=0' "$doc"
require_contains 'failure_mode_register_sha256_recorded=0' "$doc"
require_contains 'recovery_drill_transcript_sha256_recorded=0' "$doc"
require_contains 'rollback_drill_transcript_sha256_recorded=0' "$doc"
require_contains 'operator_recovery_receipt_sha256_recorded=0' "$doc"
require_contains 'recovery_runbook_review_present=0' "$doc"
require_contains 'failure_mode_register_review_present=0' "$doc"
require_contains 'recovery_drill_review_present=0' "$doc"
require_contains 'rollback_drill_review_present=0' "$doc"
require_contains 'operator_recovery_receipt_review_present=0' "$doc"
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
require_contains 'package_manager_invoked=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'It does not install, uninstall, upgrade, rollback, recover a host, invoke a package manager, write transcripts, mutate a host, or validate production installer recovery behavior.' "$doc"
require_contains 'installer_failure_mode_evidence_recorded=1' "$doc"
require_contains 'Create and review the production-installer recovery runbook, failure-mode register, recovery drill transcript, rollback drill transcript, and operator recovery receipt.' "$doc"
require_contains 'Validate recovery runbook, failure-mode register, recovery drill, rollback drill, operator receipt, and review evidence with the recovery evidence intake validator.' "$doc"
require_contains 'This status record is not a production installer.' "$doc"

require_contains 'artifact_manifest_fixture_present=1' "$fixture"
require_contains 'artifact_manifest_validated=1' "$fixture"

require_contains 'production_installer_recovery_failure_mode_status_present=1' "$prod"
require_contains 'installer_failure_mode_status_present=1' "$prod"
require_contains 'installer_recovery_runbook_status_present=1' "$prod"
require_contains 'installer_recovery_drill_status_present=1' "$prod"
require_contains 'installer_recovery_failure_mode_status_no_effect=1' "$prod"
require_contains 'installer_failure_mode_documented=0' "$prod"
require_contains 'installer_recovery_runbook_present=0' "$prod"
require_contains 'installer_recovery_drill_validated=0' "$prod"
require_contains 'installer_rollback_drill_validated=0' "$prod"
require_contains 'installer_failure_mode_evidence_recorded=0' "$prod"
require_contains 'recovery_evidence_intake_validator_present=1' "$prod"
require_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$prod"
require_contains 'recovery_evidence_candidate_valid=0' "$prod"
require_contains 'recovery_evidence_accepted_by_intake_validator=0' "$prod"
require_contains 'recovery_evidence_written_by_intake_validator=0' "$prod"
require_contains 'installer_recovery_promotion_allowed_by_intake_validator_alone=0' "$prod"
require_contains 'release_artifact_promotion_gate_passed=0' "$prod"
require_contains 'production_installer_recovery_failure_mode_status_present=1' "$ledger"
require_contains 'installer_failure_mode_status_present=1' "$ledger"
require_contains 'installer_recovery_runbook_status_present=1' "$ledger"
require_contains 'installer_recovery_drill_status_present=1' "$ledger"
require_contains 'installer_recovery_failure_mode_status_no_effect=1' "$ledger"
require_contains 'installer_recovery_runbook_present=0' "$ledger"
require_contains 'installer_failure_mode_evidence_recorded=0' "$ledger"
require_contains 'recovery_evidence_intake_validator_present=1' "$ledger"
require_contains 'recovery_evidence_candidate_valid=0' "$ledger"
require_contains 'PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'installer_recovery_failure_mode_status' "$installer_page"
require_contains 'recovery_evidence_intake_validator' "$installer_page"
require_contains 'test-production-installer-recovery-failure-mode-status-contract.sh' Makefile

output="$(sh "$status_script")"
require_output_contains 'LATTICRA PRODUCTION INSTALLER RECOVERY FAILURE-MODE STATUS' "$output"
require_output_contains 'status_mode=no-effect-installer-recovery-failure-mode-status' "$output"
require_output_contains 'production_installer_recovery_failure_mode_status_present=1' "$output"
require_output_contains 'installer_failure_mode_status_present=1' "$output"
require_output_contains 'installer_recovery_runbook_status_present=1' "$output"
require_output_contains 'installer_recovery_drill_status_present=1' "$output"
require_output_contains 'installer_recovery_failure_mode_status_no_effect=1' "$output"
require_output_contains 'production_installer_transcript_status_present=1' "$output"
require_output_contains 'production_installer_lifecycle_validation_status_present=1' "$output"
require_output_contains 'recovery_runbook_path=docs/runbooks/latticra-production-installer-recovery-runbook.md' "$output"
require_output_contains 'failure_mode_register_path=artifacts/release/latticra-production-installer-failure-mode-register.txt' "$output"
require_output_contains 'recovery_drill_transcript_path=artifacts/release/latticra-production-installer-recovery-drill-transcript.txt' "$output"
require_output_contains 'rollback_drill_transcript_path=artifacts/release/latticra-production-installer-rollback-drill-transcript.txt' "$output"
require_output_contains 'operator_recovery_receipt_path=artifacts/release/latticra-production-installer-operator-recovery-receipt.txt' "$output"
require_output_contains 'recovery_runbook_present=0' "$output"
require_output_contains 'failure_mode_register_present=0' "$output"
require_output_contains 'recovery_drill_transcript_present=0' "$output"
require_output_contains 'rollback_drill_transcript_present=0' "$output"
require_output_contains 'operator_recovery_receipt_present=0' "$output"
require_output_contains 'recovery_runbook_reviewed=0' "$output"
require_output_contains 'failure_mode_register_reviewed=0' "$output"
require_output_contains 'recovery_drill_reviewed=0' "$output"
require_output_contains 'rollback_drill_reviewed=0' "$output"
require_output_contains 'operator_recovery_receipt_reviewed=0' "$output"
require_output_contains 'recovery_evidence_intake_validator_present=1' "$output"
require_output_contains 'recovery_evidence_intake_validation_mode=no-effect-validation' "$output"
require_output_contains 'recovery_evidence_candidate_valid=0' "$output"
require_output_contains 'recovery_runbook_file_present=0' "$output"
require_output_contains 'failure_mode_register_file_present=0' "$output"
require_output_contains 'recovery_drill_transcript_file_present=0' "$output"
require_output_contains 'rollback_drill_transcript_file_present=0' "$output"
require_output_contains 'operator_recovery_receipt_file_present=0' "$output"
require_output_contains 'recovery_runbook_sha256_recorded=0' "$output"
require_output_contains 'failure_mode_register_sha256_recorded=0' "$output"
require_output_contains 'recovery_drill_transcript_sha256_recorded=0' "$output"
require_output_contains 'rollback_drill_transcript_sha256_recorded=0' "$output"
require_output_contains 'operator_recovery_receipt_sha256_recorded=0' "$output"
require_output_contains 'recovery_runbook_review_present=0' "$output"
require_output_contains 'failure_mode_register_review_present=0' "$output"
require_output_contains 'recovery_drill_review_present=0' "$output"
require_output_contains 'rollback_drill_review_present=0' "$output"
require_output_contains 'operator_recovery_receipt_review_present=0' "$output"
require_output_contains 'recovery_evidence_accepted_by_intake_validator=0' "$output"
require_output_contains 'recovery_evidence_written_by_intake_validator=0' "$output"
require_output_contains 'installer_recovery_promotion_allowed_by_intake_validator_alone=0' "$output"
require_output_contains 'release_artifact_promotion_gate_passed=0' "$output"
require_output_contains 'installer_failure_mode_documented=0' "$output"
require_output_contains 'installer_recovery_runbook_present=0' "$output"
require_output_contains 'installer_recovery_runbook_reviewed=0' "$output"
require_output_contains 'installer_recovery_drill_validated=0' "$output"
require_output_contains 'installer_rollback_drill_validated=0' "$output"
require_output_contains 'installer_failure_mode_evidence_recorded=0' "$output"
require_output_contains 'recovery_performed=0' "$output"
require_output_contains 'rollback_drill_performed=0' "$output"
require_output_contains 'package_manager_invoked=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"

printf 'production_installer_recovery_failure_mode_status_contract: ok\n'
