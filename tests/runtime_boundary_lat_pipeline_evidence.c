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
    pipeline.parse_error = LATTICRA_LAT_PARSE_OK;
    pipeline.semantic_error = LATTICRA_LAT_SEMANTIC_OK;
    pipeline.model_error = LATTICRA_LAT_MODEL_OK;
    pipeline.lowering_error = LATTICRA_LAT_TO_LIR_OK;
    pipeline.lir_error = LATTICRA_LIR_OK;
    strcpy(pipeline.module_name, "RuntimeEvidenceModule");
    pipeline.source_len = 256u;
    pipeline.span.start_offset = 25u;
    pipeline.span.end_offset = 256u;
    pipeline.span.start_line = 2u;
    pipeline.span.start_column = 1u;
    pipeline.span.end_line = 30u;
    pipeline.span.end_column = 2u;
    pipeline.declaration_count = 5u;
    pipeline.clause_count = 23u;
    pipeline.comment_count = 2u;
    pipeline.first_comment_span.start_offset = 0u;
    pipeline.first_comment_span.end_offset = 24u;
    pipeline.first_comment_span.start_line = 1u;
    pipeline.first_comment_span.start_column = 1u;
    pipeline.first_comment_span.end_line = 1u;
    pipeline.first_comment_span.end_column = 25u;
    pipeline.node_count = 29u;
    pipeline.edge_count = 29u;
    pipeline.last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_REPORT;
    pipeline.failed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    pipeline.parse_ok = 1;
    pipeline.semantic_ok = 1;
    pipeline.model_ok = 1;
    pipeline.lowering_ok = 1;
    pipeline.lir_ok = 1;
    pipeline.no_effect_chain_ok = 1;
    pipeline.evidence_level = 2u;
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
    EXPECT_TRUE(result.record.lat_pipeline_parse_error == LATTICRA_LAT_PARSE_OK, "pipeline parse error copied");
    EXPECT_TRUE(result.record.lat_pipeline_span.start_line == 2u, "pipeline span line copied");
    EXPECT_TRUE(result.record.lat_pipeline_span.start_column == 1u, "pipeline span column copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_error == LATTICRA_LAT_SEMANTIC_OK, "pipeline semantic error copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_error == LATTICRA_LAT_MODEL_OK, "pipeline model error copied");
    EXPECT_TRUE(result.record.lat_pipeline_lowering_error == LATTICRA_LAT_TO_LIR_OK, "pipeline lowering error copied");
    EXPECT_TRUE(result.record.lat_pipeline_lir_error == LATTICRA_LIR_OK, "pipeline lir error copied");
    EXPECT_TRUE(result.record.lat_pipeline_last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_REPORT, "pipeline last completed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_failed_stage == LATTICRA_LAT_PIPELINE_STAGE_NONE, "pipeline failed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_parse_ok == 1, "pipeline parse ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_ok == 1, "pipeline semantic ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_ok == 1, "pipeline model ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_lowering_ok == 1, "pipeline lowering ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_lir_ok == 1, "pipeline lir ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_no_effect_chain_ok == 1, "pipeline no-effect chain copied");
    EXPECT_TRUE(result.record.lat_pipeline_evidence_level == 2u, "pipeline evidence level copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_valid == 1, "pipeline semantic valid copied");
    EXPECT_TRUE(result.record.lat_pipeline_source_len == 256u, "pipeline source length copied");
    EXPECT_TRUE(result.record.lat_pipeline_node_count == 29u, "pipeline node count copied");
    EXPECT_TRUE(result.record.lat_pipeline_edge_count == 29u, "pipeline edge count copied");
    EXPECT_TRUE(result.record.lat_pipeline_comment_count == 2u, "pipeline comment count copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_line == 1u, "pipeline comment line copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_column == 1u, "pipeline comment column copied");
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
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    pipeline.error = LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK;
    pipeline.semantic_error = LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE;
    pipeline.last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_PARSE;
    pipeline.failed_stage = LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC;
    pipeline.semantic_ok = 0;
    pipeline.model_ok = 0;
    pipeline.lowering_ok = 0;
    pipeline.lir_ok = 0;
    pipeline.evidence_level = 1u;
    pipeline.semantic_valid = 0;
    pipeline.span.start_offset = 54u;
    pipeline.span.end_offset = 54u;
    pipeline.span.start_line = 3u;
    pipeline.span.start_column = 3u;
    pipeline.span.end_line = 3u;
    pipeline.span.end_column = 3u;
    pipeline.comment_count = 1u;
    pipeline.first_comment_span.start_offset = 0u;
    pipeline.first_comment_span.end_offset = 28u;
    pipeline.first_comment_span.start_line = 1u;
    pipeline.first_comment_span.start_column = 1u;
    pipeline.first_comment_span.end_line = 1u;
    pipeline.first_comment_span.end_column = 29u;

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
    EXPECT_TRUE(result.record.lat_pipeline_span.start_line == 3u, "failed pipeline span line copied");
    EXPECT_TRUE(result.record.lat_pipeline_span.start_column == 3u, "failed pipeline span column copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_error == LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE, "failed semantic error copied");
    EXPECT_TRUE(result.record.lat_pipeline_last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_PARSE, "failed pipeline completed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_failed_stage == LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC, "failed pipeline failed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_ok == 0, "failed pipeline semantic ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_ok == 0, "failed pipeline model ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_evidence_level == 1u, "failed pipeline evidence copied");
    EXPECT_TRUE(result.record.lat_pipeline_semantic_valid == 0, "failed semantic flag copied");
    EXPECT_TRUE(result.record.lat_pipeline_comment_count == 1u, "failed pipeline comment count copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_line == 1u, "failed pipeline comment line copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_column == 1u, "failed pipeline comment column copied");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed pipeline report status ok");
    EXPECT_TRUE(strstr(report, "lat_pipeline_error=semantic_not_ok\n") != 0, "failed pipeline error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_error=unknown_transition_source\n") != 0, "failed semantic error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_last_completed_stage=parse\n") != 0, "failed pipeline completed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_failed_stage=semantic\n") != 0, "failed pipeline failed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_ok=0\n") != 0, "failed pipeline semantic ok report present");
    return 0;
}

