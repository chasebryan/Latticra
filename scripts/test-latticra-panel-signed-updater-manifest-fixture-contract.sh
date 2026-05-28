#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater manifest fixture contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater manifest fixture contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater manifest fixture contract: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

fixture='fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT_STATUS.md'
script='scripts/latticra-panel-signed-updater-manifest-fixture-contract.sh'
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

require_file "$fixture"
require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$denial_doc"
require_file "$denial_status"
require_file "$denial_script"
require_file "$denial_test"
require_file "$gate_doc"
require_file "$gate_status"
require_file "$gate_script"
require_file "$gate_test"
require_file "$index"
require_file "$self_update"
require_file "$makefile"
require_file "$workflow"

require_contains 'manifest_schema = "latticra-panel-signed-updater-manifest-fixture-v0"' "$fixture"
require_contains 'manifest_fixture = true' "$fixture"
require_contains 'manifest_fixture_scope = "local-no-effect"' "$fixture"
require_contains 'manifest_fixture_effect = "none"' "$fixture"
require_contains 'manifest_fixture_trusted_for_apply = false' "$fixture"
require_contains 'update_id = "panel-local-checkout-fixture"' "$fixture"
require_contains 'update_channel = "lab"' "$fixture"
require_contains 'source_strategy = "current-source-checkout"' "$fixture"
require_contains 'apply_mode = "guarded-local-prefix-reinstall"' "$fixture"
require_contains 'target_component = "latticra-panel"' "$fixture"
require_contains 'target_version = "fixture-only"' "$fixture"
require_contains 'network_fetch_authority = false' "$fixture"
require_contains 'remote_update_repository_trust = false' "$fixture"
require_contains 'signed_update_delivery_ready = false' "$fixture"
require_contains 'trusted_signed_manifest_present = false' "$fixture"
require_contains 'manifest_signature_verified = false' "$fixture"
require_contains 'artifact_hash_verified = false' "$fixture"
require_contains 'artifact_signature_verified = false' "$fixture"
require_contains 'rollback_plan_present = false' "$fixture"
require_contains 'operator_confirmation_observed = false' "$fixture"
require_contains 'update_receipt_written = false' "$fixture"
require_contains 'signed_update_apply_allowed = false' "$fixture"
require_contains 'host_mutation_allowed = false' "$fixture"
require_contains 'production_update_ready = false' "$fixture"
require_contains 'not-a-trusted-update-manifest' "$fixture"

require_contains 'Status: local no-effect signed updater manifest fixture contract' "$doc"
require_contains 'fixtures/latticra-panel/signed-updater-manifest.fixture.toml' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-manifest-fixture-contract.sh' "$doc"
require_contains 'signed_updater_manifest_fixture_present=1' "$doc"
require_contains 'manifest_fixture_trusted_for_apply=0' "$doc"
require_contains 'trusted_signed_manifest_present=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'network_fetch_attempted=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'not signed update evidence' "$doc"

require_contains 'Status: local no-effect signed updater manifest fixture contract status' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_contract_present=1' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_guard_present=1' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_present=1' "$status"
require_contains 'manifest_fixture_path=fixtures/latticra-panel/signed-updater-manifest.fixture.toml' "$status"
require_contains 'signed_updater_manifest_fixture_contract_present=1' "$status"
require_contains 'signed_updater_manifest_fixture_present=1' "$status"
require_contains 'trusted_signed_manifest_present=0' "$status"
require_contains 'signed_manifest_present=0' "$status"
require_contains 'manifest_signature_verified=0' "$status"
require_contains 'artifact_hash_verified=0' "$status"
require_contains 'artifact_signature_verified=0' "$status"
require_contains 'rollback_plan_present=0' "$status"
require_contains 'operator_confirmation_observed=0' "$status"
require_contains 'signed_update_apply_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"
require_contains 'not signed update evidence' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE CONTRACT' "$script"
require_contains 'signed_updater_manifest_fixture_contract_status=$CONTRACT_STATUS' "$script"
require_contains 'manifest_fixture_path=$FIXTURE_RELATIVE' "$script"
require_contains 'signed_updater_manifest_fixture_contract_present=1' "$script"
require_contains 'trusted_signed_manifest_present=0' "$script"
require_contains 'signed_manifest_present=0' "$script"
require_contains 'signed_update_apply_allowed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT_STATUS.md' "$index"
require_contains 'signed updater manifest fixture contract' "$index"

require_contains 'signed_updater_manifest_fixture_contract_present=1' "$self_update"
require_contains 'signed_updater_manifest_fixture_present=1' "$self_update"
require_contains 'manifest_fixture_trusted_for_apply=0' "$self_update"
require_contains 'trusted_signed_manifest_present=0' "$self_update"
require_contains 'local signed updater manifest fixture contract' "$self_update"

require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review' "$gate_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review' "$gate_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review' "$gate_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review' "$gate_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review' "$denial_script"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review' "$denial_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review' "$denial_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review' "$denial_test"

require_contains 'sh ./scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT_STATUS.md' "$workflow"
require_contains 'fixtures/latticra-panel/signed-updater-manifest.fixture.toml' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-manifest-fixture-contract.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater manifest fixture contract' "$workflow"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE CONTRACT'
require_output_contains "$output" 'signed_updater_manifest_fixture_contract_status=ok'
require_output_contains "$output" 'signed_updater_delivery_gate_state=closed'
require_output_contains "$output" 'signed_updater_denial_transcript_present=1'
require_output_contains "$output" 'manifest_fixture_path=fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
require_output_contains "$output" 'signed_updater_manifest_fixture_contract_present=1'
require_output_contains "$output" 'signed_updater_manifest_fixture_present=1'
require_output_contains "$output" 'manifest_fixture_schema=latticra-panel-signed-updater-manifest-fixture-v0'
require_output_contains "$output" 'manifest_fixture_effect=none'
require_output_contains "$output" 'manifest_fixture_trusted_for_apply=0'
require_output_contains "$output" 'trusted_signed_manifest_present=0'
require_output_contains "$output" 'signed_manifest_present=0'
require_output_contains "$output" 'manifest_signature_verified=0'
require_output_contains "$output" 'artifact_hash_verified=0'
require_output_contains "$output" 'artifact_signature_verified=0'
require_output_contains "$output" 'rollback_plan_present=0'
require_output_contains "$output" 'operator_confirmation_observed=0'
require_output_contains "$output" 'update_receipt_written=0'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'network_fetch_attempted=0'
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'signed_update_apply_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'root_authority=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review'

sh scripts/test-latticra-panel-signed-updater-denial-transcript.sh

printf 'latticra_panel_signed_updater_manifest_fixture_contract: ok\n'
