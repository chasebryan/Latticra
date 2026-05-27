# Debian, FreeBSD, and OpenBSD Package Artifact Naming Contract

Status: active package artifact naming contract
Scope: define future Debian, FreeBSD, and OpenBSD package artifact names and output boundaries without creating package artifacts.

## Purpose

This contract records the artifact names, output-directory rules, checksum binding, retention requirements, and publication non-claims required before any future Debian, FreeBSD, or OpenBSD package build can create package files.

The goal is narrow: package artifacts must have predictable names, be written only inside a disposable validation environment, bind back to the source archive digest, and remain non-published review outputs until separate payload inspection, install/remove, and publication review contracts exist.

This contract is documentation-only and static. It does not run package build tools, create package artifacts, install Latticra, write FreeBSD or OpenBSD `distinfo` files, publish packages, or claim package readiness.

## Current Artifact Naming State

```text
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1
debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_review_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1
artifact_naming_contract_present=1
artifact_naming_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
publication_non_claim_review_contract_state=specified-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
build_evidence_intake_denial_disposition_state=closed-upheld-no-effect
build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect
build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect
package_build_gate_state=closed-no-effect
package_build_environment_contract_state=specified-no-effect
package_artifact_output_directory_required_under_disposable_environment=1
package_artifact_output_directory_created=0
repository_package_artifact_write_allowed=0
publication_directory_write_allowed=0
package_artifact_created=0
deb_artifact_created=0
debian_source_package_created=0
freebsd_package_artifact_created=0
openbsd_package_artifact_created=0
package_artifact_sha256_recorded=0
package_artifact_published=0
install_on_host_run=0
publication_non_claim_review_present=1
platform_build_evidence_intake_denied=1
denial_disposition_present=1
denial_disposition_closeout_present=1
denial_archive_gate_present=1
denial_archive_gate_state=closed-no-effect
denial_closed=1
denial_archived=0
denial_archive_allowed=0
denial_archive_record_write_allowed=0
denial_archive_record_written=0
denial_re_request_allowed=0
platform_build_evidence_accepted=0
package_readiness_claimed=0
```

## Debian Artifact Names

Future Debian artifact names must be derived from the current Debian changelog version and the clean build environment architecture.

```text
debian_source_package_name=latticra_0.0.0-1local1.dsc
debian_orig_archive_name=latticra_0.0.0.orig.tar.gz
debian_debian_tar_name=latticra_0.0.0-1local1.debian.tar.xz
debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb
debian_changes_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.changes
debian_buildinfo_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.buildinfo
debian_artifact_name_pattern_recorded=1
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
deb_artifact_created=0
debian_source_package_created=0
```

The `${DEB_HOST_ARCH}` token must be resolved from the disposable Debian environment transcript before any Debian artifact can be accepted.

## FreeBSD Artifact Names

Future FreeBSD package artifact names must be derived from the current port `PORTNAME` and `DISTVERSION`.

```text
freebsd_package_name=latticra-0.0.0.pkg
freebsd_distfile_name=latticra-0.0.0.tar.gz
freebsd_artifact_name_pattern_recorded=1
freebsd_package_artifact_created=0
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_run=0
```

The FreeBSD package name is a future local validation artifact only. It is not a FreeBSD ports-tree submission, poudriere result, official package, or publication claim.

## OpenBSD Artifact Names

Future OpenBSD package artifact names must be derived from the current port `DISTNAME`.

```text
openbsd_package_name=latticra-0.0.0.tgz
openbsd_distfile_name=latticra-0.0.0.tar.gz
openbsd_artifact_name_pattern_recorded=1
openbsd_package_artifact_created=0
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
openbsd_bulk_build_run=0
```

The OpenBSD package name is a future local validation artifact only. `PERMIT_PACKAGE=No` remains in force until license, redistribution, notice, checksum, and maintainer-review evidence exists.

## Output Boundary

Future package artifacts must be written only under a disposable validation environment output directory. The repository itself remains a no-artifact workspace.

```text
artifact_output_root_under_disposable_environment=1
debian_artifact_output_directory=artifacts/debian/
freebsd_artifact_output_directory=artifacts/freebsd/
openbsd_artifact_output_directory=artifacts/openbsd/
repository_package_artifact_write_allowed=0
root_workspace_package_artifact_write_allowed=0
publication_directory_write_allowed=0
artifact_retention_policy_required=1
artifact_cleanup_policy_required=1
```

Any future artifact transcript must bind each package file to:

```text
source_archive_sha256
package_input_archive_sha256
package_artifact_sha256
artifact_size_bytes
artifact_output_directory
artifact_generation_command
environment_identifier
operator_authorization_reference
```

## Current Blockers

Package artifact creation remains blocked under this blocker and dependency state:

```text
source_archive_accepted_for_build=0
license_expression_reviewed=1
package_notice_obligations_reviewed=0
explicit_operator_build_authorization=0
environment_transcript_present=0
install_remove_transcript_contract_present=1
payload_inspection_contract_present=1
publication_non_claim_review_present=1
platform_build_evidence_accepted=0
package_validation_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run dpkg-buildpackage
run debuild
run lintian
run FreeBSD make stage
run FreeBSD make package
run portlint
run poudriere
run OpenBSD make plist
run OpenBSD make package
run portcheck
run an OpenBSD bulk build
create .deb artifacts
create .dsc artifacts
create .changes artifacts
create .buildinfo artifacts
create .pkg artifacts
create .tgz artifacts
install Latticra on a host
publish package artifacts
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
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
```

The package-build gate remains closed. This artifact naming contract only records the names and output boundaries future validation artifacts must use after separate source, license, notice, environment, authorization, payload inspection, install/remove, and publication non-claim evidence exists.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package payload inspection contract before any package artifact can be accepted.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh
```

That lane defines how package payloads are inspected after creation while keeping `package_build_gate_state=closed-no-effect` until the remaining prerequisites are satisfied.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package install/remove transcript contract before any package install can be accepted.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-install-remove-transcript-contract.sh
```

That lane defines disposable install/remove evidence while keeping host installs and package readiness blocked.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package publication non-claim review contract before any package validation result can be promoted.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-publication-non-claim-review-contract.sh
```

That lane records local-only publication and official-port non-claims while keeping package publication and readiness blocked.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package validation promotion blocker matrix before any platform-specific build evidence can be accepted.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-validation-promotion-blocker-matrix-contract.sh
```

That lane ties source, environment, artifact, payload, install/remove, and publication non-claim blockers together while keeping platform build evidence acceptance and validation promotion blocked.

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

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition contract before any reviewed denial can be closed or re-requested.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-disposition-contract.sh
```

That lane records the reviewed denial disposition while keeping package builds and readiness blocked.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition closeout contract before any disposed denial can be archived or re-requested.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-disposition-closeout-contract.sh
```

That lane closes out the no-effect disposition while keeping archive, package builds, and readiness blocked.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition closeout archive gate contract before any closed-out denial can be archived or re-requested.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh
```

That lane keeps archiving and re-request blocked while preserving package build and readiness blockers.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial disposition closeout archive gate review contract before any archive gate can be relaxed or re-requested.
```

That future lane should review the closed archive gate while preserving package build and readiness blockers.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_artifact_naming_contract: ok
```
