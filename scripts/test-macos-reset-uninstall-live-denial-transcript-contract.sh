#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-denial transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-denial transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-denial transcript contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-denial transcript contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-denial-transcript-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-denial-transcript-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
preflight_doc='docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md'
preflight_status='docs/status/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT_STATUS.md'
preflight_script='scripts/macos-reset-uninstall-live-execution-preflight-contract.sh'
makefile='Makefile'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$readme"
require_file "$readme_status"
require_file "$preflight_doc"
require_file "$preflight_status"
require_file "$preflight_script"
require_file "$makefile"

require_contains 'Status: no-effect macOS reset/uninstall live-denial transcript contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-denial-transcript-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$doc"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$doc"
require_contains 'live_denial_transcript_contract_decision=denied-by-preflight-block' "$doc"
require_contains 'live_denial_transcript_stdout_only=1' "$doc"
require_contains 'live_denial_transcript_file_write_enabled=0' "$doc"
require_contains 'live_denial_transcript_receipt_write_enabled=0' "$doc"
require_contains 'live_denial_transcript_absence_report_write_enabled=0' "$doc"
require_contains 'live_denial_transcript_preflight_present=1' "$doc"
require_contains 'live_denial_transcript_preflight_passed=0' "$doc"
require_contains 'live_denial_transcript_denial_reason=missing-complete-evidence-bundle-and-effect-authorization' "$doc"
require_contains 'macos_reset_uninstall_live_execution_preflight_contract_present=1' "$doc"
require_contains 'live_execution_preflight_contract_state=closed-no-effect' "$doc"
require_contains 'live_execution_preflight_passed=0' "$doc"
require_contains 'live_execution_preflight_blocking=1' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$doc"
require_contains 'live_denial_transcript_requires_preflight_denial=1' "$doc"
require_contains 'live_denial_transcript_requires_no_deletion=1' "$doc"
require_contains 'live_denial_transcript_result_stdout_only=met' "$doc"
require_contains 'live_denial_transcript_entry_7=no_effects_performed' "$doc"
require_contains 'live_denial_transcript_phase_4_status=disabled-until-interface-contract' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract: ok' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$doc"

require_contains 'Status: no-effect reset/uninstall live-denial transcript contract status' "$status"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_guard_present=1' "$status"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$status"
require_contains 'live_denial_transcript_recorded=1' "$status"
require_contains 'live_denial_transcript_stdout_only=1' "$status"
require_contains 'live_denial_transcript_file_write_enabled=0' "$status"
require_contains 'live_denial_transcript_preflight_passed=0' "$status"
require_contains 'live_denial_transcript_requires_no_deletion=1' "$status"
require_contains 'live_denial_transcript_phase_4_status=disabled-until-interface-contract' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'live reset execution' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-denial transcript contract status' "$index"

require_contains 'stage_4_macos_reset_uninstall_live_denial_transcript_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-denial-transcript-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$transfer_status"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$transfer_status"
require_contains 'live_denial_transcript_recorded=1' "$transfer_status"
require_contains 'live_denial_transcript_stdout_only=1' "$transfer_status"
require_contains 'live_denial_transcript_file_write_enabled=0' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$transfer_status"

require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-live-denial-transcript-contract.sh' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$readme"
require_contains 'live_denial_transcript_recorded=1' "$readme"
require_contains 'live_denial_transcript_stdout_only=1' "$readme"
require_contains 'live_denial_transcript_file_write_enabled=0' "$readme"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$readme_status"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$readme_status"
require_contains 'live_denial_transcript_recorded=1' "$readme_status"
require_contains 'live_denial_transcript_stdout_only=1' "$readme_status"
require_contains 'live_denial_transcript_file_write_enabled=0' "$readme_status"

require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$preflight_doc"
require_contains 'Add a macOS reset/uninstall live-runner no-op prototype contract' "$preflight_status"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract' "$preflight_script"
require_contains 'macos-reset-uninstall-live-denial-transcript:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-denial-transcript-contract.sh' "$makefile"

require_contains 'MACOS RESET UNINSTALL LIVE DENIAL TRANSCRIPT CONTRACT' "$script"
require_contains 'reset_uninstall_live_denial_transcript_contract_status=ok' "$script"
require_contains 'macos_reset_uninstall_live_denial_transcript_contract_present=1' "$script"
require_contains 'live_denial_transcript_contract_state=recorded-no-effect' "$script"
require_contains 'live_denial_transcript_contract_decision=denied-by-preflight-block' "$script"
require_contains 'live_denial_transcript_stdout_only=1' "$script"
require_contains 'live_denial_transcript_file_write_enabled=0' "$script"
require_contains 'live_denial_transcript_receipt_write_enabled=0' "$script"
require_contains 'live_denial_transcript_absence_report_write_enabled=0' "$script"
require_contains 'live_denial_transcript_preflight_passed=0' "$script"
require_contains 'live_execution_preflight_passed=0' "$script"
require_contains 'reset_uninstall_live_run_allowed=0' "$script"
require_contains 'reset_uninstall_deletion_enabled=0' "$script"
require_contains 'effect_authorization_open=0' "$script"
require_contains 'reset_uninstall_effect_authorized=0' "$script"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$script"
require_contains 'live_denial_transcript_requires_preflight_denial=1' "$script"
require_contains 'live_denial_transcript_condition_stdout_only=required' "$script"
require_contains 'live_denial_transcript_result_no_deletion=met' "$script"
require_contains 'live_denial_transcript_result_no_network=met' "$script"
require_contains 'live_denial_transcript_result_no_root=met' "$script"
require_contains 'live_denial_transcript_phase_4_status=disabled-until-interface-contract' "$script"
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
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE DENIAL TRANSCRIPT CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_denial_transcript_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_denial_transcript_contract_present=1'
require_output_contains "$output" 'live_denial_transcript_contract_decision=denied-by-preflight-block'
require_output_contains "$output" 'live_denial_transcript_recorded=1'
require_output_contains "$output" 'live_denial_transcript_stdout_only=1'
require_output_contains "$output" 'live_denial_transcript_file_write_enabled=0'
require_output_contains "$output" 'live_denial_transcript_preflight_passed=0'
require_output_contains "$output" 'live_execution_preflight_passed=0'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'live_denial_transcript_result_no_deletion=met'
require_output_contains "$output" 'live_denial_transcript_phase_4_status=disabled-until-interface-contract'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-denial-transcript-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-execution-preflight-contract.sh

printf 'macos_reset_uninstall_live_denial_transcript_contract: ok\n'
