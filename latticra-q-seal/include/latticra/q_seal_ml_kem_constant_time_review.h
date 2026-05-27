#ifndef LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_H
#define LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_constant_time_review_error_t;

typedef struct {
    char review_profile[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_LABEL_MAX];
    char review_scope[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_LABEL_MAX];
    char analysis_policy[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_LABEL_MAX];
    char review_state[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_STATE_MAX];
    unsigned constant_time_review_present;
    unsigned fips_203_source_verified;
    unsigned secret_dependent_branch_forbidden;
    unsigned secret_dependent_memory_index_forbidden;
    unsigned secret_dependent_loop_bound_forbidden;
    unsigned secret_dependent_early_return_forbidden;
    unsigned constant_time_compare_required;
    unsigned decapsulation_implicit_rejection_required;
    unsigned compiler_optimization_review_required;
    unsigned dudect_measurement_recorded;
    unsigned ctgrind_or_static_analysis_recorded;
    unsigned generated_assembly_review_recorded;
    unsigned optimizer_flag_review_recorded;
    unsigned secret_state_inventory_bound;
    unsigned negative_timing_test_recorded;
    unsigned cross_platform_timing_review_recorded;
    unsigned formal_reviewer_signoff_recorded;
    unsigned ci_constant_time_gate_recorded;
    unsigned implementation_binding_recorded;
    unsigned measurement_execution_allowed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_review_items_total;
    unsigned required_review_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_STATE_MAX];
    latticra_q_seal_ml_kem_constant_time_review_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_STATE_MAX];
} latticra_q_seal_ml_kem_constant_time_review_t;

const char *latticra_q_seal_ml_kem_constant_time_review_error_label(
    latticra_q_seal_ml_kem_constant_time_review_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_review_prepare(
    latticra_q_seal_ml_kem_constant_time_review_t *out);
int latticra_q_seal_ml_kem_constant_time_review_is_policy_only(
    const latticra_q_seal_ml_kem_constant_time_review_t *review);
int latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_constant_time_review_t *review);
latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_review_report(
    const latticra_q_seal_ml_kem_constant_time_review_t *review,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
