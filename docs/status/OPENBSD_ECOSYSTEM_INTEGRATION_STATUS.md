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
packaging/openbsd/README.md
packaging/openbsd/Makefile
packaging/openbsd/pkg/DESCR
packaging/openbsd/pkg/PLIST
scripts/test-openbsd-port-static-validation.sh
.github/workflows/openbsd-port-static-validation.yml
```

## Current Boundary

The OpenBSD lane does not publish a package, submit to the OpenBSD ports tree, claim ports@ review evidence, claim maintainer acceptance, claim bulk build success, claim portcheck success, enable package redistribution, install an rc.d script, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local ports metadata keeps `PERMIT_PACKAGE=No` and `LicenseRef-Latticra-TBD` until license, documentation, source archive, checksum, redistribution, and notice obligations are reviewed.

## Next Recommended Lane

```text
Add an OpenBSD source archive, checksum, and license redistribution contract before accepting PERMIT_PACKAGE=Yes, make plist, make package, portcheck, or bulk build evidence.
```
