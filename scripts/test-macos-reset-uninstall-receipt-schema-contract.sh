#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall receipt-schema contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall receipt-schema contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall receipt-schema contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall receipt-schema contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-receipt-schema-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-receipt-schema-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
absence_doc='docs/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT.md'
absence_status='docs/status/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT_STATUS.md'
planner_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER_STATUS.md'
verification_status='docs/status/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md'
commit_status='docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$readme"
require_file "$absence_doc"
require_file "$absence_status"
require_file "$planner_status"
require_file "$verification_status"
require_file "$commit_status"

require_contains 'Status: no-effect macOS reset/uninstall receipt-schema contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-receipt-schema-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$doc"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'receipt_schema_contract_state=defined-no-effect' "$doc"
require_contains 'receipt_schema_contract_decision=contract-defined-receipt-not-written' "$doc"
require_contains 'receipt_schema_required=1' "$doc"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$doc"
require_contains 'receipt_schema_evidence_present=0' "$doc"
require_contains 'reset_receipt_write_performed=0' "$doc"
require_contains 'receipt_write_performed=0' "$doc"
require_contains 'receipt_written=0' "$doc"
require_contains 'receipt_must_be_outside_removed_prefix=1' "$doc"
require_contains 'removed_prefix_must_not_contain_receipt=1' "$doc"
require_contains 'receipt_format=json' "$doc"
require_contains 'receipt_schema_version=macos-reset-uninstall-receipt/1' "$doc"
require_contains 'receipt_digest_algorithm=sha256' "$doc"
require_contains 'receipt_field_planner_transcript_digest_required=1' "$doc"
require_contains 'receipt_field_live_classifier_digest_required=1' "$doc"
require_contains 'receipt_field_absence_report_path_required=1' "$doc"
require_contains 'receipt_field_authority_denials_required=1' "$doc"
require_contains 'receipt_schema_phase_6_status=disabled' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_receipt_schema_contract: ok' "$doc"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$doc"

require_contains 'Status: no-effect reset/uninstall receipt-schema contract status' "$status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_guard_present=1' "$status"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$status"
require_contains 'receipt_schema_contract_state=defined-no-effect' "$status"
require_contains 'receipt_schema_required=1' "$status"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$status"
require_contains 'receipt_schema_evidence_present=0' "$status"
require_contains 'receipt_write_performed=0' "$status"
require_contains 'receipt_written=0' "$status"
require_contains 'receipt_must_be_outside_removed_prefix=1' "$status"
require_contains 'removed_prefix_must_not_contain_receipt=1' "$status"
require_contains 'receipt_schema_version=macos-reset-uninstall-receipt/1' "$status"
require_contains 'receipt_field_authority_denials_required=1' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS reset evidence' "$status"

require_contains 'MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall receipt-schema contract status' "$index"
require_contains 'stage_4_macos_reset_uninstall_receipt_schema_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-receipt-schema-contract.sh' "$transfer_plan"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$transfer_status"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$transfer_status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$readme"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-receipt-schema-contract.sh' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$absence_doc"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$absence_doc"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$absence_status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$planner_status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$verification_status"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$commit_status"

require_contains 'MACOS RESET UNINSTALL RECEIPT SCHEMA CONTRACT' "$script"
require_contains 'reset_uninstall_receipt_schema_contract_status=ok' "$script"
require_contains 'macos_reset_uninstall_receipt_schema_contract_present=1' "$script"
require_contains 'macos_reset_uninstall_implementation_gate_contract_present=1' "$script"
require_contains 'receipt_schema_contract_state=defined-no-effect' "$script"
require_contains 'receipt_schema_contract_decision=contract-defined-receipt-not-written' "$script"
require_contains 'receipt_schema_required=1' "$script"
require_contains 'reset_uninstall_receipt_evidence_present=0' "$script"
require_contains 'receipt_schema_evidence_present=0' "$script"
require_contains 'receipt_must_be_outside_removed_prefix=1' "$script"
require_contains 'removed_prefix_must_not_contain_receipt=1' "$script"
require_contains 'receipt_format=json' "$script"
require_contains 'receipt_schema_version=macos-reset-uninstall-receipt/1' "$script"
require_contains 'receipt_digest_algorithm=sha256' "$script"
require_contains 'receipt_field_operation_required=1' "$script"
require_contains 'receipt_field_planner_transcript_digest_required=1' "$script"
require_contains 'receipt_field_live_classifier_digest_required=1' "$script"
require_contains 'receipt_field_absence_report_path_required=1' "$script"
require_contains 'receipt_field_target_actions_required=1' "$script"
require_contains 'receipt_field_removed_managed_targets_required=1' "$script"
require_contains 'receipt_field_preserved_unmanaged_targets_required=1' "$script"
require_contains 'receipt_field_authority_denials_required=1' "$script"
require_contains 'receipt_schema_phase_6_status=disabled' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-execution-preflight-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL RECEIPT SCHEMA CONTRACT'
require_output_contains "$output" 'reset_uninstall_receipt_schema_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_receipt_schema_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_implementation_gate_contract_present=1'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_present=0'
require_output_contains "$output" 'receipt_schema_contract_decision=contract-defined-receipt-not-written'
require_output_contains "$output" 'receipt_schema_required=1'
require_output_contains "$output" 'reset_uninstall_receipt_evidence_present=0'
require_output_contains "$output" 'receipt_schema_evidence_present=0'
require_output_contains "$output" 'macos_reset_uninstall_absence_report_contract_present=1'
require_output_contains "$output" 'reset_uninstall_dry_run_planner_transcript_present=1'
require_output_contains "$output" 'receipt_must_be_outside_removed_prefix=1'
require_output_contains "$output" 'removed_prefix_must_not_contain_receipt=1'
require_output_contains "$output" 'receipt_format=json'
require_output_contains "$output" 'receipt_schema_version=macos-reset-uninstall-receipt/1'
require_output_contains "$output" 'receipt_field_authority_denials_required=1'
require_output_contains "$output" 'receipt_schema_phase_6_status=disabled'
require_output_contains "$output" 'reset_receipt_write_performed=0'
require_output_contains "$output" 'receipt_write_performed=0'
require_output_contains "$output" 'receipt_written=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-execution-preflight-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-receipt-schema-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-absence-report-contract.sh

printf 'macos_reset_uninstall_receipt_schema_contract: ok\n'
