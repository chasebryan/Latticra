#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model2 prediction failure analysis: %s\n' "$1" >&2
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

analysis_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS.md'
analysis_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS_STATUS.md'
gate_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE.md'
gate_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE_STATUS.md'
model2_prediction_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER.md'
model2_prediction_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_RUNNER_STATUS.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
prediction_tool='tools/latticra_identity_replay_model2_runner.py'
evaluation_tool='tools/latticra_identity_replay_model2_evaluate.py'
analysis_tool='tools/latticra_identity_replay_model2_failure_analysis.py'
gate_tool='tools/latticra_identity_replay_model3_worthiness_gate.py'
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
workflow='.github/workflows/latticra-identity-replay-model2-prediction-failure-analysis.yml'

for file in "$analysis_doc" "$analysis_status" "$gate_doc" "$gate_status" "$model2_prediction_doc" "$model2_prediction_status" "$proof_object_4" "$table" "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$analysis_doc" "$analysis_status"
do
  require_contains 'latticra_identity_replay_model2_prediction_failure_analysis_present=1' "$file"
  require_contains 'analysis_id=latticra-identity-replay-model2-prediction-failure-analysis' "$file"
  require_contains 'analysis_tool=tools/latticra_identity_replay_model2_failure_analysis.py' "$file"
  require_contains 'model3_worthiness_gate_reference=tools/latticra_identity_replay_model3_worthiness_gate.py' "$file"
  require_contains 'model2_prediction_receipt_hash_valid=1' "$file"
  require_contains 'model2_evaluation_receipt_hash_valid=1' "$file"
  require_contains 'prediction_receipt_emitted_before_target_load=1' "$file"
  require_contains 'target_load_after_prediction_receipt=1' "$file"
  require_contains 'prediction_law_id=model2-hierarchical-hash-seeded-scale-product-law' "$file"
  require_contains 'model2_prediction_law_rejected=1' "$file"
  require_contains 'model2_prediction_conclusion=rejected_by_target_table' "$file"
  require_contains 'prediction_dynamic_range=22.098461538461538461538461538461538461538461538461538461538461538461538461538462' "$file"
  require_contains 'target_dynamic_range=337691.49623497269417' "$file"
  require_contains 'dynamic_range_deficit_factor=15281.221982228644612259816207184628237259816207184628237259816207184628237259816' "$file"
  require_contains 'prediction_dynamic_range_meets_target_range=0' "$file"
  require_contains 'target_count=7' "$file"
  require_contains 'failed_identity_count=6' "$file"
  require_contains 'surviving_identity_count=1' "$file"
  require_contains 'failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top' "$file"
  require_contains 'ordering_failure_present=1' "$file"
  require_contains 'lepton_family_order_inversion_present=1' "$file"
  require_contains 'lepton_family_gap_underestimated=1' "$file"
  require_contains 'heavy_sector_compression_present=1' "$file"
  require_contains 'heavy_sector_min_required_multiplier=62382.137440339614729086538461538461538461538461538461538461538461538461538461539' "$file"
  require_contains 'heavy_sector_max_required_multiplier=1114381.937575409890761' "$file"
  require_contains 'top_quark_amplification_required=1114381.937575409890761' "$file"
  require_contains 'required_model3_property=target_blind_topological_replay_amplification' "$file"
  require_contains 'minimum_model3_dynamic_range_multiplier_required=15281.221982228644612259816207184628237259816207184628237259816207184628237259816' "$file"
  require_contains 'model3_worthiness_gate_required=1' "$file"
  require_contains 'model3_prediction_runner_authorized=0' "$file"
  require_contains 'model3_preregistration_worthwhile_if_gate_passes=1' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'model2_failure_analysis_receipt_hash_generated=1' "$file"
done

