#include "latticra/q_seal_ml_kem_acvp_intake.h"

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
    const latticra_q_seal_ml_kem_acvp_intake_t *intake) {
    unsigned satisfied = 0u;

    satisfied += one_if(intake->acvp_document_tracked);
    satisfied += one_if(intake->acvp_ml_kem_schema_tracked);
    satisfied += one_if(intake->algorithm_ml_kem_required);
    satisfied += one_if(intake->revision_fips203_required);
    satisfied += one_if(intake->keygen_mode_required);
    satisfied += one_if(intake->encap_decap_mode_required);
    satisfied += one_if(intake->ml_kem_512_required);
    satisfied += one_if(intake->ml_kem_768_required);
    satisfied += one_if(intake->ml_kem_1024_required);
    satisfied += one_if(intake->vector_source_url_recorded);
    satisfied += one_if(intake->vector_bundle_digest_recorded);
    satisfied += one_if(intake->vector_license_review_recorded);
    satisfied += one_if(intake->vector_json_schema_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_intake_error_label(
    latticra_q_seal_ml_kem_acvp_intake_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_intake_prepare(
    latticra_q_seal_ml_kem_acvp_intake_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->intake_profile,
        sizeof(out->intake_profile),
        "latticra-q-seal-ml-kem-acvp-intake/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Intake");
    copy_literal(out->acvp_document, sizeof(out->acvp_document), "NIST-ACVP-ML-KEM-JSON");
    copy_literal(out->algorithm, sizeof(out->algorithm), "ML-KEM");
    copy_literal(out->revision, sizeof(out->revision), "FIPS203");
    copy_literal(out->intake_state, sizeof(out->intake_state), "offline-intake-shape-only");

    out->acvp_intake_present = 1u;
    out->acvp_document_tracked = 1u;
    out->acvp_ml_kem_schema_tracked = 1u;
    out->algorithm_ml_kem_required = 1u;
    out->revision_fips203_required = 1u;
    out->keygen_mode_required = 1u;
    out->encap_decap_mode_required = 1u;
    out->ml_kem_512_required = 1u;
    out->ml_kem_768_required = 1u;
    out->ml_kem_1024_required = 1u;
    out->vector_source_url_recorded = 0u;
    out->vector_bundle_digest_recorded = 0u;
    out->vector_license_review_recorded = 0u;
    out->vector_json_schema_reviewed = 0u;
    out->vector_json_loaded = 0u;
    out->response_json_generation_enabled = 0u;
    out->offline_fixture_only = 1u;
    out->network_session_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_intake_items_total = 13u;
    out->required_intake_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "vector-source-digest-license-schema-review-and-loader-not-recorded");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-acvp-intake-offline-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_intake_is_offline_only(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake) {
    if (intake == NULL) {
        return 0;
    }

    return intake->offline_fixture_only == 1u &&
           intake->network_session_enabled == 0u &&
           intake->acvp_submission_allowed == 0u &&
           intake->operation_execution_allowed == 0u &&
           intake->vector_json_loaded == 0u &&
           intake->response_json_generation_enabled == 0u &&
           intake->production_crypto_claim_allowed == 0u &&
           intake->fips_claim_allowed == 0u &&
           intake->runtime_authority_granted == 0u;
}

int latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake) {
    if (intake == NULL) {
        return 0;
    }

    return intake->acvp_document_tracked == 1u &&
           intake->acvp_ml_kem_schema_tracked == 1u &&
           intake->algorithm_ml_kem_required == 1u &&
           intake->revision_fips203_required == 1u &&
           intake->keygen_mode_required == 1u &&
           intake->encap_decap_mode_required == 1u &&
           intake->ml_kem_512_required == 1u &&
           intake->ml_kem_768_required == 1u &&
           intake->ml_kem_1024_required == 1u &&
           intake->vector_source_url_recorded == 1u &&
           intake->vector_bundle_digest_recorded == 1u &&
           intake->vector_license_review_recorded == 1u &&
           intake->vector_json_schema_reviewed == 1u &&
           intake->vector_json_loaded == 1u &&
           intake->operation_execution_allowed == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_intake_report(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (intake == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP INTAKE\n"
        "intake_profile=%s\n"
        "formal_title=%s\n"
        "acvp_document=%s\n"
        "algorithm=%s\n"
        "revision=%s\n"
        "intake_state=%s\n"
        "acvp_intake_present=%u\n"
        "acvp_document_tracked=%u\n"
        "acvp_ml_kem_schema_tracked=%u\n"
        "algorithm_ml_kem_required=%u\n"
        "revision_fips203_required=%u\n"
        "keygen_mode_required=%u\n"
        "encap_decap_mode_required=%u\n"
        "ml_kem_512_required=%u\n"
        "ml_kem_768_required=%u\n"
        "ml_kem_1024_required=%u\n"
        "vector_source_url_recorded=%u\n"
        "vector_bundle_digest_recorded=%u\n"
        "vector_license_review_recorded=%u\n"
        "vector_json_schema_reviewed=%u\n"
        "vector_json_loaded=%u\n"
        "response_json_generation_enabled=%u\n"
        "offline_fixture_only=%u\n"
        "network_session_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_intake_items_total=%u\n"
        "required_intake_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        intake->intake_profile,
        intake->formal_title,
        intake->acvp_document,
        intake->algorithm,
        intake->revision,
        intake->intake_state,
        intake->acvp_intake_present,
        intake->acvp_document_tracked,
        intake->acvp_ml_kem_schema_tracked,
        intake->algorithm_ml_kem_required,
        intake->revision_fips203_required,
        intake->keygen_mode_required,
        intake->encap_decap_mode_required,
        intake->ml_kem_512_required,
        intake->ml_kem_768_required,
        intake->ml_kem_1024_required,
        intake->vector_source_url_recorded,
        intake->vector_bundle_digest_recorded,
        intake->vector_license_review_recorded,
        intake->vector_json_schema_reviewed,
        intake->vector_json_loaded,
        intake->response_json_generation_enabled,
        intake->offline_fixture_only,
        intake->network_session_enabled,
        intake->acvp_submission_allowed,
        intake->operation_execution_allowed,
        intake->production_crypto_claim_allowed,
        intake->fips_claim_allowed,
        intake->runtime_authority_granted,
        intake->required_intake_items_total,
        intake->required_intake_items_satisfied,
        intake->blocked_reason,
        latticra_q_seal_ml_kem_acvp_intake_error_label(intake->error),
        intake->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
