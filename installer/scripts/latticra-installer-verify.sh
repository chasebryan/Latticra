#!/usr/bin/env sh
set -eu

PREFIX="$HOME/.local/share/latticra"
while [ "$#" -gt 0 ]; do
  case "$1" in
    --prefix)
      PREFIX="$2"
      shift 2
      ;;
    *)
      echo "unknown argument: $1" >&2
      exit 64
      ;;
  esac
done

expand_path() {
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

canonical_existing_path() {
  path="$1"
  dir=$(dirname -- "$path")
  base=$(basename -- "$path")

  resolved=$(
    cd -- "$dir" 2>/dev/null &&
      printf '%s/%s\n' "$(pwd -P)" "$base"
  ) || {
    printf '%s\n' "$path"
    return 0
  }

  printf '%s\n' "$resolved"
}

fail() {
  printf '%s\n' "$*" >&2
  exit 1
}

path_has_parent_reference() {
  case "$1" in
    ..|../*|*/..|*/../*) return 0 ;;
    *) return 1 ;;
  esac
}

prefix_is_allowed_user_local() {
  candidate="$1"
  home_real=$(canonical_existing_path "$HOME")

  case "$candidate" in
    "$HOME"/.local/share/latticra|"$HOME"/.local/share/latticra/*|"$HOME"/.local/share/latticra-validation|"$HOME"/.local/share/latticra-validation/*)
      return 0
      ;;
    "$home_real"/.local/share/latticra|"$home_real"/.local/share/latticra/*|"$home_real"/.local/share/latticra-validation|"$home_real"/.local/share/latticra-validation/*)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

PREFIX=$(expand_path "$PREFIX")

case "$PREFIX" in
  /*) ;;
  *) fail "refusing to verify unsafe prefix: $PREFIX" ;;
esac

if path_has_parent_reference "$PREFIX"; then
  fail "refusing to verify unsafe prefix with parent-directory traversal: $PREFIX"
fi

if [ -L "$PREFIX" ]; then
  fail "refusing to verify symlink prefix: $PREFIX"
fi

PREFIX_REAL=$(canonical_existing_path "$PREFIX")
if path_has_parent_reference "$PREFIX_REAL"; then
  fail "refusing to verify unsafe prefix with parent-directory traversal: $PREFIX"
fi

prefix_is_allowed_user_local "$PREFIX" &&
  prefix_is_allowed_user_local "$PREFIX_REAL" ||
  fail "refusing to verify unsafe prefix: $PREFIX"

USER_BIN="$HOME/.local/bin"
APP_FILE="$HOME/.local/share/applications/latticra-panel.desktop"
ICON_FILE="$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png"
LC_INSTALL_CONFIG="$PREFIX/share/latticra/lc/install/config.toml"
LC_COMMAND_REGISTRY="$PREFIX/share/latticra/lc/commands/seed-registry.txt"
LC_WORKSPACE_CONTRACT="$PREFIX/share/latticra/lc/workspace/contract.toml"
LC_NAMESPACE_CONTRACT="$PREFIX/share/latticra/lc/namespace/contract.toml"
LC_ROOTFS_CONTRACT="$PREFIX/share/latticra/lc/rootfs/contract.toml"
LC_PACKAGES_CONTRACT="$PREFIX/share/latticra/lc/packages/contract.toml"
LC_INIT_CONTRACT="$PREFIX/share/latticra/lc/init/contract.toml"
LC_SERVICES_CONTRACT="$PREFIX/share/latticra/lc/services/contract.toml"
LC_SERVICE_SCHEMA_CONTRACT="$PREFIX/share/latticra/lc/services/definition-schema.toml"
LC_SERVICE_DEFINITIONS_CONTRACT="$PREFIX/share/latticra/lc/services/definitions.toml"
LC_SERVICE_PLAN_CONTRACT="$PREFIX/share/latticra/lc/services/plan.toml"
UPDATER_CONFIG="$PREFIX/etc/latticra/updater.toml"
UPDATER_POLICY="$PREFIX/share/latticra/updater/policy.toml"
TMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/latticra-installer-verify.XXXXXX")"
failures=0

cleanup() {
  rm -rf "$TMP_DIR"
}

trap cleanup EXIT INT HUP TERM

toml_get_key() {
  path="$1"
  key="$2"
  [ -f "$path" ] || return 1

  awk -F '=' -v key="$key" '
    /^[[:space:]]*#/ { next }
    /^[[:space:]]*\[/ { next }
    {
      left = $1
      gsub(/^[ \t]+|[ \t]+$/, "", left)
      if (left == key) {
        val = $2
        for (i = 3; i <= NF; i++) val = val "=" $i
        sub(/[ \t]+#.*/, "", val)
        gsub(/^[ \t]+|[ \t]+$/, "", val)
        gsub(/^"/, "", val)
        gsub(/"$/, "", val)
        print val
        exit
      }
    }
  ' "$path"
}

