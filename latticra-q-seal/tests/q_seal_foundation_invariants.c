#include "latticra/q_seal.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int foundation_prepares_clean_room_subsystem(void) {
    latticra_q_seal_foundation_t foundation;
    char rendered[LATTICRA_Q_SEAL_REPORT_MAX];

    EXPECT_TRUE(latticra_q_seal_foundation_prepare(&foundation) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(foundation.error == LATTICRA_Q_SEAL_FOUNDATION_OK, "error ok");
    EXPECT_TRUE(strcmp(foundation.formal_title, "Latticra Q-Seal") == 0, "formal title");
    EXPECT_TRUE(strcmp(foundation.subsystem_directory, "latticra-q-seal") == 0, "subsystem directory");
    EXPECT_TRUE(strcmp(foundation.q_seal_profile, "latticra-q-seal-foundation/0.1") == 0, "profile");
    EXPECT_TRUE(strcmp(foundation.clean_room_profile, "latticra-clean-room-pqc/0.1") == 0, "clean profile");
    EXPECT_TRUE(strcmp(foundation.source_boundary, "clean-room-no-apple-code") == 0, "source boundary");
    EXPECT_TRUE(strcmp(foundation.implementation_lane, "standards-first-no-effect") == 0, "lane");
    EXPECT_TRUE(foundation.latticra_q_seal_present == 1u, "present");
    EXPECT_TRUE(foundation.nist_fips_203_ml_kem_tracked == 1u, "fips 203");
    EXPECT_TRUE(foundation.nist_fips_204_ml_dsa_tracked == 1u, "fips 204");
    EXPECT_TRUE(foundation.nist_fips_205_slh_dsa_backup_tracked == 1u, "fips 205");
    EXPECT_TRUE(foundation.ml_kem_work_packet_next == 1u, "ml-kem next");
    EXPECT_TRUE(foundation.ml_dsa_work_packet_planned == 1u, "ml-dsa planned");
    EXPECT_TRUE(foundation.liboqs_comparison_provider_allowed == 1u, "liboqs compare");
    EXPECT_TRUE(foundation.apple_corecrypto_reference_allowed == 1u, "apple reference");
    EXPECT_TRUE(foundation.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(foundation.apple_corecrypto_proof_artifacts_copied == 0u, "apple proof artifacts");
    EXPECT_TRUE(foundation.provider_linked == 0u, "provider linked");
    EXPECT_TRUE(foundation.provider_runtime_used == 0u, "provider runtime");
    EXPECT_TRUE(foundation.key_generation_performed == 0u, "keygen");
    EXPECT_TRUE(foundation.key_storage_performed == 0u, "storage");
    EXPECT_TRUE(foundation.encapsulation_performed == 0u, "encapsulation");
    EXPECT_TRUE(foundation.decapsulation_performed == 0u, "decapsulation");
    EXPECT_TRUE(foundation.signing_performed == 0u, "signing");
    EXPECT_TRUE(foundation.verification_performed == 0u, "verification");
    EXPECT_TRUE(foundation.encryption_performed == 0u, "encryption");
    EXPECT_TRUE(foundation.production_crypto_claim_allowed == 0u, "production claim");
    EXPECT_TRUE(foundation.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(foundation.post_quantum_migration_claim_allowed == 0u, "migration claim");
    EXPECT_TRUE(foundation.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(foundation.foundation_state, "prepared-clean-room-foundation") == 0, "state");
    EXPECT_TRUE(strcmp(foundation.blocked_reason, "crypto-operations-not-implemented") == 0, "blocked reason");
    EXPECT_TRUE(latticra_q_seal_foundation_is_clean_room(&foundation) == 1, "clean room");
    EXPECT_TRUE(latticra_q_seal_foundation_is_authority_neutral(&foundation) == 1, "authority neutral");
    EXPECT_TRUE(
        latticra_q_seal_foundation_report(&foundation, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL FOUNDATION") != 0, "report header");
    EXPECT_TRUE(strstr(rendered, "formal_title=Latticra Q-Seal") != 0, "report title");
    EXPECT_TRUE(strstr(rendered, "subsystem_directory=latticra-q-seal") != 0, "report directory");
    EXPECT_TRUE(strstr(rendered, "apple_corecrypto_code_copied=0") != 0, "report apple");
    EXPECT_TRUE(strstr(rendered, "key_generation_performed=0") != 0, "report keygen");
    return 0;
}

static int null_and_buffer_handling_fails_closed(void) {
    latticra_q_seal_foundation_t foundation;
    char tiny[1];

    EXPECT_TRUE(latticra_q_seal_foundation_prepare(0) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT, "null prepare");
    EXPECT_TRUE(latticra_q_seal_foundation_is_clean_room(0) == 0, "null clean");
    EXPECT_TRUE(latticra_q_seal_foundation_is_authority_neutral(0) == 0, "null neutral");
    EXPECT_TRUE(latticra_q_seal_foundation_prepare(&foundation) == LATTICRA_Q_SEAL_STATUS_OK, "prepare");
    EXPECT_TRUE(
        latticra_q_seal_foundation_report(&foundation, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(
        latticra_q_seal_foundation_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report foundation");
    EXPECT_TRUE(
        latticra_q_seal_foundation_report(&foundation, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (foundation_prepares_clean_room_subsystem() != 0) {
        return 1;
    }
    if (null_and_buffer_handling_fails_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal foundation invariants: ok\n");
    return 0;
}
