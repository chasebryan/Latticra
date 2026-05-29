# Latticra Identity-Replay Model-1 Bounded Range Falsifier Status

Status: guarded Model-1 falsifier status
Date: 2026-05-29 CDT
Scope: status checkpoint for the bounded-range conclusion after Model-1 dynamic replay.

## Summary

Latticra now has a bounded-range falsifier for the first Model-1 substrate class.

The status meaning is narrow. The finite bounded-cell Model-1 substrate cannot express enough electron-normalized replay-cost dynamic range to recover the measured target vector. The class is falsified as a mass-ratio recovery candidate while the broader identity-replay impedance research program remains open.

## Status Fields

```text
latticra_identity_replay_model1_bounded_range_falsifier_present=1
latticra_identity_replay_model1_bounded_range_falsifier_guard_present=1
falsifier_id=latticra-identity-replay-model1-bounded-range-falsifier
falsifier_version=1
model1_runner_reference=tools/latticra_identity_replay_model1_substrate.py
model1_evaluator_reference=tools/latticra_identity_replay_model1_evaluate.py
range_falsifier_tool=tools/latticra_identity_replay_model1_range_falsifier.py
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
bounded_substrate_class_scope=Model-1 finite cyclic bounded-cell L1 repair substrate
width=17
max_cell_abs=2
repair_cost_unit=1
replay_horizon_N=16
epsilon_identity_tolerance=0
parameter_count=4
target_count=7
parameter_count_less_than_target_count=1
max_cell_delta=4
max_kappa_per_step=68
max_Z_L_under_bounded_repair=68
min_positive_horizon_mean=0.0625
max_ratio_bound_with_current_stationary_replay=68
max_ratio_bound_with_any_nonzero_horizon_mean=1088
target_max_ratio_to_electron=337691.49623497269417
target_ratio_exceeds_bounded_model1_range=1
model1_bounded_substrate_class_falsified=1
bounded_model1_conclusion=falsified_as_mass_ratio_recovery_candidate
required_next_substrate_property=hierarchical or multiscale impedance range before target-table recovery can be credible
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
falsifier_receipt_hash_generated=1
```

## Public Meaning

The careful public meaning is:

```text
The current finite bounded-cell Model-1 substrate is falsified as a mass-ratio recovery candidate because its maximum replay-cost ratio is too small for the measured target vector. Latticra must move to a pre-registered hierarchical or multiscale substrate before stronger Higgs-causal-closure language is credible.
```

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model1-bounded-range-falsifier.sh
```

Expected output:

```text
latticra_identity_replay_model1_bounded_range_falsifier: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-2 hierarchical substrate pre-registration.
```

## Non-Claims

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
