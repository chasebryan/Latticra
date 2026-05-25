#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos app bundle writer dry-run: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos app bundle writer dry-run: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos app bundle writer dry-run: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md'
status='docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md'
script='scripts/macos-app-bundle-writer-dry-run.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
implementation_plan='docs/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN.md'
implementation_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md'
contract_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md'
dry_status='docs/status/MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md'
probe_status='docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md'
workflow='.github/workflows/macos-app-bundle-writer-dry-run.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$implementation_plan"
require_file "$implementation_status"
require_file "$contract_status"
require_file "$dry_status"
require_file "$probe_status"
require_file "$workflow"

require_contains 'Status: no-effect macOS app bundle writer dry-run prototype' "$doc"
require_contains 'sh scripts/macos-app-bundle-writer-dry-run.sh' "$doc"
require_contains 'phase_report_only=1' "$doc"
require_contains 'phase_8=commit_user_local_managed_artifacts' "$doc"
require_contains 'phase_8_status=disabled' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'path_guard_status=blocked-unsafe-user-local-path' "$doc"
require_contains 'dry_run_decision=blocked-unsafe-path' "$doc"
require_contains 'unmanaged-preserve-and-block' "$doc"
require_contains 'dry_run_decision=blocked-unmanaged-existing-target' "$doc"
require_contains 'app_bundle_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'no-effect macOS local candidate asset probe' "$doc"

require_contains 'Status: no-effect writer dry-run status' "$status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$status"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$status"
require_contains 'macos_app_bundle_writer_phase_report_present=1' "$status"
require_contains 'macos_app_bundle_writer_path_guard_present=1' "$status"
require_contains 'macos_app_bundle_writer_marker_inspection_present=1' "$status"
require_contains 'macos_app_bundle_writer_commit_disabled=1' "$status"
require_contains 'macos_app_bundle_writer_present=0' "$status"
require_contains 'commit_user_local_managed_artifacts=0' "$status"
require_contains 'macos_app_bundle_created=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md' "$index"
require_contains 'macOS app bundle writer dry-run status' "$index"
require_contains 'stage_3_user_local_app_bundle_writer_dry_run=present' "$transfer_plan"
require_contains 'stage_3_user_local_app_bundle=future' "$transfer_plan"
require_contains 'docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md' "$transfer_plan"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$transfer_status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$implementation_status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$contract_status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$dry_status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$probe_status"
require_contains 'no-effect macOS local candidate asset probe' "$implementation_plan"
require_contains 'sh scripts/test-macos-app-bundle-writer-dry-run.sh' "$workflow"

require_contains 'MACOS APP BUNDLE WRITER DRY RUN' "$script"
require_contains 'commit_user_local_managed_artifacts=0' "$script"
require_contains 'app_bundle_write_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"

default_output=$(sh "$script")
require_output_contains "$default_output" 'MACOS APP BUNDLE WRITER DRY RUN'
require_output_contains "$default_output" 'dry_run_status=ok'
require_output_contains "$default_output" 'phase_report_only=1'
require_output_contains "$default_output" 'path_guard_status=allowed-user-local-dry-run'
require_output_contains "$default_output" 'phase_8_status=disabled'
require_output_contains "$default_output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$default_output" 'dry_run_decision=blocked-missing-panel-executable'
require_output_contains "$default_output" 'app_bundle_write_performed=0'
require_output_contains "$default_output" 'host_mutation_performed=0'
require_output_contains "$default_output" 'network_performed=0'

blocked_output=$(sh "$script" --app-bundle /Applications/Latticra.app)
require_output_contains "$blocked_output" 'path_guard_status=blocked-unsafe-user-local-path'
require_output_contains "$blocked_output" 'unsafe_path_detected=1'
require_output_contains "$blocked_output" 'phase_2_status=blocked-unsafe-path'
require_output_contains "$blocked_output" 'dry_run_decision=blocked-unsafe-path'
require_output_contains "$blocked_output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$blocked_output" 'app_bundle_write_performed=0'
require_output_contains "$blocked_output" 'host_mutation_performed=0'

sh scripts/test-macos-user-local-app-bundle-contract.sh
sh scripts/test-macos-user-local-app-bundle-implementation-plan.sh

printf 'macos_app_bundle_writer_dry_run: ok\n'
