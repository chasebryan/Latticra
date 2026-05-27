# Latticra Q-Seal ML-KEM Vector Schema

Status: ACVP/KAT schema recorded; vector processing blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM vector schema records the test-vector shape required before Q-Seal can load known-answer vectors or participate in ACVP-style validation work.

This slice is intentionally schema-only. It records the fields Q-Seal must understand for ML-KEM key generation, encapsulation, decapsulation, key checks, AFT tests, VAL tests, parameter sets, and implicit rejection, but it does not parse JSON, load vector bundles, generate responses, submit ACVP sessions, execute vectors, or enable cryptography.

Vector-bundle authority, SHA-256 digest policy, freshness, license review, errata binding, offline storage, and import review are recorded separately in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md`.

## Schema Fields

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

## Runtime Blockers

Vector processing remains blocked until:

- vector source URL, source digest, and license review are recorded;
- an offline JSON parser exists and is reviewed;
- fixture canonicality, duplicate detection, malformed input handling, and response canonicality are tested;
- keyGen, encapsulation, decapsulation, encapsulation-key-check, decapsulation-key-check, and implicit-rejection cases are verified against reviewed vectors;
- ACVP response generation is reviewed but still kept offline until submission authority is explicitly granted;
- production cryptography, FIPS claims, and runtime authority remain denied until the broader Q-Seal readiness profile is satisfied.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_schema.h
latticra-q-seal/src/q_seal_ml_kem_vector_schema.c
latticra-q-seal/tests/q_seal_ml_kem_vector_schema_invariants.c
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
make latticra-q-seal-ml-kem-vector-schema
```

Expected output:

```text
latticra q-seal ml-kem vector schema invariants: ok
latticra q-seal ml-kem vector schema: ok
```
