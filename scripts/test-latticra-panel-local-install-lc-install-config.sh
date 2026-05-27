#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel-lc-install-config.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

home="$tmpdir/home"
standalone_home="$tmpdir/standalone-home"
plan="$tmpdir/install-plan.txt"
receipt_dir="$tmpdir/receipts"
run_log="$tmpdir/run.log"
live_config="$tmpdir/live.installer.toml"
standalone_plan="$tmpdir/standalone-plan.txt"
standalone_receipts="$tmpdir/standalone-receipts"
standalone_log="$tmpdir/standalone.log"
standalone_local_plan="$tmpdir/standalone-local-plan.txt"
standalone_local_receipts="$tmpdir/standalone-local-receipts"
standalone_local_log="$tmpdir/standalone-local.log"
standalone_lc_report="$tmpdir/standalone-lc-install-config.txt"
standalone_contract_report="$tmpdir/standalone-contract.txt"
standalone_session_report="$tmpdir/standalone-session.txt"
standalone_workspace_report="$tmpdir/standalone-workspace.txt"
standalone_namespace_report="$tmpdir/standalone-namespace.txt"
standalone_rootfs_report="$tmpdir/standalone-rootfs.txt"
standalone_packages_report="$tmpdir/standalone-packages.txt"
standalone_init_report="$tmpdir/standalone-init.txt"
standalone_services_report="$tmpdir/standalone-services.txt"
standalone_service_schema_report="$tmpdir/standalone-service-schema.txt"
standalone_service_definitions_report="$tmpdir/standalone-service-definitions.txt"
standalone_service_plan_report="$tmpdir/standalone-service-plan.txt"
live_plan="$tmpdir/live-plan.txt"
live_receipts="$tmpdir/live-receipts"
lc_report="$tmpdir/lc-install-config.txt"
latticra_lc_report="$tmpdir/latticra-lc-install-config.txt"
lc_help="$tmpdir/lc-help.txt"
lc_man="$tmpdir/lc-man.txt"
lc_usage="$tmpdir/lc-usage.txt"
lc_service_schema_report="$tmpdir/lc-service-schema.txt"
lc_service_definitions_report="$tmpdir/lc-service-definitions.txt"
lc_service_plan_report="$tmpdir/lc-service-plan.txt"
verify_log="$tmpdir/verify.log"
lc_wrapper="latticra-console-custom"
bad_config="$tmpdir/bad.installer.toml"
symlink_home="$tmpdir/symlink-home"
symlink_config="$tmpdir/symlink.installer.toml"
symlink_plan="$tmpdir/symlink-plan.txt"
symlink_receipts="$tmpdir/symlink-receipts"
symlink_log="$tmpdir/symlink.log"
symlink_target="$tmpdir/symlink-target-lc.toml"
plan_symlink_home="$tmpdir/plan-symlink-home"
plan_symlink_path="$tmpdir/symlink-plan-path.txt"
plan_symlink_target="$tmpdir/symlink-plan-target.txt"
plan_symlink_receipts="$tmpdir/plan-symlink-receipts"
plan_symlink_log="$tmpdir/plan-symlink.log"
receipt_symlink_home="$tmpdir/receipt-symlink-home"
receipt_symlink_plan="$tmpdir/receipt-symlink-plan.txt"
receipt_symlink_dir="$tmpdir/receipt-symlink-receipts"
receipt_latest_target="$tmpdir/receipt-latest-target.txt"
receipt_symlink_log="$tmpdir/receipt-symlink.log"
icon_symlink_home="$tmpdir/icon-symlink-home"
icon_symlink_config="$tmpdir/icon-symlink.installer.toml"
icon_symlink_plan="$tmpdir/icon-symlink-plan.txt"
icon_symlink_receipts="$tmpdir/icon-symlink-receipts"
icon_symlink_log="$tmpdir/icon-symlink.log"
icon_symlink_target="$tmpdir/icon-symlink-target.png"
mkdir -p "$home" "$standalone_home" "$plan_symlink_home" "$receipt_symlink_home" "$icon_symlink_home"

