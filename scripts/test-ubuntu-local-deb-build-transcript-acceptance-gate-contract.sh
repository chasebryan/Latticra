#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu local deb build transcript acceptance gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb build transcript acceptance gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
build_transcript_contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md'
lintian_static_contract='docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md'
license_gate='docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md'
install_remove_contract='docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-local-deb-build-transcript-acceptance-gate-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$build_transcript_contract"
require_file "$lintian_static_contract"
require_file "$license_gate"
require_file "$install_remove_contract"
require_file "$static_validation"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/install

require_contains 'Status: no-effect local deb build transcript acceptance gate contract' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_present=1' "$contract"
require_contains 'transcript_header_reviewed=1' "$contract"
require_contains 'tooling_evidence_reviewed=1' "$contract"
require_contains 'package_evidence_reviewed=1' "$contract"
require_contains 'build_evidence_reviewed=1' "$contract"
require_contains 'payload_evidence_reviewed=1' "$contract"
require_contains 'non_claims_reviewed=1' "$contract"
require_contains 'deb_artifact_digest_recorded=1' "$contract"
require_contains 'changes_file_digest_recorded=1' "$contract"
require_contains 'build_log_digest_recorded=1' "$contract"
require_contains 'lintian_output_digest_recorded=1' "$contract"
require_contains 'expected_draft_findings_classified=1' "$contract"
require_contains 'unexpected_findings_classified=1' "$contract"
require_contains 'build_transcript_acceptance_gate_unblocked=1' "$contract"
require_contains 'local_deb_build_transcript_accepted=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_present=0' "$contract"
require_contains 'build_transcript_acceptance_gate_open=0' "$contract"
require_contains 'build_transcript_acceptance_gate_unblocked=0' "$contract"
require_contains 'local_deb_build_transcript_accepted=0' "$contract"
require_contains 'transcript_header_reviewed=0' "$contract"
require_contains 'tooling_evidence_reviewed=0' "$contract"
require_contains 'package_evidence_reviewed=0' "$contract"
require_contains 'build_evidence_reviewed=0' "$contract"
require_contains 'payload_evidence_reviewed=0' "$contract"
require_contains 'non_claims_reviewed=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'deb_artifact_installed=0' "$contract"
require_contains 'deb_installed_on_host=0' "$contract"
require_contains 'deb_removed_from_host=0' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract: ok' "$contract"

require_contains 'Status: no-effect transcript contract' "$build_transcript_contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$lintian_static_contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$license_gate"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$install_remove_contract"
require_contains 'deb_artifact_created=0' "$static_validation"
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control
require_contains 'build/latticra usr/bin' packaging/ubuntu/debian/install

require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$status"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' "$status"
require_contains 'build_transcript_acceptance_gate_open=0' "$status"
require_contains 'build_transcript_acceptance_gate_unblocked=0' "$status"
require_contains 'local_deb_build_transcript_accepted=0' "$status"
require_contains 'transcript_header_reviewed=0' "$status"
require_contains 'tooling_evidence_reviewed=0' "$status"
require_contains 'package_evidence_reviewed=0' "$status"
require_contains 'build_evidence_reviewed=0' "$status"
require_contains 'payload_evidence_reviewed=0' "$status"
require_contains 'non_claims_reviewed=0' "$status"
require_contains 'ubuntu_local_deb_build_transcript_present=0' "$status"
require_contains 'deb_artifact_created=0' "$status"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$status"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$status"
require_contains 'docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-local-deb-build-transcript-acceptance-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-local-deb-build-transcript-acceptance-gate-contract.yml' "$status"

require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$build_transcript_contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$readiness"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$readiness"
require_contains 'local_deb_build_transcript_acceptance_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'sh scripts/test-ubuntu-local-deb-build-transcript-acceptance-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-local-deb-build-transcript-acceptance-gate-contract.sh' "$workflow"

printf 'ubuntu_local_deb_build_transcript_acceptance_gate_contract: ok\n'
