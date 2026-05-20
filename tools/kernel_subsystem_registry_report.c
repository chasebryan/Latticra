#include "latticra/kernel_subsystem_registry.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_subsystem_registry_request_t request;
    latticra_kernel_subsystem_registry_result_t result;
    char report[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_REPORT_MAX];

    if (latticra_kernel_subsystem_registry_default_request(&request) != LATTICRA_STATUS_OK) {
        fputs("kernel_subsystem_registry_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_subsystem_registry_evaluate(&request, &result) != LATTICRA_STATUS_OK) {
        fputs("kernel_subsystem_registry_report: evaluation failed\n", stderr);
        return 1;
    }

    if (latticra_kernel_subsystem_registry_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("kernel_subsystem_registry_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
