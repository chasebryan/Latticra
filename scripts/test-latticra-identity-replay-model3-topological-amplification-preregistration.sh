#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model3 topological amplification preregistration: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION_STATUS.md'
gate_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE.md'
gate_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE_STATUS.md'
failure_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS.md'
failure_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS_STATUS.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
pre_registration_tool='tools/latticra_identity_replay_model3_preregistration.py'
capacity_tool='tools/latticra_identity_replay_model3_capacity_gate.py'
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
workflow='.github/workflows/latticra-identity-replay-model3-topological-amplification-preregistration.yml'

for file in "$doc" "$status" "$gate_doc" "$gate_status" "$failure_doc" "$failure_status" "$proof_object_4" "$table" "$pre_registration_tool" "$capacity_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model3_topological_amplification_preregistration_present=1' "$file"
  require_contains 'pre_registration_id=latticra-identity-replay-model3-topological-amplification-preregistration' "$file"
  require_contains 'model3_law_id=model3-target-blind-topological-replay-amplification' "$file"
  require_contains 'pre_registration_tool=tools/latticra_identity_replay_model3_preregistration.py' "$file"
  require_contains 'capacity_gate_tool=tools/latticra_identity_replay_model3_capacity_gate.py' "$file"
  require_contains 'target_table_loaded=0' "$file"
  require_contains 'target_comparison_performed=0' "$file"
  require_contains 'pre_registered_before_target_load=1' "$file"
  require_contains 'model3_pre_registration_receipt_hash_valid=1' "$file"
  require_contains 'target_load_after_pre_registration_receipt=1' "$file"
  require_contains 'measured_masses_used_in_law=0' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'target_ratios_used_in_law=0' "$file"
  require_contains 'particle_features_hand_declared=0' "$file"
  require_contains 'mass_ratio_predictions_emitted=0' "$file"
  require_contains 'model3_topological_amplification_present=1' "$file"
  require_contains 'topological_amplification_trace_required=1' "$file"
  require_contains 'target_blind_dynamic_range_proof_before_prediction=1' "$file"
  require_contains 'topological_branching_factor=3' "$file"
  require_contains 'topological_branching_semantics=erase_reinforce_invert' "$file"
  require_contains 'topological_replay_depth=12' "$file"
  require_contains 'quotient_instability_layers=4' "$file"
  require_contains 'scale_levels=4' "$file"
  require_contains 'model2_hierarchical_max_ratio_bound_before_target_load=342102016' "$file"
  require_contains 'topological_amplification_multiplier_before_target_load=531441' "$file"
  require_contains 'model3_topological_max_ratio_bound_before_target_load=181807037485056' "$file"
  require_contains 'target_max_ratio_to_electron=337691.49623497269417' "$file"
  require_contains 'target_max_ratio_identity=I_top' "$file"
  require_contains 'model3_capacity_margin_over_target=538382042.52129263265789900292129756016072732793006502458542080618422320551335316' "$file"
  require_contains 'target_ratio_within_model3_topological_capacity=1' "$file"
  require_contains 'model3_not_falsified_by_range_bound=1' "$file"
  require_contains 'model3_capacity_gate_conclusion=range_capacity_sufficient_for_model3_prediction_runner' "$file"
  require_contains 'model3_prediction_runner_authorized_after_capacity_gate=1' "$file"
  require_contains 'required_next_artifact=Model-3 prediction-only topological amplification runner before any mass-ratio recovery claim' "$file"
  require_contains 'parameter_count=6' "$file"
  require_contains 'target_count=7' "$file"
  require_contains 'parameter_count_less_than_target_count=1' "$file"
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
  require_contains 'model3_pre_registration_receipt_hash_generated=1' "$file"
  require_contains 'model3_capacity_gate_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Pre-Registration Checkpoint' '## Capacity Gate' '## Current Conclusion' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model3_preregistration.py --pre-register' \
  'python3 tools/latticra_identity_replay_model3_capacity_gate.py' \
  'Model-3 topological amplification is not falsified by dynamic-range capacity and is authorized for a prediction-only runner.' \
  'Identity-replay impedance Model-3 prediction-only topological amplification runner.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$pre_registration_tool"; then
  fail "$pre_registration_tool must not contain measured target masses or measured ratios"
fi

python3 -m py_compile "$pre_registration_tool" "$capacity_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model3-topological-preregistration.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
pre_registration_json="$tmp_dir/model3_preregistration.json"
capacity_json="$tmp_dir/model3_capacity.json"

if python3 "$pre_registration_tool" > "$tmp_dir/no-flag.json" 2>"$tmp_dir/no-flag.err"; then
  fail "$pre_registration_tool must require --pre-register"
fi

python3 "$pre_registration_tool" --pre-register > "$pre_registration_json"
python3 "$capacity_tool" --pre-registration "$pre_registration_json" --targets "$table" > "$capacity_json"

