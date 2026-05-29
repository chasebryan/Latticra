#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra model1 bridge protocol contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing pattern in $file: $pattern"
}

doc='docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md'
status='docs/status/LATTICRA_MODEL1_BRIDGE_PROTOCOL_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
separate_build_doc='docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md'
separate_build_status='docs/status/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-model1-bridge-protocol-contract.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$separate_build_doc" "$separate_build_status" "$status_index" "$docs_hub" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_model1_bridge_protocol_contract_present=1' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md' "$file"
  require_contains 'effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'allowed_initial_transports=stdio-json-lines,local-pipe' "$file"
  require_contains 'blocked_initial_transports=network-socket,ffi-shared-memory,unrestricted-shell,host-service,production-daemon' "$file"
  require_contains 'bridge_message_format_required=1' "$file"
  require_contains 'trace_correlation_required=1' "$file"
  require_contains 'authority_handoff_required=1' "$file"
  require_contains 'target_evidence_fields_required=1' "$file"
  require_contains 'denial_behavior_required=1' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'latticra_model1_bridge_protocol_contract: ok' "$file"
done

for field in bridge_protocol_id bridge_protocol_version message_id trace_id contract_id source_revision request_family requested_effect allowed_effect authority_decision_reference allowlist_reference build_profile_reference operator_workflow_reference target_identity target_mode transport_mode payload_digest evidence_record_required non_claims
do
  require_contains "$field" "$doc"
done

for field in target_revision target_decision target_denial_reason target_evidence_id target_observation_digest target_effect_performed target_command_execution_performed target_file_mutation_performed target_network_performed target_runtime_authority_granted redaction_status
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'model1_import_accepted=0' "$file"
done

require_contains 'Model-1 import and mixed-build review boundary.' "$separate_build_doc"
require_contains 'Model-1 import and mixed-build review boundary.' "$separate_build_status"
require_contains 'LATTICRA_MODEL1_BRIDGE_PROTOCOL_STATUS.md' "$status_index"
require_contains 'Model-1 Bridge Protocol Contract' "$docs_hub"
require_contains 'Latest Latticra Model-1 bridge protocol contract note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra Model-1 bridge protocol contract note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra Model-1 bridge protocol contract note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra Model-1 bridge protocol contract note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$current_status"
require_contains 'Model-1 import and mixed-build review boundary.' "$upcoming_work"
require_contains 'latticra-model1-bridge-protocol-contract:' "$makefile"
require_contains 'sh ./scripts/test-latticra-model1-bridge-protocol-contract.sh' "$makefile"
require_contains 'latticra-model1-bridge-protocol-contract:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-model1-bridge-protocol-contract.sh' "$quality_guard"
require_contains 'Run Latticra Model-1 bridge protocol contract guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-model1-bridge-protocol-contract.sh' "$workflow"

printf 'latticra_model1_bridge_protocol_contract: ok\n'
