#include "latticra/q_seal_readiness.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int readiness_profile_aggregates_fail_closed_state(void) {
    latticra_q_seal_readiness_t readiness;
    char rendered[LATTICRA_Q_SEAL_READINESS_REPORT_MAX];

    EXPECT_TRUE(latticra_q_seal_readiness_prepare(&readiness) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(strcmp(readiness.readiness_profile, "latticra-q-seal-readiness/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(readiness.formal_title, "Latticra Q-Seal Readiness Profile") == 0, "title");
    EXPECT_TRUE(strcmp(readiness.subsystem_path, "latticra-q-seal") == 0, "path");
    EXPECT_TRUE(
        strcmp(readiness.standards_basis, "NIST-FIPS-203-and-NIST-ACVP-ML-KEM") == 0,
        "standards");
    EXPECT_TRUE(strcmp(readiness.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(
        strcmp(readiness.readiness_state, "design-frame-ready-runtime-crypto-blocked") == 0,
        "state");
    EXPECT_TRUE(readiness.readiness_profile_present == 1u, "present");
    EXPECT_TRUE(readiness.foundation_present == 1u, "foundation");
    EXPECT_TRUE(readiness.ml_kem_parameters_present == 1u, "parameters");
    EXPECT_TRUE(readiness.ml_kem_512_parameters_present == 1u, "512");
    EXPECT_TRUE(readiness.ml_kem_768_parameters_present == 1u, "768");
    EXPECT_TRUE(readiness.ml_kem_1024_parameters_present == 1u, "1024");
    EXPECT_TRUE(readiness.evidence_gate_present == 1u, "evidence");
    EXPECT_TRUE(readiness.acvp_intake_present == 1u, "acvp");
    EXPECT_TRUE(readiness.vector_schema_present == 1u, "vector schema");
    EXPECT_TRUE(readiness.vector_source_intake_present == 1u, "vector source");
    EXPECT_TRUE(readiness.negative_test_evidence_present == 1u, "negative test");
    EXPECT_TRUE(readiness.memory_safety_evidence_present == 1u, "memory safety");
    EXPECT_TRUE(readiness.api_misuse_resistance_present == 1u, "api misuse");
    EXPECT_TRUE(readiness.source_digest_manifest_present == 1u, "source digest");
    EXPECT_TRUE(readiness.code_owner_review_present == 1u, "code owner");
    EXPECT_TRUE(readiness.ci_promotion_evidence_present == 1u, "ci promotion");
    EXPECT_TRUE(readiness.constant_time_review_present == 1u, "constant time");
    EXPECT_TRUE(readiness.randomness_source_contract_present == 1u, "randomness");
    EXPECT_TRUE(readiness.zeroization_evidence_present == 1u, "zeroization");
    EXPECT_TRUE(readiness.side_channel_review_present == 1u, "side channel");
    EXPECT_TRUE(readiness.provider_differential_present == 1u, "provider");
    EXPECT_TRUE(readiness.implementation_binding_manifest_present == 1u, "binding");
    EXPECT_TRUE(readiness.implementation_frame_present == 1u, "implementation");
    EXPECT_TRUE(readiness.secret_state_contract_present == 1u, "secret state");
    EXPECT_TRUE(readiness.clean_room_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(readiness.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(readiness.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(readiness.provider_runtime_used == 0u, "provider runtime");
    EXPECT_TRUE(readiness.components_total == 20u, "components total");
    EXPECT_TRUE(readiness.components_present == 20u, "components present");
    EXPECT_TRUE(readiness.runtime_blockers_total == 18u, "runtime blockers");
    EXPECT_TRUE(readiness.required_readiness_items_total == 328u, "readiness total");
    EXPECT_TRUE(readiness.required_readiness_items_satisfied == 158u, "readiness satisfied");
    EXPECT_TRUE(readiness.design_frame_integration_ready == 1u, "design frame");
    EXPECT_TRUE(readiness.runtime_crypto_ready == 0u, "runtime crypto");
    EXPECT_TRUE(readiness.operations_enabled == 0u, "operations");
    EXPECT_TRUE(readiness.key_generation_enabled == 0u, "keygen");
    EXPECT_TRUE(readiness.encapsulation_enabled == 0u, "encaps");
    EXPECT_TRUE(readiness.decapsulation_enabled == 0u, "decaps");
    EXPECT_TRUE(readiness.shared_secret_emitted == 0u, "shared secret");
    EXPECT_TRUE(readiness.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(readiness.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(readiness.runtime_authority_granted == 0u, "authority");
    EXPECT_TRUE(readiness.error == LATTICRA_Q_SEAL_READINESS_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_readiness_is_design_frame_ready(&readiness) == 1,
        "design ready function");
    EXPECT_TRUE(
        latticra_q_seal_readiness_allows_runtime_crypto(&readiness) == 0,
        "runtime function");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL READINESS PROFILE") != 0, "header");
    EXPECT_TRUE(strstr(rendered, "components_present=20") != 0, "components report");
    EXPECT_TRUE(strstr(rendered, "negative_test_evidence_present=1") != 0, "negative report");
    EXPECT_TRUE(strstr(rendered, "memory_safety_evidence_present=1") != 0, "memory report");
    EXPECT_TRUE(strstr(rendered, "api_misuse_resistance_present=1") != 0, "api report");
    EXPECT_TRUE(strstr(rendered, "source_digest_manifest_present=1") != 0, "digest report");
    EXPECT_TRUE(strstr(rendered, "code_owner_review_present=1") != 0, "owner report");
    EXPECT_TRUE(strstr(rendered, "ci_promotion_evidence_present=1") != 0, "ci report");
    EXPECT_TRUE(strstr(rendered, "constant_time_review_present=1") != 0, "constant report");
    EXPECT_TRUE(
        strstr(rendered, "randomness_source_contract_present=1") != 0,
        "randomness report");
    EXPECT_TRUE(strstr(rendered, "zeroization_evidence_present=1") != 0, "zeroization report");
    EXPECT_TRUE(strstr(rendered, "side_channel_review_present=1") != 0, "side-channel report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_binding_manifest_present=1") != 0,
        "binding report");
    EXPECT_TRUE(strstr(rendered, "runtime_blockers_total=18") != 0, "blockers report");
    EXPECT_TRUE(
        strstr(rendered, "design_frame_integration_ready=1") != 0,
        "design report");
    EXPECT_TRUE(strstr(rendered, "runtime_crypto_ready=0") != 0, "runtime report");
    EXPECT_TRUE(strstr(rendered, "status=q-seal-readiness-profile-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_readiness_t readiness;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_readiness_prepare(0) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_readiness_is_design_frame_ready(0) == 0, "null design");
    EXPECT_TRUE(latticra_q_seal_readiness_allows_runtime_crypto(0) == 0, "null runtime");
    EXPECT_TRUE(latticra_q_seal_readiness_prepare(&readiness) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report readiness");
    EXPECT_TRUE(
        latticra_q_seal_readiness_report(&readiness, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (readiness_profile_aggregates_fail_closed_state() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal readiness invariants: ok\n");
    return 0;
}
