#include "latticra/q_seal_ml_kem_constant_time_review.h"

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
    const latticra_q_seal_ml_kem_constant_time_review_t *review) {
    unsigned satisfied = 0u;

    satisfied += one_if(review->fips_203_source_verified);
    satisfied += one_if(review->secret_dependent_branch_forbidden);
    satisfied += one_if(review->secret_dependent_memory_index_forbidden);
    satisfied += one_if(review->secret_dependent_loop_bound_forbidden);
    satisfied += one_if(review->secret_dependent_early_return_forbidden);
    satisfied += one_if(review->constant_time_compare_required);
    satisfied += one_if(review->decapsulation_implicit_rejection_required);
    satisfied += one_if(review->compiler_optimization_review_required);
    satisfied += one_if(review->dudect_measurement_recorded);
    satisfied += one_if(review->ctgrind_or_static_analysis_recorded);
    satisfied += one_if(review->generated_assembly_review_recorded);
    satisfied += one_if(review->optimizer_flag_review_recorded);
    satisfied += one_if(review->secret_state_inventory_bound);
    satisfied += one_if(review->negative_timing_test_recorded);
    satisfied += one_if(review->cross_platform_timing_review_recorded);
    satisfied += one_if(review->formal_reviewer_signoff_recorded);
    satisfied += one_if(review->ci_constant_time_gate_recorded);
    satisfied += one_if(review->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_constant_time_review_error_label(
    latticra_q_seal_ml_kem_constant_time_review_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_review_prepare(
    latticra_q_seal_ml_kem_constant_time_review_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->review_profile,
        sizeof(out->review_profile),
        "latticra-q-seal-ml-kem-constant-time-review/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Constant-Time Review");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->review_scope,
        sizeof(out->review_scope),
        "ML-KEM-keygen-encap-decap-secret-state");
    copy_literal(
        out->analysis_policy,
        sizeof(out->analysis_policy),
        "no-secret-dependent-control-flow-or-addresses");
    copy_literal(
        out->review_state,
        sizeof(out->review_state),
        "design-rules-recorded-measurement-not-recorded");

    out->constant_time_review_present = 1u;
    out->fips_203_source_verified = 1u;
    out->secret_dependent_branch_forbidden = 1u;
    out->secret_dependent_memory_index_forbidden = 1u;
    out->secret_dependent_loop_bound_forbidden = 1u;
    out->secret_dependent_early_return_forbidden = 1u;
    out->constant_time_compare_required = 1u;
    out->decapsulation_implicit_rejection_required = 1u;
    out->compiler_optimization_review_required = 1u;
    out->dudect_measurement_recorded = 0u;
    out->ctgrind_or_static_analysis_recorded = 0u;
    out->generated_assembly_review_recorded = 0u;
    out->optimizer_flag_review_recorded = 0u;
    out->secret_state_inventory_bound = 0u;
    out->negative_timing_test_recorded = 0u;
    out->cross_platform_timing_review_recorded = 0u;
    out->formal_reviewer_signoff_recorded = 0u;
    out->ci_constant_time_gate_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->measurement_execution_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_review_items_total = 18u;
    out->required_review_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "timing-measurement-static-analysis-assembly-optimizer-inventory-ci-and-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-constant-time-review-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_constant_time_review_is_policy_only(
    const latticra_q_seal_ml_kem_constant_time_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->constant_time_review_present == 1u &&
           review->secret_dependent_branch_forbidden == 1u &&
           review->secret_dependent_memory_index_forbidden == 1u &&
           review->secret_dependent_loop_bound_forbidden == 1u &&
           review->secret_dependent_early_return_forbidden == 1u &&
           review->measurement_execution_allowed == 0u &&
           review->implementation_promotion_allowed == 0u &&
           review->operation_execution_allowed == 0u &&
           review->production_crypto_claim_allowed == 0u &&
           review->fips_claim_allowed == 0u &&
           review->runtime_authority_granted == 0u &&
           review->error == LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW_BLOCKED;
}

int latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_constant_time_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->fips_203_source_verified == 1u &&
           review->secret_dependent_branch_forbidden == 1u &&
           review->secret_dependent_memory_index_forbidden == 1u &&
           review->secret_dependent_loop_bound_forbidden == 1u &&
           review->secret_dependent_early_return_forbidden == 1u &&
           review->constant_time_compare_required == 1u &&
           review->decapsulation_implicit_rejection_required == 1u &&
           review->compiler_optimization_review_required == 1u &&
           review->dudect_measurement_recorded == 1u &&
           review->ctgrind_or_static_analysis_recorded == 1u &&
           review->generated_assembly_review_recorded == 1u &&
           review->optimizer_flag_review_recorded == 1u &&
           review->secret_state_inventory_bound == 1u &&
           review->negative_timing_test_recorded == 1u &&
           review->cross_platform_timing_review_recorded == 1u &&
           review->formal_reviewer_signoff_recorded == 1u &&
           review->ci_constant_time_gate_recorded == 1u &&
           review->implementation_binding_recorded == 1u &&
           review->measurement_execution_allowed == 1u &&
           review->implementation_promotion_allowed == 1u &&
           review->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_constant_time_review_report(
    const latticra_q_seal_ml_kem_constant_time_review_t *review,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (review == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM CONSTANT-TIME REVIEW\n"
        "review_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "review_scope=%s\n"
        "analysis_policy=%s\n"
        "review_state=%s\n"
        "constant_time_review_present=%u\n"
        "fips_203_source_verified=%u\n"
        "secret_dependent_branch_forbidden=%u\n"
        "secret_dependent_memory_index_forbidden=%u\n"
        "secret_dependent_loop_bound_forbidden=%u\n"
        "secret_dependent_early_return_forbidden=%u\n"
        "constant_time_compare_required=%u\n"
        "decapsulation_implicit_rejection_required=%u\n"
        "compiler_optimization_review_required=%u\n"
        "dudect_measurement_recorded=%u\n"
        "ctgrind_or_static_analysis_recorded=%u\n"
        "generated_assembly_review_recorded=%u\n"
        "optimizer_flag_review_recorded=%u\n"
        "secret_state_inventory_bound=%u\n"
        "negative_timing_test_recorded=%u\n"
        "cross_platform_timing_review_recorded=%u\n"
        "formal_reviewer_signoff_recorded=%u\n"
        "ci_constant_time_gate_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "measurement_execution_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_review_items_total=%u\n"
        "required_review_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        review->review_profile,
        review->formal_title,
        review->standards_source,
        review->review_scope,
        review->analysis_policy,
        review->review_state,
        review->constant_time_review_present,
        review->fips_203_source_verified,
        review->secret_dependent_branch_forbidden,
        review->secret_dependent_memory_index_forbidden,
        review->secret_dependent_loop_bound_forbidden,
        review->secret_dependent_early_return_forbidden,
        review->constant_time_compare_required,
        review->decapsulation_implicit_rejection_required,
        review->compiler_optimization_review_required,
        review->dudect_measurement_recorded,
        review->ctgrind_or_static_analysis_recorded,
        review->generated_assembly_review_recorded,
        review->optimizer_flag_review_recorded,
        review->secret_state_inventory_bound,
        review->negative_timing_test_recorded,
        review->cross_platform_timing_review_recorded,
        review->formal_reviewer_signoff_recorded,
        review->ci_constant_time_gate_recorded,
        review->implementation_binding_recorded,
        review->measurement_execution_allowed,
        review->implementation_promotion_allowed,
        review->operation_execution_allowed,
        review->production_crypto_claim_allowed,
        review->fips_claim_allowed,
        review->runtime_authority_granted,
        review->required_review_items_total,
        review->required_review_items_satisfied,
        review->blocked_reason,
        latticra_q_seal_ml_kem_constant_time_review_error_label(review->error),
        review->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
