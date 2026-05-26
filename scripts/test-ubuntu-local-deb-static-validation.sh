#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu local deb static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu local deb static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_file docs/UBUNTU_READINESS_PLAN.md
require_file docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
require_file packaging/ubuntu/README.md
require_file packaging/ubuntu/debian/control
require_file packaging/ubuntu/debian/rules
require_file packaging/ubuntu/debian/changelog
require_file packaging/ubuntu/debian/copyright
require_file packaging/ubuntu/debian/install
require_file packaging/ubuntu/debian/source/format
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'static checks for the local-only Ubuntu deb packaging draft' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_inventory_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'package_notice_inventory_report_present=1' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'deb_artifact_created=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_archive_ready=0' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'ubuntu_local_deb_static_validation: ok' docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md

require_contains 'Status: local-only packaging draft' packaging/ubuntu/README.md
require_contains 'not an Ubuntu archive package' packaging/ubuntu/README.md
require_contains 'not a PPA package' packaging/ubuntu/README.md
require_contains 'deb_artifact_created=0' packaging/ubuntu/README.md
require_contains 'package_notice_inventory_present=1' packaging/ubuntu/README.md
require_contains 'package_notice_inventory_report_present=1' packaging/ubuntu/README.md
require_contains 'ppa_claimed=0' packaging/ubuntu/README.md
require_contains 'ubuntu_archive_ready=0' packaging/ubuntu/README.md

require_contains 'Source: latticra' packaging/ubuntu/debian/control
require_contains 'Build-Depends:' packaging/ubuntu/debian/control
require_contains 'debhelper-compat (= 13)' packaging/ubuntu/debian/control
require_contains 'gcc' packaging/ubuntu/debian/control
require_contains 'make' packaging/ubuntu/debian/control
require_contains 'Rules-Requires-Root: no' packaging/ubuntu/debian/control
require_contains 'Package: latticra' packaging/ubuntu/debian/control
require_contains 'Architecture: any' packaging/ubuntu/debian/control
require_contains 'local Ubuntu draft records package shape only' packaging/ubuntu/debian/control

require_contains 'sh scripts/test-state-lattice.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-system-bootstrap.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-kernel.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-kernel-lifecycle.sh' packaging/ubuntu/debian/rules
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' packaging/ubuntu/debian/rules
require_contains 'cc $(CFLAGS) $(CPPFLAGS) -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra $(LDFLAGS)' packaging/ubuntu/debian/rules

require_contains 'latticra (0.0.0-0ubuntu0.1local1) UNRELEASED' packaging/ubuntu/debian/changelog
require_contains 'LOCAL-ONLY DRAFT' packaging/ubuntu/debian/copyright
require_contains 'LicenseRef-Latticra-TBD' packaging/ubuntu/debian/copyright
require_contains 'build/latticra usr/bin' packaging/ubuntu/debian/install
require_contains 'README.md usr/share/doc/latticra' packaging/ubuntu/debian/install
require_contains '3.0 (quilt)' packaging/ubuntu/debian/source/format

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent '.service' packaging/ubuntu/debian/control
require_absent '.service' packaging/ubuntu/debian/rules
require_absent '.service' packaging/ubuntu/debian/install
require_absent 'systemctl' packaging/ubuntu/debian/control
require_absent 'systemctl' packaging/ubuntu/debian/rules
require_absent 'systemctl' packaging/ubuntu/debian/install
require_absent '/etc/latticra' packaging/ubuntu/debian/install
require_absent '/boot/latticra' packaging/ubuntu/debian/install
require_absent '/usr/lib/modules' packaging/ubuntu/debian/install
require_absent '/usr/share/selinux' packaging/ubuntu/debian/install

printf 'ubuntu_local_deb_static_validation: ok\n'
