#include "latticra/q_seal_ml_kem_acvp_fixture_row_plan.h"

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
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan) {
    unsigned satisfied = 0u;

    satisfied += one_if(plan->acvp_fixture_row_plan_present);
    satisfied += one_if(plan->fips_203_algorithm_bound);
    satisfied += one_if(plan->acvp_ml_kem_json_bound);
    satisfied += one_if(plan->acvp_capability_matrix_bound);
    satisfied += one_if(plan->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(plan->vector_fixture_digest_ledger_bound);
    satisfied += one_if(plan->top_level_vector_set_fields_recorded);
    satisfied += one_if(plan->test_group_fields_recorded);
    satisfied += one_if(plan->test_case_fields_recorded);
    satisfied += one_if(plan->response_group_fields_recorded);
    satisfied += one_if(plan->response_case_fields_recorded);
    satisfied += one_if(plan->parameter_set_rows_planned == 3u);
    satisfied += one_if(
        plan->keygen_aft_rows_required == 3u &&
        plan->keygen_aft_rows_planned == plan->keygen_aft_rows_required);
    satisfied += one_if(
        plan->encapsulation_aft_rows_required == 3u &&
        plan->encapsulation_aft_rows_planned == plan->encapsulation_aft_rows_required);
    satisfied += one_if(
        plan->decapsulation_val_rows_required == 3u &&
        plan->decapsulation_val_rows_planned == plan->decapsulation_val_rows_required);
    satisfied += one_if(
        plan->encapsulation_key_check_val_rows_required == 3u &&
        plan->encapsulation_key_check_val_rows_planned ==
            plan->encapsulation_key_check_val_rows_required);
    satisfied += one_if(
        plan->decapsulation_key_check_val_rows_required == 3u &&
        plan->decapsulation_key_check_val_rows_planned ==
            plan->decapsulation_key_check_val_rows_required);
    satisfied += one_if(
        plan->minimum_fixture_row_classes_required == 15u &&
        plan->minimum_fixture_row_classes_planned ==
            plan->minimum_fixture_row_classes_required);
    satisfied += one_if(plan->fixture_row_ids_reserved);
    satisfied += one_if(plan->digest_columns_required);
    satisfied += one_if(plan->source_url_columns_required);
    satisfied += one_if(plan->license_review_columns_required);
    satisfied += one_if(plan->schema_crosscheck_columns_required);
    satisfied += one_if(plan->review_columns_required);
    satisfied += one_if(plan->clean_room_source_boundary_recorded);
    satisfied += one_if(plan->acvp_registration_json_reviewed);
    satisfied += one_if(plan->capability_matrix_reviewed);
    satisfied += one_if(plan->fixture_row_plan_reviewed);
    satisfied += one_if(plan->fixture_digest_rows_recorded);
    satisfied += one_if(plan->fixture_source_digests_recorded);
    satisfied += one_if(plan->fixture_storage_paths_recorded);
    satisfied += one_if(plan->fixture_license_review_recorded);
    satisfied += one_if(plan->fixture_schema_crosscheck_recorded);
    satisfied += one_if(plan->fixture_import_reviewed);
    satisfied += one_if(plan->fixture_digest_ledger_reviewed);
    satisfied += one_if(plan->row_plan_to_digest_ledger_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_label(
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->row_plan_profile,
        sizeof(out->row_plan_profile),
        "latticra-q-seal-ml-kem-acvp-fixture-row-plan/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Fixture Row Plan");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->row_plan_scope,
        sizeof(out->row_plan_scope),
        "ML-KEM-ACVP-fixture-row-classes-before-digest-ledger-acceptance");
    copy_literal(
        out->row_plan_state,
        sizeof(out->row_plan_state),
        "fixture-row-plan-recorded-digest-rows-missing");

    out->acvp_fixture_row_plan_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->top_level_vector_set_fields_recorded = 1u;
    out->test_group_fields_recorded = 1u;
    out->test_case_fields_recorded = 1u;
    out->response_group_fields_recorded = 1u;
    out->response_case_fields_recorded = 1u;
    out->parameter_set_rows_total = 3u;
    out->parameter_set_rows_planned = 3u;
    out->keygen_aft_rows_required = 3u;
    out->keygen_aft_rows_planned = 3u;
    out->encapsulation_aft_rows_required = 3u;
    out->encapsulation_aft_rows_planned = 3u;
    out->decapsulation_val_rows_required = 3u;
    out->decapsulation_val_rows_planned = 3u;
    out->encapsulation_key_check_val_rows_required = 3u;
    out->encapsulation_key_check_val_rows_planned = 3u;
    out->decapsulation_key_check_val_rows_required = 3u;
    out->decapsulation_key_check_val_rows_planned = 3u;
    out->minimum_fixture_row_classes_required = 15u;
    out->minimum_fixture_row_classes_planned = 15u;
    out->fixture_row_ids_reserved = 1u;
    out->digest_columns_required = 1u;
    out->source_url_columns_required = 1u;
    out->license_review_columns_required = 1u;
    out->schema_crosscheck_columns_required = 1u;
    out->review_columns_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->acvp_registration_json_reviewed = 0u;
    out->capability_matrix_reviewed = 0u;
    out->fixture_row_plan_reviewed = 0u;
    out->fixture_digest_rows_recorded = 0u;
    out->fixture_source_digests_recorded = 0u;
    out->fixture_storage_paths_recorded = 0u;
    out->fixture_license_review_recorded = 0u;
    out->fixture_schema_crosscheck_recorded = 0u;
    out->fixture_import_reviewed = 0u;
    out->fixture_digest_ledger_reviewed = 0u;
    out->row_plan_to_digest_ledger_reviewed = 0u;
    out->fixture_bundle_loaded = 0u;
    out->vector_execution_allowed = 0u;
    out->response_json_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_fixture_row_plan_items_total = 36u;
    out->required_fixture_row_plan_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-row-plan-review-digest-source-storage-license-schema-and-ledger-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-acvp-fixture-row-plan-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_fixture_row_plan_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan) {
    if (plan == NULL) {
        return 0;
    }

    return plan->acvp_fixture_row_plan_present == 1u &&
           plan->clean_room_source_boundary_recorded == 1u &&
           plan->apple_corecrypto_code_copied == 0u &&
           plan->external_provider_code_copied == 0u &&
           plan->fixture_bundle_loaded == 0u &&
           plan->vector_execution_allowed == 0u &&
           plan->response_json_generation_enabled == 0u &&
           plan->acvp_submission_allowed == 0u &&
           plan->operation_execution_allowed == 0u &&
           plan->production_crypto_claim_allowed == 0u &&
           plan->fips_claim_allowed == 0u &&
           plan->runtime_authority_granted == 0u &&
           plan->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_ROW_PLAN_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_fixture_row_plan_allows_fixture_digest_rows(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan) {
    if (plan == NULL) {
        return 0;
    }

    return plan->acvp_fixture_row_plan_present == 1u &&
           plan->fips_203_algorithm_bound == 1u &&
           plan->acvp_ml_kem_json_bound == 1u &&
           plan->acvp_capability_matrix_bound == 1u &&
           plan->acvp_fixture_digest_row_template_bound == 1u &&
           plan->vector_fixture_digest_ledger_bound == 1u &&
           plan->top_level_vector_set_fields_recorded == 1u &&
           plan->test_group_fields_recorded == 1u &&
           plan->test_case_fields_recorded == 1u &&
           plan->response_group_fields_recorded == 1u &&
           plan->response_case_fields_recorded == 1u &&
           plan->parameter_set_rows_planned == 3u &&
           plan->keygen_aft_rows_planned == plan->keygen_aft_rows_required &&
           plan->encapsulation_aft_rows_planned == plan->encapsulation_aft_rows_required &&
           plan->decapsulation_val_rows_planned == plan->decapsulation_val_rows_required &&
           plan->encapsulation_key_check_val_rows_planned ==
               plan->encapsulation_key_check_val_rows_required &&
           plan->decapsulation_key_check_val_rows_planned ==
               plan->decapsulation_key_check_val_rows_required &&
           plan->minimum_fixture_row_classes_planned ==
               plan->minimum_fixture_row_classes_required &&
           plan->fixture_row_ids_reserved == 1u &&
           plan->digest_columns_required == 1u &&
           plan->source_url_columns_required == 1u &&
           plan->license_review_columns_required == 1u &&
           plan->schema_crosscheck_columns_required == 1u &&
           plan->review_columns_required == 1u &&
           plan->clean_room_source_boundary_recorded == 1u &&
           plan->apple_corecrypto_code_copied == 0u &&
           plan->external_provider_code_copied == 0u &&
           plan->acvp_registration_json_reviewed == 1u &&
           plan->capability_matrix_reviewed == 1u &&
           plan->fixture_row_plan_reviewed == 1u &&
           plan->fixture_digest_rows_recorded == 1u &&
           plan->fixture_source_digests_recorded == 1u &&
           plan->fixture_storage_paths_recorded == 1u &&
           plan->fixture_license_review_recorded == 1u &&
           plan->fixture_schema_crosscheck_recorded == 1u &&
           plan->fixture_import_reviewed == 1u &&
           plan->fixture_digest_ledger_reviewed == 1u &&
           plan->row_plan_to_digest_ledger_reviewed == 1u &&
           plan->fixture_bundle_loaded == 0u &&
           plan->vector_execution_allowed == 0u &&
           plan->response_json_generation_enabled == 0u &&
           plan->acvp_submission_allowed == 0u &&
           plan->operation_execution_allowed == 0u &&
           plan->production_crypto_claim_allowed == 0u &&
           plan->fips_claim_allowed == 0u &&
           plan->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_fixture_row_plan_report(
    const latticra_q_seal_ml_kem_acvp_fixture_row_plan_t *plan,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (plan == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP FIXTURE ROW PLAN\n"
        "row_plan_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "row_plan_scope=%s\n"
        "row_plan_state=%s\n"
        "acvp_fixture_row_plan_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "top_level_vector_set_fields_recorded=%u\n"
        "test_group_fields_recorded=%u\n"
        "test_case_fields_recorded=%u\n"
        "response_group_fields_recorded=%u\n"
        "response_case_fields_recorded=%u\n"
        "parameter_set_rows_total=%u\n"
        "parameter_set_rows_planned=%u\n"
        "keygen_aft_rows_required=%u\n"
        "keygen_aft_rows_planned=%u\n"
        "encapsulation_aft_rows_required=%u\n"
        "encapsulation_aft_rows_planned=%u\n"
        "decapsulation_val_rows_required=%u\n"
        "decapsulation_val_rows_planned=%u\n"
        "encapsulation_key_check_val_rows_required=%u\n"
        "encapsulation_key_check_val_rows_planned=%u\n"
        "decapsulation_key_check_val_rows_required=%u\n"
        "decapsulation_key_check_val_rows_planned=%u\n"
        "minimum_fixture_row_classes_required=%u\n"
        "minimum_fixture_row_classes_planned=%u\n"
        "fixture_row_ids_reserved=%u\n"
        "digest_columns_required=%u\n"
        "source_url_columns_required=%u\n"
        "license_review_columns_required=%u\n"
        "schema_crosscheck_columns_required=%u\n"
        "review_columns_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "acvp_registration_json_reviewed=%u\n"
        "capability_matrix_reviewed=%u\n"
        "fixture_row_plan_reviewed=%u\n"
        "fixture_digest_rows_recorded=%u\n"
        "fixture_source_digests_recorded=%u\n"
        "fixture_storage_paths_recorded=%u\n"
        "fixture_license_review_recorded=%u\n"
        "fixture_schema_crosscheck_recorded=%u\n"
        "fixture_import_reviewed=%u\n"
        "fixture_digest_ledger_reviewed=%u\n"
        "row_plan_to_digest_ledger_reviewed=%u\n"
        "fixture_bundle_loaded=%u\n"
        "vector_execution_allowed=%u\n"
        "response_json_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_fixture_row_plan_items_total=%u\n"
        "required_fixture_row_plan_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        plan->row_plan_profile,
        plan->formal_title,
        plan->standards_basis,
        plan->row_plan_scope,
        plan->row_plan_state,
        plan->acvp_fixture_row_plan_present,
        plan->fips_203_algorithm_bound,
        plan->acvp_ml_kem_json_bound,
        plan->acvp_capability_matrix_bound,
        plan->acvp_fixture_digest_row_template_bound,
        plan->vector_fixture_digest_ledger_bound,
        plan->top_level_vector_set_fields_recorded,
        plan->test_group_fields_recorded,
        plan->test_case_fields_recorded,
        plan->response_group_fields_recorded,
        plan->response_case_fields_recorded,
        plan->parameter_set_rows_total,
        plan->parameter_set_rows_planned,
        plan->keygen_aft_rows_required,
        plan->keygen_aft_rows_planned,
        plan->encapsulation_aft_rows_required,
        plan->encapsulation_aft_rows_planned,
        plan->decapsulation_val_rows_required,
        plan->decapsulation_val_rows_planned,
        plan->encapsulation_key_check_val_rows_required,
        plan->encapsulation_key_check_val_rows_planned,
        plan->decapsulation_key_check_val_rows_required,
        plan->decapsulation_key_check_val_rows_planned,
        plan->minimum_fixture_row_classes_required,
        plan->minimum_fixture_row_classes_planned,
        plan->fixture_row_ids_reserved,
        plan->digest_columns_required,
        plan->source_url_columns_required,
        plan->license_review_columns_required,
        plan->schema_crosscheck_columns_required,
        plan->review_columns_required,
        plan->clean_room_source_boundary_recorded,
        plan->apple_corecrypto_code_copied,
        plan->external_provider_code_copied,
        plan->acvp_registration_json_reviewed,
        plan->capability_matrix_reviewed,
        plan->fixture_row_plan_reviewed,
        plan->fixture_digest_rows_recorded,
        plan->fixture_source_digests_recorded,
        plan->fixture_storage_paths_recorded,
        plan->fixture_license_review_recorded,
        plan->fixture_schema_crosscheck_recorded,
        plan->fixture_import_reviewed,
        plan->fixture_digest_ledger_reviewed,
        plan->row_plan_to_digest_ledger_reviewed,
        plan->fixture_bundle_loaded,
        plan->vector_execution_allowed,
        plan->response_json_generation_enabled,
        plan->acvp_submission_allowed,
        plan->operation_execution_allowed,
        plan->production_crypto_claim_allowed,
        plan->fips_claim_allowed,
        plan->runtime_authority_granted,
        plan->required_fixture_row_plan_items_total,
        plan->required_fixture_row_plan_items_satisfied,
        plan->blocked_reason,
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_error_label(plan->error),
        plan->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
