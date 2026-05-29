# Latticra Identity-Replay Impedance L2 Pre-Registered Substrate Law With Blinded Holdout

Status: guarded pre-registration gate
Date: 2026-05-29 CDT
Scope: pre-registration receipt for a candidate identity-replay impedance law before any future blinded holdout can be opened.

## Purpose

L2 exists to stop Latticra from accidentally turning target-guided fitting into a proof claim.

L1 searched against known targets and therefore had to keep `higgs_checkmate_claimed=0`. L2 locks a candidate law and blinded-holdout protocol so a future target can be opened only after the law is committed by receipt.

## Pre-Registration Checkpoint

```text
latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout_present=1
pre_registration_id=latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout
pre_registration_version=1
candidate_law_id=identity-replay-impedance-l2-preregistered-log-linear-law
candidate_law_version=1
target_table_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md
l1_search_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L1_CONSTRAINED_SUBSTRATE_SEARCH.md
l0_runner_reference=docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_TOY_SUBSTRATE_L0_MASS_RATIO_RUNNER.md
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
pre_registration_tool=tools/latticra_identity_replay_l2_preregistration.py
pre_registered_law_present=1
pre_registration_receipt_hash_generated=1
blinded_holdout_protocol_defined=1
blinded_holdout_oracle_required=1
blinded_holdout_oracle_present=0
blinded_holdout_values_available_to_runner=0
holdout_evaluation_performed=0
candidate_survives_blinded_holdout=0
candidate_promoted=0
l1_target_guided_context_inherited=1
law_independence_from_prior_targets_proven=0
oracle_opened_after_pre_registration=0
measured_masses_used_in_kappa=0
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

## Pre-Registered Law

The locked candidate law is:

```text
log10(Z_L(I) / Z_L(I_e)) = dot(w, phi(I)) / 10
```

The current basis is:

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

The weight vector is inherited from the non-promoted L1 search:

```text
generation_lift=2
generation_square_lift=3
localization_excess=13
electroweak_spin_load=2
scalar_load=1
color_localization_load=-2
boundary_oscillation_load=0
charge_gap_to_electron=0
```

Because this law comes after target-guided L1 search, L2 records:

```text
l1_target_guided_context_inherited=1
law_independence_from_prior_targets_proven=0
```

## Blinded Holdout Protocol

A future holdout is acceptable only if an external reviewer or oracle provides a target after the pre-registration receipt exists.

The oracle must provide:

```text
oracle_id
oracle_version
pre_registration_receipt_hash
holdout_identity
holdout_feature_vector
holdout_ratio_to_electron
source_reference
source_cutoff_date
oracle_opened_after_pre_registration
reviewer_attestation
```

Before oracle opening, the runner must not see:

```text
holdout_ratio_to_electron
holdout_mass_mev
measured_mass_target
```

## Invocation

```sh
python3 tools/latticra_identity_replay_l2_preregistration.py
```

The tool emits a JSON receipt with:

```text
pre_registration_receipt_hash
pre_registered_law_present
blinded_holdout_protocol_defined
blinded_holdout_oracle_required
holdout_evaluation_performed
candidate_promoted
higgs_checkmate_claimed
```

## Current L2 Result

The current L2 result is a pre-registration receipt, not a holdout success:

```text
blinded_holdout_oracle_present=0
holdout_evaluation_performed=0
candidate_survives_blinded_holdout=0
candidate_promoted=0
higgs_checkmate_claimed=0
```

This is still progress. It creates the first hard gate where future proof language has to pass an independent target opening instead of reusing known masses.

## Higgs Checkmate Boundary

L2 sharpens the Higgs counterplay without overstating it:

```text
Higgs-only causal closure still does not derive the mass-ratio vector from substrate primitives.
Latticra now has a pre-registration receipt for a candidate ledger law.
No checkmate claim is allowed until a blinded holdout opens after that receipt and survives review.
```

## Validation

This pre-registration lane is guarded by:

```sh
sh scripts/test-latticra-identity-replay-impedance-l2-preregistered-substrate-law-blinded-holdout.sh
```

Expected output:

```text
latticra_identity_replay_impedance_l2_preregistered_substrate_law_blinded_holdout: ok
```

## Next Recommended Lane

```text
Identity-replay impedance L3 external blinded-holdout intake.
```

The guarded intake handoff is:

```text
L3 External Blinded-Holdout Intake.
```

L3 must validate that any future oracle is bound to the L2 receipt and was opened after pre-registration, while keeping `holdout_evaluation_performed=0` when no oracle is supplied.

The guarded execution-gate handoff is:

```text
L4 Blinded-Holdout Execution Gate.
```

L4 must define the prediction execution rule and acceptance boundary while keeping `holdout_execution_performed=0` when no oracle is supplied.

## Non-Claims

This pre-registration is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not blinded holdout success, not Model-1 execution, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
