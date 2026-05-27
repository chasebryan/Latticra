#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu launchpad build result evidence contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu launchpad build result evidence contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
source_package_contract='docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md'
upload_signing_contract='docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md'
publication_non_claim_contract='docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$source_package_contract"
require_file "$upload_signing_contract"
require_file "$publication_non_claim_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect Launchpad build result evidence contract' "$contract"
require_contains 'does not run `dput`, `debsign`, `launchpad`, `dpkg-source`, `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=1' "$contract"
require_contains 'source_package_created=1' "$contract"
require_contains 'source_package_digest_recorded=1' "$contract"
require_contains 'dsc_digest_recorded=1' "$contract"
require_contains 'changes_file_digest_recorded=1' "$contract"
require_contains 'upload_target_recorded=1' "$contract"
require_contains 'upload_authority_reviewed=1' "$contract"
require_contains 'signature_fingerprint_recorded=1' "$contract"
require_contains 'upload_exit_status_recorded=1' "$contract"
require_contains 'source_package_uploaded=1' "$contract"
require_contains 'launchpad_upload_url_recorded=1' "$contract"
require_contains 'launchpad_build_log_recorded=1' "$contract"
require_contains 'launchpad_build_result_recorded=1' "$contract"
require_contains 'launchpad_build_result_reviewed=1' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=1' "$contract"
require_contains 'launchpad_expected_findings_classified=1' "$contract"
require_contains 'launchpad_unexpected_findings_classified=1' "$contract"
require_contains 'launchpad_publication_non_claims_reviewed=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$contract"
require_contains 'source_package_created=0' "$contract"
require_contains 'source_package_uploaded=0' "$contract"
require_contains 'upload_exit_status_recorded=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"
require_contains 'launchpad_upload_url_recorded=0' "$contract"
require_contains 'launchpad_build_log_recorded=0' "$contract"
require_contains 'launchpad_build_result_recorded=0' "$contract"
require_contains 'launchpad_build_result_reviewed=0' "$contract"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$contract"
require_contains 'launchpad_expected_findings_classified=0' "$contract"
require_contains 'launchpad_unexpected_findings_classified=0' "$contract"
require_contains 'launchpad_publication_non_claims_reviewed=0' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$contract"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$contract"
require_contains 'ppa_created=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_submission_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract: ok' "$contract"

require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$status"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$status"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$status"
require_contains 'launchpad_upload_url_recorded=0' "$status"
require_contains 'launchpad_build_result_recorded=0' "$status"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$status"
require_contains 'launchpad_expected_findings_classified=0' "$status"
require_contains 'launchpad_unexpected_findings_classified=0' "$status"
require_contains 'launchpad_publication_non_claims_reviewed=0' "$status"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$status"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$status"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$status"
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml' "$status"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$status"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$source_package_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$upload_signing_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$upload_signing_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$upload_signing_contract"

require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$publication_non_claim_contract"
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' "$publication_non_claim_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=1' "$publication_non_claim_contract"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$publication_non_claim_contract"

require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$publication_gate"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=1' "$publication_gate"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$publication_gate"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$publication_gate"
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' "$publication_gate"
require_contains 'launchpad_upload_url_recorded=0' "$publication_gate"
require_contains 'launchpad_build_result_recorded=0' "$publication_gate"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$publication_gate"

require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$static_validation"
require_contains 'launchpad_build_result_evidence_contract_present=1' "$static_validation"
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$static_validation"
require_contains 'launchpad_upload_url_recorded=0' "$static_validation"
require_contains 'launchpad_build_result_recorded=0' "$static_validation"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$static_validation"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$static_validation"
require_contains 'publication_non_claim_review_contract_present=1' "$static_validation"
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' "$static_validation"

require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' "$readiness"
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' "$readiness"
require_contains 'launchpad_upload_url_recorded=0' "$readiness"
require_contains 'launchpad_build_result_recorded=0' "$readiness"
require_contains 'launchpad_binary_artifact_listing_recorded=0' "$readiness"
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-publication-non-claim-review-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-publication-non-claim-review-contract.yml' "$readiness"

require_contains 'ubuntu_launchpad_build_result_evidence_contract_present=1' README.md
require_contains 'ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' README.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' README.md
require_contains 'ubuntu_publication_non_claim_review_contract_present=1' README.md
require_contains 'ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence' README.md
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' README.md
require_contains 'launchpad_upload_url_recorded=0' README.md
require_contains 'launchpad_build_result_recorded=0' README.md
require_contains 'launchpad_binary_artifact_listing_recorded=0' README.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' packaging/ubuntu/README.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' packaging/ubuntu/README.md
require_contains 'publication_non_claim_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_non_claim_review_unblocked=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-publication-non-claim-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh' "$workflow"
require_contains 'Ubuntu Launchpad Build Result Evidence Contract' "$workflow"

printf 'ubuntu_launchpad_build_result_evidence_contract: ok\n'
