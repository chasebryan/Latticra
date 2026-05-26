#include "latticra/runtime_boundary_domain_matrix.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", message, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

static void copy_text(char *dest, size_t dest_len, const char *src) {
    if (dest_len == 0u) {
        return;
    }
    (void)snprintf(dest, dest_len, "%s", src);
}

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    copy_text(authority.status_label, sizeof(authority.status_label), "ok");
    copy_text(authority.validator_label, sizeof(authority.validator_label), "domain-matrix");
    copy_text(authority.requested_effect_label, sizeof(authority.requested_effect_label), "none");
    copy_text(authority.denial_reason, sizeof(authority.denial_reason), "ok");
    authority.no_effect = 1;
    return authority;
}

static latticra_lat_pipeline_result_t ok_pipeline(void) {
    latticra_lat_pipeline_result_t pipeline;
    memset(&pipeline, 0, sizeof(pipeline));
    pipeline.status = LATTICRA_STATUS_OK;
    pipeline.error = LATTICRA_LAT_PIPELINE_OK;
    pipeline.semantic_valid = 1;
    pipeline.no_effect = 1;
    return pipeline;
}

static int runtime_boundary_domain_matrix_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_runtime_boundary_domain_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE), "declarative", "declarative label");
    EXPECT_STR_EQ(latticra_runtime_boundary_domain_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_OPERATIONAL), "operational", "operational label");
    EXPECT_STR_EQ(latticra_runtime_boundary_domain_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED), "future-gated", "future-gated label");
    EXPECT_STR_EQ(latticra_runtime_boundary_domain_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID), "invalid", "invalid label");
    EXPECT_STR_EQ(latticra_runtime_boundary_domain_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN), "unknown", "unknown label");
    return 0;
}

static int runtime_boundary_domain_matrix_reports_declarative_host_domain(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t boundary;
    latticra_runtime_boundary_domain_matrix_result_t matrix;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "domain-matrix-host");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &boundary) == LATTICRA_STATUS_OK, "host classify status");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_evaluate(&boundary, &matrix) == LATTICRA_STATUS_OK, "host matrix status");
    EXPECT_TRUE(matrix.cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE, "host declarative cell");
    EXPECT_TRUE(matrix.domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_HOST, "host domain");
    EXPECT_TRUE(matrix.domain_known == 1, "host known");
    EXPECT_TRUE(matrix.domain_declarative == 1, "host declarative");
    EXPECT_TRUE(matrix.domain_operational == 0, "host not operational");
    EXPECT_TRUE(matrix.domain_future_gated == 0, "host not future gated");
    EXPECT_TRUE(matrix.domain_effect_allowed == 1, "host effect allowed");
    EXPECT_TRUE(matrix.domain_authority_available == 1, "host authority available");
    EXPECT_TRUE(matrix.evidence_level == 2u, "host evidence level");
    return 0;
}

static int runtime_boundary_domain_matrix_reports_future_gated_process_domain(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t boundary;
    latticra_runtime_boundary_domain_matrix_result_t matrix;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "domain-matrix-process");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &boundary) == LATTICRA_STATUS_OK, "process classify status");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_evaluate(&boundary, &matrix) == LATTICRA_STATUS_OK, "process matrix status");
    EXPECT_TRUE(matrix.cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_FUTURE_GATED, "process future-gated cell");
    EXPECT_TRUE(matrix.domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS, "process domain");
    EXPECT_TRUE(matrix.domain_known == 1, "process known");
    EXPECT_TRUE(matrix.domain_operational == 1, "process operational");
    EXPECT_TRUE(matrix.domain_future_gated == 1, "process future gated");
    EXPECT_TRUE(matrix.evidence_level == 1u, "process evidence level");
    return 0;
}

static int runtime_boundary_domain_matrix_reports_unknown_domain(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t boundary;
    latticra_runtime_boundary_domain_matrix_result_t matrix;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "domain-matrix-unknown");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &boundary) == LATTICRA_STATUS_OK, "unknown classify status");
    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_evaluate(&boundary, &matrix) == LATTICRA_STATUS_OK, "unknown matrix status");
    EXPECT_TRUE(matrix.cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_UNKNOWN, "unknown cell");
    EXPECT_TRUE(matrix.domain_known == 0, "unknown not known");
    EXPECT_TRUE(matrix.evidence_level == 0u, "unknown evidence level");
    return 0;
}

static int runtime_boundary_domain_matrix_reports_invalid_input(void) {
    latticra_runtime_boundary_domain_matrix_result_t matrix;

    EXPECT_TRUE(latticra_runtime_boundary_domain_matrix_evaluate(0, &matrix) == LATTICRA_STATUS_NULL_ARGUMENT, "null boundary matrix status");
    EXPECT_TRUE(matrix.cell == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_INVALID, "null boundary invalid cell");
    EXPECT_TRUE(matrix.evidence_level == 0u, "null boundary evidence level");
    return 0;
}

int main(void) {
    if (runtime_boundary_domain_matrix_labels_are_stable() != 0) return 1;
    if (runtime_boundary_domain_matrix_reports_declarative_host_domain() != 0) return 1;
    if (runtime_boundary_domain_matrix_reports_future_gated_process_domain() != 0) return 1;
    if (runtime_boundary_domain_matrix_reports_unknown_domain() != 0) return 1;
    if (runtime_boundary_domain_matrix_reports_invalid_input() != 0) return 1;

    puts("runtime_boundary_domain_matrix_refinement: ok");
    return 0;
}
