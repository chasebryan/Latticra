#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

TMP_DIR="$(mktemp -d)"

cleanup() {
  rm -rf "$TMP_DIR"
}

trap cleanup EXIT

fail() {
  printf 'latticra panel local uninstall reset: %s\n' "$1" >&2
  exit 1
}

require_exists() {
  path="$1"
  [ -e "$path" ] || fail "expected path to exist: $path"
}

require_absent() {
  path="$1"
  [ ! -e "$path" ] || fail "expected path to be absent: $path"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

write_managed() {
  path="$1"
  mkdir -p "$(dirname "$path")"
  {
    printf '%s\n' '#!/usr/bin/env sh'
    printf '%s\n' '# LATTICRA_INSTALLER_MANAGED=1'
    printf '%s\n' 'exit 0'
  } > "$path"
  chmod 0755 "$path"
}

write_legacy_wrapper() {
  path="$1"
  prefix="$2"
  name="$(basename "$path")"
  mkdir -p "$(dirname "$path")"

  case "$name" in
    latticra)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'PREFIX="%s"\n' "$prefix"
        printf '%s\n' 'echo "Latticra is installed."'
        printf '%s\n' 'echo "payload=$PREFIX/lib/latticra"'
        printf '%s\n' 'echo "receipts=$PREFIX/share/latticra/receipts"'
      } > "$path"
      ;;
    lat)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'PREFIX="%s"\n' "$prefix"
        printf '%s\n' 'echo "Lat tooling is installed as part of the Latticra payload."'
        printf '%s\n' 'echo "payload=$PREFIX/lib/latticra"'
      } > "$path"
      ;;
    latticra-lc)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'LC_DIR="%s/share/latticra/lc"\n' "$prefix"
        printf '%s\n' 'echo "LATTICRA CONSOLE"'
        printf '%s\n' 'echo "$LC_DIR"'
      } > "$path"
      ;;
    latticra-seal)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'PREFIX="%s"\n' "$prefix"
        printf '%s\n' 'REPORT_DIR="$PREFIX/share/latticra/receipts"'
        printf '%s\n' 'echo "LATTICRA SEAL REPORT"'
        printf '%s\n' 'echo "$REPORT_DIR"'
      } > "$path"
      ;;
    latticra-nadia)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'NADIA_DIR="%s/share/latticra/nadia"\n' "$prefix"
        printf '%s\n' 'echo "NADIA OFFLINE AI FOUNDATION"'
        printf '%s\n' 'echo "$NADIA_DIR"'
      } > "$path"
      ;;
    latticra-panel)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf 'export LATTICRA_INSTALLER_ROOT="%s/lib/latticra/installer"\n' "$prefix"
        printf 'exec "%s/bin/latticra-panel" "$@"\n' "$prefix"
      } > "$path"
      ;;
    latticra-installer)
      {
        printf '%s\n' '#!/usr/bin/env sh'
        printf '%s\n' 'exec "$HOME/.local/bin/latticra-panel" "$@"'
      } > "$path"
      ;;
    *)
      fail "unknown legacy wrapper fixture: $name"
      ;;
  esac
  chmod 0755 "$path"
}

write_legacy_desktop_entry() {
  path="$1"
  command="$2"
  mkdir -p "$(dirname "$path")"
  {
    printf '%s\n' '[Desktop Entry]'
    printf '%s\n' 'Name=Latticra Installer'
    printf 'Exec=%s\n' "$command"
    printf '%s\n' 'Type=Application'
  } > "$path"
}

