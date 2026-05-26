# Debian, FreeBSD, and OpenBSD Source Archive Contract

Status: active source archive contract
Scope: define evidence required before Debian, FreeBSD, or OpenBSD package/port build evidence can be accepted.

## Purpose

This contract records source archive, checksum, and distinfo blockers before any Debian, FreeBSD, or OpenBSD package build lane can run.

The contract does not create source archives, generate distinfo files, run package build tools, install Latticra, publish artifacts, or claim package readiness.

## Expected Inputs

```text
debian_orig_archive_name=latticra_0.0.0.orig.tar.gz
debian_source_root=latticra-0.0.0/
freebsd_distfile_name=latticra-0.0.0.tar.gz
freebsd_distfile_root=latticra-0.0.0/
openbsd_distfile_name=latticra-0.0.0.tar.gz
openbsd_distfile_root=latticra-0.0.0/
openbsd_permit_package_requires_license_review=1
```

## Current Baseline

```text
debian_freebsd_openbsd_source_archive_contract_present=1
source_archive_policy_recorded=1
source_archive_created=0
source_archive_sha256_recorded=0
source_archive_accepted_for_build=0
freebsd_distinfo_created=0
openbsd_distinfo_created=0
package_artifact_created=0
package_readiness_claimed=0
```

## Completed Follow-On Lanes

```text
docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
```

## Boundary

This contract does not run `dpkg-source`, `dpkg-buildpackage`, `debuild`, `lintian`, FreeBSD `make stage`, FreeBSD `make package`, OpenBSD `make plist`, OpenBSD `make package`, `portlint`, `portcheck`, `poudriere`, or an OpenBSD bulk build.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_source_archive_contract: ok
```
