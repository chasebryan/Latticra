#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra proof object 2 higgs counterplay: %s\n' "$1" >&2
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

doc='docs/LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY.md'
status='docs/status/LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY_STATUS.md'
proof_object_1='docs/LATTICRA_PROOF_OBJECT_1_EMERGENT_PARTICLE_MASS.md'
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
workflow='.github/workflows/latticra-proof-object-2-higgs-counterplay.yml'

for file in "$doc" "$status" "$proof_object_1" "$foundation" "$math_physics" "$speculum" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_proof_object_2_higgs_counterplay_present=1' "$file"
  require_contains 'proof_object_id=latticra-proof-object-2-higgs-counterplay' "$file"
  require_contains 'proof_object_version=1' "$file"
  require_contains 'claim_under_test=higgs-as-final-causal-origin-of-mass' "$file"
  require_contains 'higgs_existence_denied=0' "$file"
  require_contains 'higgs_effective_mechanism_denied=0' "$file"
  require_contains 'higgs_primitive_necessity_refuted=1' "$file"
  require_contains 'higgs_exhaustive_mass_origin_refuted=1' "$file"
  require_contains 'higgs_final_causality_refuted=1' "$file"
  require_contains 'substrate_impedance_theory_present=1' "$file"
  require_contains 'mass_as_replay_stable_identity_cost=1' "$file"
  require_contains 'mass_without_primitive_higgs_countermodel_required=1' "$file"
  require_contains 'substrate_spectral_gap_required=1' "$file"
  require_contains 'emergent_higgs_order_parameter_allowed=1' "$file"
  require_contains 'standard_model_reproduction_required=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_proof_object_2_higgs_counterplay: ok' "$file"
done

for section in '## Target Claim' '## Latticra Counterplay Principle' '## Countermodel Schema' '## Lemma 1: Primitive Higgs Necessity Is False By Counterexample' '## Lemma 2: Higgs Is Not Exhaustive For Observable Mass' '## Lemma 3: Higgs Leaves A Causal Ledger Unpaid' '## Lemma 4: Higgs Can Be Emergent Rather Than Primitive' '## Theorem: Higgs Is Counterplayed, Not Denied' '## Latticra Replacement Program' '## Counterplay Predictions' '## Falsifier Conditions'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'mass is the replay-stable cost for a localized pattern to remain self-identical under update, projection, and interaction.' \
  'I_L(P) = limsup_N (1 / N) sum_{n=0}^{N-1} Cost_T(P_n -> P_{n+1} | Omega)' \
  'm_L(P) = I_L(P) / c_*^2' \
  'L = (V, E, A, T, Omega, G, O, K)' \
  'm a = -log(lambda_1 / lambda_0)' \
  'm > 0' \
  'One counterexample is sufficient to refute necessity.' \
  'Higgs leaves a causal ledger open' \
  'Phi(x) = O_phi(s restricted to N(x))' \
  'V(Phi) = -mu^2 |Phi|^2 + lambda |Phi|^4' \
  'higgs_boson_mass_near_125_GeV' \
  'mass_ratios should reduce to substrate impedance ratios' \
  'This is not a priority dispute and not an accusation.' \
  'It is also not a claim of theft, plagiarism, priority violation, suppressed credit, or historical dependence' \
  'wrong_higgs_coupling_scaling' \
  'no_substrate_impedance_ledger' \
  'identity_cost_fails_to_correlate_with_mass' \
  'photon_acquires_forbidden_mass' \
  'https://doi.org/10.1103/PhysRevLett.13.508' \
  'https://home.cern/science/physics/higgs-boson/how/' \
  'https://doi.org/10.1103/PhysRevD.10.2445' \
  'https://www.energy.gov/science/np/articles/scientists-locate-missing-mass-inside-proton'
do
  require_contains "$pattern" "$doc"
done

require_contains 'Proof Object 2' "$proof_object_1"
require_contains 'Proof Object 2' "$foundation"
require_contains 'Proof Object 2' "$math_physics"
require_contains 'Proof Object 2' "$speculum"
require_contains 'LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY_STATUS.md' "$status_index"
require_contains 'Proof Object 2: Higgs Counterplay' "$docs_hub"
require_contains 'Proof Object 2](docs/LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY.md)' "$root_readme"
require_contains 'Proof Object 2](../LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY.md)' "$status_index"
require_contains 'Proof Object 2' "$handbook"
require_contains 'Latest Latticra proof object 2 Higgs counterplay note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra proof object 2 Higgs counterplay note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra proof object 2 Higgs counterplay note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra proof object 2 Higgs counterplay note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Measured Latticra electroweak-substrate candidate L0 specification.' "$current_status"
require_contains 'Measured Latticra electroweak-substrate candidate L0 specification.' "$current_direction"
require_contains 'Measured Latticra electroweak-substrate candidate L0 specification.' "$upcoming_work"
require_contains 'latticra-proof-object-2-higgs-counterplay:' "$makefile"
require_contains 'sh ./scripts/test-latticra-proof-object-2-higgs-counterplay.sh' "$makefile"
require_contains 'latticra-proof-object-2-higgs-counterplay:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-proof-object-2-higgs-counterplay.sh' "$quality_guard"
require_contains 'Run Latticra proof object 2 Higgs counterplay guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-proof-object-2-higgs-counterplay.sh' "$workflow"

printf 'latticra_proof_object_2_higgs_counterplay: ok\n'
