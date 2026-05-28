#include "latticra/q_seal_ml_kem_acvp_submission_package_contract.h"

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
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract) {
    unsigned satisfied = 0u;

    satisfied += one_if(contract->acvp_submission_package_contract_present);
    satisfied += one_if(contract->fips_203_algorithm_bound);
    satisfied += one_if(contract->acvp_ml_kem_json_bound);
    satisfied += one_if(contract->acvp_intake_bound);
    satisfied += one_if(contract->acvp_capability_matrix_bound);
    satisfied += one_if(contract->acvp_fixture_row_plan_bound);
    satisfied += one_if(contract->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(contract->acvp_parser_contract_bound);
    satisfied += one_if(contract->acvp_response_contract_bound);
    satisfied += one_if(contract->acvp_response_fixture_bound);
    satisfied += one_if(contract->kat_result_schema_bound);
    satisfied += one_if(contract->kat_result_row_fixture_bound);
    satisfied += one_if(contract->vector_schema_bound);
    satisfied += one_if(contract->vector_fixture_digest_ledger_bound);
    satisfied += one_if(contract->negative_test_evidence_bound);
    satisfied += one_if(contract->implementation_binding_manifest_bound);
    satisfied += one_if(contract->ci_promotion_evidence_bound);
    satisfied += one_if(contract->clean_room_source_boundary_recorded);
    satisfied += one_if(contract->submission_package_policy_recorded);
    satisfied += one_if(contract->offline_package_manifest_required);
    satisfied += one_if(contract->algorithm_registration_required);
    satisfied += one_if(contract->acvp_session_metadata_required);
    satisfied += one_if(contract->vsid_tgid_tcid_traceability_required);
    satisfied += one_if(contract->request_bundle_digest_required);
    satisfied += one_if(contract->response_bundle_digest_required);
    satisfied += one_if(contract->canonical_response_json_required);
    satisfied += one_if(contract->local_replay_transcript_required);
    satisfied += one_if(contract->no_secret_material_logging_required);
    satisfied += one_if(contract->no_network_submission_required);
    satisfied += one_if(contract->no_dynamic_code_loading_required);
    satisfied += one_if(contract->submission_package_reviewed);
    satisfied += one_if(contract->request_bundle_digest_bound);
    satisfied += one_if(contract->response_bundle_digest_bound);
    satisfied += one_if(contract->vector_execution_evidence_recorded);
    satisfied += one_if(contract->response_output_accepted);
    satisfied += one_if(contract->local_replay_transcript_recorded);
    satisfied += one_if(contract->acvp_client_boundary_reviewed);
    satisfied += one_if(contract->submission_receipt_recorded);
    satisfied += one_if(contract->validation_server_acceptance_recorded);
    satisfied += one_if(contract->acvp_submission_package_accepted);
    satisfied += one_if(contract->acvp_response_acceptance_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_submission_package_error_label(
    latticra_q_seal_ml_kem_acvp_submission_package_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(
    latticra_q_seal_ml_kem_acvp_submission_package_contract_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->submission_package_profile,
        sizeof(out->submission_package_profile),
        "latticra-q-seal-ml-kem-acvp-submission-package-contract/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Submission Package Contract");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->submission_package_scope,
        sizeof(out->submission_package_scope),
        "ML-KEM-ACVP-submission-package-before-network-submission");
    copy_literal(
        out->submission_package_state,
        sizeof(out->submission_package_state),
        "acvp-submission-package-contract-recorded-package-acceptance-missing");

    out->acvp_submission_package_contract_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_intake_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->acvp_response_fixture_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->submission_package_policy_recorded = 1u;
    out->offline_package_manifest_required = 1u;
    out->algorithm_registration_required = 1u;
    out->acvp_session_metadata_required = 1u;
    out->vsid_tgid_tcid_traceability_required = 1u;
    out->request_bundle_digest_required = 1u;
    out->response_bundle_digest_required = 1u;
    out->canonical_response_json_required = 1u;
    out->local_replay_transcript_required = 1u;
    out->no_secret_material_logging_required = 1u;
    out->no_network_submission_required = 1u;
    out->no_dynamic_code_loading_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->submission_package_reviewed = 0u;
    out->request_bundle_digest_bound = 0u;
    out->response_bundle_digest_bound = 0u;
    out->vector_execution_evidence_recorded = 0u;
    out->response_output_accepted = 0u;
    out->local_replay_transcript_recorded = 0u;
    out->acvp_client_boundary_reviewed = 0u;
    out->submission_receipt_recorded = 0u;
    out->validation_server_acceptance_recorded = 0u;
    out->acvp_submission_package_accepted = 0u;
    out->acvp_response_acceptance_recorded = 0u;
    out->response_json_generation_enabled = 0u;
    out->network_session_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_submission_package_items_total = 41u;
    out->required_submission_package_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "submission-package-review-digests-replay-transcript-client-boundary-receipt-and-acceptance-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-acvp-submission-package-contract-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_submission_package_contract_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_submission_package_contract_present == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->submission_package_reviewed == 0u &&
           contract->request_bundle_digest_bound == 0u &&
           contract->response_bundle_digest_bound == 0u &&
           contract->response_output_accepted == 0u &&
           contract->network_session_enabled == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u &&
           contract->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_SUBMISSION_PACKAGE_BLOCKED;
}

int
latticra_q_seal_ml_kem_acvp_submission_package_contract_allows_package_acceptance(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract) {
    if (contract == NULL) {
        return 0;
    }

    return contract->acvp_submission_package_contract_present == 1u &&
           contract->fips_203_algorithm_bound == 1u &&
           contract->acvp_ml_kem_json_bound == 1u &&
           contract->acvp_intake_bound == 1u &&
           contract->acvp_capability_matrix_bound == 1u &&
           contract->acvp_fixture_row_plan_bound == 1u &&
           contract->acvp_fixture_digest_row_template_bound == 1u &&
           contract->acvp_parser_contract_bound == 1u &&
           contract->acvp_response_contract_bound == 1u &&
           contract->acvp_response_fixture_bound == 1u &&
           contract->kat_result_schema_bound == 1u &&
           contract->kat_result_row_fixture_bound == 1u &&
           contract->vector_schema_bound == 1u &&
           contract->vector_fixture_digest_ledger_bound == 1u &&
           contract->negative_test_evidence_bound == 1u &&
           contract->implementation_binding_manifest_bound == 1u &&
           contract->ci_promotion_evidence_bound == 1u &&
           contract->clean_room_source_boundary_recorded == 1u &&
           contract->submission_package_policy_recorded == 1u &&
           contract->offline_package_manifest_required == 1u &&
           contract->algorithm_registration_required == 1u &&
           contract->acvp_session_metadata_required == 1u &&
           contract->vsid_tgid_tcid_traceability_required == 1u &&
           contract->request_bundle_digest_required == 1u &&
           contract->response_bundle_digest_required == 1u &&
           contract->canonical_response_json_required == 1u &&
           contract->local_replay_transcript_required == 1u &&
           contract->no_secret_material_logging_required == 1u &&
           contract->no_network_submission_required == 1u &&
           contract->no_dynamic_code_loading_required == 1u &&
           contract->apple_corecrypto_code_copied == 0u &&
           contract->external_provider_code_copied == 0u &&
           contract->submission_package_reviewed == 1u &&
           contract->request_bundle_digest_bound == 1u &&
           contract->response_bundle_digest_bound == 1u &&
           contract->vector_execution_evidence_recorded == 1u &&
           contract->response_output_accepted == 1u &&
           contract->local_replay_transcript_recorded == 1u &&
           contract->acvp_client_boundary_reviewed == 1u &&
           contract->submission_receipt_recorded == 1u &&
           contract->validation_server_acceptance_recorded == 1u &&
           contract->acvp_submission_package_accepted == 1u &&
           contract->acvp_response_acceptance_recorded == 1u &&
           contract->response_json_generation_enabled == 0u &&
           contract->network_session_enabled == 0u &&
           contract->acvp_submission_allowed == 0u &&
           contract->operation_execution_allowed == 0u &&
           contract->production_crypto_claim_allowed == 0u &&
           contract->fips_claim_allowed == 0u &&
           contract->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t
latticra_q_seal_ml_kem_acvp_submission_package_contract_report(
    const latticra_q_seal_ml_kem_acvp_submission_package_contract_t *contract,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (contract == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP SUBMISSION PACKAGE CONTRACT\n"
        "submission_package_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "submission_package_scope=%s\n"
        "submission_package_state=%s\n"
        "acvp_submission_package_contract_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_intake_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "acvp_response_fixture_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "submission_package_policy_recorded=%u\n"
        "offline_package_manifest_required=%u\n"
        "algorithm_registration_required=%u\n"
        "acvp_session_metadata_required=%u\n"
        "vsid_tgid_tcid_traceability_required=%u\n"
        "request_bundle_digest_required=%u\n"
        "response_bundle_digest_required=%u\n"
        "canonical_response_json_required=%u\n"
        "local_replay_transcript_required=%u\n"
        "no_secret_material_logging_required=%u\n"
        "no_network_submission_required=%u\n"
        "no_dynamic_code_loading_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "submission_package_reviewed=%u\n"
        "request_bundle_digest_bound=%u\n"
        "response_bundle_digest_bound=%u\n"
        "vector_execution_evidence_recorded=%u\n"
        "response_output_accepted=%u\n"
        "local_replay_transcript_recorded=%u\n"
        "acvp_client_boundary_reviewed=%u\n"
        "submission_receipt_recorded=%u\n"
        "validation_server_acceptance_recorded=%u\n"
        "acvp_submission_package_accepted=%u\n"
        "acvp_response_acceptance_recorded=%u\n"
        "response_json_generation_enabled=%u\n"
        "network_session_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_submission_package_items_total=%u\n"
        "required_submission_package_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        contract->submission_package_profile,
        contract->formal_title,
        contract->standards_basis,
        contract->submission_package_scope,
        contract->submission_package_state,
        contract->acvp_submission_package_contract_present,
        contract->fips_203_algorithm_bound,
        contract->acvp_ml_kem_json_bound,
        contract->acvp_intake_bound,
        contract->acvp_capability_matrix_bound,
        contract->acvp_fixture_row_plan_bound,
        contract->acvp_fixture_digest_row_template_bound,
        contract->acvp_parser_contract_bound,
        contract->acvp_response_contract_bound,
        contract->acvp_response_fixture_bound,
        contract->kat_result_schema_bound,
        contract->kat_result_row_fixture_bound,
        contract->vector_schema_bound,
        contract->vector_fixture_digest_ledger_bound,
        contract->negative_test_evidence_bound,
        contract->implementation_binding_manifest_bound,
        contract->ci_promotion_evidence_bound,
        contract->clean_room_source_boundary_recorded,
        contract->submission_package_policy_recorded,
        contract->offline_package_manifest_required,
        contract->algorithm_registration_required,
        contract->acvp_session_metadata_required,
        contract->vsid_tgid_tcid_traceability_required,
        contract->request_bundle_digest_required,
        contract->response_bundle_digest_required,
        contract->canonical_response_json_required,
        contract->local_replay_transcript_required,
        contract->no_secret_material_logging_required,
        contract->no_network_submission_required,
        contract->no_dynamic_code_loading_required,
        contract->apple_corecrypto_code_copied,
        contract->external_provider_code_copied,
        contract->submission_package_reviewed,
        contract->request_bundle_digest_bound,
        contract->response_bundle_digest_bound,
        contract->vector_execution_evidence_recorded,
        contract->response_output_accepted,
        contract->local_replay_transcript_recorded,
        contract->acvp_client_boundary_reviewed,
        contract->submission_receipt_recorded,
        contract->validation_server_acceptance_recorded,
        contract->acvp_submission_package_accepted,
        contract->acvp_response_acceptance_recorded,
        contract->response_json_generation_enabled,
        contract->network_session_enabled,
        contract->acvp_submission_allowed,
        contract->operation_execution_allowed,
        contract->production_crypto_claim_allowed,
        contract->fips_claim_allowed,
        contract->runtime_authority_granted,
        contract->required_submission_package_items_total,
        contract->required_submission_package_items_satisfied,
        contract->blocked_reason,
        latticra_q_seal_ml_kem_acvp_submission_package_error_label(contract->error),
        contract->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
