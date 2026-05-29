#include "latticra/q_seal_ml_kem_kat_manifest.h"

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
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest) {
    unsigned satisfied = 0u;

    satisfied += one_if(manifest->ml_kem_kat_manifest_present);
    satisfied += one_if(manifest->fips_203_algorithm_bound);
    satisfied += one_if(manifest->acvp_ml_kem_schema_bound);
    satisfied += one_if(manifest->acvp_keygen_aft_required);
    satisfied += one_if(manifest->acvp_encapdecap_aft_required);
    satisfied += one_if(manifest->acvp_decapsulation_val_required);
    satisfied += one_if(manifest->acvp_keycheck_val_required);
    satisfied += one_if(manifest->ml_kem_512_coverage_required);
    satisfied += one_if(manifest->ml_kem_768_coverage_required);
    satisfied += one_if(manifest->ml_kem_1024_coverage_required);
    satisfied += one_if(manifest->seed_material_handling_policy_recorded);
    satisfied += one_if(manifest->positive_vector_family_required);
    satisfied += one_if(manifest->negative_vector_family_required);
    satisfied += one_if(manifest->malformed_vector_family_required);
    satisfied += one_if(manifest->implicit_rejection_vector_required);
    satisfied += one_if(manifest->acvp_parser_contract_bound);
    satisfied += one_if(manifest->acvp_response_contract_bound);
    satisfied += one_if(manifest->vector_schema_bound);
    satisfied += one_if(manifest->vector_source_bound);
    satisfied += one_if(manifest->vector_fixture_lock_bound);
    satisfied += one_if(manifest->vector_fixture_digest_ledger_bound);
    satisfied += one_if(manifest->negative_test_evidence_bound);
    satisfied += one_if(manifest->provider_differential_bound);
    satisfied += one_if(manifest->implementation_binding_manifest_bound);
    satisfied += one_if(manifest->clean_room_source_boundary_recorded);
    satisfied += one_if(manifest->no_embedded_vectors_policy_recorded);
    satisfied += one_if(manifest->kat_runner_implementation_present);
    satisfied += one_if(manifest->vector_bundle_digest_recorded);
    satisfied += one_if(manifest->vector_bundle_license_reviewed);
    satisfied += one_if(manifest->vector_bundle_storage_reviewed);
    satisfied += one_if(manifest->kat_parser_reviewed);
    satisfied += one_if(manifest->positive_vectors_verified);
    satisfied += one_if(manifest->negative_vectors_verified);
    satisfied += one_if(manifest->malformed_vectors_verified);
    satisfied += one_if(manifest->cross_provider_differential_recorded);
    satisfied += one_if(manifest->ci_kat_replay_recorded);
    satisfied += one_if(manifest->known_answer_vectors_loaded);
    satisfied += one_if(manifest->known_answer_vectors_verified);
    satisfied += one_if(manifest->acvp_vector_review_recorded);
    satisfied += one_if(manifest->operation_implementation_present);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_kat_manifest_error_label(
    latticra_q_seal_ml_kem_kat_manifest_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_manifest_prepare(
    latticra_q_seal_ml_kem_kat_manifest_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->manifest_profile,
        sizeof(out->manifest_profile),
        "latticra-q-seal-ml-kem-kat-manifest/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM KAT Manifest");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->kat_scope,
        sizeof(out->kat_scope),
        "ML-KEM-known-answer-manifest-before-vector-execution");
    copy_literal(
        out->manifest_state,
        sizeof(out->manifest_state),
        "kat-manifest-recorded-runner-and-vector-evidence-missing");

    out->ml_kem_kat_manifest_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_schema_bound = 1u;
    out->acvp_keygen_aft_required = 1u;
    out->acvp_encapdecap_aft_required = 1u;
    out->acvp_decapsulation_val_required = 1u;
    out->acvp_keycheck_val_required = 1u;
    out->ml_kem_512_coverage_required = 1u;
    out->ml_kem_768_coverage_required = 1u;
    out->ml_kem_1024_coverage_required = 1u;
    out->seed_material_handling_policy_recorded = 1u;
    out->positive_vector_family_required = 1u;
    out->negative_vector_family_required = 1u;
    out->malformed_vector_family_required = 1u;
    out->implicit_rejection_vector_required = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->provider_differential_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->no_embedded_vectors_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->kat_runner_implementation_present = 0u;
    out->vector_bundle_digest_recorded = 0u;
    out->vector_bundle_license_reviewed = 0u;
    out->vector_bundle_storage_reviewed = 0u;
    out->kat_parser_reviewed = 0u;
    out->positive_vectors_verified = 0u;
    out->negative_vectors_verified = 0u;
    out->malformed_vectors_verified = 0u;
    out->cross_provider_differential_recorded = 0u;
    out->ci_kat_replay_recorded = 0u;
    out->known_answer_vectors_loaded = 0u;
    out->known_answer_vectors_verified = 0u;
    out->acvp_vector_review_recorded = 0u;
    out->operation_implementation_present = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_kat_manifest_items_total = 40u;
    out->required_kat_manifest_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "kat-runner-vector-digest-license-storage-parser-review-vector-verification-provider-differential-ci-replay-and-operation-implementation-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-kat-manifest-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_kat_manifest_is_no_effect(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->ml_kem_kat_manifest_present == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->kat_runner_implementation_present == 0u &&
           manifest->known_answer_vectors_loaded == 0u &&
           manifest->known_answer_vectors_verified == 0u &&
           manifest->operation_implementation_present == 0u &&
           manifest->acvp_submission_allowed == 0u &&
           manifest->operation_execution_allowed == 0u &&
           manifest->production_crypto_claim_allowed == 0u &&
           manifest->fips_claim_allowed == 0u &&
           manifest->runtime_authority_granted == 0u &&
           manifest->error == LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_BLOCKED;
}

