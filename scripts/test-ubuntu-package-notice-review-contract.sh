#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu package notice review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu package notice review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md'
inventory='docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md'
doc_license_contract='docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md'
third_party_contract='docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md'
generated_artifact_contract='docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md'
notice_file_contract='docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md'
copyright_mapping_contract='docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md'
trademark_contract='docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md'
release_artifact_contract='docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md'
license_contract='docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
workflow='.github/workflows/ubuntu-package-notice-review-contract.yml'

require_file "$contract"
require_file "$inventory"
require_file "$doc_license_contract"
require_file "$third_party_contract"
require_file "$generated_artifact_contract"
require_file "$notice_file_contract"
require_file "$copyright_mapping_contract"
require_file "$trademark_contract"
require_file "$release_artifact_contract"
require_file "$license_contract"
require_file "$status"
require_file "$workflow"
require_file scripts/ubuntu-package-notice-inventory.sh
require_file docs/LICENSE_POLICY.md
require_file docs/LICENSE_MIGRATION_PLAN.md
require_file TRADEMARK_POLICY.md
require_file README.md
require_file packaging/ubuntu/debian/copyright

require_contains 'Status: no-effect notice and documentation-license review contract' "$contract"
require_contains 'third_party_material_policy_present=1' "$contract"
require_contains 'generated_artifact_notice_policy_present=1' "$contract"
require_contains 'ubuntu_package_notice_inventory_present=1' "$contract"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' "$contract"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$contract"
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' "$contract"
require_contains 'ubuntu_notice_file_decision_contract_present=1' "$contract"
require_contains 'ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements' "$contract"
require_contains 'third_party_material_inventory_recorded=1' "$contract"
require_contains 'notice_file_present=0' "$contract"
require_contains 'documentation_license_decision_present=0' "$contract"
require_contains 'binary_payload=usr/bin/latticra' "$contract"
require_contains 'binary_payload_source=src/latticra_cli.c' "$contract"
require_contains 'doc_payload=usr/share/doc/latticra/README.md' "$contract"
require_contains 'doc_payload_source=README.md' "$contract"
require_contains 'doc_payload_license_decision_recorded=1' "$contract"
require_contains 'third_party_material_inventory_reviewed=1' "$contract"
require_contains 'generated_artifact_notice_reviewed=1' "$contract"
require_contains 'notice_file_required_decision_recorded=1' "$contract"
require_contains 'notice_file_content_requirements_recorded=1' "$contract"
require_contains 'notice_file_decision_recorded=1' "$contract"
require_contains 'debian_copyright_notice_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_binary_payload_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_doc_payload_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_third_party_notice_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_generated_artifact_notice_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_notice_file_mapping_reviewed=1' "$contract"
require_contains 'debian_copyright_trademark_notice_boundary_reviewed=1' "$contract"
require_contains 'debian_copyright_license_ref_replaced_or_justified=1' "$contract"
require_contains 'trademark_notice_boundary_recorded=1' "$contract"
require_contains 'trademark_policy_applied_to_package_notice=1' "$contract"
require_contains 'package_description_endorsement_boundary_reviewed=1' "$contract"
require_contains 'documentation_trademark_boundary_reviewed=1' "$contract"
require_contains 'canonical_endorsement_boundary_reviewed=1' "$contract"
require_contains 'project_identity_downstream_use_boundary_recorded=1' "$contract"
require_contains 'release_artifact_notice_requirements_recorded=1' "$contract"
require_contains 'source_package_notice_requirements_recorded=1' "$contract"
require_contains 'release_notes_notice_requirements_recorded=1' "$contract"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review' "$contract"
require_contains 'ubuntu_package_notice_inventory_present=1' "$contract"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' "$contract"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$contract"
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$contract"
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' "$contract"
require_contains 'ubuntu_notice_file_decision_contract_present=1' "$contract"
require_contains 'ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$contract"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$contract"
require_contains 'ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements' "$contract"
require_contains 'doc_payload_license_reviewed=0' "$contract"
require_contains 'doc_payload_license_unresolved=1' "$contract"
require_contains 'doc_payload_license_decision_recorded=0' "$contract"
require_contains 'third_party_material_inventory_reviewed=0' "$contract"
require_contains 'third_party_notice_requirements_recorded=0' "$contract"
require_contains 'generated_artifact_notice_reviewed=0' "$contract"
require_contains 'generated_artifact_notice_requirements_recorded=0' "$contract"
require_contains 'third_party_notice_reviewed=0' "$contract"
require_contains 'notice_file_present=0' "$contract"
require_contains 'notice_file_decision_recorded=0' "$contract"
require_contains 'notice_file_required_decision_recorded=0' "$contract"
require_contains 'notice_file_content_requirements_recorded=0' "$contract"
require_contains 'debian_copyright_notice_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_binary_payload_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_doc_payload_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_third_party_notice_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_generated_artifact_notice_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_notice_file_mapping_reviewed=0' "$contract"
require_contains 'debian_copyright_trademark_notice_boundary_reviewed=0' "$contract"
require_contains 'debian_copyright_license_ref_replaced_or_justified=0' "$contract"
require_contains 'trademark_notice_boundary_recorded=0' "$contract"
require_contains 'trademark_policy_applied_to_package_notice=0' "$contract"
require_contains 'package_description_endorsement_boundary_reviewed=0' "$contract"
require_contains 'documentation_trademark_boundary_reviewed=0' "$contract"
require_contains 'canonical_endorsement_boundary_reviewed=0' "$contract"
require_contains 'project_identity_downstream_use_boundary_recorded=0' "$contract"
require_contains 'release_artifact_notice_requirements_recorded=0' "$contract"
require_contains 'source_package_notice_requirements_recorded=0' "$contract"
require_contains 'release_notes_notice_requirements_recorded=0' "$contract"
require_contains 'ubuntu_package_license_review_unblocked=0' "$contract"
require_contains 'ubuntu_lintian_static_metadata_unblocked=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_unblocked=0' "$contract"
require_contains 'ubuntu_package_notice_review_contract: ok' "$contract"

