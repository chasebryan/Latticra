#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu local deb static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_file docs/UBUNTU_READINESS_PLAN.md
require_file docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md
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
require_file docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md
require_file docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md
require_file docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md
require_file docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md
require_file docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md
require_file docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/rules
require_file packaging/ubuntu/debian/changelog
require_file packaging/ubuntu/debian/copyright
require_file packaging/ubuntu/debian/install
require_file packaging/ubuntu/debian/source/format
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'static checks for the local-only Ubuntu deb packaging draft' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_inventory_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_inventory_report_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'doc_payload_license_review_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'doc_payload_license_review_status=resolved-cc-by-4.0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'documentation_license_decision_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'third_party_material_review_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'third_party_material_review_status=blocked-pending-third-party-material-review' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'third_party_notice_requirements_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'generated_artifact_notice_review_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'generated_artifact_notice_requirements_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'notice_file_decision_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'notice_file_decision_status=blocked-pending-notice-file-decision' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'notice_file_present=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_copyright_notice_mapping_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_copyright_notice_mapping_reviewed=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'trademark_notice_boundary_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'trademark_notice_boundary_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'release_artifact_notice_requirements_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'release_artifact_notice_requirements_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_promotion_gate_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_promotion_gate_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_license_promotion_gate_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_license_promotion_gate_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'lintian_static_metadata_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'lintian_static_metadata_status=blocked-pending-package-license-promotion' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'lintian_static_metadata_run=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'local_deb_build_transcript_acceptance_gate_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'local_deb_build_transcript_accepted=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'local_deb_install_remove_evidence_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'deb_installed_on_host=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'deb_removed_from_host=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'source_package_evidence_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'dpkg_source_run=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'dpkg_buildpackage_source_run=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'source_package_created=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'source_package_uploaded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_source_package_evidence_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'upload_signing_authority_evidence_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'upload_target_kind_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_account_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ppa_or_archive_target_reviewed=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'gpg_signing_key_fingerprint_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'upload_command_non_claims_reviewed=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_build_result_evidence_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_upload_url_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_build_result_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_binary_artifact_listing_recorded=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ppa_archive_publication_gate_contract_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'launchpad_upload_run=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_publication_gate_unblocked=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'deb_artifact_created=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_archive_ready=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_local_deb_static_validation: ok' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md

