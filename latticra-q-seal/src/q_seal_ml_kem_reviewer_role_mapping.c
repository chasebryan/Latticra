#include "latticra/q_seal_ml_kem_reviewer_role_mapping.h"

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
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping) {
    unsigned satisfied = 0u;

    satisfied += one_if(mapping->reviewer_role_mapping_present);
    satisfied += one_if(mapping->fips_203_algorithm_bound);
    satisfied += one_if(mapping->ssdf_review_practice_bound);
    satisfied += one_if(mapping->clean_room_review_policy_recorded);
    satisfied += one_if(mapping->code_owner_review_gate_bound);
    satisfied += one_if(mapping->review_disposition_ledger_bound);
    satisfied += one_if(mapping->reviewer_identity_fixture_bound);
    satisfied += one_if(mapping->implementation_binding_manifest_bound);
    satisfied += one_if(mapping->ci_promotion_evidence_bound);
    satisfied += one_if(mapping->role_schema_recorded);
    satisfied += one_if(mapping->cryptography_role_required);
    satisfied += one_if(mapping->security_role_required);
    satisfied += one_if(mapping->code_owner_role_required);
    satisfied += one_if(mapping->standards_traceability_role_required);
    satisfied += one_if(mapping->side_channel_role_required);
    satisfied += one_if(mapping->source_digest_role_required);
    satisfied += one_if(mapping->dual_reviewer_separation_required);
    satisfied += one_if(mapping->conflict_of_interest_policy_recorded);
    satisfied += one_if(mapping->pii_minimization_policy_bound);
    satisfied += one_if(mapping->approval_authority_mapping_required);
    satisfied += one_if(mapping->reviewer_identities_imported);
    satisfied += one_if(mapping->role_mapping_records_imported);
    satisfied += one_if(mapping->cryptography_role_mapped);
    satisfied += one_if(mapping->security_role_mapped);
    satisfied += one_if(mapping->code_owner_role_mapped);
    satisfied += one_if(mapping->standards_traceability_role_mapped);
    satisfied += one_if(mapping->side_channel_role_mapped);
    satisfied += one_if(mapping->source_digest_role_mapped);
    satisfied += one_if(mapping->separation_review_recorded);
    satisfied += one_if(mapping->approval_authority_mapped);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_reviewer_role_mapping_error_label(
    latticra_q_seal_ml_kem_reviewer_role_mapping_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(
    latticra_q_seal_ml_kem_reviewer_role_mapping_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->mapping_profile,
        sizeof(out->mapping_profile),
        "latticra-q-seal-ml-kem-reviewer-role-mapping/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Reviewer Role Mapping");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->mapping_scope,
        sizeof(out->mapping_scope),
        "ML-KEM-reviewer-role-mapping-before-promotion");
    copy_literal(
        out->mapping_state,
        sizeof(out->mapping_state),
        "reviewer-role-mapping-fixture-blocked");

    out->reviewer_role_mapping_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_review_practice_bound = 1u;
    out->clean_room_review_policy_recorded = 1u;
    out->code_owner_review_gate_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->reviewer_identity_fixture_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->role_schema_recorded = 1u;
    out->cryptography_role_required = 1u;
    out->security_role_required = 1u;
    out->code_owner_role_required = 1u;
    out->standards_traceability_role_required = 1u;
    out->side_channel_role_required = 1u;
    out->source_digest_role_required = 1u;
    out->dual_reviewer_separation_required = 1u;
    out->conflict_of_interest_policy_recorded = 1u;
    out->pii_minimization_policy_bound = 1u;
    out->approval_authority_mapping_required = 1u;
    out->reviewer_identities_imported = 0u;
    out->role_mapping_records_imported = 0u;
    out->cryptography_role_mapped = 0u;
    out->security_role_mapped = 0u;
    out->code_owner_role_mapped = 0u;
    out->standards_traceability_role_mapped = 0u;
    out->side_channel_role_mapped = 0u;
    out->source_digest_role_mapped = 0u;
    out->separation_review_recorded = 0u;
    out->approval_authority_mapped = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_role_mapping_items_total = 30u;
    out->required_role_mapping_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "reviewer-identities-role-records-separation-and-approval-authority-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-reviewer-role-mapping-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_reviewer_role_mapping_is_no_effect(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping) {
    if (mapping == NULL) {
        return 0;
    }

    return mapping->reviewer_role_mapping_present == 1u &&
           mapping->operation_execution_allowed == 0u &&
           mapping->production_crypto_claim_allowed == 0u &&
           mapping->fips_claim_allowed == 0u &&
           mapping->runtime_authority_granted == 0u &&
           mapping->error == LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_BLOCKED;
}

