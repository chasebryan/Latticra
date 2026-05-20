#include "latticra/kernel_memory_map.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_memory_map_request_t request;
    latticra_kernel_memory_map_result_t result;
    char report[LATTICRA_KERNEL_MEMORY_MAP_REPORT_MAX];

    if (latticra_kernel_memory_map_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_memory_map_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_memory_map_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) return 1;

    fputs(report, stdout);
    return 0;
}
