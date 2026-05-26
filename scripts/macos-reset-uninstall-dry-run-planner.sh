#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-reset-uninstall-dry-run-planner.sh [--app-support-prefix <dir>] [--app-bundle <dir>] [--cli-wrapper <file>] [--reset-receipts-dir <dir>]

Consumes the no-effect macOS reset/uninstall live-target classifier and emits a
dry-run reset/uninstall transcript. It plans only future managed-target actions.
It does not delete files, remove directories, write receipts, mutate host state,
open the network, or claim reset/uninstall implementation.
USAGE
}

extract_field() {
  name="$1"
  value=$(printf '%s\n' "$CLASSIFIER_OUTPUT" | sed -n "s/^$name=//p" | sed -n '1p')
  if [ -n "$value" ]; then
    printf '%s\n' "$value"
  else
    printf 'missing\n'
  fi
}

planned_target_action() {
  kind="$1"
  state="$2"

  if [ "$UNSAFE_PATH_DETECTED" = "1" ]; then
    printf 'skip-unsafe-path\n'
    return 0
  fi

  if [ "$UNMANAGED_TARGET_DETECTED" = "1" ]; then
    case "$state" in
      unmanaged-preserve)
        printf 'preserve-unmanaged-target\n'
        ;;
      managed)
        printf 'blocked-managed-target-until-unmanaged-resolved\n'
        ;;
      absent)
        printf 'skip-absent\n'
        ;;
      *)
        printf 'not-classified\n'
        ;;
    esac
    return 0
  fi

  case "$state" in
    absent)
      printf 'skip-absent\n'
      ;;
    managed)
      case "$kind" in
        cli_wrapper)
          printf 'would-remove-managed-wrapper\n'
          ;;
        app_bundle)
          printf 'would-remove-managed-app-bundle\n'
          ;;
        app_support)
          printf 'would-remove-managed-application-support-prefix\n'
          ;;
        reset_receipts)
          printf 'preserve-existing-reset-receipts-dir\n'
          ;;
        *)
          printf 'would-preserve-managed-target\n'
          ;;
      esac
      ;;
    unmanaged-preserve)
      printf 'preserve-unmanaged-target\n'
      ;;
    not-classified-unsafe-path)
      printf 'skip-unsafe-path\n'
      ;;
    *)
      printf 'not-classified\n'
      ;;
  esac
}

planned_removal_flag() {
  action="$1"
  case "$action" in
    would-remove-*)
      printf '1\n'
      ;;
    *)
      printf '0\n'
      ;;
  esac
}

APP_SUPPORT_RAW="$HOME/Library/Application Support/Latticra"
APP_BUNDLE_RAW="$HOME/Applications/Latticra Panel.app"
CLI_WRAPPER_RAW="$HOME/.local/bin/latticra-panel"
RESET_RECEIPTS_RAW="$HOME/Library/Application Support/Latticra Reset Receipts"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --app-support-prefix)
      [ "$#" -ge 2 ] || { echo "missing value for --app-support-prefix" >&2; exit 64; }
      APP_SUPPORT_RAW="$2"
      shift 2
      ;;
    --app-bundle)
      [ "$#" -ge 2 ] || { echo "missing value for --app-bundle" >&2; exit 64; }
      APP_BUNDLE_RAW="$2"
      shift 2
      ;;
    --cli-wrapper)
      [ "$#" -ge 2 ] || { echo "missing value for --cli-wrapper" >&2; exit 64; }
      CLI_WRAPPER_RAW="$2"
      shift 2
      ;;
    --reset-receipts-dir)
      [ "$#" -ge 2 ] || { echo "missing value for --reset-receipts-dir" >&2; exit 64; }
      RESET_RECEIPTS_RAW="$2"
      shift 2
      ;;
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
CLASSIFIER="$ROOT/scripts/macos-reset-uninstall-live-target-classifier.sh"

if [ ! -f "$CLASSIFIER" ]; then
  echo "missing classifier script: $CLASSIFIER" >&2
  exit 1
fi

