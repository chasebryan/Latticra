#include "latticra/q_seal_ml_kem_api_misuse_resistance.h"

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
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance) {
    unsigned satisfied = 0u;

    satisfied += one_if(resistance->fips_203_source_verified);
    satisfied += one_if(resistance->fips_140_3_interface_security_tracked);
    satisfied += one_if(resistance->nist_ssdf_source_tracked);
    satisfied += one_if(resistance->implementation_frame_bound);
    satisfied += one_if(resistance->memory_safety_evidence_bound);
    satisfied += one_if(resistance->negative_test_evidence_bound);
    satisfied += one_if(resistance->explicit_algorithm_identifier_required);
    satisfied += one_if(resistance->parameter_set_validation_required);
    satisfied += one_if(resistance->buffer_length_preflight_required);
    satisfied += one_if(resistance->typed_key_material_required);
    satisfied += one_if(resistance->no_implicit_rng_required);
    satisfied += one_if(resistance->error_taxonomy_recorded);
    satisfied += one_if(resistance->api_state_machine_recorded);
    satisfied += one_if(resistance->misuse_case_matrix_recorded);
    satisfied += one_if(resistance->wrong_parameter_set_tests_recorded);
    satisfied += one_if(resistance->null_and_overlap_tests_recorded);
    satisfied += one_if(resistance->deterministic_test_mode_guard_recorded);
    satisfied += one_if(resistance->secret_output_lifetime_policy_recorded);
    satisfied += one_if(resistance->language_binding_policy_recorded);
    satisfied += one_if(resistance->documentation_examples_review_recorded);
    satisfied += one_if(resistance->implementation_binding_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_api_misuse_resistance_error_label(
    latticra_q_seal_ml_kem_api_misuse_resistance_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_api_misuse_resistance_prepare(
    latticra_q_seal_ml_kem_api_misuse_resistance_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->resistance_profile,
        sizeof(out->resistance_profile),
        "latticra-q-seal-ml-kem-api-misuse-resistance/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM API Misuse Resistance");
    copy_literal(out->standards_source, sizeof(out->standards_source), "NIST-FIPS-203");
    copy_literal(
        out->module_security_source,
        sizeof(out->module_security_source),
        "NIST-FIPS-140-3-module-interface-security");
    copy_literal(
        out->secure_development_source,
        sizeof(out->secure_development_source),
        "NIST-SP-800-218-SSDF");
    copy_literal(
        out->resistance_scope,
        sizeof(out->resistance_scope),
        "ML-KEM-public-api-parameter-buffer-key-and-error-misuse-resistance");
    copy_literal(
        out->resistance_state,
        sizeof(out->resistance_state),
        "policy-recorded-misuse-test-evidence-missing");

    out->api_misuse_resistance_present = 1u;
    out->fips_203_source_verified = 1u;
    out->fips_140_3_interface_security_tracked = 1u;
    out->nist_ssdf_source_tracked = 1u;
    out->implementation_frame_bound = 1u;
    out->memory_safety_evidence_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->explicit_algorithm_identifier_required = 1u;
    out->parameter_set_validation_required = 1u;
    out->buffer_length_preflight_required = 1u;
    out->typed_key_material_required = 1u;
    out->no_implicit_rng_required = 1u;
    out->error_taxonomy_recorded = 0u;
    out->api_state_machine_recorded = 0u;
    out->misuse_case_matrix_recorded = 0u;
    out->wrong_parameter_set_tests_recorded = 0u;
    out->null_and_overlap_tests_recorded = 0u;
    out->deterministic_test_mode_guard_recorded = 0u;
    out->secret_output_lifetime_policy_recorded = 0u;
    out->language_binding_policy_recorded = 0u;
    out->documentation_examples_review_recorded = 0u;
    out->implementation_binding_recorded = 0u;
    out->api_misuse_tests_executed = 0u;
    out->public_api_execution_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_api_misuse_items_total = 21u;
    out->required_api_misuse_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "error-taxonomy-state-machine-misuse-tests-language-docs-and-binding-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-api-misuse-resistance-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_api_misuse_resistance_is_policy_only(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance) {
    if (resistance == NULL) {
        return 0;
    }

    return resistance->api_misuse_resistance_present == 1u &&
           resistance->explicit_algorithm_identifier_required == 1u &&
           resistance->parameter_set_validation_required == 1u &&
           resistance->buffer_length_preflight_required == 1u &&
           resistance->typed_key_material_required == 1u &&
           resistance->error_taxonomy_recorded == 0u &&
           resistance->api_state_machine_recorded == 0u &&
           resistance->misuse_case_matrix_recorded == 0u &&
           resistance->api_misuse_tests_executed == 0u &&
           resistance->public_api_execution_allowed == 0u &&
           resistance->implementation_promotion_allowed == 0u &&
           resistance->operation_execution_allowed == 0u &&
           resistance->production_crypto_claim_allowed == 0u &&
           resistance->fips_claim_allowed == 0u &&
           resistance->runtime_authority_granted == 0u &&
           resistance->error == LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE_BLOCKED;
}

int latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance) {
    if (resistance == NULL) {
        return 0;
    }

    return resistance->fips_203_source_verified == 1u &&
           resistance->fips_140_3_interface_security_tracked == 1u &&
           resistance->nist_ssdf_source_tracked == 1u &&
           resistance->implementation_frame_bound == 1u &&
           resistance->memory_safety_evidence_bound == 1u &&
           resistance->negative_test_evidence_bound == 1u &&
           resistance->explicit_algorithm_identifier_required == 1u &&
           resistance->parameter_set_validation_required == 1u &&
           resistance->buffer_length_preflight_required == 1u &&
           resistance->typed_key_material_required == 1u &&
           resistance->no_implicit_rng_required == 1u &&
           resistance->error_taxonomy_recorded == 1u &&
           resistance->api_state_machine_recorded == 1u &&
           resistance->misuse_case_matrix_recorded == 1u &&
           resistance->wrong_parameter_set_tests_recorded == 1u &&
           resistance->null_and_overlap_tests_recorded == 1u &&
           resistance->deterministic_test_mode_guard_recorded == 1u &&
           resistance->secret_output_lifetime_policy_recorded == 1u &&
           resistance->language_binding_policy_recorded == 1u &&
           resistance->documentation_examples_review_recorded == 1u &&
           resistance->implementation_binding_recorded == 1u &&
           resistance->public_api_execution_allowed == 1u &&
           resistance->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_api_misuse_resistance_report(
    const latticra_q_seal_ml_kem_api_misuse_resistance_t *resistance,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (resistance == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM API MISUSE RESISTANCE\n"
        "resistance_profile=%s\n"
        "formal_title=%s\n"
        "standards_source=%s\n"
        "module_security_source=%s\n"
        "secure_development_source=%s\n"
        "resistance_scope=%s\n"
        "resistance_state=%s\n"
        "api_misuse_resistance_present=%u\n"
        "fips_203_source_verified=%u\n"
        "fips_140_3_interface_security_tracked=%u\n"
        "nist_ssdf_source_tracked=%u\n"
        "implementation_frame_bound=%u\n"
        "memory_safety_evidence_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "explicit_algorithm_identifier_required=%u\n"
        "parameter_set_validation_required=%u\n"
        "buffer_length_preflight_required=%u\n"
        "typed_key_material_required=%u\n"
        "no_implicit_rng_required=%u\n"
        "error_taxonomy_recorded=%u\n"
        "api_state_machine_recorded=%u\n"
        "misuse_case_matrix_recorded=%u\n"
        "wrong_parameter_set_tests_recorded=%u\n"
        "null_and_overlap_tests_recorded=%u\n"
        "deterministic_test_mode_guard_recorded=%u\n"
        "secret_output_lifetime_policy_recorded=%u\n"
        "language_binding_policy_recorded=%u\n"
        "documentation_examples_review_recorded=%u\n"
        "implementation_binding_recorded=%u\n"
        "api_misuse_tests_executed=%u\n"
        "public_api_execution_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_api_misuse_items_total=%u\n"
        "required_api_misuse_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        resistance->resistance_profile,
        resistance->formal_title,
        resistance->standards_source,
        resistance->module_security_source,
        resistance->secure_development_source,
        resistance->resistance_scope,
        resistance->resistance_state,
        resistance->api_misuse_resistance_present,
        resistance->fips_203_source_verified,
        resistance->fips_140_3_interface_security_tracked,
        resistance->nist_ssdf_source_tracked,
        resistance->implementation_frame_bound,
        resistance->memory_safety_evidence_bound,
        resistance->negative_test_evidence_bound,
        resistance->explicit_algorithm_identifier_required,
        resistance->parameter_set_validation_required,
        resistance->buffer_length_preflight_required,
        resistance->typed_key_material_required,
        resistance->no_implicit_rng_required,
        resistance->error_taxonomy_recorded,
        resistance->api_state_machine_recorded,
        resistance->misuse_case_matrix_recorded,
        resistance->wrong_parameter_set_tests_recorded,
        resistance->null_and_overlap_tests_recorded,
        resistance->deterministic_test_mode_guard_recorded,
        resistance->secret_output_lifetime_policy_recorded,
        resistance->language_binding_policy_recorded,
        resistance->documentation_examples_review_recorded,
        resistance->implementation_binding_recorded,
        resistance->api_misuse_tests_executed,
        resistance->public_api_execution_allowed,
        resistance->implementation_promotion_allowed,
        resistance->operation_execution_allowed,
        resistance->production_crypto_claim_allowed,
        resistance->fips_claim_allowed,
        resistance->runtime_authority_granted,
        resistance->required_api_misuse_items_total,
        resistance->required_api_misuse_items_satisfied,
        resistance->blocked_reason,
        latticra_q_seal_ml_kem_api_misuse_resistance_error_label(resistance->error),
        resistance->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
