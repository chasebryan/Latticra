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
    copy_text(authority.validator_label, sizeof(authority.validator_label), "runtime-report-refinement");
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
    copy_text(pipeline.module_name, sizeof(pipeline.module_name), "RuntimeReportRefinementModule");
    pipeline.source_len = 128u;
    pipeline.node_count = 8u;
    pipeline.edge_count = 7u;
    pipeline.semantic_valid = 1;
    pipeline.no_effect = 1;
    return pipeline;
}

static int runtime_boundary_report_refinement_classifies_declarative_pipeline(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-declarative");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "declarative classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "pipeline validation allowed");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE, "pipeline classified declarative");
    EXPECT_TRUE(result.record.boundary_domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN, "pipeline report domain unknown");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_NOT_REQUESTED, "pipeline auth not requested");
    EXPECT_TRUE(result.record.evidence_level == 2u, "pipeline evidence level two");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "declarative report status ok");
    EXPECT_TRUE(strstr(report, "report_classification=declarative\n") != 0, "declarative report classification present");
    EXPECT_TRUE(strstr(report, "boundary_domain=unknown\n") != 0, "unknown boundary domain present");
    EXPECT_TRUE(strstr(report, "authorization_state=not-requested\n") != 0, "not-requested authorization present");
    EXPECT_TRUE(strstr(report, "evidence_level=2\n") != 0, "evidence level present");
    return 0;
}

static int runtime_boundary_report_refinement_marks_future_gate_boundary_seeking(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-exec");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "future gate classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE, "future gate policy set");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING, "future gate boundary seeking");
    EXPECT_TRUE(result.record.boundary_domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_PROCESS, "lat execute maps to process domain");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE, "future gate authorization reserved");
    EXPECT_TRUE(result.record.evidence_level == 1u, "future gate evidence level one");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "future gate report status ok");
    EXPECT_TRUE(strstr(report, "report_classification=boundary-seeking\n") != 0, "boundary-seeking report classification present");
    EXPECT_TRUE(strstr(report, "boundary_domain=process\n") != 0, "process boundary domain present");
    EXPECT_TRUE(strstr(report, "authorization_state=reserved-for-future\n") != 0, "reserved future authorization present");
    return 0;
}

static int runtime_boundary_report_refinement_maps_effect_domains(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-file");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_FILE_WRITE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_LOCAL_MUTATION;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "file domain classification status ok");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING, "file write boundary seeking");
    EXPECT_TRUE(result.record.boundary_domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM, "file write maps to filesystem");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE, "file write reserved for future");

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-network");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_NETWORK_OPEN;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "network domain classification status ok");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING, "network open boundary seeking");
    EXPECT_TRUE(result.record.boundary_domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_NETWORK, "network open maps to network");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE, "network open reserved for future");
    return 0;
}

static int runtime_boundary_report_refinement_marks_invalid_unknown_request(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-invalid");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_UNKNOWN;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "invalid classification status ok");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_INVALID, "unknown request invalid");
    EXPECT_TRUE(result.record.boundary_domain == LATTICRA_RUNTIME_BOUNDARY_DOMAIN_UNKNOWN, "unknown request domain unknown");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_UNAVAILABLE, "unknown request authorization unavailable");
    EXPECT_TRUE(result.record.evidence_level == 0u, "unknown request evidence level zero");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "invalid report status ok");
    EXPECT_TRUE(strstr(report, "report_classification=invalid\n") != 0, "invalid report classification present");
    EXPECT_TRUE(strstr(report, "authorization_state=unavailable\n") != 0, "unavailable authorization present");
    return 0;
}

static int runtime_boundary_report_refinement_marks_denied_prerequisite(void) {
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "report-refinement-denied");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "denied classification status ok");
    EXPECT_TRUE(result.record.report_classification == LATTICRA_RUNTIME_BOUNDARY_REPORT_DENIED, "missing authority denied");
    EXPECT_TRUE(result.record.authorization_state == LATTICRA_RUNTIME_BOUNDARY_AUTH_DENIED, "missing authority auth denied");
    EXPECT_TRUE(result.record.evidence_level == 1u, "missing authority evidence level one");
    return 0;
}

int main(void) {
    if (runtime_boundary_report_refinement_classifies_declarative_pipeline() != 0) return 1;
    if (runtime_boundary_report_refinement_marks_future_gate_boundary_seeking() != 0) return 1;
    if (runtime_boundary_report_refinement_maps_effect_domains() != 0) return 1;
    if (runtime_boundary_report_refinement_marks_invalid_unknown_request() != 0) return 1;
    if (runtime_boundary_report_refinement_marks_denied_prerequisite() != 0) return 1;

    puts("runtime_boundary_report_refinement: ok");
    return 0;
}
