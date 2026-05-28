#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu ppa/archive publication gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu ppa/archive publication gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
install_remove_contract='docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md'
source_package_contract='docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md'
upload_signing_contract='docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md'
launchpad_build_contract='docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md'
publication_non_claim_contract='docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
blocker_matrix_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
intake_denial_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
intake_denial_review_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
intake_denial_disposition_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
intake_denial_disposition_closeout_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
intake_denial_disposition_closeout_archive_gate_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$install_remove_contract"
require_file "$source_package_contract"
require_file "$upload_signing_contract"
require_file "$launchpad_build_contract"
require_file "$publication_non_claim_contract"
require_file "$blocker_matrix_contract"
require_file "$intake_denial_contract"
require_file "$intake_denial_review_contract"
require_file "$intake_denial_disposition_contract"
require_file "$intake_denial_disposition_closeout_contract"
require_file "$intake_denial_disposition_closeout_archive_gate_contract"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control

require_contains 'Status: no-effect PPA/archive publication gate contract' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$contract"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=1' "$contract"
require_contains 'ubuntu_install_remove_evidence_unblocked=1' "$contract"
require_contains 'local_deb_build_transcript_accepted=1' "$contract"
require_contains 'deb_artifact_created=1' "$contract"
require_contains 'deb_artifact_digest_recorded=1' "$contract"
require_contains 'source_package_created=1' "$contract"
require_contains 'source_package_digest_recorded=1' "$contract"
require_contains 'dsc_digest_recorded=1' "$contract"
require_contains 'changes_file_digest_recorded=1' "$contract"
require_contains 'upload_target_recorded=1' "$contract"
require_contains 'upload_authority_reviewed=1' "$contract"
require_contains 'debsign_command_recorded=1' "$contract"
require_contains 'signature_fingerprint_recorded=1' "$contract"
require_contains 'dput_command_recorded=1' "$contract"
require_contains 'upload_exit_status_recorded=1' "$contract"
require_contains 'launchpad_build_log_recorded=1' "$contract"
require_contains 'launchpad_build_result_recorded=1' "$contract"
require_contains 'launchpad_build_result_reviewed=1' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=1' "$contract"
require_contains 'launchpad_expected_findings_classified=1' "$contract"
require_contains 'launchpad_unexpected_findings_classified=1' "$contract"
require_contains 'launchpad_publication_non_claims_reviewed=1' "$contract"
require_contains 'publication_scope_recorded=1' "$contract"
require_contains 'publication_target_type_recorded=1' "$contract"
require_contains 'publication_claims_reviewed=1' "$contract"
require_contains 'ppa_claim_absence_reviewed=1' "$contract"
require_contains 'ubuntu_archive_claim_absence_reviewed=1' "$contract"
require_contains 'canonical_endorsement_absence_reviewed=1' "$contract"
require_contains 'sponsorship_claim_absence_reviewed=1' "$contract"
require_contains 'production_installer_claim_absence_reviewed=1' "$contract"
require_contains 'root_installer_claim_absence_reviewed=1' "$contract"
require_contains 'publication_readiness_non_claims_reviewed=1' "$contract"
require_contains 'publication_non_claims_reviewed=1' "$contract"
require_contains 'ubuntu_publication_gate_unblocked=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$contract"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_review_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_present=1' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_decision=closeout-upheld-denial' "$contract"
require_contains 'publication_evidence_denial_disposition_present=1' "$contract"
require_contains 'publication_evidence_denial_disposition_decision=close-upheld-denial' "$contract"
require_contains 'publication_evidence_denial_closed=1' "$contract"
require_contains 'publication_evidence_denial_archived=0' "$contract"
require_contains 'publication_evidence_denial_archive_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_written=0' "$contract"
require_contains 'publication_evidence_denial_review_present=1' "$contract"
require_contains 'publication_evidence_denial_review_decision=uphold-denial' "$contract"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_allowed=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_requested=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archived=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$contract"
require_contains 'publication_transcript_intake_accepted=0' "$contract"
require_contains 'ppa_creation_evidence_accepted=0' "$contract"
require_contains 'launchpad_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_archive_submission_evidence_accepted=0' "$contract"
require_contains 'ubuntu_install_remove_evidence_unblocked=0' "$contract"
require_contains 'local_deb_build_transcript_accepted=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'deb_artifact_digest_recorded=0' "$contract"
require_contains 'source_package_created=0' "$contract"
require_contains 'source_package_digest_recorded=0' "$contract"
require_contains 'dsc_digest_recorded=0' "$contract"
require_contains 'changes_file_digest_recorded=0' "$contract"
require_contains 'upload_target_recorded=0' "$contract"
require_contains 'upload_authority_reviewed=0' "$contract"
require_contains 'debsign_command_recorded=0' "$contract"
require_contains 'signature_fingerprint_recorded=0' "$contract"
require_contains 'dput_command_recorded=0' "$contract"
require_contains 'upload_exit_status_recorded=0' "$contract"
require_contains 'launchpad_upload_url_recorded=0' "$contract"
require_contains 'launchpad_build_log_recorded=0' "$contract"
require_contains 'launchpad_build_result_recorded=0' "$contract"
require_contains 'launchpad_build_result_reviewed=0' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$contract"
require_contains 'launchpad_expected_findings_classified=0' "$contract"
require_contains 'launchpad_unexpected_findings_classified=0' "$contract"
require_contains 'launchpad_publication_non_claims_reviewed=0' "$contract"
require_contains 'publication_scope_recorded=0' "$contract"
require_contains 'publication_target_type_recorded=0' "$contract"
require_contains 'publication_claims_reviewed=0' "$contract"
require_contains 'ppa_claim_absence_reviewed=0' "$contract"
require_contains 'ubuntu_archive_claim_absence_reviewed=0' "$contract"
require_contains 'canonical_endorsement_absence_reviewed=0' "$contract"
require_contains 'sponsorship_claim_absence_reviewed=0' "$contract"
require_contains 'production_installer_claim_absence_reviewed=0' "$contract"
require_contains 'root_installer_claim_absence_reviewed=0' "$contract"
require_contains 'publication_readiness_non_claims_reviewed=0' "$contract"
require_contains 'publication_non_claims_reviewed=0' "$contract"
require_contains 'ubuntu_publication_promotion_blocked=1' "$contract"
require_contains 'ubuntu_platform_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_publication_result_promoted=0' "$contract"
require_contains 'ubuntu_publication_gate_unblocked=0' "$contract"
require_contains 'ppa_created=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"
require_contains 'ubuntu_archive_submission_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_contract: ok' "$contract"

