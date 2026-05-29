#include "latticra/q_seal_ml_kem_security_policy_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int security_policy_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_security_policy_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(gate.security_policy_gate_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            gate.security_policy_profile,
            "latticra-q-seal-ml-kem-security-policy-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(gate.formal_title, "Latticra Q-Seal ML-KEM Security Policy Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-140-3,NIST-SP-800-140B-REV-1,NIST-CMVP,NIST-FIPS-203,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(gate.fips_140_3_module_security_bound == 1u, "fips 140-3");
    EXPECT_TRUE(gate.sp800_140b_rev1_security_policy_bound == 1u, "sp 800-140b");
    EXPECT_TRUE(gate.cmvp_program_bound == 1u, "cmvp");
    EXPECT_TRUE(gate.fips_203_algorithm_bound == 1u, "fips 203");
    EXPECT_TRUE(gate.module_boundary_gate_bound == 1u, "module boundary");
    EXPECT_TRUE(gate.validation_claim_gate_bound == 1u, "claim");
    EXPECT_TRUE(gate.acvp_verdict_receipt_gate_bound == 1u, "acvp");
    EXPECT_TRUE(gate.source_digest_verification_bound == 1u, "digest");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "roles");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.security_policy_template_recorded == 1u, "template");
    EXPECT_TRUE(gate.non_proprietary_policy_required == 1u, "non proprietary");
    EXPECT_TRUE(gate.module_identification_section_required == 1u, "module section");
    EXPECT_TRUE(
        gate.cryptographic_module_specification_section_required == 1u,
        "spec section");
    EXPECT_TRUE(gate.approved_algorithms_section_required == 1u, "algorithms");
    EXPECT_TRUE(
        gate.roles_services_authentication_section_required == 1u,
        "services roles");
    EXPECT_TRUE(gate.software_firmware_security_section_required == 1u, "software");
    EXPECT_TRUE(gate.operational_environment_section_required == 1u, "environment section");
    EXPECT_TRUE(gate.self_tests_section_required == 1u, "self tests");
    EXPECT_TRUE(gate.entropy_boundary_section_required == 1u, "entropy section");
    EXPECT_TRUE(gate.life_cycle_assurance_section_required == 1u, "life cycle");
    EXPECT_TRUE(gate.mitigation_other_attacks_section_required == 1u, "mitigations");
    EXPECT_TRUE(gate.acronyms_references_section_required == 1u, "references");
    EXPECT_TRUE(gate.no_implicit_fips_claim_policy_recorded == 1u, "fips wording");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.security_policy_evidence_recorded == 0u, "policy evidence");
    EXPECT_TRUE(gate.security_policy_document_digest_recorded == 0u, "policy digest");
    EXPECT_TRUE(gate.module_name_version_recorded == 0u, "module version");
    EXPECT_TRUE(gate.security_level_table_recorded == 0u, "level table");
    EXPECT_TRUE(gate.approved_security_functions_table_recorded == 0u, "functions");
    EXPECT_TRUE(gate.services_roles_table_recorded == 0u, "services table");
    EXPECT_TRUE(gate.self_test_table_recorded == 0u, "self-test table");
    EXPECT_TRUE(gate.entropy_source_statement_recorded == 0u, "entropy statement");
    EXPECT_TRUE(gate.operational_environment_recorded == 0u, "environment");
    EXPECT_TRUE(gate.guidance_statement_recorded == 0u, "guidance");
    EXPECT_TRUE(gate.reviewer_disposition_recorded == 0u, "reviewer");
    EXPECT_TRUE(gate.security_policy_gate_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_security_policy_items_total == 41u, "total");
    EXPECT_TRUE(gate.required_security_policy_items_satisfied == 29u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_allows_policy_acceptance(&gate) == 0,
        "allows policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM SECURITY POLICY GATE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "security_policy_gate_present=1") != 0, "present");
    EXPECT_TRUE(
        strstr(rendered, "sp800_140b_rev1_security_policy_bound=1") != 0,
        "sp 800-140b report");
    EXPECT_TRUE(
        strstr(rendered, "security_policy_evidence_recorded=0") != 0,
        "policy evidence report");
    EXPECT_TRUE(
        strstr(rendered, "required_security_policy_items_total=41") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-security-policy-gate-blocked") != 0,
        "status");
    return 0;
}

static int security_policy_gate_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_security_policy_gate_t gate;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_allows_policy_acceptance(0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_security_policy_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (security_policy_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (security_policy_gate_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem security policy gate invariants: ok\n");
    return 0;
}
