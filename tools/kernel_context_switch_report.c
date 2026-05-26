#include "latticra/kernel_context_switch.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_context_switch_request_t request;
    latticra_kernel_context_switch_result_t result;
    char report[LATTICRA_KERNEL_CONTEXT_SWITCH_REPORT_MAX];

    if (latticra_kernel_context_switch_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_context_switch_evaluate(&request, &result) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_context_switch_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
