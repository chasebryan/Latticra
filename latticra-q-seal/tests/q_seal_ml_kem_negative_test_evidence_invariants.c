#include "latticra/q_seal_ml_kem_negative_test_evidence.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int negative_test_evidence_records_policy_without_execution(void) {
    latticra_q_seal_ml_kem_negative_test_evidence_t evidence;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            evidence.evidence_profile,
            "latticra-q-seal-ml-kem-negative-test-evidence/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(evidence.formal_title, "Latticra Q-Seal ML-KEM Negative-Test Evidence") == 0,
        "title");
    EXPECT_TRUE(strcmp(evidence.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(strcmp(evidence.acvp_source, "NIST-ACVP-ML-KEM") == 0, "acvp");
    EXPECT_TRUE(
        strcmp(evidence.evidence_scope, "ML-KEM-malformed-input-negative-vector-behavior") == 0,
        "scope");
    EXPECT_TRUE(
        strcmp(evidence.evidence_state, "policy-recorded-test-execution-missing") == 0,
        "state");
    EXPECT_TRUE(evidence.negative_test_evidence_present == 1u, "present");
    EXPECT_TRUE(evidence.fips_203_source_verified == 1u, "fips 203");
    EXPECT_TRUE(evidence.acvp_ml_kem_schema_tracked == 1u, "acvp schema");
    EXPECT_TRUE(evidence.vector_schema_bound == 1u, "vector schema");
    EXPECT_TRUE(evidence.vector_source_bound == 1u, "vector source");
    EXPECT_TRUE(evidence.malformed_ciphertext_tests_required == 1u, "ciphertext required");
    EXPECT_TRUE(evidence.malformed_key_tests_required == 1u, "key required");
    EXPECT_TRUE(evidence.negative_replay_tests_required == 1u, "replay required");
    EXPECT_TRUE(evidence.length_validation_tests_recorded == 0u, "length");
    EXPECT_TRUE(evidence.encoding_canonicality_tests_recorded == 0u, "encoding");
    EXPECT_TRUE(evidence.invalid_ciphertext_tests_recorded == 0u, "ciphertext");
    EXPECT_TRUE(evidence.invalid_public_key_tests_recorded == 0u, "public key");
    EXPECT_TRUE(evidence.invalid_secret_key_tests_recorded == 0u, "secret key");
    EXPECT_TRUE(evidence.decapsulation_failure_tests_recorded == 0u, "decap failure");
    EXPECT_TRUE(evidence.implicit_rejection_tests_recorded == 0u, "implicit rejection");
    EXPECT_TRUE(evidence.parser_rejection_tests_recorded == 0u, "parser rejection");
    EXPECT_TRUE(evidence.fuzzing_corpus_recorded == 0u, "fuzzing");
    EXPECT_TRUE(evidence.differential_negative_tests_recorded == 0u, "differential");
    EXPECT_TRUE(evidence.implementation_binding_recorded == 0u, "binding");
    EXPECT_TRUE(evidence.negative_tests_executed == 0u, "executed");
    EXPECT_TRUE(evidence.parser_execution_allowed == 0u, "parser execution");
    EXPECT_TRUE(evidence.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(evidence.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(evidence.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(evidence.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(evidence.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(evidence.required_negative_test_items_total == 18u, "total");
    EXPECT_TRUE(evidence.required_negative_test_items_satisfied == 7u, "satisfied");
    EXPECT_TRUE(evidence.error == LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_is_policy_only(&evidence) == 1,
        "policy only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(
            &evidence) == 0,
        "promotion helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_report(
            &evidence,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM NEGATIVE-TEST EVIDENCE") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "negative_test_evidence_present=1") != 0, "present report");
    EXPECT_TRUE(strstr(rendered, "negative_tests_executed=0") != 0, "executed report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-negative-test-evidence-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_negative_test_evidence_t evidence;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_is_policy_only(0) == 0,
        "null policy");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_allows_implementation_promotion(0) == 0,
        "null promotion");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_prepare(&evidence) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_report(&evidence, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report evidence");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_negative_test_evidence_report(&evidence, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (negative_test_evidence_records_policy_without_execution() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem negative-test evidence invariants: ok\n");
    return 0;
}
