#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpm gate classifier docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpm gate classifier docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/FEDORA_LOCAL_RPM_INSTALL_MUTATION_GATE_CONTRACT.md
require_file include/latticra/fedora_rpm_gate.h
require_file src/fedora_rpm_gate.c
require_file tests/fedora_rpm_gate.c
require_file scripts/test-fedora-rpm-gate-classifier.sh

require_contains 'Status: implementation record' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'Evidence level: 4' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'pure Fedora local RPM gate classification' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'latticra_fedora_rpm_gate_classify' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'latticra_fedora_rpm_gate_report' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'fedora_host=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'mutable_fedora_host=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'immutable_host=0' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'operator_install_confirmation=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'dry_run_passed=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'rollback_or_remove_plan_present=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'snapshot_captured=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'live_probe_performed=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'FEDORA LOCAL RPM INSTALL MUTATION GATE' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'install_gate_status=allowed' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'install_mutation_allowed=1' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'install_mutation_performed=0' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'host_mutation_performed=0' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'network_allowed=0' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'fedora_rpm_gate_classifier: ok' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'fedora_rpm_gate_classifier_docs: ok' docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_contains 'classifier only' docs/FEDORA_RPM_GATE_CLASSIFIER.md

require_contains 'LATTICRA_FEDORA_RPM_GATE_ALLOWED' include/latticra/fedora_rpm_gate.h
require_contains 'LATTICRA_FEDORA_RPM_GATE_DENIAL_DRY_RUN_MISSING' include/latticra/fedora_rpm_gate.h
require_contains 'latticra_fedora_rpm_gate_classify' include/latticra/fedora_rpm_gate.h
require_contains 'latticra_fedora_rpm_gate_report' include/latticra/fedora_rpm_gate.h

printf 'fedora_rpm_gate_classifier_docs: ok\n'
