#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package payload inspection contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package payload inspection contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package payload inspection contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
require_file "$artifact_contract"
require_file "$environment_contract"
require_file "$gate_contract"
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_file docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/README.md
require_file docs/status/README.md
require_file packaging/debian/README.md
require_file packaging/debian/debian/control
require_file packaging/debian/debian/install
require_file packaging/freebsd/README.md
require_file packaging/freebsd/pkg-plist
require_file packaging/openbsd/README.md
require_file packaging/openbsd/pkg/PLIST
require_file README.md
require_file .github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml

require_contains 'Status: active package payload inspection contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'payload_inspection_contract_present=1' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'artifact_naming_contract_state=specified-no-effect' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'package_payload_inspection_run=0' "$contract"
require_contains 'debian_payload_inspection_run=0' "$contract"
require_contains 'freebsd_payload_inspection_run=0' "$contract"
require_contains 'openbsd_payload_inspection_run=0' "$contract"
require_contains 'package_payload_accepted=0' "$contract"
require_contains 'package_artifact_sha256_recorded=0' "$contract"
require_contains 'install_on_host_run=0' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'payload_cli_path_required=1' "$contract"
require_contains 'payload_doc_readme_required=1' "$contract"
require_contains 'payload_service_files_allowed=0' "$contract"
require_contains 'payload_init_files_allowed=0' "$contract"
require_contains 'payload_kernel_files_allowed=0' "$contract"
require_contains 'payload_privileged_helper_allowed=0' "$contract"
require_contains 'payload_network_authority_allowed=0' "$contract"
require_contains 'payload_host_mutation_hooks_allowed=0' "$contract"

require_contains 'debian_payload_expected_bin=usr/bin/latticra' "$contract"
require_contains 'debian_payload_expected_doc=usr/share/doc/latticra/README.md' "$contract"
require_contains 'debian_payload_listing_required=1' "$contract"
require_contains 'debian_control_metadata_inspection_required=1' "$contract"
require_contains 'debian_maintainer_script_absence_required=1' "$contract"
require_contains 'debian_systemd_unit_absence_required=1' "$contract"
require_contains 'debian_init_script_absence_required=1' "$contract"
require_contains 'debian_privileged_helper_absence_required=1' "$contract"
require_contains 'debian_payload_unexpected_file_count=0' "$contract"
require_contains 'dpkg_deb_contents_inspection_run=0' "$contract"
require_contains 'dpkg_deb_metadata_inspection_run=0' "$contract"

require_contains 'freebsd_payload_expected_bin=bin/latticra' "$contract"
require_contains 'freebsd_payload_expected_doc=%%DOCSDIR%%/README.md' "$contract"
require_contains 'freebsd_payload_listing_required=1' "$contract"
require_contains 'freebsd_manifest_inspection_required=1' "$contract"
require_contains 'freebsd_rc_script_absence_required=1' "$contract"
require_contains 'freebsd_periodic_script_absence_required=1' "$contract"
require_contains 'freebsd_privileged_helper_absence_required=1' "$contract"
require_contains 'freebsd_payload_unexpected_file_count=0' "$contract"
require_contains 'freebsd_pkg_info_inspection_run=0' "$contract"
require_contains 'freebsd_pkg_manifest_inspection_run=0' "$contract"

require_contains 'openbsd_payload_expected_bin=bin/latticra' "$contract"
require_contains 'openbsd_payload_expected_doc=share/doc/latticra/README.md' "$contract"
require_contains 'openbsd_payload_listing_required=1' "$contract"
require_contains 'openbsd_pkg_info_inspection_required=1' "$contract"
require_contains 'openbsd_rc_script_absence_required=1' "$contract"
require_contains 'openbsd_privileged_helper_absence_required=1' "$contract"
require_contains 'openbsd_payload_unexpected_file_count=0' "$contract"
require_contains 'openbsd_pkg_info_list_run=0' "$contract"
require_contains 'openbsd_package_tar_listing_run=0' "$contract"

require_contains 'package_artifact_name' "$contract"
require_contains 'payload_listing_sha256' "$contract"
require_contains 'expected_payload_paths_present' "$contract"
require_contains 'unexpected_payload_paths_absent' "$contract"
require_contains 'service_files_absent' "$contract"
require_contains 'privileged_helpers_absent' "$contract"
require_contains 'host_mutation_hooks_absent' "$contract"
require_contains 'environment_identifier' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'install_remove_transcript_contract_present=1' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_validation_result_promoted=0' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package install/remove transcript contract' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package publication non-claim review contract' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package validation promotion blocker matrix' "$contract"
require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract: ok' "$contract"

require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' "$contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$contract"
require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$gate_contract"
require_contains "$contract" docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/debian/README.md
require_contains "$contract" packaging/freebsd/README.md
require_contains "$contract" packaging/openbsd/README.md
require_contains "$contract" README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'payload_inspection_contract_state=specified-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_payload_expected_bin=usr/bin/latticra' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_payload_expected_doc=usr/share/doc/latticra/README.md' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_payload_inspection_run=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'payload_inspection_contract_state=specified-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_payload_expected_bin=bin/latticra' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_payload_expected_doc=%%DOCSDIR%%/README.md' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_payload_inspection_run=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'payload_inspection_contract_state=specified-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_payload_expected_bin=bin/latticra' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_payload_expected_doc=share/doc/latticra/README.md' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_payload_inspection_run=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' packaging/debian/README.md
require_contains 'payload_inspection_contract_state=specified-no-effect' packaging/debian/README.md
require_contains 'debian_payload_expected_bin=usr/bin/latticra' packaging/debian/README.md
require_contains 'debian_payload_expected_doc=usr/share/doc/latticra/README.md' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' packaging/freebsd/README.md
require_contains 'payload_inspection_contract_state=specified-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_payload_expected_bin=bin/latticra' packaging/freebsd/README.md
require_contains 'freebsd_payload_expected_doc=%%DOCSDIR%%/README.md' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' packaging/openbsd/README.md
require_contains 'payload_inspection_contract_state=specified-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_payload_expected_bin=bin/latticra' packaging/openbsd/README.md
require_contains 'openbsd_payload_expected_doc=share/doc/latticra/README.md' packaging/openbsd/README.md

require_contains 'build/latticra usr/bin' packaging/debian/debian/install
require_contains 'README.md usr/share/doc/latticra' packaging/debian/debian/install
require_contains 'bin/latticra' packaging/freebsd/pkg-plist
require_contains '%%DOCSDIR%%/README.md' packaging/freebsd/pkg-plist
require_contains 'bin/latticra' packaging/openbsd/pkg/PLIST
require_contains 'share/doc/latticra/README.md' packaging/openbsd/pkg/PLIST

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo

require_contains 'Run Debian FreeBSD OpenBSD package payload inspection contract guard' .github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh' .github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml

printf 'debian_freebsd_openbsd_package_payload_inspection_contract: ok\n'
