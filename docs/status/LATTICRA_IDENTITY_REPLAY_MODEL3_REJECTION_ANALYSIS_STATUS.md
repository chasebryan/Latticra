# Latticra Identity-Replay Model-3 Rejection Analysis Status

Status: guarded Model-3 rejection analysis status
Date: 2026-05-29 CDT
Scope: status checkpoint for Model-3 rejection analysis and refinement gate.

## Summary

Latticra now has a guarded rejection analysis for the first deterministic Model-3 prediction law.

The status meaning is narrow. Model-3 improved range but failed sector placement and identity ordering. A refined Model-3 pre-registration is authorized; no prediction runner, mass recovery, or Higgs checkmate is authorized.

## Status Fields

```text
latticra_identity_replay_model3_rejection_analysis_present=1
latticra_identity_replay_model3_rejection_analysis_guard_present=1
latticra_identity_replay_model3_refinement_gate_present=1
analysis_id=latticra-identity-replay-model3-rejection-analysis
gate_id=latticra-identity-replay-model3-refinement-gate
analysis_tool=tools/latticra_identity_replay_model3_rejection_analysis.py
gate_tool=tools/latticra_identity_replay_model3_refinement_gate.py
model3_prediction_receipt_hash_valid=1
model3_evaluation_receipt_hash_valid=1
model3_rejection_analysis_receipt_hash_valid=1
prediction_receipt_emitted_before_target_load=1
target_load_after_prediction_receipt=1
prediction_law_id=model3-target-blind-topological-replay-amplification
model3_prediction_law_rejected=1
model3_prediction_conclusion=rejected_by_target_table
prediction_dynamic_range=61685.116071428571428571428571428571428571428571428571428571428571428571428571427
target_dynamic_range=337691.49623497269417
dynamic_range_deficit_factor=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395
prediction_dynamic_range_meets_target_range=0
target_count=7
failed_identity_count=6
surviving_identity_count=1
failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top
predicted_identity_order_by_ratio=I_H,I_Z,I_e,I_tau,I_mu,I_W,I_top
target_identity_order_by_ratio=I_e,I_mu,I_tau,I_W,I_Z,I_H,I_top
ordering_failure_present=1
lepton_family_order_inversion_present=1
lepton_family_gap_underestimated=1
heavy_sector_underamplified=1
low_electroweak_below_electron_present=1
low_electroweak_below_electron_targets=Higgs boson,Z boson
top_quark_still_underamplified=1
non_anchor_min_required_multiplier=10.292350482886447063105680868838763575605680868838763575605680868838763575605681
non_anchor_max_required_multiplier=844629.21666892438261939285714285714285714285714285714285714285714285714285714286
single_global_amplifier_insufficient=1
required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity
refined_model3_required_law_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity
minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395
refined_model3_preregistration_authorized=1
refined_model3_prediction_runner_authorized=0
refined_model3_candidate_promoted=0
model3_refinement_gate_conclusion=worth_refining_only_not_worth_promoting
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
model3_rejection_analysis_receipt_hash_generated=1
model3_refinement_gate_receipt_hash_generated=1
```

## Public Meaning

The careful public meaning is:

```text
Model-3 was useful because it failed specifically: global topological amplification improved range but did not recover sector placement or identity ordering. The next candidate must be pre-registered as a target-blind sector-resolved topological charge law with family monotonicity.
```

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model3-rejection-analysis.sh
```

Expected output:

```text
latticra_identity_replay_model3_rejection_analysis: ok
```

## Next Recommended Lane

```text
Identity-replay impedance refined Model-3 sector-resolved topological charge pre-registration.
```

## Non-Claims

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
