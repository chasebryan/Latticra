#include "latticra/q_seal_ml_kem_source_digest_receipt.h"

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
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt) {
    unsigned satisfied = 0u;

    satisfied += one_if(receipt->source_digest_receipt_present);
    satisfied += one_if(receipt->fips_203_algorithm_bound);
    satisfied += one_if(receipt->ssdf_source_integrity_bound);
    satisfied += one_if(receipt->digest_algorithm_sha256_required);
    satisfied += one_if(receipt->clean_room_source_boundary_recorded);
    satisfied += one_if(receipt->source_digest_manifest_bound);
    satisfied += one_if(receipt->implementation_binding_manifest_bound);
    satisfied += one_if(receipt->ci_promotion_evidence_bound);
    satisfied += one_if(receipt->planned_source_receipts_count == 9u);
    satisfied += one_if(receipt->planned_test_receipts_count == 9u);
    satisfied += one_if(receipt->planned_build_receipts_count == 1u);
    satisfied += one_if(receipt->receipt_schema_recorded);
    satisfied += one_if(receipt->normalized_path_policy_recorded);
    satisfied += one_if(receipt->hash_command_policy_recorded);
    satisfied += one_if(receipt->reproducible_snapshot_policy_recorded);
    satisfied += one_if(receipt->tamper_evidence_policy_recorded);
    satisfied += one_if(receipt->source_receipts_recorded);
    satisfied += one_if(receipt->test_receipts_recorded);
    satisfied += one_if(receipt->build_receipts_recorded);
    satisfied += one_if(receipt->source_receipts_verified);
    satisfied += one_if(receipt->reviewed_digest_receipt_recorded);
    satisfied += one_if(receipt->receipt_replay_check_recorded);
    satisfied += one_if(receipt->ci_digest_verification_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_source_digest_receipt_error_label(
    latticra_q_seal_ml_kem_source_digest_receipt_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_receipt_prepare(
    latticra_q_seal_ml_kem_source_digest_receipt_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->receipt_profile,
        sizeof(out->receipt_profile),
        "latticra-q-seal-ml-kem-source-digest-receipt/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Source Digest Receipt");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->receipt_scope,
        sizeof(out->receipt_scope),
        "ML-KEM-clean-room-source-digest-receipts-before-promotion");
    copy_literal(
        out->receipt_state,
        sizeof(out->receipt_state),
        "source-digest-receipt-fixture-blocked");

    out->source_digest_receipt_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_source_integrity_bound = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->source_digest_manifest_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->planned_source_receipts_count = 9u;
    out->planned_test_receipts_count = 9u;
    out->planned_build_receipts_count = 1u;
    out->receipt_schema_recorded = 1u;
    out->normalized_path_policy_recorded = 1u;
    out->hash_command_policy_recorded = 1u;
    out->reproducible_snapshot_policy_recorded = 1u;
    out->tamper_evidence_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_files_created = 0u;
    out->source_receipts_recorded = 0u;
    out->test_receipts_recorded = 0u;
    out->build_receipts_recorded = 0u;
    out->source_receipts_verified = 0u;
    out->reviewed_digest_receipt_recorded = 0u;
    out->receipt_replay_check_recorded = 0u;
    out->ci_digest_verification_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_receipt_items_total = 23u;
    out->required_receipt_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-test-build-receipts-verification-review-ci-and-replay-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-source-digest-receipt-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_source_digest_receipt_is_no_effect(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return receipt->source_digest_receipt_present == 1u &&
           receipt->clean_room_source_boundary_recorded == 1u &&
           receipt->apple_corecrypto_code_copied == 0u &&
           receipt->external_provider_code_copied == 0u &&
           receipt->implementation_files_created == 0u &&
           receipt->operation_execution_allowed == 0u &&
           receipt->production_crypto_claim_allowed == 0u &&
           receipt->fips_claim_allowed == 0u &&
           receipt->runtime_authority_granted == 0u &&
           receipt->error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_RECEIPT_BLOCKED;
}

int latticra_q_seal_ml_kem_source_digest_receipt_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt) {
    if (receipt == NULL) {
        return 0;
    }

    return receipt->source_digest_receipt_present == 1u &&
           receipt->fips_203_algorithm_bound == 1u &&
           receipt->ssdf_source_integrity_bound == 1u &&
           receipt->digest_algorithm_sha256_required == 1u &&
           receipt->clean_room_source_boundary_recorded == 1u &&
           receipt->source_digest_manifest_bound == 1u &&
           receipt->implementation_binding_manifest_bound == 1u &&
           receipt->ci_promotion_evidence_bound == 1u &&
           receipt->planned_source_receipts_count == 9u &&
           receipt->planned_test_receipts_count == 9u &&
           receipt->planned_build_receipts_count == 1u &&
           receipt->receipt_schema_recorded == 1u &&
           receipt->normalized_path_policy_recorded == 1u &&
           receipt->hash_command_policy_recorded == 1u &&
           receipt->reproducible_snapshot_policy_recorded == 1u &&
           receipt->tamper_evidence_policy_recorded == 1u &&
           receipt->apple_corecrypto_code_copied == 0u &&
           receipt->external_provider_code_copied == 0u &&
           receipt->implementation_files_created == 1u &&
           receipt->source_receipts_recorded == 1u &&
           receipt->test_receipts_recorded == 1u &&
           receipt->build_receipts_recorded == 1u &&
           receipt->source_receipts_verified == 1u &&
           receipt->reviewed_digest_receipt_recorded == 1u &&
           receipt->receipt_replay_check_recorded == 1u &&
           receipt->ci_digest_verification_recorded == 1u &&
           receipt->operation_execution_allowed == 1u &&
           receipt->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_receipt_report(
    const latticra_q_seal_ml_kem_source_digest_receipt_t *receipt,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (receipt == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST RECEIPT\n"
        "receipt_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "receipt_scope=%s\n"
        "receipt_state=%s\n"
        "source_digest_receipt_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_source_integrity_bound=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "source_digest_manifest_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "planned_source_receipts_count=%u\n"
        "planned_test_receipts_count=%u\n"
        "planned_build_receipts_count=%u\n"
        "receipt_schema_recorded=%u\n"
        "normalized_path_policy_recorded=%u\n"
        "hash_command_policy_recorded=%u\n"
        "reproducible_snapshot_policy_recorded=%u\n"
        "tamper_evidence_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_files_created=%u\n"
        "source_receipts_recorded=%u\n"
        "test_receipts_recorded=%u\n"
        "build_receipts_recorded=%u\n"
        "source_receipts_verified=%u\n"
        "reviewed_digest_receipt_recorded=%u\n"
        "receipt_replay_check_recorded=%u\n"
        "ci_digest_verification_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_receipt_items_total=%u\n"
        "required_receipt_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        receipt->receipt_profile,
        receipt->formal_title,
        receipt->standards_basis,
        receipt->receipt_scope,
        receipt->receipt_state,
        receipt->source_digest_receipt_present,
        receipt->fips_203_algorithm_bound,
        receipt->ssdf_source_integrity_bound,
        receipt->digest_algorithm_sha256_required,
        receipt->clean_room_source_boundary_recorded,
        receipt->source_digest_manifest_bound,
        receipt->implementation_binding_manifest_bound,
        receipt->ci_promotion_evidence_bound,
        receipt->planned_source_receipts_count,
        receipt->planned_test_receipts_count,
        receipt->planned_build_receipts_count,
        receipt->receipt_schema_recorded,
        receipt->normalized_path_policy_recorded,
        receipt->hash_command_policy_recorded,
        receipt->reproducible_snapshot_policy_recorded,
        receipt->tamper_evidence_policy_recorded,
        receipt->apple_corecrypto_code_copied,
        receipt->external_provider_code_copied,
        receipt->implementation_files_created,
        receipt->source_receipts_recorded,
        receipt->test_receipts_recorded,
        receipt->build_receipts_recorded,
        receipt->source_receipts_verified,
        receipt->reviewed_digest_receipt_recorded,
        receipt->receipt_replay_check_recorded,
        receipt->ci_digest_verification_recorded,
        receipt->operation_execution_allowed,
        receipt->production_crypto_claim_allowed,
        receipt->fips_claim_allowed,
        receipt->runtime_authority_granted,
        receipt->required_receipt_items_total,
        receipt->required_receipt_items_satisfied,
        receipt->blocked_reason,
        latticra_q_seal_ml_kem_source_digest_receipt_error_label(receipt->error),
        receipt->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
