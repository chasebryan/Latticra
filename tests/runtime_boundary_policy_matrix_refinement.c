#include "latticra/runtime_boundary.h"

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

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    strcpy(authority.status_label, "ok");
    strcpy(authority.validator_label, "runtime-policy-matrix-refinement");
    strcpy(authority.requested_effect_label, "none");
    strcpy(authority.denial_reason, "ok");
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

static int runtime_boundary_policy_matrix_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_REPORT), "no-effect-report", "report cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION), "no-effect-validation", "validation cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_CLASSIFICATION), "no-effect-classification", "classification cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION), "future-gated-operation", "future gate cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT), "blocked-effect", "blocked effect cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED), "prerequisite-denied", "prereq cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID), "invalid", "invalid cell label");
    EXPECT_STR_EQ(latticra_runtime_boundary_policy_matrix_cell_label(LATTICRA_RUNTIME_BOUNDARY_MATRIX_UNSUPPORTED), "unsupported", "unsupported cell label");
    return 0;
}

static int runtime_boundary_policy_matrix_reports_validation_cell(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "policy-matrix-validation");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "validation classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "validation policy allowed");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION, "validation matrix cell");
    EXPECT_TRUE(result.record.matrix_effect_allowed == 1, "validation effect allowed");
    EXPECT_TRUE(result.record.matrix_mode_allowed == 1, "validation mode allowed");
    EXPECT_TRUE(result.record.matrix_requires_authority == 1, "validation authority required");
    EXPECT_TRUE(result.record.matrix_requires_future_gate == 0, "validation future gate not required");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "validation report ok");
    EXPECT_TRUE(strstr(report, "policy_matrix_cell=no-effect-validation\n") != 0, "validation matrix cell report");
    EXPECT_TRUE(strstr(report, "matrix_effect_allowed=1\n") != 0, "validation effect allowed report");
    EXPECT_TRUE(strstr(report, "matrix_mode_allowed=1\n") != 0, "validation mode allowed report");
    EXPECT_TRUE(strstr(report, "matrix_requires_authority=1\n") != 0, "validation authority required report");
    EXPECT_TRUE(strstr(report, "matrix_requires_future_gate=0\n") != 0, "validation future gate report");
    return 0;
}

static int runtime_boundary_policy_matrix_reports_future_gate_cell(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "policy-matrix-future");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "future gate classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE, "future gate policy");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION, "future gate matrix cell");
    EXPECT_TRUE(result.record.matrix_effect_allowed == 1, "future gate no-effect capture");
    EXPECT_TRUE(result.record.matrix_mode_allowed == 1, "future gate mode capture");
    EXPECT_TRUE(result.record.matrix_requires_authority == 1, "future gate authority required");
    EXPECT_TRUE(result.record.matrix_requires_future_gate == 1, "future gate required");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "future gate report ok");
    EXPECT_TRUE(strstr(report, "policy_matrix_cell=future-gated-operation\n") != 0, "future gate matrix report");
    EXPECT_TRUE(strstr(report, "matrix_requires_future_gate=1\n") != 0, "future gate required report");
    return 0;
}

static int runtime_boundary_policy_matrix_reports_blocked_effect_cell(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "policy-matrix-blocked-effect");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "blocked effect classification status ok");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT, "blocked effect matrix cell");
    EXPECT_TRUE(result.record.matrix_effect_allowed == 0, "blocked effect not allowed");
    EXPECT_TRUE(result.record.matrix_mode_allowed == 1, "blocked effect mode allowed");
    EXPECT_TRUE(result.record.matrix_requires_future_gate == 0, "blocked effect no future gate");
    return 0;
}

static int runtime_boundary_policy_matrix_reports_prerequisite_denial_cell(void) {
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "policy-matrix-prereq");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "prereq classification status ok");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED, "authority prereq denied");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED, "prereq matrix cell");
    EXPECT_TRUE(result.record.matrix_effect_allowed == 1, "prereq effect allowed");
    EXPECT_TRUE(result.record.matrix_mode_allowed == 1, "prereq mode allowed");
    EXPECT_TRUE(result.record.matrix_requires_authority == 1, "prereq authority required");
    return 0;
}

static int runtime_boundary_policy_matrix_reports_invalid_cell(void) {
    latticra_runtime_boundary_result_t result;

    EXPECT_TRUE(latticra_runtime_boundary_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "null request rejected");
    EXPECT_TRUE(result.record.policy_matrix_cell == LATTICRA_RUNTIME_BOUNDARY_MATRIX_INVALID, "null request invalid cell");
    EXPECT_TRUE(result.record.matrix_effect_allowed == 0, "null effect not allowed");
    EXPECT_TRUE(result.record.matrix_mode_allowed == 0, "null mode not allowed");
    EXPECT_TRUE(result.record.matrix_requires_authority == 0, "null authority not required");
    EXPECT_TRUE(result.record.matrix_requires_future_gate == 0, "null future gate not required");
    return 0;
}

int main(void) {
    if (runtime_boundary_policy_matrix_labels_are_stable() != 0) return 1;
    if (runtime_boundary_policy_matrix_reports_validation_cell() != 0) return 1;
    if (runtime_boundary_policy_matrix_reports_future_gate_cell() != 0) return 1;
    if (runtime_boundary_policy_matrix_reports_blocked_effect_cell() != 0) return 1;
    if (runtime_boundary_policy_matrix_reports_prerequisite_denial_cell() != 0) return 1;
    if (runtime_boundary_policy_matrix_reports_invalid_cell() != 0) return 1;

    puts("runtime_boundary_policy_matrix_refinement: ok");
    return 0;
}
