#include "latticra/q_seal_ml_kem_kat_runner_contract.h"

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
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract) {
    unsigned satisfied = 0u;

    satisfied += one_if(contract->kat_runner_contract_present);
    satisfied += one_if(contract->fips_203_algorithm_bound);
    satisfied += one_if(contract->acvp_ml_kem_json_bound);
    satisfied += one_if(contract->kat_manifest_bound);
    satisfied += one_if(contract->acvp_parser_contract_bound);
    satisfied += one_if(contract->acvp_response_contract_bound);
    satisfied += one_if(contract->kat_result_schema_bound);
    satisfied += one_if(contract->kat_result_row_fixture_bound);
    satisfied += one_if(contract->vector_schema_bound);
    satisfied += one_if(contract->vector_source_bound);
    satisfied += one_if(contract->vector_fixture_lock_bound);
    satisfied += one_if(contract->vector_fixture_digest_ledger_bound);
    satisfied += one_if(contract->negative_test_evidence_bound);
    satisfied += one_if(contract->provider_differential_bound);
    satisfied += one_if(contract->replay_transcript_gate_bound);
    satisfied += one_if(contract->implementation_binding_manifest_bound);
    satisfied += one_if(contract->clean_room_source_boundary_recorded);
    satisfied += one_if(contract->deterministic_replay_policy_recorded);
    satisfied += one_if(contract->offline_fixture_policy_recorded);
    satisfied += one_if(contract->no_network_execution_required);
    satisfied += one_if(contract->no_dynamic_provider_loading_required);
    satisfied += one_if(contract->seed_material_handling_policy_recorded);
    satisfied += one_if(contract->positive_result_row_policy_recorded);
    satisfied += one_if(contract->negative_result_row_policy_recorded);
    satisfied += one_if(contract->malformed_result_row_policy_recorded);
    satisfied += one_if(contract->implicit_rejection_result_policy_recorded);
    satisfied += one_if(contract->parameter_set_coverage_required);
    satisfied += one_if(contract->operation_family_coverage_required);
    satisfied += one_if(contract->transcript_retention_policy_recorded);
    satisfied += one_if(contract->failure_triage_policy_recorded);
    satisfied += one_if(contract->no_embedded_vectors_policy_recorded);
    satisfied += one_if(contract->kat_runner_implementation_present);
    satisfied += one_if(contract->fixture_bundle_loaded);
    satisfied += one_if(contract->fixture_bundle_digest_verified);
    satisfied += one_if(contract->fixture_bundle_license_reviewed);
    satisfied += one_if(contract->fixture_bundle_storage_reviewed);
    satisfied += one_if(contract->parser_reviewed_for_runner);
    satisfied += one_if(contract->result_schema_reviewed);
    satisfied += one_if(contract->positive_result_rows_recorded);
    satisfied += one_if(contract->negative_result_rows_recorded);
    satisfied += one_if(contract->malformed_result_rows_recorded);
    satisfied += one_if(contract->implicit_rejection_rows_recorded);
    satisfied += one_if(contract->provider_differential_rows_recorded);
    satisfied += one_if(contract->ci_kat_replay_transcript_recorded);
    satisfied += one_if(contract->operation_implementation_present);
    satisfied += one_if(contract->kat_execution_enabled);
    satisfied += one_if(contract->acvp_response_generation_enabled);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_kat_runner_contract_error_label(
    latticra_q_seal_ml_kem_kat_runner_contract_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_runner_contract_prepare(
    latticra_q_seal_ml_kem_kat_runner_contract_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->runner_profile,
        sizeof(out->runner_profile),
        "latticra-q-seal-ml-kem-kat-runner-contract/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM KAT Runner Contract");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->runner_scope,
        sizeof(out->runner_scope),
        "ML-KEM-known-answer-runner-contract-before-vector-replay");
    copy_literal(
        out->runner_state,
        sizeof(out->runner_state),
        "kat-runner-contract-recorded-runner-implementation-missing");

    out->kat_runner_contract_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_source_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->provider_differential_bound = 1u;
    out->replay_transcript_gate_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->deterministic_replay_policy_recorded = 1u;
    out->offline_fixture_policy_recorded = 1u;
    out->no_network_execution_required = 1u;
    out->no_dynamic_provider_loading_required = 1u;
    out->seed_material_handling_policy_recorded = 1u;
    out->positive_result_row_policy_recorded = 1u;
    out->negative_result_row_policy_recorded = 1u;
    out->malformed_result_row_policy_recorded = 1u;
    out->implicit_rejection_result_policy_recorded = 1u;
    out->parameter_set_coverage_required = 1u;
    out->operation_family_coverage_required = 1u;
    out->transcript_retention_policy_recorded = 1u;
    out->failure_triage_policy_recorded = 1u;
    out->no_embedded_vectors_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->kat_runner_implementation_present = 0u;
    out->fixture_bundle_loaded = 0u;
    out->fixture_bundle_digest_verified = 0u;
    out->fixture_bundle_license_reviewed = 0u;
    out->fixture_bundle_storage_reviewed = 0u;
    out->parser_reviewed_for_runner = 0u;
    out->result_schema_reviewed = 0u;
    out->positive_result_rows_recorded = 0u;
    out->negative_result_rows_recorded = 0u;
    out->malformed_result_rows_recorded = 0u;
    out->implicit_rejection_rows_recorded = 0u;
    out->provider_differential_rows_recorded = 0u;
    out->ci_kat_replay_transcript_recorded = 0u;
    out->operation_implementation_present = 0u;
    out->kat_execution_enabled = 0u;
    out->acvp_response_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_kat_runner_contract_items_total = 47u;
    out->required_kat_runner_contract_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "kat-runner-implementation-fixture-load-digest-license-storage-parser-review-result-schema-result-rows-provider-differential-ci-replay-operation-implementation-and-execution-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-kat-runner-contract-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_kat_runner_contract_is_no_effect(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->kat_runner_contract_present == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->kat_runner_implementation_present == 0u &&
           contract->fixture_bundle_loaded == 0u &&
           contract->operation_implementation_present == 0u &&
           contract->kat_execution_enabled == 0u &&
           contract->acvp_response_generation_enabled == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u &&
           contract->error == LATTICRA_Q_SEAL_ML_KEM_KAT_RUNNER_CONTRACT_BLOCKED;
}

