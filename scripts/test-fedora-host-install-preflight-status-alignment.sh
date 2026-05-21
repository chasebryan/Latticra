#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora host install preflight status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora host install preflight status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_file docs/status/README.md
require_file docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_file include/latticra/fedora_host_install_preflight.h
require_file src/fedora_host_install_preflight.c
require_file tests/fedora_host_install_preflight.c
require_file scripts/test-fedora-host-install-preflight.sh
require_file scripts/test-fedora-host-install-preflight-docs.sh

require_contains 'Status: merged no-effect Fedora preflight classifier' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains '#198 Add Fedora host install preflight classifier' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'bbcb42afce009a29b7ba5c0ea8b354a9bca93966' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'classification=ready-local-rpm' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'host_install_candidate=1' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'host_install_performed=0' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'host_mutation_performed=0' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'network_allowed=0' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'no_effect=1' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'Add Fedora install preflight snapshot capture plan' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md
require_contains 'No host install' docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md

require_contains 'FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md' docs/status/README.md
require_contains 'status record for the no-effect Fedora host install preflight classifier' docs/status/README.md
require_contains 'FEDORA_RPM_GATE_CLASSIFIER_STATUS.md' docs/status/README.md
require_contains 'Current Fedora RPM gate classifier checkpoint' docs/status/README.md
require_contains 'install_mutation_performed=0' docs/status/README.md
require_contains 'host_mutation_performed=0' docs/status/README.md
require_contains 'evidence_level=4' docs/status/README.md
require_contains 'Add Fedora local RPM removal and rollback plan' docs/status/README.md

printf 'fedora_host_install_preflight_status_alignment: ok\n'