require_contains 'Status: local-only packaging draft' packaging/ubuntu/README.md
require_contains 'not an Ubuntu archive package' packaging/ubuntu/README.md
require_contains 'not a PPA package' packaging/ubuntu/README.md
require_contains 'deb_artifact_created=0' packaging/ubuntu/README.md
require_contains 'package_notice_inventory_present=1' packaging/ubuntu/README.md
require_contains 'package_notice_inventory_report_present=1' packaging/ubuntu/README.md
require_contains 'doc_payload_license_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'doc_payload_license_review_status=resolved-cc-by-4.0' packaging/ubuntu/README.md
require_contains 'third_party_material_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'third_party_material_review_status=blocked-pending-third-party-material-review' packaging/ubuntu/README.md
require_contains 'generated_artifact_notice_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review' packaging/ubuntu/README.md
require_contains 'notice_file_decision_contract_present=1' packaging/ubuntu/README.md
require_contains 'notice_file_decision_status=blocked-pending-notice-file-decision' packaging/ubuntu/README.md
require_contains 'debian_copyright_notice_mapping_contract_present=1' packaging/ubuntu/README.md
require_contains 'debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping' packaging/ubuntu/README.md
require_contains 'trademark_notice_boundary_contract_present=1' packaging/ubuntu/README.md
require_contains 'trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary' packaging/ubuntu/README.md
require_contains 'release_artifact_notice_requirements_contract_present=1' packaging/ubuntu/README.md
require_contains 'release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements' packaging/ubuntu/README.md
require_contains 'package_notice_promotion_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites' packaging/ubuntu/README.md
require_contains 'package_license_promotion_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites' packaging/ubuntu/README.md
require_contains 'package_license_promotion_gate_unblocked=0' packaging/ubuntu/README.md
require_contains 'lintian_static_metadata_contract_present=1' packaging/ubuntu/README.md
require_contains 'lintian_static_metadata_status=blocked-pending-package-license-promotion' packaging/ubuntu/README.md
require_contains 'lintian_static_metadata_run=0' packaging/ubuntu/README.md
require_contains 'local_deb_build_transcript_acceptance_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript' packaging/ubuntu/README.md
require_contains 'local_deb_build_transcript_accepted=0' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'local_deb_install_remove_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'deb_installed_on_host=0' packaging/ubuntu/README.md
require_contains 'deb_removed_from_host=0' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'source_package_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'source_package_evidence_status=blocked-pending-accepted-build-transcript' packaging/ubuntu/README.md
require_contains 'dpkg_source_run=0' packaging/ubuntu/README.md
require_contains 'dpkg_buildpackage_source_run=0' packaging/ubuntu/README.md
require_contains 'source_package_created=0' packaging/ubuntu/README.md
require_contains 'source_package_uploaded=0' packaging/ubuntu/README.md
require_contains 'ubuntu_source_package_evidence_unblocked=0' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'upload_signing_authority_evidence_status=blocked-pending-source-package-evidence' packaging/ubuntu/README.md
require_contains 'upload_target_kind_recorded=0' packaging/ubuntu/README.md
require_contains 'launchpad_account_recorded=0' packaging/ubuntu/README.md
require_contains 'ppa_or_archive_target_reviewed=0' packaging/ubuntu/README.md
require_contains 'gpg_signing_key_fingerprint_recorded=0' packaging/ubuntu/README.md
require_contains 'upload_command_non_claims_reviewed=0' packaging/ubuntu/README.md
require_contains 'ubuntu_upload_signing_authority_evidence_unblocked=0' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_contract_present=1' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence' packaging/ubuntu/README.md
require_contains 'launchpad_upload_url_recorded=0' packaging/ubuntu/README.md
require_contains 'launchpad_build_result_recorded=0' packaging/ubuntu/README.md
require_contains 'launchpad_binary_artifact_listing_recorded=0' packaging/ubuntu/README.md
require_contains 'ubuntu_launchpad_build_result_evidence_unblocked=0' packaging/ubuntu/README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence' packaging/ubuntu/README.md
require_contains 'launchpad_upload_run=0' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_gate_unblocked=0' packaging/ubuntu/README.md
require_contains 'ppa_claimed=0' packaging/ubuntu/README.md
require_contains 'ubuntu_archive_ready=0' packaging/ubuntu/README.md

require_contains 'Source: latticra' packaging/ubuntu/debian/control
require_contains 'Build-Depends:' packaging/ubuntu/debian/control
require_contains 'debhelper-compat (= 13)' packaging/ubuntu/debian/control
require_contains 'gcc' packaging/ubuntu/debian/control
require_contains 'make' packaging/ubuntu/debian/control
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control
require_contains 'Package: latticra' packaging/ubuntu/debian/control
require_contains 'Architecture: any' packaging/ubuntu/debian/control
require_contains 'local Ubuntu draft records package shape only' packaging/ubuntu/debian/control

require_contains 'sh scripts/test-state-lattice.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-system-bootstrap.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-kernel.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-kernel-lifecycle.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' packaging/ubuntu/debian/rules
require_contains 'cc $(CFLAGS) $(CPPFLAGS) -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra $(LDFLAGS)' packaging/ubuntu/debian/rules

require_contains 'latticra (0.0.0-0ubuntu0.1local1) UNRELEASED' packaging/ubuntu/debian/changelog
require_contains 'LOCAL-ONLY DRAFT' packaging/ubuntu/debian/copyright
require_contains 'License: AGPL-3.0-or-later' packaging/ubuntu/debian/copyright
require_contains 'build/latticra usr/bin' packaging/ubuntu/debian/install
require_contains 'README.md usr/share/doc/latticra' packaging/ubuntu/debian/install
require_contains '3.0 (quilt)' packaging/ubuntu/debian/source/format

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent '.service' packaging/ubuntu/debian/control
require_absent '.service' packaging/ubuntu/debian/rules
require_absent '.service' packaging/ubuntu/debian/install
require_absent 'systemctl' packaging/ubuntu/debian/control
require_absent 'systemctl' packaging/ubuntu/debian/rules
require_absent 'systemctl' packaging/ubuntu/debian/install
require_absent '/etc/latticra' packaging/ubuntu/debian/install
require_absent '/boot/latticra' packaging/ubuntu/debian/install
require_absent '/usr/lib/modules' packaging/ubuntu/debian/install
require_absent '/usr/share/selinux' packaging/ubuntu/debian/install

printf 'ubuntu_local_deb_static_validation: ok\n'