grep -Fq 'pub struct LatticraConsoleInstallConfig' installer/latticra-installer/src/config.rs
grep -Fq 'pub install: LatticraConsoleInstallConfig' installer/latticra-installer/src/config.rs
grep -Fq 'LC install configuration' installer/latticra-installer/src/ui.rs
grep -Fq 'lc install-config' installer/latticra-installer/src/ui.rs
grep -Fq '[lc.install]' installer/configs/default.installer.toml
grep -Fq 'install_profile = "lc-panel-install-v0"' installer/configs/default.installer.toml
grep -Fq 'standalone_console = true' installer/configs/default.installer.toml
grep -Fq 'session_contract_profile = "lc-session-v0"' installer/configs/default.installer.toml
grep -Fq 'workspace_contract_profile = "lc-workspace-v0"' installer/configs/default.installer.toml
grep -Fq 'namespace_contract_profile = "lc-namespace-v0"' installer/configs/default.installer.toml
grep -Fq 'rootfs_contract_profile = "lc-rootfs-v0"' installer/configs/default.installer.toml
grep -Fq 'packages_contract_profile = "lc-packages-v0"' installer/configs/default.installer.toml
grep -Fq 'init_contract_profile = "lc-init-v0"' installer/configs/default.installer.toml
grep -Fq 'services_contract_profile = "lc-services-v0"' installer/configs/default.installer.toml
grep -Fq 'service_schema_contract_profile = "lc-service-schema-v0"' installer/configs/default.installer.toml
grep -Fq 'service_definitions_contract_profile = "lc-service-definitions-v0"' installer/configs/default.installer.toml
grep -Fq 'service_plan_contract_profile = "lc-service-plan-v0"' installer/configs/default.installer.toml
grep -Fq 'allow_external_host_commands = false' installer/configs/default.installer.toml
grep -Fq 'profile = "lc_standalone"' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_profile = "lc-standalone-install-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_mode = "metadata-only-standalone-console"' installer/configs/lc-standalone.installer.toml
grep -Fq 'panel_embedded_console = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'session_contract_profile = "lc-session-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'workspace_contract_profile = "lc-workspace-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'namespace_contract_profile = "lc-namespace-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'rootfs_contract_profile = "lc-rootfs-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'packages_contract_profile = "lc-packages-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'init_contract_profile = "lc-init-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'services_contract_profile = "lc-services-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'service_schema_contract_profile = "lc-service-schema-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'service_definitions_contract_profile = "lc-service-definitions-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'service_plan_contract_profile = "lc-service-plan-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'allow_external_host_commands = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'dry_run = false' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'allow_host_mutation = true' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'install_profile = "lc-standalone-install-v0"' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'panel_embedded_console = false' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_STANDALONE_CONSOLE=$(cfg_section lc.install standalone_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SESSION_CONTRACT_PROFILE=$(cfg_section lc session_contract_profile lc-session-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_WORKSPACE_CONTRACT_PROFILE=$(cfg_section lc workspace_contract_profile lc-workspace-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_NAMESPACE_CONTRACT_PROFILE=$(cfg_section lc namespace_contract_profile lc-namespace-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_ROOTFS_CONTRACT_PROFILE=$(cfg_section lc rootfs_contract_profile lc-rootfs-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PACKAGES_CONTRACT_PROFILE=$(cfg_section lc packages_contract_profile lc-packages-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INIT_CONTRACT_PROFILE=$(cfg_section lc init_contract_profile lc-init-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICES_CONTRACT_PROFILE=$(cfg_section lc services_contract_profile lc-services-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_SCHEMA_CONTRACT_PROFILE=$(cfg_section lc service_schema_contract_profile lc-service-schema-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_DEFINITIONS_CONTRACT_PROFILE=$(cfg_section lc service_definitions_contract_profile lc-service-definitions-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_PLAN_CONTRACT_PROFILE=$(cfg_section lc service_plan_contract_profile lc-service-plan-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC install configuration cannot enable external host commands from the Panel' installer/scripts/latticra-installer-apply.sh
grep -Fq 'default target not run during install' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc install-config category=core effect=none capability=lc.install.config' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc session category=core effect=none capability=lc.session.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc workspace category=core effect=none capability=lc.workspace.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc namespace category=core effect=none capability=lc.namespace.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc packages category=core effect=none capability=lc.packages.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc init category=core effect=none capability=lc.init.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc services category=core effect=none capability=lc.services.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-definitions category=core effect=none capability=lc.service.definitions.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-plan category=core effect=none capability=lc.service.plan.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'install-config|install)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_COMMAND_WRAPPER="$LC_INSTALL_COMMAND_WRAPPER"' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC command wrapper ($LC_COMMAND_WRAPPER)' installer/scripts/latticra-installer-verify.sh
grep -Fq 'LC install-config registry command' installer/scripts/latticra-installer-verify.sh

printf '%s\n' 'outside' > "$plan_symlink_target"
ln -s "$plan_symlink_target" "$plan_symlink_path"
if HOME="$plan_symlink_home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/default.installer.toml \
  --plan "$plan_symlink_path" \
  --receipt-dir "$plan_symlink_receipts" > "$plan_symlink_log" 2>&1; then
  echo "expected symlink plan write to be refused" >&2
  exit 1
fi

grep -Fq 'refusing to overwrite symlink file:' "$plan_symlink_log"
grep -Fqx 'outside' "$plan_symlink_target"
test -L "$plan_symlink_path"

mkdir -p "$receipt_symlink_dir"
printf '%s\n' 'outside' > "$receipt_latest_target"
ln -s "$receipt_latest_target" "$receipt_symlink_dir/latest-receipt.txt"
if HOME="$receipt_symlink_home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/default.installer.toml \
  --plan "$receipt_symlink_plan" \
  --receipt-dir "$receipt_symlink_dir" > "$receipt_symlink_log" 2>&1; then
  echo "expected symlink receipt latest write to be refused" >&2
  exit 1
