# Latticra Q-Seal ML-KEM Negative-Test Evidence

Status: negative-test policy recorded; execution blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM negative-test evidence contract defines the malformed-input and negative-vector gate for future clean-room ML-KEM parser, validation, and decapsulation behavior. It records required evidence for length validation, canonical encoding, invalid ciphertexts, invalid keys, decapsulation failure, implicit rejection, parser rejection, fuzzing corpus, differential negative tests, and implementation binding.

This slice does not implement parsing, load vectors, execute negative tests, run fuzzing, promote implementation code, execute ML-KEM operations, or allow production cryptography claims.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
acvp_ml_kem_schema_url=https://pages.nist.gov/ACVP/draft-celi-acvp-ml-kem.html
```

## Evidence Fields

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

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_negative_test_evidence.h
latticra-q-seal/src/q_seal_ml_kem_negative_test_evidence.c
latticra-q-seal/tests/q_seal_ml_kem_negative_test_evidence_invariants.c
latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
```

## Runtime Blockers

Implementation promotion remains blocked until:

- length-validation and canonical-encoding tests are recorded;
- invalid ciphertext, public-key, and secret-key tests are recorded;
- decapsulation-failure and implicit-rejection tests are recorded;
- parser-rejection tests are recorded;
- fuzzing corpus and differential negative-test evidence are recorded;
- implementation binding is recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
make latticra-q-seal-ml-kem-negative-test-evidence
```

Expected output:

```text
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
```
