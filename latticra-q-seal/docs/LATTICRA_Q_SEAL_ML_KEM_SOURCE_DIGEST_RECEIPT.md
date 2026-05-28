# Latticra Q-Seal ML-KEM Source Digest Receipt

Status: fail-closed source digest receipt fixture
Date: 2026-05-27
Scope: source, test, and build digest receipt rows before implementation promotion.

This slice records the receipt fixture that future clean-room ML-KEM implementation files must satisfy after the source digest manifest exists. It keeps implementation source creation, receipt acceptance, receipt verification, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled. The downstream replay harness is recorded in `LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_receipt.h
latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_receipt_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
```

## Current Fields

```text
ml_kem_source_digest_receipt_present=1
formal_title=Latticra Q-Seal ML-KEM Source Digest Receipt
receipt_profile=latticra-q-seal-ml-kem-source-digest-receipt/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
receipt_scope=ML-KEM-clean-room-source-digest-receipts-before-promotion
receipt_state=source-digest-receipt-fixture-blocked
source_digest_receipt_present=1
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
digest_algorithm_sha256_required=1
clean_room_source_boundary_recorded=1
source_digest_manifest_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
planned_source_receipts_count=9
planned_test_receipts_count=9
planned_build_receipts_count=1
receipt_schema_recorded=1
normalized_path_policy_recorded=1
hash_command_policy_recorded=1
reproducible_snapshot_policy_recorded=1
tamper_evidence_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_files_created=0
source_receipts_recorded=0
test_receipts_recorded=0
build_receipts_recorded=0
source_receipts_verified=0
reviewed_digest_receipt_recorded=0
receipt_replay_check_recorded=0
ci_digest_verification_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_receipt_items_total=23
required_receipt_items_satisfied=16
status=ml-kem-source-digest-receipt-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
```

Expected output:

```text
latticra q-seal ml-kem source digest receipt invariants: ok
latticra q-seal ml-kem source digest receipt: ok
```
