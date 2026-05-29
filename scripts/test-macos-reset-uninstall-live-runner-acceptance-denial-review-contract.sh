#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner acceptance-denial review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial review contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner acceptance-denial review contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
transcript_script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh'
transcript_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md'
makefile='Makefile'

review_phrase='Add a macOS reset/uninstall live-runner acceptance-denial review contract that reviews the closed gate transcript without enabling dispatch or deletion.'
next_phrase='The next lane should add a disposition contract so the reviewed closed-gate denial has a recorded no-effect disposition before any future dispatch work is reconsidered.'
next_lane_phrase='Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.'

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
require_file "$makefile"

require_contains 'Status: no-effect macOS reset/uninstall live-runner acceptance-denial review contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_contract_state=reviewed-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_review_contract_decision=closed-gate-review-retains-zero-dispatch' "$doc"
require_contains 'live_runner_acceptance_denial_review_required=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_completed=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_recorded=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_review_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_scope=review-closed-gate-transcript-only' "$doc"
require_contains 'live_runner_acceptance_denial_review_source_contract=macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract' "$doc"
require_contains 'live_runner_acceptance_denial_review_closed_gate_transcript_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_closed_gate_reviewed=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_denial_reason_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_denial_reason_reviewed=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_dispatch_reviewed=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_runner_handoff_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_receipt_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_absence_report_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_effect=none' "$doc"
require_contains 'live_runner_acceptance_denial_review_effect_authorized=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_effect_boundary_preserved=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_disposition_opened=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_result=closed-gate-boundary-preserved' "$doc"
require_contains 'reset_uninstall_live_run_allowed=0' "$doc"
require_contains 'reset_uninstall_deletion_enabled=0' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_contract_decision=acceptance-gate-closed-no-dispatch-recorded' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_recorded=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_transcript_denial_reason=missing-passed-preflight-complete-evidence-effect-authorization-operator-intent-and-implementation' "$doc"
require_contains 'live_runner_acceptance_denial_review_transcript_state=recorded-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_review_transcript_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_transcript_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_transcript_deletion_enabled=0' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_gate_contract_state=closed-no-effect' "$doc"
require_contains 'live_runner_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_gate_acceptance_granted=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_gate_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_gate_result_passed_preflight=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_complete_evidence_bundle=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_effect_authorization=blocked' "$doc"
require_contains 'live_runner_acceptance_gate_result_no_dispatch_until_open=met' "$doc"
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
require_contains 'operator_reset_uninstall_intent_evidence_present=0' "$doc"
require_contains 'reset_uninstall_implementation_present=0' "$doc"
require_contains 'live_runner_acceptance_denial_review_schema_version=macos-reset-uninstall-live-runner-acceptance-denial-review/1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_acceptance_denial_transcript=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_closed_gate=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_denial_reason=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_review_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_effects=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_deletion=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_receipt_write=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_absence_report_write=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_network=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_no_root=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_requires_disposition_handoff=1' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_acceptance_denial_transcript=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_closed_gate=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_denial_reason=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_review_only=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_effects=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_dispatch=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_deletion=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_receipt_write=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_absence_report_write=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_network=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_no_root=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_result_disposition_handoff=met' "$doc"
require_contains 'live_runner_acceptance_denial_review_entry_3=denial_reason_reviewed' "$doc"
require_contains 'live_runner_acceptance_denial_review_entry_5=no_effects_confirmed' "$doc"
require_contains 'live_runner_acceptance_denial_review_entry_6=disposition_required' "$doc"
require_contains 'live_runner_acceptance_denial_review_phase_2_status=review-only' "$doc"
require_contains 'live_runner_acceptance_denial_review_phase_3_status=blocked-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_review_phase_4=handoff_to_acceptance_denial_disposition' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains "$review_phrase" "$doc"
require_contains "$next_phrase" "$doc"
require_contains "$next_lane_phrase" "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner acceptance-denial review contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_guard_present=1' "$status"
require_contains 'live_runner_acceptance_denial_review_contract_state=reviewed-no-effect' "$status"
require_contains 'live_runner_acceptance_denial_review_contract_decision=closed-gate-review-retains-zero-dispatch' "$status"
require_contains 'live_runner_acceptance_denial_review_completed=1' "$status"
require_contains 'live_runner_acceptance_denial_review_closed_gate_reviewed=1' "$status"
require_contains 'live_runner_acceptance_denial_review_denial_reason_reviewed=1' "$status"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_open=0' "$status"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_review_dispatch_performed=0' "$status"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_review_disposition_opened=0' "$status"
require_contains 'live_runner_acceptance_denial_review_result_no_dispatch=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner acceptance-denial review contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1' "$readme"
require_contains 'live_runner_acceptance_denial_review_contract_state=reviewed-no-effect' "$readme"
require_contains 'live_runner_acceptance_denial_review_stdout_only=1' "$readme"
require_contains 'live_runner_acceptance_denial_review_file_write_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_review_closed_gate_reviewed=1' "$readme"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_open=0' "$readme"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_review_dispatch_performed=0' "$readme"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_review_disposition_opened=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1' "$readme_status"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$readme_status"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_acceptance_denial_review_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner acceptance-denial review lane now present' "$transfer_plan"
require_contains "$review_phrase" "$transfer_plan"
require_contains "$next_lane_phrase" "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_contract_state=reviewed-no-effect' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_stdout_only=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_file_write_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_closed_gate_reviewed=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_open=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_dispatch_performed=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_review_disposition_opened=0' "$transfer_status"
require_contains 'Current live-runner acceptance-denial review lane' "$transfer_status"
require_contains "$review_phrase" "$transfer_status"
require_contains "$next_lane_phrase" "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL REVIEW CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_acceptance_denial_review_contract_status=ok' "$script"
require_contains 'live_runner_acceptance_denial_review_contract_state=reviewed-no-effect' "$script"
require_contains 'live_runner_acceptance_denial_review_closed_gate_reviewed=1' "$script"
require_contains 'live_runner_acceptance_denial_review_acceptance_gate_open=0' "$script"
require_contains 'live_runner_acceptance_denial_review_dispatch_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_review_dispatch_performed=0' "$script"
require_contains 'live_runner_acceptance_denial_review_deletion_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_review_result_no_dispatch=met' "$script"
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
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL REVIEW CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_acceptance_denial_review_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1'
require_output_contains "$output" 'live_runner_acceptance_denial_review_contract_decision=closed-gate-review-retains-zero-dispatch'
require_output_contains "$output" 'live_runner_acceptance_denial_review_completed=1'
require_output_contains "$output" 'live_runner_acceptance_denial_review_closed_gate_reviewed=1'
require_output_contains "$output" 'live_runner_acceptance_denial_review_acceptance_gate_open=0'
require_output_contains "$output" 'live_runner_acceptance_denial_review_dispatch_reviewed=1'
require_output_contains "$output" 'live_runner_acceptance_denial_review_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_review_dispatch_performed=0'
require_output_contains "$output" 'live_runner_acceptance_denial_review_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_review_disposition_opened=0'
require_output_contains "$output" 'live_runner_acceptance_denial_review_result_closed_gate=met'
require_output_contains "$output" 'live_runner_acceptance_denial_review_result_no_dispatch=met'
require_output_contains "$output" 'live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect'
require_output_contains "$output" 'live_runner_acceptance_gate_open=0'
require_output_contains "$output" 'live_runner_acceptance_gate_result_passed_preflight=blocked'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract'

require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract' "$transcript_script"
require_contains "$next_lane_phrase" "$transcript_doc"
require_contains 'macos-reset-uninstall-live-runner-acceptance-denial-review:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh' "$makefile"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh

printf 'macos_reset_uninstall_live_runner_acceptance_denial_review_contract: ok\n'
