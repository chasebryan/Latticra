#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm install mutation gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm install mutation gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_file docs/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER.md
require_file docs/status/FEDORA_LIVE_READONLY_SNAPSHOT_ADAPTER_STATUS.md
require_file include/latticra/fedora_live_snapshot_adapter.h
require_file include/latticra/fedora_install_preflight_snapshot.h
require_file include/latticra/fedora_host_install_preflight.h

require_contains 'Status: contract record' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'Evidence level: 4 target, contract only' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'fedora_host=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'mutable_fedora_host=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'immutable_host=0' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'local_rpm_present=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'root_or_sudo_available=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'network_required=0' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'operator_install_confirmation=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'dry_run_passed=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'rollback_or_remove_plan_present=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'preflight_classification=ready-local-rpm' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'preflight_denial=none' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'live_probe_performed=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'FEDORA LOCAL RPM INSTALL MUTATION GATE' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'install_mutation_allowed=1' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'install_mutation_performed=0' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'host_mutation_performed=0' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'not-fedora-host' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'operator-confirmation-missing' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'dry-run-missing' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'rollback-plan-missing' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'separate contract' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'does not implement installation' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_contains 'fedora_local_rpm_install_mutation_gate_contract: ok' docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md

printf 'fedora_local_rpm_install_mutation_gate_contract: ok\n'
