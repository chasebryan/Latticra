#include "latticra/kernel.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_request_t request;
    latticra_kernel_result_t result;
    char report[LATTICRA_KERNEL_REPORT_MAX];

    if (latticra_kernel_default_request(&request) != LATTICRA_STATUS_OK) {
        fputs("kernel_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_initialize(&request, &result) != LATTICRA_STATUS_OK) {
        fputs("kernel_report: kernel initialize failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("kernel_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
