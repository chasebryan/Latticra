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
    (void)snprintf(result.record.authority.status_label, sizeof(result.record.authority.status_label), "%s", "ok");
    (void)snprintf(result.record.authority.validator_label, sizeof(result.record.authority.validator_label), "%s", "runtime-authority");
    (void)snprintf(result.record.authority.requested_effect_label, sizeof(result.record.authority.requested_effect_label), "%s", "none");
    (void)snprintf(result.record.authority.denial_reason, sizeof(result.record.authority.denial_reason), "%s", "runtime-disabled");

    if (latticra_runtime_boundary_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "report failed\n");
        return 1;
    }

    CHECK_TEXT(report, "authority_status_label=ok");
    CHECK_TEXT(report, "authority_validator=runtime-authority");
    CHECK_TEXT(report, "authority_requested_effect=none");
    CHECK_TEXT(report, "authority_reason=runtime-disabled");

    puts("runtime_boundary_authority_label_report: ok");
    return 0;
}
