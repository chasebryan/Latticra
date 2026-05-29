#include "latticra/kernel_scheduler_credit.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_scheduler_credit_request_t request;
    latticra_kernel_scheduler_credit_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_CREDIT_REPORT_MAX];

    if (latticra_kernel_scheduler_credit_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_credit_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_scheduler_credit_report(&result, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
