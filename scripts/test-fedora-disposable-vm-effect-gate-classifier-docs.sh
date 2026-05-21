#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm effect gate classifier docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm effect gate classifier docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER.md'
header='include/latticra/fedora_disposable_vm_effect_gate.h'
source='src/fedora_disposable_vm_effect_gate.c'
test='tests/fedora_disposable_vm_effect_gate.c'
script='scripts/test-fedora-disposable-vm-effect-gate-classifier.sh'

require_file "$doc"
require_file "$header"
require_file "$source"
require_file "$test"
require_file "$script"
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE.md

require_contains 'Status: implementation record' "$doc"
require_contains 'Evidence level: 8' "$doc"
require_contains 'pure classifier' "$doc"
require_contains 'disposable_vm_effect_gate_status=eligible' "$doc"
require_contains 'disposable_vm_effect_gate_status=blocked' "$doc"
require_contains 'disposable_vm_effect_gate_status=invalid' "$doc"
require_contains 'latticra_fedora_disposable_vm_effect_gate_classify' "$doc"
require_contains 'latticra_fedora_disposable_vm_effect_gate_report' "$doc"
require_contains 'target_is_disposable_fedora_vm=1' "$doc"
require_contains 'target_is_daily_driver=0' "$doc"
require_contains 'target_is_production_host=0' "$doc"
require_contains 'target_is_immutable_fedora=0' "$doc"
require_contains 'target_has_clean_snapshot=1' "$doc"
require_contains 'target_has_recovery_path=1' "$doc"
require_contains 'operator_consent_recorded=1' "$doc"
require_contains 'local_rpm_built_from_current_tree=1' "$doc"
require_contains 'rpm_name_is_latticra=1' "$doc"
require_contains 'rpm_version_recorded=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_is_documentation_only=1' "$doc"
require_contains 'unexpected_runtime_surface_absent=1' "$doc"
require_contains 'installroot_lifecycle_evidence_present=1' "$doc"
require_contains 'post_removal_absence_evidence_present=1' "$doc"
require_contains 'manual_host_dry_run_transcript_contract_present=1' "$doc"
require_contains 'manual_host_rc_decision_classifier_present=1' "$doc"
require_contains 'rpm_gate_allowed=1' "$doc"
require_contains 'removal_rollback_ready=1' "$doc"
require_contains 'disposable_vm_effect_eligible=1' "$doc"
require_contains 'disposable_vm_effect_eligible=0' "$doc"
require_contains 'host_install_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'not-disposable-fedora-vm' "$doc"
require_contains 'daily-driver-target' "$doc"
require_contains 'production-target' "$doc"
require_contains 'immutable-fedora-target' "$doc"
require_contains 'snapshot-missing' "$doc"
require_contains 'rpm-payload-listing-missing' "$doc"
require_contains 'transcript-contract-missing' "$doc"
require_contains 'invalid-classifier-input' "$doc"
require_contains 'FEDORA DISPOSABLE VM EFFECT GATE CLASSIFIER' "$doc"
require_contains 'fedora_disposable_vm_effect_gate_classifier: ok' "$doc"
require_contains 'fedora_disposable_vm_effect_gate_classifier_docs: ok' "$doc"
require_contains 'Align Fedora disposable VM effect gate classifier status' "$doc"
require_contains 'not production readiness' "$doc"

require_contains 'LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_ELIGIBLE' "$header"
require_contains 'LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_BLOCKED' "$header"
require_contains 'LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_INVALID' "$header"
require_contains 'LATTICRA_FEDORA_DISPOSABLE_VM_EFFECT_GATE_DENIAL_INVALID_INPUT' "$header"
require_contains 'latticra_fedora_disposable_vm_effect_gate_classify' "$header"
require_contains 'latticra_fedora_disposable_vm_effect_gate_report' "$header"

printf 'fedora_disposable_vm_effect_gate_classifier_docs: ok\n'
