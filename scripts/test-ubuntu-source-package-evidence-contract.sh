#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu source package evidence contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu source package evidence contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
upload_signing_contract='docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-source-package-evidence-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$upload_signing_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/changelog
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/source/format

require_contains 'Status: no-effect source package evidence contract' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$contract"
require_contains 'local_deb_build_transcript_accepted=1' "$contract"
require_contains 'source_package_build_environment_recorded=1' "$contract"
require_contains 'dpkg_source_command_recorded=1' "$contract"
require_contains 'dpkg_buildpackage_source_command_recorded=1' "$contract"
require_contains 'source_package_created=1' "$contract"
require_contains 'source_package_name_recorded=1' "$contract"
require_contains 'source_package_digest_recorded=1' "$contract"
require_contains 'dsc_path_recorded=1' "$contract"
require_contains 'dsc_digest_recorded=1' "$contract"
require_contains 'changes_file_path_recorded=1' "$contract"
require_contains 'changes_file_digest_recorded=1' "$contract"
require_contains 'orig_tarball_path_recorded=1' "$contract"
require_contains 'orig_tarball_digest_recorded=1' "$contract"
require_contains 'debian_source_format_verified=1' "$contract"
require_contains 'source_package_payload_reviewed=1' "$contract"
require_contains 'source_package_notice_requirements_reviewed=1' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$contract"
require_contains 'local_deb_build_transcript_accepted=0' "$contract"
require_contains 'source_package_build_environment_recorded=0' "$contract"
require_contains 'dpkg_source_command_recorded=0' "$contract"
require_contains 'dpkg_buildpackage_source_command_recorded=0' "$contract"
require_contains 'dpkg_source_run=0' "$contract"
require_contains 'dpkg_buildpackage_source_run=0' "$contract"
require_contains 'source_package_created=0' "$contract"
require_contains 'source_package_name_recorded=0' "$contract"
require_contains 'source_package_digest_recorded=0' "$contract"
require_contains 'dsc_path_recorded=0' "$contract"
require_contains 'dsc_digest_recorded=0' "$contract"
require_contains 'changes_file_path_recorded=0' "$contract"
require_contains 'changes_file_digest_recorded=0' "$contract"
require_contains 'orig_tarball_path_recorded=0' "$contract"
require_contains 'orig_tarball_digest_recorded=0' "$contract"
require_contains 'debian_source_format_verified=0' "$contract"
require_contains 'source_package_payload_reviewed=0' "$contract"
require_contains 'source_package_notice_requirements_reviewed=0' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$contract"
require_contains 'debsign_command_recorded=0' "$contract"
require_contains 'dput_command_recorded=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"
require_contains 'source_package_uploaded=0' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_source_package_evidence_contract: ok' "$contract"

require_contains 'ubuntu_source_package_evidence_contract_present=1' "$status"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$status"
require_contains 'source_package_build_environment_recorded=0' "$status"
require_contains 'dpkg_source_command_recorded=0' "$status"
require_contains 'dpkg_buildpackage_source_command_recorded=0' "$status"
require_contains 'dpkg_source_run=0' "$status"
require_contains 'dpkg_buildpackage_source_run=0' "$status"
require_contains 'source_package_created=0' "$status"
require_contains 'source_package_name_recorded=0' "$status"
require_contains 'source_package_digest_recorded=0' "$status"
require_contains 'dsc_path_recorded=0' "$status"
require_contains 'dsc_digest_recorded=0' "$status"
require_contains 'changes_file_path_recorded=0' "$status"
require_contains 'orig_tarball_path_recorded=0' "$status"
require_contains 'orig_tarball_digest_recorded=0' "$status"
require_contains 'debian_source_format_verified=0' "$status"
require_contains 'source_package_payload_reviewed=0' "$status"
require_contains 'source_package_notice_requirements_reviewed=0' "$status"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$status"
require_contains 'source_package_uploaded=0' "$status"
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-source-package-evidence-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-source-package-evidence-contract.yml' "$status"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$upload_signing_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$upload_signing_contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$publication_gate"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$publication_gate"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$publication_gate"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$publication_gate"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$publication_gate"

require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'source_package_evidence_contract_present=1' "$static_validation"
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' "$static_validation"
require_contains 'upload_signing_authority_evidence_contract_present=1' "$static_validation"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$static_validation"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$readiness"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$readiness"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$readiness"
require_contains 'scripts/test-ubuntu-source-package-evidence-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml' "$readiness"
require_contains '.github/workflows/ubuntu-source-package-evidence-contract.yml' "$readiness"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' README.md
require_contains 'ubuntu_source_package_evidence_contract_present=1' README.md
require_contains 'ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' README.md
require_contains 'ubuntu_source_package_evidence_unblocked=0' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'source_package_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'source_package_uploaded=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-source-package-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-source-package-evidence-contract.sh' "$workflow"
require_contains 'Ubuntu Source Package Evidence Contract' "$workflow"
require_contains 'latticra (0.0.0-0ubuntu0.1local1) UNRELEASED' packaging/ubuntu/debian/changelog
require_contains 'Source: latticra' packaging/ubuntu/debian/control
require_contains '3.0 (quilt)' packaging/ubuntu/debian/source/format

printf 'ubuntu_source_package_evidence_contract: ok\n'
