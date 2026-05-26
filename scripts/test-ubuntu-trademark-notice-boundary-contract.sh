#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu trademark notice boundary contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu trademark notice boundary contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
notice_contract='docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md'
doc_license_contract='docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md'
third_party_contract='docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md'
generated_artifact_contract='docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md'
notice_file_contract='docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md'
copyright_mapping_contract='docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md'
release_artifact_contract='docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md'
license_contract='docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-trademark-notice-boundary-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$notice_contract"
require_file "$doc_license_contract"
require_file "$third_party_contract"
require_file "$generated_artifact_contract"
require_file "$notice_file_contract"
require_file "$copyright_mapping_contract"
require_file "$release_artifact_contract"
require_file "$license_contract"
require_file "$readiness"
require_file "$workflow"
require_file TRADEMARK_POLICY.md
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/copyright

require_contains 'Status: no-effect trademark notice boundary contract' "$contract"
require_contains 'package_scope=local-deb-draft' "$contract"
require_contains 'trademark_policy_present=1' "$contract"
require_contains 'project_identity_terms_recorded=1' "$contract"
require_contains 'binary_payload=usr/bin/latticra' "$contract"
require_contains 'doc_payload=usr/share/doc/latticra/README.md' "$contract"
require_contains 'debian_control_file=packaging/ubuntu/debian/control' "$contract"
require_contains 'debian_copyright_file=packaging/ubuntu/debian/copyright' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$contract"
require_contains 'trademark_notice_boundary_recorded=1' "$contract"
require_contains 'trademark_policy_applied_to_package_notice=1' "$contract"
require_contains 'package_description_endorsement_boundary_reviewed=1' "$contract"
require_contains 'debian_copyright_trademark_notice_boundary_reviewed=1' "$contract"
require_contains 'documentation_trademark_boundary_reviewed=1' "$contract"
require_contains 'canonical_endorsement_boundary_reviewed=1' "$contract"
require_contains 'project_identity_downstream_use_boundary_recorded=1' "$contract"
require_contains 'trademark_notice_missing_required_entries=0' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$contract"
require_contains 'trademark_notice_boundary_recorded=0' "$contract"
require_contains 'trademark_policy_applied_to_package_notice=0' "$contract"
require_contains 'package_description_endorsement_boundary_reviewed=0' "$contract"
require_contains 'debian_copyright_trademark_notice_boundary_reviewed=0' "$contract"
require_contains 'documentation_trademark_boundary_reviewed=0' "$contract"
require_contains 'canonical_endorsement_boundary_reviewed=0' "$contract"
require_contains 'project_identity_downstream_use_boundary_recorded=0' "$contract"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_contract: ok' "$contract"

require_contains 'Software and documentation licenses do not grant trademark' TRADEMARK_POLICY.md
require_contains 'Canonical endorsement' "$contract"
require_contains 'local Ubuntu draft records package shape only' packaging/ubuntu/debian/control
require_contains 'LOCAL-ONLY DRAFT' packaging/ubuntu/debian/copyright

require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$status"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$status"
require_contains 'trademark_notice_boundary_recorded=0' "$status"
require_contains 'trademark_policy_applied_to_package_notice=0' "$status"
require_contains 'package_description_endorsement_boundary_reviewed=0' "$status"
require_contains 'debian_copyright_trademark_notice_boundary_reviewed=0' "$status"
require_contains 'documentation_trademark_boundary_reviewed=0' "$status"
require_contains 'canonical_endorsement_boundary_reviewed=0' "$status"
require_contains 'project_identity_downstream_use_boundary_recorded=0' "$status"
require_contains 'docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-trademark-notice-boundary-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-trademark-notice-boundary-contract.yml' "$status"

require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$notice_contract"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$notice_contract"
require_contains 'trademark_notice_boundary_recorded=1' "$notice_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$doc_license_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$third_party_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$generated_artifact_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$notice_file_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$copyright_mapping_contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$release_artifact_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$license_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$readiness"
require_contains 'docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md' README.md
require_contains 'sh scripts/test-ubuntu-trademark-notice-boundary-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-trademark-notice-boundary-contract.sh' "$workflow"

printf 'ubuntu_trademark_notice_boundary_contract: ok\n'
