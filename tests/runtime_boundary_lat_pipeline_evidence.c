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
    copy_text(authority.validator_label, sizeof(authority.validator_label), "runtime-lat-pipeline-evidence");
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
    pipeline.parse_error = LATTICRA_LAT_PARSE_OK;
    pipeline.semantic_error = LATTICRA_LAT_SEMANTIC_OK;
    pipeline.model_error = LATTICRA_LAT_MODEL_OK;
    pipeline.lowering_error = LATTICRA_LAT_TO_LIR_OK;
    pipeline.lir_error = LATTICRA_LIR_OK;
    copy_text(pipeline.module_name, sizeof(pipeline.module_name), "RuntimeEvidenceModule");
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
    pipeline.model_declaration_count = 5u;
    pipeline.model_clause_count = 23u;
    pipeline.first_declaration_node_index = 1u;
    pipeline.first_declaration_kind = LATTICRA_LAT_DECLARATION_STATE;
    copy_text(pipeline.first_declaration_name, sizeof(pipeline.first_declaration_name), "RootCell");
    copy_text(pipeline.first_declaration_source, sizeof(pipeline.first_declaration_source), "");
    pipeline.first_declaration_parse_index = 0u;
    pipeline.first_declaration_first_clause_index = 0u;
    pipeline.first_declaration_clause_count = 9u;
    pipeline.first_declaration_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    pipeline.first_transition_source_index = 0u;
    pipeline.first_clause_node_index = 6u;
    pipeline.first_clause_role = LATTICRA_LAT_MODEL_CLAUSE_FIELD;
    pipeline.first_clause_effect = LATTICRA_LAT_EFFECT_NONE;
    copy_text(pipeline.first_clause_name, sizeof(pipeline.first_clause_name), "name");
    copy_text(pipeline.first_clause_operator, sizeof(pipeline.first_clause_operator), "=");
    copy_text(pipeline.first_clause_value, sizeof(pipeline.first_clause_value), "root");
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
    lir.report_classification = LATTICRA_LIR_REPORT_MATERIALIZED;
    lir.shape_kind = LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH;
    copy_text(lir.module_name, sizeof(lir.module_name), "RuntimeEvidenceModule");
    lir.source_span.start_offset = 25u;
    lir.source_span.end_offset = 256u;
    lir.source_span.start_line = 2u;
    lir.source_span.start_column = 1u;
    lir.source_span.end_line = 30u;
    lir.source_span.end_column = 2u;
    lir.node_count = 7u;
    lir.edge_count = 5u;
    lir.binding_count = 2u;
    lir.text_count = 1u;
    lir.no_effect_chain_ok = 1;
    lir.evidence_level = 2u;
    lir.no_effect = 1;
    lir.nodes[0].kind = LATTICRA_LIR_NODE_MODULE;
    lir.nodes[1].kind = LATTICRA_LIR_NODE_LAT_STATE;
    copy_text(lir.nodes[1].name, sizeof(lir.nodes[1].name), "RootCell");
    copy_text(lir.nodes[1].value, sizeof(lir.nodes[1].value), "root");
    copy_text(lir.nodes[1].operator_text, sizeof(lir.nodes[1].operator_text), "=");
    copy_text(lir.nodes[1].binding, sizeof(lir.nodes[1].binding), "lat.state.root");
    lir.nodes[1].source_span.start_offset = 31u;
    lir.nodes[1].source_span.end_offset = 64u;
    lir.nodes[1].source_span.start_line = 3u;
    lir.nodes[1].source_span.start_column = 5u;
    lir.nodes[1].source_span.end_line = 3u;
    lir.nodes[1].source_span.end_column = 38u;
    lir.nodes[2].kind = LATTICRA_LIR_NODE_LAT_TRANSITION;
    copy_text(lir.nodes[2].name, sizeof(lir.nodes[2].name), "BootTransition");
    copy_text(lir.nodes[2].value, sizeof(lir.nodes[2].value), "RootCell");
    copy_text(lir.nodes[2].operator_text, sizeof(lir.nodes[2].operator_text), "from");
    copy_text(lir.nodes[2].binding, sizeof(lir.nodes[2].binding), "lat.transition.boot");
    lir.nodes[2].source_span.start_offset = 80u;
    lir.nodes[2].source_span.end_offset = 96u;
    lir.nodes[2].source_span.start_line = 4u;
    lir.nodes[2].source_span.start_column = 21u;
    lir.nodes[2].source_span.end_line = 4u;
    lir.nodes[2].source_span.end_column = 37u;
    lir.nodes[3].kind = LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    lir.nodes[4].kind = LATTICRA_LIR_NODE_LAT_POLICY;
    lir.nodes[5].kind = LATTICRA_LIR_NODE_LAT_ASSERTION;
    lir.nodes[6].kind = LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION;
    lir.edges[0].from_index = 0u;
    lir.edges[0].to_index = 1u;
    lir.edges[0].edge_kind = LATTICRA_LIR_EDGE_CONTAINS;
    lir.edges[0].source_span.start_offset = 64u;
    lir.edges[0].source_span.end_offset = 80u;
    lir.edges[0].source_span.start_line = 4u;
    lir.edges[0].source_span.start_column = 3u;
    lir.edges[0].source_span.end_line = 4u;
    lir.edges[0].source_span.end_column = 19u;
    lir.edges[1].edge_kind = LATTICRA_LIR_EDGE_BINDS;
    lir.edges[2].edge_kind = LATTICRA_LIR_EDGE_ANNOTATES;
    lir.edges[3].edge_kind = LATTICRA_LIR_EDGE_ORDERS_BEFORE;
    lir.edges[4].from_index = 2u;
    lir.edges[4].to_index = 1u;
    lir.edges[4].edge_kind = LATTICRA_LIR_EDGE_TRANSITIONS_FROM;
    lir.edges[4].source_span.start_offset = 96u;
    lir.edges[4].source_span.end_offset = 112u;
    lir.edges[4].source_span.start_line = 5u;
    lir.edges[4].source_span.start_column = 7u;
    lir.edges[4].source_span.end_line = 5u;
    lir.edges[4].source_span.end_column = 23u;
    return lir;
}

