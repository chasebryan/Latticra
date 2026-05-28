# Latticra Q-Seal Foundation

Status: dedicated subsystem foundation for Latticra Q-Seal
Date: 2026-05-27
Scope: top-level Q-Seal directory, clean-room source boundary, no-effect C foundation API, invariant tests, and local validation before ML-KEM or ML-DSA implementation.

Latticra Q-Seal is the formal Latticra title for the project quantum-resistant cryptography subsystem. It is standards-first and clean-room by default.

This foundation does not implement encryption, key encapsulation, decapsulation, signatures, key generation, key storage, provider linking, production cryptography, FIPS validation, network behavior, host mutation, or runtime authority.

## Files

```text
latticra-q-seal/README.md
latticra-q-seal/evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/evidence/ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
latticra-q-seal/evidence/ML_KEM_ACVP_INTAKE.md
latticra-q-seal/evidence/ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/evidence/ML_KEM_CODE_OWNER_REVIEW.md
latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/evidence/ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
latticra-q-seal/evidence/ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/evidence/ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/evidence/ML_KEM_VALIDATION_CLAIM_GATE.md
latticra-q-seal/evidence/ML_KEM_MODULE_BOUNDARY_GATE.md
latticra-q-seal/evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
latticra-q-seal/include/latticra/q_seal.h
latticra-q-seal/include/latticra/q_seal_ml_kem.h
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_capability_matrix.h
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_fixture_row_plan.h
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_verdict_receipt_gate.h
latticra-q-seal/include/latticra/q_seal_ml_kem_acvp_intake.h
latticra-q-seal/include/latticra/q_seal_ml_kem_api_misuse_resistance.h
latticra-q-seal/include/latticra/q_seal_ml_kem_code_owner_review.h
latticra-q-seal/include/latticra/q_seal_ml_kem_ci_promotion_evidence.h
latticra-q-seal/include/latticra/q_seal_ml_kem_constant_time_review.h
latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_gate.h
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
latticra-q-seal/include/latticra/q_seal_ml_kem_implementation_frame.h
latticra-q-seal/include/latticra/q_seal_ml_kem_memory_safety_evidence.h
latticra-q-seal/include/latticra/q_seal_ml_kem_negative_test_evidence.h
latticra-q-seal/include/latticra/q_seal_ml_kem_provider_differential.h
latticra-q-seal/include/latticra/q_seal_ml_kem_randomness_source.h
latticra-q-seal/include/latticra/q_seal_ml_kem_receipt_replay_results.h
latticra-q-seal/include/latticra/q_seal_ml_kem_review_disposition_ledger.h
latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_identity_fixture.h
latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_role_mapping.h
latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
latticra-q-seal/include/latticra/q_seal_ml_kem_secret_state_contract.h
latticra-q-seal/include/latticra/q_seal_ml_kem_side_channel_review.h
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_manifest.h
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_receipt.h
latticra-q-seal/include/latticra/q_seal_ml_kem_source_digest_verification.h
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_schema.h
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_source.h
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_lock.h
latticra-q-seal/include/latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h
latticra-q-seal/include/latticra/q_seal_ml_kem_validation_claim_gate.h
latticra-q-seal/include/latticra/q_seal_ml_kem_module_boundary_gate.h
latticra-q-seal/include/latticra/q_seal_ml_kem_zeroization_evidence.h
latticra-q-seal/src/q_seal.c
latticra-q-seal/src/q_seal_ml_kem.c
latticra-q-seal/src/q_seal_ml_kem_acvp_capability_matrix.c
latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c
latticra-q-seal/src/q_seal_ml_kem_acvp_verdict_receipt_gate.c
latticra-q-seal/src/q_seal_ml_kem_acvp_intake.c
latticra-q-seal/src/q_seal_ml_kem_api_misuse_resistance.c
latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c
latticra-q-seal/src/q_seal_ml_kem_ci_promotion_evidence.c
latticra-q-seal/src/q_seal_ml_kem_constant_time_review.c
latticra-q-seal/src/q_seal_ml_kem_evidence_gate.c
latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c
latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c
latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
latticra-q-seal/src/q_seal_ml_kem_negative_test_evidence.c
latticra-q-seal/src/q_seal_ml_kem_provider_differential.c
latticra-q-seal/src/q_seal_ml_kem_randomness_source.c
latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c
latticra-q-seal/src/q_seal_ml_kem_review_disposition_ledger.c
latticra-q-seal/src/q_seal_ml_kem_reviewer_identity_fixture.c
latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c
latticra-q-seal/src/q_seal_ml_kem_side_channel_review.c
latticra-q-seal/src/q_seal_ml_kem_source_digest_manifest.c
latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c
latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c
latticra-q-seal/src/q_seal_ml_kem_vector_schema.c
latticra-q-seal/src/q_seal_ml_kem_vector_source.c
latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c
latticra-q-seal/src/q_seal_ml_kem_vector_fixture_digest_ledger.c
latticra-q-seal/src/q_seal_ml_kem_validation_claim_gate.c
latticra-q-seal/src/q_seal_ml_kem_module_boundary_gate.c
latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c
latticra-q-seal/tests/q_seal_foundation_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_parameters_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_capability_matrix_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_fixture_row_plan_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_verdict_receipt_gate_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_acvp_intake_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_api_misuse_resistance_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_code_owner_review_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_ci_promotion_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_constant_time_review_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_evidence_gate_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_implementation_frame_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_negative_test_evidence_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_provider_differential_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_randomness_source_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_receipt_replay_results_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_review_disposition_ledger_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_reviewer_identity_fixture_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_secret_state_contract_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_side_channel_review_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_manifest_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_receipt_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_source_digest_verification_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_vector_schema_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_vector_source_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_lock_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_vector_fixture_digest_ledger_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_validation_claim_gate_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_module_boundary_gate_invariants.c
latticra-q-seal/tests/q_seal_ml_kem_zeroization_evidence_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-foundation.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
scripts/test-latticra-q-seal-foundation.sh
scripts/test-latticra-q-seal-ml-kem-parameters.sh
scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
scripts/test-latticra-q-seal-ml-kem-vector-source.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
latticra-q-seal/docs/LATTICRA_Q_SEAL_FOUNDATION.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md
```

