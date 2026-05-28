#include "latticra/q_seal_ml_kem_implementation_traceability_matrix.h"

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

static unsigned required_items_satisfied(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix) {
    unsigned satisfied = 0u;

    satisfied += one_if(matrix->implementation_traceability_matrix_present);
    satisfied += one_if(matrix->clean_room_source_boundary_recorded);
    satisfied += one_if(matrix->planned_source_units_count == 9u);
    satisfied += one_if(matrix->planned_test_units_count == 9u);
    satisfied += one_if(matrix->planned_source_unit_matrix_recorded);
    satisfied += one_if(matrix->polynomial_arithmetic_unit_bound);
    satisfied += one_if(matrix->ntt_unit_bound);
    satisfied += one_if(matrix->sampling_unit_bound);
    satisfied += one_if(matrix->compression_unit_bound);
    satisfied += one_if(matrix->encoding_unit_bound);
    satisfied += one_if(matrix->hash_xof_unit_bound);
    satisfied += one_if(matrix->keygen_unit_bound);
    satisfied += one_if(matrix->encaps_unit_bound);
    satisfied += one_if(matrix->decaps_unit_bound);
    satisfied += one_if(matrix->fips_203_section_mapping_recorded);
    satisfied += one_if(matrix->sp800_227_usage_mapping_recorded);
    satisfied += one_if(matrix->kat_vector_family_mapping_recorded);
    satisfied += one_if(matrix->acvp_test_type_mapping_recorded);
    satisfied += one_if(matrix->clean_room_review_path_recorded);
    satisfied += one_if(matrix->no_external_code_dependency_recorded);
    satisfied += one_if(matrix->constant_time_review_mapping_recorded);
    satisfied += one_if(matrix->memory_safety_mapping_recorded);
    satisfied += one_if(matrix->zeroization_mapping_recorded);
    satisfied += one_if(matrix->randomness_mapping_recorded);
    satisfied += one_if(matrix->negative_test_mapping_recorded);
    satisfied += one_if(matrix->source_digest_mapping_recorded);
    satisfied += one_if(matrix->code_owner_mapping_recorded);
    satisfied += one_if(matrix->review_disposition_mapping_recorded);
    satisfied += one_if(matrix->implementation_trace_accepted);
    satisfied += one_if(matrix->implementation_file_digest_manifest_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_implementation_traceability_matrix_error_label(
    latticra_q_seal_ml_kem_implementation_traceability_matrix_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(
    latticra_q_seal_ml_kem_implementation_traceability_matrix_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->traceability_profile,
        sizeof(out->traceability_profile),
        "latticra-q-seal-ml-kem-implementation-traceability-matrix/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Implementation Traceability Matrix");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->traceability_scope,
        sizeof(out->traceability_scope),
        "ML-KEM-source-unit-to-evidence-trace-before-implementation");
    copy_literal(
        out->traceability_state,
        sizeof(out->traceability_state),
        "traceability-recorded-implementation-blocked");

    out->implementation_traceability_matrix_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->planned_source_unit_matrix_recorded = 1u;
    out->polynomial_arithmetic_unit_bound = 1u;
    out->ntt_unit_bound = 1u;
    out->sampling_unit_bound = 1u;
    out->compression_unit_bound = 1u;
    out->encoding_unit_bound = 1u;
    out->hash_xof_unit_bound = 1u;
    out->keygen_unit_bound = 1u;
    out->encaps_unit_bound = 1u;
    out->decaps_unit_bound = 1u;
    out->fips_203_section_mapping_recorded = 1u;
    out->sp800_227_usage_mapping_recorded = 1u;
    out->kat_vector_family_mapping_recorded = 1u;
    out->acvp_test_type_mapping_recorded = 1u;
    out->clean_room_review_path_recorded = 1u;
    out->no_external_code_dependency_recorded = 1u;
    out->constant_time_review_mapping_recorded = 0u;
    out->memory_safety_mapping_recorded = 0u;
    out->zeroization_mapping_recorded = 0u;
    out->randomness_mapping_recorded = 0u;
    out->negative_test_mapping_recorded = 0u;
    out->source_digest_mapping_recorded = 0u;
    out->code_owner_mapping_recorded = 0u;
    out->review_disposition_mapping_recorded = 0u;
    out->implementation_trace_accepted = 0u;
    out->implementation_file_digest_manifest_recorded = 0u;
    out->implementation_code_present = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_traceability_items_total = 30u;
    out->required_traceability_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "review-digest-constant-time-memory-randomness-zeroization-negative-and-owner-mappings-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-traceability-matrix-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_implementation_traceability_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->implementation_traceability_matrix_present == 1u &&
           matrix->clean_room_source_boundary_recorded == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->implementation_trace_accepted == 0u &&
           matrix->implementation_code_present == 0u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u &&
           matrix->error == LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_BLOCKED;
}

int latticra_q_seal_ml_kem_implementation_traceability_matrix_allows_trace_acceptance(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->implementation_traceability_matrix_present == 1u &&
           matrix->clean_room_source_boundary_recorded == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->planned_source_units_count == 9u &&
           matrix->planned_test_units_count == 9u &&
           matrix->planned_source_unit_matrix_recorded == 1u &&
           matrix->polynomial_arithmetic_unit_bound == 1u &&
           matrix->ntt_unit_bound == 1u &&
           matrix->sampling_unit_bound == 1u &&
           matrix->compression_unit_bound == 1u &&
           matrix->encoding_unit_bound == 1u &&
           matrix->hash_xof_unit_bound == 1u &&
           matrix->keygen_unit_bound == 1u &&
           matrix->encaps_unit_bound == 1u &&
           matrix->decaps_unit_bound == 1u &&
           matrix->fips_203_section_mapping_recorded == 1u &&
           matrix->sp800_227_usage_mapping_recorded == 1u &&
           matrix->kat_vector_family_mapping_recorded == 1u &&
           matrix->acvp_test_type_mapping_recorded == 1u &&
           matrix->clean_room_review_path_recorded == 1u &&
           matrix->no_external_code_dependency_recorded == 1u &&
           matrix->constant_time_review_mapping_recorded == 1u &&
           matrix->memory_safety_mapping_recorded == 1u &&
           matrix->zeroization_mapping_recorded == 1u &&
           matrix->randomness_mapping_recorded == 1u &&
           matrix->negative_test_mapping_recorded == 1u &&
           matrix->source_digest_mapping_recorded == 1u &&
           matrix->code_owner_mapping_recorded == 1u &&
           matrix->review_disposition_mapping_recorded == 1u &&
           matrix->implementation_trace_accepted == 1u &&
           matrix->implementation_file_digest_manifest_recorded == 1u &&
           matrix->implementation_code_present == 0u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (matrix == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION TRACEABILITY MATRIX\n"
        "traceability_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "traceability_scope=%s\n"
        "traceability_state=%s\n"
        "implementation_traceability_matrix_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "planned_source_unit_matrix_recorded=%u\n"
        "polynomial_arithmetic_unit_bound=%u\n"
        "ntt_unit_bound=%u\n"
        "sampling_unit_bound=%u\n"
        "compression_unit_bound=%u\n"
        "encoding_unit_bound=%u\n"
        "hash_xof_unit_bound=%u\n"
        "keygen_unit_bound=%u\n"
        "encaps_unit_bound=%u\n"
        "decaps_unit_bound=%u\n"
        "fips_203_section_mapping_recorded=%u\n"
        "sp800_227_usage_mapping_recorded=%u\n"
        "kat_vector_family_mapping_recorded=%u\n"
        "acvp_test_type_mapping_recorded=%u\n"
        "clean_room_review_path_recorded=%u\n"
        "no_external_code_dependency_recorded=%u\n"
        "constant_time_review_mapping_recorded=%u\n"
        "memory_safety_mapping_recorded=%u\n"
        "zeroization_mapping_recorded=%u\n"
        "randomness_mapping_recorded=%u\n"
        "negative_test_mapping_recorded=%u\n"
        "source_digest_mapping_recorded=%u\n"
        "code_owner_mapping_recorded=%u\n"
        "review_disposition_mapping_recorded=%u\n"
        "implementation_trace_accepted=%u\n"
        "implementation_file_digest_manifest_recorded=%u\n"
        "implementation_code_present=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_traceability_items_total=%u\n"
        "required_traceability_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        matrix->traceability_profile,
        matrix->formal_title,
        matrix->standards_basis,
        matrix->source_boundary,
        matrix->traceability_scope,
        matrix->traceability_state,
        matrix->implementation_traceability_matrix_present,
        matrix->clean_room_source_boundary_recorded,
        matrix->apple_corecrypto_code_copied,
        matrix->external_provider_code_copied,
        matrix->planned_source_units_count,
        matrix->planned_test_units_count,
        matrix->planned_source_unit_matrix_recorded,
        matrix->polynomial_arithmetic_unit_bound,
        matrix->ntt_unit_bound,
        matrix->sampling_unit_bound,
        matrix->compression_unit_bound,
        matrix->encoding_unit_bound,
        matrix->hash_xof_unit_bound,
        matrix->keygen_unit_bound,
        matrix->encaps_unit_bound,
        matrix->decaps_unit_bound,
        matrix->fips_203_section_mapping_recorded,
        matrix->sp800_227_usage_mapping_recorded,
        matrix->kat_vector_family_mapping_recorded,
        matrix->acvp_test_type_mapping_recorded,
        matrix->clean_room_review_path_recorded,
        matrix->no_external_code_dependency_recorded,
        matrix->constant_time_review_mapping_recorded,
        matrix->memory_safety_mapping_recorded,
        matrix->zeroization_mapping_recorded,
        matrix->randomness_mapping_recorded,
        matrix->negative_test_mapping_recorded,
        matrix->source_digest_mapping_recorded,
        matrix->code_owner_mapping_recorded,
        matrix->review_disposition_mapping_recorded,
        matrix->implementation_trace_accepted,
        matrix->implementation_file_digest_manifest_recorded,
        matrix->implementation_code_present,
        matrix->operation_execution_allowed,
        matrix->production_crypto_claim_allowed,
        matrix->fips_claim_allowed,
        matrix->runtime_authority_granted,
        matrix->required_traceability_items_total,
        matrix->required_traceability_items_satisfied,
        matrix->blocked_reason,
        latticra_q_seal_ml_kem_implementation_traceability_matrix_error_label(matrix->error),
        matrix->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