int latticra_q_seal_ml_kem_reviewer_role_mapping_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping) {
    if (mapping == NULL) {
        return 0;
    }

    return mapping->reviewer_role_mapping_present == 1u &&
           mapping->fips_203_algorithm_bound == 1u &&
           mapping->ssdf_review_practice_bound == 1u &&
           mapping->clean_room_review_policy_recorded == 1u &&
           mapping->code_owner_review_gate_bound == 1u &&
           mapping->review_disposition_ledger_bound == 1u &&
           mapping->reviewer_identity_fixture_bound == 1u &&
           mapping->implementation_binding_manifest_bound == 1u &&
           mapping->ci_promotion_evidence_bound == 1u &&
           mapping->role_schema_recorded == 1u &&
           mapping->cryptography_role_required == 1u &&
           mapping->security_role_required == 1u &&
           mapping->code_owner_role_required == 1u &&
           mapping->standards_traceability_role_required == 1u &&
           mapping->side_channel_role_required == 1u &&
           mapping->source_digest_role_required == 1u &&
           mapping->dual_reviewer_separation_required == 1u &&
           mapping->conflict_of_interest_policy_recorded == 1u &&
           mapping->pii_minimization_policy_bound == 1u &&
           mapping->approval_authority_mapping_required == 1u &&
           mapping->reviewer_identities_imported == 1u &&
           mapping->role_mapping_records_imported == 1u &&
           mapping->cryptography_role_mapped == 1u &&
           mapping->security_role_mapped == 1u &&
           mapping->code_owner_role_mapped == 1u &&
           mapping->standards_traceability_role_mapped == 1u &&
           mapping->side_channel_role_mapped == 1u &&
           mapping->source_digest_role_mapped == 1u &&
           mapping->separation_review_recorded == 1u &&
           mapping->approval_authority_mapped == 1u &&
           mapping->operation_execution_allowed == 1u &&
           mapping->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_role_mapping_report(
    const latticra_q_seal_ml_kem_reviewer_role_mapping_t *mapping,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (mapping == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM REVIEWER ROLE MAPPING\n"
        "mapping_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "mapping_scope=%s\n"
        "mapping_state=%s\n"
        "reviewer_role_mapping_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_review_practice_bound=%u\n"
        "clean_room_review_policy_recorded=%u\n"
        "code_owner_review_gate_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "reviewer_identity_fixture_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "role_schema_recorded=%u\n"
        "cryptography_role_required=%u\n"
        "security_role_required=%u\n"
        "code_owner_role_required=%u\n"
        "standards_traceability_role_required=%u\n"
        "side_channel_role_required=%u\n"
        "source_digest_role_required=%u\n"
        "dual_reviewer_separation_required=%u\n"
        "conflict_of_interest_policy_recorded=%u\n"
        "pii_minimization_policy_bound=%u\n"
        "approval_authority_mapping_required=%u\n"
        "reviewer_identities_imported=%u\n"
        "role_mapping_records_imported=%u\n"
        "cryptography_role_mapped=%u\n"
        "security_role_mapped=%u\n"
        "code_owner_role_mapped=%u\n"
        "standards_traceability_role_mapped=%u\n"
        "side_channel_role_mapped=%u\n"
        "source_digest_role_mapped=%u\n"
        "separation_review_recorded=%u\n"
        "approval_authority_mapped=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_role_mapping_items_total=%u\n"
        "required_role_mapping_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        mapping->mapping_profile,
        mapping->formal_title,
        mapping->standards_basis,
        mapping->mapping_scope,
        mapping->mapping_state,
        mapping->reviewer_role_mapping_present,
        mapping->fips_203_algorithm_bound,
        mapping->ssdf_review_practice_bound,
        mapping->clean_room_review_policy_recorded,
        mapping->code_owner_review_gate_bound,
        mapping->review_disposition_ledger_bound,
        mapping->reviewer_identity_fixture_bound,
        mapping->implementation_binding_manifest_bound,
        mapping->ci_promotion_evidence_bound,
        mapping->role_schema_recorded,
        mapping->cryptography_role_required,
        mapping->security_role_required,
        mapping->code_owner_role_required,
        mapping->standards_traceability_role_required,
        mapping->side_channel_role_required,
        mapping->source_digest_role_required,
        mapping->dual_reviewer_separation_required,
        mapping->conflict_of_interest_policy_recorded,
        mapping->pii_minimization_policy_bound,
        mapping->approval_authority_mapping_required,
        mapping->reviewer_identities_imported,
        mapping->role_mapping_records_imported,
        mapping->cryptography_role_mapped,
        mapping->security_role_mapped,
        mapping->code_owner_role_mapped,
        mapping->standards_traceability_role_mapped,
        mapping->side_channel_role_mapped,
        mapping->source_digest_role_mapped,
        mapping->separation_review_recorded,
        mapping->approval_authority_mapped,
        mapping->operation_execution_allowed,
        mapping->production_crypto_claim_allowed,
        mapping->fips_claim_allowed,
        mapping->runtime_authority_granted,
        mapping->required_role_mapping_items_total,
        mapping->required_role_mapping_items_satisfied,
        mapping->blocked_reason,
        latticra_q_seal_ml_kem_reviewer_role_mapping_error_label(mapping->error),
        mapping->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
