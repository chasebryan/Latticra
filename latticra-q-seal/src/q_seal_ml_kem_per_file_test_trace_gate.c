#include "latticra/q_seal_ml_kem_per_file_test_trace_gate.h"

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
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->per_file_test_trace_gate_present);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->planned_source_units_count == 9u);
    satisfied += one_if(gate->planned_test_units_count == 9u);
    satisfied += one_if(gate->primitive_source_acceptance_gate_bound);
    satisfied += one_if(gate->implementation_traceability_matrix_bound);
    satisfied += one_if(gate->implementation_file_digest_plan_bound);
    satisfied += one_if(gate->clean_room_author_attestation_gate_bound);
    satisfied += one_if(gate->per_file_standards_trace_gate_bound);
    satisfied += one_if(gate->kat_manifest_bound);
    satisfied += one_if(gate->kat_runner_contract_bound);
    satisfied += one_if(gate->kat_result_schema_bound);
    satisfied += one_if(gate->kat_result_row_fixture_bound);
    satisfied += one_if(gate->acvp_contracts_bound);
    satisfied += one_if(gate->vector_schema_bound);
    satisfied += one_if(gate->vector_fixture_lock_bound);
    satisfied += one_if(gate->vector_fixture_digest_ledger_bound);
    satisfied += one_if(gate->negative_test_evidence_bound);
    satisfied += one_if(gate->source_digest_manifest_bound);
    satisfied += one_if(gate->source_digest_receipt_bound);
    satisfied += one_if(gate->code_owner_review_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->test_family_columns_recorded);
    satisfied += one_if(gate->parameter_set_columns_recorded);
    satisfied += one_if(gate->operation_family_columns_recorded);
    satisfied += one_if(gate->vector_reference_columns_recorded);
    satisfied += one_if(gate->expected_result_columns_recorded);
    satisfied += one_if(gate->review_disposition_columns_recorded);
    satisfied += one_if(gate->source_files_created);
    satisfied += one_if(gate->per_file_test_trace_rows_recorded);
    satisfied += one_if(gate->kat_trace_coverage_reviewed);
    satisfied += one_if(gate->acvp_trace_coverage_reviewed);
    satisfied += one_if(gate->negative_test_trace_reviewed);
    satisfied += one_if(gate->trace_review_approved);
    satisfied += one_if(gate->per_file_test_trace_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_per_file_test_trace_gate_error_label(
    latticra_q_seal_ml_kem_per_file_test_trace_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_per_file_test_trace_gate_prepare(
    latticra_q_seal_ml_kem_per_file_test_trace_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->test_trace_profile,
        sizeof(out->test_trace_profile),
        "latticra-q-seal-ml-kem-per-file-test-trace-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Per-File Test Trace Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->trace_scope,
        sizeof(out->trace_scope),
        "ML-KEM-per-file-KAT-ACVP-negative-test-trace-before-source-acceptance");
    copy_literal(
        out->trace_state,
        sizeof(out->trace_state),
        "test-trace-template-recorded-trace-rows-blocked");

    out->per_file_test_trace_gate_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->primitive_source_acceptance_gate_bound = 1u;
    out->implementation_traceability_matrix_bound = 1u;
    out->implementation_file_digest_plan_bound = 1u;
    out->clean_room_author_attestation_gate_bound = 1u;
    out->per_file_standards_trace_gate_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->kat_runner_contract_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->acvp_contracts_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_lock_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->source_digest_manifest_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->test_family_columns_recorded = 1u;
    out->parameter_set_columns_recorded = 1u;
    out->operation_family_columns_recorded = 1u;
    out->vector_reference_columns_recorded = 1u;
    out->expected_result_columns_recorded = 1u;
    out->review_disposition_columns_recorded = 1u;
    out->source_files_created = 0u;
    out->per_file_test_trace_rows_recorded = 0u;
    out->kat_trace_coverage_reviewed = 0u;
    out->acvp_trace_coverage_reviewed = 0u;
    out->negative_test_trace_reviewed = 0u;
    out->trace_review_approved = 0u;
    out->per_file_test_trace_accepted = 0u;
    out->operation_execution_allowed = 0u;
    out->shared_secret_emission_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_test_trace_items_total = 39u;
    out->required_test_trace_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-files-per-file-test-trace-rows-kat-acvp-negative-coverage-review-and-trace-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-per-file-test-trace-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_per_file_test_trace_gate_is_no_effect(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->per_file_test_trace_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->source_files_created == 0u &&
           gate->per_file_test_trace_accepted == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->shared_secret_emission_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_TEST_TRACE_BLOCKED;
}

int latticra_q_seal_ml_kem_per_file_test_trace_gate_allows_trace_acceptance(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->per_file_test_trace_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->planned_source_units_count == 9u &&
           gate->planned_test_units_count == 9u &&
           gate->primitive_source_acceptance_gate_bound == 1u &&
           gate->implementation_traceability_matrix_bound == 1u &&
           gate->implementation_file_digest_plan_bound == 1u &&
           gate->clean_room_author_attestation_gate_bound == 1u &&
           gate->per_file_standards_trace_gate_bound == 1u &&
           gate->kat_manifest_bound == 1u &&
           gate->kat_runner_contract_bound == 1u &&
           gate->kat_result_schema_bound == 1u &&
           gate->kat_result_row_fixture_bound == 1u &&
           gate->acvp_contracts_bound == 1u &&
           gate->vector_schema_bound == 1u &&
           gate->vector_fixture_lock_bound == 1u &&
           gate->vector_fixture_digest_ledger_bound == 1u &&
           gate->negative_test_evidence_bound == 1u &&
           gate->source_digest_manifest_bound == 1u &&
           gate->source_digest_receipt_bound == 1u &&
           gate->code_owner_review_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->test_family_columns_recorded == 1u &&
           gate->parameter_set_columns_recorded == 1u &&
           gate->operation_family_columns_recorded == 1u &&
           gate->vector_reference_columns_recorded == 1u &&
           gate->expected_result_columns_recorded == 1u &&
           gate->review_disposition_columns_recorded == 1u &&
           gate->source_files_created == 1u &&
           gate->per_file_test_trace_rows_recorded == 1u &&
           gate->kat_trace_coverage_reviewed == 1u &&
           gate->acvp_trace_coverage_reviewed == 1u &&
           gate->negative_test_trace_reviewed == 1u &&
           gate->trace_review_approved == 1u &&
           gate->per_file_test_trace_accepted == 1u &&
           gate->operation_execution_allowed == 0u &&
           gate->shared_secret_emission_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_per_file_test_trace_gate_report(
    const latticra_q_seal_ml_kem_per_file_test_trace_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM PER-FILE TEST TRACE GATE\n"
        "test_trace_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "trace_scope=%s\n"
        "trace_state=%s\n"
        "per_file_test_trace_gate_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "primitive_source_acceptance_gate_bound=%u\n"
        "implementation_traceability_matrix_bound=%u\n"
        "implementation_file_digest_plan_bound=%u\n"
        "clean_room_author_attestation_gate_bound=%u\n"
        "per_file_standards_trace_gate_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "kat_runner_contract_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "acvp_contracts_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_lock_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "source_digest_manifest_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "test_family_columns_recorded=%u\n"
        "parameter_set_columns_recorded=%u\n"
        "operation_family_columns_recorded=%u\n"
        "vector_reference_columns_recorded=%u\n"
        "expected_result_columns_recorded=%u\n"
        "review_disposition_columns_recorded=%u\n"
        "source_files_created=%u\n"
        "per_file_test_trace_rows_recorded=%u\n"
        "kat_trace_coverage_reviewed=%u\n"
        "acvp_trace_coverage_reviewed=%u\n"
        "negative_test_trace_reviewed=%u\n"
        "trace_review_approved=%u\n"
        "per_file_test_trace_accepted=%u\n"
        "operation_execution_allowed=%u\n"
        "shared_secret_emission_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_test_trace_items_total=%u\n"
        "required_test_trace_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->test_trace_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->source_boundary,
        gate->trace_scope,
        gate->trace_state,
        gate->per_file_test_trace_gate_present,
        gate->clean_room_source_boundary_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->planned_source_units_count,
        gate->planned_test_units_count,
        gate->primitive_source_acceptance_gate_bound,
        gate->implementation_traceability_matrix_bound,
        gate->implementation_file_digest_plan_bound,
        gate->clean_room_author_attestation_gate_bound,
        gate->per_file_standards_trace_gate_bound,
        gate->kat_manifest_bound,
        gate->kat_runner_contract_bound,
        gate->kat_result_schema_bound,
        gate->kat_result_row_fixture_bound,
        gate->acvp_contracts_bound,
        gate->vector_schema_bound,
        gate->vector_fixture_lock_bound,
        gate->vector_fixture_digest_ledger_bound,
        gate->negative_test_evidence_bound,
        gate->source_digest_manifest_bound,
        gate->source_digest_receipt_bound,
        gate->code_owner_review_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->ci_promotion_evidence_bound,
        gate->test_family_columns_recorded,
        gate->parameter_set_columns_recorded,
        gate->operation_family_columns_recorded,
        gate->vector_reference_columns_recorded,
        gate->expected_result_columns_recorded,
        gate->review_disposition_columns_recorded,
        gate->source_files_created,
        gate->per_file_test_trace_rows_recorded,
        gate->kat_trace_coverage_reviewed,
        gate->acvp_trace_coverage_reviewed,
        gate->negative_test_trace_reviewed,
        gate->trace_review_approved,
        gate->per_file_test_trace_accepted,
        gate->operation_execution_allowed,
        gate->shared_secret_emission_allowed,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->required_test_trace_items_total,
        gate->required_test_trace_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_per_file_test_trace_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
