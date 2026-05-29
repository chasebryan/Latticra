#include "latticra/q_seal_ml_kem_constant_time_review.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int constant_time_review_records_policy_without_promotion(void) {
    latticra_q_seal_ml_kem_constant_time_review_t review;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(review.review_profile, "latticra-q-seal-ml-kem-constant-time-review/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(review.formal_title, "Latticra Q-Seal ML-KEM Constant-Time Review") == 0,
        "title");
    EXPECT_TRUE(strcmp(review.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(
        strcmp(review.review_scope, "ML-KEM-keygen-encap-decap-secret-state") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(review.analysis_policy, "no-secret-dependent-control-flow-or-addresses") == 0,
        "policy");
    EXPECT_TRUE(
        strcmp(review.review_state, "design-rules-recorded-measurement-not-recorded") == 0,
        "state");
    EXPECT_TRUE(review.constant_time_review_present == 1u, "present");
    EXPECT_TRUE(review.fips_203_source_verified == 1u, "fips");
    EXPECT_TRUE(review.secret_dependent_branch_forbidden == 1u, "branch");
    EXPECT_TRUE(review.secret_dependent_memory_index_forbidden == 1u, "memory");
    EXPECT_TRUE(review.secret_dependent_loop_bound_forbidden == 1u, "loop");
    EXPECT_TRUE(review.secret_dependent_early_return_forbidden == 1u, "early return");
    EXPECT_TRUE(review.constant_time_compare_required == 1u, "compare");
    EXPECT_TRUE(review.decapsulation_implicit_rejection_required == 1u, "implicit rejection");
    EXPECT_TRUE(review.compiler_optimization_review_required == 1u, "compiler");
    EXPECT_TRUE(review.dudect_measurement_recorded == 0u, "dudect");
    EXPECT_TRUE(review.ctgrind_or_static_analysis_recorded == 0u, "static");
    EXPECT_TRUE(review.generated_assembly_review_recorded == 0u, "assembly");
    EXPECT_TRUE(review.optimizer_flag_review_recorded == 0u, "optimizer");
    EXPECT_TRUE(review.secret_state_inventory_bound == 0u, "inventory");
    EXPECT_TRUE(review.negative_timing_test_recorded == 0u, "negative timing");
    EXPECT_TRUE(review.cross_platform_timing_review_recorded == 0u, "platform");
    EXPECT_TRUE(review.formal_reviewer_signoff_recorded == 0u, "signoff");
    EXPECT_TRUE(review.ci_constant_time_gate_recorded == 0u, "ci");
    EXPECT_TRUE(review.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(review.measurement_execution_allowed == 0u, "measurement execution");
    EXPECT_TRUE(review.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(review.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(review.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(review.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(review.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(review.required_review_items_total == 18u, "total");
    EXPECT_TRUE(review.required_review_items_satisfied == 8u, "satisfied");
    EXPECT_TRUE(review.error == LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_is_policy_only(&review) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(&review) == 0,
        "promotion helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_report(&review, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM CONSTANT-TIME REVIEW") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "constant_time_review_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "dudect_measurement_recorded=0") != 0, "dudect report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_promotion_allowed=0") != 0,
        "promotion report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-constant-time-review-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_constant_time_review_t review;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_constant_time_review_is_policy_only(0) == 0, "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(0) == 0,
        "null promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_report(&review, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report review");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_constant_time_review_report(&review, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (constant_time_review_records_policy_without_promotion() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem constant-time review invariants: ok\n");
    return 0;
}
