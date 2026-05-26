#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition closeout audit contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition closeout audit contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition closeout audit contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition closeout audit contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
review_script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract.sh'
review_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_REVIEW_CONTRACT.md'
review_status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_REVIEW_CONTRACT_STATUS.md'
makefile='Makefile'

current_phrase='Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit contract that audits the no-effect closeout without opening dispatch or deletion.'
next_phrase='Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.'

for file in "$doc" "$status" "$script" "$workflow" "$index" "$readme" "$readme_status" "$transfer_plan" "$transfer_status" "$review_script" "$review_doc" "$review_status" "$makefile"; do
  require_file "$file"
done

require_contains 'Status: no-effect macOS reset/uninstall live-runner acceptance-denial disposition closeout audit contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_decision=no-effect-closeout-audit-keeps-dispatch-closed' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_completed=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_source_contract=macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_review_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_review_state=reviewed-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_review_closeout_opened=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_state=closed-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audited=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_applied=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_opens_dispatch=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_audited=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_audit_review_opened=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_schema_version=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit/1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_requires_acceptance_denial_disposition_review=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_requires_no_effect_closeout=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_requires_no_deletion=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_requires_audit_review_handoff=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_result_no_dispatch=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_result_no_deletion=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_result_audit_review_handoff=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_entry_6=audit_review_required' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_phase_4=handoff_to_acceptance_denial_disposition_closeout_audit_review' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains "$current_phrase" "$doc"
require_contains "$next_phrase" "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner acceptance-denial disposition closeout audit contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_guard_present=1' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_performed=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_audit_review_opened=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_result_no_dispatch=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner acceptance-denial disposition closeout audit contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_stdout_only=1' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_file_write_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1' "$readme_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner acceptance-denial disposition closeout audit lane now present' "$transfer_plan"
require_contains "$current_phrase" "$transfer_plan"
require_contains "$next_phrase" "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_stdout_only=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_file_write_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0' "$transfer_status"
require_contains 'Current live-runner acceptance-denial disposition closeout audit lane' "$transfer_status"
require_contains "$current_phrase" "$transfer_status"
require_contains "$next_phrase" "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL DISPOSITION CLOSEOUT AUDIT CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_status=ok' "$script"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout' "$script"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_disposition_closeout_audit_result_no_dispatch=met' "$script"
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
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL DISPOSITION CLOSEOUT AUDIT CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_contract_decision=no-effect-closeout-audit-keeps-dispatch-closed'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audited=1'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_dispatch_performed=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_audit_review_opened=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_result_no_dispatch=met'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_closeout_audit_phase_4=handoff_to_acceptance_denial_disposition_closeout_audit_review'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract'

require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract' "$review_script"
require_contains "$next_phrase" "$review_doc"
require_contains "$next_phrase" "$review_status"
require_contains 'macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh' "$makefile"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract.sh

printf 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract: ok\n'
