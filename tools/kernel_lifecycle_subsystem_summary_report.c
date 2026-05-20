// SPDX-License-Identifier: AGPL-3.0-or-later

#include "latticra/kernel_lifecycle_subsystem_summary.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;
    latticra_kernel_lifecycle_subsystem_summary_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_REPORT_MAX];

    if (latticra_kernel_lifecycle_subsystem_summary_default_request(&request) !=
        LATTICRA_STATUS_OK) {
        fputs("kernel_lifecycle_subsystem_summary_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_lifecycle_subsystem_summary_evaluate(&request, &result) !=
        LATTICRA_STATUS_OK) {
        fputs("kernel_lifecycle_subsystem_summary_report: evaluation failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_lifecycle_subsystem_summary_report(&result, report, sizeof(report)) !=
        LATTICRA_STATUS_OK) {
        fputs("kernel_lifecycle_subsystem_summary_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
