#include "latticra/q_seal_ml_kem_source_digest_verification.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int source_digest_verification_is_fail_closed_harness(void) {
    latticra_q_seal_ml_kem_source_digest_verification_t verification;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_prepare(&verification) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            verification.verification_profile,
            "latticra-q-seal-ml-kem-source-digest-verification/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            verification.formal_title,
            "Latticra Q-Seal ML-KEM Source Digest Verification") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(verification.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(
        strcmp(
            verification.verification_scope,
            "ML-KEM-source-digest-replay-harness-before-promotion") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(
            verification.verification_state,
            "source-digest-verification-harness-blocked") == 0,
        "state");
    EXPECT_TRUE(verification.source_digest_verification_present == 1u, "present");
    EXPECT_TRUE(verification.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(verification.ssdf_source_integrity_bound == 1u, "ssdf");
    EXPECT_TRUE(verification.digest_algorithm_sha256_required == 1u, "sha256");
    EXPECT_TRUE(verification.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(verification.source_digest_manifest_bound == 1u, "manifest");
    EXPECT_TRUE(verification.source_digest_receipt_bound == 1u, "receipt");
    EXPECT_TRUE(verification.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(verification.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(verification.receipt_schema_bound == 1u, "schema");
    EXPECT_TRUE(verification.normalized_path_policy_bound == 1u, "path policy");
    EXPECT_TRUE(verification.replay_harness_template_recorded == 1u, "replay template");
    EXPECT_TRUE(verification.tamper_fixture_template_recorded == 1u, "tamper template");
    EXPECT_TRUE(verification.offline_only_verification_recorded == 1u, "offline");
    EXPECT_TRUE(verification.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(verification.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(verification.implementation_files_created == 0u, "files");
    EXPECT_TRUE(verification.source_receipts_available == 0u, "source receipts");
    EXPECT_TRUE(verification.test_receipts_available == 0u, "test receipts");
    EXPECT_TRUE(verification.build_receipts_available == 0u, "build receipts");
    EXPECT_TRUE(verification.source_digest_replay_executed == 0u, "replay");
    EXPECT_TRUE(verification.tamper_fixture_executed == 0u, "tamper");
    EXPECT_TRUE(verification.ci_verification_harness_recorded == 0u, "ci harness");
    EXPECT_TRUE(verification.verification_result_reviewed == 0u, "reviewed");
    EXPECT_TRUE(verification.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(verification.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(verification.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(verification.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(verification.required_verification_items_total == 23u, "total");
    EXPECT_TRUE(verification.required_verification_items_satisfied == 16u, "satisfied");
    EXPECT_TRUE(
        verification.error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_is_no_effect(&verification) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_allows_implementation_promotion(
            &verification) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_report(
            &verification,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST VERIFICATION") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_verification_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "source_digest_replay_executed=0") != 0, "replay report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-source-digest-verification-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_source_digest_verification_t verification;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_is_no_effect(0) == 0,
        "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_allows_implementation_promotion(0) ==
            0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_prepare(&verification) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_report(
            &verification,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report verification");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_verification_report(
            &verification,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (source_digest_verification_is_fail_closed_harness() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem source digest verification invariants: ok\n");
    return 0;
}
