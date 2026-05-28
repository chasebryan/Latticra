#ifndef LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER_H
#define LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_review_disposition_ledger_error_t;

typedef struct {
    char disposition_profile[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LABEL_MAX];
    char disposition_scope[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LABEL_MAX];
    char disposition_state[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_STATE_MAX];
    unsigned review_disposition_ledger_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_review_practice_bound;
    unsigned clean_room_review_policy_recorded;
    unsigned code_owner_review_gate_bound;
    unsigned source_digest_receipt_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned dual_reviewer_disposition_required;
    unsigned cryptography_disposition_required;
    unsigned security_disposition_required;
    unsigned standards_traceability_disposition_required;
    unsigned side_channel_disposition_required;
    unsigned source_digest_disposition_required;
    unsigned finding_severity_taxonomy_recorded;
    unsigned rejection_disposition_policy_recorded;
    unsigned approval_receipt_required;
    unsigned reviewer_identity_disposition_recorded;
    unsigned code_owner_disposition_recorded;
    unsigned cryptography_disposition_recorded;
    unsigned security_disposition_recorded;
    unsigned standards_traceability_disposition_recorded;
    unsigned side_channel_disposition_recorded;
    unsigned source_digest_disposition_recorded;
    unsigned blocking_findings_closed;
    unsigned approval_receipt_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_disposition_items_total;
    unsigned required_disposition_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_STATE_MAX];
    latticra_q_seal_ml_kem_review_disposition_ledger_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_STATE_MAX];
} latticra_q_seal_ml_kem_review_disposition_ledger_t;

const char *latticra_q_seal_ml_kem_review_disposition_ledger_error_label(
    latticra_q_seal_ml_kem_review_disposition_ledger_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_review_disposition_ledger_prepare(
    latticra_q_seal_ml_kem_review_disposition_ledger_t *out);
int latticra_q_seal_ml_kem_review_disposition_ledger_is_no_effect(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger);
int latticra_q_seal_ml_kem_review_disposition_ledger_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger);
latticra_q_seal_status_t latticra_q_seal_ml_kem_review_disposition_ledger_report(
    const latticra_q_seal_ml_kem_review_disposition_ledger_t *ledger,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
