#include "latticra/q_seal_ml_kem_acvp_verdict_receipt_gate.h"

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
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->acvp_verdict_receipt_gate_present);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->acvp_ml_kem_protocol_bound);
    satisfied += one_if(gate->acvp_submission_package_contract_bound);
    satisfied += one_if(gate->replay_transcript_gate_bound);
    satisfied += one_if(gate->acvp_response_contract_bound);
    satisfied += one_if(gate->acvp_response_fixture_bound);
    satisfied += one_if(gate->acvp_parser_contract_bound);
    satisfied += one_if(gate->acvp_capability_matrix_bound);
    satisfied += one_if(gate->vector_fixture_digest_ledger_bound);
    satisfied += one_if(gate->implementation_binding_manifest_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_identity_fixture_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->offline_verdict_receipt_policy_recorded);
    satisfied += one_if(gate->validation_server_receipt_required);
    satisfied += one_if(gate->acvp_session_identifier_required);
    satisfied += one_if(gate->vsid_tgid_tcid_verdict_mapping_required);
    satisfied += one_if(gate->algorithm_revision_required);
    satisfied += one_if(gate->parameter_set_verdicts_required);
    satisfied += one_if(gate->operation_verdicts_required);
    satisfied += one_if(gate->pass_fail_verdict_required);
    satisfied += one_if(gate->server_response_digest_required);
    satisfied += one_if(gate->receipt_digest_sha256_required);
    satisfied += one_if(gate->certificate_or_validation_record_required);
    satisfied += one_if(gate->validation_date_required);
    satisfied += one_if(gate->lab_or_server_identity_required);
    satisfied += one_if(gate->no_secret_material_logging_required);
    satisfied += one_if(gate->offline_only_intake_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->submission_receipt_bound);
    satisfied += one_if(gate->validation_server_acceptance_bound);
    satisfied += one_if(gate->pass_verdict_recorded);
    satisfied += one_if(gate->certificate_identifier_recorded);
    satisfied += one_if(gate->receipt_digest_verified);
    satisfied += one_if(gate->reviewer_disposition_recorded);
    satisfied += one_if(gate->acvp_verdict_receipt_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_label(
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->verdict_receipt_profile,
        sizeof(out->verdict_receipt_profile),
        "latticra-q-seal-ml-kem-acvp-verdict-receipt-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Verdict Receipt Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF");
    copy_literal(
        out->verdict_receipt_scope,
        sizeof(out->verdict_receipt_scope),
        "ML-KEM-ACVP-validation-server-verdicts-before-validation-claims");
    copy_literal(
        out->verdict_receipt_state,
        sizeof(out->verdict_receipt_state),
        "acvp-verdict-receipt-gate-recorded-verdict-missing");

    out->acvp_verdict_receipt_gate_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_protocol_bound = 1u;
    out->acvp_submission_package_contract_bound = 1u;
    out->replay_transcript_gate_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->acvp_response_fixture_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_identity_fixture_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->offline_verdict_receipt_policy_recorded = 1u;
    out->validation_server_receipt_required = 1u;
    out->acvp_session_identifier_required = 1u;
    out->vsid_tgid_tcid_verdict_mapping_required = 1u;
    out->algorithm_revision_required = 1u;
    out->parameter_set_verdicts_required = 1u;
    out->operation_verdicts_required = 1u;
    out->pass_fail_verdict_required = 1u;
    out->server_response_digest_required = 1u;
    out->receipt_digest_sha256_required = 1u;
    out->certificate_or_validation_record_required = 1u;
    out->validation_date_required = 1u;
    out->lab_or_server_identity_required = 1u;
    out->no_secret_material_logging_required = 1u;
    out->offline_only_intake_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->submission_receipt_bound = 0u;
    out->validation_server_acceptance_bound = 0u;
    out->pass_verdict_recorded = 0u;
    out->certificate_identifier_recorded = 0u;
    out->receipt_digest_verified = 0u;
    out->reviewer_disposition_recorded = 0u;
    out->acvp_verdict_receipt_accepted = 0u;
    out->network_session_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_verdict_receipt_items_total = 39u;
    out->required_verdict_receipt_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "acvp-verdict-receipt-server-acceptance-pass-record-certificate-digest-review-and-acceptance-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-acvp-verdict-receipt-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->acvp_verdict_receipt_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->submission_receipt_bound == 0u &&
           gate->validation_server_acceptance_bound == 0u &&
           gate->pass_verdict_recorded == 0u &&
           gate->certificate_identifier_recorded == 0u &&
           gate->receipt_digest_verified == 0u &&
           gate->reviewer_disposition_recorded == 0u &&
           gate->acvp_verdict_receipt_accepted == 0u &&
           gate->network_session_enabled == 0u &&
           gate->acvp_submission_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_VERDICT_RECEIPT_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_allows_verdict_acceptance(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->acvp_verdict_receipt_gate_present == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->acvp_ml_kem_protocol_bound == 1u &&
           gate->acvp_submission_package_contract_bound == 1u &&
           gate->replay_transcript_gate_bound == 1u &&
           gate->acvp_response_contract_bound == 1u &&
           gate->acvp_response_fixture_bound == 1u &&
           gate->acvp_parser_contract_bound == 1u &&
           gate->acvp_capability_matrix_bound == 1u &&
           gate->vector_fixture_digest_ledger_bound == 1u &&
           gate->implementation_binding_manifest_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_identity_fixture_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->offline_verdict_receipt_policy_recorded == 1u &&
           gate->validation_server_receipt_required == 1u &&
           gate->acvp_session_identifier_required == 1u &&
           gate->vsid_tgid_tcid_verdict_mapping_required == 1u &&
           gate->algorithm_revision_required == 1u &&
           gate->parameter_set_verdicts_required == 1u &&
           gate->operation_verdicts_required == 1u &&
           gate->pass_fail_verdict_required == 1u &&
           gate->server_response_digest_required == 1u &&
           gate->receipt_digest_sha256_required == 1u &&
           gate->certificate_or_validation_record_required == 1u &&
           gate->validation_date_required == 1u &&
           gate->lab_or_server_identity_required == 1u &&
           gate->no_secret_material_logging_required == 1u &&
           gate->offline_only_intake_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->submission_receipt_bound == 1u &&
           gate->validation_server_acceptance_bound == 1u &&
           gate->pass_verdict_recorded == 1u &&
           gate->certificate_identifier_recorded == 1u &&
           gate->receipt_digest_verified == 1u &&
           gate->reviewer_disposition_recorded == 1u &&
           gate->acvp_verdict_receipt_accepted == 1u &&
           gate->network_session_enabled == 0u &&
           gate->acvp_submission_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_report(
    const latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP VERDICT RECEIPT GATE\n"
        "verdict_receipt_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "verdict_receipt_scope=%s\n"
        "verdict_receipt_state=%s\n"
        "acvp_verdict_receipt_gate_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_protocol_bound=%u\n"
        "acvp_submission_package_contract_bound=%u\n"
        "replay_transcript_gate_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "acvp_response_fixture_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_identity_fixture_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "offline_verdict_receipt_policy_recorded=%u\n"
        "validation_server_receipt_required=%u\n"
        "acvp_session_identifier_required=%u\n"
        "vsid_tgid_tcid_verdict_mapping_required=%u\n"
        "algorithm_revision_required=%u\n"
        "parameter_set_verdicts_required=%u\n"
        "operation_verdicts_required=%u\n"
        "pass_fail_verdict_required=%u\n"
        "server_response_digest_required=%u\n"
        "receipt_digest_sha256_required=%u\n"
        "certificate_or_validation_record_required=%u\n"
        "validation_date_required=%u\n"
        "lab_or_server_identity_required=%u\n"
        "no_secret_material_logging_required=%u\n"
        "offline_only_intake_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "submission_receipt_bound=%u\n"
        "validation_server_acceptance_bound=%u\n"
        "pass_verdict_recorded=%u\n"
        "certificate_identifier_recorded=%u\n"
        "receipt_digest_verified=%u\n"
        "reviewer_disposition_recorded=%u\n"
        "acvp_verdict_receipt_accepted=%u\n"
        "network_session_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_verdict_receipt_items_total=%u\n"
        "required_verdict_receipt_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->verdict_receipt_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->verdict_receipt_scope,
        gate->verdict_receipt_state,
        gate->acvp_verdict_receipt_gate_present,
        gate->fips_203_algorithm_bound,
        gate->acvp_ml_kem_protocol_bound,
        gate->acvp_submission_package_contract_bound,
        gate->replay_transcript_gate_bound,
        gate->acvp_response_contract_bound,
        gate->acvp_response_fixture_bound,
        gate->acvp_parser_contract_bound,
        gate->acvp_capability_matrix_bound,
        gate->vector_fixture_digest_ledger_bound,
        gate->implementation_binding_manifest_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_identity_fixture_bound,
        gate->reviewer_role_mapping_bound,
        gate->clean_room_source_boundary_recorded,
        gate->offline_verdict_receipt_policy_recorded,
        gate->validation_server_receipt_required,
        gate->acvp_session_identifier_required,
        gate->vsid_tgid_tcid_verdict_mapping_required,
        gate->algorithm_revision_required,
        gate->parameter_set_verdicts_required,
        gate->operation_verdicts_required,
        gate->pass_fail_verdict_required,
        gate->server_response_digest_required,
        gate->receipt_digest_sha256_required,
        gate->certificate_or_validation_record_required,
        gate->validation_date_required,
        gate->lab_or_server_identity_required,
        gate->no_secret_material_logging_required,
        gate->offline_only_intake_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->submission_receipt_bound,
        gate->validation_server_acceptance_bound,
        gate->pass_verdict_recorded,
        gate->certificate_identifier_recorded,
        gate->receipt_digest_verified,
        gate->reviewer_disposition_recorded,
        gate->acvp_verdict_receipt_accepted,
        gate->network_session_enabled,
        gate->acvp_submission_allowed,
        gate->operation_execution_allowed,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->runtime_authority_granted,
        gate->required_verdict_receipt_items_total,
        gate->required_verdict_receipt_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
