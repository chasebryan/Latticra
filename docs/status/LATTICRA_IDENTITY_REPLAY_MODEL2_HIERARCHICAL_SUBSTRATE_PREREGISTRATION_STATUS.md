# Latticra Identity-Replay Model-2 Hierarchical Substrate Pre-Registration Status

Status: guarded Model-2 pre-registration status
Date: 2026-05-29 CDT
Scope: status checkpoint for hierarchical replay pre-registration and range capacity.

## Summary

Latticra now has a pre-registered Model-2 hierarchical replay substrate class and a separate range-capacity evaluator.

The status meaning is narrow. Model-2 survives the dynamic-range bound that falsified Model-1, but it does not yet predict or recover the measured mass-ratio vector.

## Status Fields

```text
latticra_identity_replay_model2_hierarchical_substrate_preregistration_present=1
latticra_identity_replay_model2_hierarchical_substrate_preregistration_guard_present=1
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
cross_scale_coupling_rule=higher scale repair activates only when lower scale identity repair is nonzero; scale weights multiply, not add
repair_cost_accumulation_rule=Z_L = product(max(1, kappa_level_mean)) over active replay scales
zero_mass_control_rule=all-zero and uniform synchronized cross-scale states remain fixed under update and produce zero active repair cost
negative_controls_present=1
photon_zero_rest_mass_control_present=1
gluon_zero_rest_mass_control_present=1
base_max_kappa_per_step=68
hierarchical_max_Z_L_before_target_load=21381376
hierarchical_max_ratio_bound_before_target_load=342102016
model2_pre_registration_receipt_hash_generated=1
latticra_identity_replay_model2_hierarchical_range_capacity_present=1
model2_pre_registration_receipt_hash_valid=1
target_load_after_pre_registration_receipt=1
dynamic_range_capacity_evaluated_against_targets=1
target_ratio_recovery_evaluated=0
target_max_ratio_to_electron=337691.49623497269417
target_max_ratio_identity=I_top
hierarchical_capacity_margin_over_target=1013.0607960644598980091844681183754361457383377083533724071360813038948924026433
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

## Public Meaning

The careful public meaning is:

```text
Model-2 hierarchical replay clears the necessary dynamic-range capacity gate that killed Model-1. It is now eligible for a prediction-only hierarchical replay runner, but no mass-ratio recovery or Higgs-checkmate claim is open.
```

The follow-on Model-2 Prediction Runner now records that the first deterministic hierarchical replay prediction law is rejected by the guarded target table.

## Guard Validation

This status record is guarded by:

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

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
