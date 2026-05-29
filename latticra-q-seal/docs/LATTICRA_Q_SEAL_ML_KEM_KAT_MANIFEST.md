# Latticra Q-Seal ML-KEM KAT Manifest

Status: fail-closed known-answer readiness contract

Scope: ML-KEM known-answer and ACVP test-class manifest before any vector execution, response submission, operation implementation, production cryptography claim, FIPS claim, or runtime authority.

This slice promotes the existing `ML_KEM_KAT_MANIFEST.md` evidence into a first-class Q-Seal component. It records the known-answer coverage required for ML-KEM-512, ML-KEM-768, and ML-KEM-1024 across the ACVP ML-KEM keyGen AFT, encapDecap AFT, decapsulation VAL, and key-check VAL paths. It does not embed vectors, load vectors, run vectors, generate keys, encapsulate, decapsulate, submit ACVP responses, claim FIPS validation, or grant runtime authority.

## Standards Anchors

```text
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
acvp_ml_kem_json_url=https://pages.nist.gov/ACVP/draft-celi-acvp-ml-kem.html
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_kat_manifest.h
latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c
latticra-q-seal/tests/q_seal_ml_kem_kat_manifest_invariants.c
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
```

## Current State

```text
manifest_profile=latticra-q-seal-ml-kem-kat-manifest/0.1
formal_title=Latticra Q-Seal ML-KEM KAT Manifest
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
kat_scope=ML-KEM-known-answer-manifest-before-vector-execution
manifest_state=kat-manifest-recorded-runner-and-vector-evidence-missing
ml_kem_kat_manifest_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
acvp_keygen_aft_required=1
acvp_encapdecap_aft_required=1
acvp_decapsulation_val_required=1
acvp_keycheck_val_required=1
ml_kem_512_coverage_required=1
ml_kem_768_coverage_required=1
ml_kem_1024_coverage_required=1
seed_material_handling_policy_recorded=1
positive_vector_family_required=1
negative_vector_family_required=1
malformed_vector_family_required=1
implicit_rejection_vector_required=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
no_embedded_vectors_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
kat_runner_implementation_present=0
vector_bundle_digest_recorded=0
vector_bundle_license_reviewed=0
vector_bundle_storage_reviewed=0
kat_parser_reviewed=0
positive_vectors_verified=0
negative_vectors_verified=0
malformed_vectors_verified=0
cross_provider_differential_recorded=0
ci_kat_replay_recorded=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
operation_implementation_present=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_manifest_items_total=40
required_kat_manifest_items_satisfied=26
status=ml-kem-kat-manifest-blocked
```

## Required Coverage

```text
ML-KEM-512 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
ML-KEM-768 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
ML-KEM-1024 -> keyGen AFT, encapDecap AFT, decapsulation VAL, key-check VAL, malformed-input negative cases, implicit rejection
```

## Promotion Blockers

```text
kat_runner_implementation_present=0
vector_bundle_digest_recorded=0
vector_bundle_license_reviewed=0
vector_bundle_storage_reviewed=0
kat_parser_reviewed=0
positive_vectors_verified=0
negative_vectors_verified=0
malformed_vectors_verified=0
cross_provider_differential_recorded=0
ci_kat_replay_recorded=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
operation_implementation_present=0
```

## Validation

```text
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
make latticra-q-seal-ml-kem-kat-manifest
```

Expected output:

```text
latticra q-seal ml-kem kat manifest invariants: ok
latticra q-seal ml-kem kat manifest: ok
```

## Non-Claims

This contract is not a vector bundle, not a vector parser implementation, not a known-answer runner, not an ML-KEM implementation, not ACVP validation, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
