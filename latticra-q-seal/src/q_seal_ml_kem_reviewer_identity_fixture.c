#include "latticra/q_seal_ml_kem_reviewer_identity_fixture.h"

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
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture) {
    unsigned satisfied = 0u;

    satisfied += one_if(fixture->reviewer_identity_fixture_present);
    satisfied += one_if(fixture->fips_203_algorithm_bound);
    satisfied += one_if(fixture->ssdf_review_practice_bound);
    satisfied += one_if(fixture->clean_room_review_policy_recorded);
    satisfied += one_if(fixture->code_owner_review_gate_bound);
    satisfied += one_if(fixture->review_disposition_ledger_bound);
    satisfied += one_if(fixture->implementation_binding_manifest_bound);
    satisfied += one_if(fixture->ci_promotion_evidence_bound);
    satisfied += one_if(fixture->dual_reviewer_identity_required);
    satisfied += one_if(fixture->cryptography_reviewer_identity_required);
    satisfied += one_if(fixture->security_reviewer_identity_required);
    satisfied += one_if(fixture->code_owner_identity_required);
    satisfied += one_if(fixture->reviewer_independence_required);
    satisfied += one_if(fixture->identity_schema_recorded);
    satisfied += one_if(fixture->identity_import_template_recorded);
    satisfied += one_if(fixture->pii_minimization_policy_recorded);
    satisfied += one_if(fixture->reviewer_identities_imported);
    satisfied += one_if(fixture->cryptography_reviewer_identity_recorded);
    satisfied += one_if(fixture->security_reviewer_identity_recorded);
    satisfied += one_if(fixture->code_owner_identity_recorded);
    satisfied += one_if(fixture->independence_attestation_recorded);
    satisfied += one_if(fixture->identity_import_reviewed);
    satisfied += one_if(fixture->approval_authority_recorded);

    return satisfied;
}

