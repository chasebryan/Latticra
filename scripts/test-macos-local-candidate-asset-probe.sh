#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos local candidate asset probe: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos local candidate asset probe: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos local candidate asset probe: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_LOCAL_CANDIDATE_ASSET_PROBE.md'
status='docs/status/MACOS_LOCAL_CANDIDATE_ASSET_PROBE_STATUS.md'
script='scripts/macos-local-candidate-asset-probe.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
alignment_doc='docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md'
alignment_status='docs/status/MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md'
writer_doc='docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md'
writer_status='docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md'
workflow='.github/workflows/macos-local-candidate-asset-probe.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$alignment_doc"
require_file "$alignment_status"
require_file "$writer_doc"
require_file "$writer_status"
require_file "$workflow"
require_file installer/latticra-installer/assets/latticra-panel.png

require_contains 'Status: no-effect macOS local candidate asset probe' "$doc"
require_contains 'sh scripts/macos-local-candidate-asset-probe.sh' "$doc"
require_contains 'local_panel_executable_candidate_probe=1' "$doc"
require_contains 'local_icon_candidate_probe=1' "$doc"
require_contains 'blocked-panel-candidate-not-executable' "$doc"
require_contains 'blocked-panel-candidate-not-readable' "$doc"
require_contains 'blocked-icon-candidate-not-readable' "$doc"
require_contains 'blocked-unsupported-icon-candidate' "$doc"
require_contains 'ready-for-dry-run-writer-inputs' "$doc"
require_contains 'build_performed=0' "$doc"
require_contains 'panel_build_performed=0' "$doc"
require_contains 'icon_conversion_performed=0' "$doc"
require_contains 'download_performed=0' "$doc"
require_contains 'copy_performed=0' "$doc"
require_contains 'signing_performed=0' "$doc"
require_contains 'notarization_performed=0' "$doc"
require_contains 'app_bundle_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'macOS dry-run writer candidate integration' "$doc"
require_contains 'macOS commit gate contract' "$doc"

require_contains 'Status: no-effect local candidate asset probe status' "$status"
require_contains 'macos_local_candidate_asset_probe_present=1' "$status"
require_contains 'macos_local_candidate_asset_probe_guard_present=1' "$status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$status"
require_contains 'panel_candidate_executable_check_present=1' "$status"
require_contains 'panel_candidate_readable_check_present=1' "$status"
require_contains 'icon_candidate_format_check_present=1' "$status"
require_contains 'icon_candidate_readable_check_present=1' "$status"
require_contains 'asset_probe_ready_decision_present=1' "$status"
require_contains 'build_performed=0' "$status"
require_contains 'panel_build_performed=0' "$status"
require_contains 'icon_conversion_performed=0' "$status"
require_contains 'download_performed=0' "$status"
require_contains 'copy_performed=0' "$status"
require_contains 'signing_performed=0' "$status"
require_contains 'notarization_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'runtime_authority_granted=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_LOCAL_CANDIDATE_ASSET_PROBE_STATUS.md' "$index"
require_contains 'macOS local candidate asset probe status' "$index"
require_contains 'stage_3_local_candidate_asset_probe=present' "$transfer_plan"
require_contains 'stage_3_dry_run_writer_candidate_integration=present' "$transfer_plan"
require_contains 'docs/MACOS_LOCAL_CANDIDATE_ASSET_PROBE.md' "$transfer_plan"
require_contains 'docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md' "$transfer_plan"
require_contains 'macos_local_candidate_asset_probe_present=1' "$transfer_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$transfer_status"
require_contains 'macos_local_candidate_asset_probe_present=1' "$alignment_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$alignment_status"
require_contains 'macos_local_candidate_asset_probe_present=1' "$writer_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$writer_status"
require_contains 'macOS local candidate asset probe' "$alignment_doc"
require_contains 'macOS local candidate asset probe' "$writer_doc"
require_contains 'sh scripts/test-macos-local-candidate-asset-probe.sh' "$workflow"

