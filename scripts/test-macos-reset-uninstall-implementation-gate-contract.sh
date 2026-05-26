#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall implementation-gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall implementation-gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall implementation-gate contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall implementation-gate contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-implementation-gate-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-implementation-gate-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
receipt_doc='docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md'
receipt_status='docs/status/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT_STATUS.md'
absence_status='docs/status/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT_STATUS.md'
planner_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER_STATUS.md'
classifier_status='docs/status/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER_STATUS.md'
commit_status='docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$readme"
require_file "$readme_status"
require_file "$receipt_doc"
require_file "$receipt_status"
require_file "$absence_status"
require_file "$planner_status"
require_file "$classifier_status"
require_file "$commit_status"

require_contains 'Status: no-effect macOS reset/uninstall implementation-gate contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-implementation-gate-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$doc"
require_contains 'implementation_gate_contract_state=closed-no-effect' "$doc"
require_contains 'implementation_gate_state=closed-no-effect' "$doc"
require_contains 'implementation_gate_decision=blocked-missing-reset-uninstall-evidence' "$doc"
require_contains 'implementation_gate_open=0' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$doc"
require_contains 'managed_target_removal_allowed=0' "$doc"
require_contains 'reset_uninstall_receipt_write_enabled=0' "$doc"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$doc"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$doc"
require_contains 'macos_reset_uninstall_dry_run_planner_present=1' "$doc"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$doc"
require_contains 'macos_commit_gate_contract_present=1' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$doc"
require_contains 'operator_explicit_reset_uninstall_intent_required=1' "$doc"
require_contains 'operator_intent_must_name_operation=1' "$doc"
require_contains 'operator_intent_must_acknowledge_managed_targets_only=1' "$doc"
require_contains 'gate_condition_operator_intent_evidence_present=required' "$doc"
require_contains 'implementation_gate_phase_5_status=disabled' "$doc"
require_contains 'implementation_gate_phase_6_status=disabled' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_implementation_gate_contract: ok' "$doc"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$doc"

require_contains 'Status: no-effect reset/uninstall implementation-gate contract status' "$status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_guard_present=1' "$status"
require_contains 'implementation_gate_contract_state=closed-no-effect' "$status"
require_contains 'implementation_gate_state=closed-no-effect' "$status"
require_contains 'implementation_gate_open=0' "$status"
require_contains 'reset_uninstall_live_run_allowed=0' "$status"
require_contains 'reset_uninstall_deletion_enabled=0' "$status"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$status"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$status"
require_contains 'gate_condition_receipt_schema_contract_present=required' "$status"
require_contains 'gate_condition_operator_intent_evidence_present=required' "$status"
require_contains 'implementation_gate_phase_6_status=disabled' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS reset evidence' "$status"

require_contains 'MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall implementation-gate contract status' "$index"
require_contains 'stage_4_macos_reset_uninstall_implementation_gate_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-implementation-gate-contract.sh' "$transfer_plan"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$transfer_status"
require_contains 'reset_uninstall_live_run_allowed=0' "$transfer_status"
require_contains 'reset_uninstall_deletion_enabled=0' "$transfer_status"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$transfer_status"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$transfer_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-implementation-gate-contract.sh' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md' "$readme"
require_contains 'reset_uninstall_live_run_allowed=0' "$readme"
require_contains 'reset_uninstall_deletion_enabled=0' "$readme"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$readme"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$readme"
require_contains 'macos_reset_uninstall_implementation_gate_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$readme_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$receipt_doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$receipt_doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$receipt_doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$receipt_doc"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$receipt_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$absence_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$planner_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$classifier_status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$commit_status"

require_contains 'MACOS RESET UNINSTALL IMPLEMENTATION GATE CONTRACT' "$script"
require_contains 'reset_uninstall_implementation_gate_contract_status=ok' "$script"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$script"
require_contains 'implementation_gate_contract_state=closed-no-effect' "$script"
require_contains 'implementation_gate_decision=blocked-missing-reset-uninstall-evidence' "$script"
require_contains 'implementation_gate_required=1' "$script"
require_contains 'implementation_gate_open=0' "$script"
require_contains 'reset_uninstall_live_run_allowed=0' "$script"
require_contains 'reset_uninstall_deletion_enabled=0' "$script"
require_contains 'managed_target_removal_allowed=0' "$script"
require_contains 'reset_uninstall_receipt_write_enabled=0' "$script"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$script"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$script"
require_contains 'operator_explicit_reset_uninstall_intent_required=1' "$script"
require_contains 'operator_intent_must_acknowledge_receipt_path=1' "$script"
require_contains 'gate_condition_no_unsafe_paths=required' "$script"
require_contains 'implementation_gate_phase_5_status=disabled' "$script"
require_contains 'implementation_gate_phase_6_status=disabled' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL IMPLEMENTATION GATE CONTRACT'
require_output_contains "$output" 'reset_uninstall_implementation_gate_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_implementation_gate_contract_present=1'
require_output_contains "$output" 'implementation_gate_decision=blocked-missing-reset-uninstall-evidence'
require_output_contains "$output" 'implementation_gate_required=1'
require_output_contains "$output" 'implementation_gate_open=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'macos_reset_uninstall_receipt_schema_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_absence_report_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_dry_run_planner_present=1'
require_output_contains "$output" 'macos_reset_uninstall_live_target_classifier_present=1'
require_output_contains "$output" 'managed_target_removal_allowed=0'
require_output_contains "$output" 'reset_uninstall_receipt_write_enabled=0'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_present=0'
require_output_contains "$output" 'operator_explicit_reset_uninstall_intent_required=1'
require_output_contains "$output" 'operator_explicit_reset_uninstall_intent_observed=0'
require_output_contains "$output" 'gate_condition_operator_intent_evidence_present=required'
require_output_contains "$output" 'implementation_gate_phase_5_status=disabled'
require_output_contains "$output" 'implementation_gate_phase_6_status=disabled'
require_output_contains "$output" 'reset_uninstall_implementation_present=0'
require_output_contains "$output" 'macos_reset_uninstall_implemented=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-implementation-gate-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-receipt-schema-contract.sh

printf 'macos_reset_uninstall_implementation_gate_contract: ok\n'
