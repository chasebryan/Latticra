# Debian, FreeBSD, and OpenBSD Package Install/Remove Transcript Contract

Status: active package install/remove transcript contract
Scope: define future disposable install/remove evidence for Debian, FreeBSD, and OpenBSD package artifacts without installing or removing packages.

## Purpose

This contract records the install/remove transcript evidence required before any future Debian, FreeBSD, or OpenBSD package artifact can be accepted as installable validation evidence.

The goal is narrow: a future package install/remove transcript must prove that installation happens only inside a disposable validation environment, the expected no-effect CLI payload appears after install, the package can be removed cleanly, and no host-level service, kernel, privileged-helper, or network authority is introduced.

This contract is documentation-only and static. It does not install packages, remove packages, run package managers, create package artifacts, inspect package artifacts, publish packages, or claim package readiness.

## Current Install/Remove State

```text
debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1
debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1
install_remove_transcript_contract_present=1
install_remove_transcript_contract_state=specified-no-effect
publication_non_claim_review_contract_state=specified-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
package_build_gate_state=closed-no-effect
payload_inspection_contract_state=specified-no-effect
install_remove_disposable_environment_required=1
install_remove_transcript_present=0
install_on_host_run=0
remove_on_host_run=0
host_install_allowed=0
host_remove_allowed=0
host_mutation_allowed=0
service_state_change_allowed=0
package_artifact_created=0
package_payload_accepted=0
publication_non_claim_review_present=1
platform_build_evidence_intake_denied=1
platform_build_evidence_accepted=0
package_readiness_claimed=0
```

## Debian Install/Remove Transcript

Future Debian install/remove validation must run only in a disposable Debian environment.

Required Debian transcript evidence:

```text
debian_install_remove_transcript_required=1
debian_install_remove_transcript_present=0
debian_package_install_run=0
debian_package_remove_run=0
debian_dpkg_install_run=0
debian_apt_install_run=0
debian_dpkg_remove_run=0
debian_apt_remove_run=0
debian_payload_post_install_check_required=1
debian_payload_post_remove_absence_check_required=1
debian_service_state_change_allowed=0
debian_systemd_unit_enable_allowed=0
```

The future Debian transcript must bind install/remove evidence to:

```text
debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb
debian_package_artifact_sha256
debian_payload_expected_bin=usr/bin/latticra
debian_payload_expected_doc=usr/share/doc/latticra/README.md
```

## FreeBSD Install/Remove Transcript

Future FreeBSD install/remove validation must run only in a disposable FreeBSD jail or VM.

Required FreeBSD transcript evidence:

```text
freebsd_install_remove_transcript_required=1
freebsd_install_remove_transcript_present=0
freebsd_package_install_run=0
freebsd_package_remove_run=0
freebsd_pkg_add_run=0
freebsd_pkg_delete_run=0
freebsd_payload_post_install_check_required=1
freebsd_payload_post_remove_absence_check_required=1
freebsd_rc_service_enable_allowed=0
```

The future FreeBSD transcript must bind install/remove evidence to:

```text
freebsd_package_name=latticra-0.0.0.pkg
freebsd_package_artifact_sha256
freebsd_payload_expected_bin=bin/latticra
freebsd_payload_expected_doc=%%DOCSDIR%%/README.md
```

## OpenBSD Install/Remove Transcript

Future OpenBSD install/remove validation must run only in a disposable OpenBSD environment.

Required OpenBSD transcript evidence:

```text
openbsd_install_remove_transcript_required=1
openbsd_install_remove_transcript_present=0
openbsd_package_install_run=0
openbsd_package_remove_run=0
openbsd_pkg_add_run=0
openbsd_pkg_delete_run=0
openbsd_payload_post_install_check_required=1
openbsd_payload_post_remove_absence_check_required=1
openbsd_rc_service_enable_allowed=0
```

The future OpenBSD transcript must bind install/remove evidence to:

```text
openbsd_package_name=latticra-0.0.0.tgz
openbsd_package_artifact_sha256
openbsd_payload_expected_bin=bin/latticra
openbsd_payload_expected_doc=share/doc/latticra/README.md
```

## Transcript Requirements

A future install/remove transcript must record:

```text
environment_identifier
operator_authorization_reference
package_artifact_name
package_artifact_sha256
pre_install_package_state
install_command
install_exit_code
post_install_payload_listing
post_install_cli_no_effect_output
service_state_after_install
remove_command
remove_exit_code
post_remove_absence_report
post_remove_package_state
host_mutation_review
```

The transcript must be reviewed before a package artifact can be accepted as install/remove-valid.

## Current Blockers

Package install/remove acceptance remains blocked under this blocker and dependency state:

```text
package_artifact_created=0
package_artifact_sha256_recorded=0
package_payload_accepted=0
environment_transcript_present=0
explicit_operator_build_authorization=0
publication_non_claim_review_present=1
platform_build_evidence_accepted=0
package_validation_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run dpkg -i
run apt install
run dpkg -r
run apt remove
run FreeBSD pkg add
run FreeBSD pkg delete
run OpenBSD pkg_add
run OpenBSD pkg_delete
install Latticra on a host
remove Latticra from a host
change service state
create package artifacts
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
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
```

The package-build gate remains closed. This install/remove transcript contract only defines the evidence future disposable validation environments must produce after package artifacts exist and payload inspection evidence is accepted.

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

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package build-evidence intake denial review contract before any denial can be re-requested.
```

That future lane should review denied intake requests while keeping package builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-install-remove-transcript-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_install_remove_transcript_contract: ok
```
