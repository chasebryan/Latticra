#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora manual host rc decision classifier docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora manual host rc decision classifier docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER.md'
header='include/latticra/fedora_manual_host_rc_decision.h'
source='src/fedora_manual_host_rc_decision.c'
test='tests/fedora_manual_host_rc_decision.c'
script='scripts/test-fedora-manual-host-rc-decision-classifier.sh'

require_file "$doc"
require_file "$header"
require_file "$source"
require_file "$test"
require_file "$script"
require_file docs/FEDORA_MANUAL_HOST_RC_CHECKLIST.md
require_file docs/status/FEDORA_MANUAL_HOST_RC_CHECKLIST_STATUS.md

require_contains 'Status: implementation record' "$doc"
require_contains 'Evidence level: 7' "$doc"
require_contains 'pure no-effect classifier' "$doc"
require_contains 'latticra_fedora_manual_host_rc_decision_classify' "$doc"
require_contains 'latticra_fedora_manual_host_rc_decision_report' "$doc"
require_contains 'target_is_disposable_fedora_vm=1' "$doc"
require_contains 'target_is_daily_driver=0' "$doc"
require_contains 'target_is_production_host=0' "$doc"
require_contains 'target_is_immutable_fedora=0' "$doc"
require_contains 'target_has_clean_snapshot=1' "$doc"
require_contains 'target_has_recovery_path=1' "$doc"
require_contains 'operator_consent_recorded=1' "$doc"
require_contains 'local_rpm_built_from_current_tree=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_is_documentation_only=1' "$doc"
require_contains 'unexpected_runtime_surface_absent=1' "$doc"
require_contains 'installroot_lifecycle_evidence_present=1' "$doc"
require_contains 'post_removal_absence_evidence_present=1' "$doc"
require_contains 'host_preflight_ready_local_rpm=1' "$doc"
require_contains 'rpm_gate_allowed=1' "$doc"
require_contains 'removal_rollback_ready=1' "$doc"
require_contains 'network_requirement_detected=0' "$doc"
require_contains 'service_boundary_detected=0' "$doc"
require_contains 'boot_boundary_detected=0' "$doc"
require_contains 'kernel_boundary_detected=0' "$doc"
require_contains 'policy_boundary_detected=0' "$doc"
require_contains 'manual_host_rc_status=candidate' "$doc"
require_contains 'manual_host_rc_status=blocked' "$doc"
require_contains 'manual_host_rc_status=invalid' "$doc"
require_contains 'not-disposable-fedora-vm' "$doc"
require_contains 'daily-driver-target' "$doc"
require_contains 'production-target' "$doc"
require_contains 'immutable-fedora-target' "$doc"
require_contains 'snapshot-missing' "$doc"
require_contains 'recovery-path-missing' "$doc"
require_contains 'operator-consent-missing' "$doc"
require_contains 'local-rpm-not-current-tree' "$doc"
require_contains 'rpm-payload-listing-missing' "$doc"
require_contains 'rpm-payload-not-documentation-only' "$doc"
require_contains 'unexpected-runtime-surface' "$doc"
require_contains 'installroot-evidence-missing' "$doc"
require_contains 'post-removal-evidence-missing' "$doc"
require_contains 'preflight-not-ready' "$doc"
require_contains 'rpm-gate-not-allowed' "$doc"
require_contains 'removal-rollback-not-ready' "$doc"
require_contains 'network-required' "$doc"
require_contains 'service-boundary' "$doc"
require_contains 'boot-boundary' "$doc"
require_contains 'kernel-boundary' "$doc"
require_contains 'policy-boundary' "$doc"
require_contains 'invalid-classifier-input' "$doc"
require_contains 'FEDORA MANUAL HOST RC DECISION CLASSIFIER' "$doc"
require_contains 'manual_host_release_candidate_ready=1' "$doc"
require_contains 'manual_host_release_candidate_ready=0' "$doc"
require_contains 'live_host_validation_completed=0' "$doc"
require_contains 'host_change_performed=0' "$doc"
require_contains 'sudo_invoked=0' "$doc"
require_contains 'rpm_invoked=0' "$doc"
require_contains 'dnf_invoked=0' "$doc"
require_contains 'network_allowed=0' "$doc"
require_contains 'service_operation_allowed=0' "$doc"
require_contains 'boot_operation_allowed=0' "$doc"
require_contains 'kernel_operation_allowed=0' "$doc"
require_contains 'policy_operation_allowed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'fedora_manual_host_rc_decision_classifier: ok' "$doc"
require_contains 'fedora_manual_host_rc_decision_classifier_docs: ok' "$doc"
require_contains 'Align Fedora manual host RC decision classifier status' "$doc"
require_contains 'does not implement installation' "$doc"

require_contains 'LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_CANDIDATE' "$header"
require_contains 'LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_BLOCKED' "$header"
require_contains 'LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_INVALID' "$header"
require_contains 'LATTICRA_FEDORA_MANUAL_HOST_RC_DECISION_DENIAL_INVALID_INPUT' "$header"
require_contains 'latticra_fedora_manual_host_rc_decision_classify' "$header"
require_contains 'latticra_fedora_manual_host_rc_decision_report' "$header"

printf 'fedora_manual_host_rc_decision_classifier_docs: ok\n'
