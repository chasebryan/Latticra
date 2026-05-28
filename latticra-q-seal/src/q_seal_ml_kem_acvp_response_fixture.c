#include "latticra/q_seal_ml_kem_acvp_response_fixture.h"

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
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture) {
    unsigned satisfied = 0u;

    satisfied += one_if(fixture->acvp_response_fixture_present);
    satisfied += one_if(fixture->fips_203_algorithm_bound);
    satisfied += one_if(fixture->acvp_ml_kem_json_bound);
    satisfied += one_if(fixture->acvp_intake_bound);
    satisfied += one_if(fixture->acvp_capability_matrix_bound);
    satisfied += one_if(fixture->acvp_fixture_row_plan_bound);
    satisfied += one_if(fixture->acvp_fixture_digest_row_template_bound);
    satisfied += one_if(fixture->acvp_parser_contract_bound);
    satisfied += one_if(fixture->acvp_response_contract_bound);
    satisfied += one_if(fixture->kat_result_schema_bound);
    satisfied += one_if(fixture->kat_result_row_fixture_bound);
    satisfied += one_if(fixture->vector_schema_bound);
    satisfied += one_if(fixture->vector_fixture_digest_ledger_bound);
    satisfied += one_if(fixture->negative_test_evidence_bound);
    satisfied += one_if(fixture->implementation_binding_manifest_bound);
    satisfied += one_if(fixture->ci_promotion_evidence_bound);
    satisfied += one_if(fixture->clean_room_source_boundary_recorded);
    satisfied += one_if(fixture->response_fixture_policy_recorded);
    satisfied += one_if(fixture->response_envelope_policy_recorded);
    satisfied += one_if(fixture->acv_version_echo_required);
    satisfied += one_if(fixture->vsid_echo_required);
    satisfied += one_if(fixture->tgid_tcid_mapping_required);
    satisfied += one_if(fixture->deterministic_ordering_required);
    satisfied += one_if(fixture->keygen_response_fixture_required);
    satisfied += one_if(fixture->encapsulation_response_fixture_required);
    satisfied += one_if(fixture->decapsulation_response_fixture_required);
    satisfied += one_if(fixture->key_check_response_fixture_required);
    satisfied += one_if(fixture->canonical_hex_output_required);
    satisfied += one_if(fixture->boolean_output_policy_recorded);
    satisfied += one_if(fixture->no_secret_material_logging_required);
    satisfied += one_if(fixture->no_network_submission_required);
    satisfied += one_if(fixture->no_dynamic_code_loading_required);
    satisfied += one_if(fixture->response_fixture_reviewed);
    satisfied += one_if(fixture->fixture_bundle_digest_bound);
    satisfied += one_if(fixture->parser_output_accepted);
    satisfied += one_if(fixture->vector_execution_evidence_recorded);
    satisfied += one_if(fixture->keygen_response_fixture_recorded);
    satisfied += one_if(fixture->encapsulation_response_fixture_recorded);
    satisfied += one_if(fixture->decapsulation_response_fixture_recorded);
    satisfied += one_if(fixture->key_check_response_fixture_recorded);
    satisfied += one_if(fixture->negative_response_fixture_recorded);
    satisfied += one_if(fixture->response_schema_reviewed);
    satisfied += one_if(fixture->response_security_reviewed);
    satisfied += one_if(fixture->response_ci_replay_recorded);
    satisfied += one_if(fixture->response_output_accepted);
    satisfied += one_if(fixture->acvp_response_generation_evidence_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_acvp_response_fixture_error_label(
    latticra_q_seal_ml_kem_acvp_response_fixture_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_fixture_prepare(
    latticra_q_seal_ml_kem_acvp_response_fixture_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->response_fixture_profile,
        sizeof(out->response_fixture_profile),
        "latticra-q-seal-ml-kem-acvp-response-fixture/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM ACVP Response Fixture");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203-and-NIST-ACVP-ML-KEM");
    copy_literal(
        out->response_fixture_scope,
        sizeof(out->response_fixture_scope),
        "ML-KEM-ACVP-response-fixture-before-response-output-acceptance");
    copy_literal(
        out->response_fixture_state,
        sizeof(out->response_fixture_state),
        "acvp-response-fixture-recorded-response-output-missing");

    out->acvp_response_fixture_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_json_bound = 1u;
    out->acvp_intake_bound = 1u;
    out->acvp_capability_matrix_bound = 1u;
    out->acvp_fixture_row_plan_bound = 1u;
    out->acvp_fixture_digest_row_template_bound = 1u;
    out->acvp_parser_contract_bound = 1u;
    out->acvp_response_contract_bound = 1u;
    out->kat_result_schema_bound = 1u;
    out->kat_result_row_fixture_bound = 1u;
    out->vector_schema_bound = 1u;
    out->vector_fixture_digest_ledger_bound = 1u;
    out->negative_test_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->response_fixture_policy_recorded = 1u;
    out->response_envelope_policy_recorded = 1u;
    out->acv_version_echo_required = 1u;
    out->vsid_echo_required = 1u;
    out->tgid_tcid_mapping_required = 1u;
    out->deterministic_ordering_required = 1u;
    out->keygen_response_fixture_required = 1u;
    out->encapsulation_response_fixture_required = 1u;
    out->decapsulation_response_fixture_required = 1u;
    out->key_check_response_fixture_required = 1u;
    out->canonical_hex_output_required = 1u;
    out->boolean_output_policy_recorded = 1u;
    out->no_secret_material_logging_required = 1u;
    out->no_network_submission_required = 1u;
    out->no_dynamic_code_loading_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->response_fixture_reviewed = 0u;
    out->fixture_bundle_digest_bound = 0u;
    out->parser_output_accepted = 0u;
    out->vector_execution_evidence_recorded = 0u;
    out->keygen_response_fixture_recorded = 0u;
    out->encapsulation_response_fixture_recorded = 0u;
    out->decapsulation_response_fixture_recorded = 0u;
    out->key_check_response_fixture_recorded = 0u;
    out->negative_response_fixture_recorded = 0u;
    out->response_schema_reviewed = 0u;
    out->response_security_reviewed = 0u;
    out->response_ci_replay_recorded = 0u;
    out->response_output_accepted = 0u;
    out->acvp_response_generation_evidence_recorded = 0u;
    out->response_json_generation_enabled = 0u;
    out->acvp_submission_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_response_fixture_items_total = 46u;
    out->required_response_fixture_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "response-fixture-review-digest-parser-vector-row-security-ci-output-and-generation-evidence-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-acvp-response-fixture-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_acvp_response_fixture_is_no_effect(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->acvp_response_fixture_present == 1u &&
           fixture->clean_room_source_boundary_recorded == 1u &&
           fixture->apple_corecrypto_code_copied == 0u &&
           fixture->external_provider_code_copied == 0u &&
           fixture->response_fixture_reviewed == 0u &&
           fixture->parser_output_accepted == 0u &&
           fixture->vector_execution_evidence_recorded == 0u &&
           fixture->response_output_accepted == 0u &&
           fixture->response_json_generation_enabled == 0u &&
           fixture->acvp_submission_allowed == 0u &&
           fixture->operation_execution_allowed == 0u &&
           fixture->production_crypto_claim_allowed == 0u &&
           fixture->fips_claim_allowed == 0u &&
           fixture->runtime_authority_granted == 0u &&
           fixture->error == LATTICRA_Q_SEAL_ML_KEM_ACVP_RESPONSE_FIXTURE_BLOCKED;
}

int latticra_q_seal_ml_kem_acvp_response_fixture_allows_response_output(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->acvp_response_fixture_present == 1u &&
           fixture->fips_203_algorithm_bound == 1u &&
           fixture->acvp_ml_kem_json_bound == 1u &&
           fixture->acvp_intake_bound == 1u &&
           fixture->acvp_capability_matrix_bound == 1u &&
           fixture->acvp_fixture_row_plan_bound == 1u &&
           fixture->acvp_fixture_digest_row_template_bound == 1u &&
           fixture->acvp_parser_contract_bound == 1u &&
           fixture->acvp_response_contract_bound == 1u &&
           fixture->kat_result_schema_bound == 1u &&
           fixture->kat_result_row_fixture_bound == 1u &&
           fixture->vector_schema_bound == 1u &&
           fixture->vector_fixture_digest_ledger_bound == 1u &&
           fixture->negative_test_evidence_bound == 1u &&
           fixture->implementation_binding_manifest_bound == 1u &&
           fixture->ci_promotion_evidence_bound == 1u &&
           fixture->clean_room_source_boundary_recorded == 1u &&
           fixture->response_fixture_policy_recorded == 1u &&
           fixture->response_envelope_policy_recorded == 1u &&
           fixture->acv_version_echo_required == 1u &&
           fixture->vsid_echo_required == 1u &&
           fixture->tgid_tcid_mapping_required == 1u &&
           fixture->deterministic_ordering_required == 1u &&
           fixture->keygen_response_fixture_required == 1u &&
           fixture->encapsulation_response_fixture_required == 1u &&
           fixture->decapsulation_response_fixture_required == 1u &&
           fixture->key_check_response_fixture_required == 1u &&
           fixture->canonical_hex_output_required == 1u &&
           fixture->boolean_output_policy_recorded == 1u &&
           fixture->no_secret_material_logging_required == 1u &&
           fixture->no_network_submission_required == 1u &&
           fixture->no_dynamic_code_loading_required == 1u &&
           fixture->apple_corecrypto_code_copied == 0u &&
           fixture->external_provider_code_copied == 0u &&
           fixture->response_fixture_reviewed == 1u &&
           fixture->fixture_bundle_digest_bound == 1u &&
           fixture->parser_output_accepted == 1u &&
           fixture->vector_execution_evidence_recorded == 1u &&
           fixture->keygen_response_fixture_recorded == 1u &&
           fixture->encapsulation_response_fixture_recorded == 1u &&
           fixture->decapsulation_response_fixture_recorded == 1u &&
           fixture->key_check_response_fixture_recorded == 1u &&
           fixture->negative_response_fixture_recorded == 1u &&
           fixture->response_schema_reviewed == 1u &&
           fixture->response_security_reviewed == 1u &&
           fixture->response_ci_replay_recorded == 1u &&
           fixture->response_output_accepted == 1u &&
           fixture->acvp_response_generation_evidence_recorded == 1u &&
           fixture->response_json_generation_enabled == 1u &&
           fixture->acvp_submission_allowed == 0u &&
           fixture->operation_execution_allowed == 0u &&
           fixture->production_crypto_claim_allowed == 0u &&
           fixture->fips_claim_allowed == 0u &&
           fixture->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_acvp_response_fixture_report(
    const latticra_q_seal_ml_kem_acvp_response_fixture_t *fixture,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (fixture == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM ACVP RESPONSE FIXTURE\n"
        "response_fixture_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "response_fixture_scope=%s\n"
        "response_fixture_state=%s\n"
        "acvp_response_fixture_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_json_bound=%u\n"
        "acvp_intake_bound=%u\n"
        "acvp_capability_matrix_bound=%u\n"
        "acvp_fixture_row_plan_bound=%u\n"
        "acvp_fixture_digest_row_template_bound=%u\n"
        "acvp_parser_contract_bound=%u\n"
        "acvp_response_contract_bound=%u\n"
        "kat_result_schema_bound=%u\n"
        "kat_result_row_fixture_bound=%u\n"
        "vector_schema_bound=%u\n"
        "vector_fixture_digest_ledger_bound=%u\n"
        "negative_test_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "response_fixture_policy_recorded=%u\n"
        "response_envelope_policy_recorded=%u\n"
        "acv_version_echo_required=%u\n"
        "vsid_echo_required=%u\n"
        "tgid_tcid_mapping_required=%u\n"
        "deterministic_ordering_required=%u\n"
        "keygen_response_fixture_required=%u\n"
        "encapsulation_response_fixture_required=%u\n"
        "decapsulation_response_fixture_required=%u\n"
        "key_check_response_fixture_required=%u\n"
        "canonical_hex_output_required=%u\n"
        "boolean_output_policy_recorded=%u\n"
        "no_secret_material_logging_required=%u\n"
        "no_network_submission_required=%u\n"
        "no_dynamic_code_loading_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "response_fixture_reviewed=%u\n"
        "fixture_bundle_digest_bound=%u\n"
        "parser_output_accepted=%u\n"
        "vector_execution_evidence_recorded=%u\n"
        "keygen_response_fixture_recorded=%u\n"
        "encapsulation_response_fixture_recorded=%u\n"
        "decapsulation_response_fixture_recorded=%u\n"
        "key_check_response_fixture_recorded=%u\n"
        "negative_response_fixture_recorded=%u\n"
        "response_schema_reviewed=%u\n"
        "response_security_reviewed=%u\n"
        "response_ci_replay_recorded=%u\n"
        "response_output_accepted=%u\n"
        "acvp_response_generation_evidence_recorded=%u\n"
        "response_json_generation_enabled=%u\n"
        "acvp_submission_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_response_fixture_items_total=%u\n"
        "required_response_fixture_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        fixture->response_fixture_profile,
        fixture->formal_title,
        fixture->standards_basis,
        fixture->response_fixture_scope,
        fixture->response_fixture_state,
        fixture->acvp_response_fixture_present,
        fixture->fips_203_algorithm_bound,
        fixture->acvp_ml_kem_json_bound,
        fixture->acvp_intake_bound,
        fixture->acvp_capability_matrix_bound,
        fixture->acvp_fixture_row_plan_bound,
        fixture->acvp_fixture_digest_row_template_bound,
        fixture->acvp_parser_contract_bound,
        fixture->acvp_response_contract_bound,
        fixture->kat_result_schema_bound,
        fixture->kat_result_row_fixture_bound,
        fixture->vector_schema_bound,
        fixture->vector_fixture_digest_ledger_bound,
        fixture->negative_test_evidence_bound,
        fixture->implementation_binding_manifest_bound,
        fixture->ci_promotion_evidence_bound,
        fixture->clean_room_source_boundary_recorded,
        fixture->response_fixture_policy_recorded,
        fixture->response_envelope_policy_recorded,
        fixture->acv_version_echo_required,
        fixture->vsid_echo_required,
        fixture->tgid_tcid_mapping_required,
        fixture->deterministic_ordering_required,
        fixture->keygen_response_fixture_required,
        fixture->encapsulation_response_fixture_required,
        fixture->decapsulation_response_fixture_required,
        fixture->key_check_response_fixture_required,
        fixture->canonical_hex_output_required,
        fixture->boolean_output_policy_recorded,
        fixture->no_secret_material_logging_required,
        fixture->no_network_submission_required,
        fixture->no_dynamic_code_loading_required,
        fixture->apple_corecrypto_code_copied,
        fixture->external_provider_code_copied,
        fixture->response_fixture_reviewed,
        fixture->fixture_bundle_digest_bound,
        fixture->parser_output_accepted,
        fixture->vector_execution_evidence_recorded,
        fixture->keygen_response_fixture_recorded,
        fixture->encapsulation_response_fixture_recorded,
        fixture->decapsulation_response_fixture_recorded,
        fixture->key_check_response_fixture_recorded,
        fixture->negative_response_fixture_recorded,
        fixture->response_schema_reviewed,
        fixture->response_security_reviewed,
        fixture->response_ci_replay_recorded,
        fixture->response_output_accepted,
        fixture->acvp_response_generation_evidence_recorded,
        fixture->response_json_generation_enabled,
        fixture->acvp_submission_allowed,
        fixture->operation_execution_allowed,
        fixture->production_crypto_claim_allowed,
        fixture->fips_claim_allowed,
        fixture->runtime_authority_granted,
        fixture->required_response_fixture_items_total,
        fixture->required_response_fixture_items_satisfied,
        fixture->blocked_reason,
        latticra_q_seal_ml_kem_acvp_response_fixture_error_label(fixture->error),
        fixture->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
