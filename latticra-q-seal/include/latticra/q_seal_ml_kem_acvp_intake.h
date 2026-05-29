#ifndef LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_H
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_ACVP_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_LABEL_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_STATE_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_ACVP_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_acvp_intake_error_t;

typedef struct {
    char intake_profile[LATTICRA_Q_SEAL_ML_KEM_ACVP_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_ACVP_LABEL_MAX];
    char acvp_document[LATTICRA_Q_SEAL_ML_KEM_ACVP_LABEL_MAX];
    char algorithm[LATTICRA_Q_SEAL_ML_KEM_ACVP_LABEL_MAX];
    char revision[LATTICRA_Q_SEAL_ML_KEM_ACVP_LABEL_MAX];
    char intake_state[LATTICRA_Q_SEAL_ML_KEM_ACVP_STATE_MAX];
    unsigned acvp_intake_present;
    unsigned acvp_document_tracked;
    unsigned acvp_ml_kem_schema_tracked;
    unsigned algorithm_ml_kem_required;
    unsigned revision_fips203_required;
    unsigned keygen_mode_required;
    unsigned encap_decap_mode_required;
    unsigned ml_kem_512_required;
    unsigned ml_kem_768_required;
    unsigned ml_kem_1024_required;
    unsigned vector_source_url_recorded;
    unsigned vector_bundle_digest_recorded;
    unsigned vector_license_review_recorded;
    unsigned vector_json_schema_reviewed;
    unsigned vector_json_loaded;
    unsigned response_json_generation_enabled;
    unsigned offline_fixture_only;
    unsigned network_session_enabled;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_intake_items_total;
    unsigned required_intake_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_ACVP_STATE_MAX];
    latticra_q_seal_ml_kem_acvp_intake_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_ACVP_STATE_MAX];
} latticra_q_seal_ml_kem_acvp_intake_t;

const char *latticra_q_seal_ml_kem_acvp_intake_error_label(
    latticra_q_seal_ml_kem_acvp_intake_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_intake_prepare(
    latticra_q_seal_ml_kem_acvp_intake_t *out);
int latticra_q_seal_ml_kem_acvp_intake_is_offline_only(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake);
int latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake);
latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_intake_report(
    const latticra_q_seal_ml_kem_acvp_intake_t *intake,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
