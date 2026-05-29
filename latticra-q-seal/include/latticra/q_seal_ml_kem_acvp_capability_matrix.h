#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_capability_matrix_error_t;

typedef struct {
    char matrix_profile[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_LABEL_MAX];
    char matrix_scope[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_LABEL_MAX];
    char matrix_state[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_STATE_MAX];
    unsigned acvp_capability_matrix_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_json_bound;
    unsigned algorithm_ml_kem_recorded;
    unsigned revision_fips203_recorded;
    unsigned keygen_mode_required;
    unsigned encap_decap_mode_required;
    unsigned ml_kem_512_parameter_set_required;
    unsigned ml_kem_768_parameter_set_required;
    unsigned ml_kem_1024_parameter_set_required;
    unsigned keygen_aft_required;
    unsigned encap_decap_aft_required;
    unsigned decapsulation_val_required;
    unsigned encapsulation_function_required;
    unsigned decapsulation_function_required;
    unsigned encapsulation_key_check_required;
    unsigned decapsulation_key_check_required;
    unsigned response_schema_keygen_bound;
    unsigned response_schema_encap_decap_bound;
    unsigned capability_exchange_policy_recorded;
    unsigned prereq_sha_validation_policy_recorded;
    unsigned vector_source_intake_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned acvp_registration_json_reviewed;
    unsigned capability_matrix_reviewed;
    unsigned keygen_parameter_coverage_reviewed;
    unsigned encap_decap_parameter_coverage_reviewed;
    unsigned function_coverage_reviewed;
    unsigned response_schema_reviewed;
    unsigned fixture_row_generation_allowed;
    unsigned vector_json_loaded;
    unsigned response_json_generation_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_capability_items_total;
    unsigned required_capability_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_capability_matrix_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_CAPABILITY_MATRIX_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_capability_matrix_t;

const char *latticra_q_seal_ml_kem_acvp_capability_matrix_error_label(
    latticra_q_seal_ml_kem_acvp_capability_matrix_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(
    latticra_q_seal_ml_kem_acvp_capability_matrix_t *out);
int latticra_q_seal_ml_kem_acvp_capability_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix);
int latticra_q_seal_ml_kem_acvp_capability_matrix_allows_fixture_row_planning(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_capability_matrix_report(
    const latticra_q_seal_ml_kem_acvp_capability_matrix_t *matrix,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
