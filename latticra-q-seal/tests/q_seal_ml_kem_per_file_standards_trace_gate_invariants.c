#include "latticra/q_seal_ml_kem_per_file_standards_trace_gate.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int per_file_standards_trace_gate_is_fail_closed(void) {
    latticra_q_seal_ml_kem_per_file_standards_trace_gate_t gate;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_STANDARDS_TRACE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            gate.standards_trace_profile,
            "latticra-q-seal-ml-kem-per-file-standards-trace-gate/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            gate.formal_title,
            "Latticra Q-Seal ML-KEM Per-File Standards Trace Gate") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            gate.standards_basis,
            "NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(strcmp(gate.source_boundary, "clean-room-no-apple-code") == 0, "boundary");
    EXPECT_TRUE(gate.per_file_standards_trace_gate_present == 1u, "present");
    EXPECT_TRUE(gate.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(gate.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(gate.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(gate.planned_source_units_count == 9u, "source units");
    EXPECT_TRUE(gate.planned_test_units_count == 9u, "test units");
    EXPECT_TRUE(gate.fips_conformance_matrix_bound == 1u, "fips");
    EXPECT_TRUE(gate.sp800_227_usage_profile_bound == 1u, "usage");
    EXPECT_TRUE(gate.implementation_traceability_matrix_bound == 1u, "traceability");
    EXPECT_TRUE(gate.implementation_file_digest_plan_bound == 1u, "file digest");
    EXPECT_TRUE(gate.clean_room_author_attestation_gate_bound == 1u, "author");
    EXPECT_TRUE(gate.primitive_source_acceptance_gate_bound == 1u, "source acceptance");
    EXPECT_TRUE(gate.source_digest_manifest_bound == 1u, "digest manifest");
    EXPECT_TRUE(gate.source_digest_receipt_bound == 1u, "digest receipt");
    EXPECT_TRUE(gate.code_owner_review_bound == 1u, "code owner");
    EXPECT_TRUE(gate.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(gate.reviewer_role_mapping_bound == 1u, "role");
    EXPECT_TRUE(gate.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(gate.fips203_clause_columns_recorded == 1u, "fips columns");
    EXPECT_TRUE(gate.sp800_227_usage_columns_recorded == 1u, "usage columns");
    EXPECT_TRUE(gate.parameter_set_columns_recorded == 1u, "parameter columns");
    EXPECT_TRUE(gate.operation_family_columns_recorded == 1u, "operation columns");
    EXPECT_TRUE(gate.acceptance_blocker_columns_recorded == 1u, "blocker columns");
    EXPECT_TRUE(gate.review_disposition_columns_recorded == 1u, "review columns");
    EXPECT_TRUE(gate.source_files_created == 0u, "source files");
    EXPECT_TRUE(gate.per_file_standards_trace_rows_recorded == 0u, "rows");
    EXPECT_TRUE(gate.fips203_clause_coverage_reviewed == 0u, "fips review");
    EXPECT_TRUE(gate.sp800_227_usage_coverage_reviewed == 0u, "usage review");
    EXPECT_TRUE(gate.parameter_set_coverage_reviewed == 0u, "parameter review");
    EXPECT_TRUE(gate.trace_review_approved == 0u, "trace review");
    EXPECT_TRUE(gate.per_file_standards_trace_accepted == 0u, "accepted");
    EXPECT_TRUE(gate.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(gate.shared_secret_emission_allowed == 0u, "shared secret");
    EXPECT_TRUE(gate.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(gate.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(gate.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(gate.required_standards_trace_items_total == 31u, "total");
    EXPECT_TRUE(gate.required_standards_trace_items_satisfied == 24u, "satisfied");
    EXPECT_TRUE(gate.error == LATTICRA_Q_SEAL_ML_KEM_STANDARDS_TRACE_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_is_no_effect(&gate) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_allows_trace_acceptance(
            &gate) == 0,
        "allows trace acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_report(
            &gate,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM PER-FILE STANDARDS TRACE GATE") != 0,
        "header");
    EXPECT_TRUE(
        strstr(rendered, "per_file_standards_trace_gate_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "fips203_clause_columns_recorded=1") != 0,
        "fips column report");
    EXPECT_TRUE(
        strstr(rendered, "per_file_standards_trace_accepted=0") != 0,
        "accepted report");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_emission_allowed=0") != 0,
        "shared secret report");
    EXPECT_TRUE(
        strstr(rendered, "required_standards_trace_items_total=31") != 0,
        "total report");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-per-file-standards-trace-gate-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_per_file_standards_trace_gate_t gate;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_allows_trace_acceptance(
            0) == 0,
        "null trace acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_prepare(&gate) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_report(
            &gate,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report gate");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_per_file_standards_trace_gate_report(
            &gate,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (per_file_standards_trace_gate_is_fail_closed() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem per-file standards trace gate invariants: ok\n");
    return 0;
}
