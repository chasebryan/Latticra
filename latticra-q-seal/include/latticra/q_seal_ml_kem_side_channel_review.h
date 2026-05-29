#ifndef LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_H
#define LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_side_channel_review_error_t;

typedef struct {
    char review_profile[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_LABEL_MAX];
    char module_security_source[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_LABEL_MAX];
    char review_scope[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_LABEL_MAX];
    char review_state[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_STATE_MAX];
    unsigned side_channel_review_present;
    unsigned fips_203_source_verified;
    unsigned fips_140_3_non_invasive_security_tracked;
    unsigned constant_time_review_bound;
    unsigned secret_state_contract_bound;
    unsigned power_analysis_review_required;
    unsigned timing_leakage_review_required;
    unsigned cache_access_review_required;
    unsigned leakage_model_recorded;
    unsigned power_analysis_test_recorded;
    unsigned timing_measurement_recorded;
    unsigned cache_access_analysis_recorded;
    unsigned fault_injection_review_recorded;
    unsigned microarchitectural_leakage_review_recorded;
    unsigned masked_or_hardened_design_recorded;
    unsigned compiler_artifact_review_recorded;
    unsigned test_platform_matrix_recorded;
    unsigned negative_leakage_test_recorded;
    unsigned reviewer_signoff_recorded;
    unsigned implementation_binding_recorded;
    unsigned side_channel_tests_executed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_review_items_total;
    unsigned required_review_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_STATE_MAX];
    latticra_q_seal_ml_kem_side_channel_review_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_STATE_MAX];
} latticra_q_seal_ml_kem_side_channel_review_t;

const char *latticra_q_seal_ml_kem_side_channel_review_error_label(
    latticra_q_seal_ml_kem_side_channel_review_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_side_channel_review_prepare(
    latticra_q_seal_ml_kem_side_channel_review_t *out);
int latticra_q_seal_ml_kem_side_channel_review_is_policy_only(
    const latticra_q_seal_ml_kem_side_channel_review_t *review);
int latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_side_channel_review_t *review);
latticra_q_seal_status_t latticra_q_seal_ml_kem_side_channel_review_report(
    const latticra_q_seal_ml_kem_side_channel_review_t *review,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
