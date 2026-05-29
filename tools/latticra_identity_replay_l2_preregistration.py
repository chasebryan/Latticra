#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra L2 pre-registered substrate law receipt.

L2 is a proof-hygiene gate. It locks a candidate law and blinded-holdout
protocol without evaluating any holdout target.
"""

from __future__ import annotations

import hashlib
import json


BASIS_NAMES = [
    "generation_lift",
    "generation_square_lift",
    "localization_excess",
    "electroweak_spin_load",
    "scalar_load",
    "color_localization_load",
    "boundary_oscillation_load",
    "charge_gap_to_electron",
]

# This is the non-promoted L1 best vector, frozen here as a law candidate.
# Because it came after target-guided L1 search, L2 records inherited target
# exposure and refuses proof promotion until a future independent holdout exists.
PRE_REGISTERED_WEIGHT_VECTOR = {
    "generation_lift": 2,
    "generation_square_lift": 3,
    "localization_excess": 13,
    "electroweak_spin_load": 2,
    "scalar_load": 1,
    "color_localization_load": -2,
    "boundary_oscillation_load": 0,
    "charge_gap_to_electron": 0,
}

ORACLE_SCHEMA = {
    "oracle_id": "external-blinded-mass-ratio-oracle",
    "required_fields": [
        "oracle_id",
        "oracle_version",
        "pre_registration_receipt_hash",
        "holdout_identity",
        "holdout_feature_vector",
        "holdout_ratio_to_electron",
        "source_reference",
        "source_cutoff_date",
        "oracle_opened_after_pre_registration",
        "reviewer_attestation",
    ],
    "forbidden_fields_before_open": [
        "holdout_ratio_to_electron",
        "holdout_mass_mev",
        "measured_mass_target",
    ],
}


def build_receipt() -> dict[str, object]:
    law = {
        "candidate_law_id": "identity-replay-impedance-l2-preregistered-log-linear-law",
        "candidate_law_version": 1,
        "law_family": "log-linear-small-integer-identity-feature-impedance",
        "basis_names": BASIS_NAMES,
        "weight_scale": 10,
        "pre_registered_weight_vector": PRE_REGISTERED_WEIGHT_VECTOR,
        "prediction_rule": "log10(Z_L(I) / Z_L(I_e)) = dot(w, phi(I)) / 10",
    }
    receipt = {
        "latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout_present": 1,
        "pre_registration_id": "latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout",
        "pre_registration_version": 1,
        "candidate_law": law,
        "target_table_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md",
        "l1_search_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md",
        "l0_runner_reference": "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md",
        "proof_object_reference": "docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md",
        "pre_registration_tool": "tools/latticra_identity_replay_l2_preregistration.py",
        "pre_registered_law_present": 1,
        "blinded_holdout_protocol_defined": 1,
        "blinded_holdout_oracle_required": 1,
        "blinded_holdout_oracle_present": 0,
        "blinded_holdout_values_available_to_runner": 0,
        "holdout_evaluation_performed": 0,
        "candidate_survives_blinded_holdout": 0,
        "candidate_promoted": 0,
        "l1_target_guided_context_inherited": 1,
        "law_independence_from_prior_targets_proven": 0,
        "oracle_opened_after_pre_registration": 0,
        "oracle_schema": ORACLE_SCHEMA,
        "measured_masses_used_in_kappa": 0,
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
            "not_blinded_holdout_success",
        ],
    }
    canonical = json.dumps(receipt, sort_keys=True, separators=(",", ":"))
    receipt["pre_registration_receipt_hash"] = "sha256:" + hashlib.sha256(
        canonical.encode("utf-8")
    ).hexdigest()
    receipt["pre_registration_receipt_hash_generated"] = 1
    return receipt


def main() -> int:
    print(json.dumps(build_receipt(), indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
