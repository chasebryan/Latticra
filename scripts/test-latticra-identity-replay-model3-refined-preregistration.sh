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
rejection_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS.md'
rejection_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS_STATUS.md'
visual_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE.md'
visual_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE_STATUS.md'
one_page='docs/LATTICRA_HIGGS_CHALLENGE_ONE_PAGE.md'
prediction_tool='tools/latticra_identity_replay_model3_runner.py'
evaluation_tool='tools/latticra_identity_replay_model3_evaluate.py'
analysis_tool='tools/latticra_identity_replay_model3_rejection_analysis.py'
gate_tool='tools/latticra_identity_replay_model3_refinement_gate.py'
pre_registration_tool='tools/latticra_identity_replay_model3_refined_preregistration.py'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
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
workflow='.github/workflows/latticra-identity-replay-model3-refined-preregistration.yml'

for file in "$doc" "$status" "$rejection_doc" "$rejection_status" "$visual_doc" "$visual_status" "$one_page" "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool" "$pre_registration_tool" "$table" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model3_refined_preregistration_present=1' "$file"
  require_contains 'pre_registration_id=latticra-identity-replay-model3-refined-preregistration' "$file"
  require_contains 'refined_model3_law_id=refined-model3-target-blind-sector-resolved-topological-charge' "$file"
  require_contains 'pre_registration_tool=tools/latticra_identity_replay_model3_refined_preregistration.py' "$file"
  require_contains 'model3_refinement_gate_receipt_hash_valid=1' "$file"
  require_contains 'refined_model3_required_law_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'refined_model3_preregistration_authorized_by_gate=1' "$file"
  require_contains 'target_table_loaded=0' "$file"
  require_contains 'target_comparison_performed=0' "$file"
  require_contains 'pre_registered_before_target_load=1' "$file"
  require_contains 'measured_masses_used_in_law=0' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'target_ratios_used_in_law=0' "$file"
  require_contains 'particle_features_hand_declared=0' "$file"
  require_contains 'particle_name_to_sector_mapping_used=0' "$file"
  require_contains 'particle_name_to_cost_mapping_used=0' "$file"
  require_contains 'post_target_parameter_tuning_used=0' "$file"
  require_contains 'target_guided_loss_function_used=0' "$file"
  require_contains 'mass_ratio_predictions_emitted=0' "$file"
  require_contains 'refined_model3_sector_resolved_topological_charge_present=1' "$file"
  require_contains 'family_monotonicity_constraint_present=1' "$file"
  require_contains 'single_global_amplifier_used=0' "$file"
  require_contains 'sector_charge_radix=5' "$file"
  require_contains 'sector_charge_depth=4' "$file"
  require_contains 'family_monotonicity_states=3' "$file"
  require_contains 'family_monotonicity_depth=2' "$file"
  require_contains 'model3_topological_max_ratio_bound_before_target_load=181807037485056' "$file"
  require_contains 'refined_sector_charge_multiplier_before_target_load=5625' "$file"
  require_contains 'refined_model3_max_ratio_bound_before_target_load=1022664585853440000' "$file"
  require_contains 'minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395' "$file"
  require_contains 'parameter_count=6' "$file"
  require_contains 'target_count_loaded=0' "$file"
  require_contains 'parameter_count_less_than_target_count=0' "$file"
  require_contains 'parameter_count_less_than_target_count_required=1' "$file"
  require_contains 'negative_controls_required=1' "$file"
  require_contains 'photon_zero_rest_mass_control_required=1' "$file"
  require_contains 'gluon_zero_rest_mass_control_required=1' "$file"
  require_contains 'required_next_artifact=Refined Model-3 target-blind capacity gate before any prediction-only runner' "$file"
  require_contains 'refined_model3_capacity_gate_required_before_prediction=1' "$file"
  require_contains 'refined_model3_prediction_receipt_before_target_load_required=1' "$file"
  require_contains 'refined_model3_target_load_after_prediction_receipt_required=1' "$file"
  require_contains 'refined_model3_prediction_runner_authorized=0' "$file"
  require_contains 'refined_model3_candidate_promoted=0' "$file"
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
  require_contains 'refined_model3_pre_registration_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Pre-Registration Receipt' '## Law Shape' '## Current Conclusion' '## Invocation' '## Validation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model3_refinement_gate.py' \
  'python3 tools/latticra_identity_replay_model3_refined_preregistration.py' \
  'Refined Model-3 is pre-registered only' \
  'Identity-replay impedance refined Model-3 target-blind capacity gate.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$pre_registration_tool"; then
  fail "$pre_registration_tool must not contain measured target masses or measured ratios"
fi

python3 -m py_compile "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool" "$pre_registration_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model3-refined-preregistration.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/model3_prediction.json"
evaluation_json="$tmp_dir/model3_evaluation.json"
analysis_json="$tmp_dir/model3_rejection_analysis.json"
gate_json="$tmp_dir/model3_refinement_gate.json"
refined_json="$tmp_dir/model3_refined_preregistration.json"

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"
python3 "$analysis_tool" --predictions "$prediction_json" --evaluation "$evaluation_json" > "$analysis_json"
python3 "$gate_tool" --analysis "$analysis_json" > "$gate_json"

if python3 "$pre_registration_tool" --gate "$gate_json" > "$tmp_dir/no-flag.json" 2>"$tmp_dir/no-flag.err"; then
  fail "$pre_registration_tool must require --pre-register"
fi

python3 "$pre_registration_tool" --gate "$gate_json" --pre-register > "$refined_json"

