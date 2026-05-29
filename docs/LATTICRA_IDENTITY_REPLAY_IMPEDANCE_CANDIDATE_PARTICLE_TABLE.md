# Latticra Identity-Replay Impedance Candidate Particle Table

Status: guarded target table
Date: 2026-05-29 CDT
Scope: measured particle mass-ratio targets for the next identity-replay impedance computation lane.

## Purpose

This table is the first hard target ledger after Proof Object 4.

Proof Object 4 defines:

```text
mass is the minimal replay-stable cost required for a localized projected identity to remain itself under substrate update.
```

This document does not compute that cost yet. It records the target particle identities, measured mass ratios, falsifier conditions, and anti-smuggling rules a later Latticra runner must satisfy before any mass-recovery claim can be promoted.

## Candidate Table Checkpoint

```text
latticra_identity_replay_impedance_candidate_particle_table_present=1
candidate_table_id=latticra-identity-replay-impedance-candidate-particle-table
candidate_table_version=1
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
source_reference=pdg_2025_update_summary_tables
source_cutoff_date=2025-01-15
mass_target_snapshot_date=2026-05-29
measured_mass_ratio_targets_present=1
candidate_identity_classes_named=1
ledger_computation_performed=0
identity_replay_impedance_values_computed=0
mass_ratio_recovery_claimed=0
standard_model_replacement_claimed=0
higgs_denied=0
simulation_proven=0
reality_simulation_claimed=0
physics_bound_by_simulative_concepts_claimed=0
scientific_claim_promoted=0
```

## External Source Anchors

The target masses are external validation anchors, not Latticra-derived values.

```text
pdg_home_url=https://pdg.lbl.gov/
pdg_summary_tables_url=https://pdg.lbl.gov/2025/tables/contents_tables.html
pdg_lepton_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-leptons.pdf
pdg_gauge_higgs_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-gauge-higgs-bosons.pdf
pdg_quark_summary_url=https://pdg.lbl.gov/2025/tables/rpp2025-sum-quarks.pdf
```

Source notes:

```text
PDG 2025 update cites S. Navas et al. (Particle Data Group), Phys. Rev. D 110, 030001 (2024) and 2025 update.
The PDG listings and summary-table cutoff date is Jan. 15, 2025.
```

## Anti-Smuggling Rule

A later Latticra runner is not allowed to insert the measured mass values into `kappa`, `R`, `Q`, or the substrate update rule.

The measured table can only be used after the candidate substrate has already emitted:

```text
fixed_substrate_definition
candidate_identity_class_definition
replay_receipt
counterfactual_repair_cost_trace
Z_L_estimate
mass_ratio_prediction
prediction_error_against_external_target
```

If the measured masses are used to tune the ledger after target inspection, the candidate fails this table.

## Candidate Identity Targets

All masses are expressed in MeV. Ratios are computed against the electron target mass `0.51099895000 MeV`.

| Target | Candidate identity class | Measured mass target | Ratio target to electron | Latticra ledger status | Primary test |
| --- | --- | ---: | ---: | --- | --- |
| electron | `I_e` | `0.51099895000` | `1` | `Z_L(I_e)=uncomputed` | anchor target for ratio-only comparison |
| muon | `I_mu` | `105.6583755` | `206.76828298766563023` | `Z_L(I_mu)=uncomputed` | `Z_L(I_mu)/Z_L(I_e)` |
| tau | `I_tau` | `1776.93` | `3477.36526660181982761` | `Z_L(I_tau)=uncomputed` | `Z_L(I_tau)/Z_L(I_e)` |
| W boson | `I_W` | `80369.2` | `157278.60106170472562` | `Z_L(I_W)=uncomputed` | `Z_L(I_W)/Z_L(I_e)` |
| Z boson | `I_Z` | `91188.0` | `178450.46452639481940` | `Z_L(I_Z)=uncomputed` | `Z_L(I_Z)/Z_L(I_e)` |
| Higgs boson | `I_H` | `125200` | `245010.28818160976652` | `Z_L(I_H)=uncomputed` | `Z_L(I_H)/Z_L(I_e)` |
| top quark | `I_top` | `172560` | `337691.49623497269417` | `Z_L(I_top)=uncomputed` | `Z_L(I_top)/Z_L(I_e)` |

## Cross-Ratio Targets

The next runner should report both electron-normalized ratios and cross-ratios, because cross-ratios make scale insertion harder to hide.

```text
tau_over_muon_target=16.81769184497825257592
W_over_Z_target=0.88135719612229679344
Higgs_over_Z_target=1.37298767381673027153
top_over_Higgs_target=1.37827476038338658147
```

## What A Later Runner Must Emit

A numeric candidate can only advance past this table if it emits:

```text
candidate_substrate_id
candidate_substrate_version
state_space_definition
local_update_operator
observer_projection
identity_quotient
distance_metric
counterfactual_repair_cost_function
receipt_hash
replay_horizon_N
epsilon_identity_tolerance
Z_L_estimates
mass_ratio_predictions
error_vector_against_target_table
parameter_count
compression_argument_against_free_mass_insertion
failure_record_if_any_target_breaks
```

## Falsifier Conditions

This target table kills or narrows a candidate if any of these are true:

```text
identity_quotient_not_defined_for_candidate_class
replay_receipt_not_generated_for_candidate_class
counterfactual_repair_cost_not_computable
Z_L_diverges_for_candidate_particle
Z_L_collapses_to_zero_for_massive_target
ratio_fit_requires_measured_mass_insertion
free_parameter_count_exceeds_observable_compression
mass_ratio_recovery_mismatch_exceeds_epsilon_after_model_fixed
higgs_coupling_shadow_test_fails
low_energy_lorentz_behavior_not_recovered
receipt_replay_not_independent
```

## Higgs Boundary

This table does not deny Higgs evidence. It treats the Higgs mass and electroweak boson mass targets as external constraints that an identity-replay impedance ledger must reproduce or fail.

The check is:

```text
Higgs can remain the effective coupling map.
Latticra must derive a substrate impedance ledger whose ratios project to the observed targets.
If the ledger cannot do this without smuggling the measured masses into the substrate, the candidate fails.
```

## Public Statement

The strongest legitimate public statement for this table is:

```text
Latticra now has a guarded candidate-particle target table for identity-replay impedance: measured mass-ratio anchors that a future replay ledger must derive without inserting the measured masses as inputs.
```

## Validation

This target table is guarded by:

```sh
sh scripts/test-latticra-identity-replay-impedance-candidate-particle-table.sh
```

Expected output:

```text
latticra_identity_replay_impedance_candidate_particle_table: ok
```

## Next Recommended Lane

```text
Identity-replay impedance toy substrate L0 mass-ratio runner.
```

The guarded executable handoff is:

```text
Toy Substrate L0 Mass-Ratio Runner.
```

The L0 runner must compute toy `Z_L` ratios, emit a receipt hash, compare against this target table, and preserve `mass_ratio_recovery_claimed=0` unless the target vector is recovered without measured-mass insertion.

The next guarded search artifact is:

```text
L1 Constrained Substrate Search.
```

L1 may use this table for scoring only if it records `target_guided_search_performed=1`, `targets_used_for_candidate_scoring=1`, and `candidate_promoted=0` unless independent validation survives.

The next pre-registration artifact is:

```text
L2 Pre-Registered Substrate Law With Blinded Holdout.
```

L2 must not treat this already-known table as blinded evidence.

## Non-Claims

This table is not a Latticra mass computation, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not Model-1 execution, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
