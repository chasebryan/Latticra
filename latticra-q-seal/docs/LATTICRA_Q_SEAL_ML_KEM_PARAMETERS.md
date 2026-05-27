# Latticra Q-Seal ML-KEM Parameters

Status: no-effect FIPS 203 parameter record for Latticra Q-Seal ML-KEM
Date: 2026-05-27
Source: NIST FIPS 203, Module-Lattice-Based Key-Encapsulation Mechanism Standard

This record starts the `Latticra Q-Seal ML-KEM` packet by encoding FIPS 203 parameter-set metadata and operation-disabled stubs. It does not implement ML-KEM key generation, encapsulation, decapsulation, shared-secret output, provider linking, production cryptography, FIPS validation, network behavior, host mutation, or runtime authority.

## Source

FIPS 203 was published by NIST on August 13, 2024. It specifies ML-KEM and the three approved parameter sets ML-KEM-512, ML-KEM-768, and ML-KEM-1024.

```text
source_url=https://csrc.nist.gov/pubs/fips/203/final
publication_url=https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.203.pdf
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem.h
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_intake.h
latticra-q-seal/include/latticra/q_seal_ml_kem_api_misuse_resistance.h
latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_gate.h
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_frame.h
latticra-q-seal/include/latticra/q_seal_ml_kem_memory_safety_evidence.h
latticra-q-seal/include/latticra/q_seal_ml_kem_negative_test_evidence.h
latticra-q-seal/include/latticra/q_seal_ml_kem_provider_differential.h
latticra-q-seal/include/latticra/q_seal_ml_kem_secret_state_contract.h
latticra-q-seal/include/latticra/q_seal_ml_kem_side_channel_review.h
latticra-q-seal/src/q_seal_ml_kem.c
latticra-q-seal/src/q_seal_ml_kem_acvp_intake.c
latticra-q-seal/src/q_seal_ml_kem_api_misuse_resistance.c
latticra-q-seal/src/q_seal_ml_kem_ci_promotion_evidence.c
latticra-q-seal/src/q_seal_ml_kem_evidence_gate.c
latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
latticra-q-seal/src/q_seal_ml_kem_negative_test_evidence.c
latticra-q-seal/src/q_seal_ml_kem_provider_differential.c
latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
latticra-q-seal/src/q_seal_ml_kem_side_channel_review.c
latticra-q-seal/tests/q_seal_ml_kem_parameters_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_intake_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_api_misuse_resistance_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_ci_promotion_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_evidence_gate_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_negative_test_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_provider_differential_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_side_channel_review_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
latticra-q-seal/evidence/ML_KEM_ACVP_INTAKE.md
latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
scripts/test-latticra-q-seal-ml-kem-parameters.sh
scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW.md
```

## Current Fields

```text
ml_kem_parameters_present=1
formal_title=Latticra Q-Seal ML-KEM
ml_kem_profile=latticra-q-seal-ml-kem/0.1
standards_source=NIST-FIPS-203
fips_203_parameter_set_tracked=1
known_answer_tests_required=1
acvp_vector_review_required=1
clean_room_required=1
apple_corecrypto_code_copied=0
provider_linked=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
key_generation_performed=0
encapsulation_performed=0
decapsulation_performed=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
operation_state=operations-disabled
blocked_reason=clean-room-implementation-not-present
```

## FIPS 203 Parameter Table

Columns:

```text
name n q k eta1 eta2 du dv rbg_strength_bits encapsulation_key_bytes decapsulation_key_bytes ciphertext_bytes shared_secret_key_bytes
```

Values:

```text
ML-KEM-512 256 3329 2 3 2 10 4 128 800 1632 768 32
ML-KEM-768 256 3329 3 2 2 10 4 192 1184 2400 1088 32
ML-KEM-1024 256 3329 4 2 2 11 5 256 1568 3168 1568 32
```

## Disabled Operations

The current C surface intentionally returns disabled status for:

```text
ML-KEM.KeyGen
ML-KEM.Encaps
ML-KEM.Decaps
```

Before any operation is enabled, Latticra Q-Seal requires:

```text
known_answer_test_vectors_recorded=1
acvp_vector_review_recorded=1
constant_time_review_recorded=1
side_channel_review_recorded=1
randomness_source_contract_recorded=1
intermediate_zeroization_contract_recorded=1
clean_room_implementation_review_recorded=1
provider_differential_test_contract_recorded=1
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

Expected output:

```text
latticra q-seal ml-kem parameters invariants: ok
latticra q-seal ml-kem parameters: ok
latticra q-seal ml-kem evidence gate invariants: ok
latticra q-seal ml-kem evidence gate: ok
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
latticra q-seal ml-kem provider differential invariants: ok
latticra q-seal ml-kem provider differential: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
```
