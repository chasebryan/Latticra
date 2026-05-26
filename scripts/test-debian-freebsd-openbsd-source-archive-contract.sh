#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd source archive contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd source archive contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_file packaging/debian/debian/changelog
require_file packaging/freebsd/Makefile
require_file packaging/openbsd/Makefile

require_contains 'Status: active source archive contract' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'debian_orig_archive_name=latticra_0.0.0.orig.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'freebsd_distfile_name=latticra-0.0.0.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'openbsd_distfile_name=latticra-0.0.0.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_created=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_accepted_for_build=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'debian_freebsd_openbsd_source_archive_contract: ok' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'latticra (0.0.0-1local1) UNRELEASED' packaging/debian/debian/changelog
require_contains 'DISTVERSION=	0.0.0' packaging/freebsd/Makefile
require_contains 'DISTNAME=	latticra-0.0.0' packaging/openbsd/Makefile

printf 'debian_freebsd_openbsd_source_archive_contract: ok\n'
