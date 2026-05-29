#include "latticra/q_seal_ml_kem_side_channel_review.h"

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
    const latticra_q_seal_ml_kem_side_channel_review_t *review) {
    unsigned satisfied = 0u;

    satisfied += one_if(review->fips_203_source_verified);
    satisfied += one_if(review->fips_140_3_non_invasive_security_tracked);
    satisfied += one_if(review->constant_time_review_bound);
    satisfied += one_if(review->secret_state_contract_bound);
    satisfied += one_if(review->power_analysis_review_required);
    satisfied += one_if(review->timing_leakage_review_required);
    satisfied += one_if(review->cache_access_review_required);
    satisfied += one_if(review->leakage_model_recorded);
    satisfied += one_if(review->power_analysis_test_recorded);
    satisfied += one_if(review->timing_measurement_recorded);
    satisfied += one_if(review->cache_access_analysis_recorded);
    satisfied += one_if(review->fault_injection_review_recorded);
    satisfied += one_if(review->microarchitectural_leakage_review_recorded);
    satisfied += one_if(review->masked_or_hardened_design_recorded);
    satisfied += one_if(review->compiler_artifact_review_recorded);
    satisfied += one_if(review->test_platform_matrix_recorded);
    satisfied += one_if(review->negative_leakage_test_recorded);
    satisfied += one_if(review->reviewer_signoff_recorded);
    satisfied += one_if(review->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_side_channel_review_error_label(
    latticra_q_seal_ml_kem_side_channel_review_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_side_channel_review_prepare(
    latticra_q_seal_ml_kem_side_channel_review_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->review_profile,
        sizeof(out->review_profile),
        "latticra-q-seal-ml-kem-side-channel-review/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Side-Channel Review");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->module_security_source,
        sizeof(out->module_security_source),
        "NIST-FIPS-140-3-non-invasive-security-posture");
    copy_literal(
        out->review_scope,
        sizeof(out->review_scope),
        "ML-KEM-keygen-encap-decap-side-channel-surface");
    copy_literal(
        out->review_state,
        sizeof(out->review_state),
        "policy-recorded-leakage-evidence-missing");

    out->side_channel_review_present = 1u;
    out->fips_203_source_verified = 1u;
    out->fips_140_3_non_invasive_security_tracked = 1u;
    out->constant_time_review_bound = 1u;
    out->secret_state_contract_bound = 1u;
    out->power_analysis_review_required = 1u;
    out->timing_leakage_review_required = 1u;
    out->cache_access_review_required = 1u;
    out->leakage_model_recorded = 0u;
    out->power_analysis_test_recorded = 0u;
    out->timing_measurement_recorded = 0u;
    out->cache_access_analysis_recorded = 0u;
    out->fault_injection_review_recorded = 0u;
    out->microarchitectural_leakage_review_recorded = 0u;
    out->masked_or_hardened_design_recorded = 0u;
    out->compiler_artifact_review_recorded = 0u;
    out->test_platform_matrix_recorded = 0u;
    out->negative_leakage_test_recorded = 0u;
    out->reviewer_signoff_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->side_channel_tests_executed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_review_items_total = 19u;
    out->required_review_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "leakage-model-power-timing-cache-fault-platform-signoff-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-side-channel-review-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_side_channel_review_is_policy_only(
    const latticra_q_seal_ml_kem_side_channel_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->side_channel_review_present == 1u &&
           review->power_analysis_review_required == 1u &&
           review->timing_leakage_review_required == 1u &&
           review->cache_access_review_required == 1u &&
           review->leakage_model_recorded == 0u &&
           review->power_analysis_test_recorded == 0u &&
           review->timing_measurement_recorded == 0u &&
           review->cache_access_analysis_recorded == 0u &&
           review->side_channel_tests_executed == 0u &&
           review->implementation_promotion_allowed == 0u &&
           review->operation_execution_allowed == 0u &&
           review->production_crypto_claim_allowed == 0u &&
           review->fips_claim_allowed == 0u &&
           review->runtime_authority_granted == 0u &&
           review->error == LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW_BLOCKED;
}

int latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_side_channel_review_t *review) {
    if (review == NULL) {
        return 0;
    }

    return review->fips_203_source_verified == 1u &&
           review->fips_140_3_non_invasive_security_tracked == 1u &&
           review->constant_time_review_bound == 1u &&
           review->secret_state_contract_bound == 1u &&
           review->power_analysis_review_required == 1u &&
           review->timing_leakage_review_required == 1u &&
           review->cache_access_review_required == 1u &&
           review->leakage_model_recorded == 1u &&
           review->power_analysis_test_recorded == 1u &&
           review->timing_measurement_recorded == 1u &&
           review->cache_access_analysis_recorded == 1u &&
           review->fault_injection_review_recorded == 1u &&
           review->microarchitectural_leakage_review_recorded == 1u &&
           review->masked_or_hardened_design_recorded == 1u &&
           review->compiler_artifact_review_recorded == 1u &&
           review->test_platform_matrix_recorded == 1u &&
           review->negative_leakage_test_recorded == 1u &&
           review->reviewer_signoff_recorded == 1u &&
           review->implementation_binding_recorded == 1u &&
           review->implementation_promotion_allowed == 1u &&
           review->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_side_channel_review_report(
    const latticra_q_seal_ml_kem_side_channel_review_t *review,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (review == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SIDE-CHANNEL REVIEW\n"
        "review_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "module_security_source=%s\n"
        "review_scope=%s\n"
        "review_state=%s\n"
        "side_channel_review_present=%u\n"
        "fips_203_source_verified=%u\n"
        "fips_140_3_non_invasive_security_tracked=%u\n"
        "constant_time_review_bound=%u\n"
        "secret_state_contract_bound=%u\n"
        "power_analysis_review_required=%u\n"
        "timing_leakage_review_required=%u\n"
        "cache_access_review_required=%u\n"
        "leakage_model_recorded=%u\n"
        "power_analysis_test_recorded=%u\n"
        "timing_measurement_recorded=%u\n"
        "cache_access_analysis_recorded=%u\n"
        "fault_injection_review_recorded=%u\n"
        "microarchitectural_leakage_review_recorded=%u\n"
        "masked_or_hardened_design_recorded=%u\n"
        "compiler_artifact_review_recorded=%u\n"
        "test_platform_matrix_recorded=%u\n"
        "negative_leakage_test_recorded=%u\n"
        "reviewer_signoff_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "side_channel_tests_executed=%u\n"
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
        review->module_security_source,
        review->review_scope,
        review->review_state,
        review->side_channel_review_present,
        review->fips_203_source_verified,
        review->fips_140_3_non_invasive_security_tracked,
        review->constant_time_review_bound,
        review->secret_state_contract_bound,
        review->power_analysis_review_required,
        review->timing_leakage_review_required,
        review->cache_access_review_required,
        review->leakage_model_recorded,
        review->power_analysis_test_recorded,
        review->timing_measurement_recorded,
        review->cache_access_analysis_recorded,
        review->fault_injection_review_recorded,
        review->microarchitectural_leakage_review_recorded,
        review->masked_or_hardened_design_recorded,
        review->compiler_artifact_review_recorded,
        review->test_platform_matrix_recorded,
        review->negative_leakage_test_recorded,
        review->reviewer_signoff_recorded,
        review->implementation_binding_recorded,
        review->side_channel_tests_executed,
        review->implementation_promotion_allowed,
        review->operation_execution_allowed,
        review->production_crypto_claim_allowed,
        review->fips_claim_allowed,
        review->runtime_authority_granted,
        review->required_review_items_total,
        review->required_review_items_satisfied,
        review->blocked_reason,
        latticra_q_seal_ml_kem_side_channel_review_error_label(review->error),
        review->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
