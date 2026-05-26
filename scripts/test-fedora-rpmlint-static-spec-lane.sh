#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpmlint static spec lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpmlint static spec lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/FEDORA_RPMLINT_AVAILABILITY.md
require_file scripts/test-fedora-rpmlint-availability.sh
require_file packaging/fedora/latticra.spec

require_contains 'Status: active static spec lint lane' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'rpmlint can inspect packaging/fedora/latticra.spec' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'rpmlint output is captured for audit' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not create package artifacts' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'does not submit Latticra to Fedora' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'Add rpmlint findings classification report' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_contains 'fedora_rpmlint_static_spec_lane: ok' docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md

require_contains 'LOCAL-ONLY DRAFT' packaging/fedora/latticra.spec
require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' packaging/fedora/latticra.spec
require_contains '0.1.local' packaging/fedora/latticra.spec

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora rpmlint static spec lane: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpmlint
command -v rpmlint >/dev/null 2>&1

rpmlint_output="$(mktemp)"
if rpmlint packaging/fedora/latticra.spec >"$rpmlint_output" 2>&1; then
  rpmlint_status=0
else
  rpmlint_status=$?
fi

cat "$rpmlint_output"

if [ "$rpmlint_status" -gt 64 ]; then
  printf 'fedora rpmlint static spec lane: rpmlint failed unexpectedly with status %s\n' "$rpmlint_status" >&2
  rm -f "$rpmlint_output"
  exit 1
fi

if [ ! -s "$rpmlint_output" ]; then
  printf 'fedora rpmlint static spec lane: expected rpmlint audit output\n' >&2
  rm -f "$rpmlint_output"
  exit 1
fi

rm -f "$rpmlint_output"

sh scripts/test-fedora-rpmlint-availability.sh

printf 'fedora_rpmlint_static_spec_lane: ok\n'