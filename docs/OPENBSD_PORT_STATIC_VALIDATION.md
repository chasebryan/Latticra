# OpenBSD Port Static Validation

Status: active static validation lane
Scope: static checks for the local-only OpenBSD ports metadata draft.

## Purpose

This lane checks that the OpenBSD port draft is present, narrow, and honest.

It verifies local ports metadata shape for the no-effect CLI payload, but it does not run `make package`, `make plist`, `portcheck`, a bulk build, or `pkg_add`, and it does not create package artifacts.

## Guarded Files

```text
packaging/openbsd/README.md
packaging/openbsd/Makefile
packaging/openbsd/pkg/DESCR
packaging/openbsd/pkg/PLIST
docs/OPENBSD_PORT_STATIC_VALIDATION.md
docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-openbsd-port-static-validation.sh
.github/workflows/openbsd-port-static-validation.yml
```

## Preserved Boundary

```text
local_only_draft=1
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
production_readiness_claimed=0
```

## Package Intent

The local OpenBSD port draft records only this initial payload shape:

```text
bin/latticra
share/doc/latticra/README.md
```

The CLI remains the no-effect status surface from:

```text
src/latticra_cli.c
```

## Explicit Non-Claims

This static lane does not:

```text
build a package artifact
install a package artifact
submit to the OpenBSD ports tree
claim ports@ review evidence
claim maintainer acceptance
claim bulk build success
claim portcheck success
enable package redistribution
install an rc.d script
install kernel modules
write /etc or /bsd
claim production readiness
```

## Next Recommended Lane

Add an OpenBSD source archive, checksum, and license redistribution contract before accepting `PERMIT_PACKAGE=Yes`, `make plist`, `make package`, portcheck, or bulk build evidence.

## Validation

Run:

```sh
sh scripts/test-openbsd-port-static-validation.sh
```

Expected output:

```text
openbsd_port_static_validation: ok
```
