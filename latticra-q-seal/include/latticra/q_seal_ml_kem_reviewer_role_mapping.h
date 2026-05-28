#ifndef LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_H
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_reviewer_role_mapping_error_t;

typedef struct {
    char mapping_profile[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_LABEL_MAX];
    char mapping_scope[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_LABEL_MAX];
    char mapping_state[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_STATE_MAX];
    unsigned reviewer_role_mapping_present;
    unsigned fips_203_algorithm_bound;
    unsigned ssdf_review_practice_bound;
    unsigned clean_room_review_policy_recorded;
    unsigned code_owner_review_gate_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_identity_fixture_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned role_schema_recorded;
    unsigned cryptography_role_required;
    unsigned security_role_required;
    unsigned code_owner_role_required;
    unsigned standards_traceability_role_required;
    unsigned side_channel_role_required;
    unsigned source_digest_role_required;
    unsigned dual_reviewer_separation_required;
    unsigned conflict_of_interest_policy_recorded;
    unsigned pii_minimization_policy_bound;
    unsigned approval_authority_mapping_required;
    unsigned reviewer_identities_imported;
    unsigned role_mapping_records_imported;
    unsigned cryptography_role_mapped;
    unsigned security_role_mapped;
    unsigned code_owner_role_mapped;
    unsigned standards_traceability_role_mapped;
    unsigned side_channel_role_mapped;
    unsigned source_digest_role_mapped;
    unsigned separation_review_recorded;
    unsigned approval_authority_mapped;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_role_mapping_items_total;
    unsigned required_role_mapping_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_STATE_MAX];
    latticra_q_seal_ml_kem_reviewer_role_mapping_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_STATE_MAX];
} latticra_q_seal_ml_kem_reviewer_role_mapping_t;

const char *latticra_q_seal_ml_kem_reviewer_role_mapping_error_label(
    latticra_q_seal_ml_kem_reviewer_role_mapping_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(
    latticra_q_seal_ml_kem_reviewer_role_mapping_t *out);
int latticra_q_seal_ml_kem_reviewer_role_mapping_is_no_effect(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping);
int latticra_q_seal_ml_kem_reviewer_role_mapping_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping);
latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_role_mapping_report(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
