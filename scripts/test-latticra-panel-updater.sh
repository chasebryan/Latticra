#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra panel updater: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_output_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf '%s\n' "--- output: $file ---" >&2
    sed -n '1,160p' "$file" >&2
    fail "missing required output pattern: $pattern"
  fi
}

ui='installer/latticra-installer/src/ui.rs'
config='installer/latticra-installer/src/config.rs'
apply='installer/scripts/latticra-installer-apply.sh'
verify='installer/scripts/latticra-installer-verify.sh'
default_config='installer/configs/default.installer.toml'
local_config='installer/configs/local-prefix-example.installer.toml'
installer_readme='installer/README.md'
quick_start='docs/QUICK_START_CHEATSHEET.md'
checkpoint='docs/status/LATTICRA_PANEL_UI_DESIGN_CHECKPOINT.md'
design_check='scripts/check_latticra_panel_ui_design.py'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$ui" \
  "$config" \
  "$apply" \
  "$verify" \
  "$default_config" \
  "$local_config" \
  "$installer_readme" \
  "$quick_start" \
  "$checkpoint" \
  "$design_check" \
  Makefile \
  "$workflow"
do
  require_file "$file"
done

require_contains 'WorkspaceTab::Updater' "$ui"
require_contains 'fn show_updater(&mut self, ui: &mut egui::Ui)' "$ui"
require_contains 'fn start_update_dry_run(&mut self)' "$ui"
require_contains 'fn start_update_apply(&mut self)' "$ui"
require_contains '["updater", "dry-run"]' "$ui"
require_contains '["updater", "apply"]' "$ui"
require_contains 'Network fetch (future; disabled)' "$ui"
require_contains 'Updater apply is locked until Preview update completes successfully.' "$ui"
require_contains 'pub struct UpdaterConfig' "$config"
require_contains 'allow_network_fetch: false' "$config"
require_contains 'Updater network fetch is not implemented in this installer.' "$config"
require_contains '[updater]' "$default_config"
require_contains 'allow_network_fetch = false' "$default_config"
require_contains '[updater]' "$local_config"
require_contains 'allow_network_fetch = false' "$local_config"
require_contains 'UPDATER_ALLOW_NETWORK_FETCH=$(cfg_section updater allow_network_fetch false)' "$apply"
require_contains 'fail "updater network fetch authority is not implemented in this installer" 78' "$apply"
require_contains 'write_file "$PREFIX/etc/latticra/updater.toml"' "$apply"
require_contains 'write_file "$PREFIX/share/latticra/updater/policy.toml"' "$apply"
require_contains 'update|updater)' "$apply"
require_contains 'LATTICRA PANEL UPDATER' "$apply"
require_contains 'UPDATER_ACTION="\${2:-open}"' "$apply"
require_contains 'preview_command=updater dry-run' "$apply"
require_contains 'apply_command=updater apply' "$apply"
require_contains 'network_fetch_authority=0' "$apply"
require_contains 'write_update_receipt = $UPDATER_WRITE_UPDATE_RECEIPT' "$apply"
require_contains 'update_apply_mode = "guarded-local-prefix-reinstall"' "$apply"
require_contains 'usage: latticra updater {status|open|dry-run|apply}' "$apply"
require_contains 'UPDATER_CONFIG="$PREFIX/etc/latticra/updater.toml"' "$verify"
require_contains 'check "updater config" "$UPDATER_CONFIG"' "$verify"
require_contains 'if "$USER_BIN/latticra" updater status' "$verify"
require_contains 'updater status report' "$verify"
require_contains 'updater policy receipt setting' "$verify"
require_contains 'Use the **Updater** workspace in Latticra Panel' "$installer_readme"
require_contains 'Use the **Updater** workspace in Latticra Panel' "$quick_start"
require_contains 'latticra updater status' "$installer_readme"
require_contains 'latticra updater status' "$quick_start"
require_contains 'updater tab' "$checkpoint"
require_contains 'updater function' "$design_check"
require_contains 'sh ./scripts/test-latticra-panel-updater.sh' Makefile
require_contains 'Validate Latticra Panel updater surface' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel-updater-test.XXXXXX")"
mkdir -p "$tmp/home" "$tmp/receipts"
trap 'rm -rf "$tmp"' EXIT HUP INT TERM

