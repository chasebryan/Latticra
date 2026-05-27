#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu local deb install/remove evidence contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb install/remove evidence contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
acceptance_gate='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md'
build_transcript_contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-local-deb-install-remove-evidence-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$acceptance_gate"
require_file "$build_transcript_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/install

require_contains 'Status: no-effect local deb install/remove evidence contract' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' "$contract"
require_contains 'local_deb_build_transcript_accepted=1' "$contract"
require_contains 'deb_artifact_created=1' "$contract"
require_contains 'deb_artifact_digest_recorded=1' "$contract"
require_contains 'install_remove_test_environment_recorded=1' "$contract"
require_contains 'install_command_recorded=1' "$contract"
require_contains 'install_exit_status_recorded=1' "$contract"
require_contains 'installed_payload_listing_recorded=1' "$contract"
require_contains 'usr_bin_latticra_installed=1' "$contract"
require_contains 'status_command_after_install_recorded=1' "$contract"
require_contains 'remove_command_recorded=1' "$contract"
require_contains 'remove_exit_status_recorded=1' "$contract"
require_contains 'post_remove_absence_checked=1' "$contract"
require_contains 'residual_payload_reviewed=1' "$contract"
require_contains 'install_remove_findings_classified=1' "$contract"
require_contains 'host_mutation_scope_reviewed=1' "$contract"
require_contains 'ubuntu_install_remove_evidence_unblocked=1' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$contract"
require_contains 'local_deb_build_transcript_accepted=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'deb_artifact_digest_recorded=0' "$contract"
require_contains 'deb_installed_on_host=0' "$contract"
require_contains 'deb_removed_from_host=0' "$contract"
require_contains 'install_remove_test_environment_recorded=0' "$contract"
require_contains 'install_command_recorded=0' "$contract"
require_contains 'install_exit_status_recorded=0' "$contract"
require_contains 'installed_payload_listing_recorded=0' "$contract"
require_contains 'usr_bin_latticra_installed=0' "$contract"
require_contains 'status_command_after_install_recorded=0' "$contract"
require_contains 'remove_command_recorded=0' "$contract"
require_contains 'remove_exit_status_recorded=0' "$contract"
require_contains 'post_remove_absence_checked=0' "$contract"
require_contains 'residual_payload_reviewed=0' "$contract"
require_contains 'install_remove_findings_classified=0' "$contract"
require_contains 'host_mutation_scope_reviewed=0' "$contract"
require_contains 'ubuntu_install_remove_evidence_unblocked=0' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$contract"
require_contains 'ubuntu_publication_gate_unblocked=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'root_installer_ready=0' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract: ok' "$contract"

require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$status"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$status"
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' "$status"
require_contains 'deb_installed_on_host=0' "$status"
require_contains 'deb_removed_from_host=0' "$status"
require_contains 'install_remove_test_environment_recorded=0' "$status"
require_contains 'install_command_recorded=0' "$status"
require_contains 'install_exit_status_recorded=0' "$status"
require_contains 'installed_payload_listing_recorded=0' "$status"
require_contains 'usr_bin_latticra_installed=0' "$status"
require_contains 'status_command_after_install_recorded=0' "$status"
require_contains 'remove_command_recorded=0' "$status"
require_contains 'remove_exit_status_recorded=0' "$status"
require_contains 'post_remove_absence_checked=0' "$status"
require_contains 'residual_payload_reviewed=0' "$status"
require_contains 'install_remove_findings_classified=0' "$status"
require_contains 'host_mutation_scope_reviewed=0' "$status"
require_contains 'ubuntu_install_remove_evidence_unblocked=0' "$status"
require_contains 'ubuntu_publication_gate_unblocked=0' "$status"
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' "$status"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-local-deb-install-remove-evidence-contract.yml' "$status"

require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$acceptance_gate"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$acceptance_gate"
require_contains 'deb_installed_on_host=0' "$acceptance_gate"
require_contains 'deb_removed_from_host=0' "$acceptance_gate"

require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$build_transcript_contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$build_transcript_contract"
require_contains 'deb_removed_from_host=0' "$build_transcript_contract"
require_contains 'ubuntu_ppa_archive_publication_gate_contract_present=1' "$publication_gate"

require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' "$static_validation"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$static_validation"
require_contains 'local_deb_install_remove_evidence_contract_present=1' "$static_validation"
require_contains 'local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$static_validation"
require_contains 'deb_removed_from_host=0' "$static_validation"

require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$readiness"
require_contains 'deb_removed_from_host=0' "$readiness"
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' "$readiness"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' "$readiness"
require_contains 'scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh' "$readiness"
require_contains '.github/workflows/ubuntu-local-deb-install-remove-evidence-contract.yml' "$readiness"

require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' README.md
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' README.md
require_contains 'deb_removed_from_host=0' README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'local_deb_install_remove_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'deb_removed_from_host=0' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh' "$workflow"
require_contains 'Ubuntu Local Deb Install Remove Evidence Contract' "$workflow"
require_contains 'build/latticra usr/bin' packaging/ubuntu/debian/install

printf 'ubuntu_local_deb_install_remove_evidence_contract: ok\n'
