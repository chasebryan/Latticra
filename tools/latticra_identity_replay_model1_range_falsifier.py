#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Falsify bounded Model-1 replay range against target mass ratios."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_receipt_utils import decimal_to_text, parse_target_table
from latticra_identity_replay_model1_substrate import (
    EPSILON_IDENTITY_TOLERANCE,
    MAX_CELL_ABS,
    PARAMETER_COUNT,
    REPAIR_COST_UNIT,
    REPLAY_HORIZON_N,
    WIDTH,
    build_prediction_receipt,
)


getcontext().prec = 50


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def target_ratio_summary(
    targets: dict[str, dict[str, str]], generous_ratio_bound: Decimal
) -> tuple[str, list[dict[str, object]]]:
    max_target = Decimal("0")
    exceeded_rows = []
    for target, row in targets.items():
        ratio = Decimal(row["ratio_to_electron"])
        if ratio > max_target:
            max_target = ratio
        if ratio > generous_ratio_bound:
            exceeded_rows.append(
                {
                    "target": target,
                    "identity": row["identity"],
                    "target_ratio_to_electron": decimal_to_text(ratio),
                    "generous_bound": decimal_to_text(generous_ratio_bound),
                    "exceeds_bound": 1,
                }
            )
    return decimal_to_text(max_target), exceeded_rows


def build_receipt(target_path: Path) -> dict[str, object]:
    prediction = build_prediction_receipt()
    targets, _cross_ratios = parse_target_table(target_path)

    max_cell_delta = Decimal(2 * MAX_CELL_ABS)
    max_kappa_per_step = Decimal(WIDTH) * max_cell_delta * Decimal(REPAIR_COST_UNIT)
    min_positive_horizon_mean = Decimal(REPAIR_COST_UNIT) / Decimal(REPLAY_HORIZON_N)
    generous_ratio_bound = max_kappa_per_step / min_positive_horizon_mean
    stationary_ratio_bound = max_kappa_per_step / Decimal(REPAIR_COST_UNIT)
    target_max_ratio, exceeded_rows = target_ratio_summary(targets, generous_ratio_bound)
    target_dynamic_range_exceeds_model_bound = int(bool(exceeded_rows))

    receipt: dict[str, object] = {
        "latticra_identity_replay_model1_bounded_range_falsifier_present": 1,
        "falsifier_id": "latticra-identity-replay-model1-bounded-range-falsifier",
        "falsifier_version": 1,
        "model1_runner_reference": "tools/latticra_identity_replay_model1_substrate.py",
        "model1_evaluator_reference": "tools/latticra_identity_replay_model1_evaluate.py",
        "target_table_reference": str(target_path),
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "bounded_substrate_class_scope": (
            "Model-1 finite cyclic bounded-cell L1 repair substrate"
        ),
        "state_space_definition": prediction["state_space_definition"],
        "local_update_operator": prediction["local_update_operator"],
        "identity_quotient": prediction["identity_quotient"],
        "distance_metric": prediction["distance_metric"],
        "counterfactual_repair_cost_function": prediction[
            "counterfactual_repair_cost_function"
        ],
        "width": WIDTH,
        "max_cell_abs": MAX_CELL_ABS,
        "repair_cost_unit": REPAIR_COST_UNIT,
        "replay_horizon_N": REPLAY_HORIZON_N,
        "epsilon_identity_tolerance": EPSILON_IDENTITY_TOLERANCE,
        "parameter_count": PARAMETER_COUNT,
        "target_count": len(targets),
        "parameter_count_less_than_target_count": int(PARAMETER_COUNT < len(targets)),
        "max_cell_delta": decimal_to_text(max_cell_delta),
        "max_kappa_per_step": decimal_to_text(max_kappa_per_step),
        "max_Z_L_under_bounded_repair": decimal_to_text(max_kappa_per_step),
        "min_positive_horizon_mean": decimal_to_text(min_positive_horizon_mean),
        "max_ratio_bound_with_current_stationary_replay": decimal_to_text(
            stationary_ratio_bound
        ),
        "max_ratio_bound_with_any_nonzero_horizon_mean": decimal_to_text(
            generous_ratio_bound
        ),
        "target_max_ratio_to_electron": target_max_ratio,
        "target_ratio_exceeds_bounded_model1_range": target_dynamic_range_exceeds_model_bound,
        "targets_exceeding_bounded_range": exceeded_rows,
        "model1_bounded_substrate_class_falsified": target_dynamic_range_exceeds_model_bound,
        "bounded_model1_conclusion": (
            "falsified_as_mass_ratio_recovery_candidate"
            if target_dynamic_range_exceeds_model_bound
            else "not_falsified_by_range_bound"
        ),
        "required_next_substrate_property": (
            "hierarchical or multiscale impedance range before target-table recovery "
            "can be credible"
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
    receipt["falsifier_receipt_hash"] = receipt_hash(receipt)
    receipt["falsifier_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--targets", required=True, help="guarded target table markdown")
    args = parser.parse_args(list(argv) if argv is not None else None)
    print(json.dumps(build_receipt(Path(args.targets)), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
