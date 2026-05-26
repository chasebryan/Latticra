# FreeBSD Port Draft

Status: local-only port draft

This directory contains FreeBSD ports metadata experiments for Latticra.

The current port files are a local-only draft used by static guards. They are not a FreeBSD ports tree submission, not a Bugzilla PR, not committer review evidence, not a poudriere build, not a `make package` result, not a portlint result, and not package-readiness evidence.

## Where This Fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- FreeBSD status: [`../../docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md`](../../docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/freebsd/README.md
packaging/freebsd/Makefile
packaging/freebsd/pkg-descr
packaging/freebsd/pkg-plist
docs/FREEBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
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

The static lane preserves:

```text
local_only_draft=1
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
make_package_run=0
portlint_run=0
package_artifact_created=0
package_artifact_sha256_recorded=0
install_on_host_run=0
freebsd_official_port_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
bin/latticra
%%DOCSDIR%%/README.md
```

The CLI reports no-effect status and disabled runtime behavior.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and future distinfo boundary, but it does not create an archive, generate `distinfo`, run `make stage`, run `make package`, run portlint, or accept FreeBSD build evidence.

The package-build gate is recorded in [`../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`](../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md). It keeps `package_build_gate_state=closed-no-effect` and `freebsd_build_allowed=0` until source, checksum, license, notice, ports environment, operator authorization, payload inspection, install/remove, and publication non-claim evidence exists.

The package-build environment contract is recorded in [`../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md`](../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md). It documents the FreeBSD jail or VM ports environment requirement while keeping `freebsd_build_environment_provisioned=0`, `explicit_operator_build_authorization=0`, and all FreeBSD build commands disabled.

The package artifact naming contract is recorded in [`../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md`](../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md). It records the future `latticra-0.0.0.pkg` artifact name while keeping `freebsd_package_artifact_created=0`, `repository_package_artifact_write_allowed=0`, and `package_artifact_sha256_recorded=0`.

The package payload inspection contract is recorded in [`../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md`](../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md). It records the expected FreeBSD payload paths while keeping `freebsd_payload_inspection_run=0`, `package_payload_accepted=0`, and `package_artifact_created=0`.
