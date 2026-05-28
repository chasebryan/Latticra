#ifndef LATTICRA_Q_SEAL_ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_clean_room_author_attestation_gate_error_t;

typedef struct {
    char attestation_profile[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_LABEL_MAX];
    char attestation_scope[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_LABEL_MAX];
    char attestation_state[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_STATE_MAX];
    unsigned clean_room_author_attestation_gate_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned source_layout_bound;
    unsigned implementation_file_digest_plan_bound;
    unsigned implementation_traceability_matrix_bound;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned source_digest_verification_bound;
    unsigned receipt_replay_results_bound;
    unsigned fips_conformance_matrix_bound;
    unsigned sp800_227_usage_profile_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned ssdf_provenance_policy_bound;
    unsigned no_third_party_source_policy_recorded;
    unsigned author_attestation_schema_recorded;
    unsigned per_file_author_columns_recorded;
    unsigned review_independence_required;
    unsigned source_files_created;
    unsigned author_identity_imported;
    unsigned per_file_author_attestations_recorded;
    unsigned clean_room_attestation_reviewed;
    unsigned provenance_exception_reviewed;
    unsigned source_author_attestation_accepted;
    unsigned operation_execution_allowed;
    unsigned shared_secret_emission_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_attestation_items_total;
    unsigned required_attestation_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_STATE_MAX];
    latticra_q_seal_ml_kem_clean_room_author_attestation_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_AUTHOR_ATTESTATION_STATE_MAX];
} latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t;

const char *latticra_q_seal_ml_kem_clean_room_author_attestation_gate_error_label(
    latticra_q_seal_ml_kem_clean_room_author_attestation_gate_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_clean_room_author_attestation_gate_prepare(
    latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t *out);
int latticra_q_seal_ml_kem_clean_room_author_attestation_gate_is_no_effect(
    const latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t *gate);
int latticra_q_seal_ml_kem_clean_room_author_attestation_gate_allows_attestation_acceptance(
    const latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t *gate);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_clean_room_author_attestation_gate_report(
    const latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
