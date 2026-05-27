#include "latticra/kernel_scheduler_run_entry.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_scheduler_run_entry_request_t request;
    latticra_kernel_scheduler_run_entry_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_RUN_ENTRY_REPORT_MAX];

    if (latticra_kernel_scheduler_run_entry_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_run_entry_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_run_entry_report(&result, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
