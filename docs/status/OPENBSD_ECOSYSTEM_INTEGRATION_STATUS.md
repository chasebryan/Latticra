# OpenBSD Ecosystem Integration Status

Status: OpenBSD integration status record
Date: 2026-05-26

## Summary

Latticra now has an OpenBSD-facing local ports metadata draft for the no-effect CLI payload.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
openbsd_port_draft_present=1
openbsd_port_static_validation_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_package_build_gate_contract_present=1
debian_freebsd_openbsd_package_build_environment_contract_present=1
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
temporary_openbsd_distfile_staged=1
package_build_gate_state=closed-no-effect
package_build_environment_contract_state=specified-no-effect
artifact_naming_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
openbsd_build_allowed=0
openbsd_ports_environment_documented=1
openbsd_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
environment_transcript_present=0
openbsd_artifact_name_pattern_recorded=1
openbsd_package_name=latticra-0.0.0.tgz
openbsd_package_artifact_created=0
package_artifact_output_directory_created=0
repository_package_artifact_write_allowed=0
openbsd_payload_expected_bin=bin/latticra
openbsd_payload_expected_doc=share/doc/latticra/README.md
openbsd_payload_inspection_run=0
package_payload_inspection_run=0
package_payload_accepted=0
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
openbsd_distinfo_created=0
openbsd_make_makesum_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
openbsd_ports_tree_submission_claimed=0
openbsd_ports_review_thread_claimed=0
openbsd_maintainer_acceptance_claimed=0
make_package_run=0
make_plist_run=0
bulk_build_run=0
openbsd_bulk_build_run=0
portcheck_run=0
package_artifact_created=0
package_artifact_sha256_recorded=0
install_on_host_run=0
permit_package_enabled=0
openbsd_official_port_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/OPENBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
packaging/openbsd/README.md
packaging/openbsd/Makefile
packaging/openbsd/pkg/DESCR
packaging/openbsd/pkg/PLIST
scripts/test-openbsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-environment-contract.sh
scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh
scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh
.github/workflows/openbsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml
.github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml
.github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml
```

## Current Boundary

The OpenBSD lane does not publish a package, submit to the OpenBSD ports tree, claim ports@ review evidence, claim maintainer acceptance, claim bulk build success, claim portcheck success, enable package redistribution, install an rc.d script, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local ports metadata keeps `PERMIT_PACKAGE=No` and `LicenseRef-Latticra-TBD` until license, documentation, source archive, checksum, redistribution, and notice obligations are reviewed.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and distinfo boundary while keeping archive creation, checksum acceptance, `distinfo`, `PERMIT_PACKAGE=Yes`, package artifacts, and build transcript promotion blocked.

The package-build gate is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`. It keeps `package_build_gate_state=closed-no-effect`, `openbsd_build_allowed=0`, `openbsd_make_makesum_run=0`, `openbsd_make_plist_run=0`, `openbsd_make_package_run=0`, `portcheck_run=0`, and `openbsd_bulk_build_run=0` until source, checksum, license, redistribution, notice, ports environment, operator authorization, payload inspection, install/remove transcript, and publication non-claim evidence exists.

The package-build environment contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md`. It documents the OpenBSD disposable ports environment requirement while keeping `openbsd_build_environment_provisioned=0`, `explicit_operator_build_authorization=0`, `environment_transcript_present=0`, `PERMIT_PACKAGE=No`, and all OpenBSD package build commands disabled.

The package artifact naming contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md`. It records the future `latticra-0.0.0.tgz` artifact name while keeping `openbsd_package_artifact_created=0`, `repository_package_artifact_write_allowed=0`, `package_artifact_sha256_recorded=0`, and `PERMIT_PACKAGE=No`.

The package payload inspection contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md`. It records the expected OpenBSD payload paths while keeping `openbsd_payload_inspection_run=0`, `package_payload_accepted=0`, `package_artifact_created=0`, and `PERMIT_PACKAGE=No`.

## Next Recommended Lane

```text
Add an OpenBSD package install/remove transcript contract before accepting PERMIT_PACKAGE=Yes, make plist, make package, portcheck, or bulk build evidence.
```
