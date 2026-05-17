#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define CHECK_TRUE(value, label) \
    do { \
        if (!(value)) { \
            fprintf(stderr, "FAIL: %s\n", label); \
            return 1; \
        } \
    } while (0)

static latticra_runtime_boundary_authority_summary_t ok_authority(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    authority.no_effect = 1;
    return authority;
}

static latticra_runtime_boundary_request_t request_base(const latticra_runtime_boundary_authority_summary_t *authority) {
    latticra_runtime_boundary_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", "runtime-prereq-ok");
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.authority = authority;
    return request;
}

static int valid_render_report_allows_report_mode(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_l_ui_render_result_t render;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&render, 0, sizeof(render));
    render.status = LATTICRA_STATUS_OK;
    render.error = LATTICRA_L_UI_RENDER_OK;
    request = request_base(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.render = &render;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "render status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT, "render policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "render reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "render gate");
    CHECK_TRUE(result.record.render_status == LATTICRA_STATUS_OK, "render status copied");
    CHECK_TRUE(result.record.render_error == LATTICRA_L_UI_RENDER_OK, "render error copied");
    CHECK_TRUE(result.record.executed == 0, "render no execution");
    return 0;
}

static int valid_lat_validate_allows_validation_mode(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lat_parse_result_t lat;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&lat, 0, sizeof(lat));
    lat.status = LATTICRA_STATUS_OK;
    lat.error = LATTICRA_LAT_PARSE_OK;
    request = request_base(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.lat = &lat;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "lat status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "lat policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "lat reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "lat gate");
    CHECK_TRUE(result.record.lat_status == LATTICRA_STATUS_OK, "lat status copied");
    CHECK_TRUE(result.record.lat_error == LATTICRA_LAT_PARSE_OK, "lat error copied");
    CHECK_TRUE(result.record.executed == 0, "lat no execution");
    return 0;
}

static int valid_lir_validate_allows_validation_mode(void) {
    latticra_runtime_boundary_authority_summary_t authority = ok_authority();
    latticra_lir_module_t lir;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&lir, 0, sizeof(lir));
    lir.status = LATTICRA_STATUS_OK;
    lir.error = LATTICRA_LIR_OK;
    request = request_base(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY;
    request.lir = &lir;
    CHECK_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "lir status");
    CHECK_TRUE(result.record.policy == LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION, "lir policy");
    CHECK_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK, "lir reason");
    CHECK_TRUE(result.record.gate_state == LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED, "lir gate");
    CHECK_TRUE(result.record.lir_status == LATTICRA_STATUS_OK, "lir status copied");
    CHECK_TRUE(result.record.lir_error == LATTICRA_LIR_OK, "lir error copied");
    CHECK_TRUE(result.record.executed == 0, "lir no execution");
    return 0;
}

int main(void) {
    if (valid_render_report_allows_report_mode() != 0) return 1;
    if (valid_lat_validate_allows_validation_mode() != 0) return 1;
    if (valid_lir_validate_allows_validation_mode() != 0) return 1;
    puts("runtime_boundary_prerequisite_happy_paths: ok");
    return 0;
}
