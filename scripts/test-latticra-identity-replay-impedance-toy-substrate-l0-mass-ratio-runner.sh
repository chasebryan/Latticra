#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance toy substrate l0 mass ratio runner: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER_STATUS.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l0_runner.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.yml'

for file in "$doc" "$status" "$table" "$proof_object_4" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_toy_substrate_l0_mass_ratio_runner_present=1' "$file"
  require_contains 'runner_id=latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner' "$file"
  require_contains 'runner_version=1' "$file"
  require_contains 'candidate_substrate_id=identity-replay-impedance-toy-l0' "$file"
  require_contains 'candidate_substrate_version=1' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'runner_tool=tools/latticra_identity_replay_l0_runner.py' "$file"
  require_contains 'toy_substrate_l0_runner_executes=1' "$file"
  require_contains 'receipt_generation_required=1' "$file"
  require_contains 'receipt_hash_generated=1' "$file"
  require_contains 'toy_Z_L_values_computed=1' "$file"
  require_contains 'toy_mass_ratio_predictions_computed=1' "$file"
  require_contains 'target_error_vector_computed=1' "$file"
  require_contains 'candidate_survives_target_table=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_identity_replay_impedance_toy_substrate_l0_mass_ratio_runner: ok' "$file"
done

for section in '## L0 Substrate Definition' '## Invocation' '## Anti-Smuggling Result' '## Current L0 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'L0 = (S0, T0, O0, Q0, d0, kappa0, R0)' \
  'kappa0 = toy_impedance(identity_features)' \
  'python3 tools/latticra_identity_replay_l0_runner.py' \
  'target_values_loaded_after_predictions=1' \
  'measured_masses_used_in_kappa=0' \
  'That failure is valuable. It proves the lane has a candidate-killing surface instead of a story-only surface.' \
  'L0 does not defeat Higgs. L0 defines the executable gate a future Latticra candidate must pass before public proof language is allowed.' \
  'Identity-replay impedance L1 constrained substrate search.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l0-runner-receipt.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/receipt.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_toy_substrate_l0_mass_ratio_runner_present": 1' \
  '"runner_id": "latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner"' \
  '"candidate_substrate_id": "identity-replay-impedance-toy-l0"' \
  '"target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md"' \
  '"proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md"' \
  '"counterfactual_repair_cost_function": "toy_impedance(identity_features)"' \
  '"target_values_loaded_after_predictions": 1' \
  '"measured_masses_used_in_kappa": 0' \
  '"toy_Z_L_values_computed": 1' \
  '"toy_mass_ratio_predictions_computed": 1' \
  '"target_error_vector_computed": 1' \
  '"candidate_survives_target_table": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"standard_model_replacement_claimed": 0' \
  '"higgs_denied": 0' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"receipt_hash": "sha256:' \
  '"receipt_hash_generated": 1' \
  '"identity": "I_e"' \
  '"identity": "I_mu"' \
  '"identity": "I_tau"' \
  '"identity": "I_W"' \
  '"identity": "I_Z"' \
  '"identity": "I_H"' \
  '"identity": "I_top"' \
  '"top_over_Higgs"' \
  '"not_mass_ratio_recovery"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'Toy Substrate L0 Mass-Ratio Runner' "$table"
require_contains 'Toy Substrate L0 Mass-Ratio Runner' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER_STATUS.md' "$status_index"
require_contains 'Toy Substrate L0 Mass-Ratio Runner' "$docs_hub"
require_contains 'L0 Mass-Ratio Runner](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md)' "$root_readme"
require_contains 'L0 Mass-Ratio Runner](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md)' "$status_index"
require_contains 'L0 mass-ratio runner' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L0 mass-ratio runner note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L0 mass-ratio runner note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L0 mass-ratio runner note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L0 mass-ratio runner note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$current_status"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$current_direction"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$upcoming_work"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$current_status"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$current_direction"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance toy substrate L0 mass-ratio runner guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner.sh' "$workflow"

printf 'latticra_identity_replay_impedance_toy_substrate_l0_mass_ratio_runner: ok\n'
