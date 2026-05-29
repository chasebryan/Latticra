#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner acceptance-denial transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial transcript contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner acceptance-denial transcript contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
gate_script='scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh'
gate_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md'
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
require_file "$gate_script"
require_file "$gate_doc"
require_file "$makefile"

require_contains 'Status: no-effect macOS reset/uninstall live-runner acceptance-denial transcript contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_contract_decision=acceptance-gate-closed-no-dispatch-recorded' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_required=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_recorded=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_state=closed-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_runner_handoff_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_receipt_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_absence_report_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_effect_authorized=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_denial_reason=missing-passed-preflight-complete-evidence-effect-authorization-operator-intent-and-implementation' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_denial_source=macos-reset-uninstall-live-runner-acceptance-gate-contract' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$doc"
require_contains 'live_runner_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_result_passed_preflight=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_complete_evidence_bundle=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_effect_authorization=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_no_dispatch_until_open=met' "$doc"
require_contains 'live_runner_denied_dispatch_review_dispatch_denied=1' "$doc"
require_contains 'live_execution_preflight_passed=0' "$doc"
require_contains 'evidence_bundle_complete=0' "$doc"
require_contains 'effect_authorization_open=0' "$doc"
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'reset_uninstall_implementation_present=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_schema_version=macos-reset-uninstall-live-runner-acceptance-denial-transcript/1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_acceptance_gate=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_closed_gate=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_denial_reason=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_no_deletion=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_no_receipt_write=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_requires_no_absence_report_write=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_result_acceptance_gate=met' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_result_closed_gate=met' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_result_no_dispatch=met' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_result_no_deletion=met' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_entry_3=acceptance_inputs_blocked' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_entry_4=dispatch_blocked' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_entry_3_status=recorded' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_phase_2_status=stdout-only' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_phase_3_status=blocked-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_phase_4=handoff_to_acceptance_denial_review' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner acceptance-denial transcript contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_guard_present=1' "$status"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$status"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0' "$status"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_performed=0' "$status"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_transcript_result_no_dispatch=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner acceptance-denial transcript contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_stdout_only=1' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_file_write_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_performed=0' "$readme"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$readme_status"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner acceptance-denial transcript lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_stdout_only=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_file_write_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_performed=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$transfer_status"
require_contains 'Current live-runner acceptance-denial transcript lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL TRANSCRIPT CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_acceptance_denial_transcript_contract_status=ok' "$script"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$script"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0' "$script"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_transcript_result_no_dispatch=met' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

output=$(sh "$script")
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL TRANSCRIPT CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_acceptance_denial_transcript_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_contract_decision=acceptance-gate-closed-no-dispatch-recorded'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_recorded=1'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_dispatch_performed=0'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_result_acceptance_gate=met'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_result_no_dispatch=met'
require_output_contains "$output" 'live_runner_acceptance_gate_result_passed_preflight=blocked'
require_output_contains "$output" 'live_runner_acceptance_gate_result_complete_evidence_bundle=blocked'
require_output_contains "$output" 'live_runner_acceptance_gate_result_effect_authorization=blocked'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract'

require_contains 'live_runner_acceptance_gate_phase_4=handoff_to_acceptance_denial_transcript' "$gate_script"
require_contains 'live_runner_acceptance_gate_phase_4=handoff_to_acceptance_denial_transcript' "$gate_doc"
require_contains 'macos-reset-uninstall-live-runner-acceptance-denial-transcript:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh' "$makefile"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-acceptance-gate-contract.sh

printf 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract: ok\n'
