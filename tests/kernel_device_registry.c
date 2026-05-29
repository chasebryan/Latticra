#include "latticra/kernel_device_registry.h"

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
    latticra_kernel_device_registry_request_t request;

    EXPECT_TRUE(latticra_kernel_device_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "default request status");
    EXPECT_TRUE(request.requested_device_count == 4u,
        "default device count");
    EXPECT_TRUE(request.vfs_namespace_request.requested_mount_count == 4u,
        "vfs namespace seed request preserved");
    EXPECT_TRUE(request.vfs_namespace_request.ipc_table_request.requested_port_count == 5u,
        "ipc table seed request preserved");
    return 0;
}

static int device_registry_seed_is_metadata_only(void) {
    latticra_kernel_device_registry_request_t request;
    latticra_kernel_device_registry_result_t result;

    EXPECT_TRUE(latticra_kernel_device_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized");
    EXPECT_TRUE(latticra_kernel_device_registry_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "device registry evaluates");
    EXPECT_TRUE(strcmp(result.registry_status, "device-registry-seed-ready") == 0,
        "registry ready");
    EXPECT_TRUE(strcmp(result.policy_status, "report-only") == 0,
        "policy report-only");
    EXPECT_TRUE(strcmp(result.vfs_namespace.namespace_status, "vfs-namespace-seed-ready") == 0,
        "vfs namespace ready");
    EXPECT_TRUE(strcmp(result.vfs_namespace.ipc_table.table_status,
            "ipc-table-seed-ready") == 0,
        "ipc table ready");
    EXPECT_TRUE(result.device_count == 4u,
        "device count four");
    EXPECT_TRUE(result.no_effect == 1,
        "device registry no-effect");
    EXPECT_TRUE(result.device_open_allowed == 0,
        "device open denied");
    EXPECT_TRUE(result.device_read_allowed == 0,
        "device read denied");
    EXPECT_TRUE(result.device_write_allowed == 0,
        "device write denied");
    EXPECT_TRUE(result.driver_bind_allowed == 0,
        "driver bind denied");
    EXPECT_TRUE(result.hardware_effect_allowed == 0,
        "hardware effect denied");
    EXPECT_TRUE(result.host_effect_allowed == 0,
        "host effect denied");

    EXPECT_TRUE(strcmp(result.devices[0].path, "/dev/console") == 0,
        "console path");
    EXPECT_TRUE(strcmp(result.devices[0].device_class, "character-device") == 0,
        "console class");
    EXPECT_TRUE(strcmp(result.devices[1].path, "/dev/root") == 0,
        "root device path");
    EXPECT_TRUE(strcmp(result.devices[2].label, "entropy-device-metadata") == 0,
        "entropy label");
    EXPECT_TRUE(strcmp(result.devices[3].device_class, "timer-device") == 0,
        "clock class");
    EXPECT_TRUE(strcmp(result.devices[0].authority_status, "device-access-denied") == 0,
        "device authority denied");
    EXPECT_TRUE(result.devices[0].declared == 1,
        "device declared");
    EXPECT_TRUE(result.devices[0].registered == 0,
        "device not registered");
    EXPECT_TRUE(result.devices[0].open_allowed == 0,
        "device open denied");
    EXPECT_TRUE(result.devices[0].read_allowed == 0,
        "device read denied");
    EXPECT_TRUE(result.devices[0].write_allowed == 0,
        "device write denied");
    EXPECT_TRUE(result.devices[0].driver_bind_allowed == 0,
        "device driver bind denied");
    EXPECT_TRUE(result.devices[0].hardware_effect_allowed == 0,
        "device hardware effect denied");
    EXPECT_TRUE(result.devices[0].host_effect_allowed == 0,
        "device host effect denied");
    EXPECT_TRUE(result.devices[0].no_effect == 1,
        "device no-effect");
    return 0;
}

static int device_registry_caps_device_count(void) {
    latticra_kernel_device_registry_request_t request;
    latticra_kernel_device_registry_result_t result;

    EXPECT_TRUE(latticra_kernel_device_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for cap");
    request.requested_device_count = 99u;
    EXPECT_TRUE(latticra_kernel_device_registry_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "device registry evaluates cap");
    EXPECT_TRUE(result.device_count == LATTICRA_KERNEL_DEVICE_REGISTRY_DEVICE_MAX,
        "device count capped");
    EXPECT_TRUE(strcmp(result.devices[4].label, "reserved-device-metadata") == 0,
        "reserved device label");
    EXPECT_TRUE(result.devices[4].device_token == 1004ul,
        "reserved device token");
    return 0;
}

static int device_registry_report_is_deterministic(void) {
    latticra_kernel_device_registry_request_t request;
    latticra_kernel_device_registry_result_t result;
    char report[LATTICRA_KERNEL_DEVICE_REGISTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_device_registry_default_request(&request) == LATTICRA_STATUS_OK,
        "request initialized for report");
    EXPECT_TRUE(latticra_kernel_device_registry_evaluate(&request, &result) == LATTICRA_STATUS_OK,
        "device registry evaluates for report");
    EXPECT_TRUE(latticra_kernel_device_registry_report(&result, report, sizeof(report)) ==
            LATTICRA_STATUS_OK,
        "report writes");

    EXPECT_TRUE(strstr(report, "LATTICRA KERNEL DEVICE REGISTRY REPORT\n") != 0,
        "report title");
    EXPECT_TRUE(strstr(report, "registry_status=device-registry-seed-ready\n") != 0,
        "registry status emitted");
    EXPECT_TRUE(strstr(report, "policy_status=report-only\n") != 0,
        "policy emitted");
    EXPECT_TRUE(strstr(report, "vfs_namespace_status=vfs-namespace-seed-ready\n") != 0,
        "vfs namespace emitted");
    EXPECT_TRUE(strstr(report, "device_count=4\n") != 0,
        "device count emitted");
    EXPECT_TRUE(strstr(report, "device_open_allowed=0\n") != 0,
        "open flag emitted");
    EXPECT_TRUE(strstr(report, "device_read_allowed=0\n") != 0,
        "read flag emitted");
    EXPECT_TRUE(strstr(report, "device_write_allowed=0\n") != 0,
        "write flag emitted");
    EXPECT_TRUE(strstr(report, "driver_bind_allowed=0\n") != 0,
        "driver flag emitted");
    EXPECT_TRUE(strstr(report, "hardware_effect_allowed=0\n") != 0,
        "hardware flag emitted");
    EXPECT_TRUE(strstr(report, "device[0].path=/dev/console\n") != 0,
        "console emitted");
    EXPECT_TRUE(strstr(report, "device[1].class=block-device\n") != 0,
        "block class emitted");
    EXPECT_TRUE(strstr(report, "device[3].label=clock-device-metadata\n") != 0,
        "clock emitted");
    EXPECT_TRUE(strstr(report, "device[0].registered=0\n") != 0,
        "registered flag emitted");
    EXPECT_TRUE(strstr(report, "device[0].no_effect=1\n") != 0,
        "device no-effect emitted");
    return 0;
}

static int null_guards_are_safe(void) {
    latticra_kernel_device_registry_result_t result;
    char report[LATTICRA_KERNEL_DEVICE_REGISTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_kernel_device_registry_default_request(0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null default request");
    EXPECT_TRUE(latticra_kernel_device_registry_evaluate(0, &result) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate request");
    EXPECT_TRUE(latticra_kernel_device_registry_evaluate(0, 0) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null evaluate result");
    EXPECT_TRUE(latticra_kernel_device_registry_report(0, report, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report result");
    EXPECT_TRUE(latticra_kernel_device_registry_report(&result, 0, sizeof(report)) ==
            LATTICRA_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(latticra_kernel_device_registry_report(&result, report, 0u) ==
            LATTICRA_STATUS_BUFFER_TOO_SMALL,
        "zero report buffer");
    return 0;
}

int main(void) {
    if (default_request_is_stable() != 0) return 1;
    if (device_registry_seed_is_metadata_only() != 0) return 1;
    if (device_registry_caps_device_count() != 0) return 1;
    if (device_registry_report_is_deterministic() != 0) return 1;
    if (null_guards_are_safe() != 0) return 1;

    puts("kernel_device_registry: ok");
    return 0;
}
