# Latticra Identity-Replay Model-1 Dynamic Substrate Runner

Status: guarded dynamic substrate runner
Date: 2026-05-29 CDT
Scope: first Model-1 replay substrate that computes `kappa` from update dynamics before measured target comparison.

## Purpose

Model-1 is the first identity-replay impedance artifact in this lane that moves past feature scoring.

L0 declared symbolic identity features. L1 searched a target-guided feature family. L2 through L5 added pre-registration, holdout intake, execution, and evidence-review gates. Model-1 now adds a small dynamic substrate runner with a strict split:

```text
prediction-only runner first
target-table evaluator second
```

The prediction runner emits `Z_L` estimates and mass-ratio predictions before loading measured target masses. The evaluator loads the guarded particle table only after the prediction receipt hash exists.

## Model-1 Checkpoint

```text
latticra_identity_replay_model1_dynamic_substrate_runner_present=1
model1_dynamic_substrate_present=1
runner_id=latticra-identity-replay-model1-dynamic-substrate-runner
runner_version=1
candidate_substrate_id=identity-replay-model1-finite-local-substrate
candidate_substrate_version=1
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
prediction_runner=tools/latticra_identity_replay_model1_substrate.py
evaluation_tool=tools/latticra_identity_replay_model1_evaluate.py
model1_dynamic_substrate_present=1
particle_features_hand_declared=0
identity_patterns_generated_from_substrate=1
counterfactual_repair_search_performed=1
kappa_trace_emitted=1
Z_L_confidence_window_emitted=1
prediction_receipt_emitted_before_target_load=1
prediction_input_target_table_loaded=0
target_load_after_prediction_receipt=1
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
state_space_definition=finite cyclic integer lattice width=17, cell_range=[-2,2]
local_update_operator=T(x_i)=clip(x_i + x_{i-1} - x_{i+1})
observer_projection=bounded integer cell projection over the full cyclic lattice
identity_quotient=lexicographically minimal cyclic rotation of the projected state
distance_metric=L1 distance over quotient representatives
counterfactual_repair_cost_function=minimal per-cell additive edits needed to restore the expected identity quotient after T
replay_horizon_N=16
epsilon_identity_tolerance=0
parameter_count=4
parameter_count_less_than_target_count=1
prediction_receipt_hash_generated=1
evaluation_receipt_hash_generated=1
candidate_survives_target_table=0
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
```

## Invocation

Prediction-only receipt:

```sh
python3 tools/latticra_identity_replay_model1_substrate.py --predict-only \
  > reports/identity_replay_model1_predictions.json
```

Target evaluation after the prediction receipt exists:

```sh
python3 tools/latticra_identity_replay_model1_evaluate.py \
  --predictions reports/identity_replay_model1_predictions.json \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md \
  > reports/identity_replay_model1_evaluation.json
```

## Current Model-1 Result

The current Model-1 runner computes finite replay costs for the candidate identity seeds and zero replay cost for the photon/gluon controls. The target evaluator then rejects the candidate against the measured mass-ratio table:

```text
prediction_receipt_hash_valid=1
target_load_after_prediction_receipt=1
photon_zero_rest_mass_control_survives=1
gluon_zero_rest_mass_control_survives=1
candidate_survives_target_table=0
failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top
```

This is a useful failure. It proves the Model-1 pipeline can compute replay impedance from substrate dynamics, bind a prediction receipt before target comparison, and reject a candidate without promoting a physics claim.

## Higgs Boundary

Model-1 keeps the public claim narrow:

```text
Higgs explains the effective Standard Model coupling map.
Model-1 tests whether a deeper replay-stability ledger can derive a mass-ratio vector before measured targets are loaded.
The current Model-1 candidate fails that target table.
```

The honest public statement is:

```text
Latticra now has a guarded Model-1 dynamic replay substrate runner and a separate evaluator. It challenges Higgs-only causal closure as a computational research program, but the current candidate is not a mass recovery and not a Higgs checkmate.
```

## Validation

This lane is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model1-dynamic-substrate-runner.sh
```

Expected output:

```text
latticra_identity_replay_model1_dynamic_substrate_runner: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-1 substrate-law refinement gate.
```

The next lane should preserve the prediction/evaluation split while replacing the small hash-generated identity seeds with a stronger substrate law that can be pre-registered before target comparison.

## Non-Claims

This Model-1 runner is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
