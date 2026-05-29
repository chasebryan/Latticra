#ifndef LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_H
#define LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_H

#include "latticra/q_seal_ml_kem.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_PROFILE_MAX 96u
#define LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_LABEL_MAX 160u
#define LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_STATE_MAX 192u
#define LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_REPORT_MAX 8192u

typedef enum {
    LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_OK = 0,
    LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_BLOCKED = 1,
    LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_INVALID_INPUT = 2
} latticra_q_seal_ml_kem_secret_state_contract_error_t;

typedef struct {
    char contract_profile[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_PROFILE_MAX];
    char formal_title[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_LABEL_MAX];
    char standards_source[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_LABEL_MAX];
    char source_boundary[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_LABEL_MAX];
    char contract_state[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_STATE_MAX];
    unsigned secret_state_contract_present;
    unsigned clean_room_source_boundary_recorded;
    unsigned apple_corecrypto_code_copied;
    unsigned external_provider_code_copied;
    unsigned implementation_code_present;
    unsigned secret_material_inventory_required;
    unsigned secret_material_inventory_recorded;
    unsigned secret_dependent_branch_forbidden;
    unsigned secret_dependent_branch_review_recorded;
    unsigned secret_indexed_memory_forbidden;
    unsigned secret_indexed_memory_review_recorded;
    unsigned secret_dependent_early_return_forbidden;
    unsigned secret_dependent_early_return_review_recorded;
    unsigned constant_time_compare_required;
    unsigned constant_time_compare_recorded;
    unsigned constant_time_decapsulation_required;
    unsigned constant_time_decapsulation_recorded;
    unsigned implicit_rejection_required;
    unsigned implicit_rejection_recorded;
    unsigned zeroization_required;
    unsigned zeroization_design_recorded;
    unsigned zeroization_primitive_selected;
    unsigned zeroization_primitive_implemented;
    unsigned randomness_boundary_required;
    unsigned randomness_boundary_recorded;
    unsigned seed_material_handling_required;
    unsigned seed_material_handling_recorded;
    unsigned stack_secret_spill_review_required;
    unsigned stack_secret_spill_review_recorded;
    unsigned compiler_optimization_review_required;
    unsigned compiler_optimization_review_recorded;
    unsigned sanitizer_strategy_required;
    unsigned sanitizer_strategy_recorded;
    unsigned side_channel_review_required;
    unsigned side_channel_review_recorded;
    unsigned operations_enabled;
    unsigned key_generation_enabled;
    unsigned encapsulation_enabled;
    unsigned decapsulation_enabled;
    unsigned shared_secret_emitted;
    unsigned production_crypto_claim_allowed;
    unsigned fips_claim_allowed;
    unsigned runtime_authority_granted;
    unsigned required_secret_state_items_total;
    unsigned required_secret_state_items_satisfied;
    char blocked_reason[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_STATE_MAX];
    latticra_q_seal_ml_kem_secret_state_contract_error_t error;
    char status[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_STATE_MAX];
} latticra_q_seal_ml_kem_secret_state_contract_t;

const char *latticra_q_seal_ml_kem_secret_state_contract_error_label(
    latticra_q_seal_ml_kem_secret_state_contract_error_t error);
latticra_q_seal_status_t latticra_q_seal_ml_kem_secret_state_contract_prepare(
    latticra_q_seal_ml_kem_secret_state_contract_t *out);
int latticra_q_seal_ml_kem_secret_state_contract_is_no_secret_effect(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract);
int latticra_q_seal_ml_kem_secret_state_contract_allows_operations(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract);
latticra_q_seal_status_t latticra_q_seal_ml_kem_secret_state_contract_report(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
