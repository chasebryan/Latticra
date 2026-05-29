#ifndef LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE_H
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_reviewer_identity_fixture_error_t;

typedef struct {
    char identity_profile[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_LABEL_MAX];
    char identity_scope[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_LABEL_MAX];
    char identity_state[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_STATE_MAX];
    unsigned reviewer_identity_fixture_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_review_practice_bound;
    unsigned clean_room_review_policy_recorded;
    unsigned code_owner_review_gate_bound;
    unsigned review_disposition_ledger_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned dual_reviewer_identity_required;
    unsigned cryptography_reviewer_identity_required;
    unsigned security_reviewer_identity_required;
    unsigned code_owner_identity_required;
    unsigned reviewer_independence_required;
    unsigned identity_schema_recorded;
    unsigned identity_import_template_recorded;
    unsigned pii_minimization_policy_recorded;
    unsigned reviewer_identities_imported;
    unsigned cryptography_reviewer_identity_recorded;
    unsigned security_reviewer_identity_recorded;
    unsigned code_owner_identity_recorded;
    unsigned independence_attestation_recorded;
    unsigned identity_import_reviewed;
    unsigned approval_authority_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_identity_items_total;
    unsigned required_identity_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_STATE_MAX];
    latticra_q_seal_ml_kem_reviewer_identity_fixture_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_STATE_MAX];
} latticra_q_seal_ml_kem_reviewer_identity_fixture_t;

const char *latticra_q_seal_ml_kem_reviewer_identity_fixture_error_label(
    latticra_q_seal_ml_kem_reviewer_identity_fixture_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(
    latticra_q_seal_ml_kem_reviewer_identity_fixture_t *out);
int latticra_q_seal_ml_kem_reviewer_identity_fixture_is_no_effect(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture);
int latticra_q_seal_ml_kem_reviewer_identity_fixture_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture);
latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_identity_fixture_report(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
