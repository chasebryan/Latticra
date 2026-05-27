#include "latticra/kernel_scheduler_activation.h"

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
    latticra_kernel_scheduler_activation_request_t request;

    EXPECT_TRUE(latticra_kernel_scheduler_activation_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_activation_count == 4u,
        "default activation count");
    EXPECT_TRUE(request.scheduler_handoff_request.requested_handoff_count == 4u,
        "scheduler handoff seed request preserved");
    EXPECT_TRUE(request.scheduler_handoff_request.scheduler_dispatch_request.requested_dispatch_count == 4u,
        "scheduler dispatch seed request preserved");
    return 0;
}

static int scheduler_activation_seed_is_metadata_only(void) {
    latticra_kernel_scheduler_activation_request_t request;
    latticra_kernel_scheduler_activation_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_activation_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler activation evaluates");
    EXPECT_TRUE(strcmp(result.activation_status,
            "scheduler-activation-seed-ready") == 0,
        "scheduler activation ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.scheduler_handoff.handoff_status,
            "scheduler-handoff-seed-ready") == 0,
        "scheduler handoff ready");
    EXPECT_TRUE(strcmp(result.scheduler_handoff.scheduler_dispatch.dispatch_status,
            "scheduler-dispatch-seed-ready") == 0,
        "scheduler dispatch ready");
    EXPECT_TRUE(result.activation_count == 4u,
        "activation count four");
    EXPECT_TRUE(result.no_effect == 1,
        "scheduler activation no-effect");
    EXPECT_TRUE(result.scheduler_activation_allowed == 0,
        "scheduler activation denied");
    EXPECT_TRUE(result.scheduler_handoff_allowed == 0,
        "scheduler handoff denied");
    EXPECT_TRUE(result.scheduler_dispatch_allowed == 0,
        "scheduler dispatch denied");
    EXPECT_TRUE(result.scheduler_selection_allowed == 0,
        "scheduler selection denied");
    EXPECT_TRUE(result.dispatch_allowed == 0,
        "dispatch denied");
    EXPECT_TRUE(result.run_queue_mutation_allowed == 0,
        "run queue mutation denied");
    EXPECT_TRUE(result.context_switch_allowed == 0,
        "context switch denied");
    EXPECT_TRUE(result.runtime_entry_allowed == 0,
        "runtime entry denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.activations[0].process_label,
            "kernel-report-process-metadata") == 0,
        "activation zero process");
    EXPECT_TRUE(strcmp(result.activations[0].activation_class,
            "kernel-report-scheduler-activation") == 0,
        "activation zero class");
    EXPECT_TRUE(result.activations[0].activation_token == 0ul,
        "activation zero token");
    EXPECT_TRUE(result.activations[0].handoff_token == 0ul,
        "activation zero handoff token");
    EXPECT_TRUE(result.activations[0].dispatch_token == 0ul,
        "activation zero dispatch token");
    EXPECT_TRUE(result.activations[0].selection_token == 0ul,
        "activation zero selection token");
    EXPECT_TRUE(result.activations[0].pid_token == 1ul,
        "activation zero pid");
    EXPECT_TRUE(result.activations[0].activation_rank == 1ul,
        "activation zero rank");
    EXPECT_TRUE(result.activations[0].scheduler_credit_ns == 10000000ul,
        "activation zero scheduler credit");
    EXPECT_TRUE(result.activations[0].remaining_budget_ns == 10000000ul,
        "activation zero remaining");
    EXPECT_TRUE(result.activations[0].activation_declared == 1,
        "activation zero declared");
    EXPECT_TRUE(strcmp(result.activations[0].authority_status,
            "scheduler-activation-authority-denied") == 0,
        "activation authority denied");
    EXPECT_TRUE(result.activations[0].declared == 1,
        "activation declared");
    EXPECT_TRUE(result.activations[0].activation_planned == 0,
        "activation not planned");
    EXPECT_TRUE(result.activations[0].activated == 0,
        "activation not performed");
    EXPECT_TRUE(result.activations[0].execution_entered == 0,
        "execution not entered");
    EXPECT_TRUE(result.activations[0].context_switch_planned == 0,
        "activation no context switch planned");
    EXPECT_TRUE(result.activations[0].scheduler_activation_allowed == 0,
        "entry scheduler activation denied");
    EXPECT_TRUE(result.activations[0].scheduler_handoff_allowed == 0,
        "entry scheduler handoff denied");
    EXPECT_TRUE(result.activations[0].dispatch_allowed == 0,
        "entry dispatch denied");
    EXPECT_TRUE(result.activations[0].run_queue_mutation_allowed == 0,
        "entry run queue mutation denied");
    EXPECT_TRUE(result.activations[0].context_switch_allowed == 0,
        "entry context switch denied");
    EXPECT_TRUE(result.activations[0].runtime_entry_allowed == 0,
        "entry runtime entry denied");
    EXPECT_TRUE(result.activations[0].no_effect == 1,
        "entry no-effect");
    EXPECT_TRUE(strcmp(result.activations[1].activation_class,
            "entropy-scheduler-activation") == 0,
        "entropy activation class");
    EXPECT_TRUE(strcmp(result.activations[2].activation_class,
            "console-scheduler-activation") == 0,
        "console activation class");
    EXPECT_TRUE(strcmp(result.activations[3].activation_class,
            "idle-scheduler-activation") == 0,
        "idle activation class");
    return 0;
}

