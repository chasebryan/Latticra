#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"
recovery_runbook_path="${2:-docs/runbooks/latticra-production-installer-recovery-runbook.md}"
failure_mode_register_path="${3:-artifacts/release/latticra-production-installer-failure-mode-register.txt}"
recovery_drill_transcript_path="${4:-artifacts/release/latticra-production-installer-recovery-drill-transcript.txt}"
rollback_drill_transcript_path="${5:-artifacts/release/latticra-production-installer-rollback-drill-transcript.txt}"
operator_recovery_receipt_path="${6:-artifacts/release/latticra-production-installer-operator-recovery-receipt.txt}"

if [ ! -f "$fixture" ]; then
  printf 'production installer recovery failure-mode status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer recovery failure-mode status: missing fixture line: %s\n' "$pattern" >&2
    exit 1
  fi
}

presence() {
  if [ -f "$1" ]; then
    printf '1'
  else
    printf '0'
  fi
}

require_line 'artifact_manifest_fixture_present=1'
require_line 'artifact_manifest_validated=1'
require_line 'production_installer_ready=0'

recovery_runbook_present="$(presence "$recovery_runbook_path")"
failure_mode_register_present="$(presence "$failure_mode_register_path")"
recovery_drill_transcript_present="$(presence "$recovery_drill_transcript_path")"
rollback_drill_transcript_present="$(presence "$rollback_drill_transcript_path")"
operator_recovery_receipt_present="$(presence "$operator_recovery_receipt_path")"

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER RECOVERY FAILURE-MODE STATUS' \
  'status_version=1' \
  'status_mode=no-effect-installer-recovery-failure-mode-status' \
  'production_installer_recovery_failure_mode_status_present=1' \
  'installer_failure_mode_status_present=1' \
  'installer_recovery_runbook_status_present=1' \
  'installer_recovery_drill_status_present=1' \
  'installer_recovery_failure_mode_status_no_effect=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_transcript_status_present=1' \
  'production_installer_lifecycle_validation_status_present=1' \
  "recovery_runbook_path=$recovery_runbook_path" \
  "failure_mode_register_path=$failure_mode_register_path" \
  "recovery_drill_transcript_path=$recovery_drill_transcript_path" \
  "rollback_drill_transcript_path=$rollback_drill_transcript_path" \
  "operator_recovery_receipt_path=$operator_recovery_receipt_path" \
  "recovery_runbook_present=$recovery_runbook_present" \
  "failure_mode_register_present=$failure_mode_register_present" \
  "recovery_drill_transcript_present=$recovery_drill_transcript_present" \
  "rollback_drill_transcript_present=$rollback_drill_transcript_present" \
  "operator_recovery_receipt_present=$operator_recovery_receipt_present" \
  'recovery_runbook_reviewed=0' \
  'failure_mode_register_reviewed=0' \
  'recovery_drill_reviewed=0' \
  'rollback_drill_reviewed=0' \
  'operator_recovery_receipt_reviewed=0' \
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
  'recovery_performed=0' \
  'rollback_drill_performed=0' \
  'package_manager_invoked=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
