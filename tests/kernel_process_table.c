#include "latticra/kernel_process_table.h"

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
    latticra_kernel_process_table_request_t request;

    EXPECT_TRUE(latticra_kernel_process_table_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_process_count == 4u, "default process count");
    EXPECT_TRUE(request.memory_map_request.requested_region_count == 4u,
        "memory map seed request preserved");
    EXPECT_TRUE(request.memory_map_request.scheduler_request.requested_slot_count == 3u,
        "scheduler seed request preserved");
    return 0;
}

static int process_table_seed_is_metadata_only(void) {
    latticra_kernel_process_table_request_t request;
    latticra_kernel_process_table_result_t result;

    EXPECT_TRUE(latticra_kernel_process_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_process_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "process table evaluates");
    EXPECT_TRUE(strcmp(result.table_status, "process-table-seed-ready") == 0,
        "table ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.memory_map.map_status, "memory-map-seed-ready") == 0,
        "memory map ready");
    EXPECT_TRUE(strcmp(result.memory_map.scheduler.scheduler_status, "scheduler-seed-ready") == 0,
        "scheduler ready");
    EXPECT_TRUE(result.process_count == 4u, "process count four");
    EXPECT_TRUE(result.no_effect == 1, "process table no-effect");
    EXPECT_TRUE(result.process_spawn_allowed == 0, "spawn remains disabled");
    EXPECT_TRUE(result.context_switch_allowed == 0, "context switch remains disabled");
    EXPECT_TRUE(result.signal_delivery_allowed == 0, "signal delivery remains disabled");
    EXPECT_TRUE(result.address_space_mutation_allowed == 0,
        "address-space mutation remains disabled");

    EXPECT_TRUE(strcmp(result.processes[0].label, "idle-process-metadata") == 0,
        "process zero label");
    EXPECT_TRUE(strcmp(result.processes[1].label, "kernel-report-process-metadata") == 0,
        "process one label");
    EXPECT_TRUE(strcmp(result.processes[2].label, "operator-report-process-metadata") == 0,
        "process two label");
    EXPECT_TRUE(strcmp(result.processes[3].label, "supervisor-process-metadata") == 0,
        "process three label");
    EXPECT_TRUE(strcmp(result.processes[0].lifecycle_status, "declared-metadata") == 0,
        "process lifecycle metadata");
    EXPECT_TRUE(strcmp(result.processes[0].authority_status, "spawn-denied") == 0,
        "process spawn denied");
    EXPECT_TRUE(strcmp(result.processes[0].scheduler_slot_label, "idle-metadata") == 0,
        "process scheduler label");
    EXPECT_TRUE(strcmp(result.processes[0].memory_region_label, "kernel-stack-metadata") == 0,
        "process memory label");
    EXPECT_TRUE(result.processes[0].declared == 1, "process declared");
    EXPECT_TRUE(result.processes[0].runnable == 0, "process not runnable");
    EXPECT_TRUE(result.processes[0].scheduled == 0, "process not scheduled");
    EXPECT_TRUE(result.processes[0].spawned == 0, "process not spawned");
    EXPECT_TRUE(result.processes[0].no_effect == 1, "process no-effect");
    return 0;
}

static int process_table_caps_process_count(void) {
    latticra_kernel_process_table_request_t request;
    latticra_kernel_process_table_result_t result;

    EXPECT_TRUE(latticra_kernel_process_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_process_count = 99u;
    EXPECT_TRUE(latticra_kernel_process_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "process table evaluates cap");
    EXPECT_TRUE(result.process_count == LATTICRA_KERNEL_PROCESS_TABLE_PROCESS_MAX,
        "process count capped");
    EXPECT_TRUE(strcmp(result.processes[4].label, "reserved-process-metadata") == 0,
        "reserved process label");
    EXPECT_TRUE(result.processes[4].pid_token == 1004ul,
        "reserved process token");
    return 0;
}

static int process_table_report_is_deterministic(void) {
    latticra_kernel_process_table_request_t request;
    latticra_kernel_process_table_result_t result;
    char report[LATTICRA_KERNEL_PROCESS_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_process_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_process_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "process table evaluates for report");
    EXPECT_TRUE(latticra_kernel_process_table_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL PROCESS TABLE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "table_status=process-table-seed-ready\n") != 0,
        "table status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "memory_map_status=memory-map-seed-ready\n") != 0,
        "memory emitted");
    EXPECT_TRUE(strstr(report, "scheduler_status=scheduler-seed-ready\n") != 0,
        "scheduler emitted");
    EXPECT_TRUE(strstr(report, "process_count=4\n") != 0,
        "process count emitted");
    EXPECT_TRUE(strstr(report, "process_spawn_allowed=0\n") != 0,
        "spawn flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "signal_delivery_allowed=0\n") != 0,
        "signal flag emitted");
    EXPECT_TRUE(strstr(report, "address_space_mutation_allowed=0\n") != 0,
        "address-space flag emitted");
    EXPECT_TRUE(strstr(report, "process[0].label=idle-process-metadata\n") != 0,
        "idle process emitted");
    EXPECT_TRUE(strstr(report, "process[0].authority_status=spawn-denied\n") != 0,
        "authority emitted");
    EXPECT_TRUE(strstr(report, "process[0].scheduler_slot_label=idle-metadata\n") != 0,
        "scheduler label emitted");
    EXPECT_TRUE(strstr(report, "process[0].memory_region_label=kernel-stack-metadata\n") != 0,
        "memory label emitted");
    EXPECT_TRUE(strstr(report, "process[0].spawned=0\n") != 0,
        "spawned emitted");
    EXPECT_TRUE(strstr(report, "process[0].no_effect=1\n") != 0,
        "process no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_process_table_result_t result;
    char report[LATTICRA_KERNEL_PROCESS_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_process_table_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_process_table_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_process_table_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_process_table_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_process_table_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_process_table_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (process_table_seed_is_metadata_only() != 0) return 1;
    if (process_table_caps_process_count() != 0) return 1;
    if (process_table_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_process_table: ok");
    return 0;
}
