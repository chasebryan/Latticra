#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model3 rejection analysis: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS_STATUS.md'
prediction_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_PREDICTION_RUNNER.md'
prediction_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_PREDICTION_RUNNER_STATUS.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
prediction_tool='tools/latticra_identity_replay_model3_runner.py'
evaluation_tool='tools/latticra_identity_replay_model3_evaluate.py'
analysis_tool='tools/latticra_identity_replay_model3_rejection_analysis.py'
gate_tool='tools/latticra_identity_replay_model3_refinement_gate.py'
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
workflow='.github/workflows/latticra-identity-replay-model3-rejection-analysis.yml'

for file in "$doc" "$status" "$prediction_doc" "$prediction_status" "$proof_object_4" "$table" "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model3_rejection_analysis_present=1' "$file"
  require_contains 'latticra_identity_replay_model3_refinement_gate_present=1' "$file"
  require_contains 'analysis_id=latticra-identity-replay-model3-rejection-analysis' "$file"
  require_contains 'gate_id=latticra-identity-replay-model3-refinement-gate' "$file"
  require_contains 'analysis_tool=tools/latticra_identity_replay_model3_rejection_analysis.py' "$file"
  require_contains 'gate_tool=tools/latticra_identity_replay_model3_refinement_gate.py' "$file"
  require_contains 'model3_prediction_receipt_hash_valid=1' "$file"
  require_contains 'model3_evaluation_receipt_hash_valid=1' "$file"
  require_contains 'model3_rejection_analysis_receipt_hash_valid=1' "$file"
  require_contains 'prediction_receipt_emitted_before_target_load=1' "$file"
  require_contains 'target_load_after_prediction_receipt=1' "$file"
  require_contains 'prediction_law_id=model3-target-blind-topological-replay-amplification' "$file"
  require_contains 'model3_prediction_law_rejected=1' "$file"
  require_contains 'model3_prediction_conclusion=rejected_by_target_table' "$file"
  require_contains 'prediction_dynamic_range=61685.116071428571428571428571428571428571428571428571428571428571428571428571427' "$file"
  require_contains 'target_dynamic_range=337691.49623497269417' "$file"
  require_contains 'dynamic_range_deficit_factor=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395' "$file"
  require_contains 'prediction_dynamic_range_meets_target_range=0' "$file"
  require_contains 'target_count=7' "$file"
  require_contains 'failed_identity_count=6' "$file"
  require_contains 'surviving_identity_count=1' "$file"
  require_contains 'failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top' "$file"
  require_contains 'predicted_identity_order_by_ratio=I_H,I_Z,I_e,I_tau,I_mu,I_W,I_top' "$file"
  require_contains 'target_identity_order_by_ratio=I_e,I_mu,I_tau,I_W,I_Z,I_H,I_top' "$file"
  require_contains 'ordering_failure_present=1' "$file"
  require_contains 'lepton_family_order_inversion_present=1' "$file"
  require_contains 'lepton_family_gap_underestimated=1' "$file"
  require_contains 'heavy_sector_underamplified=1' "$file"
  require_contains 'low_electroweak_below_electron_present=1' "$file"
  require_contains 'low_electroweak_below_electron_targets=Higgs boson,Z boson' "$file"
  require_contains 'top_quark_still_underamplified=1' "$file"
  require_contains 'non_anchor_min_required_multiplier=10.292350482886447063105680868838763575605680868838763575605680868838763575605681' "$file"
  require_contains 'non_anchor_max_required_multiplier=844629.21666892438261939285714285714285714285714285714285714285714285714285714286' "$file"
  require_contains 'single_global_amplifier_insufficient=1' "$file"
  require_contains 'required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'refined_model3_required_law_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395' "$file"
  require_contains 'refined_model3_preregistration_authorized=1' "$file"
  require_contains 'refined_model3_prediction_runner_authorized=0' "$file"
  require_contains 'refined_model3_candidate_promoted=0' "$file"
  require_contains 'model3_refinement_gate_conclusion=worth_refining_only_not_worth_promoting' "$file"
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
  require_contains 'model3_rejection_analysis_receipt_hash_generated=1' "$file"
  require_contains 'model3_refinement_gate_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Rejection Analysis Checkpoint' '## Refinement Gate' '## Failure Shape' '## Current Conclusion' '## Invocation' '## Validation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model3_rejection_analysis.py' \
  'python3 tools/latticra_identity_replay_model3_refinement_gate.py' \
  'Model-3 is useful but not sufficient' \
  'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.'
