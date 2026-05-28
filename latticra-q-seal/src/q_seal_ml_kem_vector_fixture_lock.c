#include "latticra/q_seal_ml_kem_vector_fixture_lock.h"

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
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock) {
    unsigned satisfied = 0u;

    satisfied += one_if(lock->vector_fixture_lock_present);
    satisfied += one_if(lock->fips_203_algorithm_bound);
    satisfied += one_if(lock->acvp_ml_kem_schema_bound);
    satisfied += one_if(lock->vector_schema_bound);
    satisfied += one_if(lock->vector_source_intake_bound);
    satisfied += one_if(lock->kat_manifest_bound);
    satisfied += one_if(lock->negative_test_evidence_bound);
    satisfied += one_if(lock->implementation_binding_manifest_bound);
    satisfied += one_if(lock->digest_algorithm_sha256_required);
    satisfied += one_if(lock->clean_room_source_boundary_recorded);
    satisfied += one_if(lock->offline_only_fixture_recorded);
    satisfied += one_if(lock->fixture_manifest_schema_recorded);
    satisfied += one_if(lock->fixture_hash_manifest_required);
    satisfied += one_if(lock->ml_kem_512_fixture_required);
    satisfied += one_if(lock->ml_kem_768_fixture_required);
    satisfied += one_if(lock->ml_kem_1024_fixture_required);
    satisfied += one_if(lock->keygen_fixture_family_required);
    satisfied += one_if(lock->encaps_fixture_family_required);
    satisfied += one_if(lock->decaps_fixture_family_required);
    satisfied += one_if(lock->malformed_fixture_family_required);
    satisfied += one_if(lock->implicit_rejection_fixture_required);
    satisfied += one_if(lock->fixture_source_digest_recorded);
    satisfied += one_if(lock->fixture_license_review_recorded);
    satisfied += one_if(lock->fixture_storage_path_recorded);
    satisfied += one_if(lock->fixture_schema_crosscheck_recorded);
    satisfied += one_if(lock->fixture_parameter_coverage_recorded);
    satisfied += one_if(lock->fixture_negative_case_coverage_recorded);
    satisfied += one_if(lock->fixture_import_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_vector_fixture_lock_error_label(
    latticra_q_seal_ml_kem_vector_fixture_lock_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_lock_prepare(
    latticra_q_seal_ml_kem_vector_fixture_lock_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->lock_profile,
        sizeof(out->lock_profile),
        "latticra-q-seal-ml-kem-vector-fixture-lock/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Vector Fixture Lock");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->fixture_scope,
        sizeof(out->fixture_scope),
        "ML-KEM-offline-vector-fixture-lock-before-import");
    copy_literal(
        out->fixture_state,
        sizeof(out->fixture_state),
        "fixture-lock-recorded-vector-bundle-not-loaded");

    out->vector_fixture_lock_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_schema_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_intake_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->offline_only_fixture_recorded = 1u;
    out->fixture_manifest_schema_recorded = 1u;
    out->fixture_hash_manifest_required = 1u;
    out->ml_kem_512_fixture_required = 1u;
    out->ml_kem_768_fixture_required = 1u;
    out->ml_kem_1024_fixture_required = 1u;
    out->keygen_fixture_family_required = 1u;
    out->encaps_fixture_family_required = 1u;
    out->decaps_fixture_family_required = 1u;
    out->malformed_fixture_family_required = 1u;
    out->implicit_rejection_fixture_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->fixture_source_digest_recorded = 0u;
    out->fixture_license_review_recorded = 0u;
    out->fixture_storage_path_recorded = 0u;
    out->fixture_schema_crosscheck_recorded = 0u;
    out->fixture_parameter_coverage_recorded = 0u;
    out->fixture_negative_case_coverage_recorded = 0u;
    out->fixture_import_reviewed = 0u;
    out->fixture_bundle_loaded = 0u;
    out->vector_execution_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_fixture_lock_items_total = 28u;
    out->required_fixture_lock_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-digest-license-storage-schema-coverage-negative-case-and-import-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-vector-fixture-lock-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_vector_fixture_lock_is_no_effect(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock) {
    if (lock == NULL) {
        return 0;
    }

    return lock->vector_fixture_lock_present == 1u &&
           lock->apple_corecrypto_code_copied == 0u &&
           lock->external_provider_code_copied == 0u &&
           lock->fixture_bundle_loaded == 0u &&
           lock->vector_execution_allowed == 0u &&
           lock->acvp_submission_allowed == 0u &&
           lock->operation_execution_allowed == 0u &&
           lock->production_crypto_claim_allowed == 0u &&
           lock->fips_claim_allowed == 0u &&
           lock->runtime_authority_granted == 0u &&
           lock->error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_BLOCKED;
}

int latticra_q_seal_ml_kem_vector_fixture_lock_allows_vector_execution(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock) {
    if (lock == NULL) {
        return 0;
    }

    return lock->vector_fixture_lock_present == 1u &&
           lock->fips_203_algorithm_bound == 1u &&
           lock->acvp_ml_kem_schema_bound == 1u &&
           lock->vector_schema_bound == 1u &&
           lock->vector_source_intake_bound == 1u &&
           lock->kat_manifest_bound == 1u &&
           lock->negative_test_evidence_bound == 1u &&
           lock->implementation_binding_manifest_bound == 1u &&
           lock->digest_algorithm_sha256_required == 1u &&
           lock->clean_room_source_boundary_recorded == 1u &&
           lock->offline_only_fixture_recorded == 1u &&
           lock->fixture_manifest_schema_recorded == 1u &&
           lock->fixture_hash_manifest_required == 1u &&
           lock->ml_kem_512_fixture_required == 1u &&
           lock->ml_kem_768_fixture_required == 1u &&
           lock->ml_kem_1024_fixture_required == 1u &&
           lock->keygen_fixture_family_required == 1u &&
           lock->encaps_fixture_family_required == 1u &&
           lock->decaps_fixture_family_required == 1u &&
           lock->malformed_fixture_family_required == 1u &&
           lock->implicit_rejection_fixture_required == 1u &&
           lock->fixture_source_digest_recorded == 1u &&
           lock->fixture_license_review_recorded == 1u &&
           lock->fixture_storage_path_recorded == 1u &&
           lock->fixture_schema_crosscheck_recorded == 1u &&
           lock->fixture_parameter_coverage_recorded == 1u &&
           lock->fixture_negative_case_coverage_recorded == 1u &&
           lock->fixture_import_reviewed == 1u &&
           lock->fixture_bundle_loaded == 1u &&
           lock->vector_execution_allowed == 1u &&
           lock->operation_execution_allowed == 1u &&
           lock->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_lock_report(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (lock == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM VECTOR FIXTURE LOCK\n"
        "lock_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "fixture_scope=%s\n"
        "fixture_state=%s\n"
        "vector_fixture_lock_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_schema_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_intake_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "offline_only_fixture_recorded=%u\n"
        "fixture_manifest_schema_recorded=%u\n"
        "fixture_hash_manifest_required=%u\n"
        "ml_kem_512_fixture_required=%u\n"
        "ml_kem_768_fixture_required=%u\n"
        "ml_kem_1024_fixture_required=%u\n"
        "keygen_fixture_family_required=%u\n"
        "encaps_fixture_family_required=%u\n"
        "decaps_fixture_family_required=%u\n"
        "malformed_fixture_family_required=%u\n"
        "implicit_rejection_fixture_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "fixture_source_digest_recorded=%u\n"
        "fixture_license_review_recorded=%u\n"
        "fixture_storage_path_recorded=%u\n"
        "fixture_schema_crosscheck_recorded=%u\n"
        "fixture_parameter_coverage_recorded=%u\n"
        "fixture_negative_case_coverage_recorded=%u\n"
        "fixture_import_reviewed=%u\n"
        "fixture_bundle_loaded=%u\n"
        "vector_execution_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_fixture_lock_items_total=%u\n"
        "required_fixture_lock_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        lock->lock_profile,
        lock->formal_title,
        lock->standards_basis,
        lock->fixture_scope,
        lock->fixture_state,
        lock->vector_fixture_lock_present,
        lock->fips_203_algorithm_bound,
        lock->acvp_ml_kem_schema_bound,
        lock->vector_schema_bound,
        lock->vector_source_intake_bound,
        lock->kat_manifest_bound,
        lock->negative_test_evidence_bound,
        lock->implementation_binding_manifest_bound,
        lock->digest_algorithm_sha256_required,
        lock->clean_room_source_boundary_recorded,
        lock->offline_only_fixture_recorded,
        lock->fixture_manifest_schema_recorded,
        lock->fixture_hash_manifest_required,
        lock->ml_kem_512_fixture_required,
        lock->ml_kem_768_fixture_required,
        lock->ml_kem_1024_fixture_required,
        lock->keygen_fixture_family_required,
        lock->encaps_fixture_family_required,
        lock->decaps_fixture_family_required,
        lock->malformed_fixture_family_required,
        lock->implicit_rejection_fixture_required,
        lock->apple_corecrypto_code_copied,
        lock->external_provider_code_copied,
        lock->fixture_source_digest_recorded,
        lock->fixture_license_review_recorded,
        lock->fixture_storage_path_recorded,
        lock->fixture_schema_crosscheck_recorded,
        lock->fixture_parameter_coverage_recorded,
        lock->fixture_negative_case_coverage_recorded,
        lock->fixture_import_reviewed,
        lock->fixture_bundle_loaded,
        lock->vector_execution_allowed,
        lock->acvp_submission_allowed,
        lock->operation_execution_allowed,
        lock->production_crypto_claim_allowed,
        lock->fips_claim_allowed,
        lock->runtime_authority_granted,
        lock->required_fixture_lock_items_total,
        lock->required_fixture_lock_items_satisfied,
        lock->blocked_reason,
        latticra_q_seal_ml_kem_vector_fixture_lock_error_label(lock->error),
        lock->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
