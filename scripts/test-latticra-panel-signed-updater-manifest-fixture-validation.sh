#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater manifest fixture validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater manifest fixture validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater manifest fixture validation: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater manifest fixture validation: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

fixture='fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION_STATUS.md'
script='scripts/latticra-panel-signed-updater-manifest-fixture-validation.sh'
contract_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT.md'
contract_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_CONTRACT_STATUS.md'
contract_test='scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh'
delivery_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DELIVERY_GATE_STATUS.md'
denial_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_DENIAL_TRANSCRIPT_STATUS.md'
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
  "$contract_test" \
  "$delivery_status" \
  "$denial_status" \
  "$self_update" \
  "$index" \
  "$makefile" \
  "$workflow"
do
  require_file "$file"
done

require_contains 'manifest_schema = "latticra-panel-signed-updater-manifest-fixture-v0"' "$fixture"
require_contains 'manifest_fixture = true' "$fixture"
require_contains 'manifest_fixture_scope = "local-no-effect"' "$fixture"
require_contains 'manifest_fixture_effect = "none"' "$fixture"
require_contains 'manifest_fixture_trusted_for_apply = false' "$fixture"
require_contains 'source_strategy = "current-source-checkout"' "$fixture"
require_contains 'network_fetch_authority = false' "$fixture"
require_contains 'remote_update_repository_trust = false' "$fixture"
require_contains 'signed_update_delivery_ready = false' "$fixture"
require_contains 'trusted_signed_manifest_present = false' "$fixture"
require_contains 'manifest_signature_verified = false' "$fixture"
require_contains 'artifact_hash_verified = false' "$fixture"
require_contains 'artifact_signature_verified = false' "$fixture"
require_contains 'rollback_plan_present = false' "$fixture"
require_contains 'operator_confirmation_observed = false' "$fixture"
require_contains 'signed_update_apply_allowed = false' "$fixture"
require_contains 'host_mutation_allowed = false' "$fixture"
require_contains 'production_update_ready = false' "$fixture"
require_contains 'not-a-trusted-update-manifest' "$fixture"

require_contains 'Status: local no-effect signed updater manifest fixture validation' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-manifest-fixture-validation.sh' "$doc"
require_contains 'fixtures/latticra-panel/signed-updater-manifest.fixture.toml' "$doc"
require_contains 'signed_updater_manifest_fixture_validation_present=1' "$doc"
require_contains 'signed_updater_manifest_fixture_validated=1' "$doc"
require_contains 'signed_updater_manifest_fixture_validation_scope=shape-and-closed-authority-fields' "$doc"
require_contains 'manifest_fixture_trusted_for_apply=0' "$doc"
require_contains 'signed_updater_manifest_fixture_valid_for_apply=0' "$doc"
require_contains 'trusted_signed_manifest_present=0' "$doc"
require_contains 'signed_update_apply_allowed=0' "$doc"
require_contains 'network_fetch_attempted=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'latticra_panel_signed_updater_manifest_fixture_validation: ok' "$doc"

require_contains 'Status: local no-effect signed updater manifest fixture validation status' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_validation_present=1' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_validation_guard_present=1' "$status"
require_contains 'latticra_panel_signed_updater_manifest_fixture_contract_present=1' "$status"
require_contains 'manifest_fixture_path=fixtures/latticra-panel/signed-updater-manifest.fixture.toml' "$status"
require_contains 'signed_updater_manifest_fixture_validated=1' "$status"
require_contains 'manifest_schema_validated=1' "$status"
require_contains 'closed_authority_fields_validated=1' "$status"
require_contains 'manifest_fixture_trusted_for_apply=0' "$status"
require_contains 'trusted_signed_manifest_present=0' "$status"
require_contains 'signed_manifest_present=0' "$status"
require_contains 'manifest_signature_verified=0' "$status"
require_contains 'artifact_hash_verified=0' "$status"
require_contains 'artifact_signature_verified=0' "$status"
require_contains 'signed_update_apply_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE VALIDATION' "$script"
require_contains 'require_fixture_line' "$script"
require_contains 'signed_updater_manifest_fixture_validation_status=ok' "$script"
require_contains 'manifest_fixture_path=$FIXTURE_RELATIVE' "$script"
require_contains 'signed_updater_manifest_fixture_validation_present=1' "$script"
require_contains 'signed_updater_manifest_fixture_validated=1' "$script"
require_contains 'manifest_schema_validated=1' "$script"
require_contains 'closed_authority_fields_validated=1' "$script"
require_contains 'manifest_fixture_trusted_for_apply=0' "$script"
require_contains 'trusted_signed_manifest_present=0' "$script"
require_contains 'signed_update_apply_allowed=0' "$script"
require_contains 'network_fetch_attempted=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-fixture-validation' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION_STATUS.md' "$index"
require_contains 'signed updater manifest fixture validation status' "$index"
require_contains 'Panel signed-updater state fixture validation' "$contract_doc"
require_contains 'Panel signed-updater state fixture validation' "$contract_status"
require_contains 'Panel signed-updater state fixture validation' "$delivery_status"
require_contains 'Panel signed-updater state fixture validation' "$denial_status"
require_contains 'signed_updater_manifest_fixture_contract_present=1' "$self_update"
require_contains 'local signed updater manifest fixture contract' "$self_update"
require_contains 'signed_updater_manifest_fixture_validation_present=1' "$self_update"
require_contains 'signed_updater_manifest_fixture_validated=1' "$self_update"
require_contains 'signed_updater_manifest_fixture_valid_for_apply=0' "$self_update"
require_contains 'local signed updater manifest fixture validation' "$self_update"

require_contains 'sh ./scripts/test-latticra-panel-signed-updater-manifest-fixture-validation.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_MANIFEST_FIXTURE_VALIDATION_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-manifest-fixture-validation.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-manifest-fixture-validation.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater manifest fixture validation' "$workflow"

sh -n "$script"
sh -n "$0"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE VALIDATION'
require_output_contains "$output" 'signed_updater_manifest_fixture_validation_status=ok'
require_output_contains "$output" 'manifest_fixture_path=fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
require_output_contains "$output" 'signed_updater_manifest_fixture_validation_present=1'
require_output_contains "$output" 'signed_updater_manifest_fixture_validated=1'
require_output_contains "$output" 'manifest_schema_validated=1'
require_output_contains "$output" 'closed_authority_fields_validated=1'
require_output_contains "$output" 'manifest_fixture_trusted_for_apply=0'
require_output_contains "$output" 'trusted_signed_manifest_present=0'
require_output_contains "$output" 'signed_manifest_present=0'
require_output_contains "$output" 'manifest_signature_verified=0'
require_output_contains "$output" 'artifact_hash_verified=0'
require_output_contains "$output" 'artifact_signature_verified=0'
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'signed_update_apply_performed=0'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'network_fetch_attempted=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-fixture-validation'

sh scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh

printf 'latticra_panel_signed_updater_manifest_fixture_validation: ok\n'
