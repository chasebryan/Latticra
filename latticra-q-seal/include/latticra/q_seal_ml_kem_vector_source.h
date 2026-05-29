#ifndef LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_H
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_vector_source_error_t;

typedef struct {
    char source_profile[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX];
    char acvp_document[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX];
    char approved_source_authority[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX];
    char digest_algorithm[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_LABEL_MAX];
    char source_state[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_STATE_MAX];
    unsigned vector_source_intake_present;
    unsigned fips_203_source_verified;
    unsigned acvp_documentation_tracked;
    unsigned approved_source_authority_recorded;
    unsigned source_freshness_policy_recorded;
    unsigned digest_algorithm_recorded;
    unsigned bundle_source_url_recorded;
    unsigned bundle_digest_recorded;
    unsigned bundle_size_recorded;
    unsigned bundle_license_review_recorded;
    unsigned bundle_hash_verified;
    unsigned bundle_schema_crosscheck_recorded;
    unsigned errata_review_binding_recorded;
    unsigned offline_storage_path_recorded;
    unsigned bundle_import_review_recorded;
    unsigned bundle_fetch_performed;
    unsigned bundle_imported;
    unsigned network_fetch_enabled;
    unsigned vector_processing_allowed;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_source_items_total;
    unsigned required_source_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_STATE_MAX];
    latticra_q_seal_ml_kem_vector_source_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE_STATE_MAX];
} latticra_q_seal_ml_kem_vector_source_t;

const char *latticra_q_seal_ml_kem_vector_source_error_label(
    latticra_q_seal_ml_kem_vector_source_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_source_prepare(
    latticra_q_seal_ml_kem_vector_source_t *out);
int latticra_q_seal_ml_kem_vector_source_is_no_fetch(
    const latticra_q_seal_ml_kem_vector_source_t *source);
int latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(
    const latticra_q_seal_ml_kem_vector_source_t *source);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_source_report(
    const latticra_q_seal_ml_kem_vector_source_t *source,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