write_minimal_apply_config() {
  path="$1"
  prefix="$2"
  {
    printf '%s\n' 'profile = "developer_local"'
    printf 'install_prefix = "%s"\n' "$prefix"
    printf '%s\n' 'latticra_console = true'
    printf '%s\n' 'lat_tooling = true'
    printf '%s\n' 'lir_contracts = false'
    printf '%s\n' 'seal_report_only = true'
    printf '%s\n' 'nadia_offline_ai = true'
    printf '%s\n' 'fedora_validation = false'
    printf '%s\n' 'docs_and_examples = false'
    printf '%s\n' 'developer_cli_helpers = false'
    printf '%s\n' 'dry_run = false'
    printf '%s\n' 'allow_host_mutation = true'
    printf '%s\n' 'allow_network_effect = false'
    printf '%s\n' 'require_component_manifest = false'
    printf '%s\n' 'require_artifact_measurements = false'
    printf '%s\n' 'require_verification_policy_metadata = false'
    printf '%s\n' 'write_operator_receipt = true'
    printf '%s\n' 'create_prefix_layout = true'
    printf '%s\n' 'create_component_markers = true'
    printf '%s\n' 'create_cli_shims = true'
    printf '%s\n' 'preserve_existing_files = true'
    printf '%s\n' 'build_gui_installer = false'
    printf '%s\n' 'build_latticra_from_source = false'
    printf '%s\n' 'install_payload_tree = false'
    printf '%s\n' 'install_desktop_entry = true'
    printf '%s\n' 'install_user_bin_wrappers = true'
  } > "$path"
}

HOME_DIR="$TMP_DIR/home"
PREFIX="$HOME_DIR/.local/share/latticra"
RECEIPTS="$TMP_DIR/receipts"
USER_BIN="$HOME_DIR/.local/bin"
APP_DIR="$HOME_DIR/.local/share/applications"
ICON_DIR="$HOME_DIR/.local/share/icons/hicolor/256x256/apps"
SCRIPT="installer/scripts/latticra-installer-uninstall.sh"
APPLY_SCRIPT="installer/scripts/latticra-installer-apply.sh"

require_contains 'reset|uninstall)' "$APPLY_SCRIPT"
require_contains 'latticra-installer-uninstall.sh' "$APPLY_SCRIPT"
require_contains 'usage: latticra {status|path|gui|receipts|docs|lc|reset|seal|nadia|run}' "$APPLY_SCRIPT"
require_contains 'LC_COMMAND_WRAPPER=$(detect_lc_command_wrapper)' "$SCRIPT"
require_contains 'for command in $COMMAND_WRAPPERS; do' "$SCRIPT"

mkdir -p "$PREFIX/share/latticra/components" "$USER_BIN" "$APP_DIR" "$ICON_DIR"
printf '%s\n' 'payload' > "$PREFIX/payload.txt"
printf '%s\n' 'operator-owned' > "$USER_BIN/latticra"
chmod 0755 "$USER_BIN/latticra"
write_legacy_wrapper "$USER_BIN/latticra-seal" "$PREFIX"

for command in lat latticra-nadia latticra-panel latticra-installer; do
  write_managed "$USER_BIN/$command"
done

write_managed "$APP_DIR/latticra-panel.desktop"
write_managed "$APP_DIR/latticra-installer.desktop"
printf '%s\n' 'panel icon' > "$ICON_DIR/latticra-panel.png"
printf '%s\n' 'installer icon' > "$ICON_DIR/latticra-installer.png"
printf '%s\n' 'seal icon' > "$ICON_DIR/latticra-seal.png"

HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$RECEIPTS" --dry-run > "$TMP_DIR/dry-run.out"

require_contains 'mode=dry-reset' "$TMP_DIR/dry-run.out"
require_contains '[dry-run] would remove command wrapper' "$TMP_DIR/dry-run.out"
require_contains 'RESET_RESULT: success mode=dry-reset' "$TMP_DIR/dry-run.out"
require_exists "$PREFIX/payload.txt"
require_exists "$USER_BIN/lat"
require_exists "$ICON_DIR/latticra-panel.png"
require_contains 'mode=dry-reset' "$RECEIPTS/latest-reset-receipt.txt"

HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$RECEIPTS" > "$TMP_DIR/reset.out"

