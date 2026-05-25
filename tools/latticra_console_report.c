#include "latticra/latticra_console.h"

#include <stdio.h>

int main(void) {
    latticra_console_request_t request;
    latticra_console_result_t result;
    char report[LATTICRA_CONSOLE_REPORT_MAX];

    if (latticra_console_default_request(&request) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: default request failed\n", stderr);
        return 1;
    }

    if (latticra_console_initialize(&request, &result) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: initialize failed\n", stderr);
        return 1;
    }

    if (latticra_console_report(&result, report, sizeof(report)) != LATTICRA_STATUS_OK) {
        fputs("latticra_console_report: report render failed\n", stderr);
        return 1;
    }

    fputs(report, stdout);
    return 0;
}
