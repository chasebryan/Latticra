#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model2 hierarchical substrate preregistration: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION_STATUS.md'
model1_falsifier_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md'
model1_falsifier_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER_STATUS.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
pre_registration_tool='tools/latticra_identity_replay_model2_preregistration.py'
range_capacity_tool='tools/latticra_identity_replay_model2_range_capacity.py'
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
workflow='.github/workflows/latticra-identity-replay-model2-hierarchical-substrate-preregistration.yml'

for file in "$doc" "$status" "$model1_falsifier_doc" "$model1_falsifier_status" "$table" "$proof_object_4" "$pre_registration_tool" "$range_capacity_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model2_hierarchical_substrate_preregistration_present=1' "$file"
  require_contains 'pre_registration_id=latticra-identity-replay-model2-hierarchical-substrate-preregistration' "$file"
  require_contains 'pre_registration_version=1' "$file"
  require_contains 'model1_bounded_range_falsifier_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'pre_registration_tool=tools/latticra_identity_replay_model2_preregistration.py' "$file"
  require_contains 'range_capacity_tool=tools/latticra_identity_replay_model2_range_capacity.py' "$file"
  require_contains 'target_table_loaded=0' "$file"
  require_contains 'target_comparison_performed=0' "$file"
  require_contains 'pre_registered_before_target_load=1' "$file"
  require_contains 'measured_masses_used_in_law=0' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'particle_features_hand_declared=0' "$file"
  require_contains 'mass_ratio_predictions_emitted=0' "$file"
  require_contains 'model2_hierarchical_substrate_present=1' "$file"
  require_contains 'candidate_substrate_id=identity-replay-model2-hierarchical-substrate' "$file"
  require_contains 'scale_levels=4' "$file"
  require_contains 'cross_scale_coupling_rule=higher scale repair activates only when lower scale identity repair is nonzero; scale weights multiply, not add' "$file"
  require_contains 'repair_cost_accumulation_rule=Z_L = product(max(1, kappa_level_mean)) over active replay scales' "$file"
  require_contains 'zero_mass_control_rule=all-zero and uniform synchronized cross-scale states remain fixed under update and produce zero active repair cost' "$file"
  require_contains 'base_max_kappa_per_step=68' "$file"
  require_contains 'hierarchical_max_Z_L_before_target_load=21381376' "$file"
  require_contains 'hierarchical_max_ratio_bound_before_target_load=342102016' "$file"
  require_contains 'model2_pre_registration_receipt_hash_generated=1' "$file"
  require_contains 'latticra_identity_replay_model2_hierarchical_range_capacity_present=1' "$file"
  require_contains 'model2_pre_registration_receipt_hash_valid=1' "$file"
  require_contains 'target_load_after_pre_registration_receipt=1' "$file"
  require_contains 'dynamic_range_capacity_evaluated_against_targets=1' "$file"
  require_contains 'target_ratio_recovery_evaluated=0' "$file"
  require_contains 'target_max_ratio_to_electron=337691.49623497269417' "$file"
  require_contains 'target_max_ratio_identity=I_top' "$file"
  require_contains 'target_ratio_within_model2_hierarchical_capacity=1' "$file"
  require_contains 'target_ratio_within_model2_stationary_capacity=1' "$file"
  require_contains 'model2_not_falsified_by_range_bound=1' "$file"
  require_contains 'model2_range_capacity_conclusion=range_capacity_sufficient_for_target_vector' "$file"
  require_contains 'required_next_artifact=Model-2 prediction-only hierarchical replay runner before any mass-ratio recovery claim' "$file"
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
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'model2_range_capacity_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Pre-Registration Checkpoint' '## Range-Capacity Conclusion' '## Current Conclusion' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model2_preregistration.py --pre-register' \
  'python3 tools/latticra_identity_replay_model2_range_capacity.py' \
  'Model-2 hierarchical replay is not falsified by the dynamic-range bound that killed Model-1.' \
  'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$pre_registration_tool"; then
  fail "$pre_registration_tool must not contain measured target masses or measured ratios"
fi

python3 -m py_compile "$pre_registration_tool" "$range_capacity_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model2-hierarchical.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
pre_registration_json="$tmp_dir/model2_preregistration.json"
range_capacity_json="$tmp_dir/model2_range_capacity.json"

if python3 "$pre_registration_tool" > "$tmp_dir/no-flag.json" 2>"$tmp_dir/no-flag.err"; then
  fail "$pre_registration_tool must require --pre-register"
fi

