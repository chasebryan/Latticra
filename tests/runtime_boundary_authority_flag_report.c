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
    result.record.authority.status = LATTICRA_STATUS_OK;
    result.record.authority.no_effect = 1;

    if (latticra_runtime_boundary_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "report failed\n");
        return 1;
    }

    CHECK_TEXT(report, "authority_execution_allowed=0");
    CHECK_TEXT(report, "authority_mutation_allowed=0");
    CHECK_TEXT(report, "authority_server_allowed=0");
    CHECK_TEXT(report, "authority_network_allowed=0");
    CHECK_TEXT(report, "authority_recovery_allowed=0");
    CHECK_TEXT(report, "authority_hardware_allowed=0");

    puts("runtime_boundary_authority_flag_report: ok");
    return 0;
}
