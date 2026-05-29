#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance l3 external blinded holdout intake: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE_STATUS.md'
l2_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md'
l1_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l3_holdout_intake.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.yml'

for file in "$doc" "$status" "$l2_doc" "$l1_doc" "$table" "$proof_object_4" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_l3_external_blinded_holdout_intake_present=1' "$file"
  require_contains 'intake_id=latticra-identity-replay-impedance-l3-external-blinded-holdout-intake' "$file"
  require_contains 'intake_version=1' "$file"
  require_contains 'l2_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md' "$file"
  require_contains 'l1_search_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'intake_tool=tools/latticra_identity_replay_l3_holdout_intake.py' "$file"
  require_contains 'external_blinded_holdout_intake_defined=1' "$file"
  require_contains 'external_blinded_holdout_oracle_required=1' "$file"
  require_contains 'external_blinded_holdout_oracle_received=0' "$file"
  require_contains 'oracle_validation_performed=0' "$file"
  require_contains 'oracle_schema_valid=0' "$file"
  require_contains 'oracle_receipt_hash_matches_pre_registration=0' "$file"
  require_contains 'oracle_opened_after_pre_registration=0' "$file"
  require_contains 'holdout_values_available_to_runner=0' "$file"
  require_contains 'holdout_execution_ready=0' "$file"
  require_contains 'holdout_evaluation_performed=0' "$file"
  require_contains 'candidate_survives_blinded_holdout=0' "$file"
  require_contains 'candidate_promoted=0' "$file"
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
  require_contains 'intake_receipt_hash_generated=1' "$file"
  require_contains 'latticra_identity_replay_impedance_l3_external_blinded_holdout_intake: ok' "$file"
done

for section in '## Required Oracle Fields' '## Invocation' '## Current L3 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'pre_registration_receipt_hash' \
  'holdout_ratio_to_electron' \
  'python3 tools/latticra_identity_replay_l3_holdout_intake.py' \
  'python3 tools/latticra_identity_replay_l3_holdout_intake.py --oracle path/to/oracle.json' \
  'This is a validated checkpoint because it makes the next proof step externally auditable. It does not provide the hidden target.' \
  'Identity-replay impedance L4 blinded-holdout execution gate.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l3-holdout-intake.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/intake.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_l3_external_blinded_holdout_intake_present": 1' \
  '"intake_id": "latticra-identity-replay-impedance-l3-external-blinded-holdout-intake"' \
  '"l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md"' \
  '"l2_pre_registration_receipt_hash": "sha256:' \
  '"intake_tool": "tools/latticra_identity_replay_l3_holdout_intake.py"' \
  '"external_blinded_holdout_intake_defined": 1' \
  '"external_blinded_holdout_oracle_required": 1' \
  '"external_blinded_holdout_oracle_received": 0' \
  '"oracle_validation_performed": 0' \
  '"oracle_schema_valid": 0' \
  '"oracle_receipt_hash_matches_pre_registration": 0' \
  '"oracle_opened_after_pre_registration": 0' \
  '"holdout_values_available_to_runner": 0' \
  '"holdout_execution_ready": 0' \
  '"holdout_evaluation_performed": 0' \
  '"candidate_survives_blinded_holdout": 0' \
  '"candidate_promoted": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"intake_receipt_hash": "sha256:' \
  '"intake_receipt_hash_generated": 1' \
  '"oracle_not_supplied"' \
  '"not_holdout_execution"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'L3 External Blinded-Holdout Intake' "$l2_doc"
require_contains 'L3 External Blinded-Holdout Intake' "$l1_doc"
require_contains 'L3 External Blinded-Holdout Intake' "$table"
require_contains 'L3 External Blinded-Holdout Intake' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE_STATUS.md' "$status_index"
require_contains 'L3 External Blinded-Holdout Intake' "$docs_hub"
require_contains 'L3 Holdout Intake](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md)' "$root_readme"
require_contains 'L3 Holdout Intake](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md)' "$status_index"
require_contains 'L3 external blinded-holdout intake validator' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L3 holdout intake note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L3 holdout intake note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L3 holdout intake note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L3 holdout intake note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$current_status"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$current_direction"
require_contains 'Identity-replay impedance L3 external blinded-holdout intake.' "$upcoming_work"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$current_status"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$current_direction"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-l3-external-blinded-holdout-intake:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-l3-external-blinded-holdout-intake:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance L3 external blinded-holdout intake guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-l3-external-blinded-holdout-intake.sh' "$workflow"

printf 'latticra_identity_replay_impedance_l3_external_blinded_holdout_intake: ok\n'
