#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package build-evidence intake denial contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package build-evidence intake denial contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package build-evidence intake denial contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
matrix_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
publication_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
install_remove_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$matrix_contract"
require_file "$publication_contract"
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
require_file .github/workflows/debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.yml

require_contains 'Status: active package build-evidence intake denial contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_review_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'package_build_evidence_intake_denial_contract_present=1' "$contract"
require_contains 'build_evidence_intake_denial_state=denied-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$contract"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'platform_build_evidence_intake_allowed=0' "$contract"
require_contains 'platform_build_evidence_intake_requested=0' "$contract"
require_contains 'platform_build_evidence_intake_denied=1' "$contract"
require_contains 'denial_review_present=1' "$contract"
require_contains 'denial_disposition_present=1' "$contract"
require_contains 'denial_closed=1' "$contract"
require_contains 'denial_re_request_allowed=0' "$contract"
require_contains 'platform_build_evidence_accepted=0' "$contract"
require_contains 'build_transcript_intake_accepted=0' "$contract"
require_contains 'package_build_lane_opened=0' "$contract"
require_contains 'single_platform_build_lane_opened=0' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'package_artifact_sha256_recorded=0' "$contract"
require_contains 'package_payload_accepted=0' "$contract"
require_contains 'install_remove_transcript_present=0' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'package_validation_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'build_evidence_denial_reason=validation-promotion-blocker-matrix-closed' "$contract"
require_contains 'denial_review_required_before_re_request=1' "$contract"
require_contains 'build_evidence_intake_request_identifier' "$contract"
require_contains 'requested_build_evidence_kind' "$contract"
require_contains 'requested_build_command' "$contract"
require_contains 'submitted_transcript_reference' "$contract"
require_contains 'denial_decision' "$contract"
require_contains 'denial_reason' "$contract"
require_contains 'denial_reviewer' "$contract"

require_contains 'debian_build_evidence_intake_allowed=0' "$contract"
require_contains 'debian_build_evidence_intake_requested=0' "$contract"
require_contains 'debian_build_evidence_intake_denied=1' "$contract"
require_contains 'debian_build_evidence_intake_denial_review_present=1' "$contract"
require_contains 'debian_build_evidence_intake_denial_disposition_present=1' "$contract"
require_contains 'debian_build_evidence_intake_denial_closed=1' "$contract"
require_contains 'debian_build_evidence_intake_denial_upheld=1' "$contract"
require_contains 'debian_denial_re_request_allowed=0' "$contract"
require_contains 'debian_platform_build_evidence_accepted=0' "$contract"
require_contains 'debian_build_transcript_intake_accepted=0' "$contract"
require_contains 'debian_dpkg_buildpackage_evidence_accepted=0' "$contract"
require_contains 'debian_debuild_evidence_accepted=0' "$contract"
require_contains 'debian_lintian_evidence_accepted=0' "$contract"
require_contains 'debian_source_package_evidence_accepted=0' "$contract"
require_contains 'debian_binary_package_evidence_accepted=0' "$contract"
require_contains 'dpkg_buildpackage_run=0' "$contract"
require_contains 'debuild_run=0' "$contract"
require_contains 'lintian_run=0' "$contract"
require_contains 'debian_validation_result_promoted=0' "$contract"

require_contains 'freebsd_build_evidence_intake_allowed=0' "$contract"
require_contains 'freebsd_build_evidence_intake_requested=0' "$contract"
require_contains 'freebsd_build_evidence_intake_denied=1' "$contract"
require_contains 'freebsd_build_evidence_intake_denial_review_present=1' "$contract"
require_contains 'freebsd_build_evidence_intake_denial_disposition_present=1' "$contract"
require_contains 'freebsd_build_evidence_intake_denial_closed=1' "$contract"
require_contains 'freebsd_build_evidence_intake_denial_upheld=1' "$contract"
require_contains 'freebsd_denial_re_request_allowed=0' "$contract"
require_contains 'freebsd_platform_build_evidence_accepted=0' "$contract"
require_contains 'freebsd_stage_evidence_accepted=0' "$contract"
require_contains 'freebsd_package_evidence_accepted=0' "$contract"
require_contains 'freebsd_make_stage_evidence_accepted=0' "$contract"
require_contains 'freebsd_make_package_evidence_accepted=0' "$contract"
require_contains 'freebsd_portlint_evidence_accepted=0' "$contract"
require_contains 'freebsd_poudriere_evidence_accepted=0' "$contract"
require_contains 'freebsd_make_makesum_evidence_accepted=0' "$contract"
require_contains 'freebsd_make_makesum_run=0' "$contract"
require_contains 'freebsd_make_stage_run=0' "$contract"
require_contains 'freebsd_make_package_run=0' "$contract"
require_contains 'portlint_run=0' "$contract"
require_contains 'poudriere_run=0' "$contract"
require_contains 'freebsd_validation_result_promoted=0' "$contract"

