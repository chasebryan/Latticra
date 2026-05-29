#include "latticra/kernel_vfs_namespace.h"

#include <stdio.h>

int main(void) {
    latticra_kernel_vfs_namespace_request_t request;
    latticra_kernel_vfs_namespace_result_t result;
    char report[LATTICRA_KERNEL_VFS_NAMESPACE_REPORT_MAX];

    if (latticra_kernel_vfs_namespace_default_request(&request) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_vfs_namespace_evaluate(&request, &result) != LATTICRA_STATUS_OK) return 1;
    if (latticra_kernel_vfs_namespace_report(&result, report, sizeof(report)) !=
            LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
