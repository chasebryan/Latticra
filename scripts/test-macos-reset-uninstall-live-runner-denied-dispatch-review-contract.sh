#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner denied-dispatch review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner denied-dispatch review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner denied-dispatch review contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner denied-dispatch review contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
transcript_script='scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh'
transcript_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$readme"
require_file "$readme_status"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$transcript_script"
require_file "$transcript_doc"

require_contains 'Status: no-effect macOS reset/uninstall live-runner denied-dispatch review contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_contract_state=reviewed-no-effect' "$doc"
require_contains 'live_runner_denied_dispatch_review_contract_decision=denial-review-retains-zero-dispatch' "$doc"
require_contains 'live_runner_denied_dispatch_review_stdout_only=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_file_write_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_denial_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_denial_reason_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_performed=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_deletion_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_effect_authorized=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_source_contract=macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract' "$doc"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_state=recorded-no-effect' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_decision=dispatch-denied-no-effects-recorded' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_dispatch_denied=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_dispatch_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_file_write_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_transcript_denial_reason=failed-preflight-and-denied-interface' "$doc"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$doc"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$doc"
require_contains 'live_runner_noop_prototype_dispatch_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_deletion_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_no_effects_performed=1' "$doc"
require_contains 'macos_reset_uninstall_live_runner_interface_contract_present=1' "$doc"
require_contains 'live_runner_interface_contract_state=defined-no-effect' "$doc"
require_contains 'live_runner_interface_preflight_passed=0' "$doc"
require_contains 'live_runner_interface_denial_path_active=1' "$doc"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$doc"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$doc"
require_contains 'live_execution_preflight_passed=0' "$doc"
require_contains 'live_runner_denied_dispatch_review_schema_version=macos-reset-uninstall-live-runner-denied-dispatch-review/1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_denied_dispatch_transcript=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_dispatch_denied=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_denial_reason=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_review_only=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_requires_no_deletion=1' "$doc"
require_contains 'live_runner_denied_dispatch_review_result_denied_dispatch_transcript=met' "$doc"
require_contains 'live_runner_denied_dispatch_review_result_no_dispatch=met' "$doc"
require_contains 'live_runner_denied_dispatch_review_result_no_deletion=met' "$doc"
require_contains 'live_runner_denied_dispatch_review_entry_2=dispatch_denial_recorded' "$doc"
require_contains 'live_runner_denied_dispatch_review_entry_3=denial_reason_reviewed' "$doc"
require_contains 'live_runner_denied_dispatch_review_entry_5=acceptance_gate_required' "$doc"
require_contains 'live_runner_denied_dispatch_review_phase_2_status=review-only' "$doc"
require_contains 'live_runner_denied_dispatch_review_phase_3_status=blocked-no-effect' "$doc"
require_contains 'live_runner_denied_dispatch_review_phase_4_status=future-gate-only' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.' "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner denied-dispatch review contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_guard_present=1' "$status"
require_contains 'live_runner_denied_dispatch_review_contract_state=reviewed-no-effect' "$status"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$status"
require_contains 'live_runner_denied_dispatch_review_stdout_only=1' "$status"
require_contains 'live_runner_denied_dispatch_review_file_write_enabled=0' "$status"
require_contains 'live_runner_denied_dispatch_review_result_no_dispatch=met' "$status"
require_contains 'live_runner_denied_dispatch_review_result_no_deletion=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner denied-dispatch review contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$readme"
require_contains 'live_runner_denied_dispatch_review_contract_state=reviewed-no-effect' "$readme"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$readme"
require_contains 'live_runner_denied_dispatch_review_stdout_only=1' "$readme"
require_contains 'live_runner_denied_dispatch_review_file_write_enabled=0' "$readme"
require_contains 'live_runner_denied_dispatch_review_dispatch_enabled=0' "$readme"
require_contains 'live_runner_denied_dispatch_review_deletion_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$readme_status"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_denied_dispatch_review_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner denied-dispatch review lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1' "$transfer_status"
require_contains 'live_runner_denied_dispatch_review_contract_state=reviewed-no-effect' "$transfer_status"
require_contains 'live_runner_denied_dispatch_review_stdout_only=1' "$transfer_status"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$transfer_status"
require_contains 'Current live-runner denied-dispatch review lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.' "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER DENIED DISPATCH REVIEW CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_denied_dispatch_review_contract_status=ok' "$script"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$script"
require_contains 'live_runner_denied_dispatch_review_dispatch_enabled=0' "$script"
require_contains 'live_runner_denied_dispatch_review_file_write_enabled=0' "$script"
require_contains 'live_runner_denied_dispatch_review_result_no_dispatch=met' "$script"
require_contains 'live_runner_denied_dispatch_review_result_no_deletion=met' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER DENIED DISPATCH REVIEW CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_denied_dispatch_review_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1'
require_output_contains "$output" 'live_runner_denied_dispatch_review_contract_decision=denial-review-retains-zero-dispatch'
require_output_contains "$output" 'live_runner_denied_dispatch_review_dispatch_denied=1'
require_output_contains "$output" 'live_runner_denied_dispatch_review_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_review_dispatch_performed=0'
require_output_contains "$output" 'live_runner_denied_dispatch_review_stdout_only=1'
require_output_contains "$output" 'live_runner_denied_dispatch_review_file_write_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_review_transcript_dispatch_denied=1'
require_output_contains "$output" 'live_runner_denied_dispatch_review_transcript_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_noop_prototype_denial_path_exercised=1'
require_output_contains "$output" 'live_runner_noop_prototype_dispatch_enabled=0'
require_output_contains "$output" 'live_execution_preflight_passed=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_review_result_no_dispatch=met'
require_output_contains "$output" 'live_runner_denied_dispatch_review_result_no_deletion=met'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract'

require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract' "$transcript_script"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.' "$transcript_doc"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh

printf 'macos_reset_uninstall_live_runner_denied_dispatch_review_contract: ok\n'
