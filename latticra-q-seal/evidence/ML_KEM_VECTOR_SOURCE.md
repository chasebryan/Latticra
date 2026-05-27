# Latticra Q-Seal ML-KEM Vector Source Intake Evidence

Status: source authority and digest policy recorded; vector bundle blocked
Date: 2026-05-27

This evidence record defines how Latticra Q-Seal will accept ML-KEM KAT/ACVP vector bundles later. It records the approved authority class, digest algorithm, freshness policy, and fail-closed blockers before any bundle URL, digest, license review, fetch, import, processing, or submission is allowed.

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

## Acceptance Rule

Q-Seal may not accept a vector bundle until the reviewed source URL, SHA-256 digest, bundle size, license review, hash verification, schema crosscheck, FIPS 203 errata binding, offline storage path, and import review are recorded. Even after bundle acceptance, runtime cryptography remains blocked until the broader Q-Seal readiness profile is satisfied.

No network fetch, vector import, vector processing, ACVP submission, ML-KEM operation, production cryptography claim, FIPS claim, or runtime authority is enabled by this evidence record.
