#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner acceptance-gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-gate contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner acceptance-gate contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-acceptance-gate-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
review_script='scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh'
review_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$readme"
require_file "$readme_status"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$review_script"
require_file "$review_doc"

require_contains 'Status: no-effect macOS reset/uninstall live-runner acceptance-gate contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$doc"
require_contains 'live_runner_acceptance_gate_contract_decision=dispatch-blocked-missing-passed-preflight-evidence-and-authorization' "$doc"
require_contains 'live_runner_acceptance_gate_required=1' "$doc"
require_contains 'live_runner_acceptance_gate_present=1' "$doc"
require_contains 'live_runner_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_gate_acceptance_granted=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_gate_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_gate_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_gate_runner_handoff_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_receipt_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_absence_report_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_effect_authorized=0' "$doc"
require_contains 'live_runner_acceptance_gate_denial_reason=missing-passed-preflight-complete-evidence-effect-authorization-operator-intent-and-implementation' "$doc"
require_contains 'live_runner_acceptance_gate_source_contract=macos-reset-uninstall-live-runner-denied-dispatch-review-contract' "$doc"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_contract_state=reviewed-no-effect' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_performed=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_deletion_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_acceptance_gate_opened=0' "$doc"
require_contains 'live_execution_preflight_passed=0' "$doc"
require_contains 'evidence_bundle_complete=0' "$doc"
require_contains 'effect_authorization_open=0' "$doc"
require_contains 'reset_uninstall_effect_authorized=0' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'reset_uninstall_implementation_present=0' "$doc"
require_contains 'live_runner_acceptance_gate_schema_version=macos-reset-uninstall-live-runner-acceptance-gate/1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_denied_dispatch_review=1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_passed_preflight=1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_complete_evidence_bundle=1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_effect_authorization=1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_operator_intent=1' "$doc"
require_contains 'live_runner_acceptance_gate_requires_implementation=1' "$doc"
require_contains 'live_runner_acceptance_gate_result_denied_dispatch_review=met' "$doc"
require_contains 'live_runner_acceptance_gate_result_passed_preflight=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_complete_evidence_bundle=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_effect_authorization=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_operator_intent=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_implementation=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_no_dispatch_until_open=met' "$doc"
require_contains 'live_runner_acceptance_gate_entry_7=dispatch_blocked' "$doc"
require_contains 'live_runner_acceptance_gate_phase_2_status=blocking' "$doc"
require_contains 'live_runner_acceptance_gate_phase_3_status=blocked-no-effect' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that keeps the live runner closed until passed preflight, evidence, authorization, operator intent, and implementation are all present.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.' "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner acceptance-gate contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_guard_present=1' "$status"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$status"
require_contains 'live_runner_acceptance_gate_open=0' "$status"
require_contains 'live_runner_acceptance_gate_acceptance_granted=0' "$status"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$status"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$status"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$status"
require_contains 'live_runner_acceptance_gate_receipt_write_enabled=0' "$status"
require_contains 'live_runner_acceptance_gate_absence_report_write_enabled=0' "$status"
require_contains 'live_runner_acceptance_gate_result_denied_dispatch_review=met' "$status"
require_contains 'live_runner_acceptance_gate_result_passed_preflight=blocked' "$status"
require_contains 'reset_uninstall_live_run_allowed=0' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner acceptance-gate contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$readme"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$readme"
require_contains 'live_runner_acceptance_gate_open=0' "$readme"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$readme"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$readme"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$readme_status"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_acceptance_gate_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner acceptance-gate lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that keeps the live runner closed until passed preflight, evidence, authorization, operator intent, and implementation are all present.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$transfer_status"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$transfer_status"
require_contains 'live_runner_acceptance_gate_open=0' "$transfer_status"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$transfer_status"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$transfer_status"
require_contains 'Current live-runner acceptance-gate lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that keeps the live runner closed until passed preflight, evidence, authorization, operator intent, and implementation are all present.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.' "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE GATE CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_acceptance_gate_contract_status=ok' "$script"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$script"
require_contains 'live_runner_acceptance_gate_open=0' "$script"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$script"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$script"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$script"
require_contains 'live_runner_acceptance_gate_result_no_dispatch_until_open=met' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE GATE CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_acceptance_gate_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1'
require_output_contains "$output" 'live_runner_acceptance_gate_contract_decision=dispatch-blocked-missing-passed-preflight-evidence-and-authorization'
require_output_contains "$output" 'live_runner_acceptance_gate_present=1'
require_output_contains "$output" 'live_runner_acceptance_gate_open=0'
require_output_contains "$output" 'live_runner_acceptance_gate_closed=1'
require_output_contains "$output" 'live_runner_acceptance_gate_acceptance_granted=0'
require_output_contains "$output" 'live_runner_acceptance_gate_dispatch_allowed=0'
require_output_contains "$output" 'live_runner_acceptance_gate_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_gate_dispatch_performed=0'
require_output_contains "$output" 'live_runner_acceptance_gate_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_gate_receipt_write_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_gate_absence_report_write_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_review_dispatch_denied=1'
require_output_contains "$output" 'live_runner_denied_dispatch_review_dispatch_enabled=0'
require_output_contains "$output" 'live_execution_preflight_passed=0'
require_output_contains "$output" 'evidence_bundle_complete=0'
require_output_contains "$output" 'effect_authorization_open=0'
require_output_contains "$output" 'reset_uninstall_effect_authorized=0'
require_output_contains "$output" 'operator_reset_uninstall_intent_evidence_present=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_gate_result_denied_dispatch_review=met'
require_output_contains "$output" 'live_runner_acceptance_gate_result_passed_preflight=blocked'
require_output_contains "$output" 'live_runner_acceptance_gate_result_no_dispatch_until_open=met'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract'

require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract' "$review_script"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.' "$review_doc"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-acceptance-gate-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh

printf 'macos_reset_uninstall_live_runner_acceptance_gate_contract: ok\n'
