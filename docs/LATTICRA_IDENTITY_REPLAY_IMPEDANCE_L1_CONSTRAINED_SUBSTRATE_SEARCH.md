# Latticra Identity-Replay Impedance L1 Constrained Substrate Search

Status: guarded executable search harness
Date: 2026-05-29 CDT
Scope: deterministic target-guided search over a constrained identity-feature impedance family after the L0 toy substrate failure.

## Purpose

L0 proved the proof lane can kill a weak candidate. L1 adds the next pressure test: a constrained search over small integer-weight log-impedance laws.

The search is useful only if it stays honest. L1 is target-guided, so it cannot be treated as independent proof. It must expose target use, parameter count, overfit risk, leave-one-out behavior, receipt hash, and non-claims.

## Search Checkpoint

```text
latticra_identity_replay_impedance_l1_constrained_substrate_search_present=1
search_id=latticra-identity-replay-impedance-l1-constrained-substrate-search
search_version=1
candidate_family_id=log-linear-small-integer-identity-feature-impedance
candidate_family_version=1
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
l0_runner_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md
search_tool=tools/latticra_identity_replay_l1_search.py
search_deterministic=1
target_guided_search_performed=1
targets_used_for_candidate_scoring=1
measured_masses_used_in_kappa=0
leave_one_out_validation_performed=1
receipt_hash_generated=1
overfit_risk_flag=1
candidate_survives_target_table=0
candidate_survives_leave_one_out=0
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

## Candidate Family

L1 searches this family:

```text
log10(Z_L(I) / Z_L(I_e)) =
  (w . phi(I)) / weight_scale
```

where `w` is a small integer vector and `phi(I)` is the identity-feature vector:

```text
generation_lift
generation_square_lift
localization_excess
electroweak_spin_load
scalar_load
color_localization_load
boundary_oscillation_load
charge_gap_to_electron
```

The search bounds are:

```text
weight_min=-20
weight_max=20
weight_scale=10
```

## Invocation

```sh
python3 tools/latticra_identity_replay_l1_search.py
```

The runner emits JSON with:

```text
best_weight_vector
best_mean_abs_log10_error
best_max_abs_log10_error
candidate_survives_target_table
leave_one_out
candidate_survives_leave_one_out
receipt_hash
```

## Anti-Smuggling Boundary

L1 is allowed to use target masses for scoring because it is a search harness. It is not allowed to hide that target use.

The receipt must therefore include:

```text
target_guided_search_performed=1
targets_used_for_candidate_scoring=1
measured_masses_used_in_kappa=0
candidate_promoted=0
mass_ratio_recovery_claimed=0
```

## Current L1 Result

The current L1 search emits a best candidate and receipt, but does not survive the target table or leave-one-out review:

```text
candidate_survives_target_table=0
candidate_survives_leave_one_out=0
overfit_risk_flag=1
```

This is a stronger result than a verbal claim. It narrows the path: the next candidate must either reduce overfit risk, pre-register a substrate law before target scoring, or provide a blinded holdout that survives.

## Higgs Checkmate Boundary

The legitimate checkmate remains:

```text
Higgs-only causal closure does not derive the target mass-ratio vector from substrate primitives.
Latticra must derive that vector from a replayable impedance ledger without smuggling target masses.
L1 does not yet do that; it makes the failure measurable.
```

L1 challenges Higgs-only closure by defining the computable burden. It does not refute the Higgs mechanism and does not claim final proof.

## Validation

This search lane is guarded by:

```sh
sh scripts/test-latticra-identity-replay-impedance-l1-constrained-substrate-search.sh
```

Expected output:

```text
latticra_identity_replay_impedance_l1_constrained_substrate_search: ok
```

## Next Recommended Lane

```text
Identity-replay impedance L2 pre-registered substrate law with blinded holdout.
```

## Non-Claims

This search is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not Model-1 execution, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
