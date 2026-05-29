#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Pre-register Model-3 target-blind topological replay amplification."""

from __future__ import annotations

import argparse
import hashlib
import json
from decimal import Decimal, getcontext
from typing import Iterable

from latticra_identity_replay_model1_evaluate import decimal_to_text
from latticra_identity_replay_model2_preregistration import (
    SCALE_LEVELS,
    build_receipt as build_model2_pre_registration,
)


getcontext().prec = 80

TOPOLOGICAL_BRANCHING_FACTOR = 3
TOPOLOGICAL_REPLAY_DEPTH = 12
QUOTIENT_INSTABILITY_LAYERS = SCALE_LEVELS
PARAMETER_COUNT = 6
LAW_ID = "model3-target-blind-topological-replay-amplification"


def receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def amplification_multiplier() -> Decimal:
    return Decimal(TOPOLOGICAL_BRANCHING_FACTOR) ** Decimal(TOPOLOGICAL_REPLAY_DEPTH)


def build_receipt() -> dict[str, object]:
    model2_pre_registration = build_model2_pre_registration()
    model2_bound = Decimal(
        str(model2_pre_registration["hierarchical_max_ratio_bound_before_target_load"])
    )
    multiplier = amplification_multiplier()
    model3_bound = model2_bound * multiplier

    receipt: dict[str, object] = {
        "latticra_identity_replay_model3_topological_amplification_preregistration_present": 1,
        "pre_registration_id": "latticra-identity-replay-model3-topological-amplification-preregistration",
        "pre_registration_version": 1,
        "model3_law_id": LAW_ID,
        "model3_worthiness_gate_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL3_WORTHINESS_GATE.md",
        "model2_failure_analysis_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL2_PREDICTION_FAILURE_ANALYSIS.md",
        "model2_pre_registration_reference": "docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "target_table_loaded": 0,
        "target_comparison_performed": 0,
        "pre_registered_before_target_load": 1,
        "measured_masses_used_in_law": 0,
        "measured_masses_used_in_kappa": 0,
        "target_ratios_used_in_law": 0,
        "particle_features_hand_declared": 0,
        "mass_ratio_predictions_emitted": 0,
        "model3_topological_amplification_present": 1,
        "model3_preregistration_authorized_by_worthiness_gate": 1,
        "model3_prediction_runner_authorized": 0,
        "candidate_substrate_id": "identity-replay-model3-topological-amplification-substrate",
        "candidate_substrate_version": 1,
        "state_space_definition": (
            "nested cyclic replay lattices plus a target-blind branch/coalescence "
            "graph over quotient identities"
        ),
        "local_update_operator": (
            "Model-2 per-scale local update, lifted into branch/coalescence replay graph"
        ),
        "observer_projection": (
            "per-scale quotient projection plus unlabeled branch-coalescence topology"
        ),
        "identity_quotient": (
            "lexicographic cyclic quotient at each scale, then target-blind "
            "topological coalescence class"
        ),
        "distance_metric": (
            "sum of per-scale quotient L1 distances plus branch-instability count"
        ),
        "counterfactual_repair_cost_function": (
            "minimal local repair edits multiplied by target-blind topological "
            "branch/coalescence instability"
        ),
        "topological_amplification_rule": (
            "A replay branch can erase, reinforce, or invert local repair orientation; "
            "only branches that coalesce to the same observer quotient amplify repair cost"
        ),
        "topological_amplification_trace_required": 1,
        "target_blind_dynamic_range_proof_before_prediction": 1,
        "topological_branching_factor": TOPOLOGICAL_BRANCHING_FACTOR,
        "topological_branching_semantics": "erase_reinforce_invert",
        "topological_replay_depth": TOPOLOGICAL_REPLAY_DEPTH,
        "quotient_instability_layers": QUOTIENT_INSTABILITY_LAYERS,
        "scale_levels": SCALE_LEVELS,
        "model2_hierarchical_max_ratio_bound_before_target_load": decimal_to_text(
            model2_bound
        ),
        "topological_amplification_multiplier_before_target_load": decimal_to_text(
            multiplier
        ),
        "model3_topological_max_ratio_bound_before_target_load": decimal_to_text(
            model3_bound
        ),
        "parameter_count": PARAMETER_COUNT,
        "target_count_loaded": 0,
        "parameter_count_less_than_target_count": 0,
        "negative_controls_present": 1,
        "photon_zero_rest_mass_control_present": 1,
        "gluon_zero_rest_mass_control_present": 1,
        "zero_mass_control_rule": (
            "zero and uniform synchronized branch states have no instability branches "
            "and preserve zero active repair cost"
        ),
        "forbidden_inputs": [
            "measured_particle_masses",
            "target_mass_ratios",
            "target_order_labels_as_weights",
            "particle_name_to_cost_mapping",
            "post_target_parameter_tuning",
            "target_guided_loss_function",
        ],
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
            "not_model3_prediction",
            "not_target_table_evaluation",
        ],
    }
    receipt["model3_pre_registration_receipt_hash"] = receipt_hash(receipt)
    receipt["model3_pre_registration_receipt_hash_generated"] = 1
    return receipt


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--pre-register",
        action="store_true",
        help="emit Model-3 topological amplification pre-registration without targets",
    )
    args = parser.parse_args(list(argv) if argv is not None else None)
    if not args.pre_register:
        parser.error("Model-3 pre-registration currently requires --pre-register")
    print(json.dumps(build_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
