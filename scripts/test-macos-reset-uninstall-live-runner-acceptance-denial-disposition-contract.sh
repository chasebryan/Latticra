#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-runner acceptance-denial disposition contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.yml'
index='docs/status/README.md'
readme='README.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
review_script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh'
review_doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md'
makefile='Makefile'

for file in "$doc" "$status" "$script" "$workflow" "$index" "$readme" "$readme_status" "$transfer_plan" "$transfer_status" "$review_script" "$review_doc" "$makefile"; do
  require_file "$file"
done

require_contains 'Status: no-effect macOS reset/uninstall live-runner acceptance-denial disposition contract' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh' "$doc"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_contract_decision=closed-gate-denial-disposed-no-dispatch' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_recorded=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_stdout_only=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_file_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_record_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_source_contract=macos-reset-uninstall-live-runner-acceptance-denial-review-contract' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_review_present=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_acceptance_gate_open=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_acceptance_gate_closed=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_allowed=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_performed=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_deletion_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_receipt_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_absence_report_write_enabled=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_applied=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_opens_dispatch=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_releases_runner=0' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_schema_version=macos-reset-uninstall-live-runner-acceptance-denial-disposition/1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_requires_acceptance_denial_review=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_requires_no_dispatch=1' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_result_no_dispatch=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_result_no_deletion=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_result_review_handoff=met' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_entry_6=disposition_review_required' "$doc"
require_contains 'live_runner_acceptance_denial_disposition_phase_4=handoff_to_acceptance_denial_disposition_review' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition contract that records the reviewed closed-gate denial as a no-effect disposition without opening dispatch.' "$doc"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$doc"

require_contains 'Status: no-effect reset/uninstall live-runner acceptance-denial disposition contract status' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1' "$status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_guard_present=1' "$status"
require_contains 'live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect' "$status"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_performed=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_deletion_enabled=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_applied=0' "$status"
require_contains 'live_runner_acceptance_denial_disposition_result_no_dispatch=met' "$status"
require_contains 'runtime_authority_granted=0' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-runner acceptance-denial disposition contract status' "$index"
require_contains 'sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_stdout_only=1' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_file_write_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$readme"
require_contains 'live_runner_acceptance_denial_disposition_deletion_enabled=0' "$readme"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT.md' "$readme"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_command_documented=1' "$readme_status"
require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1' "$readme_status"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$readme_status"

require_contains 'stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh' "$transfer_plan"
require_contains 'docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT_STATUS.md' "$transfer_plan"
require_contains 'Current live-runner acceptance-denial disposition lane now present' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition contract that records the reviewed closed-gate denial as a no-effect disposition without opening dispatch.' "$transfer_plan"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$transfer_plan"

require_contains 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_stdout_only=1' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_file_write_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$transfer_status"
require_contains 'live_runner_acceptance_denial_disposition_deletion_enabled=0' "$transfer_status"
require_contains 'Current live-runner acceptance-denial disposition lane' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition contract that records the reviewed closed-gate denial as a no-effect disposition without opening dispatch.' "$transfer_status"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$transfer_status"

require_contains 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL DISPOSITION CONTRACT' "$script"
require_contains 'reset_uninstall_live_runner_acceptance_denial_disposition_contract_status=ok' "$script"
require_contains 'live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect' "$script"
require_contains 'live_runner_acceptance_denial_disposition_dispatch_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_disposition_deletion_enabled=0' "$script"
require_contains 'live_runner_acceptance_denial_disposition_result_no_dispatch=met' "$script"
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
require_output_contains "$output" 'MACOS RESET UNINSTALL LIVE RUNNER ACCEPTANCE DENIAL DISPOSITION CONTRACT'
require_output_contains "$output" 'reset_uninstall_live_runner_acceptance_denial_disposition_contract_status=ok'
require_output_contains "$output" 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_contract_decision=closed-gate-denial-disposed-no-dispatch'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_recorded=1'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_acceptance_gate_open=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_dispatch_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_dispatch_performed=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_deletion_enabled=0'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_result_acceptance_denial_review=met'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_result_no_dispatch=met'
require_output_contains "$output" 'live_runner_acceptance_denial_disposition_phase_4=handoff_to_acceptance_denial_disposition_review'
require_output_contains "$output" 'reset_uninstall_live_run_allowed=0'
require_output_contains "$output" 'reset_uninstall_deletion_enabled=0'
require_output_contains "$output" 'file_delete_performed=0'
require_output_contains "$output" 'directory_delete_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract'

require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract' "$review_script"
require_contains 'Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.' "$review_doc"
require_contains 'macos-reset-uninstall-live-runner-acceptance-denial-disposition:' "$makefile"
require_contains 'sh ./scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh' "$makefile"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh' "$workflow"

sh scripts/test-macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh

printf 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract: ok\n'
