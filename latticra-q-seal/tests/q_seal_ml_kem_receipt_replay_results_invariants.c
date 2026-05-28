#include "latticra/q_seal_ml_kem_receipt_replay_results.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int receipt_replay_results_are_fail_closed(void) {
    latticra_q_seal_ml_kem_receipt_replay_results_t results;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_prepare(&results) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(results.receipt_replay_results_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            results.replay_profile,
            "latticra-q-seal-ml-kem-receipt-replay-results/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(results.formal_title, "Latticra Q-Seal ML-KEM Receipt Replay Results") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(results.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(results.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(results.ssdf_source_integrity_bound == 1u, "ssdf");
    EXPECT_TRUE(results.digest_algorithm_sha256_required == 1u, "sha256");
    EXPECT_TRUE(results.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(results.source_digest_manifest_bound == 1u, "manifest");
    EXPECT_TRUE(results.source_digest_receipt_bound == 1u, "receipt");
    EXPECT_TRUE(results.source_digest_verification_bound == 1u, "verification");
    EXPECT_TRUE(results.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(results.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(results.source_receipt_result_schema_recorded == 1u, "source schema");
    EXPECT_TRUE(results.test_receipt_result_schema_recorded == 1u, "test schema");
    EXPECT_TRUE(results.build_receipt_result_schema_recorded == 1u, "build schema");
    EXPECT_TRUE(results.replay_command_template_recorded == 1u, "replay command");
    EXPECT_TRUE(results.tamper_result_template_recorded == 1u, "tamper result");
    EXPECT_TRUE(results.ci_result_binding_recorded == 1u, "ci result");
    EXPECT_TRUE(results.offline_only_replay_recorded == 1u, "offline only");
    EXPECT_TRUE(results.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(results.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(results.implementation_files_created == 0u, "implementation");
    EXPECT_TRUE(results.source_replay_results_recorded == 0u, "source results");
    EXPECT_TRUE(results.test_replay_results_recorded == 0u, "test results");
    EXPECT_TRUE(results.build_replay_results_recorded == 0u, "build results");
    EXPECT_TRUE(results.tamper_replay_results_recorded == 0u, "tamper replay");
    EXPECT_TRUE(results.replay_result_reviewed == 0u, "reviewed");
    EXPECT_TRUE(results.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(results.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(results.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(results.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(results.required_replay_items_total == 24u, "total");
    EXPECT_TRUE(results.required_replay_items_satisfied == 19u, "satisfied");
    EXPECT_TRUE(
        results.error == LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_BLOCKED,
        "error");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_is_no_effect(&results) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_allows_implementation_promotion(
            &results) == 0,
        "promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_report(
            &results,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "receipt_replay_results_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_verification_bound=1") != 0,
        "verification report");
    EXPECT_TRUE(
        strstr(rendered, "source_replay_results_recorded=0") != 0,
        "source result report");
    EXPECT_TRUE(
        strstr(rendered, "required_replay_items_total=24") != 0,
        "total report");
    return 0;
}

static int receipt_replay_results_reject_invalid_inputs(void) {
    latticra_q_seal_ml_kem_receipt_replay_results_t results;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_allows_implementation_promotion(0) ==
            0,
        "null promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_prepare(&results) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_report(&results, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_receipt_replay_results_report(&results, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (receipt_replay_results_are_fail_closed() != 0) {
        return 1;
    }
    if (receipt_replay_results_reject_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem receipt replay results invariants: ok\n");
    return 0;
}
