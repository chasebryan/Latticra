#include "latticra/q_seal_ml_kem_api_misuse_resistance.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int api_misuse_resistance_records_policy_without_public_api(void) {
    latticra_q_seal_ml_kem_api_misuse_resistance_t resistance;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_prepare(&resistance) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            resistance.resistance_profile,
            "latticra-q-seal-ml-kem-api-misuse-resistance/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(resistance.formal_title, "Latticra Q-Seal ML-KEM API Misuse Resistance") == 0,
        "title");
    EXPECT_TRUE(strcmp(resistance.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(
        strcmp(resistance.module_security_source, "NIST-FIPS-140-3-module-interface-security") ==
            0,
        "module");
    EXPECT_TRUE(
        strcmp(resistance.secure_development_source, "NIST-SP-800-218-SSDF") == 0,
        "ssdf");
    EXPECT_TRUE(
        strcmp(
            resistance.resistance_scope,
            "ML-KEM-public-api-parameter-buffer-key-and-error-misuse-resistance") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(resistance.resistance_state, "policy-recorded-misuse-test-evidence-missing") ==
            0,
        "state");
    EXPECT_TRUE(resistance.api_misuse_resistance_present == 1u, "present");
    EXPECT_TRUE(resistance.fips_203_source_verified == 1u, "fips 203");
    EXPECT_TRUE(resistance.fips_140_3_interface_security_tracked == 1u, "fips 140-3");
    EXPECT_TRUE(resistance.nist_ssdf_source_tracked == 1u, "ssdf tracked");
    EXPECT_TRUE(resistance.implementation_frame_bound == 1u, "implementation frame");
    EXPECT_TRUE(resistance.memory_safety_evidence_bound == 1u, "memory safety");
    EXPECT_TRUE(resistance.negative_test_evidence_bound == 1u, "negative test");
    EXPECT_TRUE(resistance.explicit_algorithm_identifier_required == 1u, "algorithm id");
    EXPECT_TRUE(resistance.parameter_set_validation_required == 1u, "parameter validation");
    EXPECT_TRUE(resistance.buffer_length_preflight_required == 1u, "buffer preflight");
    EXPECT_TRUE(resistance.typed_key_material_required == 1u, "typed key");
    EXPECT_TRUE(resistance.no_implicit_rng_required == 1u, "rng");
    EXPECT_TRUE(resistance.error_taxonomy_recorded == 0u, "error taxonomy");
    EXPECT_TRUE(resistance.api_state_machine_recorded == 0u, "state machine");
    EXPECT_TRUE(resistance.misuse_case_matrix_recorded == 0u, "misuse matrix");
    EXPECT_TRUE(resistance.wrong_parameter_set_tests_recorded == 0u, "wrong parameter");
    EXPECT_TRUE(resistance.null_and_overlap_tests_recorded == 0u, "null overlap");
    EXPECT_TRUE(resistance.deterministic_test_mode_guard_recorded == 0u, "test mode");
    EXPECT_TRUE(resistance.secret_output_lifetime_policy_recorded == 0u, "secret lifetime");
    EXPECT_TRUE(resistance.language_binding_policy_recorded == 0u, "language binding");
    EXPECT_TRUE(resistance.documentation_examples_review_recorded == 0u, "docs");
    EXPECT_TRUE(resistance.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(resistance.api_misuse_tests_executed == 0u, "executed");
    EXPECT_TRUE(resistance.public_api_execution_allowed == 0u, "public api");
    EXPECT_TRUE(resistance.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(resistance.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(resistance.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(resistance.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(resistance.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(resistance.required_api_misuse_items_total == 21u, "total");
    EXPECT_TRUE(resistance.required_api_misuse_items_satisfied == 11u, "satisfied");
    EXPECT_TRUE(resistance.error == LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_is_policy_only(&resistance) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(&resistance) == 0,
        "public api helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_report(
            &resistance,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM API MISUSE RESISTANCE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "api_misuse_resistance_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "api_misuse_tests_executed=0") != 0, "executed report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-api-misuse-resistance-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_api_misuse_resistance_t resistance;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_is_policy_only(0) == 0,
        "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(0) == 0,
        "null public api");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_prepare(&resistance) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_report(&resistance, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report resistance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_api_misuse_resistance_report(&resistance, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (api_misuse_resistance_records_policy_without_public_api() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem api misuse resistance invariants: ok\n");
    return 0;
}
