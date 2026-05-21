#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm local rpm validation status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm local rpm validation status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_STATUS.md'
index='docs/status/README.md'
lane='docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md'
runner='scripts/run-fedora-disposable-vm-local-rpm-validation-lane.sh'
docs_guard='scripts/test-fedora-disposable-vm-local-rpm-validation-lane-docs.sh'
workflow='.github/workflows/fedora-vm-rpm-validation-lane-docs.yml'

require_file "$status"
require_file "$index"
require_file "$lane"
require_file "$runner"
require_file "$docs_guard"
require_file "$workflow"
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE.md
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER.md
require_file docs/status/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER_STATUS.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: status alignment' "$status"
require_contains 'source=PR #223' "$status"
require_contains 'validation_lane_documented=1' "$status"
require_contains 'validation_runner_present=1' "$status"
require_contains 'validation_lane_docs_guard_present=1' "$status"
require_contains 'validation_lane_docs_workflow_present=1' "$status"
require_contains 'runner_manual_only=1' "$status"
require_contains 'ci_auto_vm_rpm_validation_allowed=0' "$status"
require_contains 'disposable_vm_target_required=1' "$status"
require_contains 'daily_driver_block_required=1' "$status"
require_contains 'production_host_block_required=1' "$status"
require_contains 'immutable_fedora_block_required=1' "$status"
require_contains 'clean_snapshot_required=1' "$status"
require_contains 'recovery_path_required=1' "$status"
require_contains 'operator_consent_required=1' "$status"
require_contains 'rpm_payload_listing_required=1' "$status"
require_contains 'rpm_payload_documentation_only_required=1' "$status"
require_contains 'unexpected_runtime_surface_absent_required=1' "$status"
require_contains 'validation_report_schema_present=1' "$status"
require_contains 'target_evidence_level=9' "$status"
require_contains 'current_evidence_level=8' "$status"
require_contains 'evidence_level_9_achieved=0' "$status"
require_contains 'disposable_vm_local_rpm_validation_lane_present=1' "$status"
require_contains 'disposable_vm_local_rpm_validation_status=blocked-pending-real-vm-run' "$status"
require_contains 'disposable_vm_validation_transcript_present=0' "$status"
require_contains 'disposable_vm_validation_completed=0' "$status"
require_contains 'live_host_validation_completed=0' "$status"
require_contains 'host_install_ready=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'This status alignment does not run the validation lane.' "$status"
require_contains 'The RPM validation runner must remain manual and gated by explicit disposable-VM evidence.' "$status"
require_contains 'Capture disposable Fedora VM local RPM validation transcript evidence' "$status"
require_contains 'The root README should not claim install readiness yet.' "$status"

require_contains 'FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_STATUS.md' "$index"
require_contains 'Current Fedora disposable VM local RPM validation lane checkpoint' "$index"
require_contains 'source=PR #223' "$index"
require_contains 'validation_runner_present=1' "$index"
require_contains 'runner_manual_only=1' "$index"
require_contains 'ci_auto_vm_rpm_validation_allowed=0' "$index"
require_contains 'disposable_vm_local_rpm_validation_status=blocked-pending-real-vm-run' "$index"
require_contains 'disposable_vm_validation_transcript_present=0' "$index"
require_contains 'host_install_ready=0' "$index"
require_contains 'Capture disposable Fedora VM local RPM validation transcript evidence' "$index"
require_contains 'Current Fedora disposable VM effect gate classifier checkpoint' "$index"

require_contains 'Status: gated validation lane' "$lane"
require_contains 'Evidence level: 9 target' "$lane"
require_contains 'FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE' "$lane"
require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$lane"
require_contains 'live_host_validation_completed=1' "$lane"
require_contains 'host_install_ready=1' "$lane"

require_contains 'require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM 1' "$runner"
require_contains 'FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE' "$runner"
require_contains 'host_install_ready=1' "$runner"

printf 'fedora_disposable_vm_local_rpm_validation_status_alignment: ok\n'
