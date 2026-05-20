#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm spec skeleton: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm spec skeleton: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file packaging/fedora/latticra.spec
require_file docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_file docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_file scripts/test-fedora-local-rpm-spec-draft-plan.sh

require_contains 'LOCAL-ONLY DRAFT' packaging/fedora/latticra.spec
require_contains 'Name:           latticra' packaging/fedora/latticra.spec
require_contains 'Version:        0.0.0' packaging/fedora/latticra.spec
require_contains 'Release:        0.1.local%{?dist}' packaging/fedora/latticra.spec
require_contains 'Summary:        Contract-first systems architecture and language project' packaging/fedora/latticra.spec
require_contains 'License:        LicenseRef-Latticra-TBD' packaging/fedora/latticra.spec
require_contains 'URL:            https://github.com/Bryforge/Latticra' packaging/fedora/latticra.spec
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains 'BuildRequires:  gcc' packaging/fedora/latticra.spec
require_contains 'BuildRequires:  make' packaging/fedora/latticra.spec
require_contains '%description' packaging/fedora/latticra.spec
require_contains '%prep' packaging/fedora/latticra.spec
require_contains '%build' packaging/fedora/latticra.spec
require_contains '%install' packaging/fedora/latticra.spec
require_contains '%files' packaging/fedora/latticra.spec
require_contains '%changelog' packaging/fedora/latticra.spec
require_contains 'sh scripts/test-state-lattice.sh' packaging/fedora/latticra.spec
require_contains 'sh scripts/test-system-bootstrap.sh' packaging/fedora/latticra.spec
require_contains 'sh scripts/test-kernel.sh' packaging/fedora/latticra.spec
require_contains 'sh scripts/test-kernel-lifecycle.sh' packaging/fedora/latticra.spec

printf 'fedora_local_rpm_spec_skeleton: ok\n'
