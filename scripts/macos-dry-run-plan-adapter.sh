#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-dry-run-plan-adapter.sh [--app-support-prefix <dir>] [--app-bundle <dir>] [--cli-bin <dir>] [--output <file>]

Renders a no-effect macOS dry-run plan for user-local Latticra artifacts.
It does not create app bundles, install files, write wrappers, mutate shell
profiles, use launchd, access Keychain, request TCC permissions, use the
network, or grant authority.
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

APP_SUPPORT_RAW="$HOME/Library/Application Support/Latticra"
APP_BUNDLE_RAW="$HOME/Applications/Latticra Panel.app"
CLI_BIN_RAW="$HOME/.local/bin"
OUTPUT=""

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
    --output)
      [ "$#" -ge 2 ] || { echo "missing value for --output" >&2; exit 64; }
      OUTPUT="$2"
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
RECEIPTS_DIR="$APP_SUPPORT/receipts"
PAYLOAD_DIR="$APP_SUPPORT/lib/latticra"
CONFIG_DIR="$APP_SUPPORT/etc/latticra"
APP_CONTENTS="$APP_BUNDLE/Contents"
APP_MACOS="$APP_CONTENTS/MacOS"
APP_RESOURCES="$APP_CONTENTS/Resources"
APP_INFO_PLIST="$APP_CONTENTS/Info.plist"
APP_EXECUTABLE="$APP_MACOS/latticra-panel"
APP_ICON="$APP_RESOURCES/latticra-panel.icns"

if [ "$UNAME_S" = "Darwin" ]; then
  MACOS_HOST_DETECTED=1
else
  MACOS_HOST_DETECTED=0
fi

if path_allowed "$APP_SUPPORT" && path_allowed "$APP_BUNDLE" && path_allowed "$CLI_BIN" && path_allowed "$LOGS_DIR" && path_allowed "$CACHES_DIR"; then
  PATH_GUARD_STATUS="allowed-user-local-dry-run"
  DRY_RUN_ALLOWED=1
else
  PATH_GUARD_STATUS="blocked-unsafe-user-local-path"
  DRY_RUN_ALLOWED=0
fi

REPORT=$(cat <<REPORT
MACOS DRY RUN PLAN ADAPTER

plan_status=ok
plan_mode=macos-dry-run-plan
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_host_detected=$MACOS_HOST_DETECTED
path_guard_status=$PATH_GUARD_STATUS
dry_run_allowed=$DRY_RUN_ALLOWED
application_support_prefix=$APP_SUPPORT
payload_dir=$PAYLOAD_DIR
config_dir=$CONFIG_DIR
receipts_dir=$RECEIPTS_DIR
logs_dir=$LOGS_DIR
caches_dir=$CACHES_DIR
app_bundle=$APP_BUNDLE
app_contents_dir=$APP_CONTENTS
app_macos_dir=$APP_MACOS
app_resources_dir=$APP_RESOURCES
app_info_plist=$APP_INFO_PLIST
app_executable=$APP_EXECUTABLE
app_icon=$APP_ICON
cli_bin=$CLI_BIN
planned_latticra_wrapper=$CLI_BIN/latticra
planned_lat_wrapper=$CLI_BIN/lat
planned_latticra_seal_wrapper=$CLI_BIN/latticra-seal
planned_latticra_nadia_wrapper=$CLI_BIN/latticra-nadia
planned_latticra_panel_wrapper=$CLI_BIN/latticra-panel
planned_verification_command=sh scripts/macos-dry-run-plan-adapter.sh
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
next_lane=macos-user-local-app-bundle-contract
REPORT
)

if [ -n "$OUTPUT" ]; then
  mkdir -p "$(dirname -- "$OUTPUT")"
  printf '%s\n' "$REPORT" > "$OUTPUT"
  printf 'MACOS_DRY_RUN_PLAN_ADAPTER_REPORT: %s\n' "$OUTPUT"
else
  printf '%s\n' "$REPORT"
fi
