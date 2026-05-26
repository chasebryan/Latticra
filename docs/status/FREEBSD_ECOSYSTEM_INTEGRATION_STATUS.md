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
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
freebsd_distinfo_created=0
freebsd_ports_tree_submission_claimed=0
freebsd_bugzilla_pr_claimed=0
freebsd_committer_review_claimed=0
poudriere_build_run=0
make_stage_run=0
make_package_run=0
portlint_run=0
package_artifact_created=0
freebsd_official_port_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/FREEBSD_PORT_STATIC_VALIDATION.md
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
packaging/freebsd/README.md
packaging/freebsd/Makefile
packaging/freebsd/pkg-descr
packaging/freebsd/pkg-plist
scripts/test-freebsd-port-static-validation.sh
scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
.github/workflows/freebsd-port-static-validation.yml
.github/workflows/debian-freebsd-openbsd-source-archive-contract.yml
```

## Current Boundary

The FreeBSD lane does not publish a package, submit to the FreeBSD ports tree, claim Bugzilla PR evidence, claim committer review, claim poudriere success, claim portlint success, install an rc.d service, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local ports metadata keeps `LicenseRef-Latticra-TBD` until license, documentation, source archive, checksum, and notice obligations are reviewed.

The source archive contract records the expected `latticra-0.0.0.tar.gz` distfile and distinfo boundary while keeping archive creation, checksum acceptance, `distinfo`, package artifacts, and build transcript promotion blocked.

## Next Recommended Lane

```text
Add a FreeBSD source archive and checksum contract before accepting make stage, make package, portlint, or poudriere evidence.
```
