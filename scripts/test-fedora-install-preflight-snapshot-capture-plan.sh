#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora install preflight snapshot capture plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora install preflight snapshot capture plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_file docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_file include/latticra/fedora_host_install_preflight.h
require_file scripts/test-fedora-host-install-preflight.sh

require_contains 'Status: planning record' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'read-only host facts' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'The capture lane must not run:' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Read-only command allowance' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'command-presence probes' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Privilege rule' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Immutable Fedora rule' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Local RPM rule' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Current package posture rule' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'sudo_validation_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'install_command_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'package_build_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'network_allowed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'host_mutation_performed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'host_install_performed=0' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'snapshot_forwarded_to_classifier=1' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'Add a small snapshot-capture contract/API' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'fedora_install_preflight_snapshot_capture_plan: ok' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'does not implement snapshot capture' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md
require_contains 'does not install Latticra' docs/FEDORA_INSTALL_PREFLIGHT_SNAPSHOT_CAPTURE_PLAN.md

printf 'fedora_install_preflight_snapshot_capture_plan: ok\n'
