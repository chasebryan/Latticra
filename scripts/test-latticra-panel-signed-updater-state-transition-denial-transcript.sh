#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater state transition denial transcript: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state transition denial transcript: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state transition denial transcript: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater state transition denial transcript: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_TRANSCRIPT.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_TRANSCRIPT_STATUS.md'
script='scripts/latticra-panel-signed-updater-state-transition-denial-transcript.sh'
fixture='fixtures/latticra-panel/signed-updater-state.fixture.toml'
state_validation_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION.md'
state_validation_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION_STATUS.md'
state_validation_script='scripts/latticra-panel-signed-updater-state-fixture-validation.sh'
state_validation_test='scripts/test-latticra-panel-signed-updater-state-fixture-validation.sh'
state_contract_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT.md'
state_contract_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT_STATUS.md'
state_contract_script='scripts/latticra-panel-signed-updater-state-fixture-contract.sh'
state_contract_test='scripts/test-latticra-panel-signed-updater-state-fixture-contract.sh'
manifest_validation_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION.md'
manifest_validation_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION_STATUS.md'
manifest_validation_script='scripts/latticra-panel-signed-updater-manifest-fixture-validation.sh'
manifest_validation_test='scripts/test-latticra-panel-signed-updater-manifest-fixture-validation.sh'
manifest_contract_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT.md'
manifest_contract_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT_STATUS.md'
manifest_contract_script='scripts/latticra-panel-signed-updater-manifest-fixture-contract.sh'
manifest_contract_test='scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh'
denial_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT.md'
denial_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT_STATUS.md'
denial_script='scripts/latticra-panel-signed-updater-denial-transcript.sh'
denial_test='scripts/test-latticra-panel-signed-updater-denial-transcript.sh'
gate_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE.md'
gate_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md'
gate_script='scripts/latticra-panel-signed-updater-delivery-gate.sh'
gate_test='scripts/test-latticra-panel-signed-updater-delivery-gate.sh'
self_update='docs/SELF_UPDATE_MODEL.md'
index='docs/status/README.md'
makefile='Makefile'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$doc" \
  "$status" \
  "$script" \
  "$fixture" \
  "$state_validation_doc" \
  "$state_validation_status" \
  "$state_validation_script" \
  "$state_validation_test" \
  "$state_contract_doc" \
  "$state_contract_status" \
  "$state_contract_script" \
  "$state_contract_test" \
  "$manifest_validation_doc" \
  "$manifest_validation_status" \
  "$manifest_validation_script" \
  "$manifest_validation_test" \
  "$manifest_contract_doc" \
  "$manifest_contract_status" \
  "$manifest_contract_script" \
  "$manifest_contract_test" \
  "$denial_doc" \
  "$denial_status" \
  "$denial_script" \
  "$denial_test" \
  "$gate_doc" \
  "$gate_status" \
  "$gate_script" \
  "$gate_test" \
  "$self_update" \
  "$index" \
  "$makefile" \
  "$workflow"
do
  require_file "$file"
done

require_contains 'Status: no-effect signed updater state transition denial transcript' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-state-transition-denial-transcript.sh' "$doc"
require_contains 'signed_updater_state_transition_denial_transcript_present=1' "$doc"
require_contains 'signed_updater_state_transition_denial_transcript_stdout_only=1' "$doc"
require_contains 'signed_updater_state_transition_denial_transcript_file_write_enabled=0' "$doc"
require_contains 'signed_updater_state_transition_denial_decision=deny-state-transition' "$doc"
require_contains 'signed_updater_state_transition_denial_reason=missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation' "$doc"
require_contains 'state_transition_execution_allowed=0' "$doc"
require_contains 'state_transition_execution_performed=0' "$doc"
require_contains 'transcript_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'not update-state evidence' "$doc"

