#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos user-local app bundle implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos user-local app bundle implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN.md'
status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
contract_doc='docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md'
contract_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md'
dry_status='docs/status/MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md'
probe_status='docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$contract_doc"
require_file "$contract_status"
require_file "$dry_status"
require_file "$probe_status"

require_contains 'Status: no-effect macOS user-local app bundle implementation plan' "$doc"
require_contains 'macos_build_platform_probe_present=1' "$doc"
require_contains 'macos_dry_run_plan_adapter_present=1' "$doc"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$doc"
require_contains 'phase_1=validate_macos_host_and_toolchain_probe' "$doc"
require_contains 'phase_2=validate_user_local_paths_and_contract' "$doc"
require_contains 'phase_3=inspect_existing_targets_for_managed_markers' "$doc"
require_contains 'phase_8=commit_user_local_managed_artifacts' "$doc"
require_contains 'phase_10=run_verification_transcript' "$doc"
require_contains 'phase_report_only=1' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'unsafe_path_detected -> block_before_write' "$doc"
require_contains 'unmanaged_existing_app_bundle -> preserve_and_block' "$doc"
require_contains 'missing_panel_executable -> block_before_write' "$doc"
require_contains 'sudo' "$doc"
require_contains 'network_download' "$doc"
require_contains 'reset_phase_1=validate_user_local_targets' "$doc"
require_contains 'reset_phase_8=emit_verification_absence_report' "$doc"
require_contains 'default dry-run phase rendering' "$doc"
require_contains 'unsafe path blocked before write' "$doc"
require_contains 'unmanaged app bundle preserved' "$doc"
require_contains 'macos_app_bundle_writer_present=0' "$doc"
require_contains 'macos_app_bundle_writer_dry_run_present=0' "$doc"
require_contains 'macos_app_bundle_created=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'no-effect macOS app bundle writer dry-run prototype' "$doc"

require_contains 'Status: implementation plan status' "$status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$status"
require_contains 'macos_writer_phase_plan_recorded=1' "$status"
require_contains 'macos_writer_failure_behavior_recorded=1' "$status"
require_contains 'macos_reset_uninstall_sequence_recorded=1' "$status"
require_contains 'macos_writer_verification_commands_recorded=1' "$status"
require_contains 'macos_future_writer_guard_tests_recorded=1' "$status"
require_contains 'macos_app_bundle_writer_present=0' "$status"
require_contains 'macos_app_bundle_writer_dry_run_present=0' "$status"
require_contains 'macos_app_bundle_created=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md' "$index"
require_contains 'macOS user-local app bundle implementation plan status' "$index"
require_contains 'stage_3_user_local_app_bundle_implementation_plan=present' "$transfer_plan"
require_contains 'stage_3_user_local_app_bundle=future' "$transfer_plan"
require_contains 'docs/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN.md' "$transfer_plan"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$transfer_status"
require_contains 'no-effect macOS app bundle writer dry-run prototype' "$contract_doc"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$contract_status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$dry_status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$probe_status"

printf 'macos_user_local_app_bundle_implementation_plan: ok\n'
