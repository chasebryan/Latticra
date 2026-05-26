#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel-lc-install-config.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

home="$tmpdir/home"
plan="$tmpdir/install-plan.txt"
receipt_dir="$tmpdir/receipts"
run_log="$tmpdir/run.log"
live_config="$tmpdir/live.installer.toml"
live_plan="$tmpdir/live-plan.txt"
live_receipts="$tmpdir/live-receipts"
lc_report="$tmpdir/lc-install-config.txt"
latticra_lc_report="$tmpdir/latticra-lc-install-config.txt"
lc_help="$tmpdir/lc-help.txt"
lc_man="$tmpdir/lc-man.txt"
lc_usage="$tmpdir/lc-usage.txt"
verify_log="$tmpdir/verify.log"
lc_wrapper="latticra-console-custom"
bad_config="$tmpdir/bad.installer.toml"
mkdir -p "$home"

grep -Fq 'pub struct LatticraConsoleInstallConfig' installer/latticra-installer/src/config.rs
grep -Fq 'pub install: LatticraConsoleInstallConfig' installer/latticra-installer/src/config.rs
grep -Fq 'LC install configuration' installer/latticra-installer/src/ui.rs
grep -Fq 'lc install-config' installer/latticra-installer/src/ui.rs
grep -Fq '[lc.install]' installer/configs/default.installer.toml
grep -Fq 'install_profile = "lc-panel-install-v0"' installer/configs/default.installer.toml
grep -Fq 'allow_external_host_commands = false' installer/configs/default.installer.toml
grep -Fq 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC install configuration cannot enable external host commands from the Panel' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc install-config category=core effect=none capability=lc.install.config' installer/scripts/latticra-installer-apply.sh
grep -Fq 'install-config|install)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_COMMAND_WRAPPER="$LC_INSTALL_COMMAND_WRAPPER"' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC command wrapper ($LC_COMMAND_WRAPPER)' installer/scripts/latticra-installer-verify.sh
grep -Fq 'LC install-config registry command' installer/scripts/latticra-installer-verify.sh

HOME="$home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/default.installer.toml \
  --plan "$plan" \
  --receipt-dir "$receipt_dir" > "$run_log"

grep -Fq 'install_profile=lc-panel-install-v0' "$plan"
grep -Fq 'install_mode=metadata-only-console-foundation' "$plan"
grep -Fq 'install_config_path=etc/latticra/lc.toml' "$plan"
grep -Fq 'install_share_path=share/latticra/lc' "$plan"
grep -Fq 'install_command_wrapper=latticra-lc' "$plan"
grep -Fq 'allow_external_host_commands=false' "$plan"
grep -Fq 'lc_install_profile=lc-panel-install-v0' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_allow_external_host_commands=false' "$receipt_dir/latest-receipt.txt"
grep -Fq '[dry-run] would install LC config profile lc-panel-install-v0' "$run_log"

cat > "$live_config" <<LIVECONFIG
profile = "developer_local"
install_prefix = "$home/.local/share/latticra"
latticra_console = true
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

[lc.install]
install_profile = "lc-panel-install-v0"
install_mode = "metadata-only-console-foundation"
config_path = "etc/latticra/lc.toml"
share_path = "share/latticra/lc"
command_wrapper = "$lc_wrapper"
panel_embedded_console = true
write_config_file = true
write_profile_presets = true
write_command_registry = true
write_contract_files = true
install_user_wrapper = true
allow_external_host_commands = false
LIVECONFIG

HOME="$home" sh installer/scripts/latticra-installer-apply.sh \
  --config "$live_config" \
  --plan "$live_plan" \
  --receipt-dir "$live_receipts" > "$tmpdir/live.log"

prefix="$home/.local/share/latticra"
test -f "$prefix/etc/latticra/lc.toml"
test -f "$prefix/share/latticra/lc/install/config.toml"
test -f "$prefix/share/latticra/lc/commands/seed-registry.txt"
test -x "$home/.local/bin/latticra"
test -x "$home/.local/bin/$lc_wrapper"

