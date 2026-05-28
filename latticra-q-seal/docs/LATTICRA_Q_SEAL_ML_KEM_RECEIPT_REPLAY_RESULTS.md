# Latticra Q-Seal ML-KEM Receipt Replay Results

Status: fail-closed receipt replay result fixture
Date: 2026-05-27
Scope: source, test, build, and tamper replay result records before implementation promotion.

This slice records the replay result fixture that future clean-room ML-KEM source digest receipts must satisfy after the source digest verification harness exists. It keeps replay execution, tamper fixture execution, replay result approval, implementation promotion, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_receipt_replay_results.h
latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
latticra-q-seal/tests/q_seal_ml_kem_receipt_replay_results_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
```

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

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
```

Expected output:

```text
latticra q-seal ml-kem receipt replay results invariants: ok
latticra q-seal ml-kem receipt replay results: ok
```
