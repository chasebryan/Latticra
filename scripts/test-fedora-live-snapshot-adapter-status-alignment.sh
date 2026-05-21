#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora live snapshot adapter status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora live snapshot adapter status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_file docs/status/README.md
require_file docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_file include/latticra/fedora_live_snapshot_adapter.h
require_file src/fedora_live_snapshot_adapter.c
require_file tests/fedora_live_snapshot_adapter.c
require_file scripts/test-fedora-live-snapshot-adapter.sh
require_file scripts/test-fedora-live-snapshot-adapter-docs.sh

require_contains 'Status: merged live read-only Fedora adapter implementation' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains '#203 Add Fedora live read-only snapshot adapter' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'df2dba248eb1fcd6d37d9fa2f9dfae830b08a468' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'fedora_live_snapshot_adapter: ok' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'fedora_live_snapshot_adapter_docs: ok' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'live_probe_performed=1' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'snapshot_forwarded_to_classifier=1' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'sudo_validation_allowed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'install_command_allowed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'package_build_allowed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'network_allowed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'host_mutation_performed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'host_install_performed=0' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'evidence_level=3' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_contains 'Add Fedora local RPM install mutation gate contract' docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md

require_contains 'FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md' docs/status/README.md
require_contains 'status record for the live read-only Fedora snapshot adapter implementation' docs/status/README.md
require_contains 'FEDORA_RPM_GATE_CLASSIFIER_STATUS.md' docs/status/README.md
require_contains 'Current Fedora RPM gate classifier checkpoint' docs/status/README.md
require_contains 'install_mutation_performed=0' docs/status/README.md
require_contains 'host_mutation_performed=0' docs/status/README.md
require_contains 'evidence_level=4' docs/status/README.md
require_contains 'Add Fedora local RPM removal and rollback plan' docs/status/README.md

printf 'fedora_live_snapshot_adapter_status_alignment: ok\n'
