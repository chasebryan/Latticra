#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora host install preflight docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora host install preflight docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_file include/latticra/fedora_host_install_preflight.h
require_file src/fedora_host_install_preflight.c
require_file tests/fedora_host_install_preflight.c
require_file scripts/test-fedora-host-install-preflight.sh

require_contains 'Status: implementation record' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'Evidence level: 1' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'no-effect' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'FEDORA HOST INSTALL PREFLIGHT' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'classification=ready-local-rpm' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'host_install_candidate=1' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'host_install_performed=0' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'host_mutation_performed=0' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'network_allowed=0' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'runtime-entrypoint-not-present' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'fedora_host_install_preflight: ok' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'fedora_host_install_preflight_docs: ok' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'does not install Latticra' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md
require_contains 'does not provide a production installer' docs/FEDORA_HOST_INSTALL_PREFLIGHT_CLASSIFIER.md

require_contains 'LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM' include/latticra/fedora_host_install_preflight.h
require_contains 'LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED' include/latticra/fedora_host_install_preflight.h
require_contains 'LATTICRA_FEDORA_PREFLIGHT_DENIAL_RUNTIME_ENTRYPOINT_NOT_PRESENT' include/latticra/fedora_host_install_preflight.h
require_contains 'latticra_fedora_host_install_preflight_classify' include/latticra/fedora_host_install_preflight.h
require_contains 'latticra_fedora_host_install_preflight_report' include/latticra/fedora_host_install_preflight.h

printf 'fedora_host_install_preflight_docs: ok\n'
