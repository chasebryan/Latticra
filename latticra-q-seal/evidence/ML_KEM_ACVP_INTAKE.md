# Latticra Q-Seal ML-KEM ACVP Intake

Status: offline ACVP intake shape
Date: 2026-05-27
Scope: ACVP ML-KEM vector intake planning before vector loading, response generation, ACVP submission, or operation execution.

This record defines the offline intake shape for future NIST ACVP ML-KEM vectors. It does not download vectors, open an ACVP session, parse vector JSON, generate response JSON, execute ML-KEM, submit results, claim FIPS validation, claim production cryptography, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_acvp_intake_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Intake
intake_profile=latticra-q-seal-ml-kem-acvp-intake/0.1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm=ML-KEM
revision=FIPS203
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
status=ml-kem-acvp-intake-offline-blocked
```

## Required JSON Families

```text
ML-KEM keyGen FIPS203 ML-KEM-512
ML-KEM keyGen FIPS203 ML-KEM-768
ML-KEM keyGen FIPS203 ML-KEM-1024
ML-KEM encapDecap FIPS203 ML-KEM-512
ML-KEM encapDecap FIPS203 ML-KEM-768
ML-KEM encapDecap FIPS203 ML-KEM-1024
```

## Promotion Blockers

```text
vector_source_url_recorded=0
vector_bundle_digest_recorded=0
vector_license_review_recorded=0
vector_json_schema_reviewed=0
vector_json_loaded=0
response_json_generation_enabled=0
operation_execution_allowed=0
```

## Non-Claims

This intake record is not an ACVP client, not a vector parser, not an ACVP submission, not FIPS validation, not a cryptographic implementation, not provider linking, not production cryptography, not network behavior, not host mutation, and not runtime authority.
