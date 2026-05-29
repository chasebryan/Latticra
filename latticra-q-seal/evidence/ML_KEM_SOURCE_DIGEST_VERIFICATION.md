# Latticra Q-Seal ML-KEM Source Digest Verification

Status: source digest replay harness fixture
Date: 2026-05-27
Scope: offline source, test, and build receipt replay before ML-KEM implementation promotion.

This fixture records the no-effect verification harness shape for future clean-room ML-KEM source digest receipts. It does not create implementation files, read or hash primitive source, replay source receipts, execute tamper fixtures, approve verification results, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

The downstream receipt replay result fixture is recorded in `ML_KEM_RECEIPT_REPLAY_RESULTS.md`; it remains fail-closed until source, test, build, and tamper replay results are recorded and reviewed.

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

## Required Verification Fixtures

```text
source_receipts_available=required
test_receipts_available=required
build_receipts_available=required
source_digest_replay_executed=required
tamper_fixture_executed=required
ci_verification_harness_recorded=required
verification_result_reviewed=required
```

## Non-Claims

This fixture is not a source receipt replay, not a digest verification result, not primitive code, not generated source, not third-party code intake, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
