# Latticra Q-Seal ML-KEM Implementation Frame

Status: clean-room implementation design frame
Date: 2026-05-27
Scope: ML-KEM module planning and implementation blockers before primitive code.

This slice names the clean-room ML-KEM implementation modules that Latticra Q-Seal will eventually need, while explicitly blocking implementation until constant-time, secret-branch, secret-memory, zeroization, randomness, serialization, malformed-input, test-vector, and formal-review records exist.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_frame.h
latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

## Current Fields

```text
ml_kem_implementation_frame_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation Frame
implementation_profile=latticra-q-seal-ml-kem-implementation-frame/0.1
source_boundary=clean-room-no-apple-code
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
parameter_sets_recorded=1
module_plan_recorded=1
planned_module_count=9
polynomial_arithmetic_planned=1
ntt_planned=1
sampling_planned=1
compression_planned=1
encoding_planned=1
hash_xof_planned=1
keygen_planned=1
encaps_planned=1
decaps_planned=1
implementation_code_present=0
polynomial_arithmetic_implemented=0
ntt_implemented=0
sampling_implemented=0
compression_implemented=0
encoding_implemented=0
hash_xof_implemented=0
keygen_implemented=0
encaps_implemented=0
decaps_implemented=0
constant_time_design_required=1
constant_time_design_recorded=0
secret_branch_review_required=1
secret_branch_review_recorded=0
secret_memory_review_required=1
secret_memory_review_recorded=0
zeroization_design_required=1
zeroization_design_recorded=0
randomness_design_required=1
randomness_design_recorded=0
serialization_canonicality_required=1
serialization_canonicality_recorded=0
malformed_input_policy_required=1
malformed_input_policy_recorded=0
test_vector_binding_required=1
test_vector_binding_recorded=0
formal_review_required=1
formal_review_recorded=0
operations_enabled=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_design_items_total=12
required_design_items_satisfied=3
blocked_reason=constant-time-secret-memory-zeroization-randomness-serialization-test-vector-and-formal-reviews-missing
status=ml-kem-implementation-frame-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
```
