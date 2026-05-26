#include "latticra/kernel_scheduler_handoff.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_scheduler_handoff_request_t request;
    latticra_kernel_scheduler_handoff_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_HANDOFF_REPORT_MAX];

    if (latticra_kernel_scheduler_handoff_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_handoff_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_handoff_report(&result, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
