#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-dry-run-writer-candidate-integration.sh [--panel-executable <file>] [--icon <file>]

Runs the macOS local candidate asset probe and the app bundle writer dry-run
with the same caller-supplied inputs, then reports whether both no-effect
checks agree that the inputs can reach the future commit gate.
USAGE
}

field_from_output() {
  field="$1"
  output="$2"
  printf '%s\n' "$output" | awk -F= -v field="$field" '
    $1 == field {
      print substr($0, length($1) + 2)
      found = 1
      exit
    }
    END {
      if (!found) {
        print "missing"
      }
    }
  '
}

run_asset_probe() {
  if [ -n "$PANEL_RAW" ] && [ -n "$ICON_RAW" ]; then
    sh "$ROOT/scripts/macos-local-candidate-asset-probe.sh" --panel-executable "$PANEL_RAW" --icon "$ICON_RAW"
  elif [ -n "$PANEL_RAW" ]; then
    sh "$ROOT/scripts/macos-local-candidate-asset-probe.sh" --panel-executable "$PANEL_RAW"
  elif [ -n "$ICON_RAW" ]; then
    sh "$ROOT/scripts/macos-local-candidate-asset-probe.sh" --icon "$ICON_RAW"
  else
    sh "$ROOT/scripts/macos-local-candidate-asset-probe.sh"
  fi
}

run_writer_dry_run() {
  if [ -n "$PANEL_RAW" ] && [ -n "$ICON_RAW" ]; then
    sh "$ROOT/scripts/macos-app-bundle-writer-dry-run.sh" --panel-executable "$PANEL_RAW" --icon "$ICON_RAW"
  elif [ -n "$PANEL_RAW" ]; then
    sh "$ROOT/scripts/macos-app-bundle-writer-dry-run.sh" --panel-executable "$PANEL_RAW"
  elif [ -n "$ICON_RAW" ]; then
    sh "$ROOT/scripts/macos-app-bundle-writer-dry-run.sh" --icon "$ICON_RAW"
  else
    sh "$ROOT/scripts/macos-app-bundle-writer-dry-run.sh"
  fi
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

ASSET_OUTPUT=$(run_asset_probe)
WRITER_OUTPUT=$(run_writer_dry_run)

ASSET_DECISION=$(field_from_output asset_probe_decision "$ASSET_OUTPUT")
WRITER_DECISION=$(field_from_output dry_run_decision "$WRITER_OUTPUT")
WRITER_PHASE_5=$(field_from_output phase_5_status "$WRITER_OUTPUT")
COMMIT_FLAG=$(field_from_output commit_user_local_managed_artifacts "$WRITER_OUTPUT")
APP_BUNDLE_WRITE=$(field_from_output app_bundle_write_performed "$WRITER_OUTPUT")
HOST_MUTATION=$(field_from_output host_mutation_performed "$WRITER_OUTPUT")
NETWORK=$(field_from_output network_performed "$WRITER_OUTPUT")
PANEL_CANDIDATE=$(field_from_output panel_executable_candidate "$WRITER_OUTPUT")
ICON_CANDIDATE=$(field_from_output icon_candidate "$WRITER_OUTPUT")

if [ "$ASSET_DECISION" = "ready-for-dry-run-writer-inputs" ]; then
  ASSET_READY=1
else
  ASSET_READY=0
fi

if [ "$WRITER_DECISION" = "ready-for-future-commit-gate" ]; then
  WRITER_READY=1
else
  WRITER_READY=0
fi

if [ "$COMMIT_FLAG" = "0" ] && [ "$APP_BUNDLE_WRITE" = "0" ] && [ "$HOST_MUTATION" = "0" ] && [ "$NETWORK" = "0" ]; then
  AUTHORITY_BOUNDARY_PRESERVED=1
else
  AUTHORITY_BOUNDARY_PRESERVED=0
fi

if [ "$ASSET_READY" = "1" ] && [ "$WRITER_READY" = "1" ] && [ "$AUTHORITY_BOUNDARY_PRESERVED" = "1" ]; then
  CANDIDATE_FLOW_READY=1
  INTEGRATION_DECISION="ready-for-future-commit-gate-no-effect"
elif [ "$ASSET_READY" = "0" ]; then
  CANDIDATE_FLOW_READY=0
  INTEGRATION_DECISION="blocked-asset-probe-not-ready"
elif [ "$WRITER_READY" = "0" ]; then
  CANDIDATE_FLOW_READY=0
  INTEGRATION_DECISION="blocked-writer-dry-run-not-ready"
else
  CANDIDATE_FLOW_READY=0
  INTEGRATION_DECISION="blocked-authority-boundary-widened"
fi

cat <<REPORT
MACOS DRY RUN WRITER CANDIDATE INTEGRATION

integration_status=ok
integration_mode=macos-dry-run-writer-candidate-integration
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
asset_probe_script=$ROOT/scripts/macos-local-candidate-asset-probe.sh
writer_dry_run_script=$ROOT/scripts/macos-app-bundle-writer-dry-run.sh
panel_executable_candidate=$PANEL_CANDIDATE
icon_candidate=$ICON_CANDIDATE
asset_probe_decision=$ASSET_DECISION
writer_dry_run_decision=$WRITER_DECISION
writer_phase_5_status=$WRITER_PHASE_5
asset_probe_ready=$ASSET_READY
writer_dry_run_ready=$WRITER_READY
authority_boundary_preserved=$AUTHORITY_BOUNDARY_PRESERVED
candidate_flow_ready=$CANDIDATE_FLOW_READY
integration_decision=$INTEGRATION_DECISION
commit_user_local_managed_artifacts=$COMMIT_FLAG
app_bundle_write_performed=$APP_BUNDLE_WRITE
host_mutation_performed=$HOST_MUTATION
network_performed=$NETWORK
build_performed=0
download_performed=0
copy_performed=0
signing_performed=0
notarization_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
next_lane=macos-reset-uninstall-live-runner-denied-dispatch-review-contract
REPORT
