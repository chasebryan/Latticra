#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit Model-2 prediction-only hierarchical replay receipts."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from typing import Iterable

from latticra_receipt_utils import decimal_to_text, path_reference
from latticra_identity_replay_model1_substrate import (
    EPSILON_IDENTITY_TOLERANCE,
    MASSIVE_IDENTITY_CLASSES,
    MAX_CELL_ABS,
    REPAIR_COST_UNIT,
    REPLAY_HORIZON_N,
    WIDTH,
    ZERO_REST_MASS_CONTROLS,
    confidence_window,
    distance_metric,
    generated_control_pattern,
    identity_quotient,
    local_update_operator,
    observer_projection,
    repair_operations,
)
from latticra_identity_replay_model2_preregistration import (
    PARAMETER_COUNT,
    SCALE_NAMES,
    build_receipt as build_pre_registration_receipt,
)


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def generated_scale_pattern(target: str, identity: str, scale_name: str) -> tuple[int, ...]:
    digest = hashlib.sha256(
        f"model2-prediction:{scale_name}:{identity}:{target}".encode("utf-8")
    ).digest()
    state = [0] * WIDTH
    center = WIDTH // 2
    active_count = 2 + digest[0] % 7
    used = {center}
    cursor = 1
    while len(used) < active_count:
        position = digest[cursor % len(digest)] % WIDTH
        used.add(position)
        cursor += 1
    for order, position in enumerate(sorted(used)):
        byte = digest[(cursor + order) % len(digest)]
        magnitude = 1 + byte % MAX_CELL_ABS
        sign = 1 if byte & 1 else -1
        state[position] = sign * magnitude
    return tuple(state)


def replay_scale(base_state: tuple[int, ...]) -> dict[str, object]:
    expected_identity = identity_quotient(observer_projection(base_state))
    kappa_trace: list[int] = []
    trace_rows = []

    for step in range(1, REPLAY_HORIZON_N + 1):
        raw_next = local_update_operator(base_state)
        observed_identity = identity_quotient(observer_projection(raw_next))
        distance = distance_metric(observed_identity, expected_identity)
        operations = repair_operations(observed_identity, expected_identity)
        kappa_n = sum(operation["cost"] for operation in operations)
        kappa_trace.append(kappa_n)
        trace_rows.append(
            {
                "step": step,
                "raw_distance_to_expected_identity": distance,
                "kappa_n": kappa_n,
                "repair_operation_count": len(operations),
                "replay_stable_after_repair": 1,
            }
        )

    mean = Decimal(sum(kappa_trace)) / Decimal(len(kappa_trace))
    lower, upper = confidence_window(kappa_trace)
    return {
        "generated_pattern": list(base_state),
        "expected_identity_quotient": list(expected_identity),
        "kappa_trace": kappa_trace,
        "kappa_mean": decimal_to_text(mean),
        "kappa_confidence_window": {
            "lower": decimal_to_text(lower),
            "upper": decimal_to_text(upper),
            "method": "deterministic first-half/second-half mean window",
        },
        "trace": trace_rows,
    }


def replay_massive_identity(target: str, identity: str) -> dict[str, object]:
    scale_rows = []
    active_means: list[Decimal] = []
    for scale_name in SCALE_NAMES:
        scale_state = generated_scale_pattern(target, identity, scale_name)
        scale_result = replay_scale(scale_state)
        mean = Decimal(str(scale_result["kappa_mean"]))
        active_means.append(max(Decimal(REPAIR_COST_UNIT), mean))
        scale_rows.append({"scale": scale_name, **scale_result})

    z_l = Decimal(REPAIR_COST_UNIT)
    for mean in active_means:
        z_l *= mean

    return {
        "target": target,
        "identity": identity,
        "seed_kind": "hierarchical_massive",
        "scale_results": scale_rows,
        "active_scale_means": [decimal_to_text(mean) for mean in active_means],
        "Z_L": decimal_to_text(z_l),
        "zero_rest_mass_control": 0,
    }


def replay_control_identity(target: str, identity: str, seed_kind: str) -> dict[str, object]:
    scale_rows = []
    for scale_name in SCALE_NAMES:
        scale_state = generated_control_pattern(seed_kind)
        scale_rows.append({"scale": scale_name, **replay_scale(scale_state)})
    return {
        "target": target,
        "identity": identity,
        "seed_kind": seed_kind,
        "scale_results": scale_rows,
        "active_scale_means": ["0" for _ in SCALE_NAMES],
        "Z_L": "0",
        "zero_rest_mass_control": 1,
    }


