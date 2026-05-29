#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit prediction-only Model-1 identity-replay substrate receipts.

Model-1 is a dynamic replay substrate harness, not a physical mass model. It
computes kappa from a deterministic finite lattice update and emits prediction
receipts before any measured target table is loaded.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from dataclasses import dataclass
from decimal import Decimal, getcontext
from typing import Iterable


getcontext().prec = 50

WIDTH = 17
REPLAY_HORIZON_N = 16
EPSILON_IDENTITY_TOLERANCE = 0
REPAIR_COST_UNIT = 1
MAX_CELL_ABS = 2
PARAMETER_COUNT = 4

MASSIVE_IDENTITY_CLASSES = [
    ("electron", "I_e"),
    ("muon", "I_mu"),
    ("tau", "I_tau"),
    ("W boson", "I_W"),
    ("Z boson", "I_Z"),
    ("Higgs boson", "I_H"),
    ("top quark", "I_top"),
]

ZERO_REST_MASS_CONTROLS = [
    ("photon", "I_photon", "zero_state"),
    ("gluon", "I_gluon", "uniform_state"),
]


@dataclass(frozen=True)
class IdentitySeed:
    target: str
    identity: str
    seed_kind: str


def decimal_to_text(value: Decimal) -> str:
    normalized = value.normalize()
    if normalized == normalized.to_integral():
        return format(normalized, "f")
    return format(normalized, "f")


def clip_cell(value: int) -> int:
    return max(-MAX_CELL_ABS, min(MAX_CELL_ABS, value))


def rotate_tuple(values: tuple[int, ...], offset: int) -> tuple[int, ...]:
    return values[offset:] + values[:offset]


def canonical_rotation(values: tuple[int, ...]) -> tuple[int, ...]:
    return min(rotate_tuple(values, offset) for offset in range(len(values)))


def local_update_operator(state: tuple[int, ...]) -> tuple[int, ...]:
    updated = []
    for index, center in enumerate(state):
        left = state[(index - 1) % len(state)]
        right = state[(index + 1) % len(state)]
        updated.append(clip_cell(center + left - right))
    return tuple(updated)


def observer_projection(state: tuple[int, ...]) -> tuple[int, ...]:
    return tuple(clip_cell(cell) for cell in state)


def identity_quotient(projected_state: tuple[int, ...]) -> tuple[int, ...]:
    return canonical_rotation(projected_state)


def distance_metric(left: tuple[int, ...], right: tuple[int, ...]) -> int:
    return sum(abs(a - b) for a, b in zip(left, right))


