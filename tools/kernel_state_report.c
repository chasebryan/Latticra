#include "latticra/kernel_state.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_state_request_t request;
    latticra_kernel_state_result_t result;
    char report[LATTICRA_KERNEL_STATE_REPORT_MAX];

    if (latticra_kernel_state_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    if (latticra_kernel_state_transition(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_state_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) return 1;

    fputs(report, stdout);
    return 0;
}
