#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner no-op prototype contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner no-op prototype contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner no-op prototype contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner no-op prototype contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-noop-prototype-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
interface_script='scripts/macos-reset-uninstall-live-runner-interface-contract.sh'
makefile='Makefile'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$readme"
require_file "$readme_status"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$interface_script"
require_file "$makefile"

require_contains 'Status: no-effect macOS reset/uninstall live-runner no-op prototype contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$doc"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$doc"
require_contains 'live_runner_noop_prototype_contract_decision=denied-interface-path-only' "$doc"
require_contains 'live_runner_noop_prototype_invocation_simulated=1' "$doc"
require_contains 'live_runner_noop_prototype_stdout_only=1' "$doc"
require_contains 'live_runner_noop_prototype_denial_path_exercised=1' "$doc"
require_contains 'live_runner_noop_prototype_dispatch_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_runner_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_deletion_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_receipt_write_enabled=0' "$doc"
require_contains 'live_runner_noop_prototype_absence_report_write_enabled=0' "$doc"
require_contains 'macos_reset_uninstall_live_runner_interface_contract_present=1' "$doc"
require_contains 'live_runner_interface_contract_decision=denied-current-preflight-not-passed' "$doc"
require_contains 'live_runner_noop_prototype_requires_denied_interface_path=1' "$doc"
require_contains 'live_runner_noop_prototype_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_noop_prototype_result_no_dispatch=met' "$doc"
require_contains 'live_runner_noop_prototype_result_no_deletion=met' "$doc"
require_contains 'live_runner_noop_prototype_phase_4_status=blocked-no-effect' "$doc"
require_contains 'live_runner_noop_prototype_phase_5_status=stdout-only' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"

require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_guard_present=1' "$status"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$status"
require_contains 'live_runner_noop_prototype_contract_decision=denied-interface-path-only' "$status"
require_contains 'live_runner_noop_prototype_stdout_only=1' "$status"
require_contains 'live_runner_noop_prototype_phase_5_status=stdout-only' "$status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that requires passed preflight, complete evidence, and explicit effect authorization before dispatch.' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner no-op prototype contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$readme"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$readme"
require_contains 'live_runner_noop_prototype_invocation_simulated=1' "$readme"
require_contains 'live_runner_noop_prototype_stdout_only=1' "$readme"
require_contains 'live_runner_noop_prototype_dispatch_enabled=0' "$readme"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_command_documented=1' "$readme_status"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$readme_status"
require_contains 'stage_4_macos_reset_uninstall_live_runner_noop_prototype_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT.md' "$transfer_plan"
require_contains 'Current live-runner no-op prototype lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that requires passed preflight, complete evidence, and explicit effect authorization before dispatch.' "$transfer_plan"
require_contains 'macos_reset_uninstall_live_runner_noop_prototype_contract_present=1' "$transfer_status"
require_contains 'live_runner_noop_prototype_contract_state=executed-no-effect' "$transfer_status"
require_contains 'live_runner_noop_prototype_stdout_only=1' "$transfer_status"
require_contains 'Current live-runner no-op prototype lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-gate contract that requires passed preflight, complete evidence, and explicit effect authorization before dispatch.' "$transfer_status"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-gate-contract' "$interface_script"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER NOOP PROTOTYPE CONTRACT' "$script"
require_contains 'live_runner_noop_prototype_runner_enabled=0' "$script"
require_contains 'live_runner_noop_prototype_requires_no_dispatch=1' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-gate-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'reset_uninstall_live_runner_noop_prototype_contract_status=ok'
require_output_contains "$output" 'live_runner_noop_prototype_contract_decision=denied-interface-path-only'
require_output_contains "$output" 'live_runner_noop_prototype_denial_path_exercised=1'
require_output_contains "$output" 'live_runner_noop_prototype_stdout_only=1'
require_output_contains "$output" 'live_runner_noop_prototype_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_noop_prototype_deletion_enabled=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-gate-contract'

require_contains 'macos-reset-uninstall-live-runner-noop-prototype:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh' "$makefile"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-interface-contract.sh

printf 'macos_reset_uninstall_live_runner_noop_prototype_contract: ok\n'
