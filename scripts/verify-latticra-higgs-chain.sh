#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

run_guard() {
  label="$1"
  script="$2"
  printf 'verify_higgs_chain:%s: start\n' "$label"
  sh "$script"
  printf 'verify_higgs_chain:%s: ok\n' "$label"
}

run_guard proof_object_2 scripts/test-latticra-proof-object-2-higgs-counterplay.sh
run_guard proof_object_3 scripts/test-latticra-proof-object-3-higgs-causal-closure-no-go.sh
run_guard proof_object_4 scripts/test-latticra-proof-object-4-identity-replay-impedance.sh
run_guard particle_table scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh
run_guard l0_toy_runner scripts/test-latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.sh
run_guard l1_constrained_search scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh
run_guard l2_preregistered_holdout scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh
run_guard l3_holdout_intake scripts/test-latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.sh
run_guard l4_execution_gate scripts/test-latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.sh
run_guard l5_evidence_review scripts/test-latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.sh
run_guard model1_dynamic_substrate scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh
run_guard model1_bounded_range scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh
run_guard model2_preregistration scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh
run_guard model2_prediction scripts/test-latticra-identity-replay-model2-prediction-runner.sh
run_guard model2_failure_analysis scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh
run_guard model3_preregistration scripts/test-latticra-identity-replay-model3-topological-amplification-preregistration.sh
run_guard model3_prediction scripts/test-latticra-identity-replay-model3-prediction-runner.sh
run_guard model3_rejection_analysis scripts/test-latticra-identity-replay-model3-rejection-analysis.sh
run_guard model3_failure_visual_suite scripts/test-latticra-identity-replay-model3-failure-visual-suite.sh
run_guard refined_model3_preregistration scripts/test-latticra-identity-replay-model3-refined-preregistration.sh
printf "verify_higgs_chain:sh-portable-paths-lib: start
"
ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
. "$ROOT/scripts/lib/latticra-portable-paths.sh" 2>/dev/null || { echo "lib fail" >&2; exit 1; }
p=$(portable_path "$ROOT/README.md")
[ "$p" = "README.md" ] || { echo "portable bad" >&2; exit 1; }
printf "verify_higgs_chain:sh-portable-paths-lib: ok
"


printf 'latticra_higgs_chain_verifier: ok\n'

# portable lib test (appended for robustness)
printf 'verify_higgs_chain:sh-portable-paths-lib: start\n'
ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
. "$ROOT/scripts/lib/latticra-portable-paths.sh" 2>/dev/null || { echo 'lib source fail' >&2; exit 1; }
p=$(portable_path "$ROOT/README.md")
[ "$p" = "README.md" ] || { echo 'portable lib bad relative' >&2; exit 1; }
abs_p=$(portable_path "$ROOT/fixtures/latticra-model1-demo-evidence/valid-denied.packet")
[ "$abs_p" = "fixtures/latticra-model1-demo-evidence/valid-denied.packet" ] || { echo 'portable lib bad abs' >&2; exit 1; }
printf 'verify_higgs_chain:sh-portable-paths-lib: ok\n'