for pattern in \
  '"latticra_identity_replay_model3_topological_amplification_preregistration_present": 1' \
  '"pre_registration_id": "latticra-identity-replay-model3-topological-amplification-preregistration"' \
  '"model3_law_id": "model3-target-blind-topological-replay-amplification"' \
  '"target_table_loaded": 0' \
  '"target_comparison_performed": 0' \
  '"pre_registered_before_target_load": 1' \
  '"measured_masses_used_in_law": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"target_ratios_used_in_law": 0' \
  '"particle_features_hand_declared": 0' \
  '"mass_ratio_predictions_emitted": 0' \
  '"model3_topological_amplification_present": 1' \
  '"topological_branching_factor": 3' \
  '"topological_replay_depth": 12' \
  '"topological_amplification_multiplier_before_target_load": "531441"' \
  '"model3_topological_max_ratio_bound_before_target_load": "181807037485056"' \
  '"model3_prediction_runner_authorized": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model3_pre_registration_receipt_hash": "sha256:' \
  '"model3_pre_registration_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$pre_registration_json"
done

for pattern in \
  '"latticra_identity_replay_model3_topological_capacity_gate_present": 1' \
  '"capacity_gate_id": "latticra-identity-replay-model3-topological-capacity-gate"' \
  '"model3_pre_registration_receipt_hash_valid": 1' \
  '"pre_registration_target_table_loaded": 0' \
  '"pre_registration_target_comparison_performed": 0' \
  '"target_table_loaded": 1' \
  '"target_load_after_pre_registration_receipt": 1' \
  '"dynamic_range_capacity_evaluated_against_targets": 1' \
  '"target_ratio_recovery_evaluated": 0' \
  '"mass_ratio_predictions_emitted": 0' \
  '"model3_topological_max_ratio_bound_before_target_load": "181807037485056"' \
  '"target_max_ratio_to_electron": "337691.49623497269417"' \
  '"target_max_ratio_identity": "I_top"' \
  '"model3_capacity_margin_over_target": "538382042.52129263265789900292129756016072732793006502458542080618422320551335316"' \
  '"target_ratio_within_model3_topological_capacity": 1' \
  '"model3_not_falsified_by_range_bound": 1' \
  '"model3_capacity_gate_conclusion": "range_capacity_sufficient_for_model3_prediction_runner"' \
  '"model3_prediction_runner_authorized_after_capacity_gate": 1' \
  '"parameter_count": 6' \
  '"target_count": 7' \
  '"parameter_count_less_than_target_count": 1' \
  '"candidate_survives_target_table": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model3_capacity_gate_receipt_hash": "sha256:' \
  '"model3_capacity_gate_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$capacity_json"
done

python3 - "$pre_registration_json" "$capacity_json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    pre_registration = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    capacity = json.load(handle)

assert pre_registration["target_table_loaded"] == 0
assert pre_registration["target_comparison_performed"] == 0
assert pre_registration["pre_registered_before_target_load"] == 1
assert pre_registration["target_ratios_used_in_law"] == 0
assert pre_registration["mass_ratio_predictions_emitted"] == 0
assert capacity["model3_pre_registration_receipt_hash_valid"] == 1
assert capacity["target_load_after_pre_registration_receipt"] == 1
assert capacity["target_ratio_within_model3_topological_capacity"] == 1
assert capacity["model3_prediction_runner_authorized_after_capacity_gate"] == 1
assert capacity["mass_ratio_recovery_claimed"] == 0
assert capacity["higgs_checkmate_claimed"] == 0
assert capacity["simulation_proven"] == 0
PY

require_contains 'Model-3 Topological Amplification Pre-Registration' "$gate_doc"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$gate_status"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$failure_doc"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$failure_status"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$proof_object_4"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$table"
require_contains 'Model-3 topological amplification pre-registration' "$handbook"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION_STATUS.md' "$status_index"
require_contains 'Model-3 Topological Amplification Pre-Registration' "$docs_hub"
require_contains 'Model-3 Topological Amplification Pre-Registration](docs/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION.md)' "$root_readme"
require_contains 'Latest Latticra identity-replay Model-3 topological amplification pre-registration note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-3 topological amplification pre-registration note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-3 topological amplification pre-registration note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-3 topological amplification pre-registration note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$current_status"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance Model-3 target-blind topological amplification pre-registration.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-3 prediction-only topological amplification runner.' "$current_status"
require_contains 'Identity-replay impedance Model-3 prediction-only topological amplification runner.' "$current_direction"
require_contains 'Identity-replay impedance Model-3 prediction-only topological amplification runner.' "$upcoming_work"
require_contains 'latticra-identity-replay-model3-topological-amplification-preregistration:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-topological-amplification-preregistration.sh' "$makefile"
require_contains 'latticra-identity-replay-model3-topological-amplification-preregistration:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-topological-amplification-preregistration.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-3 topological amplification pre-registration guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model3-topological-amplification-preregistration.sh' "$workflow"

printf 'latticra_identity_replay_model3_topological_amplification_preregistration: ok\n'
