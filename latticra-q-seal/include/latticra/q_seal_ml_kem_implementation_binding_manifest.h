#ifndef LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST_H
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_BINDING_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_BINDING_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_BINDING_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_BINDING_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_BINDING_MANIFEST_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_implementation_binding_manifest_error_t;

typedef struct {
    char binding_profile[LATTICRA_Q_SEAL_ML_KEM_BINDING_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_BINDING_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_BINDING_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_BINDING_LABEL_MAX];
    char manifest_scope[LATTICRA_Q_SEAL_ML_KEM_BINDING_LABEL_MAX];
    char binding_state[LATTICRA_Q_SEAL_ML_KEM_BINDING_STATE_MAX];
    unsigned implementation_binding_manifest_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned fips_203_algorithm_bound;
    unsigned sp_800_227_kem_usage_bound;
    unsigned kat_manifest_bound;
    unsigned acvp_intake_bound;
    unsigned acvp_capability_matrix_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned acvp_response_fixture_bound;
    unsigned acvp_submission_package_contract_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_bound;
    unsigned vector_fixture_lock_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned memory_safety_evidence_bound;
    unsigned api_misuse_resistance_bound;
    unsigned constant_time_review_bound;
    unsigned randomness_source_bound;
    unsigned zeroization_evidence_bound;
    unsigned side_channel_review_bound;
    unsigned provider_differential_bound;
    unsigned secret_state_contract_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned module_to_gate_matrix_recorded;
    unsigned implementation_files_created;
    unsigned implementation_code_present;
    unsigned primitive_operations_bound;
    unsigned keygen_binding_approved;
    unsigned encaps_binding_approved;
    unsigned decaps_binding_approved;
    unsigned implementation_file_digest_manifest_recorded;
    unsigned code_owner_review_recorded;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_binding_items_total;
    unsigned required_binding_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_BINDING_STATE_MAX];
    latticra_q_seal_ml_kem_implementation_binding_manifest_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_BINDING_STATE_MAX];
} latticra_q_seal_ml_kem_implementation_binding_manifest_t;

const char *latticra_q_seal_ml_kem_implementation_binding_manifest_error_label(
    latticra_q_seal_ml_kem_implementation_binding_manifest_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(
    latticra_q_seal_ml_kem_implementation_binding_manifest_t *out);
int latticra_q_seal_ml_kem_implementation_binding_manifest_is_clean_room_no_effect(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest);
int latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest);
latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_binding_manifest_report(
    const latticra_q_seal_ml_kem_implementation_binding_manifest_t *manifest,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