static int runtime_boundary_allows_valid_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_lir_module_t lir = lat_lir_module();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline");
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
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_module_name, "RuntimeEvidenceModule") == 0, "pipeline module name copied");
    EXPECT_TRUE(result.record.lat_pipeline_source_len == 256u, "pipeline source length copied");
    EXPECT_TRUE(result.record.lat_pipeline_declaration_count == 5u, "pipeline declaration count copied");
    EXPECT_TRUE(result.record.lat_pipeline_clause_count == 23u, "pipeline clause count copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_declaration_count == 5u, "pipeline model declaration count copied");
    EXPECT_TRUE(result.record.lat_pipeline_model_clause_count == 23u, "pipeline model clause count copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_node_index == 1u, "pipeline first declaration node copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_kind == LATTICRA_LAT_DECLARATION_STATE, "pipeline first declaration kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_first_declaration_name, "RootCell") == 0, "pipeline first declaration name copied");
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_first_declaration_source, "") == 0, "pipeline first declaration source copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_parse_index == 0u, "pipeline first declaration parse index copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_first_clause_index == 0u, "pipeline first declaration first clause copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_clause_count == 9u, "pipeline first declaration clause count copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_declaration_source_index == LATTICRA_LAT_MODEL_NO_INDEX, "pipeline first declaration source index copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_transition_source_index == 0u, "pipeline first transition source index copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_clause_node_index == 6u, "pipeline first clause node copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_clause_role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "pipeline first clause role copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_clause_effect == LATTICRA_LAT_EFFECT_NONE, "pipeline first clause effect copied");
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_first_clause_name, "name") == 0, "pipeline first clause name copied");
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_first_clause_operator, "=") == 0, "pipeline first clause operator copied");
    EXPECT_TRUE(strcmp(result.record.lat_pipeline_first_clause_value, "root") == 0, "pipeline first clause value copied");
    EXPECT_TRUE(result.record.lat_pipeline_node_count == 29u, "pipeline node count copied");
    EXPECT_TRUE(result.record.lat_pipeline_edge_count == 29u, "pipeline edge count copied");
    EXPECT_TRUE(result.record.lat_pipeline_comment_count == 2u, "pipeline comment count copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_line == 1u, "pipeline comment line copied");
    EXPECT_TRUE(result.record.lat_pipeline_first_comment_span.start_column == 1u, "pipeline comment column copied");
    EXPECT_TRUE(result.record.lat_lir_source_kind == LATTICRA_LIR_SOURCE_LAT_MODULE, "lat lir source kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_module_name, "RuntimeEvidenceModule") == 0, "lat lir module name copied");
    EXPECT_TRUE(result.record.lat_lir_report_classification == LATTICRA_LIR_REPORT_MATERIALIZED, "lat lir report classification copied");
    EXPECT_TRUE(result.record.lat_lir_shape_kind == LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH, "lat lir shape kind copied");
    EXPECT_TRUE(result.record.lat_lir_source_span.start_line == 2u, "lat lir span line copied");
    EXPECT_TRUE(result.record.lat_lir_source_span.start_column == 1u, "lat lir span column copied");
    EXPECT_TRUE(result.record.lat_lir_source_span.end_line == 30u, "lat lir span end line copied");
    EXPECT_TRUE(result.record.lat_lir_source_span.end_column == 2u, "lat lir span end column copied");
    EXPECT_TRUE(result.record.lat_lir_module_node_count == 7u, "lat lir node count copied");
    EXPECT_TRUE(result.record.lat_lir_module_edge_count == 5u, "lat lir edge count copied");
    EXPECT_TRUE(result.record.lat_lir_binding_count == 2u, "lat lir binding count copied");
    EXPECT_TRUE(result.record.lat_lir_text_count == 1u, "lat lir text count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_state_node_count == 1u, "lat lir state node count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_policy_node_count == 1u, "lat lir policy node count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_transition_node_count == 1u, "lat lir transition node count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_assertion_node_count == 1u, "lat lir assertion node count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_requirement_node_count == 1u, "lat lir requirement node count copied");
    EXPECT_TRUE(result.record.lat_lir_lat_effect_declaration_node_count == 1u, "lat lir effect declaration node count copied");
    EXPECT_TRUE(result.record.lat_lir_has_first_lat_node == 1, "lat lir first node present");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_index == 1u, "lat lir first node index copied");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_kind == LATTICRA_LIR_NODE_LAT_STATE, "lat lir first node kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_lat_node_name, "RootCell") == 0, "lat lir first node name copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_lat_node_value, "root") == 0, "lat lir first node value copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_lat_node_operator, "=") == 0, "lat lir first node operator copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_lat_node_binding, "lat.state.root") == 0, "lat lir first node binding copied");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_span.start_line == 3u, "lat lir first node span line copied");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_span.start_column == 5u, "lat lir first node span column copied");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_span.end_line == 3u, "lat lir first node span end line copied");
    EXPECT_TRUE(result.record.lat_lir_first_lat_node_span.end_column == 38u, "lat lir first node span end column copied");
    EXPECT_TRUE(result.record.lat_lir_has_first_transition_node == 1, "lat lir first transition node present");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_index == 2u, "lat lir first transition node index copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_kind == LATTICRA_LIR_NODE_LAT_TRANSITION, "lat lir first transition node kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_node_name, "BootTransition") == 0, "lat lir first transition node name copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_node_value, "RootCell") == 0, "lat lir first transition node value copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_node_operator, "from") == 0, "lat lir first transition node operator copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_node_binding, "lat.transition.boot") == 0, "lat lir first transition node binding copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.start_offset == 80u, "lat lir first transition node span start copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.end_offset == 96u, "lat lir first transition node span end copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.start_line == 4u, "lat lir first transition node span line copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.start_column == 21u, "lat lir first transition node span column copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.end_line == 4u, "lat lir first transition node span end line copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_node_span.end_column == 37u, "lat lir first transition node span end column copied");
    EXPECT_TRUE(result.record.lat_lir_no_effect_chain_ok == 1, "lat lir no-effect chain copied");
    EXPECT_TRUE(result.record.lat_lir_evidence_level == 2u, "lat lir evidence level copied");
    EXPECT_TRUE(result.record.lat_lir_no_effect == 1, "lat lir no-effect copied");
    EXPECT_TRUE(result.record.lat_lir_execution_allowed == 0, "lat lir execution flag copied");
    EXPECT_TRUE(result.record.lat_lir_mutation_allowed == 0, "lat lir mutation flag copied");
    EXPECT_TRUE(result.record.lat_lir_server_allowed == 0, "lat lir server flag copied");
    EXPECT_TRUE(result.record.lat_lir_network_allowed == 0, "lat lir network flag copied");
    EXPECT_TRUE(result.record.lat_lir_recovery_allowed == 0, "lat lir recovery flag copied");
    EXPECT_TRUE(result.record.lat_lir_hardware_allowed == 0, "lat lir hardware flag copied");
    EXPECT_TRUE(result.record.lat_lir_contains_edge_count == 1u, "lat lir contains edge count copied");
    EXPECT_TRUE(result.record.lat_lir_binds_edge_count == 1u, "lat lir binds edge count copied");
    EXPECT_TRUE(result.record.lat_lir_annotates_edge_count == 1u, "lat lir annotates edge count copied");
    EXPECT_TRUE(result.record.lat_lir_orders_before_edge_count == 1u, "lat lir orders edge count copied");
    EXPECT_TRUE(result.record.lat_lir_transition_edge_count == 1u, "transition edge count copied");
    EXPECT_TRUE(result.record.lat_lir_has_first_edge == 1, "lat lir first edge present");
    EXPECT_TRUE(result.record.lat_lir_first_edge_index == 0u, "lat lir first edge index copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_from_index == 0u, "lat lir first edge from copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_to_index == 1u, "lat lir first edge to copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_kind == LATTICRA_LIR_EDGE_CONTAINS, "lat lir first edge kind copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.start_offset == 64u, "lat lir first edge span start copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.end_offset == 80u, "lat lir first edge span end copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.start_line == 4u, "lat lir first edge span line copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.start_column == 3u, "lat lir first edge span column copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.end_line == 4u, "lat lir first edge span end line copied");
    EXPECT_TRUE(result.record.lat_lir_first_edge_span.end_column == 19u, "lat lir first edge span end column copied");
    EXPECT_TRUE(result.record.lat_lir_has_lat_state_nodes == 1, "lat state evidence copied");
    EXPECT_TRUE(result.record.lat_lir_has_lat_transition_nodes == 1, "lat transition evidence copied");
    EXPECT_TRUE(result.record.lat_lir_has_transition_source_edges == 1, "transition source evidence copied");
    EXPECT_TRUE(result.record.lat_lir_has_first_transition_source_edge == 1, "first transition source edge present");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_index == 4u, "first transition source edge index copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_from_index == 2u, "first transition source edge from copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_to_index == 1u, "first transition source edge to copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_kind == LATTICRA_LIR_EDGE_TRANSITIONS_FROM, "first transition source edge kind copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_from_node_kind == LATTICRA_LIR_NODE_LAT_TRANSITION, "first transition source edge from node kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_source_edge_from_node_name, "BootTransition") == 0, "first transition source edge from node name copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_to_node_kind == LATTICRA_LIR_NODE_LAT_STATE, "first transition source edge to node kind copied");
    EXPECT_TRUE(strcmp(result.record.lat_lir_first_transition_source_edge_to_node_name, "RootCell") == 0, "first transition source edge to node name copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.start_offset == 96u, "first transition source edge span start copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.end_offset == 112u, "first transition source edge span end copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.start_line == 5u, "first transition source edge span line copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.start_column == 7u, "first transition source edge span column copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.end_line == 5u, "first transition source edge span end line copied");
    EXPECT_TRUE(result.record.lat_lir_first_transition_source_edge_span.end_column == 23u, "first transition source edge span end column copied");
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
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline-failed");
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
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline-parse-failed");
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
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline-model-failed");
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

static int runtime_boundary_denies_network_marked_lat_pipeline_metadata(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];

    pipeline.network_allowed = 1;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline-network-denied");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.operator_confirmation = LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE;
    request.authority = &authority;
    request.lat_pipeline = &pipeline;

    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "network pipeline classification status ok");
    EXPECT_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY, "network pipeline denied");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS, "network pipeline no-effect reason");
    EXPECT_TRUE(result.network_allowed == 0, "network pipeline boundary remains denied");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "network pipeline report status ok");
    EXPECT_TRUE(strstr(report, "reason=non-no-effect-flags\n") != 0, "network pipeline reason report present");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "network pipeline boundary network report present");
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
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-pipeline-report");
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
    EXPECT_TRUE(strstr(report, "lat_pipeline_module_name=RuntimeEvidenceModule\n") != 0, "pipeline module name report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_source_len=256\n") != 0, "pipeline source length report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_declaration_count=5\n") != 0, "pipeline declaration count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_clause_count=23\n") != 0, "pipeline clause count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_declaration_count=5\n") != 0, "pipeline model declaration count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_model_clause_count=23\n") != 0, "pipeline model clause count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_node_index=1\n") != 0, "pipeline first declaration node report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_kind=state\n") != 0, "pipeline first declaration kind report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_name=RootCell\n") != 0, "pipeline first declaration name report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_source=\n") != 0, "pipeline first declaration source report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_parse_index=0\n") != 0, "pipeline first declaration parse index report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_first_clause_index=0\n") != 0, "pipeline first declaration first clause report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_clause_count=9\n") != 0, "pipeline first declaration clause count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_declaration_source_index=") != 0, "pipeline first declaration source index report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_transition_source_index=0\n") != 0, "pipeline first transition source index report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_node_index=6\n") != 0, "pipeline first clause node report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_role=field\n") != 0, "pipeline first clause role report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_effect=none\n") != 0, "pipeline first clause effect report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_name=name\n") != 0, "pipeline first clause name report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_operator==\n") != 0, "pipeline first clause operator report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_clause_value=root\n") != 0, "pipeline first clause value report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_node_count=29\n") != 0, "pipeline node count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_edge_count=29\n") != 0, "pipeline edge count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_comment_count=2\n") != 0, "pipeline comment count report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_comment_start_line=1\n") != 0, "pipeline comment line report present");
    EXPECT_TRUE(strstr(report, "lat_pipeline_first_comment_start_column=1\n") != 0, "pipeline comment column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_source_kind=lat_module\n") != 0, "lat lir source kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_module_name=RuntimeEvidenceModule\n") != 0, "lat lir module name report present");
    EXPECT_TRUE(strstr(report, "lat_lir_report_classification=materialized\n") != 0, "lat lir report classification report present");
    EXPECT_TRUE(strstr(report, "lat_lir_shape_kind=lat-module-graph\n") != 0, "lat lir shape report present");
    EXPECT_TRUE(strstr(report, "lat_lir_span_start_line=2\n") != 0, "lat lir span line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_span_start_column=1\n") != 0, "lat lir span column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_span_end_line=30\n") != 0, "lat lir span end line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_span_end_column=2\n") != 0, "lat lir span end column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_module_node_count=7\n") != 0, "lat lir node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_module_edge_count=5\n") != 0, "lat lir edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_binding_count=2\n") != 0, "lat lir binding count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_text_count=1\n") != 0, "lat lir text count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_state_node_count=1\n") != 0, "lat lir state node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_policy_node_count=1\n") != 0, "lat lir policy node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_transition_node_count=1\n") != 0, "lat lir transition node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_assertion_node_count=1\n") != 0, "lat lir assertion node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_requirement_node_count=1\n") != 0, "lat lir requirement node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_lat_effect_declaration_node_count=1\n") != 0, "lat lir effect declaration node count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_first_lat_node=1\n") != 0, "lat lir first node present report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_index=1\n") != 0, "lat lir first node index report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_kind=lat_state\n") != 0, "lat lir first node kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_name=RootCell\n") != 0, "lat lir first node name report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_value=root\n") != 0, "lat lir first node value report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_operator==\n") != 0, "lat lir first node operator report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_binding=lat.state.root\n") != 0, "lat lir first node binding report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_span_start_line=3\n") != 0, "lat lir first node span line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_span_start_column=5\n") != 0, "lat lir first node span column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_span_end_line=3\n") != 0, "lat lir first node span end line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_lat_node_span_end_column=38\n") != 0, "lat lir first node span end column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_first_transition_node=1\n") != 0, "lat lir first transition node present report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_index=2\n") != 0, "lat lir first transition node index report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_kind=lat_transition\n") != 0, "lat lir first transition node kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_name=BootTransition\n") != 0, "lat lir first transition node name report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_value=RootCell\n") != 0, "lat lir first transition node value report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_operator=from\n") != 0, "lat lir first transition node operator report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_binding=lat.transition.boot\n") != 0, "lat lir first transition node binding report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_start_offset=80\n") != 0, "lat lir first transition node span start report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_end_offset=96\n") != 0, "lat lir first transition node span end report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_start_line=4\n") != 0, "lat lir first transition node span line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_start_column=21\n") != 0, "lat lir first transition node span column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_end_line=4\n") != 0, "lat lir first transition node span end line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_node_span_end_column=37\n") != 0, "lat lir first transition node span end column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_no_effect_chain_ok=1\n") != 0, "lat lir no-effect chain report present");
    EXPECT_TRUE(strstr(report, "lat_lir_evidence_level=2\n") != 0, "lat lir evidence level report present");
    EXPECT_TRUE(strstr(report, "lat_lir_no_effect=1\n") != 0, "lat lir no-effect report present");
    EXPECT_TRUE(strstr(report, "lat_lir_execution_allowed=0\n") != 0, "lat lir execution flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_mutation_allowed=0\n") != 0, "lat lir mutation flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_server_allowed=0\n") != 0, "lat lir server flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_network_allowed=0\n") != 0, "lat lir network flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_recovery_allowed=0\n") != 0, "lat lir recovery flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_hardware_allowed=0\n") != 0, "lat lir hardware flag report present");
    EXPECT_TRUE(strstr(report, "lat_lir_contains_edge_count=1\n") != 0, "lat lir contains edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_binds_edge_count=1\n") != 0, "lat lir binds edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_annotates_edge_count=1\n") != 0, "lat lir annotates edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_orders_before_edge_count=1\n") != 0, "lat lir orders edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_transition_edge_count=1\n") != 0, "lat lir transition edge count report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_first_edge=1\n") != 0, "lat lir first edge present report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_index=0\n") != 0, "lat lir first edge index report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_from_index=0\n") != 0, "lat lir first edge from report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_to_index=1\n") != 0, "lat lir first edge to report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_kind=contains\n") != 0, "lat lir first edge kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_start_offset=64\n") != 0, "lat lir first edge span start report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_end_offset=80\n") != 0, "lat lir first edge span end report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_start_line=4\n") != 0, "lat lir first edge span line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_start_column=3\n") != 0, "lat lir first edge span column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_end_line=4\n") != 0, "lat lir first edge span end line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_edge_span_end_column=19\n") != 0, "lat lir first edge span end column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_lat_state_nodes=1\n") != 0, "lat state report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_lat_transition_nodes=1\n") != 0, "lat transition report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_transition_source_edges=1\n") != 0, "transition source report present");
    EXPECT_TRUE(strstr(report, "lat_lir_has_first_transition_source_edge=1\n") != 0, "first transition source edge present report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_index=4\n") != 0, "first transition source edge index report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_from_index=2\n") != 0, "first transition source edge from report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_to_index=1\n") != 0, "first transition source edge to report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_kind=transitions_from\n") != 0, "first transition source edge kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_from_node_kind=lat_transition\n") != 0, "first transition source edge from node kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_from_node_name=BootTransition\n") != 0, "first transition source edge from node name report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_to_node_kind=lat_state\n") != 0, "first transition source edge to node kind report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_to_node_name=RootCell\n") != 0, "first transition source edge to node name report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_start_offset=96\n") != 0, "first transition source edge span start report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_end_offset=112\n") != 0, "first transition source edge span end report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_start_line=5\n") != 0, "first transition source edge span line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_start_column=7\n") != 0, "first transition source edge span column report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_end_line=5\n") != 0, "first transition source edge span end line report present");
    EXPECT_TRUE(strstr(report, "lat_lir_first_transition_source_edge_span_end_column=23\n") != 0, "first transition source edge span end column report present");
    return 0;
}

static int runtime_boundary_keeps_lat_lir_execution_future_gated(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_pipeline_result_t pipeline = ok_pipeline();
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;

    memset(&request, 0, sizeof(request));
    copy_text(request.runtime_id, sizeof(request.runtime_id), "runtime-lat-execute-denied");
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
    if (runtime_boundary_denies_network_marked_lat_pipeline_metadata() != 0) return 1;
    if (runtime_boundary_reports_lat_pipeline_evidence() != 0) return 1;
    if (runtime_boundary_keeps_lat_lir_execution_future_gated() != 0) return 1;

    puts("runtime_boundary_lat_pipeline_evidence: ok");
    return 0;
}
