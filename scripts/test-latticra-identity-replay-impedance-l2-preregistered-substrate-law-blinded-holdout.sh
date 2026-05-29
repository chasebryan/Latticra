#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance l2 preregistered substrate law blinded holdout: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT_STATUS.md'
l1_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md'
l0_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l2_preregistration.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.yml'

for file in "$doc" "$status" "$l1_doc" "$l0_doc" "$table" "$proof_object_4" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout_present=1' "$file"
  require_contains 'pre_registration_id=latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout' "$file"
  require_contains 'pre_registration_version=1' "$file"
  require_contains 'candidate_law_id=identity-replay-impedance-l2-preregistered-log-linear-law' "$file"
  require_contains 'candidate_law_version=1' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'l1_search_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md' "$file"
  require_contains 'l0_runner_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'pre_registration_tool=tools/latticra_identity_replay_l2_preregistration.py' "$file"
  require_contains 'pre_registered_law_present=1' "$file"
  require_contains 'pre_registration_receipt_hash_generated=1' "$file"
  require_contains 'blinded_holdout_protocol_defined=1' "$file"
  require_contains 'blinded_holdout_oracle_required=1' "$file"
  require_contains 'blinded_holdout_oracle_present=0' "$file"
  require_contains 'blinded_holdout_values_available_to_runner=0' "$file"
  require_contains 'holdout_evaluation_performed=0' "$file"
  require_contains 'candidate_survives_blinded_holdout=0' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'l1_target_guided_context_inherited=1' "$file"
  require_contains 'law_independence_from_prior_targets_proven=0' "$file"
  require_contains 'oracle_opened_after_pre_registration=0' "$file"
  require_contains 'measured_masses_used_in_kappa=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'higgs_only_causal_closure_challenged=1' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout: ok' "$file"
done

for section in '## Pre-Registered Law' '## Blinded Holdout Protocol' '## Invocation' '## Current L2 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'log10(Z_L(I) / Z_L(I_e)) = dot(w, phi(I)) / 10' \
  'l1_target_guided_context_inherited=1' \
  'law_independence_from_prior_targets_proven=0' \
  'oracle_id' \
  'holdout_ratio_to_electron' \
  'python3 tools/latticra_identity_replay_l2_preregistration.py' \
  'This is still progress. It creates the first hard gate where future proof language has to pass an independent target opening instead of reusing known masses.' \
  'Identity-replay impedance L3 external blinded-holdout intake.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l2-preregistration-receipt.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/receipt.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout_present": 1' \
  '"pre_registration_id": "latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout"' \
  '"candidate_law_id": "identity-replay-impedance-l2-preregistered-log-linear-law"' \
  '"target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md"' \
  '"l1_search_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md"' \
  '"l0_runner_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md"' \
  '"proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md"' \
  '"pre_registered_law_present": 1' \
  '"pre_registration_receipt_hash": "sha256:' \
  '"pre_registration_receipt_hash_generated": 1' \
  '"blinded_holdout_protocol_defined": 1' \
  '"blinded_holdout_oracle_required": 1' \
  '"blinded_holdout_oracle_present": 0' \
  '"blinded_holdout_values_available_to_runner": 0' \
  '"holdout_evaluation_performed": 0' \
  '"candidate_survives_blinded_holdout": 0' \
  '"candidate_promoted": 0' \
  '"l1_target_guided_context_inherited": 1' \
  '"law_independence_from_prior_targets_proven": 0' \
  '"oracle_opened_after_pre_registration": 0' \
  '"measured_masses_used_in_kappa": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"not_blinded_holdout_success"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'L2 Pre-Registered Substrate Law With Blinded Holdout' "$l1_doc"
require_contains 'L2 Pre-Registered Substrate Law With Blinded Holdout' "$l0_doc"
require_contains 'L2 Pre-Registered Substrate Law With Blinded Holdout' "$table"
require_contains 'L2 Pre-Registered Substrate Law With Blinded Holdout' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT_STATUS.md' "$status_index"
require_contains 'L2 Pre-Registered Substrate Law With Blinded Holdout' "$docs_hub"
require_contains 'L2 Pre-Registered Holdout](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md)' "$root_readme"
require_contains 'L2 Pre-Registered Holdout](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md)' "$status_index"
require_contains 'L2 pre-registration gate' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L2 pre-registered holdout note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L2 pre-registered holdout note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L2 pre-registered holdout note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L2 pre-registered holdout note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$current_status"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$current_direction"
require_contains 'Identity-replay impedance L2 pre-registered substrate law with blinded holdout.' "$upcoming_work"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$current_status"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$current_direction"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance L2 pre-registered substrate law blinded holdout guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh' "$workflow"

printf 'latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout: ok\n'
