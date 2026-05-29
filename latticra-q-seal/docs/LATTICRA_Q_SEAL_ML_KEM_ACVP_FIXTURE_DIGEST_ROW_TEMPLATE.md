# Latticra Q-Seal ML-KEM ACVP Fixture Digest Row Template

Status: fixture digest row template
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md` for the Q-Seal documentation set. The template records the required offline row schema for future ML-KEM ACVP fixture digest rows before any row can be accepted by the vector fixture digest ledger. The upstream ACVP fixture row plan is recorded in `LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md`, and the downstream vector fixture digest ledger is recorded in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h
latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_digest_row_template_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
```

## Current Fields

```text
ml_kem_acvp_fixture_digest_row_template_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Fixture Digest Row Template
template_profile=latticra-q-seal-ml-kem-acvp-fixture-digest-row-template/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
template_scope=ML-KEM-ACVP-fixture-digest-row-schema-before-ledger-acceptance
template_state=digest-row-template-recorded-real-rows-missing
acvp_fixture_digest_row_template_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_fixture_row_plan_bound=1
vector_fixture_digest_ledger_bound=1
vector_source_intake_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
clean_room_source_boundary_recorded=1
row_id_column_required=1
parameter_set_column_required=1
mode_column_required=1
test_type_column_required=1
function_column_required=1
source_url_column_required=1
sha256_digest_column_required=1
bundle_size_column_required=1
storage_path_column_required=1
license_review_column_required=1
schema_crosscheck_column_required=1
reviewer_identity_column_required=1
review_timestamp_column_required=1
ci_replay_transcript_column_required=1
tamper_evidence_column_required=1
planned_fixture_digest_rows_required=15
planned_fixture_digest_rows_reserved=15
ml_kem_512_row_class_reserved=1
ml_kem_768_row_class_reserved=1
ml_kem_1024_row_class_reserved=1
keygen_row_class_reserved=1
encaps_row_class_reserved=1
decaps_row_class_reserved=1
val_row_class_reserved=1
key_check_row_class_reserved=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_digest_rows_recorded=0
source_url_rows_recorded=0
sha256_digest_rows_recorded=0
bundle_size_rows_recorded=0
storage_path_rows_recorded=0
license_review_rows_recorded=0
schema_crosscheck_rows_recorded=0
reviewer_identity_rows_recorded=0
review_timestamp_rows_recorded=0
ci_replay_transcript_rows_recorded=0
tamper_evidence_rows_recorded=0
digest_row_template_reviewed=0
fixture_digest_row_acceptance_allowed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_digest_row_template_items_total=45
required_digest_row_template_items_satisfied=33
status=ml-kem-acvp-fixture-digest-row-template-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
```

Expected output:

```text
latticra q-seal ml-kem acvp fixture digest row template invariants: ok
latticra q-seal ml-kem acvp fixture digest row template: ok
```
