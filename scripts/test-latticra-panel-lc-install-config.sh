#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra panel lc install config: %s\n' "$1" >&2
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
default_config='installer/configs/default.installer.toml'
standalone_config='installer/configs/lc-standalone.installer.toml'
standalone_local_config='installer/configs/lc-standalone-local.installer.toml'
local_config='installer/configs/local-prefix-example.installer.toml'
manifest='installer/manifests/components.toml'
foundation_doc='docs/LATTICRA_CONSOLE_FOUNDATION.md'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$ui" \
  "$config" \
  "$apply" \
  "$default_config" \
  "$standalone_config" \
  "$standalone_local_config" \
  "$local_config" \
  "$manifest" \
  "$foundation_doc" \
  "$workflow" \
  Makefile
do
  require_file "$file"
done

require_contains 'pub struct LatticraConsoleInstallConfig' "$config"
require_contains 'install: LatticraConsoleInstallConfig' "$config"
require_contains 'InstallProfile::LcStandalone' "$config"
require_contains 'LC install configuration cannot enable external host commands from the Panel.' "$config"
require_contains 'LC command wrapper must be a single command name.' "$config"
require_contains 'must be a relative path under the install prefix.' "$config"
require_contains 'LC install configuration' "$ui"
require_contains 'Install Latticra Console' "$ui"
require_contains 'Standalone console' "$ui"
require_contains 'Console only' "$ui"
require_contains 'External host commands (future; disabled)' "$ui"
require_contains '[lc.install]' "$default_config"
require_contains 'install_profile = "lc-panel-install-v0"' "$default_config"
require_contains 'standalone_console = true' "$default_config"
require_contains 'session_contract_profile = "lc-session-v0"' "$default_config"
require_contains 'require_session_contract = true' "$default_config"
require_contains 'workspace_contract_profile = "lc-workspace-v0"' "$default_config"
require_contains 'require_workspace_contract = true' "$default_config"
require_contains 'namespace_contract_profile = "lc-namespace-v0"' "$default_config"
require_contains 'require_namespace_contract = true' "$default_config"
require_contains 'rootfs_contract_profile = "lc-rootfs-v0"' "$default_config"
require_contains 'require_rootfs_contract = true' "$default_config"
require_contains 'packages_contract_profile = "lc-packages-v0"' "$default_config"
require_contains 'require_packages_contract = true' "$default_config"
require_contains 'init_contract_profile = "lc-init-v0"' "$default_config"
require_contains 'require_init_contract = true' "$default_config"
require_contains 'services_contract_profile = "lc-services-v0"' "$default_config"
require_contains 'require_services_contract = true' "$default_config"
require_contains 'allow_external_host_commands = false' "$default_config"
require_contains 'profile = "lc_standalone"' "$standalone_config"
require_contains 'profile = "standalone"' "$standalone_config"
require_contains 'install_profile = "lc-standalone-install-v0"' "$standalone_config"
require_contains 'install_mode = "metadata-only-standalone-console"' "$standalone_config"
require_contains 'standalone_console = true' "$standalone_config"
require_contains 'session_contract_profile = "lc-session-v0"' "$standalone_config"
require_contains 'workspace_contract_profile = "lc-workspace-v0"' "$standalone_config"
require_contains 'namespace_contract_profile = "lc-namespace-v0"' "$standalone_config"
require_contains 'rootfs_contract_profile = "lc-rootfs-v0"' "$standalone_config"
require_contains 'packages_contract_profile = "lc-packages-v0"' "$standalone_config"
require_contains 'init_contract_profile = "lc-init-v0"' "$standalone_config"
require_contains 'services_contract_profile = "lc-services-v0"' "$standalone_config"
require_contains 'panel_embedded_console = false' "$standalone_config"
require_contains 'allow_external_host_commands = false' "$standalone_config"
require_contains 'build_gui_installer = false' "$standalone_config"
require_contains 'install_desktop_entry = false' "$standalone_config"
require_contains 'profile = "lc_standalone"' "$standalone_local_config"
require_contains 'profile = "standalone"' "$standalone_local_config"
require_contains 'install_profile = "lc-standalone-install-v0"' "$standalone_local_config"
require_contains 'install_mode = "metadata-only-standalone-console"' "$standalone_local_config"
require_contains 'dry_run = false' "$standalone_local_config"
require_contains 'allow_host_mutation = true' "$standalone_local_config"
require_contains 'allow_network_effect = false' "$standalone_local_config"
require_contains 'panel_embedded_console = false' "$standalone_local_config"
require_contains 'build_gui_installer = false' "$standalone_local_config"
require_contains 'install_desktop_entry = false' "$standalone_local_config"
require_contains '[lc.install]' "$local_config"
require_contains 'install_user_wrapper = true' "$local_config"
require_contains 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' "$apply"
require_contains 'LC_INSTALL_STANDALONE_CONSOLE=$(cfg_section lc.install standalone_console true)' "$apply"
require_contains 'LC_SESSION_CONTRACT_PROFILE=$(cfg_section lc session_contract_profile lc-session-v0)' "$apply"
require_contains 'LC_WORKSPACE_CONTRACT_PROFILE=$(cfg_section lc workspace_contract_profile lc-workspace-v0)' "$apply"
require_contains 'LC_NAMESPACE_CONTRACT_PROFILE=$(cfg_section lc namespace_contract_profile lc-namespace-v0)' "$apply"
require_contains 'LC_ROOTFS_CONTRACT_PROFILE=$(cfg_section lc rootfs_contract_profile lc-rootfs-v0)' "$apply"
require_contains 'LC_PACKAGES_CONTRACT_PROFILE=$(cfg_section lc packages_contract_profile lc-packages-v0)' "$apply"
require_contains 'LC_INIT_CONTRACT_PROFILE=$(cfg_section lc init_contract_profile lc-init-v0)' "$apply"
require_contains 'LC_SERVICES_CONTRACT_PROFILE=$(cfg_section lc services_contract_profile lc-services-v0)' "$apply"
require_contains 'LC_INSTALL_ALLOW_EXTERNAL_HOST_COMMANDS=$(cfg_section lc.install allow_external_host_commands false)' "$apply"
require_contains 'fail "LC install configuration cannot enable external host commands from the Panel" 78' "$apply"
require_contains 'write_file "$PREFIX/share/latticra/lc/install/config.toml"' "$apply"
require_contains 'if bool_true "$LATTICRA_CONSOLE" && bool_true "$LC_INSTALL_USER_WRAPPER"; then' "$apply"
require_contains 'LC_COMMAND_WRAPPER="$LC_INSTALL_COMMAND_WRAPPER"' "$apply"
require_contains 'echo "  \$LC_COMMAND_WRAPPER install-config"' "$apply"
require_contains 'echo "usage: \$LC_COMMAND_WRAPPER {status|help|man|boundary|commands|install-config' "$apply"
require_contains 'bin/<lc.install.command_wrapper>' "$manifest"
require_contains 'share/latticra/lc/install/config.toml' "$manifest"
require_contains 'share/latticra/lc/standalone' "$manifest"
require_contains 'share/latticra/lc/session' "$manifest"
require_contains 'share/latticra/lc/workspace' "$manifest"
require_contains 'share/latticra/lc/namespace' "$manifest"
require_contains 'share/latticra/lc/rootfs' "$manifest"
require_contains 'share/latticra/lc/packages' "$manifest"
require_contains 'share/latticra/lc/init' "$manifest"
require_contains 'share/latticra/lc/services' "$manifest"
require_contains 'LC install metadata records config/share paths and the standalone command wrapper' "$manifest"
require_contains 'share/latticra/lc/install/config.toml' "$foundation_doc"
require_contains 'lc.install.command_wrapper' "$foundation_doc"
require_contains 'installer/configs/lc-standalone.installer.toml' "$foundation_doc"
require_contains 'installer/configs/lc-standalone-local.installer.toml' "$foundation_doc"
require_contains 'lc-standalone-install-v0' "$foundation_doc"
require_contains 'sh ./scripts/test-latticra-panel-lc-install-config.sh' Makefile
require_contains 'lc-standalone-dry-run' installer/Makefile
require_contains 'lc-standalone-local' installer/Makefile
require_contains 'Validate Latticra Panel LC install configuration' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel-lc-install-config-test.XXXXXX")"
mkdir -p "$tmp/home" "$tmp/receipts"
trap 'rm -rf "$tmp"' EXIT HUP INT TERM

