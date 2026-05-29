#include "latticra/q_seal_ml_kem_acvp_response_contract.h"

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
    const latticra_q_seal_ml_kem_acvp_response_contract_t *contract) {
    unsigned satisfied = 0u;

    satisfied += one_if(contract->acvp_response_contract_present);
    satisfied += one_if(contract->fips_203_algorithm_bound);
    satisfied += one_if(contract->acvp_ml_kem_json_bound);
    satisfied += one_if(contract->acvp_intake_bound);
    satisfied += one_if(contract->acvp_capability_matrix_bound);
    satisfied += one_if(contract->acvp_fixture_row_plan_bound);
    satisfied += one_if(contract->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(contract->acvp_parser_contract_bound);
    satisfied += one_if(contract->acvp_response_fixture_bound);
    satisfied += one_if(contract->vector_schema_bound);
    satisfied += one_if(contract->vector_source_intake_bound);
    satisfied += one_if(contract->vector_fixture_digest_ledger_bound);
    satisfied += one_if(contract->negative_test_evidence_bound);
    satisfied += one_if(contract->implementation_binding_manifest_bound);
    satisfied += one_if(contract->clean_room_source_boundary_recorded);
    satisfied += one_if(contract->response_envelope_policy_recorded);
    satisfied += one_if(contract->keygen_response_fields_policy_recorded);
    satisfied += one_if(contract->encapsulation_response_fields_policy_recorded);
    satisfied += one_if(contract->decapsulation_response_fields_policy_recorded);
    satisfied += one_if(contract->key_check_response_fields_policy_recorded);
    satisfied += one_if(contract->tcid_tgid_mapping_required);
    satisfied += one_if(contract->acv_version_echo_policy_recorded);
    satisfied += one_if(contract->vsid_echo_policy_recorded);
    satisfied += one_if(contract->parameter_set_crosscheck_required);
    satisfied += one_if(contract->function_crosscheck_required);
    satisfied += one_if(contract->hex_output_canonicalization_required);
    satisfied += one_if(contract->boolean_output_policy_recorded);
    satisfied += one_if(contract->deterministic_ordering_required);
    satisfied += one_if(contract->duplicate_response_rejection_required);
    satisfied += one_if(contract->unknown_response_field_rejection_required);
    satisfied += one_if(contract->response_size_limit_recorded);
    satisfied += one_if(contract->no_dynamic_code_loading_required);
    satisfied += one_if(contract->no_network_submission_required);
    satisfied += one_if(contract->response_generator_implementation_present);
    satisfied += one_if(contract->response_negative_tests_recorded);
    satisfied += one_if(contract->response_schema_reviewed);
    satisfied += one_if(contract->response_security_reviewed);
    satisfied += one_if(contract->response_ci_replay_recorded);
    satisfied += one_if(contract->parser_output_accepted);
    satisfied += one_if(contract->vector_execution_evidence_recorded);
    satisfied += one_if(contract->response_json_generation_enabled);
    satisfied += one_if(contract->response_output_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_response_contract_error_label(
    latticra_q_seal_ml_kem_acvp_response_contract_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_contract_prepare(
    latticra_q_seal_ml_kem_acvp_response_contract_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->response_profile,
        sizeof(out->response_profile),
        "latticra-q-seal-ml-kem-acvp-response-contract/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Response Contract");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->response_scope,
        sizeof(out->response_scope),
        "ML-KEM-ACVP-JSON-response-contract-before-response-generation");
    copy_literal(
        out->response_state,
        sizeof(out->response_state),
        "response-contract-recorded-response-generator-missing");

    out->acvp_response_contract_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_intake_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_fixture_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_intake_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->response_envelope_policy_recorded = 1u;
    out->keygen_response_fields_policy_recorded = 1u;
    out->encapsulation_response_fields_policy_recorded = 1u;
    out->decapsulation_response_fields_policy_recorded = 1u;
    out->key_check_response_fields_policy_recorded = 1u;
    out->tcid_tgid_mapping_required = 1u;
    out->acv_version_echo_policy_recorded = 1u;
    out->vsid_echo_policy_recorded = 1u;
    out->parameter_set_crosscheck_required = 1u;
    out->function_crosscheck_required = 1u;
    out->hex_output_canonicalization_required = 1u;
    out->boolean_output_policy_recorded = 1u;
    out->deterministic_ordering_required = 1u;
    out->duplicate_response_rejection_required = 1u;
    out->unknown_response_field_rejection_required = 1u;
    out->response_size_limit_recorded = 1u;
    out->no_dynamic_code_loading_required = 1u;
    out->no_network_submission_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->response_generator_implementation_present = 0u;
    out->response_negative_tests_recorded = 0u;
    out->response_schema_reviewed = 0u;
    out->response_security_reviewed = 0u;
    out->response_ci_replay_recorded = 0u;
    out->parser_output_accepted = 0u;
    out->vector_execution_evidence_recorded = 0u;
    out->response_json_generation_enabled = 0u;
    out->response_output_accepted = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_response_contract_items_total = 42u;
    out->required_response_contract_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "response-generator-negative-tests-schema-review-security-review-ci-replay-parser-output-vector-evidence-generation-and-output-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-acvp-response-contract-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_response_contract_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_response_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_response_contract_present == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->response_generator_implementation_present == 0u &&
           contract->parser_output_accepted == 0u &&
           contract->vector_execution_evidence_recorded == 0u &&
           contract->response_json_generation_enabled == 0u &&
           contract->response_output_accepted == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u &&
           contract->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_CONTRACT_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_response_contract_allows_response_generation(
    const latticra_q_seal_ml_kem_acvp_response_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_response_contract_present == 1u &&
           contract->fips_203_algorithm_bound == 1u &&
           contract->acvp_ml_kem_json_bound == 1u &&
           contract->acvp_intake_bound == 1u &&
           contract->acvp_capability_matrix_bound == 1u &&
           contract->acvp_fixture_row_plan_bound == 1u &&
           contract->acvp_fixture_digest_row_template_bound == 1u &&
           contract->acvp_parser_contract_bound == 1u &&
           contract->acvp_response_fixture_bound == 1u &&
           contract->vector_schema_bound == 1u &&
           contract->vector_source_intake_bound == 1u &&
           contract->vector_fixture_digest_ledger_bound == 1u &&
           contract->negative_test_evidence_bound == 1u &&
           contract->implementation_binding_manifest_bound == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->response_envelope_policy_recorded == 1u &&
           contract->keygen_response_fields_policy_recorded == 1u &&
           contract->encapsulation_response_fields_policy_recorded == 1u &&
           contract->decapsulation_response_fields_policy_recorded == 1u &&
           contract->key_check_response_fields_policy_recorded == 1u &&
           contract->tcid_tgid_mapping_required == 1u &&
           contract->acv_version_echo_policy_recorded == 1u &&
           contract->vsid_echo_policy_recorded == 1u &&
           contract->parameter_set_crosscheck_required == 1u &&
           contract->function_crosscheck_required == 1u &&
           contract->hex_output_canonicalization_required == 1u &&
           contract->boolean_output_policy_recorded == 1u &&
           contract->deterministic_ordering_required == 1u &&
           contract->duplicate_response_rejection_required == 1u &&
           contract->unknown_response_field_rejection_required == 1u &&
           contract->response_size_limit_recorded == 1u &&
           contract->no_dynamic_code_loading_required == 1u &&
           contract->no_network_submission_required == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->response_generator_implementation_present == 1u &&
           contract->response_negative_tests_recorded == 1u &&
           contract->response_schema_reviewed == 1u &&
           contract->response_security_reviewed == 1u &&
           contract->response_ci_replay_recorded == 1u &&
           contract->parser_output_accepted == 1u &&
           contract->vector_execution_evidence_recorded == 1u &&
           contract->response_json_generation_enabled == 1u &&
           contract->response_output_accepted == 1u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_contract_report(
    const latticra_q_seal_ml_kem_acvp_response_contract_t *contract,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (contract == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP RESPONSE CONTRACT\n"
        "response_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "response_scope=%s\n"
        "response_state=%s\n"
        "acvp_response_contract_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_intake_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_fixture_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_intake_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "response_envelope_policy_recorded=%u\n"
        "keygen_response_fields_policy_recorded=%u\n"
        "encapsulation_response_fields_policy_recorded=%u\n"
        "decapsulation_response_fields_policy_recorded=%u\n"
        "key_check_response_fields_policy_recorded=%u\n"
        "tcid_tgid_mapping_required=%u\n"
        "acv_version_echo_policy_recorded=%u\n"
        "vsid_echo_policy_recorded=%u\n"
        "parameter_set_crosscheck_required=%u\n"
        "function_crosscheck_required=%u\n"
        "hex_output_canonicalization_required=%u\n"
        "boolean_output_policy_recorded=%u\n"
        "deterministic_ordering_required=%u\n"
        "duplicate_response_rejection_required=%u\n"
        "unknown_response_field_rejection_required=%u\n"
        "response_size_limit_recorded=%u\n"
        "no_dynamic_code_loading_required=%u\n"
        "no_network_submission_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "response_generator_implementation_present=%u\n"
        "response_negative_tests_recorded=%u\n"
        "response_schema_reviewed=%u\n"
        "response_security_reviewed=%u\n"
        "response_ci_replay_recorded=%u\n"
        "parser_output_accepted=%u\n"
        "vector_execution_evidence_recorded=%u\n"
        "response_json_generation_enabled=%u\n"
        "response_output_accepted=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_response_contract_items_total=%u\n"
        "required_response_contract_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        contract->response_profile,
        contract->formal_title,
        contract->standards_basis,
        contract->response_scope,
        contract->response_state,
        contract->acvp_response_contract_present,
        contract->fips_203_algorithm_bound,
        contract->acvp_ml_kem_json_bound,
        contract->acvp_intake_bound,
        contract->acvp_capability_matrix_bound,
        contract->acvp_fixture_row_plan_bound,
        contract->acvp_fixture_digest_row_template_bound,
        contract->acvp_parser_contract_bound,
        contract->acvp_response_fixture_bound,
        contract->vector_schema_bound,
        contract->vector_source_intake_bound,
        contract->vector_fixture_digest_ledger_bound,
        contract->negative_test_evidence_bound,
        contract->implementation_binding_manifest_bound,
        contract->clean_room_source_boundary_recorded,
        contract->response_envelope_policy_recorded,
        contract->keygen_response_fields_policy_recorded,
        contract->encapsulation_response_fields_policy_recorded,
        contract->decapsulation_response_fields_policy_recorded,
        contract->key_check_response_fields_policy_recorded,
        contract->tcid_tgid_mapping_required,
        contract->acv_version_echo_policy_recorded,
        contract->vsid_echo_policy_recorded,
        contract->parameter_set_crosscheck_required,
        contract->function_crosscheck_required,
        contract->hex_output_canonicalization_required,
        contract->boolean_output_policy_recorded,
        contract->deterministic_ordering_required,
        contract->duplicate_response_rejection_required,
        contract->unknown_response_field_rejection_required,
        contract->response_size_limit_recorded,
        contract->no_dynamic_code_loading_required,
        contract->no_network_submission_required,
        contract->apple_corecrypto_code_copied,
        contract->external_provider_code_copied,
        contract->response_generator_implementation_present,
        contract->response_negative_tests_recorded,
        contract->response_schema_reviewed,
        contract->response_security_reviewed,
        contract->response_ci_replay_recorded,
        contract->parser_output_accepted,
        contract->vector_execution_evidence_recorded,
        contract->response_json_generation_enabled,
        contract->response_output_accepted,
        contract->acvp_submission_allowed,
        contract->operation_execution_allowed,
        contract->production_crypto_claim_allowed,
        contract->fips_claim_allowed,
        contract->runtime_authority_granted,
        contract->required_response_contract_items_total,
        contract->required_response_contract_items_satisfied,
        contract->blocked_reason,
        latticra_q_seal_ml_kem_acvp_response_contract_error_label(contract->error),
        contract->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
