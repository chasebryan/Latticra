#include "latticra/q_seal_ml_kem_implementation_file_digest_plan.h"

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
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan) {
    unsigned satisfied = 0u;

    satisfied += one_if(plan->implementation_file_digest_plan_present);
    satisfied += one_if(plan->clean_room_source_boundary_recorded);
    satisfied += one_if(plan->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(plan->external_provider_code_copied == 0u);
    satisfied += one_if(plan->planned_source_units_count == 9u);
    satisfied += one_if(plan->planned_test_units_count == 9u);
    satisfied += one_if(plan->digest_algorithm_sha256_recorded);
    satisfied += one_if(plan->source_digest_manifest_bound);
    satisfied += one_if(plan->source_digest_receipt_bound);
    satisfied += one_if(plan->source_digest_verification_bound);
    satisfied += one_if(plan->receipt_replay_results_bound);
    satisfied += one_if(plan->implementation_binding_manifest_bound);
    satisfied += one_if(plan->implementation_traceability_matrix_bound);
    satisfied += one_if(plan->primitive_source_acceptance_gate_bound);
    satisfied += one_if(plan->source_layout_gate_bound);
    satisfied += one_if(plan->fips_conformance_matrix_bound);
    satisfied += one_if(plan->sp800_227_usage_profile_bound);
    satisfied += one_if(plan->kat_manifest_bound);
    satisfied += one_if(plan->acvp_contracts_bound);
    satisfied += one_if(plan->code_owner_review_bound);
    satisfied += one_if(plan->review_disposition_ledger_bound);
    satisfied += one_if(plan->reviewer_role_mapping_bound);
    satisfied += one_if(plan->ci_promotion_evidence_bound);
    satisfied += one_if(plan->per_file_digest_row_schema_recorded);
    satisfied += one_if(plan->per_file_trace_columns_recorded);
    satisfied += one_if(plan->per_file_review_columns_recorded);
    satisfied += one_if(plan->source_files_created);
    satisfied += one_if(plan->implementation_file_digest_rows_recorded);
    satisfied += one_if(plan->test_file_digest_rows_recorded);
    satisfied += one_if(plan->build_script_digest_rows_recorded);
    satisfied += one_if(plan->digest_receipt_reviewed);
    satisfied += one_if(plan->digest_replay_verified);
    satisfied += one_if(plan->file_digest_plan_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_implementation_file_digest_plan_error_label(
    latticra_q_seal_ml_kem_implementation_file_digest_plan_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(
    latticra_q_seal_ml_kem_implementation_file_digest_plan_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->digest_plan_profile,
        sizeof(out->digest_plan_profile),
        "latticra-q-seal-ml-kem-implementation-file-digest-plan/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Implementation File Digest Plan");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-ACVP-ML-KEM");
    copy_literal(out->digest_algorithm, sizeof(out->digest_algorithm), "SHA-256");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->digest_plan_scope,
        sizeof(out->digest_plan_scope),
        "ML-KEM-implementation-file-digest-row-plan-before-source-acceptance");
    copy_literal(
        out->digest_plan_state,
        sizeof(out->digest_plan_state),
        "file-digest-plan-recorded-digest-rows-blocked");

    out->implementation_file_digest_plan_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->digest_algorithm_sha256_recorded = 1u;
    out->source_digest_manifest_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->receipt_replay_results_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->implementation_traceability_matrix_bound = 1u;
    out->primitive_source_acceptance_gate_bound = 1u;
    out->source_layout_gate_bound = 1u;
    out->fips_conformance_matrix_bound = 1u;
    out->sp800_227_usage_profile_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->acvp_contracts_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->per_file_digest_row_schema_recorded = 1u;
    out->per_file_trace_columns_recorded = 1u;
    out->per_file_review_columns_recorded = 1u;
    out->source_files_created = 0u;
    out->implementation_file_digest_rows_recorded = 0u;
    out->test_file_digest_rows_recorded = 0u;
    out->build_script_digest_rows_recorded = 0u;
    out->digest_receipt_reviewed = 0u;
    out->digest_replay_verified = 0u;
    out->file_digest_plan_accepted = 0u;
    out->operation_execution_allowed = 0u;
    out->shared_secret_emission_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_digest_plan_items_total = 33u;
    out->required_digest_plan_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-files-implementation-test-build-digest-rows-reviewed-receipts-replay-and-plan-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-implementation-file-digest-plan-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_implementation_file_digest_plan_is_no_effect(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan) {
    if (plan == NULL) {
        return 0;
    }

    return plan->implementation_file_digest_plan_present == 1u &&
           plan->clean_room_source_boundary_recorded == 1u &&
           plan->apple_corecrypto_code_copied == 0u &&
           plan->external_provider_code_copied == 0u &&
           plan->source_files_created == 0u &&
           plan->operation_execution_allowed == 0u &&
           plan->shared_secret_emission_allowed == 0u &&
           plan->production_crypto_claim_allowed == 0u &&
           plan->fips_claim_allowed == 0u &&
           plan->runtime_authority_granted == 0u &&
           plan->error == LATTICRA_Q_SEAL_ML_KEM_FILE_DIGEST_PLAN_BLOCKED;
}

int latticra_q_seal_ml_kem_implementation_file_digest_plan_allows_digest_row_acceptance(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan) {
    if (plan == NULL) {
        return 0;
    }

    return plan->implementation_file_digest_plan_present == 1u &&
           plan->clean_room_source_boundary_recorded == 1u &&
           plan->apple_corecrypto_code_copied == 0u &&
           plan->external_provider_code_copied == 0u &&
           plan->planned_source_units_count == 9u &&
           plan->planned_test_units_count == 9u &&
           plan->digest_algorithm_sha256_recorded == 1u &&
           plan->source_digest_manifest_bound == 1u &&
           plan->source_digest_receipt_bound == 1u &&
           plan->source_digest_verification_bound == 1u &&
           plan->receipt_replay_results_bound == 1u &&
           plan->implementation_binding_manifest_bound == 1u &&
           plan->implementation_traceability_matrix_bound == 1u &&
           plan->primitive_source_acceptance_gate_bound == 1u &&
           plan->source_layout_gate_bound == 1u &&
           plan->fips_conformance_matrix_bound == 1u &&
           plan->sp800_227_usage_profile_bound == 1u &&
           plan->kat_manifest_bound == 1u &&
           plan->acvp_contracts_bound == 1u &&
           plan->code_owner_review_bound == 1u &&
           plan->review_disposition_ledger_bound == 1u &&
           plan->reviewer_role_mapping_bound == 1u &&
           plan->ci_promotion_evidence_bound == 1u &&
           plan->per_file_digest_row_schema_recorded == 1u &&
           plan->per_file_trace_columns_recorded == 1u &&
           plan->per_file_review_columns_recorded == 1u &&
           plan->source_files_created == 1u &&
           plan->implementation_file_digest_rows_recorded == 1u &&
           plan->test_file_digest_rows_recorded == 1u &&
           plan->build_script_digest_rows_recorded == 1u &&
           plan->digest_receipt_reviewed == 1u &&
           plan->digest_replay_verified == 1u &&
           plan->file_digest_plan_accepted == 1u &&
           plan->operation_execution_allowed == 0u &&
           plan->shared_secret_emission_allowed == 0u &&
           plan->production_crypto_claim_allowed == 0u &&
           plan->fips_claim_allowed == 0u &&
           plan->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_implementation_file_digest_plan_report(
    const latticra_q_seal_ml_kem_implementation_file_digest_plan_t *plan,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (plan == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM IMPLEMENTATION FILE DIGEST PLAN\n"
        "digest_plan_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "digest_algorithm=%s\n"
        "source_boundary=%s\n"
        "digest_plan_scope=%s\n"
        "digest_plan_state=%s\n"
        "implementation_file_digest_plan_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "digest_algorithm_sha256_recorded=%u\n"
        "source_digest_manifest_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "receipt_replay_results_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "implementation_traceability_matrix_bound=%u\n"
        "primitive_source_acceptance_gate_bound=%u\n"
        "source_layout_gate_bound=%u\n"
        "fips_conformance_matrix_bound=%u\n"
        "sp800_227_usage_profile_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "acvp_contracts_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "per_file_digest_row_schema_recorded=%u\n"
        "per_file_trace_columns_recorded=%u\n"
        "per_file_review_columns_recorded=%u\n"
        "source_files_created=%u\n"
        "implementation_file_digest_rows_recorded=%u\n"
        "test_file_digest_rows_recorded=%u\n"
        "build_script_digest_rows_recorded=%u\n"
        "digest_receipt_reviewed=%u\n"
        "digest_replay_verified=%u\n"
        "file_digest_plan_accepted=%u\n"
        "operation_execution_allowed=%u\n"
        "shared_secret_emission_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_digest_plan_items_total=%u\n"
        "required_digest_plan_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        plan->digest_plan_profile,
        plan->formal_title,
        plan->standards_basis,
        plan->digest_algorithm,
        plan->source_boundary,
        plan->digest_plan_scope,
        plan->digest_plan_state,
        plan->implementation_file_digest_plan_present,
        plan->clean_room_source_boundary_recorded,
        plan->apple_corecrypto_code_copied,
        plan->external_provider_code_copied,
        plan->planned_source_units_count,
        plan->planned_test_units_count,
        plan->digest_algorithm_sha256_recorded,
        plan->source_digest_manifest_bound,
        plan->source_digest_receipt_bound,
        plan->source_digest_verification_bound,
        plan->receipt_replay_results_bound,
        plan->implementation_binding_manifest_bound,
        plan->implementation_traceability_matrix_bound,
        plan->primitive_source_acceptance_gate_bound,
        plan->source_layout_gate_bound,
        plan->fips_conformance_matrix_bound,
        plan->sp800_227_usage_profile_bound,
        plan->kat_manifest_bound,
        plan->acvp_contracts_bound,
        plan->code_owner_review_bound,
        plan->review_disposition_ledger_bound,
        plan->reviewer_role_mapping_bound,
        plan->ci_promotion_evidence_bound,
        plan->per_file_digest_row_schema_recorded,
        plan->per_file_trace_columns_recorded,
        plan->per_file_review_columns_recorded,
        plan->source_files_created,
        plan->implementation_file_digest_rows_recorded,
        plan->test_file_digest_rows_recorded,
        plan->build_script_digest_rows_recorded,
        plan->digest_receipt_reviewed,
        plan->digest_replay_verified,
        plan->file_digest_plan_accepted,
        plan->operation_execution_allowed,
        plan->shared_secret_emission_allowed,
        plan->production_crypto_claim_allowed,
        plan->fips_claim_allowed,
        plan->runtime_authority_granted,
        plan->required_digest_plan_items_total,
        plan->required_digest_plan_items_satisfied,
        plan->blocked_reason,
        latticra_q_seal_ml_kem_implementation_file_digest_plan_error_label(plan->error),
        plan->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
