#include "latticra/kernel_ipc_table.h"

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
    latticra_kernel_ipc_table_request_t request;

    EXPECT_TRUE(latticra_kernel_ipc_table_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_port_count == 5u,
        "default port count");
    EXPECT_TRUE(request.syscall_table_request.requested_call_count == 8u,
        "syscall table seed request preserved");
    EXPECT_TRUE(request.syscall_table_request.process_table_request.requested_process_count == 4u,
        "process table seed request preserved");
    return 0;
}

static int ipc_table_seed_is_metadata_only(void) {
    latticra_kernel_ipc_table_request_t request;
    latticra_kernel_ipc_table_result_t result;

    EXPECT_TRUE(latticra_kernel_ipc_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_ipc_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "ipc table evaluates");
    EXPECT_TRUE(strcmp(result.table_status, "ipc-table-seed-ready") == 0,
        "table ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.syscall_table.table_status, "syscall-table-seed-ready") == 0,
        "syscall table ready");
    EXPECT_TRUE(strcmp(result.syscall_table.process_table.table_status,
            "process-table-seed-ready") == 0,
        "process table ready");
    EXPECT_TRUE(result.port_count == 5u,
        "port count five");
    EXPECT_TRUE(result.no_effect == 1,
        "ipc table no-effect");
    EXPECT_TRUE(result.ipc_send_allowed == 0,
        "ipc send denied");
    EXPECT_TRUE(result.ipc_receive_allowed == 0,
        "ipc receive denied");
    EXPECT_TRUE(result.queue_mutation_allowed == 0,
        "queue mutation denied");
    EXPECT_TRUE(result.endpoint_bind_allowed == 0,
        "endpoint bind denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.ports[0].label, "kernel-control-port-metadata") == 0,
        "control port label");
    EXPECT_TRUE(strcmp(result.ports[1].domain, "process") == 0,
        "process port domain");
    EXPECT_TRUE(strcmp(result.ports[2].authority_status, "ipc-queue-denied") == 0,
        "queue authority denied");
    EXPECT_TRUE(strcmp(result.ports[3].authority_status, "ipc-endpoint-bind-denied") == 0,
        "endpoint authority denied");
    EXPECT_TRUE(strcmp(result.ports[4].domain, "network") == 0,
        "network port domain");
    EXPECT_TRUE(result.ports[0].declared == 1,
        "port declared");
    EXPECT_TRUE(result.ports[0].bound == 0,
        "port not bound");
    EXPECT_TRUE(result.ports[0].send_allowed == 0,
        "port send denied");
    EXPECT_TRUE(result.ports[0].receive_allowed == 0,
        "port receive denied");
    EXPECT_TRUE(result.ports[0].queue_mutation_allowed == 0,
        "port queue mutation denied");
    EXPECT_TRUE(result.ports[0].host_effect_allowed == 0,
        "port host effect denied");
    EXPECT_TRUE(result.ports[0].no_effect == 1,
        "port no-effect");
    return 0;
}

static int ipc_table_caps_port_count(void) {
    latticra_kernel_ipc_table_request_t request;
    latticra_kernel_ipc_table_result_t result;

    EXPECT_TRUE(latticra_kernel_ipc_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_port_count = 99u;
    EXPECT_TRUE(latticra_kernel_ipc_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "ipc table evaluates cap");
    EXPECT_TRUE(result.port_count == LATTICRA_KERNEL_IPC_TABLE_PORT_MAX,
        "port count capped");
    EXPECT_TRUE(strcmp(result.ports[5].label, "reserved-ipc-port-metadata") == 0,
        "reserved port label");
    EXPECT_TRUE(result.ports[5].port_token == 1005ul,
        "reserved port token");
    return 0;
}

static int ipc_table_report_is_deterministic(void) {
    latticra_kernel_ipc_table_request_t request;
    latticra_kernel_ipc_table_result_t result;
    char report[LATTICRA_KERNEL_IPC_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_ipc_table_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_ipc_table_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "ipc table evaluates for report");
    EXPECT_TRUE(latticra_kernel_ipc_table_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL IPC TABLE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "table_status=ipc-table-seed-ready\n") != 0,
        "table status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "syscall_table_status=syscall-table-seed-ready\n") != 0,
        "syscall table emitted");
    EXPECT_TRUE(strstr(report, "process_table_status=process-table-seed-ready\n") != 0,
        "process table emitted");
    EXPECT_TRUE(strstr(report, "port_count=5\n") != 0,
        "port count emitted");
    EXPECT_TRUE(strstr(report, "ipc_send_allowed=0\n") != 0,
        "send flag emitted");
    EXPECT_TRUE(strstr(report, "ipc_receive_allowed=0\n") != 0,
        "receive flag emitted");
    EXPECT_TRUE(strstr(report, "queue_mutation_allowed=0\n") != 0,
        "queue flag emitted");
    EXPECT_TRUE(strstr(report, "endpoint_bind_allowed=0\n") != 0,
        "endpoint flag emitted");
    EXPECT_TRUE(strstr(report, "port[0].label=kernel-control-port-metadata\n") != 0,
        "control port emitted");
    EXPECT_TRUE(strstr(report, "port[2].authority_status=ipc-queue-denied\n") != 0,
        "queue denial emitted");
    EXPECT_TRUE(strstr(report, "port[4].domain=network\n") != 0,
        "network port emitted");
    EXPECT_TRUE(strstr(report, "port[0].bound=0\n") != 0,
        "bound flag emitted");
    EXPECT_TRUE(strstr(report, "port[0].no_effect=1\n") != 0,
        "port no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_ipc_table_result_t result;
    char report[LATTICRA_KERNEL_IPC_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_ipc_table_default_request(0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_ipc_table_evaluate(0, &result) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_ipc_table_evaluate(0, 0) == LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_ipc_table_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_ipc_table_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_ipc_table_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (ipc_table_seed_is_metadata_only() != 0) return 1;
    if (ipc_table_caps_port_count() != 0) return 1;
    if (ipc_table_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_ipc_table: ok");
    return 0;
}
