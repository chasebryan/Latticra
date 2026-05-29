#include "latticra/kernel_device_registry.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_device_registry_request_t request;
    latticra_kernel_device_registry_result_t result;
    char report[LATTICRA_KERNEL_DEVICE_REGISTRY_REPORT_MAX];

    if (latticra_kernel_device_registry_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_device_registry_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_device_registry_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
