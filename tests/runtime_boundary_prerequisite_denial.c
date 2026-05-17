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

static latticra_runtime_boundary_authority_summary_t authority_ok(void) {
    latticra_runtime_boundary_authority_summary_t authority;
    memset(&authority, 0, sizeof(authority));
    authority.status = LATTICRA_STATUS_OK;
    authority.no_effect = 1;
    return authority;
}

static latticra_runtime_boundary_request_t base_request(const latticra_runtime_boundary_authority_summary_t *authority) {
    latticra_runtime_boundary_request_t request;
    memset(&request, 0, sizeof(request));
    (void)snprintf(request.runtime_id, sizeof(request.runtime_id), "%s", "runtime-prereq");
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    request.authority = authority;
    return request;
}

static int denies_failed_render_prerequisite(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_l_ui_render_result_t render;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&render, 0, sizeof(render));
    render.status = LATTICRA_STATUS_OK;
    render.error = LATTICRA_L_UI_RENDER_LIR_FAILED;
    request = base_request(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT;
    request.render = &render;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "render classify status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED, "render prerequisite denied");
    EXPECT_TRUE(result.record.render_error == LATTICRA_L_UI_RENDER_LIR_FAILED, "render error copied");
    return 0;
}

static int denies_failed_lat_prerequisite(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_lat_parse_result_t lat;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&lat, 0, sizeof(lat));
    lat.status = LATTICRA_STATUS_OK;
    lat.error = LATTICRA_LAT_PARSE_MISSING_MODULE;
    request = base_request(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE;
    request.lat = &lat;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "lat classify status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED, "lat prerequisite denied");
    EXPECT_TRUE(result.record.lat_error == LATTICRA_LAT_PARSE_MISSING_MODULE, "lat error copied");
    return 0;
}

static int denies_failed_lir_prerequisite(void) {
    latticra_runtime_boundary_authority_summary_t authority = authority_ok();
    latticra_lir_module_t lir;
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&lir, 0, sizeof(lir));
    lir.status = LATTICRA_STATUS_OK;
    lir.error = LATTICRA_LIR_SEMANTIC_FAILED;
    request = base_request(&authority);
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE;
    request.lir = &lir;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "lir classify status");
    EXPECT_TRUE(result.record.denial == LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED, "lir prerequisite denied");
    EXPECT_TRUE(result.record.lir_error == LATTICRA_LIR_SEMANTIC_FAILED, "lir error copied");
    return 0;
}

int main(void) {
    if (denies_failed_render_prerequisite() != 0) return 1;
    if (denies_failed_lat_prerequisite() != 0) return 1;
    if (denies_failed_lir_prerequisite() != 0) return 1;
    puts("runtime_boundary_prerequisite_denial: ok");
    return 0;
}