static int runtime_boundary_denies_parse_failed_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    pipeline.error = LATTICRA_LAT_PIPELINE_PARSE_NOT_OK;
    pipeline.parse_error = LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT;
    pipeline.last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_NONE;
    pipeline.failed_stage = LATTICRA_LAT_PIPELINE_STAGE_PARSE;
    pipeline.parse_ok = 0;
    pipeline.semantic_ok = 0;
    pipeline.model_ok = 0;
    pipeline.lowering_ok = 0;
    pipeline.lir_ok = 0;
    pipeline.evidence_level = 1u;
    pipeline.semantic_valid = 0;
    pipeline.span.start_offset = 54u;
    pipeline.span.end_offset = 54u;
    pipeline.span.start_line = 3u;
    pipeline.span.start_column = 3u;
    pipeline.span.end_line = 3u;
    pipeline.span.end_column = 3u;
    pipeline.comment_count = 1u;
    pipeline.first_comment_span.start_offset = 0u;
    pipeline.first_comment_span.end_offset = 28u;
    pipeline.first_comment_span.start_line = 1u;
    pipeline.first_comment_span.start_column = 1u;
    pipeline.first_comment_span.end_line = 1u;
    pipeline.first_comment_span.end_column = 29u;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-pipeline-parse-failed");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "parse failed pipeline classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "parse failed pipeline denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED, "parse failed pipeline parser reason");
    EXPECT_TRUE(result.record.lat_pipeline_error == LATTICRA_LAT_PIPELINE_PARSE_NOT_OK, "parse failed pipeline error copied");
    EXPECT_TRUE(result.record.lat_pipeline_parse_error == LATTICRA_LAT_PARSE_UNSUPPORTED_BLOCK_COMMENT, "parse failed pipeline parse error copied");
    EXPECT_TRUE(result.record.lat_pipeline_last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_NONE, "parse failed completed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_failed_stage == LATTICRA_LAT_PIPELINE_STAGE_PARSE, "parse failed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_parse_ok == 0, "parse failed parse ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_evidence_level == 1u, "parse failed evidence copied");
    EXPECT_TRUE(result.record.lat_pipeline_span.start_line == 3u, "parse failed pipeline span line copied");
    EXPECT_TRUE(result.record.lat_pipeline_span.start_column == 3u, "parse failed pipeline span column copied");
    EXPECT_TRUE(result.record.lat_pipeline_comment_count == 1u, "parse failed pipeline comment count copied");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "parse failed pipeline report status ok");
    EXPECT_TRUE(strstr(report, "lat_pipeline_error=parse_not_ok\n") != 0, "parse failed pipeline error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_parse_error=unsupported_block_comment\n") != 0, "parse failed parse error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_last_completed_stage=none\n") != 0, "parse failed completed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_failed_stage=parse\n") != 0, "parse failed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_parse_ok=0\n") != 0, "parse failed parse ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_span_start_line=3\n") != 0, "parse failed span line report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_comment_count=1\n") != 0, "parse failed comment count report present");
    return 0;
}