fi

grep -Fq 'refusing to overwrite symlink file:' "$receipt_symlink_log"
grep -Fqx 'outside' "$receipt_latest_target"
test -L "$receipt_symlink_dir/latest-receipt.txt"

HOME="$home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/default.installer.toml \
  --plan "$plan" \
  --receipt-dir "$receipt_dir" > "$run_log"

grep -Fq 'install_profile=lc-panel-install-v0' "$plan"
grep -Fq 'install_mode=metadata-only-console-foundation' "$plan"
grep -Fq 'install_config_path=etc/latticra/lc.toml' "$plan"
grep -Fq 'install_share_path=share/latticra/lc' "$plan"
grep -Fq 'install_command_wrapper=latticra-lc' "$plan"
grep -Fq 'standalone_console=true' "$plan"
grep -Fq 'standalone_requires_panel=0' "$plan"
grep -Fq 'standalone_contract_present=1' "$plan"
grep -Fq 'session_contract_present=1' "$plan"
grep -Fq 'workspace_contract_present=1' "$plan"
grep -Fq 'namespace_contract_present=1' "$plan"
grep -Fq 'rootfs_contract_present=1' "$plan"
grep -Fq 'packages_contract_present=1' "$plan"
grep -Fq 'init_contract_present=1' "$plan"
grep -Fq 'services_contract_present=1' "$plan"
grep -Fq 'service_schema_contract_present=1' "$plan"
grep -Fq 'service_definitions_contract_present=1' "$plan"
grep -Fq 'service_plan_contract_present=1' "$plan"
grep -Fq 'allow_external_host_commands=false' "$plan"
grep -Fq 'lc_install_profile=lc-panel-install-v0' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_standalone_console=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_session_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_workspace_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_namespace_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_rootfs_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_packages_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_init_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_services_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_service_schema_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_service_definitions_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_service_plan_contract_present=true' "$receipt_dir/latest-receipt.txt"
grep -Fq 'lc_allow_external_host_commands=false' "$receipt_dir/latest-receipt.txt"
grep -Fq '[dry-run] would install LC config profile lc-panel-install-v0' "$run_log"

HOME="$home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/lc-standalone.installer.toml \
  --plan "$standalone_plan" \
  --receipt-dir "$standalone_receipts" > "$standalone_log"

grep -Fq 'profile=lc_standalone' "$standalone_plan"
grep -Fq 'profile=standalone' "$standalone_plan"
grep -Fq 'install_profile=lc-standalone-install-v0' "$standalone_plan"
grep -Fq 'install_mode=metadata-only-standalone-console' "$standalone_plan"
grep -Fq 'panel_embedded_console=false' "$standalone_plan"
grep -Fq 'standalone_contract_present=1' "$standalone_plan"
grep -Fq 'session_contract_present=1' "$standalone_plan"
grep -Fq 'workspace_contract_present=1' "$standalone_plan"
grep -Fq 'namespace_contract_present=1' "$standalone_plan"
grep -Fq 'rootfs_contract_present=1' "$standalone_plan"
grep -Fq 'packages_contract_present=1' "$standalone_plan"
grep -Fq 'init_contract_present=1' "$standalone_plan"
grep -Fq 'services_contract_present=1' "$standalone_plan"
grep -Fq 'service_schema_contract_present=1' "$standalone_plan"
grep -Fq 'service_definitions_contract_present=1' "$standalone_plan"
grep -Fq 'service_plan_contract_present=1' "$standalone_plan"
grep -Fq 'allow_external_host_commands=false' "$standalone_plan"
grep -Fq 'lc_install_profile=lc-standalone-install-v0' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_standalone_requires_panel=false' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_session_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_workspace_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_namespace_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_rootfs_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_packages_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_init_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_services_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_service_schema_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_service_definitions_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_service_plan_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq 'lc_rootfs_contract_present=true' "$standalone_receipts/latest-receipt.txt"
grep -Fq '[dry-run] would install LC config profile lc-standalone-install-v0' "$standalone_log"
grep -Fq '[dry-run] Panel GUI build disabled by config' "$standalone_log"
grep -Fq '[dry-run] source build disabled by config' "$standalone_log"
grep -Fq '[dry-run] desktop entry disabled by config' "$standalone_log"

HOME="$standalone_home" sh installer/scripts/latticra-installer-apply.sh \
  --config installer/configs/lc-standalone-local.installer.toml \
  --plan "$standalone_local_plan" \
  --receipt-dir "$standalone_local_receipts" > "$standalone_local_log"

