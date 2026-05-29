#ifndef LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_MATRIX_H
#define LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_MATRIX_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_fips_conformance_matrix_error_t;

typedef struct {
    char conformance_profile[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_LABEL_MAX];
    char conformance_scope[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_LABEL_MAX];
    char conformance_state[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_STATE_MAX];
    unsigned fips_conformance_matrix_present;
    unsigned fips_203_source_bound;
    unsigned fips_203_publication_date_recorded;
    unsigned parameter_sets_bound;
    unsigned ml_kem_512_bound;
    unsigned ml_kem_768_bound;
    unsigned ml_kem_1024_bound;
    unsigned algorithm_functions_bound;
    unsigned keygen_algorithm_bound;
    unsigned encaps_algorithm_bound;
    unsigned decaps_algorithm_bound;
    unsigned byte_encoding_requirements_bound;
    unsigned randomness_requirements_bound;
    unsigned hash_xof_boundary_bound;
    unsigned decapsulation_failure_semantics_bound;
    unsigned acvp_kat_consistency_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned implementation_binding_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned per_parameter_trace_recorded;
    unsigned keygen_step_trace_recorded;
    unsigned encaps_step_trace_recorded;
    unsigned decaps_step_trace_recorded;
    unsigned encoding_tests_recorded;
    unsigned failure_semantics_tests_recorded;
    unsigned primitive_mapping_reviewed;
    unsigned errata_review_recorded;
    unsigned implementation_trace_accepted;
    unsigned conformance_matrix_accepted;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_conformance_items_total;
    unsigned required_conformance_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_STATE_MAX];
    latticra_q_seal_ml_kem_fips_conformance_matrix_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_FIPS_CONFORMANCE_STATE_MAX];
} latticra_q_seal_ml_kem_fips_conformance_matrix_t;

const char *latticra_q_seal_ml_kem_fips_conformance_matrix_error_label(
    latticra_q_seal_ml_kem_fips_conformance_matrix_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(
    latticra_q_seal_ml_kem_fips_conformance_matrix_t *out);
int latticra_q_seal_ml_kem_fips_conformance_matrix_is_no_effect(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix);
int
latticra_q_seal_ml_kem_fips_conformance_matrix_allows_implementation_trace_acceptance(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_fips_conformance_matrix_report(
    const latticra_q_seal_ml_kem_fips_conformance_matrix_t *matrix,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
