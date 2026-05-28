# Latticra Q-Seal ML-KEM Source Digest Receipt

Status: implementation-source digest receipt fixture
Date: 2026-05-27
Scope: clean-room source, test, and build-script digest receipts before ML-KEM implementation promotion.

This fixture records the receipt shape required for future clean-room ML-KEM source artifacts. It does not create implementation files, hash live primitive source, accept source receipts, verify source receipts, approve reviewed digest receipts, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

The downstream source digest verification harness is recorded in `ML_KEM_SOURCE_DIGEST_VERIFICATION.md`; it remains fail-closed until source, test, and build receipts are available, replayed offline, tamper-checked, verified in CI, and reviewed.

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

## Required Receipt Rows

```text
source_unit_count=9
test_unit_count=9
build_script_unit_count=1
digest_algorithm=SHA-256
path_policy=repo-relative-normalized-no-generated-provider-or-apple-source
review_policy=dual-review-before-source-acceptance
ci_policy=receipt-replay-and-digest-verification-before-promotion
```

## Non-Claims

This fixture is not primitive code, not a hash of primitive code, not generated source, not third-party code intake, not a source acceptance receipt, not vector execution, not an ACVP submission, not FIPS validation evidence, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
