#include "latticra/lat_pipeline_diagnostics.h"

#include <stdio.h>

latticra_status_t latticra_lat_pipeline_diagnostics_report(
    const latticra_lat_pipeline_diagnostic_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = '\0';
    written = snprintf(
        buffer,
        buffer_len,
        "LAT PIPELINE DIAGNOSTIC REPORT\n"
        "status=%d\n"
        "diagnostic_class=%s\n"
        "pipeline_error=%s\n"
        "failed_stage=%s\n"
        "semantic_class=%s\n"
        "semantic_error=%s\n"
        "lowering_class=%s\n"
        "lowering_error=%s\n"
        "model_error=%s\n"
        "lir_error=%s\n"
        "comment_count=%zu\n"
        "first_comment_start_offset=%zu\n"
        "first_comment_end_offset=%zu\n"
        "first_comment_start_line=%zu\n"
        "first_comment_start_column=%zu\n"
        "first_comment_end_line=%zu\n"
        "first_comment_end_column=%zu\n"
        "semantic_diagnostic_count=%zu\n"
        "first_diagnostic_declaration_index=%zu\n"
        "first_diagnostic_clause_index=%zu\n"
        "lowering_model_declaration_count=%zu\n"
        "lowering_model_clause_count=%zu\n"
        "lowering_first_declaration_node_index=%zu\n"
        "lowering_first_declaration_kind=%s\n"
        "lowering_first_declaration_name=%s\n"
        "lowering_first_declaration_source=%s\n"
        "lowering_first_declaration_parse_index=%zu\n"
        "lowering_first_declaration_first_clause_index=%zu\n"
        "lowering_first_declaration_clause_count=%zu\n"
        "lowering_first_declaration_source_index=%zu\n"
        "lowering_first_transition_source_index=%zu\n"
        "lowering_first_clause_node_index=%zu\n"
        "lowering_first_clause_role=%s\n"
        "lowering_first_clause_effect=%s\n"
        "lowering_first_clause_name=%s\n"
        "lowering_first_clause_operator=%s\n"
        "lowering_first_clause_value=%s\n"
        "pipeline_failed=%d\n"
        "semantic_failed=%d\n"
        "lowering_failed=%d\n"
        "model_failed=%d\n"
        "lir_failed=%d\n"
        "no_effect_issue=%d\n"
        "evidence_level=%u\n",
        (int)result->status,
        latticra_lat_pipeline_diagnostic_class_label(result->diagnostic_class),
        latticra_lat_pipeline_error_label(result->pipeline_error),
        latticra_lat_pipeline_stage_label(result->failed_stage),
        latticra_lat_semantic_diagnostic_class_label(result->semantic_class),
        latticra_lat_semantic_error_label(result->semantic_error),
        latticra_lat_to_lir_diagnostic_class_label(result->lowering_class),
        latticra_lat_to_lir_error_label(result->lowering_error),
        latticra_lat_model_error_label(result->model_error),
        latticra_lir_error_label(result->lir_error),
        result->comment_count,
        result->first_comment_span.start_offset,
        result->first_comment_span.end_offset,
        result->first_comment_span.start_line,
        result->first_comment_span.start_column,
        result->first_comment_span.end_line,
        result->first_comment_span.end_column,
        result->semantic_diagnostic_count,
        result->first_diagnostic_declaration_index,
        result->first_diagnostic_clause_index,
        result->lowering_model_declaration_count,
        result->lowering_model_clause_count,
        result->lowering_first_declaration_node_index,
        latticra_lat_declaration_kind_label(result->lowering_first_declaration_kind),
        result->lowering_first_declaration_name,
        result->lowering_first_declaration_source,
        result->lowering_first_declaration_parse_index,
        result->lowering_first_declaration_first_clause_index,
        result->lowering_first_declaration_clause_count,
        result->lowering_first_declaration_source_index,
        result->lowering_first_transition_source_index,
        result->lowering_first_clause_node_index,
        latticra_lat_model_clause_role_label(result->lowering_first_clause_role),
        latticra_lat_effect_label(result->lowering_first_clause_effect),
        result->lowering_first_clause_name,
        result->lowering_first_clause_operator,
        result->lowering_first_clause_value,
        result->pipeline_failed,
        result->semantic_failed,
        result->lowering_failed,
        result->model_failed,
        result->lir_failed,
        result->no_effect_issue,
        result->evidence_level);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
