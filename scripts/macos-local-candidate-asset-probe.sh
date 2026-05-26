#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-local-candidate-asset-probe.sh --panel-executable <file> --icon <file>

Checks caller-supplied local Panel executable and icon candidates for the
macOS app bundle dry-run lane. It does not build, download, sign, notarize,
copy, write app bundle files, mutate host state, or grant authority.
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
    ""|"none")
      return 1
      ;;
    *"://"*|http:*|https:*)
      return 1
      ;;
    /Applications|/Applications/*|/Library|/Library/*|/System|/System/*|/usr/local|/usr/local/*|/opt/homebrew|/opt/homebrew/*)
      return 1
      ;;
    *)
      return 0
      ;;
  esac
}

extension_of() {
  name="$1"
  base=${name##*/}
  case "$base" in
    *.*)
      printf '%s\n' "${base##*.}" | tr '[:upper:]' '[:lower:]'
      ;;
    *)
      printf 'none\n'
      ;;
  esac
}

icon_format_supported() {
  case "$1" in
    icns|png|svg|ico)
      printf '1\n'
      ;;
    *)
      printf '0\n'
      ;;
  esac
}

PANEL_RAW=""
ICON_RAW=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --panel-executable)
      [ "$#" -ge 2 ] || { echo "missing value for --panel-executable" >&2; exit 64; }
      PANEL_RAW="$2"
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

if [ -n "$PANEL_RAW" ]; then
  PANEL=$(expand_home "$PANEL_RAW")
  PANEL_SUPPLIED=1
else
  PANEL="none"
  PANEL_SUPPLIED=0
fi

if [ -n "$ICON_RAW" ]; then
  ICON=$(expand_home "$ICON_RAW")
  ICON_SUPPLIED=1
else
  ICON="none"
  ICON_SUPPLIED=0
fi

if path_allowed "$PANEL"; then
  PANEL_PATH_STATUS="allowed-local-candidate"
else
  PANEL_PATH_STATUS="blocked-disallowed-candidate-path"
fi

if path_allowed "$ICON"; then
  ICON_PATH_STATUS="allowed-local-candidate"
else
  ICON_PATH_STATUS="blocked-disallowed-candidate-path"
fi

if [ "$PANEL_SUPPLIED" = "1" ] && [ -e "$PANEL" ]; then PANEL_PRESENT=1; else PANEL_PRESENT=0; fi
if [ "$PANEL_SUPPLIED" = "1" ] && [ -f "$PANEL" ]; then PANEL_FILE=1; else PANEL_FILE=0; fi
if [ "$PANEL_SUPPLIED" = "1" ] && [ -x "$PANEL" ]; then PANEL_EXECUTABLE=1; else PANEL_EXECUTABLE=0; fi
if [ "$PANEL_SUPPLIED" = "1" ] && [ -r "$PANEL" ]; then PANEL_READABLE=1; else PANEL_READABLE=0; fi

if [ "$ICON_SUPPLIED" = "1" ] && [ -e "$ICON" ]; then ICON_PRESENT=1; else ICON_PRESENT=0; fi
if [ "$ICON_SUPPLIED" = "1" ] && [ -f "$ICON" ]; then ICON_FILE=1; else ICON_FILE=0; fi
if [ "$ICON_SUPPLIED" = "1" ] && [ -r "$ICON" ]; then ICON_READABLE=1; else ICON_READABLE=0; fi
ICON_FORMAT=$(extension_of "$ICON")
ICON_FORMAT_SUPPORTED=$(icon_format_supported "$ICON_FORMAT")
if [ "$ICON_FORMAT" = "icns" ]; then ICON_ICNS_READY=1; else ICON_ICNS_READY=0; fi

if [ "$PANEL_SUPPLIED" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-missing-panel-executable-candidate"
elif [ "$PANEL_PATH_STATUS" != "allowed-local-candidate" ]; then
  ASSET_PROBE_DECISION="blocked-disallowed-panel-candidate-path"
elif [ "$PANEL_PRESENT" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-missing-panel-executable-candidate"
elif [ "$PANEL_FILE" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-panel-candidate-not-file"
elif [ "$PANEL_EXECUTABLE" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-panel-candidate-not-executable"
elif [ "$PANEL_READABLE" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-panel-candidate-not-readable"
elif [ "$ICON_SUPPLIED" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-missing-icon-candidate"
elif [ "$ICON_PATH_STATUS" != "allowed-local-candidate" ]; then
  ASSET_PROBE_DECISION="blocked-disallowed-icon-candidate-path"
elif [ "$ICON_PRESENT" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-missing-icon-candidate"
elif [ "$ICON_FILE" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-icon-candidate-not-file"
elif [ "$ICON_READABLE" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-icon-candidate-not-readable"
elif [ "$ICON_FORMAT_SUPPORTED" = "0" ]; then
  ASSET_PROBE_DECISION="blocked-unsupported-icon-candidate"
else
  ASSET_PROBE_DECISION="ready-for-dry-run-writer-inputs"
fi

cat <<REPORT
MACOS LOCAL CANDIDATE ASSET PROBE

probe_status=ok
probe_mode=macos-local-candidate-asset-probe
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
panel_executable_candidate=$PANEL
panel_candidate_supplied=$PANEL_SUPPLIED
panel_candidate_path_status=$PANEL_PATH_STATUS
panel_candidate_present=$PANEL_PRESENT
panel_candidate_file=$PANEL_FILE
panel_candidate_executable=$PANEL_EXECUTABLE
panel_candidate_readable=$PANEL_READABLE
panel_executable_candidate_supplied=$PANEL_SUPPLIED
panel_executable_candidate_path_status=$PANEL_PATH_STATUS
panel_executable_candidate_present=$PANEL_PRESENT
panel_executable_candidate_file=$PANEL_FILE
panel_executable_candidate_executable=$PANEL_EXECUTABLE
panel_executable_candidate_readable=$PANEL_READABLE
icon_candidate=$ICON
icon_candidate_supplied=$ICON_SUPPLIED
icon_candidate_path_status=$ICON_PATH_STATUS
icon_candidate_present=$ICON_PRESENT
icon_candidate_file=$ICON_FILE
icon_candidate_readable=$ICON_READABLE
icon_candidate_format=$ICON_FORMAT
icon_candidate_supported_format=$ICON_FORMAT_SUPPORTED
icon_candidate_icns_ready=$ICON_ICNS_READY
local_panel_executable_candidate_probe=1
local_icon_candidate_probe=1
asset_probe_decision=$ASSET_PROBE_DECISION
build_performed=0
panel_build_performed=0
icon_conversion_performed=0
download_performed=0
copy_performed=0
signing_performed=0
notarization_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
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
next_lane=macos-reset-uninstall-receipt-schema-contract
REPORT
