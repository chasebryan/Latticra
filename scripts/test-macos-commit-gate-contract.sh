#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos commit gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos commit gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos commit gate contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_COMMIT_GATE_CONTRACT.md'
status='docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md'
script='scripts/macos-commit-gate-contract.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
integration_doc='docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md'
integration_status='docs/status/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION_STATUS.md'
verification_doc='docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md'
verification_status='docs/status/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md'
reset_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT_STATUS.md'
alignment_doc='docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md'
alignment_status='docs/status/MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md'
writer_status='docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md'
implementation_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md'
workflow='.github/workflows/macos-commit-gate-contract.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$integration_doc"
require_file "$integration_status"
require_file "$verification_doc"
require_file "$verification_status"
require_file "$reset_status"
require_file "$alignment_doc"
require_file "$alignment_status"
require_file "$writer_status"
require_file "$implementation_status"
require_file "$workflow"

require_contains 'Status: no-effect macOS commit gate contract' "$doc"
require_contains 'sh scripts/macos-commit-gate-contract.sh' "$doc"
require_contains 'commit_gate_state=closed' "$doc"
require_contains 'commit_gate_decision=blocked-missing-managed-write-implementation' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'macos_app_bundle_commit_capable_writer_present=0' "$doc"
require_contains 'managed_write_implementation_present=0' "$doc"
require_contains 'reset_uninstall_implementation_present=0' "$doc"
require_contains 'macos_verification_transcript_contract_present=1' "$doc"
require_contains 'verification_transcript_contract_present=1' "$doc"
require_contains 'verification_transcript_evidence_present=0' "$doc"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$doc"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$doc"
require_contains 'reset_uninstall_dry_run_evidence_present=0' "$doc"
require_contains 'absence_report_evidence_present=0' "$doc"
require_contains 'candidate_flow_ready_required=1' "$doc"
require_contains 'operator_explicit_commit_intent_required=1' "$doc"
require_contains 'receipt_completeness_tests_required=1' "$doc"
require_contains 'app_bundle_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'reset/uninstall dry-run contract' "$doc"

require_contains 'Status: no-effect commit gate contract status' "$status"
require_contains 'macos_commit_gate_contract_present=1' "$status"
require_contains 'macos_commit_gate_contract_guard_present=1' "$status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$status"
require_contains 'macos_verification_transcript_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$status"
require_contains 'commit_gate_state=closed' "$status"
require_contains 'commit_gate_decision=blocked-missing-managed-write-implementation' "$status"
require_contains 'commit_user_local_managed_artifacts=0' "$status"
require_contains 'managed_write_implementation_present=0' "$status"
require_contains 'verification_transcript_contract_present=1' "$status"
require_contains 'verification_transcript_evidence_present=0' "$status"
require_contains 'reset_uninstall_dry_run_evidence_present=0' "$status"
require_contains 'absence_report_evidence_present=0' "$status"
require_contains 'operator_explicit_commit_intent_required=1' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_COMMIT_GATE_CONTRACT_STATUS.md' "$index"
require_contains 'macOS commit gate contract status' "$index"
require_contains 'stage_3_macos_commit_gate_contract=present' "$transfer_plan"
require_contains 'stage_4_user_local_verification_transcript_contract=present' "$transfer_plan"
require_contains 'stage_4_macos_reset_uninstall_dry_run_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_COMMIT_GATE_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-commit-gate-contract.sh' "$transfer_plan"
require_contains 'docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md' "$transfer_plan"
require_contains 'macos_commit_gate_contract_present=1' "$transfer_status"
require_contains 'macos_verification_transcript_contract_present=1' "$transfer_status"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$transfer_status"
require_contains 'macos_commit_gate_contract_present=1' "$integration_status"
require_contains 'macos_verification_transcript_contract_present=1' "$integration_status"
require_contains 'macos_commit_gate_contract_present=1' "$alignment_status"
require_contains 'macos_commit_gate_contract_present=1' "$writer_status"
require_contains 'macos_commit_gate_contract_present=1' "$implementation_status"
require_contains 'macos_verification_transcript_contract_present=1' "$verification_status"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$reset_status"
require_contains 'macOS commit gate contract' "$integration_doc"
require_contains 'macOS verification transcript contract' "$verification_doc"
require_contains 'macOS commit gate contract' "$alignment_doc"
require_contains 'Add a macOS reset/uninstall operator-intent contract' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall operator-intent contract' "$transfer_status"
require_contains 'sh scripts/test-macos-commit-gate-contract.sh' "$workflow"

require_contains 'MACOS COMMIT GATE CONTRACT' "$script"
require_contains 'commit_gate_state=closed' "$script"
require_contains 'commit_gate_decision=blocked-missing-managed-write-implementation' "$script"
require_contains 'commit_user_local_managed_artifacts=0' "$script"
require_contains 'managed_write_implementation_present=0' "$script"
require_contains 'macos_verification_transcript_contract_present=1' "$script"
require_contains 'verification_transcript_contract_present=1' "$script"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$script"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$script"
require_contains 'reset_uninstall_dry_run_evidence_present=0' "$script"
require_contains 'absence_report_evidence_present=0' "$script"
require_contains 'app_bundle_write_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-operator-intent-contract' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS COMMIT GATE CONTRACT'
require_output_contains "$output" 'commit_gate_contract_status=ok'
require_output_contains "$output" 'macos_commit_gate_contract_present=1'
require_output_contains "$output" 'commit_gate_state=closed'
require_output_contains "$output" 'commit_gate_decision=blocked-missing-managed-write-implementation'
require_output_contains "$output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$output" 'macos_app_bundle_commit_capable_writer_present=0'
require_output_contains "$output" 'managed_write_implementation_present=0'
require_output_contains "$output" 'macos_verification_transcript_contract_present=1'
require_output_contains "$output" 'verification_transcript_contract_present=1'
require_output_contains "$output" 'verification_transcript_evidence_present=0'
require_output_contains "$output" 'macos_reset_uninstall_dry_run_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_absence_report_contract_present=1'
require_output_contains "$output" 'reset_uninstall_dry_run_evidence_present=0'
require_output_contains "$output" 'absence_report_evidence_present=0'
require_output_contains "$output" 'operator_explicit_commit_intent_observed=0'
require_output_contains "$output" 'app_bundle_write_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'production_installer_ready=0'

sh scripts/test-macos-dry-run-writer-candidate-integration.sh
sh scripts/test-macos-verification-transcript-contract.sh

printf 'macos_commit_gate_contract: ok\n'
