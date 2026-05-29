#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model2 prediction runner: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER_STATUS.md'
model2_prereg_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md'
model2_prereg_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION_STATUS.md'
model1_falsifier_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
prediction_tool='tools/latticra_identity_replay_model2_runner.py'
evaluation_tool='tools/latticra_identity_replay_model2_evaluate.py'
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
workflow='.github/workflows/latticra-identity-replay-model2-prediction-runner.yml'

for file in "$doc" "$status" "$model2_prereg_doc" "$model2_prereg_status" "$model1_falsifier_doc" "$table" "$proof_object_4" "$prediction_tool" "$evaluation_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model2_prediction_runner_present=1' "$file"
  require_contains 'prediction_runner_id=latticra-identity-replay-model2-prediction-runner' "$file"
  require_contains 'prediction_runner_version=1' "$file"
  require_contains 'prediction_law_id=model2-hierarchical-hash-seeded-scale-product-law' "$file"
  require_contains 'prediction_runner=tools/latticra_identity_replay_model2_runner.py' "$file"
  require_contains 'evaluation_tool=tools/latticra_identity_replay_model2_evaluate.py' "$file"
  require_contains 'model2_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'candidate_substrate_id=identity-replay-model2-hierarchical-substrate' "$file"
  require_contains 'prediction_mode=predict_only' "$file"
  require_contains 'target_table_loaded=0' "$file"
  require_contains 'target_comparison_performed=0' "$file"
  require_contains 'prediction_receipt_emitted_before_target_load=1' "$file"
  require_contains 'model2_prediction_receipt_hash_valid=1' "$file"
  require_contains 'prediction_input_target_table_loaded=0' "$file"
  require_contains 'prediction_input_target_comparison_performed=0' "$file"
  require_contains 'target_load_after_prediction_receipt=1' "$file"
  require_contains 'measured_masses_used_in_law=0' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'particle_features_hand_declared=0' "$file"
  require_contains 'identity_patterns_generated_from_substrate=1' "$file"
  require_contains 'model2_hierarchical_substrate_present=1' "$file"
  require_contains 'hierarchical_replay_performed=1' "$file"
  require_contains 'per_scale_kappa_traces_emitted=1' "$file"
  require_contains 'active_scale_product_cost_emitted=1' "$file"
  require_contains 'mass_ratio_predictions_emitted=1' "$file"
  require_contains 'scale_levels=4' "$file"
  require_contains 'negative_controls_present=1' "$file"
  require_contains 'photon_zero_rest_mass_control_present=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_present=1' "$file"
  require_contains 'photon_zero_rest_mass_control_survives=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_survives=1' "$file"
  require_contains 'prediction_dynamic_range=22.098461538461538461538461538461538461538461538461538461538461538461538461538462' "$file"
  require_contains 'target_dynamic_range=337691.49623497269417' "$file"
  require_contains 'prediction_dynamic_range_meets_target_range=0' "$file"
  require_contains 'parameter_count=6' "$file"
  require_contains 'target_count=7' "$file"
  require_contains 'parameter_count_less_than_target_count=1' "$file"
  require_contains 'failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top' "$file"
  require_contains 'candidate_survives_target_table=0' "$file"
  require_contains 'model2_prediction_law_rejected=1' "$file"
  require_contains 'model2_prediction_conclusion=rejected_by_target_table' "$file"
  require_contains 'hierarchy_sufficient_for_range_but_prediction_vector_failed=1' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'higgs_only_causal_closure_challenged=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'model2_prediction_receipt_hash_generated=1' "$file"
  require_contains 'model2_evaluation_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Prediction Checkpoint' '## Evaluation Conclusion' '## Current Conclusion' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model2_runner.py --predict-only' \
  'python3 tools/latticra_identity_replay_model2_evaluate.py' \
  'The first deterministic Model-2 hierarchical prediction law is rejected by the guarded target table.' \
  'Identity-replay impedance Model-2 prediction failure analysis and law refinement.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$prediction_tool"; then
  fail "$prediction_tool must not contain measured target masses or measured ratios"
fi

python3 -m py_compile "$prediction_tool" "$evaluation_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model2-prediction-runner.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/model2_prediction.json"
evaluation_json="$tmp_dir/model2_evaluation.json"

if python3 "$prediction_tool" > "$tmp_dir/no-flag.json" 2>"$tmp_dir/no-flag.err"; then
  fail "$prediction_tool must require --predict-only"
fi

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"

