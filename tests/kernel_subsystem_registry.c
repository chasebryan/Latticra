#include "latticra/kernel_subsystem_registry.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static const latticra_kernel_subsystem_entry_t *find_entry(
    const latticra_kernel_subsystem_registry_result_t *result,
    latticra_kernel_subsystem_kind_t kind) {
    size_t i;
    for (i = 0u; i < result->entry_count; ++i) {
        if (result->entries[i].kind == kind) return &result->entries[i];
    }
    return 0;
}

static int default_request_is_stable(void) {
    latticra_kernel_subsystem_registry_request_t request;

    EXPECT_TRUE(
        latticra_kernel_subsystem_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(strcmp(request.kernel_request.kernel_id, "latticra-kernel-seed") == 0,
        "kernel id preserved");
    return 0;
}

static int registry_evaluates_kernel_subsystems(void) {
    latticra_kernel_subsystem_registry_request_t request;
    latticra_kernel_subsystem_registry_result_t result;
    const latticra_kernel_subsystem_entry_t *entry;

    EXPECT_TRUE(latticra_kernel_subsystem_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "registry evaluates");
    EXPECT_TRUE(strcmp(result.registry_status, "registry-ready") == 0, "registry ready");
    EXPECT_TRUE(result.entry_count == LATTICRA_KERNEL_SUBSYSTEM_COUNT, "entry count");
    EXPECT_TRUE(result.no_effect == 1, "registry no-effect");
    EXPECT_TRUE(result.network_allowed == 0, "registry network denied");
    EXPECT_TRUE(result.kernel.no_effect == 1, "kernel no-effect");
    EXPECT_TRUE(result.kernel.network_allowed == 0, "kernel network denied");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_BOOT);
    EXPECT_TRUE(entry != 0, "boot entry");
    EXPECT_TRUE(strcmp(entry->status, "not-booted") == 0, "boot remains not booted");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_RUNTIME);
    EXPECT_TRUE(entry != 0, "runtime entry");
    EXPECT_TRUE(strcmp(entry->status, "not-entered") == 0, "runtime remains not entered");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_SCHEDULER);
    EXPECT_TRUE(entry != 0, "scheduler entry");
    EXPECT_TRUE(strcmp(entry->status, "not-started") == 0, "scheduler remains not started");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_MEMORY);
    EXPECT_TRUE(entry != 0, "memory entry");
    EXPECT_TRUE(strcmp(entry->status, "metadata-only") == 0, "memory remains metadata only");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_FILESYSTEM);
    EXPECT_TRUE(entry != 0, "filesystem entry");
    EXPECT_TRUE(strcmp(entry->status, "disabled") == 0, "filesystem remains disabled");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_NETWORK);
    EXPECT_TRUE(entry != 0, "network entry");
    EXPECT_TRUE(strcmp(entry->status, "disabled") == 0, "network remains disabled");
    EXPECT_TRUE(entry->network_allowed == 0, "network entry network denied");
    EXPECT_TRUE(entry->no_effect == 1, "network entry remains no-effect");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_DEVICE);
    EXPECT_TRUE(entry != 0, "device entry");
    EXPECT_TRUE(strcmp(entry->status, "disabled") == 0, "device remains disabled");

    entry = find_entry(&result, LATTICRA_KERNEL_SUBSYSTEM_SECURITY);
    EXPECT_TRUE(entry != 0, "security entry");
    EXPECT_TRUE(strcmp(entry->status, "not-production-boundary") == 0,
        "security remains not production boundary");

    return 0;
}

static int registry_report_is_deterministic(void) {
    latticra_kernel_subsystem_registry_request_t request;
    latticra_kernel_subsystem_registry_result_t result;
    char report[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_subsystem_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "registry evaluates for report");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL SUBSYSTEM REGISTRY REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "registry_status=registry-ready\n") != 0,
        "registry status emitted");
    EXPECT_TRUE(strstr(report, "entry_count=9\n") != 0,
        "entry count emitted");
    EXPECT_TRUE(strstr(report, "kernel_network_allowed=0\n") != 0,
        "kernel network emitted");
    EXPECT_TRUE(strstr(report, "network_allowed=0\n") != 0,
        "registry network emitted");
    EXPECT_TRUE(strstr(report, "subsystem[0].name=boot\n") != 0,
        "boot emitted");
    EXPECT_TRUE(strstr(report, "subsystem[1].name=runtime\n") != 0,
        "runtime emitted");
    EXPECT_TRUE(strstr(report, "subsystem[2].name=scheduler\n") != 0,
        "scheduler emitted");
    EXPECT_TRUE(strstr(report, "subsystem[3].name=memory\n") != 0,
        "memory emitted");
    EXPECT_TRUE(strstr(report, "subsystem[5].name=filesystem\n") != 0,
        "filesystem emitted");
    EXPECT_TRUE(strstr(report, "subsystem[6].name=network\n") != 0,
        "network emitted");
    EXPECT_TRUE(strstr(report, "subsystem[6].network_allowed=0\n") != 0,
        "network entry network emitted");
    EXPECT_TRUE(strstr(report, "subsystem[6].no_effect=1\n") != 0,
        "network entry no-effect emitted");
    EXPECT_TRUE(strstr(report, "subsystem[7].name=device\n") != 0,
        "device emitted");
    EXPECT_TRUE(strstr(report, "subsystem[8].name=security\n") != 0,
        "security emitted");
    EXPECT_TRUE(strstr(report, "no_effect=1\n") != 0,
        "no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_subsystem_registry_result_t result;
    char report[LATTICRA_KERNEL_SUBSYSTEM_REGISTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_subsystem_registry_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_subsystem_registry_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (registry_evaluates_kernel_subsystems() != 0) return 1;
    if (registry_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_subsystem_registry: ok");
    return 0;
}