do
  require_contains "$pattern" "$doc"
done

if grep -Eq '105[.]658|1776[.]93|80369[.]2|91188[.]0|125200|172560|206[.]768|337691[.]496' "$analysis_tool" "$gate_tool"; then
  fail "Model-3 rejection analysis tools must not hardcode measured target masses or measured ratios"
fi

python3 -m py_compile "$prediction_tool" "$evaluation_tool" "$analysis_tool" "$gate_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model3-rejection-analysis.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
prediction_json="$tmp_dir/model3_prediction.json"
evaluation_json="$tmp_dir/model3_evaluation.json"
analysis_json="$tmp_dir/model3_rejection_analysis.json"
gate_json="$tmp_dir/model3_refinement_gate.json"

python3 "$prediction_tool" --predict-only > "$prediction_json"
python3 "$evaluation_tool" --predictions "$prediction_json" --targets "$table" > "$evaluation_json"
python3 "$analysis_tool" --predictions "$prediction_json" --evaluation "$evaluation_json" > "$analysis_json"
python3 "$gate_tool" --analysis "$analysis_json" > "$gate_json"

for pattern in \
  '"latticra_identity_replay_model3_rejection_analysis_present": 1' \
  '"analysis_id": "latticra-identity-replay-model3-rejection-analysis"' \
  '"model3_prediction_receipt_hash_valid": 1' \
  '"model3_evaluation_receipt_hash_valid": 1' \
  '"model3_prediction_law_rejected": 1' \
  '"prediction_dynamic_range": "61685.116071428571428571428571428571428571428571428571428571428571428571428571427"' \
  '"target_dynamic_range": "337691.49623497269417"' \
  '"dynamic_range_deficit_factor": "5.4744404767584652275663280083338001338306169886721631882430541171586743908036395"' \
  '"failed_identity_count": 6' \
  '"surviving_identity_count": 1' \
  '"ordering_failure_present": 1' \
  '"lepton_family_order_inversion_present": 1' \
  '"heavy_sector_underamplified": 1' \
  '"low_electroweak_below_electron_present": 1' \
  '"non_anchor_max_required_multiplier": "844629.21666892438261939285714285714285714285714285714285714285714285714285714286"' \
  '"single_global_amplifier_insufficient": 1' \
  '"required_refined_model3_property": "target_blind_sector_resolved_topological_charge_with_family_monotonicity"' \
  '"refined_model3_prediction_runner_authorized": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model3_rejection_analysis_receipt_hash": "sha256:' \
  '"model3_rejection_analysis_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$analysis_json"
done

for pattern in \
  '"latticra_identity_replay_model3_refinement_gate_present": 1' \
  '"gate_id": "latticra-identity-replay-model3-refinement-gate"' \
  '"model3_rejection_analysis_receipt_hash_valid": 1' \
  '"model3_prediction_law_rejected": 1' \
  '"refined_model3_required_law_property": "target_blind_sector_resolved_topological_charge_with_family_monotonicity"' \
  '"minimum_refined_model3_dynamic_range_multiplier_required": "5.4744404767584652275663280083338001338306169886721631882430541171586743908036395"' \
  '"low_electroweak_below_electron_must_be_addressed": 1' \
  '"single_global_amplifier_forbidden": 1' \
  '"refined_model3_preregistration_authorized": 1' \
  '"refined_model3_prediction_runner_authorized": 0' \
  '"refined_model3_candidate_promoted": 0' \
  '"sector_resolved_topological_trace_required": 1' \
  '"family_monotonicity_trace_required": 1' \
  '"target_guided_loss_function"' \
  '"single_global_amplifier_only"' \
  '"model3_refinement_gate_conclusion": "worth_refining_only_not_worth_promoting"' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"model3_refinement_gate_receipt_hash": "sha256:' \
  '"model3_refinement_gate_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$gate_json"
