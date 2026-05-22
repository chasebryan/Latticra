#!/usr/bin/env sh
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-installer-apply.sh --config <file> [--plan <file>] [--receipt-dir <dir>]

This is the real guarded Latticra Panel user-local install engine.
It installs only under the configured user-local prefix and ~/.local/bin.
It does not require root, change the kernel, change systemd, change SELinux, or use the network.
USAGE
}

CONFIG=""
PLAN=""
RECEIPT_DIR=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --config)
      [ "$#" -ge 2 ] || { echo "missing value for --config" >&2; exit 64; }
      CONFIG="$2"
      shift 2
      ;;
    --plan)
      [ "$#" -ge 2 ] || { echo "missing value for --plan" >&2; exit 64; }
      PLAN="$2"
      shift 2
      ;;
    --receipt-dir)
      [ "$#" -ge 2 ] || { echo "missing value for --receipt-dir" >&2; exit 64; }
      RECEIPT_DIR="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage >&2
      exit 64
      ;;
  esac
done

[ -n "$CONFIG" ] || { echo "--config is required" >&2; exit 64; }
[ -f "$CONFIG" ] || { echo "config not found: $CONFIG" >&2; exit 66; }

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
INSTALLER_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
REPO_ROOT=$(CDPATH= cd -- "$INSTALLER_ROOT/.." && pwd)
MANIFEST="$INSTALLER_ROOT/manifests/components.toml"

if [ -z "$RECEIPT_DIR" ]; then
  RECEIPT_DIR="$INSTALLER_ROOT/latticra-installer-receipts"
fi

if [ -z "$PLAN" ]; then
  PLAN="$RECEIPT_DIR/latticra-installer-plan.txt"
fi

TOTAL_PHASES=10

phase() {
  printf 'PHASE %s/%s: %s\n' "$1" "$TOTAL_PHASES" "$2"
}

fail() {
  printf 'ERROR: %s\n' "$1" >&2
  exit "${2:-1}"
}

log() {
  printf '%s\n' "$*"
}

toml_get() {
  key="$1"
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
  ' "$CONFIG"
}

cfg() {
  key="$1"
  default="$2"
  value=$(toml_get "$key" || true)
  if [ -n "$value" ]; then
    printf '%s\n' "$value"
  else
    printf '%s\n' "$default"
  fi
}

bool_true() {
  case "${1:-false}" in
    true|1|yes|on) return 0 ;;
    *) return 1 ;;
  esac
}

bool01() {
  if bool_true "$1"; then printf '1\n'; else printf '0\n'; fi
}

expand_prefix() {
  raw="$1"
  case "$raw" in
    "~") printf '%s\n' "$HOME" ;;
    "~/"*) printf '%s/%s\n' "$HOME" "${raw#\~/}" ;;
    *) printf '%s\n' "$raw" ;;
  esac
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

