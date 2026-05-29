#include "latticra/q_seal_ml_kem_code_owner_review.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int code_owner_review_is_fail_closed(void) {
    latticra_q_seal_ml_kem_code_owner_review_t review;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(review.review_profile, "latticra-q-seal-ml-kem-code-owner-review/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(review.formal_title, "Latticra Q-Seal ML-KEM Code Owner Review") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(review.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(
        strcmp(review.review_scope, "ML-KEM-clean-room-source-review-before-promotion") == 0,
        "scope");
    EXPECT_TRUE(strcmp(review.review_state, "code-owner-review-blocked") == 0, "state");
    EXPECT_TRUE(review.code_owner_review_evidence_present == 1u, "present");
    EXPECT_TRUE(review.ssdf_review_practice_bound == 1u, "ssdf");
    EXPECT_TRUE(review.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(review.clean_room_review_policy_recorded == 1u, "clean room");
    EXPECT_TRUE(review.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(review.source_digest_manifest_required == 1u, "digest required");
    EXPECT_TRUE(review.source_digest_manifest_bound == 1u, "digest bound");
    EXPECT_TRUE(review.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(review.dual_reviewer_required == 1u, "dual");
    EXPECT_TRUE(review.cryptography_reviewer_required == 1u, "crypto");
    EXPECT_TRUE(review.security_reviewer_required == 1u, "security");
    EXPECT_TRUE(review.code_owner_file_required == 1u, "codeowners required");
    EXPECT_TRUE(review.reviewer_independence_required == 1u, "independence");
    EXPECT_TRUE(review.standards_traceability_required == 1u, "traceability");
    EXPECT_TRUE(review.side_channel_reviewer_required == 1u, "side channel");
    EXPECT_TRUE(review.reviewer_identities_recorded == 0u, "identities");
    EXPECT_TRUE(review.code_owner_file_recorded == 0u, "codeowners");
    EXPECT_TRUE(review.cryptography_review_recorded == 0u, "crypto review");
    EXPECT_TRUE(review.security_review_recorded == 0u, "security review");
    EXPECT_TRUE(review.standards_traceability_review_recorded == 0u, "traceability review");
    EXPECT_TRUE(review.side_channel_review_recorded == 0u, "side review");
    EXPECT_TRUE(review.source_digest_review_recorded == 0u, "digest review");
    EXPECT_TRUE(review.blocking_findings_closed == 0u, "findings");
    EXPECT_TRUE(review.approval_receipt_recorded == 0u, "approval");
    EXPECT_TRUE(review.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(review.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(review.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(review.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(review.required_review_items_total == 23u, "total");
    EXPECT_TRUE(review.required_review_items_satisfied == 14u, "satisfied");
    EXPECT_TRUE(review.error == LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_is_no_effect(&review) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(&review) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_report(
            &review,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM CODE OWNER REVIEW") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "code_owner_review_evidence_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "approval_receipt_recorded=0") != 0, "approval report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-code-owner-review-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_code_owner_review_t review;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_code_owner_review_is_no_effect(0) == 0, "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(0) == 0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_prepare(&review) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_report(&review, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report review");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_code_owner_review_report(&review, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (code_owner_review_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem code owner review invariants: ok\n");
    return 0;
}
