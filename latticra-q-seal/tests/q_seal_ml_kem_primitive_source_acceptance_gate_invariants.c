#include "latticra/q_seal_ml_kem_primitive_source_acceptance_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int primitive_source_acceptance_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_primitive_source_acceptance_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SOURCE_ACCEPTANCE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            gate.acceptance_profile,
            "latticra-q-seal-ml-kem-primitive-source-acceptance-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            gate.formal_title,
            "Latticra Q-Seal ML-KEM Primitive Source Acceptance Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(gate.standards_basis, "NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(strcmp(gate.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(gate.primitive_source_acceptance_gate_present == 1u, "present");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(gate.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(gate.source_layout_bound == 1u, "layout");
    EXPECT_TRUE(gate.source_layout_gate_bound == 1u, "layout gate");
    EXPECT_TRUE(gate.implementation_traceability_matrix_bound == 1u, "traceability");
    EXPECT_TRUE(gate.fips_conformance_matrix_bound == 1u, "fips");
    EXPECT_TRUE(gate.sp800_227_usage_profile_bound == 1u, "usage");
    EXPECT_TRUE(gate.kat_manifest_bound == 1u, "kat");
    EXPECT_TRUE(gate.acvp_contracts_bound == 1u, "acvp");
    EXPECT_TRUE(gate.source_digest_manifest_bound == 1u, "digest manifest");
    EXPECT_TRUE(gate.source_digest_receipt_bound == 1u, "digest receipt");
    EXPECT_TRUE(gate.source_digest_verification_bound == 1u, "digest verification");
    EXPECT_TRUE(gate.implementation_file_digest_plan_bound == 1u, "file digest plan");
    EXPECT_TRUE(gate.clean_room_author_attestation_gate_bound == 1u, "author attestation");
    EXPECT_TRUE(gate.per_file_standards_trace_gate_bound == 1u, "standards trace");
    EXPECT_TRUE(gate.per_file_test_trace_gate_bound == 1u, "test trace gate");
    EXPECT_TRUE(gate.receipt_replay_results_bound == 1u, "replay");
    EXPECT_TRUE(gate.constant_time_review_bound == 1u, "constant");
    EXPECT_TRUE(gate.memory_safety_evidence_bound == 1u, "memory");
    EXPECT_TRUE(gate.zeroization_evidence_bound == 1u, "zeroization");
    EXPECT_TRUE(gate.randomness_source_bound == 1u, "randomness");
    EXPECT_TRUE(gate.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(gate.api_misuse_resistance_bound == 1u, "api");
    EXPECT_TRUE(gate.side_channel_review_bound == 1u, "side channel");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.source_files_created == 0u, "files");
    EXPECT_TRUE(gate.implementation_code_present == 0u, "code");
    EXPECT_TRUE(gate.source_file_digest_rows_recorded == 0u, "digest rows");
    EXPECT_TRUE(gate.clean_room_author_attestation_recorded == 0u, "attestation");
    EXPECT_TRUE(gate.per_file_standards_trace_recorded == 0u, "standards trace");
    EXPECT_TRUE(gate.per_file_test_trace_recorded == 0u, "test trace");
    EXPECT_TRUE(gate.per_file_review_approval_recorded == 0u, "review approval");
    EXPECT_TRUE(gate.source_acceptance_approved == 0u, "approval");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.shared_secret_emission_allowed == 0u, "shared secret");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_acceptance_items_total == 38u, "total");
    EXPECT_TRUE(gate.required_acceptance_items_satisfied == 30u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_ACCEPTANCE_GATE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_allows_source_acceptance(
            &gate) == 0,
        "allows source acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM PRIMITIVE SOURCE ACCEPTANCE GATE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "primitive_source_acceptance_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "source_layout_bound=1") != 0, "layout report");
    EXPECT_TRUE(
        strstr(rendered, "source_layout_gate_bound=1") != 0,
        "layout gate report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_traceability_matrix_bound=1") != 0,
        "traceability report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_file_digest_plan_bound=1") != 0,
        "file digest plan report");
    EXPECT_TRUE(
        strstr(rendered, "clean_room_author_attestation_gate_bound=1") != 0,
        "author attestation report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_standards_trace_gate_bound=1") != 0,
        "standards trace report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_test_trace_gate_bound=1") != 0,
        "test trace gate report");
    EXPECT_TRUE(strstr(rendered, "source_files_created=0") != 0, "files report");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_emission_allowed=0") != 0,
        "shared secret report");
    EXPECT_TRUE(
        strstr(rendered, "required_acceptance_items_total=38") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-source-acceptance-gate-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_primitive_source_acceptance_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_allows_source_acceptance(0) ==
            0,
        "null source acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report gate");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (primitive_source_acceptance_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem primitive source acceptance gate invariants: ok\n");
    return 0;
}
