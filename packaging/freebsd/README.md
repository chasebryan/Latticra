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
docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-freebsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
.github/workflows/freebsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
```

The static lane preserves:

```text
local_only_draft=1
freebsd_port_draft_present=1
freebsd_port_static_validation_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_package_build_gate_contract_present=1
temporary_freebsd_distfile_staged=1
package_build_gate_state=closed-no-effect
freebsd_build_allowed=0
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
