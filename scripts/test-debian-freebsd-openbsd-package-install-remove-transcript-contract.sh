#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package install/remove transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package install/remove transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package install/remove transcript contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
require_file "$payload_contract"
require_file "$artifact_contract"
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
require_file .github/workflows/debian-freebsd-openbsd-package-install-remove-transcript-contract.yml

require_contains 'Status: active package install/remove transcript contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'install_remove_transcript_contract_present=1' "$contract"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'install_remove_disposable_environment_required=1' "$contract"
require_contains 'install_remove_transcript_present=0' "$contract"
require_contains 'install_on_host_run=0' "$contract"
require_contains 'remove_on_host_run=0' "$contract"
require_contains 'host_install_allowed=0' "$contract"
require_contains 'host_remove_allowed=0' "$contract"
require_contains 'host_mutation_allowed=0' "$contract"
require_contains 'service_state_change_allowed=0' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'package_payload_accepted=0' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'debian_install_remove_transcript_required=1' "$contract"
require_contains 'debian_install_remove_transcript_present=0' "$contract"
require_contains 'debian_package_install_run=0' "$contract"
require_contains 'debian_package_remove_run=0' "$contract"
require_contains 'debian_dpkg_install_run=0' "$contract"
require_contains 'debian_apt_install_run=0' "$contract"
require_contains 'debian_dpkg_remove_run=0' "$contract"
require_contains 'debian_apt_remove_run=0' "$contract"
require_contains 'debian_payload_post_install_check_required=1' "$contract"
require_contains 'debian_payload_post_remove_absence_check_required=1' "$contract"
require_contains 'debian_service_state_change_allowed=0' "$contract"
require_contains 'debian_systemd_unit_enable_allowed=0' "$contract"

require_contains 'freebsd_install_remove_transcript_required=1' "$contract"
require_contains 'freebsd_install_remove_transcript_present=0' "$contract"
require_contains 'freebsd_package_install_run=0' "$contract"
require_contains 'freebsd_package_remove_run=0' "$contract"
require_contains 'freebsd_pkg_add_run=0' "$contract"
require_contains 'freebsd_pkg_delete_run=0' "$contract"
require_contains 'freebsd_payload_post_install_check_required=1' "$contract"
require_contains 'freebsd_payload_post_remove_absence_check_required=1' "$contract"
require_contains 'freebsd_rc_service_enable_allowed=0' "$contract"

require_contains 'openbsd_install_remove_transcript_required=1' "$contract"
require_contains 'openbsd_install_remove_transcript_present=0' "$contract"
require_contains 'openbsd_package_install_run=0' "$contract"
require_contains 'openbsd_package_remove_run=0' "$contract"
require_contains 'openbsd_pkg_add_run=0' "$contract"
require_contains 'openbsd_pkg_delete_run=0' "$contract"
require_contains 'openbsd_payload_post_install_check_required=1' "$contract"
require_contains 'openbsd_payload_post_remove_absence_check_required=1' "$contract"
require_contains 'openbsd_rc_service_enable_allowed=0' "$contract"

require_contains 'pre_install_package_state' "$contract"
require_contains 'post_install_payload_listing' "$contract"
require_contains 'post_install_cli_no_effect_output' "$contract"
require_contains 'post_remove_absence_report' "$contract"
require_contains 'host_mutation_review' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_validation_result_promoted=0' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package publication non-claim review contract' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package validation promotion blocker matrix' "$contract"
require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract: ok' "$contract"

require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' "$contract"
require_contains "$contract" "$payload_contract"
require_contains "$contract" "$gate_contract"
require_contains "$contract" docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/debian/README.md
require_contains "$contract" packaging/freebsd/README.md
require_contains "$contract" packaging/openbsd/README.md
require_contains "$contract" README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_install_remove_transcript_required=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_install_remove_transcript_present=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_package_install_run=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_package_remove_run=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_install_remove_transcript_required=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_install_remove_transcript_present=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_install_run=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_remove_run=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_install_remove_transcript_required=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_install_remove_transcript_present=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_install_run=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_remove_run=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' packaging/debian/README.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' packaging/debian/README.md
require_contains 'debian_install_remove_transcript_required=1' packaging/debian/README.md
require_contains 'debian_package_install_run=0' packaging/debian/README.md
require_contains 'debian_package_remove_run=0' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' packaging/freebsd/README.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_install_remove_transcript_required=1' packaging/freebsd/README.md
require_contains 'freebsd_package_install_run=0' packaging/freebsd/README.md
require_contains 'freebsd_package_remove_run=0' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1' packaging/openbsd/README.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_install_remove_transcript_required=1' packaging/openbsd/README.md
require_contains 'openbsd_package_install_run=0' packaging/openbsd/README.md
require_contains 'openbsd_package_remove_run=0' packaging/openbsd/README.md

require_contains 'build/latticra usr/bin' packaging/debian/debian/install
require_contains 'bin/latticra' packaging/freebsd/pkg-plist
require_contains 'bin/latticra' packaging/openbsd/pkg/PLIST

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo
require_absent_file packaging/debian/debian/latticra.service
require_absent_file packaging/debian/debian/latticra.init
require_absent_file packaging/freebsd/files/latticra.in
require_absent_file packaging/openbsd/pkg/latticra.rc

require_contains 'Run Debian FreeBSD OpenBSD package install remove transcript contract guard' .github/workflows/debian-freebsd-openbsd-package-install-remove-transcript-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-install-remove-transcript-contract.sh' .github/workflows/debian-freebsd-openbsd-package-install-remove-transcript-contract.yml

printf 'debian_freebsd_openbsd_package_install_remove_transcript_contract: ok\n'
