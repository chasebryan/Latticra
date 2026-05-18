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

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    strcpy(authority.status_label, "ok");
    strcpy(authority.validator_label, "runtime-lat-pipeline-evidence");
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
    strcpy(pipeline.module_name, "RuntimeEvidenceModule");
    pipeline.source_len = 256u;
    pipeline.declaration_count = 5u;
    pipeline.clause_count = 23u;
    pipeline.node_count = 29u;
    pipeline.edge_count = 29u;
    pipeline.semantic_valid = 1;
    pipeline.no_effect = 1;
    return pipeline;
}

static latticra_lir_module_t lat_lir_module(void) {
    latticra_lir_module_t lir;
    memset(&lir, 0, sizeof(lir));
    lir.status = LATTICRA_STATUS_OK;
    lir.error = LATTICRA_LIR_OK;
    lir.source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
    strcpy(lir.module_name, "RuntimeEvidenceModule");
    lir.node_count = 4u;
    lir.edge_count = 2u;
    lir.no_effect = 1;
    lir.nodes[0].kind = LATTICRA_LIR_NODE_MODULE;
    lir.nodes[1].kind = LATTICRA_LIR_NODE_LAT_STATE;
    lir.nodes[2].kind = LATTICRA_LIR_NODE_LAT_TRANSITION;
    lir.nodes[3].kind = LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    lir.edges[0].edge_kind = LATTICRA_LIR_EDGE_CONTAINS;
    lir.edges[1].edge_kind = LATTICRA_LIR_EDGE_TRANSITIONS_FROM;
    return lir;
}

static int runtime_boundary_allows_valid_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_lir_module_t lir = lat_lir_module();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-pipeline");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;
    request.lir = &lir;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "pipeline validation allowed");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "pipeline validation reason ok");
    EXPECT_TRUE(result.record.allowed_effect == LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE, "allowed effect none");
    EXPECT_TRUE(result.no_effect == 1, "no-effect preserved");
    EXPECT_TRUE(result.execution_allowed == 0, "execution remains denied");
    EXPECT_TRUE(result.record.lat_pipeline_status == LATTICRA_STATUS_OK, "pipeline status copied");
    EXPECT_TRUE(result.record.lat_pipeline_error == LATTICRA_LAT_PIPELINE_OK, "pipeline error copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_valid == 1, "pipeline semantic valid copied");
    EXPECT_TRUE(result.record.lat_pipeline_source_len == 256u, "pipeline source length copied");
    EXPECT_TRUE(result.record.lat_pipeline_node_count == 29u, "pipeline node count copied");
    EXPECT_TRUE(result.record.lat_pipeline_edge_count == 29u, "pipeline edge count copied");
    EXPECT_TRUE(result.record.lat_lir_source_kind == LATTICRA_LIR_SOURCE_LAT_MODULE, "lat lir source kind copied");
    EXPECT_TRUE(result.record.lat_lir_module_node_count == 4u, "lat lir node count copied");
    EXPECT_TRUE(result.record.lat_lir_transition_edge_count == 1u, "transition edge count copied");
    EXPECT_TRUE(result.record.lat_lir_has_lat_state_nodes == 1, "lat state evidence copied");
    EXPECT_TRUE(result.record.lat_lir_has_lat_transition_nodes == 1, "lat transition evidence copied");
    EXPECT_TRUE(result.record.lat_lir_has_transition_source_edges == 1, "transition source evidence copied");
    return 0;
}

static int runtime_boundary_denies_failed_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    pipeline.error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK;
    pipeline.semantic_valid = 0;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-pipeline-failed");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "failed pipeline classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "failed pipeline denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED, "failed pipeline semantic reason");
    EXPECT_TRUE(result.record.lat_pipeline_error == LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK, "failed pipeline error copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_valid == 0, "failed semantic flag copied");
    return 0;
}

static int runtime_boundary_reports_lat_pipeline_evidence(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_lir_module_t lir = lat_lir_module();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-pipeline-report");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;
    request.lir = &lir;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "report classification status ok");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "report status ok");
    EXPECT_TRUE(strstr(report, "request=lat-pipeline-validate\n") != 0, "pipeline request label present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_status=0\n") != 0, "pipeline status report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_error=ok\n") != 0, "pipeline error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_valid=1\n") != 0, "pipeline semantic report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_source_len=256\n") != 0, "pipeline source length report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_node_count=29\n") != 0, "pipeline node count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_edge_count=29\n") != 0, "pipeline edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_source_kind=lat_module\n") != 0, "lat lir source kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_module_node_count=4\n") != 0, "lat lir node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_transition_edge_count=1\n") != 0, "lat lir transition edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_lat_state_nodes=1\n") != 0, "lat state report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_lat_transition_nodes=1\n") != 0, "lat transition report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_transition_source_edges=1\n") != 0, "transition source report present");
    return 0;
}

static int runtime_boundary_keeps_lat_lir_execution_future_gated(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-execute-denied");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "lat execute classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE, "lat execute future gated");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE, "lat execute future gate reason");
    EXPECT_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED, "lat execute planned gate");
    EXPECT_TRUE(result.execution_allowed == 0, "lat execute not allowed");
    return 0;
}

int main(void) {
    if (runtime_boundary_allows_valid_lat_pipeline_metadata() != 0) return 1;
    if (runtime_boundary_denies_failed_lat_pipeline_metadata() != 0) return 1;
    if (runtime_boundary_reports_lat_pipeline_evidence() != 0) return 1;
    if (runtime_boundary_keeps_lat_lir_execution_future_gated() != 0) return 1;

    puts("runtime_boundary_lat_pipeline_evidence: ok");
    return 0;
}
