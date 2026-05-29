# Latticra Q-Seal

Status: clean-room quantum-resistant cryptography subsystem foundation
Date: 2026-05-27

Latticra Q-Seal is the formal Latticra subsystem for clean-room, standards-first post-quantum cryptography work.

This directory is the dedicated home for Q-Seal source, headers, tests, docs, and local validation. The foundation and readiness gates still block production cryptography, FIPS validation claims, key storage, secret emission, network behavior, host mutation, and runtime authority. A local OpenSSL EVP provider self-test now exercises ML-KEM key generation, encapsulation, decapsulation, shared-secret comparison, and zeroization without promoting runtime authority.

## Directory Layout

```text
latticra-q-seal/
  README.md
  evidence/Q_SEAL_READINESS.md
  evidence/ML_KEM_ACVP_CAPABILITY_MATRIX.md
  evidence/ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
  evidence/ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
  evidence/ML_KEM_ACVP_PARSER_CONTRACT.md
  evidence/ML_KEM_ACVP_RESPONSE_CONTRACT.md
  evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
  evidence/ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT.md
  evidence/ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
  evidence/ML_KEM_VALIDATION_CLAIM_GATE.md
  evidence/ML_KEM_MODULE_BOUNDARY_GATE.md
  evidence/ML_KEM_SECURITY_POLICY_GATE.md
  evidence/ML_KEM_ACVP_INTAKE.md
  evidence/ML_KEM_API_MISUSE_RESISTANCE.md
  evidence/ML_KEM_CODE_OWNER_REVIEW.md
  evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
  evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
  evidence/ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
  evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
  evidence/ML_KEM_PER_FILE_TEST_TRACE_GATE.md
  evidence/ML_KEM_FIPS_CONFORMANCE_MATRIX.md
  evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
  evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
  evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
  evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
  evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
  evidence/ML_KEM_IMPLEMENTATION_FRAME.md
  evidence/ML_KEM_KAT_MANIFEST.md
  evidence/ML_KEM_KAT_RUNNER_CONTRACT.md
  evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
  evidence/ML_KEM_KAT_RESULT_SCHEMA.md
  evidence/ML_KEM_KAT_RESULT_ROW_FIXTURE.md
  evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
  evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
  evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
  evidence/ML_KEM_PROVIDER_SELF_TEST.md
  evidence/ML_KEM_RANDOMNESS_SOURCE.md
  evidence/ML_KEM_RECEIPT_REPLAY_RESULTS.md
  evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
  evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
  evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
  evidence/ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
  evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
  evidence/ML_KEM_SECRET_OPS.md
  evidence/ML_KEM_SECRET_STATE_CONTRACT.md
  evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
  evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
  evidence/ML_KEM_SOURCE_DIGEST_RECEIPT.md
  evidence/ML_KEM_SOURCE_DIGEST_VERIFICATION.md
  evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
  evidence/ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
  evidence/ML_KEM_VECTOR_FIXTURE_LOCK.md
  evidence/ML_KEM_VECTOR_SCHEMA.md
  evidence/ML_KEM_VECTOR_SOURCE.md
  evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
  include/latticra/q_seal.h
  include/latticra/q_seal_readiness.h
  include/latticra/q_seal_ml_kem.h
  include/latticra/q_seal_ml_kem_acvp_capability_matrix.h
  include/latticra/q_seal_ml_kem_acvp_fixture_row_plan.h
  include/latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h
  include/latticra/q_seal_ml_kem_acvp_parser_contract.h
  include/latticra/q_seal_ml_kem_acvp_response_contract.h
  include/latticra/q_seal_ml_kem_acvp_response_fixture.h
  include/latticra/q_seal_ml_kem_acvp_submission_package_contract.h
  include/latticra/q_seal_ml_kem_acvp_verdict_receipt_gate.h
  include/latticra/q_seal_ml_kem_validation_claim_gate.h
  include/latticra/q_seal_ml_kem_module_boundary_gate.h
  include/latticra/q_seal_ml_kem_security_policy_gate.h
  include/latticra/q_seal_ml_kem_acvp_intake.h
  include/latticra/q_seal_ml_kem_api_misuse_resistance.h
  include/latticra/q_seal_ml_kem_code_owner_review.h
  include/latticra/q_seal_ml_kem_ci_promotion_evidence.h
  include/latticra/q_seal_ml_kem_constant_time_review.h
  include/latticra/q_seal_ml_kem_clean_room_author_attestation_gate.h
  include/latticra/q_seal_ml_kem_evidence_gate.h
  include/latticra/q_seal_ml_kem_fips_conformance_matrix.h
  include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
  include/latticra/q_seal_ml_kem_source_layout_gate.h
  include/latticra/q_seal_ml_kem_implementation_file_digest_plan.h
  include/latticra/q_seal_ml_kem_implementation_traceability_matrix.h
  include/latticra/q_seal_ml_kem_primitive_source_acceptance_gate.h
  include/latticra/q_seal_ml_kem_implementation_frame.h
  include/latticra/q_seal_ml_kem_kat_manifest.h
  include/latticra/q_seal_ml_kem_kat_runner_contract.h
  include/latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h
  include/latticra/q_seal_ml_kem_kat_result_schema.h
  include/latticra/q_seal_ml_kem_kat_result_row_fixture.h
  include/latticra/q_seal_ml_kem_memory_safety_evidence.h
  include/latticra/q_seal_ml_kem_negative_test_evidence.h
  include/latticra/q_seal_ml_kem_per_file_standards_trace_gate.h
  include/latticra/q_seal_ml_kem_per_file_test_trace_gate.h
  include/latticra/q_seal_ml_kem_provider_differential.h
  include/latticra/q_seal_ml_kem_provider_self_test.h
  include/latticra/q_seal_ml_kem_randomness_source.h
  include/latticra/q_seal_ml_kem_receipt_replay_results.h
  include/latticra/q_seal_ml_kem_review_disposition_ledger.h
  include/latticra/q_seal_ml_kem_reviewer_identity_fixture.h
  include/latticra/q_seal_ml_kem_reviewer_role_mapping.h
  include/latticra/q_seal_ml_kem_evidence_import_packet_manifest.h
  include/latticra/q_seal_ml_kem_evidence_import_review_gate.h
  include/latticra/q_seal_ml_kem_secret_ops.h
  include/latticra/q_seal_ml_kem_secret_state_contract.h
  include/latticra/q_seal_ml_kem_side_channel_review.h
  include/latticra/q_seal_ml_kem_source_digest_manifest.h
  include/latticra/q_seal_ml_kem_source_digest_receipt.h
  include/latticra/q_seal_ml_kem_source_digest_verification.h
  include/latticra/q_seal_ml_kem_sp800_227_usage_profile.h
  include/latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h
  include/latticra/q_seal_ml_kem_vector_fixture_lock.h
  include/latticra/q_seal_ml_kem_vector_schema.h
  include/latticra/q_seal_ml_kem_vector_source.h
  include/latticra/q_seal_ml_kem_zeroization_evidence.h
  src/q_seal.c
  src/q_seal_readiness.c
  src/q_seal_ml_kem.c
  src/q_seal_ml_kem_acvp_capability_matrix.c
  src/q_seal_ml_kem_acvp_fixture_row_plan.c
  src/q_seal_ml_kem_acvp_fixture_digest_row_template.c
  src/q_seal_ml_kem_acvp_parser_contract.c
  src/q_seal_ml_kem_acvp_response_contract.c
  src/q_seal_ml_kem_acvp_response_fixture.c
  src/q_seal_ml_kem_acvp_submission_package_contract.c
  src/q_seal_ml_kem_acvp_verdict_receipt_gate.c
  src/q_seal_ml_kem_validation_claim_gate.c
  src/q_seal_ml_kem_module_boundary_gate.c
  src/q_seal_ml_kem_security_policy_gate.c
  src/q_seal_ml_kem_acvp_intake.c
  src/q_seal_ml_kem_api_misuse_resistance.c
  src/q_seal_ml_kem_code_owner_review.c
  src/q_seal_ml_kem_ci_promotion_evidence.c
  src/q_seal_ml_kem_constant_time_review.c
  src/q_seal_ml_kem_clean_room_author_attestation_gate.c
  src/q_seal_ml_kem_evidence_gate.c
  src/q_seal_ml_kem_fips_conformance_matrix.c
  src/q_seal_ml_kem_implementation_binding_manifest.c
  src/q_seal_ml_kem_source_layout_gate.c
  src/q_seal_ml_kem_implementation_file_digest_plan.c
  src/q_seal_ml_kem_implementation_traceability_matrix.c
  src/q_seal_ml_kem_primitive_source_acceptance_gate.c
  src/q_seal_ml_kem_implementation_frame.c
  src/q_seal_ml_kem_kat_manifest.c
  src/q_seal_ml_kem_kat_runner_contract.c
  src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
  src/q_seal_ml_kem_kat_result_schema.c
  src/q_seal_ml_kem_kat_result_row_fixture.c
  src/q_seal_ml_kem_memory_safety_evidence.c
  src/q_seal_ml_kem_negative_test_evidence.c
  src/q_seal_ml_kem_per_file_standards_trace_gate.c
  src/q_seal_ml_kem_per_file_test_trace_gate.c
  src/q_seal_ml_kem_provider_differential.c
  src/q_seal_ml_kem_provider_self_test.c
  src/q_seal_ml_kem_randomness_source.c
  src/q_seal_ml_kem_receipt_replay_results.c
  src/q_seal_ml_kem_review_disposition_ledger.c
  src/q_seal_ml_kem_reviewer_identity_fixture.c
  src/q_seal_ml_kem_reviewer_role_mapping.c
  src/q_seal_ml_kem_evidence_import_packet_manifest.c
  src/q_seal_ml_kem_evidence_import_review_gate.c
  src/q_seal_ml_kem_secret_ops.c
  src/q_seal_ml_kem_secret_state_contract.c
  src/q_seal_ml_kem_side_channel_review.c
  src/q_seal_ml_kem_source_digest_manifest.c
  src/q_seal_ml_kem_source_digest_receipt.c
  src/q_seal_ml_kem_source_digest_verification.c
  src/q_seal_ml_kem_sp800_227_usage_profile.c
  src/q_seal_ml_kem_vector_fixture_digest_ledger.c
  src/q_seal_ml_kem_vector_fixture_lock.c
  src/q_seal_ml_kem_vector_schema.c
  src/q_seal_ml_kem_vector_source.c
  src/q_seal_ml_kem_zeroization_evidence.c
  tests/q_seal_foundation_invariants.c
  tests/q_seal_readiness_invariants.c
  tests/q_seal_ml_kem_parameters_invariants.c
  tests/q_seal_ml_kem_acvp_capability_matrix_invariants.c
  tests/q_seal_ml_kem_acvp_fixture_row_plan_invariants.c
  tests/q_seal_ml_kem_acvp_fixture_digest_row_template_invariants.c
  tests/q_seal_ml_kem_acvp_parser_contract_invariants.c
  tests/q_seal_ml_kem_acvp_response_contract_invariants.c
  tests/q_seal_ml_kem_acvp_response_fixture_invariants.c
  tests/q_seal_ml_kem_acvp_submission_package_contract_invariants.c
  tests/q_seal_ml_kem_acvp_verdict_receipt_gate_invariants.c
  tests/q_seal_ml_kem_validation_claim_gate_invariants.c
  tests/q_seal_ml_kem_module_boundary_gate_invariants.c
  tests/q_seal_ml_kem_security_policy_gate_invariants.c
  tests/q_seal_ml_kem_acvp_intake_invariants.c
  tests/q_seal_ml_kem_api_misuse_resistance_invariants.c
  tests/q_seal_ml_kem_code_owner_review_invariants.c
  tests/q_seal_ml_kem_ci_promotion_evidence_invariants.c
  tests/q_seal_ml_kem_constant_time_review_invariants.c
  tests/q_seal_ml_kem_clean_room_author_attestation_gate_invariants.c
  tests/q_seal_ml_kem_evidence_gate_invariants.c
  tests/q_seal_ml_kem_fips_conformance_matrix_invariants.c
  tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
  tests/q_seal_ml_kem_source_layout_gate_invariants.c
  tests/q_seal_ml_kem_implementation_file_digest_plan_invariants.c
  tests/q_seal_ml_kem_implementation_traceability_matrix_invariants.c
  tests/q_seal_ml_kem_primitive_source_acceptance_gate_invariants.c
  tests/q_seal_ml_kem_implementation_frame_invariants.c
  tests/q_seal_ml_kem_kat_manifest_invariants.c
  tests/q_seal_ml_kem_kat_runner_contract_invariants.c
  tests/q_seal_ml_kem_kat_acvp_replay_transcript_gate_invariants.c
  tests/q_seal_ml_kem_kat_result_schema_invariants.c
  tests/q_seal_ml_kem_kat_result_row_fixture_invariants.c
  tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
  tests/q_seal_ml_kem_negative_test_evidence_invariants.c
  tests/q_seal_ml_kem_per_file_standards_trace_gate_invariants.c
  tests/q_seal_ml_kem_per_file_test_trace_gate_invariants.c
  tests/q_seal_ml_kem_provider_differential_invariants.c
  tests/q_seal_ml_kem_provider_self_test_invariants.c
  tests/q_seal_ml_kem_randomness_source_invariants.c
  tests/q_seal_ml_kem_receipt_replay_results_invariants.c
  tests/q_seal_ml_kem_review_disposition_ledger_invariants.c
  tests/q_seal_ml_kem_reviewer_identity_fixture_invariants.c
  tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c
  tests/q_seal_ml_kem_evidence_import_packet_manifest_invariants.c
  tests/q_seal_ml_kem_evidence_import_review_gate_invariants.c
  tests/q_seal_ml_kem_secret_ops_invariants.c
  tests/q_seal_ml_kem_secret_state_contract_invariants.c
  tests/q_seal_ml_kem_side_channel_review_invariants.c
  tests/q_seal_ml_kem_source_digest_manifest_invariants.c
  tests/q_seal_ml_kem_source_digest_receipt_invariants.c
  tests/q_seal_ml_kem_source_digest_verification_invariants.c
  tests/q_seal_ml_kem_sp800_227_usage_profile_invariants.c
  tests/q_seal_ml_kem_vector_fixture_digest_ledger_invariants.c
  tests/q_seal_ml_kem_vector_fixture_lock_invariants.c
  tests/q_seal_ml_kem_vector_schema_invariants.c
  tests/q_seal_ml_kem_vector_source_invariants.c
  tests/q_seal_ml_kem_zeroization_evidence_invariants.c
  scripts/test-latticra-q-seal-foundation.sh
  scripts/test-latticra-q-seal-readiness.sh
  scripts/test-latticra-q-seal-ml-kem-parameters.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
  scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
  scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
  scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
  scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
  scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
  scripts/test-latticra-q-seal-ml-kem-per-file-test-trace-gate.sh
  scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
  scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
  scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
  scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
  scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh
  scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
  scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
  scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
  scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
  scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
  scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
  scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
  scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
  scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
  scripts/test-latticra-q-seal-ml-kem-receipt-replay-results.sh
  scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
  scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
  scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
  scripts/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
  scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
  scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
  scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
  scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-source-digest-receipt.sh
  scripts/test-latticra-q-seal-ml-kem-source-digest-verification.sh
  scripts/test-latticra-q-seal-ml-kem-vector-fixture-digest-ledger.sh
  scripts/test-latticra-q-seal-ml-kem-vector-fixture-lock.sh
  scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
  scripts/test-latticra-q-seal-ml-kem-vector-source.sh
  scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
  docs/LATTICRA_Q_SEAL_FOUNDATION.md
  docs/LATTICRA_Q_SEAL_READINESS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PER_FILE_TEST_TRACE_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_MATRIX.md
  docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
  docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
  docs/LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA.md
  docs/LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER.md
  docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
  docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md
```

