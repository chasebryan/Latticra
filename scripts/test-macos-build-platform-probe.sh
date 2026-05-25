#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos build platform probe: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos build platform probe: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  pattern="$1"
  if ! printf '%s\n' "$probe_output" | grep -Fq -- "$pattern"; then
    printf 'macos build platform probe: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_BUILD_PLATFORM_PROBE.md'
status='docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md'
script='scripts/macos-build-platform-probe.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file installer/latticra-installer/Cargo.toml
require_file installer/latticra-installer/src/ui.rs
require_file tests/lat_language_grammar_invariants.c
require_file src/lat_parser.c
require_file include/latticra/lat_parser.h

require_contains 'Status: no-effect macOS build/platform probe' "$doc"
require_contains 'sh scripts/macos-build-platform-probe.sh' "$doc"
require_contains 'panel_build_probe_recorded=1' "$doc"
require_contains 'panel_build_performed=0' "$doc"
require_contains 'c_test_build_probe_recorded=1' "$doc"
require_contains 'c_test_build_performed=0' "$doc"
require_contains 'app_bundle_created=0' "$doc"
require_contains 'installer_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'keychain_authority=0' "$doc"
require_contains 'endpoint_security_authority=0' "$doc"
require_contains 'system_extension_authority=0' "$doc"
require_contains 'macOS user-local app bundle implementation plan' "$doc"

require_contains 'Status: no-effect probe status' "$status"
require_contains 'macos_build_platform_probe_present=1' "$status"
require_contains 'macos_probe_script_present=1' "$status"
require_contains 'macos_probe_guard_present=1' "$status"
require_contains 'macos_host_detection_recorded=1' "$status"
require_contains 'macos_architecture_recorded=1' "$status"
require_contains 'macos_sw_vers_probe_recorded=1' "$status"
require_contains 'macos_clang_probe_recorded=1' "$status"
require_contains 'macos_rust_probe_recorded=1' "$status"
require_contains 'macos_panel_build_probe_recorded=1' "$status"
require_contains 'macos_c_test_build_probe_recorded=1' "$status"
require_contains 'panel_build_performed=0' "$status"
require_contains 'c_test_build_performed=0' "$status"
require_contains 'app_bundle_created=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_BUILD_PLATFORM_PROBE_STATUS.md' "$index"
require_contains 'macOS build/platform probe status' "$index"
require_contains 'stage_1_macos_build_probe=present' "$transfer_plan"
require_contains 'macos_build_platform_probe_present=1' "$transfer_status"
require_contains 'macos_dry_run_plan_adapter_present=1' "$status"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$status"

require_contains 'MACOS BUILD PLATFORM PROBE' "$script"
require_contains 'panel_build_performed=0' "$script"
require_contains 'c_test_build_performed=0' "$script"
require_contains 'app_bundle_created=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'keychain_authority=0' "$script"
require_contains 'system_extension_authority=0' "$script"

probe_output=$(sh "$script")
require_output_contains 'MACOS BUILD PLATFORM PROBE'
require_output_contains 'probe_status=ok'
require_output_contains 'architecture_recorded=1'
require_output_contains 'panel_build_probe_recorded=1'
require_output_contains 'panel_build_performed=0'
require_output_contains 'c_test_build_probe_recorded=1'
require_output_contains 'c_test_build_performed=0'
require_output_contains 'app_bundle_created=0'
require_output_contains 'installer_write_performed=0'
require_output_contains 'host_mutation_performed=0'
require_output_contains 'network_performed=0'
require_output_contains 'production_installer_ready=0'

printf 'macos_build_platform_probe: ok\n'
