#include "latticra/kernel_interrupt_table.h"

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
    latticra_kernel_interrupt_table_request_t request;

    EXPECT_TRUE(latticra_kernel_interrupt_table_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_route_count == 4u,
        "default route count");
    EXPECT_TRUE(request.driver_catalog_request.requested_driver_count == 4u,
        "driver catalog seed request preserved");
    EXPECT_TRUE(request.driver_catalog_request.device_registry_request.requested_device_count == 4u,
        "device registry seed request preserved");
    return 0;
}

static int interrupt_table_seed_is_metadata_only(void) {
    latticra_kernel_interrupt_table_request_t request;
    latticra_kernel_interrupt_table_result_t result;

    EXPECT_TRUE(latticra_kernel_interrupt_table_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_interrupt_table_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "interrupt table evaluates");
    EXPECT_TRUE(strcmp(result.table_status, "interrupt-table-seed-ready") == 0,
        "table ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.driver_catalog.catalog_status,
            "driver-catalog-seed-ready") == 0,
        "driver catalog ready");
    EXPECT_TRUE(strcmp(result.driver_catalog.device_registry.registry_status,
            "device-registry-seed-ready") == 0,
        "device registry ready");
    EXPECT_TRUE(result.route_count == 4u,
        "route count four");
    EXPECT_TRUE(result.no_effect == 1,
        "interrupt table no-effect");
    EXPECT_TRUE(result.interrupt_mask_allowed == 0,
        "interrupt mask denied");
    EXPECT_TRUE(result.interrupt_unmask_allowed == 0,
        "interrupt unmask denied");
    EXPECT_TRUE(result.interrupt_dispatch_allowed == 0,
        "interrupt dispatch denied");
    EXPECT_TRUE(result.interrupt_ack_allowed == 0,
        "interrupt ack denied");
    EXPECT_TRUE(result.dma_allowed == 0,
        "dma denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.routes[0].driver_name, "console-driver-metadata") == 0,
        "console route driver");
    EXPECT_TRUE(result.routes[0].irq_vector == 32ul,
        "console route vector");
    EXPECT_TRUE(strcmp(result.routes[0].device_path, "/dev/console") == 0,
        "console route path");
    EXPECT_TRUE(strcmp(result.routes[1].route_class, "block-interrupt") == 0,
        "block route class");
    EXPECT_TRUE(strcmp(result.routes[2].driver_name, "entropy-driver-metadata") == 0,
        "entropy route driver");
    EXPECT_TRUE(strcmp(result.routes[3].route_class, "timer-interrupt") == 0,
        "clock route class");
    EXPECT_TRUE(strcmp(result.routes[0].authority_status, "interrupt-authority-denied") == 0,
        "interrupt authority denied");
    EXPECT_TRUE(result.routes[0].declared == 1,
        "route declared");
    EXPECT_TRUE(result.routes[0].connected == 0,
        "route not connected");
    EXPECT_TRUE(result.routes[0].enabled == 0,
        "route not enabled");
    EXPECT_TRUE(result.routes[0].mask_allowed == 0,
        "route mask denied");
    EXPECT_TRUE(result.routes[0].unmask_allowed == 0,
        "route unmask denied");
    EXPECT_TRUE(result.routes[0].dispatch_allowed == 0,
        "route dispatch denied");
    EXPECT_TRUE(result.routes[0].ack_allowed == 0,
        "route ack denied");
    EXPECT_TRUE(result.routes[0].dma_allowed == 0,
        "route dma denied");
    EXPECT_TRUE(result.routes[0].hardware_effect_allowed == 0,
        "route hardware effect denied");
    EXPECT_TRUE(result.routes[0].host_effect_allowed == 0,
        "route host effect denied");
    EXPECT_TRUE(result.routes[0].no_effect == 1,
        "route no-effect");
    return 0;
}

static int interrupt_table_caps_route_count(void) {
    latticra_kernel_interrupt_table_request_t request;
    latticra_kernel_interrupt_table_result_t result;

    EXPECT_TRUE(latticra_kernel_interrupt_table_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_route_count = 99u;
    EXPECT_TRUE(latticra_kernel_interrupt_table_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "interrupt table evaluates cap");
    EXPECT_TRUE(result.route_count == LATTICRA_KERNEL_INTERRUPT_TABLE_ROUTE_MAX,
        "route count capped");
    EXPECT_TRUE(strcmp(result.routes[4].driver_name, "reserved-driver-metadata") == 0,
        "reserved route driver");
    EXPECT_TRUE(result.routes[4].irq_vector == 132ul,
        "reserved route vector");
    return 0;
}

static int interrupt_table_report_is_deterministic(void) {
    latticra_kernel_interrupt_table_request_t request;
    latticra_kernel_interrupt_table_result_t result;
    char report[LATTICRA_KERNEL_INTERRUPT_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_interrupt_table_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_interrupt_table_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "interrupt table evaluates for report");
    EXPECT_TRUE(latticra_kernel_interrupt_table_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL INTERRUPT TABLE REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "table_status=interrupt-table-seed-ready\n") != 0,
        "table status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "driver_catalog_status=driver-catalog-seed-ready\n") != 0,
        "driver catalog emitted");
    EXPECT_TRUE(strstr(report, "route_count=4\n") != 0,
        "route count emitted");
    EXPECT_TRUE(strstr(report, "interrupt_mask_allowed=0\n") != 0,
        "mask flag emitted");
    EXPECT_TRUE(strstr(report, "interrupt_unmask_allowed=0\n") != 0,
        "unmask flag emitted");
    EXPECT_TRUE(strstr(report, "interrupt_dispatch_allowed=0\n") != 0,
        "dispatch flag emitted");
    EXPECT_TRUE(strstr(report, "interrupt_ack_allowed=0\n") != 0,
        "ack flag emitted");
    EXPECT_TRUE(strstr(report, "dma_allowed=0\n") != 0,
        "dma flag emitted");
    EXPECT_TRUE(strstr(report, "route[0].driver_name=console-driver-metadata\n") != 0,
        "console route emitted");
    EXPECT_TRUE(strstr(report, "route[0].irq_vector=32\n") != 0,
        "console vector emitted");
    EXPECT_TRUE(strstr(report, "route[1].route_class=block-interrupt\n") != 0,
        "block class emitted");
    EXPECT_TRUE(strstr(report, "route[3].route_class=timer-interrupt\n") != 0,
        "clock emitted");
    EXPECT_TRUE(strstr(report, "route[0].connected=0\n") != 0,
        "connected flag emitted");
    EXPECT_TRUE(strstr(report, "route[0].enabled=0\n") != 0,
        "enabled flag emitted");
    EXPECT_TRUE(strstr(report, "route[0].no_effect=1\n") != 0,
        "route no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_interrupt_table_result_t result;
    char report[LATTICRA_KERNEL_INTERRUPT_TABLE_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_interrupt_table_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_interrupt_table_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_interrupt_table_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_interrupt_table_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_interrupt_table_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_interrupt_table_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (interrupt_table_seed_is_metadata_only() != 0) return 1;
    if (interrupt_table_caps_route_count() != 0) return 1;
    if (interrupt_table_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_interrupt_table: ok");
    return 0;
}
