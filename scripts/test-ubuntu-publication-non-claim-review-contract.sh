#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu publication non-claim review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu publication non-claim review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
launchpad_build_contract='docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md'
blocker_matrix_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-publication-non-claim-review-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$launchpad_build_contract"
require_file "$blocker_matrix_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect publication non-claim review contract' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=1' "$contract"
require_contains 'source_package_uploaded=1' "$contract"
require_contains 'upload_exit_status_recorded=1' "$contract"
require_contains 'launchpad_upload_url_recorded=1' "$contract"
require_contains 'launchpad_build_log_recorded=1' "$contract"
require_contains 'launchpad_build_result_recorded=1' "$contract"
require_contains 'launchpad_build_result_reviewed=1' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=1' "$contract"
require_contains 'launchpad_expected_findings_classified=1' "$contract"
require_contains 'launchpad_unexpected_findings_classified=1' "$contract"
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
require_contains 'ubuntu_publication_non_claim_review_unblocked=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$contract"
require_contains 'source_package_uploaded=0' "$contract"
require_contains 'upload_exit_status_recorded=0' "$contract"
require_contains 'launchpad_upload_url_recorded=0' "$contract"
require_contains 'launchpad_build_log_recorded=0' "$contract"
require_contains 'launchpad_build_result_recorded=0' "$contract"
require_contains 'launchpad_build_result_reviewed=0' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$contract"
require_contains 'publication_scope_recorded=0' "$contract"
require_contains 'publication_target_type_recorded=0' "$contract"
require_contains 'publication_claims_reviewed=0' "$contract"
require_contains 'ppa_claim_absence_reviewed=0' "$contract"
require_contains 'ubuntu_archive_claim_absence_reviewed=0' "$contract"
require_contains 'canonical_endorsement_absence_reviewed=0' "$contract"
require_contains 'sponsorship_claim_absence_reviewed=0' "$contract"
require_contains 'publication_readiness_non_claims_reviewed=0' "$contract"
require_contains 'publication_non_claims_reviewed=0' "$contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$contract"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$contract"
require_contains 'ppa_created=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_submission_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'canonical_endorsement_claimed=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_publication_non_claim_review_contract: ok' "$contract"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$status"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$status"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$status"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$status"
require_contains 'ubuntu_publication_promotion_blocker_matrix_contract_present=1' "$status"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$status"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$status"
require_contains 'ubuntu_publication_promotion_blocked=1' "$status"
require_contains 'ubuntu_platform_publication_evidence_accepted=0' "$status"
require_contains 'ubuntu_publication_result_promoted=0' "$status"
require_contains 'publication_scope_recorded=0' "$status"
require_contains 'publication_target_type_recorded=0' "$status"
require_contains 'publication_claims_reviewed=0' "$status"
require_contains 'ppa_claim_absence_reviewed=0' "$status"
require_contains 'ubuntu_archive_claim_absence_reviewed=0' "$status"
require_contains 'canonical_endorsement_absence_reviewed=0' "$status"
require_contains 'sponsorship_claim_absence_reviewed=0' "$status"
require_contains 'publication_readiness_non_claims_reviewed=0' "$status"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.yml' "$status"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$launchpad_build_contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$launchpad_build_contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$launchpad_build_contract"

require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$blocker_matrix_contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$blocker_matrix_contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=1' "$blocker_matrix_contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$blocker_matrix_contract"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$publication_gate"
require_contains 'ubuntu_publication_non_claim_review_unblocked=1' "$publication_gate"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$publication_gate"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$publication_gate"
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$publication_gate"
require_contains 'publication_scope_recorded=0' "$publication_gate"
require_contains 'publication_claims_reviewed=0' "$publication_gate"
require_contains 'ppa_claim_absence_reviewed=0' "$publication_gate"
require_contains 'ubuntu_archive_claim_absence_reviewed=0' "$publication_gate"

require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$static_validation"
require_contains 'publication_non_claim_review_contract_present=1' "$static_validation"
require_contains 'publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$static_validation"
require_contains 'publication_scope_recorded=0' "$static_validation"
require_contains 'publication_target_type_recorded=0' "$static_validation"
require_contains 'publication_claims_reviewed=0' "$static_validation"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$static_validation"
require_contains 'ppa_archive_publication_promotion_blocker_matrix_contract_present=1' "$static_validation"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$static_validation"
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' "$static_validation"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$readiness"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$readiness"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$readiness"
require_contains 'publication_scope_recorded=0' "$readiness"
require_contains 'publication_target_type_recorded=0' "$readiness"
require_contains 'publication_claims_reviewed=0' "$readiness"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.yml' "$readiness"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' README.md
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' README.md
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' README.md
require_contains 'ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1' README.md
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' README.md
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' README.md
require_contains 'publication_scope_recorded=0' README.md
require_contains 'publication_claims_reviewed=0' README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'publication_non_claim_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_promotion_blocker_matrix_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_promotion_blocker_matrix_unblocked=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-publication-non-claim-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$workflow"
require_contains 'Ubuntu Publication Non-Claim Review Contract' "$workflow"

printf 'ubuntu_publication_non_claim_review_contract: ok\n'