require_contains 'openbsd_build_evidence_intake_allowed=0' "$contract"
require_contains 'openbsd_build_evidence_intake_requested=0' "$contract"
require_contains 'openbsd_build_evidence_intake_denied=1' "$contract"
require_contains 'openbsd_build_evidence_intake_denial_review_present=1' "$contract"
require_contains 'openbsd_build_evidence_intake_denial_disposition_present=1' "$contract"
require_contains 'openbsd_build_evidence_intake_denial_closed=1' "$contract"
require_contains 'openbsd_build_evidence_intake_denial_upheld=1' "$contract"
require_contains 'openbsd_denial_re_request_allowed=0' "$contract"
require_contains 'openbsd_platform_build_evidence_accepted=0' "$contract"
require_contains 'openbsd_makesum_evidence_accepted=0' "$contract"
require_contains 'openbsd_plist_evidence_accepted=0' "$contract"
require_contains 'openbsd_package_evidence_accepted=0' "$contract"
require_contains 'openbsd_make_makesum_evidence_accepted=0' "$contract"
require_contains 'openbsd_make_plist_evidence_accepted=0' "$contract"
require_contains 'openbsd_make_package_evidence_accepted=0' "$contract"
require_contains 'openbsd_portcheck_evidence_accepted=0' "$contract"
require_contains 'openbsd_bulk_build_evidence_accepted=0' "$contract"
require_contains 'openbsd_make_makesum_run=0' "$contract"
require_contains 'openbsd_make_plist_run=0' "$contract"
require_contains 'openbsd_make_package_run=0' "$contract"
require_contains 'portcheck_run=0' "$contract"
require_contains 'openbsd_bulk_build_run=0' "$contract"
require_contains 'permit_package_enabled=0' "$contract"
require_contains 'openbsd_validation_result_promoted=0' "$contract"

require_contains 'request build evidence' "$contract"
require_contains 'accept build evidence' "$contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial review contract' "$contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition contract' "$contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract: ok' "$contract"

require_contains "$contract" "$matrix_contract"
require_contains "$contract" "$publication_contract"
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
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_build_evidence_intake_denied=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_build_transcript_intake_accepted=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_build_evidence_intake_denied=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_evidence_accepted=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_build_evidence_intake_denied=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_evidence_accepted=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' packaging/debian/README.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' packaging/debian/README.md
require_contains 'debian_build_evidence_intake_denied=1' packaging/debian/README.md
require_contains 'debian_build_transcript_intake_accepted=0' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' packaging/freebsd/README.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_build_evidence_intake_denied=1' packaging/freebsd/README.md
require_contains 'freebsd_package_evidence_accepted=0' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1' packaging/openbsd/README.md
require_contains 'build_evidence_intake_denial_state=denied-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_build_evidence_intake_denied=1' packaging/openbsd/README.md
require_contains 'openbsd_package_evidence_accepted=0' packaging/openbsd/README.md
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo
require_absent_file packaging/debian/debian/latticra.service
require_absent_file packaging/debian/debian/latticra.init
require_absent_file packaging/freebsd/files/latticra.in
require_absent_file packaging/openbsd/pkg/latticra.rc

require_contains 'Run Debian FreeBSD OpenBSD package build evidence intake denial contract guard' .github/workflows/debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.sh' .github/workflows/debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.yml

printf 'debian_freebsd_openbsd_package_build_evidence_intake_denial_contract: ok\n'
