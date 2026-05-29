# Latticra Q-Seal ML-KEM Vector Fixture Lock

Status: vector fixture lock
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md` for the Q-Seal documentation set. The fixture lock is a fail-closed ACVP/KAT bundle gate: it records the required offline evidence shape before any vector import, vector execution, ACVP submission, production cryptography claim, FIPS claim, or runtime authority grant. The downstream digest and coverage ledger is recorded in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_lock.h
latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_lock_invariants.c
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
```

## Current Fields

```text
ml_kem_vector_fixture_lock_present=1
formal_title=Latticra Q-Seal ML-KEM Vector Fixture Lock
lock_profile=latticra-q-seal-ml-kem-vector-fixture-lock/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
fixture_scope=ML-KEM-offline-vector-fixture-lock-before-import
fixture_state=fixture-lock-recorded-vector-bundle-not-loaded
vector_fixture_lock_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
kat_manifest_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
digest_algorithm_sha256_required=1
clean_room_source_boundary_recorded=1
offline_only_fixture_recorded=1
fixture_manifest_schema_recorded=1
fixture_hash_manifest_required=1
ml_kem_512_fixture_required=1
ml_kem_768_fixture_required=1
ml_kem_1024_fixture_required=1
keygen_fixture_family_required=1
encaps_fixture_family_required=1
decaps_fixture_family_required=1
malformed_fixture_family_required=1
implicit_rejection_fixture_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_source_digest_recorded=0
fixture_license_review_recorded=0
fixture_storage_path_recorded=0
fixture_schema_crosscheck_recorded=0
fixture_parameter_coverage_recorded=0
fixture_negative_case_coverage_recorded=0
fixture_import_reviewed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_fixture_lock_items_total=28
required_fixture_lock_items_satisfied=21
status=ml-kem-vector-fixture-lock-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
```

Expected output:

```text
latticra q-seal ml-kem vector fixture lock invariants: ok
latticra q-seal ml-kem vector fixture lock: ok
```
