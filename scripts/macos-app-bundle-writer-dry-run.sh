#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-app-bundle-writer-dry-run.sh [--app-support-prefix <dir>] [--app-bundle <dir>] [--cli-bin <dir>] [--panel-executable <file>] [--icon <file>]

Emits a no-effect macOS app bundle writer dry-run phase report.
It validates planned paths and existing managed markers, but it does not create
app bundles, write files, install wrappers, mutate shell profiles, use launchd,
access Keychain, request TCC permissions, use the network, or grant authority.
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
    "$HOME/.local/bin"|"$HOME/.local/bin"/*)
      return 0
      ;;
    "$HOME/Library/Logs/Latticra"|"$HOME/Library/Logs/Latticra"/*)
      return 0
      ;;
    "$HOME/Library/Caches/Latticra"|"$HOME/Library/Caches/Latticra"/*)
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

existing_target_state() {
  target="$1"
  if [ ! -e "$target" ]; then
    printf 'absent\n'
  elif has_managed_marker "$target"; then
    printf 'managed\n'
  else
    printf 'unmanaged-preserve-and-block\n'
  fi
}

APP_SUPPORT_RAW="$HOME/Library/Application Support/Latticra"
APP_BUNDLE_RAW="$HOME/Applications/Latticra Panel.app"
CLI_BIN_RAW="$HOME/.local/bin"
PANEL_EXECUTABLE_RAW=""
ICON_RAW=""

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
    --cli-bin)
      [ "$#" -ge 2 ] || { echo "missing value for --cli-bin" >&2; exit 64; }
      CLI_BIN_RAW="$2"
      shift 2
      ;;
    --panel-executable)
      [ "$#" -ge 2 ] || { echo "missing value for --panel-executable" >&2; exit 64; }
      PANEL_EXECUTABLE_RAW="$2"
      shift 2
      ;;
    --icon)
      [ "$#" -ge 2 ] || { echo "missing value for --icon" >&2; exit 64; }
      ICON_RAW="$2"
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
CLI_BIN=$(expand_home "$CLI_BIN_RAW")
LOGS_DIR="$HOME/Library/Logs/Latticra"
CACHES_DIR="$HOME/Library/Caches/Latticra"
PANEL_EXECUTABLE=$(expand_home "$PANEL_EXECUTABLE_RAW")
ICON=$(expand_home "$ICON_RAW")

if [ "$UNAME_S" = "Darwin" ]; then
  MACOS_HOST_DETECTED=1
else
  MACOS_HOST_DETECTED=0
fi

if path_allowed "$APP_SUPPORT" && path_allowed "$APP_BUNDLE" && path_allowed "$CLI_BIN" && path_allowed "$LOGS_DIR" && path_allowed "$CACHES_DIR"; then
  PATH_GUARD_STATUS="allowed-user-local-dry-run"
  UNSAFE_PATH_DETECTED=0
else
  PATH_GUARD_STATUS="blocked-unsafe-user-local-path"
  UNSAFE_PATH_DETECTED=1
fi

APP_BUNDLE_STATE=$(existing_target_state "$APP_BUNDLE")
APP_SUPPORT_STATE=$(existing_target_state "$APP_SUPPORT")
PANEL_WRAPPER_STATE=$(existing_target_state "$CLI_BIN/latticra-panel")

if [ -n "$PANEL_EXECUTABLE_RAW" ] && [ -x "$PANEL_EXECUTABLE" ]; then
  PANEL_EXECUTABLE_CANDIDATE_PRESENT=1
else
  PANEL_EXECUTABLE_CANDIDATE_PRESENT=0
fi

if [ -n "$ICON_RAW" ] && [ -f "$ICON" ]; then
  ICON_CANDIDATE_PRESENT=1
else
  ICON_CANDIDATE_PRESENT=0
fi

UNMANAGED_EXISTING_TARGET=0
case "$APP_BUNDLE_STATE:$APP_SUPPORT_STATE:$PANEL_WRAPPER_STATE" in
  *unmanaged-preserve-and-block*)
    UNMANAGED_EXISTING_TARGET=1
    ;;
esac

if [ "$UNSAFE_PATH_DETECTED" = "1" ]; then
  DRY_RUN_DECISION="blocked-unsafe-path"
elif [ "$UNMANAGED_EXISTING_TARGET" = "1" ]; then
  DRY_RUN_DECISION="blocked-unmanaged-existing-target"
elif [ "$PANEL_EXECUTABLE_CANDIDATE_PRESENT" = "0" ]; then
  DRY_RUN_DECISION="blocked-missing-panel-executable"
elif [ "$ICON_CANDIDATE_PRESENT" = "0" ]; then
  DRY_RUN_DECISION="blocked-missing-icon-asset"
else
  DRY_RUN_DECISION="ready-for-future-commit-gate"
fi

if [ "$UNSAFE_PATH_DETECTED" = "0" ]; then
  PHASE_2_STATUS="ok"
else
  PHASE_2_STATUS="blocked-unsafe-path"
fi

if [ "$UNMANAGED_EXISTING_TARGET" = "0" ]; then
  PHASE_3_STATUS="ok"
else
  PHASE_3_STATUS="blocked-unmanaged-existing-target"
fi

if [ "$PANEL_EXECUTABLE_CANDIDATE_PRESENT" = "1" ] && [ "$ICON_CANDIDATE_PRESENT" = "1" ]; then
  PHASE_5_STATUS="ok"
elif [ "$PANEL_EXECUTABLE_CANDIDATE_PRESENT" = "0" ]; then
  PHASE_5_STATUS="blocked-missing-panel-executable"
else
  PHASE_5_STATUS="blocked-missing-icon-asset"
fi

cat <<REPORT
MACOS APP BUNDLE WRITER DRY RUN

dry_run_status=ok
phase_report_only=1
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_host_detected=$MACOS_HOST_DETECTED
path_guard_status=$PATH_GUARD_STATUS
unsafe_path_detected=$UNSAFE_PATH_DETECTED
application_support_prefix=$APP_SUPPORT
app_bundle=$APP_BUNDLE
cli_bin=$CLI_BIN
panel_executable_candidate=${PANEL_EXECUTABLE:-none}
panel_executable_candidate_present=$PANEL_EXECUTABLE_CANDIDATE_PRESENT
icon_candidate=${ICON:-none}
icon_candidate_present=$ICON_CANDIDATE_PRESENT
existing_app_bundle_state=$APP_BUNDLE_STATE
existing_application_support_state=$APP_SUPPORT_STATE
existing_latticra_panel_wrapper_state=$PANEL_WRAPPER_STATE
unmanaged_existing_target=$UNMANAGED_EXISTING_TARGET
phase_1=validate_macos_host_and_toolchain_probe
phase_1_status=ok
phase_2=validate_user_local_paths_and_contract
phase_2_status=$PHASE_2_STATUS
phase_3=inspect_existing_targets_for_managed_markers
phase_3_status=$PHASE_3_STATUS
phase_4=stage_app_bundle_manifest_and_infoplist
phase_4_status=report-only
phase_5=stage_panel_executable_and_icon_inputs
phase_5_status=$PHASE_5_STATUS
phase_6=stage_application_support_layout
phase_6_status=report-only
phase_7=stage_cli_wrappers
phase_7_status=report-only
phase_8=commit_user_local_managed_artifacts
phase_8_status=disabled
phase_9=write_receipts_and_measurements
phase_9_status=disabled
phase_10=run_verification_transcript
phase_10_status=not-run
dry_run_decision=$DRY_RUN_DECISION
commit_user_local_managed_artifacts=0
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
next_lane=macos-reset-uninstall-receipt-schema-contract
REPORT
