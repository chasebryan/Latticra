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

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd source archive contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_file docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_file docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_file docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_file docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/debian/README.md
require_file packaging/debian/debian/control
require_file packaging/debian/debian/changelog
require_file packaging/debian/debian/source/format
require_file packaging/freebsd/README.md
require_file packaging/freebsd/Makefile
require_file packaging/openbsd/README.md
require_file packaging/openbsd/Makefile
require_file README.md

require_contains 'Status: active source archive contract' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'latticra (0.0.0-1local1) UNRELEASED' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'debian_orig_archive_name=latticra_0.0.0.orig.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'freebsd_distfile_name=latticra-0.0.0.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'openbsd_distfile_name=latticra-0.0.0.tar.gz' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_generated_twice' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_repeated_sha256_match' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_excludes_git_dir' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_excludes_nested_archives' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_symlink_policy_checked' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'freebsd_distinfo_sha256_recorded' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'openbsd_distinfo_sha256_recorded' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_created=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_reproducible=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'source_archive_accepted_for_build=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'freebsd_distinfo_created=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'openbsd_distinfo_created=0' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'Add a temporary source archive fixture lane' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_contains 'debian_freebsd_openbsd_source_archive_contract: ok' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md

require_contains 'Source: latticra' packaging/debian/debian/control
require_contains 'latticra (0.0.0-1local1) UNRELEASED' packaging/debian/debian/changelog
require_contains '3.0 (quilt)' packaging/debian/debian/source/format
require_contains 'PORTNAME=' packaging/freebsd/Makefile
require_contains 'DISTVERSION=	0.0.0' packaging/freebsd/Makefile
require_contains 'DISTNAME=	latticra-0.0.0' packaging/openbsd/Makefile
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' packaging/debian/README.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' packaging/freebsd/README.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' packaging/openbsd/README.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_freebsd_openbsd_source_archive_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md' README.md

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo

printf 'debian_freebsd_openbsd_source_archive_contract: ok\n'
