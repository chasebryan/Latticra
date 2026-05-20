// SPDX-License-Identifier: AGPL-3.0-or-later

#include "latticra/kernel_lifecycle_subsystem_summary.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int default_request_targets_memory_map_ready(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default summary request status");
    EXPECT_TRUE(request.lifecycle_request.gate == LATTICRA_KERNEL_STATE_GATE_ALLOW,
        "summary default lifecycle gate allow");
    EXPECT_TRUE(request.lifecycle_request.target_state == LATTICRA_KERNEL_STATE_MEMORY_MAP_READY,
        "summary default target memory-map-ready");
    EXPECT_TRUE(request.lifecycle_request.max_steps == LATTICRA_KERNEL_LIFECYCLE_STEP_MAX,
        "summary default max steps");
    EXPECT_TRUE(strcmp(request.registry_request.kernel_request.kernel_id, "latticra-kernel-seed") == 0,
        "summary default registry request seeded");
    return 0;
}

static int summary_reaches_ready_without_authority(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;
    latticra_kernel_lifecycle_subsystem_summary_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "summary request initialized");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "summary evaluates");

    EXPECT_TRUE(strcmp(result.summary_status, "summary-ready") == 0,
        "summary ready");
    EXPECT_TRUE(strcmp(result.final_state, "memory-map-ready") == 0,
        "summary final state memory-map-ready");
    EXPECT_TRUE(result.lifecycle_complete == 1,
        "summary lifecycle complete");
    EXPECT_TRUE(result.lifecycle_step_count == 4u,
        "summary four lifecycle steps");
    EXPECT_TRUE(result.lifecycle_state_change_count == 4u,
        "summary four lifecycle state changes");
    EXPECT_TRUE(result.lifecycle_state_mutated == 1,
        "summary lifecycle state mutated internally");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "summary no external effect");
    EXPECT_TRUE(result.registry_no_effect == 1,
        "summary registry no effect");
    EXPECT_TRUE(result.runtime_entry_allowed == 0,
        "summary runtime entry denied");
    EXPECT_TRUE(result.scheduler_execution_allowed == 0,
        "summary scheduler execution denied");
    EXPECT_TRUE(result.memory_allocation_allowed == 0,
        "summary memory allocation denied");
    EXPECT_TRUE(result.no_external_effect_chain == 1,
        "summary no external effect chain");
    EXPECT_TRUE(result.entry_count == LATTICRA_KERNEL_SUBSYSTEM_COUNT,
        "summary entry count");

    EXPECT_TRUE(strcmp(result.entries[0].name, "boot") == 0,
        "summary boot entry name");
    EXPECT_TRUE(strcmp(result.entries[0].lifecycle_relation, "boot-sequence-seeded") == 0,
        "summary boot relation");
    EXPECT_TRUE(strcmp(result.entries[0].authority_status, "boot-denied") == 0,
        "summary boot authority denied");
    EXPECT_TRUE(result.entries[0].lifecycle_ready == 1,
        "summary boot lifecycle ready");

    EXPECT_TRUE(strcmp(result.entries[1].name, "runtime") == 0,
        "summary runtime entry name");
    EXPECT_TRUE(strcmp(result.entries[1].lifecycle_relation, "runtime-not-entered") == 0,
        "summary runtime relation");
    EXPECT_TRUE(strcmp(result.entries[1].authority_status, "runtime-entry-denied") == 0,
        "summary runtime authority denied");
    EXPECT_TRUE(result.entries[1].lifecycle_ready == 0,
        "summary runtime not ready");

    EXPECT_TRUE(strcmp(result.entries[2].name, "scheduler") == 0,
        "summary scheduler entry name");
    EXPECT_TRUE(strcmp(result.entries[2].lifecycle_relation, "scheduler-ready-metadata") == 0,
        "summary scheduler metadata ready");
    EXPECT_TRUE(strcmp(result.entries[2].authority_status, "scheduler-execution-denied") == 0,
        "summary scheduler authority denied");
    EXPECT_TRUE(result.entries[2].lifecycle_ready == 1,
        "summary scheduler lifecycle ready");

    EXPECT_TRUE(strcmp(result.entries[3].name, "memory") == 0,
        "summary memory entry name");
    EXPECT_TRUE(strcmp(result.entries[3].lifecycle_relation, "memory-map-ready") == 0,
        "summary memory map ready");
    EXPECT_TRUE(strcmp(result.entries[3].authority_status, "memory-allocation-denied") == 0,
        "summary memory authority denied");
    EXPECT_TRUE(result.entries[3].lifecycle_ready == 1,
        "summary memory lifecycle ready");

    EXPECT_TRUE(strcmp(result.entries[4].authority_status, "process-execution-denied") == 0,
        "summary process authority denied");
    EXPECT_TRUE(strcmp(result.entries[5].authority_status, "filesystem-denied") == 0,
        "summary filesystem authority denied");
    EXPECT_TRUE(strcmp(result.entries[6].authority_status, "network-denied") == 0,
        "summary network authority denied");
    EXPECT_TRUE(strcmp(result.entries[7].authority_status, "device-denied") == 0,
        "summary device authority denied");
    EXPECT_TRUE(strcmp(result.entries[8].authority_status, "not-production-boundary") == 0,
        "summary security authority boundary");
    return 0;
}

