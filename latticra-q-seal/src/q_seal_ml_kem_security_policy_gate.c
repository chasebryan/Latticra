#include "latticra/q_seal_ml_kem_security_policy_gate.h"

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
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->security_policy_gate_present);
    satisfied += one_if(gate->fips_140_3_module_security_bound);
    satisfied += one_if(gate->sp800_140b_rev1_security_policy_bound);
    satisfied += one_if(gate->cmvp_program_bound);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->module_boundary_gate_bound);
    satisfied += one_if(gate->validation_claim_gate_bound);
    satisfied += one_if(gate->acvp_verdict_receipt_gate_bound);
    satisfied += one_if(gate->source_digest_verification_bound);
    satisfied += one_if(gate->code_owner_review_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->security_policy_template_recorded);
    satisfied += one_if(gate->non_proprietary_policy_required);
    satisfied += one_if(gate->module_identification_section_required);
    satisfied += one_if(gate->cryptographic_module_specification_section_required);
    satisfied += one_if(gate->approved_algorithms_section_required);
    satisfied += one_if(gate->roles_services_authentication_section_required);
    satisfied += one_if(gate->software_firmware_security_section_required);
    satisfied += one_if(gate->operational_environment_section_required);
    satisfied += one_if(gate->self_tests_section_required);
    satisfied += one_if(gate->entropy_boundary_section_required);
    satisfied += one_if(gate->life_cycle_assurance_section_required);
    satisfied += one_if(gate->mitigation_other_attacks_section_required);
    satisfied += one_if(gate->acronyms_references_section_required);
    satisfied += one_if(gate->no_implicit_fips_claim_policy_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->security_policy_evidence_recorded);
    satisfied += one_if(gate->security_policy_document_digest_recorded);
    satisfied += one_if(gate->module_name_version_recorded);
    satisfied += one_if(gate->security_level_table_recorded);
    satisfied += one_if(gate->approved_security_functions_table_recorded);
    satisfied += one_if(gate->services_roles_table_recorded);
    satisfied += one_if(gate->self_test_table_recorded);
    satisfied += one_if(gate->entropy_source_statement_recorded);
    satisfied += one_if(gate->operational_environment_recorded);
    satisfied += one_if(gate->guidance_statement_recorded);
    satisfied += one_if(gate->reviewer_disposition_recorded);
    satisfied += one_if(gate->security_policy_gate_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_security_policy_gate_error_label(
    latticra_q_seal_ml_kem_security_policy_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_security_policy_gate_prepare(
    latticra_q_seal_ml_kem_security_policy_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->security_policy_profile,
        sizeof(out->security_policy_profile),
        "latticra-q-seal-ml-kem-security-policy-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Security Policy Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-140-3,NIST-SP-800-140B-REV-1,NIST-CMVP,NIST-FIPS-203,NIST-SP-800-218-SSDF");
    copy_literal(
        out->security_policy_scope,
        sizeof(out->security_policy_scope),
        "ML-KEM-FIPS-140-3-security-policy-before-module-boundary-or-claims");
    copy_literal(
        out->security_policy_state,
        sizeof(out->security_policy_state),
        "security-policy-gate-recorded-policy-evidence-missing");

    out->security_policy_gate_present = 1u;
    out->fips_140_3_module_security_bound = 1u;
    out->sp800_140b_rev1_security_policy_bound = 1u;
    out->cmvp_program_bound = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->module_boundary_gate_bound = 1u;
    out->validation_claim_gate_bound = 1u;
    out->acvp_verdict_receipt_gate_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->security_policy_template_recorded = 1u;
    out->non_proprietary_policy_required = 1u;
    out->module_identification_section_required = 1u;
    out->cryptographic_module_specification_section_required = 1u;
    out->approved_algorithms_section_required = 1u;
    out->roles_services_authentication_section_required = 1u;
    out->software_firmware_security_section_required = 1u;
    out->operational_environment_section_required = 1u;
    out->self_tests_section_required = 1u;
    out->entropy_boundary_section_required = 1u;
    out->life_cycle_assurance_section_required = 1u;
    out->mitigation_other_attacks_section_required = 1u;
    out->acronyms_references_section_required = 1u;
    out->no_implicit_fips_claim_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->security_policy_evidence_recorded = 0u;
    out->security_policy_document_digest_recorded = 0u;
    out->module_name_version_recorded = 0u;
    out->security_level_table_recorded = 0u;
    out->approved_security_functions_table_recorded = 0u;
    out->services_roles_table_recorded = 0u;
    out->self_test_table_recorded = 0u;
    out->entropy_source_statement_recorded = 0u;
    out->operational_environment_recorded = 0u;
    out->guidance_statement_recorded = 0u;
    out->reviewer_disposition_recorded = 0u;
    out->security_policy_gate_accepted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_security_policy_items_total = 41u;
    out->required_security_policy_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "security-policy-document-digest-module-identification-security-level-approved-functions-services-self-tests-entropy-environment-guidance-review-and-disposition-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-security-policy-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_security_policy_gate_is_no_effect(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->security_policy_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->security_policy_evidence_recorded == 0u &&
           gate->security_policy_document_digest_recorded == 0u &&
           gate->module_name_version_recorded == 0u &&
           gate->security_level_table_recorded == 0u &&
           gate->approved_security_functions_table_recorded == 0u &&
           gate->services_roles_table_recorded == 0u &&
           gate->self_test_table_recorded == 0u &&
           gate->entropy_source_statement_recorded == 0u &&
           gate->operational_environment_recorded == 0u &&
           gate->guidance_statement_recorded == 0u &&
           gate->reviewer_disposition_recorded == 0u &&
           gate->security_policy_gate_accepted == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_BLOCKED;
}

int latticra_q_seal_ml_kem_security_policy_gate_allows_policy_acceptance(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->security_policy_gate_present == 1u &&
           gate->fips_140_3_module_security_bound == 1u &&
           gate->sp800_140b_rev1_security_policy_bound == 1u &&
           gate->cmvp_program_bound == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->module_boundary_gate_bound == 1u &&
           gate->validation_claim_gate_bound == 1u &&
           gate->acvp_verdict_receipt_gate_bound == 1u &&
           gate->source_digest_verification_bound == 1u &&
           gate->code_owner_review_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->security_policy_template_recorded == 1u &&
           gate->non_proprietary_policy_required == 1u &&
           gate->module_identification_section_required == 1u &&
           gate->cryptographic_module_specification_section_required == 1u &&
           gate->approved_algorithms_section_required == 1u &&
           gate->roles_services_authentication_section_required == 1u &&
           gate->software_firmware_security_section_required == 1u &&
           gate->operational_environment_section_required == 1u &&
           gate->self_tests_section_required == 1u &&
           gate->entropy_boundary_section_required == 1u &&
           gate->life_cycle_assurance_section_required == 1u &&
           gate->mitigation_other_attacks_section_required == 1u &&
           gate->acronyms_references_section_required == 1u &&
           gate->no_implicit_fips_claim_policy_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->security_policy_evidence_recorded == 1u &&
           gate->security_policy_document_digest_recorded == 1u &&
           gate->module_name_version_recorded == 1u &&
           gate->security_level_table_recorded == 1u &&
           gate->approved_security_functions_table_recorded == 1u &&
           gate->services_roles_table_recorded == 1u &&
           gate->self_test_table_recorded == 1u &&
           gate->entropy_source_statement_recorded == 1u &&
           gate->operational_environment_recorded == 1u &&
           gate->guidance_statement_recorded == 1u &&
           gate->reviewer_disposition_recorded == 1u &&
           gate->security_policy_gate_accepted == 1u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_security_policy_gate_report(
    const latticra_q_seal_ml_kem_security_policy_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM SECURITY POLICY GATE\n"
        "security_policy_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "security_policy_scope=%s\n"
        "security_policy_state=%s\n"
        "security_policy_gate_present=%u\n"
        "fips_140_3_module_security_bound=%u\n"
        "sp800_140b_rev1_security_policy_bound=%u\n"
        "cmvp_program_bound=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "module_boundary_gate_bound=%u\n"
        "validation_claim_gate_bound=%u\n"
        "acvp_verdict_receipt_gate_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "security_policy_template_recorded=%u\n"
        "non_proprietary_policy_required=%u\n"
        "module_identification_section_required=%u\n"
        "cryptographic_module_specification_section_required=%u\n"
        "approved_algorithms_section_required=%u\n"
        "roles_services_authentication_section_required=%u\n"
        "software_firmware_security_section_required=%u\n"
        "operational_environment_section_required=%u\n"
        "self_tests_section_required=%u\n"
        "entropy_boundary_section_required=%u\n"
        "life_cycle_assurance_section_required=%u\n"
        "mitigation_other_attacks_section_required=%u\n"
        "acronyms_references_section_required=%u\n"
        "no_implicit_fips_claim_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "security_policy_evidence_recorded=%u\n"
        "security_policy_document_digest_recorded=%u\n"
        "module_name_version_recorded=%u\n"
        "security_level_table_recorded=%u\n"
        "approved_security_functions_table_recorded=%u\n"
        "services_roles_table_recorded=%u\n"
        "self_test_table_recorded=%u\n"
        "entropy_source_statement_recorded=%u\n"
        "operational_environment_recorded=%u\n"
        "guidance_statement_recorded=%u\n"
        "reviewer_disposition_recorded=%u\n"
        "security_policy_gate_accepted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_security_policy_items_total=%u\n"
        "required_security_policy_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->security_policy_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->security_policy_scope,
        gate->security_policy_state,
        gate->security_policy_gate_present,
        gate->fips_140_3_module_security_bound,
        gate->sp800_140b_rev1_security_policy_bound,
        gate->cmvp_program_bound,
        gate->fips_203_algorithm_bound,
        gate->module_boundary_gate_bound,
        gate->validation_claim_gate_bound,
        gate->acvp_verdict_receipt_gate_bound,
        gate->source_digest_verification_bound,
        gate->code_owner_review_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->clean_room_source_boundary_recorded,
        gate->security_policy_template_recorded,
        gate->non_proprietary_policy_required,
        gate->module_identification_section_required,
        gate->cryptographic_module_specification_section_required,
        gate->approved_algorithms_section_required,
        gate->roles_services_authentication_section_required,
        gate->software_firmware_security_section_required,
        gate->operational_environment_section_required,
        gate->self_tests_section_required,
        gate->entropy_boundary_section_required,
        gate->life_cycle_assurance_section_required,
        gate->mitigation_other_attacks_section_required,
        gate->acronyms_references_section_required,
        gate->no_implicit_fips_claim_policy_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->security_policy_evidence_recorded,
        gate->security_policy_document_digest_recorded,
        gate->module_name_version_recorded,
        gate->security_level_table_recorded,
        gate->approved_security_functions_table_recorded,
        gate->services_roles_table_recorded,
        gate->self_test_table_recorded,
        gate->entropy_source_statement_recorded,
        gate->operational_environment_recorded,
        gate->guidance_statement_recorded,
        gate->reviewer_disposition_recorded,
        gate->security_policy_gate_accepted,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->operation_execution_allowed,
        gate->runtime_authority_granted,
        gate->required_security_policy_items_total,
        gate->required_security_policy_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_security_policy_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
