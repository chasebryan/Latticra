#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-commit-gate-contract.sh

Emits the closed macOS commit-gate contract for the future user-local app
bundle writer. It does not create app bundles, write files, mutate host state,
or enable commit_user_local_managed_artifacts.
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
MACOS COMMIT GATE CONTRACT

commit_gate_contract_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_commit_gate_contract_present=1
commit_gate_state=closed
commit_gate_decision=blocked-missing-managed-write-implementation
commit_user_local_managed_artifacts=0
macos_app_bundle_commit_capable_writer_present=0
managed_write_implementation_present=0
reset_uninstall_implementation_present=0
macos_verification_transcript_contract_present=1
verification_transcript_contract_present=1
verification_transcript_evidence_present=0
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
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
reset_uninstall_dry_run_evidence_present=0
absence_report_evidence_present=0
candidate_integration_required=1
candidate_flow_ready_required=1
candidate_flow_ready_observed=not-evaluated
operator_explicit_commit_intent_required=1
operator_explicit_commit_intent_observed=0
unsafe_path_negative_tests_required=1
unmanaged_target_preservation_tests_required=1
receipt_completeness_tests_required=1
reset_uninstall_dry_run_required=1
verification_transcript_required=1
application_support_write_performed=0
payload_write_performed=0
config_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
installer_write_performed=0
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
production_installer_ready=0
next_lane=macos-reset-uninstall-live-execution-preflight-contract
REPORT
