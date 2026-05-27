# Latticra Q-Seal ML-KEM Source Digest Manifest

Status: fail-closed implementation-source digest readiness slice
Date: 2026-05-27
Scope: source and test digest templates before ML-KEM implementation promotion.

This slice records the source-integrity evidence that future clean-room ML-KEM implementation files must satisfy before they can be promoted. It keeps implementation source creation, source digest acceptance, generated-source acceptance, third-party source intake, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_manifest.h
latticra-q-seal/src/q_seal_ml_kem_source_digest_manifest.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_manifest_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST.md
scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
```

## Current Fields

```text
ml_kem_source_digest_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Source Digest Manifest
digest_profile=latticra-q-seal-ml-kem-source-digest-manifest/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
digest_state=source-digest-template-blocked
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
digest_algorithm_sha256_recorded=1
clean_room_source_boundary_recorded=1
planned_source_units_count=9
planned_test_units_count=9
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
digest_template_recorded=1
hash_command_policy_recorded=1
third_party_source_denial_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_files_created=0
source_file_digests_recorded=0
test_file_digests_recorded=0
build_script_digests_recorded=0
reviewed_digest_receipt_recorded=0
reproducible_source_snapshot_recorded=0
digest_verification_ci_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_digest_items_total=20
required_digest_items_satisfied=14
blocked_reason=source-test-build-digests-reproducible-snapshot-ci-and-review-receipts-missing
status=ml-kem-source-digest-manifest-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
```

Expected output:

```text
latticra q-seal ml-kem source digest manifest invariants: ok
latticra q-seal ml-kem source digest manifest: ok
```
