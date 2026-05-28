# Latticra Q-Seal ML-KEM Vector Fixture Lock

Status: vector fixture lock
Date: 2026-05-27
Scope: offline ACVP/KAT fixture lock before any ML-KEM vector bundle import, replay, or operation execution.

This fixture records the lock evidence that a future local ML-KEM ACVP/KAT bundle must satisfy before Latticra Q-Seal can load it. The downstream digest and coverage ledger is recorded in `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`. This fixture does not embed vectors, fetch vectors, import a bundle, execute vectors, generate responses, submit ACVP results, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

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

## Required Fixture Lock Rows

```text
fixture_source_digest=required
fixture_license_review=required
fixture_storage_path=required
fixture_schema_crosscheck=required
fixture_parameter_coverage=required
fixture_negative_case_coverage=required
fixture_import_review=required
```

## Non-Claims

This fixture is not a vector bundle, not an ACVP response, not a known-answer test transcript, not a provider comparison, not primitive code, not generated source, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
