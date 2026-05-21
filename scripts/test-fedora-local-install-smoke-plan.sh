#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local install smoke plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local install smoke plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_file docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_file docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: planning record' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'fresh Fedora install smoke lane' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains '/usr/share/doc/latticra/README.md' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains '/usr/bin/latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains '/etc/latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains '/usr/lib/systemd/system/latticra.service' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'rpm -Uvh <generated-rpm>' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'rpm -q latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'rpm -ql latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'rpm -V latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'rpm -e latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains '! rpm -q latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'Do not add these yet' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'command -v latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'latticra --version' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'latticra check' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'does not run `mock`' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'does not create RPM artifacts' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'does not install Latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'does not remove Latticra from the host' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'Add Fedora local install smoke lane' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_contains 'fedora_local_install_smoke_plan: ok' docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md

require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_local_install_smoke_plan: ok\n'