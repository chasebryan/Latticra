# Debian, FreeBSD, and OpenBSD Package Build-Evidence Intake Denial Disposition Closeout Contract

Status: active package build-evidence intake denial disposition closeout contract
Scope: close out the disposed Debian, FreeBSD, and OpenBSD package build-evidence intake denial while archive, re-request, validation promotion, and package readiness remain blocked.

## Purpose

This contract records the no-effect closeout of the Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition.

The goal is narrow: after denial review upholds the denial and disposition closes the reviewed denial, this closeout records that the disposed denial is closed out without making it archivable, re-requestable, promotable, or usable as package validation evidence.

This contract is documentation-only and static. It does not run package build tools, request build evidence, re-request denied evidence, archive denied evidence, accept build evidence, create package artifacts, inspect package artifacts, install packages, remove packages, publish packages, submit ports, enable OpenBSD package redistribution, promote validation results, or claim package readiness.

## Current Denial Disposition Closeout State

```text
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1
package_build_evidence_intake_denial_disposition_closeout_contract_present=1
build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect
build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect
build_evidence_intake_denial_disposition_state=closed-upheld-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
build_evidence_intake_denial_state=denied-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
package_build_gate_state=closed-no-effect
denial_disposition_closeout_present=1
denial_disposition_closeout_decision=closeout-upheld-denial
denial_archive_gate_present=1
denial_archive_gate_state=closed-no-effect
denial_disposition_present=1
denial_disposition_decision=close-upheld-denial
denial_review_present=1
denial_review_decision=uphold-denial
denial_closed=1
denial_archived=0
denial_archive_allowed=0
denial_archive_record_write_allowed=0
denial_archive_record_written=0
denial_re_request_allowed=0
platform_build_evidence_intake_allowed=0
platform_build_evidence_intake_denied=1
platform_build_evidence_accepted=0
build_transcript_intake_accepted=0
package_build_lane_opened=0
single_platform_build_lane_opened=0
source_archive_accepted_for_build=0
environment_transcript_present=0
explicit_operator_build_authorization=0
package_artifact_created=0
package_artifact_sha256_recorded=0
package_payload_accepted=0
install_remove_transcript_present=0
publication_non_claim_review_present=1
package_validation_result_promoted=0
package_readiness_claimed=0
```

## Closeout Record Requirements

A future denial disposition closeout record must bind the closeout to the disposed denial:

```text
denial_disposition_closeout_identifier
denial_disposition_reference
denial_review_reference
build_evidence_denial_reference
build_evidence_intake_request_identifier
platform_under_review
requested_build_evidence_kind
requested_build_command
submitted_transcript_reference
validation_promotion_blocker_matrix_reference
denial_disposition_closeout_decision
denial_disposition_closeout_reason
denial_disposition_closeout_reviewer
status_page_update_reference
archive_gate_reference
operator_authorization_reference
```

The only current closeout decision allowed by this contract is `closeout-upheld-denial`.

## Debian Denial Disposition Closeout

Current Debian build-evidence intake denial disposition closeout preserves the closed upheld denial:

```text
debian_build_evidence_intake_denial_disposition_closeout_present=1
debian_build_evidence_intake_denial_archive_gate_present=1
debian_build_evidence_intake_denial_archive_gate_closed=1
debian_build_evidence_intake_denial_closed_out=1
debian_build_evidence_intake_denial_disposition_present=1
debian_build_evidence_intake_denial_closed=1
debian_build_evidence_intake_denial_upheld=1
debian_build_evidence_intake_denial_archived=0
debian_denial_archive_allowed=0
debian_denial_archive_record_write_allowed=0
debian_denial_archive_record_written=0
debian_denial_re_request_allowed=0
debian_build_evidence_intake_allowed=0
debian_build_evidence_intake_denied=1
debian_build_transcript_intake_accepted=0
debian_platform_build_evidence_accepted=0
debian_dpkg_buildpackage_evidence_accepted=0
debian_debuild_evidence_accepted=0
debian_lintian_evidence_accepted=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
debian_validation_result_promoted=0
debian_archive_ready=0
```

Debian build evidence remains denied, closed, closed out, unarchived, unaccepted, and unusable as build-lane opening evidence.

## FreeBSD Denial Disposition Closeout

Current FreeBSD build-evidence intake denial disposition closeout preserves the closed upheld denial:

