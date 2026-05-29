#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra L5 blinded-holdout oracle evidence-review receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
from typing import Any

from latticra_identity_replay_l3_holdout_intake import load_oracle
from latticra_identity_replay_l4_execution_gate import build_receipt as build_l4_receipt


REQUIRED_EVIDENCE_FIELDS = [
    "oracle_id",
    "oracle_version",
    "pre_registration_receipt_hash",
    "source_reference",
    "source_cutoff_date",
    "reviewer_attestation",
]

SYNTHETIC_EVIDENCE_MARKERS = [
    "demo",
    "fixture",
    "local",
    "mock",
    "synthetic",
    "test",
]


def _nonempty_text(value: object) -> bool:
    return isinstance(value, str) and bool(value.strip())


def _contains_marker(value: object) -> bool:
    if not isinstance(value, str):
        return False
    lowered = value.casefold()
    return any(marker in lowered for marker in SYNTHETIC_EVIDENCE_MARKERS)


def review_evidence(
    oracle: dict[str, object] | None, l4_receipt: dict[str, Any]
) -> dict[str, object]:
    if oracle is None:
        return {
            "oracle_evidence_packet_received": 0,
            "evidence_review_performed": 0,
            "oracle_evidence_schema_review_passed": 0,
            "source_reference_present": 0,
            "source_cutoff_date_present": 0,
            "reviewer_attestation_present": 0,
            "synthetic_or_fixture_evidence_detected": 0,
            "evidence_externality_review_passed": 0,
            "evidence_review_failure_reasons": ["oracle_not_supplied"],
        }

    missing = [field for field in REQUIRED_EVIDENCE_FIELDS if field not in oracle]
    blank = [
        field
        for field in ("source_reference", "source_cutoff_date", "reviewer_attestation")
        if field in oracle and not _nonempty_text(oracle[field])
    ]
    synthetic_detected = any(
        _contains_marker(oracle.get(field))
        for field in ("oracle_id", "source_reference", "reviewer_attestation")
    )
    l4_execution_performed = l4_receipt["holdout_execution_performed"] == 1
    l4_evaluation_performed = l4_receipt["holdout_evaluation_performed"] == 1
    schema_review_passed = not missing and not blank
    externality_passed = schema_review_passed and not synthetic_detected
    evidence_passed = (
        externality_passed and l4_execution_performed and l4_evaluation_performed
    )

    failure_reasons = (
        missing
        + [f"blank_field:{field}" for field in blank]
        + ([] if not synthetic_detected else ["synthetic_or_fixture_evidence_detected"])
        + ([] if l4_execution_performed else ["l4_execution_not_performed"])
        + ([] if l4_evaluation_performed else ["l4_evaluation_not_performed"])
    )

    return {
        "oracle_evidence_packet_received": 1,
        "evidence_review_performed": 1,
        "oracle_evidence_schema_review_passed": int(schema_review_passed),
        "source_reference_present": int(_nonempty_text(oracle.get("source_reference"))),
        "source_cutoff_date_present": int(_nonempty_text(oracle.get("source_cutoff_date"))),
        "reviewer_attestation_present": int(
            _nonempty_text(oracle.get("reviewer_attestation"))
        ),
        "synthetic_or_fixture_evidence_detected": int(synthetic_detected),
        "evidence_externality_review_passed": int(evidence_passed),
        "evidence_review_failure_reasons": failure_reasons,
    }


def build_receipt(oracle_path: str | None = None) -> dict[str, Any]:
    l4_receipt = build_l4_receipt(oracle_path)
    oracle, oracle_state = load_oracle(oracle_path)
    review = review_evidence(oracle, l4_receipt)

    receipt: dict[str, Any] = {
        "latticra_identity_replay_impedance_l5_blinded_holdout_oracle_evidence_review_present": 1,
        "evidence_review_id": "latticra-identity-replay-impedance-l5-blinded-holdout-oracle-evidence-review",
        "evidence_review_version": 1,
        "l4_execution_gate_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md",
        "l4_execution_gate_receipt_hash": l4_receipt[
            "execution_gate_receipt_hash"
        ],
        "l3_intake_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md",
        "l3_intake_receipt_hash": l4_receipt["l3_intake_receipt_hash"],
        "l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md",
        "l2_pre_registration_receipt_hash": l4_receipt[
            "l2_pre_registration_receipt_hash"
        ],
        "l1_search_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "evidence_review_tool": "tools/latticra_identity_replay_l5_oracle_evidence_review.py",
        "oracle_evidence_review_defined": 1,
        "external_oracle_evidence_required": 1,
        "oracle_input_state": oracle_state,
        "required_evidence_fields": REQUIRED_EVIDENCE_FIELDS,
        "evidence_review_acceptance_rule": (
            "oracle supplied, L4 execution performed, required source fields "
            "present, no synthetic fixture markers"
        ),
        "l4_execution_receipt_available": 1,
        "oracle_received": l4_receipt["oracle_received"],
        "oracle_schema_valid": l4_receipt["oracle_schema_valid"],
        "holdout_execution_ready": l4_receipt["holdout_execution_ready"],
        "holdout_execution_performed": l4_receipt["holdout_execution_performed"],
        "holdout_evaluation_performed": l4_receipt["holdout_evaluation_performed"],
        "candidate_survives_blinded_holdout": l4_receipt[
            "candidate_survives_blinded_holdout"
        ],
        **review,
        "candidate_promoted": 0,
        "independent_reproduction_required": 1,
        "reproducibility_review_performed": 0,
        "precision_shadow_benchmark_required": 1,
        "precision_shadow_review_performed": 0,
        "new_prediction_required": 1,
        "new_prediction_review_performed": 0,
        "measured_masses_used_in_kappa": 0,
        "mass_ratio_recovery_claimed": 0,
        "standard_model_replacement_claimed": 0,
        "higgs_denied": 0,
        "higgs_checkmate_claimed": 0,
        "higgs_only_causal_closure_challenged": 1,
        "simulation_proven": 0,
        "reality_simulation_claimed": 0,
        "physics_bound_by_simulative_concepts_claimed": 0,
        "scientific_claim_promoted": 0,
        "non_claims": [
            "not_a_standard_model_replacement",
            "not_a_higgs_denial",
            "not_simulation_proof",
            "not_mass_ratio_recovery",
            "not_final_checkmate",
            "not_scientific_claim_promotion",
            "not_independent_reproduction",
        ],
    }
    if receipt["oracle_evidence_packet_received"] == 0:
        receipt["non_claims"].append("not_external_oracle_evidence")

    canonical = json.dumps(receipt, sort_keys=True, separators=(",", ":"))
    receipt["evidence_review_receipt_hash"] = "sha256:" + hashlib.sha256(
        canonical.encode("utf-8")
    ).hexdigest()
    receipt["evidence_review_receipt_hash_generated"] = 1
    return receipt


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--oracle", help="optional external blinded-holdout oracle JSON")
    args = parser.parse_args()
    print(json.dumps(build_receipt(args.oracle), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