for file in "$gate_doc" "$gate_status"
do
  require_contains 'latticra_identity_replay_model3_worthiness_gate_present=1' "$file"
  require_contains 'gate_id=latticra-identity-replay-model3-worthiness-gate' "$file"
  require_contains 'gate_tool=tools/latticra_identity_replay_model3_worthiness_gate.py' "$file"
  require_contains 'model2_failure_analysis_receipt_hash_valid=1' "$file"
  require_contains 'model2_prediction_law_rejected=1' "$file"
  require_contains 'model3_required_law_property=target_blind_topological_replay_amplification' "$file"
  require_contains 'minimum_model3_dynamic_range_multiplier_required=15281.221982228644612259816207184628237259816207184628237259816207184628237259816' "$file"
  require_contains 'prediction_dynamic_range_to_beat=22.098461538461538461538461538461538461538461538461538461538461538461538461538462' "$file"
  require_contains 'target_dynamic_range_to_span=337691.49623497269417' "$file"
  require_contains 'ordering_failure_must_be_addressed=1' "$file"
  require_contains 'lepton_family_order_inversion_must_be_addressed=1' "$file"
  require_contains 'heavy_sector_compression_must_be_addressed=1' "$file"
  require_contains 'model3_preregistration_authorized=1' "$file"
  require_contains 'model3_prediction_runner_authorized=0' "$file"
  require_contains 'model3_candidate_promoted=0' "$file"
  require_contains 'model3_worth_testing_if_preregistration_passes=1' "$file"
  require_contains 'model3_pre_registration_receipt_required=1' "$file"
  require_contains 'model3_prediction_receipt_before_target_load_required=1' "$file"
  require_contains 'model3_target_load_after_prediction_receipt_required=1' "$file"
  require_contains 'parameter_count_less_than_target_count_required=1' "$file"
  require_contains 'negative_controls_required=1' "$file"
  require_contains 'photon_zero_rest_mass_control_required=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_required=1' "$file"
  require_contains 'topological_amplification_trace_required=1' "$file"
  require_contains 'target_blind_dynamic_range_proof_required_before_prediction=1' "$file"
  require_contains 'model3_gate_conclusion=worth_preregistering_only_not_worth_promoting' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'model3_worthiness_gate_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Failure Analysis Checkpoint' '## Failure Shape' '## Current Conclusion' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$analysis_doc"
done

for section in '## Purpose' '## Worthiness Gate' '## Forbidden Model-3 Inputs' '## Required Model-3 Emissions' '## Checkmate Threshold' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$gate_doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model2_failure_analysis.py' \
  'Model-3 is worthwhile only if it can pre-register a target-blind topological replay amplification law.' \
  'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.'
do
  require_contains "$pattern" "$analysis_doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model3_worthiness_gate.py' \
  'measured_particle_masses' \
  'target_guided_loss_function' \
  'topological_amplification_trace' \
  'all guarded mass ratios survive declared epsilon' \
  'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.'
do
  require_contains "$pattern" "$gate_doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$analysis_tool" "$gate_tool"; then
  fail "failure-analysis and gate tools must not hardcode measured target masses or ratios"
fi

python3 -m py_compile "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model2-failure-analysis.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/model2_prediction.json"
evaluation_json="$tmp_dir/model2_evaluation.json"
analysis_json="$tmp_dir/model2_failure_analysis.json"
gate_json="$tmp_dir/model3_worthiness_gate.json"

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"
python3 "$analysis_tool" --predictions "$prediction_json" --evaluation "$evaluation_json" > "$analysis_json"
python3 "$gate_tool" --analysis "$analysis_json" > "$gate_json"

for pattern in \
  '"latticra_identity_replay_model2_prediction_failure_analysis_present": 1' \
  '"analysis_id": "latticra-identity-replay-model2-prediction-failure-analysis"' \
  '"model2_prediction_receipt_hash_valid": 1' \
  '"model2_evaluation_receipt_hash_valid": 1' \
  '"model2_prediction_law_rejected": 1' \
  '"prediction_dynamic_range": "22.098461538461538461538461538461538461538461538461538461538461538461538461538462"' \
  '"target_dynamic_range": "337691.49623497269417"' \
  '"dynamic_range_deficit_factor": "15281.221982228644612259816207184628237259816207184628237259816207184628237259816"' \
  '"failed_identity_count": 6' \
  '"surviving_identity_count": 1' \
  '"ordering_failure_present": 1' \
  '"lepton_family_order_inversion_present": 1' \
  '"heavy_sector_compression_present": 1' \
  '"heavy_sector_min_required_multiplier": "62382.137440339614729086538461538461538461538461538461538461538461538461538461539"' \
  '"top_quark_amplification_required": "1114381.937575409890761"' \
  '"required_model3_property": "target_blind_topological_replay_amplification"' \
  '"model3_prediction_runner_authorized": 0' \
  '"model3_preregistration_worthwhile_if_gate_passes": 1' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model2_failure_analysis_receipt_hash": "sha256:' \
  '"model2_failure_analysis_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$analysis_json"
