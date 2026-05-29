#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra proof object 3 higgs causal closure no go: %s\n' "$1" >&2
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

doc='docs/LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO.md'
status='docs/status/LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO_STATUS.md'
proof_object_2='docs/LATTICRA_PROOF_OBJECT_2_HIGGS_COUNTERPLAY.md'
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
workflow='.github/workflows/latticra-proof-object-3-higgs-causal-closure-no-go.yml'

for file in "$doc" "$status" "$proof_object_2" "$foundation" "$math_physics" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_proof_object_3_higgs_causal_closure_no_go_present=1' "$file"
  require_contains 'proof_object_id=latticra-proof-object-3-higgs-causal-closure-no-go' "$file"
  require_contains 'proof_object_version=1' "$file"
  require_contains 'claim_under_test=higgs-only-final-origin-of-mass' "$file"
  require_contains 'higgs_existence_denied=0' "$file"
  require_contains 'higgs_effective_mechanism_denied=0' "$file"
  require_contains 'higgs_final_causal_closure_refuted=1' "$file"
  require_contains 'free_parameter_mass_origin_rejected=1' "$file"
  require_contains 'underdetermined_yukawa_pattern_objection=1' "$file"
  require_contains 'vacuum_scale_origin_objection=1' "$file"
  require_contains 'mass_hierarchy_origin_objection=1' "$file"
  require_contains 'substrate_derivation_standard_required=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_proof_object_3_higgs_causal_closure_no_go: ok' "$file"
done

for section in '## Causal Closure Standard' '## Higgs Mass Map' '## Lemma 1: Mapping Is Not Origin' '## Lemma 2: Higgs Alone Leaves The Yukawa Ledger Open' '## Lemma 3: Higgs Alone Leaves The Vacuum Ledger Open' '## Lemma 4: Free-Parameter Explanations Are Non-Unique' '## Theorem: Higgs-Only Final Origin Is Refuted' '## Latticra Checkmate' '## Original Latticra Claim' '## Falsifier Conditions'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'm_f = y_f v / sqrt(2)' \
  'm_W = g v / 2' \
  "m_Z = sqrt(g^2 + g'^2) v / 2" \
  'm_H^2 = 2 lambda v^2' \
  'Mapping Is Not Origin' \
  'why `theta_i`?' \
  'the Higgs mechanism alone leaves the Yukawa mass pattern undetermined' \
  'This is not a historical accusation.' \
  'It is also not a claim of theft, plagiarism, priority violation, suppressed credit, or historical dependence' \
  'Higgs alone is the final first-principles origin of mass is refuted' \
  'If Higgs is effective, Latticra is allowed to search beneath it.' \
  'm_i / m_j = DeriveRatio(T, Omega, G, O, topology, impedance)' \
  'mass is substrate impedance under identity replay.' \
  'I_L(P) = limsup_N (1 / N) sum Cost_T(P_n -> P_{n+1} | Omega)' \
  'higgs_parameters_derived_by_established_theory_without_new_substrate'
do
  require_contains "$pattern" "$doc"
done

require_contains 'Proof Object 3' "$proof_object_2"
require_contains 'Proof Object 3' "$foundation"
require_contains 'Proof Object 3' "$math_physics"
require_contains 'LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO_STATUS.md' "$status_index"
require_contains 'Proof Object 3: Higgs Causal Closure No-Go' "$docs_hub"
require_contains 'Proof Object 3](docs/LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO.md)' "$root_readme"
require_contains 'Proof Object 3](../LATTICRA_PROOF_OBJECT_3_HIGGS_CAUSAL_CLOSURE_NO_GO.md)' "$status_index"
require_contains 'Proof Object 3' "$handbook"
require_contains 'Latest Latticra proof object 3 Higgs causal closure no-go note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra proof object 3 Higgs causal closure no-go note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra proof object 3 Higgs causal closure no-go note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra proof object 3 Higgs causal closure no-go note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Latticra substrate impedance mass-ratio derivation.' "$current_status"
require_contains 'Latticra substrate impedance mass-ratio derivation.' "$current_direction"
require_contains 'Latticra substrate impedance mass-ratio derivation.' "$upcoming_work"
require_contains 'latticra-proof-object-3-higgs-causal-closure-no-go:' "$makefile"
require_contains 'sh ./scripts/test-latticra-proof-object-3-higgs-causal-closure-no-go.sh' "$makefile"
require_contains 'latticra-proof-object-3-higgs-causal-closure-no-go:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-proof-object-3-higgs-causal-closure-no-go.sh' "$quality_guard"
require_contains 'Run Latticra proof object 3 Higgs causal closure no-go guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-proof-object-3-higgs-causal-closure-no-go.sh' "$workflow"

printf 'latticra_proof_object_3_higgs_causal_closure_no_go: ok\n'