require_contains 'mode=local-prefix-reset' "$TMP_DIR/reset.out"
require_contains '[preserve] unmanaged command wrapper' "$TMP_DIR/reset.out"
require_contains '[removed] legacy managed command wrapper' "$TMP_DIR/reset.out"
require_contains 'RESET_WARNING: preserved unmanaged targets may block the next install' "$TMP_DIR/reset.out"
require_contains 'PRESERVED_UNMANAGED_TARGETS_BEGIN' "$TMP_DIR/reset.out"
require_contains "$USER_BIN/latticra" "$TMP_DIR/reset.out"
require_contains 'PRESERVED_UNMANAGED_TARGETS_ACTION=move-or-remove-manually-before-reinstall' "$TMP_DIR/reset.out"
require_contains 'RESET_RESULT: success mode=local-prefix-reset' "$TMP_DIR/reset.out"
require_absent "$PREFIX"
require_exists "$USER_BIN/latticra"
require_absent "$USER_BIN/lat"
require_absent "$USER_BIN/latticra-seal"
require_absent "$USER_BIN/latticra-nadia"
require_absent "$USER_BIN/latticra-panel"
require_absent "$USER_BIN/latticra-installer"
require_absent "$APP_DIR/latticra-panel.desktop"
require_absent "$APP_DIR/latticra-installer.desktop"
require_absent "$ICON_DIR/latticra-panel.png"
require_absent "$ICON_DIR/latticra-installer.png"
require_absent "$ICON_DIR/latticra-seal.png"
require_contains 'mode=local-prefix-reset' "$RECEIPTS/latest-reset-receipt.txt"
require_contains 'preserved_count=1' "$RECEIPTS/latest-reset-receipt.txt"
require_contains 'RESET_WARNING: preserved unmanaged targets may block the next install' "$RECEIPTS/latest-reset-receipt.txt"
require_contains "$USER_BIN/latticra" "$RECEIPTS/latest-reset-receipt.txt"

RESET_LEGACY_HOME="$TMP_DIR/reset-legacy-home"
RESET_LEGACY_PREFIX="$RESET_LEGACY_HOME/.local/share/latticra"
RESET_LEGACY_RECEIPTS="$TMP_DIR/reset-legacy-receipts"
RESET_LEGACY_USER_BIN="$RESET_LEGACY_HOME/.local/bin"
RESET_LEGACY_APP_DIR="$RESET_LEGACY_HOME/.local/share/applications"
mkdir -p "$RESET_LEGACY_PREFIX" "$RESET_LEGACY_USER_BIN" "$RESET_LEGACY_APP_DIR"
printf '%s\n' 'legacy payload' > "$RESET_LEGACY_PREFIX/payload.txt"
for command in latticra lat latticra-lc latticra-seal latticra-nadia latticra-panel latticra-installer; do
  write_legacy_wrapper "$RESET_LEGACY_USER_BIN/$command" "$RESET_LEGACY_PREFIX"
done
write_legacy_desktop_entry \
  "$RESET_LEGACY_APP_DIR/latticra-installer.desktop" \
  "$RESET_LEGACY_USER_BIN/latticra-installer"
write_legacy_desktop_entry \
  "$RESET_LEGACY_APP_DIR/latticra-panel.desktop" \
  "$RESET_LEGACY_USER_BIN/latticra-panel"

HOME="$RESET_LEGACY_HOME" sh "$SCRIPT" \
  --prefix "$RESET_LEGACY_PREFIX" \
  --receipt-dir "$RESET_LEGACY_RECEIPTS" \
  > "$TMP_DIR/reset-legacy.out"

require_contains '[removed] legacy managed command wrapper' "$TMP_DIR/reset-legacy.out"
require_contains '[removed] legacy managed desktop entry' "$TMP_DIR/reset-legacy.out"
require_contains 'preserved_count=0' "$TMP_DIR/reset-legacy.out"
require_contains 'RESET_RESULT: success mode=local-prefix-reset' "$TMP_DIR/reset-legacy.out"
require_absent "$RESET_LEGACY_PREFIX"
for command in latticra lat latticra-lc latticra-seal latticra-nadia latticra-panel latticra-installer; do
  require_absent "$RESET_LEGACY_USER_BIN/$command"