## Foundation Fields

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
provider_linked=0
key_generation_performed=0
encapsulation_performed=0
decapsulation_performed=0
signing_performed=0
verification_performed=0
encryption_performed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
```

## ML-KEM Evidence Gate

```text
ml_kem_evidence_gate_present=1
standards_source=NIST-FIPS-203
standards_errata_state=errata-review-required
parameter_sets_recorded=1
known_answer_test_manifest_present=1
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
constant_time_review_recorded=0
side_channel_review_recorded=0
required_evidence_items_total=16
required_evidence_items_satisfied=3
operations_enabled=0
production_crypto_claim_allowed=0
status=ml-kem-evidence-gate-fail-closed
```

## ML-KEM FIPS 203 Conformance Matrix

```text
fips_conformance_matrix_present=1
formal_title=Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix
conformance_profile=latticra-q-seal-ml-kem-fips-conformance-matrix/0.1
standards_basis=NIST-FIPS-203
parameter_sets_bound=1
keygen_algorithm_bound=1
encaps_algorithm_bound=1
decaps_algorithm_bound=1
byte_encoding_requirements_bound=1
decapsulation_failure_semantics_bound=1
errata_review_recorded=0
implementation_trace_accepted=0
conformance_matrix_accepted=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
required_conformance_items_total=28
required_conformance_items_satisfied=18
status=ml-kem-fips-conformance-matrix-blocked
```

## ML-KEM SP 800-227 Usage Profile

```text
sp800_227_usage_profile_present=1
formal_title=Latticra Q-Seal ML-KEM SP 800-227 Usage Profile
usage_profile=latticra-q-seal-ml-kem-sp800-227-usage-profile/0.1
standards_basis=NIST-SP-800-227
approved_kem_algorithm_required=1
fips_203_ml_kem_bound=1
application_protocol_binding_required=1
key_confirmation_decision_required=1
kdf_boundary_required=1
domain_separation_required=1
shared_secret_lifecycle_required=1
failure_handling_required=1
kem_use_case_review_recorded=1
application_protocol_binding_recorded=1
key_confirmation_decision_recorded=1
kdf_binding_recorded=1
domain_separation_reviewed=1
shared_secret_lifecycle_reviewed=1
failure_handling_reviewed=1
key_separation_reviewed=1
algorithm_agility_reviewed=1
kem_usage_profile_accepted=1
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
required_usage_items_total=30
required_usage_items_satisfied=30
status=ml-kem-sp800-227-usage-profile-accepted-runtime-closed
```

## ML-KEM Implementation Traceability Matrix

```text
implementation_traceability_matrix_present=1
formal_title=Latticra Q-Seal ML-KEM Implementation Traceability Matrix
traceability_profile=latticra-q-seal-ml-kem-implementation-traceability-matrix/0.1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM
planned_source_units_count=9
planned_test_units_count=9
planned_source_unit_matrix_recorded=1
polynomial_arithmetic_unit_bound=1
ntt_unit_bound=1
sampling_unit_bound=1
compression_unit_bound=1
encoding_unit_bound=1
hash_xof_unit_bound=1
keygen_unit_bound=1
encaps_unit_bound=1
decaps_unit_bound=1
fips_203_section_mapping_recorded=1
sp800_227_usage_mapping_recorded=1
kat_vector_family_mapping_recorded=1
acvp_test_type_mapping_recorded=1
constant_time_review_mapping_recorded=0
memory_safety_mapping_recorded=0
source_digest_mapping_recorded=0
implementation_trace_accepted=0
implementation_code_present=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
required_traceability_items_total=30
required_traceability_items_satisfied=20
status=ml-kem-traceability-matrix-blocked
```

## ML-KEM Primitive Source Acceptance Gate

```text
primitive_source_acceptance_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Primitive Source Acceptance Gate
acceptance_profile=latticra-q-seal-ml-kem-primitive-source-acceptance-gate/0.1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM
source_layout_bound=1
source_layout_gate_bound=1
implementation_traceability_matrix_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
kat_manifest_bound=1
acvp_contracts_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
receipt_replay_results_bound=1
constant_time_review_bound=1
memory_safety_evidence_bound=1
zeroization_evidence_bound=1
randomness_source_bound=1
negative_test_evidence_bound=1
source_files_created=0
implementation_code_present=0
source_file_digest_rows_recorded=0
clean_room_author_attestation_recorded=0
source_acceptance_approved=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
required_acceptance_items_total=38
required_acceptance_items_satisfied=30
status=ml-kem-source-acceptance-gate-blocked
```

## ML-KEM KAT Manifest

```text
ml_kem_kat_manifest_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
kat_scope=ML-KEM-known-answer-manifest-before-vector-execution
acvp_keygen_aft_required=1
acvp_encapdecap_aft_required=1
acvp_decapsulation_val_required=1
acvp_keycheck_val_required=1
ml_kem_512_coverage_required=1
ml_kem_768_coverage_required=1
ml_kem_1024_coverage_required=1
seed_material_handling_policy_recorded=1
positive_vector_family_required=1
negative_vector_family_required=1
malformed_vector_family_required=1
implicit_rejection_vector_required=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
kat_result_schema_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
no_embedded_vectors_policy_recorded=1
kat_runner_implementation_present=0
known_answer_vectors_loaded=0
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
operation_implementation_present=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_manifest_items_total=40
required_kat_manifest_items_satisfied=26
status=ml-kem-kat-manifest-blocked
```

## ML-KEM KAT Runner Contract

```text
ml_kem_kat_runner_contract_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
runner_scope=ML-KEM-known-answer-runner-contract-before-vector-replay
kat_manifest_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
replay_transcript_gate_bound=1
deterministic_replay_policy_recorded=1
offline_fixture_policy_recorded=1
no_network_execution_required=1
no_dynamic_provider_loading_required=1
positive_result_row_policy_recorded=1
negative_result_row_policy_recorded=1
malformed_result_row_policy_recorded=1
implicit_rejection_result_policy_recorded=1
no_embedded_vectors_policy_recorded=1
kat_runner_implementation_present=0
fixture_bundle_loaded=0
fixture_bundle_digest_verified=0
result_schema_reviewed=0
positive_result_rows_recorded=0
negative_result_rows_recorded=0
malformed_result_rows_recorded=0
implicit_rejection_rows_recorded=0
provider_differential_rows_recorded=0
ci_kat_replay_transcript_recorded=0
kat_execution_enabled=0
acvp_response_generation_enabled=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_runner_contract_items_total=47
required_kat_runner_contract_items_satisfied=31
status=ml-kem-kat-runner-contract-blocked
```

## ML-KEM KAT/ACVP Replay Transcript Gate

```text
ml_kem_kat_acvp_replay_transcript_gate_present=1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
transcript_scope=ML-KEM-KAT-ACVP-replay-transcripts-before-evidence-acceptance
kat_runner_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
acvp_submission_package_contract_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
provider_differential_bound=1
deterministic_replay_transcript_schema_recorded=1
transcript_digest_sha256_required=1
transcript_command_fingerprint_required=1
fixture_digest_reference_required=1
implementation_digest_reference_required=1
positive_kat_transcript_lane_recorded=1
negative_kat_transcript_lane_recorded=1
malformed_kat_transcript_lane_recorded=1
implicit_rejection_transcript_lane_recorded=1
acvp_keygen_transcript_lane_recorded=1
acvp_encap_decap_transcript_lane_recorded=1
acvp_decapsulation_val_transcript_lane_recorded=1
acvp_key_check_transcript_lane_recorded=1
kat_replay_transcripts_recorded=0
acvp_replay_transcripts_recorded=0
transcript_digests_verified=0
ci_replay_transcript_recorded=0
review_disposition_recorded=0
transcript_gate_accepted=0
operation_execution_allowed=0
required_transcript_items_total=44
required_transcript_items_satisfied=38
status=ml-kem-kat-acvp-replay-transcript-gate-blocked
```

## ML-KEM KAT Result Schema

```text
ml_kem_kat_result_schema_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
result_scope=ML-KEM-known-answer-result-schema-before-result-recording
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_row_fixture_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
deterministic_result_ordering_required=1
fixture_digest_reference_required=1
vector_family_reference_required=1
parameter_set_field_required=1
operation_family_field_required=1
tgid_tcid_mapping_required=1
expected_result_field_required=1
observed_result_field_required=1
pass_fail_field_required=1
failure_reason_field_required=1
implicit_rejection_result_required=1
provider_differential_field_required=1
transcript_digest_field_required=1
no_secret_material_logging_required=1
result_schema_reviewed=0
fixture_bundle_digest_bound=0
result_row_fixture_recorded=0
positive_result_rows_recorded=0
negative_result_rows_recorded=0
malformed_result_rows_recorded=0
implicit_rejection_rows_recorded=0
provider_differential_rows_recorded=0
ci_kat_replay_transcript_bound=0
kat_runner_execution_recorded=0
acvp_response_generation_evidence_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_result_schema_items_total=44
required_kat_result_schema_items_satisfied=33
status=ml-kem-kat-result-schema-blocked
```

## ML-KEM KAT Result Row Fixture

```text
ml_kem_kat_result_row_fixture_present=1
kat_result_row_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM KAT Result Row Fixture
row_fixture_profile=latticra-q-seal-ml-kem-kat-result-row-fixture/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
row_fixture_scope=ML-KEM-known-answer-result-row-fixture-before-result-recording
row_fixture_state=kat-result-row-fixture-recorded-result-rows-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_schema_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
provider_differential_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
result_row_fixture_policy_recorded=1
row_id_policy_recorded=1
fixture_digest_reference_required=1
vector_family_reference_required=1
parameter_set_field_required=1
operation_family_field_required=1
test_type_field_required=1
tgid_tcid_mapping_required=1
expected_result_field_required=1
observed_result_field_required=1
pass_fail_field_required=1
failure_reason_field_required=1
implicit_rejection_row_policy_recorded=1
provider_differential_row_policy_recorded=1
transcript_digest_reference_required=1
no_secret_material_logging_required=1
deterministic_ordering_required=1
no_network_submission_required=1
no_dynamic_provider_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
row_fixture_reviewed=0
fixture_bundle_digest_bound=0
positive_result_row_fixture_recorded=0
negative_result_row_fixture_recorded=0
malformed_result_row_fixture_recorded=0
implicit_rejection_row_fixture_recorded=0
provider_differential_row_fixture_recorded=0
ci_kat_replay_transcript_bound=0
kat_runner_execution_recorded=0
acvp_response_generation_evidence_recorded=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_kat_result_row_fixture_items_total=44
required_kat_result_row_fixture_items_satisfied=34
status=ml-kem-kat-result-row-fixture-blocked
```

## ACVP Intake

```text
ml_kem_acvp_intake_present=1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm=ML-KEM
revision=FIPS203
keygen_mode_required=1
encap_decap_mode_required=1
vector_json_loaded=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
required_intake_items_total=13
required_intake_items_satisfied=9
status=ml-kem-acvp-intake-offline-blocked
```

## ACVP Capability Matrix

```text
ml_kem_acvp_capability_matrix_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
algorithm_ml_kem_recorded=1
revision_fips203_recorded=1
keygen_mode_required=1
encap_decap_mode_required=1
ml_kem_512_parameter_set_required=1
ml_kem_768_parameter_set_required=1
ml_kem_1024_parameter_set_required=1
encapsulation_function_required=1
decapsulation_function_required=1
encapsulation_key_check_required=1
decapsulation_key_check_required=1
acvp_registration_json_reviewed=0
capability_matrix_reviewed=0
fixture_row_generation_allowed=0
operation_execution_allowed=0
required_capability_items_total=30
required_capability_items_satisfied=24
status=ml-kem-acvp-capability-matrix-blocked
```

## ACVP Fixture Row Plan

```text
ml_kem_acvp_fixture_row_plan_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
acvp_capability_matrix_bound=1
acvp_fixture_digest_row_template_bound=1
vector_fixture_digest_ledger_bound=1
parameter_set_rows_planned=3
keygen_aft_rows_planned=3
encapsulation_aft_rows_planned=3
decapsulation_val_rows_planned=3
encapsulation_key_check_val_rows_planned=3
decapsulation_key_check_val_rows_planned=3
minimum_fixture_row_classes_planned=15
fixture_digest_rows_recorded=0
fixture_source_digests_recorded=0
fixture_storage_paths_recorded=0
fixture_import_reviewed=0
fixture_digest_ledger_reviewed=0
vector_execution_allowed=0
operation_execution_allowed=0
required_fixture_row_plan_items_total=36
required_fixture_row_plan_items_satisfied=25
status=ml-kem-acvp-fixture-row-plan-blocked
```

## ACVP Fixture Digest Row Template

```text
ml_kem_acvp_fixture_digest_row_template_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
acvp_fixture_row_plan_bound=1
vector_fixture_digest_ledger_bound=1
row_id_column_required=1
parameter_set_column_required=1
mode_column_required=1
test_type_column_required=1
function_column_required=1
source_url_column_required=1
sha256_digest_column_required=1
bundle_size_column_required=1
storage_path_column_required=1
license_review_column_required=1
schema_crosscheck_column_required=1
reviewer_identity_column_required=1
review_timestamp_column_required=1
ci_replay_transcript_column_required=1
tamper_evidence_column_required=1
planned_fixture_digest_rows_reserved=15
fixture_digest_rows_recorded=0
source_url_rows_recorded=0
sha256_digest_rows_recorded=0
bundle_size_rows_recorded=0
storage_path_rows_recorded=0
license_review_rows_recorded=0
schema_crosscheck_rows_recorded=0
reviewer_identity_rows_recorded=0
review_timestamp_rows_recorded=0
ci_replay_transcript_rows_recorded=0
tamper_evidence_rows_recorded=0
digest_row_template_reviewed=0
fixture_digest_row_acceptance_allowed=0
vector_execution_allowed=0
operation_execution_allowed=0
required_digest_row_template_items_total=45
required_digest_row_template_items_satisfied=33
status=ml-kem-acvp-fixture-digest-row-template-blocked
```

## ACVP Parser Contract

```text
ml_kem_acvp_parser_contract_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
parser_scope=ML-KEM-ACVP-JSON-parser-contract-before-vector-import
acvp_parser_contract_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
parameter_set_allowlist_required=1
mode_allowlist_required=1
test_type_allowlist_required=1
function_allowlist_required=1
duplicate_key_rejection_required=1
unknown_field_rejection_policy_recorded=1
malformed_json_rejection_required=1
canonical_output_mapping_required=1
no_dynamic_code_loading_required=1
no_network_fetch_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
parser_implementation_present=0
parser_negative_tests_recorded=0
parser_fuzzing_recorded=0
parser_schema_reviewed=0
parser_security_reviewed=0
parser_output_accepted=0
vector_execution_allowed=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
required_parser_contract_items_total=40
required_parser_contract_items_satisfied=31
status=ml-kem-acvp-parser-contract-blocked
```

## ACVP Response Contract

```text
ml_kem_acvp_response_contract_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
response_scope=ML-KEM-ACVP-JSON-response-contract-before-response-generation
acvp_response_contract_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_fixture_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
clean_room_source_boundary_recorded=1
response_envelope_policy_recorded=1
keygen_response_fields_policy_recorded=1
encapsulation_response_fields_policy_recorded=1
decapsulation_response_fields_policy_recorded=1
key_check_response_fields_policy_recorded=1
tcid_tgid_mapping_required=1
hex_output_canonicalization_required=1
boolean_output_policy_recorded=1
deterministic_ordering_required=1
no_dynamic_code_loading_required=1
no_network_submission_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
response_generator_implementation_present=0
response_negative_tests_recorded=0
response_schema_reviewed=0
response_security_reviewed=0
response_ci_replay_recorded=0
parser_output_accepted=0
vector_execution_evidence_recorded=0
response_json_generation_enabled=0
response_output_accepted=0
acvp_submission_allowed=0
operation_execution_allowed=0
required_response_contract_items_total=42
required_response_contract_items_satisfied=33
status=ml-kem-acvp-response-contract-blocked
```

## ACVP Response Fixture

```text
ml_kem_acvp_response_fixture_present=1
acvp_response_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Response Fixture
response_fixture_profile=latticra-q-seal-ml-kem-acvp-response-fixture/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
response_fixture_scope=ML-KEM-ACVP-response-fixture-before-response-output-acceptance
response_fixture_state=acvp-response-fixture-recorded-response-output-missing
fips_203_algorithm_bound=1
acvp_ml_kem_json_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_schema_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
response_fixture_policy_recorded=1
response_envelope_policy_recorded=1
acv_version_echo_required=1
vsid_echo_required=1
tgid_tcid_mapping_required=1
deterministic_ordering_required=1
keygen_response_fixture_required=1
encapsulation_response_fixture_required=1
decapsulation_response_fixture_required=1
key_check_response_fixture_required=1
canonical_hex_output_required=1
boolean_output_policy_recorded=1
no_secret_material_logging_required=1
no_network_submission_required=1
no_dynamic_code_loading_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
response_fixture_reviewed=0
fixture_bundle_digest_bound=0
parser_output_accepted=0
vector_execution_evidence_recorded=0
keygen_response_fixture_recorded=0
encapsulation_response_fixture_recorded=0
decapsulation_response_fixture_recorded=0
key_check_response_fixture_recorded=0
negative_response_fixture_recorded=0
response_schema_reviewed=0
response_security_reviewed=0
response_ci_replay_recorded=0
response_output_accepted=0
acvp_response_generation_evidence_recorded=0
response_json_generation_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_response_fixture_items_total=46
required_response_fixture_items_satisfied=32
status=ml-kem-acvp-response-fixture-blocked
```

## ACVP Submission Package Contract

```text
acvp_submission_package_contract_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Submission Package Contract
submission_package_profile=latticra-q-seal-ml-kem-acvp-submission-package-contract/0.1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
submission_package_scope=ML-KEM-ACVP-submission-package-before-network-submission
submission_package_state=acvp-submission-package-contract-recorded-package-acceptance-missing
acvp_response_fixture_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
offline_package_manifest_required=1
algorithm_registration_required=1
acvp_session_metadata_required=1
vsid_tgid_tcid_traceability_required=1
request_bundle_digest_required=1
response_bundle_digest_required=1
canonical_response_json_required=1
local_replay_transcript_required=1
no_secret_material_logging_required=1
no_network_submission_required=1
submission_package_reviewed=0
request_bundle_digest_bound=0
response_bundle_digest_bound=0
response_output_accepted=0
local_replay_transcript_recorded=0
acvp_client_boundary_reviewed=0
submission_receipt_recorded=0
validation_server_acceptance_recorded=0
acvp_submission_package_accepted=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_submission_package_items_total=41
required_submission_package_items_satisfied=30
status=ml-kem-acvp-submission-package-contract-blocked
```

## ACVP Verdict Receipt Gate

```text
acvp_verdict_receipt_gate_present=1
formal_title=Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate
verdict_receipt_profile=latticra-q-seal-ml-kem-acvp-verdict-receipt-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
verdict_receipt_scope=ML-KEM-ACVP-validation-server-verdicts-before-validation-claims
acvp_submission_package_contract_bound=1
replay_transcript_gate_bound=1
acvp_response_contract_bound=1
acvp_response_fixture_bound=1
acvp_parser_contract_bound=1
acvp_capability_matrix_bound=1
vector_fixture_digest_ledger_bound=1
implementation_binding_manifest_bound=1
review_disposition_ledger_bound=1
reviewer_identity_fixture_bound=1
reviewer_role_mapping_bound=1
validation_server_receipt_required=1
acvp_session_identifier_required=1
vsid_tgid_tcid_verdict_mapping_required=1
parameter_set_verdicts_required=1
operation_verdicts_required=1
pass_fail_verdict_required=1
receipt_digest_sha256_required=1
certificate_or_validation_record_required=1
submission_receipt_bound=0
validation_server_acceptance_bound=0
pass_verdict_recorded=0
certificate_identifier_recorded=0
receipt_digest_verified=0
reviewer_disposition_recorded=0
acvp_verdict_receipt_accepted=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_verdict_receipt_items_total=39
required_verdict_receipt_items_satisfied=32
status=ml-kem-acvp-verdict-receipt-gate-blocked
```

## ML-KEM Validation Claim Gate

```text
validation_claim_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Validation Claim Gate
validation_claim_profile=latticra-q-seal-ml-kem-validation-claim-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-CMVP,NIST-SP-800-218-SSDF
validation_claim_scope=ML-KEM-public-validation-and-release-claims-before-publication
validation_claim_state=validation-claim-gate-recorded-claim-evidence-missing
fips_203_algorithm_bound=1
acvp_ml_kem_protocol_bound=1
acvp_verdict_receipt_gate_bound=1
replay_transcript_gate_bound=1
acvp_submission_package_contract_bound=1
ci_promotion_evidence_bound=1
implementation_binding_manifest_bound=1
readiness_profile_bound=1
module_boundary_gate_bound=1
security_policy_gate_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
source_digest_verification_bound=1
provider_differential_bound=1
clean_room_source_boundary_recorded=1
public_claim_taxonomy_recorded=1
no_implicit_fips_claim_policy_recorded=1
no_implicit_acvp_claim_policy_recorded=1
module_boundary_required=1
security_policy_required=1
acvp_certificate_or_validation_record_required=1
cmvp_certificate_required=1
implementation_digest_receipt_required=1
release_artifact_digest_required=1
release_notes_claim_review_required=1
docs_public_surface_review_required=1
operator_warning_required=1
rollback_claim_revocation_required=1
no_secret_material_logging_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_claim_evidence_recorded=0
acvp_pass_evidence_recorded=0
cmvp_certificate_recorded=0
module_boundary_recorded=0
security_policy_recorded=0
release_artifact_digest_recorded=0
public_claim_review_recorded=0
reviewer_disposition_recorded=0
validation_claim_gate_accepted=0
public_validation_claim_allowed=0
fips_validation_claim_allowed=0
post_quantum_migration_claim_allowed=0
production_crypto_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_validation_claim_items_total=42
required_validation_claim_items_satisfied=33
status=ml-kem-validation-claim-gate-blocked
```

## ML-KEM Module Boundary Gate

```text
module_boundary_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Module Boundary Gate
module_boundary_profile=latticra-q-seal-ml-kem-module-boundary-gate/0.1
standards_basis=NIST-FIPS-203,NIST-FIPS-140-3,NIST-CMVP,NIST-SP-800-218-SSDF
module_boundary_scope=ML-KEM-FIPS-module-boundary-and-security-policy-before-CMVP-or-claims
module_boundary_state=module-boundary-gate-recorded-boundary-evidence-missing
fips_203_algorithm_bound=1
fips_140_3_module_security_bound=1
cmvp_program_bound=1
validation_claim_gate_bound=1
security_policy_gate_bound=1
acvp_verdict_receipt_gate_bound=1
ci_promotion_evidence_bound=1
implementation_binding_manifest_bound=1
source_layout_gate_bound=1
implementation_file_digest_plan_bound=1
source_digest_verification_bound=1
zeroization_evidence_bound=1
randomness_source_bound=1
side_channel_review_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
clean_room_source_boundary_recorded=1
module_boundary_schema_recorded=1
security_policy_template_recorded=1
services_roles_columns_recorded=1
operational_environment_columns_recorded=1
self_test_policy_columns_recorded=1
algorithm_certificate_columns_recorded=1
entropy_boundary_columns_recorded=1
zeroization_boundary_columns_recorded=1
source_digest_policy_bound=1
no_implicit_fips_claim_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
module_boundary_evidence_recorded=0
cryptographic_module_name_recorded=0
module_version_recorded=0
operational_environment_recorded=0
fips_140_3_security_policy_recorded=0
roles_services_authentication_recorded=0
self_test_policy_recorded=0
approved_algorithm_inventory_recorded=0
entropy_source_boundary_recorded=0
zeroization_boundary_review_recorded=0
acvp_algorithm_certificate_bound=0
cmvp_submission_identifier_recorded=0
module_boundary_review_recorded=0
reviewer_disposition_recorded=0
module_boundary_gate_accepted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_module_boundary_items_total=46
required_module_boundary_items_satisfied=31
status=ml-kem-module-boundary-gate-blocked
```

## ML-KEM Security Policy Gate

```text
security_policy_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Security Policy Gate
security_policy_profile=latticra-q-seal-ml-kem-security-policy-gate/0.1
standards_basis=NIST-FIPS-140-3,NIST-SP-800-140B-REV-1,NIST-CMVP,NIST-FIPS-203,NIST-SP-800-218-SSDF
security_policy_scope=ML-KEM-FIPS-140-3-security-policy-before-module-boundary-or-claims
security_policy_state=security-policy-gate-recorded-policy-evidence-missing
fips_140_3_module_security_bound=1
sp800_140b_rev1_security_policy_bound=1
cmvp_program_bound=1
fips_203_algorithm_bound=1
module_boundary_gate_bound=1
validation_claim_gate_bound=1
acvp_verdict_receipt_gate_bound=1
source_digest_verification_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
clean_room_source_boundary_recorded=1
security_policy_template_recorded=1
non_proprietary_policy_required=1
module_identification_section_required=1
cryptographic_module_specification_section_required=1
approved_algorithms_section_required=1
roles_services_authentication_section_required=1
software_firmware_security_section_required=1
operational_environment_section_required=1
self_tests_section_required=1
entropy_boundary_section_required=1
life_cycle_assurance_section_required=1
mitigation_other_attacks_section_required=1
acronyms_references_section_required=1
no_implicit_fips_claim_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
security_policy_evidence_recorded=0
security_policy_document_digest_recorded=0
module_name_version_recorded=0
security_level_table_recorded=0
approved_security_functions_table_recorded=0
services_roles_table_recorded=0
self_test_table_recorded=0
entropy_source_statement_recorded=0
operational_environment_recorded=0
guidance_statement_recorded=0
reviewer_disposition_recorded=0
security_policy_gate_accepted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_security_policy_items_total=41
required_security_policy_items_satisfied=29
status=ml-kem-security-policy-gate-blocked
```

## Provider Differential

```text
ml_kem_provider_differential_present=1
candidate_provider=liboqs-comparison-only
provider_comparison_only=1
provider_linking_enabled=0
provider_runtime_used=0
positive_vector_comparison_recorded=0
negative_vector_comparison_recorded=0
mismatch_triage_recorded=0
operation_execution_allowed=0
required_comparison_items_total=10
required_comparison_items_satisfied=3
status=ml-kem-provider-differential-blocked
```

## ML-KEM Vector Schema

```text
ml_kem_vector_schema_present=1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm_ml_kem_recorded=1
revision_fips203_recorded=1
keygen_mode_schema_recorded=1
encap_decap_mode_schema_recorded=1
keygen_prompt_fields_recorded=1
keygen_response_fields_recorded=1
encap_decap_prompt_fields_recorded=1
encap_decap_response_fields_recorded=1
aft_test_type_recorded=1
val_test_type_recorded=1
implicit_rejection_case_recorded=1
vector_bundle_loaded=0
vector_json_parser_implemented=0
response_generation_enabled=0
vector_execution_enabled=0
required_schema_items_total=18
required_schema_items_satisfied=15
status=ml-kem-vector-schema-blocked
```

## ML-KEM Vector Source Intake

```text
ml_kem_vector_source_intake_present=1
approved_source_authority=NIST-ACVP-or-reviewed-equivalent
digest_algorithm=SHA-256
source_freshness_policy_recorded=1
bundle_source_url_recorded=0
bundle_digest_recorded=0
bundle_license_review_recorded=0
bundle_hash_verified=0
bundle_schema_crosscheck_recorded=0
errata_review_binding_recorded=0
bundle_fetch_performed=0
bundle_imported=0
network_fetch_enabled=0
vector_processing_allowed=0
required_source_items_total=14
required_source_items_satisfied=5
status=ml-kem-vector-source-intake-blocked
```

## ML-KEM Vector Fixture Lock

```text
ml_kem_vector_fixture_lock_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
fixture_scope=ML-KEM-offline-vector-fixture-lock-before-import
vector_fixture_lock_present=1
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
kat_manifest_bound=1
negative_test_evidence_bound=1
implementation_binding_manifest_bound=1
fixture_source_digest_recorded=0
fixture_license_review_recorded=0
fixture_storage_path_recorded=0
fixture_schema_crosscheck_recorded=0
fixture_parameter_coverage_recorded=0
fixture_negative_case_coverage_recorded=0
fixture_import_reviewed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
operation_execution_allowed=0
required_fixture_lock_items_total=28
required_fixture_lock_items_satisfied=21
status=ml-kem-vector-fixture-lock-blocked
```

## ML-KEM Vector Fixture Digest Ledger

```text
ml_kem_vector_fixture_digest_ledger_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
ledger_scope=ML-KEM-offline-vector-fixture-digest-and-coverage-before-import
vector_fixture_digest_ledger_present=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
vector_schema_bound=1
vector_source_intake_bound=1
vector_fixture_lock_bound=1
fixture_source_url_recorded=0
fixture_source_digest_recorded=0
fixture_bundle_size_recorded=0
fixture_license_review_recorded=0
fixture_storage_path_recorded=0
fixture_schema_crosscheck_recorded=0
ml_kem_512_coverage_recorded=0
ml_kem_768_coverage_recorded=0
ml_kem_1024_coverage_recorded=0
keygen_coverage_recorded=0
encaps_coverage_recorded=0
decaps_coverage_recorded=0
negative_case_coverage_recorded=0
fixture_import_reviewed=0
fixture_digest_ledger_reviewed=0
fixture_bundle_loaded=0
vector_execution_allowed=0
operation_execution_allowed=0
required_fixture_digest_items_total=35
required_fixture_digest_items_satisfied=20
status=ml-kem-vector-fixture-digest-ledger-blocked
```

## ML-KEM Negative-Test Evidence

```text
ml_kem_negative_test_evidence_present=1
acvp_source=NIST-ACVP-ML-KEM
evidence_scope=ML-KEM-malformed-input-negative-vector-behavior
acvp_ml_kem_schema_tracked=1
vector_schema_bound=1
vector_source_bound=1
malformed_ciphertext_tests_required=1
malformed_key_tests_required=1
negative_replay_tests_required=1
length_validation_tests_recorded=0
encoding_canonicality_tests_recorded=0
invalid_ciphertext_tests_recorded=0
invalid_public_key_tests_recorded=0
invalid_secret_key_tests_recorded=0
decapsulation_failure_tests_recorded=0
implicit_rejection_tests_recorded=0
fuzzing_corpus_recorded=0
negative_tests_executed=0
parser_execution_allowed=0
required_negative_test_items_total=18
required_negative_test_items_satisfied=7
status=ml-kem-negative-test-evidence-blocked
```

## ML-KEM Memory-Safety Evidence

```text
ml_kem_memory_safety_evidence_present=1
secure_development_source=NIST-SP-800-218-SSDF
evidence_scope=ML-KEM-buffer-bounds-integer-lifetime-and-secret-memory-safety
fips_140_3_software_security_tracked=1
nist_ssdf_source_tracked=1
bounded_buffer_policy_required=1
fixed_capacity_api_policy_required=1
allocation_policy_required=1
size_overflow_checks_recorded=0
bounds_check_review_recorded=0
integer_overflow_review_recorded=0
sanitizer_asan_ubsan_recorded=0
static_analysis_recorded=0
fuzz_memory_safety_recorded=0
memory_safety_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_memory_safety_items_total=20
required_memory_safety_items_satisfied=8
status=ml-kem-memory-safety-evidence-blocked
```

## ML-KEM API Misuse Resistance

```text
ml_kem_api_misuse_resistance_present=1
secure_development_source=NIST-SP-800-218-SSDF
resistance_scope=ML-KEM-public-api-parameter-buffer-key-and-error-misuse-resistance
explicit_algorithm_identifier_required=1
parameter_set_validation_required=1
buffer_length_preflight_required=1
typed_key_material_required=1
no_implicit_rng_required=1
error_taxonomy_recorded=0
api_state_machine_recorded=0
misuse_case_matrix_recorded=0
wrong_parameter_set_tests_recorded=0
null_and_overlap_tests_recorded=0
api_misuse_tests_executed=0
public_api_execution_allowed=0
required_api_misuse_items_total=21
required_api_misuse_items_satisfied=11
status=ml-kem-api-misuse-resistance-blocked
```

## ML-KEM Source Digest Manifest

```text
ml_kem_source_digest_manifest_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
clean_room_source_boundary_recorded=1
planned_source_units_count=9
planned_test_units_count=9
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
digest_template_recorded=1
hash_command_policy_recorded=1
third_party_source_denial_recorded=1
implementation_files_created=0
source_file_digests_recorded=0
test_file_digests_recorded=0
build_script_digests_recorded=0
reviewed_digest_receipt_recorded=0
reproducible_source_snapshot_recorded=0
digest_verification_ci_recorded=0
operation_execution_allowed=0
required_digest_items_total=20
required_digest_items_satisfied=14
status=ml-kem-source-digest-manifest-blocked
```

## ML-KEM Source Digest Receipt

```text
ml_kem_source_digest_receipt_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
receipt_scope=ML-KEM-clean-room-source-digest-receipts-before-promotion
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
implementation_files_created=0
source_receipts_recorded=0
test_receipts_recorded=0
build_receipts_recorded=0
source_receipts_verified=0
reviewed_digest_receipt_recorded=0
receipt_replay_check_recorded=0
ci_digest_verification_recorded=0
operation_execution_allowed=0
required_receipt_items_total=23
required_receipt_items_satisfied=16
status=ml-kem-source-digest-receipt-blocked
```

## ML-KEM Source Digest Verification

```text
ml_kem_source_digest_verification_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
verification_scope=ML-KEM-source-digest-replay-harness-before-promotion
source_digest_manifest_bound=1
source_digest_receipt_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
receipt_schema_bound=1
normalized_path_policy_bound=1
replay_harness_template_recorded=1
tamper_fixture_template_recorded=1
offline_only_verification_recorded=1
source_receipts_available=0
test_receipts_available=0
build_receipts_available=0
source_digest_replay_executed=0
tamper_fixture_executed=0
ci_verification_harness_recorded=0
verification_result_reviewed=0
operation_execution_allowed=0
required_verification_items_total=23
required_verification_items_satisfied=16
status=ml-kem-source-digest-verification-blocked
```

## ML-KEM Receipt Replay Results

```text
ml_kem_receipt_replay_results_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
replay_scope=ML-KEM-source-digest-replay-results-before-promotion
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
source_replay_results_recorded=0
test_replay_results_recorded=0
build_replay_results_recorded=0
tamper_replay_results_recorded=0
replay_result_reviewed=0
operation_execution_allowed=0
required_replay_items_total=24
required_replay_items_satisfied=19
status=ml-kem-receipt-replay-results-blocked
```

## ML-KEM Code Owner Review

```text
ml_kem_code_owner_review_evidence_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
review_scope=ML-KEM-clean-room-source-review-before-promotion
clean_room_review_policy_recorded=1
implementation_binding_manifest_bound=1
source_digest_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_required=1
cryptography_reviewer_required=1
security_reviewer_required=1
code_owner_file_required=1
reviewer_independence_required=1
standards_traceability_required=1
side_channel_reviewer_required=1
reviewer_identities_recorded=0
code_owner_file_recorded=0
cryptography_review_recorded=0
security_review_recorded=0
standards_traceability_review_recorded=0
side_channel_review_recorded=0
source_digest_review_recorded=0
blocking_findings_closed=0
approval_receipt_recorded=0
operation_execution_allowed=0
required_review_items_total=23
required_review_items_satisfied=14
status=ml-kem-code-owner-review-blocked
```

## ML-KEM Review Disposition Ledger

```text
ml_kem_review_disposition_ledger_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
disposition_scope=ML-KEM-review-finding-disposition-before-promotion
code_owner_review_gate_bound=1
source_digest_receipt_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_disposition_required=1
cryptography_disposition_required=1
security_disposition_required=1
standards_traceability_disposition_required=1
side_channel_disposition_required=1
source_digest_disposition_required=1
finding_severity_taxonomy_recorded=1
rejection_disposition_policy_recorded=1
approval_receipt_required=1
reviewer_identity_disposition_recorded=0
code_owner_disposition_recorded=0
cryptography_disposition_recorded=0
security_disposition_recorded=0
standards_traceability_disposition_recorded=0
side_channel_disposition_recorded=0
source_digest_disposition_recorded=0
blocking_findings_closed=0
approval_receipt_recorded=0
operation_execution_allowed=0
required_disposition_items_total=26
required_disposition_items_satisfied=17
status=ml-kem-review-disposition-ledger-blocked
```

## ML-KEM Reviewer Identity Fixture

```text
ml_kem_reviewer_identity_fixture_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
identity_scope=ML-KEM-reviewer-identity-import-before-promotion
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_identity_required=1
cryptography_reviewer_identity_required=1
security_reviewer_identity_required=1
code_owner_identity_required=1
reviewer_independence_required=1
identity_schema_recorded=1
identity_import_template_recorded=1
pii_minimization_policy_recorded=1
reviewer_identities_imported=0
cryptography_reviewer_identity_recorded=0
security_reviewer_identity_recorded=0
code_owner_identity_recorded=0
independence_attestation_recorded=0
identity_import_reviewed=0
approval_authority_recorded=0
operation_execution_allowed=0
required_identity_items_total=23
required_identity_items_satisfied=16
status=ml-kem-reviewer-identity-fixture-blocked
```

## ML-KEM Reviewer Role Mapping

```text
ml_kem_reviewer_role_mapping_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
mapping_scope=ML-KEM-reviewer-role-mapping-before-promotion
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
reviewer_identity_fixture_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
role_schema_recorded=1
cryptography_role_required=1
security_role_required=1
code_owner_role_required=1
standards_traceability_role_required=1
side_channel_role_required=1
source_digest_role_required=1
dual_reviewer_separation_required=1
conflict_of_interest_policy_recorded=1
pii_minimization_policy_bound=1
approval_authority_mapping_required=1
reviewer_identities_imported=0
role_mapping_records_imported=0
cryptography_role_mapped=0
security_role_mapped=0
code_owner_role_mapped=0
standards_traceability_role_mapped=0
side_channel_role_mapped=0
source_digest_role_mapped=0
separation_review_recorded=0
approval_authority_mapped=0
operation_execution_allowed=0
required_role_mapping_items_total=30
required_role_mapping_items_satisfied=20
status=ml-kem-reviewer-role-mapping-blocked
```

## ML-KEM Evidence Import Packet Manifest

```text
ml_kem_evidence_import_packet_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Evidence Import Packet Manifest
evidence_packet_profile=latticra-q-seal-ml-kem-evidence-import-packet-manifest/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
evidence_packet_scope=ML-KEM-evidence-import-packet-manifest-before-import-review
evidence_packet_state=evidence-import-packet-recorded-packet-rows-missing
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
evidence_import_review_gate_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
reviewer_identity_fixture_bound=1
reviewer_role_mapping_bound=1
review_disposition_ledger_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
offline_packet_intake_recorded=1
digest_algorithm_sha256_required=1
immutable_packet_record_required=1
source_url_column_required=1
source_digest_column_required=1
bundle_size_column_required=1
license_column_required=1
storage_path_column_required=1
parameter_set_column_required=1
operation_family_column_required=1
negative_case_column_required=1
replay_transcript_column_required=1
tamper_evidence_column_required=1
reviewer_role_column_required=1
reviewer_identity_column_required=1
disposition_column_required=1
import_timestamp_column_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_digest_packet_rows_imported=0
receipt_replay_packet_rows_imported=0
source_digest_packet_rows_imported=0
reviewer_role_packet_rows_imported=0
coverage_packet_rows_imported=0
tamper_packet_rows_imported=0
evidence_packet_reviewed=0
evidence_packet_manifest_accepted=0
vector_execution_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
implementation_promotion_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_evidence_packet_items_total=41
required_evidence_packet_items_satisfied=33
status=ml-kem-evidence-import-packet-manifest-blocked
```

## ML-KEM Evidence Import Review Gate

```text
evidence_import_review_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Evidence Import Review Gate
evidence_import_profile=latticra-q-seal-ml-kem-evidence-import-review-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
evidence_import_scope=ML-KEM-evidence-import-review-before-implementation-or-promotion
evidence_import_state=evidence-import-review-recorded-import-evidence-missing
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
evidence_import_packet_manifest_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
reviewer_role_mapping_bound=1
reviewer_identity_fixture_bound=1
review_disposition_ledger_bound=1
source_digest_verification_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
offline_evidence_intake_recorded=1
digest_algorithm_sha256_required=1
immutable_import_record_required=1
source_url_digest_size_license_required=1
parameter_set_coverage_required=1
operation_family_coverage_required=1
replay_transcript_required=1
tamper_replay_required=1
reviewer_role_import_required=1
dual_reviewer_separation_required=1
approval_authority_required=1
no_implicit_operation_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_digest_rows_imported=0
receipt_replay_transcripts_imported=0
reviewer_role_records_imported=0
source_digest_receipts_imported=0
parameter_set_coverage_recorded=0
operation_family_coverage_recorded=0
negative_case_coverage_recorded=0
replay_tamper_evidence_recorded=0
evidence_import_reviewed=0
evidence_import_gate_accepted=0
vector_execution_allowed=0
acvp_submission_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_evidence_import_items_total=37
required_evidence_import_items_satisfied=27
status=ml-kem-evidence-import-review-gate-blocked
```

## ML-KEM CI Promotion Evidence

```text
ml_kem_ci_promotion_evidence_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203-and-SP-800-227
promotion_scope=ML-KEM-evidence-gates-before-implementation-promotion
ssdf_secure_build_gate_recorded=1
fips_203_parameter_gate_bound=1
sp_800_227_kem_usage_gate_bound=1
make_quality_security_standards_bound=1
local_wrapper_scripts_recorded=1
qseal_subsystem_scripts_recorded=1
readiness_gate_bound=1
implementation_binding_manifest_bound=1
replay_transcript_gate_bound=1
acvp_verdict_receipt_gate_bound=1
validation_claim_gate_bound=1
module_boundary_gate_bound=1
security_policy_gate_bound=1
evidence_import_packet_manifest_bound=1
evidence_import_review_gate_bound=1
kat_acvp_gate_passing_recorded=0
constant_time_gate_passing_recorded=0
memory_safety_gate_passing_recorded=0
side_channel_gate_passing_recorded=0
negative_test_gate_passing_recorded=0
provider_differential_gate_passing_recorded=0
implementation_binding_ci_result_recorded=0
promotion_workflow_recorded=0
release_claim_gate_recorded=0
signed_artifact_receipt_recorded=0
operation_execution_allowed=0
required_promotion_items_total=26
required_promotion_items_satisfied=16
status=ml-kem-ci-promotion-evidence-blocked
```

## ML-KEM Constant-Time Review

```text
ml_kem_constant_time_review_present=1
analysis_policy=no-secret-dependent-control-flow-or-addresses
secret_dependent_branch_forbidden=1
secret_dependent_memory_index_forbidden=1
secret_dependent_loop_bound_forbidden=1
secret_dependent_early_return_forbidden=1
constant_time_compare_required=1
decapsulation_implicit_rejection_required=1
compiler_optimization_review_required=1
dudect_measurement_recorded=0
ctgrind_or_static_analysis_recorded=0
generated_assembly_review_recorded=0
optimizer_flag_review_recorded=0
secret_state_inventory_bound=0
negative_timing_test_recorded=0
cross_platform_timing_review_recorded=0
formal_reviewer_signoff_recorded=0
ci_constant_time_gate_recorded=0
implementation_binding_recorded=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_review_items_total=18
required_review_items_satisfied=8
status=ml-kem-constant-time-review-blocked
```

## ML-KEM Randomness Source

```text
ml_kem_randomness_source_contract_present=1
random_bit_generation_source=NIST-SP-800-90A-and-NIST-SP-800-90B
keygen_seed_material_required=1
encapsulation_seed_material_required=1
deterministic_test_seed_separation_required=1
entropy_source_inventory_recorded=0
entropy_source_validation_recorded=0
drbg_selection_recorded=0
drbg_security_strength_recorded=0
seed_derivation_policy_recorded=0
reseed_policy_recorded=0
prediction_resistance_policy_recorded=0
health_tests_policy_recorded=0
failure_mode_policy_recorded=0
platform_rng_boundary_recorded=0
random_bytes_generated=0
random_bit_generation_allowed=0
key_generation_randomness_allowed=0
encapsulation_randomness_allowed=0
required_randomness_items_total=18
required_randomness_items_satisfied=6
status=ml-kem-randomness-source-blocked
```

## ML-KEM Zeroization Evidence

```text
ml_kem_zeroization_evidence_present=1
module_security_source=NIST-FIPS-140-3-zeroization-requirements
zeroization_scope=ML-KEM-secret-intermediates-key-and-seed-material
fips_140_3_zeroization_tracked=1
secret_state_contract_bound=1
zeroization_required=1
secret_material_inventory_required=1
compiler_barrier_required=1
zeroization_primitive_selected=0
zeroization_primitive_implemented=0
dead_store_elimination_review_recorded=0
volatile_or_intrinsic_strategy_recorded=0
stack_heap_register_clear_policy_recorded=0
error_path_zeroization_recorded=0
decapsulation_failure_zeroization_recorded=0
test_harness_memory_scan_recorded=0
generated_assembly_review_recorded=0
zeroization_performed=0
secret_material_handling_allowed=0
required_zeroization_items_total=19
required_zeroization_items_satisfied=6
status=ml-kem-zeroization-evidence-blocked
```

## ML-KEM Side-Channel Review

```text
ml_kem_side_channel_review_present=1
module_security_source=NIST-FIPS-140-3-non-invasive-security-posture
review_scope=ML-KEM-keygen-encap-decap-side-channel-surface
fips_140_3_non_invasive_security_tracked=1
constant_time_review_bound=1
secret_state_contract_bound=1
power_analysis_review_required=1
timing_leakage_review_required=1
cache_access_review_required=1
leakage_model_recorded=0
power_analysis_test_recorded=0
timing_measurement_recorded=0
cache_access_analysis_recorded=0
fault_injection_review_recorded=0
microarchitectural_leakage_review_recorded=0
compiler_artifact_review_recorded=0
side_channel_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_review_items_total=19
required_review_items_satisfied=7
status=ml-kem-side-channel-review-blocked
```

## ML-KEM FIPS 203 Conformance Matrix

```text
fips_conformance_matrix_present=1
formal_title=Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix
conformance_profile=latticra-q-seal-ml-kem-fips-conformance-matrix/0.1
standards_basis=NIST-FIPS-203
conformance_scope=ML-KEM-FIPS-203-conformance-before-implementation
conformance_state=fips-conformance-matrix-recorded-implementation-trace-missing
fips_203_source_bound=1
fips_203_publication_date_recorded=1
parameter_sets_bound=1
ml_kem_512_bound=1
ml_kem_768_bound=1
ml_kem_1024_bound=1
algorithm_functions_bound=1
keygen_algorithm_bound=1
encaps_algorithm_bound=1
decaps_algorithm_bound=1
byte_encoding_requirements_bound=1
randomness_requirements_bound=1
hash_xof_boundary_bound=1
decapsulation_failure_semantics_bound=1
acvp_kat_consistency_required=1
clean_room_source_boundary_recorded=1
implementation_binding_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
per_parameter_trace_recorded=0
keygen_step_trace_recorded=0
encaps_step_trace_recorded=0
decaps_step_trace_recorded=0
encoding_tests_recorded=0
failure_semantics_tests_recorded=0
primitive_mapping_reviewed=0
errata_review_recorded=0
implementation_trace_accepted=0
conformance_matrix_accepted=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_conformance_items_total=28
required_conformance_items_satisfied=18
status=ml-kem-fips-conformance-matrix-blocked
```

## Implementation Binding Manifest

```text
ml_kem_implementation_binding_manifest_present=1
standards_basis=NIST-FIPS-203-and-SP-800-227
source_boundary=clean-room-no-apple-code
planned_source_units_count=9
planned_test_units_count=9
fips_203_algorithm_bound=1
sp_800_227_kem_usage_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_layout_gate_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
kat_manifest_bound=1
acvp_intake_bound=1
acvp_capability_matrix_bound=1
acvp_fixture_row_plan_bound=1
acvp_fixture_digest_row_template_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
acvp_response_fixture_bound=1
acvp_submission_package_contract_bound=1
vector_schema_bound=1
vector_source_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
replay_transcript_gate_bound=1
acvp_verdict_receipt_gate_bound=1
validation_claim_gate_bound=1
module_boundary_gate_bound=1
negative_test_evidence_bound=1
memory_safety_evidence_bound=1
api_misuse_resistance_bound=1
constant_time_review_bound=1
randomness_source_bound=1
zeroization_evidence_bound=1
side_channel_review_bound=1
provider_differential_bound=1
secret_state_contract_bound=1
ci_promotion_evidence_bound=1
implementation_code_present=0
keygen_binding_approved=0
encaps_binding_approved=0
decaps_binding_approved=0
operation_execution_allowed=0
required_binding_items_total=48
required_binding_items_satisfied=43
status=ml-kem-implementation-binding-blocked
```

## Source Layout Gate

```text
source_layout_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Source Layout Gate
layout_profile=latticra-q-seal-ml-kem-source-layout-gate/0.1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
layout_scope=ML-KEM-source-layout-and-file-role-boundary-before-source-acceptance
layout_state=source-layout-recorded-source-files-blocked
planned_source_units_count=9
planned_test_units_count=9
implementation_unit_roles_recorded=1
test_unit_roles_recorded=1
public_api_boundary_recorded=1
internal_primitive_boundary_recorded=1
secret_state_boundary_recorded=1
randomness_boundary_recorded=1
zeroization_boundary_recorded=1
constant_time_boundary_recorded=1
parameter_set_coverage_recorded=1
negative_test_lane_recorded=1
kat_acvp_lane_recorded=1
digest_manifest_lane_recorded=1
review_owner_lane_recorded=1
implementation_binding_manifest_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_files_created=0
source_layout_rows_recorded=0
layout_digest_rows_recorded=0
layout_reviewed=0
layout_acceptance_approved=0
source_layout_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
required_layout_items_total=38
required_layout_items_satisfied=32
status=ml-kem-source-layout-gate-blocked
```

## Implementation File Digest Plan

```text
ml_kem_implementation_file_digest_plan_present=1
standards_basis=NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-ACVP-ML-KEM
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
digest_plan_scope=ML-KEM-implementation-file-digest-row-plan-before-source-acceptance
digest_plan_state=file-digest-plan-recorded-digest-rows-blocked
planned_source_units_count=9
planned_test_units_count=9
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
receipt_replay_results_bound=1
implementation_binding_manifest_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_layout_gate_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
kat_manifest_bound=1
acvp_contracts_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
per_file_digest_row_schema_recorded=1
per_file_trace_columns_recorded=1
per_file_review_columns_recorded=1
source_files_created=0
implementation_file_digest_rows_recorded=0
test_file_digest_rows_recorded=0
build_script_digest_rows_recorded=0
digest_receipt_reviewed=0
digest_replay_verified=0
file_digest_plan_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
required_digest_plan_items_total=33
required_digest_plan_items_satisfied=26
status=ml-kem-implementation-file-digest-plan-blocked
```

## Clean-Room Author Attestation Gate

```text
ml_kem_clean_room_author_attestation_gate_present=1
standards_basis=NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-SP-800-227
source_boundary=clean-room-no-apple-code
attestation_scope=ML-KEM-clean-room-author-attestation-before-source-acceptance
attestation_state=author-attestation-template-recorded-author-signoff-blocked
planned_source_units_count=9
planned_test_units_count=9
source_layout_bound=1
implementation_file_digest_plan_bound=1
implementation_traceability_matrix_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
receipt_replay_results_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
ssdf_provenance_policy_bound=1
no_third_party_source_policy_recorded=1
author_attestation_schema_recorded=1
per_file_author_columns_recorded=1
review_independence_required=1
source_files_created=0
author_identity_imported=0
per_file_author_attestations_recorded=0
clean_room_attestation_reviewed=0
provenance_exception_reviewed=0
source_author_attestation_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
required_attestation_items_total=30
required_attestation_items_satisfied=24
status=ml-kem-clean-room-author-attestation-gate-blocked
```

## Per-File Standards Trace Gate

```text
per_file_standards_trace_gate_present=1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
trace_scope=ML-KEM-per-file-FIPS-203-SP-800-227-trace-before-source-acceptance
trace_state=standards-trace-template-recorded-trace-rows-blocked
planned_source_units_count=9
planned_test_units_count=9
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
implementation_traceability_matrix_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
primitive_source_acceptance_gate_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
fips203_clause_columns_recorded=1
sp800_227_usage_columns_recorded=1
parameter_set_columns_recorded=1
operation_family_columns_recorded=1
acceptance_blocker_columns_recorded=1
review_disposition_columns_recorded=1
source_files_created=0
per_file_standards_trace_rows_recorded=0
fips203_clause_coverage_reviewed=0
sp800_227_usage_coverage_reviewed=0
parameter_set_coverage_reviewed=0
trace_review_approved=0
per_file_standards_trace_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
required_standards_trace_items_total=31
required_standards_trace_items_satisfied=24
status=ml-kem-per-file-standards-trace-gate-blocked
```

## Per-File Test Trace Gate

```text
per_file_test_trace_gate_present=1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
trace_scope=ML-KEM-per-file-KAT-ACVP-negative-test-trace-before-source-acceptance
trace_state=test-trace-template-recorded-trace-rows-blocked
planned_source_units_count=9
planned_test_units_count=9
primitive_source_acceptance_gate_bound=1
implementation_traceability_matrix_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
acvp_contracts_bound=1
vector_schema_bound=1
vector_fixture_lock_bound=1
vector_fixture_digest_ledger_bound=1
negative_test_evidence_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
test_family_columns_recorded=1
parameter_set_columns_recorded=1
operation_family_columns_recorded=1
vector_reference_columns_recorded=1
expected_result_columns_recorded=1
review_disposition_columns_recorded=1
source_files_created=0
per_file_test_trace_rows_recorded=0
kat_trace_coverage_reviewed=0
acvp_trace_coverage_reviewed=0
negative_test_trace_reviewed=0
trace_review_approved=0
per_file_test_trace_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
required_test_trace_items_total=39
required_test_trace_items_satisfied=32
status=ml-kem-per-file-test-trace-gate-blocked
```

## Implementation Frame

```text
ml_kem_implementation_frame_present=1
source_boundary=clean-room-no-apple-code
planned_module_count=9
implementation_code_present=0
constant_time_design_recorded=0
zeroization_design_recorded=0
test_vector_binding_recorded=0
formal_review_recorded=0
operations_enabled=0
required_design_items_total=12
required_design_items_satisfied=3
status=ml-kem-implementation-frame-blocked
```

## Secret-State Contract

```text
ml_kem_secret_state_contract_present=1
source_boundary=clean-room-no-apple-code
secret_dependent_branch_forbidden=1
secret_indexed_memory_forbidden=1
secret_dependent_early_return_forbidden=1
constant_time_compare_recorded=0
constant_time_decapsulation_recorded=0
zeroization_primitive_implemented=0
shared_secret_emitted=0
operations_enabled=0
required_secret_state_items_total=19
required_secret_state_items_satisfied=4
status=ml-kem-secret-state-contract-blocked
```

## ML-KEM Secret Ops

```text
ml_kem_secret_ops_present=1
secret_ops_profile=latticra-q-seal-ml-kem-secret-ops/0.1
secure_zero_candidate_present=1
constant_time_equal_candidate_present=1
constant_time_select_candidate_present=1
secret_dependent_early_return_forbidden=1
secret_indexed_memory_forbidden=1
operation_execution_allowed=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
status=ml-kem-secret-ops-candidate-present
```

## Readiness Profile

```text
q_seal_readiness_profile_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
readiness_state=design-frame-ready-runtime-crypto-blocked
foundation_present=1
ml_kem_parameters_present=1
evidence_gate_present=1
fips_conformance_matrix_present=1
sp800_227_usage_profile_present=1
kat_manifest_present=1
kat_runner_contract_present=1
replay_transcript_gate_present=1
kat_result_schema_present=1
kat_result_row_fixture_present=1
acvp_intake_present=1
acvp_capability_matrix_present=1
acvp_fixture_row_plan_present=1
acvp_fixture_digest_row_template_present=1
acvp_parser_contract_present=1
acvp_response_contract_present=1
acvp_response_fixture_present=1
acvp_submission_package_contract_present=1
acvp_verdict_receipt_gate_present=1
validation_claim_gate_present=1
module_boundary_gate_present=1
security_policy_gate_present=1
vector_schema_present=1
vector_source_intake_present=1
vector_fixture_lock_present=1
vector_fixture_digest_ledger_present=1
negative_test_evidence_present=1
memory_safety_evidence_present=1
api_misuse_resistance_present=1
source_digest_manifest_present=1
source_digest_receipt_present=1
source_digest_verification_present=1
receipt_replay_results_present=1
code_owner_review_present=1
review_disposition_ledger_present=1
reviewer_identity_fixture_present=1
reviewer_role_mapping_present=1
evidence_import_packet_manifest_present=1
evidence_import_review_gate_present=1
ci_promotion_evidence_present=1
constant_time_review_present=1
randomness_source_contract_present=1
zeroization_evidence_present=1
side_channel_review_present=1
provider_differential_present=1
implementation_binding_manifest_present=1
source_layout_gate_present=1
implementation_file_digest_plan_present=1
clean_room_author_attestation_gate_present=1
per_file_standards_trace_gate_present=1
per_file_test_trace_gate_present=1
implementation_traceability_matrix_present=1
primitive_source_acceptance_gate_present=1
implementation_frame_present=1
secret_state_contract_present=1
components_total=55
components_present=55
runtime_blockers_total=52
required_readiness_items_total=1611
required_readiness_items_satisfied=1123
design_frame_integration_ready=1
runtime_crypto_ready=0
operations_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
status=q-seal-readiness-profile-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-foundation.sh
sh scripts/test-latticra-q-seal-foundation.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
sh scripts/test-latticra-q-seal-readiness.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-runner-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-result-schema.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-result-row-fixture.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-capability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-row-plan.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-fixture-digest-row-template.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-parser-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-response-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-response-fixture.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-submission-package-contract.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-verdict-receipt-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
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
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
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
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-self-test.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-fips-conformance-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-traceability-matrix.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-source-layout-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-file-digest-plan.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-per-file-standards-trace-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-per-file-test-trace-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-per-file-test-trace-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-primitive-source-acceptance-gate.sh
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
latticra q-seal readiness invariants: ok
latticra q-seal readiness: ok
latticra q-seal ml-kem parameters invariants: ok
latticra q-seal ml-kem parameters: ok
latticra q-seal ml-kem evidence gate invariants: ok
latticra q-seal ml-kem evidence gate: ok
latticra q-seal ml-kem kat manifest invariants: ok
latticra q-seal ml-kem kat manifest: ok
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem acvp capability matrix invariants: ok
latticra q-seal ml-kem acvp capability matrix: ok
latticra q-seal ml-kem acvp fixture row plan invariants: ok
latticra q-seal ml-kem acvp fixture row plan: ok
latticra q-seal ml-kem acvp fixture digest row template invariants: ok
latticra q-seal ml-kem acvp fixture digest row template: ok
latticra q-seal ml-kem acvp parser contract invariants: ok
latticra q-seal ml-kem acvp parser contract: ok
latticra q-seal ml-kem acvp response contract invariants: ok
latticra q-seal ml-kem acvp response contract: ok
latticra q-seal ml-kem acvp response fixture invariants: ok
latticra q-seal ml-kem acvp response fixture: ok
latticra q-seal ml-kem acvp submission package contract invariants: ok
latticra q-seal ml-kem acvp submission package contract: ok
latticra q-seal ml-kem acvp verdict receipt gate invariants: ok
latticra q-seal ml-kem acvp verdict receipt gate: ok
latticra q-seal ml-kem validation claim gate invariants: ok
latticra q-seal ml-kem validation claim gate: ok
latticra q-seal ml-kem module boundary gate invariants: ok
latticra q-seal ml-kem module boundary gate: ok
latticra q-seal ml-kem security policy gate invariants: ok
latticra q-seal ml-kem security policy gate: ok
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
latticra q-seal ml-kem evidence import packet manifest invariants: ok
latticra q-seal ml-kem evidence import packet manifest: ok
latticra q-seal ml-kem evidence import review gate invariants: ok
latticra q-seal ml-kem evidence import review gate: ok
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
latticra q-seal ml-kem provider self-test invariants: ok
latticra q-seal ml-kem provider self-test: ok
latticra q-seal ml-kem fips conformance matrix invariants: ok
latticra q-seal ml-kem fips conformance matrix: ok
latticra q-seal ml-kem sp800-227 usage profile invariants: ok
latticra q-seal ml-kem sp800-227 usage profile: ok
latticra q-seal ml-kem implementation traceability matrix invariants: ok
latticra q-seal ml-kem implementation traceability matrix: ok
latticra q-seal ml-kem implementation file digest plan invariants: ok
latticra q-seal ml-kem implementation file digest plan: ok
latticra q-seal ml-kem clean-room author attestation gate invariants: ok
latticra q-seal ml-kem clean-room author attestation gate: ok
latticra q-seal ml-kem primitive source acceptance gate invariants: ok
latticra q-seal ml-kem primitive source acceptance gate: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
latticra q-seal ml-kem secret ops invariants: ok
latticra q-seal ml-kem secret ops: ok
```
