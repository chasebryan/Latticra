#include "latticra/q_seal_ml_kem_review_disposition_ledger.h"

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
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger) {
    unsigned satisfied = 0u;

    satisfied += one_if(ledger->review_disposition_ledger_present);
    satisfied += one_if(ledger->fips_203_algorithm_bound);
    satisfied += one_if(ledger->ssdf_review_practice_bound);
    satisfied += one_if(ledger->clean_room_review_policy_recorded);
    satisfied += one_if(ledger->code_owner_review_gate_bound);
    satisfied += one_if(ledger->source_digest_receipt_bound);
    satisfied += one_if(ledger->implementation_binding_manifest_bound);
    satisfied += one_if(ledger->ci_promotion_evidence_bound);
    satisfied += one_if(ledger->dual_reviewer_disposition_required);
    satisfied += one_if(ledger->cryptography_disposition_required);
    satisfied += one_if(ledger->security_disposition_required);
    satisfied += one_if(ledger->standards_traceability_disposition_required);
    satisfied += one_if(ledger->side_channel_disposition_required);
    satisfied += one_if(ledger->source_digest_disposition_required);
    satisfied += one_if(ledger->finding_severity_taxonomy_recorded);
    satisfied += one_if(ledger->rejection_disposition_policy_recorded);
    satisfied += one_if(ledger->approval_receipt_required);
    satisfied += one_if(ledger->reviewer_identity_disposition_recorded);
    satisfied += one_if(ledger->code_owner_disposition_recorded);
    satisfied += one_if(ledger->cryptography_disposition_recorded);
    satisfied += one_if(ledger->security_disposition_recorded);
    satisfied += one_if(ledger->standards_traceability_disposition_recorded);
    satisfied += one_if(ledger->side_channel_disposition_recorded);
    satisfied += one_if(ledger->source_digest_disposition_recorded);
    satisfied += one_if(ledger->blocking_findings_closed);
    satisfied += one_if(ledger->approval_receipt_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_review_disposition_ledger_error_label(
    latticra_q_seal_ml_kem_review_disposition_ledger_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_review_disposition_ledger_prepare(
    latticra_q_seal_ml_kem_review_disposition_ledger_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->disposition_profile,
        sizeof(out->disposition_profile),
        "latticra-q-seal-ml-kem-review-disposition-ledger/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Review Disposition Ledger");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->disposition_scope,
        sizeof(out->disposition_scope),
        "ML-KEM-review-finding-disposition-before-promotion");
    copy_literal(
        out->disposition_state,
        sizeof(out->disposition_state),
        "review-disposition-fixture-blocked");

    out->review_disposition_ledger_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_review_practice_bound = 1u;
    out->clean_room_review_policy_recorded = 1u;
    out->code_owner_review_gate_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->dual_reviewer_disposition_required = 1u;
    out->cryptography_disposition_required = 1u;
    out->security_disposition_required = 1u;
    out->standards_traceability_disposition_required = 1u;
    out->side_channel_disposition_required = 1u;
    out->source_digest_disposition_required = 1u;
    out->finding_severity_taxonomy_recorded = 1u;
    out->rejection_disposition_policy_recorded = 1u;
    out->approval_receipt_required = 1u;
    out->reviewer_identity_disposition_recorded = 0u;
    out->code_owner_disposition_recorded = 0u;
    out->cryptography_disposition_recorded = 0u;
    out->security_disposition_recorded = 0u;
    out->standards_traceability_disposition_recorded = 0u;
    out->side_channel_disposition_recorded = 0u;
    out->source_digest_disposition_recorded = 0u;
    out->blocking_findings_closed = 0u;
    out->approval_receipt_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_disposition_items_total = 26u;
    out->required_disposition_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "reviewer-identity-code-owner-crypto-security-standards-side-channel-digest-and-approval-dispositions-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-review-disposition-ledger-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_review_disposition_ledger_is_no_effect(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger) {
    if (ledger == NULL) {
        return 0;
    }

    return ledger->review_disposition_ledger_present == 1u &&
           ledger->operation_execution_allowed == 0u &&
           ledger->production_crypto_claim_allowed == 0u &&
           ledger->fips_claim_allowed == 0u &&
           ledger->runtime_authority_granted == 0u &&
           ledger->error == LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_BLOCKED;
}

int latticra_q_seal_ml_kem_review_disposition_ledger_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger) {
    if (ledger == NULL) {
        return 0;
    }

    return ledger->review_disposition_ledger_present == 1u &&
           ledger->fips_203_algorithm_bound == 1u &&
           ledger->ssdf_review_practice_bound == 1u &&
           ledger->clean_room_review_policy_recorded == 1u &&
           ledger->code_owner_review_gate_bound == 1u &&
           ledger->source_digest_receipt_bound == 1u &&
           ledger->implementation_binding_manifest_bound == 1u &&
           ledger->ci_promotion_evidence_bound == 1u &&
           ledger->dual_reviewer_disposition_required == 1u &&
           ledger->cryptography_disposition_required == 1u &&
           ledger->security_disposition_required == 1u &&
           ledger->standards_traceability_disposition_required == 1u &&
           ledger->side_channel_disposition_required == 1u &&
           ledger->source_digest_disposition_required == 1u &&
           ledger->finding_severity_taxonomy_recorded == 1u &&
           ledger->rejection_disposition_policy_recorded == 1u &&
           ledger->approval_receipt_required == 1u &&
           ledger->reviewer_identity_disposition_recorded == 1u &&
           ledger->code_owner_disposition_recorded == 1u &&
           ledger->cryptography_disposition_recorded == 1u &&
           ledger->security_disposition_recorded == 1u &&
           ledger->standards_traceability_disposition_recorded == 1u &&
           ledger->side_channel_disposition_recorded == 1u &&
           ledger->source_digest_disposition_recorded == 1u &&
           ledger->blocking_findings_closed == 1u &&
           ledger->approval_receipt_recorded == 1u &&
           ledger->operation_execution_allowed == 1u &&
           ledger->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_review_disposition_ledger_report(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (ledger == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM REVIEW DISPOSITION LEDGER\n"
        "disposition_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "disposition_scope=%s\n"
        "disposition_state=%s\n"
        "review_disposition_ledger_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_review_practice_bound=%u\n"
        "clean_room_review_policy_recorded=%u\n"
        "code_owner_review_gate_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "dual_reviewer_disposition_required=%u\n"
        "cryptography_disposition_required=%u\n"
        "security_disposition_required=%u\n"
        "standards_traceability_disposition_required=%u\n"
        "side_channel_disposition_required=%u\n"
        "source_digest_disposition_required=%u\n"
        "finding_severity_taxonomy_recorded=%u\n"
        "rejection_disposition_policy_recorded=%u\n"
        "approval_receipt_required=%u\n"
        "reviewer_identity_disposition_recorded=%u\n"
        "code_owner_disposition_recorded=%u\n"
        "cryptography_disposition_recorded=%u\n"
        "security_disposition_recorded=%u\n"
        "standards_traceability_disposition_recorded=%u\n"
        "side_channel_disposition_recorded=%u\n"
        "source_digest_disposition_recorded=%u\n"
        "blocking_findings_closed=%u\n"
        "approval_receipt_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_disposition_items_total=%u\n"
        "required_disposition_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        ledger->disposition_profile,
        ledger->formal_title,
        ledger->standards_basis,
        ledger->disposition_scope,
        ledger->disposition_state,
        ledger->review_disposition_ledger_present,
        ledger->fips_203_algorithm_bound,
        ledger->ssdf_review_practice_bound,
        ledger->clean_room_review_policy_recorded,
        ledger->code_owner_review_gate_bound,
        ledger->source_digest_receipt_bound,
        ledger->implementation_binding_manifest_bound,
        ledger->ci_promotion_evidence_bound,
        ledger->dual_reviewer_disposition_required,
        ledger->cryptography_disposition_required,
        ledger->security_disposition_required,
        ledger->standards_traceability_disposition_required,
        ledger->side_channel_disposition_required,
        ledger->source_digest_disposition_required,
        ledger->finding_severity_taxonomy_recorded,
        ledger->rejection_disposition_policy_recorded,
        ledger->approval_receipt_required,
        ledger->reviewer_identity_disposition_recorded,
        ledger->code_owner_disposition_recorded,
        ledger->cryptography_disposition_recorded,
        ledger->security_disposition_recorded,
        ledger->standards_traceability_disposition_recorded,
        ledger->side_channel_disposition_recorded,
        ledger->source_digest_disposition_recorded,
        ledger->blocking_findings_closed,
        ledger->approval_receipt_recorded,
        ledger->operation_execution_allowed,
        ledger->production_crypto_claim_allowed,
        ledger->fips_claim_allowed,
        ledger->runtime_authority_granted,
        ledger->required_disposition_items_total,
        ledger->required_disposition_items_satisfied,
        ledger->blocked_reason,
        latticra_q_seal_ml_kem_review_disposition_ledger_error_label(ledger->error),
        ledger->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
