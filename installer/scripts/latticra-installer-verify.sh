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
APP_FILE="$HOME/.local/share/applications/latticra-panel.desktop"
ICON_FILE="$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png"
LC_INSTALL_CONFIG="$PREFIX/share/latticra/lc/install/config.toml"
LC_COMMAND_REGISTRY="$PREFIX/share/latticra/lc/commands/seed-registry.txt"
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
check "updater config" "$UPDATER_CONFIG"
check "updater policy" "$UPDATER_POLICY"

check_contains "LC install profile metadata" 'install_profile = "lc-panel-install-v0"' "$LC_INSTALL_CONFIG"
check_contains "LC command wrapper metadata" "command_wrapper = \"$LC_COMMAND_WRAPPER\"" "$LC_INSTALL_CONFIG"
check_contains "LC standalone console metadata" 'standalone_console = true' "$LC_INSTALL_CONFIG"
check_contains "LC standalone requires Panel disabled" 'standalone_requires_panel = false' "$LC_INSTALL_CONFIG"
check_contains "LC standalone contract metadata" 'standalone_contract_present = true' "$LC_INSTALL_CONFIG"
check_contains "LC external host command authority disabled" 'allow_external_host_commands = false' "$LC_INSTALL_CONFIG"
check_contains "LC install-config registry command" 'name=lc install-config category=core effect=none capability=lc.install.config' "$LC_COMMAND_REGISTRY"
check_contains "LC standalone registry command" 'name=lc standalone category=core effect=none capability=lc.standalone.inspect' "$LC_COMMAND_REGISTRY"
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
    check_contains "LC wrapper host process launch denied" 'host_process_launch_allowed=0' "$TMP_DIR/lc-install-config.txt"
  else
    echo "failed: $LC_COMMAND_WRAPPER install-config" >&2
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
