#include "latticra/q_seal_readiness.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static unsigned one_if(unsigned value) {
    return value != 0u ? 1u : 0u;
}

static unsigned parameter_set_is_present(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set) {
    latticra_q_seal_ml_kem_parameters_t parameters;

    if (latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) !=
        LATTICRA_Q_SEAL_STATUS_OK) {
        return 0u;
    }

    return parameters.error == LATTICRA_Q_SEAL_ML_KEM_OK &&
           latticra_q_seal_ml_kem_parameters_are_authority_neutral(&parameters) == 1;
}

const char *latticra_q_seal_readiness_error_label(
    latticra_q_seal_readiness_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_READINESS_OK:
        return "ok";
    case LATTICRA_Q_SEAL_READINESS_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_READINESS_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_readiness_prepare(
    latticra_q_seal_readiness_t *out) {
    latticra_q_seal_foundation_t foundation;
    latticra_q_seal_ml_kem_evidence_gate_t evidence_gate;
    latticra_q_seal_ml_kem_acvp_intake_t acvp_intake;
    latticra_q_seal_ml_kem_vector_schema_t vector_schema;
    latticra_q_seal_ml_kem_vector_source_t vector_source;
    latticra_q_seal_ml_kem_negative_test_evidence_t negative_test_evidence;
    latticra_q_seal_ml_kem_memory_safety_evidence_t memory_safety_evidence;
    latticra_q_seal_ml_kem_api_misuse_resistance_t api_misuse_resistance;
    latticra_q_seal_ml_kem_source_digest_manifest_t source_digest_manifest;
    latticra_q_seal_ml_kem_code_owner_review_t code_owner_review;
    latticra_q_seal_ml_kem_ci_promotion_evidence_t ci_promotion_evidence;
    latticra_q_seal_ml_kem_constant_time_review_t constant_time_review;
    latticra_q_seal_ml_kem_randomness_source_t randomness_source;
    latticra_q_seal_ml_kem_zeroization_evidence_t zeroization_evidence;
    latticra_q_seal_ml_kem_side_channel_review_t side_channel_review;
    latticra_q_seal_ml_kem_provider_differential_t provider_differential;
    latticra_q_seal_ml_kem_implementation_binding_manifest_t implementation_binding_manifest;
    latticra_q_seal_ml_kem_implementation_frame_t implementation_frame;
    latticra_q_seal_ml_kem_secret_state_contract_t secret_state_contract;
    unsigned foundation_clean_room;
    unsigned foundation_authority_neutral;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    if (latticra_q_seal_foundation_prepare(&foundation) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_evidence_gate_prepare(&evidence_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_intake_prepare(&acvp_intake) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_schema_prepare(&vector_schema) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_source_prepare(&vector_source) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_negative_test_evidence_prepare(&negative_test_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_memory_safety_evidence_prepare(&memory_safety_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_api_misuse_resistance_prepare(&api_misuse_resistance) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_source_digest_manifest_prepare(&source_digest_manifest) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_code_owner_review_prepare(&code_owner_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(&ci_promotion_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_constant_time_review_prepare(&constant_time_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_randomness_source_prepare(&randomness_source) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_zeroization_evidence_prepare(&zeroization_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_side_channel_review_prepare(&side_channel_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_provider_differential_prepare(&provider_differential) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(
            &implementation_binding_manifest) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_frame_prepare(&implementation_frame) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_secret_state_contract_prepare(&secret_state_contract) !=
            LATTICRA_Q_SEAL_STATUS_OK) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    foundation_clean_room =
        (unsigned)latticra_q_seal_foundation_is_clean_room(&foundation);
    foundation_authority_neutral =
        (unsigned)latticra_q_seal_foundation_is_authority_neutral(&foundation);

    memset(out, 0, sizeof(*out));
    copy_literal(out->readiness_profile, sizeof(out->readiness_profile), "latticra-q-seal-readiness/0.1");
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Q-Seal Readiness Profile");
    copy_literal(out->subsystem_path, sizeof(out->subsystem_path), "latticra-q-seal");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->readiness_state,
        sizeof(out->readiness_state),
        "design-frame-ready-runtime-crypto-blocked");

    out->readiness_profile_present = 1u;
    out->foundation_present =
        foundation.latticra_q_seal_present == 1u &&
        foundation_clean_room == 1u &&
        foundation_authority_neutral == 1u;
    out->ml_kem_512_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    out->ml_kem_768_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    out->ml_kem_1024_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);
    out->ml_kem_parameters_present =
        out->ml_kem_512_parameters_present == 1u &&
        out->ml_kem_768_parameters_present == 1u &&
        out->ml_kem_1024_parameters_present == 1u;
    out->evidence_gate_present = evidence_gate.ml_kem_evidence_gate_present;
    out->acvp_intake_present = acvp_intake.acvp_intake_present;
    out->vector_schema_present = vector_schema.vector_schema_present;
    out->vector_source_intake_present = vector_source.vector_source_intake_present;
    out->negative_test_evidence_present =
        negative_test_evidence.negative_test_evidence_present;
    out->memory_safety_evidence_present =
        memory_safety_evidence.memory_safety_evidence_present;
    out->api_misuse_resistance_present =
        api_misuse_resistance.api_misuse_resistance_present;
    out->source_digest_manifest_present =
        source_digest_manifest.source_digest_manifest_present;
    out->code_owner_review_present =
        code_owner_review.code_owner_review_evidence_present;
    out->ci_promotion_evidence_present =
        ci_promotion_evidence.ci_promotion_evidence_present;
    out->constant_time_review_present =
        constant_time_review.constant_time_review_present;
    out->randomness_source_contract_present =
        randomness_source.randomness_source_contract_present;
    out->zeroization_evidence_present =
        zeroization_evidence.zeroization_evidence_present;
    out->side_channel_review_present =
        side_channel_review.side_channel_review_present;
    out->provider_differential_present =
        provider_differential.provider_differential_contract_present;
    out->implementation_binding_manifest_present =
        implementation_binding_manifest.implementation_binding_manifest_present;
    out->implementation_frame_present = implementation_frame.implementation_frame_present;
    out->secret_state_contract_present =
        secret_state_contract.secret_state_contract_present;
    out->clean_room_boundary_recorded =
        foundation_clean_room == 1u &&
        source_digest_manifest.clean_room_source_boundary_recorded == 1u &&
        implementation_binding_manifest.clean_room_source_boundary_recorded == 1u &&
        implementation_frame.clean_room_source_boundary_recorded == 1u &&
        secret_state_contract.clean_room_source_boundary_recorded == 1u;
    out->apple_corecrypto_code_copied =
        foundation.apple_corecrypto_code_copied |
        evidence_gate.apple_corecrypto_code_copied |
        source_digest_manifest.apple_corecrypto_code_copied |
        implementation_binding_manifest.apple_corecrypto_code_copied |
        implementation_frame.apple_corecrypto_code_copied |
        secret_state_contract.apple_corecrypto_code_copied;
    out->external_provider_code_copied =
        source_digest_manifest.external_provider_code_copied |
        implementation_binding_manifest.external_provider_code_copied |
        implementation_frame.external_provider_code_copied |
        secret_state_contract.external_provider_code_copied;
    out->provider_runtime_used =
        foundation.provider_runtime_used |
        provider_differential.provider_runtime_used;
    out->components_total = 20u;
    out->components_present =
        one_if(out->foundation_present) +
        one_if(out->ml_kem_parameters_present) +
        one_if(out->evidence_gate_present) +
        one_if(out->acvp_intake_present) +
        one_if(out->vector_schema_present) +
        one_if(out->vector_source_intake_present) +
        one_if(out->negative_test_evidence_present) +
        one_if(out->memory_safety_evidence_present) +
        one_if(out->api_misuse_resistance_present) +
        one_if(out->source_digest_manifest_present) +
        one_if(out->code_owner_review_present) +
        one_if(out->ci_promotion_evidence_present) +
        one_if(out->constant_time_review_present) +
        one_if(out->randomness_source_contract_present) +
        one_if(out->zeroization_evidence_present) +
        one_if(out->side_channel_review_present) +
        one_if(out->provider_differential_present) +
        one_if(out->implementation_binding_manifest_present) +
        one_if(out->implementation_frame_present) +
        one_if(out->secret_state_contract_present);
    out->runtime_blockers_total =
        one_if(!latticra_q_seal_ml_kem_evidence_gate_allows_operations(&evidence_gate)) +
        one_if(!latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(&acvp_intake)) +
        one_if(!latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(
            &vector_schema)) +
        one_if(!latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(
            &vector_source)) +
        one_if(!latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(
            &negative_test_evidence)) +
        one_if(!latticra_q_seal_ml_kem_memory_safety_evidence_allows_implementation_promotion(
            &memory_safety_evidence)) +
        one_if(!latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(
            &api_misuse_resistance)) +
        one_if(!latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(
            &source_digest_manifest)) +
        one_if(!latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(
            &code_owner_review)) +
        one_if(!latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(
            &ci_promotion_evidence)) +
        one_if(!latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(
            &constant_time_review)) +
        one_if(!latticra_q_seal_ml_kem_randomness_source_allows_random_generation(
            &randomness_source)) +
        one_if(!latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(
            &zeroization_evidence)) +
        one_if(!latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(
            &side_channel_review)) +
        one_if(!latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(
            &provider_differential)) +
        one_if(!latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(
            &implementation_binding_manifest)) +
        one_if(!latticra_q_seal_ml_kem_implementation_frame_allows_implementation(
            &implementation_frame)) +
        one_if(!latticra_q_seal_ml_kem_secret_state_contract_allows_operations(
            &secret_state_contract));
    out->required_readiness_items_total =
        2u +
        3u +
        evidence_gate.required_evidence_items_total +
        acvp_intake.required_intake_items_total +
        vector_schema.required_schema_items_total +
        vector_source.required_source_items_total +
        negative_test_evidence.required_negative_test_items_total +
        memory_safety_evidence.required_memory_safety_items_total +
        api_misuse_resistance.required_api_misuse_items_total +
        source_digest_manifest.required_digest_items_total +
        code_owner_review.required_review_items_total +
        ci_promotion_evidence.required_promotion_items_total +
        constant_time_review.required_review_items_total +
        randomness_source.required_randomness_items_total +
        zeroization_evidence.required_zeroization_items_total +
        side_channel_review.required_review_items_total +
        provider_differential.required_comparison_items_total +
        implementation_binding_manifest.required_binding_items_total +
        implementation_frame.required_design_items_total +
        secret_state_contract.required_secret_state_items_total;
    out->required_readiness_items_satisfied =
        foundation_clean_room +
        foundation_authority_neutral +
        out->ml_kem_512_parameters_present +
        out->ml_kem_768_parameters_present +
        out->ml_kem_1024_parameters_present +
        evidence_gate.required_evidence_items_satisfied +
        acvp_intake.required_intake_items_satisfied +
        vector_schema.required_schema_items_satisfied +
        vector_source.required_source_items_satisfied +
        negative_test_evidence.required_negative_test_items_satisfied +
        memory_safety_evidence.required_memory_safety_items_satisfied +
        api_misuse_resistance.required_api_misuse_items_satisfied +
        source_digest_manifest.required_digest_items_satisfied +
        code_owner_review.required_review_items_satisfied +
        ci_promotion_evidence.required_promotion_items_satisfied +
        constant_time_review.required_review_items_satisfied +
        randomness_source.required_randomness_items_satisfied +
        zeroization_evidence.required_zeroization_items_satisfied +
        side_channel_review.required_review_items_satisfied +
        provider_differential.required_comparison_items_satisfied +
        implementation_binding_manifest.required_binding_items_satisfied +
        implementation_frame.required_design_items_satisfied +
        secret_state_contract.required_secret_state_items_satisfied;
    out->design_frame_integration_ready =
        out->components_present == out->components_total &&
        out->clean_room_boundary_recorded == 1u &&
        out->apple_corecrypto_code_copied == 0u &&
        out->external_provider_code_copied == 0u &&
        out->provider_runtime_used == 0u;
    out->runtime_crypto_ready = 0u;
    out->operations_enabled = 0u;
    out->key_generation_enabled = 0u;
    out->encapsulation_enabled = 0u;
    out->decapsulation_enabled = 0u;
    out->shared_secret_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->post_quantum_migration_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "implementation-kat-acvp-vector-source-negative-memory-api-source-digest-code-owner-ci-binding-randomness-zeroization-side-channel-provider-constant-time-evidence-missing");
    out->error = LATTICRA_Q_SEAL_READINESS_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "q-seal-readiness-profile-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_readiness_is_design_frame_ready(
    const latticra_q_seal_readiness_t *readiness) {
    if (readiness == NULL) {
        return 0;
    }

    return readiness->readiness_profile_present == 1u &&
           readiness->components_total == 20u &&
           readiness->components_present == readiness->components_total &&
           readiness->clean_room_boundary_recorded == 1u &&
           readiness->apple_corecrypto_code_copied == 0u &&
           readiness->external_provider_code_copied == 0u &&
           readiness->provider_runtime_used == 0u &&
           readiness->operations_enabled == 0u &&
           readiness->production_crypto_claim_allowed == 0u &&
           readiness->fips_claim_allowed == 0u &&
           readiness->runtime_authority_granted == 0u;
}

int latticra_q_seal_readiness_allows_runtime_crypto(
    const latticra_q_seal_readiness_t *readiness) {
    if (readiness == NULL) {
        return 0;
    }

    return readiness->design_frame_integration_ready == 1u &&
           readiness->runtime_crypto_ready == 1u &&
           readiness->runtime_blockers_total == 0u &&
           readiness->required_readiness_items_total ==
               readiness->required_readiness_items_satisfied &&
           readiness->operations_enabled == 1u &&
           readiness->key_generation_enabled == 1u &&
           readiness->encapsulation_enabled == 1u &&
           readiness->decapsulation_enabled == 1u &&
           readiness->shared_secret_emitted == 1u &&
           readiness->production_crypto_claim_allowed == 1u &&
           readiness->runtime_authority_granted == 1u &&
           readiness->error == LATTICRA_Q_SEAL_READINESS_OK;
}

latticra_q_seal_status_t latticra_q_seal_readiness_report(
    const latticra_q_seal_readiness_t *readiness,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (readiness == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL READINESS PROFILE\n"
        "readiness_profile=%s\n"
        "formal_title=%s\n"
        "subsystem_path=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "readiness_state=%s\n"
        "readiness_profile_present=%u\n"
        "foundation_present=%u\n"
        "ml_kem_parameters_present=%u\n"
        "ml_kem_512_parameters_present=%u\n"
        "ml_kem_768_parameters_present=%u\n"
        "ml_kem_1024_parameters_present=%u\n"
        "evidence_gate_present=%u\n"
        "acvp_intake_present=%u\n"
        "vector_schema_present=%u\n"
        "vector_source_intake_present=%u\n"
        "negative_test_evidence_present=%u\n"
        "memory_safety_evidence_present=%u\n"
        "api_misuse_resistance_present=%u\n"
        "source_digest_manifest_present=%u\n"
        "code_owner_review_present=%u\n"
        "ci_promotion_evidence_present=%u\n"
        "constant_time_review_present=%u\n"
        "randomness_source_contract_present=%u\n"
        "zeroization_evidence_present=%u\n"
        "side_channel_review_present=%u\n"
        "provider_differential_present=%u\n"
        "implementation_binding_manifest_present=%u\n"
        "implementation_frame_present=%u\n"
        "secret_state_contract_present=%u\n"
        "clean_room_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "provider_runtime_used=%u\n"
        "components_total=%u\n"
        "components_present=%u\n"
        "runtime_blockers_total=%u\n"
        "required_readiness_items_total=%u\n"
        "required_readiness_items_satisfied=%u\n"
        "design_frame_integration_ready=%u\n"
        "runtime_crypto_ready=%u\n"
        "operations_enabled=%u\n"
        "key_generation_enabled=%u\n"
        "encapsulation_enabled=%u\n"
        "decapsulation_enabled=%u\n"
        "shared_secret_emitted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        readiness->readiness_profile,
        readiness->formal_title,
        readiness->subsystem_path,
        readiness->standards_basis,
        readiness->source_boundary,
        readiness->readiness_state,
        readiness->readiness_profile_present,
        readiness->foundation_present,
        readiness->ml_kem_parameters_present,
        readiness->ml_kem_512_parameters_present,
        readiness->ml_kem_768_parameters_present,
        readiness->ml_kem_1024_parameters_present,
        readiness->evidence_gate_present,
        readiness->acvp_intake_present,
        readiness->vector_schema_present,
        readiness->vector_source_intake_present,
        readiness->negative_test_evidence_present,
        readiness->memory_safety_evidence_present,
        readiness->api_misuse_resistance_present,
        readiness->source_digest_manifest_present,
        readiness->code_owner_review_present,
        readiness->ci_promotion_evidence_present,
        readiness->constant_time_review_present,
        readiness->randomness_source_contract_present,
        readiness->zeroization_evidence_present,
        readiness->side_channel_review_present,
        readiness->provider_differential_present,
        readiness->implementation_binding_manifest_present,
        readiness->implementation_frame_present,
        readiness->secret_state_contract_present,
        readiness->clean_room_boundary_recorded,
        readiness->apple_corecrypto_code_copied,
        readiness->external_provider_code_copied,
        readiness->provider_runtime_used,
        readiness->components_total,
        readiness->components_present,
        readiness->runtime_blockers_total,
        readiness->required_readiness_items_total,
        readiness->required_readiness_items_satisfied,
        readiness->design_frame_integration_ready,
        readiness->runtime_crypto_ready,
        readiness->operations_enabled,
        readiness->key_generation_enabled,
        readiness->encapsulation_enabled,
        readiness->decapsulation_enabled,
        readiness->shared_secret_emitted,
        readiness->production_crypto_claim_allowed,
        readiness->fips_claim_allowed,
        readiness->post_quantum_migration_claim_allowed,
        readiness->runtime_authority_granted,
        readiness->blocked_reason,
        latticra_q_seal_readiness_error_label(readiness->error),
        readiness->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
