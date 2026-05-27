#include "latticra/q_seal_ml_kem_implementation_frame.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int implementation_frame_is_no_effect(void) {
    latticra_q_seal_ml_kem_implementation_frame_t frame;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_prepare(&frame) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(frame.implementation_profile, "latticra-q-seal-ml-kem-implementation-frame/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(frame.formal_title, "Latticra Q-Seal ML-KEM Implementation Frame") == 0,
        "title");
    EXPECT_TRUE(strcmp(frame.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(strcmp(frame.implementation_state, "design-frame-only") == 0, "state");
    EXPECT_TRUE(frame.implementation_frame_present == 1u, "present");
    EXPECT_TRUE(frame.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(frame.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(frame.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(frame.parameter_sets_recorded == 1u, "parameters");
    EXPECT_TRUE(frame.module_plan_recorded == 1u, "module plan");
    EXPECT_TRUE(frame.planned_module_count == 9u, "module count");
    EXPECT_TRUE(frame.polynomial_arithmetic_planned == 1u, "poly planned");
    EXPECT_TRUE(frame.ntt_planned == 1u, "ntt planned");
    EXPECT_TRUE(frame.sampling_planned == 1u, "sampling planned");
    EXPECT_TRUE(frame.compression_planned == 1u, "compression planned");
    EXPECT_TRUE(frame.encoding_planned == 1u, "encoding planned");
    EXPECT_TRUE(frame.hash_xof_planned == 1u, "hash planned");
    EXPECT_TRUE(frame.keygen_planned == 1u, "keygen planned");
    EXPECT_TRUE(frame.encaps_planned == 1u, "encaps planned");
    EXPECT_TRUE(frame.decaps_planned == 1u, "decaps planned");
    EXPECT_TRUE(frame.implementation_code_present == 0u, "implementation");
    EXPECT_TRUE(frame.polynomial_arithmetic_implemented == 0u, "poly implemented");
    EXPECT_TRUE(frame.ntt_implemented == 0u, "ntt implemented");
    EXPECT_TRUE(frame.sampling_implemented == 0u, "sampling implemented");
    EXPECT_TRUE(frame.compression_implemented == 0u, "compression implemented");
    EXPECT_TRUE(frame.encoding_implemented == 0u, "encoding implemented");
    EXPECT_TRUE(frame.hash_xof_implemented == 0u, "hash implemented");
    EXPECT_TRUE(frame.keygen_implemented == 0u, "keygen implemented");
    EXPECT_TRUE(frame.encaps_implemented == 0u, "encaps implemented");
    EXPECT_TRUE(frame.decaps_implemented == 0u, "decaps implemented");
    EXPECT_TRUE(frame.constant_time_design_required == 1u, "ct required");
    EXPECT_TRUE(frame.constant_time_design_recorded == 0u, "ct recorded");
    EXPECT_TRUE(frame.secret_branch_review_required == 1u, "branch required");
    EXPECT_TRUE(frame.secret_branch_review_recorded == 0u, "branch recorded");
    EXPECT_TRUE(frame.secret_memory_review_required == 1u, "memory required");
    EXPECT_TRUE(frame.secret_memory_review_recorded == 0u, "memory recorded");
    EXPECT_TRUE(frame.zeroization_design_required == 1u, "zeroization required");
    EXPECT_TRUE(frame.zeroization_design_recorded == 0u, "zeroization recorded");
    EXPECT_TRUE(frame.randomness_design_required == 1u, "randomness required");
    EXPECT_TRUE(frame.randomness_design_recorded == 0u, "randomness recorded");
    EXPECT_TRUE(frame.serialization_canonicality_required == 1u, "serialization required");
    EXPECT_TRUE(frame.serialization_canonicality_recorded == 0u, "serialization recorded");
    EXPECT_TRUE(frame.malformed_input_policy_required == 1u, "malformed required");
    EXPECT_TRUE(frame.malformed_input_policy_recorded == 0u, "malformed recorded");
    EXPECT_TRUE(frame.test_vector_binding_required == 1u, "vector required");
    EXPECT_TRUE(frame.test_vector_binding_recorded == 0u, "vector recorded");
    EXPECT_TRUE(frame.formal_review_required == 1u, "formal required");
    EXPECT_TRUE(frame.formal_review_recorded == 0u, "formal recorded");
    EXPECT_TRUE(frame.operations_enabled == 0u, "operations");
    EXPECT_TRUE(frame.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(frame.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(frame.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(frame.required_design_items_total == 12u, "total");
    EXPECT_TRUE(frame.required_design_items_satisfied == 3u, "satisfied");
    EXPECT_TRUE(frame.error == LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_is_no_effect(&frame) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_allows_implementation(&frame) == 0,
        "allows implementation");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_report(&frame, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION FRAME") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "implementation_code_present=0") != 0, "report implementation");
    EXPECT_TRUE(strstr(rendered, "constant_time_design_recorded=0") != 0, "report ct");
    EXPECT_TRUE(strstr(rendered, "operations_enabled=0") != 0, "report operations");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-implementation-frame-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_frame_t frame;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_implementation_frame_is_no_effect(0) == 0, "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_allows_implementation(0) == 0,
        "null allows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_prepare(&frame) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_report(&frame, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report frame");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_frame_report(&frame, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (implementation_frame_is_no_effect() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem implementation frame invariants: ok\n");
    return 0;
}
