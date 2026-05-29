#include "latticra/q_seal_ml_kem_implementation_traceability_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int traceability_matrix_is_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_traceability_matrix_t matrix;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            matrix.traceability_profile,
            "latticra-q-seal-ml-kem-implementation-traceability-matrix/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            matrix.formal_title,
            "Latticra Q-Seal ML-KEM Implementation Traceability Matrix") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(matrix.standards_basis, "NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(strcmp(matrix.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(matrix.implementation_traceability_matrix_present == 1u, "present");
    EXPECT_TRUE(matrix.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(matrix.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(matrix.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(matrix.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(matrix.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(matrix.planned_source_unit_matrix_recorded == 1u, "unit matrix");
    EXPECT_TRUE(matrix.polynomial_arithmetic_unit_bound == 1u, "polynomial");
    EXPECT_TRUE(matrix.ntt_unit_bound == 1u, "ntt");
    EXPECT_TRUE(matrix.sampling_unit_bound == 1u, "sampling");
    EXPECT_TRUE(matrix.compression_unit_bound == 1u, "compression");
    EXPECT_TRUE(matrix.encoding_unit_bound == 1u, "encoding");
    EXPECT_TRUE(matrix.hash_xof_unit_bound == 1u, "hash");
    EXPECT_TRUE(matrix.keygen_unit_bound == 1u, "keygen");
    EXPECT_TRUE(matrix.encaps_unit_bound == 1u, "encaps");
    EXPECT_TRUE(matrix.decaps_unit_bound == 1u, "decaps");
    EXPECT_TRUE(matrix.fips_203_section_mapping_recorded == 1u, "fips mapping");
    EXPECT_TRUE(matrix.sp800_227_usage_mapping_recorded == 1u, "usage mapping");
    EXPECT_TRUE(matrix.kat_vector_family_mapping_recorded == 1u, "kat mapping");
    EXPECT_TRUE(matrix.acvp_test_type_mapping_recorded == 1u, "acvp mapping");
    EXPECT_TRUE(matrix.clean_room_review_path_recorded == 1u, "review path");
    EXPECT_TRUE(matrix.no_external_code_dependency_recorded == 1u, "dependency");
    EXPECT_TRUE(matrix.constant_time_review_mapping_recorded == 0u, "constant");
    EXPECT_TRUE(matrix.memory_safety_mapping_recorded == 0u, "memory");
    EXPECT_TRUE(matrix.zeroization_mapping_recorded == 0u, "zeroization");
    EXPECT_TRUE(matrix.randomness_mapping_recorded == 0u, "randomness");
    EXPECT_TRUE(matrix.negative_test_mapping_recorded == 0u, "negative");
    EXPECT_TRUE(matrix.source_digest_mapping_recorded == 0u, "digest");
    EXPECT_TRUE(matrix.code_owner_mapping_recorded == 0u, "owner");
    EXPECT_TRUE(matrix.review_disposition_mapping_recorded == 0u, "disposition");
    EXPECT_TRUE(matrix.implementation_trace_accepted == 0u, "accepted");
    EXPECT_TRUE(matrix.implementation_file_digest_manifest_recorded == 0u, "file digest");
    EXPECT_TRUE(matrix.implementation_code_present == 0u, "code");
    EXPECT_TRUE(matrix.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(matrix.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(matrix.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(matrix.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(matrix.required_traceability_items_total == 30u, "total");
    EXPECT_TRUE(matrix.required_traceability_items_satisfied == 20u, "satisfied");
    EXPECT_TRUE(matrix.error == LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_is_no_effect(&matrix) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_allows_trace_acceptance(
            &matrix) == 0,
        "acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
            &matrix,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION TRACEABILITY MATRIX") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "implementation_traceability_matrix_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "planned_source_units_count=9") != 0, "source report");
    EXPECT_TRUE(strstr(rendered, "fips_203_section_mapping_recorded=1") != 0, "fips report");
    EXPECT_TRUE(strstr(rendered, "sp800_227_usage_mapping_recorded=1") != 0, "usage report");
    EXPECT_TRUE(
        strstr(rendered, "constant_time_review_mapping_recorded=0") != 0,
        "constant report");
    EXPECT_TRUE(strstr(rendered, "implementation_code_present=0") != 0, "code report");
    EXPECT_TRUE(
        strstr(rendered, "required_traceability_items_total=30") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-traceability-matrix-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_traceability_matrix_t matrix;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_allows_trace_acceptance(0) ==
            0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
            &matrix,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report matrix");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
            &matrix,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (traceability_matrix_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem implementation traceability matrix invariants: ok\n");
    return 0;
}