HOME="$tmp/home" sh "$apply" \
  --config "$default_config" \
  --plan "$tmp/plan.txt" \
  --receipt-dir "$tmp/receipts" > "$tmp/dry-run.out" 2>&1

require_output_contains '[dry-run] updater would reuse guarded installer engine from current-source-checkout' "$tmp/dry-run.out"
require_contains '[updater]' "$tmp/plan.txt"
require_contains 'allow_network_fetch=false' "$tmp/plan.txt"
require_contains 'update_apply_mode=guarded-local-prefix-reinstall' "$tmp/plan.txt"
require_contains 'updater_panel_owned=1' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_allow_network_fetch=false' "$tmp/receipts/latest-receipt.txt"

cat > "$tmp/live.installer.toml" <<LIVE_CONFIG
profile = "developer_local"
install_prefix = "$tmp/home/.local/share/latticra"
latticra_console = false
lat_tooling = false
lir_contracts = false
seal_report_only = false
nadia_offline_ai = false
fedora_validation = false
docs_and_examples = false
developer_cli_helpers = false
dry_run = false
allow_host_mutation = true
allow_network_effect = false
require_component_manifest = false
require_artifact_measurements = false
require_verification_policy_metadata = false
write_operator_receipt = true
create_prefix_layout = true
create_component_markers = true
create_cli_shims = true
preserve_existing_files = true
build_gui_installer = false
build_latticra_from_source = false
install_payload_tree = false
install_desktop_entry = false
install_user_bin_wrappers = true

[updater]
source_strategy = "fixture-source-checkout"
update_channel = "fixture-channel"
allow_network_fetch = false
require_dry_run_before_apply = true
reuse_installer_engine = true
write_update_receipt = false
LIVE_CONFIG

HOME="$tmp/home" sh "$apply" \
  --config "$tmp/live.installer.toml" \
  --plan "$tmp/live-plan.txt" \
  --receipt-dir "$tmp/live-receipts" > "$tmp/live.out" 2>&1

HOME="$tmp/home" "$tmp/home/.local/bin/latticra" updater status > "$tmp/updater-status.out"

require_contains 'write_update_receipt = false' "$tmp/home/.local/share/latticra/share/latticra/updater/policy.toml"
require_contains 'update_apply_mode = "guarded-local-prefix-reinstall"' "$tmp/home/.local/share/latticra/share/latticra/updater/policy.toml"
require_output_contains 'LATTICRA PANEL UPDATER' "$tmp/updater-status.out"
require_output_contains 'source_strategy=fixture-source-checkout' "$tmp/updater-status.out"
require_output_contains 'update_channel=fixture-channel' "$tmp/updater-status.out"
require_output_contains 'preview_command=updater dry-run' "$tmp/updater-status.out"
require_output_contains 'apply_command=updater apply' "$tmp/updater-status.out"
require_output_contains 'write_update_receipt=false' "$tmp/updater-status.out"
require_output_contains 'network_fetch_authority=0' "$tmp/updater-status.out"
require_output_contains 'update_apply_mode=guarded-local-prefix-reinstall' "$tmp/updater-status.out"

awk '
  $0 == "allow_network_fetch = false" {
    print "allow_network_fetch = true"
    next
  }
  { print }
' "$default_config" > "$tmp/network-fetch.installer.toml"

if HOME="$tmp/home" sh "$apply" \
  --config "$tmp/network-fetch.installer.toml" \
  --plan "$tmp/network-plan.txt" \
  --receipt-dir "$tmp/network-receipts" > "$tmp/network-fetch.out" 2>&1
then
  fail "network-fetch updater config unexpectedly succeeded"
fi

require_output_contains 'updater network fetch authority is not implemented in this installer' "$tmp/network-fetch.out"

printf 'latticra_panel_updater: ok\n'
