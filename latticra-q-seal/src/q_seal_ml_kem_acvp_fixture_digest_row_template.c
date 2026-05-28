#include "latticra/q_seal_ml_kem_acvp_fixture_digest_row_template.h"

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
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record) {
    unsigned satisfied = 0u;

    satisfied += one_if(template_record->acvp_fixture_digest_row_template_present);
    satisfied += one_if(template_record->fips_203_algorithm_bound);
    satisfied += one_if(template_record->acvp_ml_kem_json_bound);
    satisfied += one_if(template_record->acvp_fixture_row_plan_bound);
    satisfied += one_if(template_record->vector_fixture_digest_ledger_bound);
    satisfied += one_if(template_record->vector_source_intake_bound);
    satisfied += one_if(template_record->vector_schema_bound);
    satisfied += one_if(template_record->vector_fixture_lock_bound);
    satisfied += one_if(template_record->clean_room_source_boundary_recorded);
    satisfied += one_if(template_record->row_id_column_required);
    satisfied += one_if(template_record->parameter_set_column_required);
    satisfied += one_if(template_record->mode_column_required);
    satisfied += one_if(template_record->test_type_column_required);
    satisfied += one_if(template_record->function_column_required);
    satisfied += one_if(template_record->source_url_column_required);
    satisfied += one_if(template_record->sha256_digest_column_required);
    satisfied += one_if(template_record->bundle_size_column_required);
    satisfied += one_if(template_record->storage_path_column_required);
    satisfied += one_if(template_record->license_review_column_required);
    satisfied += one_if(template_record->schema_crosscheck_column_required);
    satisfied += one_if(template_record->reviewer_identity_column_required);
    satisfied += one_if(template_record->review_timestamp_column_required);
    satisfied += one_if(template_record->ci_replay_transcript_column_required);
    satisfied += one_if(template_record->tamper_evidence_column_required);
    satisfied += one_if(
        template_record->planned_fixture_digest_rows_required == 15u &&
        template_record->planned_fixture_digest_rows_reserved ==
            template_record->planned_fixture_digest_rows_required);
    satisfied += one_if(template_record->ml_kem_512_row_class_reserved);
    satisfied += one_if(template_record->ml_kem_768_row_class_reserved);
    satisfied += one_if(template_record->ml_kem_1024_row_class_reserved);
    satisfied += one_if(template_record->keygen_row_class_reserved);
    satisfied += one_if(template_record->encaps_row_class_reserved);
    satisfied += one_if(template_record->decaps_row_class_reserved);
    satisfied += one_if(template_record->val_row_class_reserved);
    satisfied += one_if(template_record->key_check_row_class_reserved);
    satisfied += one_if(template_record->fixture_digest_rows_recorded);
    satisfied += one_if(template_record->source_url_rows_recorded);
    satisfied += one_if(template_record->sha256_digest_rows_recorded);
    satisfied += one_if(template_record->bundle_size_rows_recorded);
    satisfied += one_if(template_record->storage_path_rows_recorded);
    satisfied += one_if(template_record->license_review_rows_recorded);
    satisfied += one_if(template_record->schema_crosscheck_rows_recorded);
    satisfied += one_if(template_record->reviewer_identity_rows_recorded);
    satisfied += one_if(template_record->review_timestamp_rows_recorded);
    satisfied += one_if(template_record->ci_replay_transcript_rows_recorded);
    satisfied += one_if(template_record->tamper_evidence_rows_recorded);
    satisfied += one_if(template_record->digest_row_template_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_label(
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->template_profile,
        sizeof(out->template_profile),
        "latticra-q-seal-ml-kem-acvp-fixture-digest-row-template/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Fixture Digest Row Template");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->template_scope,
        sizeof(out->template_scope),
        "ML-KEM-ACVP-fixture-digest-row-schema-before-ledger-acceptance");
    copy_literal(
        out->template_state,
        sizeof(out->template_state),
        "digest-row-template-recorded-real-rows-missing");

    out->acvp_fixture_digest_row_template_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->vector_source_intake_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->row_id_column_required = 1u;
    out->parameter_set_column_required = 1u;
    out->mode_column_required = 1u;
    out->test_type_column_required = 1u;
    out->function_column_required = 1u;
    out->source_url_column_required = 1u;
    out->sha256_digest_column_required = 1u;
    out->bundle_size_column_required = 1u;
    out->storage_path_column_required = 1u;
    out->license_review_column_required = 1u;
    out->schema_crosscheck_column_required = 1u;
    out->reviewer_identity_column_required = 1u;
    out->review_timestamp_column_required = 1u;
    out->ci_replay_transcript_column_required = 1u;
    out->tamper_evidence_column_required = 1u;
    out->planned_fixture_digest_rows_required = 15u;
    out->planned_fixture_digest_rows_reserved = 15u;
    out->ml_kem_512_row_class_reserved = 1u;
    out->ml_kem_768_row_class_reserved = 1u;
    out->ml_kem_1024_row_class_reserved = 1u;
    out->keygen_row_class_reserved = 1u;
    out->encaps_row_class_reserved = 1u;
    out->decaps_row_class_reserved = 1u;
    out->val_row_class_reserved = 1u;
    out->key_check_row_class_reserved = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->fixture_digest_rows_recorded = 0u;
    out->source_url_rows_recorded = 0u;
    out->sha256_digest_rows_recorded = 0u;
    out->bundle_size_rows_recorded = 0u;
    out->storage_path_rows_recorded = 0u;
    out->license_review_rows_recorded = 0u;
    out->schema_crosscheck_rows_recorded = 0u;
    out->reviewer_identity_rows_recorded = 0u;
    out->review_timestamp_rows_recorded = 0u;
    out->ci_replay_transcript_rows_recorded = 0u;
    out->tamper_evidence_rows_recorded = 0u;
    out->digest_row_template_reviewed = 0u;
    out->fixture_digest_row_acceptance_allowed = 0u;
    out->fixture_bundle_loaded = 0u;
    out->vector_execution_allowed = 0u;
    out->response_json_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_digest_row_template_items_total = 45u;
    out->required_digest_row_template_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-digest-row-source-digest-size-storage-license-schema-review-transcript-and-tamper-records-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-acvp-fixture-digest-row-template-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record) {
    if (template_record == NULL) {
        return 0;
    }

    return template_record->acvp_fixture_digest_row_template_present == 1u &&
           template_record->clean_room_source_boundary_recorded == 1u &&
           template_record->apple_corecrypto_code_copied == 0u &&
           template_record->external_provider_code_copied == 0u &&
           template_record->fixture_digest_row_acceptance_allowed == 0u &&
           template_record->fixture_bundle_loaded == 0u &&
           template_record->vector_execution_allowed == 0u &&
           template_record->response_json_generation_enabled == 0u &&
           template_record->acvp_submission_allowed == 0u &&
           template_record->operation_execution_allowed == 0u &&
           template_record->production_crypto_claim_allowed == 0u &&
           template_record->fips_claim_allowed == 0u &&
           template_record->runtime_authority_granted == 0u &&
           template_record->error ==
               LATTICRA_Q_SEAL_ML_KEM_ACVP_FIXTURE_DIGEST_ROW_TEMPLATE_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_allows_digest_row_acceptance(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record) {
    if (template_record == NULL) {
        return 0;
    }

    return template_record->acvp_fixture_digest_row_template_present == 1u &&
           template_record->fips_203_algorithm_bound == 1u &&
           template_record->acvp_ml_kem_json_bound == 1u &&
           template_record->acvp_fixture_row_plan_bound == 1u &&
           template_record->vector_fixture_digest_ledger_bound == 1u &&
           template_record->vector_source_intake_bound == 1u &&
           template_record->vector_schema_bound == 1u &&
           template_record->vector_fixture_lock_bound == 1u &&
           template_record->clean_room_source_boundary_recorded == 1u &&
           template_record->row_id_column_required == 1u &&
           template_record->parameter_set_column_required == 1u &&
           template_record->mode_column_required == 1u &&
           template_record->test_type_column_required == 1u &&
           template_record->function_column_required == 1u &&
           template_record->source_url_column_required == 1u &&
           template_record->sha256_digest_column_required == 1u &&
           template_record->bundle_size_column_required == 1u &&
           template_record->storage_path_column_required == 1u &&
           template_record->license_review_column_required == 1u &&
           template_record->schema_crosscheck_column_required == 1u &&
           template_record->reviewer_identity_column_required == 1u &&
           template_record->review_timestamp_column_required == 1u &&
           template_record->ci_replay_transcript_column_required == 1u &&
           template_record->tamper_evidence_column_required == 1u &&
           template_record->planned_fixture_digest_rows_reserved ==
               template_record->planned_fixture_digest_rows_required &&
           template_record->ml_kem_512_row_class_reserved == 1u &&
           template_record->ml_kem_768_row_class_reserved == 1u &&
           template_record->ml_kem_1024_row_class_reserved == 1u &&
           template_record->keygen_row_class_reserved == 1u &&
           template_record->encaps_row_class_reserved == 1u &&
           template_record->decaps_row_class_reserved == 1u &&
           template_record->val_row_class_reserved == 1u &&
           template_record->key_check_row_class_reserved == 1u &&
           template_record->apple_corecrypto_code_copied == 0u &&
           template_record->external_provider_code_copied == 0u &&
           template_record->fixture_digest_rows_recorded == 1u &&
           template_record->source_url_rows_recorded == 1u &&
           template_record->sha256_digest_rows_recorded == 1u &&
           template_record->bundle_size_rows_recorded == 1u &&
           template_record->storage_path_rows_recorded == 1u &&
           template_record->license_review_rows_recorded == 1u &&
           template_record->schema_crosscheck_rows_recorded == 1u &&
           template_record->reviewer_identity_rows_recorded == 1u &&
           template_record->review_timestamp_rows_recorded == 1u &&
           template_record->ci_replay_transcript_rows_recorded == 1u &&
           template_record->tamper_evidence_rows_recorded == 1u &&
           template_record->digest_row_template_reviewed == 1u &&
           template_record->fixture_digest_row_acceptance_allowed == 1u &&
           template_record->fixture_bundle_loaded == 0u &&
           template_record->vector_execution_allowed == 0u &&
           template_record->response_json_generation_enabled == 0u &&
           template_record->acvp_submission_allowed == 0u &&
           template_record->operation_execution_allowed == 0u &&
           template_record->production_crypto_claim_allowed == 0u &&
           template_record->fips_claim_allowed == 0u &&
           template_record->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_report(
    const latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t *template_record,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (template_record == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP FIXTURE DIGEST ROW TEMPLATE\n"
        "template_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "template_scope=%s\n"
        "template_state=%s\n"
        "acvp_fixture_digest_row_template_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "vector_source_intake_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "row_id_column_required=%u\n"
        "parameter_set_column_required=%u\n"
        "mode_column_required=%u\n"
        "test_type_column_required=%u\n"
        "function_column_required=%u\n"
        "source_url_column_required=%u\n"
        "sha256_digest_column_required=%u\n"
        "bundle_size_column_required=%u\n"
        "storage_path_column_required=%u\n"
        "license_review_column_required=%u\n"
        "schema_crosscheck_column_required=%u\n"
        "reviewer_identity_column_required=%u\n"
        "review_timestamp_column_required=%u\n"
        "ci_replay_transcript_column_required=%u\n"
        "tamper_evidence_column_required=%u\n"
        "planned_fixture_digest_rows_required=%u\n"
        "planned_fixture_digest_rows_reserved=%u\n"
        "ml_kem_512_row_class_reserved=%u\n"
        "ml_kem_768_row_class_reserved=%u\n"
        "ml_kem_1024_row_class_reserved=%u\n"
        "keygen_row_class_reserved=%u\n"
        "encaps_row_class_reserved=%u\n"
        "decaps_row_class_reserved=%u\n"
        "val_row_class_reserved=%u\n"
        "key_check_row_class_reserved=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "fixture_digest_rows_recorded=%u\n"
        "source_url_rows_recorded=%u\n"
        "sha256_digest_rows_recorded=%u\n"
        "bundle_size_rows_recorded=%u\n"
        "storage_path_rows_recorded=%u\n"
        "license_review_rows_recorded=%u\n"
        "schema_crosscheck_rows_recorded=%u\n"
        "reviewer_identity_rows_recorded=%u\n"
        "review_timestamp_rows_recorded=%u\n"
        "ci_replay_transcript_rows_recorded=%u\n"
        "tamper_evidence_rows_recorded=%u\n"
        "digest_row_template_reviewed=%u\n"
        "fixture_digest_row_acceptance_allowed=%u\n"
        "fixture_bundle_loaded=%u\n"
        "vector_execution_allowed=%u\n"
        "response_json_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_digest_row_template_items_total=%u\n"
        "required_digest_row_template_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        template_record->template_profile,
        template_record->formal_title,
        template_record->standards_basis,
        template_record->template_scope,
        template_record->template_state,
        template_record->acvp_fixture_digest_row_template_present,
        template_record->fips_203_algorithm_bound,
        template_record->acvp_ml_kem_json_bound,
        template_record->acvp_fixture_row_plan_bound,
        template_record->vector_fixture_digest_ledger_bound,
        template_record->vector_source_intake_bound,
        template_record->vector_schema_bound,
        template_record->vector_fixture_lock_bound,
        template_record->clean_room_source_boundary_recorded,
        template_record->row_id_column_required,
        template_record->parameter_set_column_required,
        template_record->mode_column_required,
        template_record->test_type_column_required,
        template_record->function_column_required,
        template_record->source_url_column_required,
        template_record->sha256_digest_column_required,
        template_record->bundle_size_column_required,
        template_record->storage_path_column_required,
        template_record->license_review_column_required,
        template_record->schema_crosscheck_column_required,
        template_record->reviewer_identity_column_required,
        template_record->review_timestamp_column_required,
        template_record->ci_replay_transcript_column_required,
        template_record->tamper_evidence_column_required,
        template_record->planned_fixture_digest_rows_required,
        template_record->planned_fixture_digest_rows_reserved,
        template_record->ml_kem_512_row_class_reserved,
        template_record->ml_kem_768_row_class_reserved,
        template_record->ml_kem_1024_row_class_reserved,
        template_record->keygen_row_class_reserved,
        template_record->encaps_row_class_reserved,
        template_record->decaps_row_class_reserved,
        template_record->val_row_class_reserved,
        template_record->key_check_row_class_reserved,
        template_record->apple_corecrypto_code_copied,
        template_record->external_provider_code_copied,
        template_record->fixture_digest_rows_recorded,
        template_record->source_url_rows_recorded,
        template_record->sha256_digest_rows_recorded,
        template_record->bundle_size_rows_recorded,
        template_record->storage_path_rows_recorded,
        template_record->license_review_rows_recorded,
        template_record->schema_crosscheck_rows_recorded,
        template_record->reviewer_identity_rows_recorded,
        template_record->review_timestamp_rows_recorded,
        template_record->ci_replay_transcript_rows_recorded,
        template_record->tamper_evidence_rows_recorded,
        template_record->digest_row_template_reviewed,
        template_record->fixture_digest_row_acceptance_allowed,
        template_record->fixture_bundle_loaded,
        template_record->vector_execution_allowed,
        template_record->response_json_generation_enabled,
        template_record->acvp_submission_allowed,
        template_record->operation_execution_allowed,
        template_record->production_crypto_claim_allowed,
        template_record->fips_claim_allowed,
        template_record->runtime_authority_granted,
        template_record->required_digest_row_template_items_total,
        template_record->required_digest_row_template_items_satisfied,
        template_record->blocked_reason,
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_error_label(
            template_record->error),
        template_record->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
