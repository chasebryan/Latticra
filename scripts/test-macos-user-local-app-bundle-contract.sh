#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos user-local app bundle contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos user-local app bundle contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md'
status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
dry_doc='docs/MACOS_DRY_RUN_PLAN_ADAPTER.md'
dry_status='docs/status/MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md'
probe_status='docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$dry_doc"
require_file "$dry_status"
require_file "$probe_status"

require_contains 'Status: macOS user-local app bundle contract' "$doc"
require_contains '$HOME/Applications/Latticra Panel.app/' "$doc"
require_contains 'Contents/Info.plist' "$doc"
require_contains 'Contents/MacOS/latticra-panel' "$doc"
require_contains 'Contents/Resources/latticra-panel.icns' "$doc"
require_contains 'Contents/Resources/latticra/MANAGED_BY_LATTICRA' "$doc"
require_contains 'Contents/Resources/latticra/bundle-manifest.txt' "$doc"
require_contains 'CFBundleIdentifier=systems.latticra.panel' "$doc"
require_contains '$HOME/Library/Application Support/Latticra/' "$doc"
require_contains 'installer-config.toml' "$doc"
require_contains 'macos-plan.txt' "$doc"
require_contains 'payload-manifest.txt' "$doc"
require_contains 'LATTICRA_INSTALLER_MANAGED=1' "$doc"
require_contains 'LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1' "$doc"
require_contains '$HOME/.local/bin/latticra-panel' "$doc"
require_contains 'receipt_kind=macos-user-local-app-bundle-install' "$doc"
require_contains 'reset_receipts_dir=$HOME/Library/Application Support/Latticra Reset Receipts' "$doc"
require_contains 'preserved_unmanaged_target=1' "$doc"
require_contains 'ok: app bundle -> $HOME/Applications/Latticra Panel.app' "$doc"
require_contains 'ok: unsafe path blocked' "$doc"
require_contains 'macos_app_bundle_writer_present=0' "$doc"
require_contains 'macos_app_bundle_created=0' "$doc"
require_contains 'macos_install_verified=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'no-effect macOS app bundle writer dry-run prototype' "$doc"

require_contains 'Status: app bundle contract status' "$status"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$status"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$status"
require_contains 'macos_app_bundle_exact_files_recorded=1' "$status"
require_contains 'macos_info_plist_requirements_recorded=1' "$status"
require_contains 'macos_application_support_files_recorded=1' "$status"
require_contains 'macos_cli_wrapper_markers_recorded=1' "$status"
require_contains 'macos_reset_uninstall_contract_recorded=1' "$status"
require_contains 'macos_verification_transcript_requirements_recorded=1' "$status"
require_contains 'macos_app_bundle_writer_present=0' "$status"
require_contains 'macos_app_bundle_created=0' "$status"
require_contains 'macos_install_verified=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md' "$index"
require_contains 'macOS user-local app bundle contract status' "$index"
require_contains 'stage_3_user_local_app_bundle_contract=present' "$transfer_plan"
require_contains 'stage_3_user_local_app_bundle=future' "$transfer_plan"
require_contains 'docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md' "$transfer_plan"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$transfer_status"
require_contains 'macOS user-local app bundle implementation plan' "$dry_doc"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$dry_status"
require_contains 'macos_user_local_app_bundle_contract_present=1' "$probe_status"
require_contains 'macos_user_local_app_bundle_implementation_plan_present=1' "$status"

printf 'macos_user_local_app_bundle_contract: ok\n'