static int scheduler_activation_caps_activation_count(void) {
    latticra_kernel_scheduler_activation_request_t request;
    latticra_kernel_scheduler_activation_result_t result;

    EXPECT_TRUE(latticra_kernel_scheduler_activation_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_activation_count = 99u;
    request.scheduler_handoff_request.requested_handoff_count = 99u;
    request.scheduler_handoff_request.scheduler_dispatch_request.requested_dispatch_count = 99u;
    EXPECT_TRUE(latticra_kernel_scheduler_activation_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler activation evaluates cap");
    EXPECT_TRUE(result.activation_count == LATTICRA_KERNEL_SCHEDULER_ACTIVATION_MAX,
        "activation count capped");
    EXPECT_TRUE(strcmp(result.activations[4].activation_class,
            "reserved-scheduler-activation") == 0,
        "reserved activation class");
    EXPECT_TRUE(result.activations[4].activation_token == 13004ul,
        "reserved activation token");
    EXPECT_TRUE(result.activations[4].handoff_token == 12004ul,
        "reserved handoff token");
    EXPECT_TRUE(result.activations[4].dispatch_token == 11004ul,
        "reserved dispatch token");
    return 0;
}

static int scheduler_activation_report_is_deterministic(void) {
    latticra_kernel_scheduler_activation_request_t request;
    latticra_kernel_scheduler_activation_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_activation_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "scheduler activation evaluates for report");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_report(&result, report,
            sizeof(report)) == LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report,
            "LATTICRA KERNEL SCHEDULER ACTIVATION REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report,
            "activation_status=scheduler-activation-seed-ready\n") != 0,
        "activation status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_handoff_status=scheduler-handoff-seed-ready\n") != 0,
        "scheduler handoff status emitted");
    EXPECT_TRUE(strstr(report,
            "scheduler_dispatch_status=scheduler-dispatch-seed-ready\n") != 0,
        "scheduler dispatch status emitted");
    EXPECT_TRUE(strstr(report, "activation_count=4\n") != 0,
        "activation count emitted");
    EXPECT_TRUE(strstr(report, "scheduler_activation_allowed=0\n") != 0,
        "scheduler activation flag emitted");
    EXPECT_TRUE(strstr(report, "scheduler_handoff_allowed=0\n") != 0,
        "scheduler handoff flag emitted");
    EXPECT_TRUE(strstr(report, "dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "run_queue_mutation_allowed=0\n") != 0,
        "run queue mutation flag emitted");
    EXPECT_TRUE(strstr(report, "context_switch_allowed=0\n") != 0,
        "context switch flag emitted");
    EXPECT_TRUE(strstr(report, "runtime_entry_allowed=0\n") != 0,
        "runtime entry flag emitted");
    EXPECT_TRUE(strstr(report, "activation[0].process_label=kernel-report-process-metadata\n") != 0,
        "activation zero process emitted");
    EXPECT_TRUE(strstr(report, "activation[0].activation_class=kernel-report-scheduler-activation\n") != 0,
        "activation zero class emitted");
    EXPECT_TRUE(strstr(report, "activation[0].activation_rank=1\n") != 0,
        "activation zero rank emitted");
    EXPECT_TRUE(strstr(report, "activation[0].activation_declared=1\n") != 0,
        "activation zero declared emitted");
    EXPECT_TRUE(strstr(report, "activation[0].activation_planned=0\n") != 0,
        "activation planned emitted");
    EXPECT_TRUE(strstr(report, "activation[0].activated=0\n") != 0,
        "activated emitted");
    EXPECT_TRUE(strstr(report, "activation[0].execution_entered=0\n") != 0,
        "execution entered emitted");
    EXPECT_TRUE(strstr(report, "activation[0].no_effect=1\n") != 0,
        "activation no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_scheduler_activation_result_t result;
    char report[LATTICRA_KERNEL_SCHEDULER_ACTIVATION_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_scheduler_activation_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_report(0, report,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_report(&result, 0,
            sizeof(report)) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_scheduler_activation_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (scheduler_activation_seed_is_metadata_only() != 0) return 1;
    if (scheduler_activation_caps_activation_count() != 0) return 1;
    if (scheduler_activation_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_scheduler_activation: ok");
    return 0;
}
