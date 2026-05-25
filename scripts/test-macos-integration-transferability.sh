#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos integration transferability: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos integration transferability: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
index='docs/status/README.md'

require_file "$plan"
require_file "$status"
require_file "$index"
require_file installer/latticra-installer/src/config.rs
require_file installer/latticra-installer/src/ui.rs
require_file installer/scripts/latticra-installer-apply.sh
require_file installer/scripts/latticra-installer-uninstall.sh
require_file installer/scripts/latticra-installer-verify.sh

require_contains 'Status: macOS integration transferability plan' "$plan"
require_contains 'Current posture: planning and transferability mapping only' "$plan"
require_contains 'lat_parse_validate_lower_pipeline=transferable' "$plan"
require_contains 'latticra_seal_report_only_metadata=transferable' "$plan"
require_contains 'nadia_offline_ai_contract_surfaces=transferable' "$plan"
require_contains 'rust_egui_panel=transferable_after_macos_build_probe' "$plan"
require_contains 'xdg_desktop_entry=replace_with_app_bundle' "$plan"
require_contains 'app_support_prefix=$HOME/Library/Application Support/Latticra' "$plan"
require_contains 'app_bundle=$HOME/Applications/Latticra Panel.app' "$plan"
require_contains 'stage_1_macos_build_probe=present' "$plan"
require_contains 'docs/MACOS_BUILD_PLATFORM_PROBE.md' "$plan"
require_contains 'Latticra Panel.app/' "$plan"
require_contains 'root_authority=0' "$plan"
require_contains 'network_authority=0' "$plan"
require_contains 'launchagent_authority=0' "$plan"
require_contains 'keychain_authority=0' "$plan"
require_contains 'Endpoint_Security=future_contract_only' "$plan"
require_contains 'System_Extension=future_contract_only' "$plan"
require_contains 'Fedora/RPM lanes | Low | Keep as Linux-specific evidence, not macOS input' "$plan"
require_contains 'macos_integration_transferability_map_present=1' "$plan"
require_contains 'macos_runtime_behavior_added=0' "$plan"
require_contains 'macos_host_mutation_added=0' "$plan"
require_contains 'macos_app_bundle_created=0' "$plan"
require_contains 'macos_install_verified=0' "$plan"
require_contains 'Add a macOS dry-run plan adapter' "$plan"

require_contains 'Status: transferability status record' "$status"
require_contains 'macos_build_platform_probe_present=1' "$status"
require_contains 'macos_transferable_surfaces_classified=1' "$status"
require_contains 'macos_adapter_requirements_recorded=1' "$status"
require_contains 'macos_user_local_paths_proposed=1' "$status"
require_contains 'macos_app_bundle_proposed=1' "$status"
require_contains 'macos_security_interfaces_future_gated=1' "$status"
require_contains 'macos_runtime_behavior_added=0' "$status"
require_contains 'macos_host_mutation_added=0' "$status"
require_contains 'macos_app_bundle_created=0' "$status"
require_contains 'macos_install_verified=0' "$status"
require_contains 'macos_keychain_authority=0' "$status"
require_contains 'macos_secure_enclave_authority=0' "$status"
require_contains 'macos_tcc_bypass_authority=0' "$status"
require_contains 'macos_endpoint_security_authority=0' "$status"
require_contains 'macos_system_extension_authority=0' "$status"
require_contains 'Latticra_Panel=medium_high_transferability_with_app_bundle_adapter' "$status"
require_contains 'Fedora_RPM_lanes=not_transferable_keep_linux_specific' "$status"
require_contains 'sh scripts/test-macos-integration-transferability.sh' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md' "$index"
require_contains 'macOS integration transferability status' "$index"

printf 'macos_integration_transferability: ok\n'
