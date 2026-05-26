# Debian, FreeBSD, and OpenBSD Package Build Gate Contract

Status: active package-build evidence gate contract
Scope: define the evidence required before Debian, FreeBSD, or OpenBSD package build commands can run in any validation lane.

## Purpose

This contract closes the package-build gate after the temporary source archive fixture lane and temporary package input handoff lane.

The goal is conservative: record the exact prerequisites required before `dpkg-buildpackage`, `debuild`, `lintian`, FreeBSD package builds, OpenBSD package builds, port linters, bulk builders, host installs, or package artifact publication can be attempted or accepted as evidence.

This contract is documentation-only and static. It does not run package build tools, create package artifacts, install Latticra, write FreeBSD or OpenBSD `distinfo` files, or claim package readiness.

## Current Gate State

```text
debian_freebsd_openbsd_package_build_gate_contract_present=1
package_build_gate_state=closed-no-effect
debian_build_allowed=0
freebsd_build_allowed=0
openbsd_build_allowed=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
freebsd_make_makesum_run=0
portlint_run=0
poudriere_run=0
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
openbsd_bulk_build_run=0
package_artifact_created=0
install_on_host_run=0
package_readiness_claimed=0
```

## Required Gate Inputs

The package-build gate cannot open unless all package input evidence has already passed:

```text
debian_freebsd_openbsd_package_input_handoff_lane_present=1
temporary_package_input_handoff_lane_passed=1
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
temporary_archive_sha256_preserved=1
temporary_archive_listing_preserved=1
source_archive_accepted_for_build=1
freebsd_distinfo_file_written=0
openbsd_distinfo_file_written=0
distinfo_file_writes_blocked_until_review=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
openbsd_permit_package_reviewed=1
```

The `source_archive_accepted_for_build=1` value is a future prerequisite, not a current claim. The current source archive and handoff lanes still keep source archive acceptance closed.

## Environment Prerequisites

Before any package build command can run, a future build-lane proposal must document:

```text
debian_clean_build_environment_documented=1
freebsd_ports_environment_documented=1
openbsd_ports_environment_documented=1
explicit_operator_build_authorization=1
disposable_validation_environment=1
artifact_naming_contract_present=1
install_remove_transcript_contract_present=1
payload_inspection_contract_present=1
publication_non_claim_review_present=1
```

Those records must identify the exact host or VM class, toolchain versions, source archive digest, package input paths, package output paths, install target, remove target, and transcript retention location before a build can be attempted.

## Command Gate

All package build commands remain blocked while the current gate state is `closed-no-effect`.

Debian commands blocked by this contract:

```text
dpkg-buildpackage
debuild
lintian
dpkg-source --build
```

FreeBSD commands blocked by this contract:

```text
make makesum
make stage
make package
portlint
poudriere
```

OpenBSD commands blocked by this contract:

```text
make makesum
make plist
make package
portcheck
bulk build
```

Host effects blocked by this contract:

```text
install package on host
remove package from host
publish package artifact
submit package or port upstream
claim official package or port status
claim production readiness
```

## Future Open Conditions

A future package-build lane may move one platform from `*_build_allowed=0` to `*_build_allowed=1` only after it records:

```text
package_build_gate_state=open-for-single-platform-validation
source_archive_accepted_for_build=1
archive_sha256_bound_to_build=1
distinfo_file_writes_reviewed=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
debian_clean_build_environment_documented=1
freebsd_ports_environment_documented=1
openbsd_ports_environment_documented=1
explicit_operator_build_authorization=1
disposable_validation_environment=1
artifact_naming_contract_present=1
install_remove_transcript_contract_present=1
payload_inspection_contract_present=1
publication_non_claim_review_present=1
```

Opening one platform gate must not imply readiness for the other platforms.

## Current Non-Claims

```text
debian_archive_ready=0
debian_mentors_upload_claimed=0
debian_sponsorship_claimed=0
debian_ftp_master_acceptance_claimed=0
freebsd_official_port_claimed=0
freebsd_ports_tree_submission_claimed=0
freebsd_bugzilla_pr_claimed=0
freebsd_committer_review_claimed=0
openbsd_official_port_claimed=0
openbsd_ports_tree_submission_claimed=0
openbsd_ports_review_thread_claimed=0
openbsd_maintainer_acceptance_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
```

The source archive fixture lane proves temporary archive shape in a disposable workspace.

The package input handoff lane proves temporary package input staging while preserving archive SHA-256 identity.

This package-build gate keeps package build execution closed until source acceptance, checksum, license, notice, environment, authorization, payload inspection, install/remove, and publication non-claim evidence exists.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package-build environment contract that documents disposable validation environments without running package build commands.
```

That future lane should keep `package_build_gate_state=closed-no-effect` until environment evidence, operator authorization evidence, artifact naming, install/remove transcript rules, payload inspection rules, and publication non-claim review are all present.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_build_gate_contract: ok
```
