#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Gate Model-3 work against the Model-2 prediction failure."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
from typing import Iterable


def canonical_hash(payload: dict[str, object], omitted_keys: Iterable[str]) -> str:
    canonical_payload = dict(payload)
    for key in omitted_keys:
        canonical_payload.pop(key, None)
    canonical = json.dumps(canonical_payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def analysis_hash(payload: dict[str, object]) -> str:
    return canonical_hash(
        payload,
        (
            "model2_failure_analysis_receipt_hash",
            "model2_failure_analysis_receipt_hash_generated",
        ),
    )


def gate_hash(payload: dict[str, object]) -> str:
    return canonical_hash(
        payload,
        (
            "model3_worthiness_gate_receipt_hash",
            "model3_worthiness_gate_receipt_hash_generated",
        ),
    )


def load_analysis(path: Path) -> dict[str, object]:
    with path.open(encoding="utf-8") as handle:
        payload = json.load(handle)
    if not isinstance(payload, dict):
        raise ValueError("Model-2 failure analysis must be a JSON object")
    return payload


def build_gate_receipt(analysis_path: Path) -> dict[str, object]:
    analysis = load_analysis(analysis_path)
    expected_hash = analysis_hash(analysis)
    observed_hash = analysis.get("model2_failure_analysis_receipt_hash")
    hash_valid = int(observed_hash == expected_hash)

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_worthiness_gate_present": 1,
        "gate_id": "latticra-identity-replay-model3-worthiness-gate",
        "gate_version": 1,
        "model2_failure_analysis_reference": str(analysis_path),
        "model2_failure_analysis_receipt_hash": observed_hash,
        "model2_failure_analysis_receipt_hash_recomputed": expected_hash,
        "model2_failure_analysis_receipt_hash_valid": hash_valid,
        "model2_prediction_law_rejected": analysis.get("model2_prediction_law_rejected"),
        "model2_failure_analysis_required_property": analysis.get(
            "required_model3_property"
        ),
        "model3_required_law_property": "target_blind_topological_replay_amplification",
        "model3_required_law_property_description": (
            "A worthwhile Model-3 must amplify replay impedance from topology, "
            "branching identity quotients, nested quotient instability, or an "
            "equivalent target-blind substrate mechanism."
        ),
        "minimum_model3_dynamic_range_multiplier_required": analysis.get(
            "minimum_model3_dynamic_range_multiplier_required"
        ),
        "prediction_dynamic_range_to_beat": analysis.get("prediction_dynamic_range"),
        "target_dynamic_range_to_span": analysis.get("target_dynamic_range"),
        "ordering_failure_must_be_addressed": analysis.get("ordering_failure_present"),
        "lepton_family_order_inversion_must_be_addressed": analysis.get(
            "lepton_family_order_inversion_present"
        ),
        "heavy_sector_compression_must_be_addressed": analysis.get(
            "heavy_sector_compression_present"
        ),
        "model3_preregistration_authorized": int(
            hash_valid == 1
            and analysis.get("model2_prediction_law_rejected") == 1
            and analysis.get("required_model3_property")
            == "target_blind_topological_replay_amplification"
        ),
        "model3_prediction_runner_authorized": 0,
        "model3_candidate_promoted": 0,
        "model3_worth_testing_if_preregistration_passes": 1,
        "model3_pre_registration_receipt_required": 1,
        "model3_prediction_receipt_before_target_load_required": 1,
        "model3_target_load_after_prediction_receipt_required": 1,
        "parameter_count_less_than_target_count_required": 1,
        "negative_controls_required": 1,
        "photon_zero_rest_mass_control_required": 1,
        "gluon_zero_rest_mass_control_required": 1,
        "topological_amplification_trace_required": 1,
        "target_blind_dynamic_range_proof_required_before_prediction": 1,
        "forbidden_model3_inputs": [
            "measured_particle_masses",
            "target_mass_ratios",
            "target_order_labels_as_weights",
            "particle_name_to_cost_mapping",
            "post_target_parameter_tuning",
            "target_guided_loss_function",
        ],
        "required_model3_emissions": [
            "state_space_definition",
            "local_update_operator",
            "observer_projection",
            "identity_quotient",
            "distance_metric",
            "counterfactual_repair_cost_function",
            "topological_amplification_trace",
            "dynamic_range_capacity_receipt_before_target_load",
            "prediction_receipt_before_target_load",
            "target_table_evaluation_after_prediction_receipt",
            "negative_control_results",
            "non_claims",
        ],
        "higgs_checkmate_threshold": (
            "all guarded mass ratios survive declared epsilon, photon/gluon controls "
            "survive, parameter count stays below target count, blinded holdout "
            "survives, and the Higgs coupling map is derived as a low-energy shadow"
        ),
        "model3_gate_conclusion": "worth_preregistering_only_not_worth_promoting",
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
    receipt["model3_worthiness_gate_receipt_hash"] = gate_hash(receipt)
    receipt["model3_worthiness_gate_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--analysis", required=True)
    args = parser.parse_args(list(argv) if argv is not None else None)
    receipt = build_gate_receipt(Path(args.analysis))
    print(json.dumps(receipt, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
