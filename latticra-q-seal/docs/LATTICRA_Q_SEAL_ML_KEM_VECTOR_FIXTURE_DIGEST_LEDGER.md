# Latticra Q-Seal ML-KEM Vector Fixture Digest Ledger

Status: vector fixture digest ledger
Date: 2026-05-27

This document mirrors `latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md` for the Q-Seal documentation set. The digest ledger records the required offline source URL, digest, size, license, storage, schema, coverage, import-review, and review rows before any vector fixture can be loaded or executed. The upstream ACVP capability matrix is recorded in `LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX.md`, the upstream fixture row plan is recorded in `LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md`, and the row-level digest template is recorded in `LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h
latticra-q-seal/src/q_seal_ml_kem_vector_fixture_digest_ledger.c
latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_digest_ledger_invariants.c
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
```

## Current Fields

```text
ml_kem_vector_fixture_digest_ledger_present=1
formal_title=Latticra Q-Seal ML-KEM Vector Fixture Digest Ledger
ledger_profile=latticra-q-seal-ml-kem-vector-fixture-digest-ledger/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
ledger_scope=ML-KEM-offline-vector-fixture-digest-and-coverage-before-import
ledger_state=fixture-digest-ledger-recorded-records-not-imported
vector_fixture_digest_ledger_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_lock_bound=1
kat_manifest_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
digest_algorithm_sha256_required=1
clean_room_source_boundary_recorded=1
offline_only_digest_recorded=1
manifest_row_schema_recorded=1
canonical_path_policy_recorded=1
bundle_size_policy_recorded=1
parameter_coverage_policy_recorded=1
negative_case_coverage_policy_recorded=1
import_review_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_source_url_recorded=0
fixture_source_digest_recorded=0
fixture_bundle_size_recorded=0
fixture_license_review_recorded=0
fixture_storage_path_recorded=0
fixture_schema_crosscheck_recorded=0
ml_kem_512_coverage_recorded=0
ml_kem_768_coverage_recorded=0
ml_kem_1024_coverage_recorded=0
keygen_coverage_recorded=0
encaps_coverage_recorded=0
decaps_coverage_recorded=0
negative_case_coverage_recorded=0
fixture_import_reviewed=0
fixture_digest_ledger_reviewed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_fixture_digest_items_total=35
required_fixture_digest_items_satisfied=20
status=ml-kem-vector-fixture-digest-ledger-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
```

Expected output:

```text
latticra q-seal ml-kem vector fixture digest ledger invariants: ok
latticra q-seal ml-kem vector fixture digest ledger: ok
```
