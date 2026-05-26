#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner denied-dispatch transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner denied-dispatch transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner denied-dispatch transcript contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner denied-dispatch transcript contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
noop_script='scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$readme"
require_file "$readme_status"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$noop_script"

require_contains 'Status: no-effect macOS reset/uninstall live-runner denied-dispatch transcript contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_contract_state=recorded-no-effect' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_contract_decision=dispatch-denied-no-effects-recorded' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_stdout_only=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_file_write_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_attempted=0' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_enabled=0' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_denial_reason=failed-preflight-and-denied-interface' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_denial_source=macos-reset-uninstall-live-runner-noop-prototype-contract' "$doc"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$doc"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$doc"
require_contains 'live_runner_noop_prototype_contract_decision=denied-interface-path-only' "$doc"
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
require_contains 'live_runner_denied_dispatch_transcript_schema_version=macos-reset-uninstall-live-runner-denied-dispatch-transcript/1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_requires_noop_prototype=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_requires_denied_dispatch=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_requires_no_deletion=1' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_result_denied_dispatch=met' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_result_no_deletion=met' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_entry_4=dispatch_blocked' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_entry_4_status=recorded' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_phase_2_status=stdout-only' "$doc"
require_contains 'live_runner_denied_dispatch_transcript_phase_3_status=blocked-no-effect' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch transcript contract that records the no-op runner denial without enabling deletion.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner denied-dispatch transcript contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_guard_present=1' "$status"
require_contains 'live_runner_denied_dispatch_transcript_contract_state=recorded-no-effect' "$status"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$status"
require_contains 'live_runner_denied_dispatch_transcript_stdout_only=1' "$status"
require_contains 'live_runner_denied_dispatch_transcript_file_write_enabled=0' "$status"
require_contains 'live_runner_denied_dispatch_transcript_result_no_deletion=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner denied-dispatch transcript contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$readme"
require_contains 'live_runner_denied_dispatch_transcript_contract_state=recorded-no-effect' "$readme"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$readme"
require_contains 'live_runner_denied_dispatch_transcript_stdout_only=1' "$readme"
require_contains 'live_runner_denied_dispatch_transcript_file_write_enabled=0' "$readme"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$readme_status"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner denied-dispatch transcript lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch transcript contract that records the no-op runner denial without enabling deletion.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1' "$transfer_status"
require_contains 'live_runner_denied_dispatch_transcript_contract_state=recorded-no-effect' "$transfer_status"
require_contains 'live_runner_denied_dispatch_transcript_stdout_only=1' "$transfer_status"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$transfer_status"
require_contains 'Current live-runner denied-dispatch transcript lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch transcript contract that records the no-op runner denial without enabling deletion.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.' "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER DENIED DISPATCH TRANSCRIPT CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_denied_dispatch_transcript_contract_status=ok' "$script"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_denied=1' "$script"
require_contains 'live_runner_denied_dispatch_transcript_dispatch_enabled=0' "$script"
require_contains 'live_runner_denied_dispatch_transcript_file_write_enabled=0' "$script"
require_contains 'live_runner_denied_dispatch_transcript_result_no_deletion=met' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER DENIED DISPATCH TRANSCRIPT CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_denied_dispatch_transcript_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_contract_decision=dispatch-denied-no-effects-recorded'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_dispatch_denied=1'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_stdout_only=1'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_file_write_enabled=0'
require_output_contains "$output" 'live_runner_noop_prototype_denial_path_exercised=1'
require_output_contains "$output" 'live_runner_noop_prototype_dispatch_enabled=0'
require_output_contains "$output" 'live_execution_preflight_passed=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'live_runner_denied_dispatch_transcript_result_no_deletion=met'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh

printf 'macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract: ok\n'
