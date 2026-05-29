# FreeBSD Port Static Validation

Status: active static validation lane
Scope: static checks for the local-only FreeBSD ports metadata draft.

## Purpose

This lane checks that the FreeBSD port draft is present, narrow, and honest.

It verifies local ports metadata shape for the no-effect CLI payload, but it does not run `make package`, `make stage`, `poudriere`, `portlint`, or `pkg install`, and it does not create package artifacts.

## Guarded Files

```text
packaging/freebsd/README.md
packaging/freebsd/Makefile
packaging/freebsd/pkg-descr
packaging/freebsd/pkg-plist
docs/FREEBSD_PORT_STATIC_VALIDATION.md
docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-freebsd-port-static-validation.sh
.github/workflows/freebsd-port-static-validation.yml
```

## Preserved Boundary

```text
local_only_draft=1
freebsd_port_draft_present=1
freebsd_port_static_validation_present=1
freebsd_ports_tree_submission_claimed=0
freebsd_bugzilla_pr_claimed=0
freebsd_committer_review_claimed=0
poudriere_build_run=0
make_stage_run=0
make_package_run=0
portlint_run=0
package_artifact_created=0
freebsd_official_port_claimed=0
production_readiness_claimed=0
```

## Package Intent

The local FreeBSD port draft records only this initial payload shape:

```text
bin/latticra
%%DOCSDIR%%/README.md
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
submit to the FreeBSD ports tree
claim Bugzilla PR evidence
claim FreeBSD committer review
claim poudriere success
claim portlint success
install an rc.d service
install kernel modules
write /etc or /boot
claim production readiness
```

## Next Recommended Lane

Add a FreeBSD source archive and checksum contract before accepting `make stage`, `make package`, portlint, or poudriere evidence.

## Validation

Run:

```sh
sh scripts/test-freebsd-port-static-validation.sh
```

Expected output:

```text
freebsd_port_static_validation: ok
```
