#!/usr/bin/env sh
set -eu

usage() {
  cat >&2 <<'USAGE'
usage:
  latticra-installer-uninstall.sh [--prefix <dir>] [--receipt-dir <dir>] [--dry-run] [--no-receipt]

Removes the managed Latticra Panel user-local install so the operator can start
fresh from a new specification. The reset is limited to guarded Latticra
user-local prefixes and user-local desktop/wrapper artifacts.
USAGE
}

fail() {
  printf '%s\n' "$*" >&2
  exit 1
}

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

PREFIX_RAW="$HOME/.local/share/latticra"
RECEIPT_DIR_RAW="$HOME/.local/share/latticra-reset-receipts"
DRY_RUN=false
WRITE_RECEIPT=true

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prefix)
      [ "$#" -ge 2 ] || fail "missing value for --prefix"
      PREFIX_RAW="$2"
      shift 2
      ;;
    --receipt-dir)
      [ "$#" -ge 2 ] || fail "missing value for --receipt-dir"
      RECEIPT_DIR_RAW="$2"
      shift 2
      ;;
    --dry-run)
      DRY_RUN=true
      shift
      ;;
    --no-receipt)
      WRITE_RECEIPT=false
      shift
      ;;
    --help|-h)
      usage
      exit 0
      ;;
    *)
      usage
      fail "unknown argument: $1"
      ;;
  esac
done

PREFIX=$(expand_path "$PREFIX_RAW")
RECEIPT_DIR=$(expand_path "$RECEIPT_DIR_RAW")
USER_BIN="$HOME/.local/bin"
APP_DIR="$HOME/.local/share/applications"
ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"
TS=$(date -u +"%Y%m%dT%H%M%SZ")
MODE="local-prefix-reset"

if [ "$DRY_RUN" = true ]; then
  MODE="dry-reset"
fi

case "$PREFIX" in
  "$HOME"/.local/share/latticra|"$HOME"/.local/share/latticra/*|"$HOME"/.local/share/latticra-validation|"$HOME"/.local/share/latticra-validation/*)
    ;;
  *)
    fail "refusing to reset unsafe prefix: $PREFIX"
    ;;
esac

if [ "$WRITE_RECEIPT" = true ] && [ "$DRY_RUN" != true ]; then
  case "$RECEIPT_DIR" in
    "$PREFIX"|"$PREFIX"/*)
      fail "refusing to write reset receipt inside prefix being removed: $RECEIPT_DIR"
      ;;
  esac
fi

RECEIPT=""
removed_count=0
planned_count=0
preserved_count=0
missing_count=0

if [ "$WRITE_RECEIPT" = true ]; then
  mkdir -p "$RECEIPT_DIR"
  RECEIPT="$RECEIPT_DIR/latticra-panel-reset-receipt-$TS.txt"
  cat > "$RECEIPT" <<RECEIPT_HEADER
LATTICRA PANEL RESET RECEIPT

timestamp_utc=$TS
mode=$MODE
install_prefix=$PREFIX
user_bin=$USER_BIN
desktop_dir=$APP_DIR
icon_dir=$ICON_DIR
root_authority=0
network_authority=0
runtime_enforcement_authority=0
production_installer_ready=0

RECEIPT_HEADER
fi

log() {
  printf '%s\n' "$*"
  if [ -n "$RECEIPT" ]; then
    printf '%s\n' "$*" >> "$RECEIPT"
  fi
}

phase() {
  log "PHASE $1/5: $2"
}

remove_file() {
  path="$1"
  label="$2"

  if [ ! -e "$path" ]; then
    missing_count=$((missing_count + 1))
    log "[missing] $label: $path"
    return 0
  fi

  if [ "$DRY_RUN" = true ]; then
    planned_count=$((planned_count + 1))
    log "[dry-run] would remove $label: $path"
    return 0
  fi

  rm -f "$path"
  removed_count=$((removed_count + 1))
  log "[removed] $label: $path"
}

remove_managed_file() {
  path="$1"
  label="$2"

  if [ ! -e "$path" ]; then
    missing_count=$((missing_count + 1))
    log "[missing] $label: $path"
    return 0
  fi

  if grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$path" 2>/dev/null; then
    remove_file "$path" "$label"
  else
    preserved_count=$((preserved_count + 1))
    log "[preserve] unmanaged $label: $path"
  fi
}

remove_prefix() {
  if [ ! -d "$PREFIX" ]; then
    missing_count=$((missing_count + 1))
    log "[missing] prefix: $PREFIX"
    return 0
  fi

  if [ "$DRY_RUN" = true ]; then
    planned_count=$((planned_count + 1))
    log "[dry-run] would remove managed prefix tree: $PREFIX"
    return 0
  fi

  rm -rf "$PREFIX"
  removed_count=$((removed_count + 1))
  log "[removed] managed prefix tree: $PREFIX"
}

log "Latticra Panel reset"
log "mode=$MODE"
log "prefix=$PREFIX"

phase 1 "remove managed command wrappers"
for command in latticra lat latticra-seal latticra-nadia latticra-panel latticra-installer; do
  remove_managed_file "$USER_BIN/$command" "command wrapper"
done

phase 2 "remove managed desktop entries"
for desktop in latticra-panel.desktop latticra-installer.desktop; do
  remove_managed_file "$APP_DIR/$desktop" "desktop entry"
done

phase 3 "remove known desktop icons"
for icon in latticra-panel.png latticra-installer.png latticra-seal.png; do
  remove_file "$ICON_DIR/$icon" "desktop icon"
done

phase 4 "remove managed local prefix"
remove_prefix

phase 5 "refresh desktop metadata and write reset receipt"
if [ "$DRY_RUN" != true ]; then
  if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database "$APP_DIR" >/dev/null 2>&1 || true
  fi
  if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    gtk-update-icon-cache -q "$HOME/.local/share/icons/hicolor" >/dev/null 2>&1 || true
  fi
else
  log "[dry-run] desktop metadata refresh skipped"
fi

log "removed_count=$removed_count"
log "planned_count=$planned_count"
log "preserved_count=$preserved_count"
log "missing_count=$missing_count"
log "RESET_RESULT: success mode=$MODE prefix=$PREFIX"

if [ -n "$RECEIPT" ]; then
  log "RESET_RECEIPT: $RECEIPT"
fi

if [ "$DRY_RUN" = true ]; then
  log "Latticra local reset dry-run complete."
else
  log "Latticra local reset complete."
fi

if [ -n "$RECEIPT" ]; then
  cp "$RECEIPT" "$RECEIPT_DIR/latest-reset-receipt.txt"
fi
