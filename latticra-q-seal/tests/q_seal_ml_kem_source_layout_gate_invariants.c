#include "latticra/q_seal_ml_kem_source_layout_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int source_layout_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_source_layout_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(gate.layout_profile, "latticra-q-seal-ml-kem-source-layout-gate/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(gate.formal_title, "Latticra Q-Seal ML-KEM Source Layout Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(strcmp(gate.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(gate.source_layout_gate_present == 1u, "present");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(gate.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(gate.implementation_unit_roles_recorded == 1u, "implementation roles");
    EXPECT_TRUE(gate.test_unit_roles_recorded == 1u, "test roles");
    EXPECT_TRUE(gate.public_api_boundary_recorded == 1u, "public api");
    EXPECT_TRUE(gate.internal_primitive_boundary_recorded == 1u, "primitive");
    EXPECT_TRUE(gate.secret_state_boundary_recorded == 1u, "secret state");
    EXPECT_TRUE(gate.randomness_boundary_recorded == 1u, "randomness");
    EXPECT_TRUE(gate.zeroization_boundary_recorded == 1u, "zeroization");
    EXPECT_TRUE(gate.constant_time_boundary_recorded == 1u, "constant time");
    EXPECT_TRUE(gate.parameter_set_coverage_recorded == 1u, "parameter coverage");
    EXPECT_TRUE(gate.negative_test_lane_recorded == 1u, "negative lane");
    EXPECT_TRUE(gate.kat_acvp_lane_recorded == 1u, "kat acvp lane");
    EXPECT_TRUE(gate.digest_manifest_lane_recorded == 1u, "digest lane");
    EXPECT_TRUE(gate.review_owner_lane_recorded == 1u, "review lane");
    EXPECT_TRUE(gate.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(gate.implementation_file_digest_plan_bound == 1u, "digest plan");
    EXPECT_TRUE(gate.clean_room_author_attestation_gate_bound == 1u, "author");
    EXPECT_TRUE(gate.per_file_standards_trace_gate_bound == 1u, "standards trace");
    EXPECT_TRUE(gate.per_file_test_trace_gate_bound == 1u, "test trace");
    EXPECT_TRUE(gate.implementation_traceability_matrix_bound == 1u, "traceability");
    EXPECT_TRUE(gate.primitive_source_acceptance_gate_bound == 1u, "acceptance");
    EXPECT_TRUE(gate.source_digest_manifest_bound == 1u, "digest manifest");
    EXPECT_TRUE(gate.source_digest_receipt_bound == 1u, "digest receipt");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "code owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.source_files_created == 0u, "source files");
    EXPECT_TRUE(gate.source_layout_rows_recorded == 0u, "layout rows");
    EXPECT_TRUE(gate.layout_digest_rows_recorded == 0u, "digest rows");
    EXPECT_TRUE(gate.layout_reviewed == 0u, "review");
    EXPECT_TRUE(gate.layout_acceptance_approved == 0u, "approval");
    EXPECT_TRUE(gate.source_layout_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.shared_secret_emission_allowed == 0u, "shared secret");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_layout_items_total == 38u, "total");
    EXPECT_TRUE(gate.required_layout_items_satisfied == 32u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_allows_layout_acceptance(&gate) ==
            0,
        "allows layout acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SOURCE LAYOUT GATE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "source_layout_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "public_api_boundary_recorded=1") != 0,
        "api boundary report");
    EXPECT_TRUE(
        strstr(rendered, "source_layout_accepted=0") != 0,
        "accepted report");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_emission_allowed=0") != 0,
        "shared secret report");
    EXPECT_TRUE(
        strstr(rendered, "required_layout_items_total=38") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-source-layout-gate-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_source_layout_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_allows_layout_acceptance(0) == 0,
        "null layout acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_report(&gate, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report gate");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_layout_gate_report(&gate, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (source_layout_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem source layout gate invariants: ok\n");
    return 0;
}