```text
freebsd_build_evidence_intake_denial_disposition_closeout_present=1
freebsd_build_evidence_intake_denial_archive_gate_present=1
freebsd_build_evidence_intake_denial_archive_gate_closed=1
freebsd_build_evidence_intake_denial_closed_out=1
freebsd_build_evidence_intake_denial_disposition_present=1
freebsd_build_evidence_intake_denial_closed=1
freebsd_build_evidence_intake_denial_upheld=1
freebsd_build_evidence_intake_denial_archived=0
freebsd_denial_archive_allowed=0
freebsd_denial_archive_record_write_allowed=0
freebsd_denial_archive_record_written=0
freebsd_denial_re_request_allowed=0
freebsd_build_evidence_intake_allowed=0
freebsd_build_evidence_intake_denied=1
freebsd_platform_build_evidence_accepted=0
freebsd_make_makesum_evidence_accepted=0
freebsd_make_stage_evidence_accepted=0
freebsd_make_package_evidence_accepted=0
freebsd_portlint_evidence_accepted=0
freebsd_poudriere_evidence_accepted=0
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_run=0
freebsd_validation_result_promoted=0
freebsd_official_port_claimed=0
```

FreeBSD ports evidence remains denied, closed, closed out, unarchived, unaccepted, and unusable as build-lane opening evidence.

## OpenBSD Denial Disposition Closeout

Current OpenBSD build-evidence intake denial disposition closeout preserves the closed upheld denial:

```text
openbsd_build_evidence_intake_denial_disposition_closeout_present=1
openbsd_build_evidence_intake_denial_archive_gate_present=1
openbsd_build_evidence_intake_denial_archive_gate_closed=1
openbsd_build_evidence_intake_denial_closed_out=1
openbsd_build_evidence_intake_denial_disposition_present=1
openbsd_build_evidence_intake_denial_closed=1
openbsd_build_evidence_intake_denial_upheld=1
openbsd_build_evidence_intake_denial_archived=0
openbsd_denial_archive_allowed=0
openbsd_denial_archive_record_write_allowed=0
openbsd_denial_archive_record_written=0
openbsd_denial_re_request_allowed=0
openbsd_build_evidence_intake_allowed=0
openbsd_build_evidence_intake_denied=1
openbsd_platform_build_evidence_accepted=0
openbsd_make_makesum_evidence_accepted=0
openbsd_make_plist_evidence_accepted=0
openbsd_make_package_evidence_accepted=0
openbsd_portcheck_evidence_accepted=0
openbsd_bulk_build_evidence_accepted=0
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
openbsd_bulk_build_run=0
permit_package_enabled=0
openbsd_validation_result_promoted=0
openbsd_official_port_claimed=0
```

OpenBSD ports evidence remains denied, closed, closed out, unarchived, unaccepted, unusable as build-lane opening evidence, and unable to enable `PERMIT_PACKAGE`.

## Current Blockers

Denial disposition closeout remains no-effect under this blocker state:

```text
validation_promotion_blocker_matrix_state=blocked-no-effect
source_archive_accepted_for_build=0
environment_transcript_present=0
explicit_operator_build_authorization=0
package_artifact_created=0
package_artifact_sha256_recorded=0
package_payload_accepted=0
install_remove_transcript_present=0
platform_build_evidence_accepted=0
package_validation_result_promoted=0
denial_re_request_allowed=0
denial_closed=1
denial_archived=0
denial_archive_allowed=0
denial_archive_record_write_allowed=0
denial_archive_record_written=0
```

## Command Boundary

This contract does not:

```text
run dpkg-buildpackage
run debuild
run lintian
run FreeBSD make makesum
run FreeBSD make stage
run FreeBSD make package
run portlint
run poudriere
run OpenBSD make makesum
run OpenBSD make plist
run OpenBSD make package
run portcheck
run an OpenBSD bulk build
request build evidence
re-request build evidence
archive denied build evidence
accept build evidence
create package artifacts
inspect package artifacts
install packages
remove packages
publish package artifacts
submit package or port upstream
enable OpenBSD PERMIT_PACKAGE
promote package validation results
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
```

The package-build gate remains closed. This denial disposition closeout contract only records that the no-effect disposition was closed out while the blocker matrix remains closed.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition closeout archive gate contract before any closed-out denial can be archived or re-requested.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh
```

That lane closes the archive and re-request gate while preserving package build and readiness blockers.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition closeout archive gate review contract before any archive gate can be relaxed or re-requested.
```

That future lane should review the closed archive gate while preserving package build and readiness blockers.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-disposition-closeout-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_contract: ok
```
