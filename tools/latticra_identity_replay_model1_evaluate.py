#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Evaluate Model-1 prediction receipts against the guarded target table."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable


getcontext().prec = 50

EPSILON_RELATIVE = Decimal("0.05")

TARGET_ROW_RE = re.compile(
    r"^\| (?P<target>[^|]+?) \| `(?P<identity>[^`]+)` \| "
    r"`(?P<mass>[^`]+)` \| `(?P<ratio>[^`]+)` \|"
)

CROSS_RATIO_RE = re.compile(r"^(?P<name>[A-Za-z_]+_target)=(?P<value>[0-9.]+)$")


def decimal_to_text(value: Decimal) -> str:
    normalized = value.normalize()
    if normalized == normalized.to_integral():
        return format(normalized, "f")
    return format(normalized, "f")


def parse_target_table(path: Path) -> tuple[dict[str, dict[str, str]], dict[str, str]]:
    targets: dict[str, dict[str, str]] = {}
    cross_ratios: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        row_match = TARGET_ROW_RE.match(line)
        if row_match:
            targets[row_match.group("target")] = {
                "identity": row_match.group("identity"),
                "mass_mev": row_match.group("mass"),
                "ratio_to_electron": row_match.group("ratio"),
            }
            continue
        cross_match = CROSS_RATIO_RE.match(line.strip())
        if cross_match:
            cross_ratios[cross_match.group("name")] = cross_match.group("value")
    if not targets:
        raise ValueError(f"no candidate target rows parsed from {path}")
    return targets, cross_ratios


def prediction_receipt_hash(payload: dict[str, object]) -> str:
    canonical_payload = dict(payload)
    canonical_payload.pop("prediction_receipt_hash", None)
    canonical_payload.pop("prediction_receipt_hash_generated", None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def evaluation_receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def load_prediction(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("prediction receipt must be a JSON object")
    return payload


def compare_predictions(
    prediction: dict[str, object], targets: dict[str, dict[str, str]]
) -> tuple[list[dict[str, object]], list[str]]:
    ratio_predictions = prediction.get("mass_ratio_predictions")
    if not isinstance(ratio_predictions, dict):
        raise ValueError("prediction receipt missing mass_ratio_predictions")

    rows = []
    failures = []
    for target, target_row in targets.items():
        predicted_text = ratio_predictions.get(target)
        if not isinstance(predicted_text, str) or predicted_text == "undefined":
            rows.append(
                {
                    "target": target,
                    "identity": target_row["identity"],
                    "predicted_ratio_to_electron": "missing",
                    "target_ratio_to_electron": target_row["ratio_to_electron"],
                    "absolute_error": "undefined",
                    "relative_error": "undefined",
                    "survives_epsilon": 0,
                }
            )
            failures.append(target_row["identity"])
            continue

        predicted = Decimal(predicted_text)
        expected = Decimal(target_row["ratio_to_electron"])
        absolute_error = abs(predicted - expected)
        relative_error = absolute_error / expected if expected else Decimal("0")
        survives = relative_error <= EPSILON_RELATIVE
        if not survives:
            failures.append(target_row["identity"])
        rows.append(
            {
                "target": target,
                "identity": target_row["identity"],
                "predicted_ratio_to_electron": decimal_to_text(predicted),
                "target_ratio_to_electron": decimal_to_text(expected),
                "absolute_error": decimal_to_text(absolute_error),
                "relative_error": decimal_to_text(relative_error),
                "survives_epsilon": int(survives),
            }
        )
    return rows, failures


def control_survives(prediction: dict[str, object], control: str) -> int:
    controls = prediction.get("control_Z_L_estimates")
    if not isinstance(controls, dict):
        return 0
    return int(Decimal(str(controls.get(control, "1"))) == Decimal("0"))


def build_evaluation_receipt(prediction_path: Path, target_path: Path) -> dict[str, object]:
    prediction = load_prediction(prediction_path)
    expected_hash = prediction_receipt_hash(prediction)
    observed_hash = prediction.get("prediction_receipt_hash")
    prediction_hash_valid = int(observed_hash == expected_hash)

    targets, cross_ratios = parse_target_table(target_path)
    error_rows, failures = compare_predictions(prediction, targets)
    candidate_survives = int(not failures)
    parameter_count = int(prediction.get("parameter_count", 999999))
    parameter_count_less_than_target_count = int(parameter_count < len(targets))

    receipt: dict[str, object] = {
        "latticra_identity_replay_model1_dynamic_substrate_evaluation_present": 1,
        "evaluator_id": "latticra-identity-replay-model1-dynamic-substrate-evaluator",
        "evaluator_version": 1,
        "prediction_receipt_reference": str(prediction_path),
        "target_table_reference": str(target_path),
        "prediction_receipt_hash": observed_hash,
        "prediction_receipt_hash_recomputed": expected_hash,
        "prediction_receipt_hash_valid": prediction_hash_valid,
        "model1_dynamic_substrate_present": int(
            prediction.get("model1_dynamic_substrate_present") == 1
        ),
        "particle_features_hand_declared": prediction.get(
            "particle_features_hand_declared"
        ),
        "identity_patterns_generated_from_substrate": prediction.get(
            "identity_patterns_generated_from_substrate"
        ),
        "counterfactual_repair_search_performed": prediction.get(
            "counterfactual_repair_search_performed"
        ),
        "kappa_trace_emitted": prediction.get("kappa_trace_emitted"),
        "Z_L_confidence_window_emitted": prediction.get(
            "Z_L_confidence_window_emitted"
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
        "negative_controls_present": prediction.get("negative_controls_present"),
        "photon_zero_rest_mass_control_present": prediction.get(
            "photon_zero_rest_mass_control_present"
        ),
        "gluon_zero_rest_mass_control_present": prediction.get(
            "gluon_zero_rest_mass_control_present"
        ),
        "photon_zero_rest_mass_control_survives": control_survives(
            prediction, "photon"
        ),
        "gluon_zero_rest_mass_control_survives": control_survives(prediction, "gluon"),
        "parameter_count": parameter_count,
        "target_count": len(targets),
        "parameter_count_less_than_target_count": parameter_count_less_than_target_count,
        "epsilon_relative": decimal_to_text(EPSILON_RELATIVE),
        "Z_L_estimates": prediction.get("Z_L_estimates"),
        "mass_ratio_predictions": prediction.get("mass_ratio_predictions"),
        "target_ratios": targets,
        "cross_ratio_targets": cross_ratios,
        "error_vector_against_target_table": error_rows,
        "failure_record_if_any_target_breaks": failures,
        "candidate_survives_target_table": candidate_survives,
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
    receipt["evaluation_receipt_hash"] = evaluation_receipt_hash(receipt)
    receipt["evaluation_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--predictions", required=True, help="Model-1 prediction JSON")
    parser.add_argument("--targets", required=True, help="guarded target table markdown")
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_evaluation_receipt(Path(args.predictions), Path(args.targets))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
