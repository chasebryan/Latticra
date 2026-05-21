#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local testing guide: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local testing guide: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_file docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_file docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: active local testing guide' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'bootc/read-only Fedora systems' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'this bootc system is configured to be read-only' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'podman run --rm -it' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'dnf -y install git tar gzip rpm-build gcc make' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'git switch -C fedora-installed-report origin/fedora-installed-report' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'git switch -C fedora-install-lane origin/fedora-install-lane' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'git switch -C fedora-archive origin/fedora-archive' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'sh scripts/test-fedora-source-archive-fixture-lane.sh' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'sh scripts/test-fedora-local-binary-rpm-build-lane.sh' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'sh scripts/test-fedora-rpm-payload-inspection-report.sh' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'sh scripts/test-fedora-local-install-smoke-lane.sh' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'sh scripts/test-fedora-installed-state-report-lane.sh' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'fedora_local_install_smoke_lane: ok' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'fedora_installed_state_report_lane: ok' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'Non-installing lanes' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'Installing lanes' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'rpm -q latticra' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'package latticra is not installed' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'Do not expect these to work yet' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'command -v latticra' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'latticra --version' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'latticra check' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'does not run `mock`' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'does not create RPM artifacts' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'does not install Latticra' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'Add Fedora host install decision gate' docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_contains 'fedora_local_testing_guide: ok' docs/FEDORA_LOCAL_TESTING_GUIDE.md

require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_local_testing_guide: ok\n'