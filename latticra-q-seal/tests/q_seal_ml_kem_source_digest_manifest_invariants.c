#include "latticra/q_seal_ml_kem_source_digest_manifest.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int source_digest_manifest_is_clean_room_template_only(void) {
    latticra_q_seal_ml_kem_source_digest_manifest_t manifest;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            manifest.digest_profile,
            "latticra-q-seal-ml-kem-source-digest-manifest/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(manifest.formal_title, "Latticra Q-Seal ML-KEM Source Digest Manifest") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(manifest.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(strcmp(manifest.digest_algorithm, "SHA-256") == 0, "digest");
    EXPECT_TRUE(strcmp(manifest.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(
        strcmp(manifest.digest_state, "source-digest-template-blocked") == 0,
        "state");
    EXPECT_TRUE(manifest.source_digest_manifest_present == 1u, "present");
    EXPECT_TRUE(manifest.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(manifest.ssdf_source_integrity_bound == 1u, "ssdf");
    EXPECT_TRUE(manifest.digest_algorithm_sha256_recorded == 1u, "sha256");
    EXPECT_TRUE(manifest.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(manifest.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(manifest.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(manifest.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(manifest.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(manifest.digest_template_recorded == 1u, "template");
    EXPECT_TRUE(manifest.hash_command_policy_recorded == 1u, "hash policy");
    EXPECT_TRUE(manifest.third_party_source_denial_recorded == 1u, "third party");
    EXPECT_TRUE(manifest.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(manifest.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(manifest.implementation_files_created == 0u, "files");
    EXPECT_TRUE(manifest.source_file_digests_recorded == 0u, "source digests");
    EXPECT_TRUE(manifest.test_file_digests_recorded == 0u, "test digests");
    EXPECT_TRUE(manifest.build_script_digests_recorded == 0u, "build digests");
    EXPECT_TRUE(manifest.reviewed_digest_receipt_recorded == 0u, "receipt");
    EXPECT_TRUE(manifest.reproducible_source_snapshot_recorded == 0u, "snapshot");
    EXPECT_TRUE(manifest.digest_verification_ci_recorded == 0u, "ci verification");
    EXPECT_TRUE(manifest.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(manifest.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(manifest.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(manifest.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(manifest.required_digest_items_total == 20u, "total");
    EXPECT_TRUE(manifest.required_digest_items_satisfied == 14u, "satisfied");
    EXPECT_TRUE(manifest.error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_is_clean_room_no_effect(&manifest) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(
            &manifest) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_report(
            &manifest,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST MANIFEST") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_manifest_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "implementation_files_created=0") != 0, "files report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-source-digest-manifest-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_source_digest_manifest_t manifest;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_is_clean_room_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(0) == 0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_report(
            &manifest,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report manifest");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_source_digest_manifest_report(
            &manifest,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (source_digest_manifest_is_clean_room_template_only() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem source digest manifest invariants: ok\n");
    return 0;
}
