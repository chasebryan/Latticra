#include "latticra/q_seal_ml_kem_secret_state_contract.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static unsigned one_if(unsigned value) {
    return value != 0u ? 1u : 0u;
}

static unsigned required_items_satisfied(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract) {
    unsigned satisfied = 0u;

    satisfied += one_if(contract->clean_room_source_boundary_recorded);
    satisfied += one_if(contract->secret_dependent_branch_forbidden);
    satisfied += one_if(contract->secret_indexed_memory_forbidden);
    satisfied += one_if(contract->secret_dependent_early_return_forbidden);
    satisfied += one_if(contract->secret_material_inventory_recorded);
    satisfied += one_if(contract->secret_dependent_branch_review_recorded);
    satisfied += one_if(contract->secret_indexed_memory_review_recorded);
    satisfied += one_if(contract->secret_dependent_early_return_review_recorded);
    satisfied += one_if(contract->constant_time_compare_recorded);
    satisfied += one_if(contract->constant_time_decapsulation_recorded);
    satisfied += one_if(contract->implicit_rejection_recorded);
    satisfied += one_if(contract->zeroization_design_recorded);
    satisfied += one_if(contract->zeroization_primitive_selected);
    satisfied += one_if(contract->randomness_boundary_recorded);
    satisfied += one_if(contract->seed_material_handling_recorded);
    satisfied += one_if(contract->stack_secret_spill_review_recorded);
    satisfied += one_if(contract->compiler_optimization_review_recorded);
    satisfied += one_if(contract->sanitizer_strategy_recorded);
    satisfied += one_if(contract->side_channel_review_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_secret_state_contract_error_label(
    latticra_q_seal_ml_kem_secret_state_contract_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_secret_state_contract_prepare(
    latticra_q_seal_ml_kem_secret_state_contract_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->contract_profile,
        sizeof(out->contract_profile),
        "latticra-q-seal-ml-kem-secret-state-contract/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Secret-State Contract");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(out->contract_state, sizeof(out->contract_state), "constant-time-zeroization-design-only");

    out->secret_state_contract_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_code_present = 0u;
    out->secret_material_inventory_required = 1u;
    out->secret_material_inventory_recorded = 0u;
    out->secret_dependent_branch_forbidden = 1u;
    out->secret_dependent_branch_review_recorded = 0u;
    out->secret_indexed_memory_forbidden = 1u;
    out->secret_indexed_memory_review_recorded = 0u;
    out->secret_dependent_early_return_forbidden = 1u;
    out->secret_dependent_early_return_review_recorded = 0u;
    out->constant_time_compare_required = 1u;
    out->constant_time_compare_recorded = 0u;
    out->constant_time_decapsulation_required = 1u;
    out->constant_time_decapsulation_recorded = 0u;
    out->implicit_rejection_required = 1u;
    out->implicit_rejection_recorded = 0u;
    out->zeroization_required = 1u;
    out->zeroization_design_recorded = 0u;
    out->zeroization_primitive_selected = 0u;
    out->zeroization_primitive_implemented = 0u;
    out->randomness_boundary_required = 1u;
    out->randomness_boundary_recorded = 0u;
    out->seed_material_handling_required = 1u;
    out->seed_material_handling_recorded = 0u;
    out->stack_secret_spill_review_required = 1u;
    out->stack_secret_spill_review_recorded = 0u;
    out->compiler_optimization_review_required = 1u;
    out->compiler_optimization_review_recorded = 0u;
    out->sanitizer_strategy_required = 1u;
    out->sanitizer_strategy_recorded = 0u;
    out->side_channel_review_required = 1u;
    out->side_channel_review_recorded = 0u;
    out->operations_enabled = 0u;
    out->key_generation_enabled = 0u;
    out->encapsulation_enabled = 0u;
    out->decapsulation_enabled = 0u;
    out->shared_secret_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_secret_state_items_total = 19u;
    out->required_secret_state_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "secret-inventory-constant-time-zeroization-randomness-compiler-and-side-channel-reviews-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-secret-state-contract-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_secret_state_contract_is_no_secret_effect(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->implementation_code_present == 0u &&
           contract->zeroization_primitive_implemented == 0u &&
           contract->operations_enabled == 0u &&
           contract->key_generation_enabled == 0u &&
           contract->encapsulation_enabled == 0u &&
           contract->decapsulation_enabled == 0u &&
           contract->shared_secret_emitted == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u;
}

int latticra_q_seal_ml_kem_secret_state_contract_allows_operations(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->clean_room_source_boundary_recorded == 1u &&
           contract->secret_material_inventory_recorded == 1u &&
           contract->secret_dependent_branch_forbidden == 1u &&
           contract->secret_dependent_branch_review_recorded == 1u &&
           contract->secret_indexed_memory_forbidden == 1u &&
           contract->secret_indexed_memory_review_recorded == 1u &&
           contract->secret_dependent_early_return_forbidden == 1u &&
           contract->secret_dependent_early_return_review_recorded == 1u &&
           contract->constant_time_compare_recorded == 1u &&
           contract->constant_time_decapsulation_recorded == 1u &&
           contract->implicit_rejection_recorded == 1u &&
           contract->zeroization_design_recorded == 1u &&
           contract->zeroization_primitive_selected == 1u &&
           contract->zeroization_primitive_implemented == 1u &&
           contract->randomness_boundary_recorded == 1u &&
           contract->seed_material_handling_recorded == 1u &&
           contract->stack_secret_spill_review_recorded == 1u &&
           contract->compiler_optimization_review_recorded == 1u &&
           contract->sanitizer_strategy_recorded == 1u &&
           contract->side_channel_review_recorded == 1u &&
           contract->operations_enabled == 1u &&
           contract->production_crypto_claim_allowed == 1u &&
           contract->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_secret_state_contract_report(
    const latticra_q_seal_ml_kem_secret_state_contract_t *contract,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (contract == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SECRET-STATE CONTRACT\n"
        "contract_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "source_boundary=%s\n"
        "contract_state=%s\n"
        "secret_state_contract_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_code_present=%u\n"
        "secret_material_inventory_required=%u\n"
        "secret_material_inventory_recorded=%u\n"
        "secret_dependent_branch_forbidden=%u\n"
        "secret_dependent_branch_review_recorded=%u\n"
        "secret_indexed_memory_forbidden=%u\n"
        "secret_indexed_memory_review_recorded=%u\n"
        "secret_dependent_early_return_forbidden=%u\n"
        "secret_dependent_early_return_review_recorded=%u\n"
        "constant_time_compare_required=%u\n"
        "constant_time_compare_recorded=%u\n"
        "constant_time_decapsulation_required=%u\n"
        "constant_time_decapsulation_recorded=%u\n"
        "implicit_rejection_required=%u\n"
        "implicit_rejection_recorded=%u\n"
        "zeroization_required=%u\n"
        "zeroization_design_recorded=%u\n"
        "zeroization_primitive_selected=%u\n"
        "zeroization_primitive_implemented=%u\n"
        "randomness_boundary_required=%u\n"
        "randomness_boundary_recorded=%u\n"
        "seed_material_handling_required=%u\n"
        "seed_material_handling_recorded=%u\n"
        "stack_secret_spill_review_required=%u\n"
        "stack_secret_spill_review_recorded=%u\n"
        "compiler_optimization_review_required=%u\n"
        "compiler_optimization_review_recorded=%u\n"
        "sanitizer_strategy_required=%u\n"
        "sanitizer_strategy_recorded=%u\n"
        "side_channel_review_required=%u\n"
        "side_channel_review_recorded=%u\n"
        "operations_enabled=%u\n"
        "key_generation_enabled=%u\n"
        "encapsulation_enabled=%u\n"
        "decapsulation_enabled=%u\n"
        "shared_secret_emitted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_secret_state_items_total=%u\n"
        "required_secret_state_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        contract->contract_profile,
        contract->formal_title,
        contract->standards_source,
        contract->source_boundary,
        contract->contract_state,
        contract->secret_state_contract_present,
        contract->clean_room_source_boundary_recorded,
        contract->apple_corecrypto_code_copied,
        contract->external_provider_code_copied,
        contract->implementation_code_present,
        contract->secret_material_inventory_required,
        contract->secret_material_inventory_recorded,
        contract->secret_dependent_branch_forbidden,
        contract->secret_dependent_branch_review_recorded,
        contract->secret_indexed_memory_forbidden,
        contract->secret_indexed_memory_review_recorded,
        contract->secret_dependent_early_return_forbidden,
        contract->secret_dependent_early_return_review_recorded,
        contract->constant_time_compare_required,
        contract->constant_time_compare_recorded,
        contract->constant_time_decapsulation_required,
        contract->constant_time_decapsulation_recorded,
        contract->implicit_rejection_required,
        contract->implicit_rejection_recorded,
        contract->zeroization_required,
        contract->zeroization_design_recorded,
        contract->zeroization_primitive_selected,
        contract->zeroization_primitive_implemented,
        contract->randomness_boundary_required,
        contract->randomness_boundary_recorded,
        contract->seed_material_handling_required,
        contract->seed_material_handling_recorded,
        contract->stack_secret_spill_review_required,
        contract->stack_secret_spill_review_recorded,
        contract->compiler_optimization_review_required,
        contract->compiler_optimization_review_recorded,
        contract->sanitizer_strategy_required,
        contract->sanitizer_strategy_recorded,
        contract->side_channel_review_required,
        contract->side_channel_review_recorded,
        contract->operations_enabled,
        contract->key_generation_enabled,
        contract->encapsulation_enabled,
        contract->decapsulation_enabled,
        contract->shared_secret_emitted,
        contract->production_crypto_claim_allowed,
        contract->fips_claim_allowed,
        contract->runtime_authority_granted,
        contract->required_secret_state_items_total,
        contract->required_secret_state_items_satisfied,
        contract->blocked_reason,
        latticra_q_seal_ml_kem_secret_state_contract_error_label(contract->error),
        contract->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