CLASSIFIER_OUTPUT=$(
  sh "$CLASSIFIER" \
    --app-support-prefix "$APP_SUPPORT_RAW" \
    --app-bundle "$APP_BUNDLE_RAW" \
    --cli-wrapper "$CLI_WRAPPER_RAW" \
    --reset-receipts-dir "$RESET_RECEIPTS_RAW"
)

CLASSIFIER_STATUS=$(extract_field reset_uninstall_live_target_classifier_status)
PATH_GUARD_STATUS=$(extract_field path_guard_status)
UNSAFE_PATH_DETECTED=$(extract_field unsafe_path_detected)
CLASSIFIER_DECISION=$(extract_field reset_uninstall_live_classifier_decision)
APP_SUPPORT_TARGET=$(extract_field app_support_prefix_target)
APP_SUPPORT_STATE=$(extract_field app_support_prefix_target_state)
APP_BUNDLE_TARGET=$(extract_field app_bundle_target)
APP_BUNDLE_STATE=$(extract_field app_bundle_target_state)
CLI_WRAPPER_TARGET=$(extract_field cli_wrapper_target)
CLI_WRAPPER_STATE=$(extract_field cli_wrapper_target_state)
RESET_RECEIPTS_TARGET=$(extract_field reset_receipts_dir_target)
RESET_RECEIPTS_STATE=$(extract_field reset_receipts_dir_target_state)
PRESENT_TARGET_DETECTED=$(extract_field present_target_detected)
ABSENT_TARGET_DETECTED=$(extract_field absent_target_detected)
MANAGED_TARGET_DETECTED=$(extract_field managed_target_detected)
UNMANAGED_TARGET_DETECTED=$(extract_field unmanaged_target_detected)

APP_SUPPORT_ACTION=$(planned_target_action app_support "$APP_SUPPORT_STATE")
APP_BUNDLE_ACTION=$(planned_target_action app_bundle "$APP_BUNDLE_STATE")
CLI_WRAPPER_ACTION=$(planned_target_action cli_wrapper "$CLI_WRAPPER_STATE")
RESET_RECEIPTS_ACTION=$(planned_target_action reset_receipts "$RESET_RECEIPTS_STATE")

APP_SUPPORT_REMOVAL_PLANNED=$(planned_removal_flag "$APP_SUPPORT_ACTION")
APP_BUNDLE_REMOVAL_PLANNED=$(planned_removal_flag "$APP_BUNDLE_ACTION")
CLI_WRAPPER_REMOVAL_PLANNED=$(planned_removal_flag "$CLI_WRAPPER_ACTION")
PLANNED_REMOVAL_COUNT=$((APP_SUPPORT_REMOVAL_PLANNED + APP_BUNDLE_REMOVAL_PLANNED + CLI_WRAPPER_REMOVAL_PLANNED))

if [ "$UNSAFE_PATH_DETECTED" = "1" ]; then
  PLANNER_DECISION="blocked-unsafe-path-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="blocked-unsafe-path"
  PHASE_3_STATUS="skipped-unsafe-path"
  RECEIPT_WRITE_PLANNED=0
  ABSENCE_REPORT_PLANNED=0
elif [ "$UNMANAGED_TARGET_DETECTED" = "1" ]; then
  PLANNER_DECISION="blocked-unmanaged-targets-preserve-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="preserve-unmanaged-targets"
  RECEIPT_WRITE_PLANNED=0
  ABSENCE_REPORT_PLANNED=0
elif [ "$PLANNED_REMOVAL_COUNT" -gt 0 ]; then
  PLANNER_DECISION="planned-managed-target-removal-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="ok"
  RECEIPT_WRITE_PLANNED=1
  ABSENCE_REPORT_PLANNED=1
else
  PLANNER_DECISION="ready-no-targets-observed-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="ok"
  RECEIPT_WRITE_PLANNED=0
  ABSENCE_REPORT_PLANNED=1
fi

if [ "$RECEIPT_WRITE_PLANNED" = "1" ]; then
  RECEIPT_ACTION="would-write-reset-uninstall-receipt-outside-removed-prefix"
else
  RECEIPT_ACTION="not-planned-no-effect"
fi

if [ "$ABSENCE_REPORT_PLANNED" = "1" ]; then
  ABSENCE_ACTION="would-emit-verification-absence-report-no-effect"
