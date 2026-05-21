#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora install preflight snapshot capture status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora install preflight snapshot capture status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_file docs/status/README.md
require_file docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_IMPLEMENTATION.md
require_file include/latticra/fedora_install_preflight_snapshot.h
require_file src/fedora_install_preflight_snapshot.c
require_file tests/fedora_install_preflight_snapshot.c
require_file scripts/test-fedora-install-preflight-snapshot-capture.sh
require_file scripts/test-fedora-install-preflight-snapshot-capture-docs.sh

require_contains 'Status: merged no-effect Fedora snapshot capture implementation' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains '#201 Implement Fedora install preflight snapshot capture' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'e8a898ee1cab776c90b4c9d4741f5dc4f67e25e5' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'snapshot_capture_status=captured' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'classifier_classification=ready-local-rpm' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'snapshot_forwarded_to_classifier=1' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'sudo_validation_allowed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'install_command_allowed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'package_build_allowed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'network_allowed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'host_mutation_performed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'host_install_performed=0' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'evidence_level=2' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md
require_contains 'Add Fedora live read-only snapshot capture adapter' docs/status/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md

require_contains 'FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_STATUS.md' docs/status/README.md
require_contains 'status record for the no-effect Fedora install preflight snapshot capture implementation' docs/status/README.md
require_contains 'FEDORA_RPM_GATE_CLASSIFIER_STATUS.md' docs/status/README.md
require_contains 'Current Fedora RPM gate classifier checkpoint' docs/status/README.md
require_contains 'install_mutation_performed=0' docs/status/README.md
require_contains 'host_mutation_performed=0' docs/status/README.md
require_contains 'evidence_level=4' docs/status/README.md
require_contains 'Add Fedora local RPM removal and rollback plan' docs/status/README.md

printf 'fedora_install_preflight_snapshot_capture_status_alignment: ok\n'
