#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra effect contract schema: %s\n' "$1" >&2
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

doc='docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md'
status='docs/status/LATTICRA_EFFECT_CONTRACT_SCHEMA_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-effect-contract-schema.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_effect_contract_schema_present=1' "$file"
  require_contains 'effect_contract_schema_version=1' "$file"
  require_contains 'effect_evidence_record_contract_present=1' "$file"
  require_contains 'effect_evidence_record_schema_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'effect_status_surface_reference=docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md' "$file"
  require_contains 'allowed_initial_effect_classes=none,read' "$file"
  require_contains 'blocked_effect_classes=local_mutation,host_mutation,network,hardware,boot,recovery,external,unknown' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'build_profile_promotion_accepted=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'effect_contract_schema_intake_satisfied=1' "$file"
  require_contains 'effect_evidence_record_contract_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_contract_intake_satisfied=0' "$file"
  require_contains 'build_profile_boundary_intake_satisfied=0' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=0' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'latticra_effect_contract_schema: ok' "$file"
done

for field in contract_id contract_version contract_subject request_family requested_effect allowed_effect effect_scope effect_target source_identity source_revision operator_intent authority_reference allowlist_reference build_profile model1_bridge_mode evidence_record_required non_claims
do
  require_contains "$field" "$doc"
done

for field in evidence_record_id trace_id request_hash decision_timestamp decision_result denial_reason pre_execution_boundary post_execution_result stdout_digest stderr_digest artifact_digest redaction_status secret_capture_performed network_performed host_mutation_performed
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'effect_contract_schema_intake_satisfied=1' "$file"
  require_contains 'effect_evidence_record_contract_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_contract_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'build_profile_boundary_intake_satisfied=1' "$file"
  require_contains 'build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_runner_review_boundary_intake_satisfied=1' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'separate_build_platform_review_boundary_intake_satisfied=1' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
done

require_contains 'LATTICRA_EFFECT_CONTRACT_SCHEMA_STATUS.md' "$status_index"
require_contains 'Effect Contract Schema' "$docs_hub"
require_contains 'effect contract schema](docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md)' "$root_readme"
require_contains 'Latest Latticra effect contract schema note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra effect contract schema note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra effect contract schema note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra effect contract schema note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$current_status"
require_contains 'latticra-effect-contract-schema:' "$makefile"
require_contains 'sh ./scripts/test-latticra-effect-contract-schema.sh' "$makefile"
require_contains 'latticra-effect-contract-schema:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-effect-contract-schema.sh' "$quality_guard"
require_contains 'Run Latticra effect contract schema guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-latticra-effect-contract-schema.sh' "$workflow"

printf 'latticra_effect_contract_schema: ok\n'
