#ifndef LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_H
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_LABEL_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_implementation_frame_error_t;

typedef struct {
    char implementation_profile[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_LABEL_MAX];
    char implementation_state[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_STATE_MAX];
    unsigned implementation_frame_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned parameter_sets_recorded;
    unsigned module_plan_recorded;
    unsigned planned_module_count;
    unsigned polynomial_arithmetic_planned;
    unsigned ntt_planned;
    unsigned sampling_planned;
    unsigned compression_planned;
    unsigned encoding_planned;
    unsigned hash_xof_planned;
    unsigned keygen_planned;
    unsigned encaps_planned;
    unsigned decaps_planned;
    unsigned implementation_code_present;
    unsigned polynomial_arithmetic_implemented;
    unsigned ntt_implemented;
    unsigned sampling_implemented;
    unsigned compression_implemented;
    unsigned encoding_implemented;
    unsigned hash_xof_implemented;
    unsigned keygen_implemented;
    unsigned encaps_implemented;
    unsigned decaps_implemented;
    unsigned constant_time_design_required;
    unsigned constant_time_design_recorded;
    unsigned secret_branch_review_required;
    unsigned secret_branch_review_recorded;
    unsigned secret_memory_review_required;
    unsigned secret_memory_review_recorded;
    unsigned zeroization_design_required;
    unsigned zeroization_design_recorded;
    unsigned randomness_design_required;
    unsigned randomness_design_recorded;
    unsigned serialization_canonicality_required;
    unsigned serialization_canonicality_recorded;
    unsigned malformed_input_policy_required;
    unsigned malformed_input_policy_recorded;
    unsigned test_vector_binding_required;
    unsigned test_vector_binding_recorded;
    unsigned formal_review_required;
    unsigned formal_review_recorded;
    unsigned operations_enabled;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_design_items_total;
    unsigned required_design_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_STATE_MAX];
    latticra_q_seal_ml_kem_implementation_frame_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_STATE_MAX];
} latticra_q_seal_ml_kem_implementation_frame_t;

const char *latticra_q_seal_ml_kem_implementation_frame_error_label(
    latticra_q_seal_ml_kem_implementation_frame_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_frame_prepare(
    latticra_q_seal_ml_kem_implementation_frame_t *out);
int latticra_q_seal_ml_kem_implementation_frame_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame);
int latticra_q_seal_ml_kem_implementation_frame_allows_implementation(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame);
latticra_q_seal_status_t latticra_q_seal_ml_kem_implementation_frame_report(
    const latticra_q_seal_ml_kem_implementation_frame_t *frame,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
