#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Analyze the Model-2 prediction failure and derive Model-3 requirements."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_receipt_utils import decimal_to_text
from latticra_identity_replay_model2_evaluate import receipt_hash as prediction_hash


getcontext().prec = 80

HEAVY_SECTOR_TARGETS = {"W boson", "Z boson", "Higgs boson", "top quark"}
LEPTON_FAMILY_TARGETS = {"electron", "muon", "tau"}


def canonical_hash(payload: dict[str, object], omitted_keys: Iterable[str]) -> str:
    canonical_payload = dict(payload)
    for key in omitted_keys:
        canonical_payload.pop(key, None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def analysis_hash(payload: dict[str, object]) -> str:
    return canonical_hash(
        payload,
        (
            "model2_failure_analysis_receipt_hash",
            "model2_failure_analysis_receipt_hash_generated",
        ),
    )


def evaluation_hash(payload: dict[str, object]) -> str:
    return canonical_hash(
        payload,
        (
            "model2_evaluation_receipt_hash",
            "model2_evaluation_receipt_hash_generated",
        ),
    )


def load_json(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError(f"{path} must contain a JSON object")
    return payload


def decimal_field(payload: dict[str, object], key: str) -> Decimal:
    value = payload.get(key)
    if value is None or value == "undefined":
        raise ValueError(f"missing decimal field: {key}")
    return Decimal(str(value))


def ratio_predictions(prediction: dict[str, object]) -> dict[str, Decimal]:
    ratios = prediction.get("mass_ratio_predictions")
    if not isinstance(ratios, dict):
        raise ValueError("prediction receipt missing mass_ratio_predictions")
    return {target: Decimal(str(value)) for target, value in ratios.items()}


def target_ratios(evaluation: dict[str, object]) -> dict[str, tuple[str, Decimal]]:
    targets = evaluation.get("target_ratios")
    if not isinstance(targets, dict):
        raise ValueError("evaluation receipt missing target_ratios")
    parsed: dict[str, tuple[str, Decimal]] = {}
    for target, row in targets.items():
        if not isinstance(row, dict):
            raise ValueError(f"target row for {target} must be an object")
        parsed[str(target)] = (
            str(row["identity"]),
            Decimal(str(row["ratio_to_electron"])),
        )
    return parsed


def sorted_identity_order(
    targets: dict[str, tuple[str, Decimal]],
    values: dict[str, Decimal],
) -> list[str]:
    ordered = sorted(
        (
            (values[target], identity)
            for target, (identity, _) in targets.items()
            if target in values
        ),
        key=lambda item: item[0],
    )
    return [identity for _, identity in ordered]


def failure_rows(
    evaluation: dict[str, object],
    predictions: dict[str, Decimal],
    targets: dict[str, tuple[str, Decimal]],
) -> list[dict[str, object]]:
    rows = []
    for target, (identity, target_ratio) in targets.items():
        predicted = predictions[target]
        required_multiplier = (
            target_ratio / predicted if predicted > Decimal("0") else Decimal("Infinity")
        )
        if target in HEAVY_SECTOR_TARGETS:
            failure_class = "heavy_sector_impedance_underamplified"
        elif target in LEPTON_FAMILY_TARGETS and target != "electron":
            failure_class = "lepton_family_gap_underamplified"
        else:
            failure_class = "anchor_or_unclassified"

        survives = 0
        for error_row in evaluation.get("error_vector_against_target_table", []):
            if isinstance(error_row, dict) and error_row.get("target") == target:
                survives = int(error_row.get("survives_epsilon", 0))
                break

        rows.append(
            {
                "target": target,
                "identity": identity,
                "predicted_ratio_to_electron": decimal_to_text(predicted),
                "target_ratio_to_electron": decimal_to_text(target_ratio),
                "required_multiplier_to_target": decimal_to_text(required_multiplier),
                "survives_epsilon": survives,
                "failure_class": "survives" if survives else failure_class,
            }
        )
    return rows


def build_failure_analysis(
    prediction_path: Path, evaluation_path: Path
) -> dict[str, object]:
    prediction = load_json(prediction_path)
    evaluation = load_json(evaluation_path)

    recomputed_prediction_hash = prediction_hash(prediction)
    observed_prediction_hash = prediction.get("model2_prediction_receipt_hash")
    recomputed_evaluation_hash = evaluation_hash(evaluation)
    observed_evaluation_hash = evaluation.get("model2_evaluation_receipt_hash")

    predictions = ratio_predictions(prediction)
    targets = target_ratios(evaluation)
    target_values = {target: ratio for target, (_, ratio) in targets.items()}

    prediction_dynamic_range = decimal_field(evaluation, "prediction_dynamic_range")
    target_dynamic_range = decimal_field(evaluation, "target_dynamic_range")
    dynamic_range_deficit_factor = target_dynamic_range / prediction_dynamic_range

    predicted_order = sorted_identity_order(targets, predictions)
    target_order = sorted_identity_order(targets, target_values)
    failed_identities = evaluation.get("failure_record_if_any_target_breaks", [])
    if not isinstance(failed_identities, list):
        failed_identities = []

    heavy_prediction_values = [
        predictions[target] for target in HEAVY_SECTOR_TARGETS if target in predictions
    ]
    heavy_target_values = [
        target_values[target] for target in HEAVY_SECTOR_TARGETS if target in target_values
    ]
    heavy_multipliers = [
        target_values[target] / predictions[target]
        for target in HEAVY_SECTOR_TARGETS
        if target in predictions and predictions[target] > Decimal("0")
    ]

    muon_predicted = predictions["muon"]
    tau_predicted = predictions["tau"]
    muon_target = target_values["muon"]
    tau_target = target_values["tau"]

    receipt: dict[str, object] = {
        "latticra_identity_replay_model2_prediction_failure_analysis_present": 1,
        "analysis_id": "latticra-identity-replay-model2-prediction-failure-analysis",
        "analysis_version": 1,
        "prediction_receipt_reference": str(prediction_path),
        "evaluation_receipt_reference": str(evaluation_path),
        "prediction_runner_reference": "tools/latticra_identity_replay_model2_runner.py",
        "evaluation_tool_reference": "tools/latticra_identity_replay_model2_evaluate.py",
        "model3_worthiness_gate_reference": "tools/latticra_identity_replay_model3_worthiness_gate.py",
        "model2_prediction_receipt_hash": observed_prediction_hash,
        "model2_prediction_receipt_hash_recomputed": recomputed_prediction_hash,
        "model2_prediction_receipt_hash_valid": int(
            observed_prediction_hash == recomputed_prediction_hash
        ),
        "model2_evaluation_receipt_hash": observed_evaluation_hash,
        "model2_evaluation_receipt_hash_recomputed": recomputed_evaluation_hash,
        "model2_evaluation_receipt_hash_valid": int(
            observed_evaluation_hash == recomputed_evaluation_hash
        ),
        "prediction_receipt_emitted_before_target_load": prediction.get(
            "prediction_receipt_emitted_before_target_load"
        ),
        "target_load_after_prediction_receipt": evaluation.get(
            "target_load_after_prediction_receipt"
        ),
        "prediction_law_id": prediction.get("prediction_law_id"),
        "model2_prediction_law_rejected": evaluation.get(
            "model2_prediction_law_rejected"
        ),
        "model2_prediction_conclusion": evaluation.get("model2_prediction_conclusion"),
        "prediction_dynamic_range": decimal_to_text(prediction_dynamic_range),
        "target_dynamic_range": decimal_to_text(target_dynamic_range),
        "dynamic_range_deficit_factor": decimal_to_text(dynamic_range_deficit_factor),
        "prediction_dynamic_range_meets_target_range": evaluation.get(
            "prediction_dynamic_range_meets_target_range"
        ),
        "target_count": evaluation.get("target_count"),
        "failed_identity_count": len(failed_identities),
        "surviving_identity_count": int(evaluation.get("target_count", 0))
        - len(failed_identities),
        "failure_record_if_any_target_breaks": failed_identities,
        "failure_rows": failure_rows(evaluation, predictions, targets),
        "predicted_identity_order_by_ratio": predicted_order,
        "target_identity_order_by_ratio": target_order,
        "ordering_failure_present": int(predicted_order != target_order),
        "lepton_family_order_inversion_present": int(
            muon_predicted > tau_predicted and tau_target > muon_target
        ),
        "lepton_family_gap_underestimated": 1,
        "heavy_sector_compression_present": int(
            max(heavy_prediction_values) < Decimal("10")
            and min(heavy_target_values) > Decimal("100000")
        ),
        "heavy_sector_max_predicted_ratio": decimal_to_text(max(heavy_prediction_values)),
        "heavy_sector_min_target_ratio": decimal_to_text(min(heavy_target_values)),
        "heavy_sector_min_required_multiplier": decimal_to_text(
            min(heavy_multipliers)
        ),
        "heavy_sector_max_required_multiplier": decimal_to_text(
            max(heavy_multipliers)
        ),
        "top_quark_amplification_required": decimal_to_text(
            target_values["top quark"] / predictions["top quark"]
        ),
        "required_model3_property": "target_blind_topological_replay_amplification",
        "required_model3_property_description": (
            "Model-3 must generate orders-of-magnitude impedance separation from "
            "replay topology, branching identity quotients, or nested quotient "
            "instability before loading target masses."
        ),
        "minimum_model3_dynamic_range_multiplier_required": decimal_to_text(
            dynamic_range_deficit_factor
        ),
        "model3_worthiness_gate_required": 1,
        "model3_prediction_runner_authorized": 0,
        "model3_preregistration_worthwhile_if_gate_passes": 1,
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
            "not_model3_prediction",
            "not_scientific_claim_promotion",
        ],
    }
    receipt["model2_failure_analysis_receipt_hash"] = analysis_hash(receipt)
    receipt["model2_failure_analysis_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--predictions", required=True)
    parser.add_argument("--evaluation", required=True)
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_failure_analysis(Path(args.predictions), Path(args.evaluation))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
