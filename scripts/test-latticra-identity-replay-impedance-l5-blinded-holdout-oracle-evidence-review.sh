#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay impedance l5 blinded holdout oracle evidence review: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW_STATUS.md'
l4_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md'
l3_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md'
l2_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md'
l1_doc='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md'
table='docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md'
proof_object_4='docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md'
tool='tools/latticra_identity_replay_l5_oracle_evidence_review.py'
l2_tool='tools/latticra_identity_replay_l2_preregistration.py'
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
workflow='.github/workflows/latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.yml'

for file in "$doc" "$status" "$l4_doc" "$l3_doc" "$l2_doc" "$l1_doc" "$table" "$proof_object_4" "$tool" "$l2_tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_impedance_l5_blinded_holdout_oracle_evidence_review_present=1' "$file"
  require_contains 'evidence_review_id=latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review' "$file"
  require_contains 'evidence_review_version=1' "$file"
  require_contains 'l4_execution_gate_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md' "$file"
  require_contains 'l3_intake_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md' "$file"
  require_contains 'l2_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md' "$file"
  require_contains 'l1_search_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md' "$file"
  require_contains 'target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md' "$file"
  require_contains 'proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md' "$file"
  require_contains 'evidence_review_tool=tools/latticra_identity_replay_l5_oracle_evidence_review.py' "$file"
  require_contains 'oracle_evidence_review_defined=1' "$file"
  require_contains 'external_oracle_evidence_required=1' "$file"
  require_contains 'oracle_evidence_packet_received=0' "$file"
  require_contains 'evidence_review_performed=0' "$file"
  require_contains 'oracle_evidence_schema_review_passed=0' "$file"
  require_contains 'source_reference_present=0' "$file"
  require_contains 'source_cutoff_date_present=0' "$file"
  require_contains 'reviewer_attestation_present=0' "$file"
  require_contains 'synthetic_or_fixture_evidence_detected=0' "$file"
  require_contains 'evidence_externality_review_passed=0' "$file"
  require_contains 'l4_execution_receipt_available=1' "$file"
  require_contains 'holdout_execution_ready=0' "$file"
  require_contains 'holdout_execution_performed=0' "$file"
  require_contains 'holdout_evaluation_performed=0' "$file"
  require_contains 'candidate_survives_blinded_holdout=0' "$file"
  require_contains 'candidate_promoted=0' "$file"
  require_contains 'independent_reproduction_required=1' "$file"
  require_contains 'reproducibility_review_performed=0' "$file"
  require_contains 'precision_shadow_benchmark_required=1' "$file"
  require_contains 'precision_shadow_review_performed=0' "$file"
  require_contains 'new_prediction_required=1' "$file"
  require_contains 'new_prediction_review_performed=0' "$file"
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
  require_contains 'evidence_review_receipt_hash_generated=1' "$file"
  require_contains 'latticra_identity_replay_impedance_l5_blinded_holdout_oracle_evidence_review: ok' "$file"
done

for section in '## Evidence Rule' '## Invocation' '## Current L5 Result' '## Higgs Checkmate Boundary' '## Next Recommended Lane' '## Non-Claims'
do
  require_contains "$section" "$doc"
done

for pattern in \
  'oracle supplied, L4 execution performed, required source fields present, no synthetic fixture markers' \
  'python3 tools/latticra_identity_replay_l5_oracle_evidence_review.py' \
  'python3 tools/latticra_identity_replay_l5_oracle_evidence_review.py --oracle path/to/oracle.json' \
  'This is a stronger checkpoint than L4 because it separates execution success from evidence legitimacy.' \
  'Identity-replay impedance L6 independent holdout reproduction gate.'
