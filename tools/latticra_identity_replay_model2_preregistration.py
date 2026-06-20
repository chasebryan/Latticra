#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Pre-register the Model-2 hierarchical replay substrate law."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from typing import Iterable

from latticra_receipt_utils import decimal_to_text
from latticra_identity_replay_model1_substrate import (
    EPSILON_IDENTITY_TOLERANCE,
    MAX_CELL_ABS,
    REPAIR_COST_UNIT,
    REPLAY_HORIZON_N,
    WIDTH,
)


getcontext().prec = 80

SCALE_LEVELS = 4
PARAMETER_COUNT = 6
SCALE_NAMES = [
    "local_identity",
    "family_replay",
    "electroweak_projection",
    "heavy_sector_closure",
]


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def model1_max_kappa_per_step() -> Decimal:
    max_cell_delta = Decimal(2 * MAX_CELL_ABS)
    return Decimal(WIDTH) * max_cell_delta * Decimal(REPAIR_COST_UNIT)


def hierarchical_max_z() -> Decimal:
    return model1_max_kappa_per_step() ** Decimal(SCALE_LEVELS)


def hierarchical_min_positive_mean() -> Decimal:
    return Decimal(REPAIR_COST_UNIT) / Decimal(REPLAY_HORIZON_N)


def build_receipt() -> dict[str, object]:
    max_kappa = model1_max_kappa_per_step()
    max_z = hierarchical_max_z()
    min_positive_mean = hierarchical_min_positive_mean()
    max_ratio_bound = max_z / min_positive_mean

    receipt: dict[str, object] = {
        "latticra_identity_replay_model2_hierarchical_substrate_preregistration_present": 1,
        "pre_registration_id": "latticra-identity-replay-model2-hierarchical-substrate-preregistration",
        "pre_registration_version": 1,
        "model1_bounded_range_falsifier_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "pre_registered_before_target_load": 1,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "particle_features_hand_declared": 0,
        "mass_ratio_predictions_emitted": 0,
        "model2_hierarchical_substrate_present": 1,
        "candidate_substrate_id": "identity-replay-model2-hierarchical-substrate",
        "candidate_substrate_version": 1,
        "state_space_definition": (
            "nested finite cyclic integer lattices with shared width=17 and "
            "bounded cells across four replay scales"
        ),
        "scale_levels": SCALE_LEVELS,
        "scale_names": SCALE_NAMES,
        "local_state_per_level": (
            f"cyclic integer lattice width={WIDTH}, cell_range=[-{MAX_CELL_ABS},{MAX_CELL_ABS}]"
        ),
        "local_update_operator": "T_l(x_i)=clip(x_i + x_{i-1} - x_{i+1}) per scale",
        "cross_scale_coupling_rule": (
            "higher scale repair activates only when lower scale identity repair "
            "is nonzero; scale weights multiply, not add"
        ),
        "identity_projection_across_scales": (
            "tuple of per-scale cyclic quotient representatives plus cross-scale "
            "activation mask"
        ),
        "identity_quotient": (
            "lexicographically minimal cyclic rotation at each scale, then "
            "scale tuple quotient"
        ),
        "distance_metric": "sum of per-scale L1 quotient distances with multiplicative scale activation",
        "repair_cost_accumulation_rule": (
            "Z_L = product(max(1, kappa_level_mean)) over active replay scales"
        ),
        "counterfactual_repair_cost_function": (
            "minimal per-cell additive edits per scale, accumulated through "
            "multiplicative active-scale replay"
        ),
        "zero_mass_control_rule": (
            "all-zero and uniform synchronized cross-scale states remain fixed "
            "under update and produce zero active repair cost"
        ),
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_present": 1,
        "gluon_zero_rest_mass_control_present": 1,
        "base_width": WIDTH,
        "max_cell_abs": MAX_CELL_ABS,
        "repair_cost_unit": REPAIR_COST_UNIT,
        "replay_horizon_N": REPLAY_HORIZON_N,
        "epsilon_identity_tolerance": EPSILON_IDENTITY_TOLERANCE,
        "base_max_kappa_per_step": decimal_to_text(max_kappa),
        "hierarchical_max_Z_L_before_target_load": decimal_to_text(max_z),
        "hierarchical_min_positive_horizon_mean": decimal_to_text(min_positive_mean),
        "hierarchical_max_ratio_bound_before_target_load": decimal_to_text(
            max_ratio_bound
        ),
        "parameter_count": PARAMETER_COUNT,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "dynamic_range_capacity_evaluated_against_targets": 0,
        "target_ratio_recovery_evaluated": 0,
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
    receipt["model2_pre_registration_receipt_hash"] = receipt_hash(receipt)
    receipt["model2_pre_registration_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--pre-register",
        action="store_true",
        help="emit the Model-2 pre-registration receipt without target loading",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.pre_register:
        parser.error("Model-2 currently requires --pre-register")
    print(json.dumps(build_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
