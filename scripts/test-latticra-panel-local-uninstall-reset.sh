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
require_contains 'usage: latticra {status|path|gui|receipts|docs|reset|seal|nadia|run}' "$APPLY_SCRIPT"

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

if HOME="$HOME_DIR" sh "$SCRIPT" --prefix "$PREFIX" --receipt-dir "$PREFIX/share/latticra/receipts" > "$TMP_DIR/unsafe-receipt.out" 2>&1; then
  fail "receipt inside removed prefix should have been refused"
fi
require_contains 'refusing to write reset receipt inside prefix being removed' "$TMP_DIR/unsafe-receipt.out"

printf 'latticra_panel_local_uninstall_reset: ok\n'
