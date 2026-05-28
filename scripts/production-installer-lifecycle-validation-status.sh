#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"
upgrade_transcript_path="${2:-artifacts/release/latticra-production-installer-upgrade-transcript.txt}"
rollback_transcript_path="${3:-artifacts/release/latticra-production-installer-rollback-transcript.txt}"
reinstall_transcript_path="${4:-artifacts/release/latticra-production-installer-reinstall-transcript.txt}"

if [ ! -f "$fixture" ]; then
  printf 'production installer lifecycle validation status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer lifecycle validation status: missing fixture line: %s\n' "$pattern" >&2
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

upgrade_transcript_present="$(presence "$upgrade_transcript_path")"
rollback_transcript_present="$(presence "$rollback_transcript_path")"
reinstall_transcript_present="$(presence "$reinstall_transcript_path")"

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER LIFECYCLE VALIDATION STATUS' \
  'status_version=1' \
  'status_mode=no-effect-installer-lifecycle-validation-status' \
  'production_installer_lifecycle_validation_status_present=1' \
  'installer_upgrade_status_present=1' \
  'installer_rollback_status_present=1' \
  'installer_reinstall_idempotence_status_present=1' \
  'installer_lifecycle_validation_status_no_effect=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_transcript_status_present=1' \
  'installer_install_transcript_recorded=0' \
  'installer_uninstall_transcript_recorded=0' \
  'installer_post_removal_absence_verified=0' \
  'production_installer_release_artifact_promotion_gate_present=1' \
  'production_installer_sbom_status_present=1' \
  'installer_upgrade_candidate_present=0' \
  'installer_rollback_candidate_present=0' \
  'installer_reinstall_candidate_present=0' \
  "upgrade_transcript_path=$upgrade_transcript_path" \
  "rollback_transcript_path=$rollback_transcript_path" \
  "reinstall_transcript_path=$reinstall_transcript_path" \
  "upgrade_transcript_present=$upgrade_transcript_present" \
  "rollback_transcript_present=$rollback_transcript_present" \
  "reinstall_transcript_present=$reinstall_transcript_present" \
  'upgrade_transcript_reviewed=0' \
  'rollback_transcript_reviewed=0' \
  'reinstall_transcript_reviewed=0' \
  'lifecycle_evidence_intake_validator_present=1' \
  'lifecycle_evidence_intake_validation_mode=no-effect-validation' \
  'lifecycle_evidence_candidate_valid=0' \
  'upgrade_transcript_file_present=0' \
  'rollback_transcript_file_present=0' \
  'reinstall_transcript_file_present=0' \
  'upgrade_transcript_sha256_recorded=0' \
  'rollback_transcript_sha256_recorded=0' \
  'reinstall_transcript_sha256_recorded=0' \
  'upgrade_transcript_review_present=0' \
  'rollback_transcript_review_present=0' \
  'reinstall_transcript_review_present=0' \
  'lifecycle_evidence_accepted_by_intake_validator=0' \
  'lifecycle_evidence_written_by_intake_validator=0' \
  'installer_lifecycle_promotion_allowed_by_intake_validator_alone=0' \
  'installer_upgrade_path_validated=0' \
  'installer_rollback_path_validated=0' \
  'installer_downgrade_or_rollback_path_validated=0' \
  'installer_reinstall_idempotence_validated=0' \
  'production_installer_lifecycle_validation_performed=0' \
  'upgrade_performed=0' \
  'rollback_performed=0' \
  'reinstall_performed=0' \
  'package_manager_invoked=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