done
require_absent "$RESET_LEGACY_APP_DIR/latticra-installer.desktop"
require_absent "$RESET_LEGACY_APP_DIR/latticra-panel.desktop"

CUSTOM_LC_HOME="$TMP_DIR/custom-lc-home"
CUSTOM_LC_PREFIX="$CUSTOM_LC_HOME/.local/share/latticra"
CUSTOM_LC_RECEIPTS="$TMP_DIR/custom-lc-receipts"
CUSTOM_LC_USER_BIN="$CUSTOM_LC_HOME/.local/bin"
CUSTOM_LC_WRAPPER="latticra-console-custom"
mkdir -p "$CUSTOM_LC_PREFIX/share/latticra/lc/install" "$CUSTOM_LC_USER_BIN"
cat > "$CUSTOM_LC_PREFIX/share/latticra/lc/install/config.toml" <<CUSTOM_LC_CONFIG
install_profile = "lc-panel-install-v0"
command_wrapper = "$CUSTOM_LC_WRAPPER"
allow_external_host_commands = false
CUSTOM_LC_CONFIG
printf '%s\n' 'custom lc payload' > "$CUSTOM_LC_PREFIX/payload.txt"
write_managed "$CUSTOM_LC_USER_BIN/$CUSTOM_LC_WRAPPER"

HOME="$CUSTOM_LC_HOME" sh "$SCRIPT" \
  --prefix "$CUSTOM_LC_PREFIX" \
  --receipt-dir "$CUSTOM_LC_RECEIPTS" \
  > "$TMP_DIR/custom-lc-reset.out"

require_contains "[removed] command wrapper: $CUSTOM_LC_USER_BIN/$CUSTOM_LC_WRAPPER" "$TMP_DIR/custom-lc-reset.out"
require_contains "lc_command_wrapper=$CUSTOM_LC_WRAPPER" "$CUSTOM_LC_RECEIPTS/latest-reset-receipt.txt"
require_contains 'RESET_RESULT: success mode=local-prefix-reset' "$TMP_DIR/custom-lc-reset.out"
require_absent "$CUSTOM_LC_PREFIX"
require_absent "$CUSTOM_LC_USER_BIN/$CUSTOM_LC_WRAPPER"

HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$RECEIPTS" --operation uninstall --dry-run > "$TMP_DIR/uninstall-dry-run.out"

require_contains 'operation=uninstall' "$TMP_DIR/uninstall-dry-run.out"
require_contains 'mode=dry-uninstall' "$TMP_DIR/uninstall-dry-run.out"
require_contains 'UNINSTALL_RESULT: success mode=dry-uninstall' "$TMP_DIR/uninstall-dry-run.out"
require_contains 'operation=uninstall' "$RECEIPTS/latest-uninstall-receipt.txt"
require_contains 'mode=dry-uninstall' "$RECEIPTS/latest-uninstall-receipt.txt"

if HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$HOME_DIR/not-latticra" --receipt-dir "$RECEIPTS" > "$TMP_DIR/unsafe.out" 2>&1; then
  fail "unsafe prefix should have been refused"
fi
require_contains 'refusing to reset unsafe prefix' "$TMP_DIR/unsafe.out"

mkdir -p "$HOME_DIR/.local/share/escape"
if HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX/../escape" --receipt-dir "$RECEIPTS" > "$TMP_DIR/traversal.out" 2>&1; then
  fail "parent-directory traversal prefix should have been refused"
fi
require_contains 'parent-directory traversal' "$TMP_DIR/traversal.out"
require_exists "$HOME_DIR/.local/share/escape"

if HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$PREFIX/share/latticra/receipts" > "$TMP_DIR/unsafe-receipt.out" 2>&1; then
  fail "receipt inside removed prefix should have been refused"
fi
require_contains 'refusing to write reset receipt inside prefix being removed' "$TMP_DIR/unsafe-receipt.out"

SYMLINK_TARGET="$TMP_DIR/uninstall-symlink-target"
mkdir -p "$SYMLINK_TARGET" "$(dirname "$PREFIX")"
ln -s "$SYMLINK_TARGET" "$PREFIX"
if HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$RECEIPTS" > "$TMP_DIR/symlink.out" 2>&1; then
  fail "symlink prefix should have been refused"
fi
require_contains 'refusing to reset symlink prefix' "$TMP_DIR/symlink.out"
require_exists "$SYMLINK_TARGET"
rm -f "$PREFIX"

APPLY_LEGACY_HOME="$TMP_DIR/apply-legacy-home"
APPLY_LEGACY_PREFIX="$APPLY_LEGACY_HOME/.local/share/latticra"
APPLY_LEGACY_CONFIG="$TMP_DIR/apply-legacy.toml"
mkdir -p "$APPLY_LEGACY_HOME/.local/bin" "$APPLY_LEGACY_HOME/.local/share/applications" "$APPLY_LEGACY_PREFIX/bin"
for command in latticra lat latticra-lc latticra-seal latticra-nadia latticra-panel latticra-installer; do
  write_legacy_wrapper "$APPLY_LEGACY_HOME/.local/bin/$command" "$APPLY_LEGACY_PREFIX"
done
write_legacy_desktop_entry \
  "$APPLY_LEGACY_HOME/.local/share/applications/latticra-installer.desktop" \
  "$APPLY_LEGACY_HOME/.local/bin/latticra-installer"
write_legacy_desktop_entry \
  "$APPLY_LEGACY_HOME/.local/share/applications/latticra-panel.desktop" \
  "$APPLY_LEGACY_HOME/.local/bin/latticra-panel"
printf '%s\n' '#!/usr/bin/env sh' 'exit 0' > "$APPLY_LEGACY_PREFIX/bin/latticra-panel"
chmod 0755 "$APPLY_LEGACY_PREFIX/bin/latticra-panel"
write_minimal_apply_config "$APPLY_LEGACY_CONFIG" "$APPLY_LEGACY_PREFIX"

HOME="$APPLY_LEGACY_HOME" sh "$APPLY_SCRIPT" \
  --config "$APPLY_LEGACY_CONFIG" \
  --plan "$TMP_DIR/apply-legacy-plan.txt" \
  --receipt-dir "$TMP_DIR/apply-legacy-receipts" \
  > "$TMP_DIR/apply-legacy.out"

for command in latticra lat latticra-lc latticra-seal latticra-nadia latticra-panel latticra-installer; do
  require_contains "[replace-legacy-managed] $APPLY_LEGACY_HOME/.local/bin/$command" "$TMP_DIR/apply-legacy.out"
  require_contains 'LATTICRA_INSTALLER_MANAGED=1' "$APPLY_LEGACY_HOME/.local/bin/$command"
done
require_contains "[replace-legacy-managed] $APPLY_LEGACY_HOME/.local/share/applications/latticra-panel.desktop" "$TMP_DIR/apply-legacy.out"
require_contains "[remove-legacy-managed] $APPLY_LEGACY_HOME/.local/share/applications/latticra-installer.desktop" "$TMP_DIR/apply-legacy.out"
require_contains 'INSTALLER_RESULT: success mode=local-prefix-install' "$TMP_DIR/apply-legacy.out"
require_absent "$APPLY_LEGACY_HOME/.local/share/applications/latticra-installer.desktop"
require_contains 'LATTICRA_INSTALLER_MANAGED=1' "$APPLY_LEGACY_HOME/.local/share/applications/latticra-panel.desktop"

