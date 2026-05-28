#include "latticra/q_seal_ml_kem_acvp_capability_matrix.h"

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
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix) {
    unsigned satisfied = 0u;

    satisfied += one_if(matrix->acvp_capability_matrix_present);
    satisfied += one_if(matrix->fips_203_algorithm_bound);
    satisfied += one_if(matrix->acvp_ml_kem_json_bound);
    satisfied += one_if(matrix->algorithm_ml_kem_recorded);
    satisfied += one_if(matrix->revision_fips203_recorded);
    satisfied += one_if(matrix->keygen_mode_required);
    satisfied += one_if(matrix->encap_decap_mode_required);
    satisfied += one_if(matrix->ml_kem_512_parameter_set_required);
    satisfied += one_if(matrix->ml_kem_768_parameter_set_required);
    satisfied += one_if(matrix->ml_kem_1024_parameter_set_required);
    satisfied += one_if(matrix->keygen_aft_required);
    satisfied += one_if(matrix->encap_decap_aft_required);
    satisfied += one_if(matrix->decapsulation_val_required);
    satisfied += one_if(matrix->encapsulation_function_required);
    satisfied += one_if(matrix->decapsulation_function_required);
    satisfied += one_if(matrix->encapsulation_key_check_required);
    satisfied += one_if(matrix->decapsulation_key_check_required);
    satisfied += one_if(matrix->response_schema_keygen_bound);
    satisfied += one_if(matrix->response_schema_encap_decap_bound);
    satisfied += one_if(matrix->capability_exchange_policy_recorded);
    satisfied += one_if(matrix->prereq_sha_validation_policy_recorded);
    satisfied += one_if(matrix->vector_source_intake_bound);
    satisfied += one_if(matrix->vector_fixture_digest_ledger_bound);
    satisfied += one_if(matrix->clean_room_source_boundary_recorded);
    satisfied += one_if(matrix->acvp_registration_json_reviewed);
    satisfied += one_if(matrix->capability_matrix_reviewed);
    satisfied += one_if(matrix->keygen_parameter_coverage_reviewed);
    satisfied += one_if(matrix->encap_decap_parameter_coverage_reviewed);
    satisfied += one_if(matrix->function_coverage_reviewed);
    satisfied += one_if(matrix->response_schema_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_capability_matrix_error_label(
    latticra_q_seal_ml_kem_acvp_capability_matrix_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(
    latticra_q_seal_ml_kem_acvp_capability_matrix_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->matrix_profile,
        sizeof(out->matrix_profile),
        "latticra-q-seal-ml-kem-acvp-capability-matrix/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Capability Matrix");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->matrix_scope,
        sizeof(out->matrix_scope),
        "ML-KEM-ACVP-capability-coverage-before-fixture-row-planning");
    copy_literal(
        out->matrix_state,
        sizeof(out->matrix_state),
        "capability-matrix-recorded-review-missing");

    out->acvp_capability_matrix_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->algorithm_ml_kem_recorded = 1u;
    out->revision_fips203_recorded = 1u;
    out->keygen_mode_required = 1u;
    out->encap_decap_mode_required = 1u;
    out->ml_kem_512_parameter_set_required = 1u;
    out->ml_kem_768_parameter_set_required = 1u;
    out->ml_kem_1024_parameter_set_required = 1u;
    out->keygen_aft_required = 1u;
    out->encap_decap_aft_required = 1u;
    out->decapsulation_val_required = 1u;
    out->encapsulation_function_required = 1u;
    out->decapsulation_function_required = 1u;
    out->encapsulation_key_check_required = 1u;
    out->decapsulation_key_check_required = 1u;
    out->response_schema_keygen_bound = 1u;
    out->response_schema_encap_decap_bound = 1u;
    out->capability_exchange_policy_recorded = 1u;
    out->prereq_sha_validation_policy_recorded = 1u;
    out->vector_source_intake_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->acvp_registration_json_reviewed = 0u;
    out->capability_matrix_reviewed = 0u;
    out->keygen_parameter_coverage_reviewed = 0u;
    out->encap_decap_parameter_coverage_reviewed = 0u;
    out->function_coverage_reviewed = 0u;
    out->response_schema_reviewed = 0u;
    out->fixture_row_generation_allowed = 0u;
    out->vector_json_loaded = 0u;
    out->response_json_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_capability_items_total = 30u;
    out->required_capability_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "acvp-registration-capability-coverage-function-response-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-acvp-capability-matrix-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_capability_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->acvp_capability_matrix_present == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->fixture_row_generation_allowed == 0u &&
           matrix->vector_json_loaded == 0u &&
           matrix->response_json_generation_enabled == 0u &&
           matrix->acvp_submission_allowed == 0u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u &&
           matrix->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_capability_matrix_allows_fixture_row_planning(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix) {
    if (matrix == NULL) {
        return 0;
    }

    return matrix->acvp_capability_matrix_present == 1u &&
           matrix->fips_203_algorithm_bound == 1u &&
           matrix->acvp_ml_kem_json_bound == 1u &&
           matrix->algorithm_ml_kem_recorded == 1u &&
           matrix->revision_fips203_recorded == 1u &&
           matrix->keygen_mode_required == 1u &&
           matrix->encap_decap_mode_required == 1u &&
           matrix->ml_kem_512_parameter_set_required == 1u &&
           matrix->ml_kem_768_parameter_set_required == 1u &&
           matrix->ml_kem_1024_parameter_set_required == 1u &&
           matrix->keygen_aft_required == 1u &&
           matrix->encap_decap_aft_required == 1u &&
           matrix->decapsulation_val_required == 1u &&
           matrix->encapsulation_function_required == 1u &&
           matrix->decapsulation_function_required == 1u &&
           matrix->encapsulation_key_check_required == 1u &&
           matrix->decapsulation_key_check_required == 1u &&
           matrix->response_schema_keygen_bound == 1u &&
           matrix->response_schema_encap_decap_bound == 1u &&
           matrix->capability_exchange_policy_recorded == 1u &&
           matrix->prereq_sha_validation_policy_recorded == 1u &&
           matrix->vector_source_intake_bound == 1u &&
           matrix->vector_fixture_digest_ledger_bound == 1u &&
           matrix->clean_room_source_boundary_recorded == 1u &&
           matrix->apple_corecrypto_code_copied == 0u &&
           matrix->external_provider_code_copied == 0u &&
           matrix->acvp_registration_json_reviewed == 1u &&
           matrix->capability_matrix_reviewed == 1u &&
           matrix->keygen_parameter_coverage_reviewed == 1u &&
           matrix->encap_decap_parameter_coverage_reviewed == 1u &&
           matrix->function_coverage_reviewed == 1u &&
           matrix->response_schema_reviewed == 1u &&
           matrix->fixture_row_generation_allowed == 1u &&
           matrix->vector_json_loaded == 0u &&
           matrix->response_json_generation_enabled == 0u &&
           matrix->acvp_submission_allowed == 0u &&
           matrix->operation_execution_allowed == 0u &&
           matrix->production_crypto_claim_allowed == 0u &&
           matrix->fips_claim_allowed == 0u &&
           matrix->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_capability_matrix_report(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (matrix == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP CAPABILITY MATRIX\n"
        "matrix_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "matrix_scope=%s\n"
        "matrix_state=%s\n"
        "acvp_capability_matrix_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "algorithm_ml_kem_recorded=%u\n"
        "revision_fips203_recorded=%u\n"
        "keygen_mode_required=%u\n"
        "encap_decap_mode_required=%u\n"
        "ml_kem_512_parameter_set_required=%u\n"
        "ml_kem_768_parameter_set_required=%u\n"
        "ml_kem_1024_parameter_set_required=%u\n"
        "keygen_aft_required=%u\n"
        "encap_decap_aft_required=%u\n"
        "decapsulation_val_required=%u\n"
        "encapsulation_function_required=%u\n"
        "decapsulation_function_required=%u\n"
        "encapsulation_key_check_required=%u\n"
        "decapsulation_key_check_required=%u\n"
        "response_schema_keygen_bound=%u\n"
        "response_schema_encap_decap_bound=%u\n"
        "capability_exchange_policy_recorded=%u\n"
        "prereq_sha_validation_policy_recorded=%u\n"
        "vector_source_intake_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "acvp_registration_json_reviewed=%u\n"
        "capability_matrix_reviewed=%u\n"
        "keygen_parameter_coverage_reviewed=%u\n"
        "encap_decap_parameter_coverage_reviewed=%u\n"
        "function_coverage_reviewed=%u\n"
        "response_schema_reviewed=%u\n"
        "fixture_row_generation_allowed=%u\n"
        "vector_json_loaded=%u\n"
        "response_json_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_capability_items_total=%u\n"
        "required_capability_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        matrix->matrix_profile,
        matrix->formal_title,
        matrix->standards_basis,
        matrix->matrix_scope,
        matrix->matrix_state,
        matrix->acvp_capability_matrix_present,
        matrix->fips_203_algorithm_bound,
        matrix->acvp_ml_kem_json_bound,
        matrix->algorithm_ml_kem_recorded,
        matrix->revision_fips203_recorded,
        matrix->keygen_mode_required,
        matrix->encap_decap_mode_required,
        matrix->ml_kem_512_parameter_set_required,
        matrix->ml_kem_768_parameter_set_required,
        matrix->ml_kem_1024_parameter_set_required,
        matrix->keygen_aft_required,
        matrix->encap_decap_aft_required,
        matrix->decapsulation_val_required,
        matrix->encapsulation_function_required,
        matrix->decapsulation_function_required,
        matrix->encapsulation_key_check_required,
        matrix->decapsulation_key_check_required,
        matrix->response_schema_keygen_bound,
        matrix->response_schema_encap_decap_bound,
        matrix->capability_exchange_policy_recorded,
        matrix->prereq_sha_validation_policy_recorded,
        matrix->vector_source_intake_bound,
        matrix->vector_fixture_digest_ledger_bound,
        matrix->clean_room_source_boundary_recorded,
        matrix->apple_corecrypto_code_copied,
        matrix->external_provider_code_copied,
        matrix->acvp_registration_json_reviewed,
        matrix->capability_matrix_reviewed,
        matrix->keygen_parameter_coverage_reviewed,
        matrix->encap_decap_parameter_coverage_reviewed,
        matrix->function_coverage_reviewed,
        matrix->response_schema_reviewed,
        matrix->fixture_row_generation_allowed,
        matrix->vector_json_loaded,
        matrix->response_json_generation_enabled,
        matrix->acvp_submission_allowed,
        matrix->operation_execution_allowed,
        matrix->production_crypto_claim_allowed,
        matrix->fips_claim_allowed,
        matrix->runtime_authority_granted,
        matrix->required_capability_items_total,
        matrix->required_capability_items_satisfied,
        matrix->blocked_reason,
        latticra_q_seal_ml_kem_acvp_capability_matrix_error_label(matrix->error),
        matrix->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
