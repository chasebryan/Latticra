#ifndef LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_source_layout_gate_error_t;

typedef struct {
    char layout_profile[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_LABEL_MAX];
    char layout_scope[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_LABEL_MAX];
    char layout_state[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_STATE_MAX];
    unsigned source_layout_gate_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned implementation_unit_roles_recorded;
    unsigned test_unit_roles_recorded;
    unsigned public_api_boundary_recorded;
    unsigned internal_primitive_boundary_recorded;
    unsigned secret_state_boundary_recorded;
    unsigned randomness_boundary_recorded;
    unsigned zeroization_boundary_recorded;
    unsigned constant_time_boundary_recorded;
    unsigned parameter_set_coverage_recorded;
    unsigned negative_test_lane_recorded;
    unsigned kat_acvp_lane_recorded;
    unsigned digest_manifest_lane_recorded;
    unsigned review_owner_lane_recorded;
    unsigned implementation_binding_manifest_bound;
    unsigned implementation_file_digest_plan_bound;
    unsigned clean_room_author_attestation_gate_bound;
    unsigned per_file_standards_trace_gate_bound;
    unsigned per_file_test_trace_gate_bound;
    unsigned implementation_traceability_matrix_bound;
    unsigned primitive_source_acceptance_gate_bound;
    unsigned source_digest_manifest_bound;
    unsigned source_digest_receipt_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned source_files_created;
    unsigned source_layout_rows_recorded;
    unsigned layout_digest_rows_recorded;
    unsigned layout_reviewed;
    unsigned layout_acceptance_approved;
    unsigned source_layout_accepted;
    unsigned operation_execution_allowed;
    unsigned shared_secret_emission_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_layout_items_total;
    unsigned required_layout_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_STATE_MAX];
    latticra_q_seal_ml_kem_source_layout_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_STATE_MAX];
} latticra_q_seal_ml_kem_source_layout_gate_t;

const char *latticra_q_seal_ml_kem_source_layout_gate_error_label(
    latticra_q_seal_ml_kem_source_layout_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_layout_gate_prepare(
    latticra_q_seal_ml_kem_source_layout_gate_t *out);
int latticra_q_seal_ml_kem_source_layout_gate_is_no_effect(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate);
int latticra_q_seal_ml_kem_source_layout_gate_allows_layout_acceptance(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_source_layout_gate_report(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
