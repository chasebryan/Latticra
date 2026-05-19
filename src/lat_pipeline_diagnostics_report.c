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
        "semantic_diagnostic_count=%zu\n"
        "first_diagnostic_declaration_index=%zu\n"
        "first_diagnostic_clause_index=%zu\n"
        "pipeline_failed=%d\n"
        "semantic_failed=%d\n"
        "no_effect_issue=%d\n"
        "evidence_level=%u\n",
        (int)result->status,
        latticra_lat_pipeline_diagnostic_class_label(result->diagnostic_class),
        latticra_lat_pipeline_error_label(result->pipeline_error),
        latticra_lat_pipeline_stage_label(result->failed_stage),
        latticra_lat_semantic_diagnostic_class_label(result->semantic_class),
        latticra_lat_semantic_error_label(result->semantic_error),
        result->semantic_diagnostic_count,
        result->first_diagnostic_declaration_index,
        result->first_diagnostic_clause_index,
        result->pipeline_failed,
        result->semantic_failed,
        result->no_effect_issue,
        result->evidence_level);
    if (written < 0 || (size_t)written >= buffer_len) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}
