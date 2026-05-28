#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"
install_transcript_path="${2:-artifacts/release/latticra-production-installer-install-transcript.txt}"
uninstall_transcript_path="${3:-artifacts/release/latticra-production-installer-uninstall-transcript.txt}"
absence_transcript_path="${4:-artifacts/release/latticra-production-installer-post-removal-absence.txt}"

if [ ! -f "$fixture" ]; then
  printf 'production installer transcript status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer transcript status: missing fixture line: %s\n' "$pattern" >&2
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

install_transcript_present="$(presence "$install_transcript_path")"
uninstall_transcript_present="$(presence "$uninstall_transcript_path")"
absence_transcript_present="$(presence "$absence_transcript_path")"

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER TRANSCRIPT STATUS' \
  'status_version=1' \
  'status_mode=no-effect-installer-transcript-status' \
  'production_installer_transcript_status_present=1' \
  'installer_transcript_status_present=1' \
  'installer_install_transcript_status_present=1' \
  'installer_uninstall_transcript_status_present=1' \
  'installer_post_removal_absence_status_present=1' \
  'installer_transcript_status_no_effect=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_preflight_guard_present=1' \
  'installer_install_plan_preview_present=1' \
  'production_installer_release_artifact_promotion_gate_present=1' \
  'production_installer_sbom_status_present=1' \
  "install_transcript_path=$install_transcript_path" \
  "uninstall_transcript_path=$uninstall_transcript_path" \
  "post_removal_absence_transcript_path=$absence_transcript_path" \
  "install_transcript_present=$install_transcript_present" \
  "uninstall_transcript_present=$uninstall_transcript_present" \
  "post_removal_absence_transcript_present=$absence_transcript_present" \
  'install_transcript_reviewed=0' \
  'uninstall_transcript_reviewed=0' \
  'post_removal_absence_reviewed=0' \
  'transcript_evidence_intake_validator_present=1' \
  'transcript_evidence_intake_validation_mode=no-effect-validation' \
  'transcript_evidence_candidate_valid=0' \
  'install_transcript_file_present=0' \
  'uninstall_transcript_file_present=0' \
  'post_removal_absence_transcript_file_present=0' \
  'install_transcript_sha256_recorded=0' \
  'uninstall_transcript_sha256_recorded=0' \
  'post_removal_absence_transcript_sha256_recorded=0' \
  'install_transcript_review_present=0' \
  'uninstall_transcript_review_present=0' \
  'post_removal_absence_review_present=0' \
  'transcript_evidence_accepted_by_intake_validator=0' \
  'transcript_evidence_written_by_intake_validator=0' \
  'installer_transcript_promotion_allowed_by_intake_validator_alone=0' \
  'installer_install_transcript_recorded=0' \
  'installer_uninstall_transcript_recorded=0' \
  'installer_post_removal_absence_verified=0' \
  'production_installer_dry_run_performed=0' \
  'install_performed=0' \
  'uninstall_performed=0' \
  'package_manager_invoked=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
