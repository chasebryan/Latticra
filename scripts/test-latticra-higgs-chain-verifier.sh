#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra higgs chain verifier: %s\n' "$1" >&2
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

doc='docs/LATTICRA_HIGGS_CHALLENGE_ONE_PAGE.md'
status='docs/status/LATTICRA_HIGGS_CHALLENGE_ONE_PAGE_STATUS.md'
verifier='scripts/verify-latticra-higgs-chain.sh'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-higgs-chain-verifier.yml'

for file in "$doc" "$status" "$verifier" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_higgs_challenge_one_page_present=1' "$file"
  require_contains 'higgs_chain_verifier_present=1' "$file"
  require_contains 'single_command_reproduction_present=1' "$file"
  require_contains 'verifier_command=make verify-higgs-chain' "$file"
  require_contains 'current_best_failure=Model-3 rejection analysis' "$file"
  require_contains 'model3_prediction_law_rejected=1' "$file"
  require_contains 'required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'refined_model3_preregistration_present=1' "$file"
  require_contains 'refined_model3_prediction_runner_authorized=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
done

for pattern in \
  'make verify-higgs-chain' \
  'latticra_higgs_chain_verifier: ok' \
  'Latticra challenges Higgs-as-final-causal-closure, not Higgs-as-effective-physics.' \
  'Current candidates fail openly'
do
  require_contains "$pattern" "$doc"
done

for pattern in \
  'scripts/test-latticra-proof-object-2-higgs-counterplay.sh' \
  'scripts/test-latticra-proof-object-3-higgs-causal-closure-no-go.sh' \
  'scripts/test-latticra-proof-object-4-identity-replay-impedance.sh' \
  'scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh' \
  'scripts/test-latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.sh' \
  'scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh' \
  'scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh' \
  'scripts/test-latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.sh' \
  'scripts/test-latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.sh' \
  'scripts/test-latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.sh' \
  'scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh' \
  'scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh' \
  'scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh' \
  'scripts/test-latticra-identity-replay-model2-prediction-runner.sh' \
  'scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh' \
  'scripts/test-latticra-identity-replay-model3-topological-amplification-preregistration.sh' \
  'scripts/test-latticra-identity-replay-model3-prediction-runner.sh' \
  'scripts/test-latticra-identity-replay-model3-rejection-analysis.sh' \
  'scripts/test-latticra-identity-replay-model3-refined-preregistration.sh' \
  'scripts/test-latticra-identity-replay-model3-failure-visual-suite.sh'
do
  require_contains "$pattern" "$verifier"
done

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-higgs-chain-verifier.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
sh "$verifier" > "$tmp_dir/verifier.out"
require_contains 'latticra_higgs_chain_verifier: ok' "$tmp_dir/verifier.out"
require_contains 'verify_higgs_chain:model3_rejection_analysis: ok' "$tmp_dir/verifier.out"
require_contains 'verify_higgs_chain:refined_model3_preregistration: ok' "$tmp_dir/verifier.out"
require_contains 'verify_higgs_chain:model3_failure_visual_suite: ok' "$tmp_dir/verifier.out"

require_contains 'LATTICRA_HIGGS_CHALLENGE_ONE_PAGE_STATUS.md' "$status_index"
require_contains 'Higgs Challenge One Page' "$docs_hub"
require_contains 'Higgs Challenge One Page](docs/LATTICRA_HIGGS_CHALLENGE_ONE_PAGE.md)' "$root_readme"
require_contains 'Latest Latticra Higgs challenge one-page verifier note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra Higgs challenge one-page verifier note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra Higgs challenge one-page verifier note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra Higgs challenge one-page verifier note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'verify-higgs-chain:' "$makefile"
require_contains 'sh ./scripts/verify-latticra-higgs-chain.sh' "$makefile"
require_contains 'latticra-higgs-chain-verifier:' "$makefile"
require_contains 'sh ./scripts/test-latticra-higgs-chain-verifier.sh' "$makefile"
require_contains 'verify-higgs-chain:' "$quality_guard"
require_contains 'latticra-higgs-chain-verifier:' "$quality_guard"
require_contains 'Run Latticra Higgs chain verifier guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"

printf 'latticra_higgs_chain_verifier_guard: ok\n'
