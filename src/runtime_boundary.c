#include "latticra/runtime_boundary.h"

#include <string.h>

const char *latticra_runtime_boundary_request_kind_label(latticra_runtime_boundary_request_kind_t kind) { (void)kind; return "x"; }
const char *latticra_runtime_boundary_effect_label(latticra_runtime_boundary_effect_t effect) { (void)effect; return "x"; }
const char *latticra_runtime_boundary_mode_label(latticra_runtime_boundary_mode_t mode) { (void)mode; return "x"; }
const char *latticra_runtime_boundary_policy_label(latticra_runtime_boundary_policy_t policy) { (void)policy; return "x"; }
const char *latticra_runtime_boundary_denial_label(latticra_runtime_boundary_denial_t denial) { (void)denial; return "x"; }
const char *latticra_runtime_boundary_gate_state_label(latticra_runtime_boundary_gate_state_t gate_state) { (void)gate_state; return "x"; }
const char *latticra_runtime_boundary_operator_confirmation_label(latticra_runtime_boundary_operator_confirmation_t confirmation) { (void)confirmation; return "x"; }

latticra_status_t latticra_runtime_boundary_classify(const latticra_runtime_boundary_request_t *request, latticra_runtime_boundary_result_t *result) {
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    memset(result, 0, sizeof(*result));
    result->status = LATTICRA_STATUS_OK;
    result->record_count = 1u;
    result->no_effect = 1;
    (void)request;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_runtime_boundary_report(const latticra_runtime_boundary_result_t *result, char *buffer, size_t buffer_len) {
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (buffer_len < 2u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    buffer[0] = 'x';
    buffer[1] = '\0';
    return LATTICRA_STATUS_OK;
}
