# Latticra Q-Seal ML-KEM Negative-Test Evidence

Status: negative-test policy recorded; execution blocked
Date: 2026-05-27

This evidence record defines the malformed-input and negative-test gate for future Latticra Q-Seal ML-KEM implementation work. It records the FIPS 203 and ACVP-aligned test posture that must exist before Q-Seal may promote parser, validation, or decapsulation behavior.

No length-validation test is recorded, no invalid ciphertext test is recorded, no invalid key test is recorded, no implicit-rejection test is recorded, no fuzzing corpus is recorded, no negative tests are executed, no parser execution is allowed, no ML-KEM operation is enabled, no production cryptography claim is allowed, no FIPS claim is allowed, and no runtime authority is granted by this record.

```text
ml_kem_negative_test_evidence_present=1
evidence_profile=latticra-q-seal-ml-kem-negative-test-evidence/0.1
formal_title=Latticra Q-Seal ML-KEM Negative-Test Evidence
standards_source=NIST-FIPS-203
acvp_source=NIST-ACVP-ML-KEM
evidence_scope=ML-KEM-malformed-input-negative-vector-behavior
evidence_state=policy-recorded-test-execution-missing
fips_203_source_verified=1
acvp_ml_kem_schema_tracked=1
vector_schema_bound=1
vector_source_bound=1
malformed_ciphertext_tests_required=1
malformed_key_tests_required=1
negative_replay_tests_required=1
length_validation_tests_recorded=0
encoding_canonicality_tests_recorded=0
invalid_ciphertext_tests_recorded=0
invalid_public_key_tests_recorded=0
invalid_secret_key_tests_recorded=0
decapsulation_failure_tests_recorded=0
implicit_rejection_tests_recorded=0
parser_rejection_tests_recorded=0
fuzzing_corpus_recorded=0
differential_negative_tests_recorded=0
implementation_binding_recorded=0
negative_tests_executed=0
parser_execution_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_negative_test_items_total=18
required_negative_test_items_satisfied=7
status=ml-kem-negative-test-evidence-blocked
```

## Promotion Rule

Q-Seal may not promote ML-KEM parser, validation, or decapsulation behavior until length validation, encoding canonicality, invalid ciphertext, invalid public-key, invalid secret-key, decapsulation-failure, implicit-rejection, parser-rejection, fuzzing-corpus, differential negative-test, and implementation-binding evidence are recorded.

This record is a policy and evidence gate only; it is not a vector bundle, not a parser implementation, not a decapsulation implementation, not a negative-test result, not FIPS validation evidence, not an operation-enabling authority, and not a production cryptography claim.
