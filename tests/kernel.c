#include "latticra/kernel.h"

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
    latticra_kernel_request_t request;

    EXPECT_TRUE(latticra_kernel_default_request(&request) == LATTICRA_STATUS_OK, "default request status");
    EXPECT_TRUE(strcmp(request.kernel_id, "latticra-kernel-seed") == 0, "default kernel id");
    EXPECT_TRUE(request.source_identity != 0, "source identity present");
    EXPECT_TRUE(request.source_identity_len == strlen("kernel-default"), "source identity length");
    return 0;
}

static int kernel_initialize_is_report_only(void) {
    latticra_kernel_request_t request;
    latticra_kernel_result_t result;

    EXPECT_TRUE(latticra_kernel_default_request(&request) == LATTICRA_STATUS_OK, "request initialized");
    EXPECT_TRUE(latticra_kernel_initialize(&request, &result) == LATTICRA_STATUS_OK, "kernel initialize status");
    EXPECT_TRUE(strcmp(result.kernel_status, "initialized-report-only") == 0, "kernel status");
    EXPECT_TRUE(strcmp(result.boot_status, "not-booted") == 0, "boot status");
    EXPECT_TRUE(strcmp(result.runtime_status, "not-entered") == 0, "runtime status");
    EXPECT_TRUE(strcmp(result.scheduler_status, "not-started") == 0, "scheduler status");
    EXPECT_TRUE(strcmp(result.filesystem_status, "disabled") == 0, "filesystem disabled");
    EXPECT_TRUE(strcmp(result.network_status, "disabled") == 0, "network disabled");
    EXPECT_TRUE(strcmp(result.device_status, "disabled") == 0, "device disabled");
    EXPECT_TRUE(result.no_effect == 1, "kernel no-effect");
    EXPECT_TRUE(result.execution_allowed == 0, "execution disabled");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation disabled");
    EXPECT_TRUE(result.file_io_allowed == 0, "file I/O disabled");
    EXPECT_TRUE(result.network_allowed == 0, "network disabled");
    EXPECT_TRUE(result.server_allowed == 0, "server disabled");
    EXPECT_TRUE(result.recovery_allowed == 0, "recovery disabled");
    EXPECT_TRUE(result.hardware_allowed == 0, "hardware disabled");
    EXPECT_TRUE(result.boot_allowed == 0, "boot disabled");
    EXPECT_TRUE(result.bootstrap.no_effect == 1, "bootstrap no-effect");
    EXPECT_TRUE(result.bootstrap.network_allowed == 0, "bootstrap network disabled");
    EXPECT_TRUE(result.bootstrap.server_allowed == 0, "bootstrap server disabled");
    return 0;
}

static int kernel_report_is_deterministic(void) {
    latticra_kernel_request_t request;
    latticra_kernel_result_t result;
    char report[LATTICRA_KERNEL_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_default_request(&request) == LATTICRA_STATUS_OK, "request initialized for report");
    EXPECT_TRUE(latticra_kernel_initialize(&request, &result) == LATTICRA_STATUS_OK, "kernel initialized for report");
    EXPECT_TRUE(latticra_kernel_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK, "kernel report writes");
    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL REPORT\n") != 0, "report title");
    EXPECT_TRUE(strstr(report, "kernel_id=latticra-kernel-seed\n") != 0, "kernel id emitted");
    EXPECT_TRUE(strstr(report, "kernel_status=initialized-report-only\n") != 0, "kernel status emitted");
    EXPECT_TRUE(strstr(report, "boot_status=not-booted\n") != 0, "boot status emitted");
    EXPECT_TRUE(strstr(report, "runtime_status=not-entered\n") != 0, "runtime status emitted");
    EXPECT_TRUE(strstr(report, "filesystem_status=disabled\n") != 0, "filesystem status emitted");
    EXPECT_TRUE(strstr(report, "network_status=disabled\n") != 0, "network status emitted");
    EXPECT_TRUE(strstr(report, "device_status=disabled\n") != 0, "device status emitted");
    EXPECT_TRUE(strstr(report, "bootstrap_no_effect=1\n") != 0, "bootstrap no-effect emitted");
    EXPECT_TRUE(strstr(report, "bootstrap_network_allowed=0\n") != 0, "bootstrap network flag emitted");
    EXPECT_TRUE(strstr(report, "bootstrap_server_allowed=0\n") != 0, "bootstrap server flag emitted");
    EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0, "no-effect emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0, "network flag emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_result_t result;
    char report[LATTICRA_KERNEL_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT, "null default request");
    EXPECT_TRUE(latticra_kernel_initialize(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT, "null kernel request");
    EXPECT_TRUE(latticra_kernel_initialize(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null kernel result");
    EXPECT_TRUE(latticra_kernel_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report result");
    EXPECT_TRUE(latticra_kernel_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT, "null report buffer");
    EXPECT_TRUE(latticra_kernel_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (kernel_initialize_is_report_only() != 0) return 1;
    if (kernel_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel: ok");
    return 0;
}
