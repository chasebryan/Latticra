#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora install preflight snapshot capture docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora install preflight snapshot capture docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_file docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_file include/latticra/fedora_install_preflight_snapshot.h
require_file src/fedora_install_preflight_snapshot.c
require_file tests/fedora_install_preflight_snapshot.c
require_file scripts/test-fedora-install-preflight-snapshot-capture.sh

require_contains 'Status: implementation record' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'Evidence level: 2' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'pure no-effect snapshot capture' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'latticra_fedora_install_preflight_snapshot_capture' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'latticra_fedora_install_preflight_snapshot_report' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'FEDORA INSTALL PREFLIGHT SNAPSHOT CAPTURE' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'snapshot_forwarded_to_classifier=1' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'sudo_validation_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'install_command_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'package_build_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'network_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'host_mutation_performed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'host_install_performed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'fedora_install_preflight_snapshot_capture: ok' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'fedora_install_preflight_snapshot_capture_docs: ok' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'does not install Latticra' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_contains 'does not install Latticra' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md

require_contains 'LATTICRA_FEDORA_SNAPSHOT_CAPTURED' include/latticra/fedora_install_preflight_snapshot.h
require_contains 'latticra_fedora_install_preflight_snapshot_capture' include/latticra/fedora_install_preflight_snapshot.h
require_contains 'latticra_fedora_install_preflight_snapshot_report' include/latticra/fedora_install_preflight_snapshot.h
require_contains 'latticra_fedora_host_install_preflight_snapshot_t' include/latticra/fedora_install_preflight_snapshot.h

printf 'fedora_install_preflight_snapshot_capture_docs: ok\n'
