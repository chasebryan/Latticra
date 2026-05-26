#include "latticra/kernel_run_queue.h"

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
    latticra_kernel_run_queue_request_t request;

    EXPECT_TRUE(latticra_kernel_run_queue_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_queue_count == 4u,
        "default queue count");
    EXPECT_TRUE(request.scheduler_tick_request.requested_tick_count == 4u,
        "scheduler tick seed request preserved");
    EXPECT_TRUE(request.scheduler_tick_request.timer_source_request.requested_timer_count == 4u,
        "timer source seed request preserved");
    return 0;
}

static int run_queue_seed_is_metadata_only(void) {
    latticra_kernel_run_queue_request_t request;
    latticra_kernel_run_queue_result_t result;

    EXPECT_TRUE(latticra_kernel_run_queue_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_run_queue_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "run queue evaluates");
    EXPECT_TRUE(strcmp(result.queue_status, "run-queue-seed-ready") == 0,
        "run queue ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_tick.tick_status,
            "scheduler-tick-seed-ready") == 0,
        "scheduler tick ready");
    EXPECT_TRUE(strcmp(result.scheduler_tick.timer_source.timer_status,
            "timer-source-seed-ready") == 0,
        "timer source ready");
    EXPECT_TRUE(result.queue_count == 4u,
        "queue count four");
    EXPECT_TRUE(result.no_effect == 1,
        "run queue no-effect");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.enqueue_allowed == 0,
        "enqueue denied");
    EXPECT_TRUE(result.dequeue_allowed == 0,
        "dequeue denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.preemption_allowed == 0,
        "preemption denied");
    EXPECT_TRUE(result.time_accounting_allowed == 0,
        "time accounting denied");
    EXPECT_TRUE(result.process_wake_allowed == 0,
        "process wake denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.queues[0].process_label,
            "kernel-report-process-metadata") == 0,
        "queue zero process");
    EXPECT_TRUE(strcmp(result.queues[0].scheduler_slot_label,
            "kernel-report-metadata") == 0,
        "queue zero slot");
    EXPECT_TRUE(strcmp(result.queues[0].queue_class,
            "kernel-report-run-queue-entry") == 0,
        "queue zero class");
    EXPECT_TRUE(result.queues[0].queue_token == 0ul,
        "queue zero token");
    EXPECT_TRUE(result.queues[0].pid_token == 1ul,
        "queue zero pid");
    EXPECT_TRUE(result.queues[0].tick_token == 1ul,
        "queue zero tick");
    EXPECT_TRUE(result.queues[0].timer_token == 1ul,
        "queue zero timer");
    EXPECT_TRUE(result.queues[0].priority == 10ul,
        "queue zero priority");
    EXPECT_TRUE(result.queues[0].budget_ns == 1000000ul,
        "queue zero budget");
    EXPECT_TRUE(strcmp(result.queues[0].authority_status,
            "run-queue-authority-denied") == 0,
        "queue authority denied");
    EXPECT_TRUE(result.queues[0].declared == 1,
        "queue declared");
    EXPECT_TRUE(result.queues[0].enqueued == 0,
        "queue not enqueued");
    EXPECT_TRUE(result.queues[0].dequeued == 0,
        "queue not dequeued");
    EXPECT_TRUE(result.queues[0].selected == 0,
        "queue not selected");
    EXPECT_TRUE(result.queues[0].run_queue_mutation_allowed == 0,
        "queue entry run queue mutation denied");
    EXPECT_TRUE(result.queues[0].enqueue_allowed == 0,
        "queue entry enqueue denied");
    EXPECT_TRUE(result.queues[0].dequeue_allowed == 0,
        "queue entry dequeue denied");
    EXPECT_TRUE(result.queues[0].dispatch_allowed == 0,
        "queue entry dispatch denied");
    EXPECT_TRUE(result.queues[0].context_switch_allowed == 0,
        "queue entry context switch denied");
    EXPECT_TRUE(result.queues[0].no_effect == 1,
        "queue entry no-effect");
    EXPECT_TRUE(strcmp(result.queues[1].queue_class,
            "entropy-run-queue-entry") == 0,
        "entropy queue class");
    EXPECT_TRUE(strcmp(result.queues[2].queue_class,
            "console-run-queue-entry") == 0,
        "console queue class");
    EXPECT_TRUE(strcmp(result.queues[3].queue_class,
            "idle-run-queue-entry") == 0,
        "idle queue class");
    return 0;
}

static int run_queue_caps_queue_count(void) {
    latticra_kernel_run_queue_request_t request;
    latticra_kernel_run_queue_result_t result;

    EXPECT_TRUE(latticra_kernel_run_queue_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_queue_count = 99u;
    request.scheduler_tick_request.requested_tick_count = 99u;
    EXPECT_TRUE(latticra_kernel_run_queue_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "run queue evaluates cap");
    EXPECT_TRUE(result.queue_count == LATTICRA_KERNEL_RUN_QUEUE_MAX,
        "queue count capped");
    EXPECT_TRUE(strcmp(result.queues[4].queue_class,
            "reserved-run-queue-entry") == 0,
        "reserved queue class");
    EXPECT_TRUE(result.queues[4].queue_token == 5004ul,
        "reserved queue token");
    return 0;
}

static int run_queue_report_is_deterministic(void) {
    latticra_kernel_run_queue_request_t request;
    latticra_kernel_run_queue_result_t result;
    char report[LATTICRA_KERNEL_RUN_QUEUE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_run_queue_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_run_queue_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "run queue evaluates for report");
    EXPECT_TRUE(latticra_kernel_run_queue_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL RUN QUEUE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "queue_status=run-queue-seed-ready\n") != 0,
        "queue status emitted");
    EXPECT_TRUE(strstr(report, "scheduler_tick_status=scheduler-tick-seed-ready\n") != 0,
        "scheduler tick emitted");
    EXPECT_TRUE(strstr(report, "queue_count=4\n") != 0,
        "queue count emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue flag emitted");
    EXPECT_TRUE(strstr(report, "enqueue_allowed=0\n") != 0,
        "enqueue flag emitted");
    EXPECT_TRUE(strstr(report, "dequeue_allowed=0\n") != 0,
        "dequeue flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "queue[0].process_label=kernel-report-process-metadata\n") != 0,
        "queue zero process emitted");
    EXPECT_TRUE(strstr(report, "queue[0].queue_class=kernel-report-run-queue-entry\n") != 0,
        "queue zero class emitted");
    EXPECT_TRUE(strstr(report, "queue[0].enqueued=0\n") != 0,
        "enqueued emitted");
    EXPECT_TRUE(strstr(report, "queue[0].dequeued=0\n") != 0,
        "dequeued emitted");
    EXPECT_TRUE(strstr(report, "queue[0].selected=0\n") != 0,
        "selected emitted");
    EXPECT_TRUE(strstr(report, "queue[0].no_effect=1\n") != 0,
        "queue no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_run_queue_result_t result;
    char report[LATTICRA_KERNEL_RUN_QUEUE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_run_queue_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_run_queue_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_run_queue_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_run_queue_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_run_queue_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_run_queue_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (run_queue_seed_is_metadata_only() != 0) return 1;
    if (run_queue_caps_queue_count() != 0) return 1;
    if (run_queue_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_run_queue: ok");
    return 0;
}
