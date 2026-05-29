#include "latticra/q_seal_ml_kem_implementation_frame.h"

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

static unsigned parameter_set_is_recorded(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set) {
    latticra_q_seal_ml_kem_parameters_t parameters;

    if (latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) !=
        LATTICRA_Q_SEAL_STATUS_OK) {
        return 0u;
    }

    return parameters.error == LATTICRA_Q_SEAL_ML_KEM_OK &&
           latticra_q_seal_ml_kem_parameters_are_authority_neutral(&parameters) == 1;
}

static unsigned required_items_satisfied(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame) {
    unsigned satisfied = 0u;

    satisfied += one_if(frame->clean_room_source_boundary_recorded);
    satisfied += one_if(frame->parameter_sets_recorded);
    satisfied += one_if(frame->module_plan_recorded);
    satisfied += one_if(frame->constant_time_design_recorded);
    satisfied += one_if(frame->secret_branch_review_recorded);
    satisfied += one_if(frame->secret_memory_review_recorded);
    satisfied += one_if(frame->zeroization_design_recorded);
    satisfied += one_if(frame->randomness_design_recorded);
    satisfied += one_if(frame->serialization_canonicality_recorded);
    satisfied += one_if(frame->malformed_input_policy_recorded);
    satisfied += one_if(frame->test_vector_binding_recorded);
    satisfied += one_if(frame->formal_review_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_implementation_frame_error_label(
    latticra_q_seal_ml_kem_implementation_frame_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_frame_prepare(
    latticra_q_seal_ml_kem_implementation_frame_t *out) {
    unsigned parameter_512;
    unsigned parameter_768;
    unsigned parameter_1024;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->implementation_profile,
        sizeof(out->implementation_profile),
        "latticra-q-seal-ml-kem-implementation-frame/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Implementation Frame");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(out->implementation_state, sizeof(out->implementation_state), "design-frame-only");

    parameter_512 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    parameter_768 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    parameter_1024 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);

    out->implementation_frame_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->parameter_sets_recorded =
        parameter_512 == 1u && parameter_768 == 1u && parameter_1024 == 1u;
    out->module_plan_recorded = 1u;
    out->planned_module_count = 9u;
    out->polynomial_arithmetic_planned = 1u;
    out->ntt_planned = 1u;
    out->sampling_planned = 1u;
    out->compression_planned = 1u;
    out->encoding_planned = 1u;
    out->hash_xof_planned = 1u;
    out->keygen_planned = 1u;
    out->encaps_planned = 1u;
    out->decaps_planned = 1u;
    out->implementation_code_present = 0u;
    out->polynomial_arithmetic_implemented = 0u;
    out->ntt_implemented = 0u;
    out->sampling_implemented = 0u;
    out->compression_implemented = 0u;
    out->encoding_implemented = 0u;
    out->hash_xof_implemented = 0u;
    out->keygen_implemented = 0u;
    out->encaps_implemented = 0u;
    out->decaps_implemented = 0u;
    out->constant_time_design_required = 1u;
    out->constant_time_design_recorded = 0u;
    out->secret_branch_review_required = 1u;
    out->secret_branch_review_recorded = 0u;
    out->secret_memory_review_required = 1u;
    out->secret_memory_review_recorded = 0u;
    out->zeroization_design_required = 1u;
    out->zeroization_design_recorded = 0u;
    out->randomness_design_required = 1u;
    out->randomness_design_recorded = 0u;
    out->serialization_canonicality_required = 1u;
    out->serialization_canonicality_recorded = 0u;
    out->malformed_input_policy_required = 1u;
    out->malformed_input_policy_recorded = 0u;
    out->test_vector_binding_required = 1u;
    out->test_vector_binding_recorded = 0u;
    out->formal_review_required = 1u;
    out->formal_review_recorded = 0u;
    out->operations_enabled = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_design_items_total = 12u;
    out->required_design_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "constant-time-secret-memory-zeroization-randomness-serialization-test-vector-and-formal-reviews-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-implementation-frame-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_implementation_frame_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame) {
    if (frame == NULL) {
        return 0;
    }

    return frame->apple_corecrypto_code_copied == 0u &&
           frame->external_provider_code_copied == 0u &&
           frame->implementation_code_present == 0u &&
           frame->keygen_implemented == 0u &&
           frame->encaps_implemented == 0u &&
           frame->decaps_implemented == 0u &&
           frame->operations_enabled == 0u &&
           frame->production_crypto_claim_allowed == 0u &&
           frame->fips_claim_allowed == 0u &&
           frame->runtime_authority_granted == 0u;
}

int latticra_q_seal_ml_kem_implementation_frame_allows_implementation(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame) {
    if (frame == NULL) {
        return 0;
    }

    return frame->clean_room_source_boundary_recorded == 1u &&
           frame->parameter_sets_recorded == 1u &&
           frame->module_plan_recorded == 1u &&
           frame->constant_time_design_recorded == 1u &&
           frame->secret_branch_review_recorded == 1u &&
           frame->secret_memory_review_recorded == 1u &&
           frame->zeroization_design_recorded == 1u &&
           frame->randomness_design_recorded == 1u &&
           frame->serialization_canonicality_recorded == 1u &&
           frame->malformed_input_policy_recorded == 1u &&
           frame->test_vector_binding_recorded == 1u &&
           frame->formal_review_recorded == 1u &&
           frame->apple_corecrypto_code_copied == 0u &&
           frame->external_provider_code_copied == 0u &&
           frame->implementation_code_present == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_frame_report(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (frame == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION FRAME\n"
        "implementation_profile=%s\n"
        "formal_title=%s\n"
        "source_boundary=%s\n"
        "implementation_state=%s\n"
        "implementation_frame_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "parameter_sets_recorded=%u\n"
        "module_plan_recorded=%u\n"
        "planned_module_count=%u\n"
        "polynomial_arithmetic_planned=%u\n"
        "ntt_planned=%u\n"
        "sampling_planned=%u\n"
        "compression_planned=%u\n"
        "encoding_planned=%u\n"
        "hash_xof_planned=%u\n"
        "keygen_planned=%u\n"
        "encaps_planned=%u\n"
        "decaps_planned=%u\n"
        "implementation_code_present=%u\n"
        "polynomial_arithmetic_implemented=%u\n"
        "ntt_implemented=%u\n"
        "sampling_implemented=%u\n"
        "compression_implemented=%u\n"
        "encoding_implemented=%u\n"
        "hash_xof_implemented=%u\n"
        "keygen_implemented=%u\n"
        "encaps_implemented=%u\n"
        "decaps_implemented=%u\n"
        "constant_time_design_required=%u\n"
        "constant_time_design_recorded=%u\n"
        "secret_branch_review_required=%u\n"
        "secret_branch_review_recorded=%u\n"
        "secret_memory_review_required=%u\n"
        "secret_memory_review_recorded=%u\n"
        "zeroization_design_required=%u\n"
        "zeroization_design_recorded=%u\n"
        "randomness_design_required=%u\n"
        "randomness_design_recorded=%u\n"
        "serialization_canonicality_required=%u\n"
        "serialization_canonicality_recorded=%u\n"
        "malformed_input_policy_required=%u\n"
        "malformed_input_policy_recorded=%u\n"
        "test_vector_binding_required=%u\n"
        "test_vector_binding_recorded=%u\n"
        "formal_review_required=%u\n"
        "formal_review_recorded=%u\n"
        "operations_enabled=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_design_items_total=%u\n"
        "required_design_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        frame->implementation_profile,
        frame->formal_title,
        frame->source_boundary,
        frame->implementation_state,
        frame->implementation_frame_present,
        frame->clean_room_source_boundary_recorded,
        frame->apple_corecrypto_code_copied,
        frame->external_provider_code_copied,
        frame->parameter_sets_recorded,
        frame->module_plan_recorded,
        frame->planned_module_count,
        frame->polynomial_arithmetic_planned,
        frame->ntt_planned,
        frame->sampling_planned,
        frame->compression_planned,
        frame->encoding_planned,
        frame->hash_xof_planned,
        frame->keygen_planned,
        frame->encaps_planned,
        frame->decaps_planned,
        frame->implementation_code_present,
        frame->polynomial_arithmetic_implemented,
        frame->ntt_implemented,
        frame->sampling_implemented,
        frame->compression_implemented,
        frame->encoding_implemented,
        frame->hash_xof_implemented,
        frame->keygen_implemented,
        frame->encaps_implemented,
        frame->decaps_implemented,
        frame->constant_time_design_required,
        frame->constant_time_design_recorded,
        frame->secret_branch_review_required,
        frame->secret_branch_review_recorded,
        frame->secret_memory_review_required,
        frame->secret_memory_review_recorded,
        frame->zeroization_design_required,
        frame->zeroization_design_recorded,
        frame->randomness_design_required,
        frame->randomness_design_recorded,
        frame->serialization_canonicality_required,
        frame->serialization_canonicality_recorded,
        frame->malformed_input_policy_required,
        frame->malformed_input_policy_recorded,
        frame->test_vector_binding_required,
        frame->test_vector_binding_recorded,
        frame->formal_review_required,
        frame->formal_review_recorded,
        frame->operations_enabled,
        frame->production_crypto_claim_allowed,
        frame->fips_claim_allowed,
        frame->runtime_authority_granted,
        frame->required_design_items_total,
        frame->required_design_items_satisfied,
        frame->blocked_reason,
        latticra_q_seal_ml_kem_implementation_frame_error_label(frame->error),
        frame->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
