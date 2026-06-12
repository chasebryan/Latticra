#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra universal installer preflight contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

preflight='scripts/latticra-universal-installer-preflight.sh'
manifest='installer/manifests/universal-installer-capabilities.toml'
components='installer/manifests/components.toml'

for file in "$preflight" "$manifest" "$components" Makefile scripts/test-quality-safety-guards.sh
do
  require_file "$file"
done

require_contains 'production_installer_ready = false' "$manifest"
require_contains 'comprehensive_installer_ready = false' "$manifest"
require_contains 'network_required = false' "$manifest"
require_contains 'root_required = false' "$manifest"
require_contains '[host.linux]' "$manifest"
require_contains '[host.macos]' "$manifest"
require_contains '[host.freebsd]' "$manifest"
require_contains '[host.openbsd]' "$manifest"
require_contains '[host.windows_compat_shell]' "$manifest"
require_contains 'native_windows_supported = false' "$manifest"
require_contains 'windows_wsl_required = true' "$manifest"
require_contains 'latticra_console' "$manifest"
require_contains 'lat_tooling' "$manifest"
require_contains 'lir_contracts' "$manifest"
require_contains 'seal_report_only' "$manifest"
require_contains 'nadia_offline_ai' "$manifest"
require_contains 'docs_and_examples' "$manifest"
require_contains 'developer_cli_helpers' "$manifest"

require_contains 'sh ./scripts/test-latticra-universal-installer-preflight.sh' Makefile
require_contains 'latticra-universal-installer-preflight:' Makefile
require_contains 'sh ./scripts/latticra-universal-installer-preflight.sh' Makefile
require_contains 'sh ./scripts/test-latticra-universal-installer-preflight.sh' scripts/test-quality-safety-guards.sh

linux_output="$(sh "$preflight" --host Linux)"
require_output_contains 'LATTICRA UNIVERSAL INSTALLER PREFLIGHT' "$linux_output"
require_output_contains 'universal_installer_preflight_present=1' "$linux_output"
require_output_contains 'preflight_mode=no-effect-cross-platform-classifier' "$linux_output"
require_output_contains 'host_os_family=linux' "$linux_output"
require_output_contains 'posix_shell_install_supported=1' "$linux_output"
require_output_contains 'local_prefix_install_supported=1' "$linux_output"
require_output_contains 'native_package_lane_present=1' "$linux_output"
require_output_contains 'native_package_install_ready=0' "$linux_output"
require_output_contains 'os_image_install_ready=0' "$linux_output"
require_output_contains 'component_manifest_present=1' "$linux_output"
require_output_contains 'capability_manifest_present=1' "$linux_output"
require_output_contains 'components_total=8' "$linux_output"
require_output_contains 'components_default_enabled=6' "$linux_output"
require_output_contains 'feature_components_required=8' "$linux_output"
require_output_contains 'feature_components_declared_count=8' "$linux_output"
require_output_contains 'all_feature_components_declared=1' "$linux_output"
require_output_contains 'component_latticra_console_declared=1' "$linux_output"
require_output_contains 'component_lat_tooling_declared=1' "$linux_output"
require_output_contains 'component_lir_contracts_declared=1' "$linux_output"
require_output_contains 'component_seal_report_only_declared=1' "$linux_output"
require_output_contains 'component_nadia_offline_ai_declared=1' "$linux_output"
require_output_contains 'component_fedora_validation_declared=1' "$linux_output"
require_output_contains 'component_docs_and_examples_declared=1' "$linux_output"
require_output_contains 'component_developer_cli_helpers_declared=1' "$linux_output"
require_output_contains 'default_safe_components_required=6' "$linux_output"
require_output_contains 'default_safe_components_enabled_count=6' "$linux_output"
require_output_contains 'all_default_safe_components_enabled=1' "$linux_output"
require_output_contains 'optional_ai_component_declared=1' "$linux_output"
require_output_contains 'optional_ai_default_enabled=0' "$linux_output"
require_output_contains 'optional_fedora_validation_component_declared=1' "$linux_output"
require_output_contains 'optional_fedora_validation_default_enabled=0' "$linux_output"
require_output_contains 'network_required=0' "$linux_output"
require_output_contains 'root_required=0' "$linux_output"
require_output_contains 'install_performed=0' "$linux_output"
require_output_contains 'host_mutation_performed=0' "$linux_output"
require_output_contains 'production_installer_ready=0' "$linux_output"
require_output_contains 'comprehensive_installer_ready=0' "$linux_output"
require_output_contains 'next_lane=universal-installer-host-package-selector' "$linux_output"

darwin_output="$(sh "$preflight" --host Darwin)"
require_output_contains 'host_os_family=macos' "$darwin_output"
require_output_contains 'local_prefix_install_supported=1' "$darwin_output"
require_output_contains 'native_package_lane_present=1' "$darwin_output"
require_output_contains 'native_windows_supported=0' "$darwin_output"
require_output_contains 'windows_wsl_required=0' "$darwin_output"

freebsd_output="$(sh "$preflight" --host FreeBSD)"
require_output_contains 'host_os_family=freebsd' "$freebsd_output"
require_output_contains 'local_prefix_install_supported=1' "$freebsd_output"
require_output_contains 'native_package_install_ready=0' "$freebsd_output"

openbsd_output="$(sh "$preflight" --host OpenBSD)"
require_output_contains 'host_os_family=openbsd' "$openbsd_output"
require_output_contains 'local_prefix_install_supported=1' "$openbsd_output"
require_output_contains 'native_package_install_ready=0' "$openbsd_output"

mingw_output="$(sh "$preflight" --host MINGW64_NT)"
require_output_contains 'host_os_family=windows-compat-shell' "$mingw_output"
require_output_contains 'local_prefix_install_supported=0' "$mingw_output"
require_output_contains 'native_windows_supported=0' "$mingw_output"
require_output_contains 'windows_wsl_required=1' "$mingw_output"
require_output_contains 'unsupported_host_blocked=1' "$mingw_output"

unknown_output="$(sh "$preflight" --host Plan9)"
require_output_contains 'host_os_family=unknown-posix' "$unknown_output"
require_output_contains 'local_prefix_install_supported=0' "$unknown_output"
require_output_contains 'unsupported_host_blocked=1' "$unknown_output"
require_output_contains 'install_performed=0' "$unknown_output"

printf 'latticra_universal_installer_preflight_contract: ok\n'
