#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu upload/signing authority evidence contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu upload/signing authority evidence contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
source_package_contract='docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$source_package_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect upload/signing authority evidence contract' "$contract"
require_contains 'ubuntu_source_package_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=1' "$contract"
require_contains 'source_package_created=1' "$contract"
require_contains 'dsc_digest_recorded=1' "$contract"
require_contains 'changes_file_digest_recorded=1' "$contract"
require_contains 'upload_target_recorded=1' "$contract"
require_contains 'upload_target_kind_recorded=1' "$contract"
require_contains 'upload_authority_reviewed=1' "$contract"
require_contains 'launchpad_account_recorded=1' "$contract"
require_contains 'ppa_or_archive_target_reviewed=1' "$contract"
require_contains 'gpg_signing_key_fingerprint_recorded=1' "$contract"
require_contains 'signature_fingerprint_recorded=1' "$contract"
require_contains 'debsign_command_recorded=1' "$contract"
require_contains 'dput_command_recorded=1' "$contract"
require_contains 'upload_command_non_claims_reviewed=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$contract"
require_contains 'ubuntu_source_package_evidence_unblocked=0' "$contract"
require_contains 'source_package_created=0' "$contract"
require_contains 'dsc_digest_recorded=0' "$contract"
require_contains 'changes_file_digest_recorded=0' "$contract"
require_contains 'upload_target_recorded=0' "$contract"
require_contains 'upload_target_kind_recorded=0' "$contract"
require_contains 'upload_authority_reviewed=0' "$contract"
require_contains 'launchpad_account_recorded=0' "$contract"
require_contains 'ppa_or_archive_target_reviewed=0' "$contract"
require_contains 'gpg_signing_key_fingerprint_recorded=0' "$contract"
require_contains 'signature_fingerprint_recorded=0' "$contract"
require_contains 'debsign_command_recorded=0' "$contract"
require_contains 'dput_command_recorded=0' "$contract"
require_contains 'upload_command_non_claims_reviewed=0' "$contract"
require_contains 'upload_exit_status_recorded=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"
require_contains 'source_package_uploaded=0' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$contract"
require_contains 'ppa_created=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_submission_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_upload_signing_authority_evidence_contract: ok' "$contract"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$status"
require_contains 'upload_target_kind_recorded=0' "$status"
require_contains 'launchpad_account_recorded=0' "$status"
require_contains 'ppa_or_archive_target_reviewed=0' "$status"
require_contains 'gpg_signing_key_fingerprint_recorded=0' "$status"
require_contains 'upload_command_non_claims_reviewed=0' "$status"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$status"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml' "$status"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$source_package_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$source_package_contract"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$source_package_contract"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$publication_gate"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=1' "$publication_gate"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$publication_gate"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$publication_gate"

require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'upload_signing_authority_evidence_contract_present=1' "$static_validation"
require_contains 'upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$static_validation"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$static_validation"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' "$readiness"
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' "$readiness"
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml' "$readiness"

require_contains 'ubuntu_upload_signing_authority_evidence_contract_present=1' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' README.md
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' packaging/ubuntu/README.md
require_contains 'gpg_signing_key_fingerprint_recorded=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh' "$workflow"
require_contains 'Ubuntu Upload Signing Authority Evidence Contract' "$workflow"

printf 'ubuntu_upload_signing_authority_evidence_contract: ok\n'
