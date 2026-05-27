#include "latticra/q_seal_ml_kem_zeroization_evidence.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int zeroization_evidence_records_policy_without_wiping(void) {
    latticra_q_seal_ml_kem_zeroization_evidence_t evidence;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(evidence.zeroization_profile, "latticra-q-seal-ml-kem-zeroization-evidence/0.1") ==
            0,
        "profile");
    EXPECT_TRUE(
        strcmp(evidence.formal_title, "Latticra Q-Seal ML-KEM Zeroization Evidence") == 0,
        "title");
    EXPECT_TRUE(strcmp(evidence.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(
        strcmp(evidence.module_security_source, "NIST-FIPS-140-3-zeroization-requirements") == 0,
        "module");
    EXPECT_TRUE(
        strcmp(evidence.zeroization_scope, "ML-KEM-secret-intermediates-key-and-seed-material") ==
            0,
        "scope");
    EXPECT_TRUE(
        strcmp(evidence.zeroization_state, "policy-recorded-primitive-not-implemented") == 0,
        "state");
    EXPECT_TRUE(evidence.zeroization_evidence_present == 1u, "present");
    EXPECT_TRUE(evidence.fips_203_source_verified == 1u, "fips 203");
    EXPECT_TRUE(evidence.fips_140_3_zeroization_tracked == 1u, "fips 140-3");
    EXPECT_TRUE(evidence.secret_state_contract_bound == 1u, "secret state");
    EXPECT_TRUE(evidence.zeroization_required == 1u, "required");
    EXPECT_TRUE(evidence.secret_material_inventory_required == 1u, "inventory required");
    EXPECT_TRUE(evidence.compiler_barrier_required == 1u, "compiler barrier");
    EXPECT_TRUE(evidence.zeroization_primitive_selected == 0u, "primitive selected");
    EXPECT_TRUE(evidence.zeroization_primitive_implemented == 0u, "primitive implemented");
    EXPECT_TRUE(evidence.dead_store_elimination_review_recorded == 0u, "dse");
    EXPECT_TRUE(evidence.volatile_or_intrinsic_strategy_recorded == 0u, "strategy");
    EXPECT_TRUE(evidence.stack_heap_register_clear_policy_recorded == 0u, "locations");
    EXPECT_TRUE(evidence.error_path_zeroization_recorded == 0u, "error path");
    EXPECT_TRUE(evidence.decapsulation_failure_zeroization_recorded == 0u, "decap failure");
    EXPECT_TRUE(evidence.test_harness_memory_scan_recorded == 0u, "memory scan");
    EXPECT_TRUE(evidence.sanitizer_or_valgrind_review_recorded == 0u, "sanitizer");
    EXPECT_TRUE(evidence.generated_assembly_review_recorded == 0u, "assembly");
    EXPECT_TRUE(evidence.cross_platform_review_recorded == 0u, "platform");
    EXPECT_TRUE(evidence.formal_review_recorded == 0u, "formal");
    EXPECT_TRUE(evidence.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(evidence.zeroization_performed == 0u, "performed");
    EXPECT_TRUE(evidence.secret_material_handling_allowed == 0u, "secret handling");
    EXPECT_TRUE(evidence.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(evidence.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(evidence.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(evidence.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(evidence.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(evidence.required_zeroization_items_total == 19u, "total");
    EXPECT_TRUE(evidence.required_zeroization_items_satisfied == 6u, "satisfied");
    EXPECT_TRUE(evidence.error == LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_is_policy_only(&evidence) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(&evidence) ==
            0,
        "secret handling helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_report(&evidence, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM ZEROIZATION EVIDENCE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "zeroization_evidence_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "zeroization_primitive_implemented=0") != 0, "primitive report");
    EXPECT_TRUE(strstr(rendered, "zeroization_performed=0") != 0, "performed report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-zeroization-evidence-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_zeroization_evidence_t evidence;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_is_policy_only(0) == 0,
        "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(0) == 0,
        "null secret handling");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_report(&evidence, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report evidence");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_zeroization_evidence_report(&evidence, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (zeroization_evidence_records_policy_without_wiping() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem zeroization evidence invariants: ok\n");
    return 0;
}
