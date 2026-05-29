# Debian, FreeBSD, and OpenBSD Source Archive Fixture Lane

Status: active fixture lane
Scope: create and inspect temporary Debian, FreeBSD, and OpenBSD source archive fixtures without running package builds, installing artifacts, or publishing package metadata.

## Purpose

This lane proves that Latticra can form temporary source archives matching the current Debian `orig.tar.gz`, FreeBSD distfile, and OpenBSD distfile expectations, generate them twice, and confirm the repeated SHA-256 value matches.

It does not build packages. It only creates disposable archive fixtures and inspects their contents.

## Current Evidence

```text
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
debian_freebsd_openbsd_source_archive_contract_present=1
temporary_source_archive_created=1
temporary_source_archive_sha256_recorded=1
temporary_source_archive_reproducible=1
temporary_source_archive_generated_twice=1
temporary_source_archive_repeated_sha256_match=1
temporary_debian_orig_archive_created=1
temporary_bsd_distfile_created=1
freebsd_distinfo_checksum_computed=1
freebsd_distinfo_file_written=0
openbsd_distinfo_checksum_computed=1
openbsd_distinfo_file_written=0
source_archive_accepted_for_build=0
package_artifact_created=0
package_readiness_claimed=0
```

## Completed Follow-On Lane

```text
docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
scripts/test-debian-freebsd-openbsd-package-input-handoff-lane.sh
```

## Boundary

This lane does not run `dpkg-source`, `dpkg-buildpackage`, `debuild`, `lintian`, FreeBSD `make stage`, FreeBSD `make package`, OpenBSD `make plist`, OpenBSD `make package`, `portlint`, `portcheck`, `poudriere`, or an OpenBSD bulk build.

It does not write FreeBSD or OpenBSD `distinfo` files.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-source-archive-fixture-lane.sh
```

Expected output:

```text
debian_freebsd_openbsd_source_archive_fixture_lane: ok
```
