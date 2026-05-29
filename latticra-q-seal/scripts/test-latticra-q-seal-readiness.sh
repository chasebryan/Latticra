#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-readiness.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal readiness: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal readiness: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-readiness"

require_file latticra-q-seal/include/latticra/q_seal_readiness.h
require_file latticra-q-seal/src/q_seal_readiness.c
require_file latticra-q-seal/tests/q_seal_readiness_invariants.c
require_file latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_file latticra-q-seal/evidence/ML_KEM_FIPS_CONFORMANCE_MATRIX.md
require_file latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX.md
require_file latticra-q-seal/evidence/ML_KEM_PRIMITIVE_SOURCE_ACCEPTANCE_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_SOURCE_LAYOUT_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN.md
require_file latticra-q-seal/evidence/ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_PER_FILE_STANDARDS_TRACE_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_PER_FILE_TEST_TRACE_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_KAT_RUNNER_CONTRACT.md
require_file latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_KAT_RESULT_SCHEMA.md
require_file latticra-q-seal/evidence/ML_KEM_KAT_RESULT_ROW_FIXTURE.md
require_file latticra-q-seal/evidence/ML_KEM_ACVP_RESPONSE_FIXTURE.md
require_file latticra-q-seal/evidence/ML_KEM_ACVP_SUBMISSION_PACKAGE_CONTRACT.md
require_file latticra-q-seal/evidence/ML_KEM_ACVP_VERDICT_RECEIPT_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_VALIDATION_CLAIM_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_MODULE_BOUNDARY_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_file latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_file latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh

