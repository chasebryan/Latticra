#include "latticra/system_bootstrap.h"

#include <stdio.h>

int main(void) {
    latticra_system_bootstrap_request_t request;
    latticra_system_bootstrap_result_t result;
    char report[LATTICRA_SYSTEM_BOOTSTRAP_REPORT_MAX];

    if (latticra_system_bootstrap_default_request(&request) != LATTICRA_STATUS_OK) {
        fputs("system_bootstrap_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_system_bootstrap_run(&request, &result) != LATTICRA_STATUS_OK) {
        fputs("system_bootstrap_report: bootstrap run failed\n", stderr);
        return 1;
    }

    if (latticra_system_bootstrap_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("system_bootstrap_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
