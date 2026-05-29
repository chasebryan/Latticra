#ifndef LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_H
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_vector_schema_error_t;

typedef struct {
    char schema_profile[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_LABEL_MAX];
    char acvp_document[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_LABEL_MAX];
    char schema_state[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_STATE_MAX];
    unsigned vector_schema_present;
    unsigned fips_203_source_verified;
    unsigned acvp_ml_kem_schema_tracked;
    unsigned algorithm_ml_kem_recorded;
    unsigned revision_fips203_recorded;
    unsigned keygen_mode_schema_recorded;
    unsigned encap_decap_mode_schema_recorded;
    unsigned parameter_sets_recorded;
    unsigned keygen_prompt_fields_recorded;
    unsigned keygen_response_fields_recorded;
    unsigned encap_decap_prompt_fields_recorded;
    unsigned encap_decap_response_fields_recorded;
    unsigned aft_test_type_recorded;
    unsigned val_test_type_recorded;
    unsigned key_check_functions_recorded;
    unsigned implicit_rejection_case_recorded;
    unsigned vector_source_url_recorded;
    unsigned vector_source_digest_recorded;
    unsigned vector_license_review_recorded;
    unsigned vector_bundle_loaded;
    unsigned vector_json_parser_implemented;
    unsigned response_generation_enabled;
    unsigned vector_execution_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_schema_items_total;
    unsigned required_schema_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_STATE_MAX];
    latticra_q_seal_ml_kem_vector_schema_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_STATE_MAX];
} latticra_q_seal_ml_kem_vector_schema_t;

const char *latticra_q_seal_ml_kem_vector_schema_error_label(
    latticra_q_seal_ml_kem_vector_schema_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_schema_prepare(
    latticra_q_seal_ml_kem_vector_schema_t *out);
int latticra_q_seal_ml_kem_vector_schema_is_schema_only(
    const latticra_q_seal_ml_kem_vector_schema_t *schema);
int latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(
    const latticra_q_seal_ml_kem_vector_schema_t *schema);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_schema_report(
    const latticra_q_seal_ml_kem_vector_schema_t *schema,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
