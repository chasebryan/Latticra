# Latticra Identity-Replay Impedance Candidate Particle Table Status

Status: guarded target-table status
Date: 2026-05-29 CDT
Scope: status checkpoint for the measured target table that follows Proof Object 4.

## Summary

Latticra now has a guarded target table for identity-replay impedance candidate particles.

The status meaning is narrow. The table records measured particle mass-ratio targets, candidate identity labels, source anchors, and falsifier conditions. It does not compute `Z_L`, recover mass ratios, replace the Standard Model, deny Higgs evidence, or prove that reality is simulated.

## Status Fields

```text
latticra_identity_replay_impedance_candidate_particle_table_present=1
latticra_identity_replay_impedance_candidate_particle_table_guard_present=1
candidate_table_id=latticra-identity-replay-impedance-candidate-particle-table
candidate_table_version=1
proof_object_reference=docs/LATTICRA_PROOF_OBJECT_4_IDENTITY_REPLAY_IMPEDANCE.md
source_reference=pdg_2025_update_summary_tables
source_cutoff_date=2025-01-15
mass_target_snapshot_date=2026-05-29
measured_mass_ratio_targets_present=1
candidate_identity_classes_named=1
cms_2026_w_mass_watch_note_present=1
cms_2026_measurement_inside_current_target_cutoff=0
current_table_target_mutated_by_cms_2026_measurement=0
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

## Target Coverage

```text
electron_candidate_identity=I_e
muon_candidate_identity=I_mu
tau_candidate_identity=I_tau
W_candidate_identity=I_W
Z_candidate_identity=I_Z
Higgs_candidate_identity=I_H
top_candidate_identity=I_top
tau_over_muon_target=16.81769184497825257592
W_over_Z_target=0.88135719612229679344
cms_2026_w_over_current_Z_ratio=0.88125849892529718823
Higgs_over_Z_target=1.37298767381673027153
top_over_Higgs_target=1.37827476038338658147
```

## Public Meaning

The careful public meaning is:

```text
Latticra has moved from theorem shape to target ledger: identity-replay impedance must now produce particle mass ratios from replay receipts and counterfactual repair costs, without inserting the measured masses as substrate inputs.
```

## Guard Validation

This status record is guarded by:

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

## Non-Claims

This status record is not a Latticra mass computation, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not Model-1 execution, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
