# Latticra Identity-Replay Model-1 Bounded Range Falsifier

Status: guarded Model-1 falsifier
Date: 2026-05-29 CDT
Scope: bounded-range conclusion for the first Model-1 dynamic replay substrate class.

## Purpose

This artifact gives the first hard conclusion after Model-1.

The Model-1 dynamic runner is useful because it computes replay cost from substrate dynamics before target loading. But its finite bounded-cell substrate has a strict impedance range. If that range cannot cover the measured target vector, then the class is falsified as a mass-ratio recovery candidate before any more fitting is attempted.

This is not a defeat of identity-replay impedance as a research program. It is a falsifier for this bounded Model-1 class:

```text
finite cyclic bounded-cell L1 repair substrate
```

## Falsifier Checkpoint

```text
latticra_identity_replay_model1_bounded_range_falsifier_present=1
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

## Range Bound

The current Model-1 repair cost is L1 cell repair over a width-17 lattice whose projected cells are bounded to `[-2,2]`.

The maximum per-cell difference is:

```text
max_cell_delta=4
```

So the maximum per-step repair cost is:

```text
max_kappa_per_step = width * max_cell_delta * repair_cost_unit
                   = 17 * 4 * 1
                   = 68
```

Even under the more generous horizon-mean allowance where a nonzero anchor could average only `1/16`, the largest possible electron-normalized ratio is:

```text
max_ratio_bound_with_any_nonzero_horizon_mean=1088
```

The guarded target table reaches:

```text
target_max_ratio_to_electron=337691.49623497269417
```

Therefore:

```text
target_ratio_exceeds_bounded_model1_range=1
model1_bounded_substrate_class_falsified=1
```

## Current Conclusion

The current conclusion is:

```text
The finite bounded-cell Model-1 substrate class cannot recover the measured particle mass-ratio vector.
```

That is a real conclusion, but it is scoped. It does not kill Latticra's identity-replay impedance hypothesis. It kills this bounded substrate class as the candidate that could checkmate Higgs-only causal closure.

The next candidate must include:

```text
hierarchical impedance
multiscale replay cost
or another mechanism that produces a large ratio spread before target comparison
```

## Invocation

```sh
python3 tools/latticra_identity_replay_model1_range_falsifier.py \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
```

## Validation

This falsifier is guarded by:

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

The next model should be pre-registered before target comparison and must show how large mass-ratio dynamic range can arise without measured-mass insertion.

## Non-Claims

This bounded-range falsifier is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
