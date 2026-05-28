#ifndef LATTICRA_Q_SEAL_ML_KEM_PER_FILE_TEST_TRACE_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_PER_FILE_TEST_TRACE_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_per_file_test_trace_gate_error_t;

typedef struct {
    char test_trace_profile[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_LABEL_MAX];
    char trace_scope[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_LABEL_MAX];
    char trace_state[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_STATE_MAX];
    unsigned per_file_test_trace_gate_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned primitive_source_acceptance_gate_bound;
    unsigned implementation_traceability_matrix_bound;
    unsigned implementation_file_digest_plan_bound;
    unsigned clean_room_author_attestation_gate_bound;
    unsigned per_file_standards_trace_gate_bound;
    unsigned kat_manifest_bound;
    unsigned kat_runner_contract_bound;
    unsigned kat_result_schema_bound;
    unsigned kat_result_row_fixture_bound;
    unsigned acvp_contracts_bound;
    unsigned vector_schema_bound;
    unsigned vector_fixture_lock_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned test_family_columns_recorded;
    unsigned parameter_set_columns_recorded;
    unsigned operation_family_columns_recorded;
    unsigned vector_reference_columns_recorded;
    unsigned expected_result_columns_recorded;
    unsigned review_disposition_columns_recorded;
    unsigned source_files_created;
    unsigned per_file_test_trace_rows_recorded;
    unsigned kat_trace_coverage_reviewed;
    unsigned acvp_trace_coverage_reviewed;
    unsigned negative_test_trace_reviewed;
    unsigned trace_review_approved;
    unsigned per_file_test_trace_accepted;
    unsigned operation_execution_allowed;
    unsigned shared_secret_emission_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_test_trace_items_total;
    unsigned required_test_trace_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_STATE_MAX];
    latticra_q_seal_ml_kem_per_file_test_trace_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_STATE_MAX];
} latticra_q_seal_ml_kem_per_file_test_trace_gate_t;

const char *latticra_q_seal_ml_kem_per_file_test_trace_gate_error_label(
    latticra_q_seal_ml_kem_per_file_test_trace_gate_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_per_file_test_trace_gate_prepare(
    latticra_q_seal_ml_kem_per_file_test_trace_gate_t *out);
int latticra_q_seal_ml_kem_per_file_test_trace_gate_is_no_effect(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate);
int latticra_q_seal_ml_kem_per_file_test_trace_gate_allows_trace_acceptance(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_per_file_test_trace_gate_report(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