done

for pattern in \
  '"latticra_identity_replay_model3_worthiness_gate_present": 1' \
  '"gate_id": "latticra-identity-replay-model3-worthiness-gate"' \
  '"model2_failure_analysis_receipt_hash_valid": 1' \
  '"model3_required_law_property": "target_blind_topological_replay_amplification"' \
  '"minimum_model3_dynamic_range_multiplier_required": "15281.221982228644612259816207184628237259816207184628237259816207184628237259816"' \
  '"model3_preregistration_authorized": 1' \
  '"model3_prediction_runner_authorized": 0' \
  '"model3_worth_testing_if_preregistration_passes": 1' \
  '"topological_amplification_trace_required": 1' \
  '"target_blind_dynamic_range_proof_required_before_prediction": 1' \
  '"model3_gate_conclusion": "worth_preregistering_only_not_worth_promoting"' \
  '"measured_particle_masses"' \
  '"target_guided_loss_function"' \
  '"topological_amplification_trace"' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model3_worthiness_gate_receipt_hash": "sha256:' \
  '"model3_worthiness_gate_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$gate_json"
done

python3 - "$analysis_json" "$gate_json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    analysis = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    gate = json.load(handle)

assert analysis["model2_prediction_receipt_hash_valid"] == 1
assert analysis["model2_evaluation_receipt_hash_valid"] == 1
assert analysis["model2_prediction_law_rejected"] == 1
assert analysis["failed_identity_count"] == 6
assert analysis["surviving_identity_count"] == 1
assert analysis["ordering_failure_present"] == 1
assert analysis["heavy_sector_compression_present"] == 1
assert analysis["required_model3_property"] == "target_blind_topological_replay_amplification"
assert analysis["model3_prediction_runner_authorized"] == 0
assert analysis["higgs_checkmate_claimed"] == 0
assert analysis["simulation_proven"] == 0
assert gate["model2_failure_analysis_receipt_hash_valid"] == 1
assert gate["model3_preregistration_authorized"] == 1
assert gate["model3_prediction_runner_authorized"] == 0
assert gate["model3_candidate_promoted"] == 0
assert gate["model3_required_law_property"] == "target_blind_topological_replay_amplification"
assert "target_guided_loss_function" in gate["forbidden_model3_inputs"]
assert "topological_amplification_trace" in gate["required_model3_emissions"]
assert gate["higgs_checkmate_claimed"] == 0
assert gate["simulation_proven"] == 0
PY

require_contains 'Model-2 Prediction Failure Analysis' "$model2_prediction_doc"
require_contains 'Model-2 Prediction Failure Analysis' "$model2_prediction_status"
require_contains 'Model-2 Prediction Failure Analysis' "$proof_object_4"
require_contains 'Model-3 Worthiness Gate' "$proof_object_4"
require_contains 'Model-2 Prediction Failure Analysis' "$table"
require_contains 'Model-3 Worthiness Gate' "$handbook"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS_STATUS.md' "$status_index"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE_STATUS.md' "$status_index"
require_contains 'Model-2 Prediction Failure Analysis' "$docs_hub"
require_contains 'Model-3 Worthiness Gate' "$docs_hub"
require_contains 'Model-2 Prediction Failure Analysis](docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS.md)' "$root_readme"
require_contains 'Model-3 Worthiness Gate](docs/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE.md)' "$root_readme"
require_contains 'Latest Latticra identity-replay Model-2 prediction failure analysis note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-3 worthiness gate note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-2 prediction failure analysis note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-3 worthiness gate note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-2 prediction failure analysis note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-3 worthiness gate note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-2 prediction failure analysis note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Latest Latticra identity-replay Model-3 worthiness gate note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$current_status"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 prediction failure analysis and law refinement.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$current_status"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$upcoming_work"
require_contains 'latticra-identity-replay-model2-prediction-failure-analysis:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh' "$makefile"
require_contains 'latticra-identity-replay-model2-prediction-failure-analysis:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-2 prediction failure analysis guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh' "$workflow"

printf 'latticra_identity_replay_model2_prediction_failure_analysis: ok\n'
