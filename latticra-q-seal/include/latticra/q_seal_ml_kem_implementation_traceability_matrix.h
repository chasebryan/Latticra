#ifndef LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX_H
#define LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_TRACEABILITY_MATRIX_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_MATRIX_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_implementation_traceability_matrix_error_t;

typedef struct {
    char traceability_profile[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_LABEL_MAX];
    char traceability_scope[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_LABEL_MAX];
    char traceability_state[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_STATE_MAX];
    unsigned implementation_traceability_matrix_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned planned_source_units_count;
    unsigned planned_test_units_count;
    unsigned planned_source_unit_matrix_recorded;
    unsigned polynomial_arithmetic_unit_bound;
    unsigned ntt_unit_bound;
    unsigned sampling_unit_bound;
    unsigned compression_unit_bound;
    unsigned encoding_unit_bound;
    unsigned hash_xof_unit_bound;
    unsigned keygen_unit_bound;
    unsigned encaps_unit_bound;
    unsigned decaps_unit_bound;
    unsigned fips_203_section_mapping_recorded;
    unsigned sp800_227_usage_mapping_recorded;
    unsigned kat_vector_family_mapping_recorded;
    unsigned acvp_test_type_mapping_recorded;
    unsigned clean_room_review_path_recorded;
    unsigned no_external_code_dependency_recorded;
    unsigned constant_time_review_mapping_recorded;
    unsigned memory_safety_mapping_recorded;
    unsigned zeroization_mapping_recorded;
    unsigned randomness_mapping_recorded;
    unsigned negative_test_mapping_recorded;
    unsigned source_digest_mapping_recorded;
    unsigned code_owner_mapping_recorded;
    unsigned review_disposition_mapping_recorded;
    unsigned implementation_trace_accepted;
    unsigned implementation_file_digest_manifest_recorded;
    unsigned implementation_code_present;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_traceability_items_total;
    unsigned required_traceability_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_STATE_MAX];
    latticra_q_seal_ml_kem_implementation_traceability_matrix_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_TRACEABILITY_STATE_MAX];
} latticra_q_seal_ml_kem_implementation_traceability_matrix_t;

const char *latticra_q_seal_ml_kem_implementation_traceability_matrix_error_label(
    latticra_q_seal_ml_kem_implementation_traceability_matrix_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(
    latticra_q_seal_ml_kem_implementation_traceability_matrix_t *out);
int latticra_q_seal_ml_kem_implementation_traceability_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix);
int latticra_q_seal_ml_kem_implementation_traceability_matrix_allows_trace_acceptance(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_traceability_matrix_report(
    const latticra_q_seal_ml_kem_implementation_traceability_matrix_t *matrix,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
