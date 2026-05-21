#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora live snapshot adapter docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora live snapshot adapter docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_file include/latticra/fedora_live_snapshot_adapter.h
require_file src/fedora_live_snapshot_adapter.c
require_file tests/fedora_live_snapshot_adapter.c
require_file scripts/test-fedora-live-snapshot-adapter.sh

require_contains 'Status: implementation record' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'Evidence level: 3' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'live read-only host fact capture' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'latticra_fedora_live_snapshot_adapter_capture' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'latticra_fedora_live_snapshot_adapter_report' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'FEDORA LIVE READ-ONLY SNAPSHOT ADAPTER' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'live_probe_performed=1' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'snapshot_forwarded_to_classifier=1' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'sudo_validation_allowed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'install_command_allowed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'package_build_allowed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'network_allowed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'host_mutation_performed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'host_install_performed=0' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'fedora_live_snapshot_adapter: ok' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'fedora_live_snapshot_adapter_docs: ok' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_contains 'does not install Latticra' docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md

require_contains 'LATTICRA_FEDORA_LIVE_ADAPTER_CAPTURED' include/latticra/fedora_live_snapshot_adapter.h
require_contains 'latticra_fedora_live_snapshot_adapter_capture' include/latticra/fedora_live_snapshot_adapter.h
require_contains 'latticra_fedora_live_snapshot_adapter_report' include/latticra/fedora_live_snapshot_adapter.h
require_contains 'latticra_fedora_snapshot_capture_input_t' include/latticra/fedora_live_snapshot_adapter.h

printf 'fedora_live_snapshot_adapter_docs: ok\n'
