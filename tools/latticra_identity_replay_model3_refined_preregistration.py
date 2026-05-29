#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Pre-register refined Model-3 sector-resolved topological charge work."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
from typing import Iterable

from latticra_identity_replay_model3_refinement_gate import (
    REQUIRED_REFINED_PROPERTY,
    gate_hash,
)


LAW_ID = "model3-refined-sector-resolved-topological-charge"
PRE_REGISTRATION_ID = (
    "latticra-identity-replay-model3-refined-sector-charge-preregistration"
)


def canonical_hash(payload: dict[str, object], omitted_keys: Iterable[str]) -> str:
    canonical_payload = dict(payload)
    for key in omitted_keys:
        canonical_payload.pop(key, None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def pre_registration_hash(payload: dict[str, object]) -> str:
    return canonical_hash(
        payload,
        (
            "refined_model3_pre_registration_receipt_hash",
            "refined_model3_pre_registration_receipt_hash_generated",
        ),
    )


def load_gate(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-3 refinement gate receipt must be a JSON object")
    return payload


def build_receipt(refinement_gate_path: Path) -> dict[str, object]:
    gate = load_gate(refinement_gate_path)
    observed_gate_hash = gate.get("model3_refinement_gate_receipt_hash")
    recomputed_gate_hash = gate_hash(gate)
    gate_hash_valid = int(observed_gate_hash == recomputed_gate_hash)
    gate_authorized = int(
        gate_hash_valid == 1
        and gate.get("refined_model3_preregistration_authorized") == 1
        and gate.get("refined_model3_required_law_property")
        == REQUIRED_REFINED_PROPERTY
        and gate.get("single_global_amplifier_forbidden") == 1
    )

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_refined_preregistration_present": 1,
        "pre_registration_id": PRE_REGISTRATION_ID,
        "pre_registration_version": 1,
        "refined_model3_law_id": LAW_ID,
        "refinement_gate_reference": str(refinement_gate_path),
        "refinement_gate_tool_reference": (
            "tools/latticra_identity_replay_model3_refinement_gate.py"
        ),
        "model3_rejection_analysis_reference": gate.get(
            "model3_rejection_analysis_reference"
        ),
        "model3_refinement_gate_receipt_hash": observed_gate_hash,
        "model3_refinement_gate_receipt_hash_recomputed": recomputed_gate_hash,
        "model3_refinement_gate_receipt_hash_valid": gate_hash_valid,
        "refinement_gate_required_law_property": gate.get(
            "refined_model3_required_law_property"
        ),
        "required_refined_model3_property": REQUIRED_REFINED_PROPERTY,
        "refined_model3_preregistration_authorized_by_gate": gate_authorized,
        "refined_model3_prediction_runner_authorized": 0,
        "refined_model3_capacity_gate_required_before_prediction": 1,
        "pre_registered_before_refined_prediction": 1,
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "mass_ratio_predictions_emitted": 0,
        "target_ratio_recovery_evaluated": 0,
        "dynamic_range_capacity_evaluated_against_targets": 0,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "target_ratios_used_in_law": 0,
        "target_order_labels_as_weights_used": 0,
        "particle_features_hand_declared": 0,
        "particle_name_to_sector_mapping_used": 0,
        "particle_name_to_cost_mapping_used": 0,
        "post_target_parameter_tuning_used": 0,
        "target_guided_loss_function_used": 0,
        "single_global_amplifier_forbidden": 1,
        "single_global_amplifier_used": 0,
        "sector_resolved_topological_charge_present": 1,
        "sector_resolved_topological_trace_required": 1,
        "family_monotonicity_constraint_present": 1,
        "family_monotonicity_trace_required": 1,
        "target_blind_dynamic_range_proof_required_before_prediction": 1,
        "minimum_refined_model3_dynamic_range_multiplier_required": gate.get(
            "minimum_refined_model3_dynamic_range_multiplier_required"
        ),
        "prediction_dynamic_range_to_beat": gate.get("prediction_dynamic_range_to_beat"),
        "target_dynamic_range_to_span": gate.get("target_dynamic_range_to_span"),
        "ordering_failure_must_be_addressed": gate.get(
            "ordering_failure_must_be_addressed"
        ),
        "lepton_family_order_inversion_must_be_addressed": gate.get(
            "lepton_family_order_inversion_must_be_addressed"
        ),
        "low_electroweak_below_electron_must_be_addressed": gate.get(
            "low_electroweak_below_electron_must_be_addressed"
        ),
        "heavy_sector_underamplification_must_be_addressed": gate.get(
            "heavy_sector_underamplification_must_be_addressed"
        ),
        "state_space_definition": (
            "unlabeled replay quotient graph with local branch, coalescence, "
            "orientation, and observer-closure incidence"
        ),
        "local_update_operator": (
            "target-blind replay update over quotient-neighborhood incidence; "
            "no particle-name dispatch and no target-ratio loss"
        ),
        "observer_projection": (
            "projection to quotient-stable identity traces, sector charge, and "
            "family-order certificates without target-table loading"
        ),
        "identity_quotient": (
            "identity classes are grouped only by substrate trace invariants, "
            "not by Standard Model particle labels or measured mass order"
        ),
        "distance_metric": (
            "lexicographic replay obstruction distance: quotient depth, "
            "branch-coalescence obstruction, orientation inversion, and "
            "observer-closure cost"
        ),
        "counterfactual_repair_cost_function": (
            "minimal local edits required to preserve an unlabeled projected "
            "identity under replay update, lifted by sector charge only after "
            "the charge is derived from topology"
        ),
        "sector_charge_components": [
            "quotient_depth_charge",
            "branch_coalescence_charge",
            "orientation_inversion_charge",
            "observer_closure_charge",
        ],
        "sector_charge_rule": (
            "sector charge is the ordered tuple of topology-derived obstruction "
            "counts; it may separate sectors but may not read target names, "
            "target ratios, or measured masses"
        ),
        "family_monotonicity_rule": (
            "within any derived sector, replay-family order must be monotone in "
            "nested quotient depth and obstruction count before target evaluation"
        ),
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_required": 1,
        "gluon_zero_rest_mass_control_required": 1,
        "zero_mass_control_rule": (
            "null and gauge-uniform replay traces must keep zero rest-mass "
            "controls at zero sector charge unless a non-null obstruction is "
            "derived without target labels"
        ),
        "parameter_count": 0,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "forbidden_refined_model3_inputs": gate.get(
            "forbidden_refined_model3_inputs",
            [
                "measured_particle_masses",
                "target_mass_ratios",
                "target_order_labels_as_weights",
                "particle_name_to_sector_mapping",
                "particle_name_to_cost_mapping",
                "post_target_parameter_tuning",
                "target_guided_loss_function",
                "single_global_amplifier_only",
            ],
        ),
        "required_refined_model3_emissions_before_prediction": [
            "state_space_definition",
            "local_update_operator",
            "observer_projection",
            "identity_quotient",
            "distance_metric",
            "counterfactual_repair_cost_function",
            "sector_resolved_topological_trace",
            "family_monotonicity_trace",
            "target_blind_dynamic_range_capacity_receipt",
            "negative_control_receipts",
            "non_claims",
        ],
        "next_required_artifact": (
            "refined Model-3 target-blind dynamic-range capacity gate before "
            "any prediction-only runner"
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
            "not_refined_model3_prediction",
            "not_target_table_evaluation",
            "not_scientific_claim_promotion",
        ],
    }
    receipt["refined_model3_pre_registration_receipt_hash"] = (
        pre_registration_hash(receipt)
    )
    receipt["refined_model3_pre_registration_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--refinement-gate",
        required=True,
        help="Model-3 refinement gate JSON receipt that authorizes pre-registration",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_receipt(Path(args.refinement_gate))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
