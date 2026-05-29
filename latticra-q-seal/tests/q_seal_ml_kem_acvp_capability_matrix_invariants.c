#include "latticra/q_seal_ml_kem_acvp_capability_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int acvp_capability_matrix_is_fail_closed(void) {
    latticra_q_seal_ml_kem_acvp_capability_matrix_t matrix;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(matrix.acvp_capability_matrix_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(matrix.matrix_profile, "latticra-q-seal-ml-kem-acvp-capability-matrix/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(matrix.formal_title, "Latticra Q-Seal ML-KEM ACVP Capability Matrix") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(matrix.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(matrix.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(matrix.acvp_ml_kem_json_bound == 1u, "acvp json");
    EXPECT_TRUE(matrix.algorithm_ml_kem_recorded == 1u, "algorithm");
    EXPECT_TRUE(matrix.revision_fips203_recorded == 1u, "revision");
    EXPECT_TRUE(matrix.keygen_mode_required == 1u, "keygen");
    EXPECT_TRUE(matrix.encap_decap_mode_required == 1u, "encap decap");
    EXPECT_TRUE(matrix.ml_kem_512_parameter_set_required == 1u, "512");
    EXPECT_TRUE(matrix.ml_kem_768_parameter_set_required == 1u, "768");
    EXPECT_TRUE(matrix.ml_kem_1024_parameter_set_required == 1u, "1024");
    EXPECT_TRUE(matrix.keygen_aft_required == 1u, "keygen aft");
    EXPECT_TRUE(matrix.encap_decap_aft_required == 1u, "encap aft");
    EXPECT_TRUE(matrix.decapsulation_val_required == 1u, "decap val");
    EXPECT_TRUE(matrix.encapsulation_function_required == 1u, "encapsulation");
    EXPECT_TRUE(matrix.decapsulation_function_required == 1u, "decapsulation");
    EXPECT_TRUE(matrix.encapsulation_key_check_required == 1u, "encapsulation key check");
    EXPECT_TRUE(matrix.decapsulation_key_check_required == 1u, "decapsulation key check");
    EXPECT_TRUE(matrix.response_schema_keygen_bound == 1u, "keygen response");
    EXPECT_TRUE(matrix.response_schema_encap_decap_bound == 1u, "encap response");
    EXPECT_TRUE(matrix.capability_exchange_policy_recorded == 1u, "exchange");
    EXPECT_TRUE(matrix.prereq_sha_validation_policy_recorded == 1u, "sha prereq");
    EXPECT_TRUE(matrix.vector_source_intake_bound == 1u, "source");
    EXPECT_TRUE(matrix.vector_fixture_digest_ledger_bound == 1u, "ledger");
    EXPECT_TRUE(matrix.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(matrix.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(matrix.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(matrix.acvp_registration_json_reviewed == 0u, "registration review");
    EXPECT_TRUE(matrix.capability_matrix_reviewed == 0u, "matrix review");
    EXPECT_TRUE(matrix.keygen_parameter_coverage_reviewed == 0u, "keygen coverage");
    EXPECT_TRUE(matrix.encap_decap_parameter_coverage_reviewed == 0u, "encap coverage");
    EXPECT_TRUE(matrix.function_coverage_reviewed == 0u, "function coverage");
    EXPECT_TRUE(matrix.response_schema_reviewed == 0u, "response review");
    EXPECT_TRUE(matrix.fixture_row_generation_allowed == 0u, "row generation");
    EXPECT_TRUE(matrix.vector_json_loaded == 0u, "loaded");
    EXPECT_TRUE(matrix.response_json_generation_enabled == 0u, "response generation");
    EXPECT_TRUE(matrix.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(matrix.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(matrix.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(matrix.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(matrix.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(matrix.required_capability_items_total == 30u, "total");
    EXPECT_TRUE(matrix.required_capability_items_satisfied == 24u, "satisfied");
    EXPECT_TRUE(
        matrix.error == LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_is_no_effect(&matrix) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_allows_fixture_row_planning(
            &matrix) == 0,
        "allows row planning");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_report(
            &matrix,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "acvp_capability_matrix_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "keygen_mode_required=1") != 0, "keygen report");
    EXPECT_TRUE(
        strstr(rendered, "encapsulation_key_check_required=1") != 0,
        "function report");
    EXPECT_TRUE(
        strstr(rendered, "fixture_row_generation_allowed=0") != 0,
        "row report");
    EXPECT_TRUE(
        strstr(rendered, "required_capability_items_total=30") != 0,
        "total report");
    return 0;
}

static int acvp_capability_matrix_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_acvp_capability_matrix_t matrix;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_allows_fixture_row_planning(0) == 0,
        "null rows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(&matrix) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_report(
            &matrix,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_acvp_capability_matrix_report(
            &matrix,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (acvp_capability_matrix_is_fail_closed() != 0) {
        return 1;
    }
    if (acvp_capability_matrix_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem acvp capability matrix invariants: ok\n");
    return 0;
}