static int summary_respects_lifecycle_step_limit(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;
    latticra_kernel_lifecycle_subsystem_summary_result_t result;

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "limited summary request initialized");
    request.lifecycle_request.max_steps = 2u;

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "limited summary evaluates");
    EXPECT_TRUE(strcmp(result.summary_status, "summary-incomplete") == 0,
        "limited summary incomplete");
    EXPECT_TRUE(strcmp(result.final_state, "registry-ready") == 0,
        "limited summary final state registry-ready");
    EXPECT_TRUE(result.lifecycle_complete == 0,
        "limited summary lifecycle incomplete");
    EXPECT_TRUE(result.lifecycle_step_count == 2u,
        "limited summary two steps");
    EXPECT_TRUE(result.entries[0].lifecycle_ready == 1,
        "limited summary boot ready");
    EXPECT_TRUE(result.entries[2].lifecycle_ready == 0,
        "limited summary scheduler not ready");
    EXPECT_TRUE(result.entries[3].lifecycle_ready == 0,
        "limited summary memory not ready");
    EXPECT_TRUE(result.external_effect_performed == 0,
        "limited summary no external effect");
    EXPECT_TRUE(result.no_external_effect_chain == 1,
        "limited summary no external effect chain");
    return 0;
}

static int summary_report_is_deterministic(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;
    latticra_kernel_lifecycle_subsystem_summary_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "report summary request initialized");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "report summary evaluates");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "summary report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT\n") != 0,
        "summary report title");
    EXPECT_TRUE(strstr(report, "summary_status=summary-ready\n") != 0,
        "summary report status");
    EXPECT_TRUE(strstr(report, "final_state=memory-map-ready\n") != 0,
        "summary report final state");
    EXPECT_TRUE(strstr(report, "lifecycle_complete=1\n") != 0,
        "summary report lifecycle complete");
    EXPECT_TRUE(strstr(report, "lifecycle_step_count=4\n") != 0,
        "summary report step count");
    EXPECT_TRUE(strstr(report, "lifecycle_state_change_count=4\n") != 0,
        "summary report state changes");
    EXPECT_TRUE(strstr(report, "external_effect_performed=0\n") != 0,
        "summary report external effect");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "summary report runtime denied");
    EXPECT_TRUE(strstr(report, "scheduler_execution_allowed=0\n") != 0,
        "summary report scheduler denied");
    EXPECT_TRUE(strstr(report, "memory_allocation_allowed=0\n") != 0,
        "summary report memory allocation denied");
    EXPECT_TRUE(strstr(report, "no_external_effect_chain=1\n") != 0,
        "summary report no external effect chain");
    EXPECT_TRUE(strstr(report, "entry_count=9\n") != 0,
        "summary report entry count");
    EXPECT_TRUE(strstr(report, "subsystem[1].authority_status=runtime-entry-denied\n") != 0,
        "summary report runtime authority");
    EXPECT_TRUE(strstr(report, "subsystem[2].lifecycle_relation=scheduler-ready-metadata\n") != 0,
        "summary report scheduler relation");
    EXPECT_TRUE(strstr(report, "subsystem[3].lifecycle_relation=memory-map-ready\n") != 0,
        "summary report memory relation");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_lifecycle_subsystem_summary_request_t request;
    latticra_kernel_lifecycle_subsystem_summary_result_t result;
    char report[LATTICRA_KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default summary request");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null summary request");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "null guard request initialized");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_evaluate(&request, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null summary result");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null summary report result");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null summary report buffer");
    EXPECT_TRUE(latticra_kernel_lifecycle_subsystem_summary_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero summary report buffer");
    return 0;
}

int main(void) {
    if (default_request_targets_memory_map_ready() != 0) return 1;
    if (summary_reaches_ready_without_authority() != 0) return 1;
    if (summary_respects_lifecycle_step_limit() != 0) return 1;
    if (summary_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_lifecycle_subsystem_summary: ok");
    return 0;
}