require_contains 'Third-party material must include source, license, and compatibility notes before being added.' docs/LICENSE_POLICY.md
require_contains 'Generated artifacts may need additional notices' docs/LICENSE_POLICY.md
require_contains 'NOTICE file' docs/LICENSE_POLICY.md
require_contains 'Documentation license remains undecided' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'Software and documentation licenses do not grant trademark' TRADEMARK_POLICY.md
require_contains 'LicenseRef-Latticra-TBD' packaging/ubuntu/debian/copyright

require_contains 'ubuntu_package_notice_review_contract_present=1' "$status"
require_contains 'ubuntu_package_notice_inventory_present=1' "$status"
require_contains 'ubuntu_package_notice_inventory_report_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision' "$status"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$status"
require_contains 'ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review' "$status"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$status"
require_contains 'ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' "$status"
require_contains 'ubuntu_notice_file_decision_contract_present=1' "$status"
require_contains 'ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision' "$status"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$status"
require_contains 'ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping' "$status"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$status"
require_contains 'ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' "$status"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$status"
require_contains 'ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements' "$status"
require_contains 'ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review' "$status"
require_contains 'doc_payload_license_reviewed=0' "$status"
require_contains 'doc_payload_license_unresolved=1' "$status"
require_contains 'doc_payload_license_decision_recorded=0' "$status"
require_contains 'third_party_material_inventory_recorded=1' "$status"
require_contains 'third_party_material_inventory_reviewed=0' "$status"
require_contains 'third_party_notice_requirements_recorded=0' "$status"
require_contains 'generated_artifact_notice_reviewed=0' "$status"
require_contains 'generated_artifact_notice_requirements_recorded=0' "$status"
require_contains 'third_party_notice_reviewed=0' "$status"
require_contains 'notice_file_present=0' "$status"
require_contains 'notice_file_decision_recorded=0' "$status"
require_contains 'notice_file_required_decision_recorded=0' "$status"
require_contains 'debian_copyright_notice_mapping_reviewed=0' "$status"
require_contains 'debian_copyright_binary_payload_mapping_reviewed=0' "$status"
require_contains 'debian_copyright_notice_file_mapping_reviewed=0' "$status"
require_contains 'debian_copyright_license_ref_replaced_or_justified=0' "$status"
require_contains 'trademark_notice_boundary_recorded=0' "$status"
require_contains 'trademark_policy_applied_to_package_notice=0' "$status"
require_contains 'canonical_endorsement_boundary_reviewed=0' "$status"
require_contains 'release_artifact_notice_requirements_recorded=0' "$status"
require_contains 'source_package_notice_requirements_recorded=0' "$status"
require_contains 'release_notes_notice_requirements_recorded=0' "$status"
require_contains 'ubuntu_package_notice_review_unblocked=0' "$status"
require_contains 'ubuntu_package_license_review_unblocked=0' "$status"
require_contains 'docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md' "$status"
require_contains '.github/workflows/ubuntu-package-notice-review-contract.yml' "$status"

require_contains 'ubuntu_package_notice_inventory_present=1' "$inventory"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$doc_license_contract"
require_contains 'ubuntu_third_party_material_review_contract_present=1' "$third_party_contract"
require_contains 'ubuntu_generated_artifact_notice_review_contract_present=1' "$generated_artifact_contract"
require_contains 'ubuntu_notice_file_decision_contract_present=1' "$notice_file_contract"
require_contains 'ubuntu_debian_copyright_notice_mapping_contract_present=1' "$copyright_mapping_contract"
require_contains 'ubuntu_trademark_notice_boundary_contract_present=1' "$trademark_contract"
require_contains 'ubuntu_release_artifact_notice_requirements_contract_present=1' "$release_artifact_contract"
require_contains 'documentation scope, and notice obligations' "$license_contract"
require_contains 'sh scripts/test-ubuntu-package-notice-review-contract.sh' "$workflow"

printf 'ubuntu_package_notice_review_contract: ok\n'
