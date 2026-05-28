#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer transcript status contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md'
status_script='scripts/production-installer-transcript-status.sh'
test_script='scripts/test-production-installer-transcript-status-contract.sh'
fixture='fixtures/artifact/local-artifact-manifest.txt'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'

for file in "$doc" "$status_script" "$test_script" "$fixture" "$prod" "$ledger" "$index" "$installer_page" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect installer transcript status contract' "$doc"
require_contains 'Evidence level: 10 target, status evidence only' "$doc"
require_contains 'sh scripts/production-installer-transcript-status.sh' "$doc"
require_contains 'production_installer_transcript_status_present=1' "$doc"
require_contains 'installer_transcript_status_present=1' "$doc"
require_contains 'installer_install_transcript_status_present=1' "$doc"
require_contains 'installer_uninstall_transcript_status_present=1' "$doc"
require_contains 'installer_post_removal_absence_status_present=1' "$doc"
require_contains 'installer_transcript_status_no_effect=1' "$doc"
require_contains 'install_transcript_present=0' "$doc"
require_contains 'uninstall_transcript_present=0' "$doc"
require_contains 'post_removal_absence_transcript_present=0' "$doc"
require_contains 'install_transcript_reviewed=0' "$doc"
require_contains 'uninstall_transcript_reviewed=0' "$doc"
require_contains 'post_removal_absence_reviewed=0' "$doc"
require_contains 'transcript_evidence_intake_validator_present=1' "$doc"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'transcript_evidence_candidate_valid=0' "$doc"
require_contains 'install_transcript_file_present=0' "$doc"
require_contains 'uninstall_transcript_file_present=0' "$doc"
require_contains 'post_removal_absence_transcript_file_present=0' "$doc"
require_contains 'install_transcript_sha256_recorded=0' "$doc"
require_contains 'uninstall_transcript_sha256_recorded=0' "$doc"
require_contains 'post_removal_absence_transcript_sha256_recorded=0' "$doc"
require_contains 'install_transcript_review_present=0' "$doc"
require_contains 'uninstall_transcript_review_present=0' "$doc"
require_contains 'post_removal_absence_review_present=0' "$doc"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'transcript_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'installer_install_transcript_recorded=0' "$doc"
require_contains 'installer_uninstall_transcript_recorded=0' "$doc"
require_contains 'installer_post_removal_absence_verified=0' "$doc"
require_contains 'production_installer_dry_run_performed=0' "$doc"
require_contains 'package_manager_invoked=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'It does not install, uninstall, invoke a package manager, verify absence on a host, write transcripts, or validate production installer behavior.' "$doc"
require_contains 'production_installer_dry_run_performed=1' "$doc"
require_contains 'installer_post_removal_absence_verified=1' "$doc"
require_contains 'Run a disposable Fedora VM production-installer dry-run and attach reviewed install, uninstall, and post-removal absence transcript evidence.' "$doc"
require_contains 'Validate install, uninstall, post-removal absence, and transcript-review evidence with the transcript evidence intake validator.' "$doc"
require_contains 'This status record is not a production installer.' "$doc"

require_contains 'artifact_manifest_fixture_present=1' "$fixture"
require_contains 'artifact_manifest_validated=1' "$fixture"