for pattern in \
  '"latticra_identity_replay_model3_refinement_gate_present": 1' \
  '"model3_rejection_analysis_receipt_hash_valid": 1' \
  '"refined_model3_preregistration_authorized": 1' \
  '"refined_model3_prediction_runner_authorized": 0' \
  '"single_global_amplifier_forbidden": 1' \
  '"model3_refinement_gate_receipt_hash": "sha256:'
do
  require_contains "$pattern" "$gate_json"
done

for pattern in \
  '"latticra_identity_replay_model3_refined_preregistration_present": 1' \
  '"pre_registration_id": "latticra-identity-replay-model3-refined-preregistration"' \
  '"refined_model3_law_id": "refined-model3-target-blind-sector-resolved-topological-charge"' \
  '"model3_refinement_gate_receipt_hash_valid": 1' \
  '"refined_model3_preregistration_authorized_by_gate": 1' \
  '"target_table_loaded": 0' \
  '"target_comparison_performed": 0' \
  '"pre_registered_before_target_load": 1' \
  '"measured_masses_used_in_law": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"target_ratios_used_in_law": 0' \
  '"particle_features_hand_declared": 0' \
  '"particle_name_to_sector_mapping_used": 0' \
  '"particle_name_to_cost_mapping_used": 0' \
  '"post_target_parameter_tuning_used": 0' \
  '"target_guided_loss_function_used": 0' \
  '"mass_ratio_predictions_emitted": 0' \
  '"refined_model3_sector_resolved_topological_charge_present": 1' \
  '"family_monotonicity_constraint_present": 1' \
  '"single_global_amplifier_used": 0' \
  '"sector_charge_radix": 5' \
  '"sector_charge_depth": 4' \
  '"family_monotonicity_states": 3' \
  '"family_monotonicity_depth": 2' \
  '"model3_topological_max_ratio_bound_before_target_load": "181807037485056"' \
  '"refined_sector_charge_multiplier_before_target_load": "5625"' \
  '"refined_model3_max_ratio_bound_before_target_load": "1022664585853440000"' \
  '"minimum_refined_model3_dynamic_range_multiplier_required": "5.4744404767584652275663280083338001338306169886721631882430541171586743908036395"' \
  '"parameter_count": 6' \
  '"target_count_loaded": 0' \
  '"parameter_count_less_than_target_count": 0' \
  '"parameter_count_less_than_target_count_required": 1' \
  '"refined_model3_capacity_gate_required_before_prediction": 1' \
  '"refined_model3_prediction_runner_authorized": 0' \
  '"refined_model3_candidate_promoted": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"target_guided_loss_function"' \
  '"single_global_amplifier_only"' \
  '"refined_model3_pre_registration_receipt_hash": "sha256:' \
  '"refined_model3_pre_registration_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$refined_json"
done

python3 - "$gate_json" "$refined_json" <<'PY'
import json
import sys
from decimal import Decimal

with open(sys.argv[1], encoding="utf-8") as handle:
    gate = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    refined = json.load(handle)

assert gate["model3_rejection_analysis_receipt_hash_valid"] == 1
assert gate["refined_model3_preregistration_authorized"] == 1
assert gate["refined_model3_prediction_runner_authorized"] == 0
assert refined["model3_refinement_gate_receipt_hash_valid"] == 1
assert refined["refined_model3_preregistration_authorized_by_gate"] == 1
assert refined["target_table_loaded"] == 0
assert refined["target_comparison_performed"] == 0
assert refined["pre_registered_before_target_load"] == 1
assert refined["target_ratios_used_in_law"] == 0
assert refined["particle_name_to_sector_mapping_used"] == 0
assert refined["mass_ratio_predictions_emitted"] == 0
assert refined["single_global_amplifier_used"] == 0
assert Decimal(refined["refined_sector_charge_multiplier_before_target_load"]) == Decimal("5625")
assert Decimal(refined["refined_model3_max_ratio_bound_before_target_load"]) == Decimal("1022664585853440000")
assert refined["refined_model3_capacity_gate_required_before_prediction"] == 1
assert refined["refined_model3_prediction_runner_authorized"] == 0
assert refined["mass_ratio_recovery_claimed"] == 0
assert refined["higgs_checkmate_claimed"] == 0
assert refined["simulation_proven"] == 0
PY

require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$rejection_doc"
require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$rejection_status"
require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$visual_doc"
require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$visual_status"
require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$one_page"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL3_REFINED_PREREGISTRATION_STATUS.md' "$status_index"
require_contains 'Refined Model-3 Pre-Registration' "$docs_hub"
require_contains 'Refined Model-3 Pre-Registration](docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REFINED_PREREGISTRATION.md)' "$root_readme"
require_contains 'Latest Latticra identity-replay Model-3 refined pre-registration note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-3 refined pre-registration note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-3 refined pre-registration note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-3 refined pre-registration note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$current_status"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$upcoming_work"
require_contains 'Identity-replay impedance refined Model-3 target-blind capacity gate.' "$current_status"
require_contains 'Identity-replay impedance refined Model-3 target-blind capacity gate.' "$current_direction"
require_contains 'Identity-replay impedance refined Model-3 target-blind capacity gate.' "$upcoming_work"
require_contains 'refined Model-3 sector-resolved topological charge pre-registration' "$handbook"
require_contains 'latticra-identity-replay-model3-refined-preregistration:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-refined-preregistration.sh' "$makefile"
require_contains 'latticra-identity-replay-model3-refined-preregistration:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-refined-preregistration.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-3 refined pre-registration guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"

printf 'latticra_identity_replay_model3_refined_preregistration: ok\n'
