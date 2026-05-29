#ifndef LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_H
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_vector_fixture_lock_error_t;

typedef struct {
    char lock_profile[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_LABEL_MAX];
    char fixture_scope[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_LABEL_MAX];
    char fixture_state[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_STATE_MAX];
    unsigned vector_fixture_lock_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_schema_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_intake_bound;
    unsigned kat_manifest_bound;
    unsigned negative_test_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned digest_algorithm_sha256_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned offline_only_fixture_recorded;
    unsigned fixture_manifest_schema_recorded;
    unsigned fixture_hash_manifest_required;
    unsigned ml_kem_512_fixture_required;
    unsigned ml_kem_768_fixture_required;
    unsigned ml_kem_1024_fixture_required;
    unsigned keygen_fixture_family_required;
    unsigned encaps_fixture_family_required;
    unsigned decaps_fixture_family_required;
    unsigned malformed_fixture_family_required;
    unsigned implicit_rejection_fixture_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned fixture_source_digest_recorded;
    unsigned fixture_license_review_recorded;
    unsigned fixture_storage_path_recorded;
    unsigned fixture_schema_crosscheck_recorded;
    unsigned fixture_parameter_coverage_recorded;
    unsigned fixture_negative_case_coverage_recorded;
    unsigned fixture_import_reviewed;
    unsigned fixture_bundle_loaded;
    unsigned vector_execution_allowed;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_fixture_lock_items_total;
    unsigned required_fixture_lock_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_STATE_MAX];
    latticra_q_seal_ml_kem_vector_fixture_lock_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_LOCK_STATE_MAX];
} latticra_q_seal_ml_kem_vector_fixture_lock_t;

const char *latticra_q_seal_ml_kem_vector_fixture_lock_error_label(
    latticra_q_seal_ml_kem_vector_fixture_lock_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_lock_prepare(
    latticra_q_seal_ml_kem_vector_fixture_lock_t *out);
int latticra_q_seal_ml_kem_vector_fixture_lock_is_no_effect(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock);
int latticra_q_seal_ml_kem_vector_fixture_lock_allows_vector_execution(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_lock_report(
    const latticra_q_seal_ml_kem_vector_fixture_lock_t *lock,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
