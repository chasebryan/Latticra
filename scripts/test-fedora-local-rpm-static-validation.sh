#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_file docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_file packaging/fedora/latticra.spec
require_file scripts/test-fedora-local-rpm-spec-skeleton.sh
require_file scripts/test-fedora-local-rpm-validation-plan.sh

sh scripts/test-fedora-local-rpm-spec-skeleton.sh
sh scripts/test-fedora-local-rpm-validation-plan.sh

require_contains 'Status: active static validation lane' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'static checks for the local RPM spec skeleton' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'does not run `rpmbuild`, `rpmlint`, or `mock`' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'does not create package artifacts' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'Add rpmlint availability lane' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'fedora_local_rpm_static_validation: ok' docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md

require_contains 'LOCAL-ONLY DRAFT' packaging/fedora/latticra.spec
require_contains 'License:        LicenseRef-Latticra-TBD' packaging/fedora/latticra.spec
require_contains 'Release:        0.1.local%{?dist}' packaging/fedora/latticra.spec
require_contains '%description' packaging/fedora/latticra.spec
require_contains '%prep' packaging/fedora/latticra.spec
require_contains '%build' packaging/fedora/latticra.spec
require_contains '%install' packaging/fedora/latticra.spec
require_contains '%files' packaging/fedora/latticra.spec
require_contains '%changelog' packaging/fedora/latticra.spec

require_absent '%pre' packaging/fedora/latticra.spec
require_absent '%post' packaging/fedora/latticra.spec
require_absent '%preun' packaging/fedora/latticra.spec
require_absent '%postun' packaging/fedora/latticra.spec
require_absent '.service' packaging/fedora/latticra.spec
require_absent '%{_bindir}' packaging/fedora/latticra.spec
require_absent '%{_sbindir}' packaging/fedora/latticra.spec
require_absent 'systemctl' packaging/fedora/latticra.spec

printf 'fedora_local_rpm_static_validation: ok\n'