valid_command_name() {
  case "$1" in
    ""|*/*|*" "*|*"	"*|*[!abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-]*)
      return 1
      ;;
    *)
      return 0
      ;;
  esac
}

detect_lc_command_wrapper() {
  wrapper=$(toml_get_key "$LC_INSTALL_CONFIG" command_wrapper || true)
  if valid_command_name "$wrapper"; then
    printf '%s\n' "$wrapper"
  else
    printf '%s\n' 'latticra-lc'
  fi
}

LC_COMMAND_WRAPPER=$(detect_lc_command_wrapper)
LC_COMMAND="$USER_BIN/$LC_COMMAND_WRAPPER"

check() {
  label="$1"
  path="$2"
  if [ -e "$path" ]; then
    echo "ok: $label -> $path"
  else
    echo "missing: $label -> $path" >&2
    failures=$((failures + 1))
  fi
}

check_exec() {
  label="$1"
  path="$2"
  if [ -x "$path" ]; then
    echo "ok: $label -> $path"
  else
    echo "missing/not executable: $label -> $path" >&2
    failures=$((failures + 1))
  fi
}

check_contains() {
  label="$1"
  pattern="$2"
  path="$3"
  if [ -f "$path" ] && grep -Fq -- "$pattern" "$path"; then
    echo "ok: $label"
  else
    echo "missing pattern: $label -> $path :: $pattern" >&2
    failures=$((failures + 1))
  fi
}

check_same_file() {
  label="$1"
  left="$2"
  right="$3"
  if cmp "$left" "$right" >/dev/null 2>&1; then
    echo "ok: $label"
  else
    echo "mismatch: $label" >&2
    failures=$((failures + 1))
  fi
}

check "prefix" "$PREFIX"
check "payload tree" "$PREFIX/lib/latticra"
check "config" "$PREFIX/etc/latticra/installer-config.toml"
check "receipts" "$PREFIX/share/latticra/receipts"
check_exec "latticra command" "$USER_BIN/latticra"
check_exec "LC command wrapper ($LC_COMMAND_WRAPPER)" "$LC_COMMAND"
check_exec "lat command" "$USER_BIN/lat"
check_exec "latticra-seal command" "$USER_BIN/latticra-seal"
check_exec "latticra-panel command" "$USER_BIN/latticra-panel"
check "desktop entry" "$APP_FILE"
check "desktop icon" "$ICON_FILE"
check "LC install config" "$LC_INSTALL_CONFIG"
check "LC command registry" "$LC_COMMAND_REGISTRY"
check "LC workspace contract" "$LC_WORKSPACE_CONTRACT"
check "LC namespace contract" "$LC_NAMESPACE_CONTRACT"
check "LC rootfs contract" "$LC_ROOTFS_CONTRACT"
check "LC packages contract" "$LC_PACKAGES_CONTRACT"
check "LC init contract" "$LC_INIT_CONTRACT"
check "LC services contract" "$LC_SERVICES_CONTRACT"
check "LC service schema contract" "$LC_SERVICE_SCHEMA_CONTRACT"
check "LC service definitions contract" "$LC_SERVICE_DEFINITIONS_CONTRACT"
check "LC service plan contract" "$LC_SERVICE_PLAN_CONTRACT"
check "updater config" "$UPDATER_CONFIG"
check "updater policy" "$UPDATER_POLICY"

check_contains "LC install profile metadata" 'install_profile = "lc-panel-install-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC command wrapper metadata" "command_wrapper = \"$LC_COMMAND_WRAPPER\"" "$LC_INSTALL_CONFIG"
check_contains "LC standalone console metadata" 'standalone_console = true' "$LC_INSTALL_CONFIG"
check_contains "LC standalone requires Panel disabled" 'standalone_requires_panel = false' "$LC_INSTALL_CONFIG"
check_contains "LC standalone contract metadata" 'standalone_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC session contract profile" 'session_contract_profile = "lc-session-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC session contract metadata" 'session_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC workspace contract profile" 'workspace_contract_profile = "lc-workspace-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC workspace contract metadata" 'workspace_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC namespace contract profile" 'namespace_contract_profile = "lc-namespace-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC namespace contract metadata" 'namespace_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC rootfs contract profile" 'rootfs_contract_profile = "lc-rootfs-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC rootfs contract metadata" 'rootfs_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC packages contract profile" 'packages_contract_profile = "lc-packages-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC packages contract metadata" 'packages_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC init contract profile" 'init_contract_profile = "lc-init-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC init contract metadata" 'init_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC services contract profile" 'services_contract_profile = "lc-services-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC services contract metadata" 'services_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC service schema contract profile" 'service_schema_contract_profile = "lc-service-schema-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC service schema contract metadata" 'service_schema_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC service definitions contract profile" 'service_definitions_contract_profile = "lc-service-definitions-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC service definitions contract metadata" 'service_definitions_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC service plan contract profile" 'service_plan_contract_profile = "lc-service-plan-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC service plan contract metadata" 'service_plan_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC external host command authority disabled" 'allow_external_host_commands = false' "$LC_INSTALL_CONFIG"
check_contains "LC install-config registry command" 'name=lc install-config category=core effect=none capability=lc.install.config' "$LC_COMMAND_REGISTRY"
check_contains "LC standalone registry command" 'name=lc standalone category=core effect=none capability=lc.standalone.inspect' "$LC_COMMAND_REGISTRY"
check_contains "LC session registry command" 'name=lc session category=core effect=none capability=lc.session.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC workspace registry command" 'name=lc workspace category=core effect=none capability=lc.workspace.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC namespace registry command" 'name=lc namespace category=core effect=none capability=lc.namespace.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC rootfs registry command" 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC packages registry command" 'name=lc packages category=core effect=none capability=lc.packages.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC init registry command" 'name=lc init category=core effect=none capability=lc.init.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC services registry command" 'name=lc services category=core effect=none capability=lc.services.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC service schema registry command" 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC service definitions registry command" 'name=lc service-definitions category=core effect=none capability=lc.service.definitions.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC service plan registry command" 'name=lc service-plan category=core effect=none capability=lc.service.plan.contract' "$LC_COMMAND_REGISTRY"
check_contains "LC workspace command surface" 'command_surface = "lc workspace"' "$LC_WORKSPACE_CONTRACT"
check_contains "LC workspace mount denied" 'workspace_mount_allowed = false' "$LC_WORKSPACE_CONTRACT"
check_contains "LC workspace host process denied" 'host_process_launch_allowed = false' "$LC_WORKSPACE_CONTRACT"
check_contains "LC namespace command surface" 'command_surface = "lc namespace"' "$LC_NAMESPACE_CONTRACT"
check_contains "LC namespace mount denied" 'namespace_mount_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "LC namespace rootfs mount denied" 'rootfs_mount_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "LC namespace host process denied" 'host_process_launch_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "LC rootfs command surface" 'command_surface = "lc rootfs"' "$LC_ROOTFS_CONTRACT"
check_contains "LC rootfs image creation denied" 'rootfs_image_create_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "LC rootfs mount denied" 'rootfs_mount_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "LC rootfs package install denied" 'rootfs_package_install_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "LC rootfs host process denied" 'host_process_launch_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "LC packages command surface" 'command_surface = "lc packages"' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages manifest write denied" 'package_manifest_write_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages catalog read denied" 'package_catalog_read_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages download denied" 'package_download_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages manager execution denied" 'package_manager_execution_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages rootfs install denied" 'rootfs_package_install_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC packages host process denied" 'host_process_launch_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "LC init command surface" 'command_surface = "lc init"' "$LC_INIT_CONTRACT"
check_contains "LC init PID 1 denied" 'pid1_claim_allowed = false' "$LC_INIT_CONTRACT"
check_contains "LC init service start denied" 'service_start_allowed = false' "$LC_INIT_CONTRACT"
check_contains "LC init process supervision denied" 'process_supervision_allowed = false' "$LC_INIT_CONTRACT"
check_contains "LC init host process denied" 'host_process_launch_allowed = false' "$LC_INIT_CONTRACT"
check_contains "LC services command surface" 'command_surface = "lc services"' "$LC_SERVICES_CONTRACT"
check_contains "LC services registry write denied" 'service_registry_write_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "LC services start denied" 'service_start_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "LC services enable denied" 'service_enable_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "LC services process supervision denied" 'process_supervision_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "LC services host process denied" 'host_process_launch_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "LC service schema command surface" 'command_surface = "lc service-schema"' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "LC service schema file marker" 'service_schema_file = "definition-schema.toml"' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "LC service schema validation denied" 'service_definition_validation_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "LC service schema start denied" 'service_start_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "LC service schema host process denied" 'host_process_launch_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "LC service definitions command surface" 'command_surface = "lc service-definitions"' "$LC_SERVICE_DEFINITIONS_CONTRACT"
check_contains "LC service definitions file marker" 'service_definitions_file = "definitions.toml"' "$LC_SERVICE_DEFINITIONS_CONTRACT"
check_contains "LC service definitions validation denied" 'service_definition_validation_allowed = false' "$LC_SERVICE_DEFINITIONS_CONTRACT"
check_contains "LC service definitions start denied" 'service_start_allowed = false' "$LC_SERVICE_DEFINITIONS_CONTRACT"
check_contains "LC service definitions host process denied" 'host_process_launch_allowed = false' "$LC_SERVICE_DEFINITIONS_CONTRACT"
check_contains "LC service plan command surface" 'command_surface = "lc service-plan"' "$LC_SERVICE_PLAN_CONTRACT"
check_contains "LC service plan file marker" 'service_plan_file = "plan.toml"' "$LC_SERVICE_PLAN_CONTRACT"
check_contains "LC service plan dependency resolution denied" 'service_dependency_resolution_allowed = false' "$LC_SERVICE_PLAN_CONTRACT"
check_contains "LC service plan activation denied" 'service_activation_allowed = false' "$LC_SERVICE_PLAN_CONTRACT"
check_contains "LC service plan host process denied" 'host_process_launch_allowed = false' "$LC_SERVICE_PLAN_CONTRACT"
check_contains "updater panel-owned config" 'panel_owned = true' "$UPDATER_CONFIG"
check_contains "updater network authority disabled" 'allow_network_fetch = false' "$UPDATER_CONFIG"
check_contains "updater apply mode" 'update_apply_mode = "guarded-local-prefix-reinstall"' "$UPDATER_CONFIG"
check_contains "updater signed delivery gate closed" 'signed_delivery_gate = "closed"' "$UPDATER_CONFIG"
check_contains "updater signed manifest required" 'signed_manifest_required = true' "$UPDATER_CONFIG"
check_contains "updater signed manifest absent" 'signed_manifest_present = false' "$UPDATER_CONFIG"
check_contains "updater signed apply disabled" 'signed_update_apply_allowed = false' "$UPDATER_CONFIG"
check_contains "updater policy name" 'name = "Latticra Panel Updater"' "$UPDATER_POLICY"
check_contains "updater policy dry-run command" 'preview_command = "updater dry-run"' "$UPDATER_POLICY"
check_contains "updater policy apply command" 'apply_command = "updater apply"' "$UPDATER_POLICY"
check_contains "updater policy network authority disabled" 'network_fetch_authority = false' "$UPDATER_POLICY"
check_contains "updater policy receipt setting" 'write_update_receipt = true' "$UPDATER_POLICY"
check_contains "updater policy apply mode" 'update_apply_mode = "guarded-local-prefix-reinstall"' "$UPDATER_POLICY"
check_contains "updater policy signed delivery gate closed" 'signed_delivery_gate = "closed"' "$UPDATER_POLICY"
check_contains "updater policy signed manifest required" 'signed_manifest_required = true' "$UPDATER_POLICY"
check_contains "updater policy signed apply disabled" 'signed_update_apply_allowed = false' "$UPDATER_POLICY"

if [ -x "$USER_BIN/latticra" ]; then
  "$USER_BIN/latticra" status || failures=$((failures + 1))
  if "$USER_BIN/latticra" updater status > "$TMP_DIR/updater-status.txt"; then
    check_contains "updater status report" 'LATTICRA PANEL UPDATER' "$TMP_DIR/updater-status.txt"
    check_contains "updater status config path" "config=$UPDATER_CONFIG" "$TMP_DIR/updater-status.txt"
    check_contains "updater status policy path" "policy=$UPDATER_POLICY" "$TMP_DIR/updater-status.txt"
    check_contains "updater status dry-run command" 'preview_command=updater dry-run' "$TMP_DIR/updater-status.txt"
    check_contains "updater status apply command" 'apply_command=updater apply' "$TMP_DIR/updater-status.txt"
    check_contains "updater status network fetch authority disabled" 'network_fetch_authority=0' "$TMP_DIR/updater-status.txt"
    check_contains "updater status network authority disabled" 'network_authority=0' "$TMP_DIR/updater-status.txt"
    check_contains "updater status apply mode" 'update_apply_mode=guarded-local-prefix-reinstall' "$TMP_DIR/updater-status.txt"
    check_contains "updater status signed delivery gate closed" 'signed_delivery_gate=closed' "$TMP_DIR/updater-status.txt"
    check_contains "updater status signed manifest required" 'signed_manifest_required=1' "$TMP_DIR/updater-status.txt"
    check_contains "updater status signed manifest absent" 'signed_manifest_present=0' "$TMP_DIR/updater-status.txt"
    check_contains "updater status signed apply disabled" 'signed_update_apply_allowed=0' "$TMP_DIR/updater-status.txt"
    check_contains "updater status signed delivery not ready" 'signed_update_delivery_ready=0' "$TMP_DIR/updater-status.txt"
  else
    echo "failed: latticra updater status" >&2
    failures=$((failures + 1))
  fi
fi

if [ -x "$LC_COMMAND" ]; then
  if "$LC_COMMAND" install-config > "$TMP_DIR/lc-install-config.txt"; then
    check_contains "LC wrapper install-config report" 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper install profile" 'install_profile=lc-panel-install-v0' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper command name" "command_wrapper=$LC_COMMAND_WRAPPER" "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper standalone enabled" 'standalone_console=true' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper standalone requires Panel denied" 'standalone_requires_panel=0' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper standalone contract present" 'standalone_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper session contract present" 'session_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper workspace contract present" 'workspace_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper namespace contract present" 'namespace_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper rootfs contract present" 'rootfs_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper packages contract present" 'packages_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper init contract present" 'init_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper services contract present" 'services_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper service schema contract present" 'service_schema_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper service definitions contract present" 'service_definitions_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper service plan contract present" 'service_plan_contract_present=1' "$TMP_DIR/lc-install-config.txt"
    check_contains "LC wrapper host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-install-config.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER install-config" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" session > "$TMP_DIR/lc-session.txt"; then
    check_contains "LC wrapper session report" 'LATTICRA CONSOLE SESSION CONTRACT' "$TMP_DIR/lc-session.txt"
    check_contains "LC wrapper session command surface" 'command_surface=lc session' "$TMP_DIR/lc-session.txt"
    check_contains "LC wrapper session runtime denied" 'runtime_session_created=0' "$TMP_DIR/lc-session.txt"
    check_contains "LC wrapper session host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-session.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER session" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" workspace > "$TMP_DIR/lc-workspace.txt"; then
    check_contains "LC wrapper workspace report" 'LATTICRA CONSOLE WORKSPACE CONTRACT' "$TMP_DIR/lc-workspace.txt"
    check_contains "LC wrapper workspace command surface" 'command_surface=lc workspace' "$TMP_DIR/lc-workspace.txt"
    check_contains "LC wrapper workspace mount denied" 'workspace_mount_allowed=0' "$TMP_DIR/lc-workspace.txt"
    check_contains "LC wrapper workspace host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-workspace.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER workspace" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" namespace > "$TMP_DIR/lc-namespace.txt"; then
    check_contains "LC wrapper namespace report" 'LATTICRA CONSOLE NAMESPACE CONTRACT' "$TMP_DIR/lc-namespace.txt"
    check_contains "LC wrapper namespace command surface" 'command_surface=lc namespace' "$TMP_DIR/lc-namespace.txt"
    check_contains "LC wrapper namespace mount denied" 'namespace_mount_allowed=0' "$TMP_DIR/lc-namespace.txt"
    check_contains "LC wrapper namespace rootfs mount denied" 'rootfs_mount_allowed=0' "$TMP_DIR/lc-namespace.txt"
    check_contains "LC wrapper namespace host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-namespace.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER namespace" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" rootfs > "$TMP_DIR/lc-rootfs.txt"; then
    check_contains "LC wrapper rootfs report" 'LATTICRA CONSOLE ROOTFS CONTRACT' "$TMP_DIR/lc-rootfs.txt"
    check_contains "LC wrapper rootfs command surface" 'command_surface=lc rootfs' "$TMP_DIR/lc-rootfs.txt"
    check_contains "LC wrapper rootfs image creation denied" 'rootfs_image_create_allowed=0' "$TMP_DIR/lc-rootfs.txt"
    check_contains "LC wrapper rootfs mount denied" 'rootfs_mount_allowed=0' "$TMP_DIR/lc-rootfs.txt"
    check_contains "LC wrapper rootfs package install denied" 'rootfs_package_install_allowed=0' "$TMP_DIR/lc-rootfs.txt"
    check_contains "LC wrapper rootfs host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-rootfs.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER rootfs" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" packages > "$TMP_DIR/lc-packages.txt"; then
    check_contains "LC wrapper packages report" 'LATTICRA CONSOLE PACKAGES CONTRACT' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages command surface" 'command_surface=lc packages' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages manifest write denied" 'package_manifest_write_allowed=0' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages catalog read denied" 'package_catalog_read_allowed=0' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages download denied" 'package_download_allowed=0' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages manager execution denied" 'package_manager_execution_allowed=0' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages rootfs install denied" 'rootfs_package_install_allowed=0' "$TMP_DIR/lc-packages.txt"
    check_contains "LC wrapper packages host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-packages.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER packages" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" init > "$TMP_DIR/lc-init.txt"; then
    check_contains "LC wrapper init report" 'LATTICRA CONSOLE INIT CONTRACT' "$TMP_DIR/lc-init.txt"
    check_contains "LC wrapper init command surface" 'command_surface=lc init' "$TMP_DIR/lc-init.txt"
    check_contains "LC wrapper init PID 1 denied" 'pid1_claim_allowed=0' "$TMP_DIR/lc-init.txt"
    check_contains "LC wrapper init service start denied" 'service_start_allowed=0' "$TMP_DIR/lc-init.txt"
    check_contains "LC wrapper init process supervision denied" 'process_supervision_allowed=0' "$TMP_DIR/lc-init.txt"
    check_contains "LC wrapper init host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-init.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER init" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" services > "$TMP_DIR/lc-services.txt"; then
    check_contains "LC wrapper services report" 'LATTICRA CONSOLE SERVICES CONTRACT' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services command surface" 'command_surface=lc services' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services registry write denied" 'service_registry_write_allowed=0' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services start denied" 'service_start_allowed=0' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services enable denied" 'service_enable_allowed=0' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services process supervision denied" 'process_supervision_allowed=0' "$TMP_DIR/lc-services.txt"
    check_contains "LC wrapper services host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-services.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER services" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" service-schema > "$TMP_DIR/lc-service-schema.txt"; then
    check_contains "LC wrapper service schema report" 'LATTICRA CONSOLE SERVICE SCHEMA CONTRACT' "$TMP_DIR/lc-service-schema.txt"
    check_contains "LC wrapper service schema command surface" 'command_surface=lc service-schema' "$TMP_DIR/lc-service-schema.txt"
    check_contains "LC wrapper service schema file" 'service_schema_file=definition-schema.toml' "$TMP_DIR/lc-service-schema.txt"
    check_contains "LC wrapper service schema validation denied" 'service_definition_validation_allowed=0' "$TMP_DIR/lc-service-schema.txt"
    check_contains "LC wrapper service schema host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-service-schema.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER service-schema" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" service-definitions > "$TMP_DIR/lc-service-definitions.txt"; then
    check_contains "LC wrapper service definitions report" 'LATTICRA CONSOLE SERVICE DEFINITIONS CONTRACT' "$TMP_DIR/lc-service-definitions.txt"
    check_contains "LC wrapper service definitions command surface" 'command_surface=lc service-definitions' "$TMP_DIR/lc-service-definitions.txt"
    check_contains "LC wrapper service definitions file" 'service_definitions_file=definitions.toml' "$TMP_DIR/lc-service-definitions.txt"
    check_contains "LC wrapper service definitions stub count" 'service_definition_stub_count=0' "$TMP_DIR/lc-service-definitions.txt"
    check_contains "LC wrapper service definitions validation denied" 'service_definition_validation_allowed=0' "$TMP_DIR/lc-service-definitions.txt"
    check_contains "LC wrapper service definitions host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-service-definitions.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER service-definitions" >&2
    failures=$((failures + 1))
  fi

  if "$LC_COMMAND" service-plan > "$TMP_DIR/lc-service-plan.txt"; then
    check_contains "LC wrapper service plan report" 'LATTICRA CONSOLE SERVICE PLAN CONTRACT' "$TMP_DIR/lc-service-plan.txt"
    check_contains "LC wrapper service plan command surface" 'command_surface=lc service-plan' "$TMP_DIR/lc-service-plan.txt"
    check_contains "LC wrapper service plan file" 'service_plan_file=plan.toml' "$TMP_DIR/lc-service-plan.txt"
    check_contains "LC wrapper service plan dependency resolution denied" 'service_dependency_resolution_allowed=0' "$TMP_DIR/lc-service-plan.txt"
    check_contains "LC wrapper service plan activation denied" 'service_activation_allowed=0' "$TMP_DIR/lc-service-plan.txt"
    check_contains "LC wrapper service plan host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-service-plan.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER service-plan" >&2
    failures=$((failures + 1))
  fi
fi

if [ -x "$USER_BIN/latticra" ] && [ -x "$LC_COMMAND" ]; then
  if "$USER_BIN/latticra" lc install-config > "$TMP_DIR/latticra-lc-install-config.txt"; then
    check_contains "Latticra wrapper LC install-config report" 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$TMP_DIR/latticra-lc-install-config.txt"
    if [ -f "$TMP_DIR/lc-install-config.txt" ]; then
      check_same_file "latticra lc install-config matches LC command wrapper install-config" "$TMP_DIR/lc-install-config.txt" "$TMP_DIR/latticra-lc-install-config.txt"
    fi
  else
    echo "failed: latticra lc install-config" >&2
    failures=$((failures + 1))
  fi
fi

if [ -x "$USER_BIN/latticra-seal" ]; then
  "$USER_BIN/latticra-seal" report >/dev/null || failures=$((failures + 1))
  echo "ok: latticra-seal report generated"
fi

if [ -x "$USER_BIN/latticra-panel" ]; then
  echo "ok: Latticra Panel launcher is available"
fi

if [ "$failures" -eq 0 ]; then
  echo "Latticra local install verification: ok"
  exit 0
fi

echo "Latticra local install verification: failed checks=$failures" >&2
exit 1
