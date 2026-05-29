#include "latticra/q_seal_ml_kem.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int expect_parameters(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set,
    const char *name,
    unsigned security_category,
    unsigned k,
    unsigned eta1,
    unsigned eta2,
    unsigned du,
    unsigned dv,
    unsigned rbg_strength,
    unsigned encapsulation_key_bytes,
    unsigned decapsulation_key_bytes,
    unsigned ciphertext_bytes) {
    latticra_q_seal_ml_kem_parameters_t parameters;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) == LATTICRA_Q_SEAL_STATUS_OK,
        "parameter status");
    EXPECT_TRUE(parameters.error == LATTICRA_Q_SEAL_ML_KEM_OK, "parameter ok");
    EXPECT_TRUE(strcmp(parameters.ml_kem_profile, "latticra-q-seal-ml-kem/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(parameters.formal_title, "Latticra Q-Seal ML-KEM") == 0, "formal title");
    EXPECT_TRUE(strcmp(parameters.parameter_set_name, name) == 0, "parameter name");
    EXPECT_TRUE(strcmp(parameters.standards_source, "NIST-FIPS-203") == 0, "standards source");
    EXPECT_TRUE(parameters.parameter_set == (unsigned)parameter_set, "parameter value");
    EXPECT_TRUE(parameters.security_category == security_category, "security category");
    EXPECT_TRUE(parameters.n == 256u, "n");
    EXPECT_TRUE(parameters.q == 3329u, "q");
    EXPECT_TRUE(parameters.k == k, "k");
    EXPECT_TRUE(parameters.eta1 == eta1, "eta1");
    EXPECT_TRUE(parameters.eta2 == eta2, "eta2");
    EXPECT_TRUE(parameters.du == du, "du");
    EXPECT_TRUE(parameters.dv == dv, "dv");
    EXPECT_TRUE(parameters.required_rbg_strength_bits == rbg_strength, "rbg");
    EXPECT_TRUE(parameters.encapsulation_key_bytes == encapsulation_key_bytes, "ek bytes");
    EXPECT_TRUE(parameters.decapsulation_key_bytes == decapsulation_key_bytes, "dk bytes");
    EXPECT_TRUE(parameters.ciphertext_bytes == ciphertext_bytes, "ciphertext bytes");
    EXPECT_TRUE(parameters.shared_secret_key_bytes == 32u, "shared secret bytes");
    EXPECT_TRUE(parameters.fips_203_parameter_set_tracked == 1u, "fips 203");
    EXPECT_TRUE(parameters.known_answer_tests_required == 1u, "kat");
    EXPECT_TRUE(parameters.acvp_vector_review_required == 1u, "acvp");
    EXPECT_TRUE(parameters.clean_room_required == 1u, "clean room");
    EXPECT_TRUE(parameters.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(parameters.provider_linked == 0u, "provider linked");
    EXPECT_TRUE(parameters.key_generation_enabled == 0u, "keygen enabled");
    EXPECT_TRUE(parameters.encapsulation_enabled == 0u, "encaps enabled");
    EXPECT_TRUE(parameters.decapsulation_enabled == 0u, "decaps enabled");
    EXPECT_TRUE(parameters.key_generation_performed == 0u, "keygen performed");
    EXPECT_TRUE(parameters.encapsulation_performed == 0u, "encaps performed");
    EXPECT_TRUE(parameters.decapsulation_performed == 0u, "decaps performed");
    EXPECT_TRUE(parameters.shared_secret_emitted == 0u, "shared secret emitted");
    EXPECT_TRUE(parameters.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(parameters.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(parameters.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(parameters.operation_state, "operations-disabled") == 0, "operation state");
    EXPECT_TRUE(
        strcmp(parameters.blocked_reason, "clean-room-implementation-not-present") == 0,
        "blocked reason");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters_are_authority_neutral(&parameters) == 1,
        "authority neutral");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_keygen_disabled(&parameters) ==
            LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED,
        "keygen disabled");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_encaps_disabled(&parameters) ==
            LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED,
        "encaps disabled");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_decaps_disabled(&parameters) ==
            LATTICRA_Q_SEAL_ML_KEM_OPERATION_DISABLED,
        "decaps disabled");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters_report(&parameters, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL ML-KEM PARAMETERS") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, name) != 0, "report parameter name");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=0") != 0, "report keygen");
    EXPECT_TRUE(strstr(rendered, "shared_secret_emitted=0") != 0, "report shared secret");
    return 0;
}

static int all_fips_203_parameter_sets_are_recorded(void) {
    EXPECT_TRUE(
        expect_parameters(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512,
            "ML-KEM-512",
            1u,
            2u,
            3u,
            2u,
            10u,
            4u,
            128u,
            800u,
            1632u,
            768u) == 0,
        "ml-kem-512");
    EXPECT_TRUE(
        expect_parameters(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768,
            "ML-KEM-768",
            3u,
            3u,
            2u,
            2u,
            10u,
            4u,
            192u,
            1184u,
            2400u,
            1088u) == 0,
        "ml-kem-768");
    EXPECT_TRUE(
        expect_parameters(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024,
            "ML-KEM-1024",
            5u,
            4u,
            2u,
            2u,
            11u,
            5u,
            256u,
            1568u,
            3168u,
            1568u) == 0,
        "ml-kem-1024");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_parameters_t parameters;
    char tiny[1];

    EXPECT_TRUE(latticra_q_seal_ml_kem_parameter_set_label(0) != 0, "unknown label nonnull");
    EXPECT_TRUE(
        strcmp(latticra_q_seal_ml_kem_parameter_set_label(0), "unknown") == 0,
        "unknown label");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters(0, &parameters) == LATTICRA_Q_SEAL_STATUS_OK,
        "invalid status");
    EXPECT_TRUE(parameters.error == LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET, "invalid error");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_keygen_disabled(&parameters) ==
            LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET,
        "invalid keygen disabled");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512,
            0) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null output");
    EXPECT_TRUE(latticra_q_seal_ml_kem_parameters_are_authority_neutral(0) == 0, "null neutral");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_keygen_disabled(0) == LATTICRA_Q_SEAL_ML_KEM_INVALID_PARAMETER_SET,
        "null keygen");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters(
            LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512,
            &parameters) == LATTICRA_Q_SEAL_STATUS_OK,
        "valid status");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters_report(&parameters, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report parameters");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_parameters_report(&parameters, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (all_fips_203_parameter_sets_are_recorded() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem parameters invariants: ok\n");
    return 0;
}