require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$status"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$status"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$status"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$status"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$status"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$status"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$status"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$status"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$status"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$status"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$status"
require_contains 'ubuntu_publication_promotion_blocker_matrix_contract_present=1' "$status"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$status"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' "$status"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$status"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$status"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$status"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$status"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$status"
require_contains 'publication_evidence_denial_closed=1' "$status"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$status"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$status"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$status"
require_contains 'publication_evidence_denial_archived=0' "$status"
require_contains 'publication_evidence_denial_archive_allowed=0' "$status"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$status"
require_contains 'publication_evidence_denial_archive_record_written=0' "$status"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$status"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$status"
require_contains 'ubuntu_publication_promotion_blocked=1' "$status"
require_contains 'ubuntu_platform_publication_evidence_accepted=0' "$status"
require_contains 'ubuntu_publication_result_promoted=0' "$status"
require_contains 'source_package_created=0' "$status"
require_contains 'source_package_digest_recorded=0' "$status"
require_contains 'dsc_digest_recorded=0' "$status"
require_contains 'upload_target_recorded=0' "$status"
require_contains 'upload_authority_reviewed=0' "$status"
require_contains 'debsign_command_recorded=0' "$status"
require_contains 'signature_fingerprint_recorded=0' "$status"
require_contains 'dput_command_recorded=0' "$status"
require_contains 'upload_exit_status_recorded=0' "$status"
require_contains 'launchpad_upload_url_recorded=0' "$status"
require_contains 'launchpad_build_log_recorded=0' "$status"
require_contains 'launchpad_build_result_recorded=0' "$status"
require_contains 'launchpad_build_result_reviewed=0' "$status"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$status"
require_contains 'launchpad_expected_findings_classified=0' "$status"
require_contains 'launchpad_unexpected_findings_classified=0' "$status"
require_contains 'launchpad_publication_non_claims_reviewed=0' "$status"
require_contains 'publication_scope_recorded=0' "$status"
require_contains 'publication_target_type_recorded=0' "$status"
require_contains 'publication_claims_reviewed=0' "$status"
require_contains 'ppa_claim_absence_reviewed=0' "$status"
require_contains 'ubuntu_archive_claim_absence_reviewed=0' "$status"
require_contains 'canonical_endorsement_absence_reviewed=0' "$status"
require_contains 'sponsorship_claim_absence_reviewed=0' "$status"
require_contains 'production_installer_claim_absence_reviewed=0' "$status"
require_contains 'root_installer_claim_absence_reviewed=0' "$status"
require_contains 'publication_readiness_non_claims_reviewed=0' "$status"
require_contains 'publication_non_claims_reviewed=0' "$status"
require_contains 'ubuntu_publication_gate_unblocked=0' "$status"
require_contains 'ppa_created=0' "$status"
require_contains 'launchpad_upload_run=0' "$status"
require_contains 'ubuntu_archive_submission_claimed=0' "$status"
require_contains 'ubuntu_publication_ready=0' "$status"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$status"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml' "$status"
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml' "$status"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml' "$status"