const char *latticra_q_seal_ml_kem_reviewer_identity_fixture_error_label(
    latticra_q_seal_ml_kem_reviewer_identity_fixture_error_t error) {
    switch (error) {
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_OK:
        return "ok";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_BLOCKED:
        return "blocked";
    case LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_INVALID_INPUT:
        return "invalid-input";
    default:
        return "unknown";
    }
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(
    latticra_q_seal_ml_kem_reviewer_identity_fixture_t *out) {
    if (out == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(
        out->identity_profile,
        sizeof(out->identity_profile),
        "latticra-q-seal-ml-kem-reviewer-identity-fixture/0.1");
    copy_literal(
        out->formal_title,
        sizeof(out->formal_title),
        "Latticra Q-Seal ML-KEM Reviewer Identity Fixture");
    copy_literal(
        out->standards_basis,
        sizeof(out->standards_basis),
        "NIST-SP-800-218-SSDF-and-FIPS-203");
    copy_literal(
        out->identity_scope,
        sizeof(out->identity_scope),
        "ML-KEM-reviewer-identity-import-before-promotion");
    copy_literal(
        out->identity_state,
        sizeof(out->identity_state),
        "reviewer-identity-import-fixture-blocked");

    out->reviewer_identity_fixture_present = 1u;
    out->fips_203_algorithm_bound = 1u;
    out->ssdf_review_practice_bound = 1u;
    out->clean_room_review_policy_recorded = 1u;
    out->code_owner_review_gate_bound = 1u;
    out->review_disposition_ledger_bound = 1u;
    out->implementation_binding_manifest_bound = 1u;
    out->ci_promotion_evidence_bound = 1u;
    out->dual_reviewer_identity_required = 1u;
    out->cryptography_reviewer_identity_required = 1u;
    out->security_reviewer_identity_required = 1u;
    out->code_owner_identity_required = 1u;
    out->reviewer_independence_required = 1u;
    out->identity_schema_recorded = 1u;
    out->identity_import_template_recorded = 1u;
    out->pii_minimization_policy_recorded = 1u;
    out->reviewer_identities_imported = 0u;
    out->cryptography_reviewer_identity_recorded = 0u;
    out->security_reviewer_identity_recorded = 0u;
    out->code_owner_identity_recorded = 0u;
    out->independence_attestation_recorded = 0u;
    out->identity_import_reviewed = 0u;
    out->approval_authority_recorded = 0u;
    out->operation_execution_allowed = 0u;
    out->production_crypto_claim_allowed = 0u;
    out->fips_claim_allowed = 0u;
    out->runtime_authority_granted = 0u;
    out->required_identity_items_total = 23u;
    out->required_identity_items_satisfied = required_items_satisfied(out);
    copy_literal(
        out->blocked_reason,
        sizeof(out->blocked_reason),
        "reviewer-identities-role-mapping-independence-import-review-and-approval-authority-missing");
    out->error = LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_BLOCKED;
    copy_literal(out->status, sizeof(out->status), "ml-kem-reviewer-identity-fixture-blocked");
    return LATTICRA_Q_SEAL_STATUS_OK;
}

int latticra_q_seal_ml_kem_reviewer_identity_fixture_is_no_effect(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->reviewer_identity_fixture_present == 1u &&
           fixture->operation_execution_allowed == 0u &&
           fixture->production_crypto_claim_allowed == 0u &&
           fixture->fips_claim_allowed == 0u &&
           fixture->runtime_authority_granted == 0u &&
           fixture->error == LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_BLOCKED;
}

int latticra_q_seal_ml_kem_reviewer_identity_fixture_allows_implementation_promotion(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture) {
    if (fixture == NULL) {
        return 0;
    }

    return fixture->reviewer_identity_fixture_present == 1u &&
           fixture->fips_203_algorithm_bound == 1u &&
           fixture->ssdf_review_practice_bound == 1u &&
           fixture->clean_room_review_policy_recorded == 1u &&
           fixture->code_owner_review_gate_bound == 1u &&
           fixture->review_disposition_ledger_bound == 1u &&
           fixture->implementation_binding_manifest_bound == 1u &&
           fixture->ci_promotion_evidence_bound == 1u &&
           fixture->dual_reviewer_identity_required == 1u &&
           fixture->cryptography_reviewer_identity_required == 1u &&
           fixture->security_reviewer_identity_required == 1u &&
           fixture->code_owner_identity_required == 1u &&
           fixture->reviewer_independence_required == 1u &&
           fixture->identity_schema_recorded == 1u &&
           fixture->identity_import_template_recorded == 1u &&
           fixture->pii_minimization_policy_recorded == 1u &&
           fixture->reviewer_identities_imported == 1u &&
           fixture->cryptography_reviewer_identity_recorded == 1u &&
           fixture->security_reviewer_identity_recorded == 1u &&
           fixture->code_owner_identity_recorded == 1u &&
           fixture->independence_attestation_recorded == 1u &&
           fixture->identity_import_reviewed == 1u &&
           fixture->approval_authority_recorded == 1u &&
           fixture->operation_execution_allowed == 1u &&
           fixture->runtime_authority_granted == 1u;
}

latticra_q_seal_status_t latticra_q_seal_ml_kem_reviewer_identity_fixture_report(
    const latticra_q_seal_ml_kem_reviewer_identity_fixture_t *fixture,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (fixture == NULL || buffer == NULL) {
        return LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA Q-SEAL ML-KEM REVIEWER IDENTITY FIXTURE\n"
        "identity_profile=%s\n"
        "formal_title=%s\n"
        "standards_basis=%s\n"
        "identity_scope=%s\n"
        "identity_state=%s\n"
        "reviewer_identity_fixture_present=%u\n"
        "fips_203_algorithm_bound=%u\n"
        "ssdf_review_practice_bound=%u\n"
        "clean_room_review_policy_recorded=%u\n"
        "code_owner_review_gate_bound=%u\n"
        "review_disposition_ledger_bound=%u\n"
        "implementation_binding_manifest_bound=%u\n"
        "ci_promotion_evidence_bound=%u\n"
        "dual_reviewer_identity_required=%u\n"
        "cryptography_reviewer_identity_required=%u\n"
        "security_reviewer_identity_required=%u\n"
        "code_owner_identity_required=%u\n"
        "reviewer_independence_required=%u\n"
        "identity_schema_recorded=%u\n"
        "identity_import_template_recorded=%u\n"
        "pii_minimization_policy_recorded=%u\n"
        "reviewer_identities_imported=%u\n"
        "cryptography_reviewer_identity_recorded=%u\n"
        "security_reviewer_identity_recorded=%u\n"
        "code_owner_identity_recorded=%u\n"
        "independence_attestation_recorded=%u\n"
        "identity_import_reviewed=%u\n"
        "approval_authority_recorded=%u\n"
        "operation_execution_allowed=%u\n"
        "production_crypto_claim_allowed=%u\n"
        "fips_claim_allowed=%u\n"
        "runtime_authority_granted=%u\n"
        "required_identity_items_total=%u\n"
        "required_identity_items_satisfied=%u\n"
        "blocked_reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        fixture->identity_profile,
        fixture->formal_title,
        fixture->standards_basis,
        fixture->identity_scope,
        fixture->identity_state,
        fixture->reviewer_identity_fixture_present,
        fixture->fips_203_algorithm_bound,
        fixture->ssdf_review_practice_bound,
        fixture->clean_room_review_policy_recorded,
        fixture->code_owner_review_gate_bound,
        fixture->review_disposition_ledger_bound,
        fixture->implementation_binding_manifest_bound,
        fixture->ci_promotion_evidence_bound,
        fixture->dual_reviewer_identity_required,
        fixture->cryptography_reviewer_identity_required,
        fixture->security_reviewer_identity_required,
        fixture->code_owner_identity_required,
        fixture->reviewer_independence_required,
        fixture->identity_schema_recorded,
        fixture->identity_import_template_recorded,
        fixture->pii_minimization_policy_recorded,
        fixture->reviewer_identities_imported,
        fixture->cryptography_reviewer_identity_recorded,
        fixture->security_reviewer_identity_recorded,
        fixture->code_owner_identity_recorded,
        fixture->independence_attestation_recorded,
        fixture->identity_import_reviewed,
        fixture->approval_authority_recorded,
        fixture->operation_execution_allowed,
        fixture->production_crypto_claim_allowed,
        fixture->fips_claim_allowed,
        fixture->runtime_authority_granted,
        fixture->required_identity_items_total,
        fixture->required_identity_items_satisfied,
        fixture->blocked_reason,
        latticra_q_seal_ml_kem_reviewer_identity_fixture_error_label(fixture->error),
        fixture->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_Q_SEAL_STATUS_OK;
}