require_contains 'latticra_q_seal_readiness_prepare' latticra-q-seal/include/latticra/q_seal_readiness.h
require_contains 'latticra-q-seal-readiness/0.1' latticra-q-seal/src/q_seal_readiness.c
require_contains 'components_total = 55u' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_fips_conformance_matrix_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_source_layout_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_clean_room_author_attestation_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_per_file_test_trace_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_kat_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_kat_runner_contract_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_kat_result_schema_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_kat_result_row_fixture_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_capability_matrix_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_parser_contract_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_response_contract_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_response_fixture_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_schema_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_source_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_fixture_lock_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_negative_test_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_memory_safety_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_api_misuse_resistance_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_source_digest_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_source_digest_receipt_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_source_digest_verification_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_receipt_replay_results_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_code_owner_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_review_disposition_ledger_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_reviewer_role_mapping_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_evidence_import_review_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_ci_promotion_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_validation_claim_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_module_boundary_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_security_policy_gate_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_constant_time_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_randomness_source_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_zeroization_evidence_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_side_channel_review_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra_q_seal_ml_kem_implementation_binding_manifest_prepare' latticra-q-seal/src/q_seal_readiness.c
require_contains 'runtime_crypto_ready = 0u' latticra-q-seal/src/q_seal_readiness.c
require_contains 'required_readiness_items_total' latticra-q-seal/src/q_seal_readiness.c
require_contains 'latticra q-seal readiness invariants: ok' latticra-q-seal/tests/q_seal_readiness_invariants.c
require_contains 'q_seal_readiness_profile_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'design_frame_integration_ready=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'runtime_crypto_ready=0' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'fips_conformance_matrix_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'sp800_227_usage_profile_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'implementation_traceability_matrix_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'primitive_source_acceptance_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'source_layout_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'implementation_file_digest_plan_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'clean_room_author_attestation_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'per_file_standards_trace_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'per_file_test_trace_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'kat_manifest_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'kat_runner_contract_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'replay_transcript_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'kat_result_schema_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'kat_result_row_fixture_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'acvp_response_contract_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'acvp_response_fixture_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'acvp_submission_package_contract_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'acvp_verdict_receipt_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'validation_claim_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'module_boundary_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'security_policy_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'evidence_import_packet_manifest_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'evidence_import_review_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'components_total=55' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'runtime_blockers_total=52' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'required_readiness_items_total=1611' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'required_readiness_items_satisfied=1123' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'q_seal_readiness_profile_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'fips_conformance_matrix_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'sp800_227_usage_profile_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_traceability_matrix_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'primitive_source_acceptance_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'source_layout_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_file_digest_plan_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'clean_room_author_attestation_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'per_file_standards_trace_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'per_file_test_trace_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'kat_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'kat_runner_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'replay_transcript_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'kat_result_schema_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'kat_result_row_fixture_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_capability_matrix_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_fixture_row_plan_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_fixture_digest_row_template_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_parser_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_response_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_response_fixture_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_submission_package_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'acvp_verdict_receipt_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'validation_claim_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'module_boundary_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'security_policy_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_schema_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_source_intake_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_fixture_lock_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'vector_fixture_digest_ledger_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'negative_test_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'memory_safety_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'api_misuse_resistance_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'source_digest_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'source_digest_receipt_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'source_digest_verification_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'receipt_replay_results_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'code_owner_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'review_disposition_ledger_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'reviewer_identity_fixture_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'reviewer_role_mapping_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'evidence_import_packet_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'evidence_import_review_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'ci_promotion_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'constant_time_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'randomness_source_contract_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'zeroization_evidence_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'side_channel_review_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_binding_manifest_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_file_digest_plan_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'clean_room_author_attestation_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'implementation_traceability_matrix_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'primitive_source_acceptance_gate_present=1' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'components_total=55' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'components_present=55' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'runtime_blockers_total=52' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'required_readiness_items_total=1611' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md
require_contains 'required_readiness_items_satisfied=1123' latticra-q-seal/docs/LATTICRA_Q_SEAL_READINESS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal.c \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_evidence_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_fips_conformance_matrix.c \
  latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_runner_contract.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_result_schema.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_result_row_fixture.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_intake.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_capability_matrix.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_row_plan.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_fixture_digest_row_template.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_parser_contract.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_response_contract.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_response_fixture.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_submission_package_contract.c \
  latticra-q-seal/src/q_seal_ml_kem_acvp_verdict_receipt_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_schema.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_source.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_fixture_lock.c \
  latticra-q-seal/src/q_seal_ml_kem_vector_fixture_digest_ledger.c \
  latticra-q-seal/src/q_seal_ml_kem_negative_test_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_api_misuse_resistance.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_receipt.c \
  latticra-q-seal/src/q_seal_ml_kem_source_digest_verification.c \
  latticra-q-seal/src/q_seal_ml_kem_receipt_replay_results.c \
  latticra-q-seal/src/q_seal_ml_kem_code_owner_review.c \
  latticra-q-seal/src/q_seal_ml_kem_review_disposition_ledger.c \
  latticra-q-seal/src/q_seal_ml_kem_reviewer_identity_fixture.c \
  latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c \
  latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_ci_promotion_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_validation_claim_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_module_boundary_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_security_policy_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_constant_time_review.c \
  latticra-q-seal/src/q_seal_ml_kem_randomness_source.c \
  latticra-q-seal/src/q_seal_ml_kem_zeroization_evidence.c \
  latticra-q-seal/src/q_seal_ml_kem_side_channel_review.c \
  latticra-q-seal/src/q_seal_ml_kem_provider_differential.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_binding_manifest.c \
  latticra-q-seal/src/q_seal_ml_kem_source_layout_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_file_digest_plan.c \
  latticra-q-seal/src/q_seal_ml_kem_clean_room_author_attestation_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_per_file_standards_trace_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_per_file_test_trace_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_traceability_matrix.c \
  latticra-q-seal/src/q_seal_ml_kem_primitive_source_acceptance_gate.c \
  latticra-q-seal/src/q_seal_ml_kem_implementation_frame.c \
  latticra-q-seal/src/q_seal_ml_kem_secret_state_contract.c \
  latticra-q-seal/src/q_seal_readiness.c \
  latticra-q-seal/tests/q_seal_readiness_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal readiness: ok\n'
