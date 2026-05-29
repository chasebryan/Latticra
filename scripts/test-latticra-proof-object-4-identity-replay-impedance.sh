#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra proof object 4 identity replay impedance: %s\n' "$1" >&2
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

doc='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
status='docs/status/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE_STATUS.md'
proof_object_3='docs/LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO.md'
foundation='docs/LATTICRA_COMPUTATIONAL_PROOF_FOUNDATION.md'
math_physics='docs/LATTICRA_COMPUTATIONAL_MATH_PHYSICS_EVALUATION.md'
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
workflow='.github/workflows/latticra-proof-object-4-identity-replay-impedance.yml'

for file in "$doc" "$status" "$proof_object_3" "$foundation" "$math_physics" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_proof_object_4_identity_replay_impedance_present=1' "$file"
  require_contains 'proof_object_id=latticra-proof-object-4-identity-replay-impedance' "$file"
  require_contains 'proof_object_version=1' "$file"
  require_contains 'claim_under_test=mass-as-identity-replay-impedance' "$file"
  require_contains 'identity_replay_impedance_defined=1' "$file"
  require_contains 'projected_identity_class_required=1' "$file"
  require_contains 'counterfactual_repair_cost_required=1' "$file"
  require_contains 'receipt_replay_ledger_required=1' "$file"
  require_contains 'higgs_coupling_shadow_test_required=1' "$file"
  require_contains 'higgs_existence_denied=0' "$file"
  require_contains 'higgs_effective_mechanism_denied=0' "$file"
  require_contains 'higgs_final_causal_closure_refuted=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_proof_object_4_identity_replay_impedance: ok' "$file"
done

for section in '## Originality Boundary' '## Substrate Definition' '## Replay Stability' '## Counterfactual Repair Cost' '## Identity-Replay Impedance' '## Lemma 1: Zero Impedance Gives No Rest-Mass Ledger' '## Lemma 2: Positive Impedance Gives A Derived Mass Ledger' '## Lemma 3: Higgs Coupling Is Not The Ledger' '## Theorem: Mass-As-Identity-Replay Impedance' '## Coupling-Shadow Test' '## Checkmate Form' '## Falsifier Conditions'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'mass is the minimal replay-stable cost required for a localized projected identity to remain itself under substrate update.' \
  'projected identity class + replay receipt + counterfactual repair cost + mass ledger + Higgs coupling-shadow test' \
  'Originality here means Latticra'\''s own proposed formal construct, not a priority accusation.' \
  'It is also not a claim of theft, plagiarism, priority violation, suppressed credit, or historical dependence' \
  'L = (S, T, O, Q, d, kappa, R)' \
  'I = Q(O(P))' \
  'R(P, T, O, Q, N, epsilon) = receipt_hash' \
  'kappa_n(P) = inf Cost(delta_n)' \
  'Z_L(I) = limsup_N (1 / N) sum_{n=0}^{N-1} kappa_n(P)' \
  'm_L(I) = Z_L(I) / c_*^2' \
  'm_L(I_a) / m_L(I_b) = Z_L(I_a) / Z_L(I_b)' \
  'y_f v / sqrt(2) = Z_L(I_f) / c_*^2' \
  'Higgs: field coupling to vacuum expectation value.' \
  'Latticra: replay-stable identity impedance under substrate update.' \
  'counterfactual_repair_cost_not_computable' \
  'higgs_coupling_shadow_test_fails'
do
  require_contains "$pattern" "$doc"
done

require_contains 'Proof Object 4' "$proof_object_3"
require_contains 'Proof Object 4' "$foundation"
require_contains 'Proof Object 4' "$math_physics"
require_contains 'LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE_STATUS.md' "$status_index"
require_contains 'Proof Object 4: Identity-Replay Impedance' "$docs_hub"
require_contains 'Proof Object 4](docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md)' "$root_readme"
require_contains 'Proof Object 4](../LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md)' "$status_index"
require_contains 'Proof Object 4' "$handbook"
require_contains 'Latest Latticra proof object 4 identity-replay impedance note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra proof object 4 identity-replay impedance note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra proof object 4 identity-replay impedance note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra proof object 4 identity-replay impedance note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance candidate particle table.' "$current_status"
require_contains 'Identity-replay impedance candidate particle table.' "$current_direction"
require_contains 'Identity-replay impedance candidate particle table.' "$upcoming_work"
require_contains 'latticra-proof-object-4-identity-replay-impedance:' "$makefile"
require_contains 'sh ./scripts/test-latticra-proof-object-4-identity-replay-impedance.sh' "$makefile"
require_contains 'latticra-proof-object-4-identity-replay-impedance:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-proof-object-4-identity-replay-impedance.sh' "$quality_guard"
require_contains 'Run Latticra proof object 4 identity-replay impedance guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-proof-object-4-identity-replay-impedance.sh' "$workflow"

printf 'latticra_proof_object_4_identity_replay_impedance: ok\n'
