#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall operator-intent contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall operator-intent contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall operator-intent contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall operator-intent contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-operator-intent-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-operator-intent-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
implementation_doc='docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md'
implementation_status='docs/status/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT_STATUS.md'
implementation_script='scripts/macos-reset-uninstall-implementation-gate-contract.sh'
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
require_file "$implementation_doc"
require_file "$implementation_status"
require_file "$implementation_script"
require_file "$receipt_status"
require_file "$absence_status"
require_file "$planner_status"
require_file "$classifier_status"
require_file "$commit_status"

require_contains 'Status: no-effect macOS reset/uninstall operator-intent contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-operator-intent-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$doc"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$doc"
require_contains 'operator_intent_contract_state=defined-no-effect' "$doc"
require_contains 'operator_intent_contract_decision=contract-defined-intent-not-observed' "$doc"
require_contains 'operator_intent_contract_required=1' "$doc"
require_contains 'operator_intent_contract_open=0' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_required=1' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$doc"
require_contains 'operator_intent_capture_performed=0' "$doc"
require_contains 'operator_intent_record_write_enabled=0' "$doc"
require_contains 'operator_intent_record_written=0' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$doc"
require_contains 'operator_intent_schema_version=macos-reset-uninstall-operator-intent/1' "$doc"
require_contains 'operator_intent_evidence_format=text-transcript' "$doc"
require_contains 'operator_intent_operation_values=reset,uninstall' "$doc"
require_contains 'operator_intent_must_acknowledge_dry_run_planner_digest=1' "$doc"
require_contains 'operator_intent_must_acknowledge_live_classifier_digest=1' "$doc"
require_contains 'operator_intent_must_acknowledge_receipt_path=1' "$doc"
require_contains 'operator_intent_must_acknowledge_absence_report_path=1' "$doc"
require_contains 'operator_intent_transcript_required=1' "$doc"
require_contains 'operator_intent_must_acknowledge_managed_targets_only=1' "$doc"
require_contains 'operator_intent_must_acknowledge_no_unmanaged_removal=1' "$doc"
require_contains 'operator_intent_must_acknowledge_receipt_path=1' "$doc"
require_contains 'operator_intent_must_acknowledge_absence_report_path=1' "$doc"
require_contains 'operator_intent_must_acknowledge_live_classifier_digest=1' "$doc"
require_contains 'operator_intent_must_acknowledge_dry_run_planner_digest=1' "$doc"
require_contains 'operator_intent_phase_5_status=disabled' "$doc"
require_contains 'operator_intent_phase_6_status=disabled' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_operator_intent_contract: ok' "$doc"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$doc"

require_contains 'Status: no-effect reset/uninstall operator-intent contract status' "$status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_operator_intent_contract_guard_present=1' "$status"
require_contains 'operator_intent_contract_state=defined-no-effect' "$status"
require_contains 'operator_intent_contract_decision=contract-defined-intent-not-observed' "$status"
require_contains 'operator_intent_contract_open=0' "$status"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$status"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$status"
require_contains 'operator_intent_transcript_required=1' "$status"
require_contains 'operator_intent_must_acknowledge_no_unmanaged_removal=1' "$status"
require_contains 'operator_intent_must_acknowledge_live_classifier_digest=1' "$status"
require_contains 'operator_intent_phase_6_status=disabled' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not operator approval evidence' "$status"

require_contains 'MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall operator-intent contract status' "$index"
require_contains 'stage_4_macos_reset_uninstall_operator_intent_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-operator-intent-contract.sh' "$transfer_plan"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$transfer_status"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$transfer_status"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$transfer_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-operator-intent-contract.sh' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT.md' "$readme"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$readme"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$readme"
require_contains 'macos_reset_uninstall_operator_intent_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$readme_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$implementation_doc"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$implementation_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$receipt_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$absence_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$planner_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$classifier_status"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$commit_status"

require_contains 'MACOS RESET UNINSTALL OPERATOR INTENT CONTRACT' "$script"
require_contains 'reset_uninstall_operator_intent_contract_status=ok' "$script"
require_contains 'macos_reset_uninstall_operator_intent_contract_present=1' "$script"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$script"
require_contains 'operator_intent_contract_state=defined-no-effect' "$script"
require_contains 'operator_intent_contract_decision=contract-defined-intent-not-observed' "$script"
require_contains 'operator_intent_contract_required=1' "$script"
require_contains 'operator_intent_contract_open=0' "$script"
require_contains 'operator_reset_uninstall_intent_evidence_required=1' "$script"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$script"
require_contains 'operator_explicit_reset_uninstall_intent_observed=0' "$script"
require_contains 'operator_intent_record_write_enabled=0' "$script"
require_contains 'reset_uninstall_live_run_allowed=0' "$script"
require_contains 'reset_uninstall_deletion_enabled=0' "$script"
require_contains 'operator_intent_schema_version=macos-reset-uninstall-operator-intent/1' "$script"
require_contains 'operator_intent_transcript_required=1' "$script"
require_contains 'operator_intent_must_acknowledge_no_unmanaged_removal=1' "$script"
require_contains 'operator_intent_confirmation_phrase_required=1' "$script"
require_contains 'operator_intent_phase_5_status=disabled' "$script"
require_contains 'operator_intent_phase_6_status=disabled' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-noop-prototype-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL OPERATOR INTENT CONTRACT'
require_output_contains "$output" 'reset_uninstall_operator_intent_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_operator_intent_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_implementation_gate_contract_present=1'
require_output_contains "$output" 'operator_intent_contract_decision=contract-defined-intent-not-observed'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_required=1'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_present=0'
require_output_contains "$output" 'operator_explicit_reset_uninstall_intent_observed=0'
require_output_contains "$output" 'operator_intent_record_write_enabled=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'operator_intent_schema_version=macos-reset-uninstall-operator-intent/1'
require_output_contains "$output" 'operator_intent_must_acknowledge_live_classifier_digest=1'
require_output_contains "$output" 'operator_intent_must_acknowledge_receipt_path=1'
require_output_contains "$output" 'operator_intent_must_acknowledge_managed_targets_only=1'
require_output_contains "$output" 'operator_intent_must_acknowledge_no_unmanaged_removal=1'
require_output_contains "$output" 'operator_intent_phase_5_status=disabled'
require_output_contains "$output" 'operator_intent_phase_6_status=disabled'
require_output_contains "$output" 'reset_uninstall_implementation_present=0'
require_output_contains "$output" 'macos_reset_uninstall_implemented=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-noop-prototype-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-operator-intent-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-implementation-gate-contract.sh

printf 'macos_reset_uninstall_operator_intent_contract: ok\n'
