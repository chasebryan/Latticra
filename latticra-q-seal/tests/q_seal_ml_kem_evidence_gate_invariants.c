#include "latticra/q_seal_ml_kem_evidence_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int evidence_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_evidence_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_prepare(&gate) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(gate.gate_profile, "latticra-q-seal-ml-kem-evidence-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(gate.formal_title, "Latticra Q-Seal ML-KEM Evidence Gate") == 0,
        "formal title");
    EXPECT_TRUE(strcmp(gate.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(strcmp(gate.standards_publication_date, "2024-08-13") == 0, "publication");
    EXPECT_TRUE(
        strcmp(gate.standards_errata_state, "errata-review-required") == 0,
        "errata");
    EXPECT_TRUE(
        strcmp(gate.kat_manifest_path, "latticra-q-seal/evidence/ML_KEM_KAT_MANIFEST.md") == 0,
        "kat manifest");
    EXPECT_TRUE(strcmp(gate.acvp_vector_source, "NIST-ACVP-required") == 0, "acvp");
    EXPECT_TRUE(gate.ml_kem_evidence_gate_present == 1u, "present");
    EXPECT_TRUE(gate.fips_203_source_verified == 1u, "source verified");
    EXPECT_TRUE(gate.fips_203_errata_review_required == 1u, "errata required");
    EXPECT_TRUE(gate.fips_203_errata_review_recorded == 0u, "errata not recorded");
    EXPECT_TRUE(gate.parameter_sets_recorded == 1u, "parameter sets");
    EXPECT_TRUE(gate.ml_kem_512_parameters_recorded == 1u, "512");
    EXPECT_TRUE(gate.ml_kem_768_parameters_recorded == 1u, "768");
    EXPECT_TRUE(gate.ml_kem_1024_parameters_recorded == 1u, "1024");
    EXPECT_TRUE(gate.known_answer_test_manifest_present == 1u, "kat manifest present");
    EXPECT_TRUE(gate.known_answer_vectors_embedded == 0u, "kat embedded");
    EXPECT_TRUE(gate.known_answer_vectors_loaded == 0u, "kat loaded");
    EXPECT_TRUE(gate.known_answer_vectors_verified == 0u, "kat verified");
    EXPECT_TRUE(gate.acvp_vector_review_required == 1u, "acvp required");
    EXPECT_TRUE(gate.acvp_vector_review_recorded == 0u, "acvp recorded");
    EXPECT_TRUE(gate.clean_room_required == 1u, "clean room required");
    EXPECT_TRUE(gate.clean_room_implementation_review_recorded == 0u, "clean review");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple code");
    EXPECT_TRUE(gate.provider_differential_test_contract_required == 1u, "provider diff");
    EXPECT_TRUE(gate.provider_differential_test_contract_recorded == 0u, "provider diff recorded");
    EXPECT_TRUE(gate.provider_linked == 0u, "provider linked");
    EXPECT_TRUE(gate.constant_time_review_required == 1u, "constant time required");
    EXPECT_TRUE(gate.constant_time_review_recorded == 0u, "constant time recorded");
    EXPECT_TRUE(gate.side_channel_review_required == 1u, "side channel required");
    EXPECT_TRUE(gate.side_channel_review_recorded == 0u, "side channel recorded");
    EXPECT_TRUE(gate.randomness_source_contract_required == 1u, "randomness required");
    EXPECT_TRUE(gate.randomness_source_contract_recorded == 0u, "randomness recorded");
    EXPECT_TRUE(gate.intermediate_zeroization_contract_required == 1u, "zeroization required");
    EXPECT_TRUE(gate.intermediate_zeroization_contract_recorded == 0u, "zeroization recorded");
    EXPECT_TRUE(gate.memory_safety_review_required == 1u, "memory required");
    EXPECT_TRUE(gate.memory_safety_review_recorded == 0u, "memory recorded");
    EXPECT_TRUE(gate.api_misuse_resistance_review_required == 1u, "api required");
    EXPECT_TRUE(gate.api_misuse_resistance_review_recorded == 0u, "api recorded");
    EXPECT_TRUE(gate.fuzzing_and_negative_tests_required == 1u, "fuzzing required");
    EXPECT_TRUE(gate.fuzzing_and_negative_tests_recorded == 0u, "fuzzing recorded");
    EXPECT_TRUE(gate.ci_quality_gate_required == 1u, "ci required");
    EXPECT_TRUE(gate.ci_quality_gate_recorded == 0u, "ci recorded");
    EXPECT_TRUE(gate.required_evidence_items_total == 16u, "evidence total");
    EXPECT_TRUE(gate.required_evidence_items_satisfied == 3u, "evidence satisfied");
    EXPECT_TRUE(gate.implementation_present == 0u, "implementation");
    EXPECT_TRUE(gate.operations_enabled == 0u, "operations");
    EXPECT_TRUE(gate.key_generation_enabled == 0u, "keygen");
    EXPECT_TRUE(gate.encapsulation_enabled == 0u, "encaps");
    EXPECT_TRUE(gate.decapsulation_enabled == 0u, "decaps");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(strcmp(gate.gate_state, "blocked-awaiting-evidence") == 0, "gate state");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE_BLOCKED, "blocked");
    EXPECT_TRUE(
        strcmp(latticra_q_seal_ml_kem_evidence_gate_error_label(gate.error), "blocked") == 0,
        "error label");
    EXPECT_TRUE(latticra_q_seal_ml_kem_evidence_gate_is_fail_closed(&gate) == 1, "fail closed");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_allows_operations(&gate) == 0,
        "allows operations");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_report(&gate, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM EVIDENCE GATE") != 0,
        "report header");
    EXPECT_TRUE(strstr(rendered, "standards_errata_state=errata-review-required") != 0, "report errata");
    EXPECT_TRUE(strstr(rendered, "known_answer_vectors_verified=0") != 0, "report kat");
    EXPECT_TRUE(strstr(rendered, "operations_enabled=0") != 0, "report operations");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-evidence-gate-fail-closed") != 0, "report status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_evidence_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_evidence_gate_is_fail_closed(0) == 0, "null fail closed");
    EXPECT_TRUE(latticra_q_seal_ml_kem_evidence_gate_allows_operations(0) == 0, "null allows");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_prepare(&gate) == LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_report(&gate, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report gate");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_gate_report(&gate, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (evidence_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem evidence gate invariants: ok\n");
    return 0;
}
