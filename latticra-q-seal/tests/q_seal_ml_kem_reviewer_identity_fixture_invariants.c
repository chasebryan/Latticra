#include "latticra/q_seal_ml_kem_reviewer_identity_fixture.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int reviewer_identity_fixture_is_fail_closed(void) {
    latticra_q_seal_ml_kem_reviewer_identity_fixture_t fixture;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            fixture.identity_profile,
            "latticra-q-seal-ml-kem-reviewer-identity-fixture/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            fixture.formal_title,
            "Latticra Q-Seal ML-KEM Reviewer Identity Fixture") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(fixture.standards_basis, "NIST-SP-800-218-SSDF-and-FIPS-203") == 0,
        "standards");
    EXPECT_TRUE(
        strcmp(fixture.identity_scope, "ML-KEM-reviewer-identity-import-before-promotion") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(fixture.identity_state, "reviewer-identity-import-fixture-blocked") == 0,
        "state");
    EXPECT_TRUE(fixture.reviewer_identity_fixture_present == 1u, "present");
    EXPECT_TRUE(fixture.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(fixture.ssdf_review_practice_bound == 1u, "ssdf");
    EXPECT_TRUE(fixture.clean_room_review_policy_recorded == 1u, "clean room");
    EXPECT_TRUE(fixture.code_owner_review_gate_bound == 1u, "owner gate");
    EXPECT_TRUE(fixture.review_disposition_ledger_bound == 1u, "ledger");
    EXPECT_TRUE(fixture.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(fixture.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(fixture.dual_reviewer_identity_required == 1u, "dual");
    EXPECT_TRUE(fixture.cryptography_reviewer_identity_required == 1u, "crypto");
    EXPECT_TRUE(fixture.security_reviewer_identity_required == 1u, "security");
    EXPECT_TRUE(fixture.code_owner_identity_required == 1u, "code owner");
    EXPECT_TRUE(fixture.reviewer_independence_required == 1u, "independence");
    EXPECT_TRUE(fixture.identity_schema_recorded == 1u, "schema");
    EXPECT_TRUE(fixture.identity_import_template_recorded == 1u, "template");
    EXPECT_TRUE(fixture.pii_minimization_policy_recorded == 1u, "pii");
    EXPECT_TRUE(fixture.reviewer_identities_imported == 0u, "identities");
    EXPECT_TRUE(fixture.cryptography_reviewer_identity_recorded == 0u, "crypto id");
    EXPECT_TRUE(fixture.security_reviewer_identity_recorded == 0u, "security id");
    EXPECT_TRUE(fixture.code_owner_identity_recorded == 0u, "owner id");
    EXPECT_TRUE(fixture.independence_attestation_recorded == 0u, "attestation");
    EXPECT_TRUE(fixture.identity_import_reviewed == 0u, "reviewed");
    EXPECT_TRUE(fixture.approval_authority_recorded == 0u, "approval authority");
    EXPECT_TRUE(fixture.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(fixture.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(fixture.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(fixture.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(fixture.required_identity_items_total == 23u, "total");
    EXPECT_TRUE(fixture.required_identity_items_satisfied == 16u, "satisfied");
    EXPECT_TRUE(fixture.error == LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_is_no_effect(&fixture) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_allows_implementation_promotion(
            &fixture) == 0,
        "allows promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_report(
            &fixture,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM REVIEWER IDENTITY FIXTURE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_identity_fixture_present=1") != 0,
        "present report");
    EXPECT_TRUE(strstr(rendered, "reviewer_identities_imported=0") != 0, "identity report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-reviewer-identity-fixture-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_reviewer_identity_fixture_t fixture;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_reviewer_identity_fixture_is_no_effect(0) == 0, "null effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_allows_implementation_promotion(0) ==
            0,
        "null promote");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_prepare(&fixture) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_report(
            &fixture,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report fixture");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_reviewer_identity_fixture_report(&fixture, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (reviewer_identity_fixture_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem reviewer identity fixture invariants: ok\n");
    return 0;
}
