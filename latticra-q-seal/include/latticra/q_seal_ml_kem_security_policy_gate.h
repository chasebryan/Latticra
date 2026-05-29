#ifndef LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE_H
#define LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_security_policy_gate_error_t;

typedef struct {
    char security_policy_profile[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_LABEL_MAX];
    char security_policy_scope[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_LABEL_MAX];
    char security_policy_state[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_STATE_MAX];
    unsigned security_policy_gate_present;
    unsigned fips_140_3_module_security_bound;
    unsigned sp800_140b_rev1_security_policy_bound;
    unsigned cmvp_program_bound;
    unsigned fips_203_algorithm_bound;
    unsigned module_boundary_gate_bound;
    unsigned validation_claim_gate_bound;
    unsigned acvp_verdict_receipt_gate_bound;
    unsigned source_digest_verification_bound;
    unsigned code_owner_review_bound;
    unsigned review_disposition_ledger_bound;
    unsigned reviewer_role_mapping_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned security_policy_template_recorded;
    unsigned non_proprietary_policy_required;
    unsigned module_identification_section_required;
    unsigned cryptographic_module_specification_section_required;
    unsigned approved_algorithms_section_required;
    unsigned roles_services_authentication_section_required;
    unsigned software_firmware_security_section_required;
    unsigned operational_environment_section_required;
    unsigned self_tests_section_required;
    unsigned entropy_boundary_section_required;
    unsigned life_cycle_assurance_section_required;
    unsigned mitigation_other_attacks_section_required;
    unsigned acronyms_references_section_required;
    unsigned no_implicit_fips_claim_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned security_policy_evidence_recorded;
    unsigned security_policy_document_digest_recorded;
    unsigned module_name_version_recorded;
    unsigned security_level_table_recorded;
    unsigned approved_security_functions_table_recorded;
    unsigned services_roles_table_recorded;
    unsigned self_test_table_recorded;
    unsigned entropy_source_statement_recorded;
    unsigned operational_environment_recorded;
    unsigned guidance_statement_recorded;
    unsigned reviewer_disposition_recorded;
    unsigned security_policy_gate_accepted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned operation_execution_allowed;
    unsigned runtime_authority_granted;
    unsigned required_security_policy_items_total;
    unsigned required_security_policy_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_STATE_MAX];
    latticra_q_seal_ml_kem_security_policy_gate_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_STATE_MAX];
} latticra_q_seal_ml_kem_security_policy_gate_t;

const char *latticra_q_seal_ml_kem_security_policy_gate_error_label(
    latticra_q_seal_ml_kem_security_policy_gate_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_security_policy_gate_prepare(
    latticra_q_seal_ml_kem_security_policy_gate_t *out);
int latticra_q_seal_ml_kem_security_policy_gate_is_no_effect(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate);
int latticra_q_seal_ml_kem_security_policy_gate_allows_policy_acceptance(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate);
latticra_q_seal_status_t latticra_q_seal_ml_kem_security_policy_gate_report(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
