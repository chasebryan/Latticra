# Latticra Q-Seal ML-KEM Vector Source Intake

Status: source authority and digest policy recorded; vector bundle blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM vector source intake defines the source-control gate for future KAT/ACVP vector bundles. It records the authority class and digest policy Q-Seal will require before a vector bundle can be accepted into offline validation.

This slice does not fetch, import, parse, execute, or submit any vectors. It exists so future vector work cannot skip source provenance, digest verification, license review, errata binding, offline storage review, the downstream fixture-lock gate recorded in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md`, or the digest and coverage ledger recorded in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`.

## Source Fields

```text
ml_kem_vector_source_intake_present=1
source_profile=latticra-q-seal-ml-kem-vector-source/0.1
formal_title=Latticra Q-Seal ML-KEM Vector Source Intake
standards_source=NIST-FIPS-203
acvp_document=NIST-ACVP-ML-KEM-JSON
approved_source_authority=NIST-ACVP-or-reviewed-equivalent
digest_algorithm=SHA-256
source_state=authority-and-digest-policy-recorded-bundle-not-accepted
fips_203_source_verified=1
acvp_documentation_tracked=1
approved_source_authority_recorded=1
source_freshness_policy_recorded=1
digest_algorithm_recorded=1
bundle_source_url_recorded=0
bundle_digest_recorded=0
bundle_size_recorded=0
bundle_license_review_recorded=0
bundle_hash_verified=0
bundle_schema_crosscheck_recorded=0
errata_review_binding_recorded=0
offline_storage_path_recorded=0
bundle_import_review_recorded=0
bundle_fetch_performed=0
bundle_imported=0
network_fetch_enabled=0
vector_processing_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_source_items_total=14
required_source_items_satisfied=5
status=ml-kem-vector-source-intake-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_source.h
latticra-q-seal/src/q_seal_ml_kem_vector_source.c
latticra-q-seal/tests/q_seal_ml_kem_vector_source_invariants.c
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-vector-source.sh
```

## Runtime Blockers

Vector source acceptance remains blocked until:

- bundle source URL, SHA-256 digest, and size are recorded;
- bundle license review is recorded;
- bundle hash verification is recorded;
- bundle schema crosscheck is recorded against the Q-Seal vector schema;
- FIPS 203 errata review binding is recorded;
- offline storage path and import review are recorded;
- vector processing authority is granted by the Q-Seal readiness profile.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-source.sh
make latticra-q-seal-ml-kem-vector-source
```

Expected output:

```text
latticra q-seal ml-kem vector source invariants: ok
latticra q-seal ml-kem vector source: ok
```
