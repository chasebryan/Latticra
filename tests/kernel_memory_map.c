#include "latticra/kernel_memory_map.h"

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
    latticra_kernel_memory_map_request_t request;

    EXPECT_TRUE(latticra_kernel_memory_map_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_region_count == 4u, "default region count");
    EXPECT_TRUE(request.scheduler_request.requested_slot_count == 3u,
        "scheduler seed request preserved");
    return 0;
}

static int memory_map_seed_is_metadata_only(void) {
    latticra_kernel_memory_map_request_t request;
    latticra_kernel_memory_map_result_t result;

    EXPECT_TRUE(latticra_kernel_memory_map_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_memory_map_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "memory map evaluates");
    EXPECT_TRUE(strcmp(result.map_status, "memory-map-seed-ready") == 0,
        "map ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler.scheduler_status, "scheduler-seed-ready") == 0,
        "scheduler ready");
    EXPECT_TRUE(result.region_count == 4u, "region count four");
    EXPECT_TRUE(result.no_effect == 1, "map no-effect");
    EXPECT_TRUE(result.mapping_allowed == 0, "mapping remains disabled");
    EXPECT_TRUE(result.write_allowed == 0, "writes remain disabled");
    EXPECT_TRUE(result.execute_allowed == 0, "execution remains disabled");

    EXPECT_TRUE(strcmp(result.regions[0].label, "kernel-text-metadata") == 0,
        "region zero label");
    EXPECT_TRUE(strcmp(result.regions[1].label, "kernel-data-metadata") == 0,
        "region one label");
    EXPECT_TRUE(strcmp(result.regions[2].label, "kernel-stack-metadata") == 0,
        "region two label");
    EXPECT_TRUE(strcmp(result.regions[3].label, "kernel-report-metadata") == 0,
        "region three label");
    EXPECT_TRUE(strcmp(result.regions[0].map_status, "metadata-only") == 0,
        "region metadata only");
    EXPECT_TRUE(result.regions[0].mapped == 0, "region not mapped");
    EXPECT_TRUE(result.regions[0].writable == 0, "region not writable");
    EXPECT_TRUE(result.regions[0].executable == 0, "region not executable");
    EXPECT_TRUE(result.regions[0].no_effect == 1, "region no-effect");
    return 0;
}

static int memory_map_caps_region_count(void) {
    latticra_kernel_memory_map_request_t request;
    latticra_kernel_memory_map_result_t result;

    EXPECT_TRUE(latticra_kernel_memory_map_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_region_count = 99u;
    EXPECT_TRUE(latticra_kernel_memory_map_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "memory map evaluates cap");
    EXPECT_TRUE(result.region_count == LATTICRA_KERNEL_MEMORY_MAP_REGION_MAX,
        "region count capped");
    EXPECT_TRUE(strcmp(result.regions[4].label, "reserved-memory-metadata") == 0,
        "reserved region label");
    return 0;
}

static int memory_map_report_is_deterministic(void) {
    latticra_kernel_memory_map_request_t request;
    latticra_kernel_memory_map_result_t result;
    char report[LATTICRA_KERNEL_MEMORY_MAP_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_memory_map_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_memory_map_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "memory map evaluates for report");
    EXPECT_TRUE(latticra_kernel_memory_map_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL MEMORY MAP REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "map_status=memory-map-seed-ready\n") != 0,
        "map status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "scheduler_status=scheduler-seed-ready\n") != 0,
        "scheduler emitted");
    EXPECT_TRUE(strstr(report, "region_count=4\n") != 0,
        "region count emitted");
    EXPECT_TRUE(strstr(report, "mapping_allowed=0\n") != 0,
        "mapping flag emitted");
    EXPECT_TRUE(strstr(report, "write_allowed=0\n") != 0,
        "write flag emitted");
    EXPECT_TRUE(strstr(report, "execute_allowed=0\n") != 0,
        "execute flag emitted");
    EXPECT_TRUE(strstr(report, "region[0].label=kernel-text-metadata\n") != 0,
        "text region emitted");
    EXPECT_TRUE(strstr(report, "region[1].label=kernel-data-metadata\n") != 0,
        "data region emitted");
    EXPECT_TRUE(strstr(report, "region[2].label=kernel-stack-metadata\n") != 0,
        "stack region emitted");
    EXPECT_TRUE(strstr(report, "region[3].label=kernel-report-metadata\n") != 0,
        "report region emitted");
    EXPECT_TRUE(strstr(report, "region[0].map_status=metadata-only\n") != 0,
        "metadata-only emitted");
    EXPECT_TRUE(strstr(report, "region[0].no_effect=1\n") != 0,
        "region no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_memory_map_result_t result;
    char report[LATTICRA_KERNEL_MEMORY_MAP_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_memory_map_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_memory_map_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_memory_map_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_memory_map_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_memory_map_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_memory_map_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (memory_map_seed_is_metadata_only() != 0) return 1;
    if (memory_map_caps_region_count() != 0) return 1;
    if (memory_map_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_memory_map: ok");
    return 0;
}