standalone_prefix="$standalone_home/.local/share/latticra"
test -f "$standalone_prefix/etc/latticra/lc.toml"
test -f "$standalone_prefix/share/latticra/lc/install/config.toml"
test -f "$standalone_prefix/share/latticra/lc/standalone/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/session/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/workspace/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/namespace/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/rootfs/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/packages/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/init/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/services/contract.toml"
test -f "$standalone_prefix/share/latticra/lc/services/definition-schema.toml"
test -f "$standalone_prefix/share/latticra/lc/services/definitions.toml"
test -f "$standalone_prefix/share/latticra/lc/services/plan.toml"
test -f "$standalone_prefix/share/latticra/lc/profiles/standalone-console.toml"
test -f "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
test -x "$standalone_home/.local/bin/latticra"
test -x "$standalone_home/.local/bin/latticra-lc"
test ! -e "$standalone_home/.local/bin/latticra-panel"
test ! -e "$standalone_home/.local/share/applications/latticra-panel.desktop"

grep -Fq 'mode=local-prefix-install' "$standalone_local_plan"
grep -Fq 'profile=lc_standalone' "$standalone_local_plan"
grep -Fq 'profile=standalone' "$standalone_local_plan"
grep -Fq 'install_profile=lc-standalone-install-v0' "$standalone_local_plan"
grep -Fq 'install_mode=metadata-only-standalone-console' "$standalone_local_plan"
grep -Fq 'panel_embedded_console=false' "$standalone_local_plan"
grep -Fq 'standalone_contract_present=1' "$standalone_local_plan"
grep -Fq 'session_contract_present=1' "$standalone_local_plan"
grep -Fq 'workspace_contract_present=1' "$standalone_local_plan"
grep -Fq 'namespace_contract_present=1' "$standalone_local_plan"
grep -Fq 'rootfs_contract_present=1' "$standalone_local_plan"
grep -Fq 'packages_contract_present=1' "$standalone_local_plan"
grep -Fq 'init_contract_present=1' "$standalone_local_plan"
grep -Fq 'services_contract_present=1' "$standalone_local_plan"
grep -Fq 'service_schema_contract_present=1' "$standalone_local_plan"
grep -Fq 'service_definitions_contract_present=1' "$standalone_local_plan"
grep -Fq 'service_plan_contract_present=1' "$standalone_local_plan"
grep -Fq 'allow_external_host_commands=false' "$standalone_local_plan"
grep -Fq 'build_gui_installer=false' "$standalone_local_plan"
grep -Fq 'install_desktop_entry=false' "$standalone_local_plan"
grep -Fq 'lc_install_profile=lc-standalone-install-v0' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_standalone_console=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_standalone_requires_panel=false' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_session_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_workspace_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_namespace_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_rootfs_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_packages_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_init_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_services_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_service_schema_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_service_definitions_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_service_plan_contract_present=true' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'lc_allow_external_host_commands=false' "$standalone_local_receipts/latest-receipt.txt"
grep -Fq 'install_profile = "lc-standalone-install-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'panel_embedded_console = false' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'standalone_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'session_contract_profile = "lc-session-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'session_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'workspace_contract_profile = "lc-workspace-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'workspace_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'namespace_contract_profile = "lc-namespace-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'namespace_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'rootfs_contract_profile = "lc-rootfs-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'rootfs_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'packages_contract_profile = "lc-packages-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'packages_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'init_contract_profile = "lc-init-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'init_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'services_contract_profile = "lc-services-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'services_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_schema_contract_profile = "lc-service-schema-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_schema_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_definitions_contract_profile = "lc-service-definitions-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_definitions_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_plan_contract_profile = "lc-service-plan-v0"' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'service_plan_contract_present = true' "$standalone_prefix/share/latticra/lc/install/config.toml"
grep -Fq 'name=lc standalone category=core effect=none capability=lc.standalone.inspect' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc session category=core effect=none capability=lc.session.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc workspace category=core effect=none capability=lc.workspace.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc namespace category=core effect=none capability=lc.namespace.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc packages category=core effect=none capability=lc.packages.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc init category=core effect=none capability=lc.init.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc services category=core effect=none capability=lc.services.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-definitions category=core effect=none capability=lc.service.definitions.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-plan category=core effect=none capability=lc.service.plan.contract' "$standalone_prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'command_surface = "lc standalone"' "$standalone_prefix/share/latticra/lc/standalone/contract.toml"
grep -Fq 'command_surface = "lc session"' "$standalone_prefix/share/latticra/lc/session/contract.toml"
grep -Fq 'command_surface = "lc workspace"' "$standalone_prefix/share/latticra/lc/workspace/contract.toml"
grep -Fq 'command_surface = "lc namespace"' "$standalone_prefix/share/latticra/lc/namespace/contract.toml"
grep -Fq 'command_surface = "lc rootfs"' "$standalone_prefix/share/latticra/lc/rootfs/contract.toml"
grep -Fq 'command_surface = "lc packages"' "$standalone_prefix/share/latticra/lc/packages/contract.toml"
grep -Fq 'command_surface = "lc init"' "$standalone_prefix/share/latticra/lc/init/contract.toml"
grep -Fq 'command_surface = "lc services"' "$standalone_prefix/share/latticra/lc/services/contract.toml"
grep -Fq 'command_surface = "lc service-schema"' "$standalone_prefix/share/latticra/lc/services/definition-schema.toml"
grep -Fq 'command_surface = "lc service-definitions"' "$standalone_prefix/share/latticra/lc/services/definitions.toml"
grep -Fq 'command_surface = "lc service-plan"' "$standalone_prefix/share/latticra/lc/services/plan.toml"

HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" install-config > "$standalone_lc_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" standalone > "$standalone_contract_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" session > "$standalone_session_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" workspace > "$standalone_workspace_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" namespace > "$standalone_namespace_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" rootfs > "$standalone_rootfs_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" packages > "$standalone_packages_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" init > "$standalone_init_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" services > "$standalone_services_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" service-schema > "$standalone_service_schema_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" service-definitions > "$standalone_service_definitions_report"
HOME="$standalone_home" "$standalone_home/.local/bin/latticra-lc" service-plan > "$standalone_service_plan_report"

grep -Fq 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$standalone_lc_report"
grep -Fq 'install_profile=lc-standalone-install-v0' "$standalone_lc_report"
grep -Fq 'standalone_console=true' "$standalone_lc_report"
grep -Fq 'standalone_requires_panel=0' "$standalone_lc_report"
grep -Fq 'panel_embedded_console=false' "$standalone_lc_report"
grep -Fq 'standalone_contract_present=1' "$standalone_lc_report"
grep -Fq 'session_contract_present=1' "$standalone_lc_report"
grep -Fq 'workspace_contract_present=1' "$standalone_lc_report"
grep -Fq 'namespace_contract_present=1' "$standalone_lc_report"
grep -Fq 'rootfs_contract_present=1' "$standalone_lc_report"
grep -Fq 'packages_contract_present=1' "$standalone_lc_report"
grep -Fq 'init_contract_present=1' "$standalone_lc_report"
grep -Fq 'services_contract_present=1' "$standalone_lc_report"
grep -Fq 'service_schema_contract_present=1' "$standalone_lc_report"
grep -Fq 'service_definitions_contract_present=1' "$standalone_lc_report"
grep -Fq 'service_plan_contract_present=1' "$standalone_lc_report"
grep -Fq 'allow_external_host_commands=false' "$standalone_lc_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_lc_report"
grep -Fq 'LATTICRA CONSOLE STANDALONE CONTRACT' "$standalone_contract_report"
grep -Fq 'standalone_console_status=metadata-only-contract' "$standalone_contract_report"
grep -Fq 'standalone_requires_panel=0' "$standalone_contract_report"
grep -Fq 'panel_required_for_runtime=0' "$standalone_contract_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_contract_report"
grep -Fq 'LATTICRA CONSOLE SESSION CONTRACT' "$standalone_session_report"
grep -Fq 'session_profile=lc-session-v0' "$standalone_session_report"
grep -Fq 'runtime_session_created=0' "$standalone_session_report"
grep -Fq 'command_surface=lc session' "$standalone_session_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_session_report"
grep -Fq 'LATTICRA CONSOLE WORKSPACE CONTRACT' "$standalone_workspace_report"
grep -Fq 'workspace_profile=lc-workspace-v0' "$standalone_workspace_report"
grep -Fq 'workspace_mount_allowed=0' "$standalone_workspace_report"
grep -Fq 'command_surface=lc workspace' "$standalone_workspace_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_workspace_report"
grep -Fq 'LATTICRA CONSOLE NAMESPACE CONTRACT' "$standalone_namespace_report"
grep -Fq 'namespace_profile=lc-namespace-v0' "$standalone_namespace_report"
grep -Fq 'namespace_mount_allowed=0' "$standalone_namespace_report"
grep -Fq 'rootfs_mount_allowed=0' "$standalone_namespace_report"
grep -Fq 'command_surface=lc namespace' "$standalone_namespace_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_namespace_report"
grep -Fq 'LATTICRA CONSOLE ROOTFS CONTRACT' "$standalone_rootfs_report"
grep -Fq 'rootfs_profile=lc-rootfs-v0' "$standalone_rootfs_report"
grep -Fq 'rootfs_image_create_allowed=0' "$standalone_rootfs_report"
grep -Fq 'rootfs_mount_allowed=0' "$standalone_rootfs_report"
grep -Fq 'rootfs_package_install_allowed=0' "$standalone_rootfs_report"
grep -Fq 'command_surface=lc rootfs' "$standalone_rootfs_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_rootfs_report"
grep -Fq 'LATTICRA CONSOLE PACKAGES CONTRACT' "$standalone_packages_report"
grep -Fq 'packages_profile=lc-packages-v0' "$standalone_packages_report"
grep -Fq 'package_manifest_write_allowed=0' "$standalone_packages_report"
grep -Fq 'package_catalog_read_allowed=0' "$standalone_packages_report"
grep -Fq 'package_download_allowed=0' "$standalone_packages_report"
grep -Fq 'package_manager_execution_allowed=0' "$standalone_packages_report"
grep -Fq 'rootfs_package_install_allowed=0' "$standalone_packages_report"
grep -Fq 'command_surface=lc packages' "$standalone_packages_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_packages_report"
grep -Fq 'LATTICRA CONSOLE INIT CONTRACT' "$standalone_init_report"
grep -Fq 'init_profile=lc-init-v0' "$standalone_init_report"
grep -Fq 'pid1_claim_allowed=0' "$standalone_init_report"
grep -Fq 'service_start_allowed=0' "$standalone_init_report"
grep -Fq 'process_supervision_allowed=0' "$standalone_init_report"
grep -Fq 'command_surface=lc init' "$standalone_init_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_init_report"
grep -Fq 'LATTICRA CONSOLE SERVICES CONTRACT' "$standalone_services_report"
grep -Fq 'services_profile=lc-services-v0' "$standalone_services_report"
grep -Fq 'service_registry_write_allowed=0' "$standalone_services_report"
grep -Fq 'service_start_allowed=0' "$standalone_services_report"
grep -Fq 'service_enable_allowed=0' "$standalone_services_report"
grep -Fq 'process_supervision_allowed=0' "$standalone_services_report"
grep -Fq 'command_surface=lc services' "$standalone_services_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_services_report"
grep -Fq 'LATTICRA CONSOLE SERVICE SCHEMA CONTRACT' "$standalone_service_schema_report"
grep -Fq 'service_schema_profile=lc-service-schema-v0' "$standalone_service_schema_report"
grep -Fq 'service_schema_file=definition-schema.toml' "$standalone_service_schema_report"
grep -Fq 'service_definition_validation_allowed=0' "$standalone_service_schema_report"
grep -Fq 'command_surface=lc service-schema' "$standalone_service_schema_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_service_schema_report"
grep -Fq 'LATTICRA CONSOLE SERVICE DEFINITIONS CONTRACT' "$standalone_service_definitions_report"
grep -Fq 'service_definitions_profile=lc-service-definitions-v0' "$standalone_service_definitions_report"
grep -Fq 'service_definitions_file=definitions.toml' "$standalone_service_definitions_report"
grep -Fq 'service_definition_stub_count=0' "$standalone_service_definitions_report"
grep -Fq 'service_definition_validation_allowed=0' "$standalone_service_definitions_report"
grep -Fq 'command_surface=lc service-definitions' "$standalone_service_definitions_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_service_definitions_report"
grep -Fq 'LATTICRA CONSOLE SERVICE PLAN CONTRACT' "$standalone_service_plan_report"
grep -Fq 'service_plan_profile=lc-service-plan-v0' "$standalone_service_plan_report"
grep -Fq 'service_plan_file=plan.toml' "$standalone_service_plan_report"
grep -Fq 'service_dependency_resolution_allowed=0' "$standalone_service_plan_report"
grep -Fq 'service_activation_allowed=0' "$standalone_service_plan_report"
grep -Fq 'command_surface=lc service-plan' "$standalone_service_plan_report"
grep -Fq 'host_process_launch_allowed=0' "$standalone_service_plan_report"

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
standalone_console = true
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
test -f "$prefix/share/latticra/lc/standalone/contract.toml"
test -f "$prefix/share/latticra/lc/workspace/contract.toml"
test -f "$prefix/share/latticra/lc/namespace/contract.toml"
test -f "$prefix/share/latticra/lc/rootfs/contract.toml"
test -f "$prefix/share/latticra/lc/packages/contract.toml"
test -f "$prefix/share/latticra/lc/init/contract.toml"
test -f "$prefix/share/latticra/lc/services/contract.toml"
test -f "$prefix/share/latticra/lc/services/definition-schema.toml"
test -f "$prefix/share/latticra/lc/services/definitions.toml"
test -f "$prefix/share/latticra/lc/services/plan.toml"
test -f "$prefix/share/latticra/lc/commands/seed-registry.txt"
test -x "$home/.local/bin/latticra"
test -x "$home/.local/bin/$lc_wrapper"

