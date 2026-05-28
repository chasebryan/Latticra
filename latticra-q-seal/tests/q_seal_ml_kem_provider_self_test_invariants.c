#include "latticra/q_seal_ml_kem_provider_self_test.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int expect_provider_self_test(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    const char *name,
    unsigned security_category,
    unsigned ciphertext_bytes) {
    latticra_q_seal_ml_kem_provider_self_test_t self_test;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_run(parameter_set, &self_test) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "self-test status");
    EXPECT_TRUE(self_test.error == LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_OK, "self-test ok");
    EXPECT_TRUE(
        strcmp(self_test.self_test_profile, "latticra-q-seal-ml-kem-provider-self-test/0.1") == 0,
        "profile");
    EXPECT_TRUE(strcmp(self_test.formal_title, "Latticra Q-Seal ML-KEM Provider Self-Test") == 0, "title");
    EXPECT_TRUE(strcmp(self_test.provider_name, "OpenSSL-EVP") == 0, "provider");
    EXPECT_TRUE(strcmp(self_test.algorithm_name, name) == 0, "algorithm");
    EXPECT_TRUE(strcmp(self_test.standards_source, "NIST-FIPS-203") == 0, "standard");
    EXPECT_TRUE(self_test.parameter_set == (unsigned)parameter_set, "parameter set");
    EXPECT_TRUE(self_test.security_category == security_category, "security category");
    EXPECT_TRUE(self_test.expected_ciphertext_bytes == ciphertext_bytes, "expected ciphertext");
    EXPECT_TRUE(self_test.observed_ciphertext_bytes == ciphertext_bytes, "observed ciphertext");
    EXPECT_TRUE(
        self_test.expected_shared_secret_bytes ==
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES,
        "expected secret bytes");
    EXPECT_TRUE(
        self_test.encapsulated_shared_secret_bytes ==
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES,
        "encaps secret bytes");
    EXPECT_TRUE(
        self_test.decapsulated_shared_secret_bytes ==
            LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_SHARED_SECRET_BYTES,
        "decaps secret bytes");
    EXPECT_TRUE(self_test.provider_linked == 1u, "provider linked");
    EXPECT_TRUE(self_test.provider_available == 1u, "provider available");
    EXPECT_TRUE(self_test.provider_runtime_used == 1u, "provider runtime");
    EXPECT_TRUE(self_test.key_generation_performed == 1u, "keygen performed");
    EXPECT_TRUE(
        self_test.keypair_algorithm_identity_verified == 1u,
        "keypair algorithm identity");
    EXPECT_TRUE(self_test.public_key_reimported == 1u, "public key reimported");
    EXPECT_TRUE(
        self_test.public_key_algorithm_identity_verified == 1u,
        "public key algorithm identity");
    EXPECT_TRUE(self_test.public_key_bytes > 0u, "public key bytes");
    EXPECT_TRUE(self_test.encapsulation_performed == 1u, "encaps performed");
    EXPECT_TRUE(self_test.encapsulation_public_key_only == 1u, "public-only encaps");
    EXPECT_TRUE(self_test.decapsulation_performed == 1u, "decaps performed");
    EXPECT_TRUE(
        self_test.tampered_ciphertext_decapsulation_performed == 1u,
        "tampered decaps performed");
    EXPECT_TRUE(
        self_test.tampered_ciphertext_shared_secret_mismatch == 1u,
        "tampered mismatch");
    EXPECT_TRUE(self_test.tampered_ciphertext_rejected == 1u, "tampered rejected");
    EXPECT_TRUE(self_test.shared_secret_internal_buffers_used == 1u, "secret buffers");
    EXPECT_TRUE(self_test.shared_secret_match == 1u, "secret match");
    EXPECT_TRUE(
        self_test.shared_secret_constant_time_compare == 1u,
        "shared secret constant-time compare");
    EXPECT_TRUE(
        self_test.tampered_ciphertext_constant_time_compare == 1u,
        "tampered constant-time compare");
    EXPECT_TRUE(self_test.shared_secret_zeroized == 1u, "secret zeroized");
    EXPECT_TRUE(self_test.ciphertext_zeroized == 1u, "ciphertext zeroized");
    EXPECT_TRUE(self_test.shared_secret_output_emitted == 0u, "secret not emitted");
    EXPECT_TRUE(self_test.ciphertext_output_emitted == 0u, "ciphertext not emitted");
    EXPECT_TRUE(self_test.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(self_test.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(self_test.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(self_test.operation_state, "provider-self-test-passed") == 0, "state");
    EXPECT_TRUE(strcmp(self_test.blocked_reason, "authority-remains-denied") == 0, "blocked reason");
    EXPECT_TRUE(strcmp(self_test.status, "ml-kem-provider-self-test-passed") == 0, "status");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_is_authority_neutral(&self_test) == 1,
        "authority neutral");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_report(
            &self_test,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL ML-KEM PROVIDER SELF-TEST") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, name) != 0, "report algorithm");
    EXPECT_TRUE(strstr(rendered, "provider_runtime_used=1") != 0, "report provider");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=1") != 0, "report keygen");
    EXPECT_TRUE(
        strstr(rendered, "keypair_algorithm_identity_verified=1") != 0,
        "report keypair algorithm");
    EXPECT_TRUE(strstr(rendered, "public_key_reimported=1") != 0, "report public key");
    EXPECT_TRUE(
        strstr(rendered, "public_key_algorithm_identity_verified=1") != 0,
        "report public key algorithm");
    EXPECT_TRUE(strstr(rendered, "encapsulation_performed=1") != 0, "report encaps");
    EXPECT_TRUE(
        strstr(rendered, "encapsulation_public_key_only=1") != 0,
        "report public-only encaps");
    EXPECT_TRUE(strstr(rendered, "decapsulation_performed=1") != 0, "report decaps");
    EXPECT_TRUE(
        strstr(rendered, "tampered_ciphertext_shared_secret_mismatch=1") != 0,
        "report tampered mismatch");
    EXPECT_TRUE(
        strstr(rendered, "tampered_ciphertext_rejected=1") != 0,
        "report tampered rejected");
    EXPECT_TRUE(strstr(rendered, "shared_secret_match=1") != 0, "report match");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_constant_time_compare=1") != 0,
        "report shared secret constant-time compare");
    EXPECT_TRUE(
        strstr(rendered, "tampered_ciphertext_constant_time_compare=1") != 0,
        "report tampered constant-time compare");
    EXPECT_TRUE(strstr(rendered, "shared_secret_output_emitted=0") != 0, "report no secret");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "report authority");
    return 0;
}