python3 "$pre_registration_tool" --pre-register > "$pre_registration_json"
python3 "$range_capacity_tool" --pre-registration "$pre_registration_json" --targets "$table" > "$range_capacity_json"

for pattern in \
  '"latticra_identity_replay_model2_hierarchical_substrate_preregistration_present": 1' \
  '"pre_registration_id": "latticra-identity-replay-model2-hierarchical-substrate-preregistration"' \
  '"target_table_loaded": 0' \
  '"target_comparison_performed": 0' \
  '"pre_registered_before_target_load": 1' \
  '"measured_masses_used_in_law": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"mass_ratio_predictions_emitted": 0' \
  '"model2_hierarchical_substrate_present": 1' \
  '"scale_levels": 4' \
  '"base_max_kappa_per_step": "68"' \
  '"hierarchical_max_Z_L_before_target_load": "21381376"' \
  '"hierarchical_max_ratio_bound_before_target_load": "342102016"' \
  '"model2_pre_registration_receipt_hash": "sha256:' \
  '"model2_pre_registration_receipt_hash_generated": 1' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0'
do
  require_contains "$pattern" "$pre_registration_json"
done

for pattern in \
  '"latticra_identity_replay_model2_hierarchical_range_capacity_present": 1' \
  '"model2_pre_registration_receipt_hash_valid": 1' \
  '"pre_registration_target_table_loaded": 0' \
  '"pre_registration_target_comparison_performed": 0' \
  '"target_table_loaded": 1' \
  '"target_load_after_pre_registration_receipt": 1' \
  '"dynamic_range_capacity_evaluated_against_targets": 1' \
  '"target_ratio_recovery_evaluated": 0' \
  '"mass_ratio_predictions_emitted": 0' \
  '"hierarchical_max_ratio_bound_before_target_load": "342102016"' \
  '"target_max_ratio_to_electron": "337691.49623497269417"' \
  '"target_max_ratio_identity": "I_top"' \
  '"target_ratio_within_model2_hierarchical_capacity": 1' \
  '"target_ratio_within_model2_stationary_capacity": 1' \
  '"model2_not_falsified_by_range_bound": 1' \
  '"model2_range_capacity_conclusion": "range_capacity_sufficient_for_target_vector"' \
  '"parameter_count": 6' \
  '"target_count": 7' \
  '"parameter_count_less_than_target_count": 1' \
  '"candidate_survives_target_table": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"model2_range_capacity_receipt_hash": "sha256:' \
  '"model2_range_capacity_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$range_capacity_json"
done

python3 - "$pre_registration_json" "$range_capacity_json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    pre_registration = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    capacity = json.load(handle)

assert pre_registration["target_table_loaded"] == 0
assert pre_registration["target_comparison_performed"] == 0
assert pre_registration["pre_registered_before_target_load"] == 1
assert pre_registration["mass_ratio_predictions_emitted"] == 0
assert capacity["model2_pre_registration_receipt_hash_valid"] == 1
assert capacity["target_load_after_pre_registration_receipt"] == 1
assert capacity["target_ratio_within_model2_hierarchical_capacity"] == 1
assert capacity["model2_not_falsified_by_range_bound"] == 1
assert capacity["candidate_survives_target_table"] == 0
assert capacity["higgs_checkmate_claimed"] == 0
assert capacity["simulation_proven"] == 0
PY

require_contains 'Model-2 Hierarchical Substrate Pre-Registration' "$model1_falsifier_doc"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration' "$model1_falsifier_status"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration' "$table"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION_STATUS.md' "$status_index"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration' "$docs_hub"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration](docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md)' "$root_readme"
require_contains 'Model-2 Hierarchical Substrate Pre-Registration](../LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md)' "$status_index"
require_contains 'Model-2 hierarchical substrate pre-registration' "$handbook"
require_contains 'Latest Latticra identity-replay Model-2 hierarchical substrate pre-registration note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-2 hierarchical substrate pre-registration note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-2 hierarchical substrate pre-registration note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-2 hierarchical substrate pre-registration note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$current_status"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$current_status"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 prediction-only hierarchical replay runner.' "$upcoming_work"
require_contains 'latticra-identity-replay-model2-hierarchical-substrate-preregistration:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh' "$makefile"
require_contains 'latticra-identity-replay-model2-hierarchical-substrate-preregistration:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-2 hierarchical substrate pre-registration guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh' "$workflow"

printf 'latticra_identity_replay_model2_hierarchical_substrate_preregistration: ok\n'
