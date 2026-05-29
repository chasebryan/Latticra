#include "latticra/q_seal_ml_kem_evidence_import_packet_manifest.h"

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
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest) {
    unsigned satisfied = 0u;

    satisfied += one_if(manifest->evidence_import_packet_manifest_present);
    satisfied += one_if(manifest->fips_203_algorithm_bound);
    satisfied += one_if(manifest->acvp_ml_kem_schema_bound);
    satisfied += one_if(manifest->evidence_import_review_gate_bound);
    satisfied += one_if(manifest->vector_fixture_digest_ledger_bound);
    satisfied += one_if(manifest->receipt_replay_results_bound);
    satisfied += one_if(manifest->source_digest_receipt_bound);
    satisfied += one_if(manifest->source_digest_verification_bound);
    satisfied += one_if(manifest->reviewer_identity_fixture_bound);
    satisfied += one_if(manifest->reviewer_role_mapping_bound);
    satisfied += one_if(manifest->review_disposition_ledger_bound);
    satisfied += one_if(manifest->implementation_binding_manifest_bound);
    satisfied += one_if(manifest->ci_promotion_evidence_bound);
    satisfied += one_if(manifest->clean_room_source_boundary_recorded);
    satisfied += one_if(manifest->offline_packet_intake_recorded);
    satisfied += one_if(manifest->digest_algorithm_sha256_required);
    satisfied += one_if(manifest->immutable_packet_record_required);
    satisfied += one_if(manifest->source_url_column_required);
    satisfied += one_if(manifest->source_digest_column_required);
    satisfied += one_if(manifest->bundle_size_column_required);
    satisfied += one_if(manifest->license_column_required);
    satisfied += one_if(manifest->storage_path_column_required);
    satisfied += one_if(manifest->parameter_set_column_required);
    satisfied += one_if(manifest->operation_family_column_required);
    satisfied += one_if(manifest->negative_case_column_required);
    satisfied += one_if(manifest->replay_transcript_column_required);
    satisfied += one_if(manifest->tamper_evidence_column_required);
    satisfied += one_if(manifest->reviewer_role_column_required);
    satisfied += one_if(manifest->reviewer_identity_column_required);
    satisfied += one_if(manifest->disposition_column_required);
    satisfied += one_if(manifest->import_timestamp_column_required);
    satisfied += one_if(manifest->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(manifest->external_provider_code_copied == 0u);
    satisfied += one_if(manifest->fixture_digest_packet_rows_imported);
    satisfied += one_if(manifest->receipt_replay_packet_rows_imported);
    satisfied += one_if(manifest->source_digest_packet_rows_imported);
    satisfied += one_if(manifest->reviewer_role_packet_rows_imported);
    satisfied += one_if(manifest->coverage_packet_rows_imported);
    satisfied += one_if(manifest->tamper_packet_rows_imported);
    satisfied += one_if(manifest->evidence_packet_reviewed);
    satisfied += one_if(manifest->evidence_packet_manifest_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_label(
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->evidence_packet_profile,
        sizeof(out->evidence_packet_profile),
        "latticra-q-seal-ml-kem-evidence-import-packet-manifest/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Evidence Import Packet Manifest");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF");
    copy_literal(
        out->evidence_packet_scope,
        sizeof(out->evidence_packet_scope),
        "ML-KEM-evidence-import-packet-manifest-before-import-review");
    copy_literal(
        out->evidence_packet_state,
        sizeof(out->evidence_packet_state),
        "evidence-import-packet-recorded-packet-rows-missing");

    out->evidence_import_packet_manifest_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_schema_bound = 1u;
    out->evidence_import_review_gate_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->receipt_replay_results_bound = 1u;
    out->source_digest_receipt_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->reviewer_identity_fixture_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->offline_packet_intake_recorded = 1u;
    out->digest_algorithm_sha256_required = 1u;
    out->immutable_packet_record_required = 1u;
    out->source_url_column_required = 1u;
    out->source_digest_column_required = 1u;
    out->bundle_size_column_required = 1u;
    out->license_column_required = 1u;
    out->storage_path_column_required = 1u;
    out->parameter_set_column_required = 1u;
    out->operation_family_column_required = 1u;
    out->negative_case_column_required = 1u;
    out->replay_transcript_column_required = 1u;
    out->tamper_evidence_column_required = 1u;
    out->reviewer_role_column_required = 1u;
    out->reviewer_identity_column_required = 1u;
    out->disposition_column_required = 1u;
    out->import_timestamp_column_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->fixture_digest_packet_rows_imported = 0u;
    out->receipt_replay_packet_rows_imported = 0u;
    out->source_digest_packet_rows_imported = 0u;
    out->reviewer_role_packet_rows_imported = 0u;
    out->coverage_packet_rows_imported = 0u;
    out->tamper_packet_rows_imported = 0u;
    out->evidence_packet_reviewed = 0u;
    out->evidence_packet_manifest_accepted = 0u;
    out->vector_execution_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->implementation_promotion_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_evidence_packet_items_total = 41u;
    out->required_evidence_packet_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "fixture-digest-replay-source-digest-role-coverage-tamper-packet-rows-review-and-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-evidence-import-packet-manifest-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_evidence_import_packet_manifest_is_no_effect(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->evidence_import_packet_manifest_present == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->evidence_packet_manifest_accepted == 0u &&
           manifest->vector_execution_allowed == 0u &&
           manifest->acvp_submission_allowed == 0u &&
           manifest->operation_execution_allowed == 0u &&
           manifest->implementation_promotion_allowed == 0u &&
           manifest->production_crypto_claim_allowed == 0u &&
           manifest->fips_claim_allowed == 0u &&
           manifest->runtime_authority_granted == 0u &&
           manifest->error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_BLOCKED;
}

int latticra_q_seal_ml_kem_evidence_import_packet_manifest_allows_packet_acceptance(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest) {
    if (manifest == NULL) {
        return 0;
    }

    return manifest->evidence_import_packet_manifest_present == 1u &&
           manifest->fips_203_algorithm_bound == 1u &&
           manifest->acvp_ml_kem_schema_bound == 1u &&
           manifest->evidence_import_review_gate_bound == 1u &&
           manifest->vector_fixture_digest_ledger_bound == 1u &&
           manifest->receipt_replay_results_bound == 1u &&
           manifest->source_digest_receipt_bound == 1u &&
           manifest->source_digest_verification_bound == 1u &&
           manifest->reviewer_identity_fixture_bound == 1u &&
           manifest->reviewer_role_mapping_bound == 1u &&
           manifest->review_disposition_ledger_bound == 1u &&
           manifest->implementation_binding_manifest_bound == 1u &&
           manifest->ci_promotion_evidence_bound == 1u &&
           manifest->clean_room_source_boundary_recorded == 1u &&
           manifest->offline_packet_intake_recorded == 1u &&
           manifest->digest_algorithm_sha256_required == 1u &&
           manifest->immutable_packet_record_required == 1u &&
           manifest->source_url_column_required == 1u &&
           manifest->source_digest_column_required == 1u &&
           manifest->bundle_size_column_required == 1u &&
           manifest->license_column_required == 1u &&
           manifest->storage_path_column_required == 1u &&
           manifest->parameter_set_column_required == 1u &&
           manifest->operation_family_column_required == 1u &&
           manifest->negative_case_column_required == 1u &&
           manifest->replay_transcript_column_required == 1u &&
           manifest->tamper_evidence_column_required == 1u &&
           manifest->reviewer_role_column_required == 1u &&
           manifest->reviewer_identity_column_required == 1u &&
           manifest->disposition_column_required == 1u &&
           manifest->import_timestamp_column_required == 1u &&
           manifest->apple_corecrypto_code_copied == 0u &&
           manifest->external_provider_code_copied == 0u &&
           manifest->fixture_digest_packet_rows_imported == 1u &&
           manifest->receipt_replay_packet_rows_imported == 1u &&
           manifest->source_digest_packet_rows_imported == 1u &&
           manifest->reviewer_role_packet_rows_imported == 1u &&
           manifest->coverage_packet_rows_imported == 1u &&
           manifest->tamper_packet_rows_imported == 1u &&
           manifest->evidence_packet_reviewed == 1u &&
           manifest->evidence_packet_manifest_accepted == 1u &&
           manifest->vector_execution_allowed == 0u &&
           manifest->acvp_submission_allowed == 0u &&
           manifest->operation_execution_allowed == 0u &&
           manifest->implementation_promotion_allowed == 0u &&
           manifest->production_crypto_claim_allowed == 0u &&
           manifest->fips_claim_allowed == 0u &&
           manifest->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
    const latticra_q_seal_ml_kem_evidence_import_packet_manifest_t *manifest,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (manifest == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM EVIDENCE IMPORT PACKET MANIFEST\n"
        "evidence_packet_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "evidence_packet_scope=%s\n"
        "evidence_packet_state=%s\n"
        "evidence_import_packet_manifest_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_schema_bound=%u\n"
        "evidence_import_review_gate_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "receipt_replay_results_bound=%u\n"
        "source_digest_receipt_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "reviewer_identity_fixture_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "offline_packet_intake_recorded=%u\n"
        "digest_algorithm_sha256_required=%u\n"
        "immutable_packet_record_required=%u\n"
        "source_url_column_required=%u\n"
        "source_digest_column_required=%u\n"
        "bundle_size_column_required=%u\n"
        "license_column_required=%u\n"
        "storage_path_column_required=%u\n"
        "parameter_set_column_required=%u\n"
        "operation_family_column_required=%u\n"
        "negative_case_column_required=%u\n"
        "replay_transcript_column_required=%u\n"
        "tamper_evidence_column_required=%u\n"
        "reviewer_role_column_required=%u\n"
        "reviewer_identity_column_required=%u\n"
        "disposition_column_required=%u\n"
        "import_timestamp_column_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "fixture_digest_packet_rows_imported=%u\n"
        "receipt_replay_packet_rows_imported=%u\n"
        "source_digest_packet_rows_imported=%u\n"
        "reviewer_role_packet_rows_imported=%u\n"
        "coverage_packet_rows_imported=%u\n"
        "tamper_packet_rows_imported=%u\n"
        "evidence_packet_reviewed=%u\n"
        "evidence_packet_manifest_accepted=%u\n"
        "vector_execution_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "implementation_promotion_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_evidence_packet_items_total=%u\n"
        "required_evidence_packet_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        manifest->evidence_packet_profile,
        manifest->formal_title,
        manifest->standards_basis,
        manifest->evidence_packet_scope,
        manifest->evidence_packet_state,
        manifest->evidence_import_packet_manifest_present,
        manifest->fips_203_algorithm_bound,
        manifest->acvp_ml_kem_schema_bound,
        manifest->evidence_import_review_gate_bound,
        manifest->vector_fixture_digest_ledger_bound,
        manifest->receipt_replay_results_bound,
        manifest->source_digest_receipt_bound,
        manifest->source_digest_verification_bound,
        manifest->reviewer_identity_fixture_bound,
        manifest->reviewer_role_mapping_bound,
        manifest->review_disposition_ledger_bound,
        manifest->implementation_binding_manifest_bound,
        manifest->ci_promotion_evidence_bound,
        manifest->clean_room_source_boundary_recorded,
        manifest->offline_packet_intake_recorded,
        manifest->digest_algorithm_sha256_required,
        manifest->immutable_packet_record_required,
        manifest->source_url_column_required,
        manifest->source_digest_column_required,
        manifest->bundle_size_column_required,
        manifest->license_column_required,
        manifest->storage_path_column_required,
        manifest->parameter_set_column_required,
        manifest->operation_family_column_required,
        manifest->negative_case_column_required,
        manifest->replay_transcript_column_required,
        manifest->tamper_evidence_column_required,
        manifest->reviewer_role_column_required,
        manifest->reviewer_identity_column_required,
        manifest->disposition_column_required,
        manifest->import_timestamp_column_required,
        manifest->apple_corecrypto_code_copied,
        manifest->external_provider_code_copied,
        manifest->fixture_digest_packet_rows_imported,
        manifest->receipt_replay_packet_rows_imported,
        manifest->source_digest_packet_rows_imported,
        manifest->reviewer_role_packet_rows_imported,
        manifest->coverage_packet_rows_imported,
        manifest->tamper_packet_rows_imported,
        manifest->evidence_packet_reviewed,
        manifest->evidence_packet_manifest_accepted,
        manifest->vector_execution_allowed,
        manifest->acvp_submission_allowed,
        manifest->operation_execution_allowed,
        manifest->implementation_promotion_allowed,
        manifest->production_crypto_claim_allowed,
        manifest->fips_claim_allowed,
        manifest->runtime_authority_granted,
        manifest->required_evidence_packet_items_total,
        manifest->required_evidence_packet_items_satisfied,
        manifest->blocked_reason,
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_error_label(
            manifest->error),
        manifest->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
