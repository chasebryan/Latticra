# Debian, FreeBSD, and OpenBSD Package Build-Evidence Intake Denial Contract

Status: active package build-evidence intake denial contract
Scope: define denial of Debian, FreeBSD, and OpenBSD package build-evidence intake while the validation promotion blocker matrix is closed.

## Purpose

This contract records how Debian, FreeBSD, and OpenBSD package build evidence must be refused until the shared validation promotion blocker matrix opens.

The goal is narrow: no `dpkg-buildpackage`, `debuild`, `lintian`, FreeBSD ports, portlint, poudriere, OpenBSD ports, portcheck, bulk-build, artifact, install/remove, or publication evidence may be accepted while the matrix remains blocked.

This contract is documentation-only and static. It does not run package build tools, request build evidence, accept build evidence, create package artifacts, inspect package artifacts, install packages, remove packages, publish packages, submit ports, enable OpenBSD package redistribution, promote validation results, or claim package readiness.

## Current Intake Denial State

```text
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_review_contract_present=1
package_build_evidence_intake_denial_contract_present=1
build_evidence_intake_denial_state=denied-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
package_build_gate_state=closed-no-effect
platform_build_evidence_intake_allowed=0
platform_build_evidence_intake_requested=0
platform_build_evidence_intake_denied=1
denial_review_present=1
denial_re_request_allowed=0
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

## Denial Reason Matrix

Current build-evidence intake denial is required because:

```text
build_evidence_denial_reason=validation-promotion-blocker-matrix-closed
source_archive_column_state=blocked
environment_column_state=blocked
artifact_column_state=blocked
payload_column_state=blocked
install_remove_column_state=blocked
promotion_column_state=blocked
publication_non_claim_column_state=specified
denial_review_required_before_re_request=1
```

A future build-evidence intake request must record:

```text
build_evidence_intake_request_identifier
platform_under_review
requested_build_evidence_kind
requested_build_command
submitted_transcript_reference
source_archive_sha256
environment_identifier
operator_authorization_reference
validation_promotion_blocker_matrix_reference
denial_decision
denial_reason
denial_reviewer
status_page_update_reference
```

The only current decision allowed by this contract is denial.

## Debian Intake Denial

Current Debian build-evidence intake remains denied:

```text
debian_build_evidence_intake_allowed=0
debian_build_evidence_intake_requested=0
debian_build_evidence_intake_denied=1
debian_build_evidence_intake_denial_review_present=1
debian_build_evidence_intake_denial_upheld=1
debian_denial_re_request_allowed=0
debian_platform_build_evidence_accepted=0
debian_build_transcript_intake_accepted=0
debian_dpkg_buildpackage_evidence_accepted=0
debian_debuild_evidence_accepted=0
debian_lintian_evidence_accepted=0
debian_source_package_evidence_accepted=0
debian_binary_package_evidence_accepted=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
debian_validation_result_promoted=0
debian_archive_ready=0
```

Debian build evidence may not be requested, received, accepted, summarized as successful, or used to open a Debian build lane while the blocker matrix is closed.

## FreeBSD Intake Denial

Current FreeBSD build-evidence intake remains denied:

```text
freebsd_build_evidence_intake_allowed=0
freebsd_build_evidence_intake_requested=0
freebsd_build_evidence_intake_denied=1
freebsd_build_evidence_intake_denial_review_present=1
freebsd_build_evidence_intake_denial_upheld=1
freebsd_denial_re_request_allowed=0
freebsd_platform_build_evidence_accepted=0
freebsd_stage_evidence_accepted=0
freebsd_package_evidence_accepted=0
freebsd_make_stage_evidence_accepted=0
freebsd_make_package_evidence_accepted=0
freebsd_portlint_evidence_accepted=0
freebsd_poudriere_evidence_accepted=0
freebsd_make_makesum_evidence_accepted=0
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_run=0
freebsd_validation_result_promoted=0
freebsd_official_port_claimed=0
```

FreeBSD ports evidence may not be requested, received, accepted, summarized as successful, or used to open a FreeBSD build lane while the blocker matrix is closed.

## OpenBSD Intake Denial

Current OpenBSD build-evidence intake remains denied:

```text
openbsd_build_evidence_intake_allowed=0
openbsd_build_evidence_intake_requested=0
openbsd_build_evidence_intake_denied=1
openbsd_build_evidence_intake_denial_review_present=1
openbsd_build_evidence_intake_denial_upheld=1
openbsd_denial_re_request_allowed=0
openbsd_platform_build_evidence_accepted=0
openbsd_makesum_evidence_accepted=0
openbsd_plist_evidence_accepted=0
openbsd_package_evidence_accepted=0
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

OpenBSD ports evidence may not be requested, received, accepted, summarized as successful, used to enable `PERMIT_PACKAGE`, or used to open an OpenBSD build lane while the blocker matrix is closed.

## Current Blockers

Build-evidence intake remains denied under this blocker state:

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
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
```

The package-build gate remains closed. This intake denial contract only records that build evidence cannot be requested or accepted until the validation promotion blocker matrix opens in a future lane.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial review contract before any denial can be re-requested.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-review-contract.sh
```

That lane reviews and upholds denied build-evidence intake while keeping package builds and readiness blocked.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition contract before any reviewed denial can be closed or re-requested.
```

That future lane should record the reviewed denial disposition while keeping package builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract: ok
```
