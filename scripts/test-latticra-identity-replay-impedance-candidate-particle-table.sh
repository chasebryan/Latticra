#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance candidate particle table: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE_STATUS.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
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
workflow='.github/workflows/latticra-identity-replay-impedance-candidate-particle-table.yml'

for file in "$doc" "$status" "$proof_object_4" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_candidate_particle_table_present=1' "$file"
  require_contains 'candidate_table_id=latticra-identity-replay-impedance-candidate-particle-table' "$file"
  require_contains 'candidate_table_version=1' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'source_reference=pdg_2025_update_summary_tables' "$file"
  require_contains 'source_cutoff_date=2025-01-15' "$file"
  require_contains 'mass_target_snapshot_date=2026-05-29' "$file"
  require_contains 'measured_mass_ratio_targets_present=1' "$file"
  require_contains 'candidate_identity_classes_named=1' "$file"
  require_contains 'ledger_computation_performed=0' "$file"
  require_contains 'identity_replay_impedance_values_computed=0' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'standard_model_replacement_claimed=0' "$file"
  require_contains 'higgs_denied=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'reality_simulation_claimed=0' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
  require_contains 'latticra_identity_replay_impedance_candidate_particle_table: ok' "$file"
done

for section in '## External Source Anchors' '## Anti-Smuggling Rule' '## Candidate Identity Targets' '## Cross-Ratio Targets' '## What A Later Runner Must Emit' '## Falsifier Conditions' '## Higgs Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'pdg_summary_tables_url=https://pdg.lbl.gov/2025/tables/contents_tables.html' \
  'pdg_lepton_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-leptons.pdf' \
  'pdg_gauge_higgs_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-gauge-higgs-bosons.pdf' \
  'pdg_quark_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-quarks.pdf' \
  'If the measured masses are used to tune the ledger after target inspection, the candidate fails this table.' \
  '| electron | `I_e` | `0.51099895000` | `1` | `Z_L(I_e)=uncomputed` | anchor target for ratio-only comparison |' \
  '| muon | `I_mu` | `105.6583755` | `206.76828298766563023` | `Z_L(I_mu)=uncomputed` | `Z_L(I_mu)/Z_L(I_e)` |' \
  '| tau | `I_tau` | `1776.93` | `3477.36526660181982761` | `Z_L(I_tau)=uncomputed` | `Z_L(I_tau)/Z_L(I_e)` |' \
  '| W boson | `I_W` | `80369.2` | `157278.60106170472562` | `Z_L(I_W)=uncomputed` | `Z_L(I_W)/Z_L(I_e)` |' \
  '| Z boson | `I_Z` | `91188.0` | `178450.46452639481940` | `Z_L(I_Z)=uncomputed` | `Z_L(I_Z)/Z_L(I_e)` |' \
  '| Higgs boson | `I_H` | `125200` | `245010.28818160976652` | `Z_L(I_H)=uncomputed` | `Z_L(I_H)/Z_L(I_e)` |' \
  '| top quark | `I_top` | `172560` | `337691.49623497269417` | `Z_L(I_top)=uncomputed` | `Z_L(I_top)/Z_L(I_e)` |' \
  'tau_over_muon_target=16.81769184497825257592' \
  'W_over_Z_target=0.88135719612229679344' \
  'Higgs_over_Z_target=1.37298767381673027153' \
  'top_over_Higgs_target=1.37827476038338658147' \
  'ratio_fit_requires_measured_mass_insertion' \
  'free_parameter_count_exceeds_observable_compression' \
  'mass_ratio_recovery_mismatch_exceeds_epsilon_after_model_fixed' \
  'higgs_coupling_shadow_test_fails' \
  'Identity-replay impedance toy substrate L0 mass-ratio runner.'
do
  require_contains "$pattern" "$doc"
done

require_contains 'Identity-replay impedance candidate particle table' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE_STATUS.md' "$status_index"
require_contains 'Identity-Replay Impedance Candidate Particle Table' "$docs_hub"
require_contains 'Candidate Particle Table](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md)' "$root_readme"
require_contains 'Candidate Particle Table](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md)' "$status_index"
require_contains 'candidate-particle target table' "$handbook"
require_contains 'Latest Latticra identity-replay impedance candidate particle table note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance candidate particle table note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance candidate particle table note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance candidate particle table note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance candidate particle table.' "$current_status"
require_contains 'Identity-replay impedance candidate particle table.' "$current_direction"
require_contains 'Identity-replay impedance candidate particle table.' "$upcoming_work"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$current_status"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$current_direction"
require_contains 'Identity-replay impedance toy substrate L0 mass-ratio runner.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-candidate-particle-table:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-candidate-particle-table:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance candidate particle table guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh' "$workflow"

printf 'latticra_identity_replay_impedance_candidate_particle_table: ok\n'
