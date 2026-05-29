# Latticra Q-Seal ML-KEM Implementation Frame

Status: clean-room design frame only
Date: 2026-05-27
Scope: ML-KEM implementation module plan before any cryptographic primitive code.

This frame names the clean-room ML-KEM components Latticra Q-Seal will need before implementation begins. It does not implement polynomial arithmetic, NTT, sampling, compression, encoding, hash/XOF behavior, key generation, encapsulation, decapsulation, provider comparison, production cryptography, FIPS validation, network behavior, host mutation, or runtime authority.

Constant-time implementation promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md`; this frame does not claim timing measurements, static-analysis results, generated-assembly review, or formal signoff.

Randomness-source promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md`; this frame does not claim entropy validation, DRBG selection, random byte generation, or platform RNG review.

Zeroization promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md`; this frame does not claim a wipe primitive, dead-store-elimination review, memory-scan testing, generated-assembly review, or secret-material handling authority.

Negative-test promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md`; this frame does not claim length-validation tests, encoding canonicality tests, invalid ciphertext tests, invalid key tests, decapsulation-failure tests, implicit-rejection tests, parser-rejection tests, fuzzing corpus, differential negative tests, or implementation binding.

Memory-safety promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md`; this frame does not claim overflow review, bounds review, sanitizer evidence, static-analysis evidence, fuzzing evidence, alias/lifetime review, secret-buffer isolation, zeroization binding, or implementation binding.

API misuse-resistance promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md`; this frame does not claim error taxonomy, API state machine, misuse-case matrix, misuse tests, language-binding review, documentation review, public API execution, or implementation binding.

CI promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md`; this frame does not claim KAT/ACVP passing records, constant-time passing records, memory-safety passing records, side-channel passing records, provider differential passing records, promotion workflow evidence, release-claim gates, or signed artifact receipts.

Implementation binding is gated separately by `latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md`; this frame does not claim implementation-file digest records, keygen binding approval, encapsulation binding approval, decapsulation binding approval, code-owner review, or primitive operation binding.

Side-channel promotion is gated separately by `latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md`; this frame does not claim a leakage model, power-analysis result, timing measurement, cache-access analysis, fault-injection review, compiler-artifact review, platform matrix, negative leakage test, reviewer signoff, or implementation binding.

## Current Fields

```text
ml_kem_implementation_frame_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation Frame
implementation_profile=latticra-q-seal-ml-kem-implementation-frame/0.1
source_boundary=clean-room-no-apple-code
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
status=ml-kem-implementation-frame-blocked
```

## Non-Claims

This frame is not ML-KEM implementation code, not production cryptography, not FIPS validation, not provider linking, not evidence that constant-time behavior exists, not evidence that side-channel resistance exists, not network behavior, not host mutation, and not runtime authority.