grep -Fq 'install_profile = "lc-panel-install-v0"' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'allow_external_host_commands = false' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'name=lc install-config category=core effect=none capability=lc.install.config' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'lc_install_profile=lc-panel-install-v0' "$live_receipts/latest-receipt.txt"
grep -Fq "lc_install_command_wrapper=$lc_wrapper" "$live_receipts/latest-receipt.txt"

HOME="$home" "$home/.local/bin/$lc_wrapper" install-config > "$lc_report"
HOME="$home" "$home/.local/bin/latticra" lc install-config > "$latticra_lc_report"
HOME="$home" "$home/.local/bin/$lc_wrapper" help > "$lc_help"
HOME="$home" "$home/.local/bin/$lc_wrapper" man > "$lc_man"
if HOME="$home" "$home/.local/bin/$lc_wrapper" not-a-command > "$lc_usage" 2>&1; then
  echo "expected custom LC wrapper usage failure" >&2
  exit 1
fi

grep -Fq 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$lc_report"
grep -Fq 'install_profile=lc-panel-install-v0' "$lc_report"
grep -Fq "command_wrapper=$lc_wrapper" "$lc_report"
grep -Fq 'allow_external_host_commands=false' "$lc_report"
grep -Fq 'host_process_launch_allowed=0' "$lc_report"
cmp "$lc_report" "$latticra_lc_report" >/dev/null
grep -Fq "command_wrapper=$lc_wrapper" "$lc_help"
grep -Fq "  $lc_wrapper - Latticra Console metadata and operator-base surface" "$lc_man"
grep -Fq "  $lc_wrapper install-config" "$lc_man"
grep -Fq "usage: $lc_wrapper {status|help|man|boundary|commands|install-config" "$lc_usage"
if grep -Fq '  latticra-lc install-config' "$lc_man"; then
  echo "custom LC wrapper manpage still references the default wrapper command" >&2
  exit 1
fi

mkdir -p \
  "$home/.local/share/applications" \
  "$home/.local/share/icons/hicolor/256x256/apps"
cat > "$home/.local/bin/latticra-panel" <<'PANELFIXTURE'
#!/usr/bin/env sh
echo "Latticra Panel launcher fixture"
PANELFIXTURE
chmod 0755 "$home/.local/bin/latticra-panel"
cat > "$home/.local/share/applications/latticra-panel.desktop" <<DESKTOPFIXTURE
[Desktop Entry]
Name=Latticra Panel
Exec=$home/.local/bin/latticra-panel
Type=Application
DESKTOPFIXTURE
printf '%s\n' 'panel icon fixture' > "$home/.local/share/icons/hicolor/256x256/apps/latticra-panel.png"

HOME="$home" sh installer/scripts/latticra-installer-verify.sh --prefix "$prefix" > "$verify_log"
grep -Fq 'ok: LC install config' "$verify_log"
grep -Fq 'ok: LC install-config registry command' "$verify_log"
grep -Fq 'ok: LC wrapper install-config report' "$verify_log"
grep -Fq 'ok: latticra lc install-config matches LC command wrapper install-config' "$verify_log"
grep -Fq 'ok: updater config' "$verify_log"
grep -Fq 'ok: updater policy' "$verify_log"
grep -Fq 'ok: updater status report' "$verify_log"
grep -Fq 'ok: updater status apply mode' "$verify_log"

sed 's/allow_external_host_commands = false/allow_external_host_commands = true/' \
  installer/configs/default.installer.toml > "$bad_config"

if HOME="$home" sh installer/scripts/latticra-installer-apply.sh \
  --config "$bad_config" \
  --plan "$tmpdir/bad-plan.txt" \
  --receipt-dir "$tmpdir/bad-receipts" > "$tmpdir/bad.log" 2>&1; then
  echo "expected LC external host command configuration to be rejected" >&2
  exit 1
fi

grep -Fq 'LC install configuration cannot enable external host commands from the Panel' "$tmpdir/bad.log"

printf 'latticra_panel_local_install_lc_install_config: ok\n'
