# Latticra Q-Seal ML-KEM Vector Schema Evidence

Status: ACVP/KAT schema recorded; vector processing blocked
Date: 2026-05-27

This evidence record captures the ML-KEM test-vector shape Latticra Q-Seal must satisfy before any known-answer vector loading, ACVP response generation, provider differential execution, or runtime cryptography is allowed.

Vector source authority and digest acceptance are controlled by `latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md`; offline fixture locking is controlled by `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md`; fixture digest and coverage rows are controlled by `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`. This schema evidence does not accept, fetch, import, load, or process vector bundles.

Standards and validation sources:

- NIST FIPS 203 final publication for ML-KEM.
- NIST ACVP ML-KEM JSON draft for `ML-KEM / keyGen / FIPS203` and `ML-KEM / encapDecap / FIPS203`.

```text
ml_kem_vector_schema_present=1
schema_profile=latticra-q-seal-ml-kem-vector-schema/0.1
formal_title=Latticra Q-Seal ML-KEM Vector Schema
standards_source=NIST-FIPS-203
acvp_document=NIST-ACVP-ML-KEM-JSON
schema_state=schema-recorded-vectors-not-loaded
fips_203_source_verified=1
acvp_ml_kem_schema_tracked=1
algorithm_ml_kem_recorded=1
revision_fips203_recorded=1
keygen_mode_schema_recorded=1
encap_decap_mode_schema_recorded=1
parameter_sets_recorded=1
keygen_prompt_fields_recorded=1
keygen_response_fields_recorded=1
encap_decap_prompt_fields_recorded=1
encap_decap_response_fields_recorded=1
aft_test_type_recorded=1
val_test_type_recorded=1
key_check_functions_recorded=1
implicit_rejection_case_recorded=1
vector_source_url_recorded=0
vector_source_digest_recorded=0
vector_license_review_recorded=0
vector_bundle_loaded=0
vector_json_parser_implemented=0
response_generation_enabled=0
vector_execution_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_schema_items_total=18
required_schema_items_satisfied=15
status=ml-kem-vector-schema-blocked
```

## Prompt and Response Shape

The recorded prompt shape covers:

- keyGen AFT test groups with `tgId`, `testType`, `parameterSet`, and test cases carrying `tcId`, `d`, and `z`.
- encapDecap AFT and VAL test groups with `tgId`, `testType`, `parameterSet`, `function`, and test cases carrying `tcId` plus `ek`, `dk`, `m`, or `c` depending on function.
- parameter sets `ML-KEM-512`, `ML-KEM-768`, and `ML-KEM-1024`.

The recorded response shape covers:

- keyGen response test cases carrying `tcId`, `ek`, and `dk`.
- encapDecap response test cases carrying `tcId`, generated ciphertext `c`, shared secret `k`, or `testPassed` for key-check functions.

No vector bytes are embedded, loaded, interpreted, transformed, executed, or submitted by this evidence record.
