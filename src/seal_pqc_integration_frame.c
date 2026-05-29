#include "latticra/seal_pqc_integration_frame.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_pqc_integration_frame_error_label(
    latticra_seal_pqc_integration_frame_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK:
        return "ok";
    case LATTICRA_SEAL_PQC_INTEGRATION_FRAME_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_PQC_INTEGRATION_FRAME_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

static void frame_init(latticra_seal_pqc_integration_frame_t *frame) {
    memset(frame, 0, sizeof(*frame));
    copy_literal(
        frame->pqc_integration_profile,
        sizeof(frame->pqc_integration_profile),
        "latticra-seal-pqc-integration-frame/0.1");
    copy_literal(frame->research_date, sizeof(frame->research_date), "2026-05-27");
    copy_literal(
        frame->apple_corecrypto_source,
        sizeof(frame->apple_corecrypto_source),
        "github.com/apple/corecrypto@2026-05");
    copy_literal(
        frame->apple_corecrypto_license,
        sizeof(frame->apple_corecrypto_license),
        "evaluation-only-no-redistribution");
    copy_literal(frame->candidate_provider, sizeof(frame->candidate_provider), "liboqs");
    copy_literal(
        frame->candidate_provider_source,
        sizeof(frame->candidate_provider_source),
        "github.com/open-quantum-safe/liboqs");
    copy_literal(
        frame->candidate_provider_license,
        sizeof(frame->candidate_provider_license),
        "MIT-with-third-party-notice-review");
    frame->apple_corecrypto_ml_kem_published = 1u;
    frame->apple_corecrypto_ml_dsa_published = 1u;
    frame->apple_corecrypto_formal_verification_published = 1u;
    frame->apple_corecrypto_reference_allowed = 1u;
    frame->apple_corecrypto_embedding_allowed = 0u;
    frame->apple_corecrypto_redistribution_allowed = 0u;
    frame->nist_fips_203_ml_kem_tracked = 1u;
    frame->nist_fips_204_ml_dsa_tracked = 1u;
    frame->nist_fips_205_slh_dsa_backup_tracked = 1u;
    frame->ml_kem_key_establishment_planned = 1u;
    frame->ml_dsa_signature_planned = 1u;
    frame->hybrid_classical_pqc_transition_required = 1u;
    frame->liboqs_candidate_tracked = 1u;
    frame->liboqs_mit_license_tracked = 1u;
    frame->liboqs_prototype_only_warning_tracked = 1u;
    frame->candidate_provider_production_use_allowed = 0u;
    frame->cryptographic_module_boundary_required = 1u;
    frame->algorithm_parameter_inventory_required = 1u;
    frame->known_answer_tests_required = 1u;
    frame->cavp_acvp_vector_review_required = 1u;
    frame->constant_time_review_required = 1u;
    frame->side_channel_review_required = 1u;
    frame->fips_140_3_claim_gate_required = 1u;
    frame->sp_800_57_key_management_required = 1u;
    frame->source_notice_review_required = 1u;
    frame->third_party_code_vendored = 0u;
    frame->cryptographic_behavior_changed = 0u;
    frame->post_quantum_migration_claim_allowed = 0u;
    frame->production_crypto_claim_allowed = 0u;
    frame->fips_claim_allowed = 0u;
    frame->key_generation_allowed = 0u;
    frame->key_storage_allowed = 0u;
    frame->encryption_performed = 0u;
    frame->signing_performed = 0u;
    frame->network_lookup_allowed = 0u;
    frame->runtime_authority_granted = 0u;
    copy_literal(frame->frame_state, sizeof(frame->frame_state), "prepared-authority-neutral");
    copy_literal(
        frame->blocked_reason,
        sizeof(frame->blocked_reason),
        "license-validation-and-provider-review-required");
    frame->error = LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK;
    copy_literal(frame->status, sizeof(frame->status), "pqc-integration-frame-prepared");
}

latticra_status_t latticra_seal_pqc_integration_frame_prepare(
    latticra_seal_pqc_integration_frame_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    frame_init(out);
    return LATTICRA_STATUS_OK;
}

