#include "latticra/q_seal_ml_kem_review_disposition_ledger.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int review_disposition_ledger_is_fail_closed(void) {
    latticra_q_seal_ml_kem_review_disposition_ledger_t ledger;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_prepare(&ledger) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            ledger.disposition_profile,
            "latticra-q-seal-ml-kem-review-disposition-ledger/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            ledger.formal_title,
            "Latticra Q-Seal ML-KEM Review Disposition Ledger") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(ledger.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(
        strcmp(
            ledger.disposition_scope,
            "ML-KEM-review-finding-disposition-before-promotion") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(ledger.disposition_state, "review-disposition-fixture-blocked") == 0,
        "state");
    EXPECT_TRUE(ledger.review_disposition_ledger_present == 1u, "present");
    EXPECT_TRUE(ledger.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(ledger.ssdf_review_practice_bound == 1u, "ssdf");
    EXPECT_TRUE(ledger.clean_room_review_policy_recorded == 1u, "clean room");
    EXPECT_TRUE(ledger.code_owner_review_gate_bound == 1u, "owner");
    EXPECT_TRUE(ledger.source_digest_receipt_bound == 1u, "receipt");
    EXPECT_TRUE(ledger.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(ledger.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(ledger.dual_reviewer_disposition_required == 1u, "dual");
    EXPECT_TRUE(ledger.cryptography_disposition_required == 1u, "crypto");
    EXPECT_TRUE(ledger.security_disposition_required == 1u, "security");
    EXPECT_TRUE(ledger.standards_traceability_disposition_required == 1u, "standards");
    EXPECT_TRUE(ledger.side_channel_disposition_required == 1u, "side channel");
    EXPECT_TRUE(ledger.source_digest_disposition_required == 1u, "digest");
    EXPECT_TRUE(ledger.finding_severity_taxonomy_recorded == 1u, "taxonomy");
    EXPECT_TRUE(ledger.rejection_disposition_policy_recorded == 1u, "rejection");
    EXPECT_TRUE(ledger.approval_receipt_required == 1u, "approval required");
    EXPECT_TRUE(ledger.reviewer_identity_disposition_recorded == 0u, "identity");
    EXPECT_TRUE(ledger.code_owner_disposition_recorded == 0u, "code owner disposition");
    EXPECT_TRUE(ledger.cryptography_disposition_recorded == 0u, "crypto disposition");
    EXPECT_TRUE(ledger.security_disposition_recorded == 0u, "security disposition");
    EXPECT_TRUE(ledger.standards_traceability_disposition_recorded == 0u, "standards disposition");
    EXPECT_TRUE(ledger.side_channel_disposition_recorded == 0u, "side disposition");
    EXPECT_TRUE(ledger.source_digest_disposition_recorded == 0u, "digest disposition");
    EXPECT_TRUE(ledger.blocking_findings_closed == 0u, "findings");
    EXPECT_TRUE(ledger.approval_receipt_recorded == 0u, "approval");
    EXPECT_TRUE(ledger.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(ledger.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(ledger.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(ledger.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(ledger.required_disposition_items_total == 26u, "total");
    EXPECT_TRUE(ledger.required_disposition_items_satisfied == 17u, "satisfied");
    EXPECT_TRUE(
        ledger.error == LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_is_no_effect(&ledger) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_allows_implementation_promotion(
            &ledger) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_report(
            &ledger,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM REVIEW DISPOSITION LEDGER") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "review_disposition_ledger_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "approval_receipt_recorded=0") != 0, "approval report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-review-disposition-ledger-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_review_disposition_ledger_t ledger;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_allows_implementation_promotion(0) ==
            0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_prepare(&ledger) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_report(&ledger, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report ledger");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_review_disposition_ledger_report(&ledger, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (review_disposition_ledger_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem review disposition ledger invariants: ok\n");
    return 0;
}
