# Latticra Q-Seal ML-KEM Receipt Replay Results

Status: receipt replay result fixture
Date: 2026-05-27
Scope: offline source, test, build, and tamper replay result records before ML-KEM implementation promotion.

This fixture records the result evidence shape for future clean-room ML-KEM source digest receipt replay. It does not create implementation files, replay receipts, execute tamper fixtures, approve replay results, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_receipt_replay_results_present=1
formal_title=Latticra Q-Seal ML-KEM Receipt Replay Results
replay_profile=latticra-q-seal-ml-kem-receipt-replay-results/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
replay_scope=ML-KEM-source-digest-replay-results-before-promotion
replay_state=receipt-replay-results-fixture-blocked
receipt_replay_results_present=1
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
digest_algorithm_sha256_required=1
clean_room_source_boundary_recorded=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
source_receipt_result_schema_recorded=1
test_receipt_result_schema_recorded=1
build_receipt_result_schema_recorded=1
replay_command_template_recorded=1
tamper_result_template_recorded=1
ci_result_binding_recorded=1
offline_only_replay_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_files_created=0
source_replay_results_recorded=0
test_replay_results_recorded=0
build_replay_results_recorded=0
tamper_replay_results_recorded=0
replay_result_reviewed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_replay_items_total=24
required_replay_items_satisfied=19
status=ml-kem-receipt-replay-results-blocked
```

## Required Replay Result Rows

```text
source_replay_results=required
test_replay_results=required
build_replay_results=required
tamper_replay_results=required
replay_result_review=required
```

## Non-Claims

This fixture is not a replay transcript, not digest verification success, not primitive code, not generated source, not third-party code intake, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.