require_contains 'production_installer_transcript_status_present=1' "$prod"
require_contains 'installer_transcript_status_present=1' "$prod"
require_contains 'installer_install_transcript_status_present=1' "$prod"
require_contains 'installer_uninstall_transcript_status_present=1' "$prod"
require_contains 'installer_post_removal_absence_status_present=1' "$prod"
require_contains 'installer_transcript_status_no_effect=1' "$prod"
require_contains 'transcript_evidence_intake_validator_present=1' "$prod"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$prod"
require_contains 'transcript_evidence_candidate_valid=0' "$prod"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$prod"
require_contains 'transcript_evidence_written_by_intake_validator=0' "$prod"
require_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$prod"
require_contains 'installer_install_transcript_recorded=0' "$prod"
require_contains 'installer_uninstall_transcript_recorded=0' "$prod"
require_contains 'installer_post_removal_absence_verified=0' "$prod"
require_contains 'production_installer_transcript_status_present=1' "$ledger"
require_contains 'installer_transcript_status_present=1' "$ledger"
require_contains 'installer_install_transcript_status_present=1' "$ledger"
require_contains 'installer_uninstall_transcript_status_present=1' "$ledger"
require_contains 'installer_post_removal_absence_status_present=1' "$ledger"
require_contains 'installer_transcript_status_no_effect=1' "$ledger"
require_contains 'transcript_evidence_intake_validator_present=1' "$ledger"
require_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$ledger"
require_contains 'transcript_evidence_candidate_valid=0' "$ledger"
require_contains 'transcript_evidence_accepted_by_intake_validator=0' "$ledger"
require_contains 'transcript_evidence_written_by_intake_validator=0' "$ledger"
require_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$ledger"
require_contains 'installer_post_removal_absence_verified=0' "$ledger"
require_contains 'PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'installer_transcript_status' "$installer_page"
require_contains 'transcript_evidence_intake_validator' "$installer_page"
require_contains 'test-production-installer-transcript-status-contract.sh' Makefile

output="$(sh "$status_script")"
require_output_contains 'LATTICRA PRODUCTION INSTALLER TRANSCRIPT STATUS' "$output"
require_output_contains 'status_mode=no-effect-installer-transcript-status' "$output"
require_output_contains 'production_installer_transcript_status_present=1' "$output"
require_output_contains 'installer_transcript_status_present=1' "$output"
require_output_contains 'installer_install_transcript_status_present=1' "$output"
require_output_contains 'installer_uninstall_transcript_status_present=1' "$output"
require_output_contains 'installer_post_removal_absence_status_present=1' "$output"
require_output_contains 'installer_transcript_status_no_effect=1' "$output"
require_output_contains 'local_artifact_manifest_fixture_present=1' "$output"
require_output_contains 'production_installer_preflight_guard_present=1' "$output"
require_output_contains 'installer_install_plan_preview_present=1' "$output"
require_output_contains 'production_installer_release_artifact_promotion_gate_present=1' "$output"
require_output_contains 'production_installer_sbom_status_present=1' "$output"
require_output_contains 'install_transcript_path=artifacts/release/latticra-production-installer-install-transcript.txt' "$output"
require_output_contains 'uninstall_transcript_path=artifacts/release/latticra-production-installer-uninstall-transcript.txt' "$output"
require_output_contains 'post_removal_absence_transcript_path=artifacts/release/latticra-production-installer-post-removal-absence.txt' "$output"
require_output_contains 'install_transcript_present=0' "$output"
require_output_contains 'uninstall_transcript_present=0' "$output"
require_output_contains 'post_removal_absence_transcript_present=0' "$output"
require_output_contains 'install_transcript_reviewed=0' "$output"
require_output_contains 'uninstall_transcript_reviewed=0' "$output"
require_output_contains 'post_removal_absence_reviewed=0' "$output"
require_output_contains 'transcript_evidence_intake_validator_present=1' "$output"
require_output_contains 'transcript_evidence_intake_validation_mode=no-effect-validation' "$output"
require_output_contains 'transcript_evidence_candidate_valid=0' "$output"
require_output_contains 'transcript_evidence_accepted_by_intake_validator=0' "$output"
require_output_contains 'transcript_evidence_written_by_intake_validator=0' "$output"
require_output_contains 'installer_transcript_promotion_allowed_by_intake_validator_alone=0' "$output"
require_output_contains 'installer_install_transcript_recorded=0' "$output"
require_output_contains 'installer_uninstall_transcript_recorded=0' "$output"
require_output_contains 'installer_post_removal_absence_verified=0' "$output"
require_output_contains 'production_installer_dry_run_performed=0' "$output"
require_output_contains 'install_performed=0' "$output"
require_output_contains 'uninstall_performed=0' "$output"
require_output_contains 'package_manager_invoked=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"

printf 'production_installer_transcript_status_contract: ok\n'
