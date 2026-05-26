#include "latticra/kernel_driver_catalog.h"

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
    latticra_kernel_driver_catalog_request_t request;

    EXPECT_TRUE(latticra_kernel_driver_catalog_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_driver_count == 4u,
        "default driver count");
    EXPECT_TRUE(request.device_registry_request.requested_device_count == 4u,
        "device registry seed request preserved");
    EXPECT_TRUE(request.device_registry_request.vfs_namespace_request.requested_mount_count == 4u,
        "vfs namespace seed request preserved");
    return 0;
}

static int driver_catalog_seed_is_metadata_only(void) {
    latticra_kernel_driver_catalog_request_t request;
    latticra_kernel_driver_catalog_result_t result;

    EXPECT_TRUE(latticra_kernel_driver_catalog_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_driver_catalog_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "driver catalog evaluates");
    EXPECT_TRUE(strcmp(result.catalog_status, "driver-catalog-seed-ready") == 0,
        "catalog ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.device_registry.registry_status,
            "device-registry-seed-ready") == 0,
        "device registry ready");
    EXPECT_TRUE(strcmp(result.device_registry.vfs_namespace.namespace_status,
            "vfs-namespace-seed-ready") == 0,
        "vfs namespace ready");
    EXPECT_TRUE(result.driver_count == 4u,
        "driver count four");
    EXPECT_TRUE(result.no_effect == 1,
        "driver catalog no-effect");
    EXPECT_TRUE(result.driver_probe_allowed == 0,
        "driver probe denied");
    EXPECT_TRUE(result.driver_load_allowed == 0,
        "driver load denied");
    EXPECT_TRUE(result.driver_bind_allowed == 0,
        "driver bind denied");
    EXPECT_TRUE(result.interrupt_allowed == 0,
        "interrupt denied");
    EXPECT_TRUE(result.dma_allowed == 0,
        "dma denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.drivers[0].name, "console-driver-metadata") == 0,
        "console driver name");
    EXPECT_TRUE(strcmp(result.drivers[0].device_path, "/dev/console") == 0,
        "console driver path");
    EXPECT_TRUE(strcmp(result.drivers[0].driver_class, "tty-console-driver") == 0,
        "console driver class");
    EXPECT_TRUE(strcmp(result.drivers[1].device_path, "/dev/root") == 0,
        "root driver path");
    EXPECT_TRUE(strcmp(result.drivers[2].name, "entropy-driver-metadata") == 0,
        "entropy driver name");
    EXPECT_TRUE(strcmp(result.drivers[3].driver_class, "monotonic-clock-driver") == 0,
        "clock driver class");
    EXPECT_TRUE(strcmp(result.drivers[0].authority_status, "driver-authority-denied") == 0,
        "driver authority denied");
    EXPECT_TRUE(result.drivers[0].declared == 1,
        "driver declared");
    EXPECT_TRUE(result.drivers[0].loaded == 0,
        "driver not loaded");
    EXPECT_TRUE(result.drivers[0].bound == 0,
        "driver not bound");
    EXPECT_TRUE(result.drivers[0].probe_allowed == 0,
        "driver probe denied");
    EXPECT_TRUE(result.drivers[0].load_allowed == 0,
        "driver load denied");
    EXPECT_TRUE(result.drivers[0].bind_allowed == 0,
        "driver bind denied");
    EXPECT_TRUE(result.drivers[0].interrupt_allowed == 0,
        "driver interrupt denied");
    EXPECT_TRUE(result.drivers[0].dma_allowed == 0,
        "driver dma denied");
    EXPECT_TRUE(result.drivers[0].hardware_effect_allowed == 0,
        "driver hardware effect denied");
    EXPECT_TRUE(result.drivers[0].host_effect_allowed == 0,
        "driver host effect denied");
    EXPECT_TRUE(result.drivers[0].no_effect == 1,
        "driver no-effect");
    return 0;
}

static int driver_catalog_caps_driver_count(void) {
    latticra_kernel_driver_catalog_request_t request;
    latticra_kernel_driver_catalog_result_t result;

    EXPECT_TRUE(latticra_kernel_driver_catalog_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_driver_count = 99u;
    EXPECT_TRUE(latticra_kernel_driver_catalog_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "driver catalog evaluates cap");
    EXPECT_TRUE(result.driver_count == LATTICRA_KERNEL_DRIVER_CATALOG_DRIVER_MAX,
        "driver count capped");
    EXPECT_TRUE(strcmp(result.drivers[4].name, "reserved-driver-metadata") == 0,
        "reserved driver name");
    EXPECT_TRUE(result.drivers[4].driver_token == 2004ul,
        "reserved driver token");
    return 0;
}

static int driver_catalog_report_is_deterministic(void) {
    latticra_kernel_driver_catalog_request_t request;
    latticra_kernel_driver_catalog_result_t result;
    char report[LATTICRA_KERNEL_DRIVER_CATALOG_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_driver_catalog_default_request(&request) ==
            LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_driver_catalog_evaluate(&request, &result) ==
            LATTICRA_STATUS_OK,
        "driver catalog evaluates for report");
    EXPECT_TRUE(latticra_kernel_driver_catalog_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL DRIVER CATALOG REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "catalog_status=driver-catalog-seed-ready\n") != 0,
        "catalog status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "device_registry_status=device-registry-seed-ready\n") != 0,
        "device registry emitted");
    EXPECT_TRUE(strstr(report, "driver_count=4\n") != 0,
        "driver count emitted");
    EXPECT_TRUE(strstr(report, "driver_probe_allowed=0\n") != 0,
        "probe flag emitted");
    EXPECT_TRUE(strstr(report, "driver_load_allowed=0\n") != 0,
        "load flag emitted");
    EXPECT_TRUE(strstr(report, "driver_bind_allowed=0\n") != 0,
        "bind flag emitted");
    EXPECT_TRUE(strstr(report, "interrupt_allowed=0\n") != 0,
        "interrupt flag emitted");
    EXPECT_TRUE(strstr(report, "dma_allowed=0\n") != 0,
        "dma flag emitted");
    EXPECT_TRUE(strstr(report, "hardware_effect_allowed=0\n") != 0,
        "hardware flag emitted");
    EXPECT_TRUE(strstr(report, "driver[0].name=console-driver-metadata\n") != 0,
        "console emitted");
    EXPECT_TRUE(strstr(report, "driver[1].device_class=block-device\n") != 0,
        "block class emitted");
    EXPECT_TRUE(strstr(report, "driver[3].driver_class=monotonic-clock-driver\n") != 0,
        "clock emitted");
    EXPECT_TRUE(strstr(report, "driver[0].loaded=0\n") != 0,
        "loaded flag emitted");
    EXPECT_TRUE(strstr(report, "driver[0].bound=0\n") != 0,
        "bound flag emitted");
    EXPECT_TRUE(strstr(report, "driver[0].no_effect=1\n") != 0,
        "driver no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_driver_catalog_result_t result;
    char report[LATTICRA_KERNEL_DRIVER_CATALOG_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_driver_catalog_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_driver_catalog_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_driver_catalog_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_driver_catalog_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_driver_catalog_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_driver_catalog_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (driver_catalog_seed_is_metadata_only() != 0) return 1;
    if (driver_catalog_caps_driver_count() != 0) return 1;
    if (driver_catalog_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_driver_catalog: ok");
    return 0;
}
