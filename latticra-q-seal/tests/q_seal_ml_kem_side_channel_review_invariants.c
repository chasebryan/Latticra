#include "latticra/q_seal_ml_kem_side_channel_review.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int side_channel_review_records_policy_without_testing(void) {
    latticra_q_seal_ml_kem_side_channel_review_t review;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(review.review_profile, "latticra-q-seal-ml-kem-side-channel-review/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(review.formal_title, "Latticra Q-Seal ML-KEM Side-Channel Review") == 0,
        "title");
    EXPECT_TRUE(strcmp(review.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(
        strcmp(
            review.module_security_source,
            "NIST-FIPS-140-3-non-invasive-security-posture") == 0,
        "module");
    EXPECT_TRUE(
        strcmp(review.review_scope, "ML-KEM-keygen-encap-decap-side-channel-surface") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(review.review_state, "policy-recorded-leakage-evidence-missing") == 0,
        "state");
    EXPECT_TRUE(review.side_channel_review_present == 1u, "present");
    EXPECT_TRUE(review.fips_203_source_verified == 1u, "fips 203");
    EXPECT_TRUE(review.fips_140_3_non_invasive_security_tracked == 1u, "fips 140-3");
    EXPECT_TRUE(review.constant_time_review_bound == 1u, "constant time");
    EXPECT_TRUE(review.secret_state_contract_bound == 1u, "secret state");
    EXPECT_TRUE(review.power_analysis_review_required == 1u, "power required");
    EXPECT_TRUE(review.timing_leakage_review_required == 1u, "timing required");
    EXPECT_TRUE(review.cache_access_review_required == 1u, "cache required");
    EXPECT_TRUE(review.leakage_model_recorded == 0u, "leakage model");
    EXPECT_TRUE(review.power_analysis_test_recorded == 0u, "power test");
    EXPECT_TRUE(review.timing_measurement_recorded == 0u, "timing measurement");
    EXPECT_TRUE(review.cache_access_analysis_recorded == 0u, "cache analysis");
    EXPECT_TRUE(review.fault_injection_review_recorded == 0u, "fault injection");
    EXPECT_TRUE(review.microarchitectural_leakage_review_recorded == 0u, "microarchitectural");
    EXPECT_TRUE(review.masked_or_hardened_design_recorded == 0u, "hardened design");
    EXPECT_TRUE(review.compiler_artifact_review_recorded == 0u, "compiler artifact");
    EXPECT_TRUE(review.test_platform_matrix_recorded == 0u, "platform matrix");
    EXPECT_TRUE(review.negative_leakage_test_recorded == 0u, "negative leakage");
    EXPECT_TRUE(review.reviewer_signoff_recorded == 0u, "signoff");
    EXPECT_TRUE(review.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(review.side_channel_tests_executed == 0u, "tests");
    EXPECT_TRUE(review.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(review.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(review.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(review.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(review.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(review.required_review_items_total == 19u, "total");
    EXPECT_TRUE(review.required_review_items_satisfied == 7u, "satisfied");
    EXPECT_TRUE(review.error == LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_is_policy_only(&review) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(&review) == 0,
        "promotion helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_report(&review, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SIDE-CHANNEL REVIEW") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "side_channel_review_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "leakage_model_recorded=0") != 0, "leakage report");
    EXPECT_TRUE(strstr(rendered, "side_channel_tests_executed=0") != 0, "tests report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-side-channel-review-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_side_channel_review_t review;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_is_policy_only(0) == 0,
        "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(0) == 0,
        "null promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_report(&review, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report review");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_side_channel_review_report(&review, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (side_channel_review_records_policy_without_testing() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem side-channel review invariants: ok\n");
    return 0;
}
