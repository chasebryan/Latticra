#include "latticra/seal_pqc_integration_frame.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int prepared_frame_tracks_pqc_sources_without_authority(void) {
    latticra_seal_pqc_integration_frame_t frame;
    char rendered[LATTICRA_SEAL_PQC_FRAME_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "prepare status");
    EXPECT_TRUE(frame.error == LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK, "frame ok");
    EXPECT_TRUE(
        strcmp(frame.pqc_integration_profile, "latticra-seal-pqc-integration-frame/0.1") == 0,
        "profile");
    EXPECT_TRUE(strcmp(frame.research_date, "2026-05-27") == 0, "research date");
    EXPECT_TRUE(
        strcmp(frame.apple_corecrypto_source, "github.com/apple/corecrypto@2026-05") == 0,
        "apple source");
    EXPECT_TRUE(
        strcmp(frame.apple_corecrypto_license, "evaluation-only-no-redistribution") == 0,
        "apple license");
    EXPECT_TRUE(strcmp(frame.candidate_provider, "liboqs") == 0, "candidate provider");
    EXPECT_TRUE(frame.apple_corecrypto_ml_kem_published == 1u, "apple ml-kem");
    EXPECT_TRUE(frame.apple_corecrypto_ml_dsa_published == 1u, "apple ml-dsa");
    EXPECT_TRUE(frame.apple_corecrypto_formal_verification_published == 1u, "apple verification");
    EXPECT_TRUE(frame.apple_corecrypto_reference_allowed == 1u, "apple reference");
    EXPECT_TRUE(frame.apple_corecrypto_embedding_allowed == 0u, "apple embedding");
    EXPECT_TRUE(frame.apple_corecrypto_redistribution_allowed == 0u, "apple redistribution");
    EXPECT_TRUE(frame.nist_fips_203_ml_kem_tracked == 1u, "fips 203");
    EXPECT_TRUE(frame.nist_fips_204_ml_dsa_tracked == 1u, "fips 204");
    EXPECT_TRUE(frame.nist_fips_205_slh_dsa_backup_tracked == 1u, "fips 205");
    EXPECT_TRUE(frame.ml_kem_key_establishment_planned == 1u, "ml-kem plan");
    EXPECT_TRUE(frame.ml_dsa_signature_planned == 1u, "ml-dsa plan");
    EXPECT_TRUE(frame.hybrid_classical_pqc_transition_required == 1u, "hybrid transition");
    EXPECT_TRUE(frame.liboqs_candidate_tracked == 1u, "liboqs tracked");
    EXPECT_TRUE(frame.liboqs_mit_license_tracked == 1u, "liboqs license");
    EXPECT_TRUE(frame.liboqs_prototype_only_warning_tracked == 1u, "liboqs warning");
    EXPECT_TRUE(frame.candidate_provider_production_use_allowed == 0u, "candidate production");
    EXPECT_TRUE(frame.cryptographic_module_boundary_required == 1u, "module boundary");
    EXPECT_TRUE(frame.algorithm_parameter_inventory_required == 1u, "algorithm inventory");
    EXPECT_TRUE(frame.known_answer_tests_required == 1u, "kat");
    EXPECT_TRUE(frame.cavp_acvp_vector_review_required == 1u, "cavp acvp");
    EXPECT_TRUE(frame.constant_time_review_required == 1u, "constant-time");
    EXPECT_TRUE(frame.side_channel_review_required == 1u, "side-channel");
    EXPECT_TRUE(frame.fips_140_3_claim_gate_required == 1u, "fips 140-3");
    EXPECT_TRUE(frame.sp_800_57_key_management_required == 1u, "sp 800-57");
    EXPECT_TRUE(frame.source_notice_review_required == 1u, "notice review");
    EXPECT_TRUE(frame.third_party_code_vendored == 0u, "vendored");
    EXPECT_TRUE(frame.cryptographic_behavior_changed == 0u, "behavior");
    EXPECT_TRUE(frame.post_quantum_migration_claim_allowed == 0u, "migration claim");
    EXPECT_TRUE(frame.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(frame.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(frame.key_generation_allowed == 0u, "key generation");
    EXPECT_TRUE(frame.key_storage_allowed == 0u, "key storage");
    EXPECT_TRUE(frame.encryption_performed == 0u, "encryption");
    EXPECT_TRUE(frame.signing_performed == 0u, "signing");
    EXPECT_TRUE(frame.network_lookup_allowed == 0u, "network");
    EXPECT_TRUE(frame.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(frame.frame_state, "prepared-authority-neutral") == 0, "frame state");
    EXPECT_TRUE(
        strcmp(frame.blocked_reason, "license-validation-and-provider-review-required") == 0,
        "blocked reason");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_is_authority_neutral(&frame) == 1,
        "authority neutral");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_report(&frame, rendered, sizeof(rendered)) ==
            LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA SEAL PQC INTEGRATION FRAME") != 0,
        "report header");
    EXPECT_TRUE(
        strstr(rendered, "apple_corecrypto_embedding_allowed=0") != 0,
        "report apple embedding");
    EXPECT_TRUE(
        strstr(rendered, "nist_fips_203_ml_kem_tracked=1") != 0,
        "report fips 203");
    EXPECT_TRUE(strstr(rendered, "candidate_provider=liboqs") != 0, "report provider");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report runtime");
    return 0;
}

static int null_and_buffer_handling_fails_closed(void) {
    latticra_seal_pqc_integration_frame_t frame;
    char tiny[1];

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_is_authority_neutral(0) == 0,
        "null helper");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "valid prepare");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_report(&frame, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report");
    EXPECT_TRUE(tiny[0] == '\0', "tiny clear");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report frame");
    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_report(&frame, 0, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (prepared_frame_tracks_pqc_sources_without_authority() != 0) {
        return 1;
    }
    if (null_and_buffer_handling_fails_closed() != 0) {
        return 1;
    }
    printf("seal pqc integration frame invariants: ok\n");
    return 0;
}
