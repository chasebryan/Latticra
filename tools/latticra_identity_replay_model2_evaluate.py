#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Evaluate Model-2 hierarchical replay predictions after receipt emission."""

from __future__ import annotations

import argparse
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_receipt_utils import canonical_receipt_hash, decimal_to_text, path_reference, receipt_hash as make_receipt_hash

from latticra_identity_replay_model1_evaluate import (
    EPSILON_RELATIVE,
    compare_predictions,
    decimal_to_text,
    parse_target_table,
)


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    return make_receipt_hash(
        payload,
        exclude_keys=(
            "model2_prediction_receipt_hash",
            "model2_prediction_receipt_hash_generated",
        ),
    )


def evaluation_hash(payload: dict[str, object]) -> str:
    return canonical_receipt_hash(payload)


def load_prediction(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-2 prediction receipt must be a JSON object")
    return payload


def target_range(targets: dict[str, dict[str, str]]) -> str:
    ratios = [Decimal(row["ratio_to_electron"]) for row in targets.values()]
    nonzero = [ratio for ratio in ratios if ratio > 0]
    if not nonzero:
        return "undefined"
    return decimal_to_text(max(nonzero) / min(nonzero))


def control_survives(prediction: dict[str, object], control: str) -> int:
    controls = prediction.get("control_Z_L_estimates")
    if not isinstance(controls, dict):
        return 0
    return int(Decimal(str(controls.get(control, "1"))) == Decimal("0"))


def build_evaluation_receipt(prediction_path: Path, target_path: Path) -> dict[str, object]:
    prediction = load_prediction(prediction_path)
    expected_hash = receipt_hash(prediction)
    observed_hash = prediction.get("model2_prediction_receipt_hash")
    prediction_hash_valid = int(observed_hash == expected_hash)

    targets, cross_ratios = parse_target_table(target_path)
    error_rows, failures = compare_predictions(prediction, targets)
    candidate_survives = int(not failures)
    parameter_count = int(prediction.get("parameter_count", 999999))
    prediction_dynamic_range = str(prediction.get("prediction_dynamic_range", "undefined"))
    target_dynamic_range = target_range(targets)
    prediction_law_rejected = int(not candidate_survives)

    receipt: dict[str, object] = {
        "latticra_identity_replay_model2_prediction_evaluation_present": 1,
        "evaluation_id": "latticra-identity-replay-model2-prediction-evaluation",
        "evaluation_version": 1,
        "prediction_receipt_reference": str(prediction_path),
        "target_table_reference": str(target_path),
        "prediction_law_id": prediction.get("prediction_law_id"),
        "model2_prediction_receipt_hash": observed_hash,
        "model2_prediction_receipt_hash_recomputed": expected_hash,
        "model2_prediction_receipt_hash_valid": prediction_hash_valid,
        "model2_pre_registration_receipt_hash": prediction.get(
            "model2_pre_registration_receipt_hash"
        ),
        "prediction_receipt_emitted_before_target_load": prediction.get(
            "prediction_receipt_emitted_before_target_load"
        ),
        "prediction_input_target_table_loaded": prediction.get("target_table_loaded"),
        "prediction_input_target_comparison_performed": prediction.get(
            "target_comparison_performed"
        ),
        "target_table_loaded": 1,
        "target_load_after_prediction_receipt": int(
            prediction_hash_valid == 1
            and prediction.get("prediction_receipt_emitted_before_target_load") == 1
            and prediction.get("target_table_loaded") == 0
        ),
        "target_comparison_performed": 1,
        "model2_hierarchical_substrate_present": prediction.get(
            "model2_hierarchical_substrate_present"
        ),
        "hierarchical_replay_performed": prediction.get("hierarchical_replay_performed"),
        "per_scale_kappa_traces_emitted": prediction.get(
            "per_scale_kappa_traces_emitted"
        ),
        "active_scale_product_cost_emitted": prediction.get(
            "active_scale_product_cost_emitted"
        ),
        "mass_ratio_predictions_emitted": prediction.get(
            "mass_ratio_predictions_emitted"
        ),
        "measured_masses_used_in_law": prediction.get("measured_masses_used_in_law"),
        "measured_masses_used_in_kappa": prediction.get("measured_masses_used_in_kappa"),
        "particle_features_hand_declared": prediction.get(
            "particle_features_hand_declared"
        ),
        "identity_patterns_generated_from_substrate": prediction.get(
            "identity_patterns_generated_from_substrate"
        ),
        "negative_controls_present": prediction.get("negative_controls_present"),
        "photon_zero_rest_mass_control_survives": control_survives(
            prediction, "photon"
        ),
        "gluon_zero_rest_mass_control_survives": control_survives(prediction, "gluon"),
        "prediction_dynamic_range": prediction_dynamic_range,
        "target_dynamic_range": target_dynamic_range,
        "prediction_dynamic_range_meets_target_range": int(
            prediction_dynamic_range != "undefined"
            and Decimal(prediction_dynamic_range) >= Decimal(target_dynamic_range)
        ),
        "parameter_count": parameter_count,
        "target_count": len(targets),
        "parameter_count_less_than_target_count": int(parameter_count < len(targets)),
        "epsilon_relative": decimal_to_text(EPSILON_RELATIVE),
        "Z_L_estimates": prediction.get("Z_L_estimates"),
        "mass_ratio_predictions": prediction.get("mass_ratio_predictions"),
        "target_ratios": targets,
        "cross_ratio_targets": cross_ratios,
        "error_vector_against_target_table": error_rows,
        "failure_record_if_any_target_breaks": failures,
        "candidate_survives_target_table": candidate_survives,
        "model2_prediction_law_rejected": prediction_law_rejected,
        "model2_prediction_conclusion": (
            "survives_target_table_under_guarded_epsilon"
            if candidate_survives
            else "rejected_by_target_table"
        ),
        "hierarchy_sufficient_for_range_but_prediction_vector_failed": int(
            prediction_law_rejected
        ),
        "candidate_promoted": 0,
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
    receipt["model2_evaluation_receipt_hash"] = evaluation_hash(receipt)
    receipt["model2_evaluation_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--predictions", required=True)
    parser.add_argument("--targets", required=True)
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_evaluation_receipt(Path(args.predictions), Path(args.targets))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