int latticra_seal_pqc_integration_frame_is_authority_neutral(
    const latticra_seal_pqc_integration_frame_t *frame) {
    if (frame == NULL) {
        return 0;
    }

    return frame->apple_corecrypto_embedding_allowed == 0u &&
           frame->apple_corecrypto_redistribution_allowed == 0u &&
           frame->candidate_provider_production_use_allowed == 0u &&
           frame->third_party_code_vendored == 0u &&
           frame->cryptographic_behavior_changed == 0u &&
           frame->post_quantum_migration_claim_allowed == 0u &&
           frame->production_crypto_claim_allowed == 0u &&
           frame->fips_claim_allowed == 0u &&
           frame->key_generation_allowed == 0u &&
           frame->key_storage_allowed == 0u &&
           frame->encryption_performed == 0u &&
           frame->signing_performed == 0u &&
           frame->network_lookup_allowed == 0u &&
           frame->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_pqc_integration_frame_report(
    const latticra_seal_pqc_integration_frame_t *frame,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (frame == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL PQC INTEGRATION FRAME\n"
        "pqc_integration_profile=%s\n"
        "research_date=%s\n"
        "apple_corecrypto_source=%s\n"
        "apple_corecrypto_license=%s\n"
        "candidate_provider=%s\n"
        "candidate_provider_source=%s\n"
        "candidate_provider_license=%s\n"
        "apple_corecrypto_ml_kem_published=%u\n"
        "apple_corecrypto_ml_dsa_published=%u\n"
        "apple_corecrypto_formal_verification_published=%u\n"
        "apple_corecrypto_reference_allowed=%u\n"
        "apple_corecrypto_embedding_allowed=%u\n"
        "apple_corecrypto_redistribution_allowed=%u\n"
        "nist_fips_203_ml_kem_tracked=%u\n"
        "nist_fips_204_ml_dsa_tracked=%u\n"
        "nist_fips_205_slh_dsa_backup_tracked=%u\n"
        "ml_kem_key_establishment_planned=%u\n"
        "ml_dsa_signature_planned=%u\n"
        "hybrid_classical_pqc_transition_required=%u\n"
        "liboqs_candidate_tracked=%u\n"
        "liboqs_mit_license_tracked=%u\n"
        "liboqs_prototype_only_warning_tracked=%u\n"
        "candidate_provider_production_use_allowed=%u\n"
        "cryptographic_module_boundary_required=%u\n"
        "algorithm_parameter_inventory_required=%u\n"
        "known_answer_tests_required=%u\n"
        "cavp_acvp_vector_review_required=%u\n"
        "constant_time_review_required=%u\n"
        "side_channel_review_required=%u\n"
        "fips_140_3_claim_gate_required=%u\n"
        "sp_800_57_key_management_required=%u\n"
        "source_notice_review_required=%u\n"
        "third_party_code_vendored=%u\n"
        "cryptographic_behavior_changed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "key_generation_allowed=%u\n"
        "key_storage_allowed=%u\n"
        "encryption_performed=%u\n"
        "signing_performed=%u\n"
        "network_lookup_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "frame_state=%s\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        frame->pqc_integration_profile,
        frame->research_date,
        frame->apple_corecrypto_source,
        frame->apple_corecrypto_license,
        frame->candidate_provider,
        frame->candidate_provider_source,
        frame->candidate_provider_license,
        frame->apple_corecrypto_ml_kem_published,
        frame->apple_corecrypto_ml_dsa_published,
        frame->apple_corecrypto_formal_verification_published,
        frame->apple_corecrypto_reference_allowed,
        frame->apple_corecrypto_embedding_allowed,
        frame->apple_corecrypto_redistribution_allowed,
        frame->nist_fips_203_ml_kem_tracked,
        frame->nist_fips_204_ml_dsa_tracked,
        frame->nist_fips_205_slh_dsa_backup_tracked,
        frame->ml_kem_key_establishment_planned,
        frame->ml_dsa_signature_planned,
        frame->hybrid_classical_pqc_transition_required,
        frame->liboqs_candidate_tracked,
        frame->liboqs_mit_license_tracked,
        frame->liboqs_prototype_only_warning_tracked,
        frame->candidate_provider_production_use_allowed,
        frame->cryptographic_module_boundary_required,
        frame->algorithm_parameter_inventory_required,
        frame->known_answer_tests_required,
        frame->cavp_acvp_vector_review_required,
        frame->constant_time_review_required,
        frame->side_channel_review_required,
        frame->fips_140_3_claim_gate_required,
        frame->sp_800_57_key_management_required,
        frame->source_notice_review_required,
        frame->third_party_code_vendored,
        frame->cryptographic_behavior_changed,
        frame->post_quantum_migration_claim_allowed,
        frame->production_crypto_claim_allowed,
        frame->fips_claim_allowed,
        frame->key_generation_allowed,
        frame->key_storage_allowed,
        frame->encryption_performed,
        frame->signing_performed,
        frame->network_lookup_allowed,
        frame->runtime_authority_granted,
        frame->frame_state,
        frame->blocked_reason,
        latticra_seal_pqc_integration_frame_error_label(frame->error),
        frame->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
