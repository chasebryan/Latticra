#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra L4 blinded-holdout execution-gate receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
from typing import Any

from latticra_identity_replay_l2_preregistration import build_receipt as build_l2_receipt
from latticra_identity_replay_l3_holdout_intake import (
    build_receipt as build_l3_receipt,
    load_oracle,
)


EXECUTION_TOLERANCE_LOG10_ABS_ERROR = 0.05


def _is_number(value: object) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool)


def validate_execution_inputs(
    oracle: dict[str, object] | None, basis_names: list[str]
) -> dict[str, object]:
    if oracle is None:
        return {
            "execution_inputs_valid": 0,
            "execution_input_failure_reasons": ["oracle_not_supplied"],
        }

    feature_vector = oracle.get("holdout_feature_vector")
    ratio = oracle.get("holdout_ratio_to_electron")
    failures: list[str] = []

    if not isinstance(feature_vector, dict):
        failures.append("holdout_feature_vector_not_object")
    else:
        missing = [name for name in basis_names if name not in feature_vector]
        non_numeric = [
            name
            for name in basis_names
            if name in feature_vector and not _is_number(feature_vector[name])
        ]
        failures.extend(f"missing_feature:{name}" for name in missing)
        failures.extend(f"non_numeric_feature:{name}" for name in non_numeric)

    if not _is_number(ratio):
        failures.append("holdout_ratio_to_electron_not_numeric")
    elif float(ratio) <= 0.0:
        failures.append("holdout_ratio_to_electron_not_positive")

    return {
        "execution_inputs_valid": int(not failures),
        "execution_input_failure_reasons": failures,
    }


def predict_ratio_to_electron(
    feature_vector: dict[str, object], candidate_law: dict[str, object]
) -> float:
    basis_names = list(candidate_law["basis_names"])
    weights = dict(candidate_law["pre_registered_weight_vector"])
    weight_scale = float(candidate_law["weight_scale"])
    weighted_sum = 0.0
    for name in basis_names:
        weighted_sum += float(weights[name]) * float(feature_vector[name])
    return 10.0 ** (weighted_sum / weight_scale)


def holdout_evaluation(
    oracle: dict[str, object] | None,
    candidate_law: dict[str, object],
    ready: bool,
) -> dict[str, object]:
    if oracle is None or not ready:
        return {
            "holdout_execution_performed": 0,
            "holdout_evaluation_performed": 0,
            "holdout_identity": None,
            "predicted_ratio_to_electron": None,
            "observed_holdout_ratio_to_electron": None,
            "log10_abs_error": None,
            "candidate_survives_blinded_holdout": 0,
        }

    feature_vector = oracle["holdout_feature_vector"]
    assert isinstance(feature_vector, dict)
    predicted = predict_ratio_to_electron(feature_vector, candidate_law)
    observed = float(oracle["holdout_ratio_to_electron"])
    log10_abs_error = abs(math.log10(predicted) - math.log10(observed))
    survives = log10_abs_error <= EXECUTION_TOLERANCE_LOG10_ABS_ERROR

    return {
        "holdout_execution_performed": 1,
        "holdout_evaluation_performed": 1,
        "holdout_identity": oracle.get("holdout_identity"),
        "predicted_ratio_to_electron": predicted,
        "observed_holdout_ratio_to_electron": observed,
        "log10_abs_error": log10_abs_error,
        "candidate_survives_blinded_holdout": int(survives),
    }


def build_receipt(oracle_path: str | None = None) -> dict[str, Any]:
    l2_receipt = build_l2_receipt()
    l3_receipt = build_l3_receipt(oracle_path)
    oracle, oracle_state = load_oracle(oracle_path)
    candidate_law = dict(l2_receipt["candidate_law"])
    basis_names = list(candidate_law["basis_names"])
    input_validation = validate_execution_inputs(oracle, basis_names)
    oracle_schema_valid = bool(l3_receipt["oracle_schema_valid"])
    execution_inputs_valid = bool(input_validation["execution_inputs_valid"])
    holdout_ready = oracle_schema_valid and execution_inputs_valid
    evaluation = holdout_evaluation(oracle, candidate_law, holdout_ready)

    receipt: dict[str, Any] = {
        "latticra_identity_replay_impedance_l4_blinded_holdout_execution_gate_present": 1,
        "execution_gate_id": "latticra-identity-replay-impedance-l4-blinded-holdout-execution-gate",
        "execution_gate_version": 1,
        "l3_intake_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L3_EXTERNAL_BLINDED_HOLDOUT_INTAKE.md",
        "l3_intake_receipt_hash": l3_receipt["intake_receipt_hash"],
        "l2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L2_PREREGISTERED_SUBSTRATE_LAW_BLINDED_HOLDOUT.md",
        "l2_pre_registration_receipt_hash": l2_receipt["pre_registration_receipt_hash"],
        "l1_search_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "execution_gate_tool": "tools/latticra_identity_replay_l4_execution_gate.py",
        "execution_gate_defined": 1,
        "oracle_required": 1,
        "external_blinded_holdout_oracle_required": 1,
        "oracle_input_state": oracle_state,
        "oracle_received": l3_receipt["external_blinded_holdout_oracle_received"],
        "oracle_validation_performed": l3_receipt["oracle_validation_performed"],
        "oracle_schema_valid": l3_receipt["oracle_schema_valid"],
        "oracle_receipt_hash_matches_pre_registration": l3_receipt[
            "oracle_receipt_hash_matches_pre_registration"
        ],
        "oracle_opened_after_pre_registration": l3_receipt[
            "oracle_opened_after_pre_registration"
        ],
        "execution_inputs_valid": input_validation["execution_inputs_valid"],
        "execution_input_failure_reasons": input_validation[
            "execution_input_failure_reasons"
        ],
        "candidate_law_id": candidate_law["candidate_law_id"],
        "candidate_law_version": candidate_law["candidate_law_version"],
        "prediction_rule": candidate_law["prediction_rule"],
        "execution_acceptance_rule": (
            "abs(log10(predicted_ratio_to_electron) - "
            "log10(observed_holdout_ratio_to_electron)) <= "
            f"{EXECUTION_TOLERANCE_LOG10_ABS_ERROR}"
        ),
        "execution_tolerance_log10_abs_error": EXECUTION_TOLERANCE_LOG10_ABS_ERROR,
        "measured_masses_used_in_kappa": 0,
        "holdout_execution_ready": int(holdout_ready),
        **evaluation,
        "candidate_promoted": 0,
        "review_required_before_promotion": 1,
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
        ],
    }
    if not holdout_ready:
        receipt["non_claims"].append("not_holdout_execution")

    canonical = json.dumps(receipt, sort_keys=True, separators=(",", ":"))
    receipt["execution_gate_receipt_hash"] = "sha256:" + hashlib.sha256(
        canonical.encode("utf-8")
    ).hexdigest()
    receipt["execution_gate_receipt_hash_generated"] = 1
    return receipt


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--oracle", help="optional external blinded-holdout oracle JSON")
    args = parser.parse_args()
    print(json.dumps(build_receipt(args.oracle), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
