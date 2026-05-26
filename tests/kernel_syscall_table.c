#include "latticra/kernel_syscall_table.h"

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
    latticra_kernel_syscall_table_request_t request;

    EXPECT_TRUE(latticra_kernel_syscall_table_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_call_count == 8u, "default call count");
    EXPECT_TRUE(request.process_table_request.requested_process_count == 4u,
        "process table seed request preserved");
    EXPECT_TRUE(request.process_table_request.memory_map_request.requested_region_count == 4u,
        "memory map seed request preserved");
    return 0;
}

static int syscall_table_seed_is_metadata_only(void) {
    latticra_kernel_syscall_table_request_t request;
    latticra_kernel_syscall_table_result_t result;

    EXPECT_TRUE(latticra_kernel_syscall_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_syscall_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "syscall table evaluates");
    EXPECT_TRUE(strcmp(result.table_status, "syscall-table-seed-ready") == 0,
        "table ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.process_table.table_status, "process-table-seed-ready") == 0,
        "process table ready");
    EXPECT_TRUE(strcmp(result.process_table.memory_map.map_status, "memory-map-seed-ready") == 0,
        "memory map ready");
    EXPECT_TRUE(result.call_count == 8u, "call count eight");
    EXPECT_TRUE(result.no_effect == 1, "syscall table no-effect");
    EXPECT_TRUE(result.syscall_dispatch_allowed == 0, "syscall dispatch disabled");
    EXPECT_TRUE(result.host_effect_allowed == 0, "host effect disabled");
    EXPECT_TRUE(result.mutation_allowed == 0, "mutation disabled");
    EXPECT_TRUE(result.file_io_allowed == 0, "file I/O disabled");
    EXPECT_TRUE(result.network_allowed == 0, "network disabled");

    EXPECT_TRUE(strcmp(result.calls[0].name, "yield") == 0, "yield call name");
    EXPECT_TRUE(strcmp(result.calls[1].name, "spawn_process") == 0, "spawn call name");
    EXPECT_TRUE(strcmp(result.calls[3].domain, "memory") == 0, "memory domain");
    EXPECT_TRUE(strcmp(result.calls[4].authority_status, "file-io-denied") == 0,
        "file authority denied");
    EXPECT_TRUE(strcmp(result.calls[7].authority_status, "network-io-denied") == 0,
        "network authority denied");
    EXPECT_TRUE(strcmp(result.calls[0].dispatch_status, "dispatch-denied") == 0,
        "dispatch denied");
    EXPECT_TRUE(result.calls[0].declared == 1, "call declared");
    EXPECT_TRUE(result.calls[0].implemented == 0, "call not implemented");
    EXPECT_TRUE(result.calls[0].dispatch_allowed == 0, "call dispatch denied");
    EXPECT_TRUE(result.calls[0].host_effect_allowed == 0, "call host effect denied");
    EXPECT_TRUE(result.calls[0].no_effect == 1, "call no-effect");
    return 0;
}

static int syscall_table_caps_call_count(void) {
    latticra_kernel_syscall_table_request_t request;
    latticra_kernel_syscall_table_result_t result;

    EXPECT_TRUE(latticra_kernel_syscall_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_call_count = 99u;
    EXPECT_TRUE(latticra_kernel_syscall_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "syscall table evaluates cap");
    EXPECT_TRUE(result.call_count == LATTICRA_KERNEL_SYSCALL_TABLE_CALL_MAX,
        "call count capped");
    EXPECT_TRUE(strcmp(result.calls[8].name, "reserved_syscall") == 0,
        "reserved syscall name");
    EXPECT_TRUE(result.calls[8].call_number == 1008ul,
        "reserved syscall number");
    return 0;
}

static int syscall_table_report_is_deterministic(void) {
    latticra_kernel_syscall_table_request_t request;
    latticra_kernel_syscall_table_result_t result;
    char report[LATTICRA_KERNEL_SYSCALL_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_syscall_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_syscall_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "syscall table evaluates for report");
    EXPECT_TRUE(latticra_kernel_syscall_table_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL SYSCALL TABLE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "table_status=syscall-table-seed-ready\n") != 0,
        "table status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "process_table_status=process-table-seed-ready\n") != 0,
        "process table emitted");
    EXPECT_TRUE(strstr(report, "memory_map_status=memory-map-seed-ready\n") != 0,
        "memory map emitted");
    EXPECT_TRUE(strstr(report, "call_count=8\n") != 0,
        "call count emitted");
    EXPECT_TRUE(strstr(report, "syscall_dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "file_io_allowed=0\n") != 0,
        "file flag emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0,
        "network flag emitted");
    EXPECT_TRUE(strstr(report, "call[0].name=yield\n") != 0,
        "yield emitted");
    EXPECT_TRUE(strstr(report, "call[1].name=spawn_process\n") != 0,
        "spawn emitted");
    EXPECT_TRUE(strstr(report, "call[4].domain=filesystem\n") != 0,
        "filesystem domain emitted");
    EXPECT_TRUE(strstr(report, "call[7].authority_status=network-io-denied\n") != 0,
        "network denial emitted");
    EXPECT_TRUE(strstr(report, "call[0].implemented=0\n") != 0,
        "implemented flag emitted");
    EXPECT_TRUE(strstr(report, "call[0].no_effect=1\n") != 0,
        "call no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_syscall_table_result_t result;
    char report[LATTICRA_KERNEL_SYSCALL_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_syscall_table_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_syscall_table_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_syscall_table_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_syscall_table_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_syscall_table_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_syscall_table_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (syscall_table_seed_is_metadata_only() != 0) return 1;
    if (syscall_table_caps_call_count() != 0) return 1;
    if (syscall_table_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_syscall_table: ok");
    return 0;
}