require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$install_remove_contract"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$install_remove_contract"
require_contains 'ubuntu_publication_gate_unblocked=0' "$install_remove_contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$source_package_contract"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$source_package_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$upload_signing_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$upload_signing_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$launchpad_build_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$launchpad_build_contract"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$publication_non_claim_contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$publication_non_claim_contract"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$blocker_matrix_contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$blocker_matrix_contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' "$intake_denial_contract"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$intake_denial_contract"
require_contains "$intake_denial_contract" "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$intake_denial_review_contract"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$intake_denial_review_contract"
require_contains "$intake_denial_review_contract" "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$intake_denial_disposition_contract"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$intake_denial_disposition_contract"
require_contains "$intake_denial_disposition_contract" "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$intake_denial_disposition_closeout_contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$intake_denial_disposition_closeout_contract"
require_contains "$intake_denial_disposition_closeout_contract" "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$intake_denial_disposition_closeout_archive_gate_contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$intake_denial_disposition_closeout_archive_gate_contract"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$intake_denial_disposition_closeout_archive_gate_contract"
require_contains "$intake_denial_disposition_closeout_archive_gate_contract" "$contract"

require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$static_validation"
require_contains 'source_package_evidence_contract_present=1' "$static_validation"
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' "$static_validation"
require_contains 'upload_signing_authority_evidence_contract_present=1' "$static_validation"
require_contains 'launchpad_build_result_evidence_contract_present=1' "$static_validation"
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$static_validation"
require_contains 'publication_non_claim_review_contract_present=1' "$static_validation"
require_contains 'publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$static_validation"
require_contains 'ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$static_validation"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$static_validation"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' "$static_validation"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$static_validation"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$static_validation"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$static_validation"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$static_validation"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$static_validation"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$static_validation"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$static_validation"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$static_validation"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$static_validation"
require_contains 'publication_evidence_denial_closed=1' "$static_validation"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$static_validation"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$static_validation"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$static_validation"
require_contains 'publication_evidence_denial_archived=0' "$static_validation"
require_contains 'publication_evidence_denial_archive_allowed=0' "$static_validation"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$static_validation"
require_contains 'publication_evidence_denial_archive_record_written=0' "$static_validation"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$static_validation"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$static_validation"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$static_validation"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$static_validation"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$static_validation"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$static_validation"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$static_validation"
require_contains 'ppa_archive_publication_gate_contract_present=1' "$static_validation"
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$static_validation"
require_contains 'ubuntu_publication_gate_unblocked=0' "$static_validation"

require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$readiness"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$readiness"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$readiness"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$readiness"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$readiness"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$readiness"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$readiness"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$readiness"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' "$readiness"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$readiness"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$readiness"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$readiness"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$readiness"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$readiness"
require_contains 'publication_evidence_denial_closed=1' "$readiness"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$readiness"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$readiness"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$readiness"
require_contains 'publication_evidence_denial_archived=0' "$readiness"
require_contains 'publication_evidence_denial_archive_allowed=0' "$readiness"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$readiness"
require_contains 'publication_evidence_denial_archive_record_written=0' "$readiness"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$readiness"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$readiness"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$readiness"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$readiness"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$readiness"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$readiness"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$readiness"
require_contains 'ubuntu_publication_gate_unblocked=0' "$readiness"
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-source-package-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-source-package-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml' "$readiness"

require_contains 'ubuntu_source_package_evidence_contract_present=1' README.md
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' README.md
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' README.md
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' README.md
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' README.md
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' README.md
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' README.md
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' README.md
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' README.md
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' README.md
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' README.md
require_contains 'publication_evidence_denial_closed=1' README.md
require_contains 'publication_evidence_denial_archive_gate_present=1' README.md
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' README.md
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' README.md
require_contains 'publication_evidence_denial_archived=0' README.md
require_contains 'publication_evidence_denial_archive_allowed=0' README.md
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' README.md
require_contains 'publication_evidence_denial_archive_record_written=0' README.md
require_contains 'publication_evidence_denial_re_request_allowed=0' README.md
require_contains 'ubuntu_publication_evidence_intake_denied=1' README.md
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' README.md
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' README.md
require_contains 'ubuntu_source_package_evidence_unblocked=0' README.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' README.md
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' README.md
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' README.md
require_contains 'ubuntu_publication_gate_unblocked=0' README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'source_package_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' packaging/ubuntu/README.md
require_contains 'publication_non_claim_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_promotion_blocker_matrix_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_closed=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archived=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_allowed=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_record_written=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_re_request_allowed=0' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denied=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' packaging/ubuntu/README.md
require_contains 'launchpad_upload_run=0' packaging/ubuntu/README.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-publication-non-claim-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$workflow"
require_contains 'Ubuntu PPA Archive Publication Gate Contract' "$workflow"
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control

printf 'ubuntu_ppa_archive_publication_gate_contract: ok\n'