int latticra_q_seal_ml_kem_kat_runner_contract_allows_runner_execution(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->kat_runner_contract_present == 1u &&
           contract->fips_203_algorithm_bound == 1u &&
           contract->acvp_ml_kem_json_bound == 1u &&
           contract->kat_manifest_bound == 1u &&
           contract->acvp_parser_contract_bound == 1u &&
           contract->acvp_response_contract_bound == 1u &&
           contract->kat_result_schema_bound == 1u &&
           contract->kat_result_row_fixture_bound == 1u &&
           contract->vector_schema_bound == 1u &&
           contract->vector_source_bound == 1u &&
           contract->vector_fixture_lock_bound == 1u &&
           contract->vector_fixture_digest_ledger_bound == 1u &&
           contract->negative_test_evidence_bound == 1u &&
           contract->provider_differential_bound == 1u &&
           contract->replay_transcript_gate_bound == 1u &&
           contract->implementation_binding_manifest_bound == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->deterministic_replay_policy_recorded == 1u &&
           contract->offline_fixture_policy_recorded == 1u &&
           contract->no_network_execution_required == 1u &&
           contract->no_dynamic_provider_loading_required == 1u &&
           contract->seed_material_handling_policy_recorded == 1u &&
           contract->positive_result_row_policy_recorded == 1u &&
           contract->negative_result_row_policy_recorded == 1u &&
           contract->malformed_result_row_policy_recorded == 1u &&
           contract->implicit_rejection_result_policy_recorded == 1u &&
           contract->parameter_set_coverage_required == 1u &&
           contract->operation_family_coverage_required == 1u &&
           contract->transcript_retention_policy_recorded == 1u &&
           contract->failure_triage_policy_recorded == 1u &&
           contract->no_embedded_vectors_policy_recorded == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->kat_runner_implementation_present == 1u &&
           contract->fixture_bundle_loaded == 1u &&
           contract->fixture_bundle_digest_verified == 1u &&
           contract->fixture_bundle_license_reviewed == 1u &&
           contract->fixture_bundle_storage_reviewed == 1u &&
           contract->parser_reviewed_for_runner == 1u &&
           contract->result_schema_reviewed == 1u &&
           contract->positive_result_rows_recorded == 1u &&
           contract->negative_result_rows_recorded == 1u &&
           contract->malformed_result_rows_recorded == 1u &&
           contract->implicit_rejection_rows_recorded == 1u &&
           contract->provider_differential_rows_recorded == 1u &&
           contract->ci_kat_replay_transcript_recorded == 1u &&
           contract->operation_implementation_present == 1u &&
           contract->kat_execution_enabled == 1u &&
           contract->acvp_response_generation_enabled == 1u &&
           contract->operation_execution_allowed == 1u &&
           contract->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_runner_contract_report(
    const latticra_q_seal_ml_kem_kat_runner_contract_t *contract,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (contract == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM KAT RUNNER CONTRACT\n"
        "runner_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "runner_scope=%s\n"
        "runner_state=%s\n"
        "kat_runner_contract_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_source_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "provider_differential_bound=%u\n"
        "replay_transcript_gate_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "deterministic_replay_policy_recorded=%u\n"
        "offline_fixture_policy_recorded=%u\n"
        "no_network_execution_required=%u\n"
        "no_dynamic_provider_loading_required=%u\n"
        "seed_material_handling_policy_recorded=%u\n"
        "positive_result_row_policy_recorded=%u\n"
        "negative_result_row_policy_recorded=%u\n"
        "malformed_result_row_policy_recorded=%u\n"
        "implicit_rejection_result_policy_recorded=%u\n"
        "parameter_set_coverage_required=%u\n"
        "operation_family_coverage_required=%u\n"
        "transcript_retention_policy_recorded=%u\n"
        "failure_triage_policy_recorded=%u\n"
        "no_embedded_vectors_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "kat_runner_implementation_present=%u\n"
        "fixture_bundle_loaded=%u\n"
        "fixture_bundle_digest_verified=%u\n"
        "fixture_bundle_license_reviewed=%u\n"
        "fixture_bundle_storage_reviewed=%u\n"
        "parser_reviewed_for_runner=%u\n"
        "result_schema_reviewed=%u\n"
        "positive_result_rows_recorded=%u\n"
        "negative_result_rows_recorded=%u\n"
        "malformed_result_rows_recorded=%u\n"
        "implicit_rejection_rows_recorded=%u\n"
        "provider_differential_rows_recorded=%u\n"
        "ci_kat_replay_transcript_recorded=%u\n"
        "operation_implementation_present=%u\n"
        "kat_execution_enabled=%u\n"
        "acvp_response_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_kat_runner_contract_items_total=%u\n"
        "required_kat_runner_contract_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        contract->runner_profile,
        contract->formal_title,
        contract->standards_basis,
        contract->runner_scope,
        contract->runner_state,
        contract->kat_runner_contract_present,
        contract->fips_203_algorithm_bound,
        contract->acvp_ml_kem_json_bound,
        contract->kat_manifest_bound,
        contract->acvp_parser_contract_bound,
        contract->acvp_response_contract_bound,
        contract->kat_result_schema_bound,
        contract->kat_result_row_fixture_bound,
        contract->vector_schema_bound,
        contract->vector_source_bound,
        contract->vector_fixture_lock_bound,
        contract->vector_fixture_digest_ledger_bound,
        contract->negative_test_evidence_bound,
        contract->provider_differential_bound,
        contract->replay_transcript_gate_bound,
        contract->implementation_binding_manifest_bound,
        contract->clean_room_source_boundary_recorded,
        contract->deterministic_replay_policy_recorded,
        contract->offline_fixture_policy_recorded,
        contract->no_network_execution_required,
        contract->no_dynamic_provider_loading_required,
        contract->seed_material_handling_policy_recorded,
        contract->positive_result_row_policy_recorded,
        contract->negative_result_row_policy_recorded,
        contract->malformed_result_row_policy_recorded,
        contract->implicit_rejection_result_policy_recorded,
        contract->parameter_set_coverage_required,
        contract->operation_family_coverage_required,
        contract->transcript_retention_policy_recorded,
        contract->failure_triage_policy_recorded,
        contract->no_embedded_vectors_policy_recorded,
        contract->apple_corecrypto_code_copied,
        contract->external_provider_code_copied,
        contract->kat_runner_implementation_present,
        contract->fixture_bundle_loaded,
        contract->fixture_bundle_digest_verified,
        contract->fixture_bundle_license_reviewed,
        contract->fixture_bundle_storage_reviewed,
        contract->parser_reviewed_for_runner,
        contract->result_schema_reviewed,
        contract->positive_result_rows_recorded,
        contract->negative_result_rows_recorded,
        contract->malformed_result_rows_recorded,
        contract->implicit_rejection_rows_recorded,
        contract->provider_differential_rows_recorded,
        contract->ci_kat_replay_transcript_recorded,
        contract->operation_implementation_present,
        contract->kat_execution_enabled,
        contract->acvp_response_generation_enabled,
        contract->acvp_submission_allowed,
        contract->operation_execution_allowed,
        contract->production_crypto_claim_allowed,
        contract->fips_claim_allowed,
        contract->runtime_authority_granted,
        contract->required_kat_runner_contract_items_total,
        contract->required_kat_runner_contract_items_satisfied,
        contract->blocked_reason,
        latticra_q_seal_ml_kem_kat_runner_contract_error_label(contract->error),
        contract->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
