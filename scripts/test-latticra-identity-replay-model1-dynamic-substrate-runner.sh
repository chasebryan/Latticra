#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model1 dynamic substrate runner: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER_STATUS.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
l5_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW.md'
l5_status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW_STATUS.md'
prediction_tool='tools/latticra_identity_replay_model1_substrate.py'
evaluation_tool='tools/latticra_identity_replay_model1_evaluate.py'
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
workflow='.github/workflows/latticra-identity-replay-model1-dynamic-substrate-runner.yml'

for file in "$doc" "$status" "$table" "$proof_object_4" "$l5_doc" "$l5_status" "$prediction_tool" "$evaluation_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model1_dynamic_substrate_runner_present=1' "$file"
  require_contains 'model1_dynamic_substrate_present=1' "$file"
  require_contains 'runner_id=latticra-identity-replay-model1-dynamic-substrate-runner' "$file"
  require_contains 'runner_version=1' "$file"
  require_contains 'candidate_substrate_id=identity-replay-model1-finite-local-substrate' "$file"
  require_contains 'prediction_runner=tools/latticra_identity_replay_model1_substrate.py' "$file"
  require_contains 'evaluation_tool=tools/latticra_identity_replay_model1_evaluate.py' "$file"
  require_contains 'particle_features_hand_declared=0' "$file"
  require_contains 'identity_patterns_generated_from_substrate=1' "$file"
  require_contains 'counterfactual_repair_search_performed=1' "$file"
  require_contains 'kappa_trace_emitted=1' "$file"
  require_contains 'Z_L_confidence_window_emitted=1' "$file"
  require_contains 'prediction_receipt_emitted_before_target_load=1' "$file"
  require_contains 'prediction_input_target_table_loaded=0' "$file"
  require_contains 'target_load_after_prediction_receipt=1' "$file"
  require_contains 'negative_controls_present=1' "$file"
  require_contains 'photon_zero_rest_mass_control_present=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_present=1' "$file"
  require_contains 'photon_zero_rest_mass_control_survives=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_survives=1' "$file"
  require_contains 'state_space_definition=finite cyclic integer lattice width=17, cell_range=[-2,2]' "$file"
  require_contains 'local_update_operator=T(x_i)=clip(x_i + x_{i-1} - x_{i+1})' "$file"
  require_contains 'observer_projection=bounded integer cell projection over the full cyclic lattice' "$file"
  require_contains 'identity_quotient=lexicographically minimal cyclic rotation of the projected state' "$file"
  require_contains 'distance_metric=L1 distance over quotient representatives' "$file"
  require_contains 'counterfactual_repair_cost_function=minimal per-cell additive edits needed to restore the expected identity quotient after T' "$file"
  require_contains 'replay_horizon_N=16' "$file"
  require_contains 'epsilon_identity_tolerance=0' "$file"
  require_contains 'parameter_count=4' "$file"
  require_contains 'parameter_count_less_than_target_count=1' "$file"
  require_contains 'prediction_receipt_hash_generated=1' "$file"
  require_contains 'evaluation_receipt_hash_generated=1' "$file"
  require_contains 'candidate_survives_target_table=0' "$file"
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
done

for section in '## Purpose' '## Invocation' '## Current Model-1 Result' '## Higgs Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model1_substrate.py --predict-only' \
  'python3 tools/latticra_identity_replay_model1_evaluate.py' \
  'prediction-only runner first' \
  'target-table evaluator second' \
  'The current Model-1 candidate fails that target table.' \
  'Identity-replay impedance Model-1 substrate-law refinement gate.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$prediction_tool"; then
  fail "$prediction_tool must not contain measured target masses or measured ratios"
fi

python3 -m py_compile "$prediction_tool" "$evaluation_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-dynamic-substrate.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/prediction.json"
evaluation_json="$tmp_dir/evaluation.json"

if python3 "$prediction_tool" > "$tmp_dir/no-flag.json" 2>"$tmp_dir/no-flag.err"; then
  fail "$prediction_tool must require --predict-only"
fi

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"

