# FreeBSD Ecosystem Integration Status

Status: FreeBSD integration status record
Date: 2026-05-26

## Summary

Latticra now has a FreeBSD-facing local ports metadata draft for the no-effect CLI payload.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
freebsd_port_draft_present=1
freebsd_port_static_validation_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_package_build_gate_contract_present=1
debian_freebsd_openbsd_package_build_environment_contract_present=1
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
temporary_freebsd_distfile_staged=1
package_build_gate_state=closed-no-effect
package_build_environment_contract_state=specified-no-effect
artifact_naming_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
freebsd_build_allowed=0
freebsd_ports_environment_documented=1
freebsd_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
environment_transcript_present=0
freebsd_artifact_name_pattern_recorded=1
freebsd_package_name=latticra-0.0.0.pkg
freebsd_package_artifact_created=0
package_artifact_output_directory_created=0
repository_package_artifact_write_allowed=0
freebsd_payload_expected_bin=bin/latticra
freebsd_payload_expected_doc=%%DOCSDIR%%/README.md
freebsd_payload_inspection_run=0
package_payload_inspection_run=0
package_payload_accepted=0
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
freebsd_distinfo_created=0
freebsd_make_makesum_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
freebsd_ports_tree_submission_claimed=0
freebsd_bugzilla_pr_claimed=0
freebsd_committer_review_claimed=0
poudriere_build_run=0
poudriere_run=0
make_stage_run=0
make_package_run=0
portlint_run=0
package_artifact_created=0
package_artifact_sha256_recorded=0
install_on_host_run=0
freebsd_official_port_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/FREEBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
packaging/freebsd/README.md
packaging/freebsd/Makefile
packaging/freebsd/pkg-descr
packaging/freebsd/pkg-plist
scripts/test-freebsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-environment-contract.sh
scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh
scripts/test-debian-freebsd-openbsd-package-payload-inspection-contract.sh
.github/workflows/freebsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml
.github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml
.github/workflows/debian-freebsd-openbsd-package-payload-inspection-contract.yml
```

## Current Boundary

The FreeBSD lane does not publish a package, submit to the FreeBSD ports tree, claim Bugzilla PR evidence, claim committer review, claim poudriere success, claim portlint success, install an rc.d service, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local ports metadata keeps `LicenseRef-Latticra-TBD` until license, documentation, source archive, checksum, and notice obligations are reviewed.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and distinfo boundary while keeping archive creation, checksum acceptance, `distinfo`, package artifacts, and build transcript promotion blocked.

The package-build gate is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`. It keeps `package_build_gate_state=closed-no-effect`, `freebsd_build_allowed=0`, `freebsd_make_stage_run=0`, `freebsd_make_package_run=0`, `freebsd_make_makesum_run=0`, `portlint_run=0`, and `poudriere_run=0` until source, checksum, license, notice, ports environment, operator authorization, payload inspection, install/remove transcript, and publication non-claim evidence exists.

The package-build environment contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md`. It documents the FreeBSD jail or VM ports environment requirement while keeping `freebsd_build_environment_provisioned=0`, `explicit_operator_build_authorization=0`, `environment_transcript_present=0`, and all FreeBSD package build commands disabled.

The package artifact naming contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md`. It records the future `latticra-0.0.0.pkg` artifact name while keeping `freebsd_package_artifact_created=0`, `repository_package_artifact_write_allowed=0`, and `package_artifact_sha256_recorded=0`.

The package payload inspection contract is recorded in `docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md`. It records the expected FreeBSD payload paths while keeping `freebsd_payload_inspection_run=0`, `package_payload_accepted=0`, and `package_artifact_created=0`.

## Next Recommended Lane

```text
Add a FreeBSD package install/remove transcript contract before accepting make stage, make package, portlint, or poudriere evidence.
```
