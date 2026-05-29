#include "latticra/q_seal_ml_kem_module_boundary_gate.h"

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
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->module_boundary_gate_present);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->fips_140_3_module_security_bound);
    satisfied += one_if(gate->cmvp_program_bound);
    satisfied += one_if(gate->validation_claim_gate_bound);
    satisfied += one_if(gate->security_policy_gate_bound);
    satisfied += one_if(gate->acvp_verdict_receipt_gate_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->implementation_binding_manifest_bound);
    satisfied += one_if(gate->source_layout_gate_bound);
    satisfied += one_if(gate->implementation_file_digest_plan_bound);
    satisfied += one_if(gate->source_digest_verification_bound);
    satisfied += one_if(gate->zeroization_evidence_bound);
    satisfied += one_if(gate->randomness_source_bound);
    satisfied += one_if(gate->side_channel_review_bound);
    satisfied += one_if(gate->code_owner_review_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->module_boundary_schema_recorded);
    satisfied += one_if(gate->security_policy_template_recorded);
    satisfied += one_if(gate->services_roles_columns_recorded);
    satisfied += one_if(gate->operational_environment_columns_recorded);
    satisfied += one_if(gate->self_test_policy_columns_recorded);
    satisfied += one_if(gate->algorithm_certificate_columns_recorded);
    satisfied += one_if(gate->entropy_boundary_columns_recorded);
    satisfied += one_if(gate->zeroization_boundary_columns_recorded);
    satisfied += one_if(gate->source_digest_policy_bound);
    satisfied += one_if(gate->no_implicit_fips_claim_policy_recorded);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->module_boundary_evidence_recorded);
    satisfied += one_if(gate->cryptographic_module_name_recorded);
    satisfied += one_if(gate->module_version_recorded);
    satisfied += one_if(gate->operational_environment_recorded);
    satisfied += one_if(gate->fips_140_3_security_policy_recorded);
    satisfied += one_if(gate->roles_services_authentication_recorded);
    satisfied += one_if(gate->self_test_policy_recorded);
    satisfied += one_if(gate->approved_algorithm_inventory_recorded);
    satisfied += one_if(gate->entropy_source_boundary_recorded);
    satisfied += one_if(gate->zeroization_boundary_review_recorded);
    satisfied += one_if(gate->acvp_algorithm_certificate_bound);
    satisfied += one_if(gate->cmvp_submission_identifier_recorded);
    satisfied += one_if(gate->module_boundary_review_recorded);
    satisfied += one_if(gate->reviewer_disposition_recorded);
    satisfied += one_if(gate->module_boundary_gate_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_module_boundary_gate_error_label(
    latticra_q_seal_ml_kem_module_boundary_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_module_boundary_gate_prepare(
    latticra_q_seal_ml_kem_module_boundary_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->module_boundary_profile,
        sizeof(out->module_boundary_profile),
        "latticra-q-seal-ml-kem-module-boundary-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Module Boundary Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-FIPS-140-3,NIST-CMVP,NIST-SP-800-218-SSDF");
    copy_literal(
        out->module_boundary_scope,
        sizeof(out->module_boundary_scope),
        "ML-KEM-FIPS-module-boundary-and-security-policy-before-CMVP-or-claims");
    copy_literal(
        out->module_boundary_state,
        sizeof(out->module_boundary_state),
        "module-boundary-gate-recorded-boundary-evidence-missing");

    out->module_boundary_gate_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->fips_140_3_module_security_bound = 1u;
    out->cmvp_program_bound = 1u;
    out->validation_claim_gate_bound = 1u;
    out->security_policy_gate_bound = 1u;
    out->acvp_verdict_receipt_gate_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->source_layout_gate_bound = 1u;
    out->implementation_file_digest_plan_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->zeroization_evidence_bound = 1u;
    out->randomness_source_bound = 1u;
    out->side_channel_review_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->module_boundary_schema_recorded = 1u;
    out->security_policy_template_recorded = 1u;
    out->services_roles_columns_recorded = 1u;
    out->operational_environment_columns_recorded = 1u;
    out->self_test_policy_columns_recorded = 1u;
    out->algorithm_certificate_columns_recorded = 1u;
    out->entropy_boundary_columns_recorded = 1u;
    out->zeroization_boundary_columns_recorded = 1u;
    out->source_digest_policy_bound = 1u;
    out->no_implicit_fips_claim_policy_recorded = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->module_boundary_evidence_recorded = 0u;
    out->cryptographic_module_name_recorded = 0u;
    out->module_version_recorded = 0u;
    out->operational_environment_recorded = 0u;
    out->fips_140_3_security_policy_recorded = 0u;
    out->roles_services_authentication_recorded = 0u;
    out->self_test_policy_recorded = 0u;
    out->approved_algorithm_inventory_recorded = 0u;
    out->entropy_source_boundary_recorded = 0u;
    out->zeroization_boundary_review_recorded = 0u;
    out->acvp_algorithm_certificate_bound = 0u;
    out->cmvp_submission_identifier_recorded = 0u;
    out->module_boundary_review_recorded = 0u;
    out->reviewer_disposition_recorded = 0u;
    out->module_boundary_gate_accepted = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_module_boundary_items_total = 46u;
    out->required_module_boundary_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "module-boundary-name-version-operational-environment-security-policy-roles-services-self-test-algorithm-inventory-entropy-zeroization-certificate-cmvp-review-and-disposition-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-module-boundary-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_module_boundary_gate_is_no_effect(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->module_boundary_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->module_boundary_evidence_recorded == 0u &&
           gate->cryptographic_module_name_recorded == 0u &&
           gate->module_version_recorded == 0u &&
           gate->operational_environment_recorded == 0u &&
           gate->fips_140_3_security_policy_recorded == 0u &&
           gate->roles_services_authentication_recorded == 0u &&
           gate->approved_algorithm_inventory_recorded == 0u &&
           gate->cmvp_submission_identifier_recorded == 0u &&
           gate->module_boundary_gate_accepted == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_BLOCKED;
}

int latticra_q_seal_ml_kem_module_boundary_gate_allows_boundary_acceptance(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->module_boundary_gate_present == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->fips_140_3_module_security_bound == 1u &&
           gate->cmvp_program_bound == 1u &&
           gate->validation_claim_gate_bound == 1u &&
           gate->security_policy_gate_bound == 1u &&
           gate->acvp_verdict_receipt_gate_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->implementation_binding_manifest_bound == 1u &&
           gate->source_layout_gate_bound == 1u &&
           gate->implementation_file_digest_plan_bound == 1u &&
           gate->source_digest_verification_bound == 1u &&
           gate->zeroization_evidence_bound == 1u &&
           gate->randomness_source_bound == 1u &&
           gate->side_channel_review_bound == 1u &&
           gate->code_owner_review_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->module_boundary_schema_recorded == 1u &&
           gate->security_policy_template_recorded == 1u &&
           gate->services_roles_columns_recorded == 1u &&
           gate->operational_environment_columns_recorded == 1u &&
           gate->self_test_policy_columns_recorded == 1u &&
           gate->algorithm_certificate_columns_recorded == 1u &&
           gate->entropy_boundary_columns_recorded == 1u &&
           gate->zeroization_boundary_columns_recorded == 1u &&
           gate->source_digest_policy_bound == 1u &&
           gate->no_implicit_fips_claim_policy_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->module_boundary_evidence_recorded == 1u &&
           gate->cryptographic_module_name_recorded == 1u &&
           gate->module_version_recorded == 1u &&
           gate->operational_environment_recorded == 1u &&
           gate->fips_140_3_security_policy_recorded == 1u &&
           gate->roles_services_authentication_recorded == 1u &&
           gate->self_test_policy_recorded == 1u &&
           gate->approved_algorithm_inventory_recorded == 1u &&
           gate->entropy_source_boundary_recorded == 1u &&
           gate->zeroization_boundary_review_recorded == 1u &&
           gate->acvp_algorithm_certificate_bound == 1u &&
           gate->cmvp_submission_identifier_recorded == 1u &&
           gate->module_boundary_review_recorded == 1u &&
           gate->reviewer_disposition_recorded == 1u &&
           gate->module_boundary_gate_accepted == 1u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->fips_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_module_boundary_gate_report(
    const latticra_q_seal_ml_kem_module_boundary_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM MODULE BOUNDARY GATE\n"
        "module_boundary_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "module_boundary_scope=%s\n"
        "module_boundary_state=%s\n"
        "module_boundary_gate_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "fips_140_3_module_security_bound=%u\n"
        "cmvp_program_bound=%u\n"
        "validation_claim_gate_bound=%u\n"
        "security_policy_gate_bound=%u\n"
        "acvp_verdict_receipt_gate_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "source_layout_gate_bound=%u\n"
        "implementation_file_digest_plan_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "zeroization_evidence_bound=%u\n"
        "randomness_source_bound=%u\n"
        "side_channel_review_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "module_boundary_schema_recorded=%u\n"
        "security_policy_template_recorded=%u\n"
        "services_roles_columns_recorded=%u\n"
        "operational_environment_columns_recorded=%u\n"
        "self_test_policy_columns_recorded=%u\n"
        "algorithm_certificate_columns_recorded=%u\n"
        "entropy_boundary_columns_recorded=%u\n"
        "zeroization_boundary_columns_recorded=%u\n"
        "source_digest_policy_bound=%u\n"
        "no_implicit_fips_claim_policy_recorded=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "module_boundary_evidence_recorded=%u\n"
        "cryptographic_module_name_recorded=%u\n"
        "module_version_recorded=%u\n"
        "operational_environment_recorded=%u\n"
        "fips_140_3_security_policy_recorded=%u\n"
        "roles_services_authentication_recorded=%u\n"
        "self_test_policy_recorded=%u\n"
        "approved_algorithm_inventory_recorded=%u\n"
        "entropy_source_boundary_recorded=%u\n"
        "zeroization_boundary_review_recorded=%u\n"
        "acvp_algorithm_certificate_bound=%u\n"
        "cmvp_submission_identifier_recorded=%u\n"
        "module_boundary_review_recorded=%u\n"
        "reviewer_disposition_recorded=%u\n"
        "module_boundary_gate_accepted=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_module_boundary_items_total=%u\n"
        "required_module_boundary_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->module_boundary_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->module_boundary_scope,
        gate->module_boundary_state,
        gate->module_boundary_gate_present,
        gate->fips_203_algorithm_bound,
        gate->fips_140_3_module_security_bound,
        gate->cmvp_program_bound,
        gate->validation_claim_gate_bound,
        gate->security_policy_gate_bound,
        gate->acvp_verdict_receipt_gate_bound,
        gate->ci_promotion_evidence_bound,
        gate->implementation_binding_manifest_bound,
        gate->source_layout_gate_bound,
        gate->implementation_file_digest_plan_bound,
        gate->source_digest_verification_bound,
        gate->zeroization_evidence_bound,
        gate->randomness_source_bound,
        gate->side_channel_review_bound,
        gate->code_owner_review_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->clean_room_source_boundary_recorded,
        gate->module_boundary_schema_recorded,
        gate->security_policy_template_recorded,
        gate->services_roles_columns_recorded,
        gate->operational_environment_columns_recorded,
        gate->self_test_policy_columns_recorded,
        gate->algorithm_certificate_columns_recorded,
        gate->entropy_boundary_columns_recorded,
        gate->zeroization_boundary_columns_recorded,
        gate->source_digest_policy_bound,
        gate->no_implicit_fips_claim_policy_recorded,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->module_boundary_evidence_recorded,
        gate->cryptographic_module_name_recorded,
        gate->module_version_recorded,
        gate->operational_environment_recorded,
        gate->fips_140_3_security_policy_recorded,
        gate->roles_services_authentication_recorded,
        gate->self_test_policy_recorded,
        gate->approved_algorithm_inventory_recorded,
        gate->entropy_source_boundary_recorded,
        gate->zeroization_boundary_review_recorded,
        gate->acvp_algorithm_certificate_bound,
        gate->cmvp_submission_identifier_recorded,
        gate->module_boundary_review_recorded,
        gate->reviewer_disposition_recorded,
        gate->module_boundary_gate_accepted,
        gate->production_crypto_claim_allowed,
        gate->fips_claim_allowed,
        gate->operation_execution_allowed,
        gate->runtime_authority_granted,
        gate->required_module_boundary_items_total,
        gate->required_module_boundary_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_module_boundary_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
