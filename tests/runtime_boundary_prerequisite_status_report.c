#include "latticra/runtime_boundary.h"

#include <stdio.h>
#include <string.h>

#define CHECK_TEXT(haystack, needle) \
    do { \
        if (strstr((haystack), (needle)) == 0) { \
            fprintf(stderr, "missing: %s\n", (needle)); \
            return 1; \
        } \
    } while (0)

int main(void) {
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];
    memset(&result, 0, sizeof(result));
    result.status = LATTICRA_STATUS_OK;
    result.no_effect = 1;
    result.record_count = 1u;
    result.record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY;
    result.record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED;
    result.record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED;
    result.record.render_status = LATTICRA_STATUS_OK;
    result.record.render_error = LATTICRA_L_UI_RENDER_OK;
    result.record.lat_status = LATTICRA_STATUS_OK;
    result.record.lat_error = LATTICRA_LAT_PARSE_OK;
    result.record.lir_status = LATTICRA_STATUS_OK;
    result.record.lir_error = LATTICRA_LIR_OK;

    if (latticra_runtime_boundary_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "report failed\n");
        return 1;
    }

    CHECK_TEXT(report, "render_status=0");
    CHECK_TEXT(report, "render_error=0");
    CHECK_TEXT(report, "lat_status=0");
    CHECK_TEXT(report, "lat_error=0");
    CHECK_TEXT(report, "lir_status=0");
    CHECK_TEXT(report, "lir_error=0");

    puts("runtime_boundary_prerequisite_status_report: ok");
    return 0;
}