grep -Fq 'install_profile = "lc-panel-install-v0"' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'standalone_console = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'standalone_requires_panel = false' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc standalone"' "$prefix/share/latticra/lc/standalone/contract.toml"
grep -Fq 'workspace_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc workspace"' "$prefix/share/latticra/lc/workspace/contract.toml"
grep -Fq 'namespace_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc namespace"' "$prefix/share/latticra/lc/namespace/contract.toml"
grep -Fq 'rootfs_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc rootfs"' "$prefix/share/latticra/lc/rootfs/contract.toml"
grep -Fq 'packages_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc packages"' "$prefix/share/latticra/lc/packages/contract.toml"
grep -Fq 'init_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc init"' "$prefix/share/latticra/lc/init/contract.toml"
grep -Fq 'services_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc services"' "$prefix/share/latticra/lc/services/contract.toml"
grep -Fq 'service_schema_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc service-schema"' "$prefix/share/latticra/lc/services/definition-schema.toml"
grep -Fq 'service_definitions_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc service-definitions"' "$prefix/share/latticra/lc/services/definitions.toml"
grep -Fq 'service_plan_contract_present = true' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'command_surface = "lc service-plan"' "$prefix/share/latticra/lc/services/plan.toml"
grep -Fq 'allow_external_host_commands = false' "$prefix/share/latticra/lc/install/config.toml"
grep -Fq 'name=lc install-config category=core effect=none capability=lc.install.config' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc workspace category=core effect=none capability=lc.workspace.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc namespace category=core effect=none capability=lc.namespace.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc packages category=core effect=none capability=lc.packages.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc init category=core effect=none capability=lc.init.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc services category=core effect=none capability=lc.services.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-definitions category=core effect=none capability=lc.service.definitions.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'name=lc service-plan category=core effect=none capability=lc.service.plan.contract' "$prefix/share/latticra/lc/commands/seed-registry.txt"
grep -Fq 'lc_install_profile=lc-panel-install-v0' "$live_receipts/latest-receipt.txt"
grep -Fq "lc_install_command_wrapper=$lc_wrapper" "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_standalone_console=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_workspace_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_namespace_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_rootfs_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_packages_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_init_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_services_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_service_schema_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_service_definitions_contract_present=true' "$live_receipts/latest-receipt.txt"
grep -Fq 'lc_service_plan_contract_present=true' "$live_receipts/latest-receipt.txt"

