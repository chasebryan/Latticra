#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local binary rpm build plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local binary rpm build plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_file docs/FEDORA_INSTALL_VERIFICATION_PLAN.md
require_file docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: planning record' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'local binary RPM build lane' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'documentation-only draft' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'source archive name: latticra-<version>.tar.gz' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'source archive root directory: latticra-<version>/' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'archive excludes .git' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'rpmbuild -bb packaging/fedora/latticra.spec' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'rpm -qpi .rpmwork/RPMS/*/latticra-*.rpm' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'rpm -qpl .rpmwork/RPMS/*/latticra-*.rpm' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains '/usr/share/doc/latticra/README.md' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains '/usr/bin/latticra' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains '/usr/lib/systemd/system/latticra.service' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not run `mock`' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not create source archives' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not create binary RPM artifacts' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not install Latticra' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'does not publish package artifacts' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'Add Fedora source archive fixture lane' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_contains 'fedora_local_binary_rpm_build_plan: ok' docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md

require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains '%autosetup -n %{name}-%{version}' packaging/fedora/latticra.spec
require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_local_binary_rpm_build_plan: ok\n'