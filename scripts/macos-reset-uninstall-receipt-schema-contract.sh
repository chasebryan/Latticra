#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-reset-uninstall-receipt-schema-contract.sh

Emits the no-effect macOS reset/uninstall receipt-schema contract. It defines
the future reset/uninstall receipt shape for receipts stored outside the removed
prefix, but it does not write receipts, delete files, mutate host state, open
the network, or claim reset/uninstall implementation.
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
MACOS RESET UNINSTALL RECEIPT SCHEMA CONTRACT

reset_uninstall_receipt_schema_contract_status=ok
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
effect_authorization_contract_state=closed-no-effect
effect_authorization_open=0
reset_uninstall_effect_authorized=0
operator_intent_contract_state=defined-no-effect
operator_intent_evidence_written=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
receipt_schema_contract_state=defined-no-effect
receipt_schema_contract_decision=contract-defined-receipt-not-written
receipt_schema_required=1
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
receipt_schema_evidence_present=0
reset_receipt_write_performed=0
receipt_write_performed=0
receipt_written=0
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_verification_transcript_contract_present=1
reset_uninstall_dry_run_evidence_present=0
absence_report_evidence_present=0
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
reset_receipt_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/reset-uninstall-receipt.json
absence_report_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/absence-report.txt
receipt_must_be_outside_removed_prefix=1
removed_prefix_must_not_contain_receipt=1
receipt_format=json
receipt_schema_version=macos-reset-uninstall-receipt/1
receipt_digest_algorithm=sha256
receipt_operation_values=reset,uninstall
receipt_field_schema_version_required=1
receipt_field_operation_required=1
receipt_field_host_identity_required=1
receipt_field_architecture_required=1
receipt_field_started_at_required=1
receipt_field_completed_at_required=1
receipt_field_planner_transcript_digest_required=1
receipt_field_live_classifier_digest_required=1
receipt_field_absence_report_path_required=1
receipt_field_target_actions_required=1
receipt_field_removed_managed_targets_required=1
receipt_field_preserved_unmanaged_targets_required=1
receipt_field_authority_denials_required=1
receipt_field_no_network_required=1
receipt_field_no_root_required=1
receipt_schema_phase_1=consume_dry_run_planner_transcript
receipt_schema_phase_2=consume_absence_report_contract
receipt_schema_phase_3=validate_outside_removed_prefix_path
receipt_schema_phase_4=record_target_action_summary
receipt_schema_phase_5=record_authority_denials
receipt_schema_phase_6=write_reset_uninstall_receipt
receipt_schema_phase_1_status=contract-only
receipt_schema_phase_2_status=contract-only
receipt_schema_phase_3_status=contract-only
receipt_schema_phase_4_status=contract-only
receipt_schema_phase_5_status=contract-only
receipt_schema_phase_6_status=disabled
managed_marker_required=1
unmanaged_target_preservation_required=1
receipt_outside_removed_prefix_required=1
absence_report_required=1
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
next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract
REPORT