## Current Fields

```text
latticra_q_seal_present=1
formal_title=Latticra Q-Seal
subsystem_directory=latticra-q-seal
q_seal_profile=latticra-q-seal-foundation/0.1
clean_room_profile=latticra-clean-room-pqc/0.1
source_boundary=clean-room-no-apple-code
implementation_lane=standards-first-no-effect
nist_fips_203_ml_kem_tracked=1
nist_fips_204_ml_dsa_tracked=1
nist_fips_205_slh_dsa_backup_tracked=1
ml_kem_work_packet_next=1
ml_dsa_work_packet_planned=1
liboqs_comparison_provider_allowed=1
apple_corecrypto_reference_allowed=1
apple_corecrypto_code_copied=0
apple_corecrypto_proof_artifacts_copied=0
provider_linked=0
provider_runtime_used=0
key_generation_performed=0
key_storage_performed=0
encapsulation_performed=0
decapsulation_performed=0
signing_performed=0
verification_performed=0
encryption_performed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
post_quantum_migration_claim_allowed=0
runtime_authority_granted=0
foundation_state=prepared-clean-room-foundation
blocked_reason=crypto-operations-not-implemented
status=q-seal-foundation-prepared
```

## Engineering Direction

The first `Latticra Q-Seal ML-KEM` packet is now started in `LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md` with:

- FIPS 203 parameter constants as data only;
- known-answer test fixture requirements;
- explicit buffer-size and ownership rules;
- no provider linking by default;
- differential comparison planning against allowed providers;
- key generation, encapsulation, and decapsulation still disabled until the clean-room implementation and test-vector evidence are ready.

