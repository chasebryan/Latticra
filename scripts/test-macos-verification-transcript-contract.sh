#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos verification transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos verification transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos verification transcript contract: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos verification transcript contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md'
status='docs/status/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md'
script='scripts/macos-verification-transcript-contract.sh'
workflow='.github/workflows/macos-verification-transcript-contract.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
commit_status='docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md'
reset_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$commit_status"
require_file "$reset_status"

require_contains 'Status: no-effect macOS verification transcript contract' "$doc"
require_contains 'sh scripts/macos-verification-transcript-contract.sh' "$doc"
require_contains 'macos_verification_transcript_contract_present=1' "$doc"
require_contains 'verification_transcript_contract_state=defined-no-effect' "$doc"
require_contains 'verification_transcript_contract_decision=contract-defined-evidence-not-present' "$doc"
require_contains 'verification_transcript_evidence_present=0' "$doc"
require_contains 'macos_install_verified=0' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'app_bundle_expected=$HOME/Applications/Latticra Panel.app' "$doc"
require_contains 'transcript_line_host_identity_required=1' "$doc"
require_contains 'transcript_line_commit_gate_required=1' "$doc"
require_contains 'transcript_line_reset_uninstall_dry_run_required=1' "$doc"
require_contains 'managed_app_bundle_present_required=1' "$doc"
require_contains 'commit_gate_closed_until_evidence_required=1' "$doc"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$doc"
require_contains 'verification_transcript_run_performed=0' "$doc"
require_contains 'verification_transcript_written=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'macos_verification_transcript_contract: ok' "$doc"

require_contains 'Status: no-effect verification transcript contract status' "$status"
require_contains 'macos_verification_transcript_contract_present=1' "$status"
require_contains 'macos_verification_transcript_contract_guard_present=1' "$status"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$status"
require_contains 'verification_transcript_contract_state=defined-no-effect' "$status"
require_contains 'verification_transcript_evidence_present=0' "$status"
require_contains 'macos_install_verified=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'runtime_authority_granted=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$reset_status"
require_contains 'sh scripts/test-macos-verification-transcript-contract.sh' "$status"
require_contains 'macos_verification_transcript_contract: ok' "$status"

require_contains 'MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md' "$index"
require_contains 'macOS verification transcript contract status' "$index"
require_contains 'stage_4_user_local_verification_transcript_contract=present' "$transfer_plan"
require_contains 'stage_4_user_local_verification_transcript_evidence=future' "$transfer_plan"
require_contains 'docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'scripts/macos-verification-transcript-contract.sh' "$transfer_plan"
require_contains 'macos_verification_transcript_contract_present=1' "$transfer_status"
require_contains 'macos_verification_transcript_evidence_present=0' "$transfer_status"
require_contains 'macos_verification_transcript_contract_present=1' "$commit_status"

require_contains 'verification_transcript_contract_status=ok' "$script"
require_contains 'macos_verification_transcript_contract_present=1' "$script"
require_contains 'verification_transcript_evidence_present=0' "$script"
require_contains 'macos_reset_uninstall_dry_run_contract_present=1' "$script"
require_contains 'macos_reset_uninstall_absence_report_contract_present=1' "$script"
require_contains 'absence_report_evidence_present=0' "$script"
require_contains 'macos_install_verified=0' "$script"
require_contains 'commit_user_local_managed_artifacts=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

output=$(sh "$script")

require_output_contains "$output" 'MACOS VERIFICATION TRANSCRIPT CONTRACT'
require_output_contains "$output" 'verification_transcript_contract_status=ok'
require_output_contains "$output" 'macos_verification_transcript_contract_present=1'
require_output_contains "$output" 'verification_transcript_evidence_present=0'
require_output_contains "$output" 'macos_install_verified=0'
require_output_contains "$output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$output" 'managed_write_implementation_present=0'
require_output_contains "$output" 'reset_uninstall_implementation_present=0'
require_output_contains "$output" 'app_bundle_expected='
require_output_contains "$output" 'transcript_line_host_identity_required=1'
require_output_contains "$output" 'transcript_line_commit_gate_required=1'
require_output_contains "$output" 'commit_gate_closed_until_evidence_required=1'
require_output_contains "$output" 'macos_reset_uninstall_dry_run_contract_present=1'
require_output_contains "$output" 'macos_reset_uninstall_absence_report_contract_present=1'
require_output_contains "$output" 'absence_report_evidence_present=0'
require_output_contains "$output" 'verification_transcript_run_performed=0'
require_output_contains "$output" 'verification_transcript_written=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-macos-verification-transcript-contract.sh' "$workflow"

printf 'macos_verification_transcript_contract: ok\n'
