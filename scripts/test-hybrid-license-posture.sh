#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'hybrid license posture: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'hybrid license posture: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'hybrid license posture: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_repo_match() {
  pattern="$1"
  if command -v rg >/dev/null 2>&1; then
    matches="$(rg -n -S --glob '!.git' --glob '!scripts/test-hybrid-license-posture.sh' --glob '!scripts/test-open-ecosystem-policy.sh' --glob '!LICENSES/AGPL-3.0-or-later.txt' --glob '!LICENSES/Apache-2.0.txt' --glob '!LICENSES/CC-BY-4.0.txt' "$pattern" . || :)"
  else
    matches="$(git grep -n -F "$pattern" -- . ':!scripts/test-hybrid-license-posture.sh' ':!scripts/test-open-ecosystem-policy.sh' ':!LICENSES/AGPL-3.0-or-later.txt' ':!LICENSES/Apache-2.0.txt' ':!LICENSES/CC-BY-4.0.txt' || :)"
  fi

  if [ -n "$matches" ]; then
    printf 'hybrid license posture: forbidden repository match for pattern: %s\n%s\n' "$pattern" "$matches" >&2
    exit 1
  fi
}

require_file LICENSE
require_file LICENSES/README.md
require_file LICENSES/AGPL-3.0-or-later.txt
require_file LICENSES/Apache-2.0.txt
require_file LICENSES/CC-BY-4.0.txt
require_file docs/LICENSE_POLICY.md
require_file docs/OPEN_ECOSYSTEM_POLICY.md
require_file docs/DOCUMENTATION_LICENSE.md
require_file TRADEMARK_POLICY.md
require_file CONTRIBUTING.md

require_contains 'hybrid open licensing model' LICENSE
require_contains 'Core/runtime/security substrate: AGPL-3.0-or-later' LICENSE
require_contains 'SDKs, examples, packaging helpers, installer glue, and integration helpers: Apache-2.0' LICENSE
require_contains 'Documentation, handbooks, architecture notes, and policy notes: CC-BY-4.0' LICENSE
require_contains 'Latticra/Bryforge names, logos, marks, and identity: TRADEMARK_POLICY.md' LICENSE

require_contains 'core/runtime/security substrate: AGPL-3.0-or-later' docs/LICENSE_POLICY.md
require_contains 'SDKs/examples/packaging helpers/integration helpers: Apache-2.0' docs/LICENSE_POLICY.md
require_contains 'documentation/handbooks/policy notes: CC-BY-4.0' docs/LICENSE_POLICY.md
require_contains 'SPDX-License-Identifier: AGPL-3.0-or-later' docs/LICENSE_POLICY.md
require_contains 'SPDX-License-Identifier: Apache-2.0' docs/LICENSE_POLICY.md
require_contains 'SPDX-License-Identifier: CC-BY-4.0' docs/LICENSE_POLICY.md

require_contains 'core software direction: AGPL-3.0-or-later' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'adoption-facing helper direction: Apache-2.0' docs/OPEN_ECOSYSTEM_POLICY.md
require_contains 'documentation direction: CC-BY-4.0' docs/OPEN_ECOSYSTEM_POLICY.md

require_contains 'Status: active documentation license decision' docs/DOCUMENTATION_LICENSE.md
require_contains 'CC-BY-4.0' docs/DOCUMENTATION_LICENSE.md
require_contains 'TRADEMARK_POLICY.md' docs/DOCUMENTATION_LICENSE.md

require_contains 'AGPL-3.0-or-later' LICENSES/README.md
require_contains 'Apache-2.0' LICENSES/README.md
require_contains 'CC-BY-4.0' LICENSES/README.md

require_contains 'GNU AFFERO GENERAL PUBLIC LICENSE' LICENSES/AGPL-3.0-or-later.txt
require_contains 'Apache License' LICENSES/Apache-2.0.txt
require_contains 'Attribution 4.0 International' LICENSES/CC-BY-4.0.txt

require_contains 'license = "Apache-2.0"' installer/latticra-installer/Cargo.toml
require_not_contains 'MIT OR Apache-2.0' installer/latticra-installer/Cargo.toml

require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' packaging/fedora/latticra.spec
require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' packaging/opensuse/latticra.spec
require_contains 'LICENSE=	AGPL-3.0-or-later CC-BY-4.0' packaging/freebsd/Makefile
require_contains 'Package payload license: AGPL-3.0-or-later AND CC-BY-4.0.' packaging/openbsd/Makefile
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_contains 'License: Apache-2.0' packaging/ubuntu/debian/copyright
require_contains 'License: AGPL-3.0-or-later' packaging/ubuntu/debian/copyright
require_contains 'License: CC-BY-4.0' packaging/ubuntu/debian/copyright
require_contains 'License: Apache-2.0' packaging/debian/debian/copyright
require_contains 'License: AGPL-3.0-or-later' packaging/debian/debian/copyright
require_contains 'License: CC-BY-4.0' packaging/debian/debian/copyright

require_no_repo_match 'LicenseRef-Latticra-TBD'
require_no_repo_match 'MIT OR Apache-2.0'
require_no_repo_match 'documentation_license_decision_present=0'
require_no_repo_match 'doc_payload_license_unresolved=1'
require_no_repo_match 'license_expression_unresolved=1'
require_no_repo_match 'packaging_license_expression_updated=0'

printf 'hybrid_license_posture: ok\n'
