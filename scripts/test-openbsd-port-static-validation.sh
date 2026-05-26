#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'openbsd port static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'openbsd port static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'openbsd port static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_file docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/openbsd/README.md
require_file packaging/openbsd/Makefile
require_file packaging/openbsd/pkg/DESCR
require_file packaging/openbsd/pkg/PLIST
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'local-only OpenBSD ports metadata draft' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'does not run `make package`, `make plist`, `portcheck`, a bulk build, or `pkg_add`' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'openbsd_port_draft_present=1' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'bulk_build_run=0' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'portcheck_run=0' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'permit_package_enabled=0' docs/OPENBSD_PORT_STATIC_VALIDATION.md
require_contains 'openbsd_port_static_validation: ok' docs/OPENBSD_PORT_STATIC_VALIDATION.md

require_contains 'Status: local-only port draft' packaging/openbsd/README.md
require_contains 'not an OpenBSD ports tree submission' packaging/openbsd/README.md
require_contains 'not a ports@ review thread' packaging/openbsd/README.md
require_contains 'not a bulk build result' packaging/openbsd/README.md
require_contains 'openbsd_port_draft_present=1' packaging/openbsd/README.md
require_contains 'permit_package_enabled=0' packaging/openbsd/README.md

require_contains 'LOCAL-ONLY OpenBSD PORT DRAFT' packaging/openbsd/Makefile
require_contains 'COMMENT=' packaging/openbsd/Makefile
require_contains 'DISTNAME=' packaging/openbsd/Makefile
require_contains 'CATEGORIES=' packaging/openbsd/Makefile
require_contains 'HOMEPAGE=' packaging/openbsd/Makefile
require_contains 'MAINTAINER=' packaging/openbsd/Makefile
require_contains 'LicenseRef-Latticra-TBD' packaging/openbsd/Makefile
require_contains 'PERMIT_PACKAGE=' packaging/openbsd/Makefile
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile
require_contains 'WANTLIB += c' packaging/openbsd/Makefile
require_contains 'do-build:' packaging/openbsd/Makefile
require_contains 'do-install:' packaging/openbsd/Makefile
require_contains 'src/latticra_cli.c' packaging/openbsd/Makefile
require_contains '.include <bsd.port.mk>' packaging/openbsd/Makefile

require_contains 'local-only OpenBSD port draft' packaging/openbsd/pkg/DESCR
require_contains 'no-effect CLI status surface' packaging/openbsd/pkg/DESCR
require_contains 'bin/latticra' packaging/openbsd/pkg/PLIST
require_contains 'share/doc/latticra/README.md' packaging/openbsd/pkg/PLIST

require_contains 'openbsd_port_draft_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_port_static_validation_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'permit_package_enabled=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'LicenseRef-Latticra-TBD' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent 'rc.d' packaging/openbsd/Makefile
require_absent '@rcscript' packaging/openbsd/pkg/PLIST
require_absent 'kmod' packaging/openbsd/Makefile
require_absent '/etc' packaging/openbsd/Makefile
require_absent '/bsd' packaging/openbsd/Makefile
require_absent '/etc' packaging/openbsd/pkg/PLIST
require_absent '/bsd' packaging/openbsd/pkg/PLIST

printf 'openbsd_port_static_validation: ok\n'