for pattern in \
  '"latticra_identity_replay_model2_prediction_runner_present": 1' \
  '"prediction_runner_id": "latticra-identity-replay-model2-prediction-runner"' \
  '"prediction_law_id": "model2-hierarchical-hash-seeded-scale-product-law"' \
  '"prediction_mode": "predict_only"' \
  '"target_table_loaded": 0' \
  '"target_comparison_performed": 0' \
  '"prediction_receipt_emitted_before_target_load": 1' \
  '"measured_masses_used_in_law": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"particle_features_hand_declared": 0' \
  '"identity_patterns_generated_from_substrate": 1' \
  '"model2_hierarchical_substrate_present": 1' \
  '"hierarchical_replay_performed": 1' \
  '"per_scale_kappa_traces_emitted": 1' \
  '"active_scale_product_cost_emitted": 1' \
  '"mass_ratio_predictions_emitted": 1' \
  '"prediction_dynamic_range": "22.098461538461538461538461538461538461538461538461538461538461538461538461538462"' \
  '"control_Z_L_estimates": {' \
  '"model2_prediction_receipt_hash": "sha256:' \
  '"model2_prediction_receipt_hash_generated": 1' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0'
do
  require_contains "$pattern" "$prediction_json"
done

for pattern in \
  '"latticra_identity_replay_model2_prediction_evaluation_present": 1' \
  '"evaluation_id": "latticra-identity-replay-model2-prediction-evaluation"' \
  '"prediction_law_id": "model2-hierarchical-hash-seeded-scale-product-law"' \
  '"model2_prediction_receipt_hash_valid": 1' \
  '"prediction_input_target_table_loaded": 0' \
  '"prediction_input_target_comparison_performed": 0' \
  '"target_table_loaded": 1' \
  '"target_load_after_prediction_receipt": 1' \
  '"target_comparison_performed": 1' \
  '"prediction_dynamic_range": "22.098461538461538461538461538461538461538461538461538461538461538461538461538462"' \
  '"target_dynamic_range": "337691.49623497269417"' \
  '"prediction_dynamic_range_meets_target_range": 0' \
  '"parameter_count": 6' \
  '"target_count": 7' \
  '"parameter_count_less_than_target_count": 1' \
  '"photon_zero_rest_mass_control_survives": 1' \
  '"gluon_zero_rest_mass_control_survives": 1' \
  '"candidate_survives_target_table": 0' \
  '"model2_prediction_law_rejected": 1' \
  '"model2_prediction_conclusion": "rejected_by_target_table"' \
  '"hierarchy_sufficient_for_range_but_prediction_vector_failed": 1' \
  '"candidate_promoted": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"model2_evaluation_receipt_hash": "sha256:' \
  '"model2_evaluation_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$evaluation_json"
done

python3 - "$prediction_json" "$evaluation_json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    prediction = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    evaluation = json.load(handle)

assert prediction["target_table_loaded"] == 0
assert prediction["target_comparison_performed"] == 0
assert prediction["prediction_receipt_emitted_before_target_load"] == 1
assert prediction["particle_features_hand_declared"] == 0
assert prediction["identity_patterns_generated_from_substrate"] == 1
assert prediction["mass_ratio_predictions_emitted"] == 1
assert prediction["control_Z_L_estimates"]["photon"] == "0"
assert prediction["control_Z_L_estimates"]["gluon"] == "0"
assert evaluation["model2_prediction_receipt_hash_valid"] == 1
assert evaluation["target_load_after_prediction_receipt"] == 1
assert evaluation["prediction_dynamic_range_meets_target_range"] == 0
assert evaluation["parameter_count_less_than_target_count"] == 1
assert evaluation["candidate_survives_target_table"] == 0
assert evaluation["model2_prediction_law_rejected"] == 1
assert evaluation["model2_prediction_conclusion"] == "rejected_by_target_table"
assert evaluation["failure_record_if_any_target_breaks"] == [
    "I_mu",
    "I_tau",
    "I_W",
    "I_Z",
    "I_H",
    "I_top",
]
assert evaluation["higgs_checkmate_claimed"] == 0
assert evaluation["simulation_proven"] == 0
PY

require_contains 'Model-2 Prediction Runner' "$model2_prereg_doc"
require_contains 'Model-2 Prediction Runner' "$model2_prereg_status"
require_contains 'Model-2 Prediction Runner' "$model1_falsifier_doc"
require_contains 'Model-2 Prediction Runner' "$table"
require_contains 'Model-2 Prediction Runner' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER_STATUS.md' "$status_index"
require_contains 'Model-2 Prediction Runner' "$docs_hub"
require_contains 'Model-2 Prediction Runner](docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER.md)' "$root_readme"
require_contains 'Model-2 Prediction Runner](../LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER.md)' "$status_index"
require_contains 'Model-2 prediction runner' "$handbook"
require_contains 'Latest Latticra identity-replay Model-2 prediction runner note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-2 prediction runner note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-2 prediction runner note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-2 prediction runner note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$current_status"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$current_status"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$upcoming_work"
require_contains 'latticra-identity-replay-model2-prediction-runner:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-prediction-runner.sh' "$makefile"
require_contains 'latticra-identity-replay-model2-prediction-runner:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-prediction-runner.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-2 prediction runner guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model2-prediction-runner.sh' "$workflow"

printf 'latticra_identity_replay_model2_prediction_runner: ok\n'
