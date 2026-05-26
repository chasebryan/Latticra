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

mkdir -p "$PREFIX/share/latticra/components" "$USER_BIN" "$APP_DIR" "$ICON_DIR"
printf '%s\n' 'payload' > "$PREFIX/payload.txt"
printf '%s\n' 'operator-owned' > "$USER_BIN/latticra"
chmod 0755 "$USER_BIN/latticra"

for command in lat latticra-seal latticra-nadia latticra-panel latticra-installer; do
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
