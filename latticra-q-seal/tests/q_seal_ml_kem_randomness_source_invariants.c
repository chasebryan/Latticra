#include "latticra/q_seal_ml_kem_randomness_source.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int randomness_source_records_policy_without_random_generation(void) {
    latticra_q_seal_ml_kem_randomness_source_t source;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_prepare(&source) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(source.randomness_profile, "latticra-q-seal-ml-kem-randomness-source/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(source.formal_title, "Latticra Q-Seal ML-KEM Randomness Source Contract") == 0,
        "title");
    EXPECT_TRUE(strcmp(source.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(
        strcmp(source.random_bit_generation_source, "NIST-SP-800-90A-and-NIST-SP-800-90B") == 0,
        "rbg standards");
    EXPECT_TRUE(
        strcmp(source.randomness_scope, "ML-KEM-keygen-encapsulation-seed-material") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(source.randomness_state, "policy-recorded-random-bit-generation-blocked") == 0,
        "state");
    EXPECT_TRUE(source.randomness_source_contract_present == 1u, "present");
    EXPECT_TRUE(source.fips_203_source_verified == 1u, "fips");
    EXPECT_TRUE(source.sp_800_90a_tracked == 1u, "90a");
    EXPECT_TRUE(source.sp_800_90b_tracked == 1u, "90b");
    EXPECT_TRUE(source.keygen_seed_material_required == 1u, "keygen seed");
    EXPECT_TRUE(source.encapsulation_seed_material_required == 1u, "encapsulation seed");
    EXPECT_TRUE(source.deterministic_test_seed_separation_required == 1u, "test separation");
    EXPECT_TRUE(source.entropy_source_inventory_recorded == 0u, "entropy inventory");
    EXPECT_TRUE(source.entropy_source_validation_recorded == 0u, "entropy validation");
    EXPECT_TRUE(source.drbg_selection_recorded == 0u, "drbg");
    EXPECT_TRUE(source.drbg_security_strength_recorded == 0u, "strength");
    EXPECT_TRUE(source.seed_derivation_policy_recorded == 0u, "seed derivation");
    EXPECT_TRUE(source.reseed_policy_recorded == 0u, "reseed");
    EXPECT_TRUE(source.prediction_resistance_policy_recorded == 0u, "prediction");
    EXPECT_TRUE(source.health_tests_policy_recorded == 0u, "health");
    EXPECT_TRUE(source.failure_mode_policy_recorded == 0u, "failure");
    EXPECT_TRUE(source.platform_rng_boundary_recorded == 0u, "platform");
    EXPECT_TRUE(source.entropy_review_signoff_recorded == 0u, "signoff");
    EXPECT_TRUE(source.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(source.random_bytes_generated == 0u, "random bytes");
    EXPECT_TRUE(source.deterministic_test_seed_loaded == 0u, "test seed");
    EXPECT_TRUE(source.deterministic_rng_mode_enabled == 0u, "deterministic");
    EXPECT_TRUE(source.random_bit_generation_allowed == 0u, "generation");
    EXPECT_TRUE(source.key_generation_randomness_allowed == 0u, "keygen randomness");
    EXPECT_TRUE(source.encapsulation_randomness_allowed == 0u, "encapsulation randomness");
    EXPECT_TRUE(source.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(source.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(source.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(source.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(source.required_randomness_items_total == 18u, "total");
    EXPECT_TRUE(source.required_randomness_items_satisfied == 6u, "satisfied");
    EXPECT_TRUE(source.error == LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_is_policy_only(&source) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_allows_random_generation(&source) == 0,
        "allows random generation");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_report(&source, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM RANDOMNESS SOURCE CONTRACT") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "randomness_source_contract_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "sp_800_90a_tracked=1") != 0, "90a report");
    EXPECT_TRUE(strstr(rendered, "random_bytes_generated=0") != 0, "bytes report");
    EXPECT_TRUE(strstr(rendered, "random_bit_generation_allowed=0") != 0, "generation report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-randomness-source-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_randomness_source_t source;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_randomness_source_is_policy_only(0) == 0, "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_allows_random_generation(0) == 0,
        "null generation");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_prepare(&source) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_report(&source, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report source");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_randomness_source_report(&source, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (randomness_source_records_policy_without_random_generation() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem randomness source invariants: ok\n");
    return 0;
}
