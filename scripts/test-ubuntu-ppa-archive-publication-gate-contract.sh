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
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$install_remove_contract"
require_file "$source_package_contract"
require_file "$upload_signing_contract"
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
require_contains 'launchpad_build_result_reviewed=1' "$contract"
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
require_contains 'launchpad_build_log_recorded=0' "$contract"
require_contains 'launchpad_build_result_reviewed=0' "$contract"
require_contains 'publication_non_claims_reviewed=0' "$contract"
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
require_contains 'source_package_created=0' "$status"
require_contains 'source_package_digest_recorded=0' "$status"
require_contains 'dsc_digest_recorded=0' "$status"
require_contains 'upload_target_recorded=0' "$status"
require_contains 'upload_authority_reviewed=0' "$status"
require_contains 'debsign_command_recorded=0' "$status"
require_contains 'signature_fingerprint_recorded=0' "$status"
require_contains 'dput_command_recorded=0' "$status"
require_contains 'upload_exit_status_recorded=0' "$status"
require_contains 'launchpad_build_log_recorded=0' "$status"
require_contains 'launchpad_build_result_reviewed=0' "$status"
require_contains 'publication_non_claims_reviewed=0' "$status"
require_contains 'ubuntu_publication_gate_unblocked=0' "$status"
require_contains 'ppa_created=0' "$status"
require_contains 'launchpad_upload_run=0' "$status"
require_contains 'ubuntu_archive_submission_claimed=0' "$status"
require_contains 'ubuntu_publication_ready=0' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml' "$status"

require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$install_remove_contract"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$install_remove_contract"
require_contains 'ubuntu_publication_gate_unblocked=0' "$install_remove_contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$source_package_contract"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$source_package_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$upload_signing_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$upload_signing_contract"

require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$static_validation"
require_contains 'source_package_evidence_contract_present=1' "$static_validation"
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' "$static_validation"
require_contains 'upload_signing_authority_evidence_contract_present=1' "$static_validation"
require_contains 'ppa_archive_publication_gate_contract_present=1' "$static_validation"
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$static_validation"
require_contains 'ubuntu_publication_gate_unblocked=0' "$static_validation"

require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$readiness"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$readiness"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$readiness"
require_contains 'ubuntu_publication_gate_unblocked=0' "$readiness"
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-source-package-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-source-package-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml' "$readiness"

require_contains 'ubuntu_source_package_evidence_contract_present=1' README.md
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' README.md
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' README.md
require_contains 'ubuntu_source_package_evidence_unblocked=0' README.md
require_contains 'ubuntu_publication_gate_unblocked=0' README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'source_package_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' packaging/ubuntu/README.md
require_contains 'launchpad_upload_run=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh' "$workflow"
require_contains 'Ubuntu PPA Archive Publication Gate Contract' "$workflow"
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control

printf 'ubuntu_ppa_archive_publication_gate_contract: ok\n'
