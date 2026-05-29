#include "latticra/kernel_preemption.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_preemption_request_t request;
    latticra_kernel_preemption_result_t result;
    char report[LATTICRA_KERNEL_PREEMPTION_REPORT_MAX];

    if (latticra_kernel_preemption_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_preemption_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_preemption_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
