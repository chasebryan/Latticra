# Latticra Q-Seal ML-KEM ACVP Intake

Status: offline ACVP intake readiness slice
Date: 2026-05-27
Scope: ACVP ML-KEM schema tracking, vector intake blockers, and no-network validation before ML-KEM operation implementation.

This slice adds an offline ACVP intake contract for Latticra Q-Seal ML-KEM. It records that the NIST ACVP ML-KEM JSON schema is tracked for `ML-KEM / keyGen / FIPS203` and `ML-KEM / encapDecap / FIPS203`, while keeping vector loading, response generation, ACVP submission, network sessions, operation execution, production crypto claims, FIPS claims, and runtime authority disabled.

The schema-only field contract for those ACVP/KAT vectors is recorded separately in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA.md`. The source authority and digest intake contract for future vector bundles is recorded separately in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md`.

## Source Posture

```text
acvp_documentation_url=https://pages.nist.gov/ACVP/
ml_kem_acvp_json_url=https://pages.nist.gov/ACVP/draft-celi-acvp-ml-kem.html
algorithm=ML-KEM
revision=FIPS203
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_intake.h
latticra-q-seal/src/q_seal_ml_kem_acvp_intake.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_intake_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
latticra-q-seal/evidence/ML_KEM_ACVP_INTAKE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md
scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
scripts/test-latticra-q-seal-ml-kem-vector-source.sh
scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
```

## Current Fields

```text
ml_kem_acvp_intake_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Intake
intake_profile=latticra-q-seal-ml-kem-acvp-intake/0.1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm=ML-KEM
revision=FIPS203
acvp_document_tracked=1
acvp_ml_kem_schema_tracked=1
algorithm_ml_kem_required=1
revision_fips203_required=1
keygen_mode_required=1
encap_decap_mode_required=1
ml_kem_512_required=1
ml_kem_768_required=1
ml_kem_1024_required=1
vector_source_url_recorded=0
vector_bundle_digest_recorded=0
vector_license_review_recorded=0
vector_json_schema_reviewed=0
vector_json_loaded=0
response_json_generation_enabled=0
offline_fixture_only=1
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_intake_items_total=13
required_intake_items_satisfied=9
blocked_reason=vector-source-digest-license-schema-review-and-loader-not-recorded
status=ml-kem-acvp-intake-offline-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-source.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem vector schema invariants: ok
latticra q-seal ml-kem vector schema: ok
latticra q-seal ml-kem vector source invariants: ok
latticra q-seal ml-kem vector source: ok
```
