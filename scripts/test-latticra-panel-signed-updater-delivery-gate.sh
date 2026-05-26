#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater delivery gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater delivery gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater delivery gate: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md'
script='scripts/latticra-panel-signed-updater-delivery-gate.sh'
index='docs/status/README.md'
self_update='docs/SELF_UPDATE_MODEL.md'
apply='installer/scripts/latticra-installer-apply.sh'
verify='installer/scripts/latticra-installer-verify.sh'
updater_test='scripts/test-latticra-panel-updater.sh'
workflow='.github/workflows/latticra-panel-installer.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$index"
require_file "$self_update"
require_file "$apply"
require_file "$verify"
require_file "$updater_test"
require_file "$workflow"

require_contains 'Status: no-effect signed updater delivery gate' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-delivery-gate.sh' "$doc"
require_contains 'signed_updater_delivery_gate_state=closed' "$doc"
require_contains 'signed_update_delivery_ready=0' "$doc"
require_contains 'network_self_update_ready=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'blocked-missing-signed-manifest-artifact-verification-and-rollback-evidence' "$doc"
require_contains 'signed_manifest_present=0' "$doc"
require_contains 'manifest_signature_verified=0' "$doc"
require_contains 'artifact_hash_verified=0' "$doc"
require_contains 'artifact_signature_verified=0' "$doc"
require_contains 'rollback_plan_present=0' "$doc"
require_contains 'operator_confirmation_observed=0' "$doc"
require_contains 'remote_update_repository_trust=0' "$doc"
require_contains 'network_fetch_authority=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'root_authority=0' "$doc"
require_contains 'not a signed updater' "$doc"

require_contains 'Status: no-effect signed updater delivery gate status' "$status"
require_contains 'latticra_panel_signed_updater_delivery_gate_present=1' "$status"
require_contains 'latticra_panel_signed_updater_delivery_gate_guard_present=1' "$status"
require_contains 'latticra_panel_updater_present=1' "$status"
require_contains 'updater_current_source_strategy=current-source-checkout' "$status"
require_contains 'updater_current_apply_mode=guarded-local-prefix-reinstall' "$status"
require_contains 'signed_updater_delivery_gate_state=closed' "$status"
require_contains 'signed_update_delivery_ready=0' "$status"
require_contains 'network_self_update_ready=0' "$status"
require_contains 'remote_update_repository_trust=0' "$status"
require_contains 'network_fetch_authority=0' "$status"
require_contains 'signed_manifest_required=1' "$status"
require_contains 'signed_manifest_present=0' "$status"
require_contains 'manifest_signature_verified=0' "$status"
require_contains 'artifact_hash_verified=0' "$status"
require_contains 'artifact_signature_verified=0' "$status"
require_contains 'rollback_plan_required=1' "$status"
require_contains 'rollback_plan_present=0' "$status"
require_contains 'operator_confirmation_required=1' "$status"
require_contains 'operator_confirmation_observed=0' "$status"
require_contains 'signed_update_apply_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"
require_contains 'not signed update evidence' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER DELIVERY GATE' "$script"
require_contains 'signed_updater_delivery_gate_status=ok' "$script"
require_contains 'signed_updater_delivery_gate_state=closed' "$script"
require_contains 'signed_manifest_present=0' "$script"
require_contains 'manifest_signature_verified=0' "$script"
require_contains 'artifact_signature_verified=0' "$script"
require_contains 'rollback_plan_present=0' "$script"
require_contains 'operator_confirmation_observed=0' "$script"
require_contains 'signed_update_apply_allowed=0' "$script"
require_contains 'next_lane=panel-signed-updater-denial-transcript' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md' "$index"
require_contains 'closed signed updater delivery gate' "$index"

require_contains 'Panel-owned local-checkout updater policy is active' "$self_update"
require_contains 'signed_updater_delivery_gate_state=closed' "$self_update"
require_contains 'signed_update_delivery_ready=0' "$self_update"
require_contains 'network_self_update_ready=0' "$self_update"

require_contains 'signed_delivery_gate = "closed"' "$apply"
require_contains 'signed_manifest_required = true' "$apply"
require_contains 'signed_manifest_present = false' "$apply"
require_contains 'signed_update_apply_allowed = false' "$apply"
require_contains 'signed_update_delivery_ready = false' "$apply"
require_contains 'signed_delivery_gate=closed' "$apply"
require_contains 'signed_manifest_present=0' "$apply"
require_contains 'signed_update_apply_allowed=0' "$apply"

require_contains 'updater signed delivery gate closed' "$verify"
require_contains 'updater status signed delivery gate closed' "$verify"
require_contains 'updater status signed delivery not ready' "$verify"

require_contains 'signed_delivery_gate=closed' "$updater_test"
require_contains 'updater_signed_delivery_gate=closed' "$updater_test"
require_contains 'updater_signed_manifest_present=false' "$updater_test"

require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-delivery-gate.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater delivery gate' "$workflow"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER DELIVERY GATE'
require_output_contains "$output" 'signed_updater_delivery_gate_status=ok'
require_output_contains "$output" 'latticra_panel_updater_present=1'
require_output_contains "$output" 'signed_updater_delivery_gate_present=1'
require_output_contains "$output" 'signed_updater_delivery_gate_state=closed'
require_output_contains "$output" 'signed_update_delivery_ready=0'
require_output_contains "$output" 'network_self_update_ready=0'
require_output_contains "$output" 'remote_update_repository_trust=0'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'signed_manifest_required=1'
require_output_contains "$output" 'signed_manifest_present=0'
require_output_contains "$output" 'manifest_signature_verified=0'
require_output_contains "$output" 'artifact_hash_verified=0'
require_output_contains "$output" 'artifact_signature_verified=0'
require_output_contains "$output" 'rollback_plan_required=1'
require_output_contains "$output" 'rollback_plan_present=0'
require_output_contains "$output" 'operator_confirmation_required=1'
require_output_contains "$output" 'operator_confirmation_observed=0'
require_output_contains "$output" 'update_receipt_written=0'
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'root_authority=0'
require_output_contains "$output" 'production_update_ready=0'

printf 'latticra_panel_signed_updater_delivery_gate: ok\n'
