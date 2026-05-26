#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpmlint static spec lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpmlint static spec lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_file scripts/test-opensuse-rpmlint-osc-availability.sh
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes

require_contains 'Status: active static spec lint lane' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'rpmlint can inspect packaging/opensuse/latticra.spec' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'rpmlint output is captured for audit' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not run `rpmbuild`' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not run `osc build`' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not run `spec-cleaner`' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not create package artifacts' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'Add openSUSE rpmlint findings classification record' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'opensuse_rpmlint_static_spec_lane: ok' docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md

require_contains 'LOCAL-ONLY openSUSE DRAFT' packaging/opensuse/latticra.spec
require_contains 'LicenseRef-Latticra-TBD' packaging/opensuse/latticra.spec
require_contains '0.local' packaging/opensuse/latticra.spec
require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes

if [ ! -r /etc/os-release ] || ! grep -Eq '^(ID=opensuse|ID_LIKE=.*suse|ID="opensuse|ID_LIKE=".*suse)' /etc/os-release; then
  printf 'opensuse rpmlint static spec lane: expected openSUSE environment\n' >&2
  exit 1
fi

if ! command -v zypper >/dev/null 2>&1; then
  printf 'opensuse rpmlint static spec lane: missing zypper\n' >&2
  exit 1
fi

sh scripts/test-opensuse-rpmlint-osc-availability.sh

if ! command -v rpmlint >/dev/null 2>&1; then
  printf 'opensuse rpmlint static spec lane: missing rpmlint\n' >&2
  exit 1
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
rpmlint_output="$tmpdir/rpmlint.out"
if rpmlint packaging/opensuse/latticra.spec >"$rpmlint_output" 2>&1; then
  rpmlint_status=0
else
  rpmlint_status=$?
fi

cat "$rpmlint_output"

if [ "$rpmlint_status" -gt 64 ]; then
  printf 'opensuse rpmlint static spec lane: rpmlint failed unexpectedly with status %s\n' "$rpmlint_status" >&2
  exit 1
fi

if [ ! -s "$rpmlint_output" ]; then
  printf 'opensuse rpmlint static spec lane: expected rpmlint audit output\n' >&2
  exit 1
fi

printf 'opensuse_rpmlint_static_spec_lane: ok\n'
