#include "latticra/kernel_process_table.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_process_table_request_t request;
    latticra_kernel_process_table_result_t result;
    char report[LATTICRA_KERNEL_PROCESS_TABLE_REPORT_MAX];

    if (latticra_kernel_process_table_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_process_table_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_process_table_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
