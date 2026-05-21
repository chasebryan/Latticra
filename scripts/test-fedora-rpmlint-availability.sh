#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpmlint availability: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpmlint availability: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_RPMLINT_AVAILABILITY.md
require_file docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_file scripts/test-fedora-local-rpm-static-validation.sh
require_file packaging/fedora/latticra.spec

require_contains 'Status: active tool availability lane' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'rpmlint installs' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'does not lint the Latticra spec yet' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'does not run rpmbuild or mock' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'does not create package artifacts' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'Add rpmlint static spec lane' docs/FEDORA_RPMLINT_AVAILABILITY.md
require_contains 'fedora_rpmlint_availability: ok' docs/FEDORA_RPMLINT_AVAILABILITY.md

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora rpmlint availability: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpmlint
command -v rpmlint >/dev/null 2>&1
rpmlint --version >/dev/null 2>&1

sh scripts/test-fedora-local-rpm-static-validation.sh

printf 'fedora_rpmlint_availability: ok\n'
