#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance l4 blinded holdout execution gate: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE_STATUS.md'
l3_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md'
l2_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md'
l1_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l4_execution_gate.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.yml'

for file in "$doc" "$status" "$l3_doc" "$l2_doc" "$l1_doc" "$table" "$proof_object_4" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_l4_blinded_holdout_execution_gate_present=1' "$file"
  require_contains 'execution_gate_id=latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate' "$file"
  require_contains 'execution_gate_version=1' "$file"
  require_contains 'l3_intake_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md' "$file"
  require_contains 'l2_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md' "$file"
  require_contains 'l1_search_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'execution_gate_tool=tools/latticra_identity_replay_l4_execution_gate.py' "$file"
  require_contains 'execution_gate_defined=1' "$file"
  require_contains 'oracle_required=1' "$file"
  require_contains 'external_blinded_holdout_oracle_required=1' "$file"
  require_contains 'oracle_received=0' "$file"
  require_contains 'oracle_validation_performed=0' "$file"
  require_contains 'oracle_schema_valid=0' "$file"
  require_contains 'oracle_receipt_hash_matches_pre_registration=0' "$file"
  require_contains 'oracle_opened_after_pre_registration=0' "$file"
  require_contains 'execution_inputs_valid=0' "$file"
  require_contains 'holdout_execution_ready=0' "$file"
  require_contains 'holdout_execution_performed=0' "$file"
  require_contains 'holdout_evaluation_performed=0' "$file"
  require_contains 'candidate_survives_blinded_holdout=0' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'review_required_before_promotion=1' "$file"
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
  require_contains 'execution_gate_receipt_hash_generated=1' "$file"
  require_contains 'latticra_identity_replay_impedance_l4_blinded_holdout_execution_gate: ok' "$file"
done

for section in '## Execution Rule' '## Invocation' '## Current L4 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'abs(log10(predicted_ratio_to_electron) - log10(observed_holdout_ratio_to_electron)) <= 0.05' \
  'python3 tools/latticra_identity_replay_l4_execution_gate.py' \
  'python3 tools/latticra_identity_replay_l4_execution_gate.py --oracle path/to/oracle.json' \
  'This is a stronger checkpoint than L3 because it defines the actual execution rule' \
  'Identity-replay impedance L5 blinded-holdout oracle evidence review.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l4-execution-gate.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/execution_gate.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_l4_blinded_holdout_execution_gate_present": 1' \
  '"execution_gate_id": "latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate"' \
  '"l3_intake_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md"' \
  '"l3_intake_receipt_hash": "sha256:' \
  '"l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md"' \
  '"l2_pre_registration_receipt_hash": "sha256:' \
  '"execution_gate_tool": "tools/latticra_identity_replay_l4_execution_gate.py"' \
  '"execution_gate_defined": 1' \
  '"oracle_required": 1' \
  '"external_blinded_holdout_oracle_required": 1' \
  '"oracle_received": 0' \
  '"oracle_validation_performed": 0' \
  '"oracle_schema_valid": 0' \
  '"oracle_receipt_hash_matches_pre_registration": 0' \
  '"oracle_opened_after_pre_registration": 0' \
  '"execution_inputs_valid": 0' \
  '"holdout_execution_ready": 0' \
  '"holdout_execution_performed": 0' \
  '"holdout_evaluation_performed": 0' \
  '"candidate_survives_blinded_holdout": 0' \
  '"candidate_promoted": 0' \
  '"review_required_before_promotion": 1' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"execution_gate_receipt_hash": "sha256:' \
  '"execution_gate_receipt_hash_generated": 1' \
  '"oracle_not_supplied"' \
  '"not_holdout_execution"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'L4 Blinded-Holdout Execution Gate' "$l3_doc"
require_contains 'L4 Blinded-Holdout Execution Gate' "$l2_doc"
require_contains 'L4 Blinded-Holdout Execution Gate' "$l1_doc"
require_contains 'L4 Blinded-Holdout Execution Gate' "$table"
require_contains 'L4 Blinded-Holdout Execution Gate' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE_STATUS.md' "$status_index"
require_contains 'L4 Blinded-Holdout Execution Gate' "$docs_hub"
require_contains 'L4 Execution Gate](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md)' "$root_readme"
require_contains 'L4 Execution Gate](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md)' "$status_index"
require_contains 'L4 blinded-holdout execution gate' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L4 execution gate note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L4 execution gate note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L4 execution gate note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L4 execution gate note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$current_status"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$current_direction"
require_contains 'Identity-replay impedance L4 blinded-holdout execution gate.' "$upcoming_work"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$current_status"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$current_direction"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance L4 blinded-holdout execution gate guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate.sh' "$workflow"

printf 'latticra_identity_replay_impedance_l4_blinded_holdout_execution_gate: ok\n'
