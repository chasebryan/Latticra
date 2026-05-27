#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater state fixture validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state fixture validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state fixture validation: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater state fixture validation: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

fixture='fixtures/latticra-panel/signed-updater-state.fixture.toml'
doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION_STATUS.md'
script='scripts/latticra-panel-signed-updater-state-fixture-validation.sh'
contract_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT.md'
contract_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT_STATUS.md'
contract_script='scripts/latticra-panel-signed-updater-state-fixture-contract.sh'
contract_test='scripts/test-latticra-panel-signed-updater-state-fixture-contract.sh'
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
  "$fixture" \
  "$doc" \
  "$status" \
  "$script" \
  "$contract_doc" \
  "$contract_status" \
  "$contract_script" \
  "$contract_test" \
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

require_contains 'state_schema = "latticra-panel-signed-updater-state-fixture-v0"' "$fixture"
require_contains 'state_fixture = true' "$fixture"
require_contains 'state_fixture_scope = "local-no-effect"' "$fixture"
require_contains 'state_fixture_effect = "none"' "$fixture"
require_contains 'state_fixture_trusted_for_apply = false' "$fixture"
require_contains 'state_catalog = [' "$fixture"
require_contains '  "available",' "$fixture"
require_contains '  "downloaded",' "$fixture"
require_contains '  "verified",' "$fixture"
require_contains '  "staged",' "$fixture"
require_contains '  "armed",' "$fixture"
require_contains '  "applied",' "$fixture"
require_contains '  "rolled_back",' "$fixture"
require_contains '  "failed",' "$fixture"
require_contains '  "blocked",' "$fixture"
require_contains 'current_update_state = "blocked"' "$fixture"
require_contains 'requested_update_state = "blocked"' "$fixture"
require_contains 'state_transition_decision = "deny-transition"' "$fixture"
require_contains 'state_transition_execution_allowed = false' "$fixture"
require_contains 'state_transition_execution_performed = false' "$fixture"
require_contains 'state_receipt_written = false' "$fixture"
require_contains 'staged_state_materialized = false' "$fixture"
require_contains 'armed_state_materialized = false' "$fixture"
require_contains 'applied_state_materialized = false' "$fixture"
require_contains 'blocked_state_recorded = true' "$fixture"
require_contains 'rollback_execution_allowed = false' "$fixture"
require_contains 'signed_update_apply_allowed = false' "$fixture"
require_contains 'update_activation_allowed = false' "$fixture"
require_contains 'host_mutation_allowed = false' "$fixture"
require_contains 'not-state-transition-execution' "$fixture"

require_contains 'Status: local no-effect signed updater state fixture validation' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-state-fixture-validation.sh' "$doc"
require_contains 'fixtures/latticra-panel/signed-updater-state.fixture.toml' "$doc"
require_contains 'signed_updater_state_fixture_validation_present=1' "$doc"
require_contains 'signed_updater_state_fixture_validated=1' "$doc"
require_contains 'signed_updater_state_fixture_validation_scope=shape-state-catalog-and-closed-transition-fields' "$doc"
require_contains 'state_catalog_validated=1' "$doc"
require_contains 'blocked_state_validated=1' "$doc"
require_contains 'closed_transition_fields_validated=1' "$doc"
require_contains 'signed_updater_state_fixture_valid_for_transition=0' "$doc"
require_contains 'signed_updater_state_fixture_valid_for_apply=0' "$doc"
require_contains 'state_transition_execution_allowed=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'latticra_panel_signed_updater_state_fixture_validation: ok' "$doc"

require_contains 'Status: local no-effect signed updater state fixture validation status' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_validation_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_validation_guard_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_contract_present=1' "$status"
require_contains 'state_fixture_path=fixtures/latticra-panel/signed-updater-state.fixture.toml' "$status"
require_contains 'signed_updater_state_fixture_validated=1' "$status"
require_contains 'state_schema_validated=1' "$status"
require_contains 'state_catalog_validated=1' "$status"
require_contains 'blocked_state_validated=1' "$status"
require_contains 'closed_transition_fields_validated=1' "$status"
require_contains 'state_fixture_trusted_for_apply=0' "$status"
require_contains 'signed_updater_state_fixture_valid_for_transition=0' "$status"
require_contains 'state_transition_execution_allowed=0' "$status"
require_contains 'state_transition_execution_performed=0' "$status"
require_contains 'signed_update_apply_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER STATE FIXTURE VALIDATION' "$script"
require_contains 'require_fixture_line' "$script"
require_contains 'signed_updater_state_fixture_validation_status=ok' "$script"
require_contains 'state_fixture_path=$FIXTURE_RELATIVE' "$script"
require_contains 'signed_updater_state_fixture_validation_present=1' "$script"
require_contains 'signed_updater_state_fixture_validated=1' "$script"
require_contains 'state_schema_validated=1' "$script"
require_contains 'state_catalog_validated=1' "$script"
require_contains 'blocked_state_validated=1' "$script"
require_contains 'closed_transition_fields_validated=1' "$script"
require_contains 'state_fixture_trusted_for_apply=0' "$script"
require_contains 'state_transition_execution_allowed=0' "$script"
require_contains 'signed_update_apply_allowed=0' "$script"
require_contains 'network_fetch_attempted=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION_STATUS.md' "$index"
require_contains 'signed updater state fixture validation status' "$index"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$contract_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$contract_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_validation_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_validation_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_contract_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$manifest_contract_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$gate_status"
require_contains 'Panel signed-updater state transition denial disposition closeout' "$denial_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$contract_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$contract_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_validation_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_validation_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_contract_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$manifest_contract_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$denial_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$denial_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$gate_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout' "$gate_test"

require_contains 'signed_updater_state_fixture_validation_present=1' "$self_update"
require_contains 'signed_updater_state_fixture_validated=1' "$self_update"
require_contains 'signed_updater_state_fixture_valid_for_transition=0' "$self_update"
require_contains 'signed_updater_state_fixture_valid_for_apply=0' "$self_update"
require_contains 'local signed updater state fixture validation' "$self_update"

require_contains 'latticra-panel-signed-updater-state-fixture-validation:' "$makefile"
require_contains 'sh ./scripts/test-latticra-panel-signed-updater-state-fixture-validation.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_VALIDATION_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-state-fixture-validation.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-state-fixture-validation.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater state fixture validation' "$workflow"

sh -n "$script"
sh -n "$0"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER STATE FIXTURE VALIDATION'
require_output_contains "$output" 'signed_updater_state_fixture_validation_status=ok'
require_output_contains "$output" 'state_fixture_path=fixtures/latticra-panel/signed-updater-state.fixture.toml'
require_output_contains "$output" 'signed_updater_state_fixture_validation_present=1'
require_output_contains "$output" 'signed_updater_state_fixture_validated=1'
require_output_contains "$output" 'state_schema_validated=1'
require_output_contains "$output" 'state_catalog_validated=1'
require_output_contains "$output" 'blocked_state_validated=1'
require_output_contains "$output" 'closed_transition_fields_validated=1'
require_output_contains "$output" 'state_fixture_trusted_for_apply=0'
require_output_contains "$output" 'signed_updater_state_fixture_valid_for_transition=0'
require_output_contains "$output" 'signed_updater_state_fixture_valid_for_apply=0'
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
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout'

sh scripts/test-latticra-panel-signed-updater-state-fixture-contract.sh

printf 'latticra_panel_signed_updater_state_fixture_validation: ok\n'
