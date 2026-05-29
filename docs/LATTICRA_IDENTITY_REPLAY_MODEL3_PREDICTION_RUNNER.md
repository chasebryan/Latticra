# Latticra Identity-Replay Model-3 Prediction Runner

Status: guarded Model-3 prediction-only runner and target-table rejection
Date: 2026-05-29 CDT
Scope: topological amplification prediction receipt, separate target evaluator, and bounded conclusion.

## Purpose

Model-3 topological amplification passed the dynamic-range capacity gate. This artifact asks the stricter question:

```text
Does the first target-blind topological amplification prediction law recover the guarded mass-ratio vector?
```

The answer is no. The law improves dynamic range over Model-2, but it still fails the target table and cannot support Higgs-checkmate language.

## Prediction Checkpoint

```text
latticra_identity_replay_model3_prediction_runner_present=1
prediction_runner_id=latticra-identity-replay-model3-prediction-runner
prediction_runner_version=1
prediction_law_id=model3-target-blind-topological-replay-amplification
prediction_runner=tools/latticra_identity_replay_model3_runner.py
evaluation_tool=tools/latticra_identity_replay_model3_evaluate.py
model3_pre_registration_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL3_TOPOLOGICAL_AMPLIFICATION_PREREGISTRATION.md
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
candidate_substrate_id=identity-replay-model3-topological-amplification-substrate
prediction_mode=predict_only
target_table_loaded=0
target_comparison_performed=0
prediction_receipt_emitted_before_target_load=1
measured_masses_used_in_law=0
measured_masses_used_in_kappa=0
target_ratios_used_in_law=0
particle_features_hand_declared=0
identity_patterns_generated_from_substrate=1
model3_topological_amplification_present=1
topological_amplification_trace_emitted=1
counterfactual_repair_search_performed=1
kappa_trace_emitted=1
active_scale_product_cost_emitted=1
mass_ratio_predictions_emitted=1
topological_branching_factor=3
topological_replay_depth=12
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
parameter_count=6
target_count_loaded=0
Z_L_I_e=77220
Z_L_I_mu=1551312
Z_L_I_tau=1043280
Z_L_I_W=47309184
Z_L_I_Z=35190
Z_L_I_H=22400
Z_L_I_top=1381746600
prediction_dynamic_range=61685.116071428571428571428571428571428571428571428571428571428571428571428571427
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
```

## Evaluation Conclusion

After the prediction receipt exists, the evaluator loads the guarded target table.

```text
latticra_identity_replay_model3_prediction_evaluation_present=1
evaluation_id=latticra-identity-replay-model3-prediction-evaluation
evaluation_version=1
model3_prediction_receipt_hash_valid=1
prediction_receipt_emitted_before_target_load=1
prediction_input_target_table_loaded=0
prediction_input_target_comparison_performed=0
target_table_loaded=1
target_load_after_prediction_receipt=1
target_comparison_performed=1
prediction_dynamic_range=61685.116071428571428571428571428571428571428571428571428571428571428571428571427
target_dynamic_range=337691.49623497269417
prediction_dynamic_range_meets_target_range=0
parameter_count=6
target_count=7
parameter_count_less_than_target_count=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
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
model3_evaluation_receipt_hash_generated=1
```

## Current Conclusion

The current conclusion is:

```text
The first Model-3 topological amplification prediction law is rejected by the target table.
```

It improved the Model-2 dynamic range but did not recover the particle mass-ratio vector.

The follow-on Model-3 Rejection Analysis now records the failure as structural: Higgs and Z fall below electron-scale replay impedance, the lepton family ordering is inverted, and a single global topological amplifier is insufficient.

## Invocation

Emit the prediction receipt before target loading:

```sh
python3 tools/latticra_identity_replay_model3_runner.py --predict-only \
  > reports/identity_replay_model3_predictions.json
```

Evaluate only after that receipt exists:

```sh
python3 tools/latticra_identity_replay_model3_evaluate.py \
  --predictions reports/identity_replay_model3_predictions.json \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md \
  > reports/identity_replay_model3_evaluation.json
```

## Validation

This lane is guarded by:

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

Completed follow-on:

```text
Model-3 Rejection Analysis
```

## Non-Claims

This Model-3 prediction runner is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