require_contains 'Status: no-effect signed updater state transition denial transcript status' "$status"
require_contains 'latticra_panel_signed_updater_state_transition_denial_transcript_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_transition_denial_transcript_guard_present=1' "$status"
require_contains 'signed_updater_state_fixture_validation_present=1' "$status"
require_contains 'signed_updater_state_transition_denial_transcript_present=1' "$status"
require_contains 'signed_updater_state_transition_denial_transcript_state=recorded-no-effect' "$status"
require_contains 'signed_updater_state_transition_denial_transcript_stdout_only=1' "$status"
require_contains 'signed_updater_state_transition_denial_transcript_file_write_enabled=0' "$status"
require_contains 'signed_updater_state_transition_denial_decision=deny-state-transition' "$status"
require_contains 'current_update_state=blocked' "$status"
require_contains 'state_transition_execution_allowed=0' "$status"
require_contains 'state_transition_execution_performed=0' "$status"
require_contains 'state_receipt_written=0' "$status"
require_contains 'transcript_write_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER STATE TRANSITION DENIAL TRANSCRIPT' "$script"
require_contains 'signed_updater_state_transition_denial_transcript_status=ok' "$script"
require_contains 'signed_updater_state_transition_denial_transcript_state=recorded-no-effect' "$script"
require_contains 'signed_updater_state_transition_denial_decision=deny-state-transition' "$script"
require_contains 'state_transition_execution_allowed=0' "$script"
require_contains 'state_transition_execution_performed=0' "$script"
require_contains 'transcript_write_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_TRANSCRIPT_STATUS.md' "$index"
require_contains 'signed updater state transition denial transcript status' "$index"

require_contains 'signed_updater_state_transition_denial_transcript_present=1' "$self_update"
require_contains 'signed_updater_state_transition_denial_decision=deny-state-transition' "$self_update"
require_contains 'signed_updater_state_transition_denial_transcript_file_write_enabled=0' "$self_update"
require_contains 'local signed updater state transition denial transcript' "$self_update"

require_contains 'Panel signed-updater state transition denial disposition closeout' "$state_validation_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$state_validation_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$state_contract_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$state_contract_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_validation_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_validation_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_contract_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_contract_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$gate_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$denial_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$state_validation_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$state_validation_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$state_contract_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$state_contract_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_validation_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_validation_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_contract_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_contract_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$denial_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$denial_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$gate_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$gate_test"

require_contains 'latticra-panel-signed-updater-state-transition-denial-transcript:' "$makefile"
require_contains 'sh ./scripts/test-latticra-panel-signed-updater-state-transition-denial-transcript.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_TRANSCRIPT.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_TRANSCRIPT_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-state-transition-denial-transcript.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-state-transition-denial-transcript.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater state transition denial transcript' "$workflow"

sh -n "$script"
sh -n "$0"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER STATE TRANSITION DENIAL TRANSCRIPT'
require_output_contains "$output" 'signed_updater_state_transition_denial_transcript_status=ok'
require_output_contains "$output" 'signed_updater_state_fixture_validation_present=1'
require_output_contains "$output" 'signed_updater_state_fixture_validated=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_transcript_present=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_transcript_state=recorded-no-effect'
require_output_contains "$output" 'signed_updater_state_transition_denial_transcript_stdout_only=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_transcript_file_write_enabled=0'
require_output_contains "$output" 'signed_updater_state_transition_denial_decision=deny-state-transition'
require_output_contains "$output" 'signed_updater_state_transition_denial_reason=missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation'
require_output_contains "$output" 'current_update_state=blocked'
require_output_contains "$output" 'requested_update_state=blocked'
require_output_contains "$output" 'state_transition_decision=deny-transition'
require_output_contains "$output" 'state_transition_execution_allowed=0'
require_output_contains "$output" 'state_transition_execution_performed=0'
require_output_contains "$output" 'state_receipt_written=0'
require_output_contains "$output" 'staged_state_materialized=0'
require_output_contains "$output" 'applied_state_materialized=0'
require_output_contains "$output" 'rollback_execution_allowed=0'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'network_fetch_attempted=0'
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'signed_update_apply_performed=0'
require_output_contains "$output" 'transcript_write_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout'

sh scripts/test-latticra-panel-signed-updater-state-fixture-validation.sh

printf 'latticra_panel_signed_updater_state_transition_denial_transcript: ok\n'
