#include "latticra/q_seal_ml_kem_memory_safety_evidence.h"

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
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence) {
    unsigned satisfied = 0u;

    satisfied += one_if(evidence->fips_203_source_verified);
    satisfied += one_if(evidence->fips_140_3_software_security_tracked);
    satisfied += one_if(evidence->nist_ssdf_source_tracked);
    satisfied += one_if(evidence->implementation_frame_bound);
    satisfied += one_if(evidence->negative_test_evidence_bound);
    satisfied += one_if(evidence->bounded_buffer_policy_required);
    satisfied += one_if(evidence->fixed_capacity_api_policy_required);
    satisfied += one_if(evidence->allocation_policy_required);
    satisfied += one_if(evidence->size_overflow_checks_recorded);
    satisfied += one_if(evidence->bounds_check_review_recorded);
    satisfied += one_if(evidence->integer_overflow_review_recorded);
    satisfied += one_if(evidence->sanitizer_asan_ubsan_recorded);
    satisfied += one_if(evidence->static_analysis_recorded);
    satisfied += one_if(evidence->fuzz_memory_safety_recorded);
    satisfied += one_if(evidence->aliasing_lifetime_review_recorded);
    satisfied += one_if(evidence->secret_buffer_isolation_recorded);
    satisfied += one_if(evidence->constant_time_memory_copy_review_recorded);
    satisfied += one_if(evidence->zeroization_memory_safety_bound);
    satisfied += one_if(evidence->cross_platform_word_size_review_recorded);
    satisfied += one_if(evidence->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_memory_safety_evidence_error_label(
    latticra_q_seal_ml_kem_memory_safety_evidence_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_memory_safety_evidence_prepare(
    latticra_q_seal_ml_kem_memory_safety_evidence_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->evidence_profile,
        sizeof(out->evidence_profile),
        "latticra-q-seal-ml-kem-memory-safety-evidence/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Memory-Safety Evidence");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->module_security_source,
        sizeof(out->module_security_source),
        "NIST-FIPS-140-3-software-firmware-security");
    copy_literal(
        out->secure_development_source,
        sizeof(out->secure_development_source),
        "NIST-SP-800-218-SSDF");
    copy_literal(
        out->evidence_scope,
        sizeof(out->evidence_scope),
        "ML-KEM-buffer-bounds-integer-lifetime-and-secret-memory-safety");
    copy_literal(
        out->evidence_state,
        sizeof(out->evidence_state),
        "policy-recorded-analysis-and-test-evidence-missing");

    out->memory_safety_evidence_present = 1u;
    out->fips_203_source_verified = 1u;
    out->fips_140_3_software_security_tracked = 1u;
    out->nist_ssdf_source_tracked = 1u;
    out->implementation_frame_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->bounded_buffer_policy_required = 1u;
    out->fixed_capacity_api_policy_required = 1u;
    out->allocation_policy_required = 1u;
    out->size_overflow_checks_recorded = 0u;
    out->bounds_check_review_recorded = 0u;
    out->integer_overflow_review_recorded = 0u;
    out->sanitizer_asan_ubsan_recorded = 0u;
    out->static_analysis_recorded = 0u;
    out->fuzz_memory_safety_recorded = 0u;
    out->aliasing_lifetime_review_recorded = 0u;
    out->secret_buffer_isolation_recorded = 0u;
    out->constant_time_memory_copy_review_recorded = 0u;
    out->zeroization_memory_safety_bound = 0u;
    out->cross_platform_word_size_review_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->memory_safety_tests_executed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_memory_safety_items_total = 20u;
    out->required_memory_safety_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "overflow-bounds-sanitizer-static-fuzz-lifetime-secret-buffer-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-memory-safety-evidence-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_memory_safety_evidence_is_policy_only(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->memory_safety_evidence_present == 1u &&
           evidence->bounded_buffer_policy_required == 1u &&
           evidence->fixed_capacity_api_policy_required == 1u &&
           evidence->allocation_policy_required == 1u &&
           evidence->size_overflow_checks_recorded == 0u &&
           evidence->bounds_check_review_recorded == 0u &&
           evidence->integer_overflow_review_recorded == 0u &&
           evidence->memory_safety_tests_executed == 0u &&
           evidence->implementation_promotion_allowed == 0u &&
           evidence->operation_execution_allowed == 0u &&
           evidence->production_crypto_claim_allowed == 0u &&
           evidence->fips_claim_allowed == 0u &&
           evidence->runtime_authority_granted == 0u &&
           evidence->error == LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE_BLOCKED;
}

int latticra_q_seal_ml_kem_memory_safety_evidence_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence) {
    if (evidence == NULL) {
        return 0;
    }

    return evidence->fips_203_source_verified == 1u &&
           evidence->fips_140_3_software_security_tracked == 1u &&
           evidence->nist_ssdf_source_tracked == 1u &&
           evidence->implementation_frame_bound == 1u &&
           evidence->negative_test_evidence_bound == 1u &&
           evidence->bounded_buffer_policy_required == 1u &&
           evidence->fixed_capacity_api_policy_required == 1u &&
           evidence->allocation_policy_required == 1u &&
           evidence->size_overflow_checks_recorded == 1u &&
           evidence->bounds_check_review_recorded == 1u &&
           evidence->integer_overflow_review_recorded == 1u &&
           evidence->sanitizer_asan_ubsan_recorded == 1u &&
           evidence->static_analysis_recorded == 1u &&
           evidence->fuzz_memory_safety_recorded == 1u &&
           evidence->aliasing_lifetime_review_recorded == 1u &&
           evidence->secret_buffer_isolation_recorded == 1u &&
           evidence->constant_time_memory_copy_review_recorded == 1u &&
           evidence->zeroization_memory_safety_bound == 1u &&
           evidence->cross_platform_word_size_review_recorded == 1u &&
           evidence->implementation_binding_recorded == 1u &&
           evidence->implementation_promotion_allowed == 1u &&
           evidence->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_memory_safety_evidence_report(
    const latticra_q_seal_ml_kem_memory_safety_evidence_t *evidence,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (evidence == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM MEMORY-SAFETY EVIDENCE\n"
        "evidence_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "module_security_source=%s\n"
        "secure_development_source=%s\n"
        "evidence_scope=%s\n"
        "evidence_state=%s\n"
        "memory_safety_evidence_present=%u\n"
        "fips_203_source_verified=%u\n"
        "fips_140_3_software_security_tracked=%u\n"
        "nist_ssdf_source_tracked=%u\n"
        "implementation_frame_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "bounded_buffer_policy_required=%u\n"
        "fixed_capacity_api_policy_required=%u\n"
        "allocation_policy_required=%u\n"
        "size_overflow_checks_recorded=%u\n"
        "bounds_check_review_recorded=%u\n"
        "integer_overflow_review_recorded=%u\n"
        "sanitizer_asan_ubsan_recorded=%u\n"
        "static_analysis_recorded=%u\n"
        "fuzz_memory_safety_recorded=%u\n"
        "aliasing_lifetime_review_recorded=%u\n"
        "secret_buffer_isolation_recorded=%u\n"
        "constant_time_memory_copy_review_recorded=%u\n"
        "zeroization_memory_safety_bound=%u\n"
        "cross_platform_word_size_review_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "memory_safety_tests_executed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_memory_safety_items_total=%u\n"
        "required_memory_safety_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        evidence->evidence_profile,
        evidence->formal_title,
        evidence->standards_source,
        evidence->module_security_source,
        evidence->secure_development_source,
        evidence->evidence_scope,
        evidence->evidence_state,
        evidence->memory_safety_evidence_present,
        evidence->fips_203_source_verified,
        evidence->fips_140_3_software_security_tracked,
        evidence->nist_ssdf_source_tracked,
        evidence->implementation_frame_bound,
        evidence->negative_test_evidence_bound,
        evidence->bounded_buffer_policy_required,
        evidence->fixed_capacity_api_policy_required,
        evidence->allocation_policy_required,
        evidence->size_overflow_checks_recorded,
        evidence->bounds_check_review_recorded,
        evidence->integer_overflow_review_recorded,
        evidence->sanitizer_asan_ubsan_recorded,
        evidence->static_analysis_recorded,
        evidence->fuzz_memory_safety_recorded,
        evidence->aliasing_lifetime_review_recorded,
        evidence->secret_buffer_isolation_recorded,
        evidence->constant_time_memory_copy_review_recorded,
        evidence->zeroization_memory_safety_bound,
        evidence->cross_platform_word_size_review_recorded,
        evidence->implementation_binding_recorded,
        evidence->memory_safety_tests_executed,
        evidence->implementation_promotion_allowed,
        evidence->operation_execution_allowed,
        evidence->production_crypto_claim_allowed,
        evidence->fips_claim_allowed,
        evidence->runtime_authority_granted,
        evidence->required_memory_safety_items_total,
        evidence->required_memory_safety_items_satisfied,
        evidence->blocked_reason,
        latticra_q_seal_ml_kem_memory_safety_evidence_error_label(evidence->error),
        evidence->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
