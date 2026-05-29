#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Evaluate Model-3 topological replay predictions after receipt emission."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_identity_replay_model1_evaluate import (
    EPSILON_RELATIVE,
    compare_predictions,
    decimal_to_text,
    parse_target_table,
)
from latticra_identity_replay_model2_evaluate import target_range


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    canonical_payload = dict(payload)
    canonical_payload.pop("model3_prediction_receipt_hash", None)
    canonical_payload.pop("model3_prediction_receipt_hash_generated", None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def evaluation_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def load_prediction(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-3 prediction receipt must be a JSON object")
    return payload


def control_survives(prediction: dict[str, object], control: str) -> int:
    controls = prediction.get("control_Z_L_estimates")
    if not isinstance(controls, dict):
        return 0
    return int(Decimal(str(controls.get(control, "1"))) == Decimal("0"))


def build_evaluation_receipt(prediction_path: Path, target_path: Path) -> dict[str, object]:
    prediction = load_prediction(prediction_path)
    expected_hash = receipt_hash(prediction)
    observed_hash = prediction.get("model3_prediction_receipt_hash")
    prediction_hash_valid = int(observed_hash == expected_hash)

    targets, cross_ratios = parse_target_table(target_path)
    error_rows, failures = compare_predictions(prediction, targets)
    candidate_survives = int(not failures)
    parameter_count = int(prediction.get("parameter_count", 999999))
    prediction_dynamic_range = str(prediction.get("prediction_dynamic_range", "undefined"))
    target_dynamic_range = target_range(targets)
    prediction_law_rejected = int(not candidate_survives)

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_prediction_evaluation_present": 1,
        "evaluation_id": "latticra-identity-replay-model3-prediction-evaluation",
        "evaluation_version": 1,
        "prediction_receipt_reference": str(prediction_path),
        "target_table_reference": str(target_path),
        "prediction_law_id": prediction.get("prediction_law_id"),
        "model3_prediction_receipt_hash": observed_hash,
        "model3_prediction_receipt_hash_recomputed": expected_hash,
        "model3_prediction_receipt_hash_valid": prediction_hash_valid,
        "model3_pre_registration_receipt_hash": prediction.get(
            "model3_pre_registration_receipt_hash"
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
        "model3_topological_amplification_present": prediction.get(
            "model3_topological_amplification_present"
        ),
        "topological_amplification_trace_emitted": prediction.get(
            "topological_amplification_trace_emitted"
        ),
        "counterfactual_repair_search_performed": prediction.get(
            "counterfactual_repair_search_performed"
        ),
        "kappa_trace_emitted": prediction.get("kappa_trace_emitted"),
        "mass_ratio_predictions_emitted": prediction.get(
            "mass_ratio_predictions_emitted"
        ),
        "measured_masses_used_in_law": prediction.get("measured_masses_used_in_law"),
        "measured_masses_used_in_kappa": prediction.get("measured_masses_used_in_kappa"),
        "target_ratios_used_in_law": prediction.get("target_ratios_used_in_law"),
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
        "model3_prediction_law_rejected": prediction_law_rejected,
        "model3_prediction_conclusion": (
            "survives_target_table_under_guarded_epsilon"
            if candidate_survives
            else "rejected_by_target_table"
        ),
        "topological_amplification_improved_range_but_failed_targets": int(
            prediction_law_rejected
            and prediction_dynamic_range != "undefined"
            and Decimal(prediction_dynamic_range) > Decimal("22.098461538461538")
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
    receipt["model3_evaluation_receipt_hash"] = evaluation_hash(receipt)
    receipt["model3_evaluation_receipt_hash_generated"] = 1
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
