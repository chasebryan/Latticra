#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model3 refined preregistration: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REFINED_PREREGISTRATION.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_REFINED_PREREGISTRATION_STATUS.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
prediction_tool='tools/latticra_identity_replay_model3_runner.py'
evaluation_tool='tools/latticra_identity_replay_model3_evaluate.py'
analysis_tool='tools/latticra_identity_replay_model3_rejection_analysis.py'
gate_tool='tools/latticra_identity_replay_model3_refinement_gate.py'
pre_registration_tool='tools/latticra_identity_replay_model3_refined_preregistration.py'

for file in "$doc" "$status" "$table" "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool" "$pre_registration_tool"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model3_refined_preregistration_present=1' "$file"
  require_contains 'pre_registration_id=latticra-identity-replay-model3-refined-sector-charge-preregistration' "$file"
  require_contains 'refined_model3_law_id=model3-refined-sector-resolved-topological-charge' "$file"
  require_contains 'pre_registration_tool=tools/latticra_identity_replay_model3_refined_preregistration.py' "$file"
  require_contains 'refinement_gate_tool_reference=tools/latticra_identity_replay_model3_refinement_gate.py' "$file"
  require_contains 'model3_refinement_gate_receipt_hash_valid=1' "$file"
  require_contains 'required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'refined_model3_preregistration_authorized_by_gate=1' "$file"
  require_contains 'refined_model3_prediction_runner_authorized=0' "$file"
  require_contains 'refined_model3_capacity_gate_required_before_prediction=1' "$file"
  require_contains 'target_table_loaded=0' "$file"
  require_contains 'target_ratio_recovery_evaluated=0' "$file"
  require_contains 'target_ratios_used_in_law=0' "$file"
  require_contains 'particle_name_to_sector_mapping_used=0' "$file"
  require_contains 'target_guided_loss_function_used=0' "$file"
  require_contains 'single_global_amplifier_used=0' "$file"
  require_contains 'sector_resolved_topological_charge_present=1' "$file"
  require_contains 'family_monotonicity_constraint_present=1' "$file"
  require_contains 'target_blind_dynamic_range_proof_required_before_prediction=1' "$file"
  require_contains 'minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395' "$file"
  require_contains 'parameter_count=0' "$file"
  require_contains 'next_required_artifact=refined Model-3 target-blind dynamic-range capacity gate before any prediction-only runner' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'refined_model3_pre_registration_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Refined Pre-Registration Checkpoint' '## Boundary Rules' '## Invocation' '## Validation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'state_space_definition=unlabeled replay quotient graph' \
  'sector_charge_components=quotient_depth_charge,branch_coalescence_charge,orientation_inversion_charge,observer_closure_charge' \
  'measured_particle_masses' \
  'single_global_amplifier_only'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|337691[.]496' "$pre_registration_tool"; then
  fail "refined Model-3 pre-registration tool must not hardcode measured masses or target-ratio outcomes"
fi

python3 -m py_compile "$gate_tool" "$pre_registration_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model3-refined-preregistration.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/model3_prediction.json"
evaluation_json="$tmp_dir/model3_evaluation.json"
analysis_json="$tmp_dir/model3_rejection_analysis.json"
gate_json="$tmp_dir/model3_refinement_gate.json"
pre_registration_json="$tmp_dir/model3_refined_preregistration.json"

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"
python3 "$analysis_tool" --predictions "$prediction_json" --evaluation "$evaluation_json" > "$analysis_json"
python3 "$gate_tool" --analysis "$analysis_json" > "$gate_json"
python3 "$pre_registration_tool" --refinement-gate "$gate_json" > "$pre_registration_json"

for pattern in \
  '"latticra_identity_replay_model3_refined_preregistration_present": 1' \
  '"pre_registration_id": "latticra-identity-replay-model3-refined-sector-charge-preregistration"' \
  '"refined_model3_law_id": "model3-refined-sector-resolved-topological-charge"' \
  '"model3_refinement_gate_receipt_hash_valid": 1' \
  '"required_refined_model3_property": "target_blind_sector_resolved_topological_charge_with_family_monotonicity"' \
  '"refined_model3_preregistration_authorized_by_gate": 1' \
  '"refined_model3_prediction_runner_authorized": 0' \
  '"refined_model3_capacity_gate_required_before_prediction": 1' \
  '"target_table_loaded": 0' \
  '"target_ratios_used_in_law": 0' \
  '"particle_name_to_sector_mapping_used": 0' \
  '"single_global_amplifier_used": 0' \
  '"sector_resolved_topological_charge_present": 1' \
  '"family_monotonicity_constraint_present": 1' \
  '"minimum_refined_model3_dynamic_range_multiplier_required": "5.4744404767584652275663280083338001338306169886721631882430541171586743908036395"' \
  '"parameter_count": 0' \
  '"next_required_artifact": "refined Model-3 target-blind dynamic-range capacity gate before any prediction-only runner"' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"refined_model3_pre_registration_receipt_hash": "sha256:' \
  '"refined_model3_pre_registration_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$pre_registration_json"
done

python3 - "$gate_json" "$pre_registration_json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    gate = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    prereg = json.load(handle)

assert gate["refined_model3_preregistration_authorized"] == 1
assert gate["refined_model3_prediction_runner_authorized"] == 0
assert prereg["model3_refinement_gate_receipt_hash_valid"] == 1
assert prereg["refined_model3_preregistration_authorized_by_gate"] == 1
assert prereg["refined_model3_prediction_runner_authorized"] == 0
assert prereg["target_table_loaded"] == 0
assert prereg["target_ratios_used_in_law"] == 0
assert prereg["particle_name_to_sector_mapping_used"] == 0
assert prereg["single_global_amplifier_used"] == 0
assert prereg["sector_resolved_topological_charge_present"] == 1
assert prereg["family_monotonicity_constraint_present"] == 1
assert prereg["parameter_count"] == 0
assert prereg["candidate_promoted"] == 0
assert prereg["mass_ratio_recovery_claimed"] == 0
assert prereg["higgs_checkmate_claimed"] == 0
assert prereg["simulation_proven"] == 0
assert "not_refined_model3_prediction" in prereg["non_claims"]
PY

printf 'latticra_identity_replay_model3_refined_preregistration: ok\n'
