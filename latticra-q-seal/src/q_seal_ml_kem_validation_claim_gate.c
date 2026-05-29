#include "latticra/q_seal_ml_kem_validation_claim_gate.h"

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
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate) {
    unsigned satisfied = 0u;

    satisfied += one_if(gate->validation_claim_gate_present);
    satisfied += one_if(gate->fips_203_algorithm_bound);
    satisfied += one_if(gate->acvp_ml_kem_protocol_bound);
    satisfied += one_if(gate->acvp_verdict_receipt_gate_bound);
    satisfied += one_if(gate->replay_transcript_gate_bound);
    satisfied += one_if(gate->acvp_submission_package_contract_bound);
    satisfied += one_if(gate->ci_promotion_evidence_bound);
    satisfied += one_if(gate->implementation_binding_manifest_bound);
    satisfied += one_if(gate->readiness_profile_bound);
    satisfied += one_if(gate->module_boundary_gate_bound);
    satisfied += one_if(gate->security_policy_gate_bound);
    satisfied += one_if(gate->code_owner_review_bound);
    satisfied += one_if(gate->review_disposition_ledger_bound);
    satisfied += one_if(gate->reviewer_role_mapping_bound);
    satisfied += one_if(gate->source_digest_verification_bound);
    satisfied += one_if(gate->provider_differential_bound);
    satisfied += one_if(gate->clean_room_source_boundary_recorded);
    satisfied += one_if(gate->public_claim_taxonomy_recorded);
    satisfied += one_if(gate->no_implicit_fips_claim_policy_recorded);
    satisfied += one_if(gate->no_implicit_acvp_claim_policy_recorded);
    satisfied += one_if(gate->module_boundary_required);
    satisfied += one_if(gate->security_policy_required);
    satisfied += one_if(gate->acvp_certificate_or_validation_record_required);
    satisfied += one_if(gate->cmvp_certificate_required);
    satisfied += one_if(gate->implementation_digest_receipt_required);
    satisfied += one_if(gate->release_artifact_digest_required);
    satisfied += one_if(gate->release_notes_claim_review_required);
    satisfied += one_if(gate->docs_public_surface_review_required);
    satisfied += one_if(gate->operator_warning_required);
    satisfied += one_if(gate->rollback_claim_revocation_required);
    satisfied += one_if(gate->no_secret_material_logging_required);
    satisfied += one_if(gate->apple_corecrypto_code_copied == 0u);
    satisfied += one_if(gate->external_provider_code_copied == 0u);
    satisfied += one_if(gate->implementation_claim_evidence_recorded);
    satisfied += one_if(gate->acvp_pass_evidence_recorded);
    satisfied += one_if(gate->cmvp_certificate_recorded);
    satisfied += one_if(gate->module_boundary_recorded);
    satisfied += one_if(gate->security_policy_recorded);
    satisfied += one_if(gate->release_artifact_digest_recorded);
    satisfied += one_if(gate->public_claim_review_recorded);
    satisfied += one_if(gate->reviewer_disposition_recorded);
    satisfied += one_if(gate->validation_claim_gate_accepted);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_validation_claim_gate_error_label(
    latticra_q_seal_ml_kem_validation_claim_gate_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_validation_claim_gate_prepare(
    latticra_q_seal_ml_kem_validation_claim_gate_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->validation_claim_profile,
        sizeof(out->validation_claim_profile),
        "latticra-q-seal-ml-kem-validation-claim-gate/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Validation Claim Gate");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-CMVP,NIST-SP-800-218-SSDF");
    copy_literal(
        out->validation_claim_scope,
        sizeof(out->validation_claim_scope),
        "ML-KEM-public-validation-and-release-claims-before-publication");
    copy_literal(
        out->validation_claim_state,
        sizeof(out->validation_claim_state),
        "validation-claim-gate-recorded-claim-evidence-missing");

    out->validation_claim_gate_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->acvp_ml_kem_protocol_bound = 1u;
    out->acvp_verdict_receipt_gate_bound = 1u;
    out->replay_transcript_gate_bound = 1u;
    out->acvp_submission_package_contract_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->readiness_profile_bound = 1u;
    out->module_boundary_gate_bound = 1u;
    out->security_policy_gate_bound = 1u;
    out->code_owner_review_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_role_mapping_bound = 1u;
    out->source_digest_verification_bound = 1u;
    out->provider_differential_bound = 1u;
    out->clean_room_source_boundary_recorded = 1u;
    out->public_claim_taxonomy_recorded = 1u;
    out->no_implicit_fips_claim_policy_recorded = 1u;
    out->no_implicit_acvp_claim_policy_recorded = 1u;
    out->module_boundary_required = 1u;
    out->security_policy_required = 1u;
    out->acvp_certificate_or_validation_record_required = 1u;
    out->cmvp_certificate_required = 1u;
    out->implementation_digest_receipt_required = 1u;
    out->release_artifact_digest_required = 1u;
    out->release_notes_claim_review_required = 1u;
    out->docs_public_surface_review_required = 1u;
    out->operator_warning_required = 1u;
    out->rollback_claim_revocation_required = 1u;
    out->no_secret_material_logging_required = 1u;
    out->apple_corecrypto_code_copied = 0u;
    out->external_provider_code_copied = 0u;
    out->implementation_claim_evidence_recorded = 0u;
    out->acvp_pass_evidence_recorded = 0u;
    out->cmvp_certificate_recorded = 0u;
    out->module_boundary_recorded = 0u;
    out->security_policy_recorded = 0u;
    out->release_artifact_digest_recorded = 0u;
    out->public_claim_review_recorded = 0u;
    out->reviewer_disposition_recorded = 0u;
    out->validation_claim_gate_accepted = 0u;
    out->public_validation_claim_allowed = 0u;
    out->fips_validation_claim_allowed = 0u;
    out->post_quantum_migration_claim_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->operation_execution_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_validation_claim_items_total = 42u;
    out->required_validation_claim_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "implementation-acvp-cmvp-module-boundary-security-policy-release-artifact-public-claim-review-and-disposition-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_BLOCKED;
    copy_literal(
        out->status,
        sizeof(out->status),
        "ml-kem-validation-claim-gate-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_validation_claim_gate_is_no_effect(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->validation_claim_gate_present == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->implementation_claim_evidence_recorded == 0u &&
           gate->acvp_pass_evidence_recorded == 0u &&
           gate->cmvp_certificate_recorded == 0u &&
           gate->module_boundary_recorded == 0u &&
           gate->security_policy_recorded == 0u &&
           gate->release_artifact_digest_recorded == 0u &&
           gate->public_claim_review_recorded == 0u &&
           gate->reviewer_disposition_recorded == 0u &&
           gate->validation_claim_gate_accepted == 0u &&
           gate->public_validation_claim_allowed == 0u &&
           gate->fips_validation_claim_allowed == 0u &&
           gate->post_quantum_migration_claim_allowed == 0u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u &&
           gate->error == LATTICRA_Q_SEAL_ML_KEM_VALIDATION_CLAIM_BLOCKED;
}

int latticra_q_seal_ml_kem_validation_claim_gate_allows_validation_claims(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate) {
    if (gate == NULL) {
        return 0;
    }

    return gate->validation_claim_gate_present == 1u &&
           gate->fips_203_algorithm_bound == 1u &&
           gate->acvp_ml_kem_protocol_bound == 1u &&
           gate->acvp_verdict_receipt_gate_bound == 1u &&
           gate->replay_transcript_gate_bound == 1u &&
           gate->acvp_submission_package_contract_bound == 1u &&
           gate->ci_promotion_evidence_bound == 1u &&
           gate->implementation_binding_manifest_bound == 1u &&
           gate->readiness_profile_bound == 1u &&
           gate->module_boundary_gate_bound == 1u &&
           gate->security_policy_gate_bound == 1u &&
           gate->code_owner_review_bound == 1u &&
           gate->review_disposition_ledger_bound == 1u &&
           gate->reviewer_role_mapping_bound == 1u &&
           gate->source_digest_verification_bound == 1u &&
           gate->provider_differential_bound == 1u &&
           gate->clean_room_source_boundary_recorded == 1u &&
           gate->public_claim_taxonomy_recorded == 1u &&
           gate->no_implicit_fips_claim_policy_recorded == 1u &&
           gate->no_implicit_acvp_claim_policy_recorded == 1u &&
           gate->module_boundary_required == 1u &&
           gate->security_policy_required == 1u &&
           gate->acvp_certificate_or_validation_record_required == 1u &&
           gate->cmvp_certificate_required == 1u &&
           gate->implementation_digest_receipt_required == 1u &&
           gate->release_artifact_digest_required == 1u &&
           gate->release_notes_claim_review_required == 1u &&
           gate->docs_public_surface_review_required == 1u &&
           gate->operator_warning_required == 1u &&
           gate->rollback_claim_revocation_required == 1u &&
           gate->no_secret_material_logging_required == 1u &&
           gate->apple_corecrypto_code_copied == 0u &&
           gate->external_provider_code_copied == 0u &&
           gate->implementation_claim_evidence_recorded == 1u &&
           gate->acvp_pass_evidence_recorded == 1u &&
           gate->cmvp_certificate_recorded == 1u &&
           gate->module_boundary_recorded == 1u &&
           gate->security_policy_recorded == 1u &&
           gate->release_artifact_digest_recorded == 1u &&
           gate->public_claim_review_recorded == 1u &&
           gate->reviewer_disposition_recorded == 1u &&
           gate->validation_claim_gate_accepted == 1u &&
           gate->public_validation_claim_allowed == 1u &&
           gate->fips_validation_claim_allowed == 1u &&
           gate->post_quantum_migration_claim_allowed == 1u &&
           gate->production_crypto_claim_allowed == 0u &&
           gate->operation_execution_allowed == 0u &&
           gate->runtime_authority_granted == 0u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_validation_claim_gate_report(
    const latticra_q_seal_ml_kem_validation_claim_gate_t *gate,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (gate == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM VALIDATION CLAIM GATE\n"
        "validation_claim_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "validation_claim_scope=%s\n"
        "validation_claim_state=%s\n"
        "validation_claim_gate_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "acvp_ml_kem_protocol_bound=%u\n"
        "acvp_verdict_receipt_gate_bound=%u\n"
        "replay_transcript_gate_bound=%u\n"
        "acvp_submission_package_contract_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "readiness_profile_bound=%u\n"
        "module_boundary_gate_bound=%u\n"
        "security_policy_gate_bound=%u\n"
        "code_owner_review_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_role_mapping_bound=%u\n"
        "source_digest_verification_bound=%u\n"
        "provider_differential_bound=%u\n"
        "clean_room_source_boundary_recorded=%u\n"
        "public_claim_taxonomy_recorded=%u\n"
        "no_implicit_fips_claim_policy_recorded=%u\n"
        "no_implicit_acvp_claim_policy_recorded=%u\n"
        "module_boundary_required=%u\n"
        "security_policy_required=%u\n"
        "acvp_certificate_or_validation_record_required=%u\n"
        "cmvp_certificate_required=%u\n"
        "implementation_digest_receipt_required=%u\n"
        "release_artifact_digest_required=%u\n"
        "release_notes_claim_review_required=%u\n"
        "docs_public_surface_review_required=%u\n"
        "operator_warning_required=%u\n"
        "rollback_claim_revocation_required=%u\n"
        "no_secret_material_logging_required=%u\n"
        "apple_corecrypto_code_copied=%u\n"
        "external_provider_code_copied=%u\n"
        "implementation_claim_evidence_recorded=%u\n"
        "acvp_pass_evidence_recorded=%u\n"
        "cmvp_certificate_recorded=%u\n"
        "module_boundary_recorded=%u\n"
        "security_policy_recorded=%u\n"
        "release_artifact_digest_recorded=%u\n"
        "public_claim_review_recorded=%u\n"
        "reviewer_disposition_recorded=%u\n"
        "validation_claim_gate_accepted=%u\n"
        "public_validation_claim_allowed=%u\n"
        "fips_validation_claim_allowed=%u\n"
        "post_quantum_migration_claim_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "operation_execution_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_validation_claim_items_total=%u\n"
        "required_validation_claim_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        gate->validation_claim_profile,
        gate->formal_title,
        gate->standards_basis,
        gate->validation_claim_scope,
        gate->validation_claim_state,
        gate->validation_claim_gate_present,
        gate->fips_203_algorithm_bound,
        gate->acvp_ml_kem_protocol_bound,
        gate->acvp_verdict_receipt_gate_bound,
        gate->replay_transcript_gate_bound,
        gate->acvp_submission_package_contract_bound,
        gate->ci_promotion_evidence_bound,
        gate->implementation_binding_manifest_bound,
        gate->readiness_profile_bound,
        gate->module_boundary_gate_bound,
        gate->security_policy_gate_bound,
        gate->code_owner_review_bound,
        gate->review_disposition_ledger_bound,
        gate->reviewer_role_mapping_bound,
        gate->source_digest_verification_bound,
        gate->provider_differential_bound,
        gate->clean_room_source_boundary_recorded,
        gate->public_claim_taxonomy_recorded,
        gate->no_implicit_fips_claim_policy_recorded,
        gate->no_implicit_acvp_claim_policy_recorded,
        gate->module_boundary_required,
        gate->security_policy_required,
        gate->acvp_certificate_or_validation_record_required,
        gate->cmvp_certificate_required,
        gate->implementation_digest_receipt_required,
        gate->release_artifact_digest_required,
        gate->release_notes_claim_review_required,
        gate->docs_public_surface_review_required,
        gate->operator_warning_required,
        gate->rollback_claim_revocation_required,
        gate->no_secret_material_logging_required,
        gate->apple_corecrypto_code_copied,
        gate->external_provider_code_copied,
        gate->implementation_claim_evidence_recorded,
        gate->acvp_pass_evidence_recorded,
        gate->cmvp_certificate_recorded,
        gate->module_boundary_recorded,
        gate->security_policy_recorded,
        gate->release_artifact_digest_recorded,
        gate->public_claim_review_recorded,
        gate->reviewer_disposition_recorded,
        gate->validation_claim_gate_accepted,
        gate->public_validation_claim_allowed,
        gate->fips_validation_claim_allowed,
        gate->post_quantum_migration_claim_allowed,
        gate->production_crypto_claim_allowed,
        gate->operation_execution_allowed,
        gate->runtime_authority_granted,
        gate->required_validation_claim_items_total,
        gate->required_validation_claim_items_satisfied,
        gate->blocked_reason,
        latticra_q_seal_ml_kem_validation_claim_gate_error_label(gate->error),
        gate->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
