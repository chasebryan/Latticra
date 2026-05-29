#include "latticra/q_seal_ml_kem_kat_result_row_fixture.h"

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
    const latticra_q_seal_ml_kem_kat_result_row_fixture_t *fixture) {
    unsigned satisfied = 0u;

    satisfied += one_if(fixture->kat_result_row_fixture_present);
    satisfied += one_if(fixture->fips_203_algorithm_bound);
    satisfied += one_if(fixture->acvp_ml_kem_json_bound);
    satisfied += one_if(fixture->kat_manifest_bound);
    satisfied += one_if(fixture->kat_runner_contract_bound);
    satisfied += one_if(fixture->kat_result_schema_bound);
    satisfied += one_if(fixture->acvp_parser_contract_bound);
    satisfied += one_if(fixture->acvp_response_contract_bound);
    satisfied += one_if(fixture->vector_schema_bound);
    satisfied += one_if(fixture->vector_fixture_lock_bound);
    satisfied += one_if(fixture->vector_fixture_digest_ledger_bound);
    satisfied += one_if(fixture->negative_test_evidence_bound);
    satisfied += one_if(fixture->provider_differential_bound);
    satisfied += one_if(fixture->implementation_binding_manifest_bound);
    satisfied += one_if(fixture->clean_room_source_boundary_recorded);
    satisfied += one_if(fixture->result_row_fixture_policy_recorded);
    satisfied += one_if(fixture->row_id_policy_recorded);
    satisfied += one_if(fixture->fixture_digest_reference_required);
    satisfied += one_if(fixture->vector_family_reference_required);
    satisfied += one_if(fixture->parameter_set_field_required);
    satisfied += one_if(fixture->operation_family_field_required);
    satisfied += one_if(fixture->test_type_field_required);
    satisfied += one_if(fixture->tgid_tcid_mapping_required);
    satisfied += one_if(fixture->expected_result_field_required);
    satisfied += one_if(fixture->observed_result_field_required);
    satisfied += one_if(fixture->pass_fail_field_required);
    satisfied += one_if(fixture->failure_reason_field_required);
    satisfied += one_if(fixture->implicit_rejection_row_policy_recorded);
    satisfied += one_if(fixture->provider_differential_row_policy_recorded);
    satisfied += one_if(fixture->transcript_digest_reference_required);
    satisfied += one_if(fixture->no_secret_material_logging_required);
    satisfied += one_if(fixture->deterministic_ordering_required);
    satisfied += one_if(fixture->no_network_submission_required);
    satisfied += one_if(fixture->no_dynamic_provider_loading_required);
    satisfied += one_if(fixture->row_fixture_reviewed);
    satisfied += one_if(fixture->fixture_bundle_digest_bound);
    satisfied += one_if(fixture->positive_result_row_fixture_recorded);
    satisfied += one_if(fixture->negative_result_row_fixture_recorded);
    satisfied += one_if(fixture->malformed_result_row_fixture_recorded);
    satisfied += one_if(fixture->implicit_rejection_row_fixture_recorded);
    satisfied += one_if(fixture->provider_differential_row_fixture_recorded);
    satisfied += one_if(fixture->ci_kat_replay_transcript_bound);
    satisfied += one_if(fixture->kat_runner_execution_recorded);
    satisfied += one_if(fixture->acvp_response_generation_evidence_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_kat_result_row_fixture_error_label(
    latticra_q_seal_ml_kem_kat_result_row_fixture_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_row_fixture_prepare(
    latticra_q_seal_ml_kem_kat_result_row_fixture_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->row_fixture_profile,
        sizeof(out->row_fixture_profile),
        "latticra-q-seal-ml-kem-kat-result-row-fixture/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM KAT Result Row Fixture");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->row_fixture_scope,
        sizeof(out->row_fixture_scope),
        "ML-KEM-known-answer-result-row-fixture-before-result-recording");
    copy_literal(
        out->row_fixture_state,
        sizeof(out->row_fixture_state),
        "kat-result-row-fixture-recorded-result-rows-missing");

    out->kat_result_row_fixture_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->kat_runner_contract_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->provider_differential_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->result_row_fixture_policy_recorded = 1u;
    out->row_id_policy_recorded = 1u;
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
    out->implicit_rejection_row_policy_recorded = 1u;
    out->provider_differential_row_policy_recorded = 1u;
    out->transcript_digest_reference_required = 1u;
    out->no_secret_material_logging_required = 1u;
    out->deterministic_ordering_required = 1u;
    out->no_network_submission_required = 1u;
    out->no_dynamic_provider_loading_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->row_fixture_reviewed = 0u;
    out->fixture_bundle_digest_bound = 0u;
    out->positive_result_row_fixture_recorded = 0u;
    out->negative_result_row_fixture_recorded = 0u;
    out->malformed_result_row_fixture_recorded = 0u;
    out->implicit_rejection_row_fixture_recorded = 0u;
    out->provider_differential_row_fixture_recorded = 0u;
    out->ci_kat_replay_transcript_bound = 0u;
    out->kat_runner_execution_recorded = 0u;
    out->acvp_response_generation_evidence_recorded = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_kat_result_row_fixture_items_total = 44u;
    out->required_kat_result_row_fixture_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "row-fixture-review-fixture-digest-positive-negative-malformed-implicit-provider-differential-ci-replay-runner-execution-and-response-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-kat-result-row-fixture-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_kat_result_row_fixture_is_no_effect(
    const latticra_q_seal_ml_kem_kat_result_row_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->kat_result_row_fixture_present == 1u &&
           fixture->clean_room_source_boundary_recorded == 1u &&
           fixture->apple_corecrypto_code_copied == 0u &&
           fixture->external_provider_code_copied == 0u &&
           fixture->row_fixture_reviewed == 0u &&
           fixture->positive_result_row_fixture_recorded == 0u &&
           fixture->negative_result_row_fixture_recorded == 0u &&
           fixture->malformed_result_row_fixture_recorded == 0u &&
           fixture->implicit_rejection_row_fixture_recorded == 0u &&
           fixture->provider_differential_row_fixture_recorded == 0u &&
           fixture->kat_runner_execution_recorded == 0u &&
           fixture->acvp_response_generation_evidence_recorded == 0u &&
           fixture->acvp_submission_allowed == 0u &&
           fixture->operation_execution_allowed == 0u &&
           fixture->production_crypto_claim_allowed == 0u &&
           fixture->fips_claim_allowed == 0u &&
           fixture->runtime_authority_granted == 0u &&
           fixture->error == LATTICRA_Q_SEAL_ML_KEM_KAT_RESULT_ROW_FIXTURE_BLOCKED;
}

int latticra_q_seal_ml_kem_kat_result_row_fixture_allows_result_rows(
    const latticra_q_seal_ml_kem_kat_result_row_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->kat_result_row_fixture_present == 1u &&
           fixture->fips_203_algorithm_bound == 1u &&
           fixture->acvp_ml_kem_json_bound == 1u &&
           fixture->kat_manifest_bound == 1u &&
           fixture->kat_runner_contract_bound == 1u &&
           fixture->kat_result_schema_bound == 1u &&
           fixture->acvp_parser_contract_bound == 1u &&
           fixture->acvp_response_contract_bound == 1u &&
           fixture->vector_schema_bound == 1u &&
           fixture->vector_fixture_lock_bound == 1u &&
           fixture->vector_fixture_digest_ledger_bound == 1u &&
           fixture->negative_test_evidence_bound == 1u &&
           fixture->provider_differential_bound == 1u &&
           fixture->implementation_binding_manifest_bound == 1u &&
           fixture->clean_room_source_boundary_recorded == 1u &&
           fixture->result_row_fixture_policy_recorded == 1u &&
           fixture->row_id_policy_recorded == 1u &&
           fixture->fixture_digest_reference_required == 1u &&
           fixture->vector_family_reference_required == 1u &&
           fixture->parameter_set_field_required == 1u &&
           fixture->operation_family_field_required == 1u &&
           fixture->test_type_field_required == 1u &&
           fixture->tgid_tcid_mapping_required == 1u &&
           fixture->expected_result_field_required == 1u &&
           fixture->observed_result_field_required == 1u &&
           fixture->pass_fail_field_required == 1u &&
           fixture->failure_reason_field_required == 1u &&
           fixture->implicit_rejection_row_policy_recorded == 1u &&
           fixture->provider_differential_row_policy_recorded == 1u &&
           fixture->transcript_digest_reference_required == 1u &&
           fixture->no_secret_material_logging_required == 1u &&
           fixture->deterministic_ordering_required == 1u &&
           fixture->no_network_submission_required == 1u &&
           fixture->no_dynamic_provider_loading_required == 1u &&
           fixture->apple_corecrypto_code_copied == 0u &&
           fixture->external_provider_code_copied == 0u &&
           fixture->row_fixture_reviewed == 1u &&
           fixture->fixture_bundle_digest_bound == 1u &&
           fixture->positive_result_row_fixture_recorded == 1u &&
           fixture->negative_result_row_fixture_recorded == 1u &&
           fixture->malformed_result_row_fixture_recorded == 1u &&
           fixture->implicit_rejection_row_fixture_recorded == 1u &&
           fixture->provider_differential_row_fixture_recorded == 1u &&
           fixture->ci_kat_replay_transcript_bound == 1u &&
           fixture->kat_runner_execution_recorded == 1u &&
           fixture->acvp_response_generation_evidence_recorded == 1u &&
           fixture->operation_execution_allowed == 1u &&
           fixture->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_result_row_fixture_report(
    const latticra_q_seal_ml_kem_kat_result_row_fixture_t *fixture,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (fixture == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM KAT RESULT ROW FIXTURE\n"
        "row_fixture_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "row_fixture_scope=%s\n"
        "row_fixture_state=%s\n"
        "kat_result_row_fixture_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "kat_runner_contract_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "provider_differential_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "result_row_fixture_policy_recorded=%u\n"
        "row_id_policy_recorded=%u\n"
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
        "implicit_rejection_row_policy_recorded=%u\n"
        "provider_differential_row_policy_recorded=%u\n"
        "transcript_digest_reference_required=%u\n"
        "no_secret_material_logging_required=%u\n"
        "deterministic_ordering_required=%u\n"
        "no_network_submission_required=%u\n"
        "no_dynamic_provider_loading_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "row_fixture_reviewed=%u\n"
        "fixture_bundle_digest_bound=%u\n"
        "positive_result_row_fixture_recorded=%u\n"
        "negative_result_row_fixture_recorded=%u\n"
        "malformed_result_row_fixture_recorded=%u\n"
        "implicit_rejection_row_fixture_recorded=%u\n"
        "provider_differential_row_fixture_recorded=%u\n"
        "ci_kat_replay_transcript_bound=%u\n"
        "kat_runner_execution_recorded=%u\n"
        "acvp_response_generation_evidence_recorded=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_kat_result_row_fixture_items_total=%u\n"
        "required_kat_result_row_fixture_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        fixture->row_fixture_profile,
        fixture->formal_title,
        fixture->standards_basis,
        fixture->row_fixture_scope,
        fixture->row_fixture_state,
        fixture->kat_result_row_fixture_present,
        fixture->fips_203_algorithm_bound,
        fixture->acvp_ml_kem_json_bound,
        fixture->kat_manifest_bound,
        fixture->kat_runner_contract_bound,
        fixture->kat_result_schema_bound,
        fixture->acvp_parser_contract_bound,
        fixture->acvp_response_contract_bound,
        fixture->vector_schema_bound,
        fixture->vector_fixture_lock_bound,
        fixture->vector_fixture_digest_ledger_bound,
        fixture->negative_test_evidence_bound,
        fixture->provider_differential_bound,
        fixture->implementation_binding_manifest_bound,
        fixture->clean_room_source_boundary_recorded,
        fixture->result_row_fixture_policy_recorded,
        fixture->row_id_policy_recorded,
        fixture->fixture_digest_reference_required,
        fixture->vector_family_reference_required,
        fixture->parameter_set_field_required,
        fixture->operation_family_field_required,
        fixture->test_type_field_required,
        fixture->tgid_tcid_mapping_required,
        fixture->expected_result_field_required,
        fixture->observed_result_field_required,
        fixture->pass_fail_field_required,
        fixture->failure_reason_field_required,
        fixture->implicit_rejection_row_policy_recorded,
        fixture->provider_differential_row_policy_recorded,
        fixture->transcript_digest_reference_required,
        fixture->no_secret_material_logging_required,
        fixture->deterministic_ordering_required,
        fixture->no_network_submission_required,
        fixture->no_dynamic_provider_loading_required,
        fixture->apple_corecrypto_code_copied,
        fixture->external_provider_code_copied,
        fixture->row_fixture_reviewed,
        fixture->fixture_bundle_digest_bound,
        fixture->positive_result_row_fixture_recorded,
        fixture->negative_result_row_fixture_recorded,
        fixture->malformed_result_row_fixture_recorded,
        fixture->implicit_rejection_row_fixture_recorded,
        fixture->provider_differential_row_fixture_recorded,
        fixture->ci_kat_replay_transcript_bound,
        fixture->kat_runner_execution_recorded,
        fixture->acvp_response_generation_evidence_recorded,
        fixture->acvp_submission_allowed,
        fixture->operation_execution_allowed,
        fixture->production_crypto_claim_allowed,
        fixture->fips_claim_allowed,
        fixture->runtime_authority_granted,
        fixture->required_kat_result_row_fixture_items_total,
        fixture->required_kat_result_row_fixture_items_satisfied,
        fixture->blocked_reason,
        latticra_q_seal_ml_kem_kat_result_row_fixture_error_label(fixture->error),
        fixture->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
