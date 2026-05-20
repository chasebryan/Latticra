// SPDX-License-Identifier: AGPL-3.0-or-later

#include "latticra/kernel_lifecycle.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_lifecycle_request_t request;
    latticra_kernel_lifecycle_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_REPORT_MAX];

    if (latticra_kernel_lifecycle_default_request(&request) != LATTICRA_STATUS_OK) return 1;

    request.gate = LATTICRA_KERNEL_STATE_GATE_ALLOW;

    if (latticra_kernel_lifecycle_run(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_lifecycle_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) return 1;

    fputs(report, stdout);
    return 0;
}
