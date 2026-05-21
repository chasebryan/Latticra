#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm gate classifier status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm gate classifier status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER_STATUS.md'
index='docs/status/README.md'

require_file "$status"
require_file "$index"
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE.md
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER.md
require_file include/latticra/fedora_disposable_vm_effect_gate.h
require_file src/fedora_disposable_vm_effect_gate.c
require_file tests/fedora_disposable_vm_effect_gate.c
require_file scripts/test-fedora-disposable-vm-effect-gate-classifier.sh
require_file scripts/test-fedora-disposable-vm-effect-gate-classifier-docs.sh

require_contains 'Status: status alignment' "$status"
require_contains 'source=PR #221' "$status"
require_contains 'evidence_contract_present=1' "$status"
require_contains 'vm_effect_gate_present=1' "$status"
require_contains 'vm_gate_classifier_present=1' "$status"
require_contains 'vm_gate_classifier_guard_present=1' "$status"
require_contains 'vm_gate_classifier_docs_guard_present=1' "$status"
require_contains 'eligible_state_defined=1' "$status"
require_contains 'blocked_state_defined=1' "$status"
require_contains 'invalid_state_defined=1' "$status"
require_contains 'eligible_test_present=1' "$status"
require_contains 'blocked_target_tests_present=1' "$status"
require_contains 'blocked_package_tests_present=1' "$status"
require_contains 'blocked_prior_evidence_tests_present=1' "$status"
require_contains 'invalid_input_test_present=1' "$status"
require_contains 'classifier_evidence_level=8' "$status"
require_contains 'manual_host_dry_run_transcript_contract_present=1' "$status"
require_contains 'disposable_vm_effect_gate_present=1' "$status"
require_contains 'disposable_vm_effect_gate_classifier_present=1' "$status"
require_contains 'disposable_vm_effect_gate_status=blocked-pending-vm-validation-lane' "$status"
require_contains 'disposable_vm_effect_eligible=0' "$status"
require_contains 'live_host_validation_completed=0' "$status"
require_contains 'host_install_ready=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'Add disposable Fedora VM local RPM validation lane' "$status"
require_contains 'root README should not claim install readiness yet' "$status"

require_contains 'FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER_STATUS.md' "$index"
require_contains 'Current Fedora disposable VM effect gate classifier checkpoint' "$index"
require_contains 'source=PR #221' "$index"
require_contains 'vm_gate_classifier_present=1' "$index"
require_contains 'classifier_evidence_level=8' "$index"
require_contains 'disposable_vm_effect_gate_status=blocked-pending-vm-validation-lane' "$index"
require_contains 'host_install_ready=0' "$index"
require_contains 'Add disposable Fedora VM local RPM validation lane' "$index"
require_contains 'Current Fedora manual host RC decision classifier checkpoint' "$index"
require_contains 'Previous Fedora manual host RC checklist checkpoint' "$index"
require_contains 'Previous Fedora installroot RPM lifecycle checkpoint' "$index"

printf 'fedora_vm_gate_classifier_status_alignment: ok\n'
