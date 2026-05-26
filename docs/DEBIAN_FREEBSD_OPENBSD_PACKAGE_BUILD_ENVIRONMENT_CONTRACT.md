# Debian, FreeBSD, and OpenBSD Package Build Environment Contract

Status: active package-build environment contract
Scope: document required disposable validation environments for Debian, FreeBSD, and OpenBSD package-build lanes without running package build commands.

## Purpose

This contract documents the minimum environment evidence required before any future Debian, FreeBSD, or OpenBSD package-build lane can ask to open the package-build gate.

The goal is narrow: describe clean/disposable validation environments, required transcript fields, toolchain metadata, package input binding, and host-effect boundaries before any package build command can run.

This contract is documentation-only and static. It does not provision a VM, create a chroot, create a jail, run package build tools, create package artifacts, install Latticra, write FreeBSD or OpenBSD `distinfo` files, or claim package readiness.

## Current Environment State

```text
debian_freebsd_openbsd_package_build_environment_contract_present=1
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
package_build_environment_contract_state=specified-no-effect
artifact_naming_contract_state=specified-no-effect
package_build_gate_state=closed-no-effect
debian_clean_build_environment_documented=1
freebsd_ports_environment_documented=1
openbsd_ports_environment_documented=1
debian_build_environment_provisioned=0
freebsd_build_environment_provisioned=0
openbsd_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
disposable_validation_environment_provisioned=0
environment_transcript_present=0
toolchain_version_capture_required=1
package_input_digest_binding_required=1
package_build_command_allowed=0
package_artifact_created=0
install_on_host_run=0
package_readiness_claimed=0
```

## Debian Environment Contract

A future Debian build lane must use a disposable clean build environment before `dpkg-buildpackage`, `debuild`, or `lintian` can run.

Required Debian environment evidence:

```text
debian_clean_build_environment_documented=1
debian_clean_chroot_or_container_required=1
debian_build_host_identity_required=1
debian_suite_record_required=1
debian_architecture_record_required=1
debian_build_dependency_resolution_transcript_required=1
debian_toolchain_versions_required=1
debian_source_archive_digest_required=1
debian_package_input_path_required=1
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
```

The Debian environment contract does not choose between `sbuild`, `pbuilder`, `mmdebstrap`, a disposable container, or a disposable VM. A future effect-bearing proposal must name the exact environment and keep the build gate closed until operator authorization and all package prerequisites exist.

## FreeBSD Environment Contract

A future FreeBSD build lane must use a disposable FreeBSD ports validation environment before `make makesum`, `make stage`, `make package`, `portlint`, or `poudriere` can run.

Required FreeBSD environment evidence:

```text
freebsd_ports_environment_documented=1
freebsd_jail_or_vm_required=1
freebsd_version_record_required=1
freebsd_architecture_record_required=1
freebsd_ports_tree_revision_required=1
freebsd_distfile_digest_required=1
freebsd_port_origin_required=1
freebsd_toolchain_versions_required=1
freebsd_distinfo_review_required=1
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
portlint_run=0
poudriere_run=0
```

The FreeBSD environment contract does not create a jail, fetch a ports tree, run `make makesum`, run `make stage`, run `make package`, run portlint, or run poudriere.

## OpenBSD Environment Contract

A future OpenBSD build lane must use a disposable OpenBSD ports validation environment before `make makesum`, `make plist`, `make package`, `portcheck`, or a bulk build can run.

Required OpenBSD environment evidence:

```text
openbsd_ports_environment_documented=1
openbsd_vm_or_disposable_host_required=1
openbsd_version_record_required=1
openbsd_architecture_record_required=1
openbsd_ports_tree_revision_required=1
openbsd_distfile_digest_required=1
openbsd_port_origin_required=1
openbsd_toolchain_versions_required=1
openbsd_permit_package_review_required=1
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
portcheck_run=0
openbsd_bulk_build_run=0
```

The OpenBSD environment contract keeps `PERMIT_PACKAGE=No` until redistribution, license, notice, checksum, and maintainer-review evidence exists.

## Shared Transcript Requirements

A future environment transcript must record:

```text
environment_identifier
environment_lifecycle
host_or_vm_class
operating_system_name
operating_system_version
architecture
toolchain_versions
package_input_archive_name
package_input_archive_sha256
package_input_tree_path
package_output_directory
network_policy
host_mount_policy
cleanup_policy
operator_authorization_reference
```

The transcript must be reviewed before a package-build lane can claim that the environment is acceptable.

## Current Blockers

Package builds remain blocked because the current repository still has:

```text
source_archive_accepted_for_build=0
license_expression_reviewed=1
package_notice_obligations_reviewed=0
explicit_operator_build_authorization=0
artifact_naming_contract_present=1
install_remove_transcript_contract_present=0
payload_inspection_contract_present=0
publication_non_claim_review_present=0
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
install Latticra on a host
publish package artifacts
submit Latticra to Debian, FreeBSD, or OpenBSD
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
```

The package-build gate remains closed. This environment contract only records what future disposable validation environments must prove before a platform-specific build lane can request authorization.

## Completed Follow-On Lane

Completed follow-on lane:

```text
Add a Debian, FreeBSD, and OpenBSD package artifact naming contract before any package artifact can be created.
```

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh
```

That lane defines package artifact names, output directories, checksum binding, retention rules, and publication non-claims while keeping `package_build_gate_state=closed-no-effect`.

## Next Slice

Recommended next slice:

```text
Add a Debian, FreeBSD, and OpenBSD package payload inspection contract before any package artifact can be accepted.
```

That future lane should define payload inspection evidence for Debian, FreeBSD, and OpenBSD packages without creating package artifacts.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-build-environment-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_build_environment_contract: ok
```
