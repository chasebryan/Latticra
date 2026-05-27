#include "latticra/q_seal_ml_kem_implementation_binding_manifest.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int implementation_binding_manifest_is_clean_room_no_effect(void) {
    latticra_q_seal_ml_kem_implementation_binding_manifest_t manifest;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_BINDING_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            manifest.binding_profile,
            "latticra-q-seal-ml-kem-implementation-binding-manifest/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            manifest.formal_title,
            "Latticra Q-Seal ML-KEM Implementation Binding Manifest") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(manifest.standards_basis, "NIST-FIPS-203-and-SP-800-227") == 0,
        "standards");
    EXPECT_TRUE(strcmp(manifest.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(
        strcmp(manifest.binding_state, "implementation-binding-blocked") == 0,
        "state");
    EXPECT_TRUE(manifest.implementation_binding_manifest_present == 1u, "present");
    EXPECT_TRUE(manifest.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(manifest.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(manifest.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(manifest.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(manifest.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(manifest.fips_203_algorithm_bound == 1u, "fips203");
    EXPECT_TRUE(manifest.sp_800_227_kem_usage_bound == 1u, "sp800227");
    EXPECT_TRUE(manifest.kat_manifest_bound == 1u, "kat");
    EXPECT_TRUE(manifest.acvp_intake_bound == 1u, "acvp");
    EXPECT_TRUE(manifest.vector_schema_bound == 1u, "schema");
    EXPECT_TRUE(manifest.vector_source_bound == 1u, "source");
    EXPECT_TRUE(manifest.negative_test_evidence_bound == 1u, "negative");
    EXPECT_TRUE(manifest.memory_safety_evidence_bound == 1u, "memory");
    EXPECT_TRUE(manifest.api_misuse_resistance_bound == 1u, "api");
    EXPECT_TRUE(manifest.constant_time_review_bound == 1u, "constant");
    EXPECT_TRUE(manifest.randomness_source_bound == 1u, "randomness");
    EXPECT_TRUE(manifest.zeroization_evidence_bound == 1u, "zeroization");
    EXPECT_TRUE(manifest.side_channel_review_bound == 1u, "side channel");
    EXPECT_TRUE(manifest.provider_differential_bound == 1u, "provider differential");
    EXPECT_TRUE(manifest.secret_state_contract_bound == 1u, "secret state");
    EXPECT_TRUE(manifest.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(manifest.module_to_gate_matrix_recorded == 1u, "matrix");
    EXPECT_TRUE(manifest.implementation_files_created == 0u, "files");
    EXPECT_TRUE(manifest.implementation_code_present == 0u, "code");
    EXPECT_TRUE(manifest.primitive_operations_bound == 0u, "primitive");
    EXPECT_TRUE(manifest.keygen_binding_approved == 0u, "keygen");
    EXPECT_TRUE(manifest.encaps_binding_approved == 0u, "encaps");
    EXPECT_TRUE(manifest.decaps_binding_approved == 0u, "decaps");
    EXPECT_TRUE(manifest.implementation_file_digest_manifest_recorded == 0u, "digest");
    EXPECT_TRUE(manifest.code_owner_review_recorded == 0u, "code owner");
    EXPECT_TRUE(manifest.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(manifest.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(manifest.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(manifest.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(manifest.required_binding_items_total == 26u, "total");
    EXPECT_TRUE(manifest.required_binding_items_satisfied == 21u, "satisfied");
    EXPECT_TRUE(manifest.error == LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_is_clean_room_no_effect(
            &manifest) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(
            &manifest) == 0,
        "allows implementation");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_report(
            &manifest,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION BINDING MANIFEST") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "implementation_binding_manifest_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "planned_source_units_count=9") != 0, "source report");
    EXPECT_TRUE(
        strstr(rendered, "implementation_code_present=0") != 0,
        "code report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-implementation-binding-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_implementation_binding_manifest_t manifest;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_is_clean_room_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(0) == 0,
        "null implementation");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_report(
            &manifest,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report manifest");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_implementation_binding_manifest_report(
            &manifest,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (implementation_binding_manifest_is_clean_room_no_effect() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem implementation binding manifest invariants: ok\n");
    return 0;
}
