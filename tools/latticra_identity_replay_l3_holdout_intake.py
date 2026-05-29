#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra L3 external blinded-holdout intake receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

from latticra_identity_replay_l2_preregistration import build_receipt as build_l2_receipt


REQUIRED_ORACLE_FIELDS = [
    "oracle_id",
    "oracle_version",
    "pre_registration_receipt_hash",
    "holdout_identity",
    "holdout_feature_vector",
    "holdout_ratio_to_electron",
    "source_reference",
    "source_cutoff_date",
    "oracle_opened_after_pre_registration",
    "reviewer_attestation",
]


def load_oracle(path: str | None) -> tuple[dict[str, object] | None, str]:
    if path is None:
        return None, "oracle_not_supplied"
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    if not isinstance(data, dict):
        raise ValueError("oracle must be a JSON object")
    return data, "oracle_supplied"


def oracle_validation(oracle: dict[str, object] | None, expected_hash: str) -> dict[str, object]:
    if oracle is None:
        return {
            "external_blinded_holdout_oracle_received": 0,
            "oracle_validation_performed": 0,
            "oracle_schema_valid": 0,
            "oracle_receipt_hash_matches_pre_registration": 0,
            "oracle_opened_after_pre_registration": 0,
            "holdout_values_available_to_runner": 0,
            "oracle_failure_reasons": ["oracle_not_supplied"],
        }

    missing = [field for field in REQUIRED_ORACLE_FIELDS if field not in oracle]
    hash_matches = oracle.get("pre_registration_receipt_hash") == expected_hash
    opened_after = oracle.get("oracle_opened_after_pre_registration") is True
    schema_valid = not missing and hash_matches and opened_after
    return {
        "external_blinded_holdout_oracle_received": 1,
        "oracle_validation_performed": 1,
        "oracle_schema_valid": int(schema_valid),
        "oracle_receipt_hash_matches_pre_registration": int(hash_matches),
        "oracle_opened_after_pre_registration": int(opened_after),
        "holdout_values_available_to_runner": int(schema_valid),
        "oracle_failure_reasons": missing
        + ([] if hash_matches else ["pre_registration_receipt_hash_mismatch"])
        + ([] if opened_after else ["oracle_not_opened_after_pre_registration"]),
    }


def build_receipt(oracle_path: str | None = None) -> dict[str, object]:
    l2_receipt = build_l2_receipt()
    expected_hash = str(l2_receipt["pre_registration_receipt_hash"])
    oracle, oracle_state = load_oracle(oracle_path)
    validation = oracle_validation(oracle, expected_hash)
    holdout_ready = bool(validation["holdout_values_available_to_runner"])

    receipt = {
        "latticra_identity_replay_impedance_l3_external_blinded_holdout_intake_present": 1,
        "intake_id": "latticra-identity-replay-impedance-l3-external-blinded-holdout-intake",
        "intake_version": 1,
        "l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md",
        "l2_pre_registration_receipt_hash": expected_hash,
        "l1_search_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "intake_tool": "tools/latticra_identity_replay_l3_holdout_intake.py",
        "external_blinded_holdout_intake_defined": 1,
        "external_blinded_holdout_oracle_required": 1,
        "oracle_input_state": oracle_state,
        "required_oracle_fields": REQUIRED_ORACLE_FIELDS,
        "holdout_execution_ready": int(holdout_ready),
        "holdout_evaluation_performed": 0,
        "candidate_survives_blinded_holdout": 0,
        "candidate_promoted": 0,
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
        **validation,
        "non_claims": [
            "not_a_standard_model_replacement",
            "not_a_higgs_denial",
            "not_simulation_proof",
            "not_mass_ratio_recovery",
            "not_final_checkmate",
            "not_blinded_holdout_success",
            "not_holdout_execution",
        ],
    }
    canonical = json.dumps(receipt, sort_keys=True, separators=(",", ":"))
    receipt["intake_receipt_hash"] = "sha256:" + hashlib.sha256(
        canonical.encode("utf-8")
    ).hexdigest()
    receipt["intake_receipt_hash_generated"] = 1
    return receipt


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--oracle", help="optional external blinded-holdout oracle JSON")
    args = parser.parse_args()
    print(json.dumps(build_receipt(args.oracle), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
