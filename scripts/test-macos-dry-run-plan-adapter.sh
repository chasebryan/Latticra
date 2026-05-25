#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos dry-run plan adapter: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos dry-run plan adapter: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  pattern="$1"
  if ! printf '%s\n' "$plan_output" | grep -Fq -- "$pattern"; then
    printf 'macos dry-run plan adapter: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_DRY_RUN_PLAN_ADAPTER.md'
status='docs/status/MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md'
script='scripts/macos-dry-run-plan-adapter.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
probe_doc='docs/MACOS_BUILD_PLATFORM_PROBE.md'
probe_status='docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$probe_doc"
require_file "$probe_status"

require_contains 'Status: no-effect macOS dry-run plan adapter' "$doc"
require_contains 'sh scripts/macos-dry-run-plan-adapter.sh' "$doc"
require_contains 'application_support_prefix=$HOME/Library/Application Support/Latticra' "$doc"
require_contains 'app_bundle=$HOME/Applications/Latticra Panel.app' "$doc"
require_contains 'cli_bin=$HOME/.local/bin' "$doc"
require_contains 'path_guard_status=allowed-user-local-dry-run' "$doc"
require_contains 'path_guard_status=blocked-unsafe-user-local-path' "$doc"
require_contains 'application_support_write_performed=0' "$doc"
require_contains 'app_bundle_write_performed=0' "$doc"
require_contains 'cli_wrapper_write_performed=0' "$doc"
require_contains 'shell_profile_mutation_performed=0' "$doc"
require_contains 'installer_write_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'keychain_authority=0' "$doc"
require_contains 'system_extension_authority=0' "$doc"
require_contains 'macOS user-local app bundle implementation plan' "$doc"

require_contains 'Status: no-effect dry-run plan status' "$status"
require_contains 'macos_dry_run_plan_adapter_present=1' "$status"
require_contains 'macos_dry_run_plan_script_present=1' "$status"
require_contains 'macos_dry_run_plan_guard_present=1' "$status"
require_contains 'macos_application_support_plan_present=1' "$status"
require_contains 'macos_user_local_app_bundle_plan_present=1' "$status"
require_contains 'macos_cli_wrapper_plan_present=1' "$status"
require_contains 'macos_path_guard_present=1' "$status"
require_contains 'application_support_write_performed=0' "$status"
require_contains 'app_bundle_write_performed=0' "$status"
require_contains 'cli_wrapper_write_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md' "$index"
require_contains 'macOS dry-run plan adapter status' "$index"
require_contains 'stage_2_macos_dry_run_plan=present' "$transfer_plan"
require_contains 'docs/MACOS_DRY_RUN_PLAN_ADAPTER.md' "$transfer_plan"
require_contains 'macos_dry_run_plan_adapter_present=1' "$transfer_status"
require_contains 'macOS user-local app bundle implementation plan' "$probe_doc"
require_contains 'macos_dry_run_plan_adapter_present=1' "$probe_status"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$status"

require_contains 'MACOS DRY RUN PLAN ADAPTER' "$script"
require_contains 'application_support_write_performed=0' "$script"
require_contains 'app_bundle_write_performed=0' "$script"
require_contains 'cli_wrapper_write_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'keychain_authority=0' "$script"

plan_output=$(sh "$script")
require_output_contains 'MACOS DRY RUN PLAN ADAPTER'
require_output_contains 'plan_status=ok'
require_output_contains 'plan_mode=macos-dry-run-plan'
require_output_contains 'path_guard_status=allowed-user-local-dry-run'
require_output_contains 'dry_run_allowed=1'
require_output_contains 'application_support_prefix='"$HOME"'/Library/Application Support/Latticra'
require_output_contains 'app_bundle='"$HOME"'/Applications/Latticra Panel.app'
require_output_contains 'planned_latticra_wrapper='"$HOME"'/.local/bin/latticra'
require_output_contains 'application_support_write_performed=0'
require_output_contains 'app_bundle_write_performed=0'
require_output_contains 'cli_wrapper_write_performed=0'
require_output_contains 'shell_profile_mutation_performed=0'
require_output_contains 'host_mutation_performed=0'
require_output_contains 'network_performed=0'
require_output_contains 'production_installer_ready=0'

blocked_output=$(sh "$script" --app-bundle /Applications/Latticra.app)
if ! printf '%s\n' "$blocked_output" | grep -Fq 'path_guard_status=blocked-unsafe-user-local-path'; then
  printf 'macos dry-run plan adapter: unsafe app bundle path was not blocked\n' >&2
  exit 1
fi
if ! printf '%s\n' "$blocked_output" | grep -Fq 'dry_run_allowed=0'; then
  printf 'macos dry-run plan adapter: unsafe app bundle path did not set dry_run_allowed=0\n' >&2
  exit 1
fi
if ! printf '%s\n' "$blocked_output" | grep -Fq 'app_bundle_write_performed=0'; then
  printf 'macos dry-run plan adapter: unsafe path changed app_bundle_write_performed\n' >&2
  exit 1
fi

printf 'macos_dry_run_plan_adapter: ok\n'