require_contains 'MACOS LOCAL CANDIDATE ASSET PROBE' "$script"
require_contains 'local_panel_executable_candidate_probe=1' "$script"
require_contains 'local_icon_candidate_probe=1' "$script"
require_contains 'panel_executable_candidate_present=' "$script"
require_contains 'blocked-panel-candidate-not-readable' "$script"
require_contains 'blocked-icon-candidate-not-readable' "$script"
require_contains 'build_performed=0' "$script"
require_contains 'panel_build_performed=0' "$script"
require_contains 'icon_conversion_performed=0' "$script"
require_contains 'download_performed=0' "$script"
require_contains 'copy_performed=0' "$script"
require_contains 'signing_performed=0' "$script"
require_contains 'notarization_performed=0' "$script"
require_contains 'app_bundle_write_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'runtime_authority_granted=0' "$script"

missing_output=$(sh "$script")
require_output_contains "$missing_output" 'MACOS LOCAL CANDIDATE ASSET PROBE'
require_output_contains "$missing_output" 'probe_status=ok'
require_output_contains "$missing_output" 'asset_probe_decision=blocked-missing-panel-executable-candidate'
require_output_contains "$missing_output" 'build_performed=0'
require_output_contains "$missing_output" 'panel_build_performed=0'
require_output_contains "$missing_output" 'icon_conversion_performed=0'
require_output_contains "$missing_output" 'network_performed=0'
require_output_contains "$missing_output" 'runtime_authority_granted=0'

ready_output=$(sh "$script" --panel-executable /bin/sh --icon installer/latticra-installer/assets/latticra-panel.png)
require_output_contains "$ready_output" 'panel_candidate_path_status=allowed-local-candidate'
require_output_contains "$ready_output" 'panel_candidate_present=1'
require_output_contains "$ready_output" 'panel_candidate_executable=1'
require_output_contains "$ready_output" 'panel_executable_candidate_present=1'
require_output_contains "$ready_output" 'panel_executable_candidate_executable=1'
require_output_contains "$ready_output" 'icon_candidate_present=1'
require_output_contains "$ready_output" 'icon_candidate_format=png'
require_output_contains "$ready_output" 'icon_candidate_supported_format=1'
require_output_contains "$ready_output" 'asset_probe_decision=ready-for-dry-run-writer-inputs'
require_output_contains "$ready_output" 'panel_build_performed=0'
require_output_contains "$ready_output" 'icon_conversion_performed=0'
require_output_contains "$ready_output" 'copy_performed=0'
require_output_contains "$ready_output" 'signing_performed=0'
require_output_contains "$ready_output" 'notarization_performed=0'
require_output_contains "$ready_output" 'runtime_authority_granted=0'

not_exec_output=$(sh "$script" --panel-executable scripts/macos-app-bundle-writer-dry-run.sh --icon installer/latticra-installer/assets/latticra-panel.png)
require_output_contains "$not_exec_output" 'panel_candidate_present=1'
require_output_contains "$not_exec_output" 'panel_candidate_executable=0'
require_output_contains "$not_exec_output" 'asset_probe_decision=blocked-panel-candidate-not-executable'

unsupported_icon_output=$(sh "$script" --panel-executable /bin/sh --icon scripts/macos-app-bundle-writer-dry-run.sh)
require_output_contains "$unsupported_icon_output" 'icon_candidate_format=sh'
require_output_contains "$unsupported_icon_output" 'icon_candidate_supported_format=0'
require_output_contains "$unsupported_icon_output" 'asset_probe_decision=blocked-unsupported-icon-candidate'

unsafe_output=$(sh "$script" --panel-executable /Applications/Latticra.app --icon installer/latticra-installer/assets/latticra-panel.png)
require_output_contains "$unsafe_output" 'panel_candidate_path_status=blocked-disallowed-candidate-path'
require_output_contains "$unsafe_output" 'asset_probe_decision=blocked-disallowed-panel-candidate-path'

sh scripts/test-macos-app-bundle-writer-alignment.sh
sh scripts/test-macos-app-bundle-writer-dry-run.sh

printf 'macos_local_candidate_asset_probe: ok\n'
