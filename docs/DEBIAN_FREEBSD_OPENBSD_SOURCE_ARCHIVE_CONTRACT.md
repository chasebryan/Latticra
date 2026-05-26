# Debian, FreeBSD, and OpenBSD Source Archive Contract

Status: active source archive contract
Scope: define the evidence required before Debian, FreeBSD, or OpenBSD package/port build evidence can be accepted.

## Purpose

This contract defines the source archive and checksum evidence required before Latticra accepts any Debian, FreeBSD, or OpenBSD package/port build transcript.

The current goal is conservative: record expected source archive names, root layout, checksum requirements, distinfo requirements, transcript fields, and promotion blockers without creating an archive, generating distinfo, or running a package build.

This contract sits after the local-only static packaging drafts and before any `dpkg-buildpackage`, FreeBSD `make stage`, FreeBSD `make package`, OpenBSD `make plist`, OpenBSD `make package`, portlint, portcheck, poudriere, or bulk-build evidence.

## Current Package Inputs

The current local-only Debian draft declares:

```text
Source: latticra
latticra (0.0.0-1local1) UNRELEASED
3.0 (quilt)
```

For the current Debian draft, the expected source archive shape is:

```text
debian_orig_archive_name=latticra_0.0.0.orig.tar.gz
debian_source_root=latticra-0.0.0/
debian_source_format=3.0 (quilt)
```

The current local-only FreeBSD port draft declares:

```text
PORTNAME=	latticra
DISTVERSION=	0.0.0
```

For the current FreeBSD draft, the expected distfile and distinfo shape is:

```text
freebsd_distfile_name=latticra-0.0.0.tar.gz
freebsd_distfile_root=latticra-0.0.0/
freebsd_distinfo_requires_sha256=1
freebsd_distinfo_requires_size=1
```

The current local-only OpenBSD port draft declares:

```text
DISTNAME=	latticra-0.0.0
PERMIT_PACKAGE=	No
```

For the current OpenBSD draft, the expected distfile and distinfo shape is:

```text
openbsd_distfile_name=latticra-0.0.0.tar.gz
openbsd_distfile_root=latticra-0.0.0/
openbsd_distinfo_requires_sha256=1
openbsd_distinfo_requires_size=1
openbsd_permit_package_requires_license_review=1
```

## Required Future Evidence

A future accepted source archive transcript must record:

```text
source_tree_revision
source_archive_command
source_archive_name
source_archive_root
source_archive_size_bytes
source_archive_sha256
source_archive_entry_count
source_archive_generated_twice
source_archive_repeated_sha256_match
source_archive_contains_readme
source_archive_contains_debian_metadata
source_archive_contains_freebsd_port_metadata
source_archive_contains_openbsd_port_metadata
source_archive_excludes_git_dir
source_archive_excludes_nested_archives
source_archive_excludes_build_outputs
source_archive_excludes_package_artifacts
source_archive_symlink_policy_checked
source_archive_path_safety_checked
freebsd_distinfo_sha256_recorded
freebsd_distinfo_size_recorded
openbsd_distinfo_sha256_recorded
openbsd_distinfo_size_recorded
```

## Acceptance Rule

Debian, FreeBSD, and OpenBSD source archive evidence remains unaccepted unless all of these are true:

```text
source_archive_transcript_present=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_package_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
debian_orig_archive_name_matches_expected=1
freebsd_distinfo_sha256_recorded=1
freebsd_distinfo_size_recorded=1
openbsd_distinfo_sha256_recorded=1
openbsd_distinfo_size_recorded=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
openbsd_permit_package_reviewed=1
```

Until those conditions are met, source archive evidence is a review input only, not package build readiness.

## Current Baseline

```text
debian_freebsd_openbsd_source_archive_contract_present=1
debian_local_deb_draft_present=1
freebsd_port_draft_present=1
openbsd_port_draft_present=1
source_archive_policy_recorded=1
debian_orig_archive_name_expected=latticra_0.0.0.orig.tar.gz
freebsd_distfile_name_expected=latticra-0.0.0.tar.gz
openbsd_distfile_name_expected=latticra-0.0.0.tar.gz
source_archive_transcript_present=0
source_archive_created=0
source_archive_sha256_recorded=0
source_archive_reproducible=0
source_archive_accepted_for_build=0
freebsd_distinfo_created=0
openbsd_distinfo_created=0
debian_source_package_created=0
freebsd_package_artifact_created=0
openbsd_package_artifact_created=0
package_readiness_claimed=0
```

## Boundary

This contract does not:

```text
create a source archive
run tar
run gzip
run dpkg-source
run dpkg-buildpackage
run debuild
run lintian
generate FreeBSD distinfo
generate OpenBSD distinfo
run FreeBSD make stage
run FreeBSD make package
run OpenBSD make plist
run OpenBSD make package
run portlint
run portcheck
run poudriere
run an OpenBSD bulk build
create package artifacts
publish to Debian, FreeBSD, or OpenBSD
install Latticra on a host
claim official package or port status
claim production readiness
```

## Next Slice

Recommended next slice:

```text
Add a temporary source archive fixture lane that creates and inspects an archive in a disposable workspace without running package builds or generating package artifacts.
```

That future lane should prove archive shape and reproducibility in a temporary workspace while keeping Debian, FreeBSD, and OpenBSD package build and publication claims blocked.

## Validation

Run:

```sh
sh scripts/test-debian-freebsd-openbsd-source-archive-contract.sh
```

Expected output:

```text
debian_freebsd_openbsd_source_archive_contract: ok
```
