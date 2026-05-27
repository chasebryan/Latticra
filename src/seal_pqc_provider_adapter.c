#include "latticra/seal_pqc_provider_adapter.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_pqc_provider_adapter_error_label(
    latticra_seal_pqc_provider_adapter_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_OK:
        return "ok";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_MISSING_FRAME:
        return "missing-frame";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_FRAME:
        return "invalid-frame";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_PROVIDER_NOT_ALLOWED:
        return "provider-not-allowed";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_APPLE_BOUNDARY_VIOLATION:
        return "apple-boundary-violation";
    case LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

static void adapter_init(latticra_seal_pqc_provider_adapter_t *adapter) {
    memset(adapter, 0, sizeof(*adapter));
    copy_literal(
        adapter->adapter_profile,
        sizeof(adapter->adapter_profile),
        "latticra-seal-pqc-provider-adapter/0.1");
    copy_literal(
        adapter->clean_room_profile,
        sizeof(adapter->clean_room_profile),
        "latticra-clean-room-pqc/0.1");
    copy_literal(adapter->provider_name, sizeof(adapter->provider_name), "none");
    copy_literal(adapter->provider_role, sizeof(adapter->provider_role), "comparison-provider-blocked");
    copy_literal(adapter->source_boundary, sizeof(adapter->source_boundary), "clean-room-required");
    copy_literal(adapter->adapter_state, sizeof(adapter->adapter_state), "blocked");
    copy_literal(adapter->blocked_reason, sizeof(adapter->blocked_reason), "invalid-input");
    adapter->clean_room_design_required = 1u;
    adapter->nist_fips_203_ml_kem_required = 1u;
    adapter->nist_fips_204_ml_dsa_required = 1u;
    adapter->nist_fips_205_slh_dsa_backup_tracked = 1u;
    adapter->ml_kem_512_planned = 1u;
    adapter->ml_kem_768_planned = 1u;
    adapter->ml_kem_1024_planned = 1u;
    adapter->ml_dsa_44_planned = 1u;
    adapter->ml_dsa_65_planned = 1u;
    adapter->ml_dsa_87_planned = 1u;
    adapter->permissive_reference_code_required = 1u;
    adapter->third_party_notice_review_required = 1u;
    adapter->compile_time_gate_required = 1u;
    adapter->known_answer_tests_required = 1u;
    adapter->differential_tests_allowed = 1u;
    adapter->fuzzing_required = 1u;
    adapter->constant_time_review_required = 1u;
    adapter->side_channel_review_required = 1u;
    adapter->memory_safe_implementation_preferred = 1u;
    adapter->c_abi_boundary_required = 1u;
    adapter->cryptographic_module_boundary_required = 1u;
    adapter->fips_140_3_claim_gate_required = 1u;
    adapter->cavp_acvp_vector_review_required = 1u;
    adapter->error = LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_INPUT;
    copy_literal(adapter->status, sizeof(adapter->status), "invalid-input");
}

static latticra_status_t adapter_fail(
    latticra_seal_pqc_provider_adapter_t *adapter,
    latticra_seal_pqc_provider_adapter_error_t error,
    const char *blocked_reason) {
    copy_literal(adapter->adapter_state, sizeof(adapter->adapter_state), "blocked");
    copy_literal(adapter->blocked_reason, sizeof(adapter->blocked_reason), blocked_reason);
    adapter->liboqs_comparison_provider_allowed = 0u;
    adapter->liboqs_linked = 0u;
    adapter->liboqs_runtime_used = 0u;
    adapter->apple_corecrypto_code_copied = 0u;
    adapter->apple_corecrypto_proof_artifacts_copied = 0u;
    adapter->apple_corecrypto_symbols_reused = 0u;
    adapter->default_build_enabled = 0u;
    adapter->differential_tests_performed = 0u;
    adapter->key_generation_performed = 0u;
    adapter->key_storage_performed = 0u;
    adapter->encapsulation_performed = 0u;
    adapter->decapsulation_performed = 0u;
    adapter->signing_performed = 0u;
    adapter->verification_performed = 0u;
    adapter->encryption_performed = 0u;
    adapter->network_lookup_allowed = 0u;
    adapter->production_crypto_claim_allowed = 0u;
    adapter->post_quantum_migration_claim_allowed = 0u;
    adapter->runtime_authority_granted = 0u;
    adapter->error = error;
    copy_literal(
        adapter->status,
        sizeof(adapter->status),
        latticra_seal_pqc_provider_adapter_error_label(error));
    return LATTICRA_STATUS_OK;
}

