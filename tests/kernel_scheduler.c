#include "latticra/kernel_scheduler.h"

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
    latticra_kernel_scheduler_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_slot_count == 3u, "default slot count");
    EXPECT_TRUE(strcmp(request.registry_request.kernel_request.kernel_id, "latticra-kernel-seed") == 0,
        "kernel seed id preserved");
    return 0;
}

static int scheduler_seed_is_no_effect(void) {
    latticra_kernel_scheduler_request_t request;
    latticra_kernel_scheduler_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "scheduler evaluates");
    EXPECT_TRUE(strcmp(result.scheduler_status, "scheduler-seed-ready") == 0,
        "scheduler ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.registry.registry_status, "registry-ready") == 0,
        "registry ready");
    EXPECT_TRUE(result.slot_count == 3u, "slot count three");
    EXPECT_TRUE(result.no_effect == 1, "scheduler no-effect");
    EXPECT_TRUE(result.slot_selection_allowed == 0, "slot selection remains disabled");
    EXPECT_TRUE(result.scheduler_activation_allowed == 0, "scheduler activation remains disabled");

    EXPECT_TRUE(strcmp(result.slots[0].label, "idle-metadata") == 0, "slot zero label");
    EXPECT_TRUE(strcmp(result.slots[1].label, "kernel-report-metadata") == 0, "slot one label");
    EXPECT_TRUE(strcmp(result.slots[2].label, "operator-report-metadata") == 0, "slot two label");
    EXPECT_TRUE(strcmp(result.slots[0].selection_status, "not-selected") == 0, "slot not selected");
    EXPECT_TRUE(result.slots[0].selectable == 0, "slot not selectable");
    EXPECT_TRUE(result.slots[0].selected == 0, "slot not selected flag");
    EXPECT_TRUE(result.slots[0].no_effect == 1, "slot no-effect");
    return 0;
}

static int scheduler_caps_slot_count(void) {
    latticra_kernel_scheduler_request_t request;
    latticra_kernel_scheduler_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_slot_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "scheduler evaluates cap");
    EXPECT_TRUE(result.slot_count == LATTICRA_KERNEL_SCHEDULER_SLOT_MAX,
        "slot count capped");
    EXPECT_TRUE(strcmp(result.slots[3].label, "reserved-metadata") == 0,
        "reserved slot label");
    return 0;
}

static int scheduler_report_is_deterministic(void) {
    latticra_kernel_scheduler_request_t request;
    latticra_kernel_scheduler_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "scheduler evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_report(&result, report, sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL SCHEDULER REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "scheduler_status=scheduler-seed-ready\n") != 0,
        "scheduler status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "registry_status=registry-ready\n") != 0,
        "registry emitted");
    EXPECT_TRUE(strstr(report, "slot_count=3\n") != 0,
        "slot count emitted");
    EXPECT_TRUE(strstr(report, "slot_selection_allowed=0\n") != 0,
        "slot selection emitted");
    EXPECT_TRUE(strstr(report, "scheduler_activation_allowed=0\n") != 0,
        "activation emitted");
    EXPECT_TRUE(strstr(report, "slot[0].label=idle-metadata\n") != 0,
        "slot zero emitted");
    EXPECT_TRUE(strstr(report, "slot[1].label=kernel-report-metadata\n") != 0,
        "slot one emitted");
    EXPECT_TRUE(strstr(report, "slot[2].label=operator-report-metadata\n") != 0,
        "slot two emitted");
    EXPECT_TRUE(strstr(report, "slot[0].selection_status=not-selected\n") != 0,
        "selection status emitted");
    EXPECT_TRUE(strstr(report, "slot[0].no_effect=1\n") != 0,
        "slot no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_report(0, report, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_report(&result, 0, sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_report(&result, report, 0u) == LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_seed_is_no_effect() != 0) return 1;
    if (scheduler_caps_slot_count() != 0) return 1;
    if (scheduler_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler: ok");
    return 0;
}
