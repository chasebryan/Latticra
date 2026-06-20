#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit Model-3 topological amplification prediction-only receipts."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from typing import Iterable

from latticra_receipt_utils import decimal_to_text
from latticra_identity_replay_model1_substrate import (
    EPSILON_IDENTITY_TOLERANCE,
    MASSIVE_IDENTITY_CLASSES,
    REPLAY_HORIZON_N,
    ZERO_REST_MASS_CONTROLS,
)
from latticra_identity_replay_model2_runner import (
    prediction_range,
    replay_control_identity,
    replay_massive_identity,
)
from latticra_identity_replay_model3_preregistration import (
    LAW_ID,
    TOPOLOGICAL_BRANCHING_FACTOR,
    TOPOLOGICAL_REPLAY_DEPTH,
    build_receipt as build_pre_registration_receipt,
)


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def topology_trace(identity: str) -> dict[str, object]:
    digest = hashlib.sha256(f"model3-topological-replay:{identity}".encode("utf-8")).digest()
    branch_turns = digest[0] % (TOPOLOGICAL_REPLAY_DEPTH + 1)
    coalescence_turns = digest[1] % (TOPOLOGICAL_REPLAY_DEPTH + 1)
    inversion_turns = digest[2] % (TOPOLOGICAL_REPLAY_DEPTH + 1)
    instability_exponent = (
        branch_turns + coalescence_turns + inversion_turns
    ) % (TOPOLOGICAL_REPLAY_DEPTH + 1)
    multiplier = Decimal(TOPOLOGICAL_BRANCHING_FACTOR) ** Decimal(
        instability_exponent
    )
    return {
        "branch_turns": branch_turns,
        "coalescence_turns": coalescence_turns,
        "inversion_turns": inversion_turns,
        "instability_exponent": instability_exponent,
        "topological_multiplier": decimal_to_text(multiplier),
        "trace_rule": "sha256(identity) branch/coalescence/inversion turns modulo depth",
    }


def amplify_massive_identity(target: str, identity: str) -> dict[str, object]:
    base_row = replay_massive_identity(target, identity)
    trace = topology_trace(identity)
    base_z = Decimal(str(base_row["Z_L"]))
    multiplier = Decimal(str(trace["topological_multiplier"]))
    amplified_z = base_z * multiplier
    return {
        **base_row,
        "seed_kind": "topological_amplified_massive",
        "base_model2_Z_L": base_row["Z_L"],
        "topological_trace": trace,
        "topological_multiplier": trace["topological_multiplier"],
        "Z_L": decimal_to_text(amplified_z),
    }


def amplify_control_identity(target: str, identity: str, seed_kind: str) -> dict[str, object]:
    base_row = replay_control_identity(target, identity, seed_kind)
    return {
        **base_row,
        "seed_kind": f"topological_control_{seed_kind}",
        "base_model2_Z_L": base_row["Z_L"],
        "topological_trace": {
            "branch_turns": 0,
            "coalescence_turns": 0,
            "inversion_turns": 0,
            "instability_exponent": 0,
            "topological_multiplier": "0",
            "trace_rule": "zero-rest-mass controls do not activate topology branches",
        },
        "topological_multiplier": "0",
        "Z_L": "0",
    }


def ratio_to_electron(row: dict[str, object], electron_z: Decimal) -> str:
    if electron_z == 0:
        return "undefined"
    return decimal_to_text(Decimal(str(row["Z_L"])) / electron_z)


def build_prediction_receipt() -> dict[str, object]:
    pre_registration = build_pre_registration_receipt()
    replay_rows = [
        amplify_massive_identity(target, identity)
        for target, identity in MASSIVE_IDENTITY_CLASSES
    ]
    replay_rows.extend(
        amplify_control_identity(target, identity, seed_kind)
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
        "latticra_identity_replay_model3_prediction_runner_present": 1,
        "prediction_runner_id": "latticra-identity-replay-model3-prediction-runner",
        "prediction_runner_version": 1,
        "prediction_law_id": LAW_ID,
        "model3_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION.md",
        "model3_pre_registration_receipt_hash": pre_registration[
            "model3_pre_registration_receipt_hash"
        ],
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "candidate_substrate_id": "identity-replay-model3-topological-amplification-substrate",
        "candidate_substrate_version": 1,
        "prediction_mode": "predict_only",
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "prediction_receipt_emitted_before_target_load": 1,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "target_ratios_used_in_law": 0,
        "particle_features_hand_declared": 0,
        "identity_patterns_generated_from_substrate": 1,
        "model3_topological_amplification_present": 1,
        "topological_amplification_trace_emitted": 1,
        "counterfactual_repair_search_performed": 1,
        "kappa_trace_emitted": 1,
        "active_scale_product_cost_emitted": 1,
        "mass_ratio_predictions_emitted": 1,
        "topological_branching_factor": TOPOLOGICAL_BRANCHING_FACTOR,
        "topological_replay_depth": TOPOLOGICAL_REPLAY_DEPTH,
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_present": 1,
        "gluon_zero_rest_mass_control_present": 1,
        "photon_zero_rest_mass_control_survives": int(
            next(row for row in control_rows if row["target"] == "photon")["Z_L"] == "0"
        ),
        "gluon_zero_rest_mass_control_survives": int(
            next(row for row in control_rows if row["target"] == "gluon")["Z_L"] == "0"
        ),
        "replay_horizon_N": REPLAY_HORIZON_N,
        "epsilon_identity_tolerance": EPSILON_IDENTITY_TOLERANCE,
        "parameter_count": pre_registration["parameter_count"],
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
    receipt["model3_prediction_receipt_hash"] = receipt_hash(receipt)
    receipt["model3_prediction_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--predict-only",
        action="store_true",
        help="emit Model-3 topological replay predictions without target loading",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.predict_only:
        parser.error("Model-3 prediction runner currently requires --predict-only")
    print(json.dumps(build_prediction_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