HOME="$home" "$home/.local/bin/$lc_wrapper" install-config > "$lc_report"
HOME="$home" "$home/.local/bin/latticra" lc install-config > "$latticra_lc_report"
HOME="$home" "$home/.local/bin/$lc_wrapper" help > "$lc_help"
HOME="$home" "$home/.local/bin/$lc_wrapper" man > "$lc_man"
HOME="$home" "$home/.local/bin/$lc_wrapper" service-schema > "$lc_service_schema_report"
HOME="$home" "$home/.local/bin/$lc_wrapper" service-definitions > "$lc_service_definitions_report"
HOME="$home" "$home/.local/bin/$lc_wrapper" service-plan > "$lc_service_plan_report"
if HOME="$home" "$home/.local/bin/$lc_wrapper" not-a-command > "$lc_usage" 2>&1; then
  echo "expected custom LC wrapper usage failure" >&2
  exit 1
fi

grep -Fq 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$lc_report"
grep -Fq 'install_profile=lc-panel-install-v0' "$lc_report"
grep -Fq 'standalone_console=true' "$lc_report"
grep -Fq 'standalone_requires_panel=0' "$lc_report"
grep -Fq 'standalone_contract_present=1' "$lc_report"
grep -Fq 'workspace_contract_present=1' "$lc_report"
grep -Fq 'namespace_contract_present=1' "$lc_report"
grep -Fq 'rootfs_contract_present=1' "$lc_report"
grep -Fq 'packages_contract_present=1' "$lc_report"
grep -Fq 'init_contract_present=1' "$lc_report"
grep -Fq 'services_contract_present=1' "$lc_report"
grep -Fq 'service_schema_contract_present=1' "$lc_report"
grep -Fq 'service_definitions_contract_present=1' "$lc_report"
grep -Fq 'service_plan_contract_present=1' "$lc_report"
grep -Fq "command_wrapper=$lc_wrapper" "$lc_report"
grep -Fq 'allow_external_host_commands=false' "$lc_report"
grep -Fq 'host_process_launch_allowed=0' "$lc_report"
cmp "$lc_report" "$latticra_lc_report" >/dev/null
grep -Fq "command_wrapper=$lc_wrapper" "$lc_help"
grep -Fq "  $lc_wrapper - Latticra Console metadata and operator-base surface" "$lc_man"
grep -Fq "  $lc_wrapper install-config" "$lc_man"
grep -Fq "  $lc_wrapper service-schema" "$lc_man"
grep -Fq "  $lc_wrapper service-definitions" "$lc_man"
grep -Fq "  $lc_wrapper service-plan" "$lc_man"
grep -Fq 'LATTICRA CONSOLE SERVICE SCHEMA CONTRACT' "$lc_service_schema_report"
grep -Fq 'command_surface=lc service-schema' "$lc_service_schema_report"
grep -Fq 'service_definition_validation_allowed=0' "$lc_service_schema_report"
grep -Fq 'LATTICRA CONSOLE SERVICE DEFINITIONS CONTRACT' "$lc_service_definitions_report"
grep -Fq 'command_surface=lc service-definitions' "$lc_service_definitions_report"
grep -Fq 'service_definition_stub_count=0' "$lc_service_definitions_report"
grep -Fq 'service_definition_validation_allowed=0' "$lc_service_definitions_report"
grep -Fq 'LATTICRA CONSOLE SERVICE PLAN CONTRACT' "$lc_service_plan_report"
grep -Fq 'command_surface=lc service-plan' "$lc_service_plan_report"
grep -Fq 'service_dependency_resolution_allowed=0' "$lc_service_plan_report"
grep -Fq 'service_activation_allowed=0' "$lc_service_plan_report"
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
grep -Fq 'ok: LC workspace registry command' "$verify_log"
grep -Fq 'ok: LC namespace registry command' "$verify_log"
grep -Fq 'ok: LC rootfs registry command' "$verify_log"
grep -Fq 'ok: LC packages registry command' "$verify_log"
grep -Fq 'ok: LC init registry command' "$verify_log"
grep -Fq 'ok: LC services registry command' "$verify_log"
grep -Fq 'ok: LC service schema registry command' "$verify_log"
grep -Fq 'ok: LC service definitions registry command' "$verify_log"
grep -Fq 'ok: LC service plan registry command' "$verify_log"
grep -Fq 'ok: LC wrapper install-config report' "$verify_log"
grep -Fq 'ok: LC wrapper workspace report' "$verify_log"
grep -Fq 'ok: LC wrapper namespace report' "$verify_log"
grep -Fq 'ok: LC wrapper rootfs report' "$verify_log"
grep -Fq 'ok: LC wrapper packages report' "$verify_log"
grep -Fq 'ok: LC wrapper init report' "$verify_log"
grep -Fq 'ok: LC wrapper services report' "$verify_log"
grep -Fq 'ok: LC wrapper service schema report' "$verify_log"
grep -Fq 'ok: LC wrapper service definitions report' "$verify_log"
grep -Fq 'ok: LC wrapper service plan report' "$verify_log"
grep -Fq 'ok: latticra lc install-config matches LC command wrapper install-config' "$verify_log"
grep -Fq 'ok: updater config' "$verify_log"
grep -Fq 'ok: updater policy' "$verify_log"
grep -Fq 'ok: updater status report' "$verify_log"
grep -Fq 'ok: updater status dry-run command' "$verify_log"
grep -Fq 'ok: updater status apply command' "$verify_log"
grep -Fq 'ok: updater policy receipt setting' "$verify_log"
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

