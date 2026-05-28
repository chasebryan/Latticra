#include "latticra/q_seal_ml_kem_vector_fixture_digest_ledger.h"

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
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger) {
    unsigned satisfied = 0u;

    satisfied += one_if(ledger->vector_fixture_digest_ledger_present);
    satisfied += one_if(ledger->fips_203_algorithm_bound);
    satisfied += one_if(ledger->acvp_ml_kem_schema_bound);
    satisfied += one_if(ledger->acvp_fixture_row_plan_bound);
    satisfied += one_if(ledger->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(ledger->vector_schema_bound);
    satisfied += one_if(ledger->vector_source_intake_bound);
    satisfied += one_if(ledger->vector_fixture_lock_bound);
    satisfied += one_if(ledger->kat_manifest_bound);
    satisfied += one_if(ledger->negative_test_evidence_bound);
    satisfied += one_if(ledger->implementation_binding_manifest_bound);
    satisfied += one_if(ledger->digest_algorithm_sha256_required);
    satisfied += one_if(ledger->clean_room_source_boundary_recorded);
    satisfied += one_if(ledger->offline_only_digest_recorded);
    satisfied += one_if(ledger->manifest_row_schema_recorded);
    satisfied += one_if(ledger->canonical_path_policy_recorded);
    satisfied += one_if(ledger->bundle_size_policy_recorded);
    satisfied += one_if(ledger->parameter_coverage_policy_recorded);
    satisfied += one_if(ledger->negative_case_coverage_policy_recorded);
    satisfied += one_if(ledger->import_review_policy_recorded);
    satisfied += one_if(ledger->fixture_source_url_recorded);
    satisfied += one_if(ledger->fixture_source_digest_recorded);
    satisfied += one_if(ledger->fixture_bundle_size_recorded);
    satisfied += one_if(ledger->fixture_license_review_recorded);
    satisfied += one_if(ledger->fixture_storage_path_recorded);
    satisfied += one_if(ledger->fixture_schema_crosscheck_recorded);
    satisfied += one_if(ledger->ml_kem_512_coverage_recorded);
    satisfied += one_if(ledger->ml_kem_768_coverage_recorded);
    satisfied += one_if(ledger->ml_kem_1024_coverage_recorded);
    satisfied += one_if(ledger->keygen_coverage_recorded);
    satisfied += one_if(ledger->encaps_coverage_recorded);
    satisfied += one_if(ledger->decaps_coverage_recorded);
    satisfied += one_if(ledger->negative_case_coverage_recorded);
    satisfied += one_if(ledger->fixture_import_reviewed);
    satisfied += one_if(ledger->fixture_digest_ledger_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_label(
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->ledger_profile,
        sizeof(out->ledger_profile),
        "latticra-q-seal-ml-kem-vector-fixture-digest-ledger/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Vector Fixture Digest Ledger");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->ledger_scope,
        sizeof(out->ledger_scope),
        "ML-KEM-offline-vector-fixture-digest-and-coverage-before-import");
    copy_literal(
        out->ledger_state,
        sizeof(out->ledger_state),
        "fixture-digest-ledger-recorded-records-not-imported");

    out->vector_fixture_digest_ledger_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_schema_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_intake_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->offline_only_digest_recorded = 1u;
    out->manifest_row_schema_recorded = 1u;
    out->canonical_path_policy_recorded = 1u;
    out->bundle_size_policy_recorded = 1u;
    out->parameter_coverage_policy_recorded = 1u;
    out->negative_case_coverage_policy_recorded = 1u;
    out->import_review_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->fixture_source_url_recorded = 0u;
    out->fixture_source_digest_recorded = 0u;
    out->fixture_bundle_size_recorded = 0u;
    out->fixture_license_review_recorded = 0u;
    out->fixture_storage_path_recorded = 0u;
    out->fixture_schema_crosscheck_recorded = 0u;
    out->ml_kem_512_coverage_recorded = 0u;
    out->ml_kem_768_coverage_recorded = 0u;
    out->ml_kem_1024_coverage_recorded = 0u;
    out->keygen_coverage_recorded = 0u;
    out->encaps_coverage_recorded = 0u;
    out->decaps_coverage_recorded = 0u;
    out->negative_case_coverage_recorded = 0u;
    out->fixture_import_reviewed = 0u;
    out->fixture_digest_ledger_reviewed = 0u;
    out->fixture_bundle_loaded = 0u;
    out->vector_execution_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_fixture_digest_items_total = 35u;
    out->required_fixture_digest_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-source-url-digest-size-license-storage-schema-coverage-import-and-review-records-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-vector-fixture-digest-ledger-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_vector_fixture_digest_ledger_is_no_effect(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger) {
    if (ledger == NULL) {
        return 0;
    }

    return ledger->vector_fixture_digest_ledger_present == 1u &&
           ledger->apple_corecrypto_code_copied == 0u &&
           ledger->external_provider_code_copied == 0u &&
           ledger->fixture_bundle_loaded == 0u &&
           ledger->vector_execution_allowed == 0u &&
           ledger->acvp_submission_allowed == 0u &&
           ledger->operation_execution_allowed == 0u &&
           ledger->production_crypto_claim_allowed == 0u &&
           ledger->fips_claim_allowed == 0u &&
           ledger->runtime_authority_granted == 0u &&
           ledger->error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_BLOCKED;
}

int latticra_q_seal_ml_kem_vector_fixture_digest_ledger_allows_fixture_lock(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger) {
    if (ledger == NULL) {
        return 0;
    }

    return ledger->vector_fixture_digest_ledger_present == 1u &&
           ledger->fips_203_algorithm_bound == 1u &&
           ledger->acvp_ml_kem_schema_bound == 1u &&
           ledger->acvp_fixture_row_plan_bound == 1u &&
           ledger->acvp_fixture_digest_row_template_bound == 1u &&
           ledger->vector_schema_bound == 1u &&
           ledger->vector_source_intake_bound == 1u &&
           ledger->vector_fixture_lock_bound == 1u &&
           ledger->kat_manifest_bound == 1u &&
           ledger->negative_test_evidence_bound == 1u &&
           ledger->implementation_binding_manifest_bound == 1u &&
           ledger->digest_algorithm_sha256_required == 1u &&
           ledger->clean_room_source_boundary_recorded == 1u &&
           ledger->offline_only_digest_recorded == 1u &&
           ledger->manifest_row_schema_recorded == 1u &&
           ledger->canonical_path_policy_recorded == 1u &&
           ledger->bundle_size_policy_recorded == 1u &&
           ledger->parameter_coverage_policy_recorded == 1u &&
           ledger->negative_case_coverage_policy_recorded == 1u &&
           ledger->import_review_policy_recorded == 1u &&
           ledger->fixture_source_url_recorded == 1u &&
           ledger->fixture_source_digest_recorded == 1u &&
           ledger->fixture_bundle_size_recorded == 1u &&
           ledger->fixture_license_review_recorded == 1u &&
           ledger->fixture_storage_path_recorded == 1u &&
           ledger->fixture_schema_crosscheck_recorded == 1u &&
           ledger->ml_kem_512_coverage_recorded == 1u &&
           ledger->ml_kem_768_coverage_recorded == 1u &&
           ledger->ml_kem_1024_coverage_recorded == 1u &&
           ledger->keygen_coverage_recorded == 1u &&
           ledger->encaps_coverage_recorded == 1u &&
           ledger->decaps_coverage_recorded == 1u &&
           ledger->negative_case_coverage_recorded == 1u &&
           ledger->fixture_import_reviewed == 1u &&
           ledger->fixture_digest_ledger_reviewed == 1u &&
           ledger->fixture_bundle_loaded == 1u &&
           ledger->vector_execution_allowed == 1u &&
           ledger->operation_execution_allowed == 1u &&
           ledger->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (ledger == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM VECTOR FIXTURE DIGEST LEDGER\n"
        "ledger_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "ledger_scope=%s\n"
        "ledger_state=%s\n"
        "vector_fixture_digest_ledger_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_schema_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_intake_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "offline_only_digest_recorded=%u\n"
        "manifest_row_schema_recorded=%u\n"
        "canonical_path_policy_recorded=%u\n"
        "bundle_size_policy_recorded=%u\n"
        "parameter_coverage_policy_recorded=%u\n"
        "negative_case_coverage_policy_recorded=%u\n"
        "import_review_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "fixture_source_url_recorded=%u\n"
        "fixture_source_digest_recorded=%u\n"
        "fixture_bundle_size_recorded=%u\n"
        "fixture_license_review_recorded=%u\n"
        "fixture_storage_path_recorded=%u\n"
        "fixture_schema_crosscheck_recorded=%u\n"
        "ml_kem_512_coverage_recorded=%u\n"
        "ml_kem_768_coverage_recorded=%u\n"
        "ml_kem_1024_coverage_recorded=%u\n"
        "keygen_coverage_recorded=%u\n"
        "encaps_coverage_recorded=%u\n"
        "decaps_coverage_recorded=%u\n"
        "negative_case_coverage_recorded=%u\n"
        "fixture_import_reviewed=%u\n"
        "fixture_digest_ledger_reviewed=%u\n"
        "fixture_bundle_loaded=%u\n"
        "vector_execution_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_fixture_digest_items_total=%u\n"
        "required_fixture_digest_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        ledger->ledger_profile,
        ledger->formal_title,
        ledger->standards_basis,
        ledger->ledger_scope,
        ledger->ledger_state,
        ledger->vector_fixture_digest_ledger_present,
        ledger->fips_203_algorithm_bound,
        ledger->acvp_ml_kem_schema_bound,
        ledger->acvp_fixture_row_plan_bound,
        ledger->acvp_fixture_digest_row_template_bound,
        ledger->vector_schema_bound,
        ledger->vector_source_intake_bound,
        ledger->vector_fixture_lock_bound,
        ledger->kat_manifest_bound,
        ledger->negative_test_evidence_bound,
        ledger->implementation_binding_manifest_bound,
        ledger->digest_algorithm_sha256_required,
        ledger->clean_room_source_boundary_recorded,
        ledger->offline_only_digest_recorded,
        ledger->manifest_row_schema_recorded,
        ledger->canonical_path_policy_recorded,
        ledger->bundle_size_policy_recorded,
        ledger->parameter_coverage_policy_recorded,
        ledger->negative_case_coverage_policy_recorded,
        ledger->import_review_policy_recorded,
        ledger->apple_corecrypto_code_copied,
        ledger->external_provider_code_copied,
        ledger->fixture_source_url_recorded,
        ledger->fixture_source_digest_recorded,
        ledger->fixture_bundle_size_recorded,
        ledger->fixture_license_review_recorded,
        ledger->fixture_storage_path_recorded,
        ledger->fixture_schema_crosscheck_recorded,
        ledger->ml_kem_512_coverage_recorded,
        ledger->ml_kem_768_coverage_recorded,
        ledger->ml_kem_1024_coverage_recorded,
        ledger->keygen_coverage_recorded,
        ledger->encaps_coverage_recorded,
        ledger->decaps_coverage_recorded,
        ledger->negative_case_coverage_recorded,
        ledger->fixture_import_reviewed,
        ledger->fixture_digest_ledger_reviewed,
        ledger->fixture_bundle_loaded,
        ledger->vector_execution_allowed,
        ledger->acvp_submission_allowed,
        ledger->operation_execution_allowed,
        ledger->production_crypto_claim_allowed,
        ledger->fips_claim_allowed,
        ledger->runtime_authority_granted,
        ledger->required_fixture_digest_items_total,
        ledger->required_fixture_digest_items_satisfied,
        ledger->blocked_reason,
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_label(ledger->error),
        ledger->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
