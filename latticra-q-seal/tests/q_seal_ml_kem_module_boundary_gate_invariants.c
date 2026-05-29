#include "latticra/q_seal_ml_kem_module_boundary_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int module_boundary_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_module_boundary_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.module_boundary_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.module_boundary_profile,
            "latticra-q-seal-ml-kem-module-boundary-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(gate.formal_title, "Latticra Q-Seal ML-KEM Module Boundary Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-FIPS-140-3,NIST-CMVP,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips 203");
    EXPECT_TRUE(gate.fips_140_3_module_security_bound == 1u, "fips 140-3");
    EXPECT_TRUE(gate.cmvp_program_bound == 1u, "cmvp");
    EXPECT_TRUE(gate.validation_claim_gate_bound == 1u, "claim gate");
    EXPECT_TRUE(gate.security_policy_gate_bound == 1u, "security policy gate");
    EXPECT_TRUE(gate.acvp_verdict_receipt_gate_bound == 1u, "acvp verdict");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(gate.source_layout_gate_bound == 1u, "layout");
    EXPECT_TRUE(gate.implementation_file_digest_plan_bound == 1u, "digest plan");
    EXPECT_TRUE(gate.source_digest_verification_bound == 1u, "source digest");
    EXPECT_TRUE(gate.zeroization_evidence_bound == 1u, "zeroization");
    EXPECT_TRUE(gate.randomness_source_bound == 1u, "randomness");
    EXPECT_TRUE(gate.side_channel_review_bound == 1u, "side channel");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "roles");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.module_boundary_schema_recorded == 1u, "schema");
    EXPECT_TRUE(gate.security_policy_template_recorded == 1u, "policy template");
    EXPECT_TRUE(gate.services_roles_columns_recorded == 1u, "services roles");
    EXPECT_TRUE(gate.operational_environment_columns_recorded == 1u, "environment columns");
    EXPECT_TRUE(gate.self_test_policy_columns_recorded == 1u, "self test columns");
    EXPECT_TRUE(gate.algorithm_certificate_columns_recorded == 1u, "algorithm columns");
    EXPECT_TRUE(gate.entropy_boundary_columns_recorded == 1u, "entropy columns");
    EXPECT_TRUE(gate.zeroization_boundary_columns_recorded == 1u, "zeroization columns");
    EXPECT_TRUE(gate.source_digest_policy_bound == 1u, "digest policy");
    EXPECT_TRUE(gate.no_implicit_fips_claim_policy_recorded == 1u, "claim policy");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.module_boundary_evidence_recorded == 0u, "boundary evidence");
    EXPECT_TRUE(gate.cryptographic_module_name_recorded == 0u, "module name");
    EXPECT_TRUE(gate.module_version_recorded == 0u, "module version");
    EXPECT_TRUE(gate.operational_environment_recorded == 0u, "environment");
    EXPECT_TRUE(gate.fips_140_3_security_policy_recorded == 0u, "security policy");
    EXPECT_TRUE(gate.roles_services_authentication_recorded == 0u, "roles services");
    EXPECT_TRUE(gate.self_test_policy_recorded == 0u, "self test policy");
    EXPECT_TRUE(gate.approved_algorithm_inventory_recorded == 0u, "algorithm inventory");
    EXPECT_TRUE(gate.entropy_source_boundary_recorded == 0u, "entropy boundary");
    EXPECT_TRUE(gate.zeroization_boundary_review_recorded == 0u, "zeroization review");
    EXPECT_TRUE(gate.acvp_algorithm_certificate_bound == 0u, "algorithm certificate");
    EXPECT_TRUE(gate.cmvp_submission_identifier_recorded == 0u, "cmvp id");
    EXPECT_TRUE(gate.module_boundary_review_recorded == 0u, "boundary review");
    EXPECT_TRUE(gate.reviewer_disposition_recorded == 0u, "reviewer disposition");
    EXPECT_TRUE(gate.module_boundary_gate_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_module_boundary_items_total == 46u, "total");
    EXPECT_TRUE(gate.required_module_boundary_items_satisfied == 31u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_MODULE_BOUNDARY_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_allows_boundary_acceptance(&gate) == 0,
        "allows boundary");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM MODULE BOUNDARY GATE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "module_boundary_gate_present=1") != 0, "present");
    EXPECT_TRUE(
        strstr(rendered, "security_policy_gate_bound=1") != 0,
        "security policy gate report");
    EXPECT_TRUE(
        strstr(rendered, "fips_140_3_security_policy_recorded=0") != 0,
        "policy");
    EXPECT_TRUE(
        strstr(rendered, "required_module_boundary_items_total=46") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-module-boundary-gate-blocked") != 0,
        "status");
    return 0;
}

static int module_boundary_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_module_boundary_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_allows_boundary_acceptance(0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_module_boundary_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (module_boundary_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (module_boundary_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem module boundary gate invariants: ok\n");
    return 0;
}
