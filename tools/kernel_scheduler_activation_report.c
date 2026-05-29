#include "latticra/kernel_scheduler_activation.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_scheduler_activation_request_t request;
    latticra_kernel_scheduler_activation_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_REPORT_MAX];

    if (latticra_kernel_scheduler_activation_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_activation_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_activation_report(&result, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
