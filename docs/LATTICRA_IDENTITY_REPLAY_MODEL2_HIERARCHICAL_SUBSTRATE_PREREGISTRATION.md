# Latticra Identity-Replay Model-2 Hierarchical Substrate Pre-Registration

Status: guarded Model-2 pre-registration and range-capacity conclusion
Date: 2026-05-29 CDT
Scope: pre-registered hierarchical replay law and post-receipt dynamic-range capacity check.

## Purpose

Model-1 reached a real negative conclusion: the flat bounded-cell substrate cannot span the measured mass-ratio vector.

Model-2 is the next necessary candidate class. It pre-registers hierarchical replay cost before target loading, then separately asks whether that pre-registered class has enough possible dynamic range to be worth testing.

This artifact does not predict particle masses. It only answers the range-capacity question that Model-1 failed:

```text
Can a fixed replay substrate class span the target ratio scale before fitting masses?
```

## Pre-Registration Checkpoint

```text
latticra_identity_replay_model2_hierarchical_substrate_preregistration_present=1
pre_registration_id=latticra-identity-replay-model2-hierarchical-substrate-preregistration
pre_registration_version=1
model1_bounded_range_falsifier_reference=docs/LATTICRA_IDENTITY_REPLAY_MODEL1_BOUNDED_RANGE_FALSIFIER.md
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
pre_registration_tool=tools/latticra_identity_replay_model2_preregistration.py
range_capacity_tool=tools/latticra_identity_replay_model2_range_capacity.py
target_table_loaded=0
target_comparison_performed=0
pre_registered_before_target_load=1
measured_masses_used_in_law=0
measured_masses_used_in_kappa=0
particle_features_hand_declared=0
mass_ratio_predictions_emitted=0
model2_hierarchical_substrate_present=1
candidate_substrate_id=identity-replay-model2-hierarchical-substrate
candidate_substrate_version=1
state_space_definition=nested finite cyclic integer lattices with shared width=17 and bounded cells across four replay scales
scale_levels=4
local_state_per_level=cyclic integer lattice width=17, cell_range=[-2,2]
local_update_operator=T_l(x_i)=clip(x_i + x_{i-1} - x_{i+1}) per scale
cross_scale_coupling_rule=higher scale repair activates only when lower scale identity repair is nonzero; scale weights multiply, not add
identity_projection_across_scales=tuple of per-scale cyclic quotient representatives plus cross-scale activation mask
repair_cost_accumulation_rule=Z_L = product(max(1, kappa_level_mean)) over active replay scales
zero_mass_control_rule=all-zero and uniform synchronized cross-scale states remain fixed under update and produce zero active repair cost
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
base_max_kappa_per_step=68
hierarchical_max_Z_L_before_target_load=21381376
hierarchical_max_ratio_bound_before_target_load=342102016
parameter_count=6
target_count_loaded=0
model2_pre_registration_receipt_hash_generated=1
```

## Range-Capacity Conclusion

After the pre-registration receipt exists, the range-capacity evaluator loads the guarded target table and compares only dynamic range, not predicted masses.

```text
latticra_identity_replay_model2_hierarchical_range_capacity_present=1
range_capacity_id=latticra-identity-replay-model2-hierarchical-range-capacity
range_capacity_version=1
model2_pre_registration_receipt_hash_valid=1
target_load_after_pre_registration_receipt=1
dynamic_range_capacity_evaluated_against_targets=1
target_ratio_recovery_evaluated=0
mass_ratio_predictions_emitted=0
hierarchical_max_ratio_bound_before_target_load=342102016
target_max_ratio_to_electron=337691.49623497269417
target_max_ratio_identity=I_top
hierarchical_capacity_margin_over_target=1013.0607960644598980091844681183754361457383377083533724071360813038948924026433
hierarchical_stationary_capacity_margin_over_target=63.316299754028743625574029257398464759108646106772085775446005081493430775165206
target_ratio_within_model2_hierarchical_capacity=1
target_ratio_within_model2_stationary_capacity=1
model2_not_falsified_by_range_bound=1
model2_range_capacity_conclusion=range_capacity_sufficient_for_target_vector
required_next_artifact=Model-2 prediction-only hierarchical replay runner before any mass-ratio recovery claim
parameter_count=6
target_count=7
parameter_count_less_than_target_count=1
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
model2_range_capacity_receipt_hash_generated=1
```

## Current Conclusion

The current conclusion is:

```text
Model-2 hierarchical replay is not falsified by the dynamic-range bound that killed Model-1.
```

This is a necessary-condition pass, not a mass-recovery pass. It means Model-2 can span the target ratio scale in principle, but it has not derived the particle mass-ratio vector.

The next required artifact is:

```text
Model-2 prediction-only hierarchical replay runner.
```

That runner must emit candidate `Z_L` ratios before loading the target table.

## Invocation

Pre-register before target loading:

```sh
python3 tools/latticra_identity_replay_model2_preregistration.py --pre-register \
  > reports/identity_replay_model2_preregistration.json
```

Evaluate range capacity after the receipt exists:

```sh
python3 tools/latticra_identity_replay_model2_range_capacity.py \
  --pre-registration reports/identity_replay_model2_preregistration.json \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md \
  > reports/identity_replay_model2_range_capacity.json
```

## Validation

This lane is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model2-hierarchical-substrate-preregistration.sh
```

Expected output:

```text
latticra_identity_replay_model2_hierarchical_substrate_preregistration: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-2 prediction-only hierarchical replay runner.
```

## Non-Claims

This Model-2 pre-registration and range-capacity conclusion is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
