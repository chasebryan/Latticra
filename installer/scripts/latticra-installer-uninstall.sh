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
APP_DIR="$HOME/.local/share/applications"
ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"

case "$PREFIX" in
  "$HOME"/.local/share/latticra|"$HOME"/.local/share/latticra/*|"$HOME"/.local/share/latticra-validation|"$HOME"/.local/share/latticra-validation/*)
    ;;
  *)
    echo "refusing to uninstall unsafe prefix: $PREFIX" >&2
    exit 73
    ;;
esac

remove_managed() {
  f="$1"
  if [ ! -e "$f" ]; then
    return 0
  fi
  if grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$f" 2>/dev/null; then
    rm -f "$f"
    echo "removed managed file: $f"
  else
    echo "preserved unmanaged file: $f" >&2
  fi
}

remove_managed "$USER_BIN/latticra"
remove_managed "$USER_BIN/lat"
remove_managed "$USER_BIN/latticra-seal"
remove_managed "$USER_BIN/latticra-panel"
remove_managed "$USER_BIN/latticra-installer"
remove_managed "$APP_DIR/latticra-panel.desktop"
remove_managed "$APP_DIR/latticra-installer.desktop"

[ -e "$ICON_DIR/latticra-panel.png" ] && rm -f "$ICON_DIR/latticra-panel.png" && echo "removed icon: $ICON_DIR/latticra-panel.png"
[ -e "$ICON_DIR/latticra-seal.png" ] && rm -f "$ICON_DIR/latticra-seal.png" && echo "removed old icon: $ICON_DIR/latticra-seal.png"

if [ -d "$PREFIX" ]; then
  rm -rf "$PREFIX"
  echo "removed prefix: $PREFIX"
fi

if command -v update-desktop-database >/dev/null 2>&1; then
  update-desktop-database "$APP_DIR" >/dev/null 2>&1 || true
fi
if command -v gtk-update-icon-cache >/dev/null 2>&1; then
  gtk-update-icon-cache -q "$HOME/.local/share/icons/hicolor" >/dev/null 2>&1 || true
fi

echo "Latticra local uninstall complete."
