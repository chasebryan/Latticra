#ifndef LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_H
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_LABEL_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_STATE_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_PROVIDER_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_provider_differential_error_t;

typedef struct {
    char differential_profile[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_LABEL_MAX];
    char candidate_provider[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_LABEL_MAX];
    char comparison_scope[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_LABEL_MAX];
    char differential_state[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_STATE_MAX];
    unsigned provider_differential_contract_present;
    unsigned provider_candidate_recorded;
    unsigned provider_comparison_only;
    unsigned provider_license_review_required;
    unsigned provider_license_review_recorded;
    unsigned provider_pinned_version_required;
    unsigned provider_pinned_version_recorded;
    unsigned provider_source_digest_required;
    unsigned provider_source_digest_recorded;
    unsigned provider_build_reproducibility_required;
    unsigned provider_build_reproducibility_recorded;
    unsigned provider_linking_enabled;
    unsigned provider_runtime_used;
    unsigned parameter_sets_recorded;
    unsigned ml_kem_512_comparison_required;
    unsigned ml_kem_768_comparison_required;
    unsigned ml_kem_1024_comparison_required;
    unsigned positive_vector_comparison_required;
    unsigned positive_vector_comparison_recorded;
    unsigned negative_vector_comparison_required;
    unsigned negative_vector_comparison_recorded;
    unsigned mismatch_triage_required;
    unsigned mismatch_triage_recorded;
    unsigned differential_keygen_enabled;
    unsigned differential_encap_decap_enabled;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_comparison_items_total;
    unsigned required_comparison_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_STATE_MAX];
    latticra_q_seal_ml_kem_provider_differential_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_STATE_MAX];
} latticra_q_seal_ml_kem_provider_differential_t;

const char *latticra_q_seal_ml_kem_provider_differential_error_label(
    latticra_q_seal_ml_kem_provider_differential_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_differential_prepare(
    latticra_q_seal_ml_kem_provider_differential_t *out);
int latticra_q_seal_ml_kem_provider_differential_is_comparison_only(
    const latticra_q_seal_ml_kem_provider_differential_t *differential);
int latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(
    const latticra_q_seal_ml_kem_provider_differential_t *differential);
latticra_q_seal_status_t latticra_q_seal_ml_kem_provider_differential_report(
    const latticra_q_seal_ml_kem_provider_differential_t *differential,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
