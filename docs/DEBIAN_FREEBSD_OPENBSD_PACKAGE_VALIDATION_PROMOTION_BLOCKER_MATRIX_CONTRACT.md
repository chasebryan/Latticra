# Debian, FreeBSD, and OpenBSD Package Validation Promotion Blocker Matrix Contract

Status: active package validation promotion blocker matrix contract
Scope: define the blocker matrix for promoting Debian, FreeBSD, and OpenBSD package validation evidence without accepting build evidence.

## Purpose

This contract records the current blocker matrix that prevents any Debian, FreeBSD, or OpenBSD package validation result from being promoted.

The goal is narrow: tie the source archive, disposable environment, artifact naming, payload inspection, install/remove transcript, and publication non-claim records into one promotion matrix before any platform-specific build evidence can be accepted.

This contract is documentation-only and static. It does not run package build tools, create package artifacts, inspect package artifacts, install packages, remove packages, publish packages, submit ports, enable OpenBSD package redistribution, promote validation results, or claim package readiness.

## Current Matrix State

```text
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1
package_validation_promotion_blocker_matrix_contract_present=1
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
package_build_gate_state=closed-no-effect
publication_non_claim_review_contract_state=specified-no-effect
source_archive_accepted_for_build=0
environment_transcript_present=0
explicit_operator_build_authorization=0
package_artifact_created=0
package_artifact_sha256_recorded=0
package_payload_accepted=0
install_remove_transcript_present=0
publication_non_claim_review_present=1
platform_build_evidence_intake_allowed=0
platform_build_evidence_intake_denied=1
build_transcript_intake_accepted=0
single_platform_build_lane_opened=0
platform_build_evidence_accepted=0
package_validation_result_promoted=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Shared Promotion Blocker Matrix

Current promotion state by evidence column:

```text
source_archive_column_state=blocked
environment_column_state=blocked
artifact_column_state=blocked
payload_column_state=blocked
install_remove_column_state=blocked
publication_non_claim_column_state=specified
promotion_column_state=blocked
```

A future local validation promotion may not accept any platform-specific build evidence unless all required columns are reviewed together:

```text
source_archive_accepted_for_build=1
archive_sha256_bound_to_build=1
environment_transcript_present=1
explicit_operator_build_authorization=1
package_artifact_created=1
package_artifact_sha256_recorded=1
package_payload_accepted=1
install_remove_transcript_present=1
publication_non_claim_review_present=1
platform_publication_claimed=0
package_validation_result_promoted=1
```

Those values are future prerequisites, not current claims. The current matrix remains blocked.

## Debian Promotion Row

Current Debian validation promotion remains blocked:

```text
debian_validation_promotion_blocked=1
debian_build_evidence_intake_allowed=0
debian_build_evidence_intake_denied=1
debian_build_transcript_intake_accepted=0
debian_platform_build_evidence_accepted=0
debian_source_archive_accepted_for_build=0
debian_build_environment_provisioned=0
debian_package_artifact_created=0
debian_payload_inspection_run=0
debian_install_remove_transcript_present=0
debian_publication_non_claim_review_present=1
debian_package_publication_claimed=0
debian_validation_result_promoted=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
debian_archive_ready=0
```

Debian build, lintian, payload, install/remove, and publication evidence must remain local-only and unpromoted until the shared matrix opens in a future lane.

## FreeBSD Promotion Row

Current FreeBSD validation promotion remains blocked:

```text
freebsd_validation_promotion_blocked=1
freebsd_build_evidence_intake_allowed=0
freebsd_build_evidence_intake_denied=1
freebsd_package_evidence_accepted=0
freebsd_platform_build_evidence_accepted=0
freebsd_source_archive_accepted_for_build=0
freebsd_build_environment_provisioned=0
freebsd_package_artifact_created=0
freebsd_payload_inspection_run=0
freebsd_install_remove_transcript_present=0
freebsd_publication_non_claim_review_present=1
freebsd_package_publication_claimed=0
freebsd_validation_result_promoted=0
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_run=0
freebsd_official_port_claimed=0
```

FreeBSD ports, portlint, poudriere, package, install/remove, and publication evidence must remain local-only and unpromoted until the shared matrix opens in a future lane.

## OpenBSD Promotion Row

Current OpenBSD validation promotion remains blocked:

```text
openbsd_validation_promotion_blocked=1
openbsd_build_evidence_intake_allowed=0
openbsd_build_evidence_intake_denied=1
openbsd_package_evidence_accepted=0
openbsd_platform_build_evidence_accepted=0
openbsd_source_archive_accepted_for_build=0
openbsd_build_environment_provisioned=0
openbsd_package_artifact_created=0
openbsd_payload_inspection_run=0
openbsd_install_remove_transcript_present=0
openbsd_publication_non_claim_review_present=1
openbsd_package_publication_claimed=0
openbsd_validation_result_promoted=0
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
openbsd_bulk_build_run=0
permit_package_enabled=0
openbsd_official_port_claimed=0
```

OpenBSD ports, plist, package, portcheck, bulk build, install/remove, `PERMIT_PACKAGE`, and publication evidence must remain local-only and unpromoted until the shared matrix opens in a future lane.

## Acceptance Boundary

A future promotion record must bind every accepted platform result to:

```text
platform_under_review
source_archive_contract_reference
source_archive_sha256
environment_transcript_sha256
package_artifact_name
package_artifact_sha256
payload_inspection_transcript_sha256
install_remove_transcript_sha256
publication_non_claim_review_reference
promotion_reviewer
promotion_decision
promotion_scope
status_page_update_reference
operator_authorization_reference
```

The only permitted future promotion scope from this matrix is local package validation evidence. This matrix cannot promote Debian archive readiness, FreeBSD official port status, OpenBSD official port status, package repository publication, production installer readiness, or root installer readiness.

## Current Blockers

Package validation promotion remains blocked under this matrix:

```text
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
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
```

The package-build gate remains closed. This blocker matrix only records the promotion columns and current blocking values for future Debian, FreeBSD, and OpenBSD local validation evidence.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial contract before any single-platform build lane can open.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-contract.sh
```

That lane defines how build evidence intake is refused until the blocker matrix opens, while keeping package builds and readiness blocked.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial review contract before any denial can be re-requested.
```

That future lane should review denied intake requests while keeping package builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-validation-promotion-blocker-matrix-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract: ok
```
