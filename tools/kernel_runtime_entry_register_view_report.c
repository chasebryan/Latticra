#include "latticra/kernel_runtime_entry_register_view.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_runtime_entry_register_view_request_t request;
    latticra_kernel_runtime_entry_register_view_result_t result;
    char report[LATTICRA_KERNEL_RUNTIME_ENTRY_REGISTER_VIEW_REPORT_MAX];

    if (latticra_kernel_runtime_entry_register_view_default_request(&request) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_runtime_entry_register_view_evaluate(&request,
            &result) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_kernel_runtime_entry_register_view_report(&result, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
