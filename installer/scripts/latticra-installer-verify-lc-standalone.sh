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

USER_BIN="$HOME/.local/bin"
LC_CONFIG="$PREFIX/share/latticra/lc/install/config.toml"
LC_REGISTRY="$PREFIX/share/latticra/lc/commands/seed-registry.txt"
LC_CONTRACT="$PREFIX/share/latticra/lc/standalone/contract.toml"
LC_SESSION_CONTRACT="$PREFIX/share/latticra/lc/session/contract.toml"
LC_WORKSPACE_CONTRACT="$PREFIX/share/latticra/lc/workspace/contract.toml"
LC_NAMESPACE_CONTRACT="$PREFIX/share/latticra/lc/namespace/contract.toml"
LC_ROOTFS_CONTRACT="$PREFIX/share/latticra/lc/rootfs/contract.toml"
LC_PACKAGES_CONTRACT="$PREFIX/share/latticra/lc/packages/contract.toml"
LC_INIT_CONTRACT="$PREFIX/share/latticra/lc/init/contract.toml"
LC_SERVICES_CONTRACT="$PREFIX/share/latticra/lc/services/contract.toml"
LC_SERVICE_SCHEMA_CONTRACT="$PREFIX/share/latticra/lc/services/definition-schema.toml"
LC_PROFILE="$PREFIX/share/latticra/lc/profiles/standalone-console.toml"
TMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/latticra-lc-standalone-verify.XXXXXX")"
failures=0

cleanup() {
  rm -rf "$TMP_DIR"
}

trap cleanup EXIT INT HUP TERM

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

