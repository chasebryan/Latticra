#ifndef LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE_H
#define LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_sp800_227_usage_profile_error_t;

typedef struct {
    char usage_profile[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX];
    char standards_basis[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX];
    char sp_800_227_source_url[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX];
    char sp_800_227_publication_date[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX];
    char usage_scope[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_LABEL_MAX];
    char usage_state[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_STATE_MAX];
    unsigned sp800_227_usage_profile_present;
    unsigned sp_800_227_source_bound;
    unsigned sp_800_227_publication_date_recorded;
    unsigned kem_definition_bound;
    unsigned shared_secret_establishment_scope_bound;
    unsigned encapsulation_role_bound;
    unsigned decapsulation_role_bound;
    unsigned approved_kem_algorithm_required;
    unsigned fips_203_ml_kem_bound;
    unsigned key_establishment_context_required;
    unsigned application_protocol_binding_required;
    unsigned key_confirmation_decision_required;
    unsigned kdf_boundary_required;
    unsigned domain_separation_required;
    unsigned shared_secret_lifecycle_required;
    unsigned failure_handling_required;
    unsigned key_separation_required;
    unsigned algorithm_agility_policy_required;
    unsigned clean_room_source_boundary_recorded;
    unsigned implementation_binding_required;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned kem_use_case_review_recorded;
    unsigned application_protocol_binding_recorded;
    unsigned key_confirmation_decision_recorded;
    unsigned kdf_binding_recorded;
    unsigned domain_separation_reviewed;
    unsigned shared_secret_lifecycle_reviewed;
    unsigned failure_handling_reviewed;
    unsigned key_separation_reviewed;
    unsigned algorithm_agility_reviewed;
    unsigned kem_usage_profile_accepted;
    unsigned operation_execution_allowed;
    unsigned shared_secret_emission_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_usage_items_total;
    unsigned required_usage_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_STATE_MAX];
    latticra_q_seal_ml_kem_sp800_227_usage_profile_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_STATE_MAX];
} latticra_q_seal_ml_kem_sp800_227_usage_profile_t;

const char *latticra_q_seal_ml_kem_sp800_227_usage_profile_error_label(
    latticra_q_seal_ml_kem_sp800_227_usage_profile_error_t error);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(
    latticra_q_seal_ml_kem_sp800_227_usage_profile_t *out);
int latticra_q_seal_ml_kem_sp800_227_usage_profile_is_no_effect(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile);
int latticra_q_seal_ml_kem_sp800_227_usage_profile_allows_kem_usage_acceptance(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile);
latticra_q_seal_status_t
latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
    const latticra_q_seal_ml_kem_sp800_227_usage_profile_t *profile,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
