#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora source archive fixture lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora source archive fixture lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_archive_entry() {
  entry="$1"
  if ! grep -Fqx -- "$entry" "$archive_listing"; then
    printf 'fedora source archive fixture lane: missing archive entry: %s\n' "$entry" >&2
    exit 1
  fi
}

require_no_archive_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$archive_listing"; then
    printf 'fedora source archive fixture lane: forbidden archive pattern matched: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active fixture lane' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Source0: %{name}-%{version}.tar.gz' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains '%autosetup -n %{name}-%{version}' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0.tar.gz' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0/' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'exclude .git' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create source RPM artifacts' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create binary RPM artifacts' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not install Latticra' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Add Fedora local binary RPM build lane' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'fedora_source_archive_fixture_lane: ok' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'fedora source archive fixture lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

tmpdir="$(mktemp -d)"
archive_path="$tmpdir/$archive"
archive_listing="$tmpdir/archive.list"

mkdir -p "$tmpdir/$root"

# Copy the current checked-out tree into the expected Source0 root while excluding
# VCS metadata and local RPM work outputs. This fixture remains temporary.
tar \
  --exclude='./.git' \
  --exclude='./.rpmwork' \
  --exclude='./*.rpm' \
  --exclude='./*.tar.gz' \
  -cf - . | tar -C "$tmpdir/$root" -xf -

tar -C "$tmpdir" -czf "$archive_path" "$root"
tar -tzf "$archive_path" >"$archive_listing"

require_archive_entry "$root/README.md"
require_archive_entry "$root/packaging/fedora/latticra.spec"
require_archive_entry "$root/scripts/test-state-lattice.sh"
require_archive_entry "$root/scripts/test-system-bootstrap.sh"
require_archive_entry "$root/scripts/test-kernel.sh"
require_archive_entry "$root/scripts/test-kernel-lifecycle.sh"

require_no_archive_pattern '(^|/)\.git(/|$)'
require_no_archive_pattern '(^|/)\.rpmwork(/|$)'
require_no_archive_pattern '\.rpm$'
require_no_archive_pattern 'latticra-[^/]*\.tar\.gz$'

rm -rf "$tmpdir"

printf 'fedora_source_archive_fixture_lane: ok\n'