# Latticra Identity-Replay Model-2 Prediction Runner Status

Status: guarded Model-2 prediction runner status
Date: 2026-05-29 CDT
Scope: status checkpoint for the first prediction-only hierarchical replay law and target-table rejection.

## Summary

Latticra now has a Model-2 hierarchical replay prediction runner with a separate evaluator.

The status meaning is narrow. The prediction receipt is emitted before target loading and the evaluator validates that ordering, but the first deterministic prediction law fails the guarded target table.

## Status Fields

```text
latticra_identity_replay_model2_prediction_runner_present=1
latticra_identity_replay_model2_prediction_runner_guard_present=1
latticra_identity_replay_model2_prediction_evaluation_present=1
prediction_runner_id=latticra-identity-replay-model2-prediction-runner
prediction_runner_version=1
prediction_law_id=model2-hierarchical-hash-seeded-scale-product-law
evaluation_id=latticra-identity-replay-model2-prediction-evaluation
prediction_runner=tools/latticra_identity_replay_model2_runner.py
evaluation_tool=tools/latticra_identity_replay_model2_evaluate.py
model2_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL2_HIERARCHICAL_SUBSTRATE_PREREGISTRATION.md
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
candidate_substrate_id=identity-replay-model2-hierarchical-substrate
candidate_substrate_version=1
prediction_mode=predict_only
target_table_loaded=0
target_comparison_performed=0
prediction_receipt_emitted_before_target_load=1
model2_prediction_receipt_hash_valid=1
prediction_input_target_table_loaded=0
prediction_input_target_comparison_performed=0
target_load_after_prediction_receipt=1
measured_masses_used_in_law=0
measured_masses_used_in_kappa=0
particle_features_hand_declared=0
identity_patterns_generated_from_substrate=1
model2_hierarchical_substrate_present=1
hierarchical_replay_performed=1
per_scale_kappa_traces_emitted=1
active_scale_product_cost_emitted=1
mass_ratio_predictions_emitted=1
scale_levels=4
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
prediction_dynamic_range=22.098461538461538461538461538461538461538461538461538461538461538461538461538462
target_dynamic_range=337691.49623497269417
prediction_dynamic_range_meets_target_range=0
parameter_count=6
target_count=7
parameter_count_less_than_target_count=1
failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top
candidate_survives_target_table=0
model2_prediction_law_rejected=1
model2_prediction_conclusion=rejected_by_target_table
hierarchy_sufficient_for_range_but_prediction_vector_failed=1
candidate_promoted=0
mass_ratio_recovery_claimed=0
standard_model_replacement_claimed=0
higgs_denied=0
higgs_checkmate_claimed=0
higgs_only_causal_closure_challenged=1
simulation_proven=0
reality_simulation_claimed=0
physics_bound_by_simulative_concepts_claimed=0
scientific_claim_promoted=0
model2_prediction_receipt_hash_generated=1
model2_evaluation_receipt_hash_generated=1
```

## Public Meaning

The careful public meaning is:

```text
Model-2 hierarchy solved the range-capacity blocker, but the first deterministic Model-2 prediction law failed the measured mass-ratio target table. Latticra has not defeated Higgs; it has rejected one candidate law under a stricter computational proof standard.
```

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model2-prediction-runner.sh
```

Expected output:

```text
latticra_identity_replay_model2_prediction_runner: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-2 prediction failure analysis and law refinement.
```

## Non-Claims

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
