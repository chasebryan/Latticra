#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-reset-uninstall-live-target-classifier.sh [--app-support-prefix <dir>] [--app-bundle <dir>] [--cli-wrapper <file>] [--reset-receipts-dir <dir>]

Emits a no-effect macOS reset/uninstall live-target classifier report.
It inspects only the guarded user-local macOS targets and reports whether each
target is absent, managed, or unmanaged-preserve. It does not delete files,
write receipts, mutate host state, open the network, or claim reset/uninstall
implementation.
USAGE
}

expand_home() {
  case "$1" in
    "~")
      printf '%s\n' "$HOME"
      ;;
    "~/"*)
      printf '%s/%s\n' "$HOME" "${1#~/}"
      ;;
    *)
      printf '%s\n' "$1"
      ;;
  esac
}

path_allowed() {
  path="$1"
  case "$path" in
    "$HOME/Library/Application Support/Latticra"|"$HOME/Library/Application Support/Latticra"/*)
      return 0
      ;;
    "$HOME/Applications/Latticra Panel.app"|"$HOME/Applications/Latticra Panel.app"/*)
      return 0
      ;;
    "$HOME/.local/bin/latticra-panel")
      return 0
      ;;
    "$HOME/Library/Application Support/Latticra Reset Receipts"|"$HOME/Library/Application Support/Latticra Reset Receipts"/*)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

has_managed_marker() {
  target="$1"
  if [ ! -e "$target" ]; then
    return 1
  fi

  if [ -f "$target" ]; then
    grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$target" 2>/dev/null &&
      grep -q 'LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1' "$target" 2>/dev/null
    return $?
  fi

  if [ -d "$target" ]; then
    marker="$target/Contents/Resources/latticra/MANAGED_BY_LATTICRA"
    if [ ! -f "$marker" ]; then
      marker="$target/MANAGED_BY_LATTICRA"
    fi
    [ -f "$marker" ] &&
      grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$marker" 2>/dev/null &&
      grep -q 'LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1' "$marker" 2>/dev/null
    return $?
  fi

  return 1
}

classify_target() {
  target="$1"
  if [ ! -e "$target" ]; then
    printf 'absent\n'
  elif has_managed_marker "$target"; then
    printf 'managed\n'
  else
    printf 'unmanaged-preserve\n'
  fi
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

APP_SUPPORT=$(expand_home "$APP_SUPPORT_RAW")
APP_BUNDLE=$(expand_home "$APP_BUNDLE_RAW")
CLI_WRAPPER=$(expand_home "$CLI_WRAPPER_RAW")
RESET_RECEIPTS=$(expand_home "$RESET_RECEIPTS_RAW")

if [ "$UNAME_S" = "Darwin" ]; then
  MACOS_HOST_DETECTED=1
else
  MACOS_HOST_DETECTED=0
fi

if path_allowed "$APP_SUPPORT" && path_allowed "$APP_BUNDLE" && path_allowed "$CLI_WRAPPER" && path_allowed "$RESET_RECEIPTS"; then
  PATH_GUARD_STATUS="allowed-user-local-classification"
  UNSAFE_PATH_DETECTED=0
else
  PATH_GUARD_STATUS="blocked-unsafe-user-local-path"
  UNSAFE_PATH_DETECTED=1
fi

if [ "$UNSAFE_PATH_DETECTED" = "1" ]; then
  APP_SUPPORT_STATE="not-classified-unsafe-path"
  APP_BUNDLE_STATE="not-classified-unsafe-path"
  CLI_WRAPPER_STATE="not-classified-unsafe-path"
  RESET_RECEIPTS_STATE="not-classified-unsafe-path"
else
  APP_SUPPORT_STATE=$(classify_target "$APP_SUPPORT")
  APP_BUNDLE_STATE=$(classify_target "$APP_BUNDLE")
  CLI_WRAPPER_STATE=$(classify_target "$CLI_WRAPPER")
  RESET_RECEIPTS_STATE=$(classify_target "$RESET_RECEIPTS")
fi

ABSENT_TARGET_DETECTED=0
MANAGED_TARGET_DETECTED=0
UNMANAGED_TARGET_DETECTED=0
PRESENT_TARGET_DETECTED=0

for state in "$APP_SUPPORT_STATE" "$APP_BUNDLE_STATE" "$CLI_WRAPPER_STATE" "$RESET_RECEIPTS_STATE"; do
  case "$state" in
    absent)
      ABSENT_TARGET_DETECTED=1
      ;;
    managed)
      MANAGED_TARGET_DETECTED=1
      PRESENT_TARGET_DETECTED=1
      ;;
    unmanaged-preserve)
      UNMANAGED_TARGET_DETECTED=1
      PRESENT_TARGET_DETECTED=1
      ;;
  esac
done

if [ "$UNSAFE_PATH_DETECTED" = "1" ]; then
  CLASSIFIER_DECISION="blocked-unsafe-path"
  PHASE_1_STATUS="blocked-unsafe-path"
  PHASE_2_STATUS="skipped-unsafe-path"
  PHASE_3_STATUS="skipped-unsafe-path"
elif [ "$UNMANAGED_TARGET_DETECTED" = "1" ]; then
  CLASSIFIER_DECISION="blocked-unmanaged-targets-preserve"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="preserve-unmanaged-targets"
elif [ "$MANAGED_TARGET_DETECTED" = "1" ]; then
  CLASSIFIER_DECISION="ready-managed-targets-observed-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="ok"
else
  CLASSIFIER_DECISION="ready-no-targets-observed-no-effect"
  PHASE_1_STATUS="ok"
  PHASE_2_STATUS="ok"
  PHASE_3_STATUS="ok"
fi

cat <<REPORT
MACOS RESET UNINSTALL LIVE TARGET CLASSIFIER

reset_uninstall_live_target_classifier_status=ok
macos_reset_uninstall_live_target_classifier_present=1
classifier_report_only=1
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_host_detected=$MACOS_HOST_DETECTED
path_guard_status=$PATH_GUARD_STATUS
unsafe_path_detected=$UNSAFE_PATH_DETECTED
reset_uninstall_live_classifier_decision=$CLASSIFIER_DECISION
app_support_prefix_target=$APP_SUPPORT
app_support_prefix_target_state=$APP_SUPPORT_STATE
app_bundle_target=$APP_BUNDLE
app_bundle_target_state=$APP_BUNDLE_STATE
cli_wrapper_target=$CLI_WRAPPER
cli_wrapper_target_state=$CLI_WRAPPER_STATE
reset_receipts_dir_target=$RESET_RECEIPTS
reset_receipts_dir_target_state=$RESET_RECEIPTS_STATE
reset_receipts_dir_preservation=preserve-outside-removed-prefix
target_states_recorded=1
present_target_detected=$PRESENT_TARGET_DETECTED
absent_target_detected=$ABSENT_TARGET_DETECTED
managed_target_detected=$MANAGED_TARGET_DETECTED
unmanaged_target_detected=$UNMANAGED_TARGET_DETECTED
managed_marker_required=1
unmanaged_target_preservation_required=1
reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_dry_run_planner_present=1
macos_reset_uninstall_absence_report_contract_present=1
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
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
reset_uninstall_dry_run_evidence_present=0
absence_report_evidence_present=0
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
classifier_phase_1=validate_user_local_targets
classifier_phase_1_status=$PHASE_1_STATUS
classifier_phase_2=inspect_live_targets_for_managed_markers
classifier_phase_2_status=$PHASE_2_STATUS
classifier_phase_3=classify_absent_managed_unmanaged_targets
classifier_phase_3_status=$PHASE_3_STATUS
classifier_phase_4=emit_no_effect_reset_uninstall_readiness
classifier_phase_4_status=ok
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
next_lane=macos-reset-uninstall-live-implementation-plan-contract
REPORT
