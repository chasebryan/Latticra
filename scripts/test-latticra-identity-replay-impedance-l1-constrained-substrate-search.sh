#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance l1 constrained substrate search: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH_STATUS.md'
l0_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l1_search.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-l1-constrained-substrate-search.yml'

for file in "$doc" "$status" "$l0_doc" "$table" "$proof_object_4" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_l1_constrained_substrate_search_present=1' "$file"
  require_contains 'search_id=latticra-identity-replay-impedance-l1-constrained-substrate-search' "$file"
  require_contains 'search_version=1' "$file"
  require_contains 'candidate_family_id=log-linear-small-integer-identity-feature-impedance' "$file"
  require_contains 'candidate_family_version=1' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'l0_runner_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md' "$file"
  require_contains 'search_tool=tools/latticra_identity_replay_l1_search.py' "$file"
  require_contains 'search_deterministic=1' "$file"
  require_contains 'target_guided_search_performed=1' "$file"
  require_contains 'targets_used_for_candidate_scoring=1' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'leave_one_out_validation_performed=1' "$file"
  require_contains 'receipt_hash_generated=1' "$file"
  require_contains 'overfit_risk_flag=1' "$file"
  require_contains 'candidate_survives_target_table=0' "$file"
  require_contains 'candidate_survives_leave_one_out=0' "$file"
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
  require_contains 'latticra_identity_replay_impedance_l1_constrained_substrate_search: ok' "$file"
done

for section in '## Candidate Family' '## Invocation' '## Anti-Smuggling Boundary' '## Current L1 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'log10(Z_L(I) / Z_L(I_e)) =' \
  'generation_lift' \
  'boundary_oscillation_load' \
  'python3 tools/latticra_identity_replay_l1_search.py' \
  'target_guided_search_performed=1' \
  'targets_used_for_candidate_scoring=1' \
  'candidate_survives_leave_one_out=0' \
  'L1 does not yet do that; it makes the failure measurable.' \
  'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l1-search-receipt.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/receipt.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_l1_constrained_substrate_search_present": 1' \
  '"search_id": "latticra-identity-replay-impedance-l1-constrained-substrate-search"' \
  '"candidate_family_id": "log-linear-small-integer-identity-feature-impedance"' \
  '"target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md"' \
  '"l0_runner_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md"' \
  '"proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md"' \
  '"search_deterministic": 1' \
  '"target_guided_search_performed": 1' \
  '"targets_used_for_candidate_scoring": 1' \
  '"measured_masses_used_in_kappa": 0' \
  '"leave_one_out_validation_performed": 1' \
  '"overfit_risk_flag": 1' \
  '"candidate_survives_target_table": 0' \
  '"candidate_survives_leave_one_out": 0' \
  '"candidate_promoted": 0' \
  '"mass_ratio_recovery_claimed": 0' \
  '"higgs_denied": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"higgs_only_causal_closure_challenged": 1' \
  '"simulation_proven": 0' \
  '"scientific_claim_promoted": 0' \
  '"receipt_hash": "sha256:' \
  '"receipt_hash_generated": 1' \
  '"best_weight_vector"' \
  '"generation_lift"' \
  '"leave_one_out"' \
  '"holdout_failure_record"' \
  '"not_final_checkmate"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'L1 Constrained Substrate Search' "$l0_doc"
require_contains 'L1 Constrained Substrate Search' "$table"
require_contains 'L1 Constrained Substrate Search' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH_STATUS.md' "$status_index"
require_contains 'L1 Constrained Substrate Search' "$docs_hub"
require_contains 'L1 Constrained Search](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md)' "$root_readme"
require_contains 'L1 Constrained Search](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md)' "$status_index"
require_contains 'L1 constrained substrate search' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L1 constrained substrate search note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L1 constrained substrate search note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L1 constrained substrate search note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L1 constrained substrate search note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$current_status"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$current_direction"
require_contains 'Identity-replay impedance L1 constrained substrate search.' "$upcoming_work"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$current_status"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$current_direction"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-l1-constrained-substrate-search:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-l1-constrained-substrate-search:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance L1 constrained substrate search guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh' "$workflow"

printf 'latticra_identity_replay_impedance_l1_constrained_substrate_search: ok\n'
