#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu package notice promotion gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu package notice promotion gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
notice_contract='docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md'
doc_license_contract='docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md'
third_party_contract='docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md'
generated_artifact_contract='docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md'
notice_file_contract='docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md'
copyright_mapping_contract='docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md'
trademark_contract='docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md'
release_artifact_contract='docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md'
license_contract='docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
workflow='.github/workflows/ubuntu-package-notice-promotion-gate-contract.yml'

require_file "$contract"
require_file "$status"
require_file "$notice_contract"
require_file "$doc_license_contract"
require_file "$third_party_contract"
require_file "$generated_artifact_contract"
require_file "$notice_file_contract"
require_file "$copyright_mapping_contract"
require_file "$trademark_contract"
require_file "$release_artifact_contract"
require_file "$license_contract"
require_file "$readiness"
require_file "$workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect package notice promotion gate contract' "$contract"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$contract"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_notice_file_decision_contract_present=1' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$contract"
require_contains 'doc_payload_license_decision_recorded=1' "$contract"
require_contains 'third_party_material_inventory_reviewed=1' "$contract"
require_contains 'generated_artifact_notice_reviewed=1' "$contract"
require_contains 'notice_file_decision_recorded=1' "$contract"
require_contains 'debian_copyright_notice_mapping_reviewed=1' "$contract"
require_contains 'trademark_notice_boundary_recorded=1' "$contract"
require_contains 'release_artifact_notice_requirements_recorded=1' "$contract"
require_contains 'ubuntu_package_notice_review_unblocked=1' "$contract"
require_contains 'ubuntu_package_license_review_unblocked=1' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$contract"
require_contains 'doc_payload_license_decision_recorded=1' "$contract"
require_contains 'third_party_material_inventory_reviewed=0' "$contract"
require_contains 'generated_artifact_notice_reviewed=0' "$contract"
require_contains 'notice_file_decision_recorded=0' "$contract"
require_contains 'debian_copyright_notice_mapping_reviewed=0' "$contract"
require_contains 'trademark_notice_boundary_recorded=0' "$contract"
require_contains 'release_artifact_notice_requirements_recorded=0' "$contract"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$contract"
require_contains 'ubuntu_package_license_review_unblocked=1' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract: ok' "$contract"

require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$status"
require_contains 'ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$status"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$status"
require_contains 'ubuntu_package_license_review_unblocked=1' "$status"
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md' "$status"
require_contains 'scripts/test-ubuntu-package-notice-promotion-gate-contract.sh' "$status"
require_contains '.github/workflows/ubuntu-package-notice-promotion-gate-contract.yml' "$status"

require_contains 'ubuntu_package_notice_review_status=blocked-pending-notice-review' "$notice_contract"
require_contains 'doc_payload_license_decision_recorded=1' "$doc_license_contract"
require_contains 'third_party_material_inventory_reviewed=0' "$third_party_contract"
require_contains 'generated_artifact_notice_reviewed=0' "$generated_artifact_contract"
require_contains 'notice_file_decision_recorded=0' "$notice_file_contract"
require_contains 'debian_copyright_notice_mapping_reviewed=0' "$copyright_mapping_contract"
require_contains 'trademark_notice_boundary_recorded=0' "$trademark_contract"
require_contains 'release_artifact_notice_requirements_recorded=0' "$release_artifact_contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$license_contract"
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$readiness"
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md' README.md
require_contains 'sh scripts/test-ubuntu-package-notice-promotion-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-package-notice-promotion-gate-contract.sh' "$workflow"

printf 'ubuntu_package_notice_promotion_gate_contract: ok\n'
