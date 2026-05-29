#include "latticra/q_seal.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_q_seal_foundation_error_label(
    latticra_q_seal_foundation_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_FOUNDATION_OK:
        return "ok";
    case LATTICRA_Q_SEAL_FOUNDATION_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_foundation_prepare(
    latticra_q_seal_foundation_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Q-Seal");
    copy_literal(out->subsystem_directory, sizeof(out->subsystem_directory), "latticra-q-seal");
    copy_literal(out->q_seal_profile, sizeof(out->q_seal_profile), "latticra-q-seal-foundation/0.1");
    copy_literal(out->clean_room_profile, sizeof(out->clean_room_profile), "latticra-clean-room-pqc/0.1");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(out->implementation_lane, sizeof(out->implementation_lane), "standards-first-no-effect");
    out->latticra_q_seal_present = 1u;
    out->nist_fips_203_ml_kem_tracked = 1u;
    out->nist_fips_204_ml_dsa_tracked = 1u;
    out->nist_fips_205_slh_dsa_backup_tracked = 1u;
    out->ml_kem_work_packet_next = 1u;
    out->ml_dsa_work_packet_planned = 1u;
    out->liboqs_comparison_provider_allowed = 1u;
    out->apple_corecrypto_reference_allowed = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->apple_corecrypto_proof_artifacts_copied = 0u;
    out->provider_linked = 0u;
    out->provider_runtime_used = 0u;
    out->key_generation_performed = 0u;
    out->key_storage_performed = 0u;
    out->encapsulation_performed = 0u;
    out->decapsulation_performed = 0u;
    out->signing_performed = 0u;
    out->verification_performed = 0u;
    out->encryption_performed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->post_quantum_migration_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->foundation_state, sizeof(out->foundation_state), "prepared-clean-room-foundation");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "crypto-operations-not-implemented");
    out->error = LATTICRA_Q_SEAL_FOUNDATION_OK;
    copy_literal(out->status, sizeof(out->status), "q-seal-foundation-prepared");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_foundation_is_clean_room(
    const latticra_q_seal_foundation_t *foundation) {
    if (foundation == NULL) {
        return 0;
    }

    return foundation->latticra_q_seal_present == 1u &&
           foundation->apple_corecrypto_reference_allowed == 1u &&
           foundation->apple_corecrypto_code_copied == 0u &&
           foundation->apple_corecrypto_proof_artifacts_copied == 0u &&
           strcmp(foundation->source_boundary, "clean-room-no-apple-code") == 0;
}

int latticra_q_seal_foundation_is_authority_neutral(
    const latticra_q_seal_foundation_t *foundation) {
    if (foundation == NULL) {
        return 0;
    }

    return foundation->provider_linked == 0u &&
           foundation->provider_runtime_used == 0u &&
           foundation->key_generation_performed == 0u &&
           foundation->key_storage_performed == 0u &&
           foundation->encapsulation_performed == 0u &&
           foundation->decapsulation_performed == 0u &&
           foundation->signing_performed == 0u &&
           foundation->verification_performed == 0u &&
           foundation->encryption_performed == 0u &&
           foundation->production_crypto_claim_allowed == 0u &&
           foundation->fips_claim_allowed == 0u &&
           foundation->post_quantum_migration_claim_allowed == 0u &&
           foundation->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_foundation_report(
    const latticra_q_seal_foundation_t *foundation,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (foundation == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL FOUNDATION\n"
        "formal_title=%s\n"
        "subsystem_directory=%s\n"
        "q_seal_profile=%s\n"
        "clean_room_profile=%s\n"
        "source_boundary=%s\n"
        "implementation_lane=%s\n"
        "latticra_q_seal_present=%u\n"
        "nist_fips_203_ml_kem_tracked=%u\n"
        "nist_fips_204_ml_dsa_tracked=%u\n"
        "nist_fips_205_slh_dsa_backup_tracked=%u\n"
        "ml_kem_work_packet_next=%u\n"
        "ml_dsa_work_packet_planned=%u\n"
        "liboqs_comparison_provider_allowed=%u\n"
        "apple_corecrypto_reference_allowed=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "apple_corecrypto_proof_artifacts_copied=%u\n"
        "provider_linked=%u\n"
        "provider_runtime_used=%u\n"
        "key_generation_performed=%u\n"
        "key_storage_performed=%u\n"
        "encapsulation_performed=%u\n"
        "decapsulation_performed=%u\n"
        "signing_performed=%u\n"
        "verification_performed=%u\n"
        "encryption_performed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "foundation_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        foundation->formal_title,
        foundation->subsystem_directory,
        foundation->q_seal_profile,
        foundation->clean_room_profile,
        foundation->source_boundary,
        foundation->implementation_lane,
        foundation->latticra_q_seal_present,
        foundation->nist_fips_203_ml_kem_tracked,
        foundation->nist_fips_204_ml_dsa_tracked,
        foundation->nist_fips_205_slh_dsa_backup_tracked,
        foundation->ml_kem_work_packet_next,
        foundation->ml_dsa_work_packet_planned,
        foundation->liboqs_comparison_provider_allowed,
        foundation->apple_corecrypto_reference_allowed,
        foundation->apple_corecrypto_code_copied,
        foundation->apple_corecrypto_proof_artifacts_copied,
        foundation->provider_linked,
        foundation->provider_runtime_used,
        foundation->key_generation_performed,
        foundation->key_storage_performed,
        foundation->encapsulation_performed,
        foundation->decapsulation_performed,
        foundation->signing_performed,
        foundation->verification_performed,
        foundation->encryption_performed,
        foundation->production_crypto_claim_allowed,
        foundation->fips_claim_allowed,
        foundation->post_quantum_migration_claim_allowed,
        foundation->runtime_authority_granted,
        foundation->foundation_state,
        foundation->blocked_reason,
        latticra_q_seal_foundation_error_label(foundation->error),
        foundation->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