def ratio_to_electron(row: dict[str, object], electron_z: Decimal) -> str:
    if electron_z == 0:
        return "undefined"
    return decimal_to_text(Decimal(str(row["Z_L"])) / electron_z)


def prediction_range(predictions: dict[str, str]) -> str:
    ratios = [Decimal(value) for value in predictions.values() if value != "undefined"]
    if not ratios:
        return "undefined"
    nonzero = [ratio for ratio in ratios if ratio > 0]
    if not nonzero:
        return "undefined"
    return decimal_to_text(max(nonzero) / min(nonzero))


def build_prediction_receipt() -> dict[str, object]:
    pre_registration = build_pre_registration_receipt()
    replay_rows = [
        replay_massive_identity(target, identity)
        for target, identity in MASSIVE_IDENTITY_CLASSES
    ]
    replay_rows.extend(
        replay_control_identity(target, identity, seed_kind)
        for target, identity, seed_kind in ZERO_REST_MASS_CONTROLS
    )
    electron_row = next(row for row in replay_rows if row["target"] == "electron")
    electron_z = Decimal(str(electron_row["Z_L"]))
    mass_rows = [row for row in replay_rows if row["zero_rest_mass_control"] == 0]
    control_rows = [row for row in replay_rows if row["zero_rest_mass_control"] == 1]

    z_estimates = {row["identity"]: row["Z_L"] for row in replay_rows}
    ratio_predictions = {
        row["target"]: ratio_to_electron(row, electron_z) for row in mass_rows
    }

    receipt: dict[str, object] = {
        "latticra_identity_replay_model2_prediction_runner_present": 1,
        "prediction_runner_id": "latticra-identity-replay-model2-prediction-runner",
        "prediction_runner_version": 1,
        "prediction_law_id": "model2-hierarchical-hash-seeded-scale-product-law",
        "model2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md",
        "model2_pre_registration_receipt_hash": pre_registration[
            "model2_pre_registration_receipt_hash"
        ],
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "candidate_substrate_id": "identity-replay-model2-hierarchical-substrate",
        "candidate_substrate_version": 1,
        "prediction_mode": "predict_only",
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "prediction_receipt_emitted_before_target_load": 1,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "particle_features_hand_declared": 0,
        "identity_patterns_generated_from_substrate": 1,
        "model2_hierarchical_substrate_present": 1,
        "hierarchical_replay_performed": 1,
        "per_scale_kappa_traces_emitted": 1,
        "active_scale_product_cost_emitted": 1,
        "mass_ratio_predictions_emitted": 1,
        "scale_levels": len(SCALE_NAMES),
        "scale_names": SCALE_NAMES,
        "repair_cost_accumulation_rule": pre_registration[
            "repair_cost_accumulation_rule"
        ],
        "zero_mass_control_rule": pre_registration["zero_mass_control_rule"],
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_present": 1,
        "gluon_zero_rest_mass_control_present": 1,
        "photon_zero_rest_mass_control_survives": int(
            next(row for row in control_rows if row["target"] == "photon")["Z_L"] == "0"
        ),
        "gluon_zero_rest_mass_control_survives": int(
            next(row for row in control_rows if row["target"] == "gluon")["Z_L"] == "0"
        ),
        "base_width": WIDTH,
        "max_cell_abs": MAX_CELL_ABS,
        "repair_cost_unit": REPAIR_COST_UNIT,
        "replay_horizon_N": REPLAY_HORIZON_N,
        "epsilon_identity_tolerance": EPSILON_IDENTITY_TOLERANCE,
        "parameter_count": PARAMETER_COUNT,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "Z_L_estimates": z_estimates,
        "mass_ratio_predictions": ratio_predictions,
        "prediction_dynamic_range": prediction_range(ratio_predictions),
        "control_Z_L_estimates": {
            row["target"]: row["Z_L"] for row in control_rows
        },
        "replay_results": replay_rows,
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
            "not_target_table_evaluation",
        ],
    }
    receipt["model2_prediction_receipt_hash"] = receipt_hash(receipt)
    receipt["model2_prediction_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--predict-only",
        action="store_true",
        help="emit Model-2 hierarchical replay predictions without target loading",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.predict_only:
        parser.error("Model-2 prediction runner currently requires --predict-only")
    print(json.dumps(build_prediction_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
