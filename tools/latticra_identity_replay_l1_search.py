#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Run the Latticra identity-replay impedance L1 constrained search.

L1 searches a small integer-weight log-impedance family against the guarded
mass-ratio target table. It is target-guided hypothesis search, not proof.
"""

from __future__ import annotations

import hashlib
import json
import math

from latticra_identity_replay_l0_runner import PARTICLES


EPSILON_RELATIVE = 0.05
WEIGHT_MIN = -20
WEIGHT_MAX = 20
WEIGHT_SCALE = 10.0
MAX_COORDINATE_PASSES = 20

BASIS_NAMES = [
    "generation_lift",
    "generation_square_lift",
    "localization_excess",
    "electroweak_spin_load",
    "scalar_load",
    "color_localization_load",
    "boundary_oscillation_load",
    "charge_gap_to_electron",
]


def format_number(value: float) -> str:
    return format(value, ".17g")


def feature_raw(particle: dict[str, object]) -> list[int]:
    features = particle["features"]
    if not isinstance(features, dict):
        raise TypeError("features must be a mapping")

    generation_lift = features["generation"] - 1
    return [
        generation_lift,
        generation_lift**2,
        features["localization_rank"] - 1,
        features["weak_channel"] * features["spin_channel"],
        features["scalar_channel"],
        features["color_channel"] * features["localization_rank"],
        features["boundary_links"] * features["oscillation_nodes"],
        abs(features["charge_thirds_abs"] - PARTICLES[0]["features"]["charge_thirds_abs"]),
    ]


BASE_VECTOR = feature_raw(PARTICLES[0])


def feature_vector(particle: dict[str, object]) -> list[int]:
    return [value - base for value, base in zip(feature_raw(particle), BASE_VECTOR)]


FEATURE_VECTORS = [feature_vector(particle) for particle in PARTICLES]
TARGET_RATIOS = [float(particle["mass_mev"] / PARTICLES[0]["mass_mev"]) for particle in PARTICLES]
TARGET_LOG10_RATIOS = [math.log10(ratio) for ratio in TARGET_RATIOS]
TRAIN_INDEXES = list(range(1, len(PARTICLES)))


def predict_log10_ratio(weights: list[int], vector: list[int]) -> float:
    return sum(weight * value for weight, value in zip(weights, vector)) / WEIGHT_SCALE


def score_weights(weights: list[int], train_indexes: list[int]) -> tuple[float, float, list[float]]:
    errors = [
        abs(predict_log10_ratio(weights, FEATURE_VECTORS[index]) - TARGET_LOG10_RATIOS[index])
        for index in train_indexes
    ]
    return sum(errors) / len(errors), max(errors), errors


def fit_weights(train_indexes: list[int]) -> dict[str, object]:
    weights = [0 for _ in BASIS_NAMES]
    evaluation_count = 0

    def objective(candidate: list[int]) -> float:
        nonlocal evaluation_count
        evaluation_count += 1
        return score_weights(candidate, train_indexes)[0]

    best_score = objective(weights)
    passes_used = 0

    for pass_index in range(MAX_COORDINATE_PASSES):
        changed = False
        passes_used = pass_index + 1
        for weight_index in range(len(weights)):
            current = weights[weight_index]
            options: list[tuple[float, int]] = []
            for proposed in range(WEIGHT_MIN, WEIGHT_MAX + 1):
                weights[weight_index] = proposed
                options.append((objective(weights), proposed))
            options.sort(key=lambda item: (item[0], abs(item[1]), item[1]))
            if options[0][0] + 1e-12 < best_score:
                best_score = options[0][0]
                weights[weight_index] = options[0][1]
                changed = True
            else:
                weights[weight_index] = current
        if not changed:
            break

    mean_abs_error, max_abs_error, _ = score_weights(weights, train_indexes)
    return {
        "weights": weights,
        "mean_abs_log10_error": mean_abs_error,
        "max_abs_log10_error": max_abs_error,
        "coordinate_passes_used": passes_used,
        "candidate_evaluations": evaluation_count,
    }


def prediction_row(particle_index: int, weights: list[int]) -> dict[str, object]:
    particle = PARTICLES[particle_index]
    vector = FEATURE_VECTORS[particle_index]
    predicted_log10 = predict_log10_ratio(weights, vector)
    predicted_ratio = 10**predicted_log10
    target_ratio = TARGET_RATIOS[particle_index]
    relative_error = abs(predicted_ratio - target_ratio) / target_ratio if target_ratio else 0.0
    return {
        "target": particle["target"],
        "identity": particle["identity"],
        "feature_vector": dict(zip(BASIS_NAMES, vector)),
        "predicted_log10_ratio_to_electron": format_number(predicted_log10),
        "target_log10_ratio_to_electron": format_number(TARGET_LOG10_RATIOS[particle_index]),
        "predicted_ratio_to_electron": format_number(predicted_ratio),
        "target_ratio_to_electron": format_number(target_ratio),
        "relative_ratio_error": format_number(relative_error),
        "survives_epsilon": relative_error <= EPSILON_RELATIVE,
    }


def holdout_row(held_out_index: int) -> dict[str, object]:
    train_indexes = [index for index in TRAIN_INDEXES if index != held_out_index]
    fit = fit_weights(train_indexes)
    weights = fit["weights"]
    if not isinstance(weights, list):
        raise TypeError("weights must be a list")
    row = prediction_row(held_out_index, weights)
    row["held_out_target"] = row.pop("target")
    row["held_out_identity"] = row.pop("identity")
    row["fit_mean_abs_log10_error"] = format_number(float(fit["mean_abs_log10_error"]))
    row["fit_max_abs_log10_error"] = format_number(float(fit["max_abs_log10_error"]))
    row["fit_weight_vector"] = dict(zip(BASIS_NAMES, weights))
    row["fit_candidate_evaluations"] = fit["candidate_evaluations"]
    return row


def build_receipt() -> dict[str, object]:
    full_fit = fit_weights(TRAIN_INDEXES)
    weights = full_fit["weights"]
    if not isinstance(weights, list):
        raise TypeError("weights must be a list")

    predictions = [prediction_row(index, weights) for index in range(len(PARTICLES))]
    holdouts = [holdout_row(index) for index in TRAIN_INDEXES]
    candidate_survives = all(row["survives_epsilon"] for row in predictions)
    holdout_survives = all(row["survives_epsilon"] for row in holdouts)

    receipt = {
        "latticra_identity_replay_impedance_l1_constrained_substrate_search_present": 1,
        "search_id": "latticra-identity-replay-impedance-l1-constrained-substrate-search",
        "search_version": 1,
        "candidate_family_id": "log-linear-small-integer-identity-feature-impedance",
        "candidate_family_version": 1,
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "l0_runner_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "search_tool": "tools/latticra_identity_replay_l1_search.py",
        "search_deterministic": 1,
        "target_guided_search_performed": 1,
        "targets_used_for_candidate_scoring": 1,
        "measured_masses_used_in_kappa": 0,
        "leave_one_out_validation_performed": 1,
        "basis_names": BASIS_NAMES,
        "weight_min": WEIGHT_MIN,
        "weight_max": WEIGHT_MAX,
        "weight_scale": format_number(WEIGHT_SCALE),
        "parameter_count": len(BASIS_NAMES),
        "training_target_count": len(TRAIN_INDEXES),
        "overfit_risk_flag": int(len(BASIS_NAMES) >= len(TRAIN_INDEXES)),
        "best_weight_vector": dict(zip(BASIS_NAMES, weights)),
        "best_candidate_evaluations": full_fit["candidate_evaluations"],
        "best_mean_abs_log10_error": format_number(float(full_fit["mean_abs_log10_error"])),
        "best_max_abs_log10_error": format_number(float(full_fit["max_abs_log10_error"])),
        "epsilon_relative": format_number(EPSILON_RELATIVE),
        "candidate_survives_target_table": int(candidate_survives),
        "candidate_survives_leave_one_out": int(holdout_survives),
        "candidate_promoted": 0,
        "mass_ratio_recovery_claimed": 0,
        "standard_model_replacement_claimed": 0,
        "higgs_denied": 0,
        "higgs_checkmate_claimed": 0,
        "higgs_only_causal_closure_challenged": 1,
        "simulation_proven": 0,
        "scientific_claim_promoted": 0,
        "predictions": predictions,
        "leave_one_out": holdouts,
        "failure_record_if_any_target_breaks": [
            row["identity"] for row in predictions if not row["survives_epsilon"]
        ],
        "holdout_failure_record": [
            row["held_out_identity"] for row in holdouts if not row["survives_epsilon"]
        ],
        "non_claims": [
            "not_a_standard_model_replacement",
            "not_a_higgs_denial",
            "not_simulation_proof",
            "not_mass_ratio_recovery",
            "not_final_checkmate",
        ],
    }

    canonical = json.dumps(receipt, sort_keys=True, separators=(",", ":"))
    receipt["receipt_hash"] = "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()
    receipt["receipt_hash_generated"] = 1
    return receipt


def main() -> int:
    print(json.dumps(build_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
