#include "latticra/kernel_scheduler_tick.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_scheduler_tick_request_t request;
    latticra_kernel_scheduler_tick_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_TICK_REPORT_MAX];

    if (latticra_kernel_scheduler_tick_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_scheduler_tick_evaluate(&request, &result) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_tick_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
