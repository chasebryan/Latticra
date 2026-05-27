#ifndef LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_H
#define LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_LABEL_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_randomness_source_error_t;

typedef struct {
    char randomness_profile[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_LABEL_MAX];
    char random_bit_generation_source[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_LABEL_MAX];
    char randomness_scope[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_LABEL_MAX];
    char randomness_state[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_STATE_MAX];
    unsigned randomness_source_contract_present;
    unsigned fips_203_source_verified;
    unsigned sp_800_90a_tracked;
    unsigned sp_800_90b_tracked;
    unsigned keygen_seed_material_required;
    unsigned encapsulation_seed_material_required;
    unsigned deterministic_test_seed_separation_required;
    unsigned entropy_source_inventory_recorded;
    unsigned entropy_source_validation_recorded;
    unsigned drbg_selection_recorded;
    unsigned drbg_security_strength_recorded;
    unsigned seed_derivation_policy_recorded;
    unsigned reseed_policy_recorded;
    unsigned prediction_resistance_policy_recorded;
    unsigned health_tests_policy_recorded;
    unsigned failure_mode_policy_recorded;
    unsigned platform_rng_boundary_recorded;
    unsigned entropy_review_signoff_recorded;
    unsigned implementation_binding_recorded;
    unsigned random_bytes_generated;
    unsigned deterministic_test_seed_loaded;
    unsigned deterministic_rng_mode_enabled;
    unsigned random_bit_generation_allowed;
    unsigned key_generation_randomness_allowed;
    unsigned encapsulation_randomness_allowed;
    unsigned operation_execution_allowed;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_randomness_items_total;
    unsigned required_randomness_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_STATE_MAX];
    latticra_q_seal_ml_kem_randomness_source_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_STATE_MAX];
} latticra_q_seal_ml_kem_randomness_source_t;

const char *latticra_q_seal_ml_kem_randomness_source_error_label(
    latticra_q_seal_ml_kem_randomness_source_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_randomness_source_prepare(
    latticra_q_seal_ml_kem_randomness_source_t *out);
int latticra_q_seal_ml_kem_randomness_source_is_policy_only(
    const latticra_q_seal_ml_kem_randomness_source_t *source);
int latticra_q_seal_ml_kem_randomness_source_allows_random_generation(
    const latticra_q_seal_ml_kem_randomness_source_t *source);
latticra_q_seal_status_t latticra_q_seal_ml_kem_randomness_source_report(
    const latticra_q_seal_ml_kem_randomness_source_t *source,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
