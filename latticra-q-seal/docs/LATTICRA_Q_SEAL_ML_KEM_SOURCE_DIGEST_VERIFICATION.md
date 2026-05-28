# Latticra Q-Seal ML-KEM Source Digest Verification

Status: fail-closed source digest replay harness fixture
Date: 2026-05-27
Scope: receipt replay and tamper fixture records before implementation promotion.

This slice records the offline verification harness that future clean-room ML-KEM source digest receipts must satisfy. It keeps source receipt replay, tamper fixture execution, verification result approval, implementation promotion, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled. The downstream replay result fixture is recorded in `LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_verification.h
latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_verification_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
```

## Current Fields

```text
ml_kem_source_digest_verification_present=1
formal_title=Latticra Q-Seal ML-KEM Source Digest Verification
verification_profile=latticra-q-seal-ml-kem-source-digest-verification/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
verification_scope=ML-KEM-source-digest-replay-harness-before-promotion
verification_state=source-digest-verification-harness-blocked
source_digest_verification_present=1
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
digest_algorithm_sha256_required=1
clean_room_source_boundary_recorded=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
receipt_schema_bound=1
normalized_path_policy_bound=1
replay_harness_template_recorded=1
tamper_fixture_template_recorded=1
offline_only_verification_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_files_created=0
source_receipts_available=0
test_receipts_available=0
build_receipts_available=0
source_digest_replay_executed=0
tamper_fixture_executed=0
ci_verification_harness_recorded=0
verification_result_reviewed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_verification_items_total=23
required_verification_items_satisfied=16
status=ml-kem-source-digest-verification-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
```

Expected output:

```text
latticra q-seal ml-kem source digest verification invariants: ok
latticra q-seal ml-kem source digest verification: ok
```
