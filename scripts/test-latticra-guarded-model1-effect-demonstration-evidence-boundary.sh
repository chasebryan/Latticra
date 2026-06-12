#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra guarded model1 effect demonstration evidence boundary: %s\n' "$1" >&2
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

doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md'
status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
bridge_doc='docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md'
bridge_status='docs/status/LATTICRA_MODEL1_BRIDGE_PROTOCOL_STATUS.md'
import_doc='docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md'
import_status='docs/status/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-guarded-model1-effect-demonstration-evidence-boundary.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$bridge_doc" "$bridge_status" "$import_doc" "$import_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_guarded_model1_effect_demonstration_evidence_boundary_present=1' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_evidence_boundary_guard_present=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_intake_satisfied=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md' "$file"
  require_contains 'effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_reference=docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md' "$file"
  require_contains 'review_source=prior-import-boundary-and-bridge-protocol-contract' "$file"
  require_contains 'allowed_review_modes=static-evidence-boundary-review,operator-workflow-review,redaction-review,no-effect-packet-shape-review' "$file"
  require_contains 'blocked_review_modes=model1-launch,bridge-execution,effect-dispatch,command-execution,file-mutation,artifact-import,mixed-build-promotion,production' "$file"
  require_contains 'request_contract_required=1' "$file"
  require_contains 'bridge_request_evidence_required=1' "$file"
  require_contains 'bridge_response_evidence_required=1' "$file"
  require_contains 'deny_by_default_evidence_required=1' "$file"
  require_contains 'operator_workflow_reference_required=1' "$file"
  require_contains 'target_evidence_record_required=1' "$file"
  require_contains 'redaction_review_required=1' "$file"
  require_contains 'non_claim_review_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_evidence_accepted=0' "$file"
  require_contains 'operator_demo_non_claim_review_required=1' "$file"
  require_contains 'operator_demo_non_claim_review_satisfied=0' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'effect_runner_accepted=0' "$file"
  require_contains 'runner_dispatch_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'host_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_evidence_boundary: ok' "$file"
done

for field in guarded_demo_evidence_id guarded_demo_evidence_version source_revision request_contract_reference bridge_protocol_reference model1_import_review_reference operator_workflow_reference requested_effect allowed_effect deny_by_default_decision bridge_request_message_id bridge_request_trace_id bridge_request_digest bridge_response_message_id bridge_response_trace_id bridge_response_digest target_identity target_revision target_evidence_id target_observation_digest redaction_status non_claim_review_reference acceptance_decision denial_reason
do
  require_contains "$field" "$doc"
done

for field in model1_bridge_execution_performed model1_process_launch_performed effect_execution_performed command_execution_performed file_mutation_performed network_performed host_mutation_performed runtime_authority_granted production_readiness_claim distribution_readiness_claim
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'guarded_model1_effect_demonstration_boundary_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_intake_satisfied=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md' "$file"
  require_contains 'guarded_model1_effect_demonstration_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_evidence_accepted=0' "$file"
  require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$file"
done

require_contains 'Model-1 Import and Mixed-Build Review Boundary' "$docs_hub"
require_contains 'Guarded Model-1 Effect Demonstration Evidence Boundary' "$docs_hub"
require_contains 'LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY_STATUS.md' "$status_index"
require_contains 'guarded Model-1 effect demonstration evidence boundary](docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md)' "$root_readme"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence boundary note: 2026-06-12 CDT' "$root_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence boundary note: 2026-06-12 CDT' "$current_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence boundary note: 2026-06-12 CDT' "$current_direction"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence boundary note: 2026-06-12 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$upcoming_work"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-boundary:' "$makefile"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-boundary.sh' "$makefile"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-boundary:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-boundary.sh' "$quality_guard"
require_contains 'Run Latticra guarded Model-1 effect demonstration evidence boundary guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-guarded-model1-effect-demonstration-evidence-boundary.sh' "$workflow"

printf 'latticra_guarded_model1_effect_demonstration_evidence_boundary: ok\n'