for pattern in \
  '"latticra_identity_replay_model1_dynamic_substrate_runner_present": 1' \
  '"model1_dynamic_substrate_present": 1' \
  '"runner_id": "latticra-identity-replay-model1-dynamic-substrate-runner"' \
  '"prediction_mode": "predict_only"' \
  '"target_table_loaded": 0' \
  '"target_comparison_performed": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"particle_features_hand_declared": 0' \
  '"identity_patterns_generated_from_substrate": 1' \
  '"counterfactual_repair_search_performed": 1' \
  '"kappa_trace_emitted": 1' \
  '"Z_L_confidence_window_emitted": 1' \
  '"prediction_receipt_emitted_before_target_load": 1' \
  '"negative_controls_present": 1' \
  '"photon_zero_rest_mass_control_present": 1' \
  '"gluon_zero_rest_mass_control_present": 1' \
  '"prediction_receipt_hash": "sha256:' \
  '"prediction_receipt_hash_generated": 1' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0'
do
  require_contains "$pattern" "$prediction_json"
done

for pattern in \
  '"latticra_identity_replay_model1_dynamic_substrate_evaluation_present": 1' \
  '"prediction_receipt_hash_valid": 1' \
  '"prediction_input_target_table_loaded": 0' \
  '"prediction_input_target_comparison_performed": 0' \
  '"target_table_loaded": 1' \
  '"target_load_after_prediction_receipt": 1' \
  '"target_comparison_performed": 1' \
  '"parameter_count": 4' \
  '"target_count": 7' \
  '"parameter_count_less_than_target_count": 1' \
  '"photon_zero_rest_mass_control_survives": 1' \
  '"gluon_zero_rest_mass_control_survives": 1' \
  '"candidate_survives_target_table": 0' \
  '"candidate_promoted": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"standard_model_replacement_claimed": 0' \
  '"higgs_denied": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"evaluation_receipt_hash": "sha256:' \
  '"evaluation_receipt_hash_generated": 1'
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
assert prediction["control_Z_L_estimates"]["photon"] == "0"
assert prediction["control_Z_L_estimates"]["gluon"] == "0"
assert evaluation["prediction_receipt_hash_valid"] == 1
assert evaluation["target_load_after_prediction_receipt"] == 1
assert evaluation["parameter_count_less_than_target_count"] == 1
assert evaluation["candidate_survives_target_table"] == 0
assert "I_mu" in evaluation["failure_record_if_any_target_breaks"]
assert evaluation["higgs_checkmate_claimed"] == 0
assert evaluation["simulation_proven"] == 0
PY

require_contains 'Model-1 Dynamic Substrate Runner' "$table"
require_contains 'Model-1 Dynamic Substrate Runner' "$proof_object_4"
require_contains 'Model-1 Dynamic Substrate Runner' "$l5_doc"
require_contains 'Model-1 Dynamic Substrate Runner' "$l5_status"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER_STATUS.md' "$status_index"
require_contains 'Model-1 Dynamic Substrate Runner' "$docs_hub"
require_contains 'Model-1 Dynamic Substrate Runner](docs/LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER.md)' "$root_readme"
require_contains 'Model-1 Dynamic Substrate Runner](../LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER.md)' "$status_index"
require_contains 'Model-1 dynamic replay substrate runner' "$handbook"
require_contains 'Latest Latticra identity-replay Model-1 dynamic substrate runner note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-1 dynamic substrate runner note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-1 dynamic substrate runner note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-1 dynamic substrate runner note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-1 dynamic substrate runner.' "$current_status"
require_contains 'Identity-replay impedance Model-1 dynamic substrate runner.' "$current_direction"
require_contains 'Identity-replay impedance Model-1 dynamic substrate runner.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-1 substrate-law refinement gate.' "$current_status"
require_contains 'Identity-replay impedance Model-1 substrate-law refinement gate.' "$current_direction"
require_contains 'Identity-replay impedance Model-1 substrate-law refinement gate.' "$upcoming_work"
require_contains 'latticra-identity-replay-model1-dynamic-substrate-runner:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh' "$makefile"
require_contains 'latticra-identity-replay-model1-dynamic-substrate-runner:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-1 dynamic substrate runner guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh' "$workflow"

printf 'latticra_identity_replay_model1_dynamic_substrate_runner: ok\n'
