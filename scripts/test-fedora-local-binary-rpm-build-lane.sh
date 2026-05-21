#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

rpmwork=""
archive_staging=""

cleanup() {
  if [ -n "$rpmwork" ]; then
    rm -rf "$rpmwork"
  fi
  if [ -n "$archive_staging" ]; then
    rm -rf "$archive_staging"
  fi
}
trap cleanup EXIT INT TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local binary rpm build lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local binary rpm build lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_payload() {
  pattern="$1"
  if ! grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora local binary rpm build lane: missing payload pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_no_payload() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora local binary rpm build lane: forbidden payload pattern matched: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_file docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_file scripts/test-fedora-source-archive-fixture-lane.sh
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active local build lane' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'documentation-only package posture' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'rpm-build' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'rpmbuild -bb packaging/fedora/latticra.spec' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'debug_package %{nil}' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'rpm -qpi <generated-rpm>' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'rpm -qpl <generated-rpm>' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'does not install Latticra' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'does not publish package artifacts' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'Add Fedora RPM payload inspection report' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_contains 'fedora_local_binary_rpm_build_lane: ok' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora local binary rpm build lane: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpm-build gcc make tar gzip
command -v rpmbuild >/dev/null 2>&1
command -v rpm >/dev/null 2>&1
command -v tar >/dev/null 2>&1

# Reuse the source archive fixture guard first so the archive contract stays chained.
sh scripts/test-fedora-source-archive-fixture-lane.sh

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'fedora local binary rpm build lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

rpmwork="$(mktemp -d)"
archive_staging="$(mktemp -d)"
metadata_output="$rpmwork/rpm-info.txt"
payload_listing="$rpmwork/rpm-payload.txt"

mkdir -p \
  "$rpmwork/BUILD" \
  "$rpmwork/BUILDROOT" \
  "$rpmwork/RPMS" \
  "$rpmwork/SOURCES" \
  "$rpmwork/SPECS" \
  "$rpmwork/SRPMS" \
  "$archive_staging/$root"

tar \
  --exclude='./.git' \
  --exclude='./.rpmwork' \
  --exclude='./*.rpm' \
  --exclude='./*.tar.gz' \
  -cf - . | tar -C "$archive_staging/$root" -xf -

tar -C "$archive_staging" -czf "$rpmwork/SOURCES/$archive" "$root"

rpmbuild -bb packaging/fedora/latticra.spec \
  --define "_topdir $rpmwork" \
  --define "_sourcedir $rpmwork/SOURCES" \
  --define "_rpmdir $rpmwork/RPMS" \
  --define "_builddir $rpmwork/BUILD" \
  --define "_buildrootdir $rpmwork/BUILDROOT" \
  --define "debug_package %{nil}"

rpm_count="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | wc -l | tr -d ' ')"
if [ "$rpm_count" != '1' ]; then
  printf 'fedora local binary rpm build lane: expected exactly one local RPM, found %s\n' "$rpm_count" >&2
  exit 1
fi

rpm_path="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | head -n 1)"

rpm -qpi "$rpm_path" >"$metadata_output"
rpm -qpl "$rpm_path" >"$payload_listing"

require_contains 'Name        : latticra' "$metadata_output"
require_contains 'Version     : 0.0.0' "$metadata_output"
require_payload '/usr/share/doc/latticra/README.md$'

require_no_payload '(^|/usr/)bin/latticra$'
require_no_payload '^/etc/latticra(/|$)'
require_no_payload '^/usr/lib/systemd/system/latticra\.service$'
require_no_payload '(^|/)lib/modules(/|$)'
require_no_payload '(^|/)boot(/|$)'
require_no_payload '(^|/)selinux(/|$)'

printf 'fedora_local_binary_rpm_build_lane: ok\n'