sed \
  -e "s|install_prefix = \"$home/.local/share/latticra\"|install_prefix = \"$icon_symlink_home/.local/share/latticra\"|" \
  -e 's/install_desktop_entry = false/install_desktop_entry = true/' \
  "$live_config" > "$icon_symlink_config"
mkdir -p \
  "$icon_symlink_home/.local/share/latticra/bin" \
  "$icon_symlink_home/.local/share/icons/hicolor/256x256/apps"
printf '%s\n' '#!/usr/bin/env sh' 'exit 0' > "$icon_symlink_home/.local/share/latticra/bin/latticra-panel"
chmod 0755 "$icon_symlink_home/.local/share/latticra/bin/latticra-panel"
printf '%s\n' 'outside' > "$icon_symlink_target"
ln -s "$icon_symlink_target" "$icon_symlink_home/.local/share/icons/hicolor/256x256/apps/latticra-panel.png"

if HOME="$icon_symlink_home" sh installer/scripts/latticra-installer-apply.sh \
  --config "$icon_symlink_config" \
  --plan "$icon_symlink_plan" \
  --receipt-dir "$icon_symlink_receipts" > "$icon_symlink_log" 2>&1; then
  echo "expected symlink icon write to be refused" >&2
  exit 1
fi

grep -Fq 'refusing to overwrite symlink file:' "$icon_symlink_log"
grep -Fqx 'outside' "$icon_symlink_target"
test -L "$icon_symlink_home/.local/share/icons/hicolor/256x256/apps/latticra-panel.png"

sed "s|install_prefix = \"$home/.local/share/latticra\"|install_prefix = \"$symlink_home/.local/share/latticra\"|" \
  "$live_config" > "$symlink_config"
mkdir -p "$symlink_home/.local/share/latticra/etc/latticra"
printf '%s\n' 'outside' > "$symlink_target"
ln -s "$symlink_target" "$symlink_home/.local/share/latticra/etc/latticra/updater.toml"

if HOME="$symlink_home" sh installer/scripts/latticra-installer-apply.sh \
  --config "$symlink_config" \
  --plan "$symlink_plan" \
  --receipt-dir "$symlink_receipts" > "$symlink_log" 2>&1; then
  echo "expected symlink target write to be refused" >&2
  exit 1
fi

grep -Fq 'refusing to overwrite symlink file:' "$symlink_log"
grep -Fqx 'outside' "$symlink_target"
test -L "$symlink_home/.local/share/latticra/etc/latticra/updater.toml"

printf 'latticra_panel_local_install_lc_install_config: ok\n'
