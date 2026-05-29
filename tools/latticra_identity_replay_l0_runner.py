#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Run the Latticra identity-replay impedance toy substrate L0.

The L0 runner is a falsifiability harness, not a physical mass model. It
computes deterministic toy impedance values from declared identity features,
then compares the resulting ratios against the guarded target table.
"""

from __future__ import annotations

import hashlib
import json
from decimal import Decimal, getcontext


getcontext().prec = 50

EPSILON_RELATIVE = Decimal("0.05")

PARTICLES = [
    {
        "target": "electron",
        "identity": "I_e",
        "mass_mev": Decimal("0.51099895000"),
        "features": {
            "generation": 1,
            "weak_channel": 1,
            "charge_thirds_abs": 3,
            "color_channel": 0,
            "spin_channel": 1,
            "scalar_channel": 0,
            "boundary_links": 2,
            "oscillation_nodes": 1,
            "localization_rank": 1,
            "parity_lock": 1,
        },
    },
    {
        "target": "muon",
        "identity": "I_mu",
        "mass_mev": Decimal("105.6583755"),
        "features": {
            "generation": 2,
            "weak_channel": 1,
            "charge_thirds_abs": 3,
            "color_channel": 0,
            "spin_channel": 1,
            "scalar_channel": 0,
            "boundary_links": 3,
            "oscillation_nodes": 2,
            "localization_rank": 2,
            "parity_lock": 1,
        },
    },
    {
        "target": "tau",
        "identity": "I_tau",
        "mass_mev": Decimal("1776.93"),
        "features": {
            "generation": 3,
            "weak_channel": 1,
            "charge_thirds_abs": 3,
            "color_channel": 0,
            "spin_channel": 1,
            "scalar_channel": 0,
            "boundary_links": 5,
            "oscillation_nodes": 3,
            "localization_rank": 3,
            "parity_lock": 1,
        },
    },
    {
        "target": "W boson",
        "identity": "I_W",
        "mass_mev": Decimal("80369.2"),
        "features": {
            "generation": 1,
            "weak_channel": 3,
            "charge_thirds_abs": 3,
            "color_channel": 0,
            "spin_channel": 2,
            "scalar_channel": 0,
            "boundary_links": 8,
            "oscillation_nodes": 2,
            "localization_rank": 4,
            "parity_lock": 1,
        },
    },
    {
        "target": "Z boson",
        "identity": "I_Z",
        "mass_mev": Decimal("91188.0"),
        "features": {
            "generation": 1,
            "weak_channel": 4,
            "charge_thirds_abs": 0,
            "color_channel": 0,
            "spin_channel": 2,
            "scalar_channel": 0,
            "boundary_links": 9,
            "oscillation_nodes": 2,
            "localization_rank": 4,
            "parity_lock": 1,
        },
    },
    {
        "target": "Higgs boson",
        "identity": "I_H",
        "mass_mev": Decimal("125200"),
        "features": {
            "generation": 1,
            "weak_channel": 4,
            "charge_thirds_abs": 0,
            "color_channel": 0,
            "spin_channel": 0,
            "scalar_channel": 4,
            "boundary_links": 10,
            "oscillation_nodes": 3,
            "localization_rank": 5,
            "parity_lock": 1,
        },
    },
    {
        "target": "top quark",
        "identity": "I_top",
        "mass_mev": Decimal("172560"),
        "features": {
            "generation": 3,
            "weak_channel": 2,
            "charge_thirds_abs": 2,
            "color_channel": 3,
            "spin_channel": 1,
            "scalar_channel": 0,
            "boundary_links": 12,
            "oscillation_nodes": 5,
            "localization_rank": 7,
            "parity_lock": 1,
        },
    },
]


def decimal_to_text(value: Decimal) -> str:
    normalized = value.normalize()
    if normalized == normalized.to_integral():
        return format(normalized, "f")
    return format(normalized, "f")


def toy_impedance(features: dict[str, int]) -> Decimal:
    """Compute toy impedance from identity features only.

    No measured mass target is an input to this function.
    """

    generation_term = features["generation"] ** 3 * 31
    weak_term = features["weak_channel"] ** 2 * 17
    charge_term = features["charge_thirds_abs"] ** 2 * 7
    color_term = features["color_channel"] ** 2 * 19
    spin_term = (features["spin_channel"] + 1) * 11
    scalar_term = features["scalar_channel"] ** 2 * 23
    boundary_term = features["boundary_links"] * features["oscillation_nodes"]
    localization_term = features["localization_rank"] ** 2 * 5
    parity_term = features["parity_lock"] * 13
    return Decimal(
        generation_term
        + weak_term
        + charge_term
        + color_term
        + spin_term
        + scalar_term
        + boundary_term
        + localization_term
        + parity_term
    )


def row_prediction(particle: dict[str, object], electron_z: Decimal) -> dict[str, object]:
    mass_mev = particle["mass_mev"]
    if not isinstance(mass_mev, Decimal):
        raise TypeError("mass_mev must be Decimal")
    features = particle["features"]
    if not isinstance(features, dict):
        raise TypeError("features must be a mapping")

    z_l = toy_impedance(features)
    predicted_ratio = z_l / electron_z
    target_ratio = mass_mev / PARTICLES[0]["mass_mev"]
    absolute_error = abs(predicted_ratio - target_ratio)
    relative_error = absolute_error / target_ratio if target_ratio else Decimal("0")
    survives = relative_error <= EPSILON_RELATIVE

    return {
        "target": particle["target"],
        "identity": particle["identity"],
        "features": features,
        "toy_Z_L": decimal_to_text(z_l),
        "predicted_ratio_to_electron": decimal_to_text(predicted_ratio),
        "target_ratio_to_electron": decimal_to_text(target_ratio),
        "absolute_error": decimal_to_text(absolute_error),
        "relative_error": decimal_to_text(relative_error),
        "survives_epsilon": survives,
    }


def cross_ratio(predictions: dict[str, dict[str, object]], numerator: str, denominator: str) -> dict[str, str]:
    predicted = Decimal(str(predictions[numerator]["toy_Z_L"])) / Decimal(
        str(predictions[denominator]["toy_Z_L"])
    )
    target_mass = next(p["mass_mev"] for p in PARTICLES if p["target"] == numerator)
    denominator_mass = next(p["mass_mev"] for p in PARTICLES if p["target"] == denominator)
    target = target_mass / denominator_mass
    return {
        "predicted": decimal_to_text(predicted),
        "target": decimal_to_text(target),
        "absolute_error": decimal_to_text(abs(predicted - target)),
    }


def build_receipt() -> dict[str, object]:
    electron_z = toy_impedance(PARTICLES[0]["features"])
    prediction_rows = [row_prediction(particle, electron_z) for particle in PARTICLES]
    predictions = {row["target"]: row for row in prediction_rows}
    candidate_survives = all(row["survives_epsilon"] for row in prediction_rows)

    receipt = {
        "latticra_identity_replay_impedance_toy_substrate_l0_mass_ratio_runner_present": 1,
        "runner_id": "latticra-identity-replay-impedance-toy-substrate-l0-mass-ratio-runner",
        "runner_version": 1,
        "candidate_substrate_id": "identity-replay-impedance-toy-l0",
        "candidate_substrate_version": 1,
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "state_space_definition": "finite symbolic identity-feature lattice",
        "local_update_operator": "deterministic feature replay with bounded symbolic repair",
        "observer_projection": "feature-vector projection before target comparison",
        "identity_quotient": "candidate identity label over projected feature vector",
        "distance_metric": "L1 feature drift over projected symbolic state",
        "counterfactual_repair_cost_function": "toy_impedance(identity_features)",
        "target_values_loaded_after_predictions": 1,
        "measured_masses_used_in_kappa": 0,
        "receipt_generation_required": 1,
        "toy_Z_L_values_computed": 1,
        "toy_mass_ratio_predictions_computed": 1,
        "target_error_vector_computed": 1,
        "epsilon_relative": decimal_to_text(EPSILON_RELATIVE),
        "candidate_survives_target_table": int(candidate_survives),
        "mass_ratio_recovery_claimed": 0,
        "standard_model_replacement_claimed": 0,
        "higgs_denied": 0,
        "simulation_proven": 0,
        "scientific_claim_promoted": 0,
        "predictions": prediction_rows,
        "cross_ratios": {
            "tau_over_muon": cross_ratio(predictions, "tau", "muon"),
            "W_over_Z": cross_ratio(predictions, "W boson", "Z boson"),
            "Higgs_over_Z": cross_ratio(predictions, "Higgs boson", "Z boson"),
            "top_over_Higgs": cross_ratio(predictions, "top quark", "Higgs boson"),
        },
        "failure_record_if_any_target_breaks": [
            row["identity"]
            for row in prediction_rows
            if not row["survives_epsilon"]
        ],
        "non_claims": [
            "not_a_standard_model_replacement",
            "not_a_higgs_denial",
            "not_simulation_proof",
            "not_mass_ratio_recovery",
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
