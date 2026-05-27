#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos dry-run writer candidate integration: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos dry-run writer candidate integration: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos dry-run writer candidate integration: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md'
status='docs/status/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION_STATUS.md'
script='scripts/macos-dry-run-writer-candidate-integration.sh'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
probe_doc='docs/MACOS_LOCAL_CANDIDATE_ASSET_PROBE.md'
probe_status='docs/status/MACOS_LOCAL_CANDIDATE_ASSET_PROBE_STATUS.md'
writer_doc='docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md'
writer_status='docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md'
alignment_doc='docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md'
alignment_status='docs/status/MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md'
commit_gate_doc='docs/MACOS_COMMIT_GATE_CONTRACT.md'
commit_gate_status='docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md'
verification_status='docs/status/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md'
workflow='.github/workflows/macos-dry-run-writer-candidate-integration.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$probe_doc"
require_file "$probe_status"
require_file "$writer_doc"
require_file "$writer_status"
require_file "$alignment_doc"
require_file "$alignment_status"
require_file "$commit_gate_doc"
require_file "$commit_gate_status"
require_file "$verification_status"
require_file "$workflow"
require_file installer/latticra-installer/assets/latticra-panel.png

require_contains 'Status: no-effect macOS dry-run writer candidate integration' "$doc"
require_contains 'sh scripts/macos-dry-run-writer-candidate-integration.sh' "$doc"
require_contains 'asset_probe_decision=ready-for-dry-run-writer-inputs' "$doc"
require_contains 'writer_dry_run_decision=ready-for-future-commit-gate' "$doc"
require_contains 'integration_decision=ready-for-future-commit-gate-no-effect' "$doc"
require_contains 'blocked-asset-probe-not-ready' "$doc"
require_contains 'commit_user_local_managed_artifacts=0' "$doc"
require_contains 'app_bundle_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macOS commit gate contract' "$doc"
require_contains 'macOS verification transcript contract' "$doc"

require_contains 'Status: no-effect dry-run writer candidate integration status' "$status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$status"
require_contains 'macos_dry_run_writer_candidate_integration_guard_present=1' "$status"
require_contains 'macos_commit_gate_contract_present=1' "$status"
require_contains 'macos_verification_transcript_contract_present=1' "$status"
require_contains 'macos_local_candidate_asset_probe_present=1' "$status"
require_contains 'macos_app_bundle_writer_dry_run_present=1' "$status"
require_contains 'asset_probe_to_writer_candidate_flow_recorded=1' "$status"
require_contains 'asset_probe_ready_decision_required=1' "$status"
require_contains 'writer_ready_decision_required=1' "$status"
require_contains 'authority_boundary_preserved_required=1' "$status"
require_contains 'commit_user_local_managed_artifacts=0' "$status"
require_contains 'app_bundle_write_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS install evidence' "$status"

require_contains 'MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION_STATUS.md' "$index"
require_contains 'macOS dry-run writer candidate integration status' "$index"
require_contains 'stage_3_dry_run_writer_candidate_integration=present' "$transfer_plan"
require_contains 'stage_3_macos_commit_gate_contract=present' "$transfer_plan"
require_contains 'stage_4_user_local_verification_transcript_contract=present' "$transfer_plan"
require_contains 'docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md' "$transfer_plan"
require_contains 'docs/MACOS_COMMIT_GATE_CONTRACT.md' "$transfer_plan"
require_contains 'docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md' "$transfer_plan"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$transfer_status"
require_contains 'macos_commit_gate_contract_present=1' "$transfer_status"
require_contains 'macos_verification_transcript_contract_present=1' "$transfer_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$probe_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$writer_status"
require_contains 'macos_dry_run_writer_candidate_integration_present=1' "$alignment_status"
require_contains 'macos_commit_gate_contract_present=1' "$commit_gate_status"
require_contains 'macos_verification_transcript_contract_present=1' "$verification_status"
require_contains 'macOS dry-run writer candidate integration' "$probe_doc"
require_contains 'macOS dry-run writer candidate integration' "$writer_doc"
require_contains 'macOS dry-run writer candidate integration' "$alignment_doc"
require_contains 'macOS commit gate contract' "$commit_gate_doc"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$doc"
require_contains 'sh scripts/test-macos-dry-run-writer-candidate-integration.sh' "$workflow"

