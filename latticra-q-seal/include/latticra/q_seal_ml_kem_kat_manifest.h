#ifndef LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_H
#define LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_kat_manifest_error_t;

typedef struct {
    char manifest_profile[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_LABEL_MAX];
    char kat_scope[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_LABEL_MAX];
    char manifest_state[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_STATE_MAX];
    unsigned ml_kem_kat_manifest_present;
    unsigned fips_203_algorithm_bound;
    unsigned acvp_ml_kem_schema_bound;
    unsigned acvp_keygen_aft_required;
    unsigned acvp_encapdecap_aft_required;
    unsigned acvp_decapsulation_val_required;
    unsigned acvp_keycheck_val_required;
    unsigned ml_kem_512_coverage_required;
    unsigned ml_kem_768_coverage_required;
    unsigned ml_kem_1024_coverage_required;
    unsigned seed_material_handling_policy_recorded;
    unsigned positive_vector_family_required;
    unsigned negative_vector_family_required;
    unsigned malformed_vector_family_required;
    unsigned implicit_rejection_vector_required;
    unsigned acvp_parser_contract_bound;
    unsigned acvp_response_contract_bound;
    unsigned vector_schema_bound;
    unsigned vector_source_bound;
    unsigned vector_fixture_lock_bound;
    unsigned vector_fixture_digest_ledger_bound;
    unsigned negative_test_evidence_bound;
    unsigned provider_differential_bound;
    unsigned implementation_binding_manifest_bound;
    unsigned clean_room_source_boundary_recorded;
    unsigned no_embedded_vectors_policy_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned kat_runner_implementation_present;
    unsigned vector_bundle_digest_recorded;
    unsigned vector_bundle_license_reviewed;
    unsigned vector_bundle_storage_reviewed;
    unsigned kat_parser_reviewed;
    unsigned positive_vectors_verified;
    unsigned negative_vectors_verified;
    unsigned malformed_vectors_verified;
    unsigned cross_provider_differential_recorded;
    unsigned ci_kat_replay_recorded;
    unsigned known_answer_vectors_loaded;
    unsigned known_answer_vectors_verified;
    unsigned acvp_vector_review_recorded;
    unsigned operation_implementation_present;
    unsigned acvp_submission_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_kat_manifest_items_total;
    unsigned required_kat_manifest_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_STATE_MAX];
    latticra_q_seal_ml_kem_kat_manifest_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_KAT_MANIFEST_STATE_MAX];
} latticra_q_seal_ml_kem_kat_manifest_t;

const char *latticra_q_seal_ml_kem_kat_manifest_error_label(
    latticra_q_seal_ml_kem_kat_manifest_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_manifest_prepare(
    latticra_q_seal_ml_kem_kat_manifest_t *out);
int latticra_q_seal_ml_kem_kat_manifest_is_no_effect(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest);
int latticra_q_seal_ml_kem_kat_manifest_allows_kat_execution(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest);
latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_manifest_report(
    const latticra_q_seal_ml_kem_kat_manifest_t *manifest,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
