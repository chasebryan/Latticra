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

static int runtime_boundary_smoke_classifies_without_effects(void) {
    latticra_runtime_boundary_request_t request;
    latticra_runtime_boundary_result_t result;
    memset(&request, 0, sizeof(request));
    request.request_kind = LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY;
    request.requested_effect = LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE;
    request.mode = LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY;
    EXPECT_TRUE(latticra_runtime_boundary_classify(&request, &result) == LATTICRA_STATUS_OK, "classify status");
    EXPECT_TRUE(result.no_effect == 1, "no-effect flag preserved");
    EXPECT_TRUE(result.record_count == 1u, "record count initialized");
    EXPECT_TRUE(result.execution_allowed == 0, "execution denied");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation denied");
    return 0;
}

static int runtime_boundary_report_is_bounded(void) {
    latticra_runtime_boundary_result_t result;
    char report[LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX];
    char tiny[1];
    memset(&result, 0, sizeof(result));
    result.status = LATTICRA_STATUS_OK;
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "report status");
    EXPECT_TRUE(report[0] != '\0', "report emits text");
    EXPECT_TRUE(latticra_runtime_boundary_report(&result, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer rejected");
    return 0;
}

static int runtime_boundary_null_arguments_are_rejected(void) {
    latticra_runtime_boundary_result_t result;
    EXPECT_TRUE(latticra_runtime_boundary_classify(0, &result) == LATTICRA_STATUS_OK || latticra_runtime_boundary_classify(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "null request handled");
    EXPECT_TRUE(latticra_runtime_boundary_classify(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null result rejected");
    EXPECT_TRUE(latticra_runtime_boundary_report(0, 0, 0u) == LATTICRA_STATUS_NULL_ARGUMENT, "null report args rejected");
    return 0;
}

int main(void) {
    if (runtime_boundary_smoke_classifies_without_effects() != 0) return 1;
    if (runtime_boundary_report_is_bounded() != 0) return 1;
    if (runtime_boundary_null_arguments_are_rejected() != 0) return 1;
    puts("runtime_boundary_invariants: ok");
    return 0;
}