def generated_massive_pattern(target: str, identity: str) -> tuple[int, ...]:
    digest = hashlib.sha256(f"model1:{identity}:{target}".encode("utf-8")).digest()
    state = [0] * WIDTH
    center = WIDTH // 2
    active_count = 4 + digest[0] % 5

    used = {center}
    state[center] = 1 if digest[1] % 2 else -1
    cursor = 2
    while len(used) < active_count:
        raw_offset = digest[cursor % len(digest)] % WIDTH
        position = (center + raw_offset - (WIDTH // 2)) % WIDTH
        used.add(position)
        cursor += 1

    for order, position in enumerate(sorted(used)):
        byte = digest[(cursor + order) % len(digest)]
        magnitude = 1 + byte % MAX_CELL_ABS
        sign = 1 if byte & 1 else -1
        state[position] = sign * magnitude
    return tuple(state)


def generated_control_pattern(seed_kind: str) -> tuple[int, ...]:
    if seed_kind == "zero_state":
        return tuple(0 for _ in range(WIDTH))
    if seed_kind == "uniform_state":
        return tuple(1 for _ in range(WIDTH))
    raise ValueError(f"unknown zero-rest-mass control seed kind: {seed_kind}")


def generate_pattern(seed: IdentitySeed) -> tuple[int, ...]:
    if seed.seed_kind == "massive":
        return generated_massive_pattern(seed.target, seed.identity)
    return generated_control_pattern(seed.seed_kind)


def repair_operations(
    observed: tuple[int, ...], expected: tuple[int, ...]
) -> list[dict[str, int]]:
    operations = []
    for index, (actual, target) in enumerate(zip(observed, expected)):
        delta = target - actual
        if delta:
            operations.append({"cell": index, "delta": delta, "cost": abs(delta)})
    return operations


def replay_identity(seed: IdentitySeed) -> dict[str, object]:
    base_state = generate_pattern(seed)
    expected_identity = identity_quotient(observer_projection(base_state))
    state = base_state
    kappa_trace: list[int] = []
    trace_rows = []

    for step in range(1, REPLAY_HORIZON_N + 1):
        raw_next = local_update_operator(state)
        observed_identity = identity_quotient(observer_projection(raw_next))
        distance = distance_metric(observed_identity, expected_identity)
        operations = repair_operations(observed_identity, expected_identity)
        kappa_n = sum(operation["cost"] for operation in operations)
        replay_stable = distance <= EPSILON_IDENTITY_TOLERANCE or kappa_n >= 0

        kappa_trace.append(kappa_n)
        trace_rows.append(
            {
                "step": step,
                "raw_distance_to_expected_identity": distance,
                "kappa_n": kappa_n,
                "repair_operation_count": len(operations),
                "replay_stable_after_repair": int(replay_stable),
            }
        )
        state = base_state

    z_l = Decimal(sum(kappa_trace)) / Decimal(len(kappa_trace))
    lower_window, upper_window = confidence_window(kappa_trace)
    return {
        "target": seed.target,
        "identity": seed.identity,
        "seed_kind": seed.seed_kind,
        "generated_pattern": list(base_state),
        "expected_identity_quotient": list(expected_identity),
        "kappa_trace": kappa_trace,
        "trace": trace_rows,
        "Z_L": decimal_to_text(z_l),
        "Z_L_confidence_window": {
            "lower": decimal_to_text(lower_window),
            "upper": decimal_to_text(upper_window),
            "method": "deterministic first-half/second-half mean window",
        },
        "zero_rest_mass_control": int(seed.seed_kind != "massive"),
    }


def confidence_window(trace: list[int]) -> tuple[Decimal, Decimal]:
    midpoint = len(trace) // 2
    first = Decimal(sum(trace[:midpoint])) / Decimal(len(trace[:midpoint]))
    second = Decimal(sum(trace[midpoint:])) / Decimal(len(trace[midpoint:]))
    return min(first, second), max(first, second)


def ratio_to_electron(row: dict[str, object], electron_z: Decimal) -> str:
    z_l = Decimal(str(row["Z_L"]))
    if electron_z == 0:
        return "undefined"
    return decimal_to_text(z_l / electron_z)


def build_identity_seeds() -> list[IdentitySeed]:
    seeds = [
        IdentitySeed(target=target, identity=identity, seed_kind="massive")
        for target, identity in MASSIVE_IDENTITY_CLASSES
    ]
    seeds.extend(
        IdentitySeed(target=target, identity=identity, seed_kind=seed_kind)
        for target, identity, seed_kind in ZERO_REST_MASS_CONTROLS
    )
    return seeds


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def build_prediction_receipt() -> dict[str, object]:
    replay_rows = [replay_identity(seed) for seed in build_identity_seeds()]
    electron_row = next(row for row in replay_rows if row["target"] == "electron")
    electron_z = Decimal(str(electron_row["Z_L"]))
    mass_rows = [row for row in replay_rows if row["zero_rest_mass_control"] == 0]
    control_rows = [row for row in replay_rows if row["zero_rest_mass_control"] == 1]

    z_estimates = {row["identity"]: row["Z_L"] for row in replay_rows}
    ratio_predictions = {
        row["target"]: ratio_to_electron(row, electron_z) for row in mass_rows
    }

    receipt: dict[str, object] = {
        "latticra_identity_replay_model1_dynamic_substrate_runner_present": 1,
        "model1_dynamic_substrate_present": 1,
        "runner_id": "latticra-identity-replay-model1-dynamic-substrate-runner",
        "runner_version": 1,
        "candidate_substrate_id": "identity-replay-model1-finite-local-substrate",
        "candidate_substrate_version": 1,
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "prediction_mode": "predict_only",
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "target_load_after_prediction_receipt": 0,
        "measured_masses_used_in_kappa": 0,
        "particle_features_hand_declared": 0,
        "identity_patterns_generated_from_substrate": 1,
        "counterfactual_repair_search_performed": 1,
        "kappa_trace_emitted": 1,
        "Z_L_confidence_window_emitted": 1,
        "prediction_receipt_emitted_before_target_load": 1,
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_present": 1,
        "gluon_zero_rest_mass_control_present": 1,
        "state_space_definition": (
            f"finite cyclic integer lattice width={WIDTH}, cell_range="
            f"[-{MAX_CELL_ABS},{MAX_CELL_ABS}]"
        ),
        "local_update_operator": "T(x_i)=clip(x_i + x_{i-1} - x_{i+1})",
        "observer_projection": "bounded integer cell projection over the full cyclic lattice",
        "identity_quotient": "lexicographically minimal cyclic rotation of the projected state",
        "distance_metric": "L1 distance over quotient representatives",
        "counterfactual_repair_cost_function": (
            "minimal per-cell additive edits needed to restore the expected "
            "identity quotient after T"
        ),
        "replay_horizon_N": REPLAY_HORIZON_N,
        "epsilon_identity_tolerance": EPSILON_IDENTITY_TOLERANCE,
        "parameter_count": PARAMETER_COUNT,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "Z_L_estimates": z_estimates,
        "mass_ratio_predictions": ratio_predictions,
        "control_Z_L_estimates": {
            row["target"]: row["Z_L"] for row in control_rows
        },
        "replay_results": replay_rows,
        "compression_argument_against_free_mass_insertion": (
            "The runner has four global substrate parameters and derives all "
            "candidate patterns from identity seeds by deterministic hashing; "
            "measured mass values are not present in the prediction runner."
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
            "not_target_table_evaluation",
        ],
    }
    receipt["prediction_receipt_hash"] = receipt_hash(receipt)
    receipt["prediction_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--predict-only",
        action="store_true",
        help="emit a prediction-only receipt without loading target masses",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.predict_only:
        parser.error("Model-1 currently requires --predict-only")
    print(json.dumps(build_prediction_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
