#include "latticra/kernel_timer_source.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_timer_source_request_t request;
    latticra_kernel_timer_source_result_t result;
    char report[LATTICRA_KERNEL_TIMER_SOURCE_REPORT_MAX];

    if (latticra_kernel_timer_source_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_timer_source_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_timer_source_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