static int all_provider_self_tests_pass(void) {
    EXPECT_TRUE(
        expect_provider_self_test(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512,
            "ML-KEM-512",
            1u,
            768u) == 0,
        "ml-kem-512");
    EXPECT_TRUE(
        expect_provider_self_test(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768,
            "ML-KEM-768",
            3u,
            1088u) == 0,
        "ml-kem-768");
    EXPECT_TRUE(
        expect_provider_self_test(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024,
            "ML-KEM-1024",
            5u,
            1568u) == 0,
        "ml-kem-1024");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_provider_self_test_t self_test;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_run(
            (latticra_q_seal_ml_kem_parameter_set_t)0,
            &self_test) == LATTICRA_Q_SEAL_STATUS_OK,
        "invalid status");
    EXPECT_TRUE(
        self_test.error == LATTICRA_Q_SEAL_ML_KEM_PROVIDER_SELF_TEST_INVALID_PARAMETER_SET,
        "invalid error");
    EXPECT_TRUE(self_test.provider_runtime_used == 0u, "invalid provider runtime");
    EXPECT_TRUE(self_test.key_generation_performed == 0u, "invalid keygen");
    EXPECT_TRUE(self_test.shared_secret_output_emitted == 0u, "invalid secret output");
    EXPECT_TRUE(self_test.runtime_authority_granted == 0u, "invalid runtime");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_run(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512,
            0) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_is_authority_neutral(0) == 0,
        "null helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_report(
            &self_test,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report self-test");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_self_test_report(&self_test, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (all_provider_self_tests_pass() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem provider self-test invariants: ok\n");
    return 0;
}
