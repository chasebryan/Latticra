#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra computational math physics evaluation: %s\n' "$1" >&2
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

doc='docs/LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION.md'
status='docs/status/LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION_STATUS.md'
foundation='docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md'
foundation_status='docs/status/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION_STATUS.md'
visual_doc='docs/VISUAL_THEOREM_ENGINES.md'
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
workflow='.github/workflows/latticra-computational-math-physics-evaluation.yml'

for file in "$doc" "$status" "$foundation" "$foundation_status" "$visual_doc" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_computational_math_physics_evaluation_present=1' "$file"
  require_contains 'computational_math_physics_evaluation_version=1' "$file"
  require_contains 'foundation_reference=docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md' "$file"
  require_contains 'evaluation_order=math-first-physics-second-visual-third' "$file"
  require_contains 'math_evaluation_required=1' "$file"
  require_contains 'physics_coupling_required=1' "$file"
  require_contains 'visual_demonstration_preparation_required=1' "$file"
  require_contains 'visual_engine_reference=docs/VISUAL_THEOREM_ENGINES.md' "$file"
  require_contains 'visual_engine_candidate=latt-field-engines/substrate-engine' "$file"
  require_contains 'visual_demo_rendered=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'math_model_accepted=0' "$file"
  require_contains 'math_model_review_complete=0' "$file"
  require_contains 'math_model_ready_for_physics_coupling=0' "$file"
  require_contains 'physics_coupling_accepted=0' "$file"
  require_contains 'physics_measurement_performed=0' "$file"
  require_contains 'physics_experiment_claimed=0' "$file"
  require_contains 'physical_law_constraint_claim_promoted=0' "$file"
  require_contains 'visual_demo_evidence=0' "$file"
  require_contains 'visual_demo_claim_promoted=0' "$file"
  require_contains 'visual_demo_publication_ready=0' "$file"
  require_contains 'runtime_execution_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed_by_evaluation_lane=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'visual_render_performed=0' "$file"
  require_contains 'visual_asset_published=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'operating_system_completeness_claim=0' "$file"
  require_contains 'Computational proof object schema contract.' "$file"
  require_contains 'latticra_computational_math_physics_evaluation: ok' "$file"
done

for field in state_space_definition state_variables transition_operator time_or_step_parameter constraint_invariants observer_projection measurement_mapping conservation_or_monotonicity_claims error_terms boundary_conditions initial_conditions falsifier_conditions replay_requirements review_decision
do
  require_contains "$field" "$doc"
done

for field in physical_observable unit_or_scale_reference measurement_protocol_reference observer_effect_model symmetry_or_invariance_reference constraint_law_reference noise_model_reference alternative_explanation_reference negative_result_handling falsifier_review_reference
do
  require_contains "$field" "$doc"
done

for scene in state-space-and-initial-conditions transition-operator-and-step-evolution invariant-constraint-surfaces observer-projection-and-measurement-limits physics-coupling-and-alternative-explanations falsifier-gate-and-non-claim-boundary
do
  require_contains "$scene" "$doc"
done

require_contains 'Computational math and physics evaluation contract.' "$foundation"
require_contains 'Computational math and physics evaluation contract.' "$foundation_status"
require_contains 'Computational math and physics evaluation' "$visual_doc"
require_contains 'LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION_STATUS.md' "$status_index"
require_contains 'Computational Math and Physics Evaluation' "$docs_hub"
require_contains 'computational math and physics evaluation](docs/LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION.md)' "$root_readme"
require_contains 'computational math and physics evaluation](../LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION.md)' "$status_index"
require_contains 'math and physics evaluation' "$handbook"
require_contains 'Latest Latticra computational math and physics evaluation note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra computational math and physics evaluation note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra computational math and physics evaluation note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra computational math and physics evaluation note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Computational proof object schema contract.' "$current_status"
require_contains 'Computational proof object schema contract.' "$current_direction"
require_contains 'Computational proof object schema contract.' "$upcoming_work"
require_contains 'latticra-computational-math-physics-evaluation:' "$makefile"
require_contains 'sh ./scripts/test-latticra-computational-math-physics-evaluation.sh' "$makefile"
require_contains 'latticra-computational-math-physics-evaluation:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-computational-math-physics-evaluation.sh' "$quality_guard"
require_contains 'Run Latticra computational math and physics evaluation guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-computational-math-physics-evaluation.sh' "$workflow"

printf 'latticra_computational_math_physics_evaluation: ok\n'