else
  ABSENCE_ACTION="not-planned-no-effect"
fi

cat <<REPORT
MACOS RESET UNINSTALL DRY RUN PLANNER

reset_uninstall_dry_run_planner_status=ok
macos_reset_uninstall_dry_run_planner_present=1
planner_report_only=1
dry_run_transcript_present=1
reset_uninstall_dry_run_planner_transcript_present=1
planner_consumes_live_target_classifier=1
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
classifier_script=$CLASSIFIER
classifier_status=$CLASSIFIER_STATUS
macos_reset_uninstall_live_target_classifier_present=1
reset_uninstall_dry_run_contract_present=1
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
reset_uninstall_dry_run_evidence_present=0
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
path_guard_status=$PATH_GUARD_STATUS
unsafe_path_detected=$UNSAFE_PATH_DETECTED
reset_uninstall_live_classifier_decision=$CLASSIFIER_DECISION
reset_uninstall_dry_run_planner_decision=$PLANNER_DECISION
app_support_prefix_target=$APP_SUPPORT_TARGET
app_support_prefix_target_state=$APP_SUPPORT_STATE
app_support_prefix_dry_run_action=$APP_SUPPORT_ACTION
app_bundle_target=$APP_BUNDLE_TARGET
app_bundle_target_state=$APP_BUNDLE_STATE
app_bundle_dry_run_action=$APP_BUNDLE_ACTION
cli_wrapper_target=$CLI_WRAPPER_TARGET
cli_wrapper_target_state=$CLI_WRAPPER_STATE
cli_wrapper_dry_run_action=$CLI_WRAPPER_ACTION
reset_receipts_dir_target=$RESET_RECEIPTS_TARGET
reset_receipts_dir_target_state=$RESET_RECEIPTS_STATE
reset_receipts_dir_dry_run_action=$RESET_RECEIPTS_ACTION
target_states_recorded=1
present_target_detected=$PRESENT_TARGET_DETECTED
absent_target_detected=$ABSENT_TARGET_DETECTED
managed_target_detected=$MANAGED_TARGET_DETECTED
unmanaged_target_detected=$UNMANAGED_TARGET_DETECTED
managed_marker_required=1
unmanaged_target_preservation_required=1
receipt_outside_removed_prefix_required=1
absence_report_required=1
absence_report_contract_present=1
absence_report_evidence_present=0
managed_wrapper_removal_planned=$CLI_WRAPPER_REMOVAL_PLANNED
managed_app_bundle_removal_planned=$APP_BUNDLE_REMOVAL_PLANNED
managed_application_support_removal_planned=$APP_SUPPORT_REMOVAL_PLANNED
planned_removal_count=$PLANNED_REMOVAL_COUNT
reset_receipt_write_planned=$RECEIPT_WRITE_PLANNED
reset_receipt_dry_run_action=$RECEIPT_ACTION
absence_report_planned=$ABSENCE_REPORT_PLANNED
absence_report_dry_run_action=$ABSENCE_ACTION
dry_run_phase_1=consume_live_target_classifier
dry_run_phase_1_status=$PHASE_1_STATUS
dry_run_phase_2=validate_user_local_targets
dry_run_phase_2_status=$PHASE_2_STATUS
dry_run_phase_3=plan_unmanaged_target_preservation
dry_run_phase_3_status=$PHASE_3_STATUS
dry_run_phase_4=plan_managed_wrapper_removal
dry_run_phase_4_status=$CLI_WRAPPER_ACTION
dry_run_phase_5=plan_managed_app_bundle_removal
dry_run_phase_5_status=$APP_BUNDLE_ACTION
dry_run_phase_6=plan_managed_application_support_removal
dry_run_phase_6_status=$APP_SUPPORT_ACTION
dry_run_phase_7=plan_receipt_write_outside_removed_prefix
dry_run_phase_7_status=$RECEIPT_ACTION
dry_run_phase_8=plan_verification_absence_report
dry_run_phase_8_status=$ABSENCE_ACTION
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
next_lane=macos-reset-uninstall-live-runner-acceptance-denial-review-contract
REPORT
