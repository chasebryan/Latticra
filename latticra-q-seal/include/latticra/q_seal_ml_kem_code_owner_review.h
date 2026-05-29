#ifndef LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_H
#define LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_code_owner_review_error_t;

typedef struct {
    char review_profile[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_LABEL_MAX];
    char review_scope[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_LABEL_MAX];
    char review_state[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_STATE_MAX];
    unsigned code_owner_review_evidence_present;
    unsigned ssdf_review_practice_bound;
    unsigned fips_203_algorithm_bound;
    unsigned clean_room_review_policy_recorded;
    unsigned implementation_binding_manifest_bound;
    unsigned source_digest_manifest_required;
    unsigned source_digest_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned dual_reviewer_required;
    unsigned cryptography_reviewer_required;
    unsigned security_reviewer_required;
    unsigned code_owner_file_required;
    unsigned reviewer_independence_required;
    unsigned standards_traceability_required;
    unsigned side_channel_reviewer_required;
    unsigned reviewer_identities_recorded;
    unsigned code_owner_file_recorded;
    unsigned cryptography_review_recorded;
    unsigned security_review_recorded;
    unsigned standards_traceability_review_recorded;
    unsigned side_channel_review_recorded;
    unsigned source_digest_review_recorded;
    unsigned blocking_findings_closed;
    unsigned approval_receipt_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_review_items_total;
    unsigned required_review_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_STATE_MAX];
    latticra_q_seal_ml_kem_code_owner_review_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_STATE_MAX];
} latticra_q_seal_ml_kem_code_owner_review_t;

const char *latticra_q_seal_ml_kem_code_owner_review_error_label(
    latticra_q_seal_ml_kem_code_owner_review_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_code_owner_review_prepare(
    latticra_q_seal_ml_kem_code_owner_review_t *out);
int latticra_q_seal_ml_kem_code_owner_review_is_no_effect(
    const latticra_q_seal_ml_kem_code_owner_review_t *review);
int latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_code_owner_review_t *review);
latticra_q_seal_status_t latticra_q_seal_ml_kem_code_owner_review_report(
    const latticra_q_seal_ml_kem_code_owner_review_t *review,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