do
  require_contains "$pattern" "$doc"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-l5-evidence-review.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/evidence_review.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_identity_replay_impedance_l5_blinded_holdout_oracle_evidence_review_present": 1' \
  '"evidence_review_id": "latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review"' \
  '"l4_execution_gate_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md"' \
  '"l4_execution_gate_receipt_hash": "sha256:' \
  '"l3_intake_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md"' \
  '"l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md"' \
  '"evidence_review_tool": "tools/latticra_identity_replay_l5_oracle_evidence_review.py"' \
  '"oracle_evidence_review_defined": 1' \
  '"external_oracle_evidence_required": 1' \
  '"oracle_evidence_packet_received": 0' \
  '"evidence_review_performed": 0' \
  '"oracle_evidence_schema_review_passed": 0' \
  '"synthetic_or_fixture_evidence_detected": 0' \
  '"evidence_externality_review_passed": 0' \
  '"l4_execution_receipt_available": 1' \
  '"holdout_execution_performed": 0' \
  '"holdout_evaluation_performed": 0' \
  '"candidate_survives_blinded_holdout": 0' \
  '"candidate_promoted": 0' \
  '"independent_reproduction_required": 1' \
  '"reproducibility_review_performed": 0' \
  '"precision_shadow_benchmark_required": 1' \
  '"precision_shadow_review_performed": 0' \
  '"new_prediction_required": 1' \
  '"new_prediction_review_performed": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"simulation_proven": 0' \
  '"evidence_review_receipt_hash": "sha256:' \
  '"evidence_review_receipt_hash_generated": 1' \
  '"oracle_not_supplied"' \
  '"not_external_oracle_evidence"'
do
  require_contains "$pattern" "$tmp"
done

synthetic_oracle="$tmp_dir/synthetic_oracle.json"
python3 - "$synthetic_oracle" <<'PY'
import json
import sys
from pathlib import Path

sys.path.insert(0, "tools")
from latticra_identity_replay_l2_preregistration import build_receipt

l2 = build_receipt()
law = l2["candidate_law"]
oracle = {
    "oracle_id": "synthetic-local-fixture-oracle",
    "oracle_version": 1,
    "pre_registration_receipt_hash": l2["pre_registration_receipt_hash"],
    "holdout_identity": "synthetic_zero_feature_identity",
    "holdout_feature_vector": {name: 0 for name in law["basis_names"]},
    "holdout_ratio_to_electron": 1.0,
    "source_reference": "local synthetic fixture; not external evidence",
    "source_cutoff_date": "2026-05-29",
    "oracle_opened_after_pre_registration": True,
    "reviewer_attestation": "synthetic smoke test only",
}
Path(sys.argv[1]).write_text(json.dumps(oracle, sort_keys=True), encoding="utf-8")
PY

synthetic_tmp="$tmp_dir/synthetic_evidence_review.json"
python3 "$tool" --oracle "$synthetic_oracle" > "$synthetic_tmp"

for pattern in \
  '"oracle_evidence_packet_received": 1' \
  '"evidence_review_performed": 1' \
  '"oracle_evidence_schema_review_passed": 1' \
  '"holdout_execution_performed": 1' \
  '"holdout_evaluation_performed": 1' \
  '"candidate_survives_blinded_holdout": 1' \
  '"synthetic_or_fixture_evidence_detected": 1' \
  '"evidence_externality_review_passed": 0' \
  '"candidate_promoted": 0' \
  '"higgs_checkmate_claimed": 0' \
  '"scientific_claim_promoted": 0' \
  '"synthetic_or_fixture_evidence_detected"'
do
  require_contains "$pattern" "$synthetic_tmp"
done

require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$l4_doc"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$l3_doc"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$l2_doc"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$l1_doc"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$table"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$proof_object_4"
require_contains 'LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW_STATUS.md' "$status_index"
require_contains 'L5 Blinded-Holdout Oracle Evidence Review' "$docs_hub"
require_contains 'L5 Evidence Review](docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW.md)' "$root_readme"
require_contains 'L5 Evidence Review](../LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L5_BLINDED_HOLDOUT_ORACLE_EVIDENCE_REVIEW.md)' "$status_index"
require_contains 'L5 blinded-holdout oracle evidence-review gate' "$handbook"
require_contains 'Latest Latticra identity-replay impedance L5 evidence review note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay impedance L5 evidence review note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay impedance L5 evidence review note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay impedance L5 evidence review note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$current_status"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$current_direction"
require_contains 'Identity-replay impedance L5 blinded-holdout oracle evidence review.' "$upcoming_work"
require_contains 'Identity-replay impedance L6 independent holdout reproduction gate.' "$current_status"
require_contains 'Identity-replay impedance L6 independent holdout reproduction gate.' "$current_direction"
require_contains 'Identity-replay impedance L6 independent holdout reproduction gate.' "$upcoming_work"
require_contains 'latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.sh' "$makefile"
require_contains 'latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay impedance L5 blinded-holdout oracle evidence review guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review.sh' "$workflow"

printf 'latticra_identity_replay_impedance_l5_blinded_holdout_oracle_evidence_review: ok\n'
