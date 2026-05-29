#include "latticra/q_seal_ml_kem_receipt_replay_results.h"

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
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results) {
    unsigned satisfied = 0u;

    satisfied += one_if(results->receipt_replay_results_present);
    satisfied += one_if(results->fips_203_algorithm_bound);
    satisfied += one_if(results->ssdf_source_integrity_bound);
    satisfied += one_if(results->digest_algorithm_sha256_required);
    satisfied += one_if(results->clean_room_source_boundary_recorded);
    satisfied += one_if(results->source_digest_manifest_bound);
    satisfied += one_if(results->source_digest_receipt_bound);
    satisfied += one_if(results->source_digest_verification_bound);
    satisfied += one_if(results->implementation_binding_manifest_bound);
    satisfied += one_if(results->ci_promotion_evidence_bound);
    satisfied += one_if(results->source_receipt_result_schema_recorded);
    satisfied += one_if(results->test_receipt_result_schema_recorded);
    satisfied += one_if(results->build_receipt_result_schema_recorded);
    satisfied += one_if(results->replay_command_template_recorded);
    satisfied += one_if(results->tamper_result_template_recorded);
    satisfied += one_if(results->ci_result_binding_recorded);
    satisfied += one_if(results->offline_only_replay_recorded);
    satisfied += one_if(results->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(results->external_provider_code_copied == 0u);
    satisfied += one_if(results->source_replay_results_recorded);
    satisfied += one_if(results->test_replay_results_recorded);
    satisfied += one_if(results->build_replay_results_recorded);
    satisfied += one_if(results->tamper_replay_results_recorded);
    satisfied += one_if(results->replay_result_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_receipt_replay_results_error_label(
    latticra_q_seal_ml_kem_receipt_replay_results_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_receipt_replay_results_prepare(
    latticra_q_seal_ml_kem_receipt_replay_results_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->replay_profile,
        sizeof(out->replay_profile),
        "latticra-q-seal-ml-kem-receipt-replay-results/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Receipt Replay Results");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->replay_scope,
        sizeof(out->replay_scope),
        "ML-KEM-source-digest-replay-results-before-promotion");
    copy_literal(
        out->replay_state,
        sizeof(out->replay_state),
        "receipt-replay-results-fixture-blocked");

    out->receipt_replay_results_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_source_integrity_bound = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->source_digest_manifest_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->source_receipt_result_schema_recorded = 1u;
    out->test_receipt_result_schema_recorded = 1u;
    out->build_receipt_result_schema_recorded = 1u;
    out->replay_command_template_recorded = 1u;
    out->tamper_result_template_recorded = 1u;
    out->ci_result_binding_recorded = 1u;
    out->offline_only_replay_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_files_created = 0u;
    out->source_replay_results_recorded = 0u;
    out->test_replay_results_recorded = 0u;
    out->build_replay_results_recorded = 0u;
    out->tamper_replay_results_recorded = 0u;
    out->replay_result_reviewed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_replay_items_total = 24u;
    out->required_replay_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-test-build-tamper-replay-results-and-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-receipt-replay-results-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_receipt_replay_results_is_no_effect(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results) {
    if (results == NULL) {
        return 0;
    }

    return results->receipt_replay_results_present == 1u &&
           results->clean_room_source_boundary_recorded == 1u &&
           results->apple_corecrypto_code_copied == 0u &&
           results->external_provider_code_copied == 0u &&
           results->implementation_files_created == 0u &&
           results->operation_execution_allowed == 0u &&
           results->production_crypto_claim_allowed == 0u &&
           results->fips_claim_allowed == 0u &&
           results->runtime_authority_granted == 0u &&
           results->error == LATTICRA_Q_SEAL_ML_KEM_RECEIPT_REPLAY_RESULTS_BLOCKED;
}

int latticra_q_seal_ml_kem_receipt_replay_results_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results) {
    if (results == NULL) {
        return 0;
    }

    return results->receipt_replay_results_present == 1u &&
           results->fips_203_algorithm_bound == 1u &&
           results->ssdf_source_integrity_bound == 1u &&
           results->digest_algorithm_sha256_required == 1u &&
           results->clean_room_source_boundary_recorded == 1u &&
           results->source_digest_manifest_bound == 1u &&
           results->source_digest_receipt_bound == 1u &&
           results->source_digest_verification_bound == 1u &&
           results->implementation_binding_manifest_bound == 1u &&
           results->ci_promotion_evidence_bound == 1u &&
           results->source_receipt_result_schema_recorded == 1u &&
           results->test_receipt_result_schema_recorded == 1u &&
           results->build_receipt_result_schema_recorded == 1u &&
           results->replay_command_template_recorded == 1u &&
           results->tamper_result_template_recorded == 1u &&
           results->ci_result_binding_recorded == 1u &&
           results->offline_only_replay_recorded == 1u &&
           results->apple_corecrypto_code_copied == 0u &&
           results->external_provider_code_copied == 0u &&
           results->implementation_files_created == 1u &&
           results->source_replay_results_recorded == 1u &&
           results->test_replay_results_recorded == 1u &&
           results->build_replay_results_recorded == 1u &&
           results->tamper_replay_results_recorded == 1u &&
           results->replay_result_reviewed == 1u &&
           results->operation_execution_allowed == 1u &&
           results->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_receipt_replay_results_report(
    const latticra_q_seal_ml_kem_receipt_replay_results_t *results,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (results == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM RECEIPT REPLAY RESULTS\n"
        "replay_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "replay_scope=%s\n"
        "replay_state=%s\n"
        "receipt_replay_results_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_source_integrity_bound=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "source_digest_manifest_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "source_receipt_result_schema_recorded=%u\n"
        "test_receipt_result_schema_recorded=%u\n"
        "build_receipt_result_schema_recorded=%u\n"
        "replay_command_template_recorded=%u\n"
        "tamper_result_template_recorded=%u\n"
        "ci_result_binding_recorded=%u\n"
        "offline_only_replay_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_files_created=%u\n"
        "source_replay_results_recorded=%u\n"
        "test_replay_results_recorded=%u\n"
        "build_replay_results_recorded=%u\n"
        "tamper_replay_results_recorded=%u\n"
        "replay_result_reviewed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_replay_items_total=%u\n"
        "required_replay_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        results->replay_profile,
        results->formal_title,
        results->standards_basis,
        results->replay_scope,
        results->replay_state,
        results->receipt_replay_results_present,
        results->fips_203_algorithm_bound,
        results->ssdf_source_integrity_bound,
        results->digest_algorithm_sha256_required,
        results->clean_room_source_boundary_recorded,
        results->source_digest_manifest_bound,
        results->source_digest_receipt_bound,
        results->source_digest_verification_bound,
        results->implementation_binding_manifest_bound,
        results->ci_promotion_evidence_bound,
        results->source_receipt_result_schema_recorded,
        results->test_receipt_result_schema_recorded,
        results->build_receipt_result_schema_recorded,
        results->replay_command_template_recorded,
        results->tamper_result_template_recorded,
        results->ci_result_binding_recorded,
        results->offline_only_replay_recorded,
        results->apple_corecrypto_code_copied,
        results->external_provider_code_copied,
        results->implementation_files_created,
        results->source_replay_results_recorded,
        results->test_replay_results_recorded,
        results->build_replay_results_recorded,
        results->tamper_replay_results_recorded,
        results->replay_result_reviewed,
        results->operation_execution_allowed,
        results->production_crypto_claim_allowed,
        results->fips_claim_allowed,
        results->runtime_authority_granted,
        results->required_replay_items_total,
        results->required_replay_items_satisfied,
        results->blocked_reason,
        latticra_q_seal_ml_kem_receipt_replay_results_error_label(results->error),
        results->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
