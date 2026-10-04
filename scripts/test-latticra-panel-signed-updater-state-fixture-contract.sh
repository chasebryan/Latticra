#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater state fixture contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state fixture contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater state fixture contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

fixture='fixtures/latticra-panel/signed-updater-state.fixture.toml'
doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT_STATUS.md'
script='scripts/latticra-panel-signed-updater-state-fixture-contract.sh'
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
index='docs/status/README.md'
self_update='docs/SELF_UPDATE_MODEL.md'
makefile='Makefile'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$fixture" \
  "$doc" \
  "$status" \
  "$script" \
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
  "$index" \
  "$self_update" \
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
require_contains 'applied_state_materialized = false' "$fixture"
require_contains 'blocked_state_recorded = true' "$fixture"
require_contains 'rollback_execution_allowed = false' "$fixture"
require_contains 'signed_update_apply_allowed = false' "$fixture"
require_contains 'update_activation_allowed = false' "$fixture"
require_contains 'host_mutation_allowed = false' "$fixture"
require_contains 'not-state-transition-execution' "$fixture"

require_contains 'Status: local no-effect signed updater state fixture contract' "$doc"
require_contains 'fixtures/latticra-panel/signed-updater-state.fixture.toml' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-state-fixture-contract.sh' "$doc"
require_contains 'signed_updater_state_fixture_contract_present=1' "$doc"
require_contains 'current_update_state=blocked' "$doc"
require_contains 'state_transition_execution_allowed=0' "$doc"
require_contains 'state_transition_execution_performed=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'not update-state evidence' "$doc"

require_contains 'Status: local no-effect signed updater state fixture contract status' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_contract_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_guard_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_fixture_present=1' "$status"
require_contains 'state_fixture_path=fixtures/latticra-panel/signed-updater-state.fixture.toml' "$status"
require_contains 'signed_updater_state_fixture_contract_present=1' "$status"
require_contains 'signed_updater_state_fixture_present=1' "$status"
require_contains 'state_fixture_schema=latticra-panel-signed-updater-state-fixture-v0' "$status"
require_contains 'state_catalog_present=1' "$status"
require_contains 'state_blocked_declared=1' "$status"
require_contains 'current_update_state=blocked' "$status"
require_contains 'state_transition_decision=deny-transition' "$status"
require_contains 'state_transition_execution_allowed=0' "$status"
require_contains 'state_transition_execution_performed=0' "$status"
require_contains 'state_receipt_written=0' "$status"
require_contains 'staged_state_materialized=0' "$status"
require_contains 'applied_state_materialized=0' "$status"
require_contains 'rollback_execution_allowed=0' "$status"
require_contains 'signed_update_apply_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"
require_contains 'not update-state evidence' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER STATE FIXTURE CONTRACT' "$script"
require_contains 'signed_updater_state_fixture_contract_status=$CONTRACT_STATUS' "$script"
require_contains 'state_fixture_path=$(portable_path "$FIXTURE_RELATIVE")' "$script"
require_contains 'signed_updater_state_fixture_contract_present=1' "$script"
require_contains 'state_catalog_present=1' "$script"
require_contains 'current_update_state=blocked' "$script"
require_contains 'state_transition_execution_allowed=0' "$script"
require_contains 'state_transition_execution_performed=0' "$script"
require_contains 'signed_update_apply_allowed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT_STATUS.md' "$index"
require_contains 'signed updater state fixture contract status' "$index"

require_contains 'signed_updater_state_fixture_contract_present=1' "$self_update"
require_contains 'signed_updater_state_fixture_present=1' "$self_update"
require_contains 'state_transition_execution_allowed=0' "$self_update"
require_contains 'state_transition_execution_performed=0' "$self_update"
require_contains 'local signed updater state fixture contract' "$self_update"

require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$gate_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$gate_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$gate_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$gate_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$denial_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$denial_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$denial_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$denial_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$manifest_contract_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$manifest_contract_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$manifest_contract_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$manifest_contract_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$manifest_validation_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$manifest_validation_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$manifest_validation_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$manifest_validation_test"

require_contains 'sh ./scripts/test-latticra-panel-signed-updater-state-fixture-contract.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_FIXTURE_CONTRACT_STATUS.md' "$workflow"
require_contains 'fixtures/latticra-panel/signed-updater-state.fixture.toml' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-state-fixture-contract.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-state-fixture-contract.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater state fixture contract' "$workflow"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER STATE FIXTURE CONTRACT'
require_output_contains "$output" 'signed_updater_state_fixture_contract_status=ok'
require_output_contains "$output" 'signed_updater_delivery_gate_state=closed'
require_output_contains "$output" 'signed_updater_manifest_fixture_validation_present=1'
require_output_contains "$output" 'state_fixture_path=fixtures/latticra-panel/signed-updater-state.fixture.toml'
require_output_contains "$output" 'signed_updater_state_fixture_contract_present=1'
require_output_contains "$output" 'signed_updater_state_fixture_present=1'
require_output_contains "$output" 'state_fixture_schema=latticra-panel-signed-updater-state-fixture-v0'
require_output_contains "$output" 'state_catalog_present=1'
require_output_contains "$output" 'state_blocked_declared=1'
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
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'signed_update_apply_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'root_authority=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout'

sh scripts/test-latticra-panel-signed-updater-manifest-fixture-validation.sh

printf 'latticra_panel_signed_updater_state_fixture_contract: ok\n'
