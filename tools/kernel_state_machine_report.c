#include "latticra/kernel_state_machine.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_state_machine_t machine;
    latticra_kernel_state_machine_step_request_t request;
    latticra_kernel_state_machine_step_result_t result;
    char report[LATTICRA_KERNEL_STATE_MACHINE_REPORT_MAX];

    if (latticra_kernel_state_machine_init(&machine) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_state_machine_default_step_request(&request) != LATTICRA_STATUS_OK) return 1;

    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    if (latticra_kernel_state_machine_step(&machine, &request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_state_machine_report(&machine, report, sizeof(report)) != LATTICRA_STATUS_OK) return 1;

    fputs(report, stdout);
    return 0;
}