int latticra_q_seal_ml_kem_kat_manifest_allows_kat_execution(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->ml_kem_kat_manifest_present == 1u &&
           manifest->fips_203_algorithm_bound == 1u &&
           manifest->acvp_ml_kem_schema_bound == 1u &&
           manifest->acvp_keygen_aft_required == 1u &&
           manifest->acvp_encapdecap_aft_required == 1u &&
           manifest->acvp_decapsulation_val_required == 1u &&
           manifest->acvp_keycheck_val_required == 1u &&
           manifest->ml_kem_512_coverage_required == 1u &&
           manifest->ml_kem_768_coverage_required == 1u &&
           manifest->ml_kem_1024_coverage_required == 1u &&
           manifest->seed_material_handling_policy_recorded == 1u &&
           manifest->positive_vector_family_required == 1u &&
           manifest->negative_vector_family_required == 1u &&
           manifest->malformed_vector_family_required == 1u &&
           manifest->implicit_rejection_vector_required == 1u &&
           manifest->acvp_parser_contract_bound == 1u &&
           manifest->acvp_response_contract_bound == 1u &&
           manifest->vector_schema_bound == 1u &&
           manifest->vector_source_bound == 1u &&
           manifest->vector_fixture_lock_bound == 1u &&
           manifest->vector_fixture_digest_ledger_bound == 1u &&
           manifest->negative_test_evidence_bound == 1u &&
           manifest->provider_differential_bound == 1u &&
           manifest->implementation_binding_manifest_bound == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->no_embedded_vectors_policy_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->kat_runner_implementation_present == 1u &&
           manifest->vector_bundle_digest_recorded == 1u &&
           manifest->vector_bundle_license_reviewed == 1u &&
           manifest->vector_bundle_storage_reviewed == 1u &&
           manifest->kat_parser_reviewed == 1u &&
           manifest->positive_vectors_verified == 1u &&
           manifest->negative_vectors_verified == 1u &&
           manifest->malformed_vectors_verified == 1u &&
           manifest->cross_provider_differential_recorded == 1u &&
           manifest->ci_kat_replay_recorded == 1u &&
           manifest->known_answer_vectors_loaded == 1u &&
           manifest->known_answer_vectors_verified == 1u &&
           manifest->acvp_vector_review_recorded == 1u &&
           manifest->operation_implementation_present == 1u &&
           manifest->operation_execution_allowed == 1u &&
           manifest->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_manifest_report(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (manifest == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM KAT MANIFEST\n"
        "manifest_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "kat_scope=%s\n"
        "manifest_state=%s\n"
        "ml_kem_kat_manifest_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_schema_bound=%u\n"
        "acvp_keygen_aft_required=%u\n"
        "acvp_encapdecap_aft_required=%u\n"
        "acvp_decapsulation_val_required=%u\n"
        "acvp_keycheck_val_required=%u\n"
        "ml_kem_512_coverage_required=%u\n"
        "ml_kem_768_coverage_required=%u\n"
        "ml_kem_1024_coverage_required=%u\n"
        "seed_material_handling_policy_recorded=%u\n"
        "positive_vector_family_required=%u\n"
        "negative_vector_family_required=%u\n"
        "malformed_vector_family_required=%u\n"
        "implicit_rejection_vector_required=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "provider_differential_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "no_embedded_vectors_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "kat_runner_implementation_present=%u\n"
        "vector_bundle_digest_recorded=%u\n"
        "vector_bundle_license_reviewed=%u\n"
        "vector_bundle_storage_reviewed=%u\n"
        "kat_parser_reviewed=%u\n"
        "positive_vectors_verified=%u\n"
        "negative_vectors_verified=%u\n"
        "malformed_vectors_verified=%u\n"
        "cross_provider_differential_recorded=%u\n"
        "ci_kat_replay_recorded=%u\n"
        "known_answer_vectors_loaded=%u\n"
        "known_answer_vectors_verified=%u\n"
        "acvp_vector_review_recorded=%u\n"
        "operation_implementation_present=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_kat_manifest_items_total=%u\n"
        "required_kat_manifest_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        manifest->manifest_profile,
        manifest->formal_title,
        manifest->standards_basis,
        manifest->kat_scope,
        manifest->manifest_state,
        manifest->ml_kem_kat_manifest_present,
        manifest->fips_203_algorithm_bound,
        manifest->acvp_ml_kem_schema_bound,
        manifest->acvp_keygen_aft_required,
        manifest->acvp_encapdecap_aft_required,
        manifest->acvp_decapsulation_val_required,
        manifest->acvp_keycheck_val_required,
        manifest->ml_kem_512_coverage_required,
        manifest->ml_kem_768_coverage_required,
        manifest->ml_kem_1024_coverage_required,
        manifest->seed_material_handling_policy_recorded,
        manifest->positive_vector_family_required,
        manifest->negative_vector_family_required,
        manifest->malformed_vector_family_required,
        manifest->implicit_rejection_vector_required,
        manifest->acvp_parser_contract_bound,
        manifest->acvp_response_contract_bound,
        manifest->vector_schema_bound,
        manifest->vector_source_bound,
        manifest->vector_fixture_lock_bound,
        manifest->vector_fixture_digest_ledger_bound,
        manifest->negative_test_evidence_bound,
        manifest->provider_differential_bound,
        manifest->implementation_binding_manifest_bound,
        manifest->clean_room_source_boundary_recorded,
        manifest->no_embedded_vectors_policy_recorded,
        manifest->apple_corecrypto_code_copied,
        manifest->external_provider_code_copied,
        manifest->kat_runner_implementation_present,
        manifest->vector_bundle_digest_recorded,
        manifest->vector_bundle_license_reviewed,
        manifest->vector_bundle_storage_reviewed,
        manifest->kat_parser_reviewed,
        manifest->positive_vectors_verified,
        manifest->negative_vectors_verified,
        manifest->malformed_vectors_verified,
        manifest->cross_provider_differential_recorded,
        manifest->ci_kat_replay_recorded,
        manifest->known_answer_vectors_loaded,
        manifest->known_answer_vectors_verified,
        manifest->acvp_vector_review_recorded,
        manifest->operation_implementation_present,
        manifest->acvp_submission_allowed,
        manifest->operation_execution_allowed,
        manifest->production_crypto_claim_allowed,
        manifest->fips_claim_allowed,
        manifest->runtime_authority_granted,
        manifest->required_kat_manifest_items_total,
        manifest->required_kat_manifest_items_satisfied,
        manifest->blocked_reason,
        latticra_q_seal_ml_kem_kat_manifest_error_label(manifest->error),
        manifest->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