static int frame_allows_provider_planning(const latticra_seal_pqc_integration_frame_t *frame) {
    return frame->error == LATTICRA_SEAL_PQC_INTEGRATION_FRAME_OK &&
           latticra_seal_pqc_integration_frame_is_authority_neutral(frame) == 1 &&
           strcmp(frame->candidate_provider, "liboqs") == 0 &&
           frame->liboqs_candidate_tracked == 1u &&
           frame->liboqs_mit_license_tracked == 1u &&
           frame->liboqs_prototype_only_warning_tracked == 1u &&
           frame->candidate_provider_production_use_allowed == 0u;
}

static int frame_preserves_apple_boundary(const latticra_seal_pqc_integration_frame_t *frame) {
    return frame->apple_corecrypto_reference_allowed == 1u &&
           frame->apple_corecrypto_embedding_allowed == 0u &&
           frame->apple_corecrypto_redistribution_allowed == 0u;
}

latticra_status_t latticra_seal_pqc_provider_adapter_from_frame(
    const latticra_seal_pqc_integration_frame_t *frame,
    latticra_seal_pqc_provider_adapter_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    adapter_init(out);

    if (frame == NULL) {
        return adapter_fail(out, LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_MISSING_FRAME, "missing-frame");
    }

    out->integration_frame_present = 1u;
    copy_literal(out->integration_profile, sizeof(out->integration_profile), frame->pqc_integration_profile);
    copy_literal(out->provider_name, sizeof(out->provider_name), frame->candidate_provider);
    copy_literal(out->provider_license, sizeof(out->provider_license), frame->candidate_provider_license);
    out->apple_corecrypto_reference_allowed = frame->apple_corecrypto_reference_allowed;

    if (!frame_preserves_apple_boundary(frame)) {
        return adapter_fail(
            out,
            LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_APPLE_BOUNDARY_VIOLATION,
            "apple-boundary-violation");
    }

    if (!frame_allows_provider_planning(frame)) {
        return adapter_fail(
            out,
            LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_INVALID_FRAME,
            "invalid-integration-frame");
    }

    copy_literal(out->provider_role, sizeof(out->provider_role), "comparison-provider-only");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    out->liboqs_comparison_provider_allowed = 1u;
    out->liboqs_linked = 0u;
    out->liboqs_runtime_used = 0u;
    out->apple_corecrypto_code_copied = 0u;
    out->apple_corecrypto_proof_artifacts_copied = 0u;
    out->apple_corecrypto_symbols_reused = 0u;
    out->default_build_enabled = 0u;
    out->differential_tests_performed = 0u;
    out->key_generation_performed = 0u;
    out->key_storage_performed = 0u;
    out->encapsulation_performed = 0u;
    out->decapsulation_performed = 0u;
    out->signing_performed = 0u;
    out->verification_performed = 0u;
    out->encryption_performed = 0u;
    out->network_lookup_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->post_quantum_migration_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(out->adapter_state, sizeof(out->adapter_state), "prepared-clean-room-adapter");
    copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "crypto-operations-not-implemented");
    out->error = LATTICRA_SEAL_PQC_PROVIDER_ADAPTER_OK;
    copy_literal(out->status, sizeof(out->status), "pqc-provider-adapter-prepared");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_pqc_provider_adapter_is_clean_room(
    const latticra_seal_pqc_provider_adapter_t *adapter) {
    if (adapter == NULL) {
        return 0;
    }

    return adapter->clean_room_design_required == 1u &&
           adapter->permissive_reference_code_required == 1u &&
           adapter->apple_corecrypto_code_copied == 0u &&
           adapter->apple_corecrypto_proof_artifacts_copied == 0u &&
           adapter->apple_corecrypto_symbols_reused == 0u &&
           strcmp(adapter->source_boundary, "clean-room-no-apple-code") == 0;
}

int latticra_seal_pqc_provider_adapter_is_authority_neutral(
    const latticra_seal_pqc_provider_adapter_t *adapter) {
    if (adapter == NULL) {
        return 0;
    }

    return adapter->liboqs_linked == 0u &&
           adapter->liboqs_runtime_used == 0u &&
           adapter->default_build_enabled == 0u &&
           adapter->differential_tests_performed == 0u &&
           adapter->key_generation_performed == 0u &&
           adapter->key_storage_performed == 0u &&
           adapter->encapsulation_performed == 0u &&
           adapter->decapsulation_performed == 0u &&
           adapter->signing_performed == 0u &&
           adapter->verification_performed == 0u &&
           adapter->encryption_performed == 0u &&
           adapter->network_lookup_allowed == 0u &&
           adapter->production_crypto_claim_allowed == 0u &&
           adapter->post_quantum_migration_claim_allowed == 0u &&
           adapter->runtime_authority_granted == 0u;
}

