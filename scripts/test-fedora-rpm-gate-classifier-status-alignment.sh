#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpm gate classifier status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpm gate classifier status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_file docs/status/README.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file include/latticra/fedora_rpm_gate.h
require_file src/fedora_rpm_gate.c
require_file tests/fedora_rpm_gate.c
require_file scripts/test-fedora-rpm-gate-classifier.sh
require_file scripts/test-fedora-rpm-gate-classifier-docs.sh

require_contains 'Status: merged Fedora RPM gate classifier implementation' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains '#207 Add Fedora RPM gate classifier' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'e3e6cf85cf59c2634c0a67c7d4318afc2c86388a' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'fedora_rpm_gate_classifier: ok' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'fedora_rpm_gate_classifier_docs: ok' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'install_gate_status=allowed' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'install_gate_denial=none' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'install_mutation_allowed=1' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'install_mutation_performed=0' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'host_mutation_performed=0' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'network_allowed=0' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'evidence_level=4' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_contains 'Add Fedora local RPM removal and rollback plan' docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md

require_contains 'FEDORA_RPM_GATE_CLASSIFIER_STATUS.md' docs/status/README.md
require_contains 'Current Fedora RPM gate classifier checkpoint' docs/status/README.md
require_contains 'install_gate_status=allowed' docs/status/README.md
require_contains 'install_mutation_allowed=1' docs/status/README.md
require_contains 'install_mutation_performed=0' docs/status/README.md
require_contains 'host_mutation_performed=0' docs/status/README.md
require_contains 'network_allowed=0' docs/status/README.md
require_contains 'evidence_level=4' docs/status/README.md
require_contains 'Add Fedora local RPM removal and rollback plan' docs/status/README.md

printf 'fedora_rpm_gate_classifier_status_alignment: ok\n'
