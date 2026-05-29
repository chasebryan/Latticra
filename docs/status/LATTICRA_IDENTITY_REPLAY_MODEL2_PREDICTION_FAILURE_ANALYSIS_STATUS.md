# Latticra Identity-Replay Model-2 Prediction Failure Analysis Status

Status: guarded Model-2 failure analysis status
Date: 2026-05-29 CDT
Scope: status checkpoint for Model-2 failure analysis and the Model-3 worthiness gate.

## Summary

Latticra now has a guarded failure analysis for the first deterministic Model-2 prediction law.

The status meaning is narrow. Model-3 is not promoted and no prediction runner is authorized. The only authorized next move is pre-registration of a target-blind topological amplification law.

## Status Fields

```text
latticra_identity_replay_model2_prediction_failure_analysis_present=1
latticra_identity_replay_model2_prediction_failure_analysis_guard_present=1
latticra_identity_replay_model3_worthiness_gate_present=1
analysis_id=latticra-identity-replay-model2-prediction-failure-analysis
gate_id=latticra-identity-replay-model3-worthiness-gate
analysis_tool=tools/latticra_identity_replay_model2_failure_analysis.py
model3_worthiness_gate_reference=tools/latticra_identity_replay_model3_worthiness_gate.py
gate_tool=tools/latticra_identity_replay_model3_worthiness_gate.py
model2_prediction_receipt_hash_valid=1
model2_evaluation_receipt_hash_valid=1
model2_failure_analysis_receipt_hash_valid=1
prediction_receipt_emitted_before_target_load=1
target_load_after_prediction_receipt=1
prediction_law_id=model2-hierarchical-hash-seeded-scale-product-law
model2_prediction_law_rejected=1
model2_prediction_conclusion=rejected_by_target_table
prediction_dynamic_range=22.098461538461538461538461538461538461538461538461538461538461538461538461538462
target_dynamic_range=337691.49623497269417
dynamic_range_deficit_factor=15281.221982228644612259816207184628237259816207184628237259816207184628237259816
prediction_dynamic_range_meets_target_range=0
target_count=7
failed_identity_count=6
surviving_identity_count=1
failure_record_if_any_target_breaks=I_mu,I_tau,I_W,I_Z,I_H,I_top
ordering_failure_present=1
lepton_family_order_inversion_present=1
lepton_family_gap_underestimated=1
heavy_sector_compression_present=1
heavy_sector_min_required_multiplier=62382.137440339614729086538461538461538461538461538461538461538461538461538461539
heavy_sector_max_required_multiplier=1114381.937575409890761
top_quark_amplification_required=1114381.937575409890761
required_model3_property=target_blind_topological_replay_amplification
model3_required_law_property=target_blind_topological_replay_amplification
minimum_model3_dynamic_range_multiplier_required=15281.221982228644612259816207184628237259816207184628237259816207184628237259816
model3_worthiness_gate_required=1
model3_preregistration_authorized=1
model3_prediction_runner_authorized=0
model3_candidate_promoted=0
model3_preregistration_worthwhile_if_gate_passes=1
model3_worth_testing_if_preregistration_passes=1
model3_gate_conclusion=worth_preregistering_only_not_worth_promoting
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
model2_failure_analysis_receipt_hash_generated=1
model3_worthiness_gate_receipt_hash_generated=1
```

## Public Meaning

The careful public meaning is:

```text
Model-2 failed because it compressed heavy-sector replay cost and inverted the required identity ordering. Model-3 is only worthwhile as a pre-registered target-blind topological amplification candidate; it is not yet a prediction, mass recovery, or Higgs checkmate.
```

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-identity-replay-model2-prediction-failure-analysis.sh
```

Expected output:

```text
latticra_identity_replay_model2_prediction_failure_analysis: ok
```

## Next Recommended Lane

```text
Identity-replay impedance Model-3 target-blind topological amplification pre-registration.
```

The guarded follow-on is now the Model-3 Topological Amplification Pre-Registration and capacity gate.

## Non-Claims

This status record is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
