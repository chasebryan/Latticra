#include "latticra/seal_pqc_provider_adapter.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int adapter_prepares_clean_room_provider_without_crypto(void) {
    latticra_seal_pqc_integration_frame_t frame;
    latticra_seal_pqc_provider_adapter_t adapter;
    char rendered[LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_REPORT_MAX];

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "frame status");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(&frame, &adapter) == LATTICRA_STATUS_OK,
        "adapter status");
    EXPECT_TRUE(adapter.error == LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_OK, "adapter ok");
    EXPECT_TRUE(
        strcmp(adapter.adapter_profile, "latticra-seal-pqc-provider-adapter/0.1") == 0,
        "adapter profile");
    EXPECT_TRUE(
        strcmp(adapter.integration_profile, "latticra-seal-pqc-integration-frame/0.1") == 0,
        "integration profile");
    EXPECT_TRUE(strcmp(adapter.clean_room_profile, "latticra-clean-room-pqc/0.1") == 0, "clean profile");
    EXPECT_TRUE(strcmp(adapter.provider_name, "liboqs") == 0, "provider name");
    EXPECT_TRUE(strcmp(adapter.provider_role, "comparison-provider-only") == 0, "provider role");
    EXPECT_TRUE(
        strcmp(adapter.source_boundary, "clean-room-no-apple-code") == 0,
        "source boundary");
    EXPECT_TRUE(adapter.integration_frame_present == 1u, "frame present");
    EXPECT_TRUE(adapter.clean_room_design_required == 1u, "clean room");
    EXPECT_TRUE(adapter.nist_fips_203_ml_kem_required == 1u, "fips 203");
    EXPECT_TRUE(adapter.nist_fips_204_ml_dsa_required == 1u, "fips 204");
    EXPECT_TRUE(adapter.nist_fips_205_slh_dsa_backup_tracked == 1u, "fips 205");
    EXPECT_TRUE(adapter.ml_kem_512_planned == 1u, "ml-kem-512");
    EXPECT_TRUE(adapter.ml_kem_768_planned == 1u, "ml-kem-768");
    EXPECT_TRUE(adapter.ml_kem_1024_planned == 1u, "ml-kem-1024");
    EXPECT_TRUE(adapter.ml_dsa_44_planned == 1u, "ml-dsa-44");
    EXPECT_TRUE(adapter.ml_dsa_65_planned == 1u, "ml-dsa-65");
    EXPECT_TRUE(adapter.ml_dsa_87_planned == 1u, "ml-dsa-87");
    EXPECT_TRUE(adapter.liboqs_comparison_provider_allowed == 1u, "liboqs compare");
    EXPECT_TRUE(adapter.liboqs_linked == 0u, "liboqs linked");
    EXPECT_TRUE(adapter.liboqs_runtime_used == 0u, "liboqs runtime");
    EXPECT_TRUE(adapter.apple_corecrypto_reference_allowed == 1u, "apple reference");
    EXPECT_TRUE(adapter.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(adapter.apple_corecrypto_proof_artifacts_copied == 0u, "apple proofs");
    EXPECT_TRUE(adapter.apple_corecrypto_symbols_reused == 0u, "apple symbols");
    EXPECT_TRUE(adapter.permissive_reference_code_required == 1u, "permissive reference");
    EXPECT_TRUE(adapter.third_party_notice_review_required == 1u, "notice review");
    EXPECT_TRUE(adapter.compile_time_gate_required == 1u, "compile gate");
    EXPECT_TRUE(adapter.default_build_enabled == 0u, "default build");
    EXPECT_TRUE(adapter.known_answer_tests_required == 1u, "kat");
    EXPECT_TRUE(adapter.differential_tests_allowed == 1u, "differential allowed");
    EXPECT_TRUE(adapter.differential_tests_performed == 0u, "differential performed");
    EXPECT_TRUE(adapter.fuzzing_required == 1u, "fuzzing");
    EXPECT_TRUE(adapter.constant_time_review_required == 1u, "constant time");
    EXPECT_TRUE(adapter.side_channel_review_required == 1u, "side channel");
    EXPECT_TRUE(adapter.memory_safe_implementation_preferred == 1u, "memory safe");
    EXPECT_TRUE(adapter.c_abi_boundary_required == 1u, "c abi");
    EXPECT_TRUE(adapter.cryptographic_module_boundary_required == 1u, "module boundary");
    EXPECT_TRUE(adapter.fips_140_3_claim_gate_required == 1u, "fips 140-3");
    EXPECT_TRUE(adapter.cavp_acvp_vector_review_required == 1u, "cavp acvp");
    EXPECT_TRUE(adapter.key_generation_performed == 0u, "keygen");
    EXPECT_TRUE(adapter.key_storage_performed == 0u, "storage");
    EXPECT_TRUE(adapter.encapsulation_performed == 0u, "encapsulation");
    EXPECT_TRUE(adapter.decapsulation_performed == 0u, "decapsulation");
    EXPECT_TRUE(adapter.signing_performed == 0u, "signing");
    EXPECT_TRUE(adapter.verification_performed == 0u, "verification");
    EXPECT_TRUE(adapter.encryption_performed == 0u, "encryption");
    EXPECT_TRUE(adapter.network_lookup_allowed == 0u, "network");
    EXPECT_TRUE(adapter.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(adapter.post_quantum_migration_claim_allowed == 0u, "migration claim");
    EXPECT_TRUE(adapter.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(
        strcmp(adapter.adapter_state, "prepared-clean-room-adapter") == 0,
        "adapter state");
    EXPECT_TRUE(
        strcmp(adapter.blocked_reason, "crypto-operations-not-implemented") == 0,
        "blocked reason");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_is_clean_room(&adapter) == 1,
        "clean-room helper");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_is_authority_neutral(&adapter) == 1,
        "authority helper");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_report(&adapter, rendered, sizeof(rendered)) ==
            LATTICRA_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL PQC PROVIDER ADAPTER") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "provider_name=liboqs") != 0, "report provider");
    EXPECT_TRUE(strstr(rendered, "source_boundary=clean-room-no-apple-code") != 0, "report boundary");
    EXPECT_TRUE(strstr(rendered, "apple_corecrypto_code_copied=0") != 0, "report apple code");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=0") != 0, "report keygen");
    return 0;
}

