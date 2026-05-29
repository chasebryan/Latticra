#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'freebsd port static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'freebsd port static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'freebsd port static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_file docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/freebsd/README.md
require_file packaging/freebsd/Makefile
require_file packaging/freebsd/pkg-descr
require_file packaging/freebsd/pkg-plist
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'local-only FreeBSD ports metadata draft' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'does not run `make package`, `make stage`, `poudriere`, `portlint`, or `pkg install`' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'freebsd_port_draft_present=1' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'poudriere_build_run=0' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'portlint_run=0' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'freebsd_official_port_claimed=0' docs/FREEBSD_PORT_STATIC_VALIDATION.md
require_contains 'freebsd_port_static_validation: ok' docs/FREEBSD_PORT_STATIC_VALIDATION.md

require_contains 'Status: local-only port draft' packaging/freebsd/README.md
require_contains 'not a FreeBSD ports tree submission' packaging/freebsd/README.md
require_contains 'not a poudriere build' packaging/freebsd/README.md
require_contains 'not a portlint result' packaging/freebsd/README.md
require_contains 'freebsd_port_draft_present=1' packaging/freebsd/README.md
require_contains 'package_artifact_created=0' packaging/freebsd/README.md

require_contains 'LOCAL-ONLY FreeBSD PORT DRAFT' packaging/freebsd/Makefile
require_contains 'PORTNAME=' packaging/freebsd/Makefile
require_contains 'DISTVERSION=' packaging/freebsd/Makefile
require_contains 'CATEGORIES=' packaging/freebsd/Makefile
require_contains 'MAINTAINER=' packaging/freebsd/Makefile
require_contains 'COMMENT=' packaging/freebsd/Makefile
require_contains 'WWW=' packaging/freebsd/Makefile
require_contains 'LICENSE=	AGPL-3.0-or-later CC-BY-4.0' packaging/freebsd/Makefile
require_contains 'USES=' packaging/freebsd/Makefile
require_contains 'compiler:c11' packaging/freebsd/Makefile
require_contains 'do-build:' packaging/freebsd/Makefile
require_contains 'do-install:' packaging/freebsd/Makefile
require_contains 'src/latticra_cli.c' packaging/freebsd/Makefile
require_contains '.include <bsd.port.mk>' packaging/freebsd/Makefile

require_contains 'local-only FreeBSD port draft' packaging/freebsd/pkg-descr
require_contains 'no-effect CLI status surface' packaging/freebsd/pkg-descr
require_contains 'bin/latticra' packaging/freebsd/pkg-plist
require_contains '%%DOCSDIR%%/README.md' packaging/freebsd/pkg-plist

require_contains 'freebsd_port_draft_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_port_static_validation_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_official_port_claimed=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'AGPL-3.0-or-later' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent 'USE_RC_SUBR' packaging/freebsd/Makefile
require_absent 'rc.d' packaging/freebsd/Makefile
require_absent 'kldload' packaging/freebsd/Makefile
require_absent 'kldxref' packaging/freebsd/Makefile
require_absent '/etc' packaging/freebsd/Makefile
require_absent '/boot' packaging/freebsd/Makefile
require_absent '/usr/local/etc' packaging/freebsd/pkg-plist
require_absent '/boot' packaging/freebsd/pkg-plist

printf 'freebsd_port_static_validation: ok\n'
