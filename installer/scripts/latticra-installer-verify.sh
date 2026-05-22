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
failures=0

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

check "prefix" "$PREFIX"
check "payload tree" "$PREFIX/lib/latticra"
check "config" "$PREFIX/etc/latticra/installer-config.toml"
check "receipts" "$PREFIX/share/latticra/receipts"
check_exec "latticra command" "$USER_BIN/latticra"
check_exec "lat command" "$USER_BIN/lat"
check_exec "latticra-seal command" "$USER_BIN/latticra-seal"
check_exec "latticra-panel command" "$USER_BIN/latticra-panel"
check "desktop entry" "$APP_FILE"
check "desktop icon" "$ICON_FILE"

if [ -x "$USER_BIN/latticra" ]; then
  "$USER_BIN/latticra" status || failures=$((failures + 1))
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
