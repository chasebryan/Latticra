#include "latticra/q_seal_ml_kem_kat_result_schema.h"

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
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema) {
    unsigned satisfied = 0u;

    satisfied += one_if(schema->kat_result_schema_present);
    satisfied += one_if(schema->fips_203_algorithm_bound);
    satisfied += one_if(schema->acvp_ml_kem_json_bound);
    satisfied += one_if(schema->kat_manifest_bound);
    satisfied += one_if(schema->kat_runner_contract_bound);
    satisfied += one_if(schema->kat_result_row_fixture_bound);
    satisfied += one_if(schema->acvp_parser_contract_bound);
    satisfied += one_if(schema->acvp_response_contract_bound);
    satisfied += one_if(schema->vector_schema_bound);
    satisfied += one_if(schema->vector_fixture_lock_bound);
    satisfied += one_if(schema->vector_fixture_digest_ledger_bound);
    satisfied += one_if(schema->negative_test_evidence_bound);
    satisfied += one_if(schema->provider_differential_bound);
    satisfied += one_if(schema->implementation_binding_manifest_bound);
    satisfied += one_if(schema->clean_room_source_boundary_recorded);
    satisfied += one_if(schema->deterministic_result_ordering_required);
    satisfied += one_if(schema->result_envelope_policy_recorded);
    satisfied += one_if(schema->fixture_digest_reference_required);
    satisfied += one_if(schema->vector_family_reference_required);
    satisfied += one_if(schema->parameter_set_field_required);
    satisfied += one_if(schema->operation_family_field_required);
    satisfied += one_if(schema->test_type_field_required);
    satisfied += one_if(schema->tgid_tcid_mapping_required);
    satisfied += one_if(schema->expected_result_field_required);
    satisfied += one_if(schema->observed_result_field_required);
    satisfied += one_if(schema->pass_fail_field_required);
    satisfied += one_if(schema->failure_reason_field_required);
    satisfied += one_if(schema->implicit_rejection_result_required);
    satisfied += one_if(schema->provider_differential_field_required);
    satisfied += one_if(schema->transcript_digest_field_required);
    satisfied += one_if(schema->no_secret_material_logging_required);
    satisfied += one_if(schema->no_network_submission_required);
    satisfied += one_if(schema->no_dynamic_provider_loading_required);
    satisfied += one_if(schema->result_schema_reviewed);
    satisfied += one_if(schema->fixture_bundle_digest_bound);
    satisfied += one_if(schema->result_row_fixture_recorded);
    satisfied += one_if(schema->positive_result_rows_recorded);
    satisfied += one_if(schema->negative_result_rows_recorded);
    satisfied += one_if(schema->malformed_result_rows_recorded);
    satisfied += one_if(schema->implicit_rejection_rows_recorded);
    satisfied += one_if(schema->provider_differential_rows_recorded);
    satisfied += one_if(schema->ci_kat_replay_transcript_bound);
    satisfied += one_if(schema->kat_runner_execution_recorded);
    satisfied += one_if(schema->acvp_response_generation_evidence_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_kat_result_schema_error_label(
    latticra_q_seal_ml_kem_kat_result_schema_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_schema_prepare(
    latticra_q_seal_ml_kem_kat_result_schema_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->result_schema_profile,
        sizeof(out->result_schema_profile),
        "latticra-q-seal-ml-kem-kat-result-schema/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM KAT Result Schema");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->result_scope,
        sizeof(out->result_scope),
        "ML-KEM-known-answer-result-schema-before-result-recording");
    copy_literal(
        out->schema_state,
        sizeof(out->schema_state),
        "kat-result-schema-recorded-result-rows-missing");

    out->kat_result_schema_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->kat_runner_contract_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->provider_differential_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->deterministic_result_ordering_required = 1u;
    out->result_envelope_policy_recorded = 1u;
    out->fixture_digest_reference_required = 1u;
    out->vector_family_reference_required = 1u;
    out->parameter_set_field_required = 1u;
    out->operation_family_field_required = 1u;
    out->test_type_field_required = 1u;
    out->tgid_tcid_mapping_required = 1u;
    out->expected_result_field_required = 1u;
    out->observed_result_field_required = 1u;
    out->pass_fail_field_required = 1u;
    out->failure_reason_field_required = 1u;
    out->implicit_rejection_result_required = 1u;
    out->provider_differential_field_required = 1u;
    out->transcript_digest_field_required = 1u;
    out->no_secret_material_logging_required = 1u;
    out->no_network_submission_required = 1u;
    out->no_dynamic_provider_loading_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->result_schema_reviewed = 0u;
    out->fixture_bundle_digest_bound = 0u;
    out->result_row_fixture_recorded = 0u;
    out->positive_result_rows_recorded = 0u;
    out->negative_result_rows_recorded = 0u;
    out->malformed_result_rows_recorded = 0u;
    out->implicit_rejection_rows_recorded = 0u;
    out->provider_differential_rows_recorded = 0u;
    out->ci_kat_replay_transcript_bound = 0u;
    out->kat_runner_execution_recorded = 0u;
    out->acvp_response_generation_evidence_recorded = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_kat_result_schema_items_total = 44u;
    out->required_kat_result_schema_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "schema-review-fixture-digest-result-row-fixture-positive-negative-malformed-implicit-provider-differential-ci-replay-runner-execution-and-response-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-kat-result-schema-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_kat_result_schema_is_no_effect(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema) {
    if (schema == NULL) {
        return 0;
    }

    return schema->kat_result_schema_present == 1u &&
           schema->clean_room_source_boundary_recorded == 1u &&
           schema->apple_corecrypto_code_copied == 0u &&
           schema->external_provider_code_copied == 0u &&
           schema->result_schema_reviewed == 0u &&
           schema->result_row_fixture_recorded == 0u &&
           schema->kat_runner_execution_recorded == 0u &&
           schema->acvp_response_generation_evidence_recorded == 0u &&
           schema->acvp_submission_allowed == 0u &&
           schema->operation_execution_allowed == 0u &&
           schema->production_crypto_claim_allowed == 0u &&
           schema->fips_claim_allowed == 0u &&
           schema->runtime_authority_granted == 0u &&
           schema->error == LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_SCHEMA_BLOCKED;
}

int latticra_q_seal_ml_kem_kat_result_schema_allows_result_recording(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema) {
    if (schema == NULL) {
        return 0;
    }

    return schema->kat_result_schema_present == 1u &&
           schema->fips_203_algorithm_bound == 1u &&
           schema->acvp_ml_kem_json_bound == 1u &&
           schema->kat_manifest_bound == 1u &&
           schema->kat_runner_contract_bound == 1u &&
           schema->kat_result_row_fixture_bound == 1u &&
           schema->acvp_parser_contract_bound == 1u &&
           schema->acvp_response_contract_bound == 1u &&
           schema->vector_schema_bound == 1u &&
           schema->vector_fixture_lock_bound == 1u &&
           schema->vector_fixture_digest_ledger_bound == 1u &&
           schema->negative_test_evidence_bound == 1u &&
           schema->provider_differential_bound == 1u &&
           schema->implementation_binding_manifest_bound == 1u &&
           schema->clean_room_source_boundary_recorded == 1u &&
           schema->deterministic_result_ordering_required == 1u &&
           schema->result_envelope_policy_recorded == 1u &&
           schema->fixture_digest_reference_required == 1u &&
           schema->vector_family_reference_required == 1u &&
           schema->parameter_set_field_required == 1u &&
           schema->operation_family_field_required == 1u &&
           schema->test_type_field_required == 1u &&
           schema->tgid_tcid_mapping_required == 1u &&
           schema->expected_result_field_required == 1u &&
           schema->observed_result_field_required == 1u &&
           schema->pass_fail_field_required == 1u &&
           schema->failure_reason_field_required == 1u &&
           schema->implicit_rejection_result_required == 1u &&
           schema->provider_differential_field_required == 1u &&
           schema->transcript_digest_field_required == 1u &&
           schema->no_secret_material_logging_required == 1u &&
           schema->no_network_submission_required == 1u &&
           schema->no_dynamic_provider_loading_required == 1u &&
           schema->apple_corecrypto_code_copied == 0u &&
           schema->external_provider_code_copied == 0u &&
           schema->result_schema_reviewed == 1u &&
           schema->fixture_bundle_digest_bound == 1u &&
           schema->result_row_fixture_recorded == 1u &&
           schema->positive_result_rows_recorded == 1u &&
           schema->negative_result_rows_recorded == 1u &&
           schema->malformed_result_rows_recorded == 1u &&
           schema->implicit_rejection_rows_recorded == 1u &&
           schema->provider_differential_rows_recorded == 1u &&
           schema->ci_kat_replay_transcript_bound == 1u &&
           schema->kat_runner_execution_recorded == 1u &&
           schema->acvp_response_generation_evidence_recorded == 1u &&
           schema->operation_execution_allowed == 1u &&
           schema->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_schema_report(
    const latticra_q_seal_ml_kem_kat_result_schema_t *schema,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (schema == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM KAT RESULT SCHEMA\n"
        "result_schema_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "result_scope=%s\n"
        "schema_state=%s\n"
        "kat_result_schema_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "kat_runner_contract_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "provider_differential_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "deterministic_result_ordering_required=%u\n"
        "result_envelope_policy_recorded=%u\n"
        "fixture_digest_reference_required=%u\n"
        "vector_family_reference_required=%u\n"
        "parameter_set_field_required=%u\n"
        "operation_family_field_required=%u\n"
        "test_type_field_required=%u\n"
        "tgid_tcid_mapping_required=%u\n"
        "expected_result_field_required=%u\n"
        "observed_result_field_required=%u\n"
        "pass_fail_field_required=%u\n"
        "failure_reason_field_required=%u\n"
        "implicit_rejection_result_required=%u\n"
        "provider_differential_field_required=%u\n"
        "transcript_digest_field_required=%u\n"
        "no_secret_material_logging_required=%u\n"
        "no_network_submission_required=%u\n"
        "no_dynamic_provider_loading_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "result_schema_reviewed=%u\n"
        "fixture_bundle_digest_bound=%u\n"
        "result_row_fixture_recorded=%u\n"
        "positive_result_rows_recorded=%u\n"
        "negative_result_rows_recorded=%u\n"
        "malformed_result_rows_recorded=%u\n"
        "implicit_rejection_rows_recorded=%u\n"
        "provider_differential_rows_recorded=%u\n"
        "ci_kat_replay_transcript_bound=%u\n"
        "kat_runner_execution_recorded=%u\n"
        "acvp_response_generation_evidence_recorded=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_kat_result_schema_items_total=%u\n"
        "required_kat_result_schema_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        schema->result_schema_profile,
        schema->formal_title,
        schema->standards_basis,
        schema->result_scope,
        schema->schema_state,
        schema->kat_result_schema_present,
        schema->fips_203_algorithm_bound,
        schema->acvp_ml_kem_json_bound,
        schema->kat_manifest_bound,
        schema->kat_runner_contract_bound,
        schema->kat_result_row_fixture_bound,
        schema->acvp_parser_contract_bound,
        schema->acvp_response_contract_bound,
        schema->vector_schema_bound,
        schema->vector_fixture_lock_bound,
        schema->vector_fixture_digest_ledger_bound,
        schema->negative_test_evidence_bound,
        schema->provider_differential_bound,
        schema->implementation_binding_manifest_bound,
        schema->clean_room_source_boundary_recorded,
        schema->deterministic_result_ordering_required,
        schema->result_envelope_policy_recorded,
        schema->fixture_digest_reference_required,
        schema->vector_family_reference_required,
        schema->parameter_set_field_required,
        schema->operation_family_field_required,
        schema->test_type_field_required,
        schema->tgid_tcid_mapping_required,
        schema->expected_result_field_required,
        schema->observed_result_field_required,
        schema->pass_fail_field_required,
        schema->failure_reason_field_required,
        schema->implicit_rejection_result_required,
        schema->provider_differential_field_required,
        schema->transcript_digest_field_required,
        schema->no_secret_material_logging_required,
        schema->no_network_submission_required,
        schema->no_dynamic_provider_loading_required,
        schema->apple_corecrypto_code_copied,
        schema->external_provider_code_copied,
        schema->result_schema_reviewed,
        schema->fixture_bundle_digest_bound,
        schema->result_row_fixture_recorded,
        schema->positive_result_rows_recorded,
        schema->negative_result_rows_recorded,
        schema->malformed_result_rows_recorded,
        schema->implicit_rejection_rows_recorded,
        schema->provider_differential_rows_recorded,
        schema->ci_kat_replay_transcript_bound,
        schema->kat_runner_execution_recorded,
        schema->acvp_response_generation_evidence_recorded,
        schema->acvp_submission_allowed,
        schema->operation_execution_allowed,
        schema->production_crypto_claim_allowed,
        schema->fips_claim_allowed,
        schema->runtime_authority_granted,
        schema->required_kat_result_schema_items_total,
        schema->required_kat_result_schema_items_satisfied,
        schema->blocked_reason,
        latticra_q_seal_ml_kem_kat_result_schema_error_label(schema->error),
        schema->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
