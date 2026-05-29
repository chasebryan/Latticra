#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Pre-register refined Model-3 sector-resolved topological charge."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from pathlib import Path
from typing import Iterable

from latticra_identity_replay_model1_evaluate import decimal_to_text
from latticra_identity_replay_model3_preregistration import (
    build_receipt as build_model3_pre_registration,
)
from latticra_identity_replay_model3_refinement_gate import (
    REQUIRED_REFINED_PROPERTY,
    gate_hash,
)


getcontext().prec = 80

REFINED_LAW_ID = "refined-model3-target-blind-sector-resolved-topological-charge"
SECTOR_CHARGE_RADIX = 5
SECTOR_CHARGE_DEPTH = 4
FAMILY_MONOTONICITY_STATES = 3
FAMILY_MONOTONICITY_DEPTH = 2
PARAMETER_COUNT = 6


def receipt_hash(payload: dict[str, object]) -> str:
    canonical_payload = dict(payload)
    canonical_payload.pop("refined_model3_pre_registration_receipt_hash", None)
    canonical_payload.pop("refined_model3_pre_registration_receipt_hash_generated", None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def load_gate(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-3 refinement gate must be a JSON object")
    return payload


def refined_multiplier() -> Decimal:
    sector = Decimal(SECTOR_CHARGE_RADIX) ** Decimal(SECTOR_CHARGE_DEPTH)
    family = Decimal(FAMILY_MONOTONICITY_STATES) ** Decimal(
        FAMILY_MONOTONICITY_DEPTH
    )
    return sector * family


def build_receipt(gate_path: Path) -> dict[str, object]:
    gate = load_gate(gate_path)
    expected_hash = gate_hash(gate)
    observed_hash = gate.get("model3_refinement_gate_receipt_hash")
    hash_valid = int(observed_hash == expected_hash)

    pre_registration_authorized = int(
        hash_valid == 1
        and gate.get("refined_model3_preregistration_authorized") == 1
        and gate.get("refined_model3_required_law_property")
        == REQUIRED_REFINED_PROPERTY
        and gate.get("single_global_amplifier_forbidden") == 1
    )

    model3_pre_registration = build_model3_pre_registration()
    model3_bound = Decimal(
        str(model3_pre_registration["model3_topological_max_ratio_bound_before_target_load"])
    )
    multiplier = refined_multiplier()
    refined_bound = model3_bound * multiplier

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_refined_preregistration_present": 1,
        "pre_registration_id": "latticra-identity-replay-model3-refined-preregistration",
        "pre_registration_version": 1,
        "refined_model3_law_id": REFINED_LAW_ID,
        "refinement_gate_reference": str(gate_path),
        "model3_rejection_analysis_reference": gate.get(
            "model3_rejection_analysis_reference"
        ),
        "model3_refinement_gate_receipt_hash": observed_hash,
        "model3_refinement_gate_receipt_hash_recomputed": expected_hash,
        "model3_refinement_gate_receipt_hash_valid": hash_valid,
        "model3_rejection_analysis_required_property": gate.get(
            "model3_rejection_analysis_required_property"
        ),
        "refined_model3_required_law_property": REQUIRED_REFINED_PROPERTY,
        "refined_model3_preregistration_authorized_by_gate": pre_registration_authorized,
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "pre_registered_before_target_load": 1,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "target_ratios_used_in_law": 0,
        "particle_features_hand_declared": 0,
        "particle_name_to_sector_mapping_used": 0,
        "particle_name_to_cost_mapping_used": 0,
        "post_target_parameter_tuning_used": 0,
        "target_guided_loss_function_used": 0,
        "mass_ratio_predictions_emitted": 0,
        "refined_model3_sector_resolved_topological_charge_present": 1,
        "family_monotonicity_constraint_present": 1,
        "single_global_amplifier_used": 0,
        "candidate_substrate_id": "identity-replay-refined-model3-sector-charge-substrate",
        "candidate_substrate_version": 1,
        "state_space_definition": (
            "unlabeled replay quotient states carrying boundary-crossing, "
            "branch/coalescence, repair-orientation, and replay-generation traces"
        ),
        "local_update_operator": (
            "Model-3 local replay update lifted through sector-charge transitions "
            "without target labels or measured-ratio feedback"
        ),
        "observer_projection": (
            "quotient projection that exposes sector charge from topology and hides "
            "particle names, masses, and target order"
        ),
        "identity_quotient": (
            "target-blind quotient over replay generation, branch parity, "
            "coalescence rank, and repair-orientation class"
        ),
        "distance_metric": (
            "sector-charge weighted repair distance with monotone replay-generation "
            "penalty, pre-registered before target loading"
        ),
        "counterfactual_repair_cost_function": (
            "minimal local edits multiplied by sector charge and replay-generation "
            "monotonicity cost, without using target ratios"
        ),
        "sector_resolved_topological_charge_rule": (
            "derive charge from quotient-boundary crossings, branch/coalescence parity, "
            "repair orientation, and replay-generation depth"
        ),
        "family_monotonicity_rule": (
            "replay-generation chains must be monotone under the pre-registered "
            "charge order before any target table is loaded"
        ),
        "sector_resolved_topological_trace_required": 1,
        "family_monotonicity_trace_required": 1,
        "target_blind_capacity_envelope_before_target_load": 1,
        "target_blind_dynamic_range_proof_required_before_prediction": 1,
        "sector_charge_radix": SECTOR_CHARGE_RADIX,
        "sector_charge_depth": SECTOR_CHARGE_DEPTH,
        "family_monotonicity_states": FAMILY_MONOTONICITY_STATES,
        "family_monotonicity_depth": FAMILY_MONOTONICITY_DEPTH,
        "model3_topological_max_ratio_bound_before_target_load": decimal_to_text(
            model3_bound
        ),
        "refined_sector_charge_multiplier_before_target_load": decimal_to_text(
            multiplier
        ),
        "refined_model3_max_ratio_bound_before_target_load": decimal_to_text(
            refined_bound
        ),
        "minimum_refined_model3_dynamic_range_multiplier_required": gate.get(
            "minimum_refined_model3_dynamic_range_multiplier_required"
        ),
        "parameter_count": PARAMETER_COUNT,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "parameter_count_less_than_target_count_required": 1,
        "negative_controls_required": 1,
        "photon_zero_rest_mass_control_required": 1,
        "gluon_zero_rest_mass_control_required": 1,
        "zero_mass_control_rule": (
            "zero and synchronized replay states carry no sector-charge boundary "
            "crossings and must preserve zero active repair cost"
        ),
        "forbidden_inputs": [
            "measured_particle_masses",
            "target_mass_ratios",
            "target_order_labels_as_weights",
            "particle_name_to_sector_mapping",
            "particle_name_to_cost_mapping",
            "post_target_parameter_tuning",
            "target_guided_loss_function",
            "single_global_amplifier_only",
        ],
        "required_next_artifact": (
            "Refined Model-3 target-blind capacity gate before any prediction-only "
            "runner"
        ),
        "refined_model3_capacity_gate_required_before_prediction": 1,
        "refined_model3_prediction_receipt_before_target_load_required": 1,
        "refined_model3_target_load_after_prediction_receipt_required": 1,
        "refined_model3_prediction_runner_authorized": 0,
        "refined_model3_candidate_promoted": 0,
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
            "not_refined_model3_prediction",
            "not_target_table_evaluation",
            "not_scientific_claim_promotion",
        ],
    }
    receipt["refined_model3_pre_registration_receipt_hash"] = receipt_hash(receipt)
    receipt["refined_model3_pre_registration_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--gate", required=True)
    parser.add_argument(
        "--pre-register",
        action="store_true",
        help="emit refined Model-3 pre-registration without targets or predictions",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.pre_register:
        parser.error("refined Model-3 pre-registration requires --pre-register")
    print(json.dumps(build_receipt(Path(args.gate)), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
