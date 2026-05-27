#!/usr/bin/env sh
set -eu

usage() {
  cat >&2 <<'USAGE'
usage:
  latticra-installer-uninstall.sh [--prefix <dir>] [--receipt-dir <dir>] [--operation reset|uninstall] [--dry-run] [--no-receipt]

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

RECEIPT_BODY=""
cleanup_receipt_body() {
  if [ -n "${RECEIPT_BODY:-}" ] && [ -f "$RECEIPT_BODY" ]; then
    rm -f "$RECEIPT_BODY"
  fi
}
trap cleanup_receipt_body EXIT INT HUP TERM

write_file() {
  target="$1"
  mode="$2"
  dir="$(dirname -- "$target")"
  base="$(basename -- "$target")"
  mkdir -p "$dir"
  tmp=$(mktemp "$dir/.latticra-installer.$base.XXXXXX") ||
    fail "unable to create temporary file for $target"
  if ! cat > "$tmp"; then
    rm -f "$tmp"
    fail "unable to write temporary file for $target"
  fi
  if ! chmod "$mode" "$tmp"; then
    rm -f "$tmp"
    fail "unable to chmod temporary file for $target"
  fi
  if [ -L "$target" ]; then
    rm -f "$tmp"
    fail "refusing to overwrite symlink file: $target"
  fi
  if [ -e "$target" ] && [ ! -f "$target" ]; then
    rm -f "$tmp"
    fail "refusing to overwrite non-regular file: $target"
  fi
  mv "$tmp" "$target"
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

PREFIX_RAW="$HOME/.local/share/latticra"
RECEIPT_DIR_RAW="$HOME/.local/share/latticra-reset-receipts"
OPERATION=reset
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
    --operation)
      [ "$#" -ge 2 ] || fail "missing value for --operation"
      OPERATION="$2"
      shift 2
      ;;
    --reset)
      OPERATION=reset
      shift
      ;;
    --uninstall)
      OPERATION=uninstall
      shift
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

case "$OPERATION" in
  reset|uninstall)
    ;;
  *)
    fail "unknown operation: $OPERATION"
    ;;
esac

PREFIX=$(expand_path "$PREFIX_RAW")
RECEIPT_DIR=$(expand_path "$RECEIPT_DIR_RAW")
USER_BIN="$HOME/.local/bin"
APP_DIR="$HOME/.local/share/applications"
ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"
TS=$(date -u +"%Y%m%dT%H%M%SZ")
MODE="local-prefix-$OPERATION"

if [ "$DRY_RUN" = true ]; then
  MODE="dry-$OPERATION"
fi