require_contains 'MACOS DRY RUN WRITER CANDIDATE INTEGRATION' "$script"
require_contains 'asset_probe_decision=$ASSET_DECISION' "$script"
require_contains 'writer_dry_run_decision=$WRITER_DECISION' "$script"
require_contains 'integration_decision=$INTEGRATION_DECISION' "$script"
require_contains 'commit_user_local_managed_artifacts=$COMMIT_FLAG' "$script"
require_contains 'app_bundle_write_performed=$APP_BUNDLE_WRITE' "$script"
require_contains 'host_mutation_performed=$HOST_MUTATION' "$script"
require_contains 'network_performed=$NETWORK' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract' "$script"

test_home=$(mktemp -d)
trap 'rm -rf "$test_home"' EXIT INT HUP TERM

missing_output=$(HOME="$test_home" sh "$script")
require_output_contains "$missing_output" 'MACOS DRY RUN WRITER CANDIDATE INTEGRATION'
require_output_contains "$missing_output" 'integration_status=ok'
require_output_contains "$missing_output" 'asset_probe_decision=blocked-missing-panel-executable-candidate'
require_output_contains "$missing_output" 'writer_dry_run_decision=blocked-missing-panel-executable'
require_output_contains "$missing_output" 'integration_decision=blocked-asset-probe-not-ready'
require_output_contains "$missing_output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$missing_output" 'app_bundle_write_performed=0'
require_output_contains "$missing_output" 'host_mutation_performed=0'
require_output_contains "$missing_output" 'network_performed=0'

ready_output=$(HOME="$test_home" sh "$script" --panel-executable /bin/sh --icon installer/latticra-installer/assets/latticra-panel.png)
require_output_contains "$ready_output" 'asset_probe_decision=ready-for-dry-run-writer-inputs'
require_output_contains "$ready_output" 'writer_dry_run_decision=ready-for-future-commit-gate'
require_output_contains "$ready_output" 'writer_phase_5_status=ok'
require_output_contains "$ready_output" 'asset_probe_ready=1'
require_output_contains "$ready_output" 'writer_dry_run_ready=1'
require_output_contains "$ready_output" 'authority_boundary_preserved=1'
require_output_contains "$ready_output" 'candidate_flow_ready=1'
require_output_contains "$ready_output" 'integration_decision=ready-for-future-commit-gate-no-effect'
require_output_contains "$ready_output" 'commit_user_local_managed_artifacts=0'
require_output_contains "$ready_output" 'copy_performed=0'
require_output_contains "$ready_output" 'signing_performed=0'
require_output_contains "$ready_output" 'notarization_performed=0'

blocked_probe_output=$(HOME="$test_home" sh "$script" --panel-executable /bin/sh --icon scripts/macos-app-bundle-writer-dry-run.sh)
require_output_contains "$blocked_probe_output" 'asset_probe_decision=blocked-unsupported-icon-candidate'
require_output_contains "$blocked_probe_output" 'writer_dry_run_decision=ready-for-future-commit-gate'
require_output_contains "$blocked_probe_output" 'integration_decision=blocked-asset-probe-not-ready'
require_output_contains "$blocked_probe_output" 'candidate_flow_ready=0'
require_output_contains "$blocked_probe_output" 'commit_user_local_managed_artifacts=0'

sh scripts/test-macos-local-candidate-asset-probe.sh
sh scripts/test-macos-app-bundle-writer-dry-run.sh

printf 'macos_dry_run_writer_candidate_integration: ok\n'
