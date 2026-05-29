#include "latticra/q_seal_ml_kem_evidence_import_review_gate.h"

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
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->evidence_import_review_gate_present);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->acvp_ml_kem_schema_bound);
    satisfied += one_if(gate->evidence_import_packet_manifest_bound);
    satisfied += one_if(gate->vector_fixture_digest_ledger_bound);
    satisfied += one_if(gate->receipt_replay_results_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->reviewer_identity_fixture_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->source_digest_verification_bound);
    satisfied += one_if(gate->implementation_binding_manifest_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->offline_evidence_intake_recorded);
    satisfied += one_if(gate->digest_algorithm_sha256_required);
    satisfied += one_if(gate->immutable_import_record_required);
    satisfied += one_if(gate->source_url_digest_size_license_required);
    satisfied += one_if(gate->parameter_set_coverage_required);
    satisfied += one_if(gate->operation_family_coverage_required);
    satisfied += one_if(gate->replay_transcript_required);
    satisfied += one_if(gate->tamper_replay_required);
    satisfied += one_if(gate->reviewer_role_import_required);
    satisfied += one_if(gate->dual_reviewer_separation_required);
    satisfied += one_if(gate->approval_authority_required);
    satisfied += one_if(gate->no_implicit_operation_policy_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->fixture_digest_rows_imported);
    satisfied += one_if(gate->receipt_replay_transcripts_imported);
    satisfied += one_if(gate->reviewer_role_records_imported);
    satisfied += one_if(gate->source_digest_receipts_imported);
    satisfied += one_if(gate->parameter_set_coverage_recorded);
    satisfied += one_if(gate->operation_family_coverage_recorded);
    satisfied += one_if(gate->negative_case_coverage_recorded);
    satisfied += one_if(gate->replay_tamper_evidence_recorded);
    satisfied += one_if(gate->evidence_import_reviewed);
    satisfied += one_if(gate->evidence_import_gate_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_evidence_import_review_gate_error_label(
    latticra_q_seal_ml_kem_evidence_import_review_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(
    latticra_q_seal_ml_kem_evidence_import_review_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->evidence_import_profile,
        sizeof(out->evidence_import_profile),
        "latticra-q-seal-ml-kem-evidence-import-review-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Evidence Import Review Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF");
    copy_literal(
        out->evidence_import_scope,
        sizeof(out->evidence_import_scope),
        "ML-KEM-evidence-import-review-before-implementation-or-promotion");
    copy_literal(
        out->evidence_import_state,
        sizeof(out->evidence_import_state),
        "evidence-import-review-recorded-import-evidence-missing");

    out->evidence_import_review_gate_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_schema_bound = 1u;
    out->evidence_import_packet_manifest_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->receipt_replay_results_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->reviewer_identity_fixture_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->offline_evidence_intake_recorded = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->immutable_import_record_required = 1u;
    out->source_url_digest_size_license_required = 1u;
    out->parameter_set_coverage_required = 1u;
    out->operation_family_coverage_required = 1u;
    out->replay_transcript_required = 1u;
    out->tamper_replay_required = 1u;
    out->reviewer_role_import_required = 1u;
    out->dual_reviewer_separation_required = 1u;
    out->approval_authority_required = 1u;
    out->no_implicit_operation_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->fixture_digest_rows_imported = 0u;
    out->receipt_replay_transcripts_imported = 0u;
    out->reviewer_role_records_imported = 0u;
    out->source_digest_receipts_imported = 0u;
    out->parameter_set_coverage_recorded = 0u;
    out->operation_family_coverage_recorded = 0u;
    out->negative_case_coverage_recorded = 0u;
    out->replay_tamper_evidence_recorded = 0u;
    out->evidence_import_reviewed = 0u;
    out->evidence_import_gate_accepted = 0u;
    out->vector_execution_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_evidence_import_items_total = 37u;
    out->required_evidence_import_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-digest-rows-replay-transcripts-role-map-source-digest-coverage-and-review-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-evidence-import-review-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_evidence_import_review_gate_is_no_effect(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->evidence_import_review_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->evidence_import_gate_accepted == 0u &&
           gate->vector_execution_allowed == 0u &&
           gate->acvp_submission_allowed == 0u &&
           gate->implementation_promotion_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_BLOCKED;
}

int latticra_q_seal_ml_kem_evidence_import_review_gate_allows_import_acceptance(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->evidence_import_review_gate_present == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->acvp_ml_kem_schema_bound == 1u &&
           gate->evidence_import_packet_manifest_bound == 1u &&
           gate->vector_fixture_digest_ledger_bound == 1u &&
           gate->receipt_replay_results_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->reviewer_identity_fixture_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->source_digest_verification_bound == 1u &&
           gate->implementation_binding_manifest_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->offline_evidence_intake_recorded == 1u &&
           gate->digest_algorithm_sha256_required == 1u &&
           gate->immutable_import_record_required == 1u &&
           gate->source_url_digest_size_license_required == 1u &&
           gate->parameter_set_coverage_required == 1u &&
           gate->operation_family_coverage_required == 1u &&
           gate->replay_transcript_required == 1u &&
           gate->tamper_replay_required == 1u &&
           gate->reviewer_role_import_required == 1u &&
           gate->dual_reviewer_separation_required == 1u &&
           gate->approval_authority_required == 1u &&
           gate->no_implicit_operation_policy_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->fixture_digest_rows_imported == 1u &&
           gate->receipt_replay_transcripts_imported == 1u &&
           gate->reviewer_role_records_imported == 1u &&
           gate->source_digest_receipts_imported == 1u &&
           gate->parameter_set_coverage_recorded == 1u &&
           gate->operation_family_coverage_recorded == 1u &&
           gate->negative_case_coverage_recorded == 1u &&
           gate->replay_tamper_evidence_recorded == 1u &&
           gate->evidence_import_reviewed == 1u &&
           gate->evidence_import_gate_accepted == 1u &&
           gate->vector_execution_allowed == 0u &&
           gate->acvp_submission_allowed == 0u &&
           gate->implementation_promotion_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_evidence_import_review_gate_report(
    const latticra_q_seal_ml_kem_evidence_import_review_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM EVIDENCE IMPORT REVIEW GATE\n"
        "evidence_import_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "evidence_import_scope=%s\n"
        "evidence_import_state=%s\n"
        "evidence_import_review_gate_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_schema_bound=%u\n"
        "evidence_import_packet_manifest_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "receipt_replay_results_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "reviewer_identity_fixture_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "offline_evidence_intake_recorded=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "immutable_import_record_required=%u\n"
        "source_url_digest_size_license_required=%u\n"
        "parameter_set_coverage_required=%u\n"
        "operation_family_coverage_required=%u\n"
        "replay_transcript_required=%u\n"
        "tamper_replay_required=%u\n"
        "reviewer_role_import_required=%u\n"
        "dual_reviewer_separation_required=%u\n"
        "approval_authority_required=%u\n"
        "no_implicit_operation_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "fixture_digest_rows_imported=%u\n"
        "receipt_replay_transcripts_imported=%u\n"
        "reviewer_role_records_imported=%u\n"
        "source_digest_receipts_imported=%u\n"
        "parameter_set_coverage_recorded=%u\n"
        "operation_family_coverage_recorded=%u\n"
        "negative_case_coverage_recorded=%u\n"
        "replay_tamper_evidence_recorded=%u\n"
        "evidence_import_reviewed=%u\n"
        "evidence_import_gate_accepted=%u\n"
        "vector_execution_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_evidence_import_items_total=%u\n"
        "required_evidence_import_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->evidence_import_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->evidence_import_scope,
        gate->evidence_import_state,
        gate->evidence_import_review_gate_present,
        gate->fips_203_algorithm_bound,
        gate->acvp_ml_kem_schema_bound,
        gate->evidence_import_packet_manifest_bound,
        gate->vector_fixture_digest_ledger_bound,
        gate->receipt_replay_results_bound,
        gate->reviewer_role_mapping_bound,
        gate->reviewer_identity_fixture_bound,
        gate->review_disposition_ledger_bound,
        gate->source_digest_verification_bound,
        gate->implementation_binding_manifest_bound,
        gate->ci_promotion_evidence_bound,
        gate->clean_room_source_boundary_recorded,
        gate->offline_evidence_intake_recorded,
        gate->digest_algorithm_sha256_required,
        gate->immutable_import_record_required,
        gate->source_url_digest_size_license_required,
        gate->parameter_set_coverage_required,
        gate->operation_family_coverage_required,
        gate->replay_transcript_required,
        gate->tamper_replay_required,
        gate->reviewer_role_import_required,
        gate->dual_reviewer_separation_required,
        gate->approval_authority_required,
        gate->no_implicit_operation_policy_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->fixture_digest_rows_imported,
        gate->receipt_replay_transcripts_imported,
        gate->reviewer_role_records_imported,
        gate->source_digest_receipts_imported,
        gate->parameter_set_coverage_recorded,
        gate->operation_family_coverage_recorded,
        gate->negative_case_coverage_recorded,
        gate->replay_tamper_evidence_recorded,
        gate->evidence_import_reviewed,
        gate->evidence_import_gate_accepted,
        gate->vector_execution_allowed,
        gate->acvp_submission_allowed,
        gate->implementation_promotion_allowed,
        gate->operation_execution_allowed,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->required_evidence_import_items_total,
        gate->required_evidence_import_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_evidence_import_review_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
