#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu local deb build transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb build transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'

require_file "$contract"
require_file "$status"
require_file docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_file docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
require_file docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md
require_file docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md
require_file docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md
require_file docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md
require_file docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md
require_file docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
require_file docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
require_file docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_file docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md
require_file docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md
require_file packaging/ubuntu/README.md
require_file scripts/test-ubuntu-local-deb-static-validation.sh

require_contains 'Status: no-effect transcript contract' "$contract"
require_contains 'transcript_kind=ubuntu-local-deb-build' "$contract"
require_contains 'host_os_id=ubuntu' "$contract"
require_contains 'source_tree_dirty_state_recorded=1' "$contract"
require_contains 'dpkg_buildpackage_available=1' "$contract"
require_contains 'lintian_available_recorded=1' "$contract"
require_contains 'rules_requires_root_no=1' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'license_expression_unresolved=0' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'license_expression_unresolved=0' "$contract"
require_contains 'ubuntu_package_notice_inventory_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$contract"
require_contains 'ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0' "$contract"
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
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$contract"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$contract"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$contract"
require_contains 'ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$contract"
require_contains 'dpkg_buildpackage_command_recorded=1' "$contract"
require_contains 'deb_artifact_digest_recorded=1' "$contract"
require_contains 'lintian_output_digest_recorded=1' "$contract"
require_contains 'expected_draft_findings_classified=1' "$contract"
require_contains 'unexpected_findings_classified=1' "$contract"
require_contains 'usr_bin_latticra_present=1' "$contract"
require_contains 'systemd_service_present=0' "$contract"
require_contains 'kernel_module_present=0' "$contract"
require_contains 'boot_entry_present=0' "$contract"
require_contains 'etc_latticra_present=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_ready=0' "$contract"
require_contains 'production_installer_ready=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_contract_present=1' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_present=0' "$contract"
require_contains 'local_deb_build_transcript_accepted=0' "$contract"
require_contains 'build_transcript_acceptance_gate_unblocked=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'deb_artifact_installed=0' "$contract"
require_contains 'deb_removed_from_host=0' "$contract"
require_contains 'ubuntu_local_deb_build_transcript_contract: ok' "$contract"

require_contains 'ubuntu_lintian_availability_present=1' "$status"
require_contains 'ubuntu_local_deb_build_transcript_contract_present=1' "$status"
require_contains 'ubuntu_local_deb_build_transcript_present=0' "$status"
require_contains 'license_expression_reviewed=1' "$status"
require_contains 'license_expression_unresolved=0' "$status"
require_contains 'ubuntu_package_license_review_contract_present=1' "$status"
require_contains 'ubuntu_package_license_review_status=resolved-license-expression-recorded' "$status"
require_contains 'ubuntu_package_notice_inventory_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_contract_present=1' "$status"
require_contains 'ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0' "$status"
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
require_contains 'ubuntu_package_notice_promotion_gate_contract_present=1' "$status"
require_contains 'ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$status"
require_contains 'ubuntu_package_license_promotion_gate_contract_present=1' "$status"
require_contains 'ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' "$status"
require_contains 'ubuntu_lintian_static_metadata_contract_present=1' "$status"
require_contains 'ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion' "$status"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1' "$status"
require_contains 'ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' "$status"
require_contains 'ubuntu_package_notice_review_contract_present=1' "$status"
require_contains 'ubuntu_package_notice_review_status=blocked-pending-notice-review' "$status"
require_contains 'packaging_license_expression_updated=1' "$status"
require_contains 'ubuntu_local_deb_install_remove_evidence_contract_present=1' "$status"
require_contains 'ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' "$status"

printf 'ubuntu_local_deb_build_transcript_contract: ok\n'
