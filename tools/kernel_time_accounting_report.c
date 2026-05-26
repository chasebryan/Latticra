#include "latticra/kernel_time_accounting.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_time_accounting_request_t request;
    latticra_kernel_time_accounting_result_t result;
    char report[LATTICRA_KERNEL_TIME_ACCOUNTING_REPORT_MAX];

    if (latticra_kernel_time_accounting_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_time_accounting_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_time_accounting_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
