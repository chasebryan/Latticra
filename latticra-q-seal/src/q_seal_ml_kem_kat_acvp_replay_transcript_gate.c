#include "latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h"

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
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->replay_transcript_gate_present);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->nist_acvp_ml_kem_bound);
    satisfied += one_if(gate->ssdf_evidence_integrity_bound);
    satisfied += one_if(gate->kat_manifest_bound);
    satisfied += one_if(gate->kat_runner_contract_bound);
    satisfied += one_if(gate->kat_result_schema_bound);
    satisfied += one_if(gate->kat_result_row_fixture_bound);
    satisfied += one_if(gate->acvp_parser_contract_bound);
    satisfied += one_if(gate->acvp_response_contract_bound);
    satisfied += one_if(gate->acvp_submission_package_contract_bound);
    satisfied += one_if(gate->vector_fixture_digest_ledger_bound);
    satisfied += one_if(gate->receipt_replay_results_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->provider_differential_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->deterministic_replay_transcript_schema_recorded);
    satisfied += one_if(gate->transcript_digest_sha256_required);
    satisfied += one_if(gate->transcript_command_fingerprint_required);
    satisfied += one_if(gate->fixture_digest_reference_required);
    satisfied += one_if(gate->implementation_digest_reference_required);
    satisfied += one_if(gate->parameter_set_coverage_required);
    satisfied += one_if(gate->operation_family_coverage_required);
    satisfied += one_if(gate->positive_kat_transcript_lane_recorded);
    satisfied += one_if(gate->negative_kat_transcript_lane_recorded);
    satisfied += one_if(gate->malformed_kat_transcript_lane_recorded);
    satisfied += one_if(gate->implicit_rejection_transcript_lane_recorded);
    satisfied += one_if(gate->acvp_keygen_transcript_lane_recorded);
    satisfied += one_if(gate->acvp_encap_decap_transcript_lane_recorded);
    satisfied += one_if(gate->acvp_decapsulation_val_transcript_lane_recorded);
    satisfied += one_if(gate->acvp_key_check_transcript_lane_recorded);
    satisfied += one_if(gate->provider_differential_transcript_lane_recorded);
    satisfied += one_if(gate->no_secret_material_logging_required);
    satisfied += one_if(gate->offline_only_replay_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->kat_replay_transcripts_recorded);
    satisfied += one_if(gate->acvp_replay_transcripts_recorded);
    satisfied += one_if(gate->transcript_digests_verified);
    satisfied += one_if(gate->ci_replay_transcript_recorded);
    satisfied += one_if(gate->review_disposition_recorded);
    satisfied += one_if(gate->transcript_gate_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_label(
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->transcript_profile,
        sizeof(out->transcript_profile),
        "latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM KAT/ACVP Replay Transcript Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF");
    copy_literal(
        out->transcript_scope,
        sizeof(out->transcript_scope),
        "ML-KEM-KAT-ACVP-replay-transcripts-before-evidence-acceptance");
    copy_literal(
        out->transcript_state,
        sizeof(out->transcript_state),
        "replay-transcript-gate-recorded-transcripts-missing");

    out->replay_transcript_gate_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->nist_acvp_ml_kem_bound = 1u;
    out->ssdf_evidence_integrity_bound = 1u;
    out->kat_manifest_bound = 1u;
    out->kat_runner_contract_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->acvp_submission_package_contract_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->receipt_replay_results_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->provider_differential_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->deterministic_replay_transcript_schema_recorded = 1u;
    out->transcript_digest_sha256_required = 1u;
    out->transcript_command_fingerprint_required = 1u;
    out->fixture_digest_reference_required = 1u;
    out->implementation_digest_reference_required = 1u;
    out->parameter_set_coverage_required = 1u;
    out->operation_family_coverage_required = 1u;
    out->positive_kat_transcript_lane_recorded = 1u;
    out->negative_kat_transcript_lane_recorded = 1u;
    out->malformed_kat_transcript_lane_recorded = 1u;
    out->implicit_rejection_transcript_lane_recorded = 1u;
    out->acvp_keygen_transcript_lane_recorded = 1u;
    out->acvp_encap_decap_transcript_lane_recorded = 1u;
    out->acvp_decapsulation_val_transcript_lane_recorded = 1u;
    out->acvp_key_check_transcript_lane_recorded = 1u;
    out->provider_differential_transcript_lane_recorded = 1u;
    out->no_secret_material_logging_required = 1u;
    out->offline_only_replay_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->kat_replay_transcripts_recorded = 0u;
    out->acvp_replay_transcripts_recorded = 0u;
    out->transcript_digests_verified = 0u;
    out->ci_replay_transcript_recorded = 0u;
    out->review_disposition_recorded = 0u;
    out->transcript_gate_accepted = 0u;
    out->kat_execution_allowed = 0u;
    out->acvp_response_generation_allowed = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_transcript_items_total = 44u;
    out->required_transcript_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "kat-acvp-replay-transcripts-digests-ci-replay-review-and-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-kat-acvp-replay-transcript-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_is_no_effect(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->replay_transcript_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->kat_replay_transcripts_recorded == 0u &&
           gate->acvp_replay_transcripts_recorded == 0u &&
           gate->transcript_digests_verified == 0u &&
           gate->ci_replay_transcript_recorded == 0u &&
           gate->review_disposition_recorded == 0u &&
           gate->transcript_gate_accepted == 0u &&
           gate->kat_execution_allowed == 0u &&
           gate->acvp_response_generation_allowed == 0u &&
           gate->acvp_submission_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_REPLAY_TRANSCRIPT_GATE_BLOCKED;
}

int latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_allows_transcript_acceptance(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->replay_transcript_gate_present == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->nist_acvp_ml_kem_bound == 1u &&
           gate->ssdf_evidence_integrity_bound == 1u &&
           gate->kat_manifest_bound == 1u &&
           gate->kat_runner_contract_bound == 1u &&
           gate->kat_result_schema_bound == 1u &&
           gate->kat_result_row_fixture_bound == 1u &&
           gate->acvp_parser_contract_bound == 1u &&
           gate->acvp_response_contract_bound == 1u &&
           gate->acvp_submission_package_contract_bound == 1u &&
           gate->vector_fixture_digest_ledger_bound == 1u &&
           gate->receipt_replay_results_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->provider_differential_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->deterministic_replay_transcript_schema_recorded == 1u &&
           gate->transcript_digest_sha256_required == 1u &&
           gate->transcript_command_fingerprint_required == 1u &&
           gate->fixture_digest_reference_required == 1u &&
           gate->implementation_digest_reference_required == 1u &&
           gate->parameter_set_coverage_required == 1u &&
           gate->operation_family_coverage_required == 1u &&
           gate->positive_kat_transcript_lane_recorded == 1u &&
           gate->negative_kat_transcript_lane_recorded == 1u &&
           gate->malformed_kat_transcript_lane_recorded == 1u &&
           gate->implicit_rejection_transcript_lane_recorded == 1u &&
           gate->acvp_keygen_transcript_lane_recorded == 1u &&
           gate->acvp_encap_decap_transcript_lane_recorded == 1u &&
           gate->acvp_decapsulation_val_transcript_lane_recorded == 1u &&
           gate->acvp_key_check_transcript_lane_recorded == 1u &&
           gate->provider_differential_transcript_lane_recorded == 1u &&
           gate->no_secret_material_logging_required == 1u &&
           gate->offline_only_replay_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->kat_replay_transcripts_recorded == 1u &&
           gate->acvp_replay_transcripts_recorded == 1u &&
           gate->transcript_digests_verified == 1u &&
           gate->ci_replay_transcript_recorded == 1u &&
           gate->review_disposition_recorded == 1u &&
           gate->transcript_gate_accepted == 1u &&
           gate->kat_execution_allowed == 1u &&
           gate->acvp_response_generation_allowed == 1u &&
           gate->operation_execution_allowed == 1u &&
           gate->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_report(
    const latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM KAT/ACVP REPLAY TRANSCRIPT GATE\n"
        "transcript_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "transcript_scope=%s\n"
        "transcript_state=%s\n"
        "replay_transcript_gate_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "nist_acvp_ml_kem_bound=%u\n"
        "ssdf_evidence_integrity_bound=%u\n"
        "kat_manifest_bound=%u\n"
        "kat_runner_contract_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "acvp_submission_package_contract_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "receipt_replay_results_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "provider_differential_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "deterministic_replay_transcript_schema_recorded=%u\n"
        "transcript_digest_sha256_required=%u\n"
        "transcript_command_fingerprint_required=%u\n"
        "fixture_digest_reference_required=%u\n"
        "implementation_digest_reference_required=%u\n"
        "parameter_set_coverage_required=%u\n"
        "operation_family_coverage_required=%u\n"
        "positive_kat_transcript_lane_recorded=%u\n"
        "negative_kat_transcript_lane_recorded=%u\n"
        "malformed_kat_transcript_lane_recorded=%u\n"
        "implicit_rejection_transcript_lane_recorded=%u\n"
        "acvp_keygen_transcript_lane_recorded=%u\n"
        "acvp_encap_decap_transcript_lane_recorded=%u\n"
        "acvp_decapsulation_val_transcript_lane_recorded=%u\n"
        "acvp_key_check_transcript_lane_recorded=%u\n"
        "provider_differential_transcript_lane_recorded=%u\n"
        "no_secret_material_logging_required=%u\n"
        "offline_only_replay_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "kat_replay_transcripts_recorded=%u\n"
        "acvp_replay_transcripts_recorded=%u\n"
        "transcript_digests_verified=%u\n"
        "ci_replay_transcript_recorded=%u\n"
        "review_disposition_recorded=%u\n"
        "transcript_gate_accepted=%u\n"
        "kat_execution_allowed=%u\n"
        "acvp_response_generation_allowed=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_transcript_items_total=%u\n"
        "required_transcript_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->transcript_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->transcript_scope,
        gate->transcript_state,
        gate->replay_transcript_gate_present,
        gate->fips_203_algorithm_bound,
        gate->nist_acvp_ml_kem_bound,
        gate->ssdf_evidence_integrity_bound,
        gate->kat_manifest_bound,
        gate->kat_runner_contract_bound,
        gate->kat_result_schema_bound,
        gate->kat_result_row_fixture_bound,
        gate->acvp_parser_contract_bound,
        gate->acvp_response_contract_bound,
        gate->acvp_submission_package_contract_bound,
        gate->vector_fixture_digest_ledger_bound,
        gate->receipt_replay_results_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->ci_promotion_evidence_bound,
        gate->provider_differential_bound,
        gate->clean_room_source_boundary_recorded,
        gate->deterministic_replay_transcript_schema_recorded,
        gate->transcript_digest_sha256_required,
        gate->transcript_command_fingerprint_required,
        gate->fixture_digest_reference_required,
        gate->implementation_digest_reference_required,
        gate->parameter_set_coverage_required,
        gate->operation_family_coverage_required,
        gate->positive_kat_transcript_lane_recorded,
        gate->negative_kat_transcript_lane_recorded,
        gate->malformed_kat_transcript_lane_recorded,
        gate->implicit_rejection_transcript_lane_recorded,
        gate->acvp_keygen_transcript_lane_recorded,
        gate->acvp_encap_decap_transcript_lane_recorded,
        gate->acvp_decapsulation_val_transcript_lane_recorded,
        gate->acvp_key_check_transcript_lane_recorded,
        gate->provider_differential_transcript_lane_recorded,
        gate->no_secret_material_logging_required,
        gate->offline_only_replay_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->kat_replay_transcripts_recorded,
        gate->acvp_replay_transcripts_recorded,
        gate->transcript_digests_verified,
        gate->ci_replay_transcript_recorded,
        gate->review_disposition_recorded,
        gate->transcript_gate_accepted,
        gate->kat_execution_allowed,
        gate->acvp_response_generation_allowed,
        gate->acvp_submission_allowed,
        gate->operation_execution_allowed,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->required_transcript_items_total,
        gate->required_transcript_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
