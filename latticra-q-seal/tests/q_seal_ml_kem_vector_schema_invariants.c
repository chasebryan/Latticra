#include "latticra/q_seal_ml_kem_vector_schema.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int vector_schema_records_acvp_shape_without_processing_vectors(void) {
    latticra_q_seal_ml_kem_vector_schema_t schema;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_prepare(&schema) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(schema.schema_profile, "latticra-q-seal-ml-kem-vector-schema/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(schema.formal_title, "Latticra Q-Seal ML-KEM Vector Schema") == 0,
        "title");
    EXPECT_TRUE(strcmp(schema.standards_source, "NIST-FIPS-203") == 0, "standards");
    EXPECT_TRUE(strcmp(schema.acvp_document, "NIST-ACVP-ML-KEM-JSON") == 0, "acvp");
    EXPECT_TRUE(
        strcmp(schema.schema_state, "schema-recorded-vectors-not-loaded") == 0,
        "state");
    EXPECT_TRUE(schema.vector_schema_present == 1u, "present");
    EXPECT_TRUE(schema.fips_203_source_verified == 1u, "fips");
    EXPECT_TRUE(schema.acvp_ml_kem_schema_tracked == 1u, "schema tracked");
    EXPECT_TRUE(schema.algorithm_ml_kem_recorded == 1u, "algorithm");
    EXPECT_TRUE(schema.revision_fips203_recorded == 1u, "revision");
    EXPECT_TRUE(schema.keygen_mode_schema_recorded == 1u, "keygen");
    EXPECT_TRUE(schema.encap_decap_mode_schema_recorded == 1u, "encap decap");
    EXPECT_TRUE(schema.parameter_sets_recorded == 1u, "parameters");
    EXPECT_TRUE(schema.keygen_prompt_fields_recorded == 1u, "keygen prompt");
    EXPECT_TRUE(schema.keygen_response_fields_recorded == 1u, "keygen response");
    EXPECT_TRUE(schema.encap_decap_prompt_fields_recorded == 1u, "encap prompt");
    EXPECT_TRUE(schema.encap_decap_response_fields_recorded == 1u, "encap response");
    EXPECT_TRUE(schema.aft_test_type_recorded == 1u, "aft");
    EXPECT_TRUE(schema.val_test_type_recorded == 1u, "val");
    EXPECT_TRUE(schema.key_check_functions_recorded == 1u, "key checks");
    EXPECT_TRUE(schema.implicit_rejection_case_recorded == 1u, "implicit rejection");
    EXPECT_TRUE(schema.vector_source_url_recorded == 0u, "source url");
    EXPECT_TRUE(schema.vector_source_digest_recorded == 0u, "source digest");
    EXPECT_TRUE(schema.vector_license_review_recorded == 0u, "license");
    EXPECT_TRUE(schema.vector_bundle_loaded == 0u, "bundle");
    EXPECT_TRUE(schema.vector_json_parser_implemented == 0u, "parser");
    EXPECT_TRUE(schema.response_generation_enabled == 0u, "response");
    EXPECT_TRUE(schema.vector_execution_enabled == 0u, "vector execution");
    EXPECT_TRUE(schema.acvp_submission_allowed == 0u, "submission");
    EXPECT_TRUE(schema.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(schema.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(schema.fips_claim_allowed == 0u, "fips claim");
    EXPECT_TRUE(schema.runtime_authority_granted == 0u, "authority");
    EXPECT_TRUE(schema.required_schema_items_total == 18u, "total");
    EXPECT_TRUE(schema.required_schema_items_satisfied == 15u, "satisfied");
    EXPECT_TRUE(schema.error == LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA_BLOCKED, "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_is_schema_only(&schema) == 1,
        "schema only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(&schema) == 0,
        "allows vector processing");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_report(&schema, rendered, sizeof(rendered)) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(strstr(rendered, "LATTICRA Q-SEAL ML-KEM VECTOR SCHEMA") != 0, "header");
    EXPECT_TRUE(strstr(rendered, "keygen_prompt_fields_recorded=1") != 0, "keygen report");
    EXPECT_TRUE(strstr(rendered, "encap_decap_response_fields_recorded=1") != 0, "encap report");
    EXPECT_TRUE(strstr(rendered, "implicit_rejection_case_recorded=1") != 0, "implicit report");
    EXPECT_TRUE(strstr(rendered, "vector_bundle_loaded=0") != 0, "bundle report");
    EXPECT_TRUE(strstr(rendered, "status=ml-kem-vector-schema-blocked") != 0, "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_vector_schema_t schema;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(latticra_q_seal_ml_kem_vector_schema_is_schema_only(0) == 0, "null schema only");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_allows_vector_processing(0) == 0,
        "null vector processing");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_prepare(&schema) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_report(&schema, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report schema");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_vector_schema_report(&schema, 0, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (vector_schema_records_acvp_shape_without_processing_vectors() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem vector schema invariants: ok\n");
    return 0;
}
