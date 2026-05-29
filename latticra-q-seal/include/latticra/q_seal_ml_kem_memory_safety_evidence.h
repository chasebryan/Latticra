#ifndef LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_H
#define LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_memory_safety_evidence_error_t;

typedef struct {
    char evidence_profile[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX];
    char module_security_source[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX];
    char secure_development_source[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX];
    char evidence_scope[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_LABEL_MAX];
    char evidence_state[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_STATE_MAX];
    unsigned memory_safety_evidence_present;
    unsigned fips_203_source_verified;
    unsigned fips_140_3_software_security_tracked;
    unsigned nist_ssdf_source_tracked;
    unsigned implementation_frame_bound;
    unsigned negative_test_evidence_bound;
    unsigned bounded_buffer_policy_required;
    unsigned fixed_capacity_api_policy_required;
    unsigned allocation_policy_required;
    unsigned size_overflow_checks_recorded;
    unsigned bounds_check_review_recorded;
    unsigned integer_overflow_review_recorded;
    unsigned sanitizer_asan_ubsan_recorded;
    unsigned static_analysis_recorded;
    unsigned fuzz_memory_safety_recorded;
    unsigned aliasing_lifetime_review_recorded;
    unsigned secret_buffer_isolation_recorded;
    unsigned constant_time_memory_copy_review_recorded;
    unsigned zeroization_memory_safety_bound;
    unsigned cross_platform_word_size_review_recorded;
    unsigned implementation_binding_recorded;
    unsigned memory_safety_tests_executed;
    unsigned implementation_promotion_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_memory_safety_items_total;
    unsigned required_memory_safety_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_STATE_MAX];
    latticra_q_seal_ml_kem_memory_safety_evidence_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_STATE_MAX];
} latticra_q_seal_ml_kem_memory_safety_evidence_t;

const char *latticra_q_seal_ml_kem_memory_safety_evidence_error_label(
    latticra_q_seal_ml_kem_memory_safety_evidence_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_memory_safety_evidence_prepare(
    latticra_q_seal_ml_kem_memory_safety_evidence_t *out);
int latticra_q_seal_ml_kem_memory_safety_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence);
int latticra_q_seal_ml_kem_memory_safety_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence);
latticra_q_seal_status_t latticra_q_seal_ml_kem_memory_safety_evidence_report(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