done

python3 - "$analysis_json" "$gate_json" <<'PY'
import json
import sys
from decimal import Decimal

with open(sys.argv[1], encoding="utf-8") as handle:
    analysis = json.load(handle)
with open(sys.argv[2], encoding="utf-8") as handle:
    gate = json.load(handle)

assert analysis["model3_prediction_receipt_hash_valid"] == 1
assert analysis["model3_evaluation_receipt_hash_valid"] == 1
assert analysis["model3_prediction_law_rejected"] == 1
assert Decimal(analysis["dynamic_range_deficit_factor"]) == Decimal(
    "5.4744404767584652275663280083338001338306169886721631882430541171586743908036395"
)
assert analysis["failed_identity_count"] == 6
assert analysis["surviving_identity_count"] == 1
assert analysis["predicted_identity_order_by_ratio"] == [
    "I_H",
    "I_Z",
    "I_e",
    "I_tau",
    "I_mu",
    "I_W",
    "I_top",
]
assert analysis["target_identity_order_by_ratio"] == [
    "I_e",
    "I_mu",
    "I_tau",
    "I_W",
    "I_Z",
    "I_H",
    "I_top",
]
assert analysis["low_electroweak_below_electron_targets"] == [
    "Higgs boson",
    "Z boson",
]
assert analysis["single_global_amplifier_insufficient"] == 1
assert analysis["required_refined_model3_property"] == "target_blind_sector_resolved_topological_charge_with_family_monotonicity"
assert analysis["higgs_checkmate_claimed"] == 0
assert analysis["simulation_proven"] == 0
assert gate["model3_rejection_analysis_receipt_hash_valid"] == 1
assert gate["refined_model3_preregistration_authorized"] == 1
assert gate["refined_model3_prediction_runner_authorized"] == 0
assert gate["single_global_amplifier_forbidden"] == 1
assert "target_guided_loss_function" in gate["forbidden_refined_model3_inputs"]
assert "sector_resolved_topological_trace" in gate["required_refined_model3_emissions"]
assert gate["higgs_checkmate_claimed"] == 0
assert gate["simulation_proven"] == 0
PY

require_contains 'Model-3 Rejection Analysis' "$prediction_doc"
require_contains 'Model-3 Rejection Analysis' "$prediction_status"
require_contains 'Model-3 Rejection Analysis' "$proof_object_4"
require_contains 'Model-3 Rejection Analysis' "$table"
require_contains 'Model-3 rejection analysis' "$handbook"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS_STATUS.md' "$status_index"
require_contains 'Model-3 Rejection Analysis' "$docs_hub"
require_contains 'Model-3 Rejection Analysis](docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS.md)' "$root_readme"
require_contains 'Latest Latticra identity-replay Model-3 rejection analysis note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-3 rejection analysis note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-3 rejection analysis note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-3 rejection analysis note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-3 rejection analysis and amplification-law refinement.' "$current_status"
require_contains 'Identity-replay impedance Model-3 rejection analysis and amplification-law refinement.' "$current_direction"
require_contains 'Identity-replay impedance Model-3 rejection analysis and amplification-law refinement.' "$upcoming_work"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$current_status"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.' "$upcoming_work"
require_contains 'latticra-identity-replay-model3-rejection-analysis:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-rejection-analysis.sh' "$makefile"
require_contains 'latticra-identity-replay-model3-rejection-analysis:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-rejection-analysis.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-3 rejection analysis guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"

printf 'latticra_identity_replay_model3_rejection_analysis: ok\n'