case "$PREFIX" in
  /*) ;;
  *) fail "refusing to reset unsafe prefix: $PREFIX" ;;
esac

if path_has_parent_reference "$PREFIX"; then
  fail "refusing to reset unsafe prefix with parent-directory traversal: $PREFIX"
fi

if [ -L "$PREFIX" ]; then
  fail "refusing to reset symlink prefix: $PREFIX"
fi

PREFIX_REAL=$(canonical_existing_path "$PREFIX")
if path_has_parent_reference "$PREFIX_REAL"; then
  fail "refusing to reset unsafe prefix with parent-directory traversal: $PREFIX"
fi

prefix_is_allowed_user_local "$PREFIX" &&
  prefix_is_allowed_user_local "$PREFIX_REAL" ||
  fail "refusing to reset unsafe prefix: $PREFIX"

if [ "$WRITE_RECEIPT" = true ] && [ "$DRY_RUN" != true ]; then
  case "$RECEIPT_DIR" in
    "$PREFIX"|"$PREFIX"/*)
      fail "refusing to write reset receipt inside prefix being removed: $RECEIPT_DIR"
      ;;
  esac
fi

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
  wrapper=$(toml_get_key "$PREFIX/share/latticra/lc/install/config.toml" command_wrapper || true)
  if [ -z "$wrapper" ]; then
    wrapper=$(toml_get_key "$PREFIX/etc/latticra/lc.toml" install_command_wrapper || true)
  fi

  if valid_command_name "$wrapper"; then
    printf '%s\n' "$wrapper"
  else
    printf '%s\n' 'latticra-lc'
  fi
}

COMMAND_WRAPPERS=""
append_command_wrapper() {
  command="$1"
  case " $COMMAND_WRAPPERS " in
    *" $command "*)
      ;;
    *)
      COMMAND_WRAPPERS="${COMMAND_WRAPPERS:+$COMMAND_WRAPPERS }$command"
      ;;
  esac
}

LC_COMMAND_WRAPPER=$(detect_lc_command_wrapper)
append_command_wrapper latticra
append_command_wrapper latticra-lc
append_command_wrapper "$LC_COMMAND_WRAPPER"
append_command_wrapper lat
append_command_wrapper latticra-seal
append_command_wrapper latticra-nadia
append_command_wrapper latticra-panel
append_command_wrapper latticra-installer

RECEIPT=""
removed_count=0
planned_count=0
preserved_count=0
missing_count=0
preserved_unmanaged_targets=""

if [ "$WRITE_RECEIPT" = true ]; then
  mkdir -p "$RECEIPT_DIR"
  RECEIPT="$RECEIPT_DIR/latticra-panel-$OPERATION-receipt-$TS.txt"
  RECEIPT_BODY=$(mktemp "$RECEIPT_DIR/.latticra-installer-$OPERATION-receipt.XXXXXX") ||
    fail "unable to create temporary receipt body for $RECEIPT"
  if ! cat > "$RECEIPT_BODY" <<RECEIPT_HEADER
LATTICRA PANEL ${OPERATION} RECEIPT

timestamp_utc=$TS
operation=$OPERATION
mode=$MODE
install_prefix=$PREFIX
user_bin=$USER_BIN
desktop_dir=$APP_DIR
icon_dir=$ICON_DIR
lc_command_wrapper=$LC_COMMAND_WRAPPER
root_authority=0
network_authority=0
runtime_enforcement_authority=0
production_installer_ready=0

RECEIPT_HEADER
  then
    fail "unable to write temporary receipt body for $RECEIPT"
  fi
fi

log() {
  printf '%s\n' "$*"
  if [ -n "$RECEIPT_BODY" ]; then
    printf '%s\n' "$*" >> "$RECEIPT_BODY" ||
      fail "unable to append to temporary receipt body for $RECEIPT"
  fi
}

phase() {
  log "PHASE $1/5: $2"
}

record_preserved_unmanaged_target() {
  path="$1"

  if [ -z "$preserved_unmanaged_targets" ]; then
    preserved_unmanaged_targets="$path"
  else
    preserved_unmanaged_targets="$preserved_unmanaged_targets
$path"
  fi
}

is_legacy_latticra_managed_file() {
  path="$1"
  [ -f "$path" ] || return 1

  case "$(basename -- "$path")" in
    latticra)
      grep -q 'Latticra is installed.' "$path" 2>/dev/null &&
        { grep -q 'lib/latticra' "$path" 2>/dev/null ||
          grep -q 'share/latticra/receipts' "$path" 2>/dev/null ||
          grep -q 'LATTICRA_PREFIX' "$path" 2>/dev/null; }
      ;;
    lat)
      grep -q 'Lat tooling is installed as part of the Latticra payload.' "$path" 2>/dev/null ||
        { grep -q 'No compiled lat binary was found yet.' "$path" 2>/dev/null &&
          grep -q 'lib/latticra' "$path" 2>/dev/null; }
      ;;
    latticra-lc)
      grep -q 'LATTICRA CONSOLE' "$path" 2>/dev/null &&
        { grep -q 'share/latticra/lc' "$path" 2>/dev/null ||
          grep -q 'LC_DIR' "$path" 2>/dev/null; }
      ;;
    latticra-seal)
      grep -q 'LATTICRA SEAL' "$path" 2>/dev/null &&
        { grep -q 'share/latticra/receipts' "$path" 2>/dev/null ||
          grep -q 'latticra-seal-report' "$path" 2>/dev/null ||
          grep -q 'mode=report-only' "$path" 2>/dev/null; }
      ;;
    latticra-nadia)
      { grep -q 'NADIA OFFLINE AI FOUNDATION' "$path" 2>/dev/null ||
        grep -q 'Nadia Witness Foundation' "$path" 2>/dev/null; } &&
        grep -q 'share/latticra/nadia' "$path" 2>/dev/null
      ;;
    latticra-panel)
      grep -q 'latticra-panel' "$path" 2>/dev/null &&
        { grep -q 'LATTICRA_INSTALLER_ROOT' "$path" 2>/dev/null ||
          grep -q 'share/latticra' "$path" 2>/dev/null; }
      ;;
    latticra-installer)
      grep -q 'latticra-panel' "$path" 2>/dev/null ||
        grep -q 'latticra-installer' "$path" 2>/dev/null
      ;;
    latticra-panel.desktop|latticra-installer.desktop)
      { grep -q 'Name=Latticra Panel' "$path" 2>/dev/null ||
        grep -q 'Name=Latticra Installer' "$path" 2>/dev/null; } &&
        { grep -q 'Exec=.*latticra-panel' "$path" 2>/dev/null ||
          grep -q 'Exec=.*latticra-installer' "$path" 2>/dev/null; }
      ;;
    *)
      return 1
      ;;
  esac
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
  elif is_legacy_latticra_managed_file "$path"; then
    remove_file "$path" "legacy managed $label"
  else
    preserved_count=$((preserved_count + 1))
    log "[preserve] unmanaged $label: $path"
    record_preserved_unmanaged_target "$path"
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

log "Latticra Panel $OPERATION"
log "operation=$OPERATION"
log "mode=$MODE"
log "prefix=$PREFIX"

phase 1 "remove managed command wrappers"
for command in $COMMAND_WRAPPERS; do
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

phase 5 "refresh desktop metadata and write operation receipt"
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
if [ "$preserved_count" -gt 0 ]; then
  if [ "$OPERATION" = uninstall ]; then
    log "UNINSTALL_WARNING: preserved unmanaged targets may block the next install"
  else
    log "RESET_WARNING: preserved unmanaged targets may block the next install"
  fi
  log "PRESERVED_UNMANAGED_TARGETS_BEGIN"
  printf '%s\n' "$preserved_unmanaged_targets" | while IFS= read -r preserved_path; do
    [ -n "$preserved_path" ] || continue
    log "  $preserved_path"
  done
  log "PRESERVED_UNMANAGED_TARGETS_END"
  log "PRESERVED_UNMANAGED_TARGETS_ACTION=move-or-remove-manually-before-reinstall"
fi
if [ "$OPERATION" = uninstall ]; then
  log "UNINSTALL_RESULT: success mode=$MODE prefix=$PREFIX"
else
  log "RESET_RESULT: success mode=$MODE prefix=$PREFIX"
fi

if [ -n "$RECEIPT" ]; then
  if [ "$OPERATION" = uninstall ]; then
    log "UNINSTALL_RECEIPT: $RECEIPT"
  else
    log "RESET_RECEIPT: $RECEIPT"
  fi
fi

if [ "$DRY_RUN" = true ]; then
  log "Latticra local $OPERATION dry-run complete."
else
  log "Latticra local $OPERATION complete."
fi

if [ -n "$RECEIPT_BODY" ]; then
  write_file "$RECEIPT" 0644 < "$RECEIPT_BODY"
  write_file "$RECEIPT_DIR/latest-$OPERATION-receipt.txt" 0644 < "$RECEIPT_BODY"
  rm -f "$RECEIPT_BODY"
  RECEIPT_BODY=""
fi
