#include "latticra/q_seal_ml_kem_zeroization_evidence.h"

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
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence) {
    unsigned satisfied = 0u;

    satisfied += one_if(evidence->fips_203_source_verified);
    satisfied += one_if(evidence->fips_140_3_zeroization_tracked);
    satisfied += one_if(evidence->secret_state_contract_bound);
    satisfied += one_if(evidence->zeroization_required);
    satisfied += one_if(evidence->secret_material_inventory_required);
    satisfied += one_if(evidence->compiler_barrier_required);
    satisfied += one_if(evidence->zeroization_primitive_selected);
    satisfied += one_if(evidence->zeroization_primitive_implemented);
    satisfied += one_if(evidence->dead_store_elimination_review_recorded);
    satisfied += one_if(evidence->volatile_or_intrinsic_strategy_recorded);
    satisfied += one_if(evidence->stack_heap_register_clear_policy_recorded);
    satisfied += one_if(evidence->error_path_zeroization_recorded);
    satisfied += one_if(evidence->decapsulation_failure_zeroization_recorded);
    satisfied += one_if(evidence->test_harness_memory_scan_recorded);
    satisfied += one_if(evidence->sanitizer_or_valgrind_review_recorded);
    satisfied += one_if(evidence->generated_assembly_review_recorded);
    satisfied += one_if(evidence->cross_platform_review_recorded);
    satisfied += one_if(evidence->formal_review_recorded);
    satisfied += one_if(evidence->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_zeroization_evidence_error_label(
    latticra_q_seal_ml_kem_zeroization_evidence_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_zeroization_evidence_prepare(
    latticra_q_seal_ml_kem_zeroization_evidence_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->zeroization_profile,
        sizeof(out->zeroization_profile),
        "latticra-q-seal-ml-kem-zeroization-evidence/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Zeroization Evidence");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->module_security_source,
        sizeof(out->module_security_source),
        "NIST-FIPS-140-3-zeroization-requirements");
    copy_literal(
        out->zeroization_scope,
        sizeof(out->zeroization_scope),
        "ML-KEM-secret-intermediates-key-and-seed-material");
    copy_literal(
        out->zeroization_state,
        sizeof(out->zeroization_state),
        "policy-recorded-primitive-not-implemented");

    out->zeroization_evidence_present = 1u;
    out->fips_203_source_verified = 1u;
    out->fips_140_3_zeroization_tracked = 1u;
    out->secret_state_contract_bound = 1u;
    out->zeroization_required = 1u;
    out->secret_material_inventory_required = 1u;
    out->compiler_barrier_required = 1u;
    out->zeroization_primitive_selected = 0u;
    out->zeroization_primitive_implemented = 0u;
    out->dead_store_elimination_review_recorded = 0u;
    out->volatile_or_intrinsic_strategy_recorded = 0u;
    out->stack_heap_register_clear_policy_recorded = 0u;
    out->error_path_zeroization_recorded = 0u;
    out->decapsulation_failure_zeroization_recorded = 0u;
    out->test_harness_memory_scan_recorded = 0u;
    out->sanitizer_or_valgrind_review_recorded = 0u;
    out->generated_assembly_review_recorded = 0u;
    out->cross_platform_review_recorded = 0u;
    out->formal_review_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->zeroization_performed = 0u;
    out->secret_material_handling_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_zeroization_items_total = 19u;
    out->required_zeroization_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "zeroization-primitive-compiler-strategy-path-tests-assembly-review-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-zeroization-evidence-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_zeroization_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->zeroization_evidence_present == 1u &&
           evidence->zeroization_required == 1u &&
           evidence->compiler_barrier_required == 1u &&
           evidence->zeroization_primitive_selected == 0u &&
           evidence->zeroization_primitive_implemented == 0u &&
           evidence->zeroization_performed == 0u &&
           evidence->secret_material_handling_allowed == 0u &&
           evidence->implementation_promotion_allowed == 0u &&
           evidence->operation_execution_allowed == 0u &&
           evidence->production_crypto_claim_allowed == 0u &&
           evidence->fips_claim_allowed == 0u &&
           evidence->runtime_authority_granted == 0u &&
           evidence->error == LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE_BLOCKED;
}

int latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->fips_203_source_verified == 1u &&
           evidence->fips_140_3_zeroization_tracked == 1u &&
           evidence->secret_state_contract_bound == 1u &&
           evidence->zeroization_required == 1u &&
           evidence->secret_material_inventory_required == 1u &&
           evidence->compiler_barrier_required == 1u &&
           evidence->zeroization_primitive_selected == 1u &&
           evidence->zeroization_primitive_implemented == 1u &&
           evidence->dead_store_elimination_review_recorded == 1u &&
           evidence->volatile_or_intrinsic_strategy_recorded == 1u &&
           evidence->stack_heap_register_clear_policy_recorded == 1u &&
           evidence->error_path_zeroization_recorded == 1u &&
           evidence->decapsulation_failure_zeroization_recorded == 1u &&
           evidence->test_harness_memory_scan_recorded == 1u &&
           evidence->sanitizer_or_valgrind_review_recorded == 1u &&
           evidence->generated_assembly_review_recorded == 1u &&
           evidence->cross_platform_review_recorded == 1u &&
           evidence->formal_review_recorded == 1u &&
           evidence->implementation_binding_recorded == 1u &&
           evidence->secret_material_handling_allowed == 1u &&
           evidence->implementation_promotion_allowed == 1u &&
           evidence->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_zeroization_evidence_report(
    const latticra_q_seal_ml_kem_zeroization_evidence_t *evidence,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evidence == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ZEROIZATION EVIDENCE\n"
        "zeroization_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "module_security_source=%s\n"
        "zeroization_scope=%s\n"
        "zeroization_state=%s\n"
        "zeroization_evidence_present=%u\n"
        "fips_203_source_verified=%u\n"
        "fips_140_3_zeroization_tracked=%u\n"
        "secret_state_contract_bound=%u\n"
        "zeroization_required=%u\n"
        "secret_material_inventory_required=%u\n"
        "compiler_barrier_required=%u\n"
        "zeroization_primitive_selected=%u\n"
        "zeroization_primitive_implemented=%u\n"
        "dead_store_elimination_review_recorded=%u\n"
        "volatile_or_intrinsic_strategy_recorded=%u\n"
        "stack_heap_register_clear_policy_recorded=%u\n"
        "error_path_zeroization_recorded=%u\n"
        "decapsulation_failure_zeroization_recorded=%u\n"
        "test_harness_memory_scan_recorded=%u\n"
        "sanitizer_or_valgrind_review_recorded=%u\n"
        "generated_assembly_review_recorded=%u\n"
        "cross_platform_review_recorded=%u\n"
        "formal_review_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "zeroization_performed=%u\n"
        "secret_material_handling_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_zeroization_items_total=%u\n"
        "required_zeroization_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        evidence->zeroization_profile,
        evidence->formal_title,
        evidence->standards_source,
        evidence->module_security_source,
        evidence->zeroization_scope,
        evidence->zeroization_state,
        evidence->zeroization_evidence_present,
        evidence->fips_203_source_verified,
        evidence->fips_140_3_zeroization_tracked,
        evidence->secret_state_contract_bound,
        evidence->zeroization_required,
        evidence->secret_material_inventory_required,
        evidence->compiler_barrier_required,
        evidence->zeroization_primitive_selected,
        evidence->zeroization_primitive_implemented,
        evidence->dead_store_elimination_review_recorded,
        evidence->volatile_or_intrinsic_strategy_recorded,
        evidence->stack_heap_register_clear_policy_recorded,
        evidence->error_path_zeroization_recorded,
        evidence->decapsulation_failure_zeroization_recorded,
        evidence->test_harness_memory_scan_recorded,
        evidence->sanitizer_or_valgrind_review_recorded,
        evidence->generated_assembly_review_recorded,
        evidence->cross_platform_review_recorded,
        evidence->formal_review_recorded,
        evidence->implementation_binding_recorded,
        evidence->zeroization_performed,
        evidence->secret_material_handling_allowed,
        evidence->implementation_promotion_allowed,
        evidence->operation_execution_allowed,
        evidence->production_crypto_claim_allowed,
        evidence->fips_claim_allowed,
        evidence->runtime_authority_granted,
        evidence->required_zeroization_items_total,
        evidence->required_zeroization_items_satisfied,
        evidence->blocked_reason,
        latticra_q_seal_ml_kem_zeroization_evidence_error_label(evidence->error),
        evidence->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
