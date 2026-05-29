# Latticra Identity-Replay Model-2 Prediction Failure Analysis

Status: guarded Model-2 failure analysis and Model-3 requirement
Date: 2026-05-29 CDT
Scope: post-evaluation failure analysis for the first Model-2 prediction law.

## Purpose

The Model-2 prediction runner gave a real answer: the first deterministic hierarchical replay law failed the target table.

This artifact explains why it failed and what any worthwhile Model-3 must add before a new prediction runner is allowed.

The failure is not a reason to claim defeat of identity-replay impedance. It is a useful constraint:

```text
Model-2 hierarchy gave range capacity.
Model-2 prediction did not generate the required identity ordering or heavy-sector amplification.
Model-3 is worthwhile only if it introduces target-blind topological replay amplification before target loading.
```

## Failure Analysis Checkpoint

```text
latticra_identity_replay_model2_prediction_failure_analysis_present=1
analysis_id=latticra-identity-replay-model2-prediction-failure-analysis
analysis_version=1
prediction_runner_reference=tools/latticra_identity_replay_model2_runner.py
evaluation_tool_reference=tools/latticra_identity_replay_model2_evaluate.py
analysis_tool=tools/latticra_identity_replay_model2_failure_analysis.py
model3_worthiness_gate_reference=tools/latticra_identity_replay_model3_worthiness_gate.py
model2_prediction_receipt_hash_valid=1
model2_evaluation_receipt_hash_valid=1
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
predicted_identity_order_by_ratio=I_top,I_Z,I_H,I_e,I_tau,I_W,I_mu
target_identity_order_by_ratio=I_e,I_mu,I_tau,I_W,I_Z,I_H,I_top
ordering_failure_present=1
lepton_family_order_inversion_present=1
lepton_family_gap_underestimated=1
heavy_sector_compression_present=1
heavy_sector_max_predicted_ratio=2.5212121212121212121212121212121212121212121212121212121212121212121212121212121
heavy_sector_min_target_ratio=157278.60106170472562
heavy_sector_min_required_multiplier=62382.137440339614729086538461538461538461538461538461538461538461538461538461539
heavy_sector_max_required_multiplier=1114381.937575409890761
top_quark_amplification_required=1114381.937575409890761
required_model3_property=target_blind_topological_replay_amplification
minimum_model3_dynamic_range_multiplier_required=15281.221982228644612259816207184628237259816207184628237259816207184628237259816
model3_worthiness_gate_required=1
model3_prediction_runner_authorized=0
model3_preregistration_worthwhile_if_gate_passes=1
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
```

## Failure Shape

The failure is not just numeric distance. It has structure:

```text
Model-2 predicted order: I_top, I_Z, I_H, I_e, I_tau, I_W, I_mu
Target order:          I_e, I_mu, I_tau, I_W, I_Z, I_H, I_top
```

That means the next law must fix both scale and ordering. A larger multiplier alone is not enough.

The heavy sector is the main blocker. Model-2 predicts all heavy-sector identities below or near electron-scale replay cost, while the target table requires W/Z/H/top to sit orders of magnitude above electron.

## Current Conclusion

The current conclusion is:

```text
Model-3 is worthwhile only if it can pre-register a target-blind topological replay amplification law.
```

The required amplification cannot be a particle-name lookup, a target-ratio weight, a post-target optimizer, or a feature layer derived from measured masses.

## Invocation

Generate the Model-2 prediction and evaluation receipts:

```sh
python3 tools/latticra_identity_replay_model2_runner.py --predict-only \
  > reports/identity_replay_model2_predictions.json
python3 tools/latticra_identity_replay_model2_evaluate.py \
  --predictions reports/identity_replay_model2_predictions.json \
  --targets docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md \
  > reports/identity_replay_model2_evaluation.json
```

Then analyze the failure:

```sh
python3 tools/latticra_identity_replay_model2_failure_analysis.py \
  --predictions reports/identity_replay_model2_predictions.json \
  --evaluation reports/identity_replay_model2_evaluation.json \
  > reports/identity_replay_model2_failure_analysis.json
```

## Validation

This lane is guarded by:

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

## Non-Claims

This failure analysis is not a Latticra mass recovery, not a Standard Model replacement, not a denial of CERN/ATLAS/CMS data, not a denial of the Higgs boson, not a proof that reality is simulated, not physics measurement, not experimental evidence, not a completed particle spectrum derivation, not final checkmate against Higgs, not external oracle evidence, not independent reproduction, not a Standard Model precision-shadow pass, not a new experimental prediction, not scientific claim promotion, not runtime execution, not effect execution, not production readiness, not operating-system completeness, and not public promotion of a final scientific conclusion.
