#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm effect gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm effect gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE.md'

require_file "$doc"
require_file docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_file docs/FEDORA_MANUAL_HOST_DRY_RUN_TRANSCRIPT_CONTRACT.md
require_file docs/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER.md

require_contains 'Status: gate record' "$doc"
require_contains 'Evidence level: 8 target, gate only' "$doc"
require_contains 'target_is_disposable_fedora_vm=1' "$doc"
require_contains 'target_is_daily_driver=0' "$doc"
require_contains 'target_is_production_host=0' "$doc"
require_contains 'target_has_clean_snapshot=1' "$doc"
require_contains 'target_has_recovery_path=1' "$doc"
require_contains 'operator_consent_recorded=1' "$doc"
require_contains 'local_rpm_built_from_current_tree=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_is_documentation_only=1' "$doc"
require_contains 'installroot_lifecycle_evidence_present=1' "$doc"
require_contains 'manual_host_dry_run_transcript_contract_present=1' "$doc"
require_contains 'manual_host_rc_decision_classifier_present=1' "$doc"
require_contains 'rpm_gate_allowed=1' "$doc"
require_contains 'removal_rollback_ready=1' "$doc"
require_contains 'disposable_vm_effect_gate_status=eligible' "$doc"
require_contains 'disposable_vm_effect_gate_status=blocked' "$doc"
require_contains 'disposable_vm_effect_gate_status=invalid' "$doc"
require_contains 'effect_gate_present=1' "$doc"
require_contains 'host_install_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'fedora_disposable_vm_effect_gate: ok' "$doc"
require_contains 'Implement no-effect Fedora disposable VM effect gate classifier' "$doc"

printf 'fedora_disposable_vm_effect_gate: ok\n'
