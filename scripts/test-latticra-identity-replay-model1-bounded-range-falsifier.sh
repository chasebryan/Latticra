#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model1 bounded range falsifier: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER_STATUS.md'
model1_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER.md'
model1_status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL1_DYNAMIC_SUBSTRATE_RUNNER_STATUS.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
range_tool='tools/latticra_identity_replay_model1_range_falsifier.py'
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
workflow='.github/workflows/latticra-identity-replay-model1-bounded-range-falsifier.yml'

for file in "$doc" "$status" "$model1_doc" "$model1_status" "$table" "$proof_object_4" "$range_tool" "$prediction_tool" "$evaluation_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model1_bounded_range_falsifier_present=1' "$file"
  require_contains 'falsifier_id=latticra-identity-replay-model1-bounded-range-falsifier' "$file"
  require_contains 'falsifier_version=1' "$file"
  require_contains 'model1_runner_reference=tools/latticra_identity_replay_model1_substrate.py' "$file"
  require_contains 'model1_evaluator_reference=tools/latticra_identity_replay_model1_evaluate.py' "$file"
  require_contains 'range_falsifier_tool=tools/latticra_identity_replay_model1_range_falsifier.py' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'bounded_substrate_class_scope=Model-1 finite cyclic bounded-cell L1 repair substrate' "$file"
  require_contains 'width=17' "$file"
  require_contains 'max_cell_abs=2' "$file"
  require_contains 'repair_cost_unit=1' "$file"
  require_contains 'replay_horizon_N=16' "$file"
  require_contains 'epsilon_identity_tolerance=0' "$file"
  require_contains 'parameter_count=4' "$file"
  require_contains 'target_count=7' "$file"
  require_contains 'parameter_count_less_than_target_count=1' "$file"
  require_contains 'max_cell_delta=4' "$file"
  require_contains 'max_kappa_per_step=68' "$file"
  require_contains 'max_Z_L_under_bounded_repair=68' "$file"
  require_contains 'min_positive_horizon_mean=0.0625' "$file"
  require_contains 'max_ratio_bound_with_current_stationary_replay=68' "$file"
  require_contains 'max_ratio_bound_with_any_nonzero_horizon_mean=1088' "$file"
  require_contains 'target_max_ratio_to_electron=337691.49623497269417' "$file"
  require_contains 'target_ratio_exceeds_bounded_model1_range=1' "$file"
  require_contains 'model1_bounded_substrate_class_falsified=1' "$file"
  require_contains 'bounded_model1_conclusion=falsified_as_mass_ratio_recovery_candidate' "$file"
  require_contains 'required_next_substrate_property=hierarchical or multiscale impedance range before target-table recovery can be credible' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'higgs_only_causal_closure_challenged=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'falsifier_receipt_hash_generated=1' "$file"
done

for section in '## Purpose' '## Range Bound' '## Current Conclusion' '## Invocation' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'python3 tools/latticra_identity_replay_model1_range_falsifier.py' \
  'The finite bounded-cell Model-1 substrate class cannot recover the measured particle mass-ratio vector.' \
  'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' \
  'hierarchical impedance' \
  'multiscale replay cost'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$range_tool" "$prediction_tool" "$evaluation_tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-range-falsifier.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
receipt="$tmp_dir/range_falsifier.json"
python3 "$range_tool" --targets "$table" > "$receipt"

for pattern in \
  '"latticra_identity_replay_model1_bounded_range_falsifier_present": 1' \
  '"falsifier_id": "latticra-identity-replay-model1-bounded-range-falsifier"' \
  '"bounded_substrate_class_scope": "Model-1 finite cyclic bounded-cell L1 repair substrate"' \
  '"width": 17' \
  '"max_cell_abs": 2' \
  '"repair_cost_unit": 1' \
  '"replay_horizon_N": 16' \
  '"parameter_count": 4' \
  '"target_count": 7' \
  '"parameter_count_less_than_target_count": 1' \
  '"max_cell_delta": "4"' \
  '"max_kappa_per_step": "68"' \
  '"max_Z_L_under_bounded_repair": "68"' \
  '"min_positive_horizon_mean": "0.0625"' \
  '"max_ratio_bound_with_current_stationary_replay": "68"' \
  '"max_ratio_bound_with_any_nonzero_horizon_mean": "1088"' \
  '"target_max_ratio_to_electron": "337691.49623497269417"' \
  '"target_ratio_exceeds_bounded_model1_range": 1' \
  '"model1_bounded_substrate_class_falsified": 1' \
  '"bounded_model1_conclusion": "falsified_as_mass_ratio_recovery_candidate"' \
  '"candidate_promoted": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"standard_model_replacement_claimed": 0' \
  '"higgs_denied": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"falsifier_receipt_hash": "sha256:' \
  '"falsifier_receipt_hash_generated": 1'
do
  require_contains "$pattern" "$receipt"
done

python3 - "$receipt" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as handle:
    receipt = json.load(handle)

assert receipt["max_ratio_bound_with_any_nonzero_horizon_mean"] == "1088"
assert receipt["target_ratio_exceeds_bounded_model1_range"] == 1
assert receipt["model1_bounded_substrate_class_falsified"] == 1
assert receipt["bounded_model1_conclusion"] == "falsified_as_mass_ratio_recovery_candidate"
assert receipt["higgs_checkmate_claimed"] == 0
assert receipt["simulation_proven"] == 0
assert any(row["identity"] == "I_top" for row in receipt["targets_exceeding_bounded_range"])
PY

require_contains 'Model-1 Bounded Range Falsifier' "$model1_doc"
require_contains 'Model-1 Bounded Range Falsifier' "$model1_status"
require_contains 'Model-1 Bounded Range Falsifier' "$table"
require_contains 'Model-1 Bounded Range Falsifier' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER_STATUS.md' "$status_index"
require_contains 'Model-1 Bounded Range Falsifier' "$docs_hub"
require_contains 'Model-1 Bounded Range Falsifier](docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md)' "$root_readme"
require_contains 'Model-1 Bounded Range Falsifier](../LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md)' "$status_index"
require_contains 'Model-1 bounded range falsifier' "$handbook"
require_contains 'Latest Latticra identity-replay Model-1 bounded range falsifier note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-1 bounded range falsifier note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-1 bounded range falsifier note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-1 bounded range falsifier note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance Model-1 bounded range falsifier.' "$current_status"
require_contains 'Identity-replay impedance Model-1 bounded range falsifier.' "$current_direction"
require_contains 'Identity-replay impedance Model-1 bounded range falsifier.' "$upcoming_work"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$current_status"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$current_direction"
require_contains 'Identity-replay impedance Model-2 hierarchical substrate pre-registration.' "$upcoming_work"
require_contains 'latticra-identity-replay-model1-bounded-range-falsifier:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh' "$makefile"
require_contains 'latticra-identity-replay-model1-bounded-range-falsifier:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-1 bounded range falsifier guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh' "$workflow"

printf 'latticra_identity_replay_model1_bounded_range_falsifier: ok\n'