latticra_status_t latticra_seal_pqc_provider_adapter_report(
    const latticra_seal_pqc_provider_adapter_t *adapter,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (adapter == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL PQC PROVIDER ADAPTER\n"
        "adapter_profile=%s\n"
        "integration_profile=%s\n"
        "clean_room_profile=%s\n"
        "provider_name=%s\n"
        "provider_role=%s\n"
        "provider_license=%s\n"
        "source_boundary=%s\n"
        "adapter_state=%s\n"
        "blocked_reason=%s\n"
        "integration_frame_present=%u\n"
        "clean_room_design_required=%u\n"
        "nist_fips_203_ml_kem_required=%u\n"
        "nist_fips_204_ml_dsa_required=%u\n"
        "nist_fips_205_slh_dsa_backup_tracked=%u\n"
        "ml_kem_512_planned=%u\n"
        "ml_kem_768_planned=%u\n"
        "ml_kem_1024_planned=%u\n"
        "ml_dsa_44_planned=%u\n"
        "ml_dsa_65_planned=%u\n"
        "ml_dsa_87_planned=%u\n"
        "liboqs_comparison_provider_allowed=%u\n"
        "liboqs_linked=%u\n"
        "liboqs_runtime_used=%u\n"
        "apple_corecrypto_reference_allowed=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "apple_corecrypto_proof_artifacts_copied=%u\n"
        "apple_corecrypto_symbols_reused=%u\n"
        "permissive_reference_code_required=%u\n"
        "third_party_notice_review_required=%u\n"
        "compile_time_gate_required=%u\n"
        "default_build_enabled=%u\n"
        "known_answer_tests_required=%u\n"
        "differential_tests_allowed=%u\n"
        "differential_tests_performed=%u\n"
        "fuzzing_required=%u\n"
        "constant_time_review_required=%u\n"
        "side_channel_review_required=%u\n"
        "memory_safe_implementation_preferred=%u\n"
        "c_abi_boundary_required=%u\n"
        "cryptographic_module_boundary_required=%u\n"
        "fips_140_3_claim_gate_required=%u\n"
        "cavp_acvp_vector_review_required=%u\n"
        "key_generation_performed=%u\n"
        "key_storage_performed=%u\n"
        "encapsulation_performed=%u\n"
        "decapsulation_performed=%u\n"
        "signing_performed=%u\n"
        "verification_performed=%u\n"
        "encryption_performed=%u\n"
        "network_lookup_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "error=%s\n"
        "status=%s\n",
        adapter->adapter_profile,
        adapter->integration_profile,
        adapter->clean_room_profile,
        adapter->provider_name,
        adapter->provider_role,
        adapter->provider_license,
        adapter->source_boundary,
        adapter->adapter_state,
        adapter->blocked_reason,
        adapter->integration_frame_present,
        adapter->clean_room_design_required,
        adapter->nist_fips_203_ml_kem_required,
        adapter->nist_fips_204_ml_dsa_required,
        adapter->nist_fips_205_slh_dsa_backup_tracked,
        adapter->ml_kem_512_planned,
        adapter->ml_kem_768_planned,
        adapter->ml_kem_1024_planned,
        adapter->ml_dsa_44_planned,
        adapter->ml_dsa_65_planned,
        adapter->ml_dsa_87_planned,
        adapter->liboqs_comparison_provider_allowed,
        adapter->liboqs_linked,
        adapter->liboqs_runtime_used,
        adapter->apple_corecrypto_reference_allowed,
        adapter->apple_corecrypto_code_copied,
        adapter->apple_corecrypto_proof_artifacts_copied,
        adapter->apple_corecrypto_symbols_reused,
        adapter->permissive_reference_code_required,
        adapter->third_party_notice_review_required,
        adapter->compile_time_gate_required,
        adapter->default_build_enabled,
        adapter->known_answer_tests_required,
        adapter->differential_tests_allowed,
        adapter->differential_tests_performed,
        adapter->fuzzing_required,
        adapter->constant_time_review_required,
        adapter->side_channel_review_required,
        adapter->memory_safe_implementation_preferred,
        adapter->c_abi_boundary_required,
        adapter->cryptographic_module_boundary_required,
        adapter->fips_140_3_claim_gate_required,
        adapter->cavp_acvp_vector_review_required,
        adapter->key_generation_performed,
        adapter->key_storage_performed,
        adapter->encapsulation_performed,
        adapter->decapsulation_performed,
        adapter->signing_performed,
        adapter->verification_performed,
        adapter->encryption_performed,
        adapter->network_lookup_allowed,
        adapter->production_crypto_claim_allowed,
        adapter->post_quantum_migration_claim_allowed,
        adapter->runtime_authority_granted,
        latticra_seal_pqc_provider_adapter_error_label(adapter->error),
        adapter->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
