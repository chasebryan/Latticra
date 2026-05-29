#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra speculum premise: %s\n' "$1" >&2
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

doc='docs/LATTICRA_SPECULUM_PREMISE.md'
status='docs/status/LATTICRA_SPECULUM_PREMISE_STATUS.md'
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
workflow='.github/workflows/latticra-speculum-premise.yml'
foundation='docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md'

for file in "$doc" "$status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow" "$foundation"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_speculum_premise_present=1' "$file"
  require_contains 'speculum_premise_version=1' "$file"
  require_contains 'companion_name=Speculum' "$file"
  require_contains 'companion_to=simulacrum' "$file"
  require_contains 'premise_role=clarifying-mirror-for-simulation-bound-reality-research' "$file"
  require_contains 'simulation_premise_clarified=1' "$file"
  require_contains 'simulation_premise_is_hypothesis=1' "$file"
  require_contains 'simulation_literal_claim_allowed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'public_certainty_performance_allowed=0' "$file"
  require_contains 'claim_promotion_allowed=0' "$file"
  require_contains 'model_is_reality_claimed=0' "$file"
  require_contains 'representation_is_truth_claimed=0' "$file"
  require_contains 'simulation_premise_promoted_without_proof=0' "$file"
  require_contains 'physics_measurement_inferred_from_docs=0' "$file"
  require_contains 'metaphysical_claim_promoted=0' "$file"
  require_contains 'speculum_premise_accepted_as_proof=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'proof_chain_complete=0' "$file"
  require_contains 'runtime_execution_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed_by_speculum_lane=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'physics_measurement_performed=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'operating_system_completeness_claim=0' "$file"
  require_contains 'Computational proof object schema contract.' "$file"
  require_contains 'latticra_speculum_premise: ok' "$file"
done

for field in represented_state observer_frame transition_under_review constraint_model excluded_interpretations alternative_explanations falsifier_path measurement_or_derivation_reference receipt_reference replay_reference adversarial_review_reference public_non_claims
do
  require_contains "$field" "$doc"
done

require_contains 'LATTICRA_SPECULUM_PREMISE_STATUS.md' "$status_index"
require_contains 'Speculum Premise' "$docs_hub"
require_contains 'Speculum premise](docs/LATTICRA_SPECULUM_PREMISE.md)' "$root_readme"
require_contains 'Speculum premise](../LATTICRA_SPECULUM_PREMISE.md)' "$status_index"
require_contains 'Speculum premise' "$handbook"
require_contains 'Latest Latticra Speculum premise note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra Speculum premise note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra Speculum premise note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra Speculum premise note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'The Speculum premise now names the clarifying mirror beside the simulacrum' "$root_status"
require_contains 'The Speculum premise now names the clarifying mirror beside the simulacrum' "$current_status"
require_contains 'The Speculum premise now names the clarifying mirror beside the simulacrum' "$current_direction"
require_contains 'The Speculum premise now names the clarifying mirror beside the simulacrum' "$upcoming_work"
require_contains 'latticra-speculum-premise:' "$makefile"
require_contains 'sh ./scripts/test-latticra-speculum-premise.sh' "$makefile"
require_contains 'latticra-speculum-premise:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-speculum-premise.sh' "$quality_guard"
require_contains 'Run Latticra Speculum premise guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-speculum-premise.sh' "$workflow"
require_contains 'Speculum translation fields' "$foundation"

printf 'latticra_speculum_premise: ok\n'
