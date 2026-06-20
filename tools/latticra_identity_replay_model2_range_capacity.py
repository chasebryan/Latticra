#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Evaluate Model-2 hierarchical replay range capacity after pre-registration."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_receipt_utils import decimal_to_text, parse_target_table


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def pre_registration_hash(payload: dict[str, object]) -> str:
    canonical_payload = dict(payload)
    canonical_payload.pop("model2_pre_registration_receipt_hash", None)
    canonical_payload.pop("model2_pre_registration_receipt_hash_generated", None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def load_pre_registration(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-2 pre-registration receipt must be a JSON object")
    return payload


def target_max_ratio(targets: dict[str, dict[str, str]]) -> tuple[Decimal, str]:
    max_ratio = Decimal("0")
    max_identity = ""
    for row in targets.values():
        ratio = Decimal(row["ratio_to_electron"])
        if ratio > max_ratio:
            max_ratio = ratio
            max_identity = row["identity"]
    return max_ratio, max_identity


def build_receipt(pre_registration_path: Path, target_path: Path) -> dict[str, object]:
    pre_registration = load_pre_registration(pre_registration_path)
    expected_hash = pre_registration_hash(pre_registration)
    observed_hash = pre_registration.get("model2_pre_registration_receipt_hash")
    pre_registration_hash_valid = int(observed_hash == expected_hash)

    targets, _cross_ratios = parse_target_table(target_path)
    max_ratio, max_identity = target_max_ratio(targets)
    capacity = Decimal(
        str(pre_registration["hierarchical_max_ratio_bound_before_target_load"])
    )
    stationary_capacity = Decimal(
        str(pre_registration["hierarchical_max_Z_L_before_target_load"])
    )
    capacity_margin = capacity / max_ratio if max_ratio else Decimal("0")
    stationary_capacity_margin = (
        stationary_capacity / max_ratio if max_ratio else Decimal("0")
    )
    capacity_sufficient = int(capacity >= max_ratio)
    stationary_capacity_sufficient = int(stationary_capacity >= max_ratio)
    parameter_count = int(pre_registration.get("parameter_count", 999999))

    receipt: dict[str, object] = {
        "latticra_identity_replay_model2_hierarchical_range_capacity_present": 1,
        "range_capacity_id": "latticra-identity-replay-model2-hierarchical-range-capacity",
        "range_capacity_version": 1,
        "pre_registration_receipt_reference": str(pre_registration_path),
        "target_table_reference": str(target_path),
        "model2_pre_registration_receipt_hash": observed_hash,
        "model2_pre_registration_receipt_hash_recomputed": expected_hash,
        "model2_pre_registration_receipt_hash_valid": pre_registration_hash_valid,
        "pre_registered_before_target_load": pre_registration.get(
            "pre_registered_before_target_load"
        ),
        "pre_registration_target_table_loaded": pre_registration.get(
            "target_table_loaded"
        ),
        "pre_registration_target_comparison_performed": pre_registration.get(
            "target_comparison_performed"
        ),
        "target_table_loaded": 1,
        "target_load_after_pre_registration_receipt": int(
            pre_registration_hash_valid == 1
            and pre_registration.get("pre_registered_before_target_load") == 1
            and pre_registration.get("target_table_loaded") == 0
        ),
        "dynamic_range_capacity_evaluated_against_targets": 1,
        "target_ratio_recovery_evaluated": 0,
        "mass_ratio_predictions_emitted": pre_registration.get(
            "mass_ratio_predictions_emitted"
        ),
        "model2_hierarchical_substrate_present": pre_registration.get(
            "model2_hierarchical_substrate_present"
        ),
        "scale_levels": pre_registration.get("scale_levels"),
        "scale_names": pre_registration.get("scale_names"),
        "base_max_kappa_per_step": pre_registration.get("base_max_kappa_per_step"),
        "hierarchical_max_Z_L_before_target_load": pre_registration.get(
            "hierarchical_max_Z_L_before_target_load"
        ),
        "hierarchical_max_ratio_bound_before_target_load": pre_registration.get(
            "hierarchical_max_ratio_bound_before_target_load"
        ),
        "target_max_ratio_to_electron": decimal_to_text(max_ratio),
        "target_max_ratio_identity": max_identity,
        "hierarchical_capacity_margin_over_target": decimal_to_text(capacity_margin),
        "hierarchical_stationary_capacity_margin_over_target": decimal_to_text(
            stationary_capacity_margin
        ),
        "target_ratio_within_model2_hierarchical_capacity": capacity_sufficient,
        "target_ratio_within_model2_stationary_capacity": stationary_capacity_sufficient,
        "model2_not_falsified_by_range_bound": capacity_sufficient,
        "model2_range_capacity_conclusion": (
            "range_capacity_sufficient_for_target_vector"
            if capacity_sufficient
            else "range_capacity_insufficient_for_target_vector"
        ),
        "required_next_artifact": (
            "Model-2 prediction-only hierarchical replay runner before any "
            "mass-ratio recovery claim"
        ),
        "parameter_count": parameter_count,
        "target_count": len(targets),
        "parameter_count_less_than_target_count": int(parameter_count < len(targets)),
        "candidate_survives_target_table": 0,
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
            "not_target_table_prediction",
            "not_scientific_claim_promotion",
        ],
    }
    receipt["model2_range_capacity_receipt_hash"] = receipt_hash(receipt)
    receipt["model2_range_capacity_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pre-registration", required=True)
    parser.add_argument("--targets", required=True)
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_receipt(Path(args.pre_registration), Path(args.targets))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
