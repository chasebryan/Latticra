#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora manual host dry-run transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora manual host dry-run transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_MANUAL_HOST_DRY_RUN_TRANSCRIPT_CONTRACT.md'

require_file "$doc"
require_file docs/FEDORA_MANUAL_HOST_RC_CHECKLIST.md
require_file docs/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER.md
require_file docs/status/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER_STATUS.md

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 8 target, contract only' "$doc"
require_contains 'evidence schema only' "$doc"
require_contains 'LATTICRA FEDORA MANUAL HOST DRY-RUN TRANSCRIPT' "$doc"
require_contains 'transcript_kind=dry-run' "$doc"
require_contains 'transcript_version=1' "$doc"
require_contains 'operator_review_required=1' "$doc"
require_contains 'host_change_performed=0' "$doc"
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
require_contains 'host_preflight_ready_local_rpm=1' "$doc"
require_contains 'rpm_gate_allowed=1' "$doc"
require_contains 'removal_rollback_ready=1' "$doc"
require_contains 'manual_host_rc_decision_classifier_present=1' "$doc"
require_contains 'manual_host_dry_run_transcript_present=1' "$doc"
require_contains 'live_host_validation_completed=0' "$doc"
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
require_contains 'TARGET REVIEW' "$doc"
require_contains 'PACKAGE REVIEW' "$doc"
require_contains 'PRIOR EVIDENCE REVIEW' "$doc"
require_contains 'DRY-RUN DECISION REVIEW' "$doc"
require_contains 'NO-EFFECT BOUNDARY REVIEW' "$doc"
require_contains 'OPERATOR SIGNOFF PLACEHOLDER' "$doc"
require_contains 'NEXT ACTION REVIEW' "$doc"
require_contains 'dry_run_transcript_status=accepted-for-review' "$doc"
require_contains 'dry_run_transcript_status=blocked' "$doc"
require_contains 'dry_run_transcript_status=invalid' "$doc"
require_contains 'daily_driver_detected=1' "$doc"
require_contains 'production_host_detected=1' "$doc"
require_contains 'immutable_fedora_detected=1' "$doc"
require_contains 'snapshot_missing=1' "$doc"
require_contains 'recovery_path_missing=1' "$doc"
require_contains 'operator_consent_missing=1' "$doc"
require_contains 'rpm_payload_listing_missing=1' "$doc"
require_contains 'rpm_payload_not_documentation_only=1' "$doc"
require_contains 'unexpected_runtime_surface_present=1' "$doc"
require_contains 'prior_installroot_evidence_missing=1' "$doc"
require_contains 'prior_removal_evidence_missing=1' "$doc"
require_contains 'prior_preflight_evidence_missing=1' "$doc"
require_contains 'prior_gate_evidence_missing=1' "$doc"
require_contains 'prior_removal_rollback_evidence_missing=1' "$doc"
require_contains 'network_requirement_detected=1' "$doc"
require_contains 'service_boundary_detected=1' "$doc"
require_contains 'boot_boundary_detected=1' "$doc"
require_contains 'kernel_boundary_detected=1' "$doc"
require_contains 'policy_boundary_detected=1' "$doc"
require_contains 'fedora_manual_host_dry_run_transcript_contract: ok' "$doc"
require_contains 'Implement no-effect Fedora dry-run transcript classifier' "$doc"
require_contains 'root README should wait' "$doc"
require_contains 'host_install_ready=1' "$doc"
require_contains 'not production readiness' "$doc"

printf 'fedora_manual_host_dry_run_transcript_contract: ok\n'
