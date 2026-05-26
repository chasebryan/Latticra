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
temporary_openbsd_distfile_staged=1
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
openbsd_distinfo_created=0
openbsd_ports_tree_submission_claimed=0
openbsd_ports_review_thread_claimed=0
openbsd_maintainer_acceptance_claimed=0
make_package_run=0
make_plist_run=0
bulk_build_run=0
portcheck_run=0
package_artifact_created=0
permit_package_enabled=0
openbsd_official_port_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/OPENBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
packaging/openbsd/README.md
packaging/openbsd/Makefile
packaging/openbsd/pkg/DESCR
packaging/openbsd/pkg/PLIST
scripts/test-openbsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
.github/workflows/openbsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
```

## Current Boundary

The OpenBSD lane does not publish a package, submit to the OpenBSD ports tree, claim ports@ review evidence, claim maintainer acceptance, claim bulk build success, claim portcheck success, enable package redistribution, install an rc.d script, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local ports metadata keeps `PERMIT_PACKAGE=No` and `LicenseRef-Latticra-TBD` until license, documentation, source archive, checksum, redistribution, and notice obligations are reviewed.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and distinfo boundary while keeping archive creation, checksum acceptance, `distinfo`, `PERMIT_PACKAGE=Yes`, package artifacts, and build transcript promotion blocked.

## Next Recommended Lane

```text
Add an OpenBSD source archive, checksum, and license redistribution contract before accepting PERMIT_PACKAGE=Yes, make plist, make package, portcheck, or bulk build evidence.
```
