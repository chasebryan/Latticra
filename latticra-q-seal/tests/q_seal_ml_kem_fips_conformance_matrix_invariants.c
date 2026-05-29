#include "latticra/q_seal_ml_kem_fips_conformance_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int fips_conformance_matrix_is_fail_closed(void) {
    latticra_q_seal_ml_kem_fips_conformance_matrix_t matrix;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(matrix.fips_conformance_matrix_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            matrix.conformance_profile,
            "latticra-q-seal-ml-kem-fips-conformance-matrix/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            matrix.formal_title,
            "Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix") == 0,
        "title");
    EXPECT_TRUE(strcmp(matrix.standards_basis, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(matrix.fips_203_source_bound == 1u, "source");
    EXPECT_TRUE(matrix.fips_203_publication_date_recorded == 1u, "date");
    EXPECT_TRUE(matrix.parameter_sets_bound == 1u, "parameter sets");
    EXPECT_TRUE(matrix.ml_kem_512_bound == 1u, "512");
    EXPECT_TRUE(matrix.ml_kem_768_bound == 1u, "768");
    EXPECT_TRUE(matrix.ml_kem_1024_bound == 1u, "1024");
    EXPECT_TRUE(matrix.algorithm_functions_bound == 1u, "functions");
    EXPECT_TRUE(matrix.keygen_algorithm_bound == 1u, "keygen");
    EXPECT_TRUE(matrix.encaps_algorithm_bound == 1u, "encaps");
    EXPECT_TRUE(matrix.decaps_algorithm_bound == 1u, "decaps");
    EXPECT_TRUE(matrix.byte_encoding_requirements_bound == 1u, "encoding");
    EXPECT_TRUE(matrix.randomness_requirements_bound == 1u, "randomness");
    EXPECT_TRUE(matrix.hash_xof_boundary_bound == 1u, "hash");
    EXPECT_TRUE(matrix.decapsulation_failure_semantics_bound == 1u, "failure");
    EXPECT_TRUE(matrix.acvp_kat_consistency_required == 1u, "acvp kat");
    EXPECT_TRUE(matrix.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(matrix.implementation_binding_required == 1u, "binding");
    EXPECT_TRUE(matrix.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(matrix.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(matrix.per_parameter_trace_recorded == 0u, "trace");
    EXPECT_TRUE(matrix.keygen_step_trace_recorded == 0u, "keygen trace");
    EXPECT_TRUE(matrix.encaps_step_trace_recorded == 0u, "encaps trace");
    EXPECT_TRUE(matrix.decaps_step_trace_recorded == 0u, "decaps trace");
    EXPECT_TRUE(matrix.encoding_tests_recorded == 0u, "encoding tests");
    EXPECT_TRUE(matrix.failure_semantics_tests_recorded == 0u, "failure tests");
    EXPECT_TRUE(matrix.primitive_mapping_reviewed == 0u, "primitive mapping");
    EXPECT_TRUE(matrix.errata_review_recorded == 0u, "errata");
    EXPECT_TRUE(matrix.implementation_trace_accepted == 0u, "trace accepted");
    EXPECT_TRUE(matrix.conformance_matrix_accepted == 0u, "accepted");
    EXPECT_TRUE(matrix.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(matrix.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(matrix.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(matrix.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(matrix.required_conformance_items_total == 28u, "total");
    EXPECT_TRUE(matrix.required_conformance_items_satisfied == 18u, "satisfied");
    EXPECT_TRUE(
        matrix.error == LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_is_no_effect(&matrix) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_allows_implementation_trace_acceptance(
            &matrix) == 0,
        "allows acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_report(
            &matrix,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "fips_conformance_matrix_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "keygen_algorithm_bound=1") != 0, "keygen report");
    EXPECT_TRUE(strstr(rendered, "errata_review_recorded=0") != 0, "errata report");
    EXPECT_TRUE(
        strstr(rendered, "required_conformance_items_total=28") != 0,
        "total report");
    return 0;
}

static int fips_conformance_matrix_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_fips_conformance_matrix_t matrix;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_allows_implementation_trace_acceptance(
            0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_report(
            &matrix,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_fips_conformance_matrix_report(
            &matrix,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (fips_conformance_matrix_is_fail_closed() != 0) {
        return 1;
    }
    if (fips_conformance_matrix_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem fips conformance matrix invariants: ok\n");
    return 0;
}
