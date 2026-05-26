# OpenBSD Port Draft

Status: local-only port draft

This directory contains OpenBSD ports metadata experiments for Latticra.

The current port files are a local-only draft used by static guards. They are not an OpenBSD ports tree submission, not a ports@ review thread, not maintainer acceptance evidence, not a `make package` result, not a bulk build result, not a portcheck result, and not package-readiness evidence.

## Where This Fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- OpenBSD status: [`../../docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md`](../../docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/openbsd/README.md
packaging/openbsd/Makefile
packaging/openbsd/pkg/DESCR
packaging/openbsd/pkg/PLIST
docs/OPENBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md
docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-openbsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
scripts/test-debian-freebsd-openbsd-package-build-gate-contract.sh
.github/workflows/openbsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
.github/workflows/debian-freebsd-openbsd-package-build-gate-contract.yml
```

The static lane preserves:

```text
local_only_draft=1
openbsd_port_draft_present=1
openbsd_port_static_validation_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_package_build_gate_contract_present=1
temporary_openbsd_distfile_staged=1
package_build_gate_state=closed-no-effect
openbsd_build_allowed=0
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
bulk_build_run=0
openbsd_bulk_build_run=0
portcheck_run=0
package_artifact_created=0
install_on_host_run=0
permit_package_enabled=0
openbsd_official_port_claimed=0
production_readiness_claimed=0
```

The draft payload remains intentionally narrow:

```text
bin/latticra
share/doc/latticra/README.md
```

The CLI reports no-effect status and disabled runtime behavior.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and future distinfo boundary, but it does not create an archive, generate `distinfo`, run `make plist`, run `make package`, run portcheck, run a bulk build, or accept OpenBSD build evidence.

The package-build gate is recorded in [`../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`](../../docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md). It keeps `package_build_gate_state=closed-no-effect`, `openbsd_build_allowed=0`, and `PERMIT_PACKAGE=No` until source, checksum, license, redistribution, notice, ports environment, operator authorization, payload inspection, install/remove, and publication non-claim evidence exists.
