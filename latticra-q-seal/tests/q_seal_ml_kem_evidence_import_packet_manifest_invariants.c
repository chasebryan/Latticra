#include "latticra/q_seal_ml_kem_evidence_import_packet_manifest.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int evidence_import_packet_manifest_is_fail_closed(void) {
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_t manifest;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(manifest.evidence_import_packet_manifest_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            manifest.evidence_packet_profile,
            "latticra-q-seal-ml-kem-evidence-import-packet-manifest/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            manifest.formal_title,
            "Latticra Q-Seal ML-KEM Evidence Import Packet Manifest") == 0,
        "title");
    EXPECT_TRUE(
        strcmp(
            manifest.standards_basis,
            "NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF") == 0,
        "standards");
    EXPECT_TRUE(manifest.fips_203_algorithm_bound == 1u, "fips");
    EXPECT_TRUE(manifest.acvp_ml_kem_schema_bound == 1u, "acvp");
    EXPECT_TRUE(manifest.evidence_import_review_gate_bound == 1u, "review gate");
    EXPECT_TRUE(manifest.vector_fixture_digest_ledger_bound == 1u, "fixture ledger");
    EXPECT_TRUE(manifest.receipt_replay_results_bound == 1u, "receipt replay");
    EXPECT_TRUE(manifest.source_digest_receipt_bound == 1u, "source receipt");
    EXPECT_TRUE(manifest.source_digest_verification_bound == 1u, "source verification");
    EXPECT_TRUE(manifest.reviewer_identity_fixture_bound == 1u, "identity");
    EXPECT_TRUE(manifest.reviewer_role_mapping_bound == 1u, "role mapping");
    EXPECT_TRUE(manifest.review_disposition_ledger_bound == 1u, "disposition");
    EXPECT_TRUE(manifest.implementation_binding_manifest_bound == 1u, "binding");
    EXPECT_TRUE(manifest.ci_promotion_evidence_bound == 1u, "ci");
    EXPECT_TRUE(manifest.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(manifest.offline_packet_intake_recorded == 1u, "offline");
    EXPECT_TRUE(manifest.digest_algorithm_sha256_required == 1u, "sha256");
    EXPECT_TRUE(manifest.immutable_packet_record_required == 1u, "immutable");
    EXPECT_TRUE(manifest.source_url_column_required == 1u, "source url");
    EXPECT_TRUE(manifest.source_digest_column_required == 1u, "source digest");
    EXPECT_TRUE(manifest.bundle_size_column_required == 1u, "bundle size");
    EXPECT_TRUE(manifest.license_column_required == 1u, "license");
    EXPECT_TRUE(manifest.storage_path_column_required == 1u, "storage path");
    EXPECT_TRUE(manifest.parameter_set_column_required == 1u, "parameter");
    EXPECT_TRUE(manifest.operation_family_column_required == 1u, "operation family");
    EXPECT_TRUE(manifest.negative_case_column_required == 1u, "negative case");
    EXPECT_TRUE(manifest.replay_transcript_column_required == 1u, "replay column");
    EXPECT_TRUE(manifest.tamper_evidence_column_required == 1u, "tamper column");
    EXPECT_TRUE(manifest.reviewer_role_column_required == 1u, "reviewer role");
    EXPECT_TRUE(manifest.reviewer_identity_column_required == 1u, "reviewer identity");
    EXPECT_TRUE(manifest.disposition_column_required == 1u, "disposition column");
    EXPECT_TRUE(manifest.import_timestamp_column_required == 1u, "timestamp");
    EXPECT_TRUE(manifest.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(manifest.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(manifest.fixture_digest_packet_rows_imported == 0u, "fixture rows");
    EXPECT_TRUE(manifest.receipt_replay_packet_rows_imported == 0u, "replay rows");
    EXPECT_TRUE(manifest.source_digest_packet_rows_imported == 0u, "source rows");
    EXPECT_TRUE(manifest.reviewer_role_packet_rows_imported == 0u, "role rows");
    EXPECT_TRUE(manifest.coverage_packet_rows_imported == 0u, "coverage rows");
    EXPECT_TRUE(manifest.tamper_packet_rows_imported == 0u, "tamper rows");
    EXPECT_TRUE(manifest.evidence_packet_reviewed == 0u, "reviewed");
    EXPECT_TRUE(manifest.evidence_packet_manifest_accepted == 0u, "accepted");
    EXPECT_TRUE(manifest.vector_execution_allowed == 0u, "vector execution");
    EXPECT_TRUE(manifest.acvp_submission_allowed == 0u, "acvp submission");
    EXPECT_TRUE(manifest.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(manifest.implementation_promotion_allowed == 0u, "promotion");
    EXPECT_TRUE(manifest.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(manifest.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(manifest.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(manifest.required_evidence_packet_items_total == 41u, "total");
    EXPECT_TRUE(manifest.required_evidence_packet_items_satisfied == 33u, "satisfied");
    EXPECT_TRUE(
        manifest.error == LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_PACKET_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_is_no_effect(
            &manifest) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_allows_packet_acceptance(
            &manifest) == 0,
        "acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
            &manifest,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "evidence_import_packet_manifest_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "source_digest_column_required=1") != 0,
        "source digest report");
    EXPECT_TRUE(
        strstr(rendered, "reviewer_role_packet_rows_imported=0") != 0,
        "role rows report");
    EXPECT_TRUE(
        strstr(rendered, "required_evidence_packet_items_total=41") != 0,
        "total report");
    return 0;
}

static int evidence_import_packet_manifest_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_evidence_import_packet_manifest_t manifest;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_allows_packet_acceptance(0) ==
            0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare(&manifest) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
            &manifest,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_evidence_import_packet_manifest_report(
            &manifest,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (evidence_import_packet_manifest_is_fail_closed() != 0) {
        return 1;
    }
    if (evidence_import_packet_manifest_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem evidence import packet manifest invariants: ok\n");
    return 0;
}
