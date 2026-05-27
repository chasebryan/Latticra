#include "latticra/q_seal_ml_kem_vector_source.h"

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
    const latticra_q_seal_ml_kem_vector_source_t *source) {
    unsigned satisfied = 0u;

    satisfied += one_if(source->fips_203_source_verified);
    satisfied += one_if(source->acvp_documentation_tracked);
    satisfied += one_if(source->approved_source_authority_recorded);
    satisfied += one_if(source->source_freshness_policy_recorded);
    satisfied += one_if(source->digest_algorithm_recorded);
    satisfied += one_if(source->bundle_source_url_recorded);
    satisfied += one_if(source->bundle_digest_recorded);
    satisfied += one_if(source->bundle_size_recorded);
    satisfied += one_if(source->bundle_license_review_recorded);
    satisfied += one_if(source->bundle_hash_verified);
    satisfied += one_if(source->bundle_schema_crosscheck_recorded);
    satisfied += one_if(source->errata_review_binding_recorded);
    satisfied += one_if(source->offline_storage_path_recorded);
    satisfied += one_if(source->bundle_import_review_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_vector_source_error_label(
    latticra_q_seal_ml_kem_vector_source_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_source_prepare(
    latticra_q_seal_ml_kem_vector_source_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->source_profile,
        sizeof(out->source_profile),
        "latticra-q-seal-ml-kem-vector-source/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Vector Source Intake");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->acvp_document, sizeof(out->acvp_document), "NIST-ACVP-ML-KEM-JSON");
    copy_literal(
        out->approved_source_authority,
        sizeof(out->approved_source_authority),
        "NIST-ACVP-or-reviewed-equivalent");
    copy_literal(out->digest_algorithm, sizeof(out->digest_algorithm), "SHA-256");
    copy_literal(
        out->source_state,
        sizeof(out->source_state),
        "authority-and-digest-policy-recorded-bundle-not-accepted");

    out->vector_source_intake_present = 1u;
    out->fips_203_source_verified = 1u;
    out->acvp_documentation_tracked = 1u;
    out->approved_source_authority_recorded = 1u;
    out->source_freshness_policy_recorded = 1u;
    out->digest_algorithm_recorded = 1u;
    out->bundle_source_url_recorded = 0u;
    out->bundle_digest_recorded = 0u;
    out->bundle_size_recorded = 0u;
    out->bundle_license_review_recorded = 0u;
    out->bundle_hash_verified = 0u;
    out->bundle_schema_crosscheck_recorded = 0u;
    out->errata_review_binding_recorded = 0u;
    out->offline_storage_path_recorded = 0u;
    out->bundle_import_review_recorded = 0u;
    out->bundle_fetch_performed = 0u;
    out->bundle_imported = 0u;
    out->network_fetch_enabled = 0u;
    out->vector_processing_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_source_items_total = 14u;
    out->required_source_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "bundle-url-digest-size-license-hash-schema-errata-storage-and-import-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-vector-source-intake-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_vector_source_is_no_fetch(
    const latticra_q_seal_ml_kem_vector_source_t *source) {
    if (source == NULL) {
        return 0;
    }

    return source->vector_source_intake_present == 1u &&
           source->bundle_fetch_performed == 0u &&
           source->bundle_imported == 0u &&
           source->network_fetch_enabled == 0u &&
           source->vector_processing_allowed == 0u &&
           source->acvp_submission_allowed == 0u &&
           source->operation_execution_allowed == 0u &&
           source->production_crypto_claim_allowed == 0u &&
           source->fips_claim_allowed == 0u &&
           source->runtime_authority_granted == 0u &&
           source->error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_BLOCKED;
}

int latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(
    const latticra_q_seal_ml_kem_vector_source_t *source) {
    if (source == NULL) {
        return 0;
    }

    return source->fips_203_source_verified == 1u &&
           source->acvp_documentation_tracked == 1u &&
           source->approved_source_authority_recorded == 1u &&
           source->source_freshness_policy_recorded == 1u &&
           source->digest_algorithm_recorded == 1u &&
           source->bundle_source_url_recorded == 1u &&
           source->bundle_digest_recorded == 1u &&
           source->bundle_size_recorded == 1u &&
           source->bundle_license_review_recorded == 1u &&
           source->bundle_hash_verified == 1u &&
           source->bundle_schema_crosscheck_recorded == 1u &&
           source->errata_review_binding_recorded == 1u &&
           source->offline_storage_path_recorded == 1u &&
           source->bundle_import_review_recorded == 1u &&
           source->bundle_imported == 1u &&
           source->network_fetch_enabled == 0u &&
           source->vector_processing_allowed == 1u &&
           source->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_source_report(
    const latticra_q_seal_ml_kem_vector_source_t *source,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (source == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM VECTOR SOURCE INTAKE\n"
        "source_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "acvp_document=%s\n"
        "approved_source_authority=%s\n"
        "digest_algorithm=%s\n"
        "source_state=%s\n"
        "vector_source_intake_present=%u\n"
        "fips_203_source_verified=%u\n"
        "acvp_documentation_tracked=%u\n"
        "approved_source_authority_recorded=%u\n"
        "source_freshness_policy_recorded=%u\n"
        "digest_algorithm_recorded=%u\n"
        "bundle_source_url_recorded=%u\n"
        "bundle_digest_recorded=%u\n"
        "bundle_size_recorded=%u\n"
        "bundle_license_review_recorded=%u\n"
        "bundle_hash_verified=%u\n"
        "bundle_schema_crosscheck_recorded=%u\n"
        "errata_review_binding_recorded=%u\n"
        "offline_storage_path_recorded=%u\n"
        "bundle_import_review_recorded=%u\n"
        "bundle_fetch_performed=%u\n"
        "bundle_imported=%u\n"
        "network_fetch_enabled=%u\n"
        "vector_processing_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_source_items_total=%u\n"
        "required_source_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        source->source_profile,
        source->formal_title,
        source->standards_source,
        source->acvp_document,
        source->approved_source_authority,
        source->digest_algorithm,
        source->source_state,
        source->vector_source_intake_present,
        source->fips_203_source_verified,
        source->acvp_documentation_tracked,
        source->approved_source_authority_recorded,
        source->source_freshness_policy_recorded,
        source->digest_algorithm_recorded,
        source->bundle_source_url_recorded,
        source->bundle_digest_recorded,
        source->bundle_size_recorded,
        source->bundle_license_review_recorded,
        source->bundle_hash_verified,
        source->bundle_schema_crosscheck_recorded,
        source->errata_review_binding_recorded,
        source->offline_storage_path_recorded,
        source->bundle_import_review_recorded,
        source->bundle_fetch_performed,
        source->bundle_imported,
        source->network_fetch_enabled,
        source->vector_processing_allowed,
        source->acvp_submission_allowed,
        source->operation_execution_allowed,
        source->production_crypto_claim_allowed,
        source->fips_claim_allowed,
        source->runtime_authority_granted,
        source->required_source_items_total,
        source->required_source_items_satisfied,
        source->blocked_reason,
        latticra_q_seal_ml_kem_vector_source_error_label(source->error),
        source->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
