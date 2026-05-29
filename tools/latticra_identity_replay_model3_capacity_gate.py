#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Evaluate Model-3 topological amplification capacity after pre-registration."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_identity_replay_model1_evaluate import decimal_to_text, parse_target_table


getcontext().prec = 80


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def pre_registration_hash(payload: dict[str, object]) -> str:
    canonical_payload = dict(payload)
    canonical_payload.pop("model3_pre_registration_receipt_hash", None)
    canonical_payload.pop("model3_pre_registration_receipt_hash_generated", None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def load_pre_registration(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-3 pre-registration receipt must be a JSON object")
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
    observed_hash = pre_registration.get("model3_pre_registration_receipt_hash")
    hash_valid = int(observed_hash == expected_hash)

    targets, _cross_ratios = parse_target_table(target_path)
    max_ratio, max_identity = target_max_ratio(targets)
    model3_bound = Decimal(
        str(pre_registration["model3_topological_max_ratio_bound_before_target_load"])
    )
    model2_bound = Decimal(
        str(pre_registration["model2_hierarchical_max_ratio_bound_before_target_load"])
    )
    multiplier = Decimal(
        str(pre_registration["topological_amplification_multiplier_before_target_load"])
    )
    capacity_margin = model3_bound / max_ratio if max_ratio else Decimal("0")
    model2_margin = model2_bound / max_ratio if max_ratio else Decimal("0")
    capacity_sufficient = int(model3_bound >= max_ratio)
    parameter_count = int(pre_registration.get("parameter_count", 999999))
    params_ok = int(parameter_count < len(targets))

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_topological_capacity_gate_present": 1,
        "capacity_gate_id": "latticra-identity-replay-model3-topological-capacity-gate",
        "capacity_gate_version": 1,
        "pre_registration_receipt_reference": str(pre_registration_path),
        "target_table_reference": str(target_path),
        "model3_pre_registration_receipt_hash": observed_hash,
        "model3_pre_registration_receipt_hash_recomputed": expected_hash,
        "model3_pre_registration_receipt_hash_valid": hash_valid,
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
            hash_valid == 1
            and pre_registration.get("pre_registered_before_target_load") == 1
            and pre_registration.get("target_table_loaded") == 0
        ),
        "dynamic_range_capacity_evaluated_against_targets": 1,
        "target_ratio_recovery_evaluated": 0,
        "mass_ratio_predictions_emitted": pre_registration.get(
            "mass_ratio_predictions_emitted"
        ),
        "model3_law_id": pre_registration.get("model3_law_id"),
        "model3_topological_amplification_present": pre_registration.get(
            "model3_topological_amplification_present"
        ),
        "topological_amplification_trace_required": pre_registration.get(
            "topological_amplification_trace_required"
        ),
        "target_blind_dynamic_range_proof_before_prediction": pre_registration.get(
            "target_blind_dynamic_range_proof_before_prediction"
        ),
        "topological_branching_factor": pre_registration.get(
            "topological_branching_factor"
        ),
        "topological_replay_depth": pre_registration.get("topological_replay_depth"),
        "quotient_instability_layers": pre_registration.get(
            "quotient_instability_layers"
        ),
        "model2_hierarchical_max_ratio_bound_before_target_load": decimal_to_text(
            model2_bound
        ),
        "topological_amplification_multiplier_before_target_load": decimal_to_text(
            multiplier
        ),
        "model3_topological_max_ratio_bound_before_target_load": decimal_to_text(
            model3_bound
        ),
        "target_max_ratio_to_electron": decimal_to_text(max_ratio),
        "target_max_ratio_identity": max_identity,
        "model2_capacity_margin_over_target": decimal_to_text(model2_margin),
        "model3_capacity_margin_over_target": decimal_to_text(capacity_margin),
        "target_ratio_within_model3_topological_capacity": capacity_sufficient,
        "model3_not_falsified_by_range_bound": capacity_sufficient,
        "model3_capacity_gate_conclusion": (
            "range_capacity_sufficient_for_model3_prediction_runner"
            if capacity_sufficient and params_ok
            else "range_capacity_insufficient_for_model3_prediction_runner"
        ),
        "model3_prediction_runner_authorized_after_capacity_gate": int(
            capacity_sufficient
            and params_ok
            and hash_valid == 1
            and pre_registration.get("target_table_loaded") == 0
        ),
        "required_next_artifact": (
            "Model-3 prediction-only topological amplification runner before any "
            "mass-ratio recovery claim"
        ),
        "parameter_count": parameter_count,
        "target_count": len(targets),
        "parameter_count_less_than_target_count": params_ok,
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
            "not_model3_prediction",
            "not_scientific_claim_promotion",
        ],
    }
    receipt["model3_capacity_gate_receipt_hash"] = receipt_hash(receipt)
    receipt["model3_capacity_gate_receipt_hash_generated"] = 1
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
