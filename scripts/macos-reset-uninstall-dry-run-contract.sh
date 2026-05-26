#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-reset-uninstall-dry-run-contract.sh

Emits the no-effect macOS reset/uninstall dry-run contract for a future
user-local app bundle install. It defines managed-target removal order and
preservation rules, but it does not delete files, write receipts, mutate host
state, or claim reset/uninstall implementation.
USAGE
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage >&2
      exit 64
      ;;
  esac
done

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
UNAME_S=$(uname -s 2>/dev/null || printf 'unknown')
UNAME_M=$(uname -m 2>/dev/null || printf 'unknown')

cat <<REPORT
MACOS RESET UNINSTALL DRY RUN CONTRACT

reset_uninstall_dry_run_contract_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_reset_uninstall_dry_run_contract_present=1
reset_uninstall_dry_run_contract_state=defined-no-effect
reset_uninstall_dry_run_decision=contract-defined-removal-not-performed
reset_uninstall_dry_run_required=1
reset_uninstall_dry_run_evidence_present=0
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
macos_reset_uninstall_live_execution_preflight_contract_present=1
macos_reset_uninstall_live_denial_transcript_contract_present=1
macos_reset_uninstall_live_runner_interface_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_current_preflight_passed=0
live_runner_interface_current_decision=deny
live_runner_interface_dispatch_enabled=0
live_runner_interface_runner_handoff_enabled=0
live_implementation_plan_contract_state=defined-no-effect
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
effect_authorization_open=0
reset_uninstall_effect_authorized=0
operator_intent_contract_state=defined-no-effect
operator_intent_evidence_written=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
absence_report_evidence_present=0
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
commit_user_local_managed_artifacts=0
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
managed_marker_required=1
unmanaged_target_preservation_required=1
receipt_outside_removed_prefix_required=1
absence_report_required=1
reset_phase_1=validate_user_local_targets
reset_phase_2=inspect_managed_markers
reset_phase_3=preserve_unmanaged_targets
reset_phase_4=remove_managed_wrappers
reset_phase_5=remove_managed_app_bundle
reset_phase_6=remove_managed_application_support_prefix
reset_phase_7=write_reset_or_uninstall_receipt_outside_removed_prefix
reset_phase_8=emit_verification_absence_report
reset_phase_1_status=contract-only
reset_phase_2_status=contract-only
reset_phase_3_status=contract-only
reset_phase_4_status=disabled
reset_phase_5_status=disabled
reset_phase_6_status=disabled
reset_phase_7_status=disabled
reset_phase_8_status=not-run
preserve_user_logs=1
preserve_user_caches=1
preserve_shell_profiles=1
preserve_keychain_items=1
preserve_launchagents=1
preserve_login_items=1
preserve_homebrew_files=1
preserve_applications_root=1
preserve_library_root=1
preserve_system_root=1
preserve_usr_local=1
preserve_opt_homebrew=1
managed_wrapper_removal_performed=0
managed_app_bundle_removal_performed=0
managed_application_support_removal_performed=0
reset_receipt_write_performed=0
absence_report_run_performed=0
absence_report_written=0
file_delete_performed=0
directory_delete_performed=0
application_support_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
runtime_authority_granted=0
production_installer_ready=0
next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract
REPORT