static int runtime_boundary_denies_model_failed_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    pipeline.error = LATTICRA_LAT_PIPELINE_MODEL_NOT_OK;
    pipeline.model_error = LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE;
    pipeline.lowering_error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
    pipeline.lir_error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
    pipeline.last_completed_stage = LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC;
    pipeline.failed_stage = LATTICRA_LAT_PIPELINE_STAGE_MODEL;
    pipeline.model_ok = 0;
    pipeline.lowering_ok = 0;
    pipeline.lir_ok = 0;
    pipeline.evidence_level = 1u;

    memset(&request, 0, sizeof(request));
    strcpy(request.runtime_id, "runtime-lat-pipeline-model-failed");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "model failed pipeline classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "model failed pipeline denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED, "model failed pipeline downstream reason");
    EXPECT_TRUE(result.record.lat_pipeline_error == LATTICRA_LAT_PIPELINE_MODEL_NOT_OK, "model failed pipeline error copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_error == LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE, "model failed model error copied");
    EXPECT_TRUE(result.record.lat_pipeline_lowering_error == LATTICRA_LAT_TO_LIR_MODEL_NOT_OK, "model failed lowering error copied");
    EXPECT_TRUE(result.record.lat_pipeline_lir_error == LATTICRA_LIR_UNSUPPORTED_NODE_KIND, "model failed lir error copied");
    EXPECT_TRUE(result.record.lat_pipeline_last_completed_stage == LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC, "model failed completed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_failed_stage == LATTICRA_LAT_PIPELINE_STAGE_MODEL, "model failed stage copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_ok == 0, "model failed model ok copied");
    EXPECT_TRUE(result.record.lat_pipeline_evidence_level == 1u, "model failed evidence copied");

    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "model failed pipeline report status ok");
    EXPECT_TRUE(strstr(report, "lat_pipeline_error=model_not_ok\n") != 0, "model failed pipeline error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_error=unsupported_clause\n") != 0, "model failed model error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lowering_error=model_not_ok\n") != 0, "model failed lowering error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lir_error=unsupported_node_kind\n") != 0, "model failed lir error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_last_completed_stage=semantic\n") != 0, "model failed completed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_failed_stage=model\n") != 0, "model failed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_ok=0\n") != 0, "model failed model ok report present");
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
    EXPECT_TRUE(strstr(report, "lat_pipeline_parse_error=ok\n") != 0, "pipeline parse error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_span_start_line=2\n") != 0, "pipeline span line report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_span_start_column=1\n") != 0, "pipeline span column report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_error=ok\n") != 0, "pipeline semantic error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_error=ok\n") != 0, "pipeline model error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lowering_error=ok\n") != 0, "pipeline lowering error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lir_error=ok\n") != 0, "pipeline lir error report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_last_completed_stage=report\n") != 0, "pipeline completed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_failed_stage=none\n") != 0, "pipeline failed stage report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_parse_ok=1\n") != 0, "pipeline parse ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_ok=1\n") != 0, "pipeline semantic ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_ok=1\n") != 0, "pipeline model ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lowering_ok=1\n") != 0, "pipeline lowering ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_lir_ok=1\n") != 0, "pipeline lir ok report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_no_effect_chain_ok=1\n") != 0, "pipeline no-effect chain report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_evidence_level=2\n") != 0, "pipeline evidence level report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_semantic_valid=1\n") != 0, "pipeline semantic report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_source_len=256\n") != 0, "pipeline source length report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_node_count=29\n") != 0, "pipeline node count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_edge_count=29\n") != 0, "pipeline edge count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_comment_count=2\n") != 0, "pipeline comment count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_comment_start_line=1\n") != 0, "pipeline comment line report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_comment_start_column=1\n") != 0, "pipeline comment column report present");
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
    if (runtime_boundary_denies_parse_failed_lat_pipeline_metadata() != 0) return 1;
    if (runtime_boundary_denies_model_failed_lat_pipeline_metadata() != 0) return 1;
    if (runtime_boundary_reports_lat_pipeline_evidence() != 0) return 1;
    if (runtime_boundary_keeps_lat_lir_execution_future_gated() != 0) return 1;

    puts("runtime_boundary_lat_pipeline_evidence: ok");
    return 0;
}
