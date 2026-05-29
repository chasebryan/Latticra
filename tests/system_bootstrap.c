#include "latticra/system_bootstrap.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_is_stable(void) {
    latticra_system_bootstrap_request_t request;

    EXPECT_TRUE(latticra_system_bootstrap_default_request(&request) == LATTICRA_STATUS_OK, "default request status");
    EXPECT_TRUE(strcmp(request.bootstrap_id, "latticra-system-bootstrap") == 0, "default bootstrap id");
    EXPECT_TRUE(request.source_identity != 0, "default source identity present");
    EXPECT_TRUE(request.source_identity_len == strlen("system-bootstrap-default"), "default source identity length");
    return 0;
}

static int bootstrap_run_is_no_effect(void) {
    latticra_system_bootstrap_request_t request;
    latticra_system_bootstrap_result_t result;

    EXPECT_TRUE(latticra_system_bootstrap_default_request(&request) == LATTICRA_STATUS_OK, "request initialized");
    EXPECT_TRUE(latticra_system_bootstrap_run(&request, &result) == LATTICRA_STATUS_OK, "bootstrap run status");
    EXPECT_TRUE(result.status == LATTICRA_STATUS_OK, "result status ok");
    EXPECT_TRUE(strcmp(result.system_status, "startup-report-ready") == 0, "system status ready");
    EXPECT_TRUE(strcmp(result.effect_boundary, "no-effect") == 0, "effect boundary no-effect");
    EXPECT_TRUE(strcmp(result.runtime_entry_status, "not-entered") == 0, "runtime not entered");
    EXPECT_TRUE(result.no_effect == 1, "bootstrap no-effect");
    EXPECT_TRUE(result.execution_allowed == 0, "execution remains disabled");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation remains disabled");
    EXPECT_TRUE(result.file_io_allowed == 0, "file io remains disabled");
    EXPECT_TRUE(result.network_allowed == 0, "network remains disabled");
    EXPECT_TRUE(result.server_allowed == 0, "server remains disabled");
    EXPECT_TRUE(result.recovery_allowed == 0, "recovery remains disabled");
    EXPECT_TRUE(result.hardware_allowed == 0, "hardware remains disabled");
    EXPECT_TRUE(result.nucleus_task.network_allowed == 0, "nucleus task network remains disabled");
    EXPECT_TRUE(result.runtime_boundary.network_allowed == 0, "runtime boundary network remains disabled");
    EXPECT_TRUE(result.nucleus_task.record.executed == 0, "nucleus task not executed");
    EXPECT_TRUE(result.runtime_boundary.record.executed == 0, "runtime boundary not executed");
    return 0;
}

static int bootstrap_report_is_deterministic(void) {
    latticra_system_bootstrap_request_t request;
    latticra_system_bootstrap_result_t result;
    char report[LATTICRA_SYSTEM_BOOTSTRAP_REPORT_MAX];

    EXPECT_TRUE(latticra_system_bootstrap_default_request(&request) == LATTICRA_STATUS_OK, "request initialized for report");
    EXPECT_TRUE(latticra_system_bootstrap_run(&request, &result) == LATTICRA_STATUS_OK, "bootstrap run for report");
    EXPECT_TRUE(latticra_system_bootstrap_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "report writes");
    EXPECT_TRUE(strstr(report, "LATTICRA SYSTEM BOOTSTRAP REPORT\n") != 0, "report title");
    EXPECT_TRUE(strstr(report, "bootstrap_id=latticra-system-bootstrap\n") != 0, "bootstrap id emitted");
    EXPECT_TRUE(strstr(report, "system_status=startup-report-ready\n") != 0, "status emitted");
    EXPECT_TRUE(strstr(report, "effect_boundary=no-effect\n") != 0, "effect boundary emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_status=not-entered\n") != 0, "runtime entry emitted");
    EXPECT_TRUE(strstr(report, "nucleus_runtime_status=not-entered\n") != 0, "nucleus runtime status emitted");
    EXPECT_TRUE(strstr(report, "runtime_policy=allow-report\n") != 0, "runtime policy emitted");
    EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0, "no-effect emitted");
    EXPECT_TRUE(strstr(report, "execution_allowed=0\n") != 0, "execution flag emitted");
    EXPECT_TRUE(strstr(report, "mutation_allowed=0\n") != 0, "mutation flag emitted");
    EXPECT_TRUE(strstr(report, "file_io_allowed=0\n") != 0, "file io flag emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "network flag emitted");
    EXPECT_TRUE(strstr(report, "server_allowed=0\n") != 0, "server flag emitted");
    EXPECT_TRUE(strstr(report, "nucleus_network_allowed=0\n") != 0, "nucleus network flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_network_allowed=0\n") != 0, "runtime network flag emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_system_bootstrap_result_t result;
    char report[LATTICRA_SYSTEM_BOOTSTRAP_REPORT_MAX];

    EXPECT_TRUE(latticra_system_bootstrap_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT, "null default request");
    EXPECT_TRUE(latticra_system_bootstrap_run(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "null run request");
    EXPECT_TRUE(latticra_system_bootstrap_run(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null run result");
    EXPECT_TRUE(latticra_system_bootstrap_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report result");
    EXPECT_TRUE(latticra_system_bootstrap_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report buffer");
    EXPECT_TRUE(latticra_system_bootstrap_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (bootstrap_run_is_no_effect() != 0) return 1;
    if (bootstrap_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("system_bootstrap: ok");
    return 0;
}
