#include "latticra/q_seal_ml_kem_reviewer_role_mapping.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int reviewer_role_mapping_is_fail_closed(void) {
    latticra_q_seal_ml_kem_reviewer_role_mapping_t mapping;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(&mapping) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(mapping.reviewer_role_mapping_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            mapping.mapping_profile,
            "latticra-q-seal-ml-kem-reviewer-role-mapping/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(mapping.formal_title, "Latticra Q-Seal ML-KEM Reviewer Role Mapping") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(mapping.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(mapping.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(mapping.ssdf_review_practice_bound == 1u, "ssdf");
    EXPECT_TRUE(mapping.clean_room_review_policy_recorded == 1u, "clean room");
    EXPECT_TRUE(mapping.code_owner_review_gate_bound == 1u, "owner");
    EXPECT_TRUE(mapping.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(mapping.reviewer_identity_fixture_bound == 1u, "identity");
    EXPECT_TRUE(mapping.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(mapping.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(mapping.role_schema_recorded == 1u, "schema");
    EXPECT_TRUE(mapping.cryptography_role_required == 1u, "crypto role");
    EXPECT_TRUE(mapping.security_role_required == 1u, "security role");
    EXPECT_TRUE(mapping.code_owner_role_required == 1u, "owner role");
    EXPECT_TRUE(mapping.standards_traceability_role_required == 1u, "standards role");
    EXPECT_TRUE(mapping.side_channel_role_required == 1u, "side channel role");
    EXPECT_TRUE(mapping.source_digest_role_required == 1u, "digest role");
    EXPECT_TRUE(mapping.dual_reviewer_separation_required == 1u, "separation");
    EXPECT_TRUE(mapping.conflict_of_interest_policy_recorded == 1u, "conflict");
    EXPECT_TRUE(mapping.pii_minimization_policy_bound == 1u, "pii");
    EXPECT_TRUE(mapping.approval_authority_mapping_required == 1u, "approval");
    EXPECT_TRUE(mapping.reviewer_identities_imported == 0u, "identities");
    EXPECT_TRUE(mapping.role_mapping_records_imported == 0u, "records");
    EXPECT_TRUE(mapping.cryptography_role_mapped == 0u, "crypto mapped");
    EXPECT_TRUE(mapping.security_role_mapped == 0u, "security mapped");
    EXPECT_TRUE(mapping.code_owner_role_mapped == 0u, "owner mapped");
    EXPECT_TRUE(mapping.standards_traceability_role_mapped == 0u, "standards mapped");
    EXPECT_TRUE(mapping.side_channel_role_mapped == 0u, "side channel mapped");
    EXPECT_TRUE(mapping.source_digest_role_mapped == 0u, "digest mapped");
    EXPECT_TRUE(mapping.separation_review_recorded == 0u, "separation review");
    EXPECT_TRUE(mapping.approval_authority_mapped == 0u, "approval mapped");
    EXPECT_TRUE(mapping.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(mapping.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(mapping.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(mapping.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(mapping.required_role_mapping_items_total == 30u, "total");
    EXPECT_TRUE(mapping.required_role_mapping_items_satisfied == 20u, "satisfied");
    EXPECT_TRUE(
        mapping.error == LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING_BLOCKED,
        "error");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_is_no_effect(&mapping) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_allows_implementation_promotion(
            &mapping) == 0,
        "promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_report(
            &mapping,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_role_mapping_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_identity_fixture_bound=1") != 0,
        "identity report");
    EXPECT_TRUE(
        strstr(rendered, "role_mapping_records_imported=0") != 0,
        "records report");
    EXPECT_TRUE(
        strstr(rendered, "required_role_mapping_items_total=30") != 0,
        "total report");
    return 0;
}

static int reviewer_role_mapping_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_reviewer_role_mapping_t mapping;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_reviewer_role_mapping_is_no_effect(0) == 0, "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_allows_implementation_promotion(0) ==
            0,
        "null promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_prepare(&mapping) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_report(&mapping, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_role_mapping_report(&mapping, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (reviewer_role_mapping_is_fail_closed() != 0) {
        return 1;
    }
    if (reviewer_role_mapping_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem reviewer role mapping invariants: ok\n");
    return 0;
}
