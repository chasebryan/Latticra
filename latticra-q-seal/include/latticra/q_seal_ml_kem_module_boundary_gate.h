#ifndef LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_module_boundary_gate_error_t;

typedef struct {
    char module_boundary_profile[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_LABEL_MAX];
    char module_boundary_scope[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_LABEL_MAX];
    char module_boundary_state[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_STATE_MAX];
    unsigned module_boundary_gate_present;
    unsigned fips_203_algorithm_bound;
    unsigned fips_140_3_module_security_bound;
    unsigned cmvp_program_bound;
    unsigned validation_claim_gate_bound;
    unsigned security_policy_gate_bound;
    unsigned acvp_verdict_receipt_gate_bound;
    unsigned ci_promotion_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned source_layout_gate_bound;
    unsigned implementation_file_digest_plan_bound;
    unsigned source_digest_verification_bound;
    unsigned zeroization_evidence_bound;
    unsigned randomness_source_bound;
    unsigned side_channel_review_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned module_boundary_schema_recorded;
    unsigned security_policy_template_recorded;
    unsigned services_roles_columns_recorded;
    unsigned operational_environment_columns_recorded;
    unsigned self_test_policy_columns_recorded;
    unsigned algorithm_certificate_columns_recorded;
    unsigned entropy_boundary_columns_recorded;
    unsigned zeroization_boundary_columns_recorded;
    unsigned source_digest_policy_bound;
    unsigned no_implicit_fips_claim_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned module_boundary_evidence_recorded;
    unsigned cryptographic_module_name_recorded;
    unsigned module_version_recorded;
    unsigned operational_environment_recorded;
    unsigned fips_140_3_security_policy_recorded;
    unsigned roles_services_authentication_recorded;
    unsigned self_test_policy_recorded;
    unsigned approved_algorithm_inventory_recorded;
    unsigned entropy_source_boundary_recorded;
    unsigned zeroization_boundary_review_recorded;
    unsigned acvp_algorithm_certificate_bound;
    unsigned cmvp_submission_identifier_recorded;
    unsigned module_boundary_review_recorded;
    unsigned reviewer_disposition_recorded;
    unsigned module_boundary_gate_accepted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned operation_execution_allowed;
    unsigned runtime_authority_granted;
    unsigned required_module_boundary_items_total;
    unsigned required_module_boundary_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_STATE_MAX];
    latticra_q_seal_ml_kem_module_boundary_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_STATE_MAX];
} latticra_q_seal_ml_kem_module_boundary_gate_t;

const char *latticra_q_seal_ml_kem_module_boundary_gate_error_label(
    latticra_q_seal_ml_kem_module_boundary_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_module_boundary_gate_prepare(
    latticra_q_seal_ml_kem_module_boundary_gate_t *out);
int latticra_q_seal_ml_kem_module_boundary_gate_is_no_effect(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate);
int latticra_q_seal_ml_kem_module_boundary_gate_allows_boundary_acceptance(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_module_boundary_gate_report(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
