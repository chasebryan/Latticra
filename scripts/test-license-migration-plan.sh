#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'license migration plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'license migration plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LICENSE_MIGRATION_PLAN.md
require_file docs/OPEN_ECOSYSTEM_POLICY.md
require_file docs/LICENSE_POLICY.md
require_file docs/DOCUMENTATION_LICENSE.md
require_file CONTRIBUTING.md
require_file TRADEMARK_POLICY.md
require_file LICENSES/README.md

require_contains 'Status: active migration planning record' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'No file should be relicensed silently.' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'Phase 1: governance baseline' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'Phase 2: SPDX planning guard' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'Phase 3: first source SPDX migration candidates' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'include/latticra/kernel*.h' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'src/kernel*.c' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'tests/kernel*.c' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'tools/kernel*.c' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'SPDX-License-Identifier' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'Documentation license is decided' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'CC-BY-4.0' docs/LICENSE_MIGRATION_PLAN.md
require_contains 'qualified legal review' docs/LICENSE_MIGRATION_PLAN.md

require_contains 'AGPL-3.0-or-later' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'CC-BY-4.0' docs/DOCUMENTATION_LICENSE.md
require_contains 'No silent relicensing' docs/LICENSE_POLICY.md
require_contains 'No proprietary relicensing CLA' CONTRIBUTING.md
require_contains 'Software and documentation licenses, including AGPL-3.0-or-later, Apache-2.0, and CC-BY-4.0, do not grant trademark' TRADEMARK_POLICY.md
require_contains 'AGPL-3.0-or-later' LICENSES/README.md

printf 'license_migration_plan: ok\n'
