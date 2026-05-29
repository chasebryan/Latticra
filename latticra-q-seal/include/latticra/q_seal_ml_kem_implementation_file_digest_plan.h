#ifndef LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN_H
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FILE_DIGEST_PLAN_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_implementation_file_digest_plan_error_t;

typedef struct {
    char digest_plan_profile[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX];
    char digest_algorithm[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX];
    char digest_plan_scope[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_LABEL_MAX];
    char digest_plan_state[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_STATE_MAX];
    unsigned implementation_file_digest_plan_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned digest_algorithm_sha256_recorded;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned source_digest_verification_bound;
    unsigned receipt_replay_results_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned implementation_traceability_matrix_bound;
    unsigned primitive_source_acceptance_gate_bound;
    unsigned source_layout_gate_bound;
    unsigned fips_conformance_matrix_bound;
    unsigned sp800_227_usage_profile_bound;
    unsigned kat_manifest_bound;
    unsigned acvp_contracts_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned per_file_digest_row_schema_recorded;
    unsigned per_file_trace_columns_recorded;
    unsigned per_file_review_columns_recorded;
    unsigned source_files_created;
    unsigned implementation_file_digest_rows_recorded;
    unsigned test_file_digest_rows_recorded;
    unsigned build_script_digest_rows_recorded;
    unsigned digest_receipt_reviewed;
    unsigned digest_replay_verified;
    unsigned file_digest_plan_accepted;
    unsigned operation_execution_allowed;
    unsigned shared_secret_emission_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_digest_plan_items_total;
    unsigned required_digest_plan_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_STATE_MAX];
    latticra_q_seal_ml_kem_implementation_file_digest_plan_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_STATE_MAX];
} latticra_q_seal_ml_kem_implementation_file_digest_plan_t;

const char *latticra_q_seal_ml_kem_implementation_file_digest_plan_error_label(
    latticra_q_seal_ml_kem_implementation_file_digest_plan_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(
    latticra_q_seal_ml_kem_implementation_file_digest_plan_t *out);
int latticra_q_seal_ml_kem_implementation_file_digest_plan_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan);
int latticra_q_seal_ml_kem_implementation_file_digest_plan_allows_digest_row_acceptance(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
