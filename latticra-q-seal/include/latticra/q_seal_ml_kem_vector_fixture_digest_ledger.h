#ifndef LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_H
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_t;

typedef struct {
    char ledger_profile[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_LABEL_MAX];
    char ledger_scope[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_LABEL_MAX];
    char ledger_state[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_STATE_MAX];
    unsigned vector_fixture_digest_ledger_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_schema_bound;
    unsigned acvp_fixture_row_plan_bound;
    unsigned acvp_fixture_digest_row_template_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_intake_bound;
    unsigned vector_fixture_lock_bound;
    unsigned kat_manifest_bound;
    unsigned negative_test_evidence_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned digest_algorithm_sha256_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned offline_only_digest_recorded;
    unsigned manifest_row_schema_recorded;
    unsigned canonical_path_policy_recorded;
    unsigned bundle_size_policy_recorded;
    unsigned parameter_coverage_policy_recorded;
    unsigned negative_case_coverage_policy_recorded;
    unsigned import_review_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned fixture_source_url_recorded;
    unsigned fixture_source_digest_recorded;
    unsigned fixture_bundle_size_recorded;
    unsigned fixture_license_review_recorded;
    unsigned fixture_storage_path_recorded;
    unsigned fixture_schema_crosscheck_recorded;
    unsigned ml_kem_512_coverage_recorded;
    unsigned ml_kem_768_coverage_recorded;
    unsigned ml_kem_1024_coverage_recorded;
    unsigned keygen_coverage_recorded;
    unsigned encaps_coverage_recorded;
    unsigned decaps_coverage_recorded;
    unsigned negative_case_coverage_recorded;
    unsigned fixture_import_reviewed;
    unsigned fixture_digest_ledger_reviewed;
    unsigned fixture_bundle_loaded;
    unsigned vector_execution_allowed;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_fixture_digest_items_total;
    unsigned required_fixture_digest_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_STATE_MAX];
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_VECTOR_FIXTURE_DIGEST_LEDGER_STATE_MAX];
} latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t;

const char *latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_label(
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *out);
int latticra_q_seal_ml_kem_vector_fixture_digest_ledger_is_no_effect(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger);
int latticra_q_seal_ml_kem_vector_fixture_digest_ledger_allows_fixture_lock(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger);
latticra_q_seal_status_t latticra_q_seal_ml_kem_vector_fixture_digest_ledger_report(
    const latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t *ledger,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
