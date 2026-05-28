#include "latticra/q_seal_ml_kem_source_digest_verification.h"

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
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification) {
    unsigned satisfied = 0u;

    satisfied += one_if(verification->source_digest_verification_present);
    satisfied += one_if(verification->fips_203_algorithm_bound);
    satisfied += one_if(verification->ssdf_source_integrity_bound);
    satisfied += one_if(verification->digest_algorithm_sha256_required);
    satisfied += one_if(verification->clean_room_source_boundary_recorded);
    satisfied += one_if(verification->source_digest_manifest_bound);
    satisfied += one_if(verification->source_digest_receipt_bound);
    satisfied += one_if(verification->implementation_binding_manifest_bound);
    satisfied += one_if(verification->ci_promotion_evidence_bound);
    satisfied += one_if(verification->receipt_schema_bound);
    satisfied += one_if(verification->normalized_path_policy_bound);
    satisfied += one_if(verification->replay_harness_template_recorded);
    satisfied += one_if(verification->tamper_fixture_template_recorded);
    satisfied += one_if(verification->offline_only_verification_recorded);
    satisfied += one_if(verification->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(verification->external_provider_code_copied == 0u);
    satisfied += one_if(verification->source_receipts_available);
    satisfied += one_if(verification->test_receipts_available);
    satisfied += one_if(verification->build_receipts_available);
    satisfied += one_if(verification->source_digest_replay_executed);
    satisfied += one_if(verification->tamper_fixture_executed);
    satisfied += one_if(verification->ci_verification_harness_recorded);
    satisfied += one_if(verification->verification_result_reviewed);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_source_digest_verification_error_label(
    latticra_q_seal_ml_kem_source_digest_verification_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_verification_prepare(
    latticra_q_seal_ml_kem_source_digest_verification_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->verification_profile,
        sizeof(out->verification_profile),
        "latticra-q-seal-ml-kem-source-digest-verification/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Source Digest Verification");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->verification_scope,
        sizeof(out->verification_scope),
        "ML-KEM-source-digest-replay-harness-before-promotion");
    copy_literal(
        out->verification_state,
        sizeof(out->verification_state),
        "source-digest-verification-harness-blocked");

    out->source_digest_verification_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_source_integrity_bound = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->source_digest_manifest_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->receipt_schema_bound = 1u;
    out->normalized_path_policy_bound = 1u;
    out->replay_harness_template_recorded = 1u;
    out->tamper_fixture_template_recorded = 1u;
    out->offline_only_verification_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_files_created = 0u;
    out->source_receipts_available = 0u;
    out->test_receipts_available = 0u;
    out->build_receipts_available = 0u;
    out->source_digest_replay_executed = 0u;
    out->tamper_fixture_executed = 0u;
    out->ci_verification_harness_recorded = 0u;
    out->verification_result_reviewed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_verification_items_total = 23u;
    out->required_verification_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-test-build-receipts-replay-tamper-ci-and-review-verification-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-source-digest-verification-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_source_digest_verification_is_no_effect(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification) {
    if (verification == NULL) {
        return 0;
    }

    return verification->source_digest_verification_present == 1u &&
           verification->clean_room_source_boundary_recorded == 1u &&
           verification->apple_corecrypto_code_copied == 0u &&
           verification->external_provider_code_copied == 0u &&
           verification->implementation_files_created == 0u &&
           verification->operation_execution_allowed == 0u &&
           verification->production_crypto_claim_allowed == 0u &&
           verification->fips_claim_allowed == 0u &&
           verification->runtime_authority_granted == 0u &&
           verification->error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_VERIFICATION_BLOCKED;
}

int latticra_q_seal_ml_kem_source_digest_verification_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification) {
    if (verification == NULL) {
        return 0;
    }

    return verification->source_digest_verification_present == 1u &&
           verification->fips_203_algorithm_bound == 1u &&
           verification->ssdf_source_integrity_bound == 1u &&
           verification->digest_algorithm_sha256_required == 1u &&
           verification->clean_room_source_boundary_recorded == 1u &&
           verification->source_digest_manifest_bound == 1u &&
           verification->source_digest_receipt_bound == 1u &&
           verification->implementation_binding_manifest_bound == 1u &&
           verification->ci_promotion_evidence_bound == 1u &&
           verification->receipt_schema_bound == 1u &&
           verification->normalized_path_policy_bound == 1u &&
           verification->replay_harness_template_recorded == 1u &&
           verification->tamper_fixture_template_recorded == 1u &&
           verification->offline_only_verification_recorded == 1u &&
           verification->apple_corecrypto_code_copied == 0u &&
           verification->external_provider_code_copied == 0u &&
           verification->implementation_files_created == 1u &&
           verification->source_receipts_available == 1u &&
           verification->test_receipts_available == 1u &&
           verification->build_receipts_available == 1u &&
           verification->source_digest_replay_executed == 1u &&
           verification->tamper_fixture_executed == 1u &&
           verification->ci_verification_harness_recorded == 1u &&
           verification->verification_result_reviewed == 1u &&
           verification->operation_execution_allowed == 1u &&
           verification->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_digest_verification_report(
    const latticra_q_seal_ml_kem_source_digest_verification_t *verification,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (verification == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SOURCE DIGEST VERIFICATION\n"
        "verification_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "verification_scope=%s\n"
        "verification_state=%s\n"
        "source_digest_verification_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_source_integrity_bound=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "source_digest_manifest_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "receipt_schema_bound=%u\n"
        "normalized_path_policy_bound=%u\n"
        "replay_harness_template_recorded=%u\n"
        "tamper_fixture_template_recorded=%u\n"
        "offline_only_verification_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_files_created=%u\n"
        "source_receipts_available=%u\n"
        "test_receipts_available=%u\n"
        "build_receipts_available=%u\n"
        "source_digest_replay_executed=%u\n"
        "tamper_fixture_executed=%u\n"
        "ci_verification_harness_recorded=%u\n"
        "verification_result_reviewed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_verification_items_total=%u\n"
        "required_verification_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        verification->verification_profile,
        verification->formal_title,
        verification->standards_basis,
        verification->verification_scope,
        verification->verification_state,
        verification->source_digest_verification_present,
        verification->fips_203_algorithm_bound,
        verification->ssdf_source_integrity_bound,
        verification->digest_algorithm_sha256_required,
        verification->clean_room_source_boundary_recorded,
        verification->source_digest_manifest_bound,
        verification->source_digest_receipt_bound,
        verification->implementation_binding_manifest_bound,
        verification->ci_promotion_evidence_bound,
        verification->receipt_schema_bound,
        verification->normalized_path_policy_bound,
        verification->replay_harness_template_recorded,
        verification->tamper_fixture_template_recorded,
        verification->offline_only_verification_recorded,
        verification->apple_corecrypto_code_copied,
        verification->external_provider_code_copied,
        verification->implementation_files_created,
        verification->source_receipts_available,
        verification->test_receipts_available,
        verification->build_receipts_available,
        verification->source_digest_replay_executed,
        verification->tamper_fixture_executed,
        verification->ci_verification_harness_recorded,
        verification->verification_result_reviewed,
        verification->operation_execution_allowed,
        verification->production_crypto_claim_allowed,
        verification->fips_claim_allowed,
        verification->runtime_authority_granted,
        verification->required_verification_items_total,
        verification->required_verification_items_satisfied,
        verification->blocked_reason,
        latticra_q_seal_ml_kem_source_digest_verification_error_label(verification->error),
        verification->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
