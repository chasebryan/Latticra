#include "latticra/q_seal_ml_kem_secret_state_contract.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int secret_state_contract_is_no_secret_effect(void) {
    latticra_q_seal_ml_kem_secret_state_contract_t contract;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(contract.contract_profile, "latticra-q-seal-ml-kem-secret-state-contract/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(contract.formal_title, "Latticra Q-Seal ML-KEM Secret-State Contract") == 0,
        "title");
    EXPECT_TRUE(strcmp(contract.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(strcmp(contract.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(
        strcmp(contract.contract_state, "constant-time-zeroization-design-only") == 0,
        "state");
    EXPECT_TRUE(contract.secret_state_contract_present == 1u, "present");
    EXPECT_TRUE(contract.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(contract.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(contract.external_provider_code_copied == 0u, "provider code");
    EXPECT_TRUE(contract.implementation_code_present == 0u, "implementation");
    EXPECT_TRUE(contract.secret_material_inventory_required == 1u, "inventory required");
    EXPECT_TRUE(contract.secret_material_inventory_recorded == 0u, "inventory recorded");
    EXPECT_TRUE(contract.secret_dependent_branch_forbidden == 1u, "branch forbidden");
    EXPECT_TRUE(contract.secret_dependent_branch_review_recorded == 0u, "branch review");
    EXPECT_TRUE(contract.secret_indexed_memory_forbidden == 1u, "memory forbidden");
    EXPECT_TRUE(contract.secret_indexed_memory_review_recorded == 0u, "memory review");
    EXPECT_TRUE(contract.secret_dependent_early_return_forbidden == 1u, "early return forbidden");
    EXPECT_TRUE(contract.secret_dependent_early_return_review_recorded == 0u, "early return review");
    EXPECT_TRUE(contract.constant_time_compare_required == 1u, "compare required");
    EXPECT_TRUE(contract.constant_time_compare_recorded == 0u, "compare recorded");
    EXPECT_TRUE(contract.constant_time_decapsulation_required == 1u, "decaps required");
    EXPECT_TRUE(contract.constant_time_decapsulation_recorded == 0u, "decaps recorded");
    EXPECT_TRUE(contract.implicit_rejection_required == 1u, "implicit rejection required");
    EXPECT_TRUE(contract.implicit_rejection_recorded == 0u, "implicit rejection recorded");
    EXPECT_TRUE(contract.zeroization_required == 1u, "zeroization required");
    EXPECT_TRUE(contract.zeroization_design_recorded == 0u, "zeroization design");
    EXPECT_TRUE(contract.zeroization_primitive_selected == 0u, "zeroization selected");
    EXPECT_TRUE(contract.zeroization_primitive_implemented == 0u, "zeroization implemented");
    EXPECT_TRUE(contract.randomness_boundary_required == 1u, "randomness required");
    EXPECT_TRUE(contract.randomness_boundary_recorded == 0u, "randomness recorded");
    EXPECT_TRUE(contract.seed_material_handling_required == 1u, "seed required");
    EXPECT_TRUE(contract.seed_material_handling_recorded == 0u, "seed recorded");
    EXPECT_TRUE(contract.stack_secret_spill_review_required == 1u, "stack required");
    EXPECT_TRUE(contract.stack_secret_spill_review_recorded == 0u, "stack recorded");
    EXPECT_TRUE(contract.compiler_optimization_review_required == 1u, "compiler required");
    EXPECT_TRUE(contract.compiler_optimization_review_recorded == 0u, "compiler recorded");
    EXPECT_TRUE(contract.sanitizer_strategy_required == 1u, "sanitizer required");
    EXPECT_TRUE(contract.sanitizer_strategy_recorded == 0u, "sanitizer recorded");
    EXPECT_TRUE(contract.side_channel_review_required == 1u, "side channel required");
    EXPECT_TRUE(contract.side_channel_review_recorded == 0u, "side channel recorded");
    EXPECT_TRUE(contract.operations_enabled == 0u, "operations");
    EXPECT_TRUE(contract.key_generation_enabled == 0u, "keygen");
    EXPECT_TRUE(contract.encapsulation_enabled == 0u, "encaps");
    EXPECT_TRUE(contract.decapsulation_enabled == 0u, "decaps");
    EXPECT_TRUE(contract.shared_secret_emitted == 0u, "shared secret");
    EXPECT_TRUE(contract.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(contract.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(contract.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(contract.required_secret_state_items_total == 19u, "total");
    EXPECT_TRUE(contract.required_secret_state_items_satisfied == 4u, "satisfied");
    EXPECT_TRUE(contract.error == LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_is_no_secret_effect(&contract) == 1,
        "no secret effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_allows_operations(&contract) == 0,
        "allows operations");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_report(
            &contract,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SECRET-STATE CONTRACT") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "secret_dependent_branch_forbidden=1") != 0, "branch");
    EXPECT_TRUE(strstr(rendered, "zeroization_primitive_implemented=0") != 0, "zeroization");
    EXPECT_TRUE(strstr(rendered, "shared_secret_emitted=0") != 0, "shared secret report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-secret-state-contract-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_secret_state_contract_t contract;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_is_no_secret_effect(0) == 0,
        "null no secret effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_allows_operations(0) == 0,
        "null allows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_prepare(&contract) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_report(&contract, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report contract");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_secret_state_contract_report(&contract, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (secret_state_contract_is_no_secret_effect() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem secret-state contract invariants: ok\n");
    return 0;
}
