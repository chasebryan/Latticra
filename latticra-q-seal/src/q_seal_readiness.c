#include "latticra/q_seal_readiness.h"

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

static unsigned parameter_set_is_present(
    latticra_q_seal_ml_kem_parameter_set_t parameter_set) {
    latticra_q_seal_ml_kem_parameters_t parameters;

    if (latticra_q_seal_ml_kem_parameters(parameter_set, &parameters) !=
        LATTICRA_Q_SEAL_STATUS_OK) {
        return 0u;
    }

    return parameters.error == LATTICRA_Q_SEAL_ML_KEM_OK &&
           latticra_q_seal_ml_kem_parameters_are_authority_neutral(&parameters) == 1;
}

const char *latticra_q_seal_readiness_error_label(
    latticra_q_seal_readiness_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_READINESS_OK:
        return "ok";
    case LATTICRA_Q_SEAL_READINESS_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_READINESS_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_readiness_prepare(
    latticra_q_seal_readiness_t *out) {
    latticra_q_seal_foundation_t foundation;
    latticra_q_seal_ml_kem_evidence_gate_t evidence_gate;
    latticra_q_seal_ml_kem_fips_conformance_matrix_t fips_conformance_matrix;
    latticra_q_seal_ml_kem_sp800_227_usage_profile_t sp800_227_usage_profile;
    latticra_q_seal_ml_kem_kat_manifest_t kat_manifest;
    latticra_q_seal_ml_kem_kat_runner_contract_t kat_runner_contract;
    latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_t replay_transcript_gate;
    latticra_q_seal_ml_kem_kat_result_schema_t kat_result_schema;
    latticra_q_seal_ml_kem_kat_result_row_fixture_t kat_result_row_fixture;
    latticra_q_seal_ml_kem_acvp_intake_t acvp_intake;
    latticra_q_seal_ml_kem_acvp_capability_matrix_t acvp_capability_matrix;
    latticra_q_seal_ml_kem_acvp_fixture_row_plan_t acvp_fixture_row_plan;
    latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_t
        acvp_fixture_digest_row_template;
    latticra_q_seal_ml_kem_acvp_parser_contract_t acvp_parser_contract;
    latticra_q_seal_ml_kem_acvp_response_contract_t acvp_response_contract;
    latticra_q_seal_ml_kem_acvp_response_fixture_t acvp_response_fixture;
    latticra_q_seal_ml_kem_acvp_submission_package_contract_t
        acvp_submission_package_contract;
    latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_t
        acvp_verdict_receipt_gate;
    latticra_q_seal_ml_kem_vector_schema_t vector_schema;
    latticra_q_seal_ml_kem_vector_source_t vector_source;
    latticra_q_seal_ml_kem_vector_fixture_lock_t vector_fixture_lock;
    latticra_q_seal_ml_kem_vector_fixture_digest_ledger_t vector_fixture_digest_ledger;
    latticra_q_seal_ml_kem_negative_test_evidence_t negative_test_evidence;
    latticra_q_seal_ml_kem_memory_safety_evidence_t memory_safety_evidence;
    latticra_q_seal_ml_kem_api_misuse_resistance_t api_misuse_resistance;
    latticra_q_seal_ml_kem_source_digest_manifest_t source_digest_manifest;
    latticra_q_seal_ml_kem_source_digest_receipt_t source_digest_receipt;
    latticra_q_seal_ml_kem_source_digest_verification_t source_digest_verification;
    latticra_q_seal_ml_kem_receipt_replay_results_t receipt_replay_results;
    latticra_q_seal_ml_kem_code_owner_review_t code_owner_review;
    latticra_q_seal_ml_kem_review_disposition_ledger_t review_disposition_ledger;
    latticra_q_seal_ml_kem_reviewer_identity_fixture_t reviewer_identity_fixture;
    latticra_q_seal_ml_kem_reviewer_role_mapping_t reviewer_role_mapping;
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_t
        evidence_import_packet_manifest;
    latticra_q_seal_ml_kem_evidence_import_review_gate_t evidence_import_review_gate;
    latticra_q_seal_ml_kem_ci_promotion_evidence_t ci_promotion_evidence;
    latticra_q_seal_ml_kem_validation_claim_gate_t validation_claim_gate;
    latticra_q_seal_ml_kem_module_boundary_gate_t module_boundary_gate;
    latticra_q_seal_ml_kem_security_policy_gate_t security_policy_gate;
    latticra_q_seal_ml_kem_constant_time_review_t constant_time_review;
    latticra_q_seal_ml_kem_randomness_source_t randomness_source;
    latticra_q_seal_ml_kem_zeroization_evidence_t zeroization_evidence;
    latticra_q_seal_ml_kem_side_channel_review_t side_channel_review;
    latticra_q_seal_ml_kem_provider_differential_t provider_differential;
    latticra_q_seal_ml_kem_implementation_binding_manifest_t implementation_binding_manifest;
    latticra_q_seal_ml_kem_source_layout_gate_t source_layout_gate;
    latticra_q_seal_ml_kem_implementation_file_digest_plan_t
        implementation_file_digest_plan;
    latticra_q_seal_ml_kem_clean_room_author_attestation_gate_t
        clean_room_author_attestation_gate;
    latticra_q_seal_ml_kem_per_file_standards_trace_gate_t
        per_file_standards_trace_gate;
    latticra_q_seal_ml_kem_per_file_test_trace_gate_t
        per_file_test_trace_gate;
    latticra_q_seal_ml_kem_implementation_traceability_matrix_t
        implementation_traceability_matrix;
    latticra_q_seal_ml_kem_primitive_source_acceptance_gate_t
        primitive_source_acceptance_gate;
    latticra_q_seal_ml_kem_implementation_frame_t implementation_frame;
    latticra_q_seal_ml_kem_secret_state_contract_t secret_state_contract;
    unsigned foundation_clean_room;
    unsigned foundation_authority_neutral;

    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    if (latticra_q_seal_foundation_prepare(&foundation) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_evidence_gate_prepare(&evidence_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_fips_conformance_matrix_prepare(
            &fips_conformance_matrix) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(
            &sp800_227_usage_profile) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_kat_manifest_prepare(&kat_manifest) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_kat_runner_contract_prepare(&kat_runner_contract) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare(
            &replay_transcript_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_kat_result_schema_prepare(&kat_result_schema) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_kat_result_row_fixture_prepare(
            &kat_result_row_fixture) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_intake_prepare(&acvp_intake) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_capability_matrix_prepare(
            &acvp_capability_matrix) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_fixture_row_plan_prepare(
            &acvp_fixture_row_plan) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_prepare(
            &acvp_fixture_digest_row_template) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_parser_contract_prepare(
            &acvp_parser_contract) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_response_contract_prepare(
            &acvp_response_contract) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_response_fixture_prepare(&acvp_response_fixture) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_submission_package_contract_prepare(
            &acvp_submission_package_contract) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_prepare(
            &acvp_verdict_receipt_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_schema_prepare(&vector_schema) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_source_prepare(&vector_source) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_fixture_lock_prepare(&vector_fixture_lock) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_vector_fixture_digest_ledger_prepare(
            &vector_fixture_digest_ledger) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_negative_test_evidence_prepare(&negative_test_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_memory_safety_evidence_prepare(&memory_safety_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_api_misuse_resistance_prepare(&api_misuse_resistance) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_source_digest_manifest_prepare(&source_digest_manifest) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_source_digest_receipt_prepare(&source_digest_receipt) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_source_digest_verification_prepare(
            &source_digest_verification) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_receipt_replay_results_prepare(
            &receipt_replay_results) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_code_owner_review_prepare(&code_owner_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_review_disposition_ledger_prepare(
            &review_disposition_ledger) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(
            &reviewer_identity_fixture) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(
            &reviewer_role_mapping) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(
            &evidence_import_packet_manifest) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_evidence_import_review_gate_prepare(
            &evidence_import_review_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_ci_promotion_evidence_prepare(&ci_promotion_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_validation_claim_gate_prepare(&validation_claim_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_module_boundary_gate_prepare(&module_boundary_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_security_policy_gate_prepare(&security_policy_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_constant_time_review_prepare(&constant_time_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_randomness_source_prepare(&randomness_source) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_zeroization_evidence_prepare(&zeroization_evidence) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_side_channel_review_prepare(&side_channel_review) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_provider_differential_prepare(&provider_differential) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_binding_manifest_prepare(
            &implementation_binding_manifest) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_source_layout_gate_prepare(&source_layout_gate) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_file_digest_plan_prepare(
            &implementation_file_digest_plan) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_clean_room_author_attestation_gate_prepare(
            &clean_room_author_attestation_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare(
            &per_file_standards_trace_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_per_file_test_trace_gate_prepare(
            &per_file_test_trace_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_traceability_matrix_prepare(
            &implementation_traceability_matrix) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_primitive_source_acceptance_gate_prepare(
            &primitive_source_acceptance_gate) != LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_implementation_frame_prepare(&implementation_frame) !=
            LATTICRA_Q_SEAL_STATUS_OK ||
        latticra_q_seal_ml_kem_secret_state_contract_prepare(&secret_state_contract) !=
            LATTICRA_Q_SEAL_STATUS_OK) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    foundation_clean_room =
        (unsigned)latticra_q_seal_foundation_is_clean_room(&foundation);
    foundation_authority_neutral =
        (unsigned)latticra_q_seal_foundation_is_authority_neutral(&foundation);

    memset(out, 0, sizeof(*out));
    copy_literal(out->readiness_profile, sizeof(out->readiness_profile), "latticra-q-seal-readiness/0.1");
    copy_literal(out->formal_title, sizeof(out->formal_title), "Latticra Q-Seal Readiness Profile");
    copy_literal(out->subsystem_path, sizeof(out->subsystem_path), "latticra-q-seal");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-SP-800-227,NIST-ACVP-ML-KEM");
    copy_literal(out->source_boundary, sizeof(out->source_boundary), "clean-room-no-apple-code");
    copy_literal(
        out->readiness_state,
        sizeof(out->readiness_state),
        "design-frame-ready-runtime-crypto-blocked");

    out->readiness_profile_present = 1u;
    out->foundation_present =
        foundation.latticra_q_seal_present == 1u &&
        foundation_clean_room == 1u &&
        foundation_authority_neutral == 1u;
    out->ml_kem_512_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_512);
    out->ml_kem_768_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_768);
    out->ml_kem_1024_parameters_present =
        parameter_set_is_present(LATTICRA_Q_SEAL_ML_KEM_PARAMETER_SET_1024);
    out->ml_kem_parameters_present =
        out->ml_kem_512_parameters_present == 1u &&
        out->ml_kem_768_parameters_present == 1u &&
        out->ml_kem_1024_parameters_present == 1u;
    out->evidence_gate_present = evidence_gate.ml_kem_evidence_gate_present;
    out->fips_conformance_matrix_present =
        fips_conformance_matrix.fips_conformance_matrix_present;
    out->sp800_227_usage_profile_present =
        sp800_227_usage_profile.sp800_227_usage_profile_present;
    out->kat_manifest_present = kat_manifest.ml_kem_kat_manifest_present;
    out->kat_runner_contract_present =
        kat_runner_contract.kat_runner_contract_present;
    out->replay_transcript_gate_present =
        replay_transcript_gate.replay_transcript_gate_present;
    out->kat_result_schema_present = kat_result_schema.kat_result_schema_present;
    out->kat_result_row_fixture_present =
        kat_result_row_fixture.kat_result_row_fixture_present;
    out->acvp_intake_present = acvp_intake.acvp_intake_present;
    out->acvp_capability_matrix_present =
        acvp_capability_matrix.acvp_capability_matrix_present;
    out->acvp_fixture_row_plan_present =
        acvp_fixture_row_plan.acvp_fixture_row_plan_present;
    out->acvp_fixture_digest_row_template_present =
        acvp_fixture_digest_row_template.acvp_fixture_digest_row_template_present;
    out->acvp_parser_contract_present =
        acvp_parser_contract.acvp_parser_contract_present;
    out->acvp_response_contract_present =
        acvp_response_contract.acvp_response_contract_present;
    out->acvp_response_fixture_present =
        acvp_response_fixture.acvp_response_fixture_present;
    out->acvp_submission_package_contract_present =
        acvp_submission_package_contract.acvp_submission_package_contract_present;
    out->acvp_verdict_receipt_gate_present =
        acvp_verdict_receipt_gate.acvp_verdict_receipt_gate_present;
    out->vector_schema_present = vector_schema.vector_schema_present;
    out->vector_source_intake_present = vector_source.vector_source_intake_present;
    out->vector_fixture_lock_present =
        vector_fixture_lock.vector_fixture_lock_present;
    out->vector_fixture_digest_ledger_present =
        vector_fixture_digest_ledger.vector_fixture_digest_ledger_present;
    out->negative_test_evidence_present =
        negative_test_evidence.negative_test_evidence_present;
    out->memory_safety_evidence_present =
        memory_safety_evidence.memory_safety_evidence_present;
    out->api_misuse_resistance_present =
        api_misuse_resistance.api_misuse_resistance_present;
    out->source_digest_manifest_present =
        source_digest_manifest.source_digest_manifest_present;
    out->source_digest_receipt_present =
        source_digest_receipt.source_digest_receipt_present;
    out->source_digest_verification_present =
        source_digest_verification.source_digest_verification_present;
    out->receipt_replay_results_present =
        receipt_replay_results.receipt_replay_results_present;
    out->code_owner_review_present =
        code_owner_review.code_owner_review_evidence_present;
    out->review_disposition_ledger_present =
        review_disposition_ledger.review_disposition_ledger_present;
    out->reviewer_identity_fixture_present =
        reviewer_identity_fixture.reviewer_identity_fixture_present;
    out->reviewer_role_mapping_present =
        reviewer_role_mapping.reviewer_role_mapping_present;
    out->evidence_import_packet_manifest_present =
        evidence_import_packet_manifest.evidence_import_packet_manifest_present;
    out->evidence_import_review_gate_present =
        evidence_import_review_gate.evidence_import_review_gate_present;
    out->ci_promotion_evidence_present =
        ci_promotion_evidence.ci_promotion_evidence_present;
    out->validation_claim_gate_present =
        validation_claim_gate.validation_claim_gate_present;
    out->module_boundary_gate_present =
        module_boundary_gate.module_boundary_gate_present;
    out->security_policy_gate_present =
        security_policy_gate.security_policy_gate_present;
    out->constant_time_review_present =
        constant_time_review.constant_time_review_present;
    out->randomness_source_contract_present =
        randomness_source.randomness_source_contract_present;
    out->zeroization_evidence_present =
        zeroization_evidence.zeroization_evidence_present;
    out->side_channel_review_present =
        side_channel_review.side_channel_review_present;
    out->provider_differential_present =
        provider_differential.provider_differential_contract_present;
    out->implementation_binding_manifest_present =
        implementation_binding_manifest.implementation_binding_manifest_present;
    out->source_layout_gate_present =
        source_layout_gate.source_layout_gate_present;
    out->implementation_file_digest_plan_present =
        implementation_file_digest_plan.implementation_file_digest_plan_present;
    out->clean_room_author_attestation_gate_present =
        clean_room_author_attestation_gate.clean_room_author_attestation_gate_present;
    out->per_file_standards_trace_gate_present =
        per_file_standards_trace_gate.per_file_standards_trace_gate_present;
    out->per_file_test_trace_gate_present =
        per_file_test_trace_gate.per_file_test_trace_gate_present;
    out->implementation_traceability_matrix_present =
        implementation_traceability_matrix.implementation_traceability_matrix_present;
    out->primitive_source_acceptance_gate_present =
        primitive_source_acceptance_gate.primitive_source_acceptance_gate_present;
    out->implementation_frame_present = implementation_frame.implementation_frame_present;
    out->secret_state_contract_present =
        secret_state_contract.secret_state_contract_present;
    out->clean_room_boundary_recorded =
        foundation_clean_room == 1u &&
        fips_conformance_matrix.clean_room_source_boundary_recorded == 1u &&
        sp800_227_usage_profile.clean_room_source_boundary_recorded == 1u &&
        kat_manifest.clean_room_source_boundary_recorded == 1u &&
        kat_runner_contract.clean_room_source_boundary_recorded == 1u &&
        replay_transcript_gate.clean_room_source_boundary_recorded == 1u &&
        kat_result_schema.clean_room_source_boundary_recorded == 1u &&
        kat_result_row_fixture.clean_room_source_boundary_recorded == 1u &&
        acvp_capability_matrix.clean_room_source_boundary_recorded == 1u &&
        acvp_fixture_row_plan.clean_room_source_boundary_recorded == 1u &&
        acvp_fixture_digest_row_template.clean_room_source_boundary_recorded == 1u &&
        acvp_parser_contract.clean_room_source_boundary_recorded == 1u &&
        acvp_response_contract.clean_room_source_boundary_recorded == 1u &&
        acvp_response_fixture.clean_room_source_boundary_recorded == 1u &&
        acvp_submission_package_contract.clean_room_source_boundary_recorded == 1u &&
        acvp_verdict_receipt_gate.clean_room_source_boundary_recorded == 1u &&
        source_digest_manifest.clean_room_source_boundary_recorded == 1u &&
        source_digest_receipt.clean_room_source_boundary_recorded == 1u &&
        source_digest_verification.clean_room_source_boundary_recorded == 1u &&
        receipt_replay_results.clean_room_source_boundary_recorded == 1u &&
        vector_fixture_lock.clean_room_source_boundary_recorded == 1u &&
        vector_fixture_digest_ledger.clean_room_source_boundary_recorded == 1u &&
        implementation_binding_manifest.clean_room_source_boundary_recorded == 1u &&
        source_layout_gate.clean_room_source_boundary_recorded == 1u &&
        implementation_file_digest_plan.clean_room_source_boundary_recorded == 1u &&
        clean_room_author_attestation_gate.clean_room_source_boundary_recorded == 1u &&
        per_file_standards_trace_gate.clean_room_source_boundary_recorded == 1u &&
        per_file_test_trace_gate.clean_room_source_boundary_recorded == 1u &&
        implementation_traceability_matrix.clean_room_source_boundary_recorded == 1u &&
        primitive_source_acceptance_gate.clean_room_source_boundary_recorded == 1u &&
        implementation_frame.clean_room_source_boundary_recorded == 1u &&
        validation_claim_gate.clean_room_source_boundary_recorded == 1u &&
        module_boundary_gate.clean_room_source_boundary_recorded == 1u &&
        security_policy_gate.clean_room_source_boundary_recorded == 1u &&
        evidence_import_packet_manifest.clean_room_source_boundary_recorded == 1u &&
        evidence_import_review_gate.clean_room_source_boundary_recorded == 1u &&
        secret_state_contract.clean_room_source_boundary_recorded == 1u;
    out->apple_corecrypto_code_copied =
        foundation.apple_corecrypto_code_copied |
        evidence_gate.apple_corecrypto_code_copied |
        fips_conformance_matrix.apple_corecrypto_code_copied |
        sp800_227_usage_profile.apple_corecrypto_code_copied |
        kat_manifest.apple_corecrypto_code_copied |
        kat_runner_contract.apple_corecrypto_code_copied |
        replay_transcript_gate.apple_corecrypto_code_copied |
        kat_result_schema.apple_corecrypto_code_copied |
        kat_result_row_fixture.apple_corecrypto_code_copied |
        acvp_capability_matrix.apple_corecrypto_code_copied |
        acvp_fixture_row_plan.apple_corecrypto_code_copied |
        acvp_fixture_digest_row_template.apple_corecrypto_code_copied |
        acvp_parser_contract.apple_corecrypto_code_copied |
        acvp_response_contract.apple_corecrypto_code_copied |
        acvp_response_fixture.apple_corecrypto_code_copied |
        acvp_submission_package_contract.apple_corecrypto_code_copied |
        acvp_verdict_receipt_gate.apple_corecrypto_code_copied |
        source_digest_manifest.apple_corecrypto_code_copied |
        source_digest_receipt.apple_corecrypto_code_copied |
        source_digest_verification.apple_corecrypto_code_copied |
        receipt_replay_results.apple_corecrypto_code_copied |
        vector_fixture_lock.apple_corecrypto_code_copied |
        vector_fixture_digest_ledger.apple_corecrypto_code_copied |
        implementation_binding_manifest.apple_corecrypto_code_copied |
        source_layout_gate.apple_corecrypto_code_copied |
        implementation_file_digest_plan.apple_corecrypto_code_copied |
        clean_room_author_attestation_gate.apple_corecrypto_code_copied |
        per_file_standards_trace_gate.apple_corecrypto_code_copied |
        per_file_test_trace_gate.apple_corecrypto_code_copied |
        implementation_traceability_matrix.apple_corecrypto_code_copied |
        primitive_source_acceptance_gate.apple_corecrypto_code_copied |
        implementation_frame.apple_corecrypto_code_copied |
        validation_claim_gate.apple_corecrypto_code_copied |
        module_boundary_gate.apple_corecrypto_code_copied |
        security_policy_gate.apple_corecrypto_code_copied |
        evidence_import_packet_manifest.apple_corecrypto_code_copied |
        evidence_import_review_gate.apple_corecrypto_code_copied |
        secret_state_contract.apple_corecrypto_code_copied;
    out->external_provider_code_copied =
        fips_conformance_matrix.external_provider_code_copied |
        sp800_227_usage_profile.external_provider_code_copied |
        kat_manifest.external_provider_code_copied |
        kat_runner_contract.external_provider_code_copied |
        replay_transcript_gate.external_provider_code_copied |
        kat_result_schema.external_provider_code_copied |
        kat_result_row_fixture.external_provider_code_copied |
        acvp_capability_matrix.external_provider_code_copied |
        acvp_fixture_row_plan.external_provider_code_copied |
        acvp_fixture_digest_row_template.external_provider_code_copied |
        acvp_parser_contract.external_provider_code_copied |
        acvp_response_contract.external_provider_code_copied |
        acvp_response_fixture.external_provider_code_copied |
        acvp_submission_package_contract.external_provider_code_copied |
        acvp_verdict_receipt_gate.external_provider_code_copied |
        source_digest_manifest.external_provider_code_copied |
        source_digest_receipt.external_provider_code_copied |
        source_digest_verification.external_provider_code_copied |
        receipt_replay_results.external_provider_code_copied |
        vector_fixture_lock.external_provider_code_copied |
        vector_fixture_digest_ledger.external_provider_code_copied |
        implementation_binding_manifest.external_provider_code_copied |
        source_layout_gate.external_provider_code_copied |
        implementation_file_digest_plan.external_provider_code_copied |
        clean_room_author_attestation_gate.external_provider_code_copied |
        per_file_standards_trace_gate.external_provider_code_copied |
        per_file_test_trace_gate.external_provider_code_copied |
        implementation_traceability_matrix.external_provider_code_copied |
        primitive_source_acceptance_gate.external_provider_code_copied |
        implementation_frame.external_provider_code_copied |
        validation_claim_gate.external_provider_code_copied |
        module_boundary_gate.external_provider_code_copied |
        security_policy_gate.external_provider_code_copied |
        evidence_import_packet_manifest.external_provider_code_copied |
        evidence_import_review_gate.external_provider_code_copied |
        secret_state_contract.external_provider_code_copied;
    out->provider_runtime_used =
        foundation.provider_runtime_used |
        provider_differential.provider_runtime_used;
    out->components_total = 55u;
    out->components_present =
        one_if(out->foundation_present) +
        one_if(out->ml_kem_parameters_present) +
        one_if(out->evidence_gate_present) +
        one_if(out->fips_conformance_matrix_present) +
        one_if(out->sp800_227_usage_profile_present) +
        one_if(out->kat_manifest_present) +
        one_if(out->kat_runner_contract_present) +
        one_if(out->replay_transcript_gate_present) +
        one_if(out->kat_result_schema_present) +
        one_if(out->kat_result_row_fixture_present) +
        one_if(out->acvp_intake_present) +
        one_if(out->acvp_capability_matrix_present) +
        one_if(out->acvp_fixture_row_plan_present) +
        one_if(out->acvp_fixture_digest_row_template_present) +
        one_if(out->acvp_parser_contract_present) +
        one_if(out->acvp_response_contract_present) +
        one_if(out->acvp_response_fixture_present) +
        one_if(out->acvp_submission_package_contract_present) +
        one_if(out->acvp_verdict_receipt_gate_present) +
        one_if(out->vector_schema_present) +
        one_if(out->vector_source_intake_present) +
        one_if(out->vector_fixture_lock_present) +
        one_if(out->vector_fixture_digest_ledger_present) +
        one_if(out->negative_test_evidence_present) +
        one_if(out->memory_safety_evidence_present) +
        one_if(out->api_misuse_resistance_present) +
        one_if(out->source_digest_manifest_present) +
        one_if(out->source_digest_receipt_present) +
        one_if(out->source_digest_verification_present) +
        one_if(out->receipt_replay_results_present) +
        one_if(out->code_owner_review_present) +
        one_if(out->review_disposition_ledger_present) +
        one_if(out->reviewer_identity_fixture_present) +
        one_if(out->reviewer_role_mapping_present) +
        one_if(out->evidence_import_packet_manifest_present) +
        one_if(out->evidence_import_review_gate_present) +
        one_if(out->ci_promotion_evidence_present) +
        one_if(out->validation_claim_gate_present) +
        one_if(out->module_boundary_gate_present) +
        one_if(out->security_policy_gate_present) +
        one_if(out->constant_time_review_present) +
        one_if(out->randomness_source_contract_present) +
        one_if(out->zeroization_evidence_present) +
        one_if(out->side_channel_review_present) +
        one_if(out->provider_differential_present) +
        one_if(out->implementation_binding_manifest_present) +
        one_if(out->source_layout_gate_present) +
        one_if(out->implementation_file_digest_plan_present) +
        one_if(out->clean_room_author_attestation_gate_present) +
        one_if(out->per_file_standards_trace_gate_present) +
        one_if(out->per_file_test_trace_gate_present) +
        one_if(out->implementation_traceability_matrix_present) +
        one_if(out->primitive_source_acceptance_gate_present) +
        one_if(out->implementation_frame_present) +
        one_if(out->secret_state_contract_present);
    out->runtime_blockers_total =
        one_if(!latticra_q_seal_ml_kem_evidence_gate_allows_operations(&evidence_gate)) +
        one_if(
            !latticra_q_seal_ml_kem_fips_conformance_matrix_allows_implementation_trace_acceptance(
                &fips_conformance_matrix)) +
        one_if(
            !latticra_q_seal_ml_kem_sp800_227_usage_profile_allows_kem_usage_acceptance(
                &sp800_227_usage_profile)) +
        one_if(!latticra_q_seal_ml_kem_kat_manifest_allows_kat_execution(
            &kat_manifest)) +
        one_if(!latticra_q_seal_ml_kem_kat_runner_contract_allows_runner_execution(
            &kat_runner_contract)) +
        one_if(
            !latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_allows_transcript_acceptance(
                &replay_transcript_gate)) +
        one_if(!latticra_q_seal_ml_kem_kat_result_schema_allows_result_recording(
            &kat_result_schema)) +
        one_if(!latticra_q_seal_ml_kem_kat_result_row_fixture_allows_result_rows(
            &kat_result_row_fixture)) +
        one_if(!latticra_q_seal_ml_kem_acvp_intake_allows_vector_execution(&acvp_intake)) +
        one_if(!latticra_q_seal_ml_kem_acvp_capability_matrix_allows_fixture_row_planning(
            &acvp_capability_matrix)) +
        one_if(!latticra_q_seal_ml_kem_acvp_fixture_row_plan_allows_fixture_digest_rows(
            &acvp_fixture_row_plan)) +
        one_if(
            !latticra_q_seal_ml_kem_acvp_fixture_digest_row_template_allows_digest_row_acceptance(
                &acvp_fixture_digest_row_template)) +
        one_if(!latticra_q_seal_ml_kem_acvp_parser_contract_allows_vector_parser(
            &acvp_parser_contract)) +
        one_if(!latticra_q_seal_ml_kem_acvp_response_contract_allows_response_generation(
            &acvp_response_contract)) +
        one_if(!latticra_q_seal_ml_kem_acvp_response_fixture_allows_response_output(
            &acvp_response_fixture)) +
        one_if(
            !latticra_q_seal_ml_kem_acvp_submission_package_contract_allows_package_acceptance(
                &acvp_submission_package_contract)) +
        one_if(
            !latticra_q_seal_ml_kem_acvp_verdict_receipt_gate_allows_verdict_acceptance(
                &acvp_verdict_receipt_gate)) +
        one_if(!latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(
            &vector_schema)) +
        one_if(!latticra_q_seal_ml_kem_vector_source_allows_bundle_acceptance(
            &vector_source)) +
        one_if(!latticra_q_seal_ml_kem_vector_fixture_lock_allows_vector_execution(
            &vector_fixture_lock)) +
        one_if(!latticra_q_seal_ml_kem_vector_fixture_digest_ledger_allows_fixture_lock(
            &vector_fixture_digest_ledger)) +
        one_if(!latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(
            &negative_test_evidence)) +
        one_if(!latticra_q_seal_ml_kem_memory_safety_evidence_allows_implementation_promotion(
            &memory_safety_evidence)) +
        one_if(!latticra_q_seal_ml_kem_api_misuse_resistance_allows_public_api(
            &api_misuse_resistance)) +
        one_if(!latticra_q_seal_ml_kem_source_digest_manifest_allows_implementation_promotion(
            &source_digest_manifest)) +
        one_if(!latticra_q_seal_ml_kem_source_digest_receipt_allows_implementation_promotion(
            &source_digest_receipt)) +
        one_if(!latticra_q_seal_ml_kem_source_digest_verification_allows_implementation_promotion(
            &source_digest_verification)) +
        one_if(!latticra_q_seal_ml_kem_receipt_replay_results_allows_implementation_promotion(
            &receipt_replay_results)) +
        one_if(!latticra_q_seal_ml_kem_code_owner_review_allows_implementation_promotion(
            &code_owner_review)) +
        one_if(!latticra_q_seal_ml_kem_review_disposition_ledger_allows_implementation_promotion(
            &review_disposition_ledger)) +
        one_if(!latticra_q_seal_ml_kem_reviewer_identity_fixture_allows_implementation_promotion(
            &reviewer_identity_fixture)) +
        one_if(!latticra_q_seal_ml_kem_reviewer_role_mapping_allows_implementation_promotion(
            &reviewer_role_mapping)) +
        one_if(
            !latticra_q_seal_ml_kem_evidence_import_packet_manifest_allows_packet_acceptance(
                &evidence_import_packet_manifest)) +
        one_if(!latticra_q_seal_ml_kem_evidence_import_review_gate_allows_import_acceptance(
            &evidence_import_review_gate)) +
        one_if(!latticra_q_seal_ml_kem_ci_promotion_evidence_allows_implementation_promotion(
            &ci_promotion_evidence)) +
        one_if(!latticra_q_seal_ml_kem_validation_claim_gate_allows_validation_claims(
            &validation_claim_gate)) +
        one_if(!latticra_q_seal_ml_kem_module_boundary_gate_allows_boundary_acceptance(
            &module_boundary_gate)) +
        one_if(!latticra_q_seal_ml_kem_security_policy_gate_allows_policy_acceptance(
            &security_policy_gate)) +
        one_if(!latticra_q_seal_ml_kem_constant_time_review_allows_implementation_promotion(
            &constant_time_review)) +
        one_if(!latticra_q_seal_ml_kem_randomness_source_allows_random_generation(
            &randomness_source)) +
        one_if(!latticra_q_seal_ml_kem_zeroization_evidence_allows_secret_material_handling(
            &zeroization_evidence)) +
        one_if(!latticra_q_seal_ml_kem_side_channel_review_allows_implementation_promotion(
            &side_channel_review)) +
        one_if(!latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(
            &provider_differential)) +
        one_if(!latticra_q_seal_ml_kem_implementation_binding_manifest_allows_implementation(
            &implementation_binding_manifest)) +
        one_if(!latticra_q_seal_ml_kem_source_layout_gate_allows_layout_acceptance(
            &source_layout_gate)) +
        one_if(
            !latticra_q_seal_ml_kem_implementation_file_digest_plan_allows_digest_row_acceptance(
                &implementation_file_digest_plan)) +
        one_if(
            !latticra_q_seal_ml_kem_clean_room_author_attestation_gate_allows_attestation_acceptance(
                &clean_room_author_attestation_gate)) +
        one_if(
            !latticra_q_seal_ml_kem_per_file_standards_trace_gate_allows_trace_acceptance(
                &per_file_standards_trace_gate)) +
        one_if(
            !latticra_q_seal_ml_kem_per_file_test_trace_gate_allows_trace_acceptance(
                &per_file_test_trace_gate)) +
        one_if(
            !latticra_q_seal_ml_kem_implementation_traceability_matrix_allows_trace_acceptance(
                &implementation_traceability_matrix)) +
        one_if(
            !latticra_q_seal_ml_kem_primitive_source_acceptance_gate_allows_source_acceptance(
                &primitive_source_acceptance_gate)) +
        one_if(!latticra_q_seal_ml_kem_implementation_frame_allows_implementation(
            &implementation_frame)) +
        one_if(!latticra_q_seal_ml_kem_secret_state_contract_allows_operations(
            &secret_state_contract));
    out->required_readiness_items_total =
        2u +
        3u +
        evidence_gate.required_evidence_items_total +
        fips_conformance_matrix.required_conformance_items_total +
        sp800_227_usage_profile.required_usage_items_total +
        kat_manifest.required_kat_manifest_items_total +
        kat_runner_contract.required_kat_runner_contract_items_total +
        replay_transcript_gate.required_transcript_items_total +
        kat_result_schema.required_kat_result_schema_items_total +
        kat_result_row_fixture.required_kat_result_row_fixture_items_total +
        acvp_intake.required_intake_items_total +
        acvp_capability_matrix.required_capability_items_total +
        acvp_fixture_row_plan.required_fixture_row_plan_items_total +
        acvp_fixture_digest_row_template.required_digest_row_template_items_total +
        acvp_parser_contract.required_parser_contract_items_total +
        acvp_response_contract.required_response_contract_items_total +
        acvp_response_fixture.required_response_fixture_items_total +
        acvp_submission_package_contract.required_submission_package_items_total +
        acvp_verdict_receipt_gate.required_verdict_receipt_items_total +
        vector_schema.required_schema_items_total +
        vector_source.required_source_items_total +
        vector_fixture_lock.required_fixture_lock_items_total +
        vector_fixture_digest_ledger.required_fixture_digest_items_total +
        negative_test_evidence.required_negative_test_items_total +
        memory_safety_evidence.required_memory_safety_items_total +
        api_misuse_resistance.required_api_misuse_items_total +
        source_digest_manifest.required_digest_items_total +
        source_digest_receipt.required_receipt_items_total +
        source_digest_verification.required_verification_items_total +
        receipt_replay_results.required_replay_items_total +
        code_owner_review.required_review_items_total +
        review_disposition_ledger.required_disposition_items_total +
        reviewer_identity_fixture.required_identity_items_total +
        reviewer_role_mapping.required_role_mapping_items_total +
        evidence_import_packet_manifest.required_evidence_packet_items_total +
        evidence_import_review_gate.required_evidence_import_items_total +
        ci_promotion_evidence.required_promotion_items_total +
        validation_claim_gate.required_validation_claim_items_total +
        module_boundary_gate.required_module_boundary_items_total +
        security_policy_gate.required_security_policy_items_total +
        constant_time_review.required_review_items_total +
        randomness_source.required_randomness_items_total +
        zeroization_evidence.required_zeroization_items_total +
        side_channel_review.required_review_items_total +
        provider_differential.required_comparison_items_total +
        implementation_binding_manifest.required_binding_items_total +
        source_layout_gate.required_layout_items_total +
        implementation_file_digest_plan.required_digest_plan_items_total +
        clean_room_author_attestation_gate.required_attestation_items_total +
        per_file_standards_trace_gate.required_standards_trace_items_total +
        per_file_test_trace_gate.required_test_trace_items_total +
        implementation_traceability_matrix.required_traceability_items_total +
        primitive_source_acceptance_gate.required_acceptance_items_total +
        implementation_frame.required_design_items_total +
        secret_state_contract.required_secret_state_items_total;
    out->required_readiness_items_satisfied =
        foundation_clean_room +
        foundation_authority_neutral +
        out->ml_kem_512_parameters_present +
        out->ml_kem_768_parameters_present +
        out->ml_kem_1024_parameters_present +
        evidence_gate.required_evidence_items_satisfied +
        fips_conformance_matrix.required_conformance_items_satisfied +
        sp800_227_usage_profile.required_usage_items_satisfied +
        kat_manifest.required_kat_manifest_items_satisfied +
        kat_runner_contract.required_kat_runner_contract_items_satisfied +
        replay_transcript_gate.required_transcript_items_satisfied +
        kat_result_schema.required_kat_result_schema_items_satisfied +
        kat_result_row_fixture.required_kat_result_row_fixture_items_satisfied +
        acvp_intake.required_intake_items_satisfied +
        acvp_capability_matrix.required_capability_items_satisfied +
        acvp_fixture_row_plan.required_fixture_row_plan_items_satisfied +
        acvp_fixture_digest_row_template.required_digest_row_template_items_satisfied +
        acvp_parser_contract.required_parser_contract_items_satisfied +
        acvp_response_contract.required_response_contract_items_satisfied +
        acvp_response_fixture.required_response_fixture_items_satisfied +
        acvp_submission_package_contract.required_submission_package_items_satisfied +
        acvp_verdict_receipt_gate.required_verdict_receipt_items_satisfied +
        vector_schema.required_schema_items_satisfied +
        vector_source.required_source_items_satisfied +
        vector_fixture_lock.required_fixture_lock_items_satisfied +
        vector_fixture_digest_ledger.required_fixture_digest_items_satisfied +
        negative_test_evidence.required_negative_test_items_satisfied +
        memory_safety_evidence.required_memory_safety_items_satisfied +
        api_misuse_resistance.required_api_misuse_items_satisfied +
        source_digest_manifest.required_digest_items_satisfied +
        source_digest_receipt.required_receipt_items_satisfied +
        source_digest_verification.required_verification_items_satisfied +
        receipt_replay_results.required_replay_items_satisfied +
        code_owner_review.required_review_items_satisfied +
        review_disposition_ledger.required_disposition_items_satisfied +
        reviewer_identity_fixture.required_identity_items_satisfied +
        reviewer_role_mapping.required_role_mapping_items_satisfied +
        evidence_import_packet_manifest.required_evidence_packet_items_satisfied +
        evidence_import_review_gate.required_evidence_import_items_satisfied +
        ci_promotion_evidence.required_promotion_items_satisfied +
        validation_claim_gate.required_validation_claim_items_satisfied +
        module_boundary_gate.required_module_boundary_items_satisfied +
        security_policy_gate.required_security_policy_items_satisfied +
        constant_time_review.required_review_items_satisfied +
        randomness_source.required_randomness_items_satisfied +
        zeroization_evidence.required_zeroization_items_satisfied +
        side_channel_review.required_review_items_satisfied +
        provider_differential.required_comparison_items_satisfied +
        implementation_binding_manifest.required_binding_items_satisfied +
        source_layout_gate.required_layout_items_satisfied +
        implementation_file_digest_plan.required_digest_plan_items_satisfied +
        clean_room_author_attestation_gate.required_attestation_items_satisfied +
        per_file_standards_trace_gate.required_standards_trace_items_satisfied +
        per_file_test_trace_gate.required_test_trace_items_satisfied +
        implementation_traceability_matrix.required_traceability_items_satisfied +
        primitive_source_acceptance_gate.required_acceptance_items_satisfied +
        implementation_frame.required_design_items_satisfied +
        secret_state_contract.required_secret_state_items_satisfied;
    out->design_frame_integration_ready =
        out->components_present == out->components_total &&
        out->clean_room_boundary_recorded == 1u &&
        out->apple_corecrypto_code_copied == 0u &&
        out->external_provider_code_copied == 0u &&
        out->provider_runtime_used == 0u;
    out->runtime_crypto_ready = 0u;
    out->operations_enabled = 0u;
    out->key_generation_enabled = 0u;
    out->encapsulation_enabled = 0u;
    out->decapsulation_enabled = 0u;
    out->shared_secret_emitted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->post_quantum_migration_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "primitive-source-acceptance-source-layout-clean-room-author-attestation-per-file-standards-trace-per-file-test-trace-implementation-file-digest-plan-implementation-traceability-fips-conformance-sp800-227-usage-kat-manifest-kat-runner-contract-replay-transcript-gate-kat-result-schema-kat-result-row-fixture-acvp-parser-response-fixture-submission-package-verdict-receipt-validation-claim-module-boundary-security-policy-evidence-import-packet-evidence-import-vector-fixture-negative-memory-api-source-digest-review-ci-binding-randomness-zeroization-side-channel-evidence-missing");
    out->error = LATTICRA_Q_SEAL_READINESS_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "q-seal-readiness-profile-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_readiness_is_design_frame_ready(
    const latticra_q_seal_readiness_t *readiness) {
    if (readiness == NULL) {
        return 0;
    }

    return readiness->readiness_profile_present == 1u &&
           readiness->components_total == 55u &&
           readiness->components_present == readiness->components_total &&
           readiness->clean_room_boundary_recorded == 1u &&
           readiness->apple_corecrypto_code_copied == 0u &&
           readiness->external_provider_code_copied == 0u &&
           readiness->provider_runtime_used == 0u &&
           readiness->operations_enabled == 0u &&
           readiness->production_crypto_claim_allowed == 0u &&
           readiness->fips_claim_allowed == 0u &&
           readiness->runtime_authority_granted == 0u;
}

int latticra_q_seal_readiness_allows_runtime_crypto(
    const latticra_q_seal_readiness_t *readiness) {
    if (readiness == NULL) {
        return 0;
    }

    return readiness->design_frame_integration_ready == 1u &&
           readiness->runtime_crypto_ready == 1u &&
           readiness->runtime_blockers_total == 0u &&
           readiness->required_readiness_items_total ==
               readiness->required_readiness_items_satisfied &&
           readiness->operations_enabled == 1u &&
           readiness->key_generation_enabled == 1u &&
           readiness->encapsulation_enabled == 1u &&
           readiness->decapsulation_enabled == 1u &&
           readiness->shared_secret_emitted == 1u &&
           readiness->production_crypto_claim_allowed == 1u &&
           readiness->runtime_authority_granted == 1u &&
           readiness->error == LATTICRA_Q_SEAL_READINESS_OK;
}

latticra_q_seal_status_t latticra_q_seal_readiness_report(
    const latticra_q_seal_readiness_t *readiness,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (readiness == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL READINESS PROFILE\n"
        "readiness_profile=%s\n"
        "formal_title=%s\n"
        "subsystem_path=%s\n"
        "standards_basis=%s\n"
        "source_boundary=%s\n"
        "readiness_state=%s\n"
        "readiness_profile_present=%u\n"
        "foundation_present=%u\n"
        "ml_kem_parameters_present=%u\n"
        "ml_kem_512_parameters_present=%u\n"
        "ml_kem_768_parameters_present=%u\n"
        "ml_kem_1024_parameters_present=%u\n"
        "evidence_gate_present=%u\n"
        "fips_conformance_matrix_present=%u\n"
        "sp800_227_usage_profile_present=%u\n"
        "kat_manifest_present=%u\n"
        "kat_runner_contract_present=%u\n"
        "replay_transcript_gate_present=%u\n"
        "kat_result_schema_present=%u\n"
        "kat_result_row_fixture_present=%u\n"
        "acvp_intake_present=%u\n"
        "acvp_capability_matrix_present=%u\n"
        "acvp_fixture_row_plan_present=%u\n"
        "acvp_fixture_digest_row_template_present=%u\n"
        "acvp_parser_contract_present=%u\n"
        "acvp_response_contract_present=%u\n"
        "acvp_response_fixture_present=%u\n"
        "acvp_submission_package_contract_present=%u\n"
        "acvp_verdict_receipt_gate_present=%u\n"
        "vector_schema_present=%u\n"
        "vector_source_intake_present=%u\n"
        "vector_fixture_lock_present=%u\n"
        "vector_fixture_digest_ledger_present=%u\n"
        "negative_test_evidence_present=%u\n"
        "memory_safety_evidence_present=%u\n"
        "api_misuse_resistance_present=%u\n"
        "source_digest_manifest_present=%u\n"
        "source_digest_receipt_present=%u\n"
        "source_digest_verification_present=%u\n"
        "receipt_replay_results_present=%u\n"
        "code_owner_review_present=%u\n"
        "review_disposition_ledger_present=%u\n"
        "reviewer_identity_fixture_present=%u\n"
        "reviewer_role_mapping_present=%u\n"
        "evidence_import_packet_manifest_present=%u\n"
        "evidence_import_review_gate_present=%u\n"
        "ci_promotion_evidence_present=%u\n"
        "validation_claim_gate_present=%u\n"
        "module_boundary_gate_present=%u\n"
        "security_policy_gate_present=%u\n"
        "constant_time_review_present=%u\n"
        "randomness_source_contract_present=%u\n"
        "zeroization_evidence_present=%u\n"
        "side_channel_review_present=%u\n"
        "provider_differential_present=%u\n"
        "implementation_binding_manifest_present=%u\n"
        "source_layout_gate_present=%u\n"
        "implementation_file_digest_plan_present=%u\n"
        "clean_room_author_attestation_gate_present=%u\n"
        "per_file_standards_trace_gate_present=%u\n"
        "per_file_test_trace_gate_present=%u\n"
        "implementation_traceability_matrix_present=%u\n"
        "primitive_source_acceptance_gate_present=%u\n"
        "implementation_frame_present=%u\n"
        "secret_state_contract_present=%u\n"
        "clean_room_boundary_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "provider_runtime_used=%u\n"
        "components_total=%u\n"
        "components_present=%u\n"
        "runtime_blockers_total=%u\n"
        "required_readiness_items_total=%u\n"
        "required_readiness_items_satisfied=%u\n"
        "design_frame_integration_ready=%u\n"
        "runtime_crypto_ready=%u\n"
        "operations_enabled=%u\n"
        "key_generation_enabled=%u\n"
        "encapsulation_enabled=%u\n"
        "decapsulation_enabled=%u\n"
        "shared_secret_emitted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        readiness->readiness_profile,
        readiness->formal_title,
        readiness->subsystem_path,
        readiness->standards_basis,
        readiness->source_boundary,
        readiness->readiness_state,
        readiness->readiness_profile_present,
        readiness->foundation_present,
        readiness->ml_kem_parameters_present,
        readiness->ml_kem_512_parameters_present,
        readiness->ml_kem_768_parameters_present,
        readiness->ml_kem_1024_parameters_present,
        readiness->evidence_gate_present,
        readiness->fips_conformance_matrix_present,
        readiness->sp800_227_usage_profile_present,
        readiness->kat_manifest_present,
        readiness->kat_runner_contract_present,
        readiness->replay_transcript_gate_present,
        readiness->kat_result_schema_present,
        readiness->kat_result_row_fixture_present,
        readiness->acvp_intake_present,
        readiness->acvp_capability_matrix_present,
        readiness->acvp_fixture_row_plan_present,
        readiness->acvp_fixture_digest_row_template_present,
        readiness->acvp_parser_contract_present,
        readiness->acvp_response_contract_present,
        readiness->acvp_response_fixture_present,
        readiness->acvp_submission_package_contract_present,
        readiness->acvp_verdict_receipt_gate_present,
        readiness->vector_schema_present,
        readiness->vector_source_intake_present,
        readiness->vector_fixture_lock_present,
        readiness->vector_fixture_digest_ledger_present,
        readiness->negative_test_evidence_present,
        readiness->memory_safety_evidence_present,
        readiness->api_misuse_resistance_present,
        readiness->source_digest_manifest_present,
        readiness->source_digest_receipt_present,
        readiness->source_digest_verification_present,
        readiness->receipt_replay_results_present,
        readiness->code_owner_review_present,
        readiness->review_disposition_ledger_present,
        readiness->reviewer_identity_fixture_present,
        readiness->reviewer_role_mapping_present,
        readiness->evidence_import_packet_manifest_present,
        readiness->evidence_import_review_gate_present,
        readiness->ci_promotion_evidence_present,
        readiness->validation_claim_gate_present,
        readiness->module_boundary_gate_present,
        readiness->security_policy_gate_present,
        readiness->constant_time_review_present,
        readiness->randomness_source_contract_present,
        readiness->zeroization_evidence_present,
        readiness->side_channel_review_present,
        readiness->provider_differential_present,
        readiness->implementation_binding_manifest_present,
        readiness->source_layout_gate_present,
        readiness->implementation_file_digest_plan_present,
        readiness->clean_room_author_attestation_gate_present,
        readiness->per_file_standards_trace_gate_present,
        readiness->per_file_test_trace_gate_present,
        readiness->implementation_traceability_matrix_present,
        readiness->primitive_source_acceptance_gate_present,
        readiness->implementation_frame_present,
        readiness->secret_state_contract_present,
        readiness->clean_room_boundary_recorded,
        readiness->apple_corecrypto_code_copied,
        readiness->external_provider_code_copied,
        readiness->provider_runtime_used,
        readiness->components_total,
        readiness->components_present,
        readiness->runtime_blockers_total,
        readiness->required_readiness_items_total,
        readiness->required_readiness_items_satisfied,
        readiness->design_frame_integration_ready,
        readiness->runtime_crypto_ready,
        readiness->operations_enabled,
        readiness->key_generation_enabled,
        readiness->encapsulation_enabled,
        readiness->decapsulation_enabled,
        readiness->shared_secret_emitted,
        readiness->production_crypto_claim_allowed,
        readiness->fips_claim_allowed,
        readiness->post_quantum_migration_claim_allowed,
        readiness->runtime_authority_granted,
        readiness->blocked_reason,
        latticra_q_seal_readiness_error_label(readiness->error),
        readiness->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
