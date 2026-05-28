#include "latticra/q_seal_ml_kem_acvp_parser_contract.h"

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
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract) {
    unsigned satisfied = 0u;

    satisfied += one_if(contract->acvp_parser_contract_present);
    satisfied += one_if(contract->fips_203_algorithm_bound);
    satisfied += one_if(contract->acvp_ml_kem_json_bound);
    satisfied += one_if(contract->acvp_intake_bound);
    satisfied += one_if(contract->acvp_capability_matrix_bound);
    satisfied += one_if(contract->acvp_fixture_row_plan_bound);
    satisfied += one_if(contract->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(contract->vector_schema_bound);
    satisfied += one_if(contract->vector_source_intake_bound);
    satisfied += one_if(contract->vector_fixture_digest_ledger_bound);
    satisfied += one_if(contract->negative_test_evidence_bound);
    satisfied += one_if(contract->implementation_binding_manifest_bound);
    satisfied += one_if(contract->clean_room_source_boundary_recorded);
    satisfied += one_if(contract->vector_set_fields_policy_recorded);
    satisfied += one_if(contract->test_group_fields_policy_recorded);
    satisfied += one_if(contract->test_case_fields_policy_recorded);
    satisfied += one_if(contract->response_fields_policy_recorded);
    satisfied += one_if(contract->parameter_set_allowlist_required);
    satisfied += one_if(contract->mode_allowlist_required);
    satisfied += one_if(contract->test_type_allowlist_required);
    satisfied += one_if(contract->function_allowlist_required);
    satisfied += one_if(contract->hex_string_decoder_policy_recorded);
    satisfied += one_if(contract->integer_range_policy_recorded);
    satisfied += one_if(contract->max_input_size_policy_recorded);
    satisfied += one_if(contract->max_nesting_depth_policy_recorded);
    satisfied += one_if(contract->duplicate_key_rejection_required);
    satisfied += one_if(contract->unknown_field_rejection_policy_recorded);
    satisfied += one_if(contract->malformed_json_rejection_required);
    satisfied += one_if(contract->canonical_output_mapping_required);
    satisfied += one_if(contract->no_dynamic_code_loading_required);
    satisfied += one_if(contract->no_network_fetch_required);
    satisfied += one_if(contract->parser_implementation_present);
    satisfied += one_if(contract->parser_negative_tests_recorded);
    satisfied += one_if(contract->parser_fuzzing_recorded);
    satisfied += one_if(contract->parser_schema_reviewed);
    satisfied += one_if(contract->parser_security_reviewed);
    satisfied += one_if(contract->parser_ci_replay_recorded);
    satisfied += one_if(contract->fixture_digest_rows_recorded);
    satisfied += one_if(contract->fixture_import_reviewed);
    satisfied += one_if(contract->parser_output_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_parser_contract_error_label(
    latticra_q_seal_ml_kem_acvp_parser_contract_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_parser_contract_prepare(
    latticra_q_seal_ml_kem_acvp_parser_contract_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->parser_profile,
        sizeof(out->parser_profile),
        "latticra-q-seal-ml-kem-acvp-parser-contract/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Parser Contract");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->parser_scope,
        sizeof(out->parser_scope),
        "ML-KEM-ACVP-JSON-parser-contract-before-vector-import");
    copy_literal(
        out->parser_state,
        sizeof(out->parser_state),
        "parser-contract-recorded-parser-implementation-missing");

    out->acvp_parser_contract_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_intake_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_intake_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->vector_set_fields_policy_recorded = 1u;
    out->test_group_fields_policy_recorded = 1u;
    out->test_case_fields_policy_recorded = 1u;
    out->response_fields_policy_recorded = 1u;
    out->parameter_set_allowlist_required = 1u;
    out->mode_allowlist_required = 1u;
    out->test_type_allowlist_required = 1u;
    out->function_allowlist_required = 1u;
    out->hex_string_decoder_policy_recorded = 1u;
    out->integer_range_policy_recorded = 1u;
    out->max_input_size_policy_recorded = 1u;
    out->max_nesting_depth_policy_recorded = 1u;
    out->duplicate_key_rejection_required = 1u;
    out->unknown_field_rejection_policy_recorded = 1u;
    out->malformed_json_rejection_required = 1u;
    out->canonical_output_mapping_required = 1u;
    out->no_dynamic_code_loading_required = 1u;
    out->no_network_fetch_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->parser_implementation_present = 0u;
    out->parser_negative_tests_recorded = 0u;
    out->parser_fuzzing_recorded = 0u;
    out->parser_schema_reviewed = 0u;
    out->parser_security_reviewed = 0u;
    out->parser_ci_replay_recorded = 0u;
    out->fixture_digest_rows_recorded = 0u;
    out->fixture_import_reviewed = 0u;
    out->parser_output_accepted = 0u;
    out->vector_execution_allowed = 0u;
    out->response_json_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_parser_contract_items_total = 40u;
    out->required_parser_contract_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "parser-implementation-negative-tests-fuzzing-schema-review-security-review-ci-replay-fixture-rows-import-review-and-output-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-acvp-parser-contract-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_parser_contract_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_parser_contract_present == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->parser_implementation_present == 0u &&
           contract->parser_output_accepted == 0u &&
           contract->vector_execution_allowed == 0u &&
           contract->response_json_generation_enabled == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u &&
           contract->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_PARSER_CONTRACT_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_parser_contract_allows_vector_parser(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_parser_contract_present == 1u &&
           contract->fips_203_algorithm_bound == 1u &&
           contract->acvp_ml_kem_json_bound == 1u &&
           contract->acvp_intake_bound == 1u &&
           contract->acvp_capability_matrix_bound == 1u &&
           contract->acvp_fixture_row_plan_bound == 1u &&
           contract->acvp_fixture_digest_row_template_bound == 1u &&
           contract->vector_schema_bound == 1u &&
           contract->vector_source_intake_bound == 1u &&
           contract->vector_fixture_digest_ledger_bound == 1u &&
           contract->negative_test_evidence_bound == 1u &&
           contract->implementation_binding_manifest_bound == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->vector_set_fields_policy_recorded == 1u &&
           contract->test_group_fields_policy_recorded == 1u &&
           contract->test_case_fields_policy_recorded == 1u &&
           contract->response_fields_policy_recorded == 1u &&
           contract->parameter_set_allowlist_required == 1u &&
           contract->mode_allowlist_required == 1u &&
           contract->test_type_allowlist_required == 1u &&
           contract->function_allowlist_required == 1u &&
           contract->hex_string_decoder_policy_recorded == 1u &&
           contract->integer_range_policy_recorded == 1u &&
           contract->max_input_size_policy_recorded == 1u &&
           contract->max_nesting_depth_policy_recorded == 1u &&
           contract->duplicate_key_rejection_required == 1u &&
           contract->unknown_field_rejection_policy_recorded == 1u &&
           contract->malformed_json_rejection_required == 1u &&
           contract->canonical_output_mapping_required == 1u &&
           contract->no_dynamic_code_loading_required == 1u &&
           contract->no_network_fetch_required == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->parser_implementation_present == 1u &&
           contract->parser_negative_tests_recorded == 1u &&
           contract->parser_fuzzing_recorded == 1u &&
           contract->parser_schema_reviewed == 1u &&
           contract->parser_security_reviewed == 1u &&
           contract->parser_ci_replay_recorded == 1u &&
           contract->fixture_digest_rows_recorded == 1u &&
           contract->fixture_import_reviewed == 1u &&
           contract->parser_output_accepted == 1u &&
           contract->vector_execution_allowed == 0u &&
           contract->response_json_generation_enabled == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_parser_contract_report(
    const latticra_q_seal_ml_kem_acvp_parser_contract_t *contract,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (contract == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP PARSER CONTRACT\n"
        "parser_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "parser_scope=%s\n"
        "parser_state=%s\n"
        "acvp_parser_contract_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_intake_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_intake_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "vector_set_fields_policy_recorded=%u\n"
        "test_group_fields_policy_recorded=%u\n"
        "test_case_fields_policy_recorded=%u\n"
        "response_fields_policy_recorded=%u\n"
        "parameter_set_allowlist_required=%u\n"
        "mode_allowlist_required=%u\n"
        "test_type_allowlist_required=%u\n"
        "function_allowlist_required=%u\n"
        "hex_string_decoder_policy_recorded=%u\n"
        "integer_range_policy_recorded=%u\n"
        "max_input_size_policy_recorded=%u\n"
        "max_nesting_depth_policy_recorded=%u\n"
        "duplicate_key_rejection_required=%u\n"
        "unknown_field_rejection_policy_recorded=%u\n"
        "malformed_json_rejection_required=%u\n"
        "canonical_output_mapping_required=%u\n"
        "no_dynamic_code_loading_required=%u\n"
        "no_network_fetch_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "parser_implementation_present=%u\n"
        "parser_negative_tests_recorded=%u\n"
        "parser_fuzzing_recorded=%u\n"
        "parser_schema_reviewed=%u\n"
        "parser_security_reviewed=%u\n"
        "parser_ci_replay_recorded=%u\n"
        "fixture_digest_rows_recorded=%u\n"
        "fixture_import_reviewed=%u\n"
        "parser_output_accepted=%u\n"
        "vector_execution_allowed=%u\n"
        "response_json_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_parser_contract_items_total=%u\n"
        "required_parser_contract_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        contract->parser_profile,
        contract->formal_title,
        contract->standards_basis,
        contract->parser_scope,
        contract->parser_state,
        contract->acvp_parser_contract_present,
        contract->fips_203_algorithm_bound,
        contract->acvp_ml_kem_json_bound,
        contract->acvp_intake_bound,
        contract->acvp_capability_matrix_bound,
        contract->acvp_fixture_row_plan_bound,
        contract->acvp_fixture_digest_row_template_bound,
        contract->vector_schema_bound,
        contract->vector_source_intake_bound,
        contract->vector_fixture_digest_ledger_bound,
        contract->negative_test_evidence_bound,
        contract->implementation_binding_manifest_bound,
        contract->clean_room_source_boundary_recorded,
        contract->vector_set_fields_policy_recorded,
        contract->test_group_fields_policy_recorded,
        contract->test_case_fields_policy_recorded,
        contract->response_fields_policy_recorded,
        contract->parameter_set_allowlist_required,
        contract->mode_allowlist_required,
        contract->test_type_allowlist_required,
        contract->function_allowlist_required,
        contract->hex_string_decoder_policy_recorded,
        contract->integer_range_policy_recorded,
        contract->max_input_size_policy_recorded,
        contract->max_nesting_depth_policy_recorded,
        contract->duplicate_key_rejection_required,
        contract->unknown_field_rejection_policy_recorded,
        contract->malformed_json_rejection_required,
        contract->canonical_output_mapping_required,
        contract->no_dynamic_code_loading_required,
        contract->no_network_fetch_required,
        contract->apple_corecrypto_code_copied,
        contract->external_provider_code_copied,
        contract->parser_implementation_present,
        contract->parser_negative_tests_recorded,
        contract->parser_fuzzing_recorded,
        contract->parser_schema_reviewed,
        contract->parser_security_reviewed,
        contract->parser_ci_replay_recorded,
        contract->fixture_digest_rows_recorded,
        contract->fixture_import_reviewed,
        contract->parser_output_accepted,
        contract->vector_execution_allowed,
        contract->response_json_generation_enabled,
        contract->acvp_submission_allowed,
        contract->operation_execution_allowed,
        contract->production_crypto_claim_allowed,
        contract->fips_claim_allowed,
        contract->runtime_authority_granted,
        contract->required_parser_contract_items_total,
        contract->required_parser_contract_items_satisfied,
        contract->blocked_reason,
        latticra_q_seal_ml_kem_acvp_parser_contract_error_label(contract->error),
        contract->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
