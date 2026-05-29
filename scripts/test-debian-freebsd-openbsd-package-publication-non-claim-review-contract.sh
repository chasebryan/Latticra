#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package publication non-claim review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package publication non-claim review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package publication non-claim review contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
install_remove_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$install_remove_contract"
require_file "$payload_contract"
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
require_file packaging/freebsd/Makefile
require_file packaging/freebsd/pkg-plist
require_file packaging/openbsd/README.md
require_file packaging/openbsd/Makefile
require_file packaging/openbsd/pkg/PLIST
require_file README.md
require_file .github/workflows/debian-freebsd-openbsd-package-publication-non-claim-review-contract.yml

require_contains 'Status: active package publication non-claim review contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'publication_non_claim_review_contract_present=1' "$contract"
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'package_validation_result_promoted=0' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'package_artifact_published=0' "$contract"
require_contains 'package_repository_created=0' "$contract"
require_contains 'package_repository_upload_run=0' "$contract"
require_contains 'upstream_submission_run=0' "$contract"
require_contains 'official_package_or_port_claimed=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'debian_publication_non_claim_review_required=1' "$contract"
require_contains 'debian_publication_non_claim_review_present=1' "$contract"
require_contains 'debian_package_publication_claimed=0' "$contract"
require_contains 'debian_archive_ready=0' "$contract"
require_contains 'debian_mentors_upload_claimed=0' "$contract"
require_contains 'debian_sponsorship_claimed=0' "$contract"
require_contains 'debian_ftp_master_acceptance_claimed=0' "$contract"
require_contains 'debian_source_upload_run=0' "$contract"
require_contains 'debian_mentors_upload_run=0' "$contract"
require_contains 'debian_archive_upload_run=0' "$contract"
require_contains 'debian_debsign_run=0' "$contract"
require_contains 'debian_dput_run=0' "$contract"

require_contains 'freebsd_publication_non_claim_review_required=1' "$contract"
require_contains 'freebsd_publication_non_claim_review_present=1' "$contract"
require_contains 'freebsd_package_publication_claimed=0' "$contract"
require_contains 'freebsd_ports_tree_submission_claimed=0' "$contract"
require_contains 'freebsd_bugzilla_pr_claimed=0' "$contract"
require_contains 'freebsd_committer_review_claimed=0' "$contract"
require_contains 'freebsd_official_port_claimed=0' "$contract"
require_contains 'freebsd_pkg_repo_created=0' "$contract"
require_contains 'freebsd_pkg_repo_publish_run=0' "$contract"
require_contains 'freebsd_pkg_repo_sign_run=0' "$contract"

require_contains 'openbsd_publication_non_claim_review_required=1' "$contract"
require_contains 'openbsd_publication_non_claim_review_present=1' "$contract"
require_contains 'openbsd_package_publication_claimed=0' "$contract"
require_contains 'openbsd_ports_tree_submission_claimed=0' "$contract"
require_contains 'openbsd_ports_review_thread_claimed=0' "$contract"
require_contains 'openbsd_maintainer_acceptance_claimed=0' "$contract"
require_contains 'openbsd_official_port_claimed=0' "$contract"
require_contains 'openbsd_pkg_repo_created=0' "$contract"
require_contains 'openbsd_pkg_repo_publish_run=0' "$contract"
require_contains 'permit_package_enabled=0' "$contract"

require_contains 'package_validation_result_identifier' "$contract"
require_contains 'platform_under_review' "$contract"
require_contains 'source_archive_sha256' "$contract"
require_contains 'payload_inspection_transcript_sha256' "$contract"
require_contains 'install_remove_transcript_sha256' "$contract"
require_contains 'publication_non_claim_reviewer' "$contract"
require_contains 'non_claimed_publication_targets' "$contract"
require_contains 'status_page_update_reference' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'package_payload_accepted=0' "$contract"
require_contains 'install_remove_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package validation promotion blocker matrix' "$contract"
require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract: ok' "$contract"

require_contains "$contract" "$install_remove_contract"
require_contains "$contract" "$payload_contract"
require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$environment_contract"
require_contains "$contract" "$gate_contract"
require_contains "$contract" docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/debian/README.md
require_contains "$contract" packaging/freebsd/README.md
require_contains "$contract" packaging/openbsd/README.md
require_contains "$contract" README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_publication_non_claim_review_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_package_publication_claimed=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_mentors_upload_run=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_dput_run=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_publication_non_claim_review_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_publication_claimed=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_pkg_repo_publish_run=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_official_port_claimed=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_publication_non_claim_review_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_publication_claimed=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_pkg_repo_publish_run=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_official_port_claimed=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' packaging/debian/README.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' packaging/debian/README.md
require_contains 'debian_publication_non_claim_review_present=1' packaging/debian/README.md
require_contains 'debian_package_publication_claimed=0' packaging/debian/README.md
require_contains 'debian_dput_run=0' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' packaging/freebsd/README.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_publication_non_claim_review_present=1' packaging/freebsd/README.md
require_contains 'freebsd_package_publication_claimed=0' packaging/freebsd/README.md
require_contains 'freebsd_pkg_repo_publish_run=0' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1' packaging/openbsd/README.md
require_contains 'publication_non_claim_review_contract_state=specified-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_publication_non_claim_review_present=1' packaging/openbsd/README.md
require_contains 'openbsd_package_publication_claimed=0' packaging/openbsd/README.md
require_contains 'openbsd_pkg_repo_publish_run=0' packaging/openbsd/README.md
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo
require_absent_file packaging/debian/debian/latticra.service
require_absent_file packaging/debian/debian/latticra.init
require_absent_file packaging/freebsd/files/latticra.in
require_absent_file packaging/openbsd/pkg/latticra.rc

require_contains 'Run Debian FreeBSD OpenBSD package publication non claim review contract guard' .github/workflows/debian-freebsd-openbsd-package-publication-non-claim-review-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-publication-non-claim-review-contract.sh' .github/workflows/debian-freebsd-openbsd-package-publication-non-claim-review-contract.yml

printf 'debian_freebsd_openbsd_package_publication_non_claim_review_contract: ok\n'