APPLY_BLOCK_HOME="$TMP_DIR/apply-block-home"
APPLY_BLOCK_PREFIX="$APPLY_BLOCK_HOME/.local/share/latticra"
APPLY_BLOCK_CONFIG="$TMP_DIR/apply-block.toml"
mkdir -p "$APPLY_BLOCK_HOME/.local/bin"
printf '%s\n' 'operator-owned' > "$APPLY_BLOCK_HOME/.local/bin/latticra-seal"
chmod 0755 "$APPLY_BLOCK_HOME/.local/bin/latticra-seal"
write_minimal_apply_config "$APPLY_BLOCK_CONFIG" "$APPLY_BLOCK_PREFIX"

if HOME="$APPLY_BLOCK_HOME" sh "$APPLY_SCRIPT" \
  --config "$APPLY_BLOCK_CONFIG" \
  --plan "$TMP_DIR/apply-block-plan.txt" \
  --receipt-dir "$TMP_DIR/apply-block-receipts" \
  > "$TMP_DIR/apply-block.out" 2>&1; then
  fail "unmanaged non-Latticra wrapper should have been refused"
fi
require_contains "refusing to overwrite unmanaged file: $APPLY_BLOCK_HOME/.local/bin/latticra-seal" "$TMP_DIR/apply-block.out"

APPLY_HOME="$TMP_DIR/apply-home"
APPLY_PREFIX="$APPLY_HOME/.local/share/latticra"
APPLY_RECEIPTS="$TMP_DIR/apply-receipts"
APPLY_PLAN="$TMP_DIR/apply-plan.txt"
APPLY_BAD_CONFIG="$TMP_DIR/apply-bad-prefix.toml"
mkdir -p "$APPLY_HOME/.local/share" "$APPLY_RECEIPTS"
{
  printf '%s\n' 'dry_run = true'
  printf 'install_prefix = "%s"\n' "$APPLY_PREFIX/../escape"
} > "$APPLY_BAD_CONFIG"
if HOME="$APPLY_HOME" sh "$APPLY_SCRIPT" --config "$APPLY_BAD_CONFIG" --plan "$APPLY_PLAN" --receipt-dir "$APPLY_RECEIPTS" > "$TMP_DIR/apply-traversal.out" 2>&1; then
  fail "installer apply traversal prefix should have been refused"
fi
require_contains 'refusing install prefix with parent-directory traversal' "$TMP_DIR/apply-traversal.out"

APPLY_SYMLINK_HOME="$TMP_DIR/apply-symlink-home"
APPLY_SYMLINK_PREFIX="$APPLY_SYMLINK_HOME/.local/share/latticra"
APPLY_SYMLINK_TARGET="$TMP_DIR/apply-symlink-target"
APPLY_SYMLINK_CONFIG="$TMP_DIR/apply-symlink-prefix.toml"
mkdir -p "$APPLY_SYMLINK_HOME/.local/share" "$APPLY_SYMLINK_TARGET"
ln -s "$APPLY_SYMLINK_TARGET" "$APPLY_SYMLINK_PREFIX"
{
  printf '%s\n' 'dry_run = true'
  printf 'install_prefix = "%s"\n' "$APPLY_SYMLINK_PREFIX"
} > "$APPLY_SYMLINK_CONFIG"
if HOME="$APPLY_SYMLINK_HOME" sh "$APPLY_SCRIPT" --config "$APPLY_SYMLINK_CONFIG" --plan "$TMP_DIR/apply-symlink-plan.txt" --receipt-dir "$TMP_DIR/apply-symlink-receipts" > "$TMP_DIR/apply-symlink.out" 2>&1; then
  fail "installer apply symlink prefix should have been refused"
fi
require_contains 'refusing symlink install prefix' "$TMP_DIR/apply-symlink.out"
require_exists "$APPLY_SYMLINK_TARGET"

printf 'latticra_panel_local_uninstall_reset: ok\n'
