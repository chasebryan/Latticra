#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra proof object 1 emergent particle mass: %s\n' "$1" >&2
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

doc='docs/LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS.md'
status='docs/status/LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS_STATUS.md'
foundation='docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md'
math_physics='docs/LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION.md'
speculum='docs/LATTICRA_SPECULUM_PREMISE.md'
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
workflow='.github/workflows/latticra-proof-object-1-emergent-particle-mass.yml'

for file in "$doc" "$status" "$foundation" "$math_physics" "$speculum" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_proof_object_1_emergent_particle_mass_present=1' "$file"
  require_contains 'proof_object_id=latticra-proof-object-1-emergent-particle-mass' "$file"
  require_contains 'proof_object_version=1' "$file"
  require_contains 'claim_under_test=particles-as-derived-substrate-excitations' "$file"
  require_contains 'particle_primitive_claim_rejected=1' "$file"
  require_contains 'mass_as_spectral_invariant_claimed=1' "$file"
  require_contains 'substrate_model_required=1' "$file"
  require_contains 'stable_vacuum_required=1' "$file"
  require_contains 'local_transition_rule_required=1' "$file"
  require_contains 'symmetry_structure_required=1' "$file"
  require_contains 'observer_projection_required=1' "$file"
  require_contains 'isolated_excitation_sector_required=1' "$file"
  require_contains 'falsifier_conditions_required=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'measured_candidate_L0_present=0' "$file"
  require_contains 'standard_model_spectrum_fit_performed=0' "$file"
  require_contains 'lorentz_bound_fit_performed=0' "$file"
  require_contains 'scattering_fit_performed=0' "$file"
  require_contains 'cosmological_observable_fit_performed=0' "$file"
  require_contains 'simulation_reality_corollary_closed=0' "$file"
  require_contains 'latticra_proof_object_1_emergent_particle_mass: ok' "$file"
done

for section in '## Definitions' '## Derived Particle Definition' '## Mass Definition' '## Lemma 1: Identity From Invariance' '## Lemma 2: Worldline From Persistence' '## Lemma 3: Mass From Spectral Gap' '## Theorem: No Primitive Particle Requirement' '## Corollary: Simulation-Bound Reality Becomes A Physics Program' '## Falsifier Conditions' '## Relationship To Established Physics'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'L = (V, E, A, T, Omega, G, O, H)' \
  'p = [delta s] under G' \
  'm_p c_*^2 = Delta E_p' \
  'm_p a = -log(lambda_1 / lambda_0)' \
  'Primitive particles are not required.' \
  'wrong_dispersion_relation' \
  'lorentz_violation_above_observed_bounds' \
  'failure_to_outperform_standard_model_baselines' \
  'https://doi.org/10.2307/1968551' \
  'https://doi.org/10.1103/PhysRevLett.13.508' \
  'https://doi.org/10.1103/PhysRevD.10.2445' \
  'https://arxiv.org/abs/1405.1548'
do
  require_contains "$pattern" "$doc"
done

require_contains 'Proof Object 1' "$foundation"
require_contains 'Proof Object 1' "$math_physics"
require_contains 'Proof Object 1' "$speculum"
require_contains 'LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS_STATUS.md' "$status_index"
require_contains 'Proof Object 1: Emergent Particles and Mass' "$docs_hub"
require_contains 'Proof Object 1](docs/LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS.md)' "$root_readme"
require_contains 'Proof Object 1](../LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS.md)' "$status_index"
require_contains 'Proof Object 1' "$handbook"
require_contains 'Latest Latticra proof object 1 emergent particle mass note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra proof object 1 emergent particle mass note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra proof object 1 emergent particle mass note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra proof object 1 emergent particle mass note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Measured Latticra candidate L0 specification.' "$current_status"
require_contains 'Measured Latticra candidate L0 specification.' "$current_direction"
require_contains 'Measured Latticra candidate L0 specification.' "$upcoming_work"
require_contains 'latticra-proof-object-1-emergent-particle-mass:' "$makefile"
require_contains 'sh ./scripts/test-latticra-proof-object-1-emergent-particle-mass.sh' "$makefile"
require_contains 'latticra-proof-object-1-emergent-particle-mass:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-proof-object-1-emergent-particle-mass.sh' "$quality_guard"
require_contains 'Run Latticra proof object 1 emergent particle mass guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-proof-object-1-emergent-particle-mass.sh' "$workflow"

printf 'latticra_proof_object_1_emergent_particle_mass: ok\n'
