#include "latticra/kernel_driver_catalog.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_driver_catalog_request_t request;
    latticra_kernel_driver_catalog_result_t result;
    char report[LATTICRA_KERNEL_DRIVER_CATALOG_REPORT_MAX];

    if (latticra_kernel_driver_catalog_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_driver_catalog_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_driver_catalog_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
