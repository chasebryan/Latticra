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
require_contains 'signed_delivery_gate = "closed"' "$apply"
require_contains 'signed_manifest_required = true' "$apply"
require_contains 'signed_manifest_present = false' "$apply"
require_contains 'signed_update_apply_allowed = false' "$apply"
require_contains 'signed_update_delivery_ready = false' "$apply"
require_contains 'update|updater)' "$apply"
require_contains 'LATTICRA PANEL UPDATER' "$apply"
require_contains 'UPDATER_ACTION="\${2:-open}"' "$apply"
require_contains 'usage: latticra updater {status|open|dry-run|apply}' "$apply"
require_contains 'UPDATER_CONFIG="$PREFIX/etc/latticra/updater.toml"' "$verify"
require_contains 'check "updater config" "$UPDATER_CONFIG"' "$verify"
require_contains 'if "$USER_BIN/latticra" updater status' "$verify"
require_contains 'updater status report' "$verify"
require_contains 'updater signed delivery gate closed' "$verify"
require_contains 'updater status signed apply disabled' "$verify"
require_contains 'Use the **Updater** workspace in Latticra Panel' "$installer_readme"
require_contains 'Use the **Updater** workspace in Latticra Panel' "$quick_start"
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
require_contains 'signed_delivery_gate=closed' "$tmp/plan.txt"
require_contains 'signed_manifest_required=1' "$tmp/plan.txt"
require_contains 'signed_manifest_present=0' "$tmp/plan.txt"
require_contains 'signed_update_apply_allowed=0' "$tmp/plan.txt"
require_contains 'signed_update_delivery_ready=0' "$tmp/plan.txt"
require_contains 'updater_panel_owned=1' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_allow_network_fetch=false' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_signed_delivery_gate=closed' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_signed_manifest_required=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_signed_manifest_present=false' "$tmp/receipts/latest-receipt.txt"
require_contains 'updater_signed_update_apply_allowed=false' "$tmp/receipts/latest-receipt.txt"

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
