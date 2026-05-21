#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora host install decision gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora host install decision gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_file docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_file docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: active host-install decision gate' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Host-level installation is not the default path' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'system is bootc-managed or otherwise read-only' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'system is production or daily-driver critical' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'working tree is dirty' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'local Fedora container lanes have not passed' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'local install smoke lane has not passed in disposable Fedora' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'installed-state report lane has not passed in disposable Fedora' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'user does not explicitly accept temporary RPM database modification' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'source archive fixture lane passed' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'local binary RPM build lane passed' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'RPM payload inspection report lane passed' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'host is mutable Fedora, not bootc/read-only Fedora' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'This test will temporarily modify the host RPM database' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'It should install only /usr/share/doc/latticra/README.md' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Run Fedora packaging install tests in containers or disposable CI' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Do not install directly on bootc/read-only Fedora hosts' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Do not install directly on daily-driver hosts' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Do not expect these yet' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'command -v latticra' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'latticra --version' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'latticra check' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'does not run `mock`' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'does not create RPM artifacts' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'does not install Latticra' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'does not modify the host RPM database' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'Add Fedora host install preflight plan' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_contains 'fedora_host_install_decision_gate: ok' docs/FEDORA_HOST_INSTALL_DECISION_GATE.md

require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_host_install_decision_gate: ok\n'