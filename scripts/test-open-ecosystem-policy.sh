#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'open ecosystem policy: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'open ecosystem policy: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file LICENSE
require_file LICENSES/README.md
require_file docs/LICENSE_POLICY.md
require_file docs/OPEN_ECOSYSTEM_POLICY.md
require_file CONTRIBUTING.md
require_file TRADEMARK_POLICY.md

require_contains 'Apache License' LICENSE
require_contains 'Apache-2.0' docs/LICENSE_POLICY.md
require_contains 'AGPL-3.0-or-later' docs/LICENSE_POLICY.md
require_contains 'No silent relicensing' docs/LICENSE_POLICY.md
require_contains 'SPDX-License-Identifier: AGPL-3.0-or-later' docs/LICENSE_POLICY.md
require_contains 'TRADEMARK_POLICY.md' docs/LICENSE_POLICY.md

require_contains 'open, auditable, transparent' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'AGPL-3.0-or-later' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'Existing files remain under their current license' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'SPDX-License-Identifier: AGPL-3.0-or-later' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'qualified legal review' docs/OPEN_ECOSYSTEM_POLICY.md

require_contains 'Contributing to Latticra' CONTRIBUTING.md
require_contains 'No proprietary relicensing CLA' CONTRIBUTING.md
require_contains 'Developer Certificate of Origin' CONTRIBUTING.md
require_contains 'TRADEMARK_POLICY.md' CONTRIBUTING.md

require_contains 'Trademark and Identity Policy' TRADEMARK_POLICY.md
require_contains 'Software and documentation licenses do not grant trademark' TRADEMARK_POLICY.md
require_contains 'official Latticra project' TRADEMARK_POLICY.md
require_contains 'Security and trust' TRADEMARK_POLICY.md

require_contains 'License References' LICENSES/README.md
require_contains 'Apache-2.0' LICENSES/README.md
require_contains 'AGPL-3.0-or-later' LICENSES/README.md
require_contains 'SPDX-License-Identifier: AGPL-3.0-or-later' LICENSES/README.md

printf 'open_ecosystem_policy: ok\n'
