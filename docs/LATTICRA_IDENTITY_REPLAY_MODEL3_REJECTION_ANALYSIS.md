# Latticra Identity-Replay Model-3 Rejection Analysis

Status: guarded Model-3 rejection analysis and refinement gate
Date: 2026-05-29 CDT
Scope: post-evaluation rejection analysis for the first Model-3 prediction law.

## Purpose

The first Model-3 prediction runner gave a useful negative result. It improved dynamic range over Model-2, but it still failed the guarded target table.

This artifact explains why it failed and what a refined Model-3 law must add before a new prediction runner is allowed.

The [Model-3 Failure Visual Suite](LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE.md) renders this rejection as static SVG ratio, ordering, and sector-placement charts from the same receipted prediction/evaluation/analysis path.

The failure is not evidence against the Higgs mechanism and not evidence that Latticra has proved mass recovery. It is a stricter engineering constraint:

```text
Model-3 topological amplification improved range.
Model-3 prediction did not recover identity ordering or electroweak-sector placement.
A refined Model-3 is worthwhile only if it derives sector-resolved topological charge and family monotonicity before target loading.
```

## Rejection Analysis Checkpoint

```text
latticra_identity_replay_model3_rejection_analysis_present=1
analysis_id=latticra-identity-replay-model3-rejection-analysis
analysis_version=1
prediction_runner_reference=tools/latticra_identity_replay_model3_runner.py
evaluation_tool_reference=tools/latticra_identity_replay_model3_evaluate.py
analysis_tool=tools/latticra_identity_replay_model3_rejection_analysis.py
refinement_gate_reference=tools/latticra_identity_replay_model3_refinement_gate.py
model3_prediction_receipt_hash_valid=1
model3_evaluation_receipt_hash_valid=1
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
heavy_sector_min_predicted_ratio=0.29008029008029008029008029008029008029008029008029008029008029008029008029008029
heavy_sector_max_predicted_ratio=17893.636363636363636363636363636363636363636363636363636363636363636363636363636
non_anchor_min_required_multiplier=10.292350482886447063105680868838763575605680868838763575605680868838763575605681
non_anchor_max_required_multiplier=844629.21666892438261939285714285714285714285714285714285714285714285714285714286
top_quark_required_multiplier=18.872155964968244860387136107300716354214296601127876848041457094955037341868618
higgs_required_multiplier=844629.21666892438261939285714285714285714285714285714285714285714285714285714286
z_boson_required_multiplier=391586.95284820141955294117647058823529411764705882352941176470588235294117647058
w_boson_required_multiplier=256.71661498082145979047958214624881291547958214624881291547958214624881291547958
muon_required_multiplier=10.292350482886447063105680868838763575605680868838763575605680868838763575605681
tau_required_multiplier=257.38262584061088786140269151138716356107660455486542443064182194616977225672877
capacity_pass_was_not_prediction_recovery=1
single_global_amplifier_insufficient=1
required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity
minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395
refined_model3_pre_registration_required=1
refined_model3_prediction_runner_authorized=0
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
```

## Refinement Gate

```text
latticra_identity_replay_model3_refinement_gate_present=1
gate_id=latticra-identity-replay-model3-refinement-gate
gate_tool=tools/latticra_identity_replay_model3_refinement_gate.py
model3_rejection_analysis_receipt_hash_valid=1
model3_prediction_law_rejected=1
refined_model3_required_law_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity
minimum_refined_model3_dynamic_range_multiplier_required=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395
ordering_failure_must_be_addressed=1
lepton_family_order_inversion_must_be_addressed=1
low_electroweak_below_electron_must_be_addressed=1
heavy_sector_underamplification_must_be_addressed=1
single_global_amplifier_forbidden=1
refined_model3_preregistration_authorized=1
refined_model3_prediction_runner_authorized=0
refined_model3_candidate_promoted=0
refined_model3_worth_testing_if_preregistration_passes=1
refined_model3_pre_registration_receipt_required=1
refined_model3_prediction_receipt_before_target_load_required=1
refined_model3_target_load_after_prediction_receipt_required=1
parameter_count_less_than_target_count_required=1
negative_controls_required=1
photon_zero_rest_mass_control_required=1
gluon_zero_rest_mass_control_required=1
sector_resolved_topological_trace_required=1
family_monotonicity_trace_required=1
target_blind_dynamic_range_proof_required_before_prediction=1
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
model3_refinement_gate_receipt_hash_generated=1
```

## Failure Shape

The failure is not simply that the final number is too small. The first Model-3 law has a structural ordering problem:

```text
Model-3 predicted order: I_H, I_Z, I_e, I_tau, I_mu, I_W, I_top
Target order:            I_e, I_mu, I_tau, I_W, I_Z, I_H, I_top
```

The main blocker is sector placement. Higgs and Z land below electron-scale replay cost, even though the guarded target table places them in the heavy sector. The muon/tau family order is also inverted.

This means a single global topological multiplier is not enough. The next law must derive sector-resolved structure from the substrate without using particle names, target ratios, or post-target fitting.

## Current Conclusion

The current conclusion is:

```text
Model-3 is useful but not sufficient: it must be refined into a target-blind sector-resolved topological charge law with family monotonicity before another prediction run.
```

## Refined Model-3 Pre-Registration

The immediate follow-on lane is now guarded as [Refined Model-3 Pre-Registration](LATTICRA_IDENTITY_REPLAY_MODEL3_REFINED_PREREGISTRATION.md). It records the refined Model-3 sector-resolved topological charge pre-registration before target loading while keeping refined prediction and mass recovery closed.

## Invocation

Generate the Model-3 prediction and evaluation receipts:

```sh
python3 tools/latticra_identity_replay_model3_runner.py --predict-only \
  > reports/identity_replay_model3_predictions.json
python3 tools/latticra_identity_replay_model3_evaluate.py \
  --predictions reports/identity_replay_model3_predictions.json \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md \
  > reports/identity_replay_model3_evaluation.json
```

Then analyze the rejection:

```sh
python3 tools/latticra_identity_replay_model3_rejection_analysis.py \
  --predictions reports/identity_replay_model3_predictions.json \
  --evaluation reports/identity_replay_model3_evaluation.json \
  > reports/identity_replay_model3_rejection_analysis.json
```

Gate the next refinement:

```sh
python3 tools/latticra_identity_replay_model3_refinement_gate.py \
  --analysis reports/identity_replay_model3_rejection_analysis.json \
  > reports/identity_replay_model3_refinement_gate.json
```

## Validation

This lane is guarded by:

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

This rejection analysis is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
