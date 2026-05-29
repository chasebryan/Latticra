#ifndef LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_H
#define LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_api_misuse_resistance_error_t;

typedef struct {
    char resistance_profile[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX];
    char module_security_source[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX];
    char secure_development_source[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX];
    char resistance_scope[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_LABEL_MAX];
    char resistance_state[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_STATE_MAX];
    unsigned api_misuse_resistance_present;
    unsigned fips_203_source_verified;
    unsigned fips_140_3_interface_security_tracked;
    unsigned nist_ssdf_source_tracked;
    unsigned implementation_frame_bound;
    unsigned memory_safety_evidence_bound;
    unsigned negative_test_evidence_bound;
    unsigned explicit_algorithm_identifier_required;
    unsigned parameter_set_validation_required;
    unsigned buffer_length_preflight_required;
    unsigned typed_key_material_required;
    unsigned no_implicit_rng_required;
    unsigned error_taxonomy_recorded;
    unsigned api_state_machine_recorded;
    unsigned misuse_case_matrix_recorded;
    unsigned wrong_parameter_set_tests_recorded;
    unsigned null_and_overlap_tests_recorded;
    unsigned deterministic_test_mode_guard_recorded;
    unsigned secret_output_lifetime_policy_recorded;
    unsigned language_binding_policy_recorded;
    unsigned documentation_examples_review_recorded;
    unsigned implementation_binding_recorded;
    unsigned api_misuse_tests_executed;
    unsigned public_api_execution_allowed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_api_misuse_items_total;
    unsigned required_api_misuse_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_STATE_MAX];
    latticra_q_seal_ml_kem_api_misuse_resistance_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_STATE_MAX];
} latticra_q_seal_ml_kem_api_misuse_resistance_t;

const char *latticra_q_seal_ml_kem_api_misuse_resistance_error_label(
    latticra_q_seal_ml_kem_api_misuse_resistance_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_api_misuse_resistance_prepare(
    latticra_q_seal_ml_kem_api_misuse_resistance_t *out);
int latticra_q_seal_ml_kem_api_misuse_resistance_is_policy_only(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance);
int latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance);
latticra_q_seal_status_t latticra_q_seal_ml_kem_api_misuse_resistance_report(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
