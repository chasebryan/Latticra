# Debian, FreeBSD, and OpenBSD Package Input Handoff Lane

Status: active temporary package input handoff lane
Scope: stage verified temporary source archives into Debian, FreeBSD, and OpenBSD package input layouts without running package builds or creating package artifacts.

## Purpose

This lane advances the Debian, FreeBSD, and OpenBSD package/port path from a source archive fixture into package-input staging.

The goal is conservative: prove that the temporary Debian `orig.tar.gz`, FreeBSD distfile, and OpenBSD distfile can be staged into platform-shaped input directories while preserving checksum identity and keeping all package build tools disabled.

This lane does not build Debian source packages, Debian binary packages, FreeBSD packages, or OpenBSD packages. It stages temporary package inputs only.

## Temporary Input Layouts

The Debian handoff stages:

```text
debian/latticra_0.0.0.orig.tar.gz
debian/latticra-0.0.0/
debian/latticra-0.0.0/debian/control
debian/latticra-0.0.0/debian/changelog
```

The FreeBSD handoff stages:

```text
freebsd/distfiles/latticra-0.0.0.tar.gz
freebsd/ports/devel/latticra/Makefile
freebsd/ports/devel/latticra/pkg-descr
freebsd/ports/devel/latticra/pkg-plist
```

The OpenBSD handoff stages:

```text
openbsd/distfiles/latticra-0.0.0.tar.gz
openbsd/ports/devel/latticra/Makefile
openbsd/ports/devel/latticra/pkg/DESCR
openbsd/ports/devel/latticra/pkg/PLIST
```

All paths are created under a disposable temporary directory.

## Handoff Checks

The lane verifies:

```text
temporary_package_input_handoff_lane_present=1
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
temporary_freebsd_port_input_staged=1
temporary_freebsd_distfile_staged=1
temporary_openbsd_port_input_staged=1
temporary_openbsd_distfile_staged=1
temporary_archive_sha256_preserved=1
temporary_archive_listing_preserved=1
freebsd_distinfo_file_written=0
openbsd_distinfo_file_written=0
package_artifact_created=0
```

## Boundary

This lane does not run `dpkg-source`.

It does not run `dpkg-buildpackage`.

It does not run `debuild`.

It does not run `lintian`.

It does not run FreeBSD `make makesum`.

It does not run FreeBSD `make stage`.

It does not run FreeBSD `make package`.

It does not run OpenBSD `make makesum`.

It does not run OpenBSD `make plist`.

It does not run OpenBSD `make package`.

It does not run `portlint`.

It does not run `portcheck`.

It does not run `poudriere`.

It does not run an OpenBSD bulk build.

It does not create package artifacts.

It does not write FreeBSD or OpenBSD `distinfo` files.

It does not install Latticra.

It does not publish package artifacts.

It does not submit Latticra to Debian, FreeBSD, or OpenBSD.

It does not claim Debian archive readiness, Debian sponsorship, FreeBSD official port status, OpenBSD official port status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, policy readiness, or security-hardening completion.

## Current Evidence

```text
debian_freebsd_openbsd_package_input_handoff_lane_present=1
debian_freebsd_openbsd_source_archive_fixture_lane_present=1
temporary_package_input_handoff_lane_present=1
temporary_debian_source_input_staged=1
temporary_debian_orig_archive_staged=1
temporary_debian_debian_dir_overlay_staged=1
temporary_freebsd_port_input_staged=1
temporary_freebsd_distfile_staged=1
temporary_openbsd_port_input_staged=1
temporary_openbsd_distfile_staged=1
temporary_archive_sha256_preserved=1
temporary_archive_listing_preserved=1
freebsd_distinfo_file_written=0
openbsd_distinfo_file_written=0
dpkg_source_run=0
dpkg_buildpackage_run=0
freebsd_make_stage_run=0
freebsd_make_package_run=0
openbsd_make_plist_run=0
openbsd_make_package_run=0
package_artifact_created=0
package_readiness_claimed=0
```

The handoff evidence is temporary package-input staging only. It does not promote the archive to accepted package-build input.

## Next Slice

Recommended next slice:

```text
Add Debian, FreeBSD, and OpenBSD package-build evidence gate contract before any package build command can run.
```

That future lane should define the exact evidence required before `dpkg-buildpackage`, FreeBSD package builds, or OpenBSD package builds are allowed in any validation environment.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-package-input-handoff-lane.sh
```

Expected output:

```text
debian_freebsd_openbsd_package_input_handoff_lane: ok
```
