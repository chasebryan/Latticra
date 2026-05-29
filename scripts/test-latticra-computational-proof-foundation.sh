#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra computational proof foundation: %s\n' "$1" >&2
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

doc='docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md'
status='docs/status/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
handbook='docs/latticra-system-substrate/README.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-computational-proof-foundation.yml'

for file in "$doc" "$status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_computational_proof_foundation_present=1' "$file"
  require_contains 'computational_proof_foundation_version=1' "$file"
  require_contains 'science_framing=computer-science-and-physics-modeling' "$file"
  require_contains 'research_domain=simulation-bound-reality-research' "$file"
  require_contains 'hypothesis_state=research-hypothesis' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'testability_required=1' "$file"
  require_contains 'falsifiability_required=1' "$file"
  require_contains 'proof_object_schema_required=1' "$file"
  require_contains 'observer_boundary_required=1' "$file"
  require_contains 'state_transition_model_required=1' "$file"
  require_contains 'physical_law_constraint_model_required=1' "$file"
  require_contains 'measurement_protocol_required=1' "$file"
  require_contains 'reproducibility_required=1' "$file"
  require_contains 'adversarial_review_required=1' "$file"
  require_contains 'evidence_chain_required=1' "$file"
  require_contains 'cryptographic_receipts_required=1' "$file"
  require_contains 'runtime_substrate_mapping_required=1' "$file"
  require_contains 'lat_lir_model_mapping_required=1' "$file"
  require_contains 'visual_theorem_engine_mapping_required=1' "$file"
  require_contains 'proof_object_accepted=0' "$file"
  require_contains 'claim_promoted=0' "$file"
  require_contains 'proof_chain_complete=0' "$file"
  require_contains 'runtime_execution_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed_by_proof_lane=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'physics_measurement_performed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'operating_system_completeness_claim=0' "$file"
  require_contains 'Computational math and physics evaluation contract.' "$file"
  require_contains 'latticra_computational_proof_foundation: ok' "$file"
done

for field in proof_object_id claim_under_test hypothesis_class observable_boundary observer_model state_model transition_model constraint_model measurement_protocol input_dataset_reference execution_or_derivation_reference receipt_reference falsifier_conditions replay_requirements review_decision non_claims
do
  require_contains "$field" "$doc"
done

require_contains 'LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION_STATUS.md' "$status_index"
require_contains 'Computational Proof Foundation' "$docs_hub"
require_contains 'computational proof foundation](docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md)' "$root_readme"
require_contains 'computational-proof foundation](../LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md)' "$status_index"
require_contains 'computational proof foundation' "$handbook"
require_contains 'Latest Latticra computational proof foundation note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra computational proof foundation note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra computational proof foundation note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra computational proof foundation note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Computational proof object schema contract.' "$current_status"
require_contains 'Computational proof object schema contract.' "$current_direction"
require_contains 'Computational proof object schema contract.' "$upcoming_work"
require_contains 'latticra-computational-proof-foundation:' "$makefile"
require_contains 'sh ./scripts/test-latticra-computational-proof-foundation.sh' "$makefile"
require_contains 'latticra-computational-proof-foundation:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-computational-proof-foundation.sh' "$quality_guard"
require_contains 'Run Latticra computational proof foundation guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-computational-proof-foundation.sh' "$workflow"

printf 'latticra_computational_proof_foundation: ok\n'