safe_prefix_guard() {
  prefix="$1"
  [ -n "$prefix" ] || fail "resolved install prefix is empty" 73

  case "$prefix" in
    /|/usr|/usr/*|/bin|/bin/*|/sbin|/sbin/*|/etc|/etc/*|/boot|/boot/*|/var|/var/lib|/var/lib/*|/System|/System/*|/Library|/Library/*)
      fail "refusing unsafe system prefix: $prefix" 73
      ;;
  esac

  case "$prefix" in
    "$HOME"/.local/share/latticra|"$HOME"/.local/share/latticra/*|"$HOME"/.local/share/latticra-validation|"$HOME"/.local/share/latticra-validation/*)
      :
      ;;
    *)
      fail "installer only allows Latticra user-local prefixes under $HOME/.local/share/latticra* : $prefix" 73
      ;;
  esac
}

write_file() {
  target="$1"
  mode="$2"
  mkdir -p "$(dirname -- "$target")"
  cat > "$target"
  chmod "$mode" "$target"
  log "[write] $target"
}

write_managed_file() {
  target="$1"
  mode="$2"
  tmp="$target.tmp.$$"
  mkdir -p "$(dirname -- "$target")"
  cat > "$tmp"
  if [ -e "$target" ] && ! grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$target" 2>/dev/null; then
    rm -f "$tmp"
    fail "refusing to overwrite unmanaged file: $target" 74
  fi
  mv "$tmp" "$target"
  chmod "$mode" "$target"
  log "[write-managed] $target"
}

copy_if_exists() {
  src="$1"
  dest_dir="$2"
  if [ -e "$src" ]; then
    mkdir -p "$dest_dir"
    base=$(basename -- "$src")
    rm -rf "$dest_dir/$base"
    cp -R "$src" "$dest_dir/"
    log "[copy] $src -> $dest_dir/$base"
  fi
}

install_built_executables_from_dir() {
  srcdir="$1"
  [ -d "$srcdir" ] || return 0
  find "$srcdir" -maxdepth 1 -type f -perm -111 2>/dev/null | while IFS= read -r exe; do
    name=$(basename -- "$exe")
    case "$name" in
      build-script-*|deps|examples|incremental|*.d|*.rlib|*.rmeta) continue ;;
    esac
    cp "$exe" "$PREFIX/bin/$name"
    chmod 0755 "$PREFIX/bin/$name"
    log "[binary] $PREFIX/bin/$name"
  done
}

write_component_marker() {
  marker="$1"
  component="$2"
  write_file "$marker" 0644 <<MARKER
component=$component
profile=$PROFILE
mode=$MODE
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0
MARKER
}

PROFILE=$(cfg profile custom)
INSTALL_PREFIX_RAW=$(cfg install_prefix '~/.local/share/latticra')
DRY_RUN=$(cfg dry_run true)
ALLOW_HOST_MUTATION=$(cfg allow_host_mutation false)
ALLOW_NETWORK_EFFECT=$(cfg allow_network_effect false)
REQUIRE_COMPONENT_MANIFEST=$(cfg require_component_manifest true)
REQUIRE_ARTIFACT_MEASUREMENTS=$(cfg require_artifact_measurements true)
REQUIRE_VERIFICATION_POLICY_METADATA=$(cfg require_verification_policy_metadata true)
WRITE_OPERATOR_RECEIPT=$(cfg write_operator_receipt true)

LAT_TOOLING=$(cfg lat_tooling true)
LIR_CONTRACTS=$(cfg lir_contracts true)
SEAL_REPORT_ONLY=$(cfg seal_report_only true)
FEDORA_VALIDATION=$(cfg fedora_validation false)
DOCS_AND_EXAMPLES=$(cfg docs_and_examples true)
DEVELOPER_CLI_HELPERS=$(cfg developer_cli_helpers true)

CREATE_PREFIX_LAYOUT=$(cfg create_prefix_layout true)
CREATE_COMPONENT_MARKERS=$(cfg create_component_markers true)
CREATE_CLI_SHIMS=$(cfg create_cli_shims true)
PRESERVE_EXISTING_FILES=$(cfg preserve_existing_files true)

BUILD_GUI_INSTALLER=$(cfg build_gui_installer true)
BUILD_LATTICRA_FROM_SOURCE=$(cfg build_latticra_from_source true)
INSTALL_PAYLOAD_TREE=$(cfg install_payload_tree true)
INSTALL_DESKTOP_ENTRY=$(cfg install_desktop_entry true)
INSTALL_USER_BIN_WRAPPERS=$(cfg install_user_bin_wrappers true)

PREFIX=$(expand_prefix "$INSTALL_PREFIX_RAW")
USER_BIN="$HOME/.local/bin"
PAYLOAD_DIR="$PREFIX/lib/latticra"
RECEIPTS_IN_PREFIX="$PREFIX/share/latticra/receipts"
TS=$(date -u +"%Y%m%dT%H%M%SZ")

if bool_true "$DRY_RUN"; then
  MODE="dry-install"
else
  MODE="local-prefix-install"
fi

phase 1 "validate installer configuration"

if ! bool_true "$DRY_RUN" && ! bool_true "$ALLOW_HOST_MUTATION"; then
  fail "real install requested, but allow_host_mutation is false" 77
fi

if bool_true "$ALLOW_NETWORK_EFFECT"; then
  fail "network authority is not implemented in this installer" 78
fi

phase 2 "load component manifest"

if bool_true "$REQUIRE_COMPONENT_MANIFEST" && [ ! -f "$MANIFEST" ]; then
  fail "required component manifest missing: $MANIFEST" 66
fi

phase 3 "resolve and guard install prefix"

safe_prefix_guard "$PREFIX"

phase 4 "generate install plan"

mkdir -p "$(dirname -- "$PLAN")"
cat > "$PLAN" <<PLANFILE
LATTICRA INSTALLER PLAN

timestamp_utc=$TS
repo_root=$REPO_ROOT
installer_root=$INSTALLER_ROOT
config=$CONFIG
profile=$PROFILE
mode=$MODE
install_prefix=$PREFIX
user_bin=$USER_BIN
payload_dir=$PAYLOAD_DIR
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0

[components]
lat_tooling=$LAT_TOOLING
lir_contracts=$LIR_CONTRACTS
seal_report_only=$SEAL_REPORT_ONLY
fedora_validation=$FEDORA_VALIDATION
docs_and_examples=$DOCS_AND_EXAMPLES
developer_cli_helpers=$DEVELOPER_CLI_HELPERS

[behavior]
create_prefix_layout=$CREATE_PREFIX_LAYOUT
create_component_markers=$CREATE_COMPONENT_MARKERS
create_cli_shims=$CREATE_CLI_SHIMS
preserve_existing_files=$PRESERVE_EXISTING_FILES
build_gui_installer=$BUILD_GUI_INSTALLER
build_latticra_from_source=$BUILD_LATTICRA_FROM_SOURCE
install_payload_tree=$INSTALL_PAYLOAD_TREE
install_desktop_entry=$INSTALL_DESKTOP_ENTRY
install_user_bin_wrappers=$INSTALL_USER_BIN_WRAPPERS
PLANFILE
log "[plan] $PLAN"

if bool_true "$DRY_RUN"; then
  phase 5 "dry-run prefix layout"
  log "[dry-run] would create $PREFIX"
  log "[dry-run] would install payload tree to $PAYLOAD_DIR"
  log "[dry-run] would install user commands in $USER_BIN"
  log "[dry-run] would build/copy Latticra Panel when cargo is available"
  phase 6 "dry-run build project"
  log "[dry-run] would try Cargo/CMake/Make builds when configured"
  phase 7 "dry-run install wrappers"
  log "[dry-run] would write latticra, lat, latticra-seal, latticra-panel commands"
  phase 8 "dry-run desktop integration"
  log "[dry-run] would write desktop entry when configured"
  phase 9 "dry-run manifest"
  log "[dry-run] would measure installed files"
  phase 10 "write operator receipt"
  mkdir -p "$RECEIPT_DIR"
  RECEIPT="$RECEIPT_DIR/latticra-installer-receipt-$TS.txt"
  cat > "$RECEIPT" <<RECEIPTFILE
LATTICRA INSTALLER RECEIPT

timestamp_utc=$TS
profile=$PROFILE
mode=$MODE
result=ok
install_prefix=$PREFIX
dry_run=true
plan_file=$PLAN
config=$CONFIG
RECEIPTFILE
  cp "$RECEIPT" "$RECEIPT_DIR/latest-receipt.txt"
  log "RECEIPT: $RECEIPT"
  log "INSTALLER_RESULT: success mode=$MODE prefix=$PREFIX"
  exit 0
fi

phase 5 "build local prefix layout"

if bool_true "$CREATE_PREFIX_LAYOUT"; then
  mkdir -p \
    "$PREFIX/bin" \
    "$PREFIX/etc/latticra" \
    "$PREFIX/lib" \
    "$PREFIX/share/doc/latticra" \
    "$PREFIX/share/latticra" \
    "$PREFIX/share/latticra/components" \
    "$PREFIX/share/latticra/fedora-validation" \
    "$PREFIX/share/latticra/lir-contracts" \
    "$PREFIX/share/latticra/receipts" \
    "$PAYLOAD_DIR" \
    "$USER_BIN"
  log "[mkdir] $PREFIX"
fi

cp "$CONFIG" "$PREFIX/etc/latticra/installer-config.toml"
cp "$PLAN" "$RECEIPTS_IN_PREFIX/install-plan-$TS.txt"

phase 6 "install Latticra payload tree"

if bool_true "$INSTALL_PAYLOAD_TREE"; then
  mkdir -p "$PAYLOAD_DIR"
  for item in assets docs examples fixtures include packaging scripts src tests tools README.md STATUS.md SECURITY.md CONTRIBUTING.md TRADEMARK_POLICY.md LICENSE LICENSES; do
    copy_if_exists "$REPO_ROOT/$item" "$PAYLOAD_DIR"
  done
  mkdir -p "$PAYLOAD_DIR/installer"
  for item in README.md INSTALLER_ROADMAP.md TREE.txt configs docs manifests scripts; do
    copy_if_exists "$INSTALLER_ROOT/$item" "$PAYLOAD_DIR/installer"
  done

  if [ -d "$INSTALLER_ROOT/latticra-installer" ]; then
    mkdir -p "$PAYLOAD_DIR/installer/latticra-installer"
    for item in Cargo.toml Cargo.lock .gitignore assets src; do
      copy_if_exists "$INSTALLER_ROOT/latticra-installer/$item" "$PAYLOAD_DIR/installer/latticra-installer"
    done
  fi
fi

phase 7 "build available binaries"

if bool_true "$BUILD_GUI_INSTALLER" && [ -f "$INSTALLER_ROOT/latticra-installer/Cargo.toml" ]; then
  if command -v cargo >/dev/null 2>&1; then
    log "[cargo] building graphical installer release binary"
    (cd "$INSTALLER_ROOT/latticra-installer" && cargo build --release)
    if [ -x "$INSTALLER_ROOT/latticra-installer/target/release/latticra-panel" ]; then
      cp "$INSTALLER_ROOT/latticra-installer/target/release/latticra-panel" "$PREFIX/bin/latticra-panel"
      chmod 0755 "$PREFIX/bin/latticra-panel"
      log "[binary] $PREFIX/bin/latticra-panel"
    fi
  else
    log "[skip] cargo not found; GUI binary was not built"
  fi
fi

if bool_true "$BUILD_LATTICRA_FROM_SOURCE"; then
  if [ -f "$REPO_ROOT/Cargo.toml" ] && command -v cargo >/dev/null 2>&1; then
    log "[cargo] building repo root release binaries"
    (cd "$REPO_ROOT" && cargo build --release)
    install_built_executables_from_dir "$REPO_ROOT/target/release"
  elif [ -f "$REPO_ROOT/CMakeLists.txt" ] && command -v cmake >/dev/null 2>&1; then
    log "[cmake] building repo root"
    (cd "$REPO_ROOT" && cmake -S . -B build/latticra-release -DCMAKE_BUILD_TYPE=Release && cmake --build build/latticra-release)
    find "$REPO_ROOT/build/latticra-release" -type f -perm -111 2>/dev/null | while IFS= read -r exe; do
      name=$(basename -- "$exe")
      cp "$exe" "$PREFIX/bin/$name"
      chmod 0755 "$PREFIX/bin/$name"
      log "[binary] $PREFIX/bin/$name"
    done
  elif [ -f "$REPO_ROOT/Makefile" ]; then
    log "[make] building repo root with default Makefile target"
    (cd "$REPO_ROOT" && make)
    for dir in "$REPO_ROOT/bin" "$REPO_ROOT/build" "$REPO_ROOT/target/release"; do
      install_built_executables_from_dir "$dir"
    done
  else
    log "[skip] no Cargo.toml, CMakeLists.txt, or Makefile found at repo root"
  fi
fi

phase 8 "install selected components and commands"

if bool_true "$CREATE_COMPONENT_MARKERS"; then
  if bool_true "$LAT_TOOLING"; then
    write_component_marker "$PREFIX/share/latticra/components/lat-tooling.installed" "lat_tooling"
  fi
  if bool_true "$LIR_CONTRACTS"; then
    write_component_marker "$PREFIX/share/latticra/components/lir-contracts.installed" "lir_contracts"
  fi
  if bool_true "$SEAL_REPORT_ONLY"; then
    write_component_marker "$PREFIX/share/latticra/components/latticra-seal.installed" "seal_report_only"
  fi
  if bool_true "$FEDORA_VALIDATION"; then
    write_component_marker "$PREFIX/share/latticra/components/fedora-validation.installed" "fedora_validation"
  fi
  if bool_true "$DOCS_AND_EXAMPLES"; then
    write_component_marker "$PREFIX/share/latticra/components/docs-and-examples.installed" "docs_and_examples"
  fi
  if bool_true "$DEVELOPER_CLI_HELPERS"; then
    write_component_marker "$PREFIX/share/latticra/components/developer-cli-helpers.installed" "developer_cli_helpers"
  fi
fi

if bool_true "$LIR_CONTRACTS"; then
  write_file "$PREFIX/share/latticra/lir-contracts/README.md" 0644 <<'LIRREADME'
# LIR Contracts

This directory is reserved for installed Latticra Intermediate Representation contracts and validated contract artifacts.
LIRREADME
fi

if bool_true "$SEAL_REPORT_ONLY"; then
  write_file "$PREFIX/etc/latticra/seal.toml" 0644 <<'SEALCONF'
mode = "report-only"
production_enforcement_ready = false
operator_receipts = true
SEALCONF
fi

if bool_true "$FEDORA_VALIDATION"; then
  write_file "$PREFIX/share/latticra/fedora-validation/README.md" 0644 <<'FEDORAREADME'
# Fedora Validation Workspace

This directory is reserved for Fedora/Linux validation outputs, notes, and generated reports.
This installer does not change Fedora system configuration.
FEDORAREADME
fi

if bool_true "$DOCS_AND_EXAMPLES"; then
  write_file "$PREFIX/share/doc/latticra/README.installed.md" 0644 <<DOCSREADME
# Latticra local-prefix installation

Prefix: $PREFIX
Payload tree: $PAYLOAD_DIR
Receipts: $RECEIPTS_IN_PREFIX

This user-local install does not modify kernel, systemd, SELinux, or system package state.
DOCSREADME
fi

if bool_true "$CREATE_CLI_SHIMS" && bool_true "$INSTALL_USER_BIN_WRAPPERS"; then
  write_managed_file "$USER_BIN/latticra" 0755 <<LATTICRAWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
case "\${1:-status}" in
  status)
    echo "Latticra is installed."
    echo "prefix=\$PREFIX"
    echo "payload=\$PREFIX/lib/latticra"
    echo "receipts=\$PREFIX/share/latticra/receipts"
    ;;
  path)
    echo "\$PREFIX"
    ;;
  gui)
    exec "\$HOME/.local/bin/latticra-panel"
    ;;
  receipts)
    ls -la "\$PREFIX/share/latticra/receipts"
    ;;
  docs)
    echo "\$PREFIX/share/doc/latticra"
    ;;
  seal)
    shift
    exec "\$HOME/.local/bin/latticra-seal" "\$@"
    ;;
  run)
    shift
    if [ -x "\$PREFIX/bin/latticra" ]; then
      exec "\$PREFIX/bin/latticra" "\$@"
    fi
    echo "No compiled Latticra runtime binary named latticra was found in \$PREFIX/bin." >&2
    echo "Installed source/payload is available at \$PREFIX/lib/latticra." >&2
    exit 1
    ;;
  *)
    if [ -x "\$PREFIX/bin/latticra" ]; then
      exec "\$PREFIX/bin/latticra" "\$@"
    fi
    echo "usage: latticra {status|path|gui|receipts|docs|seal|run}" >&2
    exit 64
    ;;
esac
LATTICRAWRAP

  write_managed_file "$USER_BIN/lat" 0755 <<LATWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
if [ -x "\$PREFIX/bin/lat" ]; then
  exec "\$PREFIX/bin/lat" "\$@"
fi
if [ -x "\$PREFIX/lib/latticra/tools/lat" ]; then
  exec "\$PREFIX/lib/latticra/tools/lat" "\$@"
fi
echo "Lat tooling is installed as part of the Latticra payload."
echo "prefix=\$PREFIX"
echo "payload=\$PREFIX/lib/latticra"
echo "No compiled lat binary was found yet."
LATWRAP

  write_managed_file "$USER_BIN/latticra-seal" 0755 <<SEALWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
REPORT_DIR="\$PREFIX/share/latticra/receipts"
mkdir -p "\$REPORT_DIR"
case "\${1:-report}" in
  report)
    TS=\$(date -u +"%Y%m%dT%H%M%SZ")
    REPORT="\$REPORT_DIR/latticra-seal-report-\$TS.txt"
    {
      echo "LATTICRA SEAL REPORT"
      echo
      echo "timestamp_utc=\$TS"
      echo "mode=report-only"
      echo "prefix=\$PREFIX"
      echo "kernel=\$(uname -srmo 2>/dev/null || uname -a)"
      if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo "os=\${PRETTY_NAME:-unknown}"
      fi
      echo "network_authority=0"
      echo "runtime_enforcement_authority=0"
      echo
      echo "components:"
      ls "\$PREFIX/share/latticra/components" 2>/dev/null || true
    } > "\$REPORT"
    cat "\$REPORT"
    ;;
  path)
    echo "\$REPORT_DIR"
    ;;
  *)
    echo "usage: latticra-seal {report|path}" >&2
    exit 64
    ;;
esac
SEALWRAP

  if [ -x "$PREFIX/bin/latticra-panel" ]; then
    write_managed_file "$USER_BIN/latticra-panel" 0755 <<GUIWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
export LATTICRA_INSTALLER_ROOT="$PAYLOAD_DIR/installer"
exec "$PREFIX/bin/latticra-panel" "\$@"
GUIWRAP

    # Compatibility wrapper for older docs/scripts that still call latticra-installer.
    write_managed_file "$USER_BIN/latticra-installer" 0755 <<OLDGUIWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
exec "$USER_BIN/latticra-panel" "\$@"
OLDGUIWRAP
  fi
fi

phase 9 "install desktop entry and measurements"

if bool_true "$INSTALL_DESKTOP_ENTRY" && [ -x "$PREFIX/bin/latticra-panel" ]; then
  ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"
  APP_DIR="$HOME/.local/share/applications"
  mkdir -p "$ICON_DIR" "$APP_DIR"

  # Remove old managed desktop metadata so GNOME/Fedora does not keep showing
  # the previous "Latticra Installer" application identity.
  OLD_DESKTOP="$APP_DIR/latticra-installer.desktop"
  if [ -f "$OLD_DESKTOP" ] && grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$OLD_DESKTOP" 2>/dev/null; then
    rm -f "$OLD_DESKTOP"
    log "[remove-managed] $OLD_DESKTOP"
  fi

  if [ -f "$INSTALLER_ROOT/latticra-installer/assets/latticra-seal.png" ]; then
    cp "$INSTALLER_ROOT/latticra-installer/assets/latticra-seal.png" "$ICON_DIR/latticra-panel.png"
    log "[icon] $ICON_DIR/latticra-panel.png"
  fi

  write_managed_file "$APP_DIR/latticra-panel.desktop" 0644 <<DESKTOP
[Desktop Entry]
# LATTICRA_INSTALLER_MANAGED=1
Version=1.0
Type=Application
Name=Latticra Panel
GenericName=Latticra Control Panel
Comment=Install and manage Latticra, Lat, LIR, and Latticra Seal
Exec=$USER_BIN/latticra-panel
Icon=latticra-panel
Terminal=false
Categories=Development;System;
Keywords=Latticra;Lat;LIR;Seal;Installer;Panel;
StartupNotify=true
StartupWMClass=latticra-panel
DESKTOP

  if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database "$APP_DIR" >/dev/null 2>&1 || true
  fi

  if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    gtk-update-icon-cache -q "$HOME/.local/share/icons/hicolor" >/dev/null 2>&1 || true
  fi
fi

MEASUREMENTS="$RECEIPTS_IN_PREFIX/manifest-$TS.sha256"
mkdir -p "$RECEIPTS_IN_PREFIX"
if command -v sha256sum >/dev/null 2>&1; then
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do sha256sum "/$f"; done) > "$MEASUREMENTS" || true
elif command -v shasum >/dev/null 2>&1; then
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do shasum -a 256 "/$f"; done) > "$MEASUREMENTS" || true
else
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do cksum "/$f"; done) > "$MEASUREMENTS" || true
fi
log "[measurements] $MEASUREMENTS"

phase 10 "write operator receipt"

mkdir -p "$RECEIPT_DIR" "$RECEIPTS_IN_PREFIX"
RECEIPT="$RECEIPT_DIR/latticra-installer-receipt-$TS.txt"
CONFIG_MEASUREMENT=$(measure_file "$CONFIG")
SCRIPT_MEASUREMENT=$(measure_file "$0")
if [ -f "$MANIFEST" ]; then
  MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST")
else
  MANIFEST_MEASUREMENT="missing"
fi

cat > "$RECEIPT" <<RECEIPTFILE
LATTICRA INSTALLER RECEIPT

timestamp_utc=$TS
profile=$PROFILE
mode=$MODE
result=ok
repo_root=$REPO_ROOT
install_prefix=$PREFIX
payload_dir=$PAYLOAD_DIR
user_bin=$USER_BIN
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0

dry_run=$DRY_RUN
allow_host_mutation=$ALLOW_HOST_MUTATION
allow_network_effect=$ALLOW_NETWORK_EFFECT
require_component_manifest=$REQUIRE_COMPONENT_MANIFEST
require_artifact_measurements=$REQUIRE_ARTIFACT_MEASUREMENTS
require_verification_policy_metadata=$REQUIRE_VERIFICATION_POLICY_METADATA

component_manifest=$MANIFEST
component_manifest_measurement=$MANIFEST_MEASUREMENT
config_measurement=$CONFIG_MEASUREMENT
installer_script_measurement=$SCRIPT_MEASUREMENT
installed_manifest=$MEASUREMENTS
plan_file=$PLAN

installed_commands:
  $USER_BIN/latticra
  $USER_BIN/lat
  $USER_BIN/latticra-seal
  $USER_BIN/latticra-panel
  $USER_BIN/latticra-installer (compatibility)

--- plan ---
$(cat "$PLAN")
RECEIPTFILE

cp "$RECEIPT" "$RECEIPT_DIR/latest-receipt.txt"
cp "$RECEIPT" "$RECEIPTS_IN_PREFIX/install-receipt-$TS.txt"
cp "$RECEIPT" "$RECEIPTS_IN_PREFIX/latest-receipt.txt"
log "RECEIPT: $RECEIPT"
log "INSTALLER_RESULT: success mode=$MODE prefix=$PREFIX"

if ! printf '%s' ":$PATH:" | grep -q ":$USER_BIN:"; then
  log "NOTE: $USER_BIN is not currently in PATH. Add this to your shell profile:"
  log "  export PATH=\"$USER_BIN:\$PATH\""
fi
