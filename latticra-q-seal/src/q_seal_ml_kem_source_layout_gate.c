#include "latticra/q_seal_ml_kem_source_layout_gate.h"

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
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->source_layout_gate_present);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->planned_source_units_count == 9u);
    satisfied += one_if(gate->planned_test_units_count == 9u);
    satisfied += one_if(gate->implementation_unit_roles_recorded);
    satisfied += one_if(gate->test_unit_roles_recorded);
    satisfied += one_if(gate->public_api_boundary_recorded);
    satisfied += one_if(gate->internal_primitive_boundary_recorded);
    satisfied += one_if(gate->secret_state_boundary_recorded);
    satisfied += one_if(gate->randomness_boundary_recorded);
    satisfied += one_if(gate->zeroization_boundary_recorded);
    satisfied += one_if(gate->constant_time_boundary_recorded);
    satisfied += one_if(gate->parameter_set_coverage_recorded);
    satisfied += one_if(gate->negative_test_lane_recorded);
    satisfied += one_if(gate->kat_acvp_lane_recorded);
    satisfied += one_if(gate->digest_manifest_lane_recorded);
    satisfied += one_if(gate->review_owner_lane_recorded);
    satisfied += one_if(gate->implementation_binding_manifest_bound);
    satisfied += one_if(gate->implementation_file_digest_plan_bound);
    satisfied += one_if(gate->clean_room_author_attestation_gate_bound);
    satisfied += one_if(gate->per_file_standards_trace_gate_bound);
    satisfied += one_if(gate->per_file_test_trace_gate_bound);
    satisfied += one_if(gate->implementation_traceability_matrix_bound);
    satisfied += one_if(gate->primitive_source_acceptance_gate_bound);
    satisfied += one_if(gate->source_digest_manifest_bound);
    satisfied += one_if(gate->source_digest_receipt_bound);
    satisfied += one_if(gate->code_owner_review_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->source_files_created);
    satisfied += one_if(gate->source_layout_rows_recorded);
    satisfied += one_if(gate->layout_digest_rows_recorded);
    satisfied += one_if(gate->layout_reviewed);
    satisfied += one_if(gate->layout_acceptance_approved);
    satisfied += one_if(gate->source_layout_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_source_layout_gate_error_label(
    latticra_q_seal_ml_kem_source_layout_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_layout_gate_prepare(
    latticra_q_seal_ml_kem_source_layout_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->layout_profile,
        sizeof(out->layout_profile),
        "latticra-q-seal-ml-kem-source-layout-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Source Layout Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->layout_scope,
        sizeof(out->layout_scope),
        "ML-KEM-source-layout-and-file-role-boundary-before-source-acceptance");
    copy_literal(
        out->layout_state,
        sizeof(out->layout_state),
        "source-layout-recorded-source-files-blocked");

    out->source_layout_gate_present = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->planned_source_units_count = 9u;
    out->planned_test_units_count = 9u;
    out->implementation_unit_roles_recorded = 1u;
    out->test_unit_roles_recorded = 1u;
    out->public_api_boundary_recorded = 1u;
    out->internal_primitive_boundary_recorded = 1u;
    out->secret_state_boundary_recorded = 1u;
    out->randomness_boundary_recorded = 1u;
    out->zeroization_boundary_recorded = 1u;
    out->constant_time_boundary_recorded = 1u;
    out->parameter_set_coverage_recorded = 1u;
    out->negative_test_lane_recorded = 1u;
    out->kat_acvp_lane_recorded = 1u;
    out->digest_manifest_lane_recorded = 1u;
    out->review_owner_lane_recorded = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->implementation_file_digest_plan_bound = 1u;
    out->clean_room_author_attestation_gate_bound = 1u;
    out->per_file_standards_trace_gate_bound = 1u;
    out->per_file_test_trace_gate_bound = 1u;
    out->implementation_traceability_matrix_bound = 1u;
    out->primitive_source_acceptance_gate_bound = 1u;
    out->source_digest_manifest_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->source_files_created = 0u;
    out->source_layout_rows_recorded = 0u;
    out->layout_digest_rows_recorded = 0u;
    out->layout_reviewed = 0u;
    out->layout_acceptance_approved = 0u;
    out->source_layout_accepted = 0u;
    out->operation_execution_allowed = 0u;
    out->shared_secret_emission_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_layout_items_total = 38u;
    out->required_layout_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "source-files-layout-rows-digest-rows-review-layout-approval-and-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-source-layout-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_source_layout_gate_is_no_effect(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->source_layout_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->source_files_created == 0u &&
           gate->source_layout_rows_recorded == 0u &&
           gate->source_layout_accepted == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->shared_secret_emission_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_SOURCE_LAYOUT_GATE_BLOCKED;
}

int latticra_q_seal_ml_kem_source_layout_gate_allows_layout_acceptance(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->source_layout_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->planned_source_units_count == 9u &&
           gate->planned_test_units_count == 9u &&
           gate->implementation_unit_roles_recorded == 1u &&
           gate->test_unit_roles_recorded == 1u &&
           gate->public_api_boundary_recorded == 1u &&
           gate->internal_primitive_boundary_recorded == 1u &&
           gate->secret_state_boundary_recorded == 1u &&
           gate->randomness_boundary_recorded == 1u &&
           gate->zeroization_boundary_recorded == 1u &&
           gate->constant_time_boundary_recorded == 1u &&
           gate->parameter_set_coverage_recorded == 1u &&
           gate->negative_test_lane_recorded == 1u &&
           gate->kat_acvp_lane_recorded == 1u &&
           gate->digest_manifest_lane_recorded == 1u &&
           gate->review_owner_lane_recorded == 1u &&
           gate->implementation_binding_manifest_bound == 1u &&
           gate->implementation_file_digest_plan_bound == 1u &&
           gate->clean_room_author_attestation_gate_bound == 1u &&
           gate->per_file_standards_trace_gate_bound == 1u &&
           gate->per_file_test_trace_gate_bound == 1u &&
           gate->implementation_traceability_matrix_bound == 1u &&
           gate->primitive_source_acceptance_gate_bound == 1u &&
           gate->source_digest_manifest_bound == 1u &&
           gate->source_digest_receipt_bound == 1u &&
           gate->code_owner_review_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->source_files_created == 1u &&
           gate->source_layout_rows_recorded == 1u &&
           gate->layout_digest_rows_recorded == 1u &&
           gate->layout_reviewed == 1u &&
           gate->layout_acceptance_approved == 1u &&
           gate->source_layout_accepted == 1u &&
           gate->operation_execution_allowed == 0u &&
           gate->shared_secret_emission_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_source_layout_gate_report(
    const latticra_q_seal_ml_kem_source_layout_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SOURCE LAYOUT GATE\n"
        "layout_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "layout_scope=%s\n"
        "layout_state=%s\n"
        "source_layout_gate_present=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "planned_source_units_count=%u\n"
        "planned_test_units_count=%u\n"
        "implementation_unit_roles_recorded=%u\n"
        "test_unit_roles_recorded=%u\n"
        "public_api_boundary_recorded=%u\n"
        "internal_primitive_boundary_recorded=%u\n"
        "secret_state_boundary_recorded=%u\n"
        "randomness_boundary_recorded=%u\n"
        "zeroization_boundary_recorded=%u\n"
        "constant_time_boundary_recorded=%u\n"
        "parameter_set_coverage_recorded=%u\n"
        "negative_test_lane_recorded=%u\n"
        "kat_acvp_lane_recorded=%u\n"
        "digest_manifest_lane_recorded=%u\n"
        "review_owner_lane_recorded=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "implementation_file_digest_plan_bound=%u\n"
        "clean_room_author_attestation_gate_bound=%u\n"
        "per_file_standards_trace_gate_bound=%u\n"
        "per_file_test_trace_gate_bound=%u\n"
        "implementation_traceability_matrix_bound=%u\n"
        "primitive_source_acceptance_gate_bound=%u\n"
        "source_digest_manifest_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "source_files_created=%u\n"
        "source_layout_rows_recorded=%u\n"
        "layout_digest_rows_recorded=%u\n"
        "layout_reviewed=%u\n"
        "layout_acceptance_approved=%u\n"
        "source_layout_accepted=%u\n"
        "operation_execution_allowed=%u\n"
        "shared_secret_emission_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_layout_items_total=%u\n"
        "required_layout_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->layout_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->source_boundary,
        gate->layout_scope,
        gate->layout_state,
        gate->source_layout_gate_present,
        gate->clean_room_source_boundary_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->planned_source_units_count,
        gate->planned_test_units_count,
        gate->implementation_unit_roles_recorded,
        gate->test_unit_roles_recorded,
        gate->public_api_boundary_recorded,
        gate->internal_primitive_boundary_recorded,
        gate->secret_state_boundary_recorded,
        gate->randomness_boundary_recorded,
        gate->zeroization_boundary_recorded,
        gate->constant_time_boundary_recorded,
        gate->parameter_set_coverage_recorded,
        gate->negative_test_lane_recorded,
        gate->kat_acvp_lane_recorded,
        gate->digest_manifest_lane_recorded,
        gate->review_owner_lane_recorded,
        gate->implementation_binding_manifest_bound,
        gate->implementation_file_digest_plan_bound,
        gate->clean_room_author_attestation_gate_bound,
        gate->per_file_standards_trace_gate_bound,
        gate->per_file_test_trace_gate_bound,
        gate->implementation_traceability_matrix_bound,
        gate->primitive_source_acceptance_gate_bound,
        gate->source_digest_manifest_bound,
        gate->source_digest_receipt_bound,
        gate->code_owner_review_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->ci_promotion_evidence_bound,
        gate->source_files_created,
        gate->source_layout_rows_recorded,
        gate->layout_digest_rows_recorded,
        gate->layout_reviewed,
        gate->layout_acceptance_approved,
        gate->source_layout_accepted,
        gate->operation_execution_allowed,
        gate->shared_secret_emission_allowed,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->required_layout_items_total,
        gate->required_layout_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_source_layout_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