static int adapter_blocks_invalid_frames(void) {
    latticra_seal_pqc_integration_frame_t frame;
    latticra_seal_pqc_provider_adapter_t adapter;

    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(0, &adapter) == LATTICRA_STATUS_OK,
        "missing frame status");
    EXPECT_TRUE(adapter.error == LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_MISSING_FRAME, "missing frame");

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "frame status");
    frame.apple_corecrypto_embedding_allowed = 1u;
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(&frame, &adapter) == LATTICRA_STATUS_OK,
        "apple violation status");
    EXPECT_TRUE(
        adapter.error == LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_APPLE_BOUNDARY_VIOLATION,
        "apple violation");
    EXPECT_TRUE(adapter.apple_corecrypto_code_copied == 0u, "apple copy stays closed");
    EXPECT_TRUE(adapter.runtime_authority_granted == 0u, "runtime stays closed");

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "provider frame status");
    (void)snprintf(frame.candidate_provider, sizeof(frame.candidate_provider), "%s", "unknown");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(&frame, &adapter) == LATTICRA_STATUS_OK,
        "invalid provider status");
    EXPECT_TRUE(adapter.error == LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_FRAME, "invalid provider");
    EXPECT_TRUE(adapter.liboqs_comparison_provider_allowed == 0u, "compare closed");
    return 0;
}

static int null_and_buffer_handling_fails_closed(void) {
    latticra_seal_pqc_integration_frame_t frame;
    latticra_seal_pqc_provider_adapter_t adapter;
    char tiny[1];

    EXPECT_TRUE(
        latticra_seal_pqc_integration_frame_prepare(&frame) == LATTICRA_STATUS_OK,
        "frame status");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(&frame, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_seal_pqc_provider_adapter_is_clean_room(0) == 0, "null clean");
    EXPECT_TRUE(latticra_seal_pqc_provider_adapter_is_authority_neutral(0) == 0, "null authority");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_from_frame(&frame, &adapter) == LATTICRA_STATUS_OK,
        "adapter status");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_report(&adapter, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "tiny report");
    EXPECT_TRUE(tiny[0] == '\0', "tiny clear");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report adapter");
    EXPECT_TRUE(
        latticra_seal_pqc_provider_adapter_report(&adapter, 0, sizeof(tiny)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (adapter_prepares_clean_room_provider_without_crypto() != 0) {
        return 1;
    }
    if (adapter_blocks_invalid_frames() != 0) {
        return 1;
    }
    if (null_and_buffer_handling_fails_closed() != 0) {
        return 1;
    }
    printf("seal pqc provider adapter invariants: ok\n");
    return 0;
}
