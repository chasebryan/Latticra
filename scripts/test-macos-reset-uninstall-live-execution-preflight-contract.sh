#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-execution preflight contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-execution preflight contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-execution preflight contract: forbidden pattern in %s: %s\n' "$file" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-execution preflight contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-execution-preflight-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-execution-preflight-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
live_plan_doc='docs/MACOS_RESET_UNINSTALL_LIVE_IMPLEMENTATION_PLAN_CONTRACT.md'
live_plan_status='docs/status/MACOS_RESET_UNINSTALL_LIVE_IMPLEMENTATION_PLAN_CONTRACT_STATUS.md'
live_plan_script='scripts/macos-reset-uninstall-live-implementation-plan-contract.sh'
evidence_status='docs/status/MACOS_RESET_UNINSTALL_EVIDENCE_BUNDLE_CONTRACT_STATUS.md'
effect_status='docs/status/MACOS_RESET_UNINSTALL_EFFECT_AUTHORIZATION_CONTRACT_STATUS.md'
operator_status='docs/status/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT_STATUS.md'
implementation_status='docs/status/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT_STATUS.md'
receipt_status='docs/status/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT_STATUS.md'
absence_status='docs/status/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT_STATUS.md'
planner_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER_STATUS.md'
classifier_status='docs/status/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$readme"
require_file "$readme_status"
require_file "$live_plan_doc"
require_file "$live_plan_status"
require_file "$live_plan_script"
require_file "$evidence_status"
require_file "$effect_status"
require_file "$operator_status"
require_file "$implementation_status"
require_file "$receipt_status"
require_file "$absence_status"
require_file "$planner_status"
require_file "$classifier_status"

require_contains 'Status: no-effect macOS reset/uninstall live-execution preflight contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-execution-preflight-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$doc"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$doc"
require_contains 'live_execution_preflight_contract_decision=blocked-missing-complete-evidence-bundle-and-effect-authorization' "$doc"
require_contains 'live_execution_preflight_passed=0' "$doc"
require_contains 'live_execution_preflight_blocking=1' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$doc"
require_contains 'macos_reset_uninstall_live_implementation_plan_contract_present=1' "$doc"
require_contains 'live_implementation_plan_preflight_present=1' "$doc"
require_contains 'live_implementation_plan_preflight_passed=0' "$doc"
require_contains 'reset_uninstall_evidence_bundle_complete=0' "$doc"
require_contains 'effect_authorization_open=0' "$doc"
require_contains 'reset_uninstall_effect_authorized=0' "$doc"
require_contains 'implementation_gate_open=0' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'live_execution_preflight_requires_complete_evidence_bundle=1' "$doc"
require_contains 'live_execution_preflight_requires_effect_authorization=1' "$doc"
require_contains 'live_execution_preflight_result_complete_evidence_bundle=not_met' "$doc"
require_contains 'live_execution_preflight_result_effect_authorization=not_met' "$doc"
require_contains 'live_execution_preflight_phase_8_status=disabled' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract: ok' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$doc"

require_contains 'Status: no-effect reset/uninstall live-execution preflight contract status' "$status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_guard_present=1' "$status"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$status"
require_contains 'live_execution_preflight_passed=0' "$status"
require_contains 'live_execution_preflight_blocking=1' "$status"
require_contains 'live_execution_preflight_requires_complete_evidence_bundle=1' "$status"
require_contains 'live_execution_preflight_result_effect_authorization=not_met' "$status"
require_contains 'live_execution_preflight_phase_8_status=disabled' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'live reset execution' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-execution preflight contract status' "$index"
require_contains 'stage_4_macos_reset_uninstall_live_execution_preflight_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-execution-preflight-contract.sh' "$transfer_plan"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$transfer_status"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$transfer_status"
require_contains 'live_execution_preflight_passed=0' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-execution preflight contract' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-denial transcript contract' "$transfer_status"

require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-live-execution-preflight-contract.sh' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md' "$readme"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$readme"
require_contains 'live_execution_preflight_passed=0' "$readme"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$readme_status"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$readme_status"
require_contains 'live_execution_preflight_passed=0' "$readme_status"

require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$live_plan_doc"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$live_plan_status"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-review-contract' "$live_plan_script"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$evidence_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$effect_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$operator_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$implementation_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$receipt_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$absence_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$planner_status"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$classifier_status"

require_contains 'MACOS RESET UNINSTALL LIVE EXECUTION PREFLIGHT CONTRACT' "$script"
require_contains 'reset_uninstall_live_execution_preflight_contract_status=ok' "$script"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$script"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$script"
require_contains 'live_execution_preflight_contract_decision=blocked-missing-complete-evidence-bundle-and-effect-authorization' "$script"
require_contains 'live_execution_preflight_passed=0' "$script"
require_contains 'reset_uninstall_live_run_allowed=0' "$script"
require_contains 'reset_uninstall_deletion_enabled=0' "$script"
require_contains 'live_implementation_plan_preflight_present=1' "$script"
require_contains 'live_implementation_plan_preflight_passed=0' "$script"
require_contains 'reset_uninstall_evidence_bundle_complete=0' "$script"
require_contains 'effect_authorization_open=0' "$script"
require_contains 'reset_uninstall_effect_authorized=0' "$script"
require_contains 'implementation_gate_open=0' "$script"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$script"
require_contains 'live_execution_preflight_requires_complete_evidence_bundle=1' "$script"
require_contains 'live_execution_preflight_condition_no_network=required' "$script"
require_contains 'live_execution_preflight_condition_no_root=required' "$script"
require_contains 'live_execution_preflight_result_complete_evidence_bundle=not_met' "$script"
require_contains 'live_execution_preflight_result_effect_authorization=not_met' "$script"
require_contains 'live_execution_preflight_result_no_network=met' "$script"
require_contains 'live_execution_preflight_result_no_root=met' "$script"
require_contains 'live_execution_preflight_phase_8_status=disabled' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-review-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE EXECUTION PREFLIGHT CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_execution_preflight_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_execution_preflight_contract_present=1'
require_output_contains "$output" 'live_execution_preflight_contract_decision=blocked-missing-complete-evidence-bundle-and-effect-authorization'
require_output_contains "$output" 'live_execution_preflight_passed=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'live_implementation_plan_preflight_present=1'
require_output_contains "$output" 'live_implementation_plan_preflight_passed=0'
require_output_contains "$output" 'reset_uninstall_evidence_bundle_complete=0'
require_output_contains "$output" 'effect_authorization_open=0'
require_output_contains "$output" 'reset_uninstall_effect_authorized=0'
require_output_contains "$output" 'implementation_gate_open=0'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_present=0'
require_output_contains "$output" 'live_execution_preflight_requires_complete_evidence_bundle=1'
require_output_contains "$output" 'live_execution_preflight_result_complete_evidence_bundle=not_met'
require_output_contains "$output" 'live_execution_preflight_result_effect_authorization=not_met'
require_output_contains "$output" 'live_execution_preflight_phase_8_status=disabled'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-review-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-execution-preflight-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-implementation-plan-contract.sh

printf 'macos_reset_uninstall_live_execution_preflight_contract: ok\n'
