#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian local deb static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian local deb static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'debian local deb static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_file docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/debian/README.md
require_file packaging/debian/debian/control
require_file packaging/debian/debian/rules
require_file packaging/debian/debian/changelog
require_file packaging/debian/debian/copyright
require_file packaging/debian/debian/install
require_file packaging/debian/debian/source/format
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'static checks for the local-only Debian deb packaging draft' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_archive_ready=0' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_mentors_upload_claimed=0' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_sponsorship_claimed=0' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_ftp_master_acceptance_claimed=0' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md
require_contains 'debian_local_deb_static_validation: ok' docs/DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md

require_contains 'Status: local-only packaging draft' packaging/debian/README.md
require_contains 'not a Debian archive package' packaging/debian/README.md
require_contains 'not a mentors.debian.net upload' packaging/debian/README.md
require_contains 'not sponsorship evidence' packaging/debian/README.md
require_contains 'deb_artifact_created=0' packaging/debian/README.md
require_contains 'debian_archive_ready=0' packaging/debian/README.md
require_contains 'debian_mentors_upload_claimed=0' packaging/debian/README.md
require_contains 'production_readiness_claimed=0' packaging/debian/README.md

require_contains 'Source: latticra' packaging/debian/debian/control
require_contains 'Build-Depends:' packaging/debian/debian/control
require_contains 'debhelper-compat (= 13)' packaging/debian/debian/control
require_contains 'gcc' packaging/debian/debian/control
require_contains 'make' packaging/debian/debian/control
require_contains 'Rules-Requires-Root: no' packaging/debian/debian/control
require_contains 'Package: latticra' packaging/debian/debian/control
require_contains 'Architecture: any' packaging/debian/debian/control
require_contains 'local Debian draft records package shape only' packaging/debian/debian/control

require_contains 'sh scripts/test-state-lattice.sh' packaging/debian/debian/rules
require_contains 'sh scripts/test-system-bootstrap.sh' packaging/debian/debian/rules
require_contains 'sh scripts/test-kernel.sh' packaging/debian/debian/rules
require_contains 'sh scripts/test-kernel-lifecycle.sh' packaging/debian/debian/rules
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' packaging/debian/debian/rules
require_contains 'cc $(CFLAGS) $(CPPFLAGS) -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra $(LDFLAGS)' packaging/debian/debian/rules

require_contains 'latticra (0.0.0-1local1) UNRELEASED' packaging/debian/debian/changelog
require_contains 'LOCAL-ONLY DEBIAN DRAFT' packaging/debian/debian/copyright
require_contains 'LicenseRef-Latticra-TBD' packaging/debian/debian/copyright
require_contains 'build/latticra usr/bin' packaging/debian/debian/install
require_contains 'README.md usr/share/doc/latticra' packaging/debian/debian/install
require_contains '3.0 (quilt)' packaging/debian/debian/source/format

require_contains 'debian_local_deb_draft_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_static_deb_validation_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_archive_ready=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'LicenseRef-Latticra-TBD' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent '.service' packaging/debian/debian/control
require_absent '.service' packaging/debian/debian/rules
require_absent '.service' packaging/debian/debian/install
require_absent 'systemctl' packaging/debian/debian/control
require_absent 'systemctl' packaging/debian/debian/rules
require_absent 'systemctl' packaging/debian/debian/install
require_absent '/etc/latticra' packaging/debian/debian/install
require_absent '/boot/latticra' packaging/debian/debian/install
require_absent '/usr/lib/modules' packaging/debian/debian/install

printf 'debian_local_deb_static_validation: ok\n'
