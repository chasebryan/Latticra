#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater denial transcript: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater denial transcript: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater denial transcript: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT_STATUS.md'
script='scripts/latticra-panel-signed-updater-denial-transcript.sh'
gate_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE.md'
gate_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md'
gate_script='scripts/latticra-panel-signed-updater-delivery-gate.sh'
gate_test='scripts/test-latticra-panel-signed-updater-delivery-gate.sh'
index='docs/status/README.md'
self_update='docs/SELF_UPDATE_MODEL.md'
makefile='Makefile'
workflow='.github/workflows/latticra-panel-installer.yml'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$gate_doc"
require_file "$gate_status"
require_file "$gate_script"
require_file "$gate_test"
require_file "$index"
require_file "$self_update"
require_file "$makefile"
require_file "$workflow"

require_contains 'Status: no-effect signed updater denial transcript' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-denial-transcript.sh' "$doc"
require_contains 'signed_updater_denial_decision=deny-signed-update-delivery' "$doc"
require_contains 'signed_updater_denial_reason=missing-signed-manifest-artifact-verification-and-rollback-evidence' "$doc"
require_contains 'signed_updater_denial_transcript_stdout_only=1' "$doc"
require_contains 'signed_updater_denial_transcript_file_write_enabled=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'network_fetch_attempted=0' "$doc"
require_contains 'remote_update_repository_trust=0' "$doc"
require_contains 'transcript_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'not signed update evidence' "$doc"

require_contains 'Status: no-effect signed updater denial transcript status' "$status"
require_contains 'latticra_panel_signed_updater_denial_transcript_present=1' "$status"
require_contains 'latticra_panel_signed_updater_denial_transcript_guard_present=1' "$status"
require_contains 'latticra_panel_signed_updater_delivery_gate_present=1' "$status"
require_contains 'signed_updater_delivery_gate_state=closed' "$status"
require_contains 'signed_updater_denial_transcript_state=recorded-no-effect' "$status"
require_contains 'signed_updater_denial_transcript_stdout_only=1' "$status"
require_contains 'signed_updater_denial_transcript_file_write_enabled=0' "$status"
require_contains 'signed_updater_denial_decision=deny-signed-update-delivery' "$status"
require_contains 'network_fetch_attempted=0' "$status"
require_contains 'signed_manifest_present=0' "$status"
require_contains 'manifest_signature_verified=0' "$status"
require_contains 'artifact_signature_verified=0' "$status"
require_contains 'rollback_plan_present=0' "$status"
require_contains 'operator_confirmation_observed=0' "$status"
require_contains 'update_receipt_written=0' "$status"
require_contains 'staged_update_performed=0' "$status"
require_contains 'signed_update_apply_performed=0' "$status"
require_contains 'transcript_write_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"
require_contains 'not signed update evidence' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER DENIAL TRANSCRIPT' "$script"
require_contains 'signed_updater_denial_transcript_status=ok' "$script"
require_contains 'signed_updater_denial_transcript_state=recorded-no-effect' "$script"
require_contains 'signed_updater_denial_decision=deny-signed-update-delivery' "$script"
require_contains 'network_fetch_attempted=0' "$script"
require_contains 'transcript_write_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-fixture-validation' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT_STATUS.md' "$index"
require_contains 'signed updater denial transcript' "$index"

require_contains 'signed_updater_denial_transcript_present=1' "$self_update"
require_contains 'signed_updater_denial_decision=deny-signed-update-delivery' "$self_update"
require_contains 'signed_updater_denial_transcript_file_write_enabled=0' "$self_update"

require_contains 'panel-signed-updater-state-fixture-validation' "$gate_script"
require_contains 'Panel signed-updater state fixture validation' "$gate_doc"
require_contains 'Panel signed-updater state fixture validation' "$gate_status"
require_contains 'panel-signed-updater-state-fixture-validation' "$gate_test"

require_contains 'sh ./scripts/test-latticra-panel-signed-updater-denial-transcript.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-denial-transcript.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater denial transcript' "$workflow"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER DENIAL TRANSCRIPT'
require_output_contains "$output" 'signed_updater_denial_transcript_status=ok'
require_output_contains "$output" 'signed_updater_delivery_gate_state=closed'
require_output_contains "$output" 'signed_updater_denial_transcript_present=1'
require_output_contains "$output" 'signed_updater_denial_transcript_state=recorded-no-effect'
require_output_contains "$output" 'signed_updater_denial_transcript_stdout_only=1'
require_output_contains "$output" 'signed_updater_denial_transcript_file_write_enabled=0'
require_output_contains "$output" 'signed_updater_denial_decision=deny-signed-update-delivery'
require_output_contains "$output" 'signed_updater_denial_reason=missing-signed-manifest-artifact-verification-and-rollback-evidence'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'network_fetch_attempted=0'
require_output_contains "$output" 'remote_update_repository_trust=0'
require_output_contains "$output" 'signed_manifest_present=0'
require_output_contains "$output" 'manifest_signature_verified=0'
require_output_contains "$output" 'artifact_signature_verified=0'
require_output_contains "$output" 'rollback_plan_present=0'
require_output_contains "$output" 'operator_confirmation_observed=0'
require_output_contains "$output" 'update_receipt_written=0'
require_output_contains "$output" 'staged_update_performed=0'
require_output_contains "$output" 'signed_update_apply_performed=0'
require_output_contains "$output" 'transcript_write_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'root_authority=0'
require_output_contains "$output" 'production_update_ready=0'

sh scripts/test-latticra-panel-signed-updater-delivery-gate.sh

printf 'latticra_panel_signed_updater_denial_transcript: ok\n'
