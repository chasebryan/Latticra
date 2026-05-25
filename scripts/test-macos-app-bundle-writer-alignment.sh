#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos app bundle writer alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos app bundle writer alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md'
status='docs/status/MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
writer_doc='docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md'
writer_status='docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md'
implementation_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md'
contract_status='docs/status/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md'
workflow='.github/workflows/macos-app-bundle-writer-alignment.yml'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$writer_doc"
require_file "$writer_status"
require_file "$implementation_status"
require_file "$contract_status"
require_file "$workflow"

require_contains 'Status: macOS app bundle writer contract/status alignment' "$doc"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$doc"
require_contains 'macos_app_bundle_writer_commit_disabled=1' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'macos_app_bundle_writer_present=0' "$doc"
require_contains 'macos_app_bundle_commit_capable_writer_present=0' "$doc"
require_contains 'macos_app_bundle_created=0' "$doc"
require_contains 'macos_install_verified=0' "$doc"
require_contains 'macos_local_candidate_asset_probe_present=1' "$doc"
require_contains 'local_panel_executable_candidate_probe=1' "$doc"
require_contains 'local_icon_candidate_probe=1' "$doc"
require_contains 'commit_gate_contract=1' "$doc"
require_contains 'Latticra has a no-effect macOS app bundle writer dry-run prototype' "$doc"
require_contains 'must not be shortened to "Latticra has a macOS app bundle writer"' "$doc"
require_contains 'The macOS local candidate asset probe remains a no-effect readiness check' "$doc"
require_contains 'Add a macOS commit gate contract' "$doc"
require_contains 'not macOS installation' "$doc"

require_contains 'Status: writer alignment status' "$status"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$status"
require_contains 'macos_local_candidate_asset_probe_present=1' "$status"
require_contains 'macos_dry_run_writer_public_meaning_recorded=1' "$status"
require_contains 'macos_commit_capable_writer_nonclaim_recorded=1' "$status"
require_contains 'macos_future_commit_gate_requirements_recorded=1' "$status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$status"
require_contains 'macos_app_bundle_writer_commit_disabled=1' "$status"
require_contains 'macos_app_bundle_writer_present=0' "$status"
require_contains 'macos_app_bundle_commit_capable_writer_present=0' "$status"
require_contains 'commit_user_local_managed_artifacts=0' "$status"
require_contains 'macos_app_bundle_created=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"

require_contains 'MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md' "$index"
require_contains 'macOS app bundle writer alignment status' "$index"
require_contains 'stage_3_user_local_app_bundle_writer_alignment=present' "$transfer_plan"
require_contains 'stage_3_user_local_app_bundle=future' "$transfer_plan"
require_contains 'docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md' "$transfer_plan"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$transfer_status"
require_contains 'The macOS local candidate asset probe is the no-effect readiness check' "$writer_doc"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$writer_status"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$implementation_status"
require_contains 'macos_app_bundle_writer_alignment_present=1' "$contract_status"
require_contains 'sh scripts/test-macos-app-bundle-writer-alignment.sh' "$workflow"

printf 'macos_app_bundle_writer_alignment: ok\n'