The evidence gate is now started in `LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md`, the offline ACVP intake shape is started in `LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md`, the ACVP capability matrix is started in `LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX.md`, the ACVP fixture row plan is started in `LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md`, the ACVP verdict receipt gate is started in `LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md`, the validation claim gate is started in `LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE.md`, the module-boundary gate is started in `LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_GATE.md`, the KAT/ACVP vector schema is started in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA.md`, the vector-source digest intake is started in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md`, the vector fixture lock is started in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md`, the vector fixture digest ledger is started in `LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md`, the negative-test evidence gate is started in `LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE.md`, the memory-safety evidence gate is started in `LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md`, the API misuse-resistance gate is started in `LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE.md`, the source digest manifest is started in `LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST.md`, the source digest receipt fixture is started in `LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md`, the source digest verification harness is started in `LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md`, the receipt replay result fixture is started in `LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md`, the code-owner review gate is started in `LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md`, the review disposition ledger is started in `LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER.md`, the reviewer identity fixture is started in `LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md`, the reviewer role-mapping fixture is started in `LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md`, the CI promotion evidence gate is started in `LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md`, the constant-time review gate is started in `LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW.md`, the randomness-source contract is started in `LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md`, the zeroization evidence gate is started in `LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md`, the side-channel review gate is started in `LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW.md`, the provider differential-test contract is started in `LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md`, the implementation-binding manifest is started in `LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md`, the clean-room implementation design frame is started in `LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md`, the secret-state contract is started in `LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md`, and candidate secret-operation helpers are started in `LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md`.

The next engineering packet should add reviewed fixture digest ledger rows, receipt replay transcripts, and imported reviewer role-map records before any ML-KEM operation implementation begins.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-foundation.sh
sh scripts/test-latticra-q-seal-foundation.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
```

Expected output:

```text
latticra q-seal foundation invariants: ok
latticra q-seal foundation: ok
latticra q-seal ml-kem parameters invariants: ok
latticra q-seal ml-kem parameters: ok
latticra q-seal ml-kem evidence gate invariants: ok
latticra q-seal ml-kem evidence gate: ok
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem acvp capability matrix invariants: ok
latticra q-seal ml-kem acvp capability matrix: ok
latticra q-seal ml-kem acvp fixture row plan invariants: ok
latticra q-seal ml-kem acvp fixture row plan: ok
latticra q-seal ml-kem acvp verdict receipt gate invariants: ok
latticra q-seal ml-kem acvp verdict receipt gate: ok
latticra q-seal ml-kem validation claim gate invariants: ok
latticra q-seal ml-kem validation claim gate: ok
latticra q-seal ml-kem module boundary gate invariants: ok
latticra q-seal ml-kem module boundary gate: ok
latticra q-seal ml-kem vector schema invariants: ok
latticra q-seal ml-kem vector schema: ok
latticra q-seal ml-kem vector source invariants: ok
latticra q-seal ml-kem vector source: ok
latticra q-seal ml-kem vector fixture lock invariants: ok
latticra q-seal ml-kem vector fixture lock: ok
latticra q-seal ml-kem vector fixture digest ledger invariants: ok
latticra q-seal ml-kem vector fixture digest ledger: ok
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
latticra q-seal ml-kem source digest manifest invariants: ok
latticra q-seal ml-kem source digest manifest: ok
latticra q-seal ml-kem source digest receipt invariants: ok
latticra q-seal ml-kem source digest receipt: ok
latticra q-seal ml-kem source digest verification invariants: ok
latticra q-seal ml-kem source digest verification: ok
latticra q-seal ml-kem receipt replay results invariants: ok
latticra q-seal ml-kem receipt replay results: ok
latticra q-seal ml-kem code owner review invariants: ok
latticra q-seal ml-kem code owner review: ok
latticra q-seal ml-kem review disposition ledger invariants: ok
latticra q-seal ml-kem review disposition ledger: ok
latticra q-seal ml-kem reviewer identity fixture invariants: ok
latticra q-seal ml-kem reviewer identity fixture: ok
latticra q-seal ml-kem reviewer role mapping invariants: ok
latticra q-seal ml-kem reviewer role mapping: ok
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
latticra q-seal ml-kem provider differential invariants: ok
latticra q-seal ml-kem provider differential: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
latticra q-seal ml-kem secret ops invariants: ok
latticra q-seal ml-kem secret ops: ok
```
