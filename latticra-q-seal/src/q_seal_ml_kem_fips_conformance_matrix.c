#include "latticra/q_seal_ml_kem_fips_conformance_matrix.h"

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
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix) {
    unsigned satisfied = 0u;

    satisfied += one_if(matrix->fips_conformance_matrix_present);
    satisfied += one_if(matrix->fips_203_source_bound);
    satisfied += one_if(matrix->fips_203_publication_date_recorded);
    satisfied += one_if(matrix->parameter_sets_bound);
    satisfied += one_if(matrix->ml_kem_512_bound);
    satisfied += one_if(matrix->ml_kem_768_bound);
    satisfied += one_if(matrix->ml_kem_1024_bound);
    satisfied += one_if(matrix->algorithm_functions_bound);
    satisfied += one_if(matrix->keygen_algorithm_bound);
    satisfied += one_if(matrix->encaps_algorithm_bound);
    satisfied += one_if(matrix->decaps_algorithm_bound);
    satisfied += one_if(matrix->byte_encoding_requirements_bound);
    satisfied += one_if(matrix->randomness_requirements_bound);
    satisfied += one_if(matrix->hash_xof_boundary_bound);
    satisfied += one_if(matrix->decapsulation_failure_semantics_bound);
    satisfied += one_if(matrix->acvp_kat_consistency_required);
    satisfied += one_if(matrix->clean_room_source_boundary_recorded);
    satisfied += one_if(matrix->implementation_binding_required);
    satisfied += one_if(matrix->per_parameter_trace_recorded);
    satisfied += one_if(matrix->keygen_step_trace_recorded);
    satisfied += one_if(matrix->encaps_step_trace_recorded);
    satisfied += one_if(matrix->decaps_step_trace_recorded);
    satisfied += one_if(matrix->encoding_tests_recorded);
    satisfied += one_if(matrix->failure_semantics_tests_recorded);
    satisfied += one_if(matrix->primitive_mapping_reviewed);
    satisfied += one_if(matrix->errata_review_recorded);
    satisfied += one_if(matrix->implementation_trace_accepted);
    satisfied += one_if(matrix->conformance_matrix_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_fips_conformance_matrix_error_label(
    latticra_q_seal_ml_kem_fips_conformance_matrix_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(
    latticra_q_seal_ml_kem_fips_conformance_matrix_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->conformance_profile,
        sizeof(out->conformance_profile),
        "latticra-q-seal-ml-kem-fips-conformance-matrix/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM FIPS 203 Conformance Matrix");
    copy_literal(out->standards_basis, sizeof(out->standards_basis), "NIST-FIPS-203");
    copy_literal(
        out->conformance_scope,
        sizeof(out->conformance_scope),
        "ML-KEM-FIPS-203-conformance-before-implementation");
    copy_literal(
        out->conformance_state,
        sizeof(out->conformance_state),
        "fips-conformance-matrix-recorded-implementation-trace-missing");

    out->fips_conformance_matrix_present = 1u;
    out->fips_203_source_bound = 1u;
    out->fips_203_publication_date_recorded = 1u;
    out->parameter_sets_bound = 1u;
    out->ml_kem_512_bound = 1u;
    out->ml_kem_768_bound = 1u;
    out->ml_kem_1024_bound = 1u;
    out->algorithm_functions_bound = 1u;
    out->keygen_algorithm_bound = 1u;
    out->encaps_algorithm_bound = 1u;
    out->decaps_algorithm_bound = 1u;
    out->byte_encoding_requirements_bound = 1u;
    out->randomness_requirements_bound = 1u;
    out->hash_xof_boundary_bound = 1u;
    out->decapsulation_failure_semantics_bound = 1u;
    out->acvp_kat_consistency_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->implementation_binding_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->per_parameter_trace_recorded = 0u;
    out->keygen_step_trace_recorded = 0u;
    out->encaps_step_trace_recorded = 0u;
    out->decaps_step_trace_recorded = 0u;
    out->encoding_tests_recorded = 0u;
    out->failure_semantics_tests_recorded = 0u;
    out->primitive_mapping_reviewed = 0u;
    out->errata_review_recorded = 0u;
    out->implementation_trace_accepted = 0u;
    out->conformance_matrix_accepted = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_conformance_items_total = 28u;
    out->required_conformance_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "per-parameter-step-trace-encoding-failure-semantics-primitive-mapping-errata-and-acceptance-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-fips-conformance-matrix-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_fips_conformance_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->fips_conformance_matrix_present == 1u &&
           matrix->clean_room_source_boundary_recorded == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->implementation_trace_accepted == 0u &&
           matrix->conformance_matrix_accepted == 0u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u &&
           matrix->error == LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_BLOCKED;
}

int
latticra_q_seal_ml_kem_fips_conformance_matrix_allows_implementation_trace_acceptance(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->fips_conformance_matrix_present == 1u &&
           matrix->fips_203_source_bound == 1u &&
           matrix->fips_203_publication_date_recorded == 1u &&
           matrix->parameter_sets_bound == 1u &&
           matrix->ml_kem_512_bound == 1u &&
           matrix->ml_kem_768_bound == 1u &&
           matrix->ml_kem_1024_bound == 1u &&
           matrix->algorithm_functions_bound == 1u &&
           matrix->keygen_algorithm_bound == 1u &&
           matrix->encaps_algorithm_bound == 1u &&
           matrix->decaps_algorithm_bound == 1u &&
           matrix->byte_encoding_requirements_bound == 1u &&
           matrix->randomness_requirements_bound == 1u &&
           matrix->hash_xof_boundary_bound == 1u &&
           matrix->decapsulation_failure_semantics_bound == 1u &&
           matrix->acvp_kat_consistency_required == 1u &&
           matrix->clean_room_source_boundary_recorded == 1u &&
           matrix->implementation_binding_required == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->per_parameter_trace_recorded == 1u &&
           matrix->keygen_step_trace_recorded == 1u &&
           matrix->encaps_step_trace_recorded == 1u &&
           matrix->decaps_step_trace_recorded == 1u &&
           matrix->encoding_tests_recorded == 1u &&
           matrix->failure_semantics_tests_recorded == 1u &&
           matrix->primitive_mapping_reviewed == 1u &&
           matrix->errata_review_recorded == 1u &&
           matrix->implementation_trace_accepted == 1u &&
           matrix->conformance_matrix_accepted == 1u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_fips_conformance_matrix_report(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (matrix == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM FIPS 203 CONFORMANCE MATRIX\n"
        "conformance_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "conformance_scope=%s\n"
        "conformance_state=%s\n"
        "fips_conformance_matrix_present=%u\n"
        "fips_203_source_bound=%u\n"
        "fips_203_publication_date_recorded=%u\n"
        "parameter_sets_bound=%u\n"
        "ml_kem_512_bound=%u\n"
        "ml_kem_768_bound=%u\n"
        "ml_kem_1024_bound=%u\n"
        "algorithm_functions_bound=%u\n"
        "keygen_algorithm_bound=%u\n"
        "encaps_algorithm_bound=%u\n"
        "decaps_algorithm_bound=%u\n"
        "byte_encoding_requirements_bound=%u\n"
        "randomness_requirements_bound=%u\n"
        "hash_xof_boundary_bound=%u\n"
        "decapsulation_failure_semantics_bound=%u\n"
        "acvp_kat_consistency_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "implementation_binding_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "per_parameter_trace_recorded=%u\n"
        "keygen_step_trace_recorded=%u\n"
        "encaps_step_trace_recorded=%u\n"
        "decaps_step_trace_recorded=%u\n"
        "encoding_tests_recorded=%u\n"
        "failure_semantics_tests_recorded=%u\n"
        "primitive_mapping_reviewed=%u\n"
        "errata_review_recorded=%u\n"
        "implementation_trace_accepted=%u\n"
        "conformance_matrix_accepted=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_conformance_items_total=%u\n"
        "required_conformance_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        matrix->conformance_profile,
        matrix->formal_title,
        matrix->standards_basis,
        matrix->conformance_scope,
        matrix->conformance_state,
        matrix->fips_conformance_matrix_present,
        matrix->fips_203_source_bound,
        matrix->fips_203_publication_date_recorded,
        matrix->parameter_sets_bound,
        matrix->ml_kem_512_bound,
        matrix->ml_kem_768_bound,
        matrix->ml_kem_1024_bound,
        matrix->algorithm_functions_bound,
        matrix->keygen_algorithm_bound,
        matrix->encaps_algorithm_bound,
        matrix->decaps_algorithm_bound,
        matrix->byte_encoding_requirements_bound,
        matrix->randomness_requirements_bound,
        matrix->hash_xof_boundary_bound,
        matrix->decapsulation_failure_semantics_bound,
        matrix->acvp_kat_consistency_required,
        matrix->clean_room_source_boundary_recorded,
        matrix->implementation_binding_required,
        matrix->apple_corecrypto_code_copied,
        matrix->external_provider_code_copied,
        matrix->per_parameter_trace_recorded,
        matrix->keygen_step_trace_recorded,
        matrix->encaps_step_trace_recorded,
        matrix->decaps_step_trace_recorded,
        matrix->encoding_tests_recorded,
        matrix->failure_semantics_tests_recorded,
        matrix->primitive_mapping_reviewed,
        matrix->errata_review_recorded,
        matrix->implementation_trace_accepted,
        matrix->conformance_matrix_accepted,
        matrix->operation_execution_allowed,
        matrix->production_crypto_claim_allowed,
        matrix->fips_claim_allowed,
        matrix->runtime_authority_granted,
        matrix->required_conformance_items_total,
        matrix->required_conformance_items_satisfied,
        matrix->blocked_reason,
        latticra_q_seal_ml_kem_fips_conformance_matrix_error_label(matrix->error),
        matrix->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
