# Latticra Identity-Replay Model-3 Prediction Runner Status

Status: guarded Model-3 prediction runner status
Date: 2026-05-29 CDT
Scope: status checkpoint for Model-3 prediction-only topological amplification and target-table rejection.

## Summary

Latticra now has a Model-3 topological amplification prediction runner with a separate evaluator.

The status meaning is narrow. Topological amplification improves dynamic range, but the first Model-3 prediction law still fails the target table.

## Status Fields

```text
latticra_identity_replay_model3_prediction_runner_present=1
latticra_identity_replay_model3_prediction_runner_guard_present=1
latticra_identity_replay_model3_prediction_evaluation_present=1
prediction_runner_id=latticra-identity-replay-model3-prediction-runner
evaluation_id=latticra-identity-replay-model3-prediction-evaluation
prediction_law_id=model3-target-blind-topological-replay-amplification
prediction_runner=tools/latticra_identity_replay_model3_runner.py
evaluation_tool=tools/latticra_identity_replay_model3_evaluate.py
model3_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
prediction_mode=predict_only
target_table_loaded=0
target_comparison_performed=0
prediction_receipt_emitted_before_target_load=1
model3_prediction_receipt_hash_valid=1
prediction_input_target_table_loaded=0
prediction_input_target_comparison_performed=0
target_load_after_prediction_receipt=1
measured_masses_used_in_law=0
measured_masses_used_in_kappa=0
target_ratios_used_in_law=0
particle_features_hand_declared=0
identity_patterns_generated_from_substrate=1
model3_topological_amplification_present=1
topological_amplification_trace_emitted=1
counterfactual_repair_search_performed=1
kappa_trace_emitted=1
mass_ratio_predictions_emitted=1
topological_branching_factor=3
topological_replay_depth=12
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
Z_L_I_e=77220
Z_L_I_mu=1551312
Z_L_I_tau=1043280
Z_L_I_W=47309184
Z_L_I_Z=35190
Z_L_I_H=22400
Z_L_I_top=1381746600
prediction_dynamic_range=61685.116071428571428571428571428571428571428571428571428571428571428571428571427
target_dynamic_range=337691.49623497269417
prediction_dynamic_range_meets_target_range=0
parameter_count=6
target_count=7
parameter_count_less_than_target_count=1
failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top
candidate_survives_target_table=0
model3_prediction_law_rejected=1
model3_prediction_conclusion=rejected_by_target_table
topological_amplification_improved_range_but_failed_targets=1
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
model3_prediction_receipt_hash_generated=1
model3_evaluation_receipt_hash_generated=1
```

## Public Meaning

The careful public meaning is:

```text
Model-3 topological amplification improved range but failed the target table. Latticra has not defeated Higgs; it rejected another candidate law under stricter replay rules.
```

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model3-prediction-runner.sh
```

Expected output:

```text
latticra_identity_replay_model3_prediction_runner: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-3 rejection analysis and amplification-law refinement.
```

## Non-Claims

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
