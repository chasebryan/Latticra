#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-build-platform-probe.sh [--output <file>]

Records a no-effect macOS build/platform readiness report.
It does not build app bundles, install files, mutate shell profiles, use launchd,
access Keychain, request TCC permissions, use the network, or grant authority.
USAGE
}

OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --output)
      [ "$#" -ge 2 ] || { echo "missing value for --output" >&2; exit 64; }
      OUTPUT="$2"
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

command_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

first_line() {
  "$@" 2>/dev/null | sed -n '1p' | tr '\t' ' '
}

bool_file() {
  if [ -f "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

bool_dir() {
  if [ -d "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
UNAME_S=$(uname -s 2>/dev/null || printf 'unknown')
UNAME_M=$(uname -m 2>/dev/null || printf 'unknown')

if [ "$UNAME_S" = "Darwin" ]; then
  MACOS_HOST_DETECTED=1
else
  MACOS_HOST_DETECTED=0
fi

SW_VERS_AVAILABLE=$(command_available sw_vers)
CLANG_AVAILABLE=$(command_available clang)
CC_AVAILABLE=$(command_available cc)
RUSTC_AVAILABLE=$(command_available rustc)
CARGO_AVAILABLE=$(command_available cargo)
MAKE_AVAILABLE=$(command_available make)

if [ "$SW_VERS_AVAILABLE" = "1" ]; then
  PRODUCT_NAME=$(sw_vers -productName 2>/dev/null || printf 'unknown')
  PRODUCT_VERSION=$(sw_vers -productVersion 2>/dev/null || printf 'unknown')
  PRODUCT_BUILD=$(sw_vers -buildVersion 2>/dev/null || printf 'unknown')
  SW_VERS_RECORDED=1
else
  PRODUCT_NAME="unavailable"
  PRODUCT_VERSION="unavailable"
  PRODUCT_BUILD="unavailable"
  SW_VERS_RECORDED=0
fi

if [ "$CLANG_AVAILABLE" = "1" ]; then
  CLANG_SUMMARY=$(first_line clang --version)
  CLANG_PROBE_RECORDED=1
else
  CLANG_SUMMARY="unavailable"
  CLANG_PROBE_RECORDED=0
fi

if [ "$RUSTC_AVAILABLE" = "1" ]; then
  RUSTC_SUMMARY=$(first_line rustc --version)
else
  RUSTC_SUMMARY="unavailable"
fi

if [ "$CARGO_AVAILABLE" = "1" ]; then
  CARGO_SUMMARY=$(first_line cargo --version)
else
  CARGO_SUMMARY="unavailable"
fi

PANEL_MANIFEST_PRESENT=$(bool_file "$ROOT/installer/latticra-installer/Cargo.toml")
PANEL_LOCK_PRESENT=$(bool_file "$ROOT/installer/latticra-installer/Cargo.lock")
PANEL_SOURCE_PRESENT=$(bool_file "$ROOT/installer/latticra-installer/src/ui.rs")
C_TEST_SOURCE_PRESENT=$(bool_file "$ROOT/tests/lat_language_grammar_invariants.c")
C_INCLUDE_PRESENT=$(bool_dir "$ROOT/include/latticra")
C_SRC_PRESENT=$(bool_file "$ROOT/src/lat_parser.c")

if [ "$CARGO_AVAILABLE" = "1" ] && [ "$PANEL_MANIFEST_PRESENT" = "1" ] && [ "$PANEL_SOURCE_PRESENT" = "1" ]; then
  PANEL_BUILD_READY=1
else
  PANEL_BUILD_READY=0
fi

if { [ "$CLANG_AVAILABLE" = "1" ] || [ "$CC_AVAILABLE" = "1" ]; } && [ "$C_TEST_SOURCE_PRESENT" = "1" ] && [ "$C_INCLUDE_PRESENT" = "1" ] && [ "$C_SRC_PRESENT" = "1" ]; then
  C_TEST_BUILD_READY=1
else
  C_TEST_BUILD_READY=0
fi

REPORT=$(cat <<REPORT
MACOS BUILD PLATFORM PROBE

probe_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_host_detected=$MACOS_HOST_DETECTED
sw_vers_available=$SW_VERS_AVAILABLE
sw_vers_recorded=$SW_VERS_RECORDED
macos_product_name=$PRODUCT_NAME
macos_product_version=$PRODUCT_VERSION
macos_build_version=$PRODUCT_BUILD
clang_available=$CLANG_AVAILABLE
clang_probe_recorded=$CLANG_PROBE_RECORDED
clang_summary=$CLANG_SUMMARY
cc_available=$CC_AVAILABLE
rustc_available=$RUSTC_AVAILABLE
rustc_summary=$RUSTC_SUMMARY
cargo_available=$CARGO_AVAILABLE
cargo_summary=$CARGO_SUMMARY
make_available=$MAKE_AVAILABLE
rust_probe_recorded=1
architecture_recorded=1
panel_manifest_present=$PANEL_MANIFEST_PRESENT
panel_lock_present=$PANEL_LOCK_PRESENT
panel_source_present=$PANEL_SOURCE_PRESENT
panel_build_probe_recorded=1
panel_build_performed=0
panel_build_ready=$PANEL_BUILD_READY
c_test_source_present=$C_TEST_SOURCE_PRESENT
c_include_present=$C_INCLUDE_PRESENT
c_src_present=$C_SRC_PRESENT
c_test_build_probe_recorded=1
c_test_build_performed=0
c_test_build_ready=$C_TEST_BUILD_READY
app_bundle_created=0
installer_write_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
next_lane=macos-dry-run-plan-adapter
REPORT
)

if [ -n "$OUTPUT" ]; then
  mkdir -p "$(dirname -- "$OUTPUT")"
  printf '%s\n' "$REPORT" > "$OUTPUT"
  printf 'MACOS_BUILD_PLATFORM_PROBE_REPORT: %s\n' "$OUTPUT"
else
  printf '%s\n' "$REPORT"
fi
