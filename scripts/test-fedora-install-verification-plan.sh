#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora install verification plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora install verification plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_file docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_file docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: planning record' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'local RPM path' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'documentation-only package draft' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'rpm -q latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'rpm -ql latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'rpm -V latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'test -r /usr/share/doc/latticra/README.md' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'test ! -e /usr/bin/latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'test ! -d /etc/latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'test ! -e /usr/lib/systemd/system/latticra.service' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'command -v latticra' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'latticra --version' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'latticra check' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'does not run `mock`' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'does not create RPM artifacts' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'does not install Latticra on the host' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'does not submit Latticra to Fedora' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'Add Fedora local binary RPM build plan' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_contains 'fedora_install_verification_plan: ok' docs/FEDORA_INSTALL_VERIFICATION_PLAN.md

require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_install_verification_plan: ok\n'