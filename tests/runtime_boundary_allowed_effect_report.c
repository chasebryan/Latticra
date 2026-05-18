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
    result.record.policy = LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT;
    result.record.denial = LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK;
    result.record.gate_state = LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED;
    result.record.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ;
    result.record.allowed_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ;

    if (latticra_runtime_boundary_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "report failed\n");
        return 1;
    }

    CHECK_TEXT(report, "requested_effect=read");
    CHECK_TEXT(report, "allowed_effect=read");

    puts("runtime_boundary_allowed_effect_report: ok");
    return 0;
}
