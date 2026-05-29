#include "latticra/q_seal_ml_kem_source_digest_receipt.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int source_digest_receipt_is_fail_closed_fixture(void) {
    latticra_q_seal_ml_kem_source_digest_receipt_t receipt;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_prepare(&receipt) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(receipt.receipt_profile, "latticra-q-seal-ml-kem-source-digest-receipt/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(receipt.formal_title, "Latticra Q-Seal ML-KEM Source Digest Receipt") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(receipt.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(
        strcmp(
            receipt.receipt_scope,
            "ML-KEM-clean-room-source-digest-receipts-before-promotion") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(receipt.receipt_state, "source-digest-receipt-fixture-blocked") == 0,
        "state");
    EXPECT_TRUE(receipt.source_digest_receipt_present == 1u, "present");
    EXPECT_TRUE(receipt.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(receipt.ssdf_source_integrity_bound == 1u, "ssdf");
    EXPECT_TRUE(receipt.digest_algorithm_sha256_required == 1u, "sha256");
    EXPECT_TRUE(receipt.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(receipt.source_digest_manifest_bound == 1u, "manifest");
    EXPECT_TRUE(receipt.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(receipt.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(receipt.planned_source_receipts_count == 9u, "source receipts");
    EXPECT_TRUE(receipt.planned_test_receipts_count == 9u, "test receipts");
    EXPECT_TRUE(receipt.planned_build_receipts_count == 1u, "build receipts");
    EXPECT_TRUE(receipt.receipt_schema_recorded == 1u, "schema");
    EXPECT_TRUE(receipt.normalized_path_policy_recorded == 1u, "path policy");
    EXPECT_TRUE(receipt.hash_command_policy_recorded == 1u, "hash policy");
    EXPECT_TRUE(receipt.reproducible_snapshot_policy_recorded == 1u, "snapshot");
    EXPECT_TRUE(receipt.tamper_evidence_policy_recorded == 1u, "tamper");
    EXPECT_TRUE(receipt.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(receipt.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(receipt.implementation_files_created == 0u, "files");
    EXPECT_TRUE(receipt.source_receipts_recorded == 0u, "source recorded");
    EXPECT_TRUE(receipt.test_receipts_recorded == 0u, "test recorded");
    EXPECT_TRUE(receipt.build_receipts_recorded == 0u, "build recorded");
    EXPECT_TRUE(receipt.source_receipts_verified == 0u, "verified");
    EXPECT_TRUE(receipt.reviewed_digest_receipt_recorded == 0u, "reviewed receipt");
    EXPECT_TRUE(receipt.receipt_replay_check_recorded == 0u, "replay");
    EXPECT_TRUE(receipt.ci_digest_verification_recorded == 0u, "ci verification");
    EXPECT_TRUE(receipt.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(receipt.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(receipt.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(receipt.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(receipt.required_receipt_items_total == 23u, "total");
    EXPECT_TRUE(receipt.required_receipt_items_satisfied == 16u, "satisfied");
    EXPECT_TRUE(
        receipt.error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_is_no_effect(&receipt) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_allows_implementation_promotion(
            &receipt) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_report(
            &receipt,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST RECEIPT") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_receipt_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "source_receipts_recorded=0") != 0, "source report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-source-digest-receipt-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_source_digest_receipt_t receipt;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_source_digest_receipt_is_no_effect(0) == 0, "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_allows_implementation_promotion(0) == 0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_prepare(&receipt) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_report(&receipt, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report receipt");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_receipt_report(&receipt, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (source_digest_receipt_is_fail_closed_fixture() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem source digest receipt invariants: ok\n");
    return 0;
}