HOME="$tmp/home" sh "$apply" \
  --config "$default_config" \
  --plan "$tmp/plan.txt" \
  --receipt-dir "$tmp/receipts" > "$tmp/dry-run.out" 2>&1

require_output_contains '[dry-run] would install LC config profile lc-panel-install-v0' "$tmp/dry-run.out"
require_contains 'install_profile=lc-panel-install-v0' "$tmp/plan.txt"
require_contains 'install_mode=metadata-only-console-foundation' "$tmp/plan.txt"
require_contains 'standalone_console=true' "$tmp/plan.txt"
require_contains 'standalone_installable=1' "$tmp/plan.txt"
require_contains 'standalone_requires_panel=0' "$tmp/plan.txt"
require_contains 'standalone_contract_present=1' "$tmp/plan.txt"
require_contains 'session_contract_present=1' "$tmp/plan.txt"
require_contains 'workspace_contract_present=1' "$tmp/plan.txt"
require_contains 'namespace_contract_present=1' "$tmp/plan.txt"
require_contains 'rootfs_contract_present=1' "$tmp/plan.txt"
require_contains 'packages_contract_present=1' "$tmp/plan.txt"
require_contains 'init_contract_present=1' "$tmp/plan.txt"
require_contains 'services_contract_present=1' "$tmp/plan.txt"
require_contains 'command_wrapper=latticra-lc' "$tmp/plan.txt"
require_contains 'allow_external_host_commands=false' "$tmp/plan.txt"
require_contains 'lc_install_profile=lc-panel-install-v0' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_standalone_console=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_standalone_requires_panel=false' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_session_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_workspace_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_namespace_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_rootfs_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_packages_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_init_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_services_contract_present=true' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_allow_external_host_commands=false' "$tmp/receipts/latest-receipt.txt"

