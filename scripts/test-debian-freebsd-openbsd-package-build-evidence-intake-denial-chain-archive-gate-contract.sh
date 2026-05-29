#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

label='debian/freebsd/openbsd package build-evidence intake denial chain archive gate contract'

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf '%s: missing file: %s\n' "$label" "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf '%s: missing required pattern in %s: %s\n' "$label" "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf '%s: unexpected file exists: %s\n' "$label" "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_ARCHIVE_GATE_CONTRACT.md'
predecessor_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_DISPOSITION_CLOSEOUT_CONTRACT.md'
workflow='.github/workflows/debian-freebsd-openbsd-package-build-evidence-intake-denial-chain-archive-gate-contract.yml'

for file in \
  "$contract" \
  "$predecessor_contract" \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md \
  docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md \
  docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md \
  docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md \
  docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/README.md \
  docs/status/README.md \
  packaging/debian/README.md \
  packaging/debian/debian/control \
  packaging/debian/debian/install \
  packaging/freebsd/README.md \
  packaging/freebsd/Makefile \
  packaging/freebsd/pkg-plist \
  packaging/openbsd/README.md \
  packaging/openbsd/Makefile \
  packaging/openbsd/pkg/PLIST \
  README.md \
  "$workflow"
do
  require_file "$file"
done

require_contains 'Status: active package build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'does not run package build tools' "$contract"
require_contains 'shortened continuation filename `DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_ARCHIVE_GATE_CONTRACT.md`' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_decision=deny-archive-and-re-request' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect' "$contract"
require_contains 'denial_archived=0' "$contract"
require_contains 'denial_archive_allowed=0' "$contract"
require_contains 'denial_archive_record_write_allowed=0' "$contract"
require_contains 'denial_archive_record_written=0' "$contract"
require_contains 'denial_re_request_allowed=0' "$contract"
require_contains 'platform_build_evidence_accepted=0' "$contract"
require_contains 'package_validation_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_identifier' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_decision' "$contract"
require_contains 'archive_record_write_authorization_reference' "$contract"
require_contains 'deny-archive-and-re-request' "$contract"

for platform in debian freebsd openbsd
do
  require_contains "${platform}_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1" "$contract"
  require_contains "${platform}_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1" "$contract"
  require_contains "${platform}_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_present=1" "$contract"
  require_contains "${platform}_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closed_out=1" "$contract"
  require_contains "${platform}_denial_archive_allowed=0" "$contract"
  require_contains "${platform}_denial_archive_record_write_allowed=0" "$contract"
  require_contains "${platform}_denial_archive_record_written=0" "$contract"
  require_contains "${platform}_denial_re_request_allowed=0" "$contract"
  require_contains "${platform}_platform_build_evidence_accepted=0" "$contract"
  require_contains "${platform}_validation_result_promoted=0" "$contract"
done

require_contains 'dpkg_buildpackage_run=0' "$contract"
require_contains 'debuild_run=0' "$contract"
require_contains 'lintian_run=0' "$contract"
require_contains 'debian_archive_ready=0' "$contract"
require_contains 'freebsd_make_makesum_run=0' "$contract"
require_contains 'freebsd_make_stage_run=0' "$contract"
require_contains 'freebsd_make_package_run=0' "$contract"
require_contains 'portlint_run=0' "$contract"
require_contains 'poudriere_run=0' "$contract"
require_contains 'freebsd_official_port_claimed=0' "$contract"
require_contains 'openbsd_make_makesum_run=0' "$contract"
require_contains 'openbsd_make_plist_run=0' "$contract"
require_contains 'openbsd_make_package_run=0' "$contract"
require_contains 'portcheck_run=0' "$contract"
require_contains 'openbsd_bulk_build_run=0' "$contract"
require_contains 'permit_package_enabled=0' "$contract"
require_contains 'openbsd_official_port_claimed=0' "$contract"

require_contains 'run dpkg-buildpackage' "$contract"
require_contains 'run FreeBSD make package' "$contract"
require_contains 'run OpenBSD make package' "$contract"
require_contains 'request build evidence' "$contract"
require_contains 're-request build evidence' "$contract"
require_contains 'archive denied build evidence' "$contract"
require_contains 'write archive records' "$contract"
require_contains 'accept build evidence' "$contract"
require_contains 'submit package or port upstream' "$contract"
require_contains 'enable OpenBSD PERMIT_PACKAGE' "$contract"
require_contains 'claim package readiness' "$contract"

require_contains "$predecessor_contract" "$contract"
require_contains "$contract" "$predecessor_contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial chain archive gate review contract before any closed reviewed archive gate disposition closeout archive gate can be reviewed, archived, or re-requested.' "$contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_ARCHIVE_GATE_REVIEW_CONTRACT.md' "$contract"
require_contains 'scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-chain-archive-gate-review-contract.sh' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract: ok' "$contract"

for file in \
  docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md \
  packaging/debian/README.md \
  packaging/freebsd/README.md \
  packaging/openbsd/README.md \
  README.md
do
  require_contains "$contract" "$file"
  require_contains 'debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$file"
  require_contains 'package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$file"
  require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$file"
  require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' "$file"
  require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$file"
  require_contains 'denial_archive_allowed=0' "$file"
  require_contains 'denial_archive_record_write_allowed=0' "$file"
  require_contains 'denial_re_request_allowed=0' "$file"
  require_contains 'platform_build_evidence_accepted=0' "$file"
  require_contains 'package_validation_result_promoted=0' "$file"
done

require_contains 'debian_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_ARCHIVE_GATE_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CHAIN_ARCHIVE_GATE_CONTRACT.md' docs/status/README.md
require_contains 'Run Debian FreeBSD OpenBSD package build evidence intake denial chain archive gate contract guard' "$workflow"
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-chain-archive-gate-contract.sh' "$workflow"

require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile
require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo
require_absent_file packaging/debian/debian/latticra.service
require_absent_file packaging/debian/debian/latticra.init
require_absent_file packaging/freebsd/files/latticra.in
require_absent_file packaging/openbsd/pkg/latticra.rc

sh -n "$0"

printf 'debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract: ok\n'