check_absent() {
  label="$1"
  path="$2"
  if [ ! -e "$path" ]; then
    echo "ok: absent $label -> $path"
  else
    echo "unexpected: $label -> $path" >&2
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

check "prefix" "$PREFIX"
check "LC install config" "$LC_CONFIG"
check "LC seed registry" "$LC_REGISTRY"
check "LC standalone contract" "$LC_CONTRACT"
check "LC session contract" "$LC_SESSION_CONTRACT"
check "LC workspace contract" "$LC_WORKSPACE_CONTRACT"
check "LC namespace contract" "$LC_NAMESPACE_CONTRACT"
check "LC rootfs contract" "$LC_ROOTFS_CONTRACT"
check "LC packages contract" "$LC_PACKAGES_CONTRACT"
check "LC init contract" "$LC_INIT_CONTRACT"
check "LC services contract" "$LC_SERVICES_CONTRACT"
check "LC service schema contract" "$LC_SERVICE_SCHEMA_CONTRACT"
check "LC standalone profile" "$LC_PROFILE"
check_exec "latticra command" "$USER_BIN/latticra"
check_exec "LC command wrapper" "$USER_BIN/latticra-lc"
check_absent "Latticra Panel launcher" "$USER_BIN/latticra-panel"
check_absent "Latticra Panel desktop entry" "$HOME/.local/share/applications/latticra-panel.desktop"

check_contains "standalone install profile" 'install_profile = "lc-standalone-install-v0"' "$LC_CONFIG"
check_contains "standalone install mode" 'install_mode = "metadata-only-standalone-console"' "$LC_CONFIG"
check_contains "standalone console enabled" 'standalone_console = true' "$LC_CONFIG"
check_contains "standalone requires Panel disabled" 'standalone_requires_panel = false' "$LC_CONFIG"
check_contains "standalone contract present" 'standalone_contract_present = true' "$LC_CONFIG"
check_contains "session contract profile" 'session_contract_profile = "lc-session-v0"' "$LC_CONFIG"
check_contains "session contract present" 'session_contract_present = true' "$LC_CONFIG"
check_contains "workspace contract profile" 'workspace_contract_profile = "lc-workspace-v0"' "$LC_CONFIG"
check_contains "workspace contract present" 'workspace_contract_present = true' "$LC_CONFIG"
check_contains "namespace contract profile" 'namespace_contract_profile = "lc-namespace-v0"' "$LC_CONFIG"
check_contains "namespace contract present" 'namespace_contract_present = true' "$LC_CONFIG"
check_contains "rootfs contract profile" 'rootfs_contract_profile = "lc-rootfs-v0"' "$LC_CONFIG"
check_contains "rootfs contract present" 'rootfs_contract_present = true' "$LC_CONFIG"
check_contains "packages contract profile" 'packages_contract_profile = "lc-packages-v0"' "$LC_CONFIG"
check_contains "packages contract present" 'packages_contract_present = true' "$LC_CONFIG"
check_contains "init contract profile" 'init_contract_profile = "lc-init-v0"' "$LC_CONFIG"
check_contains "init contract present" 'init_contract_present = true' "$LC_CONFIG"
check_contains "services contract profile" 'services_contract_profile = "lc-services-v0"' "$LC_CONFIG"
check_contains "services contract present" 'services_contract_present = true' "$LC_CONFIG"
check_contains "service schema contract profile" 'service_schema_contract_profile = "lc-service-schema-v0"' "$LC_CONFIG"
check_contains "service schema contract present" 'service_schema_contract_present = true' "$LC_CONFIG"
check_contains "Panel embedding disabled" 'panel_embedded_console = false' "$LC_CONFIG"
check_contains "external host commands disabled" 'allow_external_host_commands = false' "$LC_CONFIG"
check_contains "standalone registry command" 'name=lc standalone category=core effect=none capability=lc.standalone.inspect' "$LC_REGISTRY"
check_contains "session registry command" 'name=lc session category=core effect=none capability=lc.session.contract' "$LC_REGISTRY"
check_contains "workspace registry command" 'name=lc workspace category=core effect=none capability=lc.workspace.contract' "$LC_REGISTRY"
check_contains "namespace registry command" 'name=lc namespace category=core effect=none capability=lc.namespace.contract' "$LC_REGISTRY"
check_contains "rootfs registry command" 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' "$LC_REGISTRY"
check_contains "packages registry command" 'name=lc packages category=core effect=none capability=lc.packages.contract' "$LC_REGISTRY"
check_contains "init registry command" 'name=lc init category=core effect=none capability=lc.init.contract' "$LC_REGISTRY"
check_contains "services registry command" 'name=lc services category=core effect=none capability=lc.services.contract' "$LC_REGISTRY"
check_contains "service schema registry command" 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' "$LC_REGISTRY"
check_contains "standalone command surface" 'command_surface = "lc standalone"' "$LC_CONTRACT"
check_contains "standalone host process denial" 'host_process_launch_allowed = false' "$LC_CONTRACT"
check_contains "standalone network denial" 'network_allowed = false' "$LC_CONTRACT"
check_contains "session command surface" 'command_surface = "lc session"' "$LC_SESSION_CONTRACT"
check_contains "session runtime denied" 'runtime_session_created = false' "$LC_SESSION_CONTRACT"
check_contains "session host process denied" 'host_process_launch_allowed = false' "$LC_SESSION_CONTRACT"
check_contains "workspace command surface" 'command_surface = "lc workspace"' "$LC_WORKSPACE_CONTRACT"
check_contains "workspace mount denied" 'workspace_mount_allowed = false' "$LC_WORKSPACE_CONTRACT"
check_contains "workspace file write denied" 'workspace_file_write_allowed = false' "$LC_WORKSPACE_CONTRACT"
check_contains "workspace host process denied" 'host_process_launch_allowed = false' "$LC_WORKSPACE_CONTRACT"
check_contains "namespace command surface" 'command_surface = "lc namespace"' "$LC_NAMESPACE_CONTRACT"
check_contains "namespace mount denied" 'namespace_mount_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "namespace rootfs mount denied" 'rootfs_mount_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "namespace host process denied" 'host_process_launch_allowed = false' "$LC_NAMESPACE_CONTRACT"
check_contains "rootfs command surface" 'command_surface = "lc rootfs"' "$LC_ROOTFS_CONTRACT"
check_contains "rootfs image creation denied" 'rootfs_image_create_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "rootfs mount denied" 'rootfs_mount_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "rootfs package install denied" 'rootfs_package_install_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "rootfs host process denied" 'host_process_launch_allowed = false' "$LC_ROOTFS_CONTRACT"
check_contains "packages command surface" 'command_surface = "lc packages"' "$LC_PACKAGES_CONTRACT"
check_contains "packages manifest write denied" 'package_manifest_write_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "packages catalog read denied" 'package_catalog_read_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "packages download denied" 'package_download_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "packages manager execution denied" 'package_manager_execution_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "packages rootfs install denied" 'rootfs_package_install_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "packages host process denied" 'host_process_launch_allowed = false' "$LC_PACKAGES_CONTRACT"
check_contains "init command surface" 'command_surface = "lc init"' "$LC_INIT_CONTRACT"
check_contains "init PID 1 denied" 'pid1_claim_allowed = false' "$LC_INIT_CONTRACT"
check_contains "init service start denied" 'service_start_allowed = false' "$LC_INIT_CONTRACT"
check_contains "init process supervision denied" 'process_supervision_allowed = false' "$LC_INIT_CONTRACT"
check_contains "init host process denied" 'host_process_launch_allowed = false' "$LC_INIT_CONTRACT"
check_contains "services command surface" 'command_surface = "lc services"' "$LC_SERVICES_CONTRACT"
check_contains "services registry write denied" 'service_registry_write_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "services start denied" 'service_start_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "services enable denied" 'service_enable_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "services process supervision denied" 'process_supervision_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "services host process denied" 'host_process_launch_allowed = false' "$LC_SERVICES_CONTRACT"
check_contains "service schema command surface" 'command_surface = "lc service-schema"' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "service schema file marker" 'service_schema_file = "definition-schema.toml"' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "service schema definition validation denied" 'service_definition_validation_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "service schema start denied" 'service_start_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"
check_contains "service schema host process denied" 'host_process_launch_allowed = false' "$LC_SERVICE_SCHEMA_CONTRACT"

if [ -x "$USER_BIN/latticra-lc" ]; then
  if "$USER_BIN/latticra-lc" install-config > "$TMP_DIR/install-config.txt"; then
    check_contains "LC wrapper install-config report" 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper standalone install profile" 'install_profile=lc-standalone-install-v0' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper standalone enabled" 'standalone_console=true' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper session contract present" 'session_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper workspace contract present" 'workspace_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper namespace contract present" 'namespace_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper rootfs contract present" 'rootfs_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper packages contract present" 'packages_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper init contract present" 'init_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper services contract present" 'services_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper service schema contract present" 'service_schema_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper Panel embedding disabled" 'panel_embedded_console=false' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper host process denial" 'host_process_launch_allowed=0' "$TMP_DIR/install-config.txt"
  else
    echo "failed: latticra-lc install-config" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" standalone > "$TMP_DIR/standalone.txt"; then
    check_contains "LC wrapper standalone report" 'LATTICRA CONSOLE STANDALONE CONTRACT' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper standalone requires Panel denied" 'standalone_requires_panel=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper Panel runtime denied" 'panel_required_for_runtime=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper host process denial" 'host_process_launch_allowed=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper production OS claim denied" 'production_os_claim=0' "$TMP_DIR/standalone.txt"
  else
    echo "failed: latticra-lc standalone" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" session > "$TMP_DIR/session.txt"; then
    check_contains "LC wrapper session report" 'LATTICRA CONSOLE SESSION CONTRACT' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session command surface" 'command_surface=lc session' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session runtime denied" 'runtime_session_created=0' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session production OS claim denied" 'production_os_claim=0' "$TMP_DIR/session.txt"
  else
    echo "failed: latticra-lc session" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" workspace > "$TMP_DIR/workspace.txt"; then
    check_contains "LC wrapper workspace report" 'LATTICRA CONSOLE WORKSPACE CONTRACT' "$TMP_DIR/workspace.txt"
    check_contains "LC wrapper workspace command surface" 'command_surface=lc workspace' "$TMP_DIR/workspace.txt"
    check_contains "LC wrapper workspace mount denied" 'workspace_mount_allowed=0' "$TMP_DIR/workspace.txt"
    check_contains "LC wrapper workspace file write denied" 'workspace_file_write_allowed=0' "$TMP_DIR/workspace.txt"
    check_contains "LC wrapper workspace host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/workspace.txt"
    check_contains "LC wrapper workspace production OS claim denied" 'production_os_claim=0' "$TMP_DIR/workspace.txt"
  else
    echo "failed: latticra-lc workspace" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" namespace > "$TMP_DIR/namespace.txt"; then
    check_contains "LC wrapper namespace report" 'LATTICRA CONSOLE NAMESPACE CONTRACT' "$TMP_DIR/namespace.txt"
    check_contains "LC wrapper namespace command surface" 'command_surface=lc namespace' "$TMP_DIR/namespace.txt"
    check_contains "LC wrapper namespace mount denied" 'namespace_mount_allowed=0' "$TMP_DIR/namespace.txt"
    check_contains "LC wrapper namespace rootfs mount denied" 'rootfs_mount_allowed=0' "$TMP_DIR/namespace.txt"
    check_contains "LC wrapper namespace host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/namespace.txt"
    check_contains "LC wrapper namespace production OS claim denied" 'production_os_claim=0' "$TMP_DIR/namespace.txt"
  else
    echo "failed: latticra-lc namespace" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" rootfs > "$TMP_DIR/rootfs.txt"; then
    check_contains "LC wrapper rootfs report" 'LATTICRA CONSOLE ROOTFS CONTRACT' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs command surface" 'command_surface=lc rootfs' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs image creation denied" 'rootfs_image_create_allowed=0' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs mount denied" 'rootfs_mount_allowed=0' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs package install denied" 'rootfs_package_install_allowed=0' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/rootfs.txt"
    check_contains "LC wrapper rootfs production OS claim denied" 'production_os_claim=0' "$TMP_DIR/rootfs.txt"
  else
    echo "failed: latticra-lc rootfs" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" packages > "$TMP_DIR/packages.txt"; then
    check_contains "LC wrapper packages report" 'LATTICRA CONSOLE PACKAGES CONTRACT' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages command surface" 'command_surface=lc packages' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages manifest write denied" 'package_manifest_write_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages catalog read denied" 'package_catalog_read_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages download denied" 'package_download_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages manager execution denied" 'package_manager_execution_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages rootfs install denied" 'rootfs_package_install_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/packages.txt"
    check_contains "LC wrapper packages production OS claim denied" 'production_os_claim=0' "$TMP_DIR/packages.txt"
  else
    echo "failed: latticra-lc packages" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" init > "$TMP_DIR/init.txt"; then
    check_contains "LC wrapper init report" 'LATTICRA CONSOLE INIT CONTRACT' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init command surface" 'command_surface=lc init' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init PID 1 denied" 'pid1_claim_allowed=0' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init service start denied" 'service_start_allowed=0' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init process supervision denied" 'process_supervision_allowed=0' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/init.txt"
    check_contains "LC wrapper init production OS claim denied" 'production_os_claim=0' "$TMP_DIR/init.txt"
  else
    echo "failed: latticra-lc init" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" services > "$TMP_DIR/services.txt"; then
    check_contains "LC wrapper services report" 'LATTICRA CONSOLE SERVICES CONTRACT' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services command surface" 'command_surface=lc services' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services registry write denied" 'service_registry_write_allowed=0' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services start denied" 'service_start_allowed=0' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services enable denied" 'service_enable_allowed=0' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services process supervision denied" 'process_supervision_allowed=0' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/services.txt"
    check_contains "LC wrapper services production OS claim denied" 'production_os_claim=0' "$TMP_DIR/services.txt"
  else
    echo "failed: latticra-lc services" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" service-schema > "$TMP_DIR/service-schema.txt"; then
    check_contains "LC wrapper service schema report" 'LATTICRA CONSOLE SERVICE SCHEMA CONTRACT' "$TMP_DIR/service-schema.txt"
    check_contains "LC wrapper service schema command surface" 'command_surface=lc service-schema' "$TMP_DIR/service-schema.txt"
    check_contains "LC wrapper service schema file" 'service_schema_file=definition-schema.toml' "$TMP_DIR/service-schema.txt"
    check_contains "LC wrapper service definition validation denied" 'service_definition_validation_allowed=0' "$TMP_DIR/service-schema.txt"
    check_contains "LC wrapper service schema host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/service-schema.txt"
  else
    echo "failed: latticra-lc service-schema" >&2
    failures=$((failures + 1))
  fi
fi

if [ "$failures" -eq 0 ]; then
  echo "Latticra standalone LC verification: ok"
  exit 0
fi

echo "Latticra standalone LC verification: failed checks=$failures" >&2
exit 1
