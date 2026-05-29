#include "latticra/q_seal_ml_kem_code_owner_review.h"

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
    const latticra_q_seal_ml_kem_code_owner_review_t *review) {
    unsigned satisfied = 0u;

    satisfied += one_if(review->code_owner_review_evidence_present);
    satisfied += one_if(review->ssdf_review_practice_bound);
    satisfied += one_if(review->fips_203_algorithm_bound);
    satisfied += one_if(review->clean_room_review_policy_recorded);
    satisfied += one_if(review->implementation_binding_manifest_bound);
    satisfied += one_if(review->source_digest_manifest_bound);
    satisfied += one_if(review->ci_promotion_evidence_bound);
    satisfied += one_if(review->dual_reviewer_required);
    satisfied += one_if(review->cryptography_reviewer_required);
    satisfied += one_if(review->security_reviewer_required);
    satisfied += one_if(review->code_owner_file_required);
    satisfied += one_if(review->reviewer_independence_required);
    satisfied += one_if(review->standards_traceability_required);
    satisfied += one_if(review->side_channel_reviewer_required);
    satisfied += one_if(review->reviewer_identities_recorded);
    satisfied += one_if(review->code_owner_file_recorded);
    satisfied += one_if(review->cryptography_review_recorded);
    satisfied += one_if(review->security_review_recorded);
    satisfied += one_if(review->standards_traceability_review_recorded);
    satisfied += one_if(review->side_channel_review_recorded);
    satisfied += one_if(review->source_digest_review_recorded);
    satisfied += one_if(review->blocking_findings_closed);
    satisfied += one_if(review->approval_receipt_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_code_owner_review_error_label(
    latticra_q_seal_ml_kem_code_owner_review_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_code_owner_review_prepare(
    latticra_q_seal_ml_kem_code_owner_review_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->review_profile,
        sizeof(out->review_profile),
        "latticra-q-seal-ml-kem-code-owner-review/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Code Owner Review");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->review_scope,
        sizeof(out->review_scope),
        "ML-KEM-clean-room-source-review-before-promotion");
    copy_literal(out->review_state, sizeof(out->review_state), "code-owner-review-blocked");

    out->code_owner_review_evidence_present = 1u;
    out->ssdf_review_practice_bound = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->clean_room_review_policy_recorded = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->source_digest_manifest_required = 1u;
    out->source_digest_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->dual_reviewer_required = 1u;
    out->cryptography_reviewer_required = 1u;
    out->security_reviewer_required = 1u;
    out->code_owner_file_required = 1u;
    out->reviewer_independence_required = 1u;
    out->standards_traceability_required = 1u;
    out->side_channel_reviewer_required = 1u;
    out->reviewer_identities_recorded = 0u;
    out->code_owner_file_recorded = 0u;
    out->cryptography_review_recorded = 0u;
    out->security_review_recorded = 0u;
    out->standards_traceability_review_recorded = 0u;
    out->side_channel_review_recorded = 0u;
    out->source_digest_review_recorded = 0u;
    out->blocking_findings_closed = 0u;
    out->approval_receipt_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_review_items_total = 23u;
    out->required_review_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "reviewer-identities-codeowners-crypto-security-standards-side-channel-digest-approval-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-code-owner-review-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_code_owner_review_is_no_effect(
    const latticra_q_seal_ml_kem_code_owner_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->code_owner_review_evidence_present == 1u &&
           review->operation_execution_allowed == 0u &&
           review->production_crypto_claim_allowed == 0u &&
           review->fips_claim_allowed == 0u &&
           review->runtime_authority_granted == 0u &&
           review->error == LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_BLOCKED;
}

int latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_code_owner_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->code_owner_review_evidence_present == 1u &&
           review->ssdf_review_practice_bound == 1u &&
           review->fips_203_algorithm_bound == 1u &&
           review->clean_room_review_policy_recorded == 1u &&
           review->implementation_binding_manifest_bound == 1u &&
           review->source_digest_manifest_bound == 1u &&
           review->ci_promotion_evidence_bound == 1u &&
           review->dual_reviewer_required == 1u &&
           review->cryptography_reviewer_required == 1u &&
           review->security_reviewer_required == 1u &&
           review->code_owner_file_required == 1u &&
           review->reviewer_independence_required == 1u &&
           review->standards_traceability_required == 1u &&
           review->side_channel_reviewer_required == 1u &&
           review->reviewer_identities_recorded == 1u &&
           review->code_owner_file_recorded == 1u &&
           review->cryptography_review_recorded == 1u &&
           review->security_review_recorded == 1u &&
           review->standards_traceability_review_recorded == 1u &&
           review->side_channel_review_recorded == 1u &&
           review->source_digest_review_recorded == 1u &&
           review->blocking_findings_closed == 1u &&
           review->approval_receipt_recorded == 1u &&
           review->operation_execution_allowed == 1u &&
           review->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_code_owner_review_report(
    const latticra_q_seal_ml_kem_code_owner_review_t *review,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (review == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM CODE OWNER REVIEW\n"
        "review_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "review_scope=%s\n"
        "review_state=%s\n"
        "code_owner_review_evidence_present=%u\n"
        "ssdf_review_practice_bound=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "clean_room_review_policy_recorded=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "source_digest_manifest_required=%u\n"
        "source_digest_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "dual_reviewer_required=%u\n"
        "cryptography_reviewer_required=%u\n"
        "security_reviewer_required=%u\n"
        "code_owner_file_required=%u\n"
        "reviewer_independence_required=%u\n"
        "standards_traceability_required=%u\n"
        "side_channel_reviewer_required=%u\n"
        "reviewer_identities_recorded=%u\n"
        "code_owner_file_recorded=%u\n"
        "cryptography_review_recorded=%u\n"
        "security_review_recorded=%u\n"
        "standards_traceability_review_recorded=%u\n"
        "side_channel_review_recorded=%u\n"
        "source_digest_review_recorded=%u\n"
        "blocking_findings_closed=%u\n"
        "approval_receipt_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_review_items_total=%u\n"
        "required_review_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        review->review_profile,
        review->formal_title,
        review->standards_basis,
        review->review_scope,
        review->review_state,
        review->code_owner_review_evidence_present,
        review->ssdf_review_practice_bound,
        review->fips_203_algorithm_bound,
        review->clean_room_review_policy_recorded,
        review->implementation_binding_manifest_bound,
        review->source_digest_manifest_required,
        review->source_digest_manifest_bound,
        review->ci_promotion_evidence_bound,
        review->dual_reviewer_required,
        review->cryptography_reviewer_required,
        review->security_reviewer_required,
        review->code_owner_file_required,
        review->reviewer_independence_required,
        review->standards_traceability_required,
        review->side_channel_reviewer_required,
        review->reviewer_identities_recorded,
        review->code_owner_file_recorded,
        review->cryptography_review_recorded,
        review->security_review_recorded,
        review->standards_traceability_review_recorded,
        review->side_channel_review_recorded,
        review->source_digest_review_recorded,
        review->blocking_findings_closed,
        review->approval_receipt_recorded,
        review->operation_execution_allowed,
        review->production_crypto_claim_allowed,
        review->fips_claim_allowed,
        review->runtime_authority_granted,
        review->required_review_items_total,
        review->required_review_items_satisfied,
        review->blocked_reason,
        latticra_q_seal_ml_kem_code_owner_review_error_label(review->error),
        review->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
