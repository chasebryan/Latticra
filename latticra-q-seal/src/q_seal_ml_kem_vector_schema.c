#include "latticra/q_seal_ml_kem_vector_schema.h"

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
    const latticra_q_seal_ml_kem_vector_schema_t *schema) {
    unsigned satisfied = 0u;

    satisfied += one_if(schema->fips_203_source_verified);
    satisfied += one_if(schema->acvp_ml_kem_schema_tracked);
    satisfied += one_if(schema->algorithm_ml_kem_recorded);
    satisfied += one_if(schema->revision_fips203_recorded);
    satisfied += one_if(schema->keygen_mode_schema_recorded);
    satisfied += one_if(schema->encap_decap_mode_schema_recorded);
    satisfied += one_if(schema->parameter_sets_recorded);
    satisfied += one_if(schema->keygen_prompt_fields_recorded);
    satisfied += one_if(schema->keygen_response_fields_recorded);
    satisfied += one_if(schema->encap_decap_prompt_fields_recorded);
    satisfied += one_if(schema->encap_decap_response_fields_recorded);
    satisfied += one_if(schema->aft_test_type_recorded);
    satisfied += one_if(schema->val_test_type_recorded);
    satisfied += one_if(schema->key_check_functions_recorded);
    satisfied += one_if(schema->implicit_rejection_case_recorded);
    satisfied += one_if(schema->vector_source_url_recorded);
    satisfied += one_if(schema->vector_source_digest_recorded);
    satisfied += one_if(schema->vector_license_review_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_vector_schema_error_label(
    latticra_q_seal_ml_kem_vector_schema_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_schema_prepare(
    latticra_q_seal_ml_kem_vector_schema_t *out) {
    unsigned parameter_512;
    unsigned parameter_768;
    unsigned parameter_1024;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    parameter_512 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    parameter_768 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    parameter_1024 = parameter_set_is_recorded(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->schema_profile,
        sizeof(out->schema_profile),
        "latticra-q-seal-ml-kem-vector-schema/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Vector Schema");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->acvp_document, sizeof(out->acvp_document), "NIST-ACVP-ML-KEM-JSON");
    copy_literal(out->schema_state, sizeof(out->schema_state), "schema-recorded-vectors-not-loaded");

    out->vector_schema_present = 1u;
    out->fips_203_source_verified = 1u;
    out->acvp_ml_kem_schema_tracked = 1u;
    out->algorithm_ml_kem_recorded = 1u;
    out->revision_fips203_recorded = 1u;
    out->keygen_mode_schema_recorded = 1u;
    out->encap_decap_mode_schema_recorded = 1u;
    out->parameter_sets_recorded =
        parameter_512 == 1u && parameter_768 == 1u && parameter_1024 == 1u;
    out->keygen_prompt_fields_recorded = 1u;
    out->keygen_response_fields_recorded = 1u;
    out->encap_decap_prompt_fields_recorded = 1u;
    out->encap_decap_response_fields_recorded = 1u;
    out->aft_test_type_recorded = 1u;
    out->val_test_type_recorded = 1u;
    out->key_check_functions_recorded = 1u;
    out->implicit_rejection_case_recorded = 1u;
    out->vector_source_url_recorded = 0u;
    out->vector_source_digest_recorded = 0u;
    out->vector_license_review_recorded = 0u;
    out->vector_bundle_loaded = 0u;
    out->vector_json_parser_implemented = 0u;
    out->response_generation_enabled = 0u;
    out->vector_execution_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_schema_items_total = 18u;
    out->required_schema_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "vector-source-digest-license-loader-parser-response-and-execution-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-vector-schema-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_vector_schema_is_schema_only(
    const latticra_q_seal_ml_kem_vector_schema_t *schema) {
    if (schema == NULL) {
        return 0;
    }

    return schema->vector_schema_present == 1u &&
           schema->acvp_ml_kem_schema_tracked == 1u &&
           schema->vector_bundle_loaded == 0u &&
           schema->vector_json_parser_implemented == 0u &&
           schema->response_generation_enabled == 0u &&
           schema->vector_execution_enabled == 0u &&
           schema->acvp_submission_allowed == 0u &&
           schema->operation_execution_allowed == 0u &&
           schema->production_crypto_claim_allowed == 0u &&
           schema->fips_claim_allowed == 0u &&
           schema->runtime_authority_granted == 0u &&
           schema->error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_BLOCKED;
}

int latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(
    const latticra_q_seal_ml_kem_vector_schema_t *schema) {
    if (schema == NULL) {
        return 0;
    }

    return schema->fips_203_source_verified == 1u &&
           schema->acvp_ml_kem_schema_tracked == 1u &&
           schema->algorithm_ml_kem_recorded == 1u &&
           schema->revision_fips203_recorded == 1u &&
           schema->keygen_mode_schema_recorded == 1u &&
           schema->encap_decap_mode_schema_recorded == 1u &&
           schema->parameter_sets_recorded == 1u &&
           schema->keygen_prompt_fields_recorded == 1u &&
           schema->keygen_response_fields_recorded == 1u &&
           schema->encap_decap_prompt_fields_recorded == 1u &&
           schema->encap_decap_response_fields_recorded == 1u &&
           schema->aft_test_type_recorded == 1u &&
           schema->val_test_type_recorded == 1u &&
           schema->key_check_functions_recorded == 1u &&
           schema->implicit_rejection_case_recorded == 1u &&
           schema->vector_source_url_recorded == 1u &&
           schema->vector_source_digest_recorded == 1u &&
           schema->vector_license_review_recorded == 1u &&
           schema->vector_bundle_loaded == 1u &&
           schema->vector_json_parser_implemented == 1u &&
           schema->vector_execution_enabled == 1u &&
           schema->operation_execution_allowed == 1u &&
           schema->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_schema_report(
    const latticra_q_seal_ml_kem_vector_schema_t *schema,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (schema == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM VECTOR SCHEMA\n"
        "schema_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "acvp_document=%s\n"
        "schema_state=%s\n"
        "vector_schema_present=%u\n"
        "fips_203_source_verified=%u\n"
        "acvp_ml_kem_schema_tracked=%u\n"
        "algorithm_ml_kem_recorded=%u\n"
        "revision_fips203_recorded=%u\n"
        "keygen_mode_schema_recorded=%u\n"
        "encap_decap_mode_schema_recorded=%u\n"
        "parameter_sets_recorded=%u\n"
        "keygen_prompt_fields_recorded=%u\n"
        "keygen_response_fields_recorded=%u\n"
        "encap_decap_prompt_fields_recorded=%u\n"
        "encap_decap_response_fields_recorded=%u\n"
        "aft_test_type_recorded=%u\n"
        "val_test_type_recorded=%u\n"
        "key_check_functions_recorded=%u\n"
        "implicit_rejection_case_recorded=%u\n"
        "vector_source_url_recorded=%u\n"
        "vector_source_digest_recorded=%u\n"
        "vector_license_review_recorded=%u\n"
        "vector_bundle_loaded=%u\n"
        "vector_json_parser_implemented=%u\n"
        "response_generation_enabled=%u\n"
        "vector_execution_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_schema_items_total=%u\n"
        "required_schema_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        schema->schema_profile,
        schema->formal_title,
        schema->standards_source,
        schema->acvp_document,
        schema->schema_state,
        schema->vector_schema_present,
        schema->fips_203_source_verified,
        schema->acvp_ml_kem_schema_tracked,
        schema->algorithm_ml_kem_recorded,
        schema->revision_fips203_recorded,
        schema->keygen_mode_schema_recorded,
        schema->encap_decap_mode_schema_recorded,
        schema->parameter_sets_recorded,
        schema->keygen_prompt_fields_recorded,
        schema->keygen_response_fields_recorded,
        schema->encap_decap_prompt_fields_recorded,
        schema->encap_decap_response_fields_recorded,
        schema->aft_test_type_recorded,
        schema->val_test_type_recorded,
        schema->key_check_functions_recorded,
        schema->implicit_rejection_case_recorded,
        schema->vector_source_url_recorded,
        schema->vector_source_digest_recorded,
        schema->vector_license_review_recorded,
        schema->vector_bundle_loaded,
        schema->vector_json_parser_implemented,
        schema->response_generation_enabled,
        schema->vector_execution_enabled,
        schema->acvp_submission_allowed,
        schema->operation_execution_allowed,
        schema->production_crypto_claim_allowed,
        schema->fips_claim_allowed,
        schema->runtime_authority_granted,
        schema->required_schema_items_total,
        schema->required_schema_items_satisfied,
        schema->blocked_reason,
        latticra_q_seal_ml_kem_vector_schema_error_label(schema->error),
        schema->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