HOME="$tmp/home" sh "$apply" \
  --config "$standalone_config" \
  --plan "$tmp/standalone-plan.txt" \
  --receipt-dir "$tmp/standalone-receipts" > "$tmp/standalone-dry-run.out" 2>&1

require_output_contains '[dry-run] would install LC config profile lc-standalone-install-v0' "$tmp/standalone-dry-run.out"
require_output_contains '[dry-run] Panel GUI build disabled by config' "$tmp/standalone-dry-run.out"
require_output_contains '[dry-run] source build disabled by config' "$tmp/standalone-dry-run.out"
require_output_contains '[dry-run] desktop entry disabled by config' "$tmp/standalone-dry-run.out"
require_contains 'profile=lc_standalone' "$tmp/standalone-plan.txt"
require_contains 'profile=standalone' "$tmp/standalone-plan.txt"
require_contains 'install_profile=lc-standalone-install-v0' "$tmp/standalone-plan.txt"
require_contains 'install_mode=metadata-only-standalone-console' "$tmp/standalone-plan.txt"
require_contains 'panel_console_bridge=standalone-optional' "$tmp/standalone-plan.txt"
require_contains 'host_embedding_profile=not-embedded' "$tmp/standalone-plan.txt"
require_contains 'standalone_console=true' "$tmp/standalone-plan.txt"
require_contains 'panel_embedded_console=false' "$tmp/standalone-plan.txt"
require_contains 'standalone_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'session_contract_profile=lc-session-v0' "$tmp/standalone-plan.txt"
require_contains 'session_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'workspace_contract_profile=lc-workspace-v0' "$tmp/standalone-plan.txt"
require_contains 'workspace_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'namespace_contract_profile=lc-namespace-v0' "$tmp/standalone-plan.txt"
require_contains 'namespace_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'rootfs_contract_profile=lc-rootfs-v0' "$tmp/standalone-plan.txt"
require_contains 'rootfs_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'packages_contract_profile=lc-packages-v0' "$tmp/standalone-plan.txt"
require_contains 'packages_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'init_contract_profile=lc-init-v0' "$tmp/standalone-plan.txt"
require_contains 'init_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'services_contract_profile=lc-services-v0' "$tmp/standalone-plan.txt"
require_contains 'services_contract_present=1' "$tmp/standalone-plan.txt"
require_contains 'allow_external_host_commands=false' "$tmp/standalone-plan.txt"
require_contains 'build_gui_installer=false' "$tmp/standalone-plan.txt"
require_contains 'install_desktop_entry=false' "$tmp/standalone-plan.txt"
require_contains 'lc_install_profile=lc-standalone-install-v0' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_standalone_console=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_standalone_requires_panel=false' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_session_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_workspace_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_namespace_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_rootfs_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_packages_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_init_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_services_contract_present=true' "$tmp/standalone-receipts/latest-receipt.txt"
require_contains 'lc_allow_external_host_commands=false' "$tmp/standalone-receipts/latest-receipt.txt"

awk '
  $0 == "allow_external_host_commands = false" {
    print "allow_external_host_commands = true"
    next
  }
  { print }
' "$default_config" > "$tmp/external-host-commands.installer.toml"

if HOME="$tmp/home" sh "$apply" \
  --config "$tmp/external-host-commands.installer.toml" \
  --plan "$tmp/bad-plan.txt" \
  --receipt-dir "$tmp/bad-receipts" > "$tmp/external-host-commands.out" 2>&1
then
  fail "LC external-host-command config unexpectedly succeeded"
fi

require_output_contains 'LC install configuration cannot enable external host commands from the Panel' "$tmp/external-host-commands.out"

printf 'latticra_panel_lc_install_config: ok\n'
