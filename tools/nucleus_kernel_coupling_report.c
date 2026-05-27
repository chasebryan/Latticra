#include "latticra/nucleus_kernel_coupling.h"

#include <stdio.h>

int main(void) {
    latticra_nucleus_kernel_coupling_result_t coupling;
    char report[LATTICRA_NUCLEUS_KERNEL_COUPLING_REPORT_MAX];

    if (latticra_nucleus_kernel_coupling_evaluate_default(
            &coupling) != LATTICRA_STATUS_OK) {
        return 1;
    }
    if (latticra_nucleus_kernel_coupling_report(&coupling, report,
            sizeof(report)) != LATTICRA_STATUS_OK) {
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